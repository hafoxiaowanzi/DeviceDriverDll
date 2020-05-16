#include "stdafx.h"
#include "math.h"
#include "..\\include\\TLS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// COp816XCtrl::COp816XCtrl - Constructor
COp81960A::COp81960A()
{

}

/////////////////////////////////////////////////////////////////////////////
// COp816XCtrl::~COp816XCtrl - Destructor

COp81960A::~COp81960A()
{
	// TODO: Cleanup your control's instance data here.

}

/***********************************************************************
*  函数名称:OpenDevice                                                 *
*  功能: 打开设备													   *
*  输入:                                                               *
*       1、pszDeviceAddr: 包含了设备地址，连接方式等信息。例如：	   *
*  输入数据类型:DWORD                                                  *
*  输出:                                                               *
*       ComHandle:输出Handle，用于识别不同 设备                        *
*  输出数据类型:unsigned long                                          *
*  返回值:                                                             *
*        错误码                                                        *
*  返回值类型:DWORD                                                    *
*  创建日期:2013-11-25                                                 *
*  创建人:Hanfei Zhao                                                  *
*  修改历史:无                                                         *
************************************************************************/
DWORD COp81960A::OpenDevice(LPCTSTR pszDeviceAddr, unsigned long *ComHandle)
{
	DWORD dwErrorCode = SUCCESS;

	try
	{
		dwErrorCode = m_Comm.OpenDevice(pszDeviceAddr, *ComHandle);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode;
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR|ERROR_OPEN;
	}

	return dwErrorCode;
}
/////////////////////////////////////////////////////////////////////////
//函数说明：
//    设置Aglient 81960A激光器的slot号
//Add by wanxin
//Time：20160308
/////////////////////////////////////////////////////////////////////////
DWORD  COp81960A::SetTLSSlotIndex(int nSlotIndex)
{
	DWORD dwErrorCode = SUCCESS;
	m_nSlotIndex = nSlotIndex;
    return dwErrorCode;
}
//////////////////////////////////////////////////////////////////
//函数说明：
//    设置激光器的CC模式
//Add by wanxin
//Time：20140807
//////////////////////////////////////////////////////////////
DWORD COp81960A::SetCoherenceControl(BOOL bEnable)
{
	DWORD dwErrorCode = SUCCESS;
	char chReadBuf[100];
	try
	{	
		ZeroMemory(chReadBuf,100);
		sprintf(chReadBuf, "SOUR%d:AM:STAT %d\r\n",m_nSlotIndex,bEnable);
		dwErrorCode = m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_COHERENCE_CONTROL;
		} 

		ZeroMemory(chReadBuf,100);
		sprintf(chReadBuf, "SOUR%d:AM:SOUR COHC\r\n",m_nSlotIndex,bEnable);
		dwErrorCode = m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_COHERENCE_CONTROL;
		} 
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR|ERROR_COHERENCE_CONTROL;
	}

	return dwErrorCode;	
}
//////////////////////////////////////////////////////////////////
//函数说明：
//    设置激光器的的波长
//Add by wanxin
//Time：20140807
//////////////////////////////////////////////////////////////
DWORD COp81960A::SetWavelength(long lChIndex, double dblWL)
{
	DWORD dwErrorCode = SUCCESS;
	char chReadBuf[100];
	try
	{
		ZeroMemory(chReadBuf, sizeof(char)*100);
		sprintf(chReadBuf, "SOUR%d:WAV %.3fnm\r\n",m_nSlotIndex, dblWL);
		dwErrorCode = m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL;
		} 
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR|ERROR_WL;
	}

	return dwErrorCode;
}
//////////////////////////////////////////////////////////////////
//函数说明：
//    设置激光器的的功率
//Add by wanxin
//Time：20140807
//////////////////////////////////////////////////////////////
DWORD COp81960A::SetSourcePower(long lChIndex, double dblPW)
{
	DWORD dwErrorCode = SUCCESS;
	char szBuf[256];

	try
	{
		ZeroMemory(szBuf,sizeof(char)*256);
		sprintf(szBuf, "sour%d:pow %.3fdbm\r\n",m_nSlotIndex,dblPW);
		dwErrorCode = m_Comm.WriteDevice(szBuf,strlen(szBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SRC_POW;
		} 
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR|ERROR_SRC_POW;
	}

	return dwErrorCode;
}
/////////////////////////////////////////////////////////////////////
//函数说明：
//    设置模块激光器最大输出光
//Add by wanxin
///////////////////////////////////////////////////////////////////////
DWORD COp81960A::SetMaxOutput(long lChIndex)
{
	
	DWORD dwErrorCode = SUCCESS;
	char chSendBuf[MAX_PATH];
	
	try
	{
		ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"sour%d:pow max\r\n",m_nSlotIndex);
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw "Send TLS Max Power error";
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR|ERROR_SRC_POW;
	}
	
	return dwErrorCode;
}
/////////////////////////////////////////////////////////////////////
//函数说明：
//    设置模块激光器频率
//Add by wanxin
///////////////////////////////////////////////////////////////////////
DWORD COp81960A::SetTLSFrequency(long lChIndex,double dblFrequrency)
{
	DWORD dwErrorCode = SUCCESS;
	char chSendBuf[MAX_PATH];
	
	try
	{
		int nFre =(int)dblFrequrency;
		ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"sour%d:am:freq %d\r\n",m_nSlotIndex,nFre);
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw "Send TLS Frequency error";
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR|ERROR_SRC_POW;
	}
	
	return dwErrorCode;
}

