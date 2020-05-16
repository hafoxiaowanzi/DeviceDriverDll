// PMControl.h: interface for the CPMControl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PMCONTROL_H__8F680F2C_8DBB_4C0B_9B88_30A551A22F82__INCLUDED_)
#define AFX_PMCONTROL_H__8F680F2C_8DBB_4C0B_9B88_30A551A22F82__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UDLReturnCode.h"
#include "Communicationudl.h"
#include "..\\include\\ScanHeader.h"

class CPMControl 
{
public:
	CPMControl();
	virtual ~CPMControl();
	virtual DWORD OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle) = 0;
	virtual DWORD CloseDevice() = 0;
	virtual DWORD SetParameters(long lSlot,long IChan, BOOL bAutoRange, double dblWavelength, double dblAvgTile, double dblPwrRange) = 0;
	virtual DWORD SetWavelength(long lSlot,long IChan, double dblWavelength) = 0;
	virtual DWORD SetUnit(long lSlot,long IChan, long lPWMUnit)=0;
	virtual DWORD SetRangeMode(long lSlot,long IChan, long bAtuo)=0;
	virtual DWORD SetRange(long lSlot,long IChan, long lRange) =0;
	virtual DWORD SetAverageTime(long lSlot,long IChan, double dblAvgTime)=0;
	virtual DWORD GetPower(long lSlot,long IChan, double* pdblPowerValue)=0;
	virtual DWORD GetUnit(long lSlot,long IChan, long* piUnit)=0;
	virtual DWORD GetWavelength(long lSlot,long IChan, double* pdblWL)=0;
	virtual DWORD GetAverageTime(long lSlot,long IChan, double* pdblAverageTime)=0;
	virtual DWORD GetRangeMode(long lSlot,long IChan,  long* iPWMRangeMode)=0;
	virtual DWORD Zero(long lSlot,long IChan)=0;
	virtual DWORD GetDeviceInfo(CHAR * pchInfo)=0;
	virtual DWORD SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle) = 0;
	virtual DWORD PrepareScan(long lSlot,long lChIndex,stScanParam* lScanParam)= 0;
	virtual DWORD SetPMScanStart(long lSlot,long lChIndex)= 0;
	virtual DWORD getLambdaScanPMResult(long lSlot,long lChIndex,double* pdbPMArry)= 0;
	virtual DWORD SetPMScanStop(long lSlot,long lChIndex)= 0;
	virtual DWORD SetPMScanTriggerStop(long lSlot,long lChIndex)= 0;
	virtual DWORD SetPMMaxMinPowerStart(long lSlot,long IChan) =0;
	virtual DWORD GetPMMaxMinPower(long lSlot,long IChan,double *pdbGetMax,double *pdbGetMin)=0;
	virtual DWORD SetPMMinMaxStop(long lSlot,long IChan)=0;
	virtual DWORD SetPMPowerOffset(long lSlot,long IChan,double dbPowerOffset)=0;
};

class  CN7745PM: public CPMControl  
{
public:
	CN7745PM();
	virtual ~CN7745PM();

