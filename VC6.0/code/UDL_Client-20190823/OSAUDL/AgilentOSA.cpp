// AgilentOSA.cpp: implementation of the AgilentOSA class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\\include\\OSA.h"
#include "math.h"

#include "..\\include\\NFLib.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define TXLENS 1024
#define RXMINLENS 1024
#define MAX_SCAN_DATA 5001
#define MAX_SWEEP_POINT 10000

#define OSA_SCAN_MIN_WAVE                   1525
#define OSA_SCAN_MAX_WAVE                   1570
#define SCAN_BW_SEN                         0.2
#define MANUAL_OFFSET                       0.6
#define SCAN_SENSITIVITY                    -70
#define INCLUDE_SHOT_NOISE                  0   // 0: Not include shot noise// 1: Include shot noise
#define EXCLUDE_SRC_ASE_POWER               1   // 0: Don't care source(input power) ASE power// 1: Noise figure exclude source ASE power
#define RBW_CALC_MODE                       0   // 0: Average Measure RBW// 1: Actual Measure RB // 2: Scan Setting RBW
#define AUTO_MODE                           1   // Interpolation offset, auto or manual specific value
#define SOURCE_SIGNAL_OFFSET                0
#define AMP_SIGNAL_OFFSET                   0
#define SCAN_WL_STEP                        0.001
#define SCAN_BW_SEN_B                       0.2

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


/************************************************************************
*  函数名称:OpenDevice													*
*  功能: 打开连接设备,适用：                                            *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142AAgilent 86142B						*
*  输入:																*
*		1.stType:设备类型结构体											*
*       2.pszDeviceAddr:通讯信息										*
*  输出数据类型:stDevType, char* 										*
*  输出:																*
*       comHandle:基础通讯接口Handle									*
*  输出数据类型:CommunicationHandle										*
*  返回值:																*
*             0: 函数执行成功。											*
*			  0xXXXXXXXX: 其他错误									    *
*  返回值类型:DWORD														*
*  创建日期:2013-10-15													*
*  创建人:陈可明														*
*  修改历史:无															*
*************************************************************************/
DWORD AgilentOSA::OpenDevice(stDevType stType, char* pszDeviceAddr, unsigned long *comHandle)
{
	DWORD dwErrorCode = SUCCESS;

	try
	{
		m_bNFLib = FALSE;
		
		//打开设备
		dwErrorCode = m_Commun.OpenDevice(pszDeviceAddr, *comHandle);
		if (SUCCESS != dwErrorCode) 
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

		int nLen = strlen(pszDeviceAddr);

		if ('1' == pszDeviceAddr[nLen-3])
		{
			m_bNFLib = TRUE;
		}
		else
		{
			m_bNFLib = FALSE;
		}

	}
	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return ERROR_OSA|UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

/************************************************************************
*  函数名称:CloseDevice													*
*  功能: 退出连接设备,适用：                                            *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  输入: 无																*
*  输出：无                                                             *
*  返回值:																*
*             0: 函数执行成功。											*
*			  0xXXXXXXXX: 其他错误									    *
*  返回值类型:DWORD														*
*  创建日期:2013-10-15													*
*  创建人:陈可明														*
*  修改历史:无															*
*************************************************************************/
DWORD AgilentOSA::CloseDevice()
{
	DWORD dwErrorCode = SUCCESS;

	try
	{
		//退出连接状态
		dwErrorCode = m_Commun.CloseDevice();
		if (SUCCESS != dwErrorCode) 
		{
	    	throw ERROR_OSA|dwErrorCode;
		}
	}
	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = ERROR_OSA|UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

/************************************************************************
*  函数名称:ResetDevice													*
*  功能: 复位设备,适用：                                                *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  输入: 无																*
*  输出：无                                                             *
*  返回值:																*
*             0: 函数执行成功。											*
*			  0xXXXXXXXX: 其他错误									    *
*  返回值类型:DWORD														*
*  创建日期:2013-10-15													*
*  创建人:陈可明														*
*  修改历史:无															*
*************************************************************************/

DWORD AgilentOSA::ResetDevice()
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	ZeroMemory(szCmdString, TXLENS * sizeof(CHAR));

	try
	{
		//复位OSA
		sprintf(szCmdString,"*RST\r\n");
		dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
		if (SUCCESS != dwErrorCode) 
		{
	    	throw ERROR_OSA|dwErrorCode;
		}
		Sleep(2000);
        CompleteRequest();
	}
	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return ERROR_OSA|UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

/************************************************************************
*  函数名称:SetOSALocalCtrl												*
*  功能: 设置OSA设备为控制状态,适用：                                   *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  输入: 无																*
*  输出：无                                                             *
*  返回值:																*
*             0: 函数执行成功。											*
*			  0xXXXXXXXX: 其他错误									    *
*  返回值类型:DWORD														*
*  创建日期:2013-10-15													*
*  创建人:陈可明														*
*  修改历史:无															*
*************************************************************************/

DWORD AgilentOSA::SetOSALocalCtrl()
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	ZeroMemory(szCmdString, TXLENS * sizeof(CHAR));

	try
	{
		//设置LOCAL状态
		sprintf(szCmdString,"GTL\r\n");
		dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
		if (SUCCESS != dwErrorCode) 
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

	}
	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return ERROR_OSA|UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

/************************************************************************
*  函数名称:SetRBW												        *
*  功能: 设置OSA设备为控制状态,适用：                                   *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  输入: dblRBW	设置RBW目标值											*
*  输出：无                                                             *
*  返回值:																*
*             0: 函数执行成功。											*
*			  0xXXXXXXXX: 其他错误									    *
*  返回值类型:DWORD														*
*  创建日期:2013-10-15													*
*  创建人:陈可明														*
*  修改历史:无															*
*************************************************************************/
DWORD AgilentOSA::SetRBW(double dblRBW)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	ZeroMemory(szCmdString, TXLENS * sizeof(CHAR));

	try
	{
		//设置RBW值
		sprintf(szCmdString,"SENS:BWID %.2f NM\r\n", dblRBW);
		dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
		if (SUCCESS != dwErrorCode) 
		{
	    	throw ERROR_OSA|dwErrorCode;
		}
        CompleteRequest();
	}
	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return ERROR_OSA|UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

/************************************************************************
*  函数名称:GetRBW												        *
*  功能: 读取OSA RBW当前设置值,适用：                                   *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  输入: 无							                                 	*
*  输出：*dblRBW	读取RBW目标值,单位：nm                              *
*  返回值:																*
*             0: 函数执行成功。											*
*			  0xXXXXXXXX: 其他错误									    *
*  返回值类型:DWORD														*
*  创建日期:2013-10-15													*
*  创建人:陈可明														*
*  修改历史:无															*
*************************************************************************/
DWORD AgilentOSA::GetRBW(double *pdblRBW)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	CHAR szDataStream[RXMINLENS];
	ZeroMemory(szCmdString, TXLENS * sizeof(CHAR));
	ZeroMemory(szDataStream,RXMINLENS * sizeof(CHAR));

	try
	{
		//读取RBW值
		sprintf(szCmdString,"SENS:BWID?\r\n");
		dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
		if (SUCCESS != dwErrorCode) 
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

		dwErrorCode = m_Commun.ReadDevice(szDataStream, RXMINLENS);
		if (SUCCESS != dwErrorCode) 
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

		*pdblRBW = atof(szDataStream) * pow(10,9);//nm

	}
	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return ERROR_OSA|UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

/************************************************************************
*  函数名称:InitAmpTest												    *
*  功能: 读取OSA RBW当前设置值,适用：                                   *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  输入: dblStartWL：起始波长，                                         *
		 dblStopWL：终止波长，	                                        *
		 dblRBW：扫描分辨率，                                           *
		 单位：nm                                                       *
*  输出：无                                                             *
*  返回值:																*
*             0: 函数执行成功。											*
*			  0xXXXXXXXX: 其他错误									    *
*  返回值类型:DWORD														*
*  创建日期:2013-10-15													*
*  创建人:陈可明														*
*  修改历史:无															*
*************************************************************************/
DWORD AgilentOSA::InitAmpTest(double dblStartWL,double dblStopWL,double dblRBW)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	CHAR szDataStream[RXMINLENS];
	ZeroMemory(szCmdString, TXLENS * sizeof(char));
	ZeroMemory(szDataStream, RXMINLENS * sizeof(char));
	int   nIndex;

	try
	{
		//清除驱动状态
		dwErrorCode = m_Commun.ClearDevice();
		if(SUCCESS != dwErrorCode)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}
	
		//OSA初始状态
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,"INST:NSEL?\r\n");		
		dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

		dwErrorCode = m_Commun.ReadDevice(szDataStream, RXMINLENS);
		if(SUCCESS != dwErrorCode)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

		nIndex = atoi(szDataStream);
		
		if (!m_bNFLib)
		{
			//The value is 5 means it work in Amplifier mode
			if (nIndex != 5)
			{
				//复位OSA
				ZeroMemory(szCmdString,TXLENS);
				sprintf(szCmdString,"*RST\r\n");
				dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
				if(SUCCESS != dwErrorCode)
				{
					throw ERROR_OSA|dwErrorCode;
				}
				Sleep(2000);
				dwErrorCode = CompleteRequest();
				//初始到Amp ISS模式
				ZeroMemory(szCmdString,TXLENS);
				sprintf(szCmdString,"INST:SEL 'Amp_ISS_Test'\r\n");
				dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
				if(SUCCESS != dwErrorCode)
				{
					throw ERROR_OSA|dwErrorCode;
				}
				Sleep(10000);
				//等待状态
				dwErrorCode = CompleteRequest();
				if(SUCCESS != dwErrorCode)
				{
					throw ERROR_OSA|dwErrorCode;
				}
			}
			
			//设置起始波长
			ZeroMemory(szCmdString,TXLENS);
			sprintf(szCmdString, "SENS:START %.2f NM\r\n", dblStartWL);
			dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode;
			}
			
			//设置终止波长
			ZeroMemory(szCmdString,TXLENS);
			sprintf(szCmdString, "SENS:STOP %.2f NM\r\n", dblStopWL);
			dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode;
			}
			
			//设置RBW值
			ZeroMemory(szCmdString,TXLENS);
			sprintf(szCmdString, "SENS:BWID %.2f NM\r\n", dblRBW);
			dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode;
			}
		}
		else
		{
			m_stScanSetting.m_dblAmpOffset = AMP_SIGNAL_OFFSET;
			m_stScanSetting.m_dblStartWL = OSA_SCAN_MIN_WAVE;
			m_stScanSetting.m_dblStopWL = OSA_SCAN_MAX_WAVE;
			m_stScanSetting.m_dblRBW = SCAN_BW_SEN_B;
			m_stScanSetting.m_bInterpolationMode = AUTO_MODE;
			m_stScanSetting.m_dblInterpolationVal = MANUAL_OFFSET;
			m_stScanSetting.m_bIncludeShotNosie = INCLUDE_SHOT_NOISE;
			m_stScanSetting.m_bExcludeSourceASE = EXCLUDE_SRC_ASE_POWER;
			m_stScanSetting.m_bNFCalculationRBW = RBW_CALC_MODE;
			
			//The value is 0 means it work in Normal mode
			if (nIndex != 0)
			{
				dwErrorCode = ResetDevice();
				if(SUCCESS != dwErrorCode)
				{
					throw dwErrorCode;
				}
			}
			m_stScanSetting.m_dblStartWL = dblStartWL; 
			m_stScanSetting.m_dblStopWL = dblStopWL; 
			m_stScanSetting.m_dblRBW = dblRBW;

			dwErrorCode = InitSingleSweep(dblStartWL, dblStopWL, dblRBW, SWEEPPOINT);
			if(SUCCESS != dwErrorCode)
			{
				throw dwErrorCode;
			}
		}
		
		//等待状态
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA|dwErrorCode;
		}
	}
	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return ERROR_OSA|UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

