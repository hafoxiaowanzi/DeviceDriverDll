// PolDll.h: interface for the CPolDll class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POLDLL_H__88FC36E0_6C41_4A8B_BEC2_424F42DE9755__INCLUDED_)
#define AFX_POLDLL_H__88FC36E0_6C41_4A8B_BEC2_424F42DE9755__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef POCUDL_EXPORTS
#define POLCONTROLDLL_API __declspec(dllexport)
#else
#define POLCONTROLDLL_API __declspec(dllimport)
#endif

#include "..\\include\\POC.H"

#define HP_8169 0
#define OPLK_POL 1
#define N8876 2

class POLCONTROLDLL_API CPolDll  
{
public:
	CPolDll();
	virtual ~CPolDll();

	DWORD  OpenDevice(stDevType stType, LPCTSTR pszDeviceAddr,unsigned long *ComHandle);;	
	DWORD  SetHandle(stDevType stType, LPCTSTR pszDeviceAddr, unsigned long handle);
	DWORD  CloseDevice();
	DWORD  ResetDevice(void);
	DWORD  GetDeviceInfo(stDevInfo *stInfo);
	DWORD  GetCurrentPOSPolarizer(double * pdblAlphaP,double *pdblAlphaQ,double *pdblAlphaH);
	DWORD  SetALL(double alphaP, double alphaQ, double alphaH);
	DWORD  SetDiagonalAngles(double AlphaPMax, double Wavelength);
	DWORD  SetHorizontalAngles(double AlphaPMax, double Wavelength);
	DWORD  SetPOSHalf(double alpha);
	DWORD  SetPOSPolarizer(double alpha);
	DWORD  SetPOSQuarter(double alpha);
	DWORD  SetRightHandCircularAngles(double AlphaPMax, double Wavelength);
	DWORD  SetVerticalAngles(double AlphaPMax, double Wavelength);

private:
	CPolControl *m_pPol;
};

extern POLCONTROLDLL_API int nPolControlDll;

POLCONTROLDLL_API int fnPolControlDll(void);
#endif // !defined(AFX_POLDLL_H__88FC36E0_6C41_4A8B_BEC2_424F42DE9755__INCLUDED_)
