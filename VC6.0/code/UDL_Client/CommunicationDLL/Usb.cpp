// Usb.cpp: implementation of the CUsb class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\\include\\Communication.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUsb::CUsb()
{
	m_strErrorMsg=_T("");
}

CUsb::~CUsb()
{
	
}
string CUsb::GetErrorMsg()
{
    return m_strErrorMsg;
}

BOOL CUsb::Open(LPCTSTR lpCommunicationInfo)
{
	
	long lUsbIndex = 0;
	long lInfoLen = strlen(lpCommunicationInfo);
	long lFlagCount = 0;
	char chFlag = ',';
	TCHAR		tszTok[] = ",\r\n";
	char		*pRegComment;  // single register comment 
	char pchInfo[MAX_PATH];
	ZeroMemory(pchInfo, sizeof(pchInfo));
	
	
	try
	{
		if (lInfoLen > MAX_PATH)
			throw"Address String Error";
		
		memcpy(pchInfo, lpCommunicationInfo, lInfoLen);
		//USB Index 
		pRegComment = strtok(pchInfo, tszTok); 
		lUsbIndex = atol(pRegComment);
		
		ViChar szDeviceDescriptor[VI_FIND_BUFLEN];
		//打开visa的资源管理器
		status = viOpenDefaultRM (&defaultRM);	
		if(!DeviceStatusOK(status))
			throw"Open Default RM Error";
		
		sprintf(szDeviceDescriptor, "USB%d::INSTR", lUsbIndex);
		
		status = viOpen(defaultRM, szDeviceDescriptor,VI_NULL, VI_NULL, &m_usb);
		
		if(!DeviceStatusOK(status))
			throw"Open Device By USB Error";		
	}
	catch (char *pstrMsg)
	{
		m_strErrorMsg = pstrMsg;
		return FALSE;
	}
    return TRUE;
}

BOOL CUsb::Close()
{
	
	return TRUE;
}

BOOL CUsb::Clear()
{
	status = viClear(m_usb);
	if(!DeviceStatusOK(status))
	{
		m_strErrorMsg ="Clear Device Error";
		return FALSE;
	}
	
	return TRUE;
}

BOOL CUsb::Write(PVOID pWriteBuffer, DWORD dwWriteLength)
{
	LPCSTR pszWriteBuffer = (LPSTR)pWriteBuffer;
	DWORD nGetLength = 0;
	
	status = viWrite(m_usb, (unsigned char *)pszWriteBuffer, dwWriteLength, &nGetLength);
	if(!DeviceStatusOK(status))
	{
        m_strErrorMsg ="Write Something By USB Error";
		return FALSE;
	}
	
	return TRUE;
}

BOOL CUsb::Read(PVOID pReadBuffer, DWORD dwReadLength)
{
	
	DWORD nGetLength = 0;
	ZeroMemory(pReadBuffer, dwReadLength);
	
	status = viRead(m_usb, (unsigned char *)pReadBuffer, dwReadLength, &nGetLength);

	if(!DeviceStatusOK(status))
	{
        m_strErrorMsg ="Read Something By USB Error";
		return FALSE;
	}
	
	return TRUE;
}

void CUsb::SetHandle(unsigned long pHandle)
{
	m_usb = (ViSession)pHandle;
}