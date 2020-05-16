// PolDll.h: interface for the CPolDll class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SWITCHDLL_H__88FC36E0_6C41_4A8B_BEC2_424F42DE9755__INCLUDED_)
#define AFX_SWITCHDLL_H__88FC36E0_6C41_4A8B_BEC2_424F42DE9755__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef SWITCHUDL_EXPORTS
#define SWITCHCONTROLDLL_API __declspec(dllexport)
#else
#define SWITCHCONTROLDLL_API __declspec(dllimport)
#endif

#include "..\\include\\Switch.h" 

enum { DEST_SW_NAN, DEST_SW_OPM, DEST_SW_OSA };
enum { EO_PORT_1 = 1, EO_PORT_2, EO_PORT_3 };

enum OpticalSwitchType
{
	SWITCH_EDFAGENERAL = 1,
	SWITCH_1X2,
	SWITCH_1X8,
	SWITCH_1X64,
	SWITCH_1X68,
	SWITCH_BOLA,
	SWITCH_DT08,
	SWITCH_THREE1X18
};

class SWITCHCONTROLDLL_API CSwitchDll  
{
public:
	CSwitchDll();
	virtual ~CSwitchDll();

	DWORD  OpenDevice(stDevType stType, LPCTSTR pszDeviceAddr,unsigned long *ComHandle);;	
	DWORD  CloseDevice();
	DWORD  SetHandle(stDevType stType, LPCTSTR pszDeviceAddr, unsigned long handle);
	DWORD  SetSingleSWPos(long lChIndex,BYTE bySWIndex,BYTE byPos);                
	DWORD  GetSingleSWPos(long lChIndex, BYTE bySWIndex,BYTE &byPos);
	DWORD  SetMultiSWPos(long lChIndex, BYTE *pbyPosArray, BYTE bySWCount);
	DWORD  GetMultiSWPos(long lChIndex, BYTE *pbyPosArray, BYTE bySWCount);
	DWORD  SetInputVOAAtten(long lChIndex, double dblAtten);
	DWORD  GetInputVOAAtten(long lChIndex, double *pdblAtten);

	DWORD SetMSAVOAAtten(long lChIndex, double dblAtten);
	DWORD GetMSAVOAAtten(long lChIndex, double *pdblAtten);
	DWORD SetLDSSelection(long lChIndex, BYTE bySrcIndex);
	DWORD SetLDSToDutIn(long lChIndex, BYTE byDutInIndex);
	DWORD SetLDSToDutOut(long lChIndex, BYTE byDutOutIndex);
	DWORD SetLDSToMonPath(long lChIndex, BYTE byDestPos);
	DWORD SetLDSToRefPath(long lChIndex, BYTE byDestPos);
	DWORD SetDutOutToDest(long lChIndex, BYTE byDutOutIndex, BYTE byDestPos);
	DWORD SetDutInAsOutput(long lChIndex, BYTE byDutInIndex, BYTE byDestPos);
	DWORD SetDutOut98ToEO1(long lChIndex, BYTE byDutOutIndex, BYTE byDestPos);
	DWORD SetDutIn98AsOutputToEO1(long lChIndex, BYTE byDutInIndex, BYTE byDestPos);
	DWORD SetMSAInToMSAOut(long lChIndex, BYTE byMsaInPort, BYTE byMsaOutPort, double dblMsaVOAAtten);
	DWORD SetMSATapToDest(long lChIndex, BYTE byMsaOutPort, BYTE byDestPos);
	DWORD SetMSAInAsOutput(long lChIndex, BYTE byMsaInPort, BYTE byDestPos);
	DWORD SetMSAOutAsOutput(long lChIndex, BYTE byMsaOutPort, BYTE byDestPos);
	DWORD SetMSAOut98AsOutputToEO2(long lChIndex, BYTE byMsaOutPort, BYTE byDestPos);
	DWORD SetEOPortToDest(long lChIndex, BYTE byEOPort, BYTE byDestPos);
	DWORD SetVOATriggerOut(long lChIndex, double dblStartAtten, double dblEndAtten, double dblStepAtten, WORD wOPMWaitTimeMs);
	DWORD SetSWPathMapping(long lChIndex, char *pchBinfileName);
	DWORD SetSWTriggerPathScanStart(long lChIndex, WORD wExitTimeOutSecond);
	DWORD SetGPIOConfig(long lChIndex, DWORD dwCtrlPinBits, DWORD dwAlarmPinBits);
	DWORD GetGPIOStatus(long lChIndex, WORD *pdwCtrlPinBits, WORD *pdwAlarmPinBits);
	DWORD SetUARTConfig(long lChIndex, BYTE byUARTIndex, stSerialPortCfg stSerialPortCfgValue, DWORD dwTimeOut = 0);
	DWORD WriteUARTData(long lChIndex, BYTE byUARTIndex, BYTE* pbyBuffer, WORD wLength);
	DWORD ReadUARTData(long lChIndex, BYTE byUARTIndex, BYTE* pbyBuffer, WORD wLength, WORD *pwGetLength);
	DWORD GetDeviceInfo(long lChIndex, pstDevInfo pstSWInfo);
	DWORD GetSwitchingCnt(long lChIndex, BYTE bySWIndex, DWORD *pdwSwitchingCnt);
	DWORD GetInputMinIL(long lChIndex, BYTE bySWIndex, double * pdblGetMinIL);
	DWORD SetBlockBySwitch(long lChIndex, BYTE bySrcIndex);
	//DWORD SetGPIOStatus(long lChIndex, WORD wAlarmIN, WORD wAlarmOut);
	//DWORD GetGPIOStatus(long lChIndex, WORD *pwAlarmIN, WORD *pwAlarmOut);
	DWORD SetGPIOVoltage(long lChIndex, bool bVoltage5V = 1);

private:
	CSwitchControl *m_pSwitch;
};

extern SWITCHCONTROLDLL_API int nSwtichControlDll;

SWITCHCONTROLDLL_API int fnSwtichControlDll(void);

#endif // !defined(AFX_POLDLL_H__88FC36E0_6C41_4A8B_BEC2_424F42DE9755__INCLUDED_)