//////////////////////////////////////////////////////////////////
//函数说明：
//    设置激光器的的功率的单位
//Add by wanxin
//Time：20140807
//////////////////////////////////////////////////////////////
DWORD COp81960A::SetSourceUnit(long lChIndex, long lUnit)
{
	DWORD dwErrorCode = SUCCESS;
	char szBuf[256];
	try
	{
		ZeroMemory(szBuf,sizeof(char)*256);			
		sprintf(szBuf, "sour%d:POW:UNIT %d\r\n",m_nSlotIndex,lUnit);
		dwErrorCode = m_Comm.WriteDevice(szBuf,strlen(szBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_UNIT;
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR|ERROR_OPEN;
	}

	return dwErrorCode;
}
//////////////////////////////////////////////////////////////////
//函数说明：
//    设置激光器的参数函数，高低光的使用采用该函数
//Add by wanxin
//Time：20140807
//////////////////////////////////////////////////////////////
DWORD COp81960A::SetParameters(long lChIndex, BOOL bLowSSE, double dblPower, double dblWavelength)
{
	DWORD dwErrorCode = SUCCESS;
	char chReadBuf[100];
	try
	{
		ZeroMemory(chReadBuf,sizeof(char)*100);
		sprintf(chReadBuf, "sour%d:output 1\r\n",m_nSlotIndex);
		dwErrorCode = m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWITCH_CHANNEL;
		}
		if (bLowSSE)
		{							
// 			ZeroMemory(chReadBuf,sizeof(char)*100);
// 			sprintf(chReadBuf, "output0:path lows\r\n");
// 			dwErrorCode = m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
// 			if (SUCCESS != dwErrorCode)
// 			{
// 				throw dwErrorCode|ERROR_SWITCH_CHANNEL;
// 			}
		}
		else
		{
// 			ZeroMemory(chReadBuf,sizeof(char)*100);
// 			sprintf(chReadBuf, "output0:path high\r\n");
// 			dwErrorCode = m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
// 			if (SUCCESS != dwErrorCode)
// 			{
// 				throw dwErrorCode|ERROR_SWITCH_CHANNEL;
// 			}
		}

		dwErrorCode = SetSourcePower(lChIndex, dblPower);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode;
		}

		dwErrorCode = SetWavelength(lChIndex, dblWavelength);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode;
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR|ERROR_SWITCH_CHANNEL;
	}

	return dwErrorCode;
}
//////////////////////////////////////////////////////////////////
//函数说明：
//    设置激光器的激光器开启、关闭状态
//Add by wanxin
//Time：20140807
//////////////////////////////////////////////////////////////
DWORD COp81960A::SetOutputEnable(BOOL bEnable)
{
	DWORD dwErrorCode = SUCCESS;
	char chReadBuf[100];
	try
	{
		ZeroMemory(chReadBuf,sizeof(char)*100);
		sprintf(chReadBuf, "sour%d:output %d\r\n",m_nSlotIndex,bEnable);
		dwErrorCode = m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWITCH_CHANNEL;
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR|ERROR_SWITCH_CHANNEL;
	}

	return dwErrorCode;
}
//////////////////////////////////////////////////////////////////
//函数说明：
//    设置激光器的MainFrame的handle句柄
//Add by wanxin
//Time：20140807
//////////////////////////////////////////////////////////////
DWORD COp81960A::SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle)
{
	DWORD dwErrorCode = SUCCESS;
	dwErrorCode = m_Comm.SetDeviceHandle(pszDeviceAddr, handle);

	return dwErrorCode;
}
//////////////////////////////////////////////////////////////////
//函数说明：
//    关闭该激光器MainFrame设备句柄
//Add by wanxin
//Time：20140807
//////////////////////////////////////////////////////////////
DWORD COp81960A::CloseDevice()
{
	DWORD dwErrorCode = SUCCESS;
	try
	{
		dwErrorCode = m_Comm.CloseDevice();
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR|ERROR_OPEN;
	}

	return dwErrorCode;
}
/////////////////////////////////////////////////////////
//函数说明：
//     获得激光器设置
//Add by wanxin
//Time：20140827
////////////////////////////////////////////////////////////
DWORD COp81960A::GetTLSSettings(long lChIndex,double* pdblWavelength,double* pdblPower,BYTE* pdCtrlState)
{
	DWORD dwErrorCode = SUCCESS;
	char chSendBuf[MAX_PATH];
	BYTE bStatus;
	try
	{				
		
		//获得波长
		ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"sour%d:wav?\r\n",m_nSlotIndex);
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_GET_TLS_RANGE;
		}

		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		dwErrorCode = m_Comm.ReadDevice(chSendBuf,MAX_PATH);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_GET_TLS_RANGE;
		}
		* pdblWavelength = atof(chSendBuf)*1E9;
		
		//获得功率
		ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"sour%d:pow?\n",m_nSlotIndex);
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_GET_TLS_RANGE;
		}
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		dwErrorCode = m_Comm.ReadDevice(chSendBuf,MAX_PATH);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_GET_TLS_RANGE;
		}
		* pdblPower = atof(chSendBuf);
		//获得开启状态
		ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"sour%d:output stat?\n",m_nSlotIndex);
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_GET_TLS_RANGE;
		}
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		dwErrorCode = m_Comm.ReadDevice(chSendBuf,MAX_PATH);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_GET_TLS_RANGE;
		}
		bStatus = atoi(chSendBuf);
		* pdCtrlState = bStatus;
		if (bStatus ==1) 
		{			
			//获得CC状态判断状态
			ZeroMemory(chSendBuf,MAX_PATH);
			sprintf(chSendBuf,"sour%d:am:sour?\n",m_nSlotIndex);
			dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
			if (SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_GET_TLS_RANGE;
			}
			ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
			dwErrorCode = m_Comm.ReadDevice(chSendBuf,MAX_PATH);
			if (SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_GET_TLS_RANGE;
			}
            bStatus = atoi(chSendBuf);
			if (bStatus ==1)
			{
				* pdCtrlState =2;
			}	
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR|ERROR_OPEN;
	}

	return dwErrorCode;
}
/////////////////////////////////////////////////////////
//函数说明：
//     获得模块最大最小的波长范围
//Add by wanxin
//Time：20140807
////////////////////////////////////////////////////////////
DWORD COp81960A::GetTLSWLRange(double &dbWLMin,double &dbWLMax)
{
	char chSendBuf[MAX_PATH];
	DWORD dwErrorCode = SUCCESS;
	try
	{				
		
		//获得最小波长range
		ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"sour%d:wav? min\n",m_nSlotIndex);
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_GET_TLS_RANGE;
		}

		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		dwErrorCode = m_Comm.ReadDevice(chSendBuf,MAX_PATH);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_GET_TLS_RANGE;
		}
		dbWLMin = atof(chSendBuf)*1E9;
		
		//获得最大波长range
		ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"sour%d:wav? max\n",m_nSlotIndex);
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_GET_TLS_RANGE;
		}
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		dwErrorCode = m_Comm.ReadDevice(chSendBuf,MAX_PATH);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_GET_TLS_RANGE;
		}
		dbWLMax = atof(chSendBuf)*1E9;				
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR|ERROR_OPEN;
	}

	return dwErrorCode;
}

