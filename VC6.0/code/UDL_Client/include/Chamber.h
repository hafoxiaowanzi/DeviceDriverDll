#if !defined(AFX_CHAMBERCONTROL_H__8AD5CA80_E88A_4575_B33A_8EDFE709430E__INCLUDED_)
#define AFX_CHAMBERCONTROL_H__8AD5CA80_E88A_4575_B33A_8EDFE709430E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UDLReturnCode.h"
#include "Communicationudl.h"

class CChamberControl
{
public:
	CChamberControl();
	virtual ~CChamberControl();

	virtual DWORD  OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle) = 0;
	virtual DWORD  CloseDevice() = 0;
	virtual DWORD  SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle) = 0;
	virtual DWORD  ResetDevice() = 0;
	virtual DWORD  GetDeviceInfo(stDevInfo *stInfo) = 0;
	virtual DWORD  SetChamberRunStop()=0;
	virtual DWORD  SetChamberRunStart()=0;
	virtual DWORD  SetChamberSetPoint(double dbSetPoint)=0;
	virtual DWORD  GetChamberSetPoint(double* dbSetPoint)=0;
	virtual DWORD  GetChamberCurrentTemp(double *dbCurrTemp)=0;

};
class CHZChamberContorl : public CChamberControl
{
public:
	CHZChamberContorl();
	virtual ~CHZChamberContorl();
	
	virtual DWORD  OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle);
	virtual DWORD  CloseDevice();
	virtual DWORD  SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle);
	virtual DWORD  ResetDevice() ;
	virtual DWORD  GetDeviceInfo(stDevInfo *stInfo);
	virtual DWORD  SetChamberRunStop();
	virtual DWORD  SetChamberRunStart();
	virtual DWORD  SetChamberSetPoint(double dbSetPoint);
	virtual DWORD  GetChamberSetPoint(double* dbSetPoint);
	virtual DWORD  GetChamberCurrentTemp(double *dbCurrTemp);
	
private:
	CCommunicationDLL m_DevComHandle;
};
#endif 