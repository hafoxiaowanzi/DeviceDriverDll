// Op8169.cpp: implementation of the Op8169 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\\include\\SwitchDll.h"
#include "math.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIT_1X2SW::CIT_1X2SW()
{

}

CIT_1X2SW::~CIT_1X2SW()
{

}
/////////////////////////////////////////////////////////////
//函数说明：
//    打开设备
//Add by wanxin
//20140821
//////////////////////////////////////////////////////////////
DWORD CIT_1X2SW::OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle)
{
	//CString strComPort;	
	DWORD   dwErrorCode;

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
DWORD CIT_1X2SW::CloseDevice()
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
DWORD CIT_1X2SW::SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle)
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
DWORD CIT_1X2SW::GetDeviceInfo(stDevInfo *stInfo)
{
	DWORD dwErrorCode = FALSE;
	try
	{

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

DWORD  CIT_1X2SW::SwitchPort2Port(int nInputPort, int nOutputPort)
{
	DWORD dwErrorCode;
	char szSendBuffer[MAX_PATH];
	try
	{
		ZeroMemory(szSendBuffer,MAX_PATH);
		////2A 30 30 30 39 30 31 30 32 30 30 30 30 4D 0D
		if(nOutputPort==2)
		{
			szSendBuffer[0]=0x2A;
			szSendBuffer[1]=0x30;
			szSendBuffer[2]=0x30;
			szSendBuffer[3]=0x30;
			szSendBuffer[4]=0x39;
			szSendBuffer[5]=0x30;
			szSendBuffer[6]=0x32;
			szSendBuffer[7]=0x30;
			szSendBuffer[8]=0x32;
			szSendBuffer[9]=0x30;
			szSendBuffer[10]=0x30;
			szSendBuffer[11]=0x30;
			szSendBuffer[12]=0x30;
			szSendBuffer[13]=0x4D;
			szSendBuffer[14]=0x0D;	   
		}
		else if(nOutputPort==1)
		{
			////2A 30 30 30 39 30 31 30 31 30 30 30 30 4B 0D
			szSendBuffer[0]=0x2A;
			szSendBuffer[1]=0x30;
			szSendBuffer[2]=0x30;
			szSendBuffer[3]=0x30;
			szSendBuffer[4]=0x39;
			szSendBuffer[5]=0x30;
			szSendBuffer[6]=0x31;
			szSendBuffer[7]=0x30;
			szSendBuffer[8]=0x31;
			szSendBuffer[9]=0x30;
			szSendBuffer[10]=0x30;
			szSendBuffer[11]=0x30;
			szSendBuffer[12]=0x30;
			szSendBuffer[13]=0x4B;
			szSendBuffer[14]=0x0D;
		}
		

		if(nInputPort !=1)
		{
			throw ERROR_SWITCHINPUTPORTRANGE;
		}

		if(nOutputPort < 1 || nOutputPort > 2)
		{
			throw ERROR_SWITCHOUTPUTPORTRANGE;
		}
		
		dwErrorCode = m_DevComHandle.WriteDevice((char*)szSendBuffer,MAX_PATH);
		if (dwErrorCode!=SUCCESS)
		{
			throw ERROR_SWITCHSELECT;
		}
	
		Sleep(100);
		dwErrorCode = m_DevComHandle.ReadDevice((char*)szSendBuffer,MAX_PATH);
		if (dwErrorCode!=SUCCESS)
		{
			throw ERROR_SWITCHSELECT;
		}	

		if(nOutputPort==1)
		{
			if (szSendBuffer[13]!=0x4C && szSendBuffer[14]!=0x5E)
			{
				throw ERROR_SWITCHSELECT;
			}
		}
		else if(nOutputPort==2)
		{
			if (szSendBuffer[13]!=0x4E && szSendBuffer[14]!=0x5E)
			{
				throw ERROR_SWITCHSELECT;
			}	
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