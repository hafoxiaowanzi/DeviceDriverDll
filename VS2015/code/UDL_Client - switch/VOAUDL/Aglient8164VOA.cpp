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


CVOA_Aglient8164::CVOA_Aglient8164()
{

}

CVOA_Aglient8164::~CVOA_Aglient8164()
{

}

/************************************************************************
*  函数名称:OpenDevice													*
*  功能: 打开连接设备													*
*  输入:																*
*		1.stType:设备类型结构体											*
*       2.pszDeviceAddr:通讯信息										*
*  输出数据类型:stDevType, char* 										*
*  输出:																*
*       comHandle:基础通讯接口Handle									*
*  输出数据类型:CommunicationHandle										*
*  返回值:																*
*             0: 函数执行成功。											*
*    0x80000012: 其他错误												*
*  返回值类型:DWORD														*
*  创建日期:2013-09-07													*
*  创建人:赵寒飞														*
*  修改：刘珍宏	Oct 23,2013												*
*************************************************************************/
DWORD CVOA_Aglient8164::OpenDevice(char* pszDeviceAddr, unsigned long *comHandle)
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
*  函数名称: CloseDevice												*
*  功能:     关闭设备													*
*  输入: 无																*
*																		*
*  输入数据类型: 无														*
*  输出: 无																*
*  输出数据类型: 无												 		*
*  返回值:																*
*             0: 函数执行成功。											*
*    0x80000012: 其他错误												*
*  返回值类型:DWORD														*
*  创建日期:2013-09-07													*
*  创建人:赵寒飞														*
*  修改：刘珍宏	Oct 23,2013												*
*************************************************************************/
DWORD CVOA_Aglient8164::CloseDevice()
{
	DWORD	dwErrorCode = SUCCESS;
	dwErrorCode = m_Comm.CloseDevice();
	
	return dwErrorCode;
}

/************************************************************************
*  函数名称: SetHandle													*
*  功能: 设置打开设备的句柄												*
*  输入:																*
*		1.stType:设备类型结构体											*
*       2.hHandle:句柄													*
*  输入数据类型:stDevType, HANDLE 										*
*  输出:																*
*       无																*
*  输出数据类型:无														*
*  返回值:																*
*             0: 函数执行成功。											*
*    0x80000012: 其他错误												*
*  返回值类型:DWORD														*
*  创建日期:2013-11-05													*
*  创建人: Xianjun Wang													*
*  修改：																*
*************************************************************************/
DWORD CVOA_Aglient8164::SetHandle(char* pszDeviceAddr, unsigned long comHandle)
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
DWORD CVOA_Aglient8164::ResetDevice()
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
void CVOA_Aglient8164::CompleteRequest()
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
DWORD CVOA_Aglient8164::GetDeviceInfo(stDevInfo *stInfo)
{
	CHAR pszStatus[8];
	ZeroMemory(pszStatus,8);
	do
	{
		m_Comm.WriteDevice("*IDN?\r\n", strlen("*IDN?\r\n"));
		Sleep(20);
		m_Comm.ReadDevice(pszStatus, 8);
	}
	while(!strchr(pszStatus, '1'));
 
	return false;
}

DWORD CVOA_Aglient8164::SetWavelength(long lChIndex, double dblWL)
{
  	DWORD dwErrorCode = SUCCESS;
	double	dblBackWL;
	char	szCmdString[256];

	try
	{
		ZeroMemory(szCmdString, 256);
		sprintf(szCmdString, "wav %.3fnm\r\n", dblWL);

		//Set the wavelength
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL;
		}

		CompleteRequest();
		
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

DWORD CVOA_Aglient8164::GetWavelength(long lChIndex, double *dblWL)
{ 
	DWORD dwErrorCode = SUCCESS;
	TCHAR tszDataStream[32];
	char	szCmdString[256];
	
	*dblWL = 0;
	try
	{
		//Get the wavelength
		ZeroMemory(tszDataStream, 32);
		sprintf(szCmdString,"SOUR0:WAV?\r\n");

		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));

		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL;
		}
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

DWORD CVOA_Aglient8164::SetAttenuation(long lChIndex, double dblAtten)
{
	DWORD dwErrorCode = SUCCESS;
	double	dblBackAtten = 0;
	char	szCmdString[256];

	try
	{
		ZeroMemory(szCmdString, 256);
		sprintf(szCmdString, "SOUR0:POW:ATT %.5fdB\r\n", dblAtten);

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
	//	MessageBox(NULL,"未知错误!", "提示", MB_OK|MB_ICONERROR);
	}

	return dwErrorCode;	

}

DWORD CVOA_Aglient8164::GetAttenuation(long lChIndex, double *dblAtten)
{
	DWORD dwErrorCode = SUCCESS;
	TCHAR tszDataStream[32];
	char	szCmdString[256];
	
	*dblAtten = 0;
	try
	{
		//Get the attenuation
		ZeroMemory(tszDataStream, 32);
		sprintf(szCmdString,"SOUR0:POW:ATT?\r\n");

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

DWORD CVOA_Aglient8164::SetEnableOutput(long lChIndex, BOOL bEnable)
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

DWORD CVOA_Aglient8164::SetInputOffset(long lChIndex, double dblOffset)
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

DWORD CVOA_Aglient8164::GetStatus(DWORD *dwStatus)
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


BOOL CVOA_Aglient8164::GetErrorMessage(DWORD dwErrorCode, char *pszErrorMsg)
{
	if (pszErrorMsg != NULL)
	{
		strcpy(pszErrorMsg, m_pszGlobleMsg);
		memset(m_pszGlobleMsg, 0, 100);
	}
	return TRUE;
}

