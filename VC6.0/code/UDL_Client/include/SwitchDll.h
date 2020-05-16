// PolDll.h: interface for the CPolDll class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POLDLL_H__88FC36E0_6C41_4A8B_BEC2_424F42DE9755__INCLUDED_)
#define AFX_POLDLL_H__88FC36E0_6C41_4A8B_BEC2_424F42DE9755__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef SWITCHUDL_EXPORTS
#define SWITCHCONTROLDLL_API __declspec(dllexport)
#else
#define SWITCHCONTROLDLL_API __declspec(dllimport)
#endif

#include "..\\include\\Switch.H"

#define IT_1X2SW    0
#define IT_1X8SW    1
#define OMS_1X64SW  2

class SWITCHCONTROLDLL_API CSwitchDll  
{
public:
	CSwitchDll();
	virtual ~CSwitchDll();

	DWORD  OpenDevice(stDevType stType, LPCTSTR pszDeviceAddr,unsigned long *ComHandle);;	
	DWORD  OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle);
	DWORD  CloseDevice();
	DWORD  GetDeviceInfo(stDevInfo *stInfo);
	DWORD  SetHandle(stDevType stType, LPCTSTR pszDeviceAddr, unsigned long handle);
	DWORD  SwitchPort2Port(int nSwitchIndex,int nInputPort, int nOutputPort);

private:
	CSwitchControl *m_pSwitch;
};

extern SWITCHCONTROLDLL_API int nPolControlDll;

SWITCHCONTROLDLL_API int fnSwtichControlDll(void);
#endif // !defined(AFX_POLDLL_H__88FC36E0_6C41_4A8B_BEC2_424F42DE9755__INCLUDED_)
