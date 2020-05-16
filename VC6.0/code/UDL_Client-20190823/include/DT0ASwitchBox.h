// DT0ASwitchBoxDll.h: interface for the PolControl class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_OP8169_H__CAB1F721_3927_479F_A5AF_07759C01F635__INCLUDED_)
#define AFX_OP8169_H__CAB1F721_3927_479F_A5AF_07759C01F635__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UDLReturnCode.h"
#include "Communicationudl.h"

class CDT0ASwitchBoxControl 
{
public:
	CDT0ASwitchBoxControl();
	virtual ~CDT0ASwitchBoxControl();
	virtual BOOL GetVersionInfo(CString & strPN, CString& strSN, CString& strEquipment, CString& strHWVersion, CString &strFWVersion, CString& strOplinFWVersion, CString & strMFGDate) =0 ;
	virtual BOOL GetPNInfo(CString& strPN) =0 ;
    virtual BOOL GetSNInfo(CString& strSN) =0 ;
	virtual BOOL GetEquipmentInfo(CString& strEquipment) =0 ;
	virtual BOOL GetHWInfo(CString& strHWVersion) =0 ;
	virtual BOOL GetFWInfo(CString& strFWVersion) =0 ;
	virtual BOOL GetOplinkFWInfo(CString& strOplinkVersion) =0 ;
	virtual BOOL SetInputVOAAtten(double dbAtten) =0 ;
	virtual BOOL GetInputVOAAtten(double *pdbAtten) =0 ;
	virtual BOOL SetMSAVOAAtten(double dbAtten) =0 ;
	virtual BOOL GetMSAVOAAtten(double *pdbAtten) =0 ;
	virtual BOOL GetInputMinIL(double * pdbGetMinIL) =0 ;
	virtual BOOL GetOutputMinIL(double * pdbGetMinIL) =0 ;
	virtual BOOL GetMSAMinIL(double * pdbGetMinIL) =0 ;
	virtual BOOL ConfigureGPIO(long nStatus) =0 ;
	virtual BOOL GetGPIOConfigure(long * plStatus) =0 ;
	virtual BOOL ConfigureGPIOx(BYTE bInstance, BOOL bStatus) =0 ;
	virtual BOOL GetGPIOxSetPoint(BYTE bInstance, BYTE* bStatus) =0 ;
	virtual BOOL SetAllInputGPIOPoint(long lStatus) =0 ;
	virtual BOOL GetAllInputGPIOPoint(long * plStatus) =0 ;
	virtual BOOL GetGPIOxStatus(BYTE bInstance, BYTE* bStatus);
	virtual BOOL ConfigUARTx(BYTE bInstance, DWORD dwBaudRate = 115200, BYTE bByteSize = 8, BYTE bParity = NOPARITY, BYTE bStopBits = ONESTOPBIT, DWORD dwTimeOut = 0) =0 ;
	virtual BOOL ConfigAllUART(DWORD dwBaudRate = 115200, BYTE bByteSize = 8, BYTE bParity = NOPARITY, BYTE bStopBits = ONESTOPBIT, DWORD dwTimeOut = 0) =0 ;
	virtual BOOL WriteUARTxMessage(BYTE bInstance, BYTE* pBuffer, int nLength) =0 ;
	virtual BOOL ReadUARTxMessage(BYTE bInstance, BYTE* pBuffer, int nLength, int &nGetLength) =0 ;
	virtual BOOL WriteAllUARTMessage(BYTE* pBuffer, int nLength) =0 ;
	virtual BOOL SetSwitchToInputPath(int nChInput, int n2X2Ch, int nChOutput) =0 ;
	virtual BOOL SetSwitchToOutputPath(int nChInput, int n2X2Ch, int nChOutput) =0 ;
	virtual BOOL SetSwitchToMSAInToMSAOut(int nChInput, int nChOutput) =0 ;
	virtual BOOL SetSwitchToExpendPath(int nChInput, int nChOutput) =0 ;
	virtual BOOL SetSwitchMSAIToExtendPath(int nChInput, int nChOutput) =0 ;
	virtual BOOL SetSwitchSxInToMonitor(int nChInput, int nChOutput) =0 ;
	virtual BOOL SetSwitchReferencePath(int nChOutput) =0 ;
	virtual BOOL SetSwitchMSAIMonitorPath(int nChInput, int nChOutput) =0 ;
	virtual BOOL SetSwitchMSAOToExtendPath(int nChInput, int nChOutput) =0 ;