	virtual DWORD OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle);
	virtual DWORD CloseDevice();
	virtual DWORD SetParameters(long lSlot,long IChan, BOOL bAutoRange, double dblWavelength, double dblAvgTile, double dblPwrRange);
	virtual DWORD SetWavelength(long lSlot,long IChan, double dblWavelength);
	virtual DWORD SetUnit(long lSlot,long IChan, long lPWMUnit);
	virtual DWORD SetRangeMode(long lSlot,long IChan, long bAtuo);
	virtual DWORD SetRange(long lSlot,long IChan, long lRange);
	virtual DWORD SetAverageTime(long lSlot,long IChan, double dblAvgTime);
	virtual DWORD GetPower(long lSlot,long IChan, double* pdblPowerValue);
	virtual DWORD GetUnit(long lSlot,long IChan, long* piUnit);
	virtual DWORD GetWavelength(long lSlot,long IChan, double* pdblWL);
	virtual DWORD GetAverageTime(long lSlot,long IChan, double* pdblAverageTime);
	virtual DWORD GetRangeMode(long lSlot,long IChan,  long* iPWMRangeMode);
	virtual DWORD Zero(long lSlot,long IChan);
	virtual DWORD GetDeviceInfo(CHAR * pchInfo);
	virtual DWORD SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle);
	virtual DWORD PrepareScan(long lSlot,long lChIndex,stScanParam* lScanParam);
	virtual DWORD SetPMScanStart(long lSlot,long lChIndex);
	virtual DWORD getLambdaScanPMResult(long lSlot,long lChIndex,double* pdbPMArry);
	virtual DWORD SetPMScanStop(long lSlot,long lChIndex);
	virtual DWORD SetPMScanTriggerStop(long lSlot,long lChIndex);
	virtual DWORD SetPMMaxMinPowerStart(long lSlot,long IChan);
	virtual DWORD GetPMMaxMinPower(long lSlot,long IChan,double *pdbGetMax,double *pdbGetMin);
	virtual DWORD SetPMMinMaxStop(long lSlot,long IChan);
	virtual DWORD SetPMPowerOffset(long lSlot,long IChan,double dbPowerOffset);
	
private:
	DWORD GetRange(long lSlot,long IChan, double &dblRange);
    DWORD CompleteQuery();
	DWORD ReadPower(long lSlot,long iChan, double* pdblPower);
	CCommunicationDLL m_Comm;
	stScanParam* m_pScanParam;
	DWORD m_dwScanPoint;
	BOOL m_bDummyAutoEnbale;
	double m_dblAutoPowerRng;
	double m_dblPMAvgTime;
};

class COp8163A  : public CPMControl 
{
public:
	COp8163A();
	virtual ~COp8163A();

	virtual DWORD OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle);
	virtual DWORD CloseDevice();
	virtual DWORD SetParameters(long lSlot,long IChan, BOOL bAutoRange, double dblWavelength, double dblAvgTile, double dblPwrRange);
	virtual DWORD SetWavelength(long lSlot,long IChan, double dblWavelength);
	virtual DWORD SetUnit(long lSlot,long IChan, long lPWMUnit);
	virtual DWORD SetRangeMode(long lSlot,long IChan, long bAtuo);
	virtual DWORD SetRange(long lSlot,long IChan, long lRange);
	virtual DWORD SetAverageTime(long lSlot,long IChan, double dblAvgTime);
	virtual DWORD GetPower(long lSlot,long IChan, double* pdblPowerValue);
	virtual DWORD GetUnit(long lSlot,long IChan, long* piUnit);
	virtual DWORD GetWavelength(long lSlot,long IChan, double* pdblWL);
	virtual DWORD GetAverageTime(long lSlot,long IChan, double* pdblAverageTime);
	virtual DWORD GetRangeMode(long lSlot,long IChan,  long* iPWMRangeMode);
	virtual DWORD Zero(long lSlot,long IChan);
	virtual DWORD GetDeviceInfo(CHAR * pchInfo);
	virtual DWORD SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle);
	virtual DWORD PrepareScan(long lSlot,long lChIndex,stScanParam* lScanParam);
	virtual DWORD SetPMScanStart(long lSlot,long lChIndex);
	virtual DWORD getLambdaScanPMResult(long lSlot,long lChIndex,double* pdbPMArry);
	virtual DWORD SetPMScanStop(long lSlot,long lChIndex);
	virtual DWORD SetPMScanTriggerStop(long lSlot,long lChIndex);
	virtual DWORD SetPMMaxMinPowerStart(long lSlot,long IChan);
	virtual DWORD GetPMMaxMinPower(long lSlot,long IChan,double *pdbGetMax,double *pdbGetMin);
	virtual DWORD SetPMMinMaxStop(long lSlot,long IChan);
	virtual DWORD SetPMPowerOffset(long lSlot,long IChan,double dbPowerOffset);