//////////////////////////////////////////////////////
//函数说明
//    获得扫描的起始波长范围
//Add by wanxin
//Time:20140807
///////////////////////////////////////////////////////
DWORD COp81960A::GetScanWLRange(double &dbStartWL,double &dbStopWL)
{
	char chSendBuf[MAX_PATH];
	int nCount;
	DWORD dwErrorCode = SUCCESS;
	try
	{								
		//读取扫描起始波长
		nCount = 0;		
		while (TRUE)
		{
			ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
			sprintf(chSendBuf, "sour%d:wav:swe:star?\r\n",m_nSlotIndex);
			dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
			if (SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_TLS_SCAN_WLRANGE;
			}					
			ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
			dwErrorCode = m_Comm.ReadDevice(chSendBuf,MAX_PATH);
			if (SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_TLS_SCAN_WLRANGE;
			}
			
			dbStartWL = atof(chSendBuf)*1E9;
			if (dbStartWL > 0.0)
			{
				break;
			}
			nCount++;
			if (nCount > 100)
			{
				throw dwErrorCode|ERROR_TLS_SCAN_WLRANGE;
			}
		}
		//读取扫描停止波长
		nCount = 0;
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		while (TRUE)
		{
			ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
			sprintf(chSendBuf, "sour%d:wav:swe:stop?\n",m_nSlotIndex);
			dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
			if (SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_TLS_SCAN_WLRANGE;
			}	
			ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
			dwErrorCode = m_Comm.ReadDevice(chSendBuf,MAX_PATH);
			if (SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_TLS_SCAN_WLRANGE;
			}
			
			dbStopWL = atof(chSendBuf)*1E9;
			if (dbStopWL > 0.0)
			{
				break;
			}
			nCount++;
			if (nCount > 100)
			{
				throw dwErrorCode|ERROR_TLS_SCAN_WLRANGE;
			}
		}						
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR|ERROR_OPEN;
	}

	return dwErrorCode;
}

