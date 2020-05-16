// OSA_AQ6370B.cpp: implementation of the COSA_AQ6317B class.
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
#define TXLENS 4096
#define MAXSWEEPDATA 

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COSA_AQ6317B::COSA_AQ6317B()
{
	m_dblStartWL = 600.0; 
	m_dblStopWL = 1800.0;
	m_dblRBW = 0.2;
	m_dwSweepPoint = SWEEPPOINT;
	m_lCommType = 0;//0:GPIB, 1:NET
}

COSA_AQ6317B::~COSA_AQ6317B()
{

}

DWORD COSA_AQ6317B::OpenDevice(stDevType stType, char* pszDeviceAddr, unsigned long *comHandle)
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

DWORD COSA_AQ6317B::CompleteRequest()
{
	CHAR pszStatus[8];
	long lIndex = 0;
	ZeroMemory(pszStatus,8);
	char szSendBuf[MAX_PATH];
	int nFlag=1;
	do
	{
		ZeroMemory(szSendBuf,MAX_PATH);
		sprintf(szSendBuf,"SWEEP?\r\n");
		m_Comm.WriteDevice(szSendBuf,strlen(szSendBuf));
		Sleep(50);
		m_Comm.ReadDevice(pszStatus, 8);
		lIndex++;
        nFlag = atoi(pszStatus);

		//如果5分钟后，操作还未完成，返回超时错误
		if (lIndex > 15000)
		{
			return ERROR_RUN_OVERTIME;
		}
	}
	while(nFlag);
	
	return SUCCESS;
}