protected:	
	DWORD GetGPIBAress(long *dblGpibAddress);
	DWORD SetGPIBAress(long dblGpibAddress);
	DWORD CompleteQuery();
	CCommunicationDLL m_Comm;
	stScanParam* m_pScanParam;
	DWORD m_dwScanPoint;
};

class OplinkPM : public CPMControl   
{
public:
	OplinkPM();
	virtual ~OplinkPM();

	virtual DWORD OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle);
	virtual DWORD CloseDevice();
	virtual DWORD SetParameters(long lSlot,long IChan, BOOL bAutoRange, double dblWavelength, double dblAvgTile, double dblPwrRange);
	virtual DWORD SetWavelength(long lSlot,long IChan, double dblWavelength);
	virtual DWORD SetUnit(long lSlot,long IChan, long lPWMUnit);
	virtual DWORD SetRangeMode(long lSlot,long IChan, long bAtuo);
	virtual DWORD SetRange(long lSlot,long IChan, long lRange);
	virtual DWORD SetAverageTime(long lSlot,long IChan, double dblAvgTime);
	virtual DWORD GetPower(long lSlot,long IChan, double* pdblPowerValue);
	virtual DWORD GetUnit(long lSlot,long IChan, long* piUnit);
	virtual DWORD GetWavelength(long lSlot,long IChan, double* pdblWL);
	virtual DWORD GetAverageTime(long lSlot,long IChan, double* pdblAverageTime);
	virtual DWORD GetRangeMode(long lSlot,long IChan,  long* iPWMRangeMode);
	virtual DWORD Zero(long lSlot,long IChan);
	virtual DWORD GetDeviceInfo(CHAR * pchInfo);
	virtual DWORD SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle);

    virtual DWORD PrepareScan(long lSlot,long lChIndex,stScanParam* lScanParam);
	virtual DWORD SetPMScanStart(long lSlot,long lChIndex);
	virtual DWORD getLambdaScanPMResult(long lSlot,long lChIndex,double* pdbPMArry);
	virtual DWORD SetPMScanStop(long lSlot,long lChIndex);
	virtual DWORD SetPMScanTriggerStop(long lSlot,long lChIndex);
	virtual DWORD SetPMMaxMinPowerStart(long lSlot,long IChan);
	virtual DWORD GetPMMaxMinPower(long lSlot,long IChan,double *pdbGetMax,double *pdbGetMin);
	virtual DWORD SetPMMinMaxStop(long lSlot,long IChan);
	virtual DWORD SetPMPowerOffset(long lSlot,long IChan,double dbPowerOffset);

protected:
	DWORD SetCalibrate(long lSlot,long IChan);
	BOOL SetWLByIP(long iSlot, long iChannel, double dblWL);
	BOOL SetWLByPort(long iSlot, long iChannel, double dblWL);
	CCommunicationDLL m_Comm;
	BOOL	g_bLinkIp;
	long    g_lLinkType;
	BOOL g_bLinkIP;
	
};

class CPM1830C : public CPMControl  
{	
public:
	CPM1830C();
	virtual ~CPM1830C();