/************************************************************************
*  函数名称:CompleteRequest												*
*  功能: 查询OSA运行状态,适用：                                         *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  输入: 无                                                             *
*  输出：无                                                             *
*  返回值: 无															*
*  返回值:																*
*             0: 函数执行成功。											*
*			  0xXXXXXXXX: 其他错误									    *
*  返回值类型:DWORD														*
*  创建日期:2013-10-15													*
*  创建人:陈可明														*
*  修改历史:无															*
*************************************************************************/
DWORD AgilentOSA::CompleteRequest()
{
	CHAR szCmdString[TXLENS];
	CHAR szDataStream[RXMINLENS];
	long lIndex = 0;

	ZeroMemory(szCmdString, TXLENS * sizeof(CHAR));
	ZeroMemory(szDataStream, RXMINLENS * sizeof(CHAR));
	
	do
	{
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,"*OPC?\r\n");
		m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
		Sleep(50);
		ZeroMemory(szDataStream,RXMINLENS);
		m_Commun.ReadDevice(szDataStream, RXMINLENS);

		//如果5分钟后，操作还未完成，返回超时错误
		if (lIndex > 1500000)
		{
			return ERROR_RUN_OVERTIME;
		}

		lIndex++;

	} while(!strchr(szDataStream, '1'));//状态为1时，退出查询

	return SUCCESS;
}

/************************************************************************
*  函数名称:MeasureSource												*
*  功能: 放大模式下进行扫源,适用：                                      *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  输入: 无                                                             *
*  输出：无                                                             *
*  返回值:																*
*             0: 函数执行成功。											*
*			  0xXXXXXXXX: 其他错误									    *
*  返回值类型:DWORD														*
*  创建日期:2013-10-15													*
*  创建人:陈可明														*
*  修改历史:无															*
*************************************************************************/
DWORD AgilentOSA::MeasureSource()
{
	DWORD  dwErrorCode = SUCCESS;
	double* pdblSingleScan = NULL;
	double pdblWL[SWEEPPOINT];
    CHAR szCmdString[TXLENS];

	try
	{	
		if (!m_bNFLib)
		{
			//EDFA模式 扫源
			ZeroMemory(szCmdString,TXLENS);
            sprintf(szCmdString,"INIT:IMM:SEQ 1\r\n");
			dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode; 
			}
		}
		else
		{
			dwErrorCode = InitSingleSweep(m_stScanSetting.m_dblStartWL, 
										m_stScanSetting.m_dblStopWL, 
										m_stScanSetting.m_dblRBW, SWEEPPOINT);
			if(SUCCESS != dwErrorCode)
			{
				throw dwErrorCode;
			}

			pdblSingleScan = (double*)VirtualAlloc(NULL, sizeof(double) * SWEEPPOINT, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
			ZeroMemory(&m_pdblScanData[SRC_SCAN], SWEEPPOINT*sizeof(double));
			ZeroMemory(pdblWL, SWEEPPOINT*sizeof(double));
			
			dwErrorCode = RunSweep(pdblWL, pdblSingleScan, 'A');
			if(SUCCESS != dwErrorCode)
			{
				VirtualFree(pdblSingleScan, 0, MEM_RELEASE);
				throw dwErrorCode;	
			}
			
			for(int i = 0; i < SWEEPPOINT; i ++)
			{
				m_pdblScanData[SRC_SCAN][i] += pdblSingleScan[i];
			}

			VirtualFree(pdblSingleScan, 0, MEM_RELEASE);
			WORD	wChCount = 0;
			m_stEDFAResult.m_dblSumSrcSigPwr = GetSrcChPower(   m_stScanSetting.m_dblStartWL, 
																m_stScanSetting.m_dblStopWL, 
																m_stScanSetting.m_dblSrcOffset, 
																SWEEPPOINT, 
																m_pdblScanData[SRC_SCAN], 
																m_stEDFAResult.m_pdblChWL, 
																m_stEDFAResult.m_pdblSrcPwr, 
																&wChCount   );
		}
		
		
		//等待状态
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA|dwErrorCode;
		}	
	}

	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return ERROR_OSA|UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

