// Op8169.cpp: implementation of the Op8169 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\\include\\SwitchDll.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COMS_1X64SW::COMS_1X64SW()
{

}

COMS_1X64SW::~COMS_1X64SW()
{

}

/////////////////////////////////////////////////////////////
//函数说明：
//    打开设备
//Add by wanxin
//20140821
//////////////////////////////////////////////////////////////
DWORD COMS_1X64SW::OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle)
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
DWORD COMS_1X64SW::CloseDevice()
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
DWORD COMS_1X64SW::SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle)
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
DWORD COMS_1X64SW::GetDeviceInfo(stDevInfo *stInfo)
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
		return ERROR_PDLD | dwError;
	}
	catch(...)
	{
		return ERROR_PDLD|UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}
/////////////////////////////////////////////////////////////
//函数说明：
//    设置相应通道
//Add by wanxin
//20140821
//////////////////////////////////////////////////////////////
DWORD  COMS_1X64SW::SwitchPort2Port(int nInputPort, int nOutputPort)
{
	DWORD dwErrorCode;
	char szBuffer[MAX_PATH];
	try
	{	

		if(nInputPort!=1)
		{
			throw ERROR_SWITCHINPUTPORTRANGE;
		}

		if(nOutputPort<1 || nOutputPort >64)
		{
			throw ERROR_SWITCHOUTPUTPORTRANGE;
		}

        int nTempOutPutPort = nOutputPort - 1;
		ZeroMemory(szBuffer,MAX_PATH);		
		sprintf(szBuffer,"set:0:sw:0::channel=%d;",nTempOutPutPort);
		dwErrorCode = m_DevComHandle.WriteDevice(szBuffer,strlen(szBuffer));
		if(dwErrorCode!=SUCCESS)
		{
			throw dwErrorCode;
		}
		Sleep(50);
	    dwErrorCode = m_DevComHandle.ReadDevice(szBuffer,MAX_PATH);
		if(dwErrorCode!=SUCCESS)
		{
			throw dwErrorCode;
		}	
	}
	catch(DWORD dwError)
	{
		return ERROR_PDLD | dwError;
	}
	catch(...)
	{
		return ERROR_PDLD|UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