/////////////////////////////////////////////////////////////////
//函数说明：
//    读取TLS输出功率
//Add by wanxin
/////////////////////////////////////////////////////////////////
DWORD COp81960A::ReadTLSPower(double &dbPower)
{	
	char chSendBuf[MAX_PATH];
	DWORD dwErrorCode = SUCCESS;
	try
	{				
		
		ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"sour%d:pow?\n",m_nSlotIndex);
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_POWER;
		}	
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		dwErrorCode = m_Comm.ReadDevice(chSendBuf,MAX_PATH);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_POWER;
		}
		dbPower =atof(chSendBuf);
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR|ERROR_OPEN;
	}

	return dwErrorCode;
}

///////////////////////////////////////////////////////////////////////
//函数说明：
//    获得设置的扫描参数
//Add by wanxin
//Time:20140807
///////////////////////////////////////////////////////////////////////
BOOL COp81960A::GetScanParameter(stScanParam *pSettingParam)
{
	char chSendBuf[MAX_PATH];
	double dbStartWL,dbStopWL;
	double dbTLSPower;
	DWORD dwErrorCode = SUCCESS;
	try
	{				
		
		//获得扫描波长
		dwErrorCode = GetScanWLRange(dbStartWL,dbStopWL);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_WLRANGE;
		}
		pSettingParam->m_dblStartWL = dbStartWL;
		pSettingParam->m_dblStopWL = dbStopWL;
		
		//获得扫描的speed
		ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"sour%d:wav:swe:spe?\n",m_nSlotIndex);
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_WLRANGE;
		}	
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		dwErrorCode = m_Comm.ReadDevice(chSendBuf,MAX_PATH);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_WLRANGE;
		}
		double dbTemp = atof(chSendBuf);
		pSettingParam->m_nSpeed = (int)(dbTemp*1E9);
		
		//获得扫描的step
		ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"sour%d:wav:swe:step?\n",m_nSlotIndex);
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_WLRANGE;
		}	
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		dwErrorCode = m_Comm.ReadDevice(chSendBuf,MAX_PATH);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_WLRANGE;
		}
		pSettingParam->m_dblStepSize = atof(chSendBuf);
		
		if (!ReadTLSPower(dbTLSPower))
		{
			throw "Read setting power error";
		}
		pSettingParam->m_dblTLSPower = dbTLSPower;
		
	}
	catch(char *pstrMsg)
	{
		AfxMessageBox(pstrMsg);
		return FALSE;
	}
	return TRUE;
}

