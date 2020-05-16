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
#include "MuellerAlpahaPCompensate.h"

class CPolControl 
{
public:
	CPolControl();
	virtual ~CPolControl();

	virtual DWORD  OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle) = 0;
	virtual DWORD  CloseDevice() = 0;
	virtual DWORD  SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle) = 0;
	virtual DWORD  ResetDevice() = 0;
	virtual DWORD  GetDeviceInfo(stDevInfo *stInfo) = 0;
	virtual DWORD  GetCurrentPOSPolarizer(double * pdblAlphaP,double *pdblAlphaQ,double *pdblAlphaH)=0;
	virtual DWORD  SetALL(double alphaP, double alphaQ, double alphaH)=0;
	virtual DWORD  SetDiagonalAngles(double AlphaPMax, double Wavelength)=0;
	virtual DWORD  SetHorizontalAngles(double AlphaPMax, double Wavelength)=0;
	virtual DWORD  SetPOSHalf(double alpha)=0;
	virtual DWORD  SetPOSPolarizer(double alpha)=0;
	virtual DWORD  SetPOSQuarter(double alpha)=0;
	virtual DWORD  SetRightHandCircularAngles(double AlphaPMax, double Wavelength)=0;
	virtual DWORD  SetVerticalAngles(double AlphaPMax, double Wavelength)=0;
};

class COp8169 : public CPolControl
{
public:
	COp8169();
	virtual ~COp8169();
	
	virtual DWORD  OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle);
	virtual DWORD  CloseDevice();
	virtual DWORD  SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle);
	virtual DWORD  ResetDevice() ;
	virtual DWORD  GetDeviceInfo(stDevInfo *stInfo);
	virtual DWORD  GetCurrentPOSPolarizer(double * pdblAlphaP,double *pdblAlphaQ,double *pdblAlphaH );
	virtual DWORD  SetALL(double alphaP, double alphaQ, double alphaH);
	virtual DWORD  SetDiagonalAngles(double AlphaPMax, double Wavelength);
	virtual DWORD  SetHorizontalAngles(double AlphaPMax, double Wavelength);
	virtual DWORD  SetPOSHalf(double alpha);
	virtual DWORD  SetPOSPolarizer(double alpha);
	virtual DWORD  SetPOSQuarter(double alpha);
	virtual DWORD  SetRightHandCircularAngles(double AlphaPMax, double Wavelength);
	virtual DWORD  SetVerticalAngles(double AlphaPMax, double Wavelength);
private:
	CCommunicationDLL m_DevComHandle;
	MuellerAlpahaPCompensate m_compensate;
	void CompleteRequest();
};


class COpR181 : public CPolControl
{
public:
	COpR181();
	virtual ~COpR181();
	
	virtual DWORD  OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle);
	virtual DWORD  CloseDevice();
	virtual DWORD  SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle);
	virtual DWORD  ResetDevice() ;
	virtual DWORD  GetDeviceInfo(stDevInfo *stInfo);
	virtual DWORD  GetCurrentPOSPolarizer(double * pdblAlphaP,double *pdblAlphaQ,double *pdblAlphaH);
	virtual DWORD  SetALL(double alphaP, double alphaQ, double alphaH);
	virtual DWORD  SetDiagonalAngles(double AlphaPMax, double Wavelength);
	virtual DWORD  SetHorizontalAngles(double AlphaPMax, double Wavelength);
	virtual DWORD  SetPOSHalf(double alpha);
	virtual DWORD  SetPOSPolarizer(double alpha);
	virtual DWORD  SetPOSQuarter(double alpha);
	virtual DWORD  SetRightHandCircularAngles(double AlphaPMax, double Wavelength);
	virtual DWORD  SetVerticalAngles(double AlphaPMax, double Wavelength);
private:
	WORD GetAngle(BYTE bMotorIdx);
	BOOL SetToTargetAngle(BYTE bMotorIdx, WORD wTargetAngle);
	DWORD SetToTargetStep(BYTE bMotorIdx, WORD wTargetStep);
	DWORD SetMotorZero(BYTE bMotorIndex);
	CCommunicationDLL m_DevComHandle;
	MuellerAlpahaPCompensate m_compensate;
};

#endif // !defined(AFX_PMCONTROL_H__8F680F2C_8DBB_4C0B_9B88_30A551A22F82__INCLUDED_)