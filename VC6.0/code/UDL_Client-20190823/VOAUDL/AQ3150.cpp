// AQ2200_311A.cpp: implementation of the CHp8156A class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\\include\\voa.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CAQ3150::CAQ3150()
{

}

CAQ3150::~CAQ3150()
{

}


DWORD CAQ3150::OpenDevice(char* pszDeviceAddr, unsigned long *comHandle)
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


DWORD CAQ3150::CloseDevice()
{
	DWORD	dwErrorCode = SUCCESS;
	dwErrorCode = m_Comm.CloseDevice();
	
	return dwErrorCode;
}


DWORD CAQ3150::SetHandle(char* pszDeviceAddr, unsigned long comHandle)
{
	DWORD	dwErrorCode = SUCCESS;
	
	dwErrorCode = m_Comm.SetDeviceHandle(pszDeviceAddr, comHandle);

	return dwErrorCode;
}

DWORD CAQ3150::ResetDevice()
{
	DWORD dwErrorCode = FALSE;
	char szBuffer[MAX_PATH];
	try
	{
		ZeroMemory(szBuffer,MAX_PATH);
		sprintf(szBuffer,"%s","*RST\r\n");
		dwErrorCode = m_Comm.WriteDevice(szBuffer,strlen(szBuffer));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_RESET;
		}
	}
	catch(DWORD dwError)
	{
		return ERROR_VOA | dwError;
	}
	catch(...)
	{
		return ERROR_VOA|UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD CAQ3150::GetDeviceInfo(stDevInfo *stInfo)
{
//	CHAR pszStatus[8];
//	ZeroMemory(pszStatus,8);
//	do
//	{
//		m_Comm.WriteDevice("*OPC?\r\n", strlen("*OPC?\r\n"));
//		Sleep(20);
//		m_Comm.ReadDevice(pszStatus, 8);
//	}
//	while(!strchr(pszStatus, '1'));
 
	return SUCCESS;
}

DWORD CAQ3150::SetWavelength(long lChIndex, double dblWL)
{
  	DWORD dwErrorCode = SUCCESS;
	double	dblBackWL;
	char	szCmdString[256];

	try
	{
		ZeroMemory(szCmdString, 256);
		int nWL = (int)dblWL;
		sprintf(szCmdString, "W%d", dblWL);

		//Set the wavelength
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL;
		}
		
		if(GetWavelength(1,&dblBackWL)!=SUCCESS)
		{
			return FALSE;
		}

		if(fabs(dblBackWL - dblWL) > 0.000001)
		{
			throw dwErrorCode|ERROR_WL;
		}

	}	
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
		return ERROR_VOA|dwErrorCode;
	}
	catch(...)
	{
		return ERROR_VOA|UNEXPECT_OCCUR;
	}

	return dwErrorCode;	
}

DWORD CAQ3150::GetWavelength(long lChIndex, double *dblWL)
{ 
	DWORD dwErrorCode = SUCCESS;
	TCHAR tszDataStream[32];
	char	szCmdString[256];
	
	*dblWL = 0;
	try
	{
		//Get the wavelength
		ZeroMemory(tszDataStream, 32);
		sprintf(szCmdString,"W?\r\n", lChIndex);

		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));

		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL;
		}
        ZeroMemory(tszDataStream, 32);
		dwErrorCode = m_Comm.ReadDevice(tszDataStream, 32);

		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL;
		}	
		
        ZeroMemory(szCmdString, 256);
		strncpy(szCmdString,tszDataStream,strlen(tszDataStream)-1);
		*dblWL = atof(tszDataStream); //Meter
		
	}	
	catch(DWORD dwError)
	{
		return ERROR_VOA | dwError;
	}
	catch(...)
	{
		return ERROR_VOA|UNEXPECT_OCCUR;
	}

	return dwErrorCode;	
}

