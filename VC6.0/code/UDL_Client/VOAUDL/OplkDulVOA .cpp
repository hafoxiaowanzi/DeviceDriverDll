// OplkMEMSVOA.cpp: implementation of the COplkMEMSVOA class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\\include\\voa.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COplkDulVOA::COplkDulVOA()
{
//	m_hCommPort = INVALID_HANDLE_VALUE;
//	m_Comm = NULL;
//	m_Comm = new CCommunicationDLL;
}

COplkDulVOA::~COplkDulVOA()
{
//	delete m_Comm;
//	m_Comm = NULL;
}

DWORD COplkDulVOA::OpenDevice(char* pszDeviceAddr, unsigned long *comHandle)
{
	DWORD dwErrorCode = SUCCESS;

    try
	{
		dwErrorCode = m_Comm.OpenDevice(pszDeviceAddr, *comHandle);
		if (SUCCESS != dwErrorCode)
		{
			return ERROR_VOA | dwErrorCode;
		}
	}
	catch(...)
	{
		return UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD COplkDulVOA::CloseDevice()
{
	DWORD	dwErrorCode = SUCCESS;
	dwErrorCode = m_Comm.CloseDevice();
	
	return dwErrorCode;
}

DWORD COplkDulVOA::SetHandle(char* pszDeviceAddr, unsigned long comHandle)
{
	DWORD	dwErrorCode = SUCCESS;
	
	dwErrorCode = m_Comm.SetDeviceHandle(pszDeviceAddr, comHandle);

	return dwErrorCode;
}

DWORD COplkDulVOA::GetAttenuation(long lChIndex, double *dblAtten)
{
	DWORD dwErrorCode = SUCCESS;
    char pchTxData[50];
	char pchRxData[100];
	BYTE bIndex;
	CHAR pchTemp[256];

	try
	{
		ZeroMemory(pchTxData, 50);
		sprintf(pchTxData, "ATTEN %d\r\n",lChIndex);
		// 写读取衰减的命令
		dwErrorCode = m_Comm.WriteDevice(pchTxData, 7);
		if(SUCCESS != dwErrorCode)
		{
//			strcpy(m_pszGlobleMsg, "写VOA指令错误");
			throw dwErrorCode | ERROR_ATTEN;
		}

		ZeroMemory(pchRxData, 32);
		
		bIndex = 0;
		while(bIndex < 10)
		{
			Sleep(30);
			// 读取衰减
			dwErrorCode = m_Comm.ReadDevice(pchRxData, 20);
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
		if (bIndex == 10)
		{
//			strcpy(m_pszGlobleMsg, "读VOA数据错误");
			throw dwErrorCode | ERROR_ATTEN;
		}

		ZeroMemory(pchTemp, 256);
		// 数据处理
		for(int i=10, j = 0; pchRxData[i] != '\r' && i<16; i++)
		{
			pchTemp[j] = pchRxData[i];
			j++;
		}

		*dblAtten = atof(pchTemp);
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

DWORD COplkDulVOA::GetDeviceInfo(stDevInfo *stInfo)
{
	DWORD dwErrorCode = SUCCESS;
	char pchTxData[50];
	char pchRxData[100];
	BYTE bIndex, byComLen;

	try
	{
		ZeroMemory(pchTxData, 50);
		sprintf(pchTxData, "INFO\r\n");
		byComLen = strlen(pchTxData);

		// Send 'INFO' command to VOA device
		dwErrorCode = m_Comm.WriteDevice(pchTxData, byComLen);
		if(SUCCESS != dwErrorCode)
		{
			//strcpy(m_pszGlobleMsg, "发送获取VOA设备信息指令错误");
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
			//strcpy(m_pszGlobleMsg, "读VOA设备信息错误");
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

BOOL COplkDulVOA::GetErrorMessage(DWORD dwErrorCode, char *pszErrorMsg)
{
	if (pszErrorMsg != NULL)
	{
//		strcpy(pszErrorMsg, m_pszGlobleMsg);
//		memset(m_pszGlobleMsg, 0, 100);
	}
	return TRUE;
}

DWORD COplkDulVOA::GetStatus(DWORD *dwStatus)
{
	//{"INFO", "SN", "TEMP", "MONVOL", "ATTEN", "CHMODE", "WAVEFORM", "INPWR", "OUTPWR"};
	*dwStatus = 0;
	return SUCCESS;
}

DWORD COplkDulVOA::GetWavelength(long lChIndex, double *dblWL)
{
	DWORD dwErrorCode = SUCCESS;
	char pchTxData[50], pchRxData[100];
	char pchTemp[256];
	BYTE bIndex, bTxDataLength;
	int	 nTemp = 0;

	try
	{
		ZeroMemory(pchTxData, 50);
		sprintf(pchTxData, "WAVEFORM %d\r\n",lChIndex);

		bTxDataLength = strlen((const char *)pchTxData);

		dwErrorCode = m_Comm.WriteDevice(pchTxData, bTxDataLength);
		if(SUCCESS != dwErrorCode)
		{
//			strcpy(m_pszGlobleMsg, "发送读取VOA波长指令错误");
			throw ERROR_WL | dwErrorCode;
		}

		ZeroMemory(pchRxData, 32);
		
		bIndex = 0;
		while(bIndex < 10)
		{
			dwErrorCode = m_Comm.ReadDevice(pchRxData, 20);
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
//			strcpy(m_pszGlobleMsg, "读取VOA波长错误");
			throw ERROR_WL | dwErrorCode;
		}

		ZeroMemory(pchTemp, 256);
		for(int i=9, j = 0; pchRxData[i] != '\r' && i<16; i++)
		{
			pchTemp[j] = pchRxData[i];
			j++;
		}

		*dblWL = atof(pchTemp);
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

DWORD COplkDulVOA::ResetDevice()
{
	return SetAttenuation(1, 0.0);
}

DWORD COplkDulVOA::SetAttenuation(long lChIndex, double dblAtten)
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
		sprintf(pchTemp, "CHMODE %d CA\r\n",lChIndex,dblAtten);

		bTxDataLength = strlen(pchTemp);
		dwErrorCode = m_Comm.WriteDevice(pchTemp, bTxDataLength);
		if(SUCCESS != dwErrorCode)
		{
//			strcpy(m_pszGlobleMsg, "发送只是VOA衰减指令错误");
			throw ERROR_ATTEN | dwErrorCode;
		}

		ZeroMemory(pchTemp, sizeof(pchTemp));
		sprintf(pchTemp, "ATTEN %d %.2f\r\n",lChIndex,dblAtten);

		bTxDataLength = strlen(pchTemp);
		dwErrorCode = m_Comm.WriteDevice(pchTemp, bTxDataLength);
		if(SUCCESS != dwErrorCode)
		{
//			strcpy(m_pszGlobleMsg, "发送只是VOA衰减指令错误");
			throw ERROR_ATTEN | dwErrorCode;
		}

		ZeroMemory(bRxData, 32);
		
		bIndex = 0;
		while(bIndex < 150)
		{
			dwErrorCode = m_Comm.ReadDevice(bRxData, 10);
			if(SUCCESS != dwErrorCode)
			{
				bIndex ++;
				continue;
			}
			else
				break;
		}

		Sleep(20);
		dwErrorCode = GetAttenuation(lChIndex, &dblGetAtten);
		if (SUCCESS != dwErrorCode)
		{
//			strcpy(m_pszGlobleMsg, "读取VOA衰减错误");
			return ERROR_ATTEN | dwErrorCode;
		}

		if (fabs(dblGetAtten - dblAtten) >= 0.1) 
		{
//			sprintf(m_pszGlobleMsg, "设置衰减 %.2f 失败!", dblAtten);
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

DWORD COplkDulVOA::SetEnableOutput(long lChIndex, BOOL bEnable)
{
	return SUCCESS;
}

DWORD COplkDulVOA::SetInputOffset(long lChIndex, double dblOffset)
{
	return SUCCESS;
}
BOOL COplkDulVOA::SetWorkMode(long lChIndex,int nWorkMode,double dbValue)
{

	return TRUE;
}
DWORD COplkDulVOA::SetWavelength(long lChIndex, double dblWL)
{
	DWORD dwErrorCode = SUCCESS;
    char pchTxData[50];
	char pchRxData[100];
	BYTE bIndex, bTxDataLength;
	int	 nTemp = 0;

	try
	{
		ZeroMemory(pchTxData, 50);
		sprintf(pchTxData, "WAVEFORM %d %.2f\r\n",lChIndex,dblWL);

		bTxDataLength = strlen((const char *)pchTxData);

		dwErrorCode = m_Comm.WriteDevice(pchTxData, bTxDataLength);
		if(SUCCESS != dwErrorCode)
		{
//			strcpy(m_pszGlobleMsg, "设置VOA波长指令错误");
			throw dwErrorCode | ERROR_WL;
		}

		ZeroMemory(pchRxData, 32);
		
		bIndex = 0;
		while(bIndex < 150)
		{
			dwErrorCode = m_Comm.ReadDevice(pchRxData, 10);
			if(SUCCESS != dwErrorCode)
			{
				bIndex ++;
				continue;
			}
			else
				break;
		}
		if (bIndex == 150)
		{
//			strcpy(m_pszGlobleMsg, "设置波长后获取VOA反馈信息错误");
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