	virtual DWORD OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle);
	virtual DWORD CloseDevice();
	virtual DWORD SetParameters(long lSlot,long IChan, BOOL bAutoRange, double dblWavelength, double dblAvgTile, double dblPwrRange);
	virtual DWORD SetWavelength(long lSlot,long IChan, double dblWavelength);
	virtual DWORD SetUnit(long lSlot,long IChan, long lPWMUnit);
	virtual DWORD SetRangeMode(long lSlot,long IChan, long bAtuo);
	virtual DWORD SetRange(long lSlot,long IChan, long lRange);
	virtual DWORD SetAverageTime(long lSlot,long IChan, double dblAvgTime);
	virtual DWORD GetPower(long lSlot,long IChan, double* pdblPowerValue);
	virtual DWORD GetUnit(long lSlot,long IChan, long* piUnit);
	virtual DWORD GetWavelength(long lSlot,long IChan, double* pdblWL);
	virtual DWORD GetAverageTime(long lSlot,long IChan, double* pdblAverageTime);
	virtual DWORD GetRangeMode(long lSlot,long IChan,  long* iPWMRangeMode);
	virtual DWORD Zero(long lSlot,long IChan);
	virtual DWORD GetDeviceInfo(CHAR * pchInfo);
	virtual DWORD SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle);

	virtual DWORD PrepareScan(long lSlot,long lChIndex,stScanParam* lScanParam);
	virtual DWORD SetPMScanStart(long lSlot,long lChIndex);
	virtual DWORD getLambdaScanPMResult(long lSlot,long lChIndex,double* pdbPMArry);
	virtual DWORD SetPMScanStop(long lSlot,long lChIndex);
	virtual DWORD SetPMScanTriggerStop(long lSlot,long lChIndex);
	virtual DWORD SetPMMaxMinPowerStart(long lSlot,long IChan);
	virtual DWORD GetPMMaxMinPower(long lSlot,long IChan,double *pdbGetMax,double *pdbGetMin);	
	virtual DWORD SetPMMinMaxStop(long lSlot,long IChan);
	virtual DWORD SetPMPowerOffset(long lSlot,long IChan,double dbPowerOffset);
protected:
//	stDevType m_PMInfo;
	BOOL GetErrorMessage(DWORD dwErrorCode,char *pszErrorMsg);
	BOOL SetStoRef();   //归零
	BOOL SetEcho(BOOL bEchoOff = TRUE);
	CCommunicationDLL m_DevComHandle;
};

class CPMJH : public CPMControl  
{
public:
	CPMJH();
	virtual ~CPMJH();

	virtual DWORD OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle);
	virtual DWORD CloseDevice();
	virtual DWORD SetParameters(long lSlot,long IChan, BOOL bAutoRange, double dblWavelength, double dblAvgTile, double dblPwrRange);
	virtual DWORD SetWavelength(long lSlot,long IChan, double dblWavelength);
	virtual DWORD SetUnit(long lSlot,long IChan, long lPWMUnit);
	virtual DWORD SetRangeMode(long lSlot,long IChan, long bAtuo);
	virtual DWORD SetRange(long lSlot,long IChan, long lRange);
	virtual DWORD SetAverageTime(long lSlot,long IChan, double dblAvgTime);
	virtual DWORD GetPower(long lSlot,long IChan, double* pdblPowerValue);
	virtual DWORD GetUnit(long lSlot,long IChan, long* piUnit);
	virtual DWORD GetWavelength(long lSlot,long IChan, double* pdblWL);
	virtual DWORD GetAverageTime(long lSlot,long IChan, double* pdblAverageTime);
	virtual DWORD GetRangeMode(long lSlot,long IChan,  long* iPWMRangeMode);
	virtual DWORD Zero(long lSlot,long IChan);
	virtual DWORD GetDeviceInfo(CHAR * pchInfo);
	virtual DWORD SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle);

	virtual DWORD PrepareScan(long lSlot,long lChIndex,stScanParam* lScanParam);
	virtual DWORD SetPMScanStart(long lSlot,long lChIndex);
	virtual DWORD getLambdaScanPMResult(long lSlot,long lChIndex,double* pdbPMArry);
	virtual DWORD SetPMScanStop(long lSlot,long lChIndex);
	virtual DWORD SetPMScanTriggerStop(long lSlot,long lChIndex);
	virtual DWORD SetPMMaxMinPowerStart(long lSlot,long IChan);
	virtual DWORD GetPMMaxMinPower(long lSlot,long IChan,double *pdbGetMax,double *pdbGetMin);
	virtual DWORD SetPMMinMaxStop(long lSlot,long IChan);
	virtual DWORD SetPMPowerOffset(long lSlot,long IChan,double dbPowerOffset);