///////////////////////////////////////////////////////////////////
//函数说明：
//    判断当前的扫描参数是否变化,如果设置的与变化的不同则返回FASLE
//    如果判断相同则返回TRUE
//Add by wanxin
///////////////////////////////////////////////////////////////////
BOOL COp81960A::JudgeScanParameter()
{
	stScanParam stReadInof;
	BOOL bModify = FALSE;
	try
	{
		if (!GetScanParameter(&stReadInof))
		{
			throw"Read scan setting information error";
		}
		if (fabs(m_pScanParam->m_dblTLSPower - stReadInof.m_dblTLSPower)>0.1
			||fabs(m_pScanParam->m_dblStartWL-0.5 - stReadInof.m_dblStartWL)>0.1
			||fabs(m_pScanParam->m_dblStopWL+0.5 - stReadInof.m_dblStopWL)>0.1
			||fabs(m_pScanParam->m_dblStepSize - stReadInof.m_dblStepSize)>0.001
			||m_pScanParam->m_nSpeed != stReadInof.m_nSpeed)
		{
			bModify = FALSE;
		}
		else
		{
			bModify = TRUE;
		}
	}
	catch(...)
	{
		bModify = FALSE;
	}
	return bModify;
}

//////////////////////////////////////////////////
//函数说明：
//    设置激光器扫描停止函数
//Add by wanxin
//////////////////////////////////////////////////
BOOL COp81960A::SetScanStop()
{
	char chSendBuf[MAX_PATH];
	int nCount;
	int CurentFlag;
	DWORD dwErrorCode = SUCCESS;
	try
	{							
		
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		sprintf(chSendBuf, "sour%d:wav:swe:flag?\n",m_nSlotIndex);
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw "Send read swe state error";
		}	

		nCount = 0;		
		while (TRUE)
		{
			ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
			dwErrorCode = m_Comm.ReadDevice(chSendBuf,MAX_PATH);
			if (SUCCESS != dwErrorCode)
			{
				throw "Send TLS scan stop error";
			}
			CurentFlag = atoi(chSendBuf);
			if (CurentFlag == 0)
			{
				break;
			}
			else
			{
				ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
				sprintf(chSendBuf, "sour%d:wav:swe 0\n",m_nSlotIndex);
				dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
				if (SUCCESS != dwErrorCode)
				{
					throw "Send TLS scan stop error";
				}
				Sleep(2000);
				break;
			}
			nCount++;
			if (nCount > 100)
			{
				throw"Set TLS scan stop error";
			}
		}		
	}
	catch(char *pstrMsg)
	{
		AfxMessageBox(pstrMsg);
		return FALSE;
	}
	return TRUE;	
}

