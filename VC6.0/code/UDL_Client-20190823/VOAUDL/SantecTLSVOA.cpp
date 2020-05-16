// OplkMEMSVOA.cpp: implementation of the COplkMEMSVOA class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\\include\\voa.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSantectTLSVOA::CSantectTLSVOA()
{
//	m_hCommPort = INVALID_HANDLE_VALUE;
//	m_Comm = NULL;
//	m_Comm = new CCommunicationDLL;
}

CSantectTLSVOA::~CSantectTLSVOA()
{
//	delete m_Comm;
//	m_Comm = NULL;
}

DWORD CSantectTLSVOA::OpenDevice(char* pszDeviceAddr, unsigned long *comHandle)
{
	DWORD dwErrorCode = SUCCESS;
    char pchTxData[50];
    try
	{
		dwErrorCode = m_Comm.OpenDevice(pszDeviceAddr, *comHandle);
		if (SUCCESS != dwErrorCode)
		{
			return ERROR_VOA | dwErrorCode;
		}

		ZeroMemory(pchTxData,sizeof(char)*50);
		sprintf(pchTxData,"*RST\r\n");
		dwErrorCode = m_Comm.WriteDevice(pchTxData,strlen(pchTxData));
		if (SUCCESS != dwErrorCode)
		{
			throw ERROR_INITIAL;
		}

		dwErrorCode = SetEnableOutput(0,TRUE);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_INITIAL;
		}

		ZeroMemory(pchTxData, 50);
		sprintf(pchTxData, "POW:ATT:AUT 0\r\n");

		dwErrorCode = m_Comm.WriteDevice(pchTxData, strlen(pchTxData));
		if(SUCCESS != dwErrorCode)
		{
			throw ERROR_VOA | dwErrorCode;
		}
	}
	catch(...)
	{
		return UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD CSantectTLSVOA::CloseDevice()
{
	DWORD	dwErrorCode = SUCCESS;
	dwErrorCode = m_Comm.CloseDevice();
	
	return dwErrorCode;
}

DWORD CSantectTLSVOA::SetHandle(char* pszDeviceAddr, unsigned long comHandle)
{
	DWORD	dwErrorCode = SUCCESS;
	
	dwErrorCode = m_Comm.SetDeviceHandle(pszDeviceAddr, comHandle);

	return dwErrorCode;
}

DWORD CSantectTLSVOA::GetAttenuation(long lChIndex, double *dblAtten)
{
	DWORD dwErrorCode = SUCCESS;
    char pchTxData[50];
	char pchRxData[100];
	BYTE bIndex;
	CHAR pchTemp[256];

	try
	{
		ZeroMemory(pchTxData, 50);
		sprintf(pchTxData, "POW:ATT?\r\n",lChIndex);
		// –¥∂¡»°À•ºıµƒ√¸¡Ó
		dwErrorCode = m_Comm.WriteDevice(pchTxData, strlen(pchTxData));
		if(SUCCESS != dwErrorCode)
		{
//			strcpy(m_pszGlobleMsg, "–¥VOA÷∏¡Ó¥ÌŒÛ");
			throw dwErrorCode | ERROR_ATTEN;
		}

		ZeroMemory(pchRxData, 32);
		
		bIndex = 0;
		while(bIndex < 10)
		{
			Sleep(30);
			// ∂¡»°À•ºı
			dwErrorCode = m_Comm.ReadDevice(pchRxData, 32);
			if(SUCCESS != dwErrorCode)
			{
				bIndex ++;
				continue;
			}
			else
			{
				break;
			}
		}

		*dblAtten = atof(pchRxData);
	}
	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD CSantectTLSVOA::GetDeviceInfo(stDevInfo *stInfo)
{
	DWORD dwErrorCode = SUCCESS;
	char pchTxData[50];
	char pchRxData[100];
	BYTE bIndex, byComLen;

	try
	{
		ZeroMemory(pchTxData, 50);
		sprintf(pchTxData, "*IDN?\r\n");
		byComLen = strlen(pchTxData);

		// Send 'INFO' command to VOA device
		dwErrorCode = m_Comm.WriteDevice(pchTxData, byComLen);
		if(SUCCESS != dwErrorCode)
		{
			//strcpy(m_pszGlobleMsg, "∑¢ÀÕªÒ»°VOA…Ë±∏–≈œ¢÷∏¡Ó¥ÌŒÛ");
			throw ERROR_INFO | dwErrorCode;
		}

		ZeroMemory(pchRxData, 100);
		
		bIndex = 0;
		// Get info from VOA device
		while(bIndex < 10)
		{
			Sleep(30);
			dwErrorCode = m_Comm.ReadDevice(pchRxData, 100);
			if(SUCCESS != dwErrorCode)
			{
				bIndex ++;
				continue;
			}
			else
				break;
		}
		if (bIndex == 10)
		{
			//strcpy(m_pszGlobleMsg, "∂¡VOA…Ë±∏–≈œ¢¥ÌŒÛ");
			throw ERROR_INFO | dwErrorCode;
		}

		// Write data from reading to struct
		if (stInfo != NULL)
		{
			strcpy((char *)stInfo, pchRxData);
			/*
			stInfo->pszName;
			stInfo->pszSerialNum;
			stInfo->pszMFDate;
			stInfo->pszHWVer;
			stInfo->pszFWVer;
			*/
		}
	}
	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

BOOL CSantectTLSVOA::GetErrorMessage(DWORD dwErrorCode, char *pszErrorMsg)
{
	if (pszErrorMsg != NULL)
	{
//		strcpy(pszErrorMsg, m_pszGlobleMsg);
//		memset(m_pszGlobleMsg, 0, 100);
	}
	return TRUE;
}

DWORD CSantectTLSVOA::GetStatus(DWORD *dwStatus)
{
	DWORD dwErrorCode = SUCCESS;
    char pchTxData[50];
	char pchRxData[100];
	BYTE bIndex;
	CHAR pchTemp[256];

	try
	{
		ZeroMemory(pchTxData, 50);
		sprintf(pchTxData, "POW:STAT?\r\n");
		// –¥∂¡»°À•ºıµƒ√¸¡Ó
		dwErrorCode = m_Comm.WriteDevice(pchTxData, strlen(pchTxData));
		if(SUCCESS != dwErrorCode)
		{
//			strcpy(m_pszGlobleMsg, "–¥VOA÷∏¡Ó¥ÌŒÛ");
			throw dwErrorCode | ERROR_ATTEN;
		}

		ZeroMemory(pchRxData, 32);
		
		bIndex = 0;
		while(bIndex < 10)
		{
			Sleep(30);
			// ∂¡»°À•ºı
			dwErrorCode = m_Comm.ReadDevice(pchRxData, 32);
			if(SUCCESS != dwErrorCode)
			{
				bIndex ++;
				continue;
			}
			else
			{
				break;
			}
		}

		*dwStatus = atoi(pchRxData);
	}
	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD CSantectTLSVOA::GetWavelength(long lChIndex, double *dblWL)
{
	DWORD dwErrorCode = SUCCESS;
	char pchTxData[50], pchRxData[100];
	char pchTemp[256];
	BYTE bIndex, bTxDataLength;
	int	 nTemp = 0;

	try
	{
		ZeroMemory(pchTxData, 50);
		sprintf(pchTxData, "WAV?\r\n");

		bTxDataLength = strlen((const char *)pchTxData);

		dwErrorCode = m_Comm.WriteDevice(pchTxData, bTxDataLength);
		if(SUCCESS != dwErrorCode)
		{
			throw ERROR_WL | dwErrorCode;
		}

		ZeroMemory(pchRxData, 32);
		
		bIndex = 0;
		while(bIndex < 10)
		{
			dwErrorCode = m_Comm.ReadDevice(pchRxData, 32);
			if(SUCCESS != dwErrorCode)
			{
				bIndex ++;
				continue;
			}
			else
				break;
		}
		if (bIndex == 10)
		{
			throw ERROR_WL | dwErrorCode;
		}

		*dblWL = atof(pchRxData);
	}
	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD CSantectTLSVOA::ResetDevice()
{
		DWORD dwErrorCode = SUCCESS;
	char pchTxData[50], pchRxData[100];
	char pchTemp[256];
	BYTE bIndex, bTxDataLength;
	int	 nTemp = 0;

	try
	{
		ZeroMemory(pchTxData, 50);
		sprintf(pchTxData, "*RST\r\n");

		bTxDataLength = strlen((const char *)pchTxData);

		dwErrorCode = m_Comm.WriteDevice(pchTxData, bTxDataLength);
		if(SUCCESS != dwErrorCode)
		{
//			strcpy(m_pszGlobleMsg, "∑¢ÀÕ∂¡»°VOA≤®≥§÷∏¡Ó¥ÌŒÛ");
			throw ERROR_WL | dwErrorCode;
		}
		Sleep(5000);

		ZeroMemory(pchTxData, 50);
		sprintf(pchTxData, "POW:ATT:AUT 0\r\n");

		bTxDataLength = strlen((const char *)pchTxData);

		dwErrorCode = m_Comm.WriteDevice(pchTxData, bTxDataLength);
		if(SUCCESS != dwErrorCode)
		{
//			strcpy(m_pszGlobleMsg, "∑¢ÀÕ∂¡»°VOA≤®≥§÷∏¡Ó¥ÌŒÛ");
			throw ERROR_WL | dwErrorCode;
		}

	}
	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD CSantectTLSVOA::SetAttenuation(long lChIndex, double dblAtten)
{
	DWORD dwErrorCode = SUCCESS;
	char pchTemp[256];
	char bRxData[100];
	BYTE bIndex, bTxDataLength;
	double dblGetAtten;
	int nTemp = 0;

	try
	{

	    ZeroMemory(pchTemp, sizeof(pchTemp));
		sprintf(pchTemp, "POW:ATT %.3f\r\n",dblAtten);

		bTxDataLength = strlen(pchTemp);
		dwErrorCode = m_Comm.WriteDevice(pchTemp, bTxDataLength);
		if(SUCCESS != dwErrorCode)
		{
//			strcpy(m_pszGlobleMsg, "∑¢ÀÕ÷ª «VOAÀ•ºı÷∏¡Ó¥ÌŒÛ");
			throw ERROR_ATTEN | dwErrorCode;
		}

		Sleep(50);
		dwErrorCode = GetAttenuation(lChIndex, &dblGetAtten);
		if (SUCCESS != dwErrorCode)
		{
//			strcpy(m_pszGlobleMsg, "∂¡»°VOAÀ•ºı¥ÌŒÛ");
			return ERROR_ATTEN | dwErrorCode;
		}

		if (fabs(dblGetAtten - dblAtten) >= 0.1) 
		{
			return ERROR_VOA | ERROR_ATTEN;
		}
	}
	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
    
	return dwErrorCode;
}

DWORD CSantectTLSVOA::SetEnableOutput(long lChIndex, BOOL bEnable)
{
	DWORD dwErrorCode = SUCCESS;
	char szBuf[256];
	int nState = -1;
	
	try
	{
		ZeroMemory(szBuf,256);
		sprintf(szBuf,"pow:stat?\r\n");
		dwErrorCode = m_Comm.WriteDevice(szBuf,strlen(szBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_INITIAL;
		}
		
		Sleep(100);
		
		ZeroMemory(szBuf, sizeof(char)*256);
		dwErrorCode = m_Comm.ReadDevice(szBuf,256);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_INITIAL;
		}
		
		nState =atoi(szBuf);
		
		if (bEnable !=nState)
		{
			
			ZeroMemory(szBuf,sizeof(char)*256);
			sprintf(szBuf, "pow:stat %d\r\n", bEnable);
			dwErrorCode = m_Comm.WriteDevice(szBuf,strlen(szBuf));
			if (SUCCESS != dwErrorCode)
			{
				throw ERROR_INITIAL;
			}
			if (bEnable)
			{
				Sleep(40000);
			}
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR|ERROR_INITIAL;
	}

    return dwErrorCode;
}

DWORD CSantectTLSVOA::SetInputOffset(long lChIndex, double dblOffset)
{
	return SUCCESS;
}



DWORD CSantectTLSVOA::SetWavelength(long lChIndex, double dblWL)
{
	DWORD dwErrorCode = SUCCESS;
    char pchTxData[50];
	char pchRxData[100];
	BYTE bIndex, bTxDataLength;
	int	 nTemp = 0;
	double dbTempWL;

	try
	{
		ZeroMemory(pchTxData, 50);
		sprintf(pchTxData, "WAV %.2f\r\n",dblWL);

		bTxDataLength = strlen((const char *)pchTxData);

		dwErrorCode = m_Comm.WriteDevice(pchTxData, bTxDataLength);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode | ERROR_WL;
		}
        Sleep(50);
		dwErrorCode = GetWavelength(lChIndex,&dbTempWL);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode | ERROR_WL;
		}

		if(fabs(dblWL - dbTempWL) > 0.1)
		{
			throw dwErrorCode | ERROR_WL;
		}

	}
	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
    
	return dwErrorCode;
}
