// Op8169.cpp: implementation of the Op8169 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\\include\\SwitchDll.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIT_1X8SW::CIT_1X8SW()
{

}

CIT_1X8SW::~CIT_1X8SW()
{

}

/////////////////////////////////////////////////////////////
//函数说明：
//    打开设备
//Add by wanxin
//20140821
//////////////////////////////////////////////////////////////
DWORD CIT_1X8SW::OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle)
{
	//CString strComPort;	
	DWORD   dwErrorCode = FALSE;

	dwErrorCode = m_DevComHandle.OpenDevice(pszDeviceAddr,*ComHandle);
	if (dwErrorCode != SUCCESS)
	{
		return dwErrorCode;
	}	
	return dwErrorCode;
}
/////////////////////////////////////////////////////////////
//函数说明：
//    关闭设备
//Add by wanxin
//20140821
//////////////////////////////////////////////////////////////
DWORD CIT_1X8SW::CloseDevice()
{
	DWORD   dwErrorCode;
	dwErrorCode = m_DevComHandle.CloseDevice();
	if (dwErrorCode!=SUCCESS)
	{
		return dwErrorCode;
	}
	return dwErrorCode;
}
/////////////////////////////////////////////////////////////
//函数说明：
//    设置设备句柄指针
//Add by wanxin
//20140821
//////////////////////////////////////////////////////////////
DWORD CIT_1X8SW::SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle)
{
	DWORD   dwErrorCode=0;
//	LPCTSTR lpCommunicationInfo;
    
	dwErrorCode = m_DevComHandle.SetDeviceHandle(pszDeviceAddr, handle);
	return dwErrorCode;
}
/////////////////////////////////////////////////////////////
//函数说明：
//    获得设备信息
//Add by wanxin
//20140821
//////////////////////////////////////////////////////////////
DWORD CIT_1X8SW::GetDeviceInfo(stDevInfo *stInfo)
{
	DWORD dwErrorCode = FALSE;
	try
	{
//		dwErrorCode = m_DevComHandle.WriteDevice("*IDN?\r\n",strlen("*IDN?\r\n"));
//		if(SUCCESS != dwErrorCode)
//		{
//			throw dwErrorCode|ERROR_RESET;
//		}

	}
	catch(DWORD dwError)
	{
		return ERROR_SWITCH | dwError;
	}
	catch(...)
	{
		return ERROR_SWITCH|UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}


DWORD  CIT_1X8SW::SwitchPort2Port(int nInputPort, int nOutputPort)
{
	DWORD dwErrorCode=SUCCESS;
	char szSendBuffer[MAX_PATH];
	try
	{
		ZeroMemory(szSendBuffer,MAX_PATH);
		if(nOutputPort==2)
		{
			szSendBuffer[0]=0x2A;
  
		}
		else if(nOutputPort==1)
		{

		}
		
		
// 		dwErrorCode = m_DevComHandle.WriteDevice((char*)szSendBuffer,MAX_PATH);
// 		if (dwErrorCode!=SUCCESS)
// 		{
// 			throw ERROR_SWITCHSELECT;
// 		}
// 	
// 		Sleep(100);
// 		dwErrorCode = m_DevComHandle.ReadDevice((char*)szSendBuffer,MAX_PATH);
// 		if (dwErrorCode!=SUCCESS)
// 		{
// 			throw ERROR_SWITCHSELECT;
// 		}	

		if(nOutputPort==1)
		{

		}
		else if(nOutputPort==2)
		{
	
		}		
	}
	catch(DWORD dwError)
	{
		return ERROR_SWITCH | dwError;
	}
	catch(...)
	{
		return ERROR_SWITCH|UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

