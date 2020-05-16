// Communication.h: interface for the CCommunication class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMUNICATION_H__78E7CC93_4279_4615_BCC8_FC59591157E5__INCLUDED_)
#define AFX_COMMUNICATION_H__78E7CC93_4279_4615_BCC8_FC59591157E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"
#include "windows.h"
#include "..\\include\\visa.h"

#include <string>
using namespace std;


//class __declspec(dllexport) CCommunication  
class CCommunication  
{
public:
	CCommunication();
	virtual ~CCommunication();

	virtual BOOL Open(LPCTSTR lpCommunicationInfo) = 0;
	virtual BOOL Close() = 0;
	virtual BOOL Write(PVOID pWriteBuffer, DWORD dwWriteLength) = 0;
	virtual BOOL Read(PVOID pREadBuffer, DWORD dwReadLength) = 0;
	virtual BOOL Clear() = 0;
	virtual void SetHandle(unsigned long vHandle) = 0;
	virtual string GetErrorMsg() = 0;
};

class CComm  : public CCommunication
{
public:
	CComm();
	virtual ~CComm();

	virtual BOOL Open(LPCTSTR lpCommunicationInfo);
	virtual BOOL Close();
	virtual BOOL Write(PVOID pWriteBuffer, DWORD dwWriteLength);
	virtual BOOL Read(PVOID pReadBuffer, DWORD dwReadLength);
	virtual BOOL Clear();
	virtual void SetHandle(unsigned long pHandle);
	virtual string GetErrorMsg();
	string m_strErrorMsg;

    HANDLE	m_hCommPort;
	BOOL m_bSetHandle;
};

//class __declspec(dllexport) CGpib  : public CCommunication
class CGpib  : public CCommunication
{
public:
	CGpib();
	virtual ~CGpib();

	ViSession m_hGPIB;
	ViSession defaultRM;
	ViStatus status;

	virtual BOOL Open(LPCTSTR lpCommunicationInfo);
	virtual BOOL Close();
	virtual BOOL Write(PVOID pWriteBuffer, DWORD dwWriteLength);
	virtual BOOL Read(PVOID pREadBuffer, DWORD dwReadLength);
	virtual BOOL Clear();
	virtual void SetHandle(unsigned long pHandle);
	virtual string GetErrorMsg();
	
	BOOL DeviceStatusOK(ViStatus viStatus);
	string m_strErrorMsg;

};

#include <winsock.h>

#pragma comment(lib, "wsock32.lib")

#define		WINSOCK_VERSION					0x11
#define		MAX_FIELD						8192
#define		MAX_DATA_COUNT					2048

//class __declspec(dllexport) CLan  : public CCommunication
class CLan  : public CCommunication
{
public:
	CLan();
	virtual ~CLan();

	ViSession m_hSocket;
	ViSession defaultRM;
	ViStatus status;

	virtual BOOL Open(LPCTSTR lpCommunicationInfo);
	virtual BOOL Close();
	virtual BOOL Write(PVOID pWriteBuffer, DWORD dwWriteLength);
	virtual BOOL Read(PVOID pREadBuffer, DWORD dwReadLength);
	virtual BOOL SerialPoll(PCHAR pbSPByte);
	virtual BOOL WaitForCompletion(WORD wMask);
	

	virtual BOOL IsRequestCompleted();
	virtual BOOL GetError(PSTR pszErrorMessage);
	virtual BOOL Clear();
	virtual void SetHandle(unsigned long pHandle);
	virtual string GetErrorMsg();
	string m_strErrorMsg;
	BOOL DeviceStatusOK(ViStatus viStatus);

	//SOCKET				m_hSocket;

};

class CUsb : public CCommunication
{
public:
	CUsb();
	virtual ~CUsb();

	virtual BOOL Open(LPCTSTR lpCommunicationInfo);
	virtual BOOL Close();
	virtual BOOL Write(PVOID pWriteBuffer, DWORD dwWriteLength);
	virtual BOOL Read(PVOID pREadBuffer, DWORD dwReadLength);
	virtual BOOL Clear();
	virtual void SetHandle(unsigned long pHandle);
	virtual string GetErrorMsg();
	string m_strErrorMsg;

	BOOL DeviceStatusOK(ViStatus viStatus)	
	{
		return (viStatus >= VI_SUCCESS);
	}

	ViSession	 m_usb;
	ViStatus status;
	ViSession defaultRM;
};

#endif // !defined(AFX_COMMUNICATION_H__78E7CC93_4279_4615_BCC8_FC59591157E5__INCLUDED_)