/************************************************************************
*  函数名称:MeasureAmplifier										    *
*  功能: 放大模式下进行放大,适用：                                      *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  输入: bScanSrcOnly  扫描状态                                         *
*  输出：无                                                             *
*  返回值:																*
*             0: 函数执行成功。											*
*			  0xXXXXXXXX: 其他错误									    *
*  返回值类型:DWORD														*
*  创建日期:2013-10-15													*
*  创建人:陈可明														*
*  修改历史:无															*
*************************************************************************/
DWORD AgilentOSA::MeasureAmplifier(BOOL bScanSrcOnly /* = FALSE */)
{
	DWORD  dwErrorCode = SUCCESS;
	double pdblWL[SWEEPPOINT];
	double* pdblSingleScan = NULL;
	CHAR szCmdString[TXLENS];
	
	try
	{
		if(!bScanSrcOnly)
		{
			if (!m_bNFLib)
			{
				//EDFA模式 放大
				ZeroMemory(szCmdString,TXLENS);
				sprintf(szCmdString,"INIT:IMM:SEQ 2\r\n");
				dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
				if(SUCCESS != dwErrorCode)
				{
	    			throw ERROR_OSA|dwErrorCode; 
				}
			}
			else
			{
				dwErrorCode = InitSingleSweep(m_stScanSetting.m_dblStartWL, 
										m_stScanSetting.m_dblStopWL, 
										m_stScanSetting.m_dblRBW, SWEEPPOINT);
				if(SUCCESS != dwErrorCode)
				{
					throw dwErrorCode;
				}

				pdblSingleScan = (double*)VirtualAlloc(NULL, sizeof(double) * SWEEPPOINT, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
				ZeroMemory(&m_pdblScanData[AMP_SCAN], SWEEPPOINT*sizeof(double));
				ZeroMemory(pdblWL, SWEEPPOINT*sizeof(double));
				
				dwErrorCode = RunSweep(pdblWL, pdblSingleScan, 'B');
				if(SUCCESS != dwErrorCode)
				{
					VirtualFree(pdblSingleScan, 0, MEM_RELEASE);
					throw dwErrorCode;	
				}
				
				for(int i = 0; i < SWEEPPOINT; i ++)
				{
					m_pdblScanData[AMP_SCAN][i] += pdblSingleScan[i];
				}

				VirtualFree(pdblSingleScan, 0, MEM_RELEASE);

				if (!GetNormalModeEDFAResult(m_stScanSetting, &m_stEDFAResult,m_pdblScanData[SRC_SCAN], m_pdblScanData[AMP_SCAN], SWEEPPOINT))
				{
					throw ERROR_SWEEP_DATA;
				}
			}
			
		}
		
		//等待状态
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA|dwErrorCode;
		}		
	}
	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return ERROR_OSA|UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

/************************************************************************
*  函数名称:GetChannelCount										        *
*  功能:读取数据源信号通道,适用：                                       *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  输入: 无                                                             *
*  输出：*pdwChannelCount  信号通道                                     *
*  返回值:																*
*             0: 函数执行成功。											*
*			  0xXXXXXXXX: 其他错误									    *
*  返回值类型:DWORD														*
*  创建日期:2013-10-15													*
*  创建人:陈可明														*
*  修改历史:无															*
*************************************************************************/
DWORD AgilentOSA::GetChannelCount(DWORD* pdwChannelCount)
{
	DWORD	dwErrorCode = SUCCESS;
	TCHAR	tszDataStream[RXMINLENS];
	LPSTR	pszToken = ",", pszNewData = NULL;
	
	try
	{
		if (!m_bNFLib)
		{
			//读取测试信号通道数
			ZeroMemory(tszDataStream, RXMINLENS);
			sprintf(tszDataStream,"CALC:DATA:NCH?\r\n");
			dwErrorCode = m_Commun.WriteDevice(tszDataStream,strlen(tszDataStream));
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode; 
			}
			ZeroMemory(tszDataStream, RXMINLENS);
			dwErrorCode = m_Commun.ReadDevice(tszDataStream, RXMINLENS);
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode; 
			}
			
			pszNewData	= strtok(tszDataStream, pszToken);
			*pdwChannelCount	= atoi(pszNewData);
			
			//等待状态
			dwErrorCode = CompleteRequest();
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode;
			}
		}
		else
		{
			*pdwChannelCount	= m_stEDFAResult.m_wChCount;
		}
	}

	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return ERROR_OSA|UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}


/************************************************************************
*  函数名称:GetChannelWaveLens										    *
*  功能:读取数据源信号通道波长,适用：                                   *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  输入: 无                                                             *
*  输出：                                                               *
		*pdblWL 通道波长                                                *
		*pdwChannelCount  信号通道                                      * 
*  返回值:																*
*             0: 函数执行成功。											*
*			  0xXXXXXXXX: 其他错误									    *
*  返回值类型:DWORD														*
*  创建日期:2013-10-15													*
*  创建人:陈可明														*
*  修改历史:无															*
*************************************************************************/

DWORD AgilentOSA::GetChannelWaveLens(double* pdblWL, DWORD* pdwChannelCount)
{
	DWORD	dwErrorCode = SUCCESS;
	TCHAR	tszDataStream[RXMINLENS];
	LPSTR	pszToken = ",", pszNewData = NULL;
	WORD	wIndex;
	TCHAR	tszData[RXMINLENS];
	ZeroMemory(tszDataStream, RXMINLENS * sizeof(CHAR));

	try
	{
		if (!m_bNFLib)
		{
			//设置数据 ASCII
			ZeroMemory(tszDataStream, RXMINLENS);
			sprintf(tszDataStream,"FORM:DATA ASC\r\n");
			dwErrorCode = m_Commun.WriteDevice(tszDataStream,strlen(tszDataStream));
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode; 
			}
			
			//等待状态
			dwErrorCode = CompleteRequest();
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode;
			}		

			//读取首个通道
			ZeroMemory(tszDataStream, RXMINLENS);
			sprintf(tszDataStream,"CALC:DATA:CWAV?\r\n");
			dwErrorCode = m_Commun.WriteDevice(tszDataStream,strlen(tszDataStream));
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode; 
			}
			ZeroMemory(tszDataStream, RXMINLENS);
			dwErrorCode = m_Commun.ReadDevice(tszDataStream, RXMINLENS);
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode; 
			}
			
			//等待状态
			dwErrorCode = CompleteRequest();
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode;
			}		

			//从OSA获得信号通道数
			dwErrorCode = GetChannelCount(pdwChannelCount);
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode;
			}
			
			pszNewData		= strtok(tszDataStream, pszToken);
			pdblWL[0]		= atof(pszNewData);
			pdblWL[0]		= pdblWL[0] * pow(10, 9);
			
			for(wIndex = 1; wIndex < *pdwChannelCount; wIndex ++)
			{
				pszNewData				= strtok(NULL, pszToken);
				ZeroMemory(tszData, RXMINLENS*sizeof(TCHAR));
				pdblWL[wIndex]		= atof(strncat(tszData, pszNewData, 16));
				pdblWL[wIndex]		= pdblWL[wIndex] * pow(10, 9);
			}
		}
		else
		{
			//Caution: All the get channel command must be after the get data command
			//Get the data channel count from the OSA
			dwErrorCode = GetChannelCount(pdwChannelCount);
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode;
			}

			for(wIndex = 0; wIndex < *pdwChannelCount; wIndex ++)
			{
				pdblWL[wIndex]	= m_stEDFAResult.m_pdblChWL[wIndex];
			}
		}
	}

	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return ERROR_OSA|UNEXPECT_OCCUR;
	}

	return dwErrorCode;	
}