//////////////////////////////////////////////////////////////////////////
//函数说明：
//    设置扫描起始波长
//Add by wanxin
/////////////////////////////////////////////////////////////////////////
BOOL COp81960A::SetScanWLRange(double dbWLStart,double dbWLStop)
{
	char chSendBuf[MAX_PATH];
	DWORD dwErrorCode = SUCCESS;
	try
	{				
		
		//设置开始扫描波长
		ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"sour%d:wav:swe:star %.3fNM\n",m_nSlotIndex,dbWLStart);
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw "Send TLS scan stop error";
		}
		
		//设置停止扫描波长
		ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"sour%d:wav:swe:stop %.3fNM\n",m_nSlotIndex,dbWLStop);
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw "Send TLS scan stop error";
		}		
	}
	catch(char *pstrMsg)
	{
		AfxMessageBox(pstrMsg);
		return FALSE;
	}
	return TRUE;
}
/////////////////////////////////////////////////////////////////////
//函数说明：
//    设置模块激光输出功率
//Add by wanxin
///////////////////////////////////////////////////////////////////////
BOOL COp81960A::SetTLSPower(double dbPower)
{
	char chSendBuf[MAX_PATH];
	DWORD dwErrorCode = SUCCESS;
	try
	{						
		ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"sour%d:pow %.3fDBM\n",m_nSlotIndex,dbPower);
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw "Send TLS Power error";
		}		
	}
	catch(char *pstrMsg)
	{
		AfxMessageBox(pstrMsg);
		return FALSE;
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////
//函数说明：
//    关闭该激光器MainFrame设备句柄
//Add by wanxin
//Time：20140807
//////////////////////////////////////////////////////////////
DWORD COp81960A::PrepareScan(long lChIndex,stScanParam* lScanParam)
{
	char chSendBuf[MAX_PATH];
	double dbStartWL,dbStopWL;
	double dbReadStartWL,dbReadStopWL;
	DWORD dwErrorCode = SUCCESS;
	try
	{				
		m_pScanParam = lScanParam;
		if (!GetTLSWLRange(dbStartWL,dbStopWL))
        {
			throw dwErrorCode|ERROR_GET_TLS_RANGE;
        }
		if (m_pScanParam->m_dblStartWL < dbStartWL || m_pScanParam->m_dblStopWL > dbStopWL)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_WLRANGE;
		}
		//根据设置的扫描范围多扫0.05nm
		dbStartWL = m_pScanParam->m_dblStartWL - 0.5;	
		dbStopWL = m_pScanParam->m_dblStopWL + 0.5;
		
		m_pScanParam->m_dwSampleCount  = (DWORD)((m_pScanParam->m_dblStopWL - m_pScanParam->m_dblStartWL)/m_pScanParam->m_dblStepSize + 0.5);		
		
		//设置扫描模式为continue模式
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		sprintf(chSendBuf, "sour%d:wav:swe:mode cont\n",m_nSlotIndex);
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_GET_TLS_RANGE;
		}
		//设置Repeat模式为onew模式
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		sprintf(chSendBuf, "sour%d:wav:swe:rep onew\n",m_nSlotIndex);
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_PREPARE;
		}
		//判断当前扫描参数是否
		if (!JudgeScanParameter())
		{
			// 		//不管激光器是在扫描状态还是不在扫描状态，
			// 		//先发送停止扫描指令	
			if (!SetScanStop())
			{
				throw dwErrorCode|ERROR_TLS_SCAN_PREPARE;
			}
			//设置扫描的起始波长
			if (!SetScanWLRange(dbStartWL,dbStopWL))
			{
				throw dwErrorCode|ERROR_TLS_SCAN_PREPARE;
			}
			//回读扫描的起始波长
			if (!GetScanWLRange(dbReadStartWL,dbReadStopWL))
			{
				throw dwErrorCode|ERROR_TLS_SCAN_PREPARE;
			}
			//判断设置的扫描起始波长与获得的起始波长是否相同
			if (fabs(dbStartWL - dbReadStartWL) > 0.01 || fabs(dbStopWL - dbReadStopWL) > 0.01 )
			{
				throw dwErrorCode|ERROR_TLS_SCAN_PREPARE;
			}
			//设置扫描速度
			ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
			if (m_pScanParam->m_nSpeed > 40) 
			{
				sprintf(chSendBuf, "sour%d:wav:swe:spe 0.5nm/s\n",m_nSlotIndex,m_pScanParam->m_nSpeed);
			}
			else
			{
				sprintf(chSendBuf, "sour%d:wav:swe:spe %dnm/s\n",m_nSlotIndex,m_pScanParam->m_nSpeed);
			}
			
			dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
			if (SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_TLS_SCAN_PREPARE;
			}
			//设置triger扫描步长
			ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
			sprintf(chSendBuf, "sour%d:wav:swe:step %.3fnm\n",m_nSlotIndex,m_pScanParam->m_dblStepSize);
			dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
			if (SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_TLS_SCAN_PREPARE;
			}
			
			//设置激光器的功率
			if (!SetTLSPower(m_pScanParam->m_dblTLSPower))
			{
				throw dwErrorCode|ERROR_TLS_SCAN_PREPARE;
			}
		}
		
		//获得扫描的trig点数,并赋值给结构体
