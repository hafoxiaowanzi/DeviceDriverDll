// PolControl.h: interface for the PolControl class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_OP8169_H__CAB1F721_3927_479F_A5AF_07759C01F635__INCLUDED_)
#define AFX_OP8169_H__CAB1F721_3927_479F_A5AF_07759C01F635__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UDLReturnCode.h"
#include "Communicationudl.h"

class CSwitchControl 
{
public:
	CSwitchControl();
	virtual ~CSwitchControl();
	virtual DWORD  OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle) = 0;
	virtual DWORD  CloseDevice() = 0;
	virtual DWORD  SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle) = 0;
	virtual DWORD  GetDeviceInfo(stDevInfo *stInfo) = 0;
	virtual DWORD  SwitchPort2Port(int nSwitchIndex,int nInputPort, int nOutputPort)=0;

};

class CIT_1X2SW : public CSwitchControl
{
public:
	CIT_1X2SW();
	virtual ~CIT_1X2SW();
	virtual DWORD  OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle) ;
	virtual DWORD  CloseDevice();
	virtual DWORD  SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle);
	virtual DWORD  GetDeviceInfo(stDevInfo *stInfo);
	virtual DWORD  SwitchPort2Port(int nSwitchIndex,int nInputPort, int nOutputPort);
private:
	CCommunicationDLL m_DevComHandle;
};

class CIT_1X8SW : public CSwitchControl
{
public:
	CIT_1X8SW();
	virtual ~CIT_1X8SW();
	virtual DWORD  OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle) ;
	virtual DWORD  CloseDevice();
	virtual DWORD  SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle);
	virtual DWORD  GetDeviceInfo(stDevInfo *stInfo);
	virtual DWORD  SwitchPort2Port(int nSwitchIndex,int nInputPort, int nOutputPort);
private:
	CCommunicationDLL m_DevComHandle;
};

class COMS_1X64SW : public CSwitchControl
{
public:
	COMS_1X64SW();
	virtual ~COMS_1X64SW();
	virtual DWORD  OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle) ;
	virtual DWORD  CloseDevice();
	virtual DWORD  SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle);
	virtual DWORD  GetDeviceInfo(stDevInfo *stInfo);
	virtual DWORD  SwitchPort2Port(int nSwitchIndex,int nInputPort, int nOutputPort);
private:
	CCommunicationDLL m_DevComHandle;
};


#endif // !defined(AFX_PMCONTROL_H__8F680F2C_8DBB_4C0B_9B88_30A551A22F82__INCLUDED_)