/************************************************************************
*  函数名称:GetChannelNF										        *
*  功能:读取数据源信号通道噪声(NF),适用：                               *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  输入: 无                                                             *
*  输出：                                                               *
		*pdblNF 噪声NF                                                  *
		*pdwChannelCount  信号通道                                      * 
*  返回值:																*
*             0: 函数执行成功。											*
*			  0xXXXXXXXX: 其他错误									    *
*  返回值类型:DWORD														*
*  创建日期:2013-10-15													*
*  创建人:陈可明														*
*  修改历史:无															*
*************************************************************************/

DWORD AgilentOSA::GetChannelNF(double* pdblNF,DWORD* pdwChannelCount)
{
	DWORD	dwErrorCode = SUCCESS;
	TCHAR	tszDataStream[RXMINLENS];
	LPSTR	pszToken = ",", pszNewData = NULL;
	WORD	wIndex;
	TCHAR	tszData[RXMINLENS];

	try
	{
		if (!m_bNFLib)
		{
			//设置数据 ASCII
			ZeroMemory(tszDataStream, RXMINLENS);
			sprintf(tszDataStream,"FORM:DATA ASC\r\n");
			dwErrorCode = m_Commun.WriteDevice(tszDataStream,strlen(tszDataStream));
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode; 
			}
			
				//等待状态
			dwErrorCode = CompleteRequest();
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode;
			}
			
			//读取首个通道
			ZeroMemory(tszDataStream, RXMINLENS);
			sprintf(tszDataStream,"CALC:DATA:CNF?\r\n");
			dwErrorCode = m_Commun.WriteDevice(tszDataStream,strlen(tszDataStream));
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode; 
			}
			ZeroMemory(tszDataStream, RXMINLENS);
			dwErrorCode = m_Commun.ReadDevice(tszDataStream, RXMINLENS);
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode; 
			}
			
			//等待状态
			dwErrorCode = CompleteRequest();
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode;
			}
			
			//从OSA获得信号通道数
			dwErrorCode = GetChannelCount(pdwChannelCount);
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode;
			}
			
			pszNewData		= strtok(tszDataStream, pszToken);
			pdblNF[0]		= atof(pszNewData);
			
			for(wIndex = 1; wIndex < *pdwChannelCount; wIndex ++)
			{
				pszNewData				= strtok(NULL, pszToken);
				ZeroMemory(tszData, 1024*sizeof(TCHAR));
				pdblNF[wIndex]		= atof(strncat(tszData, pszNewData, 16));
			}
		}
		else
		{
			//Caution: All the get channel command must be after the get data command
			//Get the data channel count from the OSA
			dwErrorCode = GetChannelCount(pdwChannelCount);
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode;
			}
			
			for(wIndex = 0; wIndex < *pdwChannelCount; wIndex ++)
			{
				pdblNF[wIndex]	= m_stEDFAResult.m_pdblChNF[wIndex];
			}
		}
	}
	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return ERROR_OSA|UNEXPECT_OCCUR;
	}

	return dwErrorCode;	
}

/************************************************************************
*  函数名称:GetChannelGain										        *
*  功能:读取数据源信号通道增益,适用：                                   *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  输入: 无                                                             *
*  输出：                                                               *
		*pdblGain 通道增益                                              *
		*pdwChannelCount  信号通道                                      * 
*  返回值:																*
*             0: 函数执行成功。											*
*			  0xXXXXXXXX: 其他错误									    *
*  返回值类型:DWORD														*
*  创建日期:2013-10-15													*
*  创建人:陈可明														*
*  修改历史:无															*
*************************************************************************/

DWORD AgilentOSA::GetChannelGain(double* pdblGain,DWORD* pdwChannelCount)
{
	DWORD	dwErrorCode = SUCCESS;
	TCHAR	tszDataStream[RXMINLENS];
	LPSTR	pszToken = ",", pszNewData = NULL;
	WORD	wIndex;
	TCHAR	tszData[RXMINLENS];

	try
	{
		if (!m_bNFLib)
		{
			//读取首个通道
			ZeroMemory(tszDataStream, RXMINLENS);
			sprintf(tszDataStream,"CALC:DATA:CGA?\r\n");
			dwErrorCode = m_Commun.WriteDevice(tszDataStream,strlen(tszDataStream));
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode; 
			}
			
            ZeroMemory(tszDataStream, RXMINLENS);
			dwErrorCode = m_Commun.ReadDevice(tszDataStream, RXMINLENS);
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode; 
			}
			
			//等待状态
			dwErrorCode = CompleteRequest();
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode;
			}
			
			//从OSA获得信号通道数
			dwErrorCode = GetChannelCount(pdwChannelCount);
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode;
			}
			
			pszNewData		= strtok(tszDataStream, pszToken);
			pdblGain[0]		= atof(pszNewData);
			for(wIndex = 1; wIndex < *pdwChannelCount; wIndex ++)
			{
				//获得OSA Gain
				pszNewData				= strtok(NULL, pszToken);
				ZeroMemory(tszData, RXMINLENS * sizeof(TCHAR));
				pdblGain[wIndex]		= atof(strncat(tszData, pszNewData, 16));
			}
		}
		else
		{
			//Caution: All the get channel command must be after the get data command
			//从OSA获得信号通道数
			dwErrorCode = GetChannelCount(pdwChannelCount);
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode;
			}
			for(wIndex = 0; wIndex < *pdwChannelCount; wIndex ++)
			{
				//Get source power from the OSA
				pdblGain[wIndex] = m_stEDFAResult.m_pdblChGain[wIndex];
			}
		}
		
	}

	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return ERROR_OSA|UNEXPECT_OCCUR;
	}

	return dwErrorCode;	
}

/************************************************************************
*  函数名称:GetChannelSourcePower									    *
*  功能:读取数据源信号通道功率,适用：                                   *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  输入: 无                                                             *
*  输出：                                                               *
		*pdblSourcePow 源功率                                           *
		*pdwChannelCount  信号通道                                      * 
*  返回值:																*
*             0: 函数执行成功。											*
*			  0xXXXXXXXX: 其他错误									    *
*  返回值类型:DWORD														*
*  创建日期:2013-10-15													*
*  创建人:陈可明														*
*  修改历史:无															*
*************************************************************************/
DWORD AgilentOSA::GetChannelSourcePower(double* pdblSourcePow, DWORD* pdwChannelCount)
{
	DWORD	dwErrorCode = SUCCESS;
	TCHAR	tszDataStream[RXMINLENS];
	TCHAR	tszData[RXMINLENS];
	LPSTR	pszToken = ",", pszNewData = NULL;
	WORD	wIndex;

	try
	{	
		if (!m_bNFLib)
		{
			//设置数据 ASCII
			ZeroMemory(tszDataStream, RXMINLENS);
			sprintf(tszDataStream,"FORM:DATA ASC\r\n");
			dwErrorCode = m_Commun.WriteDevice(tszDataStream,strlen(tszDataStream));
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode; 
			}
			
			//等待状态
			dwErrorCode = CompleteRequest();
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode;
			}
			
			//读取首个通道
			ZeroMemory(tszDataStream, RXMINLENS);
			sprintf(tszDataStream,"CALC:DATA:CPOW?");
			dwErrorCode = m_Commun.WriteDevice(tszDataStream,strlen(tszDataStream));
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode; 
			}

			ZeroMemory(tszDataStream, RXMINLENS);
			dwErrorCode = m_Commun.ReadDevice(tszDataStream, RXMINLENS);
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode; 
			}

				//等待状态
			dwErrorCode = CompleteRequest();
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode;
			}
			
			//从OSA获得信号通道数
			dwErrorCode = GetChannelCount(pdwChannelCount);
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode;
			}
			
			pszNewData			    = strtok(tszDataStream, pszToken);
			pdblSourcePow[0]		= atof(pszNewData);
			
			for(wIndex = 1; wIndex < *pdwChannelCount; wIndex ++)
			{
				pszNewData			    = strtok(NULL, pszToken);	
				ZeroMemory(tszData,     1024 * sizeof(TCHAR));
				pdblSourcePow[wIndex]	= atof(strncat(tszData, pszNewData, 16));
			}
		}
		else
		{
			//Caution: All the get channel command must be after the get data command
			//Get the data channel count from the OSA
			dwErrorCode = GetChannelCount(pdwChannelCount);
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode;
			}

			for(wIndex = 0; wIndex < *pdwChannelCount; wIndex ++)
			{
				pdblSourcePow[wIndex] = m_stEDFAResult.m_pdblSrcPwr[wIndex];
			}
		}
	}

	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return ERROR_OSA|UNEXPECT_OCCUR;
	}

	return dwErrorCode;	
}

