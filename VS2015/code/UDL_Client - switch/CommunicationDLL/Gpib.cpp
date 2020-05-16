// Gpib.cpp: implementation of the CGpib class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\\include\\Communication.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGpib::CGpib()
{ 
	defaultRM =NULL;
	m_hGPIB = NULL;
	m_strErrorMsg =_T("");
}


CGpib::~CGpib()
{
	if (m_hGPIB ==NULL)
	{
		viClose(m_hGPIB);
	}
	if(defaultRM != NULL)
	{
		viClose(defaultRM);
	}

}

BOOL CGpib::DeviceStatusOK(ViStatus viStatus)
{
	return (viStatus >= VI_SUCCESS);
}

string CGpib::GetErrorMsg()
{
    return m_strErrorMsg;
}
 

BOOL CGpib::Open(LPCTSTR lpCommunicationInfo)
{
	LONG lPrimaryAddress = 0;
	LONG lSecondAddress = 0;
	LONG lBoardIndex = 0; 
	long lFlagCount = 0;
	char chFlag = ',';
	ViChar szDeviceDescriptor[VI_FIND_BUFLEN];
	TCHAR		tszTok[] = ",\r\n";
	char		*pRegComment;  // single register comment 
	char pchInfo[MAX_PATH];
	ZeroMemory(pchInfo, sizeof(pchInfo));
	long lInfoLen = strlen(lpCommunicationInfo);

	try
	{
		
		if (lInfoLen > MAX_PATH)
			throw"Address String Error";
		memcpy(pchInfo, lpCommunicationInfo, lInfoLen);
		//Board index 
		pRegComment = strtok(pchInfo, tszTok); 
		ASSERT(pRegComment);
		lBoardIndex = atol(pRegComment);
		//Primary GPIB address
		pRegComment = strtok(NULL, tszTok);
		ASSERT(pRegComment);
		lPrimaryAddress = atol(pRegComment);
		//Secondary GPIB address
		pRegComment = strtok(NULL, tszTok);
		ASSERT(pRegComment);
		lSecondAddress = (BYTE)atol(pRegComment); 
		
		status = viOpenDefaultRM (&defaultRM);
		if(!DeviceStatusOK(status))
			throw"Open Default RM Error";
		
		sprintf(szDeviceDescriptor,"GPIB%d::%d::INSTR",lBoardIndex,lPrimaryAddress);	
		
		status = viOpen(defaultRM, szDeviceDescriptor,VI_NULL, VI_NULL, &m_hGPIB);
		if(!DeviceStatusOK(status))
			throw"Open GPIB Error";
		
	}
	catch (char* pstrMsg)
	{
		m_strErrorMsg = pstrMsg;
		return FALSE;
	}
	return TRUE;
}

BOOL CGpib::Close()
{
	if (m_hGPIB !=NULL)
	{
		status = viClose(m_hGPIB);
		if (!DeviceStatusOK(status)) 
		{
			m_strErrorMsg ="Close GPIB Error";
			return FALSE;
		}
	}
	if(defaultRM != NULL)
	{
		status = viClose(defaultRM);
		
		if (!DeviceStatusOK(status)) 
		{
			m_strErrorMsg ="Close GPIB Error";
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CGpib::Clear()
{
	status = viClear(m_hGPIB);
	if (!DeviceStatusOK(status)) 
	{
         m_strErrorMsg ="Clear GPIB Error";
		 return FALSE;
	}
	
	return TRUE;
}

BOOL CGpib::Write(PVOID pWriteBuffer, DWORD dwWriteLength)
{
	ViUInt32 nGetLength;
	LPCSTR pszWriteBuffer = (LPSTR)pWriteBuffer;
	
	status = viWrite(m_hGPIB, (unsigned char*)pWriteBuffer, dwWriteLength,&nGetLength);
	if (!DeviceStatusOK(status)) 
	{
         m_strErrorMsg ="Write Something Use GPIB Error";
		 return FALSE;
	}
		
	return TRUE;
}

BOOL CGpib::Read(PVOID pReadBuffer, DWORD dwReadLength)
{
    ViUInt32 nGetLength;
	status =  viRead(m_hGPIB, (unsigned char*)pReadBuffer, dwReadLength,&nGetLength);
	if (!DeviceStatusOK(status)) 
	{
         m_strErrorMsg ="Read Something Use GPIB Error";
		 return FALSE;
	}

	return TRUE;
}
void CGpib::SetHandle(unsigned long pHandle)
{
	m_hGPIB = (ViSession)pHandle;
}
