// Comm.cpp: implementation of the CComm class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\\include\\Communication.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CComm::CComm()
{
	m_hCommPort = INVALID_HANDLE_VALUE;
	m_bSetHandle = FALSE;
}

CComm::~CComm()
{
	Close();
}

string CComm::GetErrorMsg()
{
    return m_strErrorMsg;
}

BOOL CComm::Close()
{
	if(m_hCommPort != INVALID_HANDLE_VALUE)
	{
		if(m_bSetHandle ==TRUE)
		{
			m_bSetHandle = FALSE;
		}
		else
		{
			if (CloseHandle(m_hCommPort))
				m_hCommPort = INVALID_HANDLE_VALUE;	
			else
				return FALSE;
		}
		
	}
	return TRUE;
}

BOOL CComm::Open(LPCTSTR lpCommunicationInfo)
{
	BOOL			bPortReady = FALSE;
	DCB				PortDCB;
	COMMTIMEOUTS	PortTimeOuts;
	DWORD dwBaudRate = 9600; 
	BYTE bByteSize = 8; 
	BYTE bParity = 0; 
	BYTE bStopBit = 0;
	LONG lCOMNum = 0;
	
	char pchCOMName[15];
	
	ZeroMemory(pchCOMName, 15);
	
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
	ZeroMemory(pchInfo, sizeof(pchInfo));
	
	if (lInfoLen > MAX_PATH)
		return FALSE;
	memcpy(pchInfo, lpCommunicationInfo, lInfoLen);
	//Com number 
	pRegComment = strtok(pchInfo, tszTok); 
	lCOMNum = atol(pRegComment);
	//Baud rate
	pRegComment = strtok(NULL, tszTok);
	dwBaudRate = atol(pRegComment);
	
	if (lFlagCount > 2 )
	{
		//Byte size
		pRegComment = strtok(NULL, tszTok);
		bByteSize = (BYTE)atol(pRegComment); 
		//Parity
		pRegComment = strtok(NULL, tszTok);
		bParity = (BYTE)atol(pRegComment); 
		//Stop bit
		pRegComment = strtok(NULL, tszTok);
		bStopBit =(BYTE) atol(pRegComment);
	}
	else if (1 != lFlagCount)
	{
		return FALSE;
	}
	
	// 判断串口号码是否大于10
	if(lCOMNum > 9)
	{
		sprintf(pchCOMName, "\\\\.\\COM%d", lCOMNum);
	}
	else
	{
		sprintf(pchCOMName, "COM%d", lCOMNum);
	}
	
	
	//	If the port was previously open, close it first
    if (m_hCommPort != INVALID_HANDLE_VALUE)
    {
		Close();
    }
	
	//	Open the port and do new settings
	m_hCommPort = CreateFile(pchCOMName, 
							 GENERIC_READ | GENERIC_WRITE, 
							 0, 
							 NULL,
							 OPEN_EXISTING, 
							 0, 
							 NULL);
	if(m_hCommPort == INVALID_HANDLE_VALUE)
		return bPortReady;
	
	//SetCommMask(m_hCommPort,EV_RXCHAR|EV_TXEMPTY);
	bPortReady = GetCommState(m_hCommPort, &PortDCB);
	if(!bPortReady)
		return bPortReady;
	
	PortDCB.BaudRate = dwBaudRate;
	PortDCB.ByteSize = bByteSize;
	PortDCB.fParity  = bParity;   //Disable parity checking 
	PortDCB.StopBits = bStopBit;

	PortDCB.fAbortOnError = TRUE;	
	PortDCB.fInX =0;
	PortDCB.fOutX =0;
	
	PortDCB.fDtrControl = 0;
	PortDCB.fOutxCtsFlow =0;
	PortDCB.fOutxDsrFlow =0;
	
	bPortReady = SetCommState(m_hCommPort, &PortDCB);
	if(!bPortReady)
		return bPortReady;
	
	bPortReady = GetCommTimeouts(m_hCommPort, &PortTimeOuts);
	if(!bPortReady)
		return bPortReady;
	
	PortTimeOuts.ReadIntervalTimeout = 50;
	PortTimeOuts.ReadTotalTimeoutConstant = 50;
	PortTimeOuts.ReadTotalTimeoutMultiplier = 10;
	PortTimeOuts.WriteTotalTimeoutConstant = 50;
	PortTimeOuts.WriteTotalTimeoutMultiplier = 10;
	
	bPortReady = SetCommTimeouts(m_hCommPort, &PortTimeOuts);
	if(!bPortReady)
		return bPortReady;
	
	bPortReady = PurgeComm(m_hCommPort, PURGE_TXCLEAR | PURGE_RXCLEAR);
	
	return bPortReady;
}

BOOL CComm::Write(PVOID pWriteBuffer, DWORD dwWriteLength)
{
	DWORD dwBytesWritten = 0;
	LPCSTR pszWriteBuffer = (LPSTR)pWriteBuffer;
	
	if(m_hCommPort == INVALID_HANDLE_VALUE)
		return FALSE;
	
	if (!PurgeComm(m_hCommPort, PURGE_TXCLEAR | PURGE_RXCLEAR))
	{
		return FALSE;
	}
	
	WriteFile(m_hCommPort, pszWriteBuffer, dwWriteLength, &dwBytesWritten, NULL);
	if(dwBytesWritten != dwWriteLength)
		return FALSE;
	return TRUE;
}

BOOL CComm::Read(PVOID pReadBuffer, DWORD dwReadLength)
{
	DWORD dwBytesRead = 0;
	COMSTAT ComStat;        // 串行设备状态结构
	
    DWORD  dwErrorFlags;
	
	if(m_hCommPort == INVALID_HANDLE_VALUE)
		return FALSE;
	ClearCommError(m_hCommPort, &dwErrorFlags, &ComStat);	
	ReadFile(m_hCommPort, pReadBuffer, dwReadLength, &dwBytesRead, NULL);
	
	if(dwBytesRead == 0)
		return FALSE;
	
	return TRUE;
}

void CComm::SetHandle(unsigned long pHandle)
{
	m_hCommPort = (HANDLE)pHandle;
	m_bSetHandle = TRUE;
}

BOOL CComm::Clear()
{
	if (!PurgeComm(m_hCommPort, PURGE_TXCLEAR | PURGE_RXCLEAR))
	{
		return FALSE;
	}
	
	return TRUE;
}



