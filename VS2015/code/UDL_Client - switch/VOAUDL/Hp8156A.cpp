// Hp8156A.cpp: implementation of the CHp8156A class.
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


CVOA_HP8156X::CVOA_HP8156X()
{

}

CVOA_HP8156X::~CVOA_HP8156X()
{

}

/************************************************************************
*  ��������:OpenDevice													*
*  ����: �������豸													*
*  ����:																*
*		1.stType:�豸���ͽṹ��											*
*       2.pszDeviceAddr:ͨѶ��Ϣ										*
*  �����������:stDevType, char* 										*
*  ���:																*
*       comHandle:����ͨѶ�ӿ�Handle									*
*  �����������:CommunicationHandle										*
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*    0x80000012: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-07													*
*  ������:�Ժ���														*
*  �޸ģ������	Oct 23,2013												*
*************************************************************************/
DWORD CVOA_HP8156X::OpenDevice(char* pszDeviceAddr, unsigned long *comHandle)
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

/************************************************************************
*  ��������: CloseDevice												*
*  ����:     �ر��豸													*
*  ����: ��																*
*																		*
*  ������������: ��														*
*  ���: ��																*
*  �����������: ��												 		*
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*    0x80000012: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-07													*
*  ������:�Ժ���														*
*  �޸ģ������	Oct 23,2013												*
*************************************************************************/
DWORD CVOA_HP8156X::CloseDevice()
{
	DWORD	dwErrorCode = SUCCESS;
	dwErrorCode = m_Comm.CloseDevice();
	
	return dwErrorCode;
}

/************************************************************************
*  ��������: SetHandle													*
*  ����: ���ô��豸�ľ��												*
*  ����:																*
*		1.stType:�豸���ͽṹ��											*
*       2.hHandle:���													*
*  ������������:stDevType, HANDLE 										*
*  ���:																*
*       ��																*
*  �����������:��														*
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*    0x80000012: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-11-05													*
*  ������: Xianjun Wang													*
*  �޸ģ�																*
*************************************************************************/
DWORD CVOA_HP8156X::SetHandle(char* pszDeviceAddr, unsigned long comHandle)
{
	DWORD	dwErrorCode = SUCCESS;
	
	dwErrorCode = m_Comm.SetDeviceHandle(pszDeviceAddr, comHandle);

	return dwErrorCode;
}

/********************************************************************************
* Function Name: ResetOSA														*
* Function:	Executes a device reset to return the instrument					*
			to the known (default) status.										*
* Input:																		*
*		None																	*
* Output:																		*
*		None																	*
* Return Value:																	*
*		0. Reset OSA fail														*
*		1. Reset OSA successful													*
* Return Type: BOOL																*
* Create Data: 2011-03-17														*
* Creator:  MaoLu																*
* Revision History: None														*
*********************************************************************************/
DWORD CVOA_HP8156X::ResetDevice()
{
	DWORD dwErrorCode = FALSE;
	try
	{
		dwErrorCode = m_Comm.WriteDevice("*RST\r\n",strlen("*RST\r\n"));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_RESET;
		}
		CompleteRequest();
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

/********************************************************************************
* Function Name: CompleteRequest												*
* Function:	 Check if the OSA busy												*
* Input:																		*
*		None																	*
* Output:																		*
*		None																	*
* Return Value:																	*
*		None																	*
* Return Type: VOID																*
* Create Data: 2011-03-15														*
* Creator: MaoLu 																*
* Revision History: None														*
*********************************************************************************/
void CVOA_HP8156X::CompleteRequest()
{
	CHAR pszStatus[8];
	ZeroMemory(pszStatus,8);
	do
	{
		m_Comm.WriteDevice("*OPC?\r\n", strlen("*OPC?\r\n"));
		Sleep(20);
		m_Comm.ReadDevice(pszStatus, 8);
	}
	while(!strchr(pszStatus, '1'));
}

/********************************************************************************
* Function Name: GetDeviceInfo													*
* Function:	 get the basic information of instrument							*
* Input:																		*
*		None																	*
* Output:																		*
*		None																	*
* Return Value:																	*
*		None																	*
* Return Type: VOID																*
* Create Data: 2011-10-23														*
* Creator: Luke Liu																*
* Revision History: None														*
*********************************************************************************/
DWORD CVOA_HP8156X::GetDeviceInfo(stDevInfo *stInfo)
{
	DWORD dwErrorCode = SUCCESS;
	char	szCmdString[256];
	
	try
	{
		//Get the wavelength
		ZeroMemory(szCmdString, 256);
		sprintf(szCmdString,"*IDN?");

		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));

		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL;
		}
		Sleep(50);
		ZeroMemory(szCmdString, 256);
		dwErrorCode = m_Comm.ReadDevice(szCmdString, 256);

		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL;
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

