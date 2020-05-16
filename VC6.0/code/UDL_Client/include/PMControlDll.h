
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the PMCONTROLDLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// PMCONTROLDLL_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef PMCONTROLDLL_EXPORTS
#define PMCONTROLDLL_API __declspec(dllexport)
#else
#define PMCONTROLDLL_API __declspec(dllimport)
#endif

#ifndef PM_MACRO_DATA_SRTUCT_HEADER
#define PM_MACRO_DATA_SRTUCT_HEADER

#include "..\\include\\UDLReturnCode.h"
#include "..\\include\\PM.h"


#define HP_8163A		0
#define OPLK_PM			1
#define PM_I830C		2
#define PM_N7745		3
#define PM_JH		    4
#define PM_OPLINKI1830C 5
#define HP_8153A        6
#define AQ2200_215      7
#define AQ2140			8

// This class is exported from the PMControlDll.dll
class PMCONTROLDLL_API CPMDll 
{
public:
	CPMDll();
	virtual~CPMDll();
	// TODO: add your methods here.
	DWORD GetUnit(long lslot,long iChan, long* piUnit);
	DWORD GetAverageTime(long lslot,long iChan, double* pdblAverageTime);
	DWORD GetWavelength(long lslot,long iChan, double* pdblWL);
	DWORD OpenDevice(stDevType stType, LPCTSTR pszDeviceAddr,unsigned long *ComHandle);
	DWORD ReadPower(long lslot,long iChan, double* pdbPowerValue);
	DWORD SetUnit(long lslot,long iChan, long iPWUnit);
	DWORD SetWavelength(long lslot,long iChan, double dblWL);
	DWORD SetAverageTime(long lslot,long iChan, double dblPWAverageTime);
	DWORD SetRangeMode(long lslot,long iChan, long iPWRangeMode);
	DWORD SetRange(long lSlot,long IChan, long lRange);
	DWORD SetParameters(long lslot,long iChan, BOOL bAutoRang, double dblWL, double dblAverageTime, double dblPwrRange);
	DWORD CloseDevice();
	DWORD GetRangeMode(long lslot,long iChan, long* iPWMRangeMode);
	DWORD SetZero(long lslot,long iChan);
	DWORD GetDeviceInfo(CHAR *pchInfo);
	DWORD SetHandle(stDevType stType, LPCTSTR pszDeviceAddr, unsigned long handle);
	DWORD PrepareScan(long lSlot,long lChIndex,stScanParam* lScanParam);
	DWORD SetPMScanStart(long lSlot,long lChIndex);
	DWORD getLambdaScanPMResult(long lSlot,long lChIndex,double* pdbPMArry);
	DWORD SetPMScanStop(long lSlot,long lChIndex);
	DWORD SetPMScanTriggerStop(long lSlot,long lChIndex);
	DWORD SetPMMaxMinPowerStart(long lSlot,long lChIndex);
	DWORD GetPMMaxMinPower(long lSlot,long lChIndex,double *pdbGetMax,double *pdbGetMin);
    DWORD SetPMMaxMinPowerStop(long lSlot,long lChIndex);
	DWORD SetPMPowerOffset(long lSlot,long IChan,double dbPowerOffset);
	
private:	
	CPMControl	*m_pPm;

};

extern PMCONTROLDLL_API int nPMControlDll;

PMCONTROLDLL_API int fnPMControlDll(void);

#endif