private:
//	stDevType m_PMInfo;
	CCommunicationDLL m_DevComHandle;
	DWORD SelectCh(int nChIndex);
	DWORD ReadJHPower(long lSlot,long lChIndex,double &dblPower);
	DWORD ReadPower(long lSlot,long lChIndex, double* pdbReadPower);
	DWORD SetMode(long lSlot,long lChIndex,DWORD dwMode);
	DWORD StopReadJHPower();
	DWORD StartReadJHPower();

	DWORD GetMode(long lSlot,long lChIndex,DWORD &dwMode);
	BOOL GetErrorMessage(DWORD dwErrorCode,char *pszErrorMsg);
	double		m_dbOldSetWL;//相差0.5NM 的不给设置
};



class COplink1830C : public CPMControl  
{	
public:
	COplink1830C();
	virtual ~COplink1830C();

	virtual DWORD OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle);
	virtual DWORD CloseDevice();
	virtual DWORD SetParameters(long lSlot,long IChan, BOOL bAutoRange, double dblWavelength, double dblAvgTile, double dblPwrRange);
	virtual DWORD SetWavelength(long lSlot,long IChan, double dblWavelength);
	virtual DWORD SetUnit(long lSlot,long IChan, long lPWMUnit);
	virtual DWORD SetRangeMode(long lSlot,long IChan, long bAtuo);
	virtual DWORD SetRange(long lSlot,long IChan, long lRange);
	virtual DWORD SetAverageTime(long lSlot,long IChan, double dblAvgTime);
	virtual DWORD GetPower(long lSlot,long IChan, double* pdblPowerValue);
	virtual DWORD GetUnit(long lSlot,long IChan, long* piUnit);
	virtual DWORD GetWavelength(long lSlot,long IChan, double* pdblWL);
	virtual DWORD GetAverageTime(long lSlot,long IChan, double* pdblAverageTime);
	virtual DWORD GetRangeMode(long lSlot,long IChan,  long* iPWMRangeMode);
	virtual DWORD Zero(long lSlot,long IChan);
	virtual DWORD GetDeviceInfo(CHAR * pchInfo);
	virtual DWORD SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle);

	virtual DWORD PrepareScan(long lSlot,long lChIndex,stScanParam* lScanParam);
	virtual DWORD SetPMScanStart(long lSlot,long lChIndex);
	virtual DWORD getLambdaScanPMResult(long lSlot,long lChIndex,double* pdbPMArry);
	virtual DWORD SetPMScanStop(long lSlot,long lChIndex);
	virtual DWORD SetPMScanTriggerStop(long lSlot,long lChIndex);
	virtual DWORD SetPMMaxMinPowerStart(long lSlot,long IChan);
	virtual DWORD GetPMMaxMinPower(long lSlot,long IChan,double *pdbGetMax,double *pdbGetMin);	
	virtual DWORD SetPMMinMaxStop(long lSlot,long IChan);
	virtual DWORD SetPMPowerOffset(long lSlot,long IChan,double dbPowerOffset);
protected:
//	stDevType m_PMInfo;
	BOOL GetErrorMessage(DWORD dwErrorCode,char *pszErrorMsg);
	BOOL SetStoRef(long lSlot,long lChIndex);   //归零
	BOOL SetEcho(long lSlot,long lChIndex,BOOL bEchoOff = TRUE);
	CCommunicationDLL m_DevComHandle;
};
class COp8153A  : public CPMControl 
{
public:
	COp8153A();
	virtual ~COp8153A();