	virtual BOOL SetVOAxAtten(BYTE bInstance, double dbAtten) =0 ;
	virtual BOOL GetVOAxAtten(BYTE bInstance, double *pdbAtten);
	virtual BOOL SetVOAxAttenToDiffrentValue(double dbAtten1, double dbAtten2) =0 ;
	virtual BOOL GetAllVOAAtten(double *pdbAtten1, double*pdbAtten2) =0 ;
	virtual BOOL SetVOAxDAC(BYTE bInstance, WORD dwDAC) =0 ;
	virtual BOOL GetVOAxDAC(BYTE bInstance, WORD* pwDAC) =0 ;
	virtual BOOL SetVOAxDACToDiffrentValue(WORD dwADC1, WORD dwADC2, WORD dwADC3, WORD dwADC4) =0 ;
	virtual BOOL GetVOAxMinIL(BYTE bInstance, double * pdbGetMinIL) =0 ;
	virtual BOOL GetAllVOAMinIL(double * pdbGetMinIL1, double*pdbGetMinIL2, double*pdbGetMinIL3) =0 ;
	virtual BOOL SetSwitchChannel(BYTE bInstance, BYTE bChannel) =0 ;
	virtual BOOL GetSwitchChannel(BYTE bInstance, BYTE* bGetChIndex) =0 ;
	virtual BOOL SetAllSwitchToDifferentChannel(BYTE bChannel, BYTE bChanne2, BYTE bChanne3, BYTE bChanne4, BYTE bChanne5, BYTE bChanne6, BYTE bChanne7, BYTE bChanne8, BYTE bChanne9) =0 ;
	virtual BOOL GetAllSwitchChannel(BYTE* bGetChArry) =0 ;
	virtual BOOL GetSwitchActualChannel(BYTE bInstance, BYTE* bGetChIndex) =0 ;
	virtual BOOL GetAllSwitchActualChannel( BYTE* bGetChArry) =0 ;
	virtual BOOL GetAllVOADAC(WORD* pwDAC1, WORD* pwDAC2, WORD* pwDAC3, WORD* pwDAC4) =0 ;

};

class CDT0ASwitchBox : public CDT0ASwitchBoxControl
{
public:
	CDT0ASwitchBox();
	virtual ~CDT0ASwitchBox();

	virtual BOOL GetVersionInfo(char *pstrPN, char *pstrSN, char *pstrEquipment, char *pstrHWVersion, char *pstrFWVersion, char *pstrOplinFWVersion, char *pstrMFGDate);
	virtual BOOL GetPNInfo(char *pstrPN);
    virtual BOOL GetSNInfo(char *pstrSN);
	virtual BOOL GetEquipmentInfo(char *pstrEquipment);
	virtual BOOL GetHWInfo(char *pstrHWVersion);
	virtual BOOL GetFWInfo(char *pstrFWVersion);
	virtual BOOL GetOplinkFWInfo(char *pstrOplinkVersion);
	virtual BOOL SetInputVOAAtten(double dbAtten);
	virtual BOOL GetInputVOAAtten(double *pdbAtten);
	virtual BOOL SetMSAVOAAtten(double dbAtten);
	virtual BOOL GetMSAVOAAtten(double *pdbAtten);
	virtual BOOL GetInputMinIL(double * pdbGetMinIL);
	virtual BOOL GetOutputMinIL(double * pdbGetMinIL);
	virtual BOOL GetMSAMinIL(double * pdbGetMinIL);
	virtual BOOL ConfigureGPIO(long nStatus);
	virtual BOOL GetGPIOConfigure(long * plStatus);
	virtual BOOL ConfigureGPIOx(BYTE bInstance, BOOL bStatus);
	virtual BOOL GetGPIOxSetPoint(BYTE bInstance, BYTE* bStatus);
	virtual BOOL SetAllInputGPIOPoint(long lStatus);
	virtual BOOL GetAllInputGPIOPoint(long * plStatus);
	virtual BOOL GetGPIOxStatus(BYTE bInstance, BYTE* bStatus);
	virtual BOOL ConfigUARTx(BYTE bInstance, DWORD dwBaudRate = 115200, BYTE bByteSize = 8, BYTE bParity = NOPARITY, BYTE bStopBits = ONESTOPBIT, DWORD dwTimeOut = 0);
	virtual BOOL ConfigAllUART(DWORD dwBaudRate = 115200, BYTE bByteSize = 8, BYTE bParity = NOPARITY, BYTE bStopBits = ONESTOPBIT, DWORD dwTimeOut = 0);
	virtual BOOL WriteUARTxMessage(BYTE bInstance, BYTE* pBuffer, int nLength);
	virtual BOOL ReadUARTxMessage(BYTE bInstance, BYTE* pBuffer, int nLength, int &nGetLength);
	virtual BOOL WriteAllUARTMessage(BYTE* pBuffer, int nLength);
	virtual BOOL SetSwitchToInputPath(int nChInput, int n2X2Ch, int nChOutput);
	virtual BOOL SetSwitchToOutputPath(int nChInput, int n2X2Ch, int nChOutput);
	virtual BOOL SetSwitchToMSAInToMSAOut(int nChInput, int nChOutput);
	virtual BOOL SetSwitchToExpendPath(int nChInput, int nChOutput);
	virtual BOOL SetSwitchMSAIToExtendPath(int nChInput, int nChOutput);
	virtual BOOL SetSwitchSxInToMonitor(int nChInput, int nChOutput);
	virtual BOOL SetSwitchReferencePath(int nChOutput);
	virtual BOOL SetSwitchMSAIMonitorPath(int nChInput, int nChOutput);
	virtual BOOL SetSwitchMSAOToExtendPath(int nChInput, int nChOutput);

