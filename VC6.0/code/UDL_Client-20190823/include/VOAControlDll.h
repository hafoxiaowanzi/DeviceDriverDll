
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the VOACONTROLDLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// VOACONTROLDLL_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef VOACONTROLDLL_EXPORTS
#define VOACONTROLDLL_API __declspec(dllexport)
#else
#define VOACONTROLDLL_API __declspec(dllimport)
#endif

#ifndef _ONCE_  
#define _ONCE_

#include "resource.h"		// main symbols
#include "..\\include\\UDLReturnCode.h"

#include "..\\include\\VOA.h"
	

// This class is exported from the VOAControlDll.dll
class VOACONTROLDLL_API CVOADll 
{
public:
	CVOADll();
	virtual ~CVOADll();
	// TODO: add your methods here.
	DWORD OpenDevice(stDevType stType, char* pszDeviceAddr, unsigned long *comHandle);
	DWORD CloseDevice();
	DWORD ResetDevice(void);
	DWORD GetDeviceInfo(stDevInfo *stInfo);
	DWORD SetWavelength(long lChIndex, double dblWL);
	DWORD GetWavelength(long lChIndex, double* pdblWL);
    DWORD SetAttenuation(long lChIndex, double dblAtten);
	DWORD GetAttenuation(long lChIndex, double* pdblAtten);
	DWORD SetEnableOutput(long lChIndex, BOOL bEnable);
	DWORD SetInputOffset(long lChIndex, double dblOffset);
	DWORD SetHandle(stDevType stType, char* pszDeviceAddr, unsigned long comHandle);
	DWORD GetStatus(DWORD *dwStatus);
	BOOL GetErrorMessage(DWORD dwErrorCode, char *pszErrorMsg);

private:

	CVOAControl *m_pVOA;

};

extern VOACONTROLDLL_API int nVOAControlDll;

VOACONTROLDLL_API int fnVOAControlDll(void);

#endif