DWORD CAQ3150::SetAttenuation(long lChIndex, double dblAtten)
{
	DWORD dwErrorCode = SUCCESS;
	double	dblBackAtten = 0;
	char	szCmdString[256];

	try
	{
		ZeroMemory(szCmdString, 256);
		sprintf(szCmdString, "AAV%.3f\r\n", dblAtten);

		//Set the attenuation
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_ATTEN;
		}
		
		//Get the attenuation
//		if(!GetAttenuation(1,&dblBackAtten))
//		{
//			throw dwErrorCode|ERROR_ATTEN;
//		}

//		if(fabs(dblBackAtten - dblAtten) > 0.2)
//		{
//			throw dwErrorCode|ERROR_ATTEN;
//		}

	}	
	catch(DWORD dwError)
	{
		return ERROR_VOA | dwError;
	}
	catch(...)
	{
		return ERROR_VOA|UNEXPECT_OCCUR;
	//	MessageBox(NULL,"Î´Öª´íÎó!", "ÌáÊ¾", MB_OK|MB_ICONERROR);
	}

	return dwErrorCode;	

}

DWORD CAQ3150::GetAttenuation(long lChIndex, double *dblAtten)
{
	DWORD dwErrorCode = SUCCESS;
	char tszDataStream[32];
	char  szCmdString[32];
	
	*dblAtten = 0;
	try
	{

		//Get the attenuation
		ZeroMemory(tszDataStream, 32);
		sprintf(szCmdString,"AV?\r\n");

		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));

		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_ATTEN;
		}
		ZeroMemory(tszDataStream, 32);
		dwErrorCode = m_Comm.ReadDevice(tszDataStream, 32);

		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_ATTEN;
		}	
		ZeroMemory(szCmdString,32);
		strncpy(szCmdString,tszDataStream,strlen(tszDataStream)-3);
		
		*dblAtten = atof(szCmdString); //dB		
	}	
	catch(DWORD dwError)
	{
		return ERROR_VOA | dwError;
	}
	catch(...)
	{
		return ERROR_VOA|UNEXPECT_OCCUR;
	}

	return dwErrorCode;	

}

DWORD CAQ3150::SetEnableOutput(long lChIndex, BOOL bEnable)
{
	DWORD      dwErrorCode = SUCCESS;
	char	szCmdString[256];

	try
	{
		ZeroMemory(szCmdString, 256);
		sprintf(szCmdString, "SHTR%d\r\n", bEnable);

		//Set Enable or disable
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if (SUCCESS != dwErrorCode)
		{
			if(bEnable == TRUE)
			{
				throw dwErrorCode|ERROR_ENABLE;
			}
			else
			{
				throw dwErrorCode|ERROR_DISENABLE;
			}
		}		
	}	
	catch(DWORD dwError)
	{
		return ERROR_VOA | dwError;
	}
	catch(...)
	{
		return ERROR_VOA|UNEXPECT_OCCUR;
	}

	return dwErrorCode;	
}

DWORD CAQ3150::SetInputOffset(long lChIndex, double dblOffset)
{
	DWORD dwErrorCode = SUCCESS;

	try
	{

		
	}	
	catch(DWORD dwError)
	{
		return ERROR_VOA | dwError;
	}
	catch(...)
	{
		return ERROR_VOA|UNEXPECT_OCCUR;
	}

	return dwErrorCode;	

}

DWORD CAQ3150::GetStatus(DWORD *dwStatus)
{
	DWORD dwErrorCode = SUCCESS;
	TCHAR tszDataStream[32];
	char	szCmdString[256];
	
	try
	{
		//Get the attenuation
		ZeroMemory(tszDataStream, 32);
		sprintf(szCmdString,"SHTR?");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));

		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_STATUS;
		}
		ZeroMemory(tszDataStream, 32);
		dwErrorCode = m_Comm.ReadDevice(tszDataStream, 32);

		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_STATUS;
		}	
		ZeroMemory(szCmdString,256);
        sprintf(szCmdString,"%s",tszDataStream[0]);

		*dwStatus = atoi(szCmdString);
		
	}	
	catch(DWORD dwError)
	{
		return ERROR_VOA | dwError;
	}
	catch(...)
	{
		return ERROR_VOA|UNEXPECT_OCCUR;
	}

	return dwErrorCode;	
}


BOOL CAQ3150::GetErrorMessage(DWORD dwErrorCode, char *pszErrorMsg)
{
	if (pszErrorMsg != NULL)
	{
		strcpy(pszErrorMsg, m_pszGlobleMsg);
		memset(m_pszGlobleMsg, 0, 100);
	}
	return TRUE;
}

