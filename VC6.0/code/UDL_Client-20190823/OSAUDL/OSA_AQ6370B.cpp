// OSA_AQ6370B.cpp: implementation of the COSA_AQ6370B class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\\include\\OSA.h"
#include "math.h"
#include <string>
using namespace std;


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
//#define new DEBUG_NEW

#endif

#define RXMINLENS 128
#define RXMAXLENS 1024
#define TXLENS 1024
#define MAXSWEEPDATA 

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COSA_AQ6370B::COSA_AQ6370B()
{
	m_dblStartWL = 1520.0; 
	m_dblStopWL = 1570.0;
	m_dblRBW = 0.2;
	m_dwSweepPoint = SWEEPPOINT;
	m_lCommType = 0;//0:GPIB, 1:NET
}

COSA_AQ6370B::~COSA_AQ6370B()
{

}

/************************************************************************
*  ��������:OpenDevice													*
*  ����: �������豸													*
*  ����:																*
*		1.stType:�豸���ͽṹ��											*
*       2.pszDeviceAddr:ͨѶ��Ϣ										*
*  ������������:stDevType, char* 										*
*  ���:																*
*       comHandle:����ͨѶ�ӿ�Handle									*
*  �����������:CommunicationHandle										*
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::OpenDevice(stDevType stType, char* pszDeviceAddr, unsigned long *comHandle)
{
	DWORD dwErrorCode = SUCCESS;
	TCHAR ptchCommuType[5] = "";
	long lFlagCount = 0;
	long lTypeLen = 0;
	char	chReveive[MAX_PATH] = {""};

	try
	{
		dwErrorCode = m_Comm.OpenDevice(pszDeviceAddr, *comHandle);
		if (SUCCESS != dwErrorCode)
		{
			return dwErrorCode;
		}
		m_lCommType = 0;

		for (UINT n = 0; n < strlen(pszDeviceAddr); n++)
		{
			if (pszDeviceAddr[n] == ',')
			{
				if (0 == lFlagCount)
				{
					lTypeLen = n;
				}
				lFlagCount++;
			}
		}

		memcpy(ptchCommuType, pszDeviceAddr, lTypeLen);

		//���������ͨѶ��������Ҫ��½��������
		//"LAN,0,192.168.x.x,80, , "
		//Type, board index,IP address, Port, Login name, Login Password
		if (0 == memcmp(ptchCommuType, "LAN", 3))
		{
			TCHAR		tszTok[] = ",";
			char		*pRegComment;  //single register comment 
			long lInfoLen = strlen(pszDeviceAddr);
			char pchInfo[MAX_PATH];
			char pchSend[MAX_PATH];
			CHAR *pchLoginName = 0;
			CHAR *pchLoginPWD = 0;
			ZeroMemory(pchInfo, sizeof(pchInfo));

			memcpy(pchInfo, pszDeviceAddr, lInfoLen);
			//Type
			pRegComment = strtok(pchInfo, tszTok); 
			//board index
			pRegComment = strtok(NULL, tszTok); 
			//IP Address 
			pRegComment = strtok(NULL, tszTok); 
			//Port
			pRegComment = strtok(NULL, tszTok);
			//Login Name
			pRegComment = strtok(NULL, tszTok);
			pchLoginName = pRegComment;
			//Login Password
			pRegComment = strtok(NULL, tszTok);
			pchLoginPWD = pRegComment;

		//	dwErrorCode = m_Comm.WriteDevice(" ",strlen(" "));
		//	if (SUCCESS != dwErrorCode)
		//	{
		//		return dwErrorCode|ERROR_LOGIN;
		//	}

			m_Comm.ClearDevice();
			
			for (int iSend = 1; iSend < 3; iSend++)
			{
				if (iSend==1)
				{
					ZeroMemory(pchSend, sizeof(pchSend));
					sprintf(pchSend,"open \"%s\"\r\n",pchLoginName);
				}
				else
				{
					ZeroMemory(pchSend, sizeof(pchSend));
					sprintf(pchSend,"%s\r\n",pchLoginPWD);
				}
				dwErrorCode = m_Comm.WriteDevice(pchSend,strlen(pchSend));
				if (SUCCESS != dwErrorCode)
				{
					return dwErrorCode|ERROR_LOGIN;
				}
				Sleep(500);
//				if(!fnReceive(chReveive, MAX_FIELD))
//				{
//					return FALSE;
//				}
				ZeroMemory(chReveive, sizeof(chReveive));
				dwErrorCode = m_Comm.ReadDevice(chReveive, MAX_PATH);

				if (SUCCESS > dwErrorCode)
				{
					return dwErrorCode|ERROR_LOGIN;
				}
				dwErrorCode = SUCCESS;
				//judge Return value
				if (!(0 == strncmp(chReveive, "AUTHENTICATE CRAM-MD5.\r\n", sizeof(chReveive))||
					0 == strncmp(chReveive, "ready\r\n", sizeof(chReveive))))
				{
					return FALSE;
				}
			}

			ZeroMemory(pchSend, sizeof(pchSend));
			sprintf(pchSend, "*IDN?\r\n", pchLoginPWD);
			dwErrorCode = m_Comm.WriteDevice(pchSend,strlen(pchSend));
			if (SUCCESS != dwErrorCode)
			{
				return dwErrorCode|ERROR_LOGIN;
			}
			Sleep(500);

			dwErrorCode = m_Comm.ReadDevice(chReveive, MAX_PATH);
			if (SUCCESS != dwErrorCode)
			{
				return dwErrorCode|ERROR_LOGIN;
			}




	/*		if (0 != strncmp(chReveive, "AUTHENTICATE CRAM-MD5.\r\n", sizeof(chReveive)))
			{
				return dwErrorCode|ERROR_LOGIN;
			}
			
			ZeroMemory(pchSend, sizeof(pchSend));
			sprintf(pchSend, "%s\r\n", pchLoginPWD);
			dwErrorCode = m_Comm.WriteDevice(pchSend,strlen(pchSend));
			if (SUCCESS != dwErrorCode)
			{
				return dwErrorCode|ERROR_LOGIN;
			}
			Sleep(500);

			dwErrorCode = m_Comm.ReadDevice(chReveive, MAX_PATH);
			if (SUCCESS != dwErrorCode)
			{
				return dwErrorCode|ERROR_LOGIN;
			}

			if (0 != strncmp(chReveive, "ready\r\n", 7))
			{
				return dwErrorCode|ERROR_LOGIN;
			}*/

			m_lCommType = 1;
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR|ERROR_ANALYSIS;
	}

	return dwErrorCode;
}