//		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
//		sprintf(chSendBuf, "sour0:wav:swe:exp?\n");
//		dwErrorCode = m_Comm.WriteDevice(chSendBuf);
//		if (SUCCESS != dwErrorCode)
//		{
//			throw dwErrorCode|ERROR_TLS_SCAN_PREPARE;
//		}
//		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
//		dwErrorCode = m_Comm.ReadDevice(chSendBuf,MAX_PATH);
//		if (SUCCESS != dwErrorCode)
//		{
//			throw "Send TLS scan stop error";
//		}
//		m_dwScanPoint = atoi(chSendBuf) - 1;
		m_dwScanPoint = (DWORD)((dbStopWL - dbStartWL)/m_pScanParam->m_dblStepSize + 0.5)-1;
		
		//设置trig的模式
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		sprintf(chSendBuf, "trig%d:conf 3\r\n",m_nSlotIndex);
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_PREPARE;
		}
		
		//设置tripg输入为sws模式
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		sprintf(chSendBuf, "trig%d:inp sws\r\n",m_nSlotIndex);
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_PREPARE;
		}
		//设置trig输出为stf模式
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		sprintf(chSendBuf, "trig%d:outp stf\r\n",m_nSlotIndex);
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_PREPARE;
		}
		//设置扫描最大循环次数
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		sprintf(chSendBuf, "sour%d:wav:swe:cycl 0\r\n",m_nSlotIndex);
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_PREPARE;
		}
		//设置am的state模式为0
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		sprintf(chSendBuf, "sour%d:am:stat 0\r\n",m_nSlotIndex);
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_PREPARE;
		}
		//设置TLS为Log模式
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		sprintf(chSendBuf, "sour%d:wav:swe:llog 1\r\n",m_nSlotIndex);
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_PREPARE;
		}
        //启动到扫描模式
		if(!ScanStart())
		{
			throw dwErrorCode|ERROR_TLS_SCAN_PREPARE;
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR|ERROR_OPEN;
	}
	
	return dwErrorCode;
}
//////////////////////////////////////////////
//函数说明：
//    通过发送软trig来驱动扫描
//Add by wanxin
//Time:20140807
////////////////////////////////////////////////
DWORD COp81960A::SetScanStart(long lChIndex)
{
	char chSendBuf[MAX_PATH];
	int preFlag,CurentFlag;
	DWORD dwErrorCode = SUCCESS;
	try
	{				
		
		
		//读取Flag标志,如果Flag%2 ==1，则发送trig开始扫描
		while(TRUE)
		{
			ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
			sprintf(chSendBuf, "sour%d:wav:swe:flag?\r\n",m_nSlotIndex);
			dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
			if (SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_TLS_SOFT_TRIGER;
			}
			Sleep(50);
			ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
			dwErrorCode = m_Comm.ReadDevice(chSendBuf,MAX_PATH);
			if (SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_TLS_SOFT_TRIGER;
			}
			
			preFlag = atoi(chSendBuf);
			if (preFlag%2==1)
			{
				break;
			}
		}
		ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"sour%d:wav:swe:soft\r\n",m_nSlotIndex);
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SOFT_TRIGER;
		}
		//读取Flag标志，如果前面的Flag小于当前Flag则认为扫描完成
		while(TRUE)
		{
			ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
			sprintf(chSendBuf, "sour%d:wav:swe:flag?\n",m_nSlotIndex);
			dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
			if (SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_TLS_SOFT_TRIGER;
			}
			Sleep(50);
			ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
			dwErrorCode = m_Comm.ReadDevice(chSendBuf,MAX_PATH);
			if (SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_TLS_SOFT_TRIGER;
			}
			CurentFlag = atoi(chSendBuf);			
			if (CurentFlag > preFlag)
			{
				break;
			}
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR|ERROR_OPEN;
	}
	
	return dwErrorCode;
}
////////////////////////////////////////////////////////////////
//函数说明：
//    通过触发软trig命令来启动扫描
//Add by wanxin
//Time:2040807
////////////////////////////////////////////////////////////////
DWORD COp81960A::ScanStart()
{
	char chSendBuf[MAX_PATH];
	DWORD dwErrorCode = SUCCESS;
	try
	{						
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		sprintf(chSendBuf, "sour%d:wav:swe 1\r\n",m_nSlotIndex);
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_START;
		}	
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR|ERROR_OPEN;
	}
	
	return dwErrorCode;	  
}
////////////////////////////////////////////////////////////////
//函数说明：
//    通过触发软trig命令来启动扫描
//Add by wanxin
//Time:2040807
////////////////////////////////////////////////////////////////
DWORD COp81960A::SetScanStop(long lChIndex)
{
	char chSendBuf[MAX_PATH];
	DWORD dwErrorCode = SUCCESS;
	try
	{						
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		sprintf(chSendBuf, "sour%d:wav:swe 0\r\n",m_nSlotIndex);
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_STOP;
		}	
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR|ERROR_OPEN;
	}
	
	return dwErrorCode;	  
}
///////////////////////////////////////////////////////////////////
//函数说明：
//    获得扫描波长函数
//Add by wanxin
///////////////////////////////////////////////////////////////////
DWORD COp81960A::GetLamdaScanWLResult(long lChIndex,double* pdbWLAarry)
{
	char chSendBuf[MAX_PATH];
	PBYTE pbWLArry =  NULL;
	double* dbTemp;
	int nTemp;
	DWORD dwErrorCode = SUCCESS;
	try
	{	
		
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		sprintf(chSendBuf, "sour%d:read:poin? llog\r\n",m_nSlotIndex);
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_RESULT;
		}
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		dwErrorCode = m_Comm.ReadDevice(chSendBuf,MAX_PATH);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_RESULT;
		}
		nTemp = atoi(chSendBuf);
		
		//从TLS扫描结果中读取点数
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		sprintf(chSendBuf,"sour%d:read:data:block? LLOG,0,%d",m_nSlotIndex,nTemp);
		dwErrorCode = m_Comm.ReadDevice(chSendBuf,MAX_PATH);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_RESULT;
		}
		if (pbWLArry == NULL)
		{
			pbWLArry = new BYTE[(nTemp)*8];
		}
		
		ZeroMemory(pbWLArry, sizeof(BYTE)*(nTemp)*8);
		dwErrorCode = m_Comm.ReadDevice(pbWLArry,nTemp*8);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_RESULT;
		}
		
		nTemp = pbWLArry[1] - '0' + 2;
		
		dbTemp = (double*)(pbWLArry+nTemp);
		
		for (int nIndex=0;nIndex < (int)m_pScanParam->m_dwSampleCount;nIndex++)
		{
			pdbWLAarry[nIndex] = dbTemp[nIndex]*1E9;		
		}	
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR|ERROR_OPEN;
	}
	
	if (pbWLArry != NULL)
	{
		delete [] pbWLArry;
		pbWLArry = NULL;
	}
	
	return dwErrorCode;	 
}