	virtual DWORD OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle);
	virtual DWORD CloseDevice();
	virtual DWORD SetParameters(long lSlot,long IChan, BOOL bAutoRange, double dblWavelength, double dblAvgTile, double dblPwrRange);
	virtual DWORD SetWavelength(long lSlot,long IChan, double dblWavelength);
	virtual DWORD SetUnit(long lSlot,long IChan, long lPWMUnit);
	virtual DWORD SetRangeMode(long lSlot,long IChan, long bAtuo);
	virtual DWORD SetRange(long lSlot,long IChan, long lRange);
	virtual DWORD SetAverageTime(long lSlot,long IChan, double dblAvgTime);
	virtual DWORD GetPower(long lSlot,long IChan, double* pdblPowerValue);
	virtual DWORD GetUnit(long lSlot,long IChan, long* piUnit);
	virtual DWORD GetWavelength(long lSlot,long IChan, double* pdblWL);
	virtual DWORD GetAverageTime(long lSlot,long IChan, double* pdblAverageTime);
	virtual DWORD GetRangeMode(long lSlot,long IChan,  long* iPWMRangeMode);
	virtual DWORD Zero(long lSlot,long IChan);
	virtual DWORD GetDeviceInfo(CHAR * pchInfo);
	virtual DWORD SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle);
	virtual DWORD PrepareScan(long lSlot,long lChIndex,stScanParam* lScanParam);
	virtual DWORD SetPMScanStart(long lSlot,long lChIndex);
	virtual DWORD getLambdaScanPMResult(long lSlot,long lChIndex,double* pdbPMArry);
	virtual DWORD SetPMScanStop(long lSlot,long lChIndex);
	virtual DWORD SetPMScanTriggerStop(long lSlot,long lChIndex);
	virtual DWORD SetPMMaxMinPowerStart(long lSlot,long IChan);
	virtual DWORD GetPMMaxMinPower(long lSlot,long IChan,double *pdbGetMax,double *pdbGetMin);
	virtual DWORD SetPMMinMaxStop(long lSlot,long IChan);
	virtual DWORD SetPMPowerOffset(long lSlot,long IChan,double dbPowerOffset);
protected:	
	DWORD GetGPIBAress(long *dblGpibAddress);
	DWORD SetGPIBAress(long dblGpibAddress);
	DWORD CompleteQuery();
	CCommunicationDLL m_Comm;
	stScanParam* m_pScanParam;
	DWORD m_dwScanPoint;
};

class CAQ2200_215  : public CPMControl 
{
public:
	CAQ2200_215();
	virtual ~CAQ2200_215();

	virtual DWORD OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle);
	virtual DWORD CloseDevice();
	virtual DWORD SetParameters(long lSlot,long IChan, BOOL bAutoRange, double dblWavelength, double dblAvgTile, double dblPwrRange);
	virtual DWORD SetWavelength(long lSlot,long IChan, double dblWavelength);
	virtual DWORD SetUnit(long lSlot,long IChan, long lPWMUnit);
	virtual DWORD SetRangeMode(long lSlot,long IChan, long bAtuo);
	virtual DWORD SetRange(long lSlot,long IChan, long lRange);
	virtual DWORD SetAverageTime(long lSlot,long IChan, double dblAvgTime);
	virtual DWORD GetPower(long lSlot,long IChan, double* pdblPowerValue);
	virtual DWORD GetUnit(long lSlot,long IChan, long* piUnit);
	virtual DWORD GetWavelength(long lSlot,long IChan, double* pdblWL);
	virtual DWORD GetAverageTime(long lSlot,long IChan, double* pdblAverageTime);
	virtual DWORD GetRangeMode(long lSlot,long IChan,  long* iPWMRangeMode);
	virtual DWORD Zero(long lSlot,long IChan);
	virtual DWORD GetDeviceInfo(CHAR * pchInfo);
	virtual DWORD SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle);

	virtual DWORD PrepareScan(long lSlot,long lChIndex,stScanParam* lScanParam);
	virtual DWORD SetPMScanStart(long lSlot,long lChIndex);
	virtual DWORD getLambdaScanPMResult(long lSlot,long lChIndex,double* pdbPMArry);
	virtual DWORD SetPMScanStop(long lSlot,long lChIndex);
	virtual DWORD SetPMScanTriggerStop(long lSlot,long lChIndex);
	virtual DWORD SetPMMaxMinPowerStart(long lSlot,long IChan);
	virtual DWORD GetPMMaxMinPower(long lSlot,long IChan,double *pdbGetMax,double *pdbGetMin);
	virtual DWORD SetPMMinMaxStop(long lSlot,long IChan);
	virtual DWORD SetPMPowerOffset(long lSlot,long IChan,double dbPowerOffset);

	virtual DWORD SetCalibrationValue(long IChan, double dblCalValue);
	virtual DWORD GetCalibrationValue(long IChan, double *dblCalValue);
	
	DWORD GetGPIBAress(long *dblGpibAddress);
	DWORD SetGPIBAress(long dblGpibAddress);
	DWORD CompleteQuery();
