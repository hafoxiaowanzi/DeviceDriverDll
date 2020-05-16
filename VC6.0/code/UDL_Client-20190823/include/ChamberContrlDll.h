// ChamberContrlDll.h : main header file for the CHAMBERCONTRLDLL DLL
//

#ifdef CHAMBERCONTROLDLL_EXPORTS
#define CHAMBERCONTROLDLL_API __declspec(dllexport)
#else
#define CHAMBERCONTROLDLL_API __declspec(dllimport)
#endif

#ifndef CHAMBER_MACRO_DATA_SRTUCT_HEADER
#define CHAMBER_MACRO_DATA_SRTUCT_HEADER

#include "..\\include\\UDLReturnCode.h"
#include "..\\include\\Chamber.h"

#define HONGZHAN 0


class CHAMBERCONTROLDLL_API CChamberDll 
{
public:
	CChamberDll();
	virtual~CChamberDll();
	// TODO: add your methods here.
	DWORD  OpenDevice(stDevType stType, LPCTSTR pszDeviceAddr, unsigned long *Comhandle);
	DWORD  SetHandle(stDevType stType, LPCTSTR pszDeviceAddr, unsigned long handle);
	DWORD  CloseDevice();
	DWORD  GetDeviceInfo(stDevInfo *stInfo);
	DWORD  SetChamberRunStop();
	DWORD  SetChamberRunStart();
	DWORD  SetChamberSetPoint(double dbSetPoint);
	DWORD  GetChamberSetPoint(double* dbSetPoint);
	DWORD  GetChamberCurrentTemp(double *dbCurrTemp);

private:	
	CChamberControl	*m_pChamber;

};

extern CHAMBERCONTROLDLL_API int nChamberDLL;

CHAMBERCONTROLDLL_API int fnChamberDLL(void);
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHAMBERCONTRLDLL_H__CDC29B1A_323C_4E3B_919F_2BD461BC15A9__INCLUDED_)