/************************************************************************
*  函数名称:SetAmpOffset									            *
*  功能:设置源、输出OFFSET,适用：                                       *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  输入：                                                               *
		pdblSourcePow 源OFFSET                                          *
		dblAmpOffsett  输出OFFSET                                       * 
*  输出：                                                               *
		无                                                              *
*  返回值:																*
*             0: 函数执行成功。											*
*			  0xXXXXXXXX: 其他错误									    *
*  返回值类型:DWORD														*
*  创建日期:2013-10-15													*
*  创建人:陈可明														*
*  修改历史:无															*
*************************************************************************/

DWORD AgilentOSA::SetAmpOffset(double dblSourceOffset, double dblAmpOffsett)
{
	CHAR  szCmdString[1024];
	DWORD  dwErrorCode = SUCCESS;

	try
	{
		if (!m_bNFLib)
		{
			//设置源OFFSET
			ZeroMemory(szCmdString, 1024);
			sprintf(szCmdString, "CALC:OFFS:SOUR%7.2f\r\n", dblSourceOffset);
			
			dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode; 
			}
			
			//设置输出OFFSET
			ZeroMemory(szCmdString, 1024);
			sprintf(szCmdString, "CALC:OFFS:AMPL%7.2f\r\n", dblAmpOffsett);
			
			dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode; 
			}
		}
		else
		{
			//Set the source signal offset
			m_stScanSetting.m_dblSrcOffset = dblSourceOffset;
			m_stScanSetting.m_dblAmpOffset = dblAmpOffsett;
		}
	}
	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return ERROR_OSA|UNEXPECT_OCCUR;
	}

	return dwErrorCode;	
}

/************************************************************************
*  函数名称:SetAmpOffset									            *
*  功能:读取源、输出OFFSET,适用：                                       *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  输入：                                                               *
		无                                                              *
*  输出：                                                               *
		dblSourceOffset 源OFFSET                                        *
		dblAmpOffset  输出OFFSET                                        * 
*  返回值:																*
*             0: 函数执行成功。											*
*			  0xXXXXXXXX: 其他错误									    *
*  返回值类型:DWORD														*
*  创建日期:2013-10-15													*
*  创建人:陈可明														*
*  修改历史:无															*
*************************************************************************/
DWORD AgilentOSA::GetAmpOffset(double &dblSourceOffset, double &dblAmpOffset)
{
	DWORD	dwErrorCode = SUCCESS;
	TCHAR	tszDataStream[RXMINLENS];
	LPSTR	pszToken = " ,\t\n", pszNewData = NULL;
	double  dblOffset;

	try
	{
		if (!m_bNFLib)
		{
			//读取源OFFSET
			ZeroMemory(tszDataStream, RXMINLENS * sizeof(TCHAR));
			sprintf(tszDataStream,"CALC:OFFS:SOUR?\r\n");
			dwErrorCode = m_Commun.WriteDevice(tszDataStream,strlen(tszDataStream));
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode; 
			}
			ZeroMemory(tszDataStream, RXMINLENS * sizeof(TCHAR));
			dwErrorCode = m_Commun.ReadDevice(tszDataStream, 32);
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode; 
			}
			
			//等待状态
			dwErrorCode = CompleteRequest();
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode;
			}
			
			dblSourceOffset = atof(tszDataStream);
			dblSourceOffset = dblSourceOffset;
			
			//读取输出OFFSET
			ZeroMemory(tszDataStream, RXMINLENS * sizeof(TCHAR));
			sprintf(tszDataStream,"CALC:OFFS:AMPL?\r\n");
			dwErrorCode = m_Commun.WriteDevice(tszDataStream,strlen(tszDataStream));
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode; 
			}
            ZeroMemory(tszDataStream, RXMINLENS * sizeof(TCHAR));
			dwErrorCode = m_Commun.ReadDevice(tszDataStream, 32);
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode; 
			}
			
			//等待状态
			dwErrorCode = CompleteRequest();
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode;
			}
			
			dblOffset = atof(tszDataStream);
			dblAmpOffset = dblOffset;

		}
		else
		{
			dblSourceOffset = m_stScanSetting.m_dblSrcOffset;
			dblAmpOffset = m_stScanSetting.m_dblAmpOffset;
		}
		
	}
	
	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return ERROR_OSA|UNEXPECT_OCCUR;
	}

	return dwErrorCode;	
}

/************************************************************************
*  函数名称:GetEDFAChResult									            *
*  功能:EDFA模式下，读取扫描数据,适用：                                 *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  输入：                                                               *
		无                                                              *
*  输出：                                                               *
		pwChCount        信号通道数                                     *
		pdblChWL         信号通道波长                                   * 
		pdblSrcpwr       信号通道源功率                                 *
		pdblChGain       信号通道增益                                   * 
		pdblChNF         信号通道噪声                                   *
		pdblChAse        信号通道ASE                                    * 
		pdblGainFlatness 信号平坦度                                     *
		pdblMaxNF        信号最大噪声                                   * 
		pdblMaxGain      信号最大增益                                   *
		pdblMinGain      信号最小增益                                   * 
*  返回值:																*
*             0: 函数执行成功。											*
*			  0xXXXXXXXX: 其他错误									    *
*  返回值类型:DWORD														*
*  创建日期:2013-10-15													*
*  创建人:陈可明														*
*  修改历史:无															*
*************************************************************************/

