// PolDll.h: interface for the CPolDll class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POLDLL_H__88FC36E0_6C41_4A8B_BEC2_424F42DE9755__INCLUDED_)
#define AFX_POLDLL_H__88FC36E0_6C41_4A8B_BEC2_424F42DE9755__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef DT0ASWITCHBOXUDL_EXPORTS
#define DT0ASWITCHBOXCONTROLDLL_API __declspec(dllexport)
#else
#define DT0ASWITCHBOXCONTROLDLL_API __declspec(dllimport)
#endif

#include "..\\include\\DTOASwitchBox.h"

#define DT0ASwitchBox    0


class DT0ASWITCHBOXCONTROLDLL_API CDT0ASwitchBoxDll
{
public:
	CDT0ASwitchBoxDll();
	~CDT0ASwitchBoxDll();
	 BOOL GetVersionInfo(char *pstrPN, char *pstrSN, char *pstrEquipment, char *pstrHWVersion, char *pstrFWVersion, char *pstrOplinFWVersion, char *pstrMFGDate);
	 BOOL GetPNInfo(char *pstrPN);
     BOOL GetSNInfo(char *pstrSN);
	 BOOL GetEquipmentInfo(char *pstrEquipment);
	 BOOL GetHWInfo(char *pstrHWVersion);
	 BOOL GetFWInfo(char *pstrFWVersion);
	 BOOL GetOplinkFWInfo(char *pstrOplinkVersion);
	 BOOL SetInputVOAAtten(double dbAtten);
	 BOOL GetInputVOAAtten(double *pdbAtten);
	 BOOL SetMSAVOAAtten(double dbAtten);
	 BOOL GetMSAVOAAtten(double *pdbAtten);
	 BOOL GetInputMinIL(double * pdbGetMinIL);
	 BOOL GetOutputMinIL(double * pdbGetMinIL);
	 BOOL GetMSAMinIL(double * pdbGetMinIL);
	 BOOL ConfigureGPIO(long nStatus);
	 BOOL GetGPIOConfigure(long * plStatus);
	 BOOL ConfigureGPIOx(BYTE bInstance, BOOL bStatus);
	 BOOL GetGPIOxSetPoint(BYTE bInstance, BYTE* bStatus);
	 BOOL SetAllInputGPIOPoint(long lStatus);
	 BOOL GetAllInputGPIOPoint(long * plStatus);
	 BOOL GetGPIOxStatus(BYTE bInstance, BYTE* bStatus);
	 BOOL ConfigUARTx(BYTE bInstance, DWORD dwBaudRate = 115200, BYTE bByteSize = 8, BYTE bParity = NOPARITY, BYTE bStopBits = ONESTOPBIT, DWORD dwTimeOut = 0);
	 BOOL ConfigAllUART(DWORD dwBaudRate = 115200, BYTE bByteSize = 8, BYTE bParity = NOPARITY, BYTE bStopBits = ONESTOPBIT, DWORD dwTimeOut = 0);
	 BOOL WriteUARTxMessage(BYTE bInstance, BYTE* pBuffer, int nLength);
	 BOOL ReadUARTxMessage(BYTE bInstance, BYTE* pBuffer, int nLength, int &nGetLength);
	 BOOL WriteAllUARTMessage(BYTE* pBuffer, int nLength);
	 BOOL SetSwitchToInputPath(int nChInput, int n2X2Ch, int nChOutput);
	 BOOL SetSwitchToOutputPath(int nChInput, int n2X2Ch, int nChOutput);
	 BOOL SetSwitchToMSAInToMSAOut(int nChInput, int nChOutput);
	 BOOL SetSwitchToExpendPath(int nChInput, int nChOutput);
	 BOOL SetSwitchMSAIToExtendPath(int nChInput, int nChOutput);
	 BOOL SetSwitchSxInToMonitor(int nChInput, int nChOutput);
	 BOOL SetSwitchReferencePath(int nChOutput);
	 BOOL SetSwitchMSAIMonitorPath(int nChInput, int nChOutput);
	 BOOL SetSwitchMSAOToExtendPath(int nChInput, int nChOutput);

	 BOOL SetVOAxAtten(BYTE bInstance, double dbAtten);
	 BOOL GetVOAxAtten(BYTE bInstance, double *pdbAtten);
	 BOOL SetVOAxAttenToDiffrentValue(double dbAtten1, double dbAtten2);
	 BOOL GetAllVOAAtten(double *pdbAtten1, double*pdbAtten2);
	 BOOL SetVOAxDAC(BYTE bInstance, WORD dwDAC);
	 BOOL GetVOAxDAC(BYTE bInstance, WORD* pwDAC);
	 BOOL SetVOAxDACToDiffrentValue(WORD dwADC1, WORD dwADC2, WORD dwADC3, WORD dwADC4);
	 BOOL GetVOAxMinIL(BYTE bInstance, double * pdbGetMinIL);
	 BOOL GetAllVOAMinIL(double * pdbGetMinIL1, double*pdbGetMinIL2, double*pdbGetMinIL3);
	 BOOL SetSwitchChannel(BYTE bInstance, BYTE bChannel);
	 BOOL GetSwitchChannel(BYTE bInstance, BYTE* bGetChIndex);
	 BOOL SetAllSwitchToDifferentChannel(BYTE bChannel, BYTE bChanne2, BYTE bChanne3, BYTE bChanne4, BYTE bChanne5, BYTE bChanne6, BYTE bChanne7, BYTE bChanne8, BYTE bChanne9);
	 BOOL GetAllSwitchChannel(BYTE* bGetChArry);
	 BOOL GetSwitchActualChannel(BYTE bInstance, BYTE* bGetChIndex);
	 BOOL GetAllSwitchActualChannel( BYTE* bGetChArry);
	 BOOL GetAllVOADAC(WORD* pwDAC1, WORD* pwDAC2, WORD* pwDAC3, WORD* pwDAC4);

	BYTE GetChecksum(BYTE* pbBuffer, int nLength);
	void AnlysisErrorString(BYTE bStatus);
	char* GetMsgString();

private:
	CDT0ASwitchBoxControl *m_pSwitch;
};

extern DT0ASWITCHBOXCONTROLDLL_API int nDT0ASwitchControlDll;

DT0ASWITCHBOXCONTROLDLL_API int fnDT0ASwtichControlDll(void);
#endif // !defined(AFX_POLDLL_H__88FC36E0_6C41_4A8B_BEC2_424F42DE9755__INCLUDED_)
