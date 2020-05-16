// TLSControl.h: interface for the CTLSControl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TLSCONTROL_H__475C20EC_0F1A_44B6_B3E6_3CA7A076F14C__INCLUDED_)
#define AFX_TLSCONTROL_H__475C20EC_0F1A_44B6_B3E6_3CA7A076F14C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UDLReturnCode.h"
#include "Communicationudl.h"
#include "..\\include\\ScanHeader.h"



class CTLSControl  
{
public:
	CTLSControl();
	virtual ~CTLSControl();
	virtual DWORD OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle) = 0;
	virtual DWORD SetWavelength(long lChIndex, double dblWL) = 0;
	virtual DWORD SetSourcePower(long lChIndex, double dblPW) = 0;
	virtual DWORD SetCoherenceControl(BOOL bEnable) = 0;
	virtual DWORD SetSourceUnit(long lChIndex, long dblAtten) = 0;
	virtual DWORD SetParameters(long lChIndex, BOOL bLowSSE, double dblPower, double dblWavelength) = 0;
	virtual DWORD SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle) = 0;
	virtual DWORD SetOutputEnable(BOOL bEnable) = 0;
	virtual DWORD CloseDevice() = 0;
	virtual DWORD PrepareScan(long lChIndex,stScanParam* lScanParam)=0;
	virtual DWORD SetScanStart(long lChIndex)=0;
	virtual DWORD SetScanStop(long lChIndex)=0;
	virtual DWORD GetLamdaScanWLResult(long lChIndex,double* pdbWLAarry)=0;
	virtual DWORD SetMaxOutput(long lChIndex)=0;
	virtual DWORD SetTLSFrequency(long lChIndex,double dblFrequrency)=0;
	virtual DWORD GetTLSSettings(long lChIndex,double* pdblWavelength,double* pdblPower,BYTE* pdCtrlState)=0;
	virtual DWORD SetTLSSlotIndex(int nSlotIndex)=0;
};

class COp816XCtrl : public CTLSControl
{
public:
	COp816XCtrl();
	virtual ~COp816XCtrl();

	virtual DWORD OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle);
	virtual DWORD SetWavelength(long lChIndex, double dblWL);
	virtual DWORD SetSourcePower(long lChIndex, double dblPW);
	virtual DWORD SetCoherenceControl(BOOL bEnable);
	virtual DWORD SetSourceUnit(long lChIndex, long dblAtten);
	virtual DWORD SetParameters(long lChIndex, BOOL bLowSSE, double dblPower, double dblWavelength);
	virtual DWORD SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle);
	virtual DWORD SetOutputEnable(BOOL bEnable);
	virtual DWORD CloseDevice();
	virtual DWORD PrepareScan(long lChIndex,stScanParam* lScanParam);
	virtual DWORD SetScanStart(long lChIndex);
	virtual DWORD SetScanStop(long lChIndex);
	virtual DWORD GetLamdaScanWLResult(long lChIndex,double* pdbWLAarry);
	virtual DWORD SetMaxOutput(long lChIndex);
	virtual DWORD SetTLSFrequency(long lChIndex,double dblFrequrency);
	virtual DWORD GetTLSSettings(long lChIndex,double* pdblWavelength,double* pdblPower,BYTE* pdCtrlState);
	virtual DWORD SetTLSSlotIndex(int nSlotIndex);
private:
	
	DWORD GetTLSWLRange(double &dbWLMin,double &dbWLMax);
	DWORD GetScanWLRange(double &dbStartWL,double &dbStopWL);
	DWORD ScanStart();
	BOOL GetScanParameter(stScanParam *pSettingParam);
	DWORD ReadTLSPower(double &dbPower);
	BOOL JudgeScanParameter();
	BOOL SetScanStop();
	BOOL SetScanWLRange(double dbWLStart,double dbWLStop);
	BOOL SetTLSPower(double dbPower);
	CCommunicationDLL m_Comm;
	PScanParam m_pScanParam;
	DWORD m_dwScanPoint;
	int m_nSlotIndex;
	
};

class CSantecTLS : public CTLSControl
{
public:
	CSantecTLS();
	virtual ~CSantecTLS();

