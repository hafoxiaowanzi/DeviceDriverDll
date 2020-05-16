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
*  ��������:OpenDevice													*
*  ����: �������豸,���ã�                                            *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142AAgilent 86142B						*
*  ����:																*
*		1.stType:�豸���ͽṹ��											*
*       2.pszDeviceAddr:ͨѶ��Ϣ										*
*  �����������:stDevType, char* 										*
*  ���:																*
*       comHandle:����ͨѶ�ӿ�Handle									*
*  �����������:CommunicationHandle										*
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*			  0xXXXXXXXX: ��������									    *
*  ����ֵ����:DWORD														*
*  ��������:2013-10-15													*
*  ������:�¿���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD AgilentOSA::OpenDevice(stDevType stType, char* pszDeviceAddr, unsigned long *comHandle)
{
	DWORD dwErrorCode = SUCCESS;

	try
	{
		m_bNFLib = FALSE;
		
		//���豸
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
*  ��������:CloseDevice													*
*  ����: �˳������豸,���ã�                                            *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  ����: ��																*
*  �������                                                             *
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*			  0xXXXXXXXX: ��������									    *
*  ����ֵ����:DWORD														*
*  ��������:2013-10-15													*
*  ������:�¿���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD AgilentOSA::CloseDevice()
{
	DWORD dwErrorCode = SUCCESS;

	try
	{
		//�˳�����״̬
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
*  ��������:ResetDevice													*
*  ����: ��λ�豸,���ã�                                                *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  ����: ��																*
*  �������                                                             *
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*			  0xXXXXXXXX: ��������									    *
*  ����ֵ����:DWORD														*
*  ��������:2013-10-15													*
*  ������:�¿���														*
*  �޸���ʷ:��															*
*************************************************************************/

DWORD AgilentOSA::ResetDevice()
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	ZeroMemory(szCmdString, TXLENS * sizeof(CHAR));

	try
	{
		//��λOSA
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
*  ��������:SetOSALocalCtrl												*
*  ����: ����OSA�豸Ϊ����״̬,���ã�                                   *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  ����: ��																*
*  �������                                                             *
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*			  0xXXXXXXXX: ��������									    *
*  ����ֵ����:DWORD														*
*  ��������:2013-10-15													*
*  ������:�¿���														*
*  �޸���ʷ:��															*
*************************************************************************/

DWORD AgilentOSA::SetOSALocalCtrl()
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	ZeroMemory(szCmdString, TXLENS * sizeof(CHAR));

	try
	{
		//����LOCAL״̬
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
*  ��������:SetRBW												        *
*  ����: ����OSA�豸Ϊ����״̬,���ã�                                   *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  ����: dblRBW	����RBWĿ��ֵ											*
*  �������                                                             *
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*			  0xXXXXXXXX: ��������									    *
*  ����ֵ����:DWORD														*
*  ��������:2013-10-15													*
*  ������:�¿���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD AgilentOSA::SetRBW(double dblRBW)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	ZeroMemory(szCmdString, TXLENS * sizeof(CHAR));

	try
	{
		//����RBWֵ
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
*  ��������:GetRBW												        *
*  ����: ��ȡOSA RBW��ǰ����ֵ,���ã�                                   *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  ����: ��							                                 	*
*  �����*dblRBW	��ȡRBWĿ��ֵ,��λ��nm                              *
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*			  0xXXXXXXXX: ��������									    *
*  ����ֵ����:DWORD														*
*  ��������:2013-10-15													*
*  ������:�¿���														*
*  �޸���ʷ:��															*
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
		//��ȡRBWֵ
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
*  ��������:InitAmpTest												    *
*  ����: ��ȡOSA RBW��ǰ����ֵ,���ã�                                   *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  ����: dblStartWL����ʼ������                                         *
		 dblStopWL����ֹ������	                                        *
		 dblRBW��ɨ��ֱ��ʣ�                                           *
		 ��λ��nm                                                       *
*  �������                                                             *
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*			  0xXXXXXXXX: ��������									    *
*  ����ֵ����:DWORD														*
*  ��������:2013-10-15													*
*  ������:�¿���														*
*  �޸���ʷ:��															*
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
		//�������״̬
		dwErrorCode = m_Commun.ClearDevice();
		if(SUCCESS != dwErrorCode)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}
	
		//OSA��ʼ״̬
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
				//��λOSA
				ZeroMemory(szCmdString,TXLENS);
				sprintf(szCmdString,"*RST\r\n");
				dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
				if(SUCCESS != dwErrorCode)
				{
					throw ERROR_OSA|dwErrorCode;
				}
				Sleep(2000);
				dwErrorCode = CompleteRequest();
				//��ʼ��Amp ISSģʽ
				ZeroMemory(szCmdString,TXLENS);
				sprintf(szCmdString,"INST:SEL 'Amp_ISS_Test'\r\n");
				dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
				if(SUCCESS != dwErrorCode)
				{
					throw ERROR_OSA|dwErrorCode;
				}
				Sleep(10000);
				//�ȴ�״̬
				dwErrorCode = CompleteRequest();
				if(SUCCESS != dwErrorCode)
				{
					throw ERROR_OSA|dwErrorCode;
				}
			}
			
			//������ʼ����
			ZeroMemory(szCmdString,TXLENS);
			sprintf(szCmdString, "SENS:START %.2f NM\r\n", dblStartWL);
			dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode;
			}
			
			//������ֹ����
			ZeroMemory(szCmdString,TXLENS);
			sprintf(szCmdString, "SENS:STOP %.2f NM\r\n", dblStopWL);
			dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode;
			}
			
			//����RBWֵ
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
		
		//�ȴ�״̬
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
*  ��������:CompleteRequest												*
*  ����: ��ѯOSA����״̬,���ã�                                         *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  ����: ��                                                             *
*  �������                                                             *
*  ����ֵ: ��															*
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*			  0xXXXXXXXX: ��������									    *
*  ����ֵ����:DWORD														*
*  ��������:2013-10-15													*
*  ������:�¿���														*
*  �޸���ʷ:��															*
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

		//���5���Ӻ󣬲�����δ��ɣ����س�ʱ����
		if (lIndex > 1500000)
		{
			return ERROR_RUN_OVERTIME;
		}

		lIndex++;

	} while(!strchr(szDataStream, '1'));//״̬Ϊ1ʱ���˳���ѯ

	return SUCCESS;
}

/************************************************************************
*  ��������:MeasureSource												*
*  ����: �Ŵ�ģʽ�½���ɨԴ,���ã�                                      *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  ����: ��                                                             *
*  �������                                                             *
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*			  0xXXXXXXXX: ��������									    *
*  ����ֵ����:DWORD														*
*  ��������:2013-10-15													*
*  ������:�¿���														*
*  �޸���ʷ:��															*
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
			//EDFAģʽ ɨԴ
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
		
		
		//�ȴ�״̬
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
*  ��������:MeasureAmplifier										    *
*  ����: �Ŵ�ģʽ�½��зŴ�,���ã�                                      *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  ����: bScanSrcOnly  ɨ��״̬                                         *
*  �������                                                             *
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*			  0xXXXXXXXX: ��������									    *
*  ����ֵ����:DWORD														*
*  ��������:2013-10-15													*
*  ������:�¿���														*
*  �޸���ʷ:��															*
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
				//EDFAģʽ �Ŵ�
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
		
		//�ȴ�״̬
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
*  ��������:GetChannelCount										        *
*  ����:��ȡ����Դ�ź�ͨ��,���ã�                                       *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  ����: ��                                                             *
*  �����*pdwChannelCount  �ź�ͨ��                                     *
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*			  0xXXXXXXXX: ��������									    *
*  ����ֵ����:DWORD														*
*  ��������:2013-10-15													*
*  ������:�¿���														*
*  �޸���ʷ:��															*
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
			//��ȡ�����ź�ͨ����
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
			
			//�ȴ�״̬
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
*  ��������:GetChannelWaveLens										    *
*  ����:��ȡ����Դ�ź�ͨ������,���ã�                                   *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  ����: ��                                                             *
*  �����                                                               *
		*pdblWL ͨ������                                                *
		*pdwChannelCount  �ź�ͨ��                                      * 
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*			  0xXXXXXXXX: ��������									    *
*  ����ֵ����:DWORD														*
*  ��������:2013-10-15													*
*  ������:�¿���														*
*  �޸���ʷ:��															*
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
			//�������� ASCII
			ZeroMemory(tszDataStream, RXMINLENS);
			sprintf(tszDataStream,"FORM:DATA ASC\r\n");
			dwErrorCode = m_Commun.WriteDevice(tszDataStream,strlen(tszDataStream));
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode; 
			}
			
			//�ȴ�״̬
			dwErrorCode = CompleteRequest();
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode;
			}		

			//��ȡ�׸�ͨ��
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
			
			//�ȴ�״̬
			dwErrorCode = CompleteRequest();
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode;
			}		

			//��OSA����ź�ͨ����
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
*  ��������:GetChannelNF										        *
*  ����:��ȡ����Դ�ź�ͨ������(NF),���ã�                               *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  ����: ��                                                             *
*  �����                                                               *
		*pdblNF ����NF                                                  *
		*pdwChannelCount  �ź�ͨ��                                      * 
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*			  0xXXXXXXXX: ��������									    *
*  ����ֵ����:DWORD														*
*  ��������:2013-10-15													*
*  ������:�¿���														*
*  �޸���ʷ:��															*
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
			//�������� ASCII
			ZeroMemory(tszDataStream, RXMINLENS);
			sprintf(tszDataStream,"FORM:DATA ASC\r\n");
			dwErrorCode = m_Commun.WriteDevice(tszDataStream,strlen(tszDataStream));
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode; 
			}
			
				//�ȴ�״̬
			dwErrorCode = CompleteRequest();
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode;
			}
			
			//��ȡ�׸�ͨ��
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
			
			//�ȴ�״̬
			dwErrorCode = CompleteRequest();
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode;
			}
			
			//��OSA����ź�ͨ����
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
*  ��������:GetChannelGain										        *
*  ����:��ȡ����Դ�ź�ͨ������,���ã�                                   *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  ����: ��                                                             *
*  �����                                                               *
		*pdblGain ͨ������                                              *
		*pdwChannelCount  �ź�ͨ��                                      * 
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*			  0xXXXXXXXX: ��������									    *
*  ����ֵ����:DWORD														*
*  ��������:2013-10-15													*
*  ������:�¿���														*
*  �޸���ʷ:��															*
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
			//��ȡ�׸�ͨ��
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
			
			//�ȴ�״̬
			dwErrorCode = CompleteRequest();
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode;
			}
			
			//��OSA����ź�ͨ����
			dwErrorCode = GetChannelCount(pdwChannelCount);
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode;
			}
			
			pszNewData		= strtok(tszDataStream, pszToken);
			pdblGain[0]		= atof(pszNewData);
			for(wIndex = 1; wIndex < *pdwChannelCount; wIndex ++)
			{
				//���OSA Gain
				pszNewData				= strtok(NULL, pszToken);
				ZeroMemory(tszData, RXMINLENS * sizeof(TCHAR));
				pdblGain[wIndex]		= atof(strncat(tszData, pszNewData, 16));
			}
		}
		else
		{
			//Caution: All the get channel command must be after the get data command
			//��OSA����ź�ͨ����
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
*  ��������:GetChannelSourcePower									    *
*  ����:��ȡ����Դ�ź�ͨ������,���ã�                                   *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  ����: ��                                                             *
*  �����                                                               *
		*pdblSourcePow Դ����                                           *
		*pdwChannelCount  �ź�ͨ��                                      * 
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*			  0xXXXXXXXX: ��������									    *
*  ����ֵ����:DWORD														*
*  ��������:2013-10-15													*
*  ������:�¿���														*
*  �޸���ʷ:��															*
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
			//�������� ASCII
			ZeroMemory(tszDataStream, RXMINLENS);
			sprintf(tszDataStream,"FORM:DATA ASC\r\n");
			dwErrorCode = m_Commun.WriteDevice(tszDataStream,strlen(tszDataStream));
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode; 
			}
			
			//�ȴ�״̬
			dwErrorCode = CompleteRequest();
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode;
			}
			
			//��ȡ�׸�ͨ��
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

				//�ȴ�״̬
			dwErrorCode = CompleteRequest();
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode;
			}
			
			//��OSA����ź�ͨ����
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
*  ��������:SetAmpOffset									            *
*  ����:����Դ�����OFFSET,���ã�                                       *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  ���룺                                                               *
		pdblSourcePow ԴOFFSET                                          *
		dblAmpOffsett  ���OFFSET                                       * 
*  �����                                                               *
		��                                                              *
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*			  0xXXXXXXXX: ��������									    *
*  ����ֵ����:DWORD														*
*  ��������:2013-10-15													*
*  ������:�¿���														*
*  �޸���ʷ:��															*
*************************************************************************/

DWORD AgilentOSA::SetAmpOffset(double dblSourceOffset, double dblAmpOffsett)
{
	CHAR  szCmdString[1024];
	DWORD  dwErrorCode = SUCCESS;

	try
	{
		if (!m_bNFLib)
		{
			//����ԴOFFSET
			ZeroMemory(szCmdString, 1024);
			sprintf(szCmdString, "CALC:OFFS:SOUR%7.2f\r\n", dblSourceOffset);
			
			dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode; 
			}
			
			//�������OFFSET
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
*  ��������:SetAmpOffset									            *
*  ����:��ȡԴ�����OFFSET,���ã�                                       *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  ���룺                                                               *
		��                                                              *
*  �����                                                               *
		dblSourceOffset ԴOFFSET                                        *
		dblAmpOffset  ���OFFSET                                        * 
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*			  0xXXXXXXXX: ��������									    *
*  ����ֵ����:DWORD														*
*  ��������:2013-10-15													*
*  ������:�¿���														*
*  �޸���ʷ:��															*
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
			//��ȡԴOFFSET
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
			
			//�ȴ�״̬
			dwErrorCode = CompleteRequest();
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode;
			}
			
			dblSourceOffset = atof(tszDataStream);
			dblSourceOffset = dblSourceOffset;
			
			//��ȡ���OFFSET
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
			
			//�ȴ�״̬
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
*  ��������:GetEDFAChResult									            *
*  ����:EDFAģʽ�£���ȡɨ������,���ã�                                 *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  ���룺                                                               *
		��                                                              *
*  �����                                                               *
		pwChCount        �ź�ͨ����                                     *
		pdblChWL         �ź�ͨ������                                   * 
		pdblSrcpwr       �ź�ͨ��Դ����                                 *
		pdblChGain       �ź�ͨ������                                   * 
		pdblChNF         �ź�ͨ������                                   *
		pdblChAse        �ź�ͨ��ASE                                    * 
		pdblGainFlatness �ź�ƽ̹��                                     *
		pdblMaxNF        �ź��������                                   * 
		pdblMaxGain      �ź��������                                   *
		pdblMinGain      �ź���С����                                   * 
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*			  0xXXXXXXXX: ��������									    *
*  ����ֵ����:DWORD														*
*  ��������:2013-10-15													*
*  ������:�¿���														*
*  �޸���ʷ:��															*
*************************************************************************/

DWORD AgilentOSA::GetEDFAChResult(DWORD *pwChCount, double *pdblChWL, double *pdblSrcpwr, double *pdblChGain, double *pdblChNF, double *pdblChAse, double *pdblGainFlatness, double *pdblMaxNF, double* pdblMaxGain, double* pdblMinGain)
{
	double	dblMaxNF = -100;		
	double dblMaxGain = -100;
	double dblMinGain = 100;
	WORD   i;
	DWORD dwErrorCode = SUCCESS;

	//��ȡ�ź�ͨ������
	dwErrorCode = GetChannelGain(pdblChGain, pwChCount);
	if(SUCCESS != dwErrorCode)
	{
		return dwErrorCode;
	}

	//��ȡ�ź�ͨ������
	dwErrorCode = GetChannelNF(pdblChNF, pwChCount);
	if(SUCCESS != dwErrorCode)
	{
		return dwErrorCode;
	}
	
	//��ȡ�ź�ͨ��Դ����
	dwErrorCode = GetChannelSourcePower(pdblSrcpwr, pwChCount);
	if(SUCCESS != dwErrorCode)
	{
		return dwErrorCode;
	}
	
	//��ȡ�ź�ͨ������
	dwErrorCode = GetChannelWaveLens(pdblChWL, pwChCount);
	if(SUCCESS != dwErrorCode)
	{
		return dwErrorCode;
	}

	//���������С����
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
	
	//����ƽ̹��
	*pdblGainFlatness = dblMaxGain-dblMinGain;

	//�����������
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
*  ��������:GetEDFAResult									            *
*  ����:��ȡԴ��������ʡ�����,���ã�                                   *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  ���룺                                                               *
		��                                                              *
*  �����                                                               *
		pdblSumSrcSigPwr Դ����                                         *
		pdblSumAmpSigPwr  �������                                      * 
		pdblSunGain ����                                                *
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*			  0xXXXXXXXX: ��������									    *
*  ����ֵ����:DWORD														*
*  ��������:2013-10-15													*
*  ������:�¿���														*
*  �޸���ʷ:��															*
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
			//���Ͷ�ȡԴ���������
			ZeroMemory(tszDataStream, RXMINLENS * sizeof(TCHAR));
			sprintf(tszDataStream,"CALC:DATA:CST?\r\n");
			dwErrorCode = m_Commun.WriteDevice(tszDataStream,strlen(tszDataStream));
			if(dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode;
			}
			
			//��ȡ����
			ZeroMemory(tszDataStream, RXMINLENS * sizeof(TCHAR));
			dwErrorCode = m_Commun.ReadDevice(tszDataStream, RXMINLENS);
			if(dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode;
			}
			
			//�ȴ�״̬
			dwErrorCode = CompleteRequest();
			if(SUCCESS != dwErrorCode)
			{
				throw ERROR_OSA|dwErrorCode;
			}	
			
			//Դ����
			pszNewData = strtok(tszDataStream, pszToken);
			pszNewData = strtok(NULL, pszToken);
			dblSrcPwr = atof(pszNewData);
			*pdblSumSrcSigPwr = dblSrcPwr;
			
			//�������
			pszNewData = strtok(NULL, pszToken);
			pszNewData = strtok(NULL, pszToken);  
			ZeroMemory(tszData, RXMINLENS * sizeof(TCHAR));
			*pdblSumAmpSigPwr = atof(strncat(tszData, pszNewData, sizeof(WORD) * 8));
			
			//��������
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
*  ��������:InitSingleSweep									            *
*  ����:��ʼ��ɨ����ʼ��������ֹ����,RBW��ɨ�����,���ã�               *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  ���룺                                                               *
		dblStartWL    ��ʼ����                                          *
		dblStopWL     ��ֹ����                                          * 
		dblRBW        ɨ��ֱ���                                        *
		dwSweepPoint  ɨ�����                                          *
*  ���룺                                                               *
		��                                                              *
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*			  0xXXXXXXXX: ��������									    *
*  ����ֵ����:DWORD														*
*  ��������:2013-10-15													*
*  ������:�¿���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD AgilentOSA::InitSingleSweep(double dblStartWL, double dblStopWL, double dblRBW, DWORD dwSweepPoint)
{
	CHAR  szCmdString[TXLENS];
	DWORD  dwErrorCode = SUCCESS;

	try
	{
		//��ʼ��ʼ����
		ZeroMemory(szCmdString, TXLENS * sizeof(CHAR));
		sprintf(szCmdString, "sens:wav:star %.3fnm\r\n", dblStartWL);
		dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

		//��ʼ��ֹ����
		ZeroMemory(szCmdString, TXLENS * sizeof(CHAR));
		sprintf(szCmdString, "sens:wav:stop %.3fnm\r\n", dblStopWL);
		dwErrorCode = m_Commun.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
	    	throw ERROR_OSA|dwErrorCode;
		}

		//��ʼRBW
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

		//��ʼɨ�����
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
		
		//�ȴ�״̬
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA|dwErrorCode;
		}
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,"INST:NSEL 0\r\n");	 //���õ�ɨ��ģʽ	
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
*  ��������:RunSweep									                *
*  ����:��ͨģʽ�£�����ɨ��,���ã�                                     *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  ���룺                                                               *
		pdblWL        ����                                              *
		pdblPower     ����                                              * 
		szSelTrace    ɨ����(A,B,C...)                                  *  
*  ���룺                                                               *
		��                                                              *
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*			  0xXXXXXXXX: ��������									    *
*  ����ֵ����:DWORD														*
*  ��������:2013-10-15													*
*  ������:�¿���														*
*  �޸���ʷ:��															*
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

	    //�ȴ�״̬
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

		
		//��ȡ��ʼ����
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
		
		//��ȡ��ֹ����
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


		//��ȡɨ�����
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

		//��ȡszSelTrace�ߵ�����
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

		//���㲨��
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
//����˵����
//    ��õ���ɨ�����
//Add by wanxin
//Time��20150520
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
		//��ȡɨ�����
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
*  ��������:GetSweepData									            *
*  ����:��ͨģʽ�£���ȡɨ������,���ã�                                 *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						*
*  ���룺                                                               *
		pdblWL        ����                                              *
		pdblPower     ����                                              * 
		szSelTrace    ɨ����(A,B,C...)                                  *  
*  ���룺                                                               *
		��                                                              *
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*			  0xXXXXXXXX: ��������									    *
*  ����ֵ����:DWORD														*
*  ��������:2013-10-15													*
*  ������:�¿���														*
*  �޸���ʷ:��															*
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
		//��ȡ��ʼ����
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
		
		//��ȡ��ֹ����
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

		//��ȡɨ�����
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
		
		//��ȡszSelTrace�ߵ�����
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

		//���㲨��
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
*  ��������:GetChannelSNR									            *
*  ����:��ȡ�ź�ͨ��SNRֵ,���ã�                                        *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						* 
*  ���룺                                                               *
		��                                                              *
*  �����                                                               *
		pdblSNR            ͨ��SNR����                                  *
		pdwChannelCount    ͨ����                                       * 
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*			  0xXXXXXXXX: ��������									    *
*  ����ֵ����:DWORD														*
*  ��������:2013-10-15													*
*  ������:�¿���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD AgilentOSA::GetChannelSNR(double* pdblSNR,DWORD* pdwChannelCount)
{
	DWORD  dwErrorCode = SUCCESS;

	return dwErrorCode;
}

/************************************************************************
*  ��������:GetDeviceInfo									            *
*  ����:��ȡ�豸��Ϣ,���ã�                                             *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						* 
*  ���룺                                                               *
		��                                                              *
*  �����                                                               *
		   stDevInfo  �豸��Ϣ�ṹ��                                    *
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*			  0xXXXXXXXX: ��������									    *
*  ����ֵ����:DWORD														*
*  ��������:2013-10-15													*
*  ������:�¿���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD AgilentOSA::GetDeviceInfo(stDevInfo *stInfo)
{
	DWORD  dwErrorCode = SUCCESS;

	return dwErrorCode;
}

/************************************************************************
*  ��������:SaveDatatoPC									            *
*  ����:�������ݵ�PC��,���ã�                                           *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						* 
*  ���룺                                                               *
		lpSavePath  ��������·��                                        *
		lpDataType  ������������                                        *
		lpFileType  �����ļ�����                                        *
		szSelTrace  ����ɨ����(A,B,C...)����                            *
*  �����                                                               *
		   ��                                                           *
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*			  0xXXXXXXXX: ��������									    *
*  ����ֵ����:DWORD														*
*  ��������:2013-10-15													*
*  ������:�¿���														*
*  �޸���ʷ:��															*
*************************************************************************/

DWORD AgilentOSA::SaveDatatoPC(LPCTSTR lpSavePath, LPCTSTR lpDataType, LPCTSTR lpFileType, char szSelTrace)
{
	DWORD  dwErrorCode = SUCCESS;

	return dwErrorCode;
}

/************************************************************************
*  ��������:SetCalibration									            *
*  ����:����УOSA����,���ã�                                            *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						* 
*  ���룺                                                               *
		dwCalibrationType  УOSA�ڡ���ģʽ��־                          *
*  �����                                                               *
		   ��                                                           *
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*			  0xXXXXXXXX: ��������									    *
*  ����ֵ����:DWORD														*
*  ��������:2013-10-15													*
*  ������:�¿���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD AgilentOSA::SetCalibration(DWORD dwCalibrationType)
{
	DWORD  dwErrorCode = SUCCESS;

	return dwErrorCode;
}

/************************************************************************
*  ��������:GetErrorMessage									            *
*  ����:ͨ���������ý�����Ϣ	,���ã�                                 *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						* 
*  ���룺                                                               *
		dwErrorCode: ������                                             *
*  �����                                                               *
		   pszErrorMsg: �����������Ϣ                                  *
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*			  0xXXXXXXXX: ��������									    *
*  ����ֵ����:BOOL														*
*  ��������:2013-10-15													*
*  ������:�¿���														*
*  �޸���ʷ:��															*
*************************************************************************/
BOOL AgilentOSA::GetErrorMessage(DWORD dwErrorCode, char *pszErrorMsg)
{
	return TRUE;
}

/************************************************************************
*  ��������:GetTotalPower									            *
*  ����:��ȡ�ܹ���,���ã�		                                        *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						* 
*  ���룺                                                               *
		��									                            *
*  �����                                                               *
		 dblPow     �ܹ���                                              *
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*			  0xXXXXXXXX: ��������									    *
*  ����ֵ����:DWORD														*
*  ��������:2014-04-11													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
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
*  ��������:SetCalibration									            *
*  ����:��ȡʵ��RBW,���ã�                                              *
					Agilent 86140A/Agilent 86140B                       *
					Agilent 86142A/Agilent 86142B						* 
*  ���룺                                                               *
		dblBwAmp  ����BW��dBֵ				                            *
*  �����                                                               *
		dblActBw  ʵ�ʵ�BW                                              *
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*			  0xXXXXXXXX: ��������									    *
*  ����ֵ����:DWORD														*
*  ��������:2014-04-11													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
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