DWORD AgilentOSA::GetEDFAChResult(DWORD *pwChCount, double *pdblChWL, double *pdblSrcpwr, double *pdblChGain, double *pdblChNF, double *pdblChAse, double *pdblGainFlatness, double *pdblMaxNF, double* pdblMaxGain, double* pdblMinGain)
{
	double	dblMaxNF = -100;		
	double dblMaxGain = -100;
	double dblMinGain = 100;
	WORD   i;
	DWORD dwErrorCode = SUCCESS;

	//读取信号通道增益
	dwErrorCode = GetChannelGain(pdblChGain, pwChCount);
	if(SUCCESS != dwErrorCode)
	{
		return dwErrorCode;
	}

	//读取信号通道噪声
	dwErrorCode = GetChannelNF(pdblChNF, pwChCount);
	if(SUCCESS != dwErrorCode)
	{
		return dwErrorCode;
	}
	
	//读取信号通道源功率
	dwErrorCode = GetChannelSourcePower(pdblSrcpwr, pwChCount);
	if(SUCCESS != dwErrorCode)
	{
		return dwErrorCode;
	}
	
	//读取信号通道波长
	dwErrorCode = GetChannelWaveLens(pdblChWL, pwChCount);
	if(SUCCESS != dwErrorCode)
	{
		return dwErrorCode;
	}

	//计算最大、最小增益
	for(i = 0; i < *pwChCount; i++)
	{
		if(pdblChGain[i] > dblMaxGain)
		{
			dblMaxGain = pdblChGain[i];
		}
		if(pdblChGain[i] < dblMinGain)
		{
			dblMinGain = pdblChGain[i];
		}
	}
	
	*pdblMaxGain = dblMaxGain;
	*pdblMinGain = dblMinGain;
	
	//计算平坦度
	*pdblGainFlatness = dblMaxGain-dblMinGain;

	//计算最大噪声
	for(i = 0; i < *pwChCount; i++)
	{
		if(pdblChNF[i] > dblMaxNF)
		{
			dblMaxNF = pdblChNF[i];
		}
	}

	*pdblMaxNF	 = dblMaxNF;

	return dwErrorCode;
}
/************************************************************************
*  函数名称:GetEDFAResult									            *
*  功能:读取源、输出功率、增益,适用：                                   *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  输入：                                                               *
		无                                                              *
*  输出：                                                               *
		pdblSumSrcSigPwr 源功率                                         *
		pdblSumAmpSigPwr  输出功率                                      * 
		pdblSunGain 增益                                                *
*  返回值:																*
*             0: 函数执行成功。											*
*			  0xXXXXXXXX: 其他错误									    *
*  返回值类型:DWORD														*
*  创建日期:2013-10-15													*
*  创建人:陈可明														*
*  修改历史:无															*
*************************************************************************/
DWORD AgilentOSA::GetEDFAResult(double *pdblSumSrcSigPwr, double *pdblSumAmpSigPwr, double *pdblSunGain)
{
	BOOL	dwErrorCode = SUCCESS;
	TCHAR	tszDataStream[RXMINLENS];
	TCHAR	tszData[RXMINLENS];
	LPSTR	pszToken = " ,\t\n", pszNewData = NULL;
	double  dblSrcPwr;

	try
	{
		if (!m_bNFLib)
		{
			//发送读取源、输出命令
			ZeroMemory(tszDataStream, RXMINLENS * sizeof(TCHAR));
			sprintf(tszDataStream,"CALC:DATA:CST?\r\n");
			dwErrorCode = m_Commun.WriteDevice(tszDataStream,strlen(tszDataStream));
			if(dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode;
			}
			
			//读取数据
			ZeroMemory(tszDataStream, RXMINLENS * sizeof(TCHAR));
			dwErrorCode = m_Commun.ReadDevice(tszDataStream, RXMINLENS);
			if(dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode;
			}
			
			//等待状态
			dwErrorCode = CompleteRequest();
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode;
			}	
			
			//源功率
			pszNewData = strtok(tszDataStream, pszToken);
			pszNewData = strtok(NULL, pszToken);
			dblSrcPwr = atof(pszNewData);
			*pdblSumSrcSigPwr = dblSrcPwr;
			
			//输出功率
			pszNewData = strtok(NULL, pszToken);
			pszNewData = strtok(NULL, pszToken);  
			ZeroMemory(tszData, RXMINLENS * sizeof(TCHAR));
			*pdblSumAmpSigPwr = atof(strncat(tszData, pszNewData, sizeof(WORD) * 8));
			
			//计算增益
			*pdblSunGain   = *pdblSumAmpSigPwr - *pdblSumSrcSigPwr;
		}
		else
		{
			*pdblSumSrcSigPwr = m_stEDFAResult.m_dblSumSrcSigPwr;

			*pdblSumAmpSigPwr = m_stEDFAResult.m_dblSumAmpSigPwr;
			
			//Calculate Gain of Sum
			*pdblSunGain   = *pdblSumAmpSigPwr - *pdblSumSrcSigPwr;
		}
		
	}
	
	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return ERROR_OSA|UNEXPECT_OCCUR;
	}

	return dwErrorCode;	
}

/************************************************************************
*  函数名称:InitSingleSweep									            *
*  功能:初始化扫描起始波长、终止波长,RBW，扫描点数,适用：               *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  输入：                                                               *
		dblStartWL    起始波长                                          *
		dblStopWL     终止波长                                          * 
		dblRBW        扫描分辨率                                        *
		dwSweepPoint  扫描点数                                          *
*  输入：                                                               *
		无                                                              *
*  返回值:																*
*             0: 函数执行成功。											*
*			  0xXXXXXXXX: 其他错误									    *
*  返回值类型:DWORD														*
*  创建日期:2013-10-15													*
*  创建人:陈可明														*
*  修改历史:无															*
*************************************************************************/
DWORD AgilentOSA::InitSingleSweep(double dblStartWL, double dblStopWL, double dblRBW, DWORD dwSweepPoint)
{
	CHAR  szCmdString[TXLENS];
	DWORD  dwErrorCode = SUCCESS;

	try
	{
		//初始起始波长
		ZeroMemory(szCmdString, TXLENS * sizeof(CHAR));
		sprintf(szCmdString, "sens:wav:star %.3fnm\r\n", dblStartWL);
		dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

		//初始终止波长
		ZeroMemory(szCmdString, TXLENS * sizeof(CHAR));
		sprintf(szCmdString, "sens:wav:stop %.3fnm\r\n", dblStopWL);
		dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

		//初始RBW
		ZeroMemory(szCmdString, TXLENS * sizeof(CHAR));
		sprintf(szCmdString, "sens:band:res %.2fnm\r\n",dblRBW);
		dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

        ZeroMemory(szCmdString, TXLENS * sizeof(CHAR));
		sprintf(szCmdString, "sens:pow:dc:rang:low %.2fdbm\n", -70.0);
		dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

		//初始扫描点数
		ZeroMemory(szCmdString, TXLENS * sizeof(CHAR));
		sprintf(szCmdString,"sens:swe:poin %d\r\n",dwSweepPoint);
		dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

		
		//Set repeat sweep off
		ZeroMemory(szCmdString, TXLENS * sizeof(CHAR));
		sprintf(szCmdString,"init:cont off\r\n");
		dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}
		
		//等待状态
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA|dwErrorCode;
		}
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,"INST:NSEL 0\r\n");	 //设置到扫描模式	
		dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA|dwErrorCode;
		}
	}	
	
	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return ERROR_OSA|UNEXPECT_OCCUR;
	}

	if (dwErrorCode != SUCCESS)
	{
		CloseDevice();
	}
	return dwErrorCode;	
}

/************************************************************************
*  函数名称:RunSweep									                *
*  功能:普通模式下，运行扫描,适用：                                     *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  输入：                                                               *
		pdblWL        波长                                              *
		pdblPower     功率                                              * 
		szSelTrace    扫描线(A,B,C...)                                  *  
*  输入：                                                               *
		无                                                              *
*  返回值:																*
*             0: 函数执行成功。											*
*			  0xXXXXXXXX: 其他错误									    *
*  返回值类型:DWORD														*
*  创建日期:2013-10-15													*
*  创建人:陈可明														*
*  修改历史:无															*
*************************************************************************/
DWORD AgilentOSA::RunSweep(double* pdblWL,double* pdblPower,char szSelTrace)
{
	CHAR   szCmdString[TXLENS];
	TCHAR  tszDataStream[RXMINLENS];
	DWORD  dwErrorCode = SUCCESS;
	double dblStartWL = 0, dblStopWL= 0, dblWLStep = 0;
	int    iScanPoint = 0;
	LPSTR  pszToken = " ,\t\n", pszNewData = NULL;
	TCHAR  *pszDataStream;
	
	pszDataStream = (TCHAR*)VirtualAlloc(NULL, sizeof(TCHAR) * MAX_SWEEP_POINT * 20, 
							   MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	try
	{
		ZeroMemory(pszDataStream, iScanPoint * 20 * sizeof(TCHAR));
		ZeroMemory(szCmdString, TXLENS * sizeof(CHAR));
		sprintf(szCmdString, "FORM:DATA ASC\r\n");
		dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
		if(dwErrorCode != SUCCESS)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

		//Turn on trace szSelTrace
		ZeroMemory(szCmdString, TXLENS * sizeof(CHAR));
		sprintf(szCmdString, "Disp:Wind:Trac:Stat Tr%c, On\r\n", szSelTrace);
		dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

		//Continually update trace szSelTrace
		ZeroMemory(szCmdString, TXLENS * sizeof(CHAR));
		sprintf(szCmdString, "Trac:Feed:Cont Tr%c, Alw\r\n", szSelTrace);
		dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

		//Single sweep
		ZeroMemory(szCmdString, TXLENS * sizeof(CHAR));
		sprintf(szCmdString, "Init:Imm\r\n", szSelTrace);
		dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

	    //等待状态
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA|dwErrorCode;
		}	

		//Stop updating trace szSelTrace
		ZeroMemory(szCmdString, TXLENS * sizeof(CHAR));
		sprintf(szCmdString, "Trac:Feed:Cont Tr%c, Nev\r\n", szSelTrace);
		dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

		
		//读取起始波长
		ZeroMemory(szCmdString, TXLENS * sizeof(CHAR));
		sprintf(szCmdString, "sens:wav:star?\r\n");
		dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

		dwErrorCode = m_Commun.ReadDevice(tszDataStream, RXMINLENS);
		if(SUCCESS != dwErrorCode)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

		dblStartWL = atof(tszDataStream);
		
		//读取终止波长
		ZeroMemory(szCmdString, TXLENS * sizeof(CHAR));
		sprintf(szCmdString, "sens:wav:stop?\r\n");
		dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

		dwErrorCode = m_Commun.ReadDevice(tszDataStream, RXMINLENS);
		if(SUCCESS != dwErrorCode)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

		dblStopWL = atof(tszDataStream);


		//读取扫描点数
		ZeroMemory(szCmdString, TXLENS * sizeof(CHAR));
		sprintf(szCmdString, "TRACE:POIN? TR%c\n",szSelTrace);
		dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}
		ZeroMemory(tszDataStream, TXLENS * sizeof(TCHAR));
		dwErrorCode = m_Commun.ReadDevice(tszDataStream, RXMINLENS);
		if(SUCCESS != dwErrorCode)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

		iScanPoint = atoi(tszDataStream);

		//读取szSelTrace线的数据
		sprintf(szCmdString, "trac:data:y? tr%c\r\n",szSelTrace);
		dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
		if(dwErrorCode != SUCCESS)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

		dwErrorCode = m_Commun.ReadDevice(pszDataStream, iScanPoint * 20 * sizeof(TCHAR));
		if(dwErrorCode != SUCCESS)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

		pszNewData = strtok(pszDataStream, pszToken);

		if(pszNewData ==NULL)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

		pdblPower[0] = atof(pszNewData);

		for(int i = 1; i < iScanPoint; i++)
		{	
			pszNewData = strtok(NULL, pszToken);
			if(pszNewData == NULL)
			{
				break;
			}
			pdblPower[i] = atof(pszNewData);
		}

		//计算波长
		dblWLStep = (dblStopWL*1E9 - dblStartWL*1E9) / (iScanPoint - 1);
		for (i = 0; i < iScanPoint; i++)
		{
			pdblWL[i] = dblStartWL*1E9 + i * dblWLStep;
		}      
	}	

	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return ERROR_OSA|UNEXPECT_OCCUR;
	}

	VirtualFree(pszDataStream, 0, MEM_RELEASE);

	return dwErrorCode;	
}
/////////////////////////////////////////////////////////////
//函数说明：
//    获得单次扫描点数
//Add by wanxin
//Time：20150520
///////////////////////////////////////////////////////////////
DWORD AgilentOSA::GetSingleSweepPoint(DWORD *pCount)
{
	CHAR   szCmdString[TXLENS];
	TCHAR  tszDataStream[RXMINLENS];
	DWORD  dwErrorCode = SUCCESS;
	double dblStartWL = 0, dblStopWL= 0, dblWLStep = 0;
	int    iScanPoint = 0;
	
	try
	{
		//读取扫描点数
		ZeroMemory(szCmdString, TXLENS * sizeof(CHAR));
		sprintf(szCmdString, "sens:swe:poin?\n");
		dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}
		ZeroMemory(tszDataStream, TXLENS * sizeof(TCHAR));
		dwErrorCode = m_Commun.ReadDevice(tszDataStream, RXMINLENS);
		if(SUCCESS != dwErrorCode)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

		iScanPoint = atoi(tszDataStream);
		*pCount = iScanPoint;
	}	

	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return ERROR_OSA|UNEXPECT_OCCUR;
	}

	return dwErrorCode;	
}


/************************************************************************
*  函数名称:GetSweepData									            *
*  功能:普通模式下，读取扫描数据,适用：                                 *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  输入：                                                               *
		pdblWL        波长                                              *
		pdblPower     功率                                              * 
		szSelTrace    扫描线(A,B,C...)                                  *  
*  输入：                                                               *
		无                                                              *
*  返回值:																*
*             0: 函数执行成功。											*
*			  0xXXXXXXXX: 其他错误									    *
*  返回值类型:DWORD														*
*  创建日期:2013-10-15													*
*  创建人:陈可明														*
*  修改历史:无															*
*************************************************************************/
DWORD AgilentOSA::GetSweepData(double* pdblWL,double* pdblPower, char szSelTrace)
{
	CHAR   szCmdString[TXLENS];
	TCHAR  tszDataStream[RXMINLENS];
	DWORD  dwErrorCode = SUCCESS;
	double dblStartWL = 0, dblStopWL= 0, dblWLStep = 0;
	int    iScanPoint = 0;
	LPSTR  pszToken = " ,\t\n", pszNewData = NULL;
	TCHAR  *pszDataStream;
	
	pszDataStream = (TCHAR*)VirtualAlloc(NULL, sizeof(TCHAR) * MAX_SWEEP_POINT * 20, 
							   MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	try
	{
		//读取起始波长
		ZeroMemory(szCmdString, TXLENS * sizeof(CHAR));
		sprintf(szCmdString, "sens:wav:star?\r\n");
		dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

        ZeroMemory(szCmdString, TXLENS * sizeof(CHAR));
		dwErrorCode = m_Commun.ReadDevice(tszDataStream, RXMINLENS);
		if(SUCCESS != dwErrorCode)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

		dblStartWL = atof(tszDataStream);
		
		//读取终止波长
		ZeroMemory(szCmdString, TXLENS * sizeof(CHAR));
		sprintf(szCmdString, "sens:wav:stop?\r\n");
		dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}
     
		dwErrorCode = m_Commun.ReadDevice(tszDataStream, RXMINLENS);
		if(SUCCESS != dwErrorCode)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

		dblStopWL = atof(tszDataStream);

		//读取扫描点数
		ZeroMemory(szCmdString, TXLENS * sizeof(CHAR));
		sprintf(szCmdString, "sens:swe:poin?\n");
		dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}
		
		dwErrorCode = m_Commun.ReadDevice(tszDataStream, RXMINLENS);
		if(SUCCESS != dwErrorCode)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

		iScanPoint = atoi(tszDataStream);

	    ZeroMemory(szCmdString, TXLENS * sizeof(CHAR));
		sprintf(szCmdString, "FORM:DATA ASC\r\n");
		dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
		if(dwErrorCode != SUCCESS)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}
		
		//读取szSelTrace线的数据
	    ZeroMemory(szCmdString, TXLENS * sizeof(CHAR));
		sprintf(szCmdString, "trac:data:y? tr%c\r\n",szSelTrace);
		dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
		if(dwErrorCode != SUCCESS)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

        ZeroMemory(pszDataStream,iScanPoint * 20 * sizeof(TCHAR));
		dwErrorCode = m_Commun.ReadDevice(pszDataStream, iScanPoint * 20 * sizeof(TCHAR));
		if(dwErrorCode != SUCCESS)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

		pszNewData = strtok(pszDataStream, pszToken);

		if(pszNewData ==NULL)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

		pdblPower[0] = atof(pszNewData);

		for(int i = 1; i < iScanPoint; i++)
		{	
			pszNewData = strtok(NULL, pszToken);
			if(pszNewData == NULL)
			{
				break;
			}
			pdblPower[i] = atof(pszNewData);
		}

		//计算波长
		dblWLStep = (dblStopWL*1E9 - dblStartWL*1E9) / (iScanPoint - 1);
		for (i = 0; i < iScanPoint; i++)
		{
			pdblWL[i] = dblStartWL*1E9 + i * dblWLStep;
		}

	}	

	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return ERROR_OSA|UNEXPECT_OCCUR;
	}

	VirtualFree(pszDataStream, 0, MEM_RELEASE);

	return dwErrorCode;	
}

/************************************************************************
*  函数名称:GetChannelSNR									            *
*  功能:获取信号通道SNR值,适用：                                        *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						* 
*  输入：                                                               *
		无                                                              *
*  输出：                                                               *
		pdblSNR            通道SNR数组                                  *
		pdwChannelCount    通道数                                       * 
*  返回值:																*
*             0: 函数执行成功。											*
*			  0xXXXXXXXX: 其他错误									    *
*  返回值类型:DWORD														*
*  创建日期:2013-10-15													*
*  创建人:陈可明														*
*  修改历史:无															*
*************************************************************************/
DWORD AgilentOSA::GetChannelSNR(double* pdblSNR,DWORD* pdwChannelCount)
{
	DWORD  dwErrorCode = SUCCESS;

	return dwErrorCode;
}

/************************************************************************
*  函数名称:GetDeviceInfo									            *
*  功能:获取设备信息,适用：                                             *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						* 
*  输入：                                                               *
		无                                                              *
*  输出：                                                               *
		   stDevInfo  设备信息结构体                                    *
*  返回值:																*
*             0: 函数执行成功。											*
*			  0xXXXXXXXX: 其他错误									    *
*  返回值类型:DWORD														*
*  创建日期:2013-10-15													*
*  创建人:陈可明														*
*  修改历史:无															*
*************************************************************************/
DWORD AgilentOSA::GetDeviceInfo(stDevInfo *stInfo)
{
	DWORD  dwErrorCode = SUCCESS;

	return dwErrorCode;
}

/************************************************************************
*  函数名称:SaveDatatoPC									            *
*  功能:保存数据到PC机,适用：                                           *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						* 
*  输入：                                                               *
		lpSavePath  保存数据路径                                        *
		lpDataType  保存数据类型                                        *
		lpFileType  保存文件类型                                        *
		szSelTrace  保存扫描线(A,B,C...)数据                            *
*  输出：                                                               *
		   无                                                           *
*  返回值:																*
*             0: 函数执行成功。											*
*			  0xXXXXXXXX: 其他错误									    *
*  返回值类型:DWORD														*
*  创建日期:2013-10-15													*
*  创建人:陈可明														*
*  修改历史:无															*
*************************************************************************/

DWORD AgilentOSA::SaveDatatoPC(LPCTSTR lpSavePath, LPCTSTR lpDataType, LPCTSTR lpFileType, char szSelTrace)
{
	DWORD  dwErrorCode = SUCCESS;

	return dwErrorCode;
}

/************************************************************************
*  函数名称:SetCalibration									            *
*  功能:设置校OSA类型,适用：                                            *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						* 
*  输入：                                                               *
		dwCalibrationType  校OSA内、外模式标志                          *
*  输出：                                                               *
		   无                                                           *
*  返回值:																*
*             0: 函数执行成功。											*
*			  0xXXXXXXXX: 其他错误									    *
*  返回值类型:DWORD														*
*  创建日期:2013-10-15													*
*  创建人:陈可明														*
*  修改历史:无															*
*************************************************************************/
DWORD AgilentOSA::SetCalibration(DWORD dwCalibrationType)
{
	DWORD  dwErrorCode = SUCCESS;

	return dwErrorCode;
}

/************************************************************************
*  函数名称:GetErrorMessage									            *
*  功能:通过错误码获得解析信息	,适用：                                 *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						* 
*  输入：                                                               *
		dwErrorCode: 错误码                                             *
*  输出：                                                               *
		   pszErrorMsg: 错误码解析信息                                  *
*  返回值:																*
*             0: 函数执行成功。											*
*			  0xXXXXXXXX: 其他错误									    *
*  返回值类型:BOOL														*
*  创建日期:2013-10-15													*
*  创建人:陈可明														*
*  修改历史:无															*
*************************************************************************/
BOOL AgilentOSA::GetErrorMessage(DWORD dwErrorCode, char *pszErrorMsg)
{
	return TRUE;
}

/************************************************************************
*  函数名称:GetTotalPower									            *
*  功能:读取总功率,适用：		                                        *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						* 
*  输入：                                                               *
		无									                            *
*  输出：                                                               *
		 dblPow     总功率                                              *
*  返回值:																*
*             0: 函数执行成功。											*
*			  0xXXXXXXXX: 其他错误									    *
*  返回值类型:DWORD														*
*  创建日期:2014-04-11													*
*  创建人:赵寒飞														*
*  修改历史:无															*
*************************************************************************/
DWORD AgilentOSA::GetTotalPower(double &dblPow, char szSelTrace)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	CHAR szDataStream[RXMINLENS];
	BYTE byTraceIndex = szSelTrace;
	BYTE byTraceStart = 'A'-1;
	ZeroMemory(szCmdString, TXLENS * sizeof(CHAR));
	ZeroMemory(szDataStream,RXMINLENS * sizeof(CHAR));

	try
	{
		byTraceIndex -= byTraceStart;
		sprintf(szCmdString, "FORM:DATA ASC\r\n");
		dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
		if (SUCCESS != dwErrorCode) 
		{
	    	throw ERROR_OSA|dwErrorCode;
		}
	
		sprintf(szCmdString, "calc%d:tpow:stat 1\r\n", byTraceIndex);
		dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
		if (SUCCESS != dwErrorCode) 
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

		sprintf(szCmdString, "calc%d:tpow:data?\r\n", byTraceIndex);
		dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
		if (SUCCESS != dwErrorCode) 
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

		dwErrorCode = m_Commun.ReadDevice(szDataStream, RXMINLENS);
		if (SUCCESS != dwErrorCode) 
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

		dblPow = atof(szDataStream);//Unit nm
	}
	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return ERROR_OSA|UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}
/************************************************************************
*  函数名称:SetCalibration									            *
*  功能:读取实际RBW,适用：                                              *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						* 
*  输入：                                                               *
		dblBwAmp  计算BW的dB值				                            *
*  输出：                                                               *
		dblActBw  实际的BW                                              *
*  返回值:																*
*             0: 函数执行成功。											*
*			  0xXXXXXXXX: 其他错误									    *
*  返回值类型:DWORD														*
*  创建日期:2014-04-11													*
*  创建人:赵寒飞														*
*  修改历史:无															*
*************************************************************************/
DWORD AgilentOSA::GetActualBW(double dblBwAmp, double &dblActBw)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	CHAR szDataStream[RXMINLENS];
	ZeroMemory(szCmdString, TXLENS * sizeof(CHAR));
	ZeroMemory(szDataStream,RXMINLENS * sizeof(CHAR));

	try
	{
		//Enable bandwidth marker
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString, "calc1:mark1:func:bwid:stat on\r\n");
		dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
		if (SUCCESS != dwErrorCode) 
		{
	    	throw ERROR_OSA|dwErrorCode;
		}
	
		//Marker to peak
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString, "calc1:mark1:max\r\n");
		dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
		if (SUCCESS != dwErrorCode) 
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

		//Select db down where bw is
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString, "CALCulate:MARKer1:FUNCtion:BWIDth:NDB %.1fDb", dblBwAmp);
		dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
		if (SUCCESS != dwErrorCode) 
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

		//Return axis values between markers
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString, "CALCulate:MARKer1:FUNCtion:BWIDth:RESult?\r\n");
		dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
		if (SUCCESS != dwErrorCode) 
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

		dwErrorCode = m_Commun.ReadDevice(szDataStream, RXMINLENS);
		if (SUCCESS != dwErrorCode) 
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

		dblActBw = atof(szDataStream)*pow(10, 9);//Unit nm
	}
	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return ERROR_OSA|UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}
DWORD AgilentOSA::SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle)
{
	DWORD   dwErrorCode = SUCCESS;
    
	dwErrorCode = m_Commun.SetDeviceHandle(pszDeviceAddr, handle);
	return dwErrorCode;
}

DWORD AgilentOSA::GetZoomValue(double dbWLNM,double dbBWNM,double *pdbGetValue)
{
	DWORD  dwErrorCode = SUCCESS;
	
	return dwErrorCode;
}