	virtual DWORD OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle);
	virtual DWORD SetWavelength(long lChIndex, double dblWL);
	virtual DWORD SetSourcePower(long lChIndex, double dblPW);
	virtual DWORD SetCoherenceControl(BOOL bEnable);
	virtual DWORD SetSourceUnit(long lChIndex, long dblAtten);
	virtual DWORD SetParameters(long lChIndex,BOOL bLowSSE, double dblPower, double dblWavelength);
	virtual DWORD SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle);
	virtual DWORD SetOutputEnable(BOOL bEnable);
	virtual DWORD CloseDevice();

	virtual DWORD PrepareScan(long lChIndex,stScanParam* lScanParam);
	virtual DWORD SetScanStart(long lChIndex);
	virtual DWORD SetScanStop(long lChIndex);
	virtual DWORD GetLamdaScanWLResult(long lChIndex,double* pdbWLAarry);
	virtual DWORD SetMaxOutput(long lChIndex);
	virtual DWORD SetTLSFrequency(long lChIndex,double dblFrequrency);
	virtual DWORD GetTLSSettings(long lChIndex,double* pdblWavelength,double* pdblPower,BYTE* pdCtrlState);
	virtual DWORD SetTLSSlotIndex(int nSlotIndex);

private:
	CCommunicationDLL m_Comm;
	PScanParam m_pScanParam;
	DWORD m_dwScanPoint;
	int m_nSlotIndex;
	
//	BOOL GetDeviceDescription(char *szBuf,int nsize);
//	void SetGPIBAddress( long laddress);
	
};

class CiTLALaser : public CTLSControl
{
public:
	CiTLALaser();
	virtual ~CiTLALaser();

	virtual DWORD OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle);
	virtual DWORD SetWavelength(long lChIndex, double dblWL);
	virtual DWORD SetSourcePower(long lChIndex, double dblPW);
	virtual DWORD SetCoherenceControl(BOOL bEnable);
	virtual DWORD SetSourceUnit(long lChIndex, long dblAtten);
	virtual DWORD SetParameters(long lChIndex, BOOL bLowSSE,double dblPower, double dblWavelength);
	virtual DWORD SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle);
	virtual DWORD SetOutputEnable(BOOL bEnable);
	virtual DWORD CloseDevice();
	virtual DWORD PrepareScan(long lChIndex,stScanParam* lScanParam);
	virtual DWORD SetScanStart(long lChIndex);
	virtual DWORD SetScanStop(long lChIndex);
	virtual DWORD GetLamdaScanWLResult(long lChIndex,double* pdbWLAarry);
	virtual DWORD SetMaxOutput(long lChIndex);
	virtual DWORD SetTLSFrequency(long lChIndex,double dblFrequrency);
	virtual DWORD GetTLSSettings(long lChIndex,double* pdblWavelength,double* pdblPower,BYTE* pdCtrlState);
	virtual DWORD SetTLSSlotIndex(int nSlotIndex);

private:
	CCommunicationDLL m_Comm;
	PScanParam m_pScanParam;
	DWORD m_dwScanPoint;
	BOOL GetDeviceConfig();
	DWORD GetDeviceVersion(int *nType);
	int m_nTypeVerion;
	
	double m_dblMinPower;
	double m_dblMaxPower;
	long m_lMinChannelNum;
	long m_lMaxChannelNum;
	long m_lMinFrequency;
	long m_lMaxFrequency;
	long m_lFrequencyGrid;
	int m_nSlotIndex;
	
};


class COp81960A : public CTLSControl
{
public:
	COp81960A();
	virtual ~COp81960A();

	virtual DWORD OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle);
	virtual DWORD SetWavelength(long lChIndex, double dblWL);
	virtual DWORD SetSourcePower(long lChIndex, double dblPW);
	virtual DWORD SetCoherenceControl(BOOL bEnable);
	virtual DWORD SetSourceUnit(long lChIndex, long dblAtten);
	virtual DWORD SetParameters(long lChIndex, BOOL bLowSSE, double dblPower, double dblWavelength);
	virtual DWORD SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle);
	virtual DWORD SetOutputEnable(BOOL bEnable);
	virtual DWORD CloseDevice();
	virtual DWORD PrepareScan(long lChIndex,stScanParam* lScanParam);
	virtual DWORD SetScanStart(long lChIndex);
	virtual DWORD SetScanStop(long lChIndex);
	virtual DWORD GetLamdaScanWLResult(long lChIndex,double* pdbWLAarry);
	virtual DWORD SetMaxOutput(long lChIndex);
	virtual DWORD SetTLSFrequency(long lChIndex,double dblFrequrency);
	virtual DWORD GetTLSSettings(long lChIndex,double* pdblWavelength,double* pdblPower,BYTE* pdCtrlState);
	virtual DWORD SetTLSSlotIndex(int nSlotIndex);
private:
	
	DWORD GetTLSWLRange(double &dbWLMin,double &dbWLMax);
	DWORD GetScanWLRange(double &dbStartWL,double &dbStopWL);
	DWORD ScanStart();
	BOOL GetScanParameter(stScanParam *pSettingParam);
	DWORD ReadTLSPower(double &dbPower);
	BOOL JudgeScanParameter();
	BOOL SetScanStop();
	BOOL SetScanWLRange(double dbWLStart,double dbWLStop);
	BOOL SetTLSPower(double dbPower);
	CCommunicationDLL m_Comm;
	PScanParam m_pScanParam;
	DWORD m_dwScanPoint;
	int m_nSlotIndex;	
};

class CAQ2200_136 : public CTLSControl
{
public:
	CAQ2200_136();
	virtual ~CAQ2200_136();

	virtual DWORD OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle);
	virtual DWORD SetWavelength(long lChIndex, double dblWL);
	virtual DWORD SetSourcePower(long lChIndex, double dblPW);
	virtual DWORD SetCoherenceControl(BOOL bEnable);
	virtual DWORD SetSourceUnit(long lChIndex, long dblAtten);
	virtual DWORD SetParameters(long lChIndex, BOOL bLowSSE, double dblPower, double dblWavelength);
	virtual DWORD SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle);
	virtual DWORD SetOutputEnable(BOOL bEnable);
	virtual DWORD CloseDevice();
	virtual DWORD PrepareScan(long lChIndex,stScanParam* lScanParam);
	virtual DWORD SetScanStart(long lChIndex);
	virtual DWORD SetScanStop(long lChIndex);
	virtual DWORD GetLamdaScanWLResult(long lChIndex,double* pdbWLAarry);
	virtual DWORD SetMaxOutput(long lChIndex);
	virtual DWORD SetTLSFrequency(long lChIndex,double dblFrequrency);
	virtual DWORD GetTLSSettings(long lChIndex,double* pdblWavelength,double* pdblPower,BYTE* pdCtrlState);
	virtual DWORD SetTLSSlotIndex(int nSlotIndex);

private:
//	DWORD SetAttenuation(long lChIndex, double dblAtten);
	CCommunicationDLL m_Comm;
	int m_nSlotIndex;
};

class CHP8168ETLS : public CTLSControl
{
public:
	CHP8168ETLS();
	virtual ~CHP8168ETLS();

	virtual DWORD OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle);
	virtual DWORD SetWavelength(long lChIndex, double dblWL);
	virtual DWORD SetSourcePower(long lChIndex, double dblPW);
	virtual DWORD SetCoherenceControl(BOOL bEnable);
	virtual DWORD SetSourceUnit(long lChIndex, long dblAtten);
	virtual DWORD SetParameters(long lChIndex, BOOL bLowSSE, double dblPower, double dblWavelength);
	virtual DWORD SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle);
	virtual DWORD SetOutputEnable(BOOL bEnable);
	virtual DWORD CloseDevice();
	virtual DWORD PrepareScan(long lChIndex,stScanParam* lScanParam);
	virtual DWORD SetScanStart(long lChIndex);
	virtual DWORD SetScanStop(long lChIndex);
	virtual DWORD GetLamdaScanWLResult(long lChIndex,double* pdbWLAarry);
	virtual DWORD SetMaxOutput(long lChIndex);
	virtual DWORD SetTLSFrequency(long lChIndex,double dblFrequrency);
	virtual DWORD GetTLSSettings(long lChIndex,double* pdblWavelength,double* pdblPower,BYTE* pdCtrlState);
	virtual DWORD SetTLSSlotIndex(int nSlotIndex);
private:
	DWORD ReadTLSPower(double &dbPower);
    BOOL SetTLSPower(double dbPower);
	CCommunicationDLL m_Comm;
	PScanParam m_pScanParam;
	DWORD m_dwScanPoint;
	int m_nSlotIndex;
	
};

#endif // !defined(AFX_TLSCONTROL_H__475C20EC_0F1A_44B6_B3E6_3CA7A076F14C__INCLUDED_)
