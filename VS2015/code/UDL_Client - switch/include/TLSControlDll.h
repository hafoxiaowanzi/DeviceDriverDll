
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the TLSCONTROLDLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// TLSCONTROLDLL_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef TLSCONTROLDLL_EXPORTS
#define TLSCONTROLDLL_API __declspec(dllexport)
#else
#define TLSCONTROLDLL_API __declspec(dllimport)
#endif

#include "..\\include\\ScanHeader.h"
#include "..\\include\\TLS.h"


#define HP_816X 0
#define OPLK_TLS 1
#define SANTEC_TLS 2
#define AGLIENT81960A 3
#define AQ2200_136    4
#define HP8168E       5
#define TLSSHARE      6

// This class is exported from the TLSControlDll.dll
class TLSCONTROLDLL_API CTLSDll 
{
public:
	CTLSDll(void);
	virtual~CTLSDll(void);
	// TODO: add your methods here.
	DWORD OpenDevice(stDevType stType, LPCTSTR pszDeviceAddr,unsigned long *ComHandle);
	DWORD SetWavelength(long lChIndex, double dblWL);
	DWORD SetSourcePower(long lChIndex, double dblPW);
	DWORD SetCoherenceControl(BOOL bEnable);
	DWORD SetSourceUnit(long lChIndex, long lUnit);
	DWORD SetParameters(long lChIndex, BOOL bLowSSE,double dblPower, double dblWavelength);
	DWORD SetHandle(stDevType stType, LPCTSTR pszDeviceAddr, unsigned long handle);
	DWORD SetOutputEnable(BOOL bEnable);
	DWORD CloseDevice();
	DWORD PrepareScan(long lChIndex,stScanParam* lScanParam);
	DWORD SetScanStart(long lChIndex);
	DWORD SetScanStop(long lChIndex);
    DWORD GetLamdaScanWLResult(long lChIndex,double* pdbWLAarry);
	DWORD SetMaxOutput(long lChIndex);
	DWORD SetTLSFrequency(long lChIndex,double dblFrequrency);
    DWORD GetTLSSettings(long lChIndex,double* pdblWavelength,double* pdblPower,BYTE* pdCtrlState);
	DWORD SetSlotIndex(long lSlotIndex);
	DWORD SetTLSLock(long lChIndex, int nTimeOut,double dbSetWL);
	DWORD SetTLSUnlock(long lChIndex);

private:
	CTLSControl *m_pTLS;
};

extern TLSCONTROLDLL_API int nTLSControlDll;

TLSCONTROLDLL_API int fnTLSControlDll(void);