DWORD CVOA_HP8156X::SetWavelength(long lChIndex, double dblWL)
{
  	DWORD dwErrorCode = SUCCESS;
	double	dblBackWL;
	char	szCmdString[256];

	try
	{
		ZeroMemory(szCmdString, 256);
		sprintf(szCmdString, "INP:WAV %.5fnm", dblWL);

		//Set the wavelength
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL;
		}

		CompleteRequest();
		Sleep(100);
		//Get the wavelength
		if(!GetWavelength(1,&dblBackWL))
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

DWORD CVOA_HP8156X::GetWavelength(long lChIndex, double *dblWL)
{ 
	DWORD dwErrorCode = SUCCESS;
	TCHAR tszDataStream[32];
	char	szCmdString[256];
	
	*dblWL = 0;
	try
	{
		//Get the wavelength
		ZeroMemory(szCmdString, 256);
		sprintf(szCmdString,"INP:WAV?");

		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));

		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL;
		}
		Sleep(50);
		ZeroMemory(tszDataStream, 32*sizeof(TCHAR));
		dwErrorCode = m_Comm.ReadDevice(tszDataStream, 32);

		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL;
		}	
		
		*dblWL = atof(tszDataStream); //Meter
		*dblWL *= pow(10, 9);

		CompleteRequest();
		
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

DWORD CVOA_HP8156X::SetAttenuation(long lChIndex, double dblAtten)
{
	DWORD dwErrorCode = SUCCESS;
	double	dblBackAtten = 0;
	char	szCmdString[256];

	try
	{
		ZeroMemory(szCmdString, 256);
		sprintf(szCmdString, "INP:ATT %.5fdB\r\n", dblAtten);

		//Set the attenuation
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_ATTEN;
		}

		CompleteRequest();
		
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
	//	MessageBox(NULL,"δ֪����!", "��ʾ", MB_OK|MB_ICONERROR);
	}

	return dwErrorCode;	

}

DWORD CVOA_HP8156X::GetAttenuation(long lChIndex, double *dblAtten)
{
	DWORD dwErrorCode = SUCCESS;
	TCHAR tszDataStream[32];
	char	szCmdString[256];
	
	*dblAtten = 0;
	try
	{
		//Get the attenuation
		ZeroMemory(tszDataStream, 32);
		sprintf(szCmdString,"INP:ATT?\r\n");

		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));

		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_ATTEN;
		}
		dwErrorCode = m_Comm.ReadDevice(tszDataStream, 32);

		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_ATTEN;
		}	
		
		*dblAtten = atof(tszDataStream); //dB

		CompleteRequest();
		
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

DWORD CVOA_HP8156X::SetEnableOutput(long lChIndex, BOOL bEnable)
{
	DWORD      dwErrorCode = SUCCESS;
	char	szCmdString[256];

	try
	{
		ZeroMemory(szCmdString, 256);
		sprintf(szCmdString, "OUTP %d\r\n", bEnable);

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

		CompleteRequest();
		
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

DWORD CVOA_HP8156X::SetInputOffset(long lChIndex, double dblOffset)
{
	DWORD dwErrorCode = SUCCESS;
	char	szCmdString[256];

	try
	{
		ZeroMemory(szCmdString, 256);
		sprintf(szCmdString, "INP:OFFS %.4f", dblOffset);

		//Set the wavelength
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_ATTEN_OFFSET;
		}

		CompleteRequest();
		
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

DWORD CVOA_HP8156X::GetStatus(DWORD *dwStatus)
{
	DWORD dwErrorCode = SUCCESS;
	TCHAR tszDataStream[32];
	char	szCmdString[256];
	
	try
	{
		//Get the attenuation
		ZeroMemory(tszDataStream, 32);
		sprintf(szCmdString,"OUTP?");
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));

		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_STATUS;
		}
		dwErrorCode = m_Comm.ReadDevice(tszDataStream, 32);

		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_STATUS;
		}	
        
		CompleteRequest();

		*dwStatus = atoi(tszDataStream);
		
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


BOOL CVOA_HP8156X::GetErrorMessage(DWORD dwErrorCode, char *pszErrorMsg)
{
	if (pszErrorMsg != NULL)
	{
		strcpy(pszErrorMsg, m_pszGlobleMsg);
		memset(m_pszGlobleMsg, 0, 100);
	}
	return TRUE;
}