protected:	
	CCommunicationDLL m_Comm;
};


class CAQ2140  : public CPMControl 
{
public:
	CAQ2140();
	virtual ~CAQ2140();

	virtual DWORD OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle);
	virtual DWORD CloseDevice();
	virtual DWORD SetParameters(long lSlot,long IChan, BOOL bAutoRange, double dblWavelength, double dblAvgTile, double dblPwrRange);
	virtual DWORD SetWavelength(long lSlot,long IChan, double dblWavelength);
	virtual DWORD SetUnit(long lSlot,long IChan, long lPWMUnit);
	virtual DWORD SetRangeMode(long lSlot,long IChan, long bAtuo);
	virtual DWORD SetRange(long lSlot,long IChan, long lRange);
	virtual DWORD SetAverageTime(long lSlot,long IChan, double dblAvgTime);
	virtual DWORD GetPower(long lSlot,long IChan, double* pdblPowerValue);
	virtual DWORD GetUnit(long lSlot,long IChan, long* piUnit);
	virtual DWORD GetWavelength(long lSlot,long IChan, double* pdblWL);
	virtual DWORD GetAverageTime(long lSlot,long IChan, double* pdblAverageTime);
	virtual DWORD GetRangeMode(long lSlot,long IChan,  long* iPWMRangeMode);
	virtual DWORD Zero(long lSlot,long IChan);
	virtual DWORD GetDeviceInfo(CHAR * pchInfo);
	virtual DWORD SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle);

	virtual DWORD PrepareScan(long lSlot,long lChIndex,stScanParam* lScanParam);
	virtual DWORD SetPMScanStart(long lSlot,long lChIndex);
	virtual DWORD getLambdaScanPMResult(long lSlot,long lChIndex,double* pdbPMArry);
	virtual DWORD SetPMScanStop(long lSlot,long lChIndex);
	virtual DWORD SetPMScanTriggerStop(long lSlot,long lChIndex);
	virtual DWORD SetPMMaxMinPowerStart(long lSlot,long IChan);
	virtual DWORD GetPMMaxMinPower(long lSlot,long IChan,double *pdbGetMax,double *pdbGetMin);
	virtual DWORD SetPMMinMaxStop(long lSlot,long IChan);
	virtual DWORD SetPMPowerOffset(long lSlot,long IChan,double dbPowerOffset);

	virtual DWORD SetCalibrationValue(long IChan, double dblCalValue);
	virtual DWORD GetCalibrationValue(long IChan, double *dblCalValue);
	
	DWORD GetGPIBAress(long *dblGpibAddress);
	DWORD SetGPIBAress(long dblGpibAddress);
//	DWORD CompleteQuery();
protected:	
	CCommunicationDLL m_Comm;
	BOOL SelectSlot(int nSlot);
};


#endif // !defined(AFX_PMCONTROL_H__8F680F2C_8DBB_4C0B_9B88_30A551A22F82__INCLUDED_)