	virtual BOOL SetVOAxAtten(BYTE bInstance, double dbAtten);
	virtual BOOL GetVOAxAtten(BYTE bInstance, double *pdbAtten);
	virtual BOOL SetVOAxAttenToDiffrentValue(double dbAtten1, double dbAtten2);
	virtual BOOL GetAllVOAAtten(double *pdbAtten1, double*pdbAtten2);
	virtual BOOL SetVOAxDAC(BYTE bInstance, WORD dwDAC);
	virtual BOOL GetVOAxDAC(BYTE bInstance, WORD* pwDAC);
	virtual BOOL SetVOAxDACToDiffrentValue(WORD dwADC1, WORD dwADC2, WORD dwADC3, WORD dwADC4);
	virtual BOOL GetVOAxMinIL(BYTE bInstance, double * pdbGetMinIL);
	virtual BOOL GetAllVOAMinIL(double * pdbGetMinIL1, double*pdbGetMinIL2, double*pdbGetMinIL3);
	virtual BOOL SetSwitchChannel(BYTE bInstance, BYTE bChannel);
	virtual BOOL GetSwitchChannel(BYTE bInstance, BYTE* bGetChIndex);
	virtual BOOL SetAllSwitchToDifferentChannel(BYTE bChannel, BYTE bChanne2, BYTE bChanne3, BYTE bChanne4, BYTE bChanne5, BYTE bChanne6, BYTE bChanne7, BYTE bChanne8, BYTE bChanne9);
	virtual BOOL GetAllSwitchChannel(BYTE* bGetChArry);
	virtual BOOL GetSwitchActualChannel(BYTE bInstance, BYTE* bGetChIndex);
	virtual BOOL GetAllSwitchActualChannel( BYTE* bGetChArry);
	virtual BOOL GetAllVOADAC(WORD* pwDAC1, WORD* pwDAC2, WORD* pwDAC3, WORD* pwDAC4);

	BYTE GetChecksum(BYTE* pbBuffer, int nLength);
	void AnlysisErrorString(BYTE bStatus);
	char* GetMsgString();

private:
	char m_strMsg[MAX_PATH];
	char m_strPN[64];
	char m_strSerialNumber[64];
	char m_strEquipmentNo[64];
	char m_HWVersion[64];
	char m_FWVersion[64];
	char m_strOplinkFWVersion[64];
	char m_strMFGDate[64];
	
	CCommunicationDLL m_DevComHandle;
};

#endif // !defined(AFX_PMCONTROL_H__8F680F2C_8DBB_4C0B_9B88_30A551A22F82__INCLUDED_)