/************************************************************************
*  ��������:CompleteRequest												*
*  ����: ��ѯ�豸�����Ƿ�ִ�����										*
*  ����: ��																*
*  ������������: ��														*
*  ���:��																*
*  �����������:��														*
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*    0x00000000: ��������												*
*  ����ֵ����: DWORD													*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::CompleteRequest()
{
	CHAR pszStatus[8];
	long lIndex = 0;
	ZeroMemory(pszStatus,8);
	char szSendBuf[MAX_PATH];
	do
	{
		ZeroMemory(szSendBuf,MAX_PATH);
		sprintf(szSendBuf,"*OPC?\r\n");
		m_Comm.WriteDevice(szSendBuf,strlen(szSendBuf));
		Sleep(20);
		m_Comm.ReadDevice(pszStatus, 8);
		lIndex++;

		//���5���Ӻ󣬲�����δ��ɣ����س�ʱ����
		if (lIndex > 150000)
		{
			return ERROR_RUN_OVERTIME;
		}
	}
	while(!strchr(pszStatus, '1'));
	
	return SUCCESS;
}

/************************************************************************
*  ��������:SetAnalysisType												*
*  ����: ��ʼִ�й��׷���												*
*  ����:																*
*		wAnalysisType(default mode is EDFA-NF analysis,value follow:)	*
*				0 Spectrum width analysis(THRESH)						*
*				1 Spectrum width analysis(ENVELOPE)						*
*				2 Spectrum width analysis (RMS)							*
*				3 Spectrum width analysis(PEAK-RMS)						*
*				4 Notch width analysis									*
*				5 DFB-LD parameter analysis								*
*				6 FP-LD parameter analysis								*
*				7 LED parameter analysis								*
*				8 SMSR analysis											*
*				9 Power analysis										*
*				10 PMD analysis											*
*				11 WDM analysis											*
*				12 NF analysis											*
*				13 Filter peak analysis									*
*				14 Filter bottom analysis								*
*				15 WDM FIL-PK analysis									*
*				16 WDM FIL-BTM analysis									*
*  ������������: ��														*
*  ���:��																*
*  �����������:��														*
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����: DWORD													*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::SetAnalysisType(DWORD wAnalysisType)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	try
	{
		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		//set analysis type
		sprintf(szCmdString,":CALCULATE:CATEGORY %d\r\n", wAnalysisType);
		dwErrorCode = m_Comm.WriteDevice(szCmdString, strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_ANALYSIS;
		}
		
		dwErrorCode = CompleteRequest();//wait
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_ANALYSIS;
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

/************************************************************************
*  ��������:SetSweepRange												*
*  ����: ����ɨ�貨����Χ												*
*  ����:																*
*		1.dblStartWL: ��ʼ����											*
*       2.dblStopWL: ��ֹ����											*
*  ������������:double			 										*
*  ���:��																*
*  �����������:��														*
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::SetSweepRange(double dblStartWL, double dblStopWL)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	try
	{
		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		//set the start wavelength
		sprintf(szCmdString,":SENSE:WAVELENGTH:START %8.2fNM\r\n",dblStartWL);
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL;
		}
		
		//set the stop wavelength
		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		sprintf(szCmdString,":SENSE:WAVELENGTH:STOP %8.2fNM\r\n",dblStopWL);
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL;
		}
		m_dblStartWL = dblStartWL; 
		m_dblStopWL = dblStopWL;
		dwErrorCode = CompleteRequest();//wait
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL;
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

/************************************************************************
*  ��������:GetChannelCount												*
*  ����: ��ȡɨ�貨����													*
*  ����:	��															*
*  ������������: ��				 										*
*  ���:																*
*		pdwChannelCount: ������											*
*  �����������: DWORD													*
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::GetChannelCount(DWORD* pdwChannelCount)
{
	DWORD dwErrorCode = FALSE;
	CHAR szDataStream[RXMINLENS];
	LPSTR pszToken = " ,\t\n",pszNewData = NULL;
	CHAR szCmdString[TXLENS];
	try
	{
		//set result format to ASCII


        ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,":FORMAT:DATA ASCII\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL_COUNT;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL_COUNT;
		}
		//get channel count
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,":CALCULATE:DATA:NCHANNELS?\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL_COUNT;
		}
		ZeroMemory(szDataStream,RXMINLENS * sizeof(CHAR));
		dwErrorCode = m_Comm.ReadDevice(szDataStream, RXMINLENS);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL_COUNT;
		}
		pszNewData = strtok(szDataStream,pszToken);
		*pdwChannelCount = atoi(pszNewData);
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL_COUNT;
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

/************************************************************************
*  ��������:GetChannelWaveLens											*
*  ����: ��ȡ������ֵ													*
*  ����: ��																*
*  ������������: ��				 										*
*  ���:																*
*		1.pdblWavelens: ������ֵ����									*
*		2.pdwChannelCount: ������										*
*  �����������: double, DWORD											*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::GetChannelWaveLens(double* pdblWavelens, DWORD* pdwChannelCount)
{
	DWORD dwErrorCode = FALSE;
	CHAR szDataStream[RXMAXLENS];
	LPSTR pszToken = " ,\t\n",pszNewData = NULL;
	char szCmdString[TXLENS];
	try
	{
		//set result format to ASCII
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,":FORMAT:DATA ASCII\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL;
		}
		//get channel wavelength
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,":CALCULATE:DATA:CWAVELENGTHS?\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL;
		}
		ZeroMemory(szDataStream,RXMAXLENS * sizeof(CHAR));
		dwErrorCode = m_Comm.ReadDevice(szDataStream,RXMAXLENS);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL;
		}
		//get channel count
		dwErrorCode = GetChannelCount(pdwChannelCount);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL;
		}
		//figure wavelength of each channel
		pszNewData = strtok(szDataStream,pszToken);
		*pdblWavelens = atof(pszNewData) * pow(10,9);
		for(DWORD i=1;i<*pdwChannelCount;i++)
		{
			pszNewData = strtok(NULL,pszToken);
			*(pdblWavelens + i) = atof(pszNewData) * pow(10,9);
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	
	return dwErrorCode;
}

/************************************************************************
*  ��������:GetChannelNF												*
*  ����: ��ȡ������ֵ													*
*  ����: ��																*
*  ������������: ��				 										*
*  ���:																*
*		1.pdblNF: ����NFֵ����											*
*		2.pdwChannelCount: ������										*
*  �����������: double, DWORD											*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::GetChannelNF(double* pdblNF, DWORD* pdwChannelCount)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szDataStream[RXMAXLENS];
	LPSTR pszToken = " ,\t\n",pszNewData = NULL;
	char szCmdString[TXLENS];
	try
	{
		//set result format to ASCII
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,":FORMAT:DATA ASCII\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_NF;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_NF;
		}
		//get channel NF
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,":CALCULATE:DATA:CNF?\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_NF;
		}
		ZeroMemory(szDataStream,RXMAXLENS * sizeof(CHAR));
		dwErrorCode = m_Comm.ReadDevice(szDataStream,RXMAXLENS);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_NF;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_NF;
		}
		//get channel count
		dwErrorCode = GetChannelCount(pdwChannelCount);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_NF;
		}
		//figure NF of each channel
		pszNewData = strtok(szDataStream,pszToken);
		*pdblNF = atof(pszNewData);
		for(DWORD i=1;i<*pdwChannelCount;i++)
		{
			pszNewData = strtok(NULL,pszToken);
			*(pdblNF + i) = atof(pszNewData);
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

/************************************************************************
*  ��������:GetChannelGain												*
*  ����: ��ȡ������ֵ													*
*  ����: ��																*
*  ������������: ��				 										*
*  ���:																*
*		1.pdblGain: ����GAINֵ����										*
*		2.pdwChannelCount: ������										*
*  �����������: double, DWORD											*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::GetChannelGain(double* pdblGain, DWORD* pdwChannelCount)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szDataStream[RXMAXLENS];
	LPSTR pszToken = " ,\t\n",pszNewData = NULL;
	char szCmdString[TXLENS];
	try
	{
		//set result format to ASCII
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,":FORMAT:DATA ASCII\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_GAIN;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_GAIN;
		}
		//get channel gain
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,":CALCULATE:DATA:CGAIN?\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_GAIN;
		}
		ZeroMemory(szDataStream,RXMAXLENS * sizeof(CHAR));
		dwErrorCode = m_Comm.ReadDevice(szDataStream,RXMAXLENS);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_GAIN;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_GAIN;
		}
		//get channel count
		dwErrorCode = GetChannelCount(pdwChannelCount);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_GAIN;
		}
		//figure gain of each channel
		pszNewData = strtok(szDataStream,pszToken);
		*pdblGain = atof(pszNewData);
		for(DWORD i=1;i<*pdwChannelCount;i++)
		{
			pszNewData = strtok(NULL,pszToken);
			*(pdblGain + i) = atof(pszNewData);
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	
	return dwErrorCode;
}

/************************************************************************
*  ��������:GetChannelSNR												*
*  ����: ��ȡ������ֵ													*
*  ����: ��																*
*  ������������: ��				 										*
*  ���:																*
*		1.pdblSNR: ����SNRֵ����										*
*		2.pdwChannelCount: ������										*
*  �����������: double, DWORD											*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::GetChannelSNR(double* pdblSNR, DWORD* pdwChannelCount)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szDataStream[RXMAXLENS];
	LPSTR pszToken = " ,\t\n",pszNewData = NULL;
	char szCmdString[TXLENS];
	
	try
	{
		//set result format to ASCII
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,":FORMAT:DATA ASCII\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SNR;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SNR;
		}
		//get channel SNR
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,":CALCULATE:DATA:CSNR?\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SNR;
		}
		ZeroMemory(szDataStream,RXMAXLENS * sizeof(CHAR));
		dwErrorCode = m_Comm.ReadDevice(szDataStream,RXMAXLENS);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SNR;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SNR;
		}
		//get channel count
		dwErrorCode = GetChannelCount(pdwChannelCount);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SNR;
		}
		//figure gain of each channel
		pszNewData = strtok(szDataStream,pszToken);
		*pdblSNR = atof(pszNewData);
		for(DWORD i=1;i<*pdwChannelCount;i++)
		{
			pszNewData = strtok(NULL,pszToken);
			*(pdblSNR + i) = atof(pszNewData);
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

/************************************************************************
*  ��������:GetChannelSourcePower										*
*  ����: ��ȡ��������													*
*  ����: ��																*
*  ������������: ��				 										*
*  ���:																*
*		1.pdblSourcePow: ��������ֵ����									*
*		2.pdwChannelCount: ������										*
*  �����������: double, DWORD											*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::GetChannelSourcePower(double* pdblSourcePow, DWORD* pdwChannelCount)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szDataStream[RXMAXLENS];
	LPSTR pszToken = " ,\t\n",pszNewData = NULL;
	char szCmdString[TXLENS];
	try
	{
		//set result format to ASCII
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,":FORMAT:DATA ASCII\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW;
		}
		//get channel SNR
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,":CALCULATE:DATA:CPOWERS?\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW;
		}
		ZeroMemory(szDataStream,RXMAXLENS * sizeof(CHAR));
		dwErrorCode = m_Comm.ReadDevice(szDataStream,RXMAXLENS);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW;
		}
		//get channel count
		dwErrorCode = GetChannelCount(pdwChannelCount);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW;
		}

		//figure gain of each channel
		pszNewData = strtok(szDataStream,pszToken);
		*pdblSourcePow = atof(pszNewData);
		for(DWORD i=1;i<*pdwChannelCount;i++)
		{
			pszNewData = strtok(NULL,pszToken);
			*(pdblSourcePow + i) = atof(pszNewData);
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

/************************************************************************
*  ��������:SetPowerOffset												*
*  ����: ���ù���ƫ����													*
*  ����:																*
*		dblOSAPowOffset: ����ƫ����ֵ									*
*  ������������: double				 									*
*  ���:��																*
*  �����������: ��														*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::SetPowerOffset(double dblOSAPowOffset)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
	try
	{
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,":SENSE:CORRECTION:LEVEL:SHIFT %7.2fDB\r\n",dblOSAPowOffset);
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW_OFFSET;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW_OFFSET;
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

/************************************************************************
*  ��������:SetWavelengthOffset											*
*  ����: ���ò���ƫ����													*
*  ����:																*
*		dblWLOffset: ����ƫ����ֵ										*
*  ������������: double				 									*
*  ���:��																*
*  �����������: ��														*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::SetWavelengthOffset(double dblWLOffset)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
	try
	{
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,":SENSE:CORRECTION:WAVELENGTH:SHIFT %7.2fNM\r\n",dblWLOffset);
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL_OFFSET;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL_OFFSET;
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	
	return dwErrorCode;
}

/************************************************************************
*  ��������:GetPowerOffset												*
*  ����: ��ù���ƫ����													*
*  ����:��																*
*  ������������: ��														*
*  ���:																*
*		dblOSAPowOffset: ����ƫ����ֵ									*
*  �����������: double	*			 									*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::GetPowerOffset(double* pdblOSAPowOffset)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szDataStream[RXMINLENS];
	CHAR szCmdString[TXLENS];
	try
	{
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,":SENSE:CORRECTION:LEVEL:SHIFT?\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW_OFFSET;
		}
		ZeroMemory(szDataStream,RXMINLENS * sizeof(CHAR));
		dwErrorCode = m_Comm.ReadDevice(szDataStream, RXMINLENS);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW_OFFSET;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW_OFFSET;
		}
		*pdblOSAPowOffset = atof(szDataStream);
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

/************************************************************************
*  ��������:GetWavelengthOffset											*
*  ����: ��ȡ����ƫ����													*
*  ����:��																*
*  ������������: ��														*
*  ���:																*
*		dblWLOffset: ����ƫ����ֵ										*
*  �����������: double *			 									*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::GetWavelengthOffset(double* pdblWLOffset)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szDataStream[RXMINLENS];
	CHAR szCmdString[TXLENS];
	try
	{
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,":SENSE:CORRECTION:WAVELENGTH:SHIFT?\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL_OFFSET;
		}
		ZeroMemory(szDataStream,RXMINLENS * sizeof(CHAR));
		dwErrorCode = m_Comm.ReadDevice(szDataStream,RXMINLENS);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL_OFFSET;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL_OFFSET;
		}
		*pdblWLOffset = atof(szDataStream) * pow(10,9);//NM
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

/************************************************************************
*  ��������:InitSingleSweep												*
*  ����: ��ʼ��ɨ��														*
*  ����:																*
*		1.dblStartWL: ��ʼ����											*
*		2.dblStopWL: ��ֹ����											*
*		3.dblRBW: ���Ƶ�����											*
*		4.dwSweepPoint: ɨ�����										*
*  ������������: double, double, double, DWORD							*
*  ���: ��																*
*  �����������: ��					 									*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::InitSingleSweep(double dblStartWL, double dblStopWL, double dblRBW, DWORD dwSweepPoint)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
	try
	{
		//set the start wavelength
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,":SENSE:WAVELENGTH:START %8.2fNM\r\n",dblStartWL);
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL;
		}
		//set the stop wavelength
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,":SENSE:WAVELENGTH:STOP %8.2fNM\r\n",dblStopWL);
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL;
		}
		m_dblStartWL = dblStartWL; 
		m_dblStopWL = dblStopWL;
		//set RBW resoln correct off
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,":SENSE:SETting:CORRect OFF\r\n",dblRBW);
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_RBW;
		}
		//set RBW
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,":SENSE:BANDWIDTH:RESOLUTION %8.3fNM\r\n",dblRBW);
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_RBW;
		}
		m_dblRBW = dblRBW;
		//set sense��normal
		/*Sens(value follow:),now ignore,default is normal
			NHLD/NAUT/MID/HIGH1/HIGH2/HIGH3/NORMAL*/
