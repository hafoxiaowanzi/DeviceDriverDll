// Lan.cpp: implementation of the CLan class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\\include\\Communication.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLan::CLan()
{
    m_hSocket =NULL;
	defaultRM =NULL;
}

CLan::~CLan()
{
   WSACleanup( );
}
BOOL CLan::DeviceStatusOK(ViStatus viStatus)
{
	return (viStatus >= VI_SUCCESS);
}
string CLan::GetErrorMsg()
{
    return m_strErrorMsg;
}

BOOL CLan::Open(LPCTSTR lpCommunicationInfo)
{
//	sockaddr_in	sockAddr;
	LPCTSTR lpDeviceAddr = 0;
	UINT uPort = 0;
	UINT uBroadIndex = 0;
	long lInfoLen = strlen(lpCommunicationInfo);
	long lFlagCount = 0;
	char chFlag = ',';

	for (int n = 0; n < lInfoLen; n++)
	{
		if (chFlag == lpCommunicationInfo[n])
		{
			lFlagCount++;
		}
	}
	
	TCHAR		tszTok[] = ",\r\n";
	char		*pRegComment;  // single register comment 
	char pchInfo[MAX_PATH];
	char szPort[32];
	ZeroMemory(pchInfo, sizeof(pchInfo));
	ZeroMemory(szPort, 32);
	if (lInfoLen > MAX_PATH)
		return FALSE;

	memcpy(pchInfo, lpCommunicationInfo, lInfoLen);
	//broad index 
	pRegComment = strtok(pchInfo, tszTok); 
	if(pRegComment!=NULL)
	     uBroadIndex = atol(pRegComment);
	//IP Address 
	pRegComment = strtok(NULL, tszTok); 
	if(pRegComment!=NULL)
	      lpDeviceAddr = pRegComment;
	//Port
	pRegComment = strtok(NULL, tszTok);
	strcpy(szPort,pRegComment);
	//uPort = atol(pRegComment);

	//Init Ethernet 
//	BYTE byResult;
	WSADATA	wsaData;
	WORD	wVersionRequested;
	int		err;
	try
	{
		
		wVersionRequested = WINSOCK_VERSION;
		
		err = WSAStartup( wVersionRequested, &wsaData );
		if ( err != 0 ) 
		{
			return FALSE;
		}
		
		ViChar szDeviceDescriptor[VI_FIND_BUFLEN];
		//打开visa的资源管理器
		status = viOpenDefaultRM (&defaultRM);	
		if(!DeviceStatusOK(status))
			throw"Open Default RM Error";

		if(lFlagCount >3)
		{
			sprintf(szDeviceDescriptor, "TCPIP%d::%s::%s::SOCKET",uBroadIndex,lpDeviceAddr,szPort);
		}
		else
		{
			sprintf(szDeviceDescriptor, "TCPIP%d::%s::%s::INSTR",uBroadIndex,lpDeviceAddr,szPort);
		}
		
		status = viOpen(defaultRM, szDeviceDescriptor,VI_NULL, VI_NULL, &m_hSocket);
		
		if(!DeviceStatusOK(status))
			throw"Open Device By NET Error";		
	}
	catch (char* pstrMsg)
	{
		m_strErrorMsg = pstrMsg;
		return FALSE;
	}
	return TRUE;
}

BOOL CLan::Close()
{
	if (m_hSocket!=NULL)
	{
		viClose(m_hSocket);
		m_hSocket =NULL;
		viClose(defaultRM);
		defaultRM =NULL;
	}
	return TRUE;
}

BOOL CLan::Clear()
{
//	PVOID pReadBuffer[MAX_PATH];
	status = viClear(m_hSocket);
	if (!DeviceStatusOK(status)) 
	{
         m_strErrorMsg ="Clear NET Error";
		 return FALSE;
	}
	
	return TRUE;
//	if (!Read(pReadBuffer, MAX_PATH))
//	{
//		return FALSE;
//	}

	return TRUE;
}

BOOL CLan::Write(PVOID pWriteBuffer, DWORD dwWriteLength)
{
	ViUInt32 nGetLength;
	LPCSTR pszWriteBuffer = (LPSTR)pWriteBuffer;
	
	status = viWrite(m_hSocket, (unsigned char*)pWriteBuffer, dwWriteLength,&nGetLength);
	if (!DeviceStatusOK(status)) 
	{
         m_strErrorMsg ="Write Something Use NET Error";
		 return FALSE;
	}
		
	return TRUE;
}

BOOL CLan::Read(PVOID pReadBuffer, DWORD dwReadLength)
{
	//ZeroMemory(pReadBuffer, dwReadLength);
	
    ViUInt32 nGetLength = 0;
	LPCSTR pszReadBuffer = (LPSTR)pReadBuffer;
	status =  viRead(m_hSocket, (unsigned char*)pszReadBuffer, dwReadLength,&nGetLength);
	if (!DeviceStatusOK(status)) 
	{
         m_strErrorMsg ="Read Something Use NET Error";
		 return FALSE;
	}

	return TRUE;
}

BOOL CLan::SerialPoll(PCHAR pbSPByte)
{
	return TRUE;
}
 
BOOL CLan::WaitForCompletion(WORD wMask)
{
	return TRUE;
}

BOOL CLan::GetError(PSTR pszErrorMessage)
{
	return TRUE;
}

BOOL CLan::IsRequestCompleted()
{

	return TRUE;
}

void CLan::SetHandle(unsigned long pHandle)
{
	m_hSocket = (ViSession)pHandle;
}