DWORD COSA_AQ6317B::SetAnalysisType(DWORD wAnalysisType)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	try
	{
		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		switch(wAnalysisType) 
		{
		case 0:      //EDFA NF模式
			{
				//set analysis type
				sprintf(szCmdString,"ANALYSYS\r\n");
				dwErrorCode = m_Comm.WriteDevice(szCmdString, strlen(szCmdString));
				if(SUCCESS != dwErrorCode)
				{
					throw dwErrorCode|ERROR_ANALYSIS;
				}
				Sleep(200);
				ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
				//set analysis type
				sprintf(szCmdString,"EDNF\r\n");
				dwErrorCode = m_Comm.WriteDevice(szCmdString, strlen(szCmdString));
				if(SUCCESS != dwErrorCode)
				{
					throw dwErrorCode|ERROR_ANALYSIS;
				}
				Sleep(200);
			}
			break;
		case 1:      //WDM NF模式
			{
				//set analysis type
				sprintf(szCmdString,"ANALYSYS\r\n");
				dwErrorCode = m_Comm.WriteDevice(szCmdString, strlen(szCmdString));
				if(SUCCESS != dwErrorCode)
				{
					throw dwErrorCode|ERROR_ANALYSIS;
				}
				Sleep(200);
				ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
				//set analysis type
				sprintf(szCmdString,"WNFAN\r\n");
				dwErrorCode = m_Comm.WriteDevice(szCmdString, strlen(szCmdString));
				if(SUCCESS != dwErrorCode)
				{
					throw dwErrorCode|ERROR_ANALYSIS;
				}	
				Sleep(5000);
			}
			break;
		case 2:      //WDM模式
			{
				sprintf(szCmdString,"ANALYSYS\r\n");
				dwErrorCode = m_Comm.WriteDevice(szCmdString, strlen(szCmdString));
				if(SUCCESS != dwErrorCode)
				{
					throw dwErrorCode|ERROR_ANALYSIS;
				}
				Sleep(200);
				ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
				//set analysis type
				sprintf(szCmdString,"WDMAN\r\n");
				dwErrorCode = m_Comm.WriteDevice(szCmdString, strlen(szCmdString));
				if(SUCCESS != dwErrorCode)
				{
					throw dwErrorCode|ERROR_ANALYSIS;
				}
				Sleep(200);
			}
			break;
		case 3:      //Power模式
			{
				sprintf(szCmdString,"ANALYSYS\r\n");
				dwErrorCode = m_Comm.WriteDevice(szCmdString, strlen(szCmdString));
				if(SUCCESS != dwErrorCode)
				{
					throw dwErrorCode|ERROR_ANALYSIS;
				}
				Sleep(200);
				ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
				//set analysis type
				sprintf(szCmdString,"PWR\r\n");
				dwErrorCode = m_Comm.WriteDevice(szCmdString, strlen(szCmdString));
				if(SUCCESS != dwErrorCode)
				{
					throw dwErrorCode|ERROR_ANALYSIS;
				}	
				Sleep(200);
			}
			break;
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

DWORD COSA_AQ6317B::SetSweepRange(double dblStartWL, double dblStopWL)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	try
	{
		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		//set the start wavelength
		sprintf(szCmdString,"STAWL%8.2f\r\n",dblStartWL);
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL;
		}
		
		//set the stop wavelength
		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		sprintf(szCmdString,"STPWL%8.2f\r\n",dblStopWL);
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL;
		}
		m_dblStartWL = dblStartWL; 
		m_dblStopWL = dblStopWL;
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


DWORD COSA_AQ6317B::GetChannelCount(DWORD* pdwChannelCount)
{
	DWORD dwErrorCode = SUCCESS;
	try
	{
		dwErrorCode = RunCalResult();
		if(SUCCESS!=dwErrorCode)
		{
			throw ERROR_WL_COUNT;
		}

		* pdwChannelCount = m_iChCount;

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

DWORD COSA_AQ6317B::GetChannelWaveLens(double* pdblWavelens, DWORD* pdwChannelCount)
{
	DWORD dwErrorCode = FALSE;
	try
	{
		dwErrorCode = RunCalResult();
		if(SUCCESS!=dwErrorCode)
		{
			throw ERROR_WL_COUNT;
		}
        * pdwChannelCount = m_iChCount;
		for(int i=0;i<m_iChCount;i++)
		{
			pdblWavelens[i] = m_dblSRCPointWL[i];
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


DWORD COSA_AQ6317B::GetChannelNF(double* pdblNF, DWORD* pdwChannelCount)
{
	DWORD dwErrorCode = SUCCESS;
	try
	{
		dwErrorCode = RunCalResult();
		if(SUCCESS!=dwErrorCode)
		{
			throw ERROR_WL_COUNT;
		}
		* pdwChannelCount = m_iChCount;
		for(int i=0;i<m_iChCount;i++)
		{
			pdblNF[i] = m_dblCHNF[i];
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

DWORD COSA_AQ6317B::GetChannelGain(double* pdblGain, DWORD* pdwChannelCount)
{
	DWORD dwErrorCode = SUCCESS;

	try
	{
		dwErrorCode = RunCalResult();
		if(SUCCESS!=dwErrorCode)
		{
			throw ERROR_WL_COUNT;
		}

		* pdwChannelCount = m_iChCount;
		for(int i=0;i<m_iChCount;i++)
		{
			pdblGain[i] = m_dblCHGain[i];
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

DWORD COSA_AQ6317B::GetChannelSNR(double* pdblSNR, DWORD* pdwChannelCount)
{
	DWORD dwErrorCode = SUCCESS;
	
	try
	{
		dwErrorCode = RunCalResult();
		if(SUCCESS!=dwErrorCode)
		{
			throw ERROR_WL_COUNT;
		}
		* pdwChannelCount = m_iChCount;
		for(int i=0;i<m_iChCount;i++)
		{
			pdblSNR[i] = m_dblASE[i];
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

DWORD COSA_AQ6317B::GetChannelSourcePower(double* pdblSourcePow, DWORD* pdwChannelCount)
{
	DWORD dwErrorCode = SUCCESS;

	try
	{
		dwErrorCode = RunCalResult();
		if(SUCCESS!=dwErrorCode)
		{
			throw ERROR_WL_COUNT;
		}

		* pdwChannelCount = m_iChCount;
		for(int i=0;i<m_iChCount;i++)
		{
			pdblSourcePow[i] = m_dblSRCPointPower[i];
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

DWORD COSA_AQ6317B::SetPowerOffset(double dblOSAPowOffset)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
	try
	{
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,"POFS%7.2f\r\n",dblOSAPowOffset);
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
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

DWORD COSA_AQ6317B::SetWavelengthOffset(double dblWLOffset)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
	try
	{
//		ZeroMemory(szCmdString,TXLENS);
//		sprintf(szCmdString,"POFS%7.2fNM\r\n",dblWLOffset);
//		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
//		if(SUCCESS != dwErrorCode)
//		{
//			throw dwErrorCode|ERROR_WL_OFFSET;
//		}
//		dwErrorCode = CompleteRequest();
//		if(SUCCESS != dwErrorCode)
//		{
//			throw dwErrorCode|ERROR_WL_OFFSET;
//		}
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

DWORD COSA_AQ6317B::GetPowerOffset(double* pdblOSAPowOffset)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szDataStream[RXMINLENS];
	CHAR szCmdString[TXLENS];
	try
	{
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,"POFS?\r\n");
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


DWORD COSA_AQ6317B::GetWavelengthOffset(double* pdblWLOffset)
{
	DWORD dwErrorCode = SUCCESS;
	try
	{
//		ZeroMemory(szCmdString,TXLENS);
//		sprintf(szCmdString,":SENSE:CORRECTION:WAVELENGTH:SHIFT?\r\n");
//		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
//		if(SUCCESS != dwErrorCode)
//		{
//			throw dwErrorCode|ERROR_WL_OFFSET;
//		}
//		ZeroMemory(szDataStream,RXMINLENS * sizeof(CHAR));
//		dwErrorCode = m_Comm.ReadDevice(szDataStream,RXMINLENS);
//		if(SUCCESS != dwErrorCode)
//		{
//			throw dwErrorCode|ERROR_WL_OFFSET;
//		}
//		*pdblWLOffset = atof(szDataStream) * pow(10,9);//NM
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

DWORD COSA_AQ6317B::InitSingleSweep(double dblStartWL, double dblStopWL, double dblRBW, DWORD dwSweepPoint)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
	try
	{
		//set the start wavelength
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString," STAWL%8.2f\r\n",dblStartWL);
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL;
		}
		//set the stop wavelength
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,"STPWL%8.2f\r\n",dblStopWL);
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL;
		}
		m_dblStartWL = dblStartWL; 
		m_dblStopWL = dblStopWL;

		//set RBW
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,"RESLN%8.3f\r\n",dblRBW);
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_RBW;
		}
		m_dblRBW = dblRBW;

		//set sweep point
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,"SMPL%d\r\n",dwSweepPoint);
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWEEP_POINT;
		}
		m_dwSweepPoint = dwSweepPoint;
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

DWORD COSA_AQ6317B::GetEDFATestResult(int nType)
{
	DWORD dwErrorCode = SUCCESS;
	char szSpec[] = ",";
	char *token = NULL;
	char szCmdString[TXLENS];
	try
	{
		if(nType==0)
		{
//			dwErrorCode =SetTraceAct('A');
//			if(SUCCESS != dwErrorCode)
//			{
//				throw dwErrorCode|ERROR_SWEEP_DATA;
//			}
			dwErrorCode = SetAnalysisType(3);
			if(SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_ANALYSIS;
			}
			dwErrorCode = CompleteRequest();
			if(SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_INITIAL;
			}
			//set result format to ASCII
			ZeroMemory(szCmdString,TXLENS);
			sprintf(szCmdString,"ANA?\r\n");
			dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
			if(SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_SWEEP_DATA;
			}
			
			ZeroMemory(szCmdString,TXLENS);
			dwErrorCode = m_Comm.ReadDevice(szCmdString,TXLENS);
			if(SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_SWEEP_DATA;
			}	
			token = strtok(szCmdString,szSpec);
			
			m_dblInputTotal = atof(token);
		}
        else if(nType==1)
		{
			dwErrorCode = SetAnalysisType(3);
			if(SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_ANALYSIS;
			}
			dwErrorCode = CompleteRequest();
			if(SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_INITIAL;
			}
			//set result format to ASCII
			ZeroMemory(szCmdString,TXLENS);
			sprintf(szCmdString,"ANA?\r\n");
			dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
			if(SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_SWEEP_DATA;
			}
			
			ZeroMemory(szCmdString,TXLENS);
			dwErrorCode = m_Comm.ReadDevice(szCmdString,TXLENS);
			if(SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_SWEEP_DATA;
			}	
			token = strtok(szCmdString,szSpec);
			//输出功率
			m_dblOutputTotal = atof(token);
		}

		dwErrorCode= SetAnalysisType(0);
		if(dwErrorCode!=SUCCESS)
		{
			throw dwErrorCode|ERROR_ANALYSIS;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_INITIAL;
		}
		Sleep(2000);
		//set result format to ASCII
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,"ANA?\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWEEP_DATA;
		}

		//get EDFA result
		ZeroMemory(szCmdString,TXLENS);
		dwErrorCode = m_Comm.ReadDevice(szCmdString,TXLENS);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWEEP_DATA;
		}	
		token = strtok(szCmdString,szSpec);
		//m_dblGF = atof(token);
		token = strtok(NULL,szSpec);
		token = strtok(NULL,szSpec);
		token = strtok(NULL,szSpec);
		m_dblMaxNF = atof(token);
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


DWORD COSA_AQ6317B::ResetDevice()
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
	
DWORD COSA_AQ6317B::SetAmpSrcSigOffset(double dblSrcSigOffset)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
	try
	{
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,"WNFOFI%.2f\r\n",dblSrcSigOffset);
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW_OFFSET;
		}
		Sleep(1000);
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

DWORD COSA_AQ6317B::GetAmpOffset(double &dblSourceOffset, double &dblAmpOffset)
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

DWORD COSA_AQ6317B::SetAmpOutSigOffset(double dblOutSigOffset)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	ZeroMemory(szCmdString, TXLENS * sizeof(CHAR));
	try
	{
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString, "WNFOFO%.2f\r\n", dblOutSigOffset);
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW_OFFSET;
		}
		Sleep(1000);
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

DWORD COSA_AQ6317B::SetAmpOffset(double dblSourceOffset, double dblAmpOffset)
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


DWORD COSA_AQ6317B::GetAmpSrcSigOffset(double* pdblSrcSigOffset)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szDataStream[RXMINLENS];
	char szCmdString[TXLENS];
	
	try
	{
		//get amp offset
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString, "WNFOFI?\r\n");
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

DWORD COSA_AQ6317B::GetAmpOutSigOffset(double* pdblOutSigOffset)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szDataStream[RXMINLENS];
	char szCmdString[TXLENS];
	try
	{
		//get amp offset
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString, "WNFOFI?\r\n");
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

DWORD COSA_AQ6317B::SetOSALocalCtrl()
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

DWORD COSA_AQ6317B::RunSweep(double* pdblSweepDataX, double* pdblSweepDataY, char szSelTrace)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR *pszDataStream = NULL;
	CHAR szCmdString[TXLENS];
	ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
	DWORD dwSweepPointNum;
    char*token=NULL;
	char szSepc[] =",";
	try
	{
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

		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,"SGL\r\n");
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

		dwErrorCode = SetTraceAttribute(szSelTrace, 1);//FIX
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode;
		}

		if(pszDataStream==NULL)
		{
			pszDataStream = (char*)VirtualAlloc(NULL,m_dwSweepPoint*8,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
			ZeroMemory(pszDataStream,m_dwSweepPoint*8);
		}
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,"WDATA\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_INITIAL;
		}
        Sleep(100);
		dwErrorCode = m_Comm.ReadDevice(pszDataStream,m_dwSweepPoint*8);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_INITIAL;
		}
		token = strtok(pszDataStream,szSepc);
		
        dwSweepPointNum = atol(token);
		for(int i=0;i<dwSweepPointNum;i++)
		{
			token = strtok(NULL,szSepc);
			//ASSERT(token);
            pdblSweepDataX[i] = atof(token);
		}

		ZeroMemory(pszDataStream,m_dwSweepPoint*8);
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,"LDATA\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_INITIAL;
		}
        Sleep(100);
		dwErrorCode = m_Comm.ReadDevice(pszDataStream,m_dwSweepPoint*8);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_INITIAL;
		}
		token = strtok(pszDataStream,szSepc);
	//	ASSERT(token);
        dwSweepPointNum = atol(token);
		for(i=0;i<dwSweepPointNum;i++)
		{
			token = strtok(NULL,szSepc);
		//	ASSERT(token);
            pdblSweepDataY[i] = atof(token);
		}
		
		
		dwErrorCode = SetTraceAttribute(szSelTrace, 0);//write
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode;
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

	if(pszDataStream!=NULL)
	{
		VirtualFree(pszDataStream, 0, MEM_RELEASE);
		pszDataStream =NULL;
	}
	

	return dwErrorCode;
	
}
/////////////////////////////////////////////////////////////
//函数说明：
//    从OSA中获得单次扫描的点数
//Add by wanxin
//Time：20150520
/////////////////////////////////////////////////////////////
DWORD COSA_AQ6317B::GetSingleSweepPoint(DWORD * pCount)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	char * pszDataStream=NULL;
	char *token=NULL;
	char szSpec[] =",";
	ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
	DWORD dwSweepPointNum=0;
	try
	{
		//get data number
		dwErrorCode = SetTraceAct('A');
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode;
		}

		if(pszDataStream==NULL)
		{
			pszDataStream = (char*)VirtualAlloc(NULL,m_dwSweepPoint*8,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
			ZeroMemory(pszDataStream,m_dwSweepPoint*8);
		}
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,"WDATA\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_INITIAL;
		}
        Sleep(100);
		dwErrorCode = m_Comm.ReadDevice(pszDataStream,m_dwSweepPoint*8);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_INITIAL;
		}
		token = strtok(pszDataStream,szSpec);
		
        dwSweepPointNum = atol(token);
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
	if(pszDataStream!=NULL)
	{
		VirtualFree(pszDataStream, 0, MEM_RELEASE);
		pszDataStream =NULL;
	}
	return dwErrorCode;
}

DWORD COSA_AQ6317B::SetWLOffsetTable(USHORT usWavelength, double dblWLOffset)
{
	DWORD dwErrorCode = FALSE;	
	try
	{

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

DWORD COSA_AQ6317B::GetWLOffsetTable(USHORT usWavelength, double* pdblWLOffset)
{
	DWORD dwErrorCode = FALSE;	
	try
	{

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

DWORD COSA_AQ6317B::SetPowOffsetTable(USHORT usWavelength, double dblPowOffset)
{
	DWORD dwErrorCode = SUCCESS;
	
	try
	{

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

DWORD COSA_AQ6317B::GetPowOffsetTable(USHORT usWavelength,double* pdblPowOffset)
{
	DWORD dwErrorCode = SUCCESS;
	try
	{

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

DWORD COSA_AQ6317B::InitAmpTest(double dblStartWL, double dblStopWL, double dblRBW)
{
	DWORD dwErrorCode = SUCCESS;
	int iStateIndex = 0;
	char szCmdString[TXLENS];
	ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
	try
	{

		//set start and stop wavelength
		dwErrorCode = SetSweepRange(dblStartWL, dblStopWL);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode;
		}
		//set RBW
		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		sprintf(szCmdString,"RESLN %8.3f\r\n",dblRBW);
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_RBW;
		}
		m_dblRBW = dblRBW;
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

DWORD COSA_AQ6317B::GetGPIBAress(int *iGpibAddress)
{
	DWORD dwErrorCode = SUCCESS;
	try
	{
	     *iGpibAddress=0;  
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

DWORD COSA_AQ6317B::SetRBW(double dblRBW)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	
	try
	{
		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		sprintf(szCmdString,"RESLN%8.3f\r\n",dblRBW);
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

DWORD COSA_AQ6317B::GetRBW(double* pdblRBW)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szDataStream[RXMINLENS];
	char szCmdString[TXLENS];
	try
	{
		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		sprintf(szCmdString,"RESLN?\r\n");
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

		*pdblRBW = atof(szDataStream);
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

DWORD COSA_AQ6317B::SetTraceAct(char szSelTrace)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	
	try
	{
		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		switch(szSelTrace)
		{
		case 'A':
			{
				sprintf(szCmdString,"ACTV0\r\n",szSelTrace);
			}
			break;
		case 'B':
			{
				sprintf(szCmdString,"ACTV1\r\n",szSelTrace);
			}
			break;
		case 'C':
			{
				sprintf(szCmdString,"ACTV2\r\n",szSelTrace);
			}
			break;
		}
		
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TRACE;
		}
		Sleep(200);
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

DWORD COSA_AQ6317B::SetTraceAttribute(char szSelTrace, USHORT uiAttribute)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	
	try
	{
		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		switch(uiAttribute)
		{
		case 0:
			sprintf(szCmdString,"WRT%c\r\n",szSelTrace);
			break;
		case 1:
			sprintf(szCmdString,"FIX%c\r\n",szSelTrace);
			break;
		case 2:
			sprintf(szCmdString,"MAX%c\r\n",szSelTrace);
			break;
		case 3:
			sprintf(szCmdString,"DSP%c\r\n",szSelTrace);
			break;
		case 4:
		    sprintf(szCmdString,"BLK%c\r\n",szSelTrace);
			break;
		}
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TRACE_ATTRIBUTE;
		}
		Sleep(200);
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

DWORD COSA_AQ6317B::MeasureSource()
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
		sprintf(szCmdString,"SGL\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWEEP_MODE;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_INITIAL;
		}

		dwErrorCode = SetTraceAttribute('A',1);//FIX
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TRACE_ATTRIBUTE;
		}
//		dwErrorCode = GetEDFATestResult(0);
//		if(SUCCESS != dwErrorCode)
//		{
//				throw dwErrorCode|ERROR_INITIAL;
//		}
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


DWORD COSA_AQ6317B::MeasureAmplifier(BOOL bScanSrcOnly)
{
	DWORD dwErrorCode = SUCCESS;
	char seps[]= ",\t\n";
	char* token=NULL;
	char *pszResult=NULL;
	double dblTemp = 0;
	CHAR szCmdString[TXLENS];
	
	try
	{

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
		sprintf(szCmdString,"SGL\r\n");
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

		dwErrorCode = SetTraceAttribute('B', 1);//fix
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode;
		}
		//start analysis data
		//Get EDFA Result
//		dwErrorCode = GetEDFATestResult(1);
//		if(SUCCESS != dwErrorCode)
//		{
//			throw dwErrorCode;
//		}
		
		dwErrorCode = RunCalResult();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode;
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

	if (NULL != pszResult)
	{
		VirtualFree(pszResult, 0, MEM_RELEASE);
	}

	return dwErrorCode;
}

DWORD COSA_AQ6317B::GetEDFAResult(double *pdblSumSrcSigPwr, double *pdblSumAmpSigPwr, double *pdblSunGain)
{
	
    char szCmdString[TXLENS];
	DWORD dwErrorCode = SUCCESS;
	//ASSERT(szCmdString);
	*pdblSumSrcSigPwr = m_dblInputTotal;
	*pdblSumAmpSigPwr = m_dblOutputTotal;
	*pdblSunGain = m_dblOutputTotal - m_dblInputTotal;

	return SUCCESS;
}

DWORD COSA_AQ6317B::GetEDFAChResult(DWORD *pwChCount, double *pdblChWL, double *pdblSrcpwr, 
									double *pdblChGain, double *pdblChNF, double *pdblChAse,
			double *pdblGainFlatness, double *pdblMaxNF, double* pdblMaxGain, double* pdblMinGain)
{
	for(int i=0;i<m_iChCount;i++)
	{
		pdblChWL[i]=m_dblSRCPointWL[i];
		pdblSrcpwr[i]=m_dblSRCPointPower[i];
	    pdblChGain[i]=m_dblCHGain[i];
		pdblChNF[i]=m_dblCHNF[i];
		pdblChAse[i] = m_dblASE[i];
		
	}
	*pdblGainFlatness	= m_dblGF;
	*pwChCount			= (DWORD)m_iChCount;	
	*pdblMaxNF			= m_dblMaxNF;
	*pdblMaxGain		= m_dblMaxGain;
	*pdblMinGain		= m_dblMinGain;

	return SUCCESS;
}

DWORD COSA_AQ6317B::CloseDevice()
{
	DWORD dwErrorCode = SUCCESS;
	
	dwErrorCode = m_Comm.CloseDevice();
	if(SUCCESS != dwErrorCode)
	{
		throw dwErrorCode;
	}
	
	return dwErrorCode;
}

DWORD COSA_AQ6317B::SaveDatatoPC(LPCTSTR lpSavePath, LPCTSTR lpDataType, LPCTSTR lpFileType, char szSelTrace)
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

	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError; 
	}



	return dwErrorCode;
}

DWORD COSA_AQ6317B::GetDeviceInfo(stDevInfo *stInfo)
{
	DWORD dwErrorCode = 0;

	return dwErrorCode;
}


BOOL COSA_AQ6317B::GetErrorMessage(DWORD dwErrorCode, char *pszErrorMsg)
{
	return TRUE;
}


DWORD COSA_AQ6317B::GetSweepData(double* pdblWL,double* pdblPower, char szSelTrace)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR *pszDataStream = NULL;
	CHAR szCmdString[TXLENS];
	char *token=NULL;
	char szSepc[]=",";
	DWORD dwSweepPointNum;

	try
	{
		//Set Trace B Active
		dwErrorCode = SetTraceAct(szSelTrace);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode;
		}

		if(pszDataStream==NULL)
		{
			pszDataStream = (char*)VirtualAlloc(NULL,m_dwSweepPoint*8,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
			ZeroMemory(pszDataStream,m_dwSweepPoint*8);
		}
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,"WDATA\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_INITIAL;
		}
        Sleep(100);
		dwErrorCode = m_Comm.ReadDevice(pszDataStream,m_dwSweepPoint*8);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_INITIAL;
		}
		token = strtok(pszDataStream,szSepc);
		
        dwSweepPointNum = atol(token);
		for(int i=0;i<dwSweepPointNum;i++)
		{
			token = strtok(NULL,szSepc);
		//	ASSERT(token);
            pdblWL[i] = atof(token);
		}

		ZeroMemory(pszDataStream,m_dwSweepPoint*8);
		ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,"LDATA\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_INITIAL;
		}
        Sleep(100);
		dwErrorCode = m_Comm.ReadDevice(pszDataStream,m_dwSweepPoint*8);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_INITIAL;
		}
		token = strtok(pszDataStream,szSepc);
//		ASSERT(token);
        dwSweepPointNum = atol(token);
		for(i=0;i<dwSweepPointNum;i++)
		{
			token = strtok(NULL,szSepc);
		//	ASSERT(token);
            pdblPower[i] = atof(token);
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

	if(pszDataStream!=NULL)
	{
		VirtualFree(pszDataStream, 0, MEM_RELEASE);
		pszDataStream =NULL;
	}

	return dwErrorCode;
}

DWORD COSA_AQ6317B::SetCalibration(DWORD dwCalibrationType)
{
	DWORD dwErrorCode = 0;

	return dwErrorCode;
}

DWORD COSA_AQ6317B::GetTotalPower(double &dblPow, char szSelTrace)
{
	DWORD  dwErrorCode = SUCCESS;
	CHAR szDataStream[RXMINLENS];
	char  szCmdString[TXLENS];
	
	try
	{
		//Set Trace szSelTrace Active
		dwErrorCode = SetTraceAct(szSelTrace);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TRACE;
		}
		dwErrorCode =SetAnalysisType(3);
		if(dwErrorCode!=SUCCESS)
		{
			throw dwErrorCode|ERROR_TRACE;
		}
		dwErrorCode = CompleteRequest();
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_INITIAL;
		}
		//get amp offset
		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		sprintf(szCmdString,"ANA?\r\n");
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

DWORD COSA_AQ6317B::GetZoomValue(double dbWLNM,double dbBWNM,double *pdbGetValue)
{
	DWORD  dwErrorCode = SUCCESS;	
	try
	{

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

DWORD COSA_AQ6317B::GetActualBW(double dblBwAmp, double &dblActBw)
{
	DWORD  dwErrorCode = SUCCESS;
	double dblData = 0;
	dwErrorCode = GetRBW(&dblData);

	if (fabs(0.2-dblData) < 0.0001)
	{
		dblActBw = dblData;
	}
	return dwErrorCode;
}
DWORD COSA_AQ6317B::SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle)
{
	DWORD   dwErrorCode = SUCCESS;
    
	dwErrorCode = m_Comm.SetDeviceHandle(pszDeviceAddr, handle);
	return dwErrorCode;
}

DWORD COSA_AQ6317B::RunCalResult()
{
	DWORD dwErrorCode = FALSE;
	CHAR szDataStream[RXMINLENS];
	char szSpec[] = ",";
	char *token = NULL;
	CHAR szCmdString[TXLENS];
	int nCount =0;
	int nLine =0;
	try
	{
		m_dblOutputTotal=0;
		m_dblInputTotal=0;
		m_dblOutputSignal=0;
		//set result format to ASCII
		dwErrorCode = SetAnalysisType(1);
		if(dwErrorCode!=SUCCESS)
		{
			throw dwErrorCode|ERROR_ANALYSIS;
		}

        ZeroMemory(szCmdString,TXLENS);
		sprintf(szCmdString,"ANA?\r\n");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL_COUNT;
		}
		Sleep(1000);
		ZeroMemory(szCmdString,TXLENS * sizeof(CHAR));
		dwErrorCode = m_Comm.ReadDevice(szCmdString, TXLENS);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL_COUNT;
		}
		//1,1553.879,   6.25,   6.25, -99.67,    0.119,   0.00,   0.00
		token = strtok(szCmdString,szSpec);
		if(token ==NULL)
		{
			throw dwErrorCode|ERROR_WL_COUNT;
		}
		//ASSERT(token);
		nCount = atoi(token);
		m_iChCount = nCount;
		
		token = strtok(NULL,szSpec);//波长
		//ASSERT(token); 
		m_dblSRCPointWL[0] = atof(token);
		m_dblAmpPointWL[0] = atof(token);
		token = strtok(NULL,szSpec);//Inupt
		m_dblSRCPointPower[0] = atof(token);
		m_dblInputTotal+=dbTomw(m_dblSRCPointPower[0] );
		//ASSERT(token); 
		token = strtok(NULL,szSpec);//OutPut
		m_dblAmpPointPower[0] = atof(token);
		m_dblOutputTotal += dbTomw(m_dblAmpPointPower[0] );
	
		token = strtok(NULL,szSpec);//ASE
		m_dblASE[0] = atof(token);
	
		token = strtok(NULL,szSpec);
		m_dblResoln[0] = atof(token);
		
		token = strtok(NULL,szSpec);
		m_dblCHGain[0] = atof(token);
		
		token = strtok(NULL,szSpec);
		m_dblCHNF[0] = atof(token);
		double dbTemp  = m_dblCHGain[0]+m_dblSRCPointPower[0];
		m_dblOutputSignal+=  dbTomw(dbTemp);
        nLine =1;
		while(1)
		{
			token = strtok(NULL,szSpec);//波长
			if(token ==NULL)
				break;
		 
			m_dblSRCPointWL[nLine] = atof(token);
			m_dblAmpPointWL[nLine] = atof(token);
			token = strtok(NULL,szSpec);//Inupt
			m_dblSRCPointPower[nLine] = atof(token);
            m_dblInputTotal += dbTomw(m_dblSRCPointPower[nLine] );
			token = strtok(NULL,szSpec);//OutPut
			m_dblAmpPointPower[nLine] = atof(token);
		    m_dblOutputTotal += dbTomw(m_dblAmpPointPower[nLine]);
		
			token = strtok(NULL,szSpec);
			m_dblASE[nLine] = atof(token);
		
			token = strtok(NULL,szSpec);
			m_dblResoln[nLine] = atof(token);
		
			token = strtok(NULL,szSpec);
			m_dblCHGain[nLine] = atof(token);
		
			token = strtok(NULL,szSpec);
			m_dblCHNF[nLine] = atof(token);
			dbTemp  = m_dblCHGain[nLine]+m_dblSRCPointPower[nLine];
		    m_dblOutputSignal+=  dbTomw(dbTemp);
			nLine++;
		}
		
		m_dblInputTotal = mwTodb(m_dblInputTotal);
		m_dblOutputSignal = mwTodb(m_dblOutputSignal);
		m_dblOutputTotal =  mwTodb(m_dblOutputTotal);

		FinddoubleMaxMin(m_dblCHGain,&m_dblMinGain,&m_dblMaxGain,nCount);
		m_dblGF = m_dblMaxGain - m_dblMinGain;
		double dbMinNF;
		FinddoubleMaxMin(m_dblCHNF,&dbMinNF,&m_dblMaxNF,nCount);
		
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

void COSA_AQ6317B::FinddoubleMaxMin(double *dbDataArry,double *dbMin,double *dbMax,int nLength)
{
	double dbPreMax,dbPreMin;
    dbPreMax = dbDataArry[0];
	dbPreMin = dbDataArry[0];
	for(int i=1;i<nLength;i++)
	{
		if(dbDataArry[i] > dbPreMax )
		{
			dbPreMax = dbDataArry[i];
		}
        if(dbDataArry[i] < dbPreMin)
		{
			dbPreMin = dbDataArry[i];
		}	
	}
	*dbMin = dbPreMin; 
	*dbMax = dbPreMax;
}


////////////////////////////////////////////////////////////
//函数说明：
//   设置OSA的SENSE模式,1-Normal，2-MID,3-H1，4-H2,5-H3
//Add by wanxin
//Time:2019/7/24
///////////////////////////////////////////////////////////
DWORD COSA_AQ6317B::SetOSASenseMode(int nMode)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	CHAR szDataStream[RXMINLENS];
	int iStateIndex = 0;
	ZeroMemory(szCmdString, TXLENS * sizeof(CHAR));
	try
	{
		if (nMode < 1 || nMode >5)
		{
			throw ERROR_SENS;
		}
		ZeroMemory(szCmdString, TXLENS * sizeof(CHAR));
		switch (nMode)
		{
		case 1:
		{
			sprintf(szCmdString, ":SENSE:SENSE NORM\r\n");
		}
		break;
		case 2:
		{
			sprintf(szCmdString, ":SENSE:SENSE MID\r\n");
		}
		break;
		case 3:
		{
			sprintf(szCmdString, ":SENSE:SENSE HIGH1\r\n");
		}
		break;
		case 4:
		{
			sprintf(szCmdString, ":SENSE:SENSE HIGH2\r\n");
		}
		break;
		case 5:
		{
			sprintf(szCmdString, ":SENSE:SENSE HIGH3\r\n");
		}
		break;
		}
		dwErrorCode = m_Comm.WriteDevice(szCmdString, strlen(szCmdString));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode | ERROR_SENS;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}