//		ZeroMemory(szCmdString,TXLENS);
//		sprintf(szCmdString,":SENSE:SENSE MID\r\n");
//		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
//		if(SUCCESS != dwErrorCode)
//		{
//			throw dwErrorCode|ERROR_SENS;
//		}


		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,"SENSE:CHOPPER OFF\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SENS;
		}
		
		//set sweep point
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,":SENSE:SWEEP:POINTS %d\r\n",dwSweepPoint);
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWEEP_POINT;
		}
		m_dwSweepPoint = dwSweepPoint;
		//set sweep mode,single
		/*Mode(value follow:), now ignore,default is single					
		single/repeat/auto/segment*/
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,":INITIATE:SMODE SINGLE\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWEEP_MODE;
		}
	
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	
	return dwErrorCode;
}

/************************************************************************
*  ��������:GetEDFATestResult											*
*  ����: ��ʼ��ɨ��														*
*  ����:																*
*		1.uiLength: �ַ�����											*
*  ������������: USHORT													*
*  ���:																*
*		1.pszResult:������ַ�����										*
*  �����������: char				 									*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::GetEDFATestResult(char* pszResult, USHORT uiLength)
{
	DWORD dwErrorCode = SUCCESS;
	LPSTR pszToken = " ,\t\n",pszNewData = NULL;
	char szCmdString[TXLENS];
	try
	{
		//set result format to ASCII
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,":FORMAT:DATA ASCII\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWEEP_DATA;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWEEP_DATA;
		}
		//get EDFA result
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,":CALCULATE:DATA?\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWEEP_DATA;
		}
		dwErrorCode = m_Comm.ReadDevice(pszResult,uiLength);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWEEP_DATA;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWEEP_DATA;
		}

/*		//channel number
		pszNewData = strtok(szDataStream,pszToken);
		//center wavelength
		pszNewData = strtok(NULL,pszToken);
		//input level
		pszNewData = strtok(NULL,pszToken);
		*pdblInputPow = atof(pszNewData);
		//output level
		pszNewData = strtok(NULL,pszToken);
		*pdblOutputPow = atof(pszNewData);
		//ASE level
		pszNewData = strtok(NULL,pszToken);
		//Measurement resolution
		pszNewData = strtok(NULL,pszToken);
		//gain
		pszNewData = strtok(NULL,pszToken);
		*pdblGain = atof(pszNewData);
		//NF
		pszNewData = strtok(NULL,pszToken);
		*pdblNF = atof(pszNewData);
		*/
		
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	
	return dwErrorCode;
}

/************************************************************************
*  ��������:ResetDevice													*
*  ����: ��������														*
*  ����:																*
*		��																*
*  ������������: ��														*
*  ���:																*
*		��																*
*  �����������: ��					 									*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::ResetDevice()
{
	DWORD dwErrorCode = SUCCESS;
	char szCmdString[TXLENS];
	try
	{
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,"*RST\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_RESET;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWEEP_DATA;
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
	
/************************************************************************
*  ��������:SetAmpSrcSigOffset											*
*  ����: ����Դ�ź�ƫ��ֵ												*
*  ����:																*
*		1.dblSrcSigOffset: Դ�ź�ƫ��ֵ									*
*  ������������: double													*
*  ���:																*
*		��																*
*  �����������: ��					 									*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::SetAmpSrcSigOffset(double dblSrcSigOffset)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
	try
	{
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,":CALCULATE:PARAMETER:NF:IOFFSET %.2fDB\r\n",dblSrcSigOffset);
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW_OFFSET;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW_OFFSET;
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}

/************************************************************************
*  ��������:GetAmpOffset												*
*  ����: ��÷Ŵ�ģʽ��ƫ��ֵ											*
*  ����:																*
*		��																*
*  ������������: ��														*
*  ���:																*
*		1.dblSourceOffset: Դ�ź�ƫ��ֵ									*
*		2.dblAmpOffset:	�Ŵ��ź�ƫ��ֵ									*
*  �����������:  double, double	 									*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::GetAmpOffset(double &dblSourceOffset, double &dblAmpOffset)
{
	DWORD dwErrorCode = 0;
	double dblOff = 0;

	dwErrorCode = GetAmpSrcSigOffset(&dblOff);
	if (SUCCESS != dwErrorCode)
	{
		return dwErrorCode;
	}
	dblSourceOffset = dblOff;

	dwErrorCode = GetAmpOutSigOffset(&dblOff);
	if (SUCCESS != dwErrorCode)
	{
		return dwErrorCode;
	}
	dblAmpOffset = dblOff;

	return dwErrorCode;
}

/************************************************************************
*  ��������:SetAmpOutSigOffset											*
*  ����: ���÷Ŵ��ź�ƫ��ֵ												*
*  ����:																*
*		1.dblOutSigOffset: �Ŵ��ź�ƫ��ֵ								*
*  ������������: double													*
*  ���:																*
*		��																*
*  �����������: ��					 									*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::SetAmpOutSigOffset(double dblOutSigOffset)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	ZeroMemory(szCmdString, TXLENS * sizeof(CHAR));
	try
	{
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString, ":CALCULATE:PARAMETER:NF:OOFFSET %7.2fDB\r\n", dblOutSigOffset);
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW_OFFSET;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW_OFFSET;
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

/************************************************************************
*  ��������:SetAmpOutSigOffset											*
*  ����: ���÷Ŵ��ź�ƫ��ֵ												*
*  ����:																*
*		1.dblSrcSigOffset: Դ�ź�ƫ��ֵ									*
*		2.dblOutSigOffset: �Ŵ��ź�ƫ��ֵ								*
*  ������������: double, double											*
*  ���:																*
*		��																*
*  �����������: ��					 									*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::SetAmpOffset(double dblSourceOffset, double dblAmpOffset)
{
	DWORD dwErrorCode = SUCCESS;
	
	dwErrorCode = SetAmpSrcSigOffset(dblSourceOffset);
	if(SUCCESS != dwErrorCode)
	{
		return dwErrorCode;
	}

	dwErrorCode = SetAmpOutSigOffset(dblAmpOffset);
	if(SUCCESS != dwErrorCode)
	{
		return dwErrorCode;
	}

	return dwErrorCode;
}

/************************************************************************
*  ��������:GetAmpSrcSigOffset											*
*  ����: ��ȡԴ�ź�ƫ��ֵ												*
*  ����:																*
*		��																*
*  ������������: ��														*
*  ���:																*
*		1.pdblSrcSigOffset: Դ�ź�ƫ��ֵ								*
*  �����������: double				 									*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::GetAmpSrcSigOffset(double* pdblSrcSigOffset)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szDataStream[RXMINLENS];
	char szCmdString[TXLENS];
	
	try
	{
		//set result format to ASCII
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString, ":FORMAT:DATA ASCII\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW_OFFSET;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW_OFFSET;
		}
		//get amp offset
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString, ":CALCULATE:PARAMETER:NF:IOFFSET?\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW_OFFSET;
		}
		ZeroMemory(szDataStream, RXMINLENS);
		dwErrorCode = m_Comm.ReadDevice(szDataStream, RXMINLENS);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW_OFFSET;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW_OFFSET;
		}
		*pdblSrcSigOffset = atof(szDataStream);
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

/************************************************************************
*  ��������:GetAmpOutSigOffset											*
*  ����: ��ȡ�Ŵ��ź�ƫ��ֵ												*
*  ����:																*
*		��																*
*  ������������: ��														*
*  ���:																*
*		1.pdblOutSigOffset: �Ŵ��ź�ƫ��ֵ								*
*  �����������: double				 									*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::GetAmpOutSigOffset(double* pdblOutSigOffset)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szDataStream[RXMINLENS];
	char szCmdString[TXLENS];
	try
	{
		//set result format to ASCII
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString, ":FORMAT:DATA ASCII\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW_OFFSET;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW_OFFSET;
		}
		//get amp offset
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString, ":CALCULATE:PARAMETER:NF:OOFFSET?\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW_OFFSET;
		}
		ZeroMemory(szDataStream, RXMINLENS);
		dwErrorCode = m_Comm.ReadDevice(szDataStream,RXMINLENS);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW_OFFSET;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW_OFFSET;
		}
		*pdblOutSigOffset = atof(szDataStream);
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

/************************************************************************
*  ��������:SetOSALocalCtrl												*
*  ����: ���ñ��ؿ�������												*
*  ����:																*
*		��																*
*  ������������: ��														*
*  ���:																*
*		��																*
*  �����������: ��					 									*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::SetOSALocalCtrl()
{
	DWORD dwErrorCode = SUCCESS;
	char szCmdString[TXLENS];
	try
	{
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString, "GTL\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_LOCAL_CONTROL;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_LOCAL_CONTROL;
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}

/************************************************************************
*  ��������:RunSweep													*
*  ����: ����ɨ��														*
*  ����:																*
*		1.szSelTrace: ɨ��������										*
*  ������������: char													*
*  ���:																*
*		1.pdblSweepDataX: ɨ��x����ֵ									*
*		2.pdblSweepDataY: ɨ��y����ֵ									*
*  �����������: double, double		 									*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::RunSweep(double* pdblSweepDataX, double* pdblSweepDataY, char szSelTrace)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR *pszDataStream = NULL;
	CHAR szDataStream[RXMINLENS];
	CHAR szCmdString[TXLENS];
	ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
	DWORD dwSweepPointNum, dwMallocSpace;
	LPSTR pszToken = " ,\t\n",pszNewData = NULL;
	try
	{
		//set result format to ASCII
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString, ":FORMAT:DATA ASCII\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWEEP;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWEEP;
		}
		//Set Trace B Active
		dwErrorCode = SetTraceAct(szSelTrace);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode;
		}

		//Set Trace A Attribute
		dwErrorCode = SetTraceAttribute(szSelTrace, 0);//write
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode;
		}

		//Initiate Single Sweep
// 		dwErrorCode = InitSingleSweep(m_dblStartWL, m_dblStopWL, m_dblRBW, m_dwSweepPoint);
// 		if(SUCCESS != dwErrorCode)
// 		{
// 			throw dwErrorCode;
// 		}
				//start
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,":INITIATE\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_INITIAL;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_INITIAL;
		}

		dwErrorCode = RunCalculate();//start analysis
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode;
		}
		
		//get data number
		for (int nIndex=0; nIndex<3;nIndex++)
		{
			ZeroMemory(szCmdString,TXLENS);
			sprintf(szCmdString,":TRACE:DATA:SNUMBER? TR%c\r\n",szSelTrace);
			dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
			if(SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_SWEEP;
			}
			ZeroMemory(szDataStream,RXMINLENS * sizeof(CHAR));
			dwErrorCode = m_Comm.ReadDevice((unsigned char*)szDataStream,RXMINLENS);
		}
	    if(SUCCESS > dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWEEP;
		}
		dwErrorCode = 0;
		dwSweepPointNum = atol(szDataStream);
		if (dwSweepPointNum <=1)
		{
			throw dwErrorCode|ERROR_SWEEP;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWEEP;
		}
		//get sweep data of x axis
		dwMallocSpace = sizeof(CHAR) * dwSweepPointNum * 20;
		pszDataStream = (CHAR*)VirtualAlloc(NULL,dwMallocSpace, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWEEP;
		}
		ZeroMemory(pszDataStream,dwMallocSpace);

		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		sprintf(szCmdString,":TRACE:X? TR%c\r\n",szSelTrace);
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWEEP;
		}
		dwErrorCode = m_Comm.ReadDevice(pszDataStream,dwMallocSpace);
	    if(SUCCESS > dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWEEP;
		}
		dwErrorCode = 0;
		//figure the data
		pszNewData = strtok(pszDataStream,pszToken);
		pdblSweepDataX[0] = atof(pszNewData)* 10E8;
		for(DWORD i=1;i<dwSweepPointNum;i++)
		{
			pszNewData = strtok(NULL,pszToken);
			if(pszNewData == NULL)
			{
				break;
			}
			pdblSweepDataX[i] = atof(pszNewData) * 10E8;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWEEP;
		}
		//get sweep data of y axis
		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		sprintf(szCmdString,":TRACE:Y? TR%c\r\n",szSelTrace);
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWEEP;
		}
		dwErrorCode = m_Comm.ReadDevice(pszDataStream,dwMallocSpace);
	    if(SUCCESS > dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWEEP;
		}
		dwErrorCode = 0;
		//figure the data
		pszNewData = strtok(pszDataStream,pszToken);
		pdblSweepDataY[0] = atof(pszNewData);
		for(i=1;i<dwSweepPointNum;i++)
		{
			pszNewData = strtok(NULL,pszToken);
			if(pszNewData == NULL)
			{
				break;
			}
			pdblSweepDataY[i] = atof(pszNewData);
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWEEP;
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	VirtualFree(pszDataStream, 0, MEM_RELEASE);

	return dwErrorCode;
	
}
/////////////////////////////////////////////////////////////
//����˵����
//    ��OSA�л�õ���ɨ��ĵ���
//Add by wanxin
//Time��20150520
/////////////////////////////////////////////////////////////
DWORD COSA_AQ6370B::GetSingleSweepPoint(DWORD * pCount)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szDataStream[RXMINLENS];
	CHAR szCmdString[TXLENS];
	ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
	DWORD dwSweepPointNum=0;
	try
	{
		//get data number
		for (int nIndex=0; nIndex<3;nIndex++)
		{
			ZeroMemory(szCmdString,TXLENS);
			sprintf(szCmdString,":TRACE:DATA:SNUMBER?\r\n");
			dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
			if(SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_SWEEP;
			}
			ZeroMemory(szDataStream,RXMINLENS * sizeof(CHAR));
			dwErrorCode = m_Comm.ReadDevice((unsigned char*)szDataStream,RXMINLENS);
		}
	    if(SUCCESS > dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWEEP;
		}
		dwErrorCode = 0;
		dwSweepPointNum = atol(szDataStream);
		* pCount = dwSweepPointNum;
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}


/************************************************************************
*  ��������:RunSweep													*
*  ����: ����ɨ��														*
*  ����:																*
*		1.szSelTrace: ɨ��������										*
*  ������������: char													*
*  ���:																*
*		1.pdblSweepDataX: ɨ��x����ֵ									*
*		2.pdblSweepDataY: ɨ��y����ֵ									*
*  �����������: double, double		 									*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::SetWLOffsetTable(USHORT usWavelength, double dblWLOffset)
{
	DWORD dwErrorCode = FALSE;
	CHAR szCmdString[TXLENS];
	
	try
	{
		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		sprintf(szCmdString,":CALIBRATION:WAVELENGTH:OFFSET:TABLE %d,%7.2fNM\r\n",usWavelength,dblWLOffset);
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL_OFFSET;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL_OFFSET;
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

/************************************************************************
*  ��������:GetWLOffsetTable											*
*  ����: ��ȡ����ƫ��ֵ													*
*  ����:																*
*		1.usWavelength: ��������λ��nm��								*
*  ������������: USHORT													*
*  ���:																*
*		1.pdblWLOffset: ����ƫ��ֵ����λ��nm��							*
*  �����������: double				 									*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::GetWLOffsetTable(USHORT usWavelength, double* pdblWLOffset)
{
	DWORD dwErrorCode = FALSE;
	CHAR szCmdString[TXLENS];
	CHAR szDataStream[RXMINLENS];
	
	try
	{
		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		sprintf(szCmdString,":CALIBRATION:WAVELENGTH:OFFSET:TABLE? %d\r\n",usWavelength);
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_CH_WL_OFFSET;
		}
		ZeroMemory(szDataStream,RXMINLENS);
		dwErrorCode = m_Comm.ReadDevice(szCmdString,RXMINLENS);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_CH_WL_OFFSET;
		}
		*pdblWLOffset = atof(szCmdString);
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_CH_WL_OFFSET;
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

/************************************************************************
*  ��������:SetPowOffsetTable											*
*  ����: ���ù���ƫ��ֵ													*
*  ����:																*
*		1.usWavelength: ��������λ��nm��								*
*		2.dblPowOffset: ����ƫ��ֵ����λ��dB��							*
*  ������������: USHORT, double											*
*  ���:																*
*		��																*
*  �����������: ��					 									*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::SetPowOffsetTable(USHORT usWavelength, double dblPowOffset)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	
	try
	{
		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		sprintf(szCmdString,":CALIBRATION:POWER:OFFSET:TABLE %d,%7.2fDB\r\n",usWavelength,dblPowOffset);
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_CH_WL_OFFSET;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_CH_WL_OFFSET;
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

/************************************************************************
*  ��������:SetPowOffsetTable											*
*  ����: ��ȡ����ƫ��ֵ													*
*  ����:																*
*		1.usWavelength: ��������λ��nm��								*
*  ������������: USHORT													*
*  ���:																*
*		1.dblPowOffset: ����ƫ��ֵ����λ��dB��							*
*  �����������: double				 									*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::GetPowOffsetTable(USHORT usWavelength,double* pdblPowOffset)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	CHAR szDataStream[RXMINLENS];
	
	try
	{
		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		sprintf(szCmdString,":CALIBRATION:POWER:OFFSET:TABLE? %d\r\n",usWavelength);
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_CH_PW_OFFSET;
		}
		ZeroMemory(szDataStream,RXMINLENS);
		dwErrorCode = m_Comm.ReadDevice(szCmdString,RXMINLENS);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_CH_PW_OFFSET;
		}
		*pdblPowOffset = atof(szCmdString);
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_CH_PW_OFFSET;
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

/************************************************************************
*  ��������:InitAmpTest													*
*  ����: ��ʼ���Ŵ�ģʽ����												*
*  ����:																*
*		1.dblStartWL: ɨ����ʼ��������λ��nm��							*
*		2.dblStopWL: ɨ����ֹ��������λ��nm��							*
*		3.dblRBW: Resolution Bandwidth����λ��nm��						*
*  ������������: double, double, double									*
*  ���:																*
*		��																*
*  �����������: ��					 									*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::InitAmpTest(double dblStartWL, double dblStopWL, double dblRBW)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	CHAR szDataStream[RXMINLENS];
	int iStateIndex = 0;
	ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
	try
	{
		//Clear Device
//		dwErrorCode = m_Comm.ClearDevice();
//		if(SUCCESS != dwErrorCode)
//		{
//			throw dwErrorCode|ERROR_CLEAR;
//		}
		//get current work state of OSA
		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		sprintf(szCmdString,":CALCULATE:CATEGORY?\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WROK_MODE;
		}
		dwErrorCode = m_Comm.ReadDevice(szDataStream, RXMINLENS);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WROK_MODE;
		}
		iStateIndex = atoi(szDataStream);
		//set OSA to EDFA_NF analysis mode
		if(12 != iStateIndex)//EDFA mode index is 12
		{
			//reset OSA
			dwErrorCode = ResetDevice();
			if(SUCCESS != dwErrorCode)
			{
				throw dwErrorCode;
			}
			//set EDFA analysis
			dwErrorCode = SetAnalysisType(12);
			if(SUCCESS != dwErrorCode)
			{
				throw dwErrorCode;
			}
		}
		//set start and stop wavelength
		dwErrorCode = SetSweepRange(dblStartWL, dblStopWL);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode;
		}
		//set RBW
		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		sprintf(szCmdString,":SENSE:BANDWIDTH:RESOLUTION %8.3fNM\r\n",dblRBW);
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_RBW;
		}
		m_dblRBW = dblRBW;
		//set sense��normal
		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		sprintf(szCmdString,":SENSE:SENSE MID\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SENS;
		}

		dwErrorCode = InitOSAAmpCalSet();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_INITIAL;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_INITIAL;
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

/************************************************************************
*  ��������:GetGPIBAress												*
*  ����: ��ȡGPIB��ַ													*
*  ����:																*
*		��																*
*  ������������: ��														*
*  ���:																*
*		iGpibAddress: GPIB��ַ											*
*  �����������: int				 									*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::GetGPIBAress(int *iGpibAddress)
{
	DWORD dwErrorCode = SUCCESS;
	TCHAR tszDataStream[1024];
	int  iAddress;;
	char  szCmdString[TXLENS];
	try
	{
		//Get the wavelength
		ZeroMemory(tszDataStream, 1024);
		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		sprintf(szCmdString,":SYSTEM:COMMUNICATE:GP-IB22:ADDRESS?\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_ADDRESS;
		}
		dwErrorCode =m_Comm.ReadDevice(tszDataStream, 1024);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_ADDRESS;
		}	
		
		iAddress = atoi(tszDataStream); //Meter
        *iGpibAddress=iAddress;
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_ADDRESS;
		}	
	}	
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}

/************************************************************************
*  ��������:SetRBW														*
*  ����: ����Resolution Bandwidth										*
*  ����:																*
*		1.dblRBW: Resolution Bandwidth����λ��nm��						*
*  ������������: double													*
*  ���:																*
*		��																*
*  �����������: ��					 									*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::SetRBW(double dblRBW)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	
	try
	{
		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		sprintf(szCmdString,":SENSE:BANDWIDTH:RESOLUTION %8.3fNM\r\n",dblRBW);
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_RBW;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_RBW;
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

/************************************************************************
*  ��������:SetRBW														*
*  ����: ��ȡResolution Bandwidth										*
*  ����:																*
*		��																*
*  ������������: ��														*
*  ���:																*
*		1.dblRBW: Resolution Bandwidth����λ��nm��						*
*  �����������: double				 									*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::GetRBW(double* pdblRBW)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szDataStream[RXMINLENS];
	char szCmdString[TXLENS];
	try
	{
		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		sprintf(szCmdString,":SENSE:BANDWIDTH?\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_RBW;
		}
		ZeroMemory(szDataStream,RXMINLENS * sizeof(CHAR));
		dwErrorCode = m_Comm.ReadDevice(szDataStream,RXMINLENS);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_RBW;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_RBW;
		}
		*pdblRBW = atof(szDataStream) * pow(10,9);//NM
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

/************************************************************************
*  ��������:RunCalculate												*
*  ����: ���м���														*
*  ����:																*
*		��																*
*  ������������: ��														*
*  ���:																*
*		��																*
*  �����������: ��					 									*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::RunCalculate()
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	try
	{
		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		sprintf(szCmdString,":CALCULATE\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_ANALYSIS;
		}
		
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_ANALYSIS;
		}

	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

/************************************************************************
*  ��������:SetTraceAct													*
*  ����: ���õ�ǰ��������												*
*  ����:																*
*		1.szSelTrace������												*
*  ������������: char													*
*  ���:																*
*		��																*
*  �����������: ��					 									*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::SetTraceAct(char szSelTrace)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	
	try
	{
		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		sprintf(szCmdString,":TRACE:ACTIVE TR%c\r\n",szSelTrace);
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TRACE;
		}
		
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TRACE;
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}

/************************************************************************
*  ��������:SetTraceAct													*
*  ����: ���õ�ǰ��������												*
*  ����:																*
*		1.szSelTrace������												*
*		2.uiAttribute������ֵ											*
*			0:WRITE														*
*			1:FIX														*
*			2:MAX HOLD													*
*			3:MIX HOLD													*
*			4:ROLL AVG													*
*			5:CALC														*
*  ������������: char, USHORT											*
*  ���:																*
*		��																*
*  �����������: ��					 									*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::SetTraceAttribute(char szSelTrace, USHORT uiAttribute)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	
	try
	{
		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		switch(uiAttribute)
		{
		case 0:
			sprintf(szCmdString,":TRACE:ATTRIBUTE:TR%c WRITE\r\n",szSelTrace);
			break;
		case 1:
			sprintf(szCmdString,":TRACE:ATTRIBUTE:TR%c FIX\r\n",szSelTrace);
			break;
		case 2:
			sprintf(szCmdString,":TRACE:ATTRIBUTE:TR%c MAX\r\n",szSelTrace);
			break;
		case 3:
			sprintf(szCmdString,":TRACE:ATTRIBUTE:TR%c MIN\r\n",szSelTrace);
			break;
		case 4:
			sprintf(szCmdString,":TRACE:ATTRIBUTE:TR%c RAVG\r\n",szSelTrace);
			break;
		case 5:
			sprintf(szCmdString,":TRACE:ATTRIBUTE:TR%c CALC\r\n",szSelTrace);
			break;
		}
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TRACE_ATTRIBUTE;
		}
		
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TRACE_ATTRIBUTE;
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}

/************************************************************************
*  ��������:MeasureSource												*
*  ����: ɨԴ															*
*  ����:																*
*		��																*
*  ������������: ��														*
*  ���:																*
*		��																*
*  �����������: ��					 									*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::MeasureSource()
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	try
	{
		ZeroMemory(m_dblSRCPointPower, SWEEPPOINT * sizeof(double));
		ZeroMemory(m_dblSRCPointWL, SWEEPPOINT * sizeof(double));

		//Set Trace A Active
		dwErrorCode = SetTraceAct('A');
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TRACE;
		}

		//Set Trace A Attribute
		dwErrorCode = SetTraceAttribute('A',0);//write
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TRACE_ATTRIBUTE;
		}

		//Initiate Single Sweep
		dwErrorCode = InitSingleSweep(m_dblStartWL, m_dblStopWL, m_dblRBW, SWEEPPOINT);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_INITIAL;
		}

	    ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,":INITIATE\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_INITIAL;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_INITIAL;
		}

		//Set Trace A Attribute
		dwErrorCode = SetTraceAttribute('A',1);//fix
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TRACE_ATTRIBUTE;
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

/************************************************************************
*  ��������:MeasureAmplifier											*
*  ����: ɨ�Ŵ�															*
*  ����:																*
*		1.bScanSrcOnly:	ֻ����ɨԴ��ʶ									*
*  ������������: BOOL													*
*  ���:																*
*		��																*
*  �����������: ��					 									*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::MeasureAmplifier(BOOL bScanSrcOnly)
{
	DWORD dwErrorCode = SUCCESS;
	char seps[]= ",\t\n";
	char* token;
	char *pszResult=NULL;
	double dblTemp = 0;
	CHAR szCmdString[TXLENS];
	
	try
	{
		m_dblOutputTotal=0;
		m_dblInputTotal=0;
		m_dblOutputSignal=0;
		ZeroMemory(m_dblAmpPointPower, SWEEPPOINT * sizeof(double));
		ZeroMemory(m_dblAmpPointWL, SWEEPPOINT * sizeof(double));
		ZeroMemory(m_dblCHNF, SWEEPPOINT * sizeof(double));
		ZeroMemory(m_dblCHGain, SWEEPPOINT * sizeof(double));
		ZeroMemory(m_dblResoln, SWEEPPOINT * sizeof(double));
		ZeroMemory(m_dblCenterWL, SWEEPPOINT * sizeof(double));

		//Set Trace B Active
		dwErrorCode = SetTraceAct('B');
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode;
		}

		//Set Trace A Attribute
		dwErrorCode = SetTraceAttribute('B', 0);//write
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode;
		}

		//Initiate Single Sweep
		dwErrorCode = InitSingleSweep(m_dblStartWL, m_dblStopWL, m_dblRBW, SWEEPPOINT);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode;
		}
        //Begin Sweep
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,":INITIATE\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_INITIAL;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_INITIAL;
		}

		//Get Trace B Data
	//	if(FALSE == RunSweep(m_dblAmpPointWL, m_dblAmpPointPower, 'B'))
	//	{
	//		return FALSE;
	//	}
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,":TRACE:STATE:TRB ON\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TRACE_ATTRIBUTE;
		}
		
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TRACE_ATTRIBUTE;
		}

		//Set Trace B Attribute
//		dwErrorCode = SetTraceAttribute('B',1);//fix
//		if(SUCCESS != dwErrorCode)
//		{
//			throw dwErrorCode|ERROR_TRACE_ATTRIBUTE;
//		}

		//start analysis data
		pszResult = (CHAR*)VirtualAlloc(NULL,1024*8, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
		dwErrorCode = RunCalculate();//start analysis
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode;
		}
		//Get EDFA Result
		dwErrorCode = GetEDFATestResult(pszResult, 1024*8);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode;
		}

		token = strtok(pszResult,seps);
		m_iChCount = atoi(token);
	//	Center WL, Input Level, Output Level, ASE Level, Resoln, Gain, NF;
		for(int i = 0; i < m_iChCount; i++)
		{
			token = strtok(NULL,seps);
			m_dblCenterWL[i] = atof(token)*10E8;//Center WL,nm
			token = strtok(NULL,seps);
			dblTemp = atof(token);
			m_dblSRCPointPower[i]=dblTemp;//Input Level
			m_dblInputTotal += dbTomw(dblTemp);//total input
			token = strtok(NULL,seps);
			dblTemp=atof(token);//Output Level
			m_dblAmpPointPower[i]=dblTemp;
			m_dblOutputTotal+=dbTomw(dblTemp);
			token = strtok(NULL,seps);
			m_dblASE[i] = atof(token);//ASE Level
			token = strtok(NULL,seps);
			m_dblResoln[i] = atof(token)*10E8;//Resoln,nm
			token = strtok(NULL,seps);
			m_dblCHGain[i] = dblTemp = atof(token);//Gain
			token = strtok(NULL,seps);
			m_dblCHNF[i] = dblTemp = atof(token);//NF

			dblTemp= m_dblCHGain[i]+m_dblSRCPointPower[i];
			m_dblOutputSignal+=dbTomw(dblTemp);
			
			if(i == 0)
			{
				m_dblMaxGain = m_dblMinGain = m_dblCHGain[i];
			}
			else
			{
				if(m_dblMaxGain < m_dblCHGain[i])
				{
					m_dblMaxGain = m_dblCHGain[i];
				}
				if(m_dblMinGain > m_dblCHGain[i])
				{
					m_dblMinGain = m_dblCHGain[i];
				}
			}
		//	token = strtok(NULL,seps);
		//	m_dblCHNF[i] = atof(token);//NF
			if (0 == i) 
			{
				m_dblMaxNF = m_dblCHNF[i];
			}
			else
			{
				if (m_dblCHNF[i] > m_dblMaxNF) 
				{
					m_dblMaxNF = m_dblCHNF[i];
				}
			}
		}
		m_dblInputTotal = mwTodb(m_dblInputTotal);
		m_dblOutputTotal = mwTodb(m_dblOutputTotal);
		m_dblOutputSignal=mwTodb(m_dblOutputSignal);
		m_dblGF = m_dblMaxGain - m_dblMinGain;
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	if (NULL != pszResult)
	{
		VirtualFree(pszResult, 0, MEM_RELEASE);
	}

	//Set Trace A Write
//	if(FALSE == SetTraceAttribute('A',0))//set A write
//	{
//		return FALSE;
//	}

	//Set Trace B Write
//	if(FALSE == SetTraceAttribute('B',0))//set B write
//	{
//		return FALSE;
//	}

	return dwErrorCode;
}

/************************************************************************
*  ��������:GetEDFAResult												*
*  ����: ��ȡ�Ŵ���													*
*  ����:																*
*		��																*
*  ������������: ��														*
*  ���:																*
*		1.pdblSumSrcSigPwr:	Դ�ܹ���									*
*		2.pdblSumAmpSigPwr:	�Ŵ��ܹ��ʣ�����ASE��						*
*		3.pdblSunGain: ������											*
*  �����������: double, double, double									*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::GetEDFAResult(double *pdblSumSrcSigPwr, double *pdblSumAmpSigPwr, double *pdblSunGain)
{
	*pdblSumSrcSigPwr = m_dblInputTotal;
	*pdblSumAmpSigPwr = m_dblOutputSignal;
	*pdblSunGain = m_dblOutputSignal - m_dblInputTotal;

	return SUCCESS;
}

/************************************************************************
*  ��������:GetEDFAChResult												*
*  ����: ��ȡ�����Ŵ���												*
*  ����:																*
*		��																*
*  ������������: ��														*
*  ���:																*
*		1.pwChCount: ��������											*
*		2.pdblChWL:	������������										*
*		3.pdblSrcpwr: ����Դ��������									*
*		4.pdblChGain: ��������											*
*		5.pdblChNF:	����NF												*
*		6.pdblChAse:	����ASE											*
*		7.pdblGainFlatness:	����ƽ̹									*
*		8.pdblMaxNF: �������NF											*
*		9.pdblMaxGain:	�����������									*
*		10.pdblMinGain:	������С����									*
*  �����������: DWORD, double											*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
































































































DWORD COSA_AQ6370B::GetEDFAChResult(DWORD *pwChCount, double *pdblChWL, double *pdblSrcpwr, 
									double *pdblChGain, double *pdblChNF, double *pdblChAse,
			double *pdblGainFlatness, double *pdblMaxNF, double* pdblMaxGain, double* pdblMinGain)
{
	double dblMaxGain=-100;
	double dblMinGain=100;
	for(int i=0;i<m_iChCount;i++)
	{
		pdblChWL[i]=m_dblCenterWL[i];
		pdblSrcpwr[i]=m_dblSRCPointPower[i];
//		if (pdblWDL != NULL)
//			pdblChGain[i]=m_dblCHGain[i]+pdblWDL[i];
//		else
	    pdblChGain[i]=m_dblCHGain[i];
		pdblChNF[i]=m_dblCHNF[i];
		
	}
	*pdblGainFlatness	= m_dblGF;

//	if(pdblWDL!=NULL)
//	{
//		for(int i=0;i<m_iChCount;i++)
//		{
//			pdblChGain[i]=m_dblCHGain[i]+pdblWDL[i];
//			if(dblMaxGain<pdblChGain[i])
//			{
//				dblMaxGain=pdblChGain[i];
//			}
//			if(dblMinGain>pdblChGain[i])
//			{
//				dblMinGain=pdblChGain[i];
//			}	
//		}
//
//		*pdblGainFlatness=dblMaxGain-dblMinGain;
//	}

	*pwChCount			= (DWORD)m_iChCount;

	
	*pdblMaxNF			= m_dblMaxNF;
	*pdblMaxGain		= m_dblMaxGain;
	*pdblMinGain		= m_dblMinGain;

	return SUCCESS;
}

/************************************************************************
*  ��������:CloseDevice													*
*  ����: �Ͽ��豸����													*
*  ����:																*
*		��																*
*  ������������: ��														*
*  ���:																*
*		��																*
*  �����������: ��														*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::CloseDevice()
{
	DWORD dwErrorCode = SUCCESS;
	
	dwErrorCode = m_Comm.CloseDevice();
	if(SUCCESS != dwErrorCode)
	{
		throw dwErrorCode;
	}
	
	return dwErrorCode;
}

/************************************************************************
*  ��������:InitOSAAmpCalSet											*
*  ����: ��ʼ���Ŵ�ģʽ����												*
*  ����:																*
*		��																*
*  ������������: ��														*
*  ���:																*
*		��																*
*  �����������: ��														*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::InitOSAAmpCalSet()
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	

	try
	{
		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		sprintf(szCmdString,":CALCulate:PARameter:NF:AALGo MFIX\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_INITIAL;
		}

// 		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
// 		sprintf(szCmdString,":CALCulate:PARameter:NF:FARea 0.40NM\r\n");
// 		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
// 		if(SUCCESS != dwErrorCode)
// 		{
// 			throw dwErrorCode|ERROR_INITIAL;
// 		}

		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		sprintf(szCmdString,":CALCulate:PARameter:NF:RBWidth CAL\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_INITIAL;
		}
	
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_INITIAL;
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}

/************************************************************************
*  ��������:SaveDatatoPC												*
*  ����: �����豸����У׼												*
*  ����:																*
*		dwCalibrationType: У׼����										*
*  ������������: DWORD													*
*  ���:																*
*		��																*
*  �����������: ��														*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::SaveDatatoPC(LPCTSTR lpSavePath, LPCTSTR lpDataType, LPCTSTR lpFileType, char szSelTrace)
{
	DWORD dwErrorCode = 0;
	TCHAR	chSend[MAX_PATH];
	TCHAR	chReceive[MAX_COMM_FIELD] = {""};
	long	iCount = 0;
	CHAR	*pchBMPData;
	int iBmpLength;
	int iBit;
	int iReadCount;
	DWORD dwSpareCount;
	DWORD			dwBytesReturned;
	TCHAR	chFileName[MAX_PATH];
	HANDLE	hFile;

	try
	{
		m_Comm.ClearDevice();
		//zero buffer
		ZeroMemory(chSend, sizeof(chSend));
		sprintf(chSend, "%s", "CFORM 1\r\n");
		dwErrorCode = m_Comm.WriteDevice(chSend,strlen(chSend));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SAVE_DATA;
		}

		//���������OSA�Դ����ڴ�
		ZeroMemory(chSend, sizeof(chSend));

//		int nCmp = strcmp(DATA_TYPE_GRAPHICS, lpDataType);
		if (0 == strcmp(DATA_TYPE_GRAPHICS, lpDataType)) 
		{
			sprintf(chSend, ":MMEMORY:STORE:GRAPHICS COLOR,BMP,"
									"\"%s\",INTERNAL\r\n", lpDataType);
		}
		else if (0 == strcmp(DATA_TYPE_TRACE, lpDataType))
		{
			sprintf(chSend, ":MMEMORY:STORE:TRACE TR%c,%s,\"%s\" INTERNAL\r\n", szSelTrace, lpFileType,lpDataType);
		}
		else
		{
			sprintf(chSend, ":MMEMORY:STORE:%s "
									"\"%s\",INTERNAL\r\n", lpDataType, lpDataType);

		}

		dwErrorCode = m_Comm.WriteDevice(chSend,strlen(chSend));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SAVE_DATA;
		}

//		dwErrorCode = CompleteRequest();
//		if(SUCCESS != dwErrorCode)
//		{
//			throw dwErrorCode|ERROR_INITIAL;
//		}
//		m_Comm.ClearDevice();
		//��BMPͼ�Զ����Ƹ�ʽ����
		ZeroMemory(chSend, sizeof(chSend));
		if (0 == strcmp(DATA_TYPE_TRACE, lpDataType))
		{
			sprintf(chSend, ":MMEM:DATA? \"%c.%s\",INT\r\n", szSelTrace, lpFileType);
		}
		else
		{
			sprintf(chSend, ":MMEM:DATA? \"%s.%s\",INT\r\n", lpDataType, lpFileType);
		}
		dwErrorCode = m_Comm.WriteDevice(chSend,strlen(chSend));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SAVE_DATA;
		}

		if (1 == m_lCommType)
		{
			ZeroMemory(chSend, sizeof(chSend));
			//����һ���������Ƿ��ȡ���ݳɹ�,�ɹ����ر�ʶ'#'
			sprintf(chSend, "%s", ":SYSTEM:BUZZER:WARNING?\r\n");
	
			dwErrorCode = m_Comm.WriteDevice(chSend,strlen(chSend));
			if(SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_SAVE_DATA;
			}

			ZeroMemory(chReceive, MAX_COMM_FIELD);
			//����־λ
			dwErrorCode = m_Comm.ReadDevice(chReceive, 1);
			if(SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_SAVE_DATA;
			}

			//�����ȡ����ʧ��
			if (FLAG_READ_SUCCESS != chReceive[0]) 
			{
				//��������2λ��\r\n��
				ZeroMemory(chReceive, sizeof(chReceive));
				dwErrorCode = m_Comm.ReadDevice(chReceive, 2);
				if(SUCCESS != dwErrorCode)
				{
					throw dwErrorCode|ERROR_SAVE_DATA;
				}

				throw ERROR_SAVE_DATA;
			}
			else
			{
				//���ļ����ȴ�Сλ
				ZeroMemory(chReceive, sizeof(chReceive));
				dwErrorCode = m_Comm.ReadDevice(chReceive, 1);
				if(SUCCESS != dwErrorCode)
				{
					throw dwErrorCode|ERROR_SAVE_DATA;
				}
				iBit = atoi(chReceive);
	
				//���ļ�����
				ZeroMemory(chReceive, sizeof(chReceive));
				dwErrorCode = m_Comm.ReadDevice(chReceive, iBit);
				if(SUCCESS != dwErrorCode)
				{
					throw dwErrorCode|ERROR_SAVE_DATA;
				}
				iBmpLength = atoi(chReceive);
	
				//���ն������ļ�
				pchBMPData = new char[iBmpLength];
				ZeroMemory(pchBMPData, sizeof(char)*iBmpLength);
	
				iReadCount = iBmpLength/MAX_FIELD;
				for (INT iReadIndex = 0; iReadIndex < iReadCount; iReadIndex++) 
				{
					Sleep(100);
					dwErrorCode = m_Comm.ReadDevice(pchBMPData+iReadIndex*MAX_FIELD, MAX_FIELD);
					
					if(SUCCESS != dwErrorCode)
					{
						throw dwErrorCode|ERROR_SAVE_DATA;
					}
				}
	
				dwSpareCount = iBmpLength%MAX_FIELD;
				
				if (dwSpareCount > 0)
				{
					dwErrorCode = m_Comm.ReadDevice(pchBMPData+iReadIndex*MAX_FIELD, dwSpareCount);
					if(SUCCESS != dwErrorCode)
					{
						throw dwErrorCode|ERROR_SAVE_DATA;
					}
				}
			
				//��������2λ��\r\n��
				ZeroMemory(chReceive, sizeof(chReceive));
				dwErrorCode = m_Comm.ReadDevice(chReceive, 2);
				if(SUCCESS != dwErrorCode)
				{
					throw dwErrorCode|ERROR_SAVE_DATA;
				}
	
				//���澯��3λ
				ZeroMemory(chReceive, sizeof(chReceive));
				dwErrorCode = m_Comm.ReadDevice(chReceive, 3);
				if(SUCCESS != dwErrorCode)
				{
					throw dwErrorCode|ERROR_SAVE_DATA;
				}

				//�����ļ���PC
				ZeroMemory(chFileName, sizeof(chFileName));
				hFile  = INVALID_HANDLE_VALUE;
				if (DATA_TYPE_TRACE == lpDataType)
				{
					sprintf(chFileName, "%s_%c.%s", lpSavePath, szSelTrace, lpFileType);
				}
				else
				{
					sprintf(chFileName, "%s_%s.%s", lpSavePath, lpDataType, lpFileType);
				}

				hFile = CreateFile(chFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);			
				
				if(INVALID_HANDLE_VALUE == hFile)
				{
					throw "�������ݴ���!";
				}

				WriteFile(hFile, pchBMPData, iBmpLength, &dwBytesReturned, NULL);
				
				if(INVALID_HANDLE_VALUE != hFile)			// close the file handle here
				{
					CloseHandle(hFile);
					hFile = INVALID_HANDLE_VALUE ;
				}

				if(NULL != pchBMPData)
				{
					delete []pchBMPData;
					pchBMPData = NULL;
				}
			}
		}
		else
		{
			ZeroMemory(chReceive, MAX_COMM_FIELD);
			//����־λ
			dwErrorCode = m_Comm.ReadDevice(chReceive, MAX_COMM_FIELD);

			//�����ȡ����ʧ��
			if (FLAG_READ_SUCCESS != chReceive[0]) 
			{
				throw dwErrorCode|ERROR_SAVE_DATA;
			}
			else
			{
				ZeroMemory(chSend, sizeof(chSend));
				memcpy(chSend, chReceive+1, 1);
				iBit = atoi(chSend);
				ZeroMemory(chSend, sizeof(chSend));
				memcpy(chSend, chReceive+2, iBit);
				iBmpLength = atoi(chSend);
				pchBMPData = chReceive+2+iBit;

				//�����ļ���PC
				ZeroMemory(chFileName, sizeof(chFileName));
				hFile  = INVALID_HANDLE_VALUE;
				if (DATA_TYPE_TRACE == lpDataType)
				{
					sprintf(chFileName, "%s_%c.%s", lpSavePath, szSelTrace, lpFileType);
				}
				else
				{
					sprintf(chFileName, "%s_%s.%s", lpSavePath, lpDataType, lpFileType);
				}

				hFile = CreateFile(chFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);			
				
				if(INVALID_HANDLE_VALUE == hFile)
				{
					throw "�������ݴ���!";
				}

				WriteFile(hFile, pchBMPData, iBmpLength, &dwBytesReturned, NULL);
				
				if(INVALID_HANDLE_VALUE != hFile)			// close the file handle here
				{
					CloseHandle(hFile);
					hFile = INVALID_HANDLE_VALUE ;
				}
			}
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError; 
	}

	return dwErrorCode;
}

/************************************************************************
*  ��������:GetDeviceInfo												*
*  ����: ��ȡ�豸��Ϣ													*
*  ����:																*
*		��																*
*  ������������: ��														*
*  ���:																*
*		stInfo: �豸��Ϣ�ṹ��											*
*  �����������: stDevInfo												*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::GetDeviceInfo(stDevInfo *stInfo)
{
	DWORD dwErrorCode = 0;

	return dwErrorCode;
}

/************************************************************************
*  ��������:GetErrorMessage												*
*  ����: ��ȡ�豸��Ϣ													*
*  ����:																*
*		dwErrorCode: ������												*
*  ������������: DWORD													*
*  ���:																*
*		pszErrorMsg: ����������ַ���									*
*  �����������: char *													*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
BOOL COSA_AQ6370B::GetErrorMessage(DWORD dwErrorCode, char *pszErrorMsg)
{
	return TRUE;
}

/************************************************************************
*  ��������:GetSweepData												*
*  ����: ��ȡ�豸��Ϣ													*
*  ����:																*
*		szSelTrace: ������												*
*  ������������: char													*
*  ���:																*
*		1.pdblWL: ��������												*
*		2.pdblPower: ������������										*
*  �����������: double													*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::GetSweepData(double* pdblWL,double* pdblPower, char szSelTrace)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR *pszDataStream = NULL;
	CHAR szDataStream[RXMINLENS];
	CHAR szCmdString[TXLENS];
	
	DWORD dwSweepPointNum, dwMallocSpace;
	LPSTR pszToken = " ,\t\n",pszNewData = NULL;
	try
	{
		//set result format to ASCII
	    ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		sprintf(szCmdString,":FORMAT:DATA ASCII\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWEEP;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWEEP;
		}
		//get data number
		for (int nIndex=0;nIndex <3;nIndex++)
		{
			ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
			sprintf(szCmdString,":TRACE:DATA:SNUMBER? TR%c\r\n",szSelTrace);
			dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
			if(SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_SWEEP;
			}
			ZeroMemory(szDataStream,RXMINLENS * sizeof(CHAR));
			dwErrorCode = m_Comm.ReadDevice(szDataStream,RXMINLENS);
		}

	    if(SUCCESS > dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWEEP;
		}
		dwErrorCode = 0;	
		dwSweepPointNum = atol(szDataStream);
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWEEP;
		}
		//get sweep data of x axis
		dwMallocSpace = sizeof(CHAR) * dwSweepPointNum * 20;
		pszDataStream = (CHAR*)VirtualAlloc(NULL,dwMallocSpace, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWEEP;
		}

		ZeroMemory(pszDataStream,dwMallocSpace);
        ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		sprintf(szCmdString,":TRACE:X? TR%c\r\n",szSelTrace);
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
	    if(SUCCESS > dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWEEP;
		}
		dwErrorCode = 0;
		dwErrorCode = m_Comm.ReadDevice(pszDataStream,dwMallocSpace);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWEEP;
		}
		//figure the data
		pszNewData = strtok(pszDataStream,pszToken);
		pdblWL[0] = atof(pszNewData);
		for(DWORD i=1;i<dwSweepPointNum;i++)
		{
			pszNewData = strtok(NULL,pszToken);
			if(pszNewData == NULL)
			{
				break;
			}
			pdblWL[i] = atof(pszNewData) * 10E8;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWEEP;
		}
		//get sweep data of y axis
		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		sprintf(szCmdString,":TRACE:Y? TR%c\r\n",szSelTrace);
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWEEP;
		}
		dwErrorCode = m_Comm.ReadDevice(pszDataStream,dwMallocSpace);
	    if(SUCCESS > dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWEEP;
		}
		dwErrorCode = 0;
		//figure the data
		pszNewData = strtok(pszDataStream,pszToken);
		pdblPower[0] = atof(pszNewData);
		for(i=1;i<dwSweepPointNum;i++)
		{
			pszNewData = strtok(NULL,pszToken);
			if(pszNewData == NULL)
			{
				break;
			}
			pdblPower[i] = atof(pszNewData);
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWEEP;
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	VirtualFree(pszDataStream, 0, MEM_RELEASE);

	return dwErrorCode;
}

/************************************************************************
*  ��������:SetCalibration												*
*  ����: ɨ�Ŵ�															*
*  ����:																*
*		1.dwCalibrationType: У׼���ͱ�ʶ								*
*  ������������: DWORD													*
*  ���:																*
*		��																*
*  �����������: ��					 									*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD COSA_AQ6370B::SetCalibration(DWORD dwCalibrationType)
{
	DWORD dwErrorCode = 0;

	return dwErrorCode;
}
/************************************************************************
*  ��������:GetTotalPower									            *
*  ����:��ȡ�ܹ���														* 
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
DWORD COSA_AQ6370B::GetTotalPower(double &dblPow, char szSelTrace)
{
	DWORD  dwErrorCode = SUCCESS;
	CHAR szDataStream[RXMINLENS];
	char  szCmdString[TXLENS];
	
	try
	{
		//set result format to ASCII
		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		sprintf(szCmdString,":FORMAT:DATA ASCII\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW;
		}
		//Set Trace szSelTrace Active
		dwErrorCode = SetTraceAct(szSelTrace);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TRACE;
		}
		//get amp offset
		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		sprintf(szCmdString,":CALCulate:CATegory POWer\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW;
		}
		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		sprintf(szCmdString,":CALCulate\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW;
		}

		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		sprintf(szCmdString,":CALCulate:DATA?\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW;
		}
		ZeroMemory(szDataStream, RXMINLENS);
		dwErrorCode = m_Comm.ReadDevice(szDataStream, RXMINLENS);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW;
		}
		dblPow = atof(szDataStream);
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD COSA_AQ6370B::GetZoomValue(double dbWLNM,double dbBWNM,double *pdbGetValue)
{
	DWORD  dwErrorCode = SUCCESS;
	CHAR szDataStream[RXMINLENS];
	char  szCmdString[TXLENS];
	
	try
	{
		//set result format to ASCII
		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		sprintf(szCmdString,":DISPLAY:TRACE:X:CENTER %.3fNM\r\n",dbWLNM);
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW;
		}

		//get amp offset
		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		sprintf(szCmdString,":DISPLAY:TRACE:X:SPAN %.3fNM\r\n",dbBWNM);
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW;
		}
		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		sprintf(szCmdString,":CALCulate\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW;
		}

		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		sprintf(szCmdString,":CALCulate:DATA?\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW;
		}
		ZeroMemory(szDataStream, RXMINLENS);
		dwErrorCode = m_Comm.ReadDevice(szDataStream, RXMINLENS);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW;
		}
		*pdbGetValue = atof(szDataStream);
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}


/************************************************************************
*  ��������:SetCalibration									            *
*  ����:��ȡʵ��RBW														* 
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
DWORD COSA_AQ6370B::GetActualBW(double dblBwAmp, double &dblActBw)
{
	DWORD  dwErrorCode = SUCCESS;
	double dblData = 0;
	dwErrorCode = GetRBW(&dblData);

	if (fabs(0.2-dblData) < 0.0001)
	{
		dblActBw = 0.140;
	}
	
	
	return dwErrorCode;
}
DWORD COSA_AQ6370B::SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle)
{
	DWORD   dwErrorCode = SUCCESS;
    
	dwErrorCode = m_Comm.SetDeviceHandle(pszDeviceAddr, handle);
	return dwErrorCode;
}