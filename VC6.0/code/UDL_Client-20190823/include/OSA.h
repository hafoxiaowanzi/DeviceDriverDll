// OSAControl.h: interface for the COSAControl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OSACONTROL_H__8AD5CA80_E88A_4575_B33A_8EDFE709430E__INCLUDED_)
#define AFX_OSACONTROL_H__8AD5CA80_E88A_4575_B33A_8EDFE709430E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UDLReturnCode.h"
#include "Communicationudl.h"
#include "NFLib.h"

#define	SRC_SCAN							0
#define	AMP_SCAN							1

#define MAX_FIELD 8192
#define MAX_COMM_FIELD 900000
#define FLAG_READ_SUCCESS '#'

//#define MAX_SCAN_DATA			2024
#define SWEEPPOINT				5001

#define dbTomw(dbm) pow(10,double(dbm)/10)
#define mwTodb(mw) (((double)log10(mw))*10)


class COSAControl 
{
public:
	COSAControl();
	virtual ~COSAControl();

	virtual DWORD OpenDevice(stDevType stType, char* pszDeviceAddr, unsigned long *comHandle) = 0;
	virtual DWORD CloseDevice() = 0;
	virtual DWORD ResetDevice(void) = 0;
	virtual DWORD SetOSALocalCtrl(void) = 0;
	virtual DWORD SetRBW(double dblRBW) = 0;
	virtual DWORD GetRBW(double* pdblRBW) = 0;
	virtual DWORD InitAmpTest(double dblStartWL,double dblStopWL,double dblRBW) = 0;
	virtual DWORD MeasureSource() = 0;
	virtual DWORD MeasureAmplifier(BOOL bScanSrcOnly = FALSE) = 0;
	virtual DWORD GetChannelCount(DWORD* pdwChannelCount) = 0;
	virtual DWORD GetChannelWaveLens(double* pdblWL,DWORD* pdwChannelCount) = 0;
	virtual DWORD GetChannelNF(double* pdblNF,DWORD* pdwChannelCount) = 0;
	virtual DWORD GetChannelGain(double* pdblGain,DWORD* pdwChannelCount) = 0;
	virtual DWORD GetChannelSNR(double* pdblSNR,DWORD* pdwChannelCount) = 0;
	virtual DWORD GetChannelSourcePower(double* pdblSourcePow,DWORD* pdwChannelCount) = 0;
	virtual DWORD SetAmpOffset(double dblSourceOffset, double dblAmpOffset) = 0;
	virtual DWORD GetAmpOffset(double &dblSourceOffset, double &dblAmpOffset) = 0;
	virtual DWORD GetEDFAResult(double *pdblSumSrcSigPwr, double *pdblSumAmpSigPwr, double *pdblSunGain) = 0;
	virtual DWORD GetEDFAChResult(DWORD *pwChCount, double *pdblChWL, double *pdblSrcpwr, double *pdblChGain, double *pdblChNF, double *pdblChAse,
			double *pdblGainFlatness, double *pdblMaxNF, double* pdblMaxGain, double* pdblMinGain) = 0;
	virtual DWORD InitSingleSweep(double dblStartWL, double dblStopWL, double dblRBW, DWORD dwSweepPoint) = 0;
	virtual DWORD RunSweep(double* pdblWL,double* pdblPower,char szSelTrace) = 0;
	virtual DWORD GetSingleSweepPoint(DWORD * pCount) = 0;
	virtual DWORD GetSweepData(double* pdblWL,double* pdblPower, char szSelTrace) = 0;
	virtual DWORD GetDeviceInfo(stDevInfo *stInfo) = 0;
	virtual DWORD SaveDatatoPC(LPCTSTR lpSavePath, LPCTSTR lpDataType, LPCTSTR lpFileType, char szSelTrace) = 0;
	
	virtual DWORD SetCalibration(DWORD dwCalibrationType) = 0;
	virtual BOOL GetErrorMessage(DWORD dwErrorCode, char *pszErrorMsg) = 0;

	virtual DWORD GetTotalPower(double &dblPow, char szSelTrace) = 0;
	virtual DWORD GetActualBW(double dblBwAmp, double &dblActBw) = 0;
	virtual DWORD SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle) = 0;
	virtual DWORD GetZoomValue(double dbWLNM,double dbBWNM,double *pdbGetValue)=0;
};

class COSA_AQ6370B : public COSAControl
{
public:
	DWORD SetSweepRange(double dblStartWL, double dblStopWL);//Set the start wavelength and stop wavelength
	DWORD GetEDFATestResult(char* pszResult,USHORT uiLength);

	virtual DWORD OpenDevice(stDevType stType, char* pszDeviceAddr, unsigned long *comHandle);
	virtual DWORD CloseDevice();
	virtual DWORD ResetDevice(void);
	virtual DWORD SetOSALocalCtrl(void);
	virtual DWORD SetRBW(double dblRBW);
	virtual DWORD GetRBW(double* pdblRBW);
	virtual DWORD InitAmpTest(double dblStartWL, double dblStopWL, double dblRBW);
	virtual DWORD MeasureSource();
	virtual DWORD MeasureAmplifier(BOOL bScanSrcOnly = FALSE);
	virtual DWORD GetChannelCount(DWORD* pdwChannelCount);
	virtual DWORD GetChannelWaveLens(double* pdblWL,DWORD* pdwChannelCount);
	virtual DWORD GetChannelNF(double* pdblNF,DWORD* pdwChannelCount);
	virtual DWORD GetChannelGain(double* pdblGain,DWORD* pdwChannelCount);
	virtual DWORD GetChannelSNR(double* pdblSNR,DWORD* pdwChannelCount);
	virtual DWORD GetChannelSourcePower(double* pdblSourcePow,DWORD* pdwChannelCount);
	virtual DWORD SetAmpOffset(double dblSourceOffset, double dblAmpOffset);
	virtual DWORD GetAmpOffset(double &dblSourceOffset, double &dblAmpOffset);
	virtual DWORD GetEDFAResult(double *pdblSumSrcSigPwr, double *pdblSumAmpSigPwr, double *pdblSunGain);
	virtual DWORD GetEDFAChResult(DWORD *pwChCount, double *pdblChWL, double *pdblSrcpwr, double *pdblChGain, double *pdblChNF, double *pdblChAse,
			double *pdblGainFlatness, double *pdblMaxNF, double* pdblMaxGain, double* pdblMinGain);
	virtual DWORD InitSingleSweep(double dblStartWL, double dblStopWL, double dblRBW, DWORD dwSweepPoint);
	virtual DWORD RunSweep(double* pdblWL,double* pdblPower,char szSelTrace);
	virtual DWORD GetSingleSweepPoint(DWORD * pCount);
	virtual DWORD GetSweepData(double* pdblWL,double* pdblPower, char szSelTrace);
	virtual DWORD GetDeviceInfo(stDevInfo *stInfo);
	virtual DWORD SaveDatatoPC(LPCTSTR lpSavePath, LPCTSTR lpDataType, LPCTSTR lpFileType, char szSelTrace);
	
	virtual DWORD SetCalibration(DWORD dwCalibrationType);
	virtual BOOL GetErrorMessage(DWORD dwErrorCode, char *pszErrorMsg);
	virtual DWORD GetTotalPower(double &dblPow, char szSelTrace);
	virtual DWORD GetActualBW(double dblBwAmp, double &dblActBw);
	virtual DWORD SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle);
	virtual DWORD GetZoomValue(double dbWLNM,double dbBWNM,double *pdbGetValue);


	DWORD InitOSAAmpCalSet();
//	BOOL GetEDFATestResult(double *pdblSumSrcSigPwr, double *pdblSumAmpSigPwr, double *pdblSunGain);
	DWORD RunCalculate();
	DWORD CompleteRequest();//Check if the OSA busy,if busy then wait.
	DWORD GetGPIBAress(int *dblGpibAddress);
//	BOOL ResetOSA();//Executes a device reset to return the instrument to the known (default) status.
	DWORD SetAnalysisType(DWORD wAnalysisType = 12);//Set and start the type of analysis mode.
//	BOOL SetOSALocalCtrl();//Switches to Local mode.
//	BOOL SetRBW(double dblRBW);//Set RBW on the OSA
//	BOOL GetRBW(double* pdblRBW);//Get RBW on the OSA
//	BOOL GetChannelCount(WORD* pdwChannelCount);//Get the number of channels of the WDM,EDFA-NF, WDM FIL-PK,or WDM FIL-BTM analysis results.
//	BOOL GetChannelSNR(double* pdblSNR,WORD* pdwChannelCount);//Get the gain value of the EDFA-NF analysis results.
	DWORD SetPowerOffset(double dblOSAPowOffset);//Set the offset value for the level.
	DWORD GetPowerOffset(double* pdblOSAPowOffset);//Get the offset value of the level.
	DWORD SetWavelengthOffset(double dblWLOffset);//Set the offset value for the level wavelength.
	DWORD GetWavelengthOffset(double* pdblWLOffset);//Get the offset value of the level wavelength.
	DWORD SetWLOffsetTable(USHORT usWavelength,double dblWLOffset);//Set the wavelength offset table.
	DWORD GetWLOffsetTable(USHORT usWavelength,double* pdblWLOffset);//Get the wavelength offset table.
	DWORD SetPowOffsetTable(USHORT usWavelength,double dblPowOffset);//Set the level offset table.
	DWORD GetPowOffsetTable(USHORT usWavelength,double* pdblPowOffset);//Get the level offset table.
	DWORD SetAmpSrcSigOffset(double dblSrcSigOffset);
	//Set level offset values (signal light) for the NF analysis function.
	DWORD GetAmpSrcSigOffset(double* pdblSrcSigOffset);
	//Get level offset values (signal light) for the NF analysis function.
	DWORD SetAmpOutSigOffset(double dblOutSigOffset);//Set level offset values (output light) for the NF analysis function.
	DWORD GetAmpOutSigOffset(double* pdblOutSigOffset);//Get level offset values (output light) for the NF analysis function.
//	BOOL InitSingleSweep(double dblStartWL, double dblStopWL, double dblRBW, WORD dwSweepPoint);//Init the OSA before performing single scan.	
//	BOOL RunSweep(double* pdblSweepDataX,double* pdblSweepDataY,char szSelTrace);//perform a sweep and get the level axis data of specified trace.
	DWORD SetTraceAct(char szSelTrace);//set which trace active
	DWORD SetTraceAttribute(char szSelTrace, USHORT uiAttribute);//set the attribute of the given trace
	COSA_AQ6370B();
	virtual ~COSA_AQ6370B();

protected:
//	COplkGPIBDevice m_gpib;
	CCommunicationDLL m_Comm;
	double m_dblSRCPointWL[SWEEPPOINT];
	double m_dblSRCPointPower[SWEEPPOINT];
	double m_dblAmpPointWL[SWEEPPOINT];
	double m_dblAmpPointPower[SWEEPPOINT];
	double m_dblCHNF[SWEEPPOINT];
	double m_dblCHGain[SWEEPPOINT];
	double m_dblASE[SWEEPPOINT];
	double m_dblResoln[SWEEPPOINT];
	double m_dblMaxNF;
	double m_dblInputTotal;
	double m_dblOutputTotal;
	double m_dblOutputSignal;
	double m_dblGF;
	double m_dblMaxGain;
	double m_dblMinGain;
	double m_dblCenterWL[SWEEPPOINT];
	int		m_iChCount;
	double m_dblStartWL; 
	double m_dblStopWL;
	double m_dblRBW;
	DWORD m_dwSweepPoint;
	
	long m_lCommType;
};

class AgilentOSA : public COSAControl  
{
public:

	CCommunicationDLL m_Commun;
	
	virtual DWORD OpenDevice(stDevType stType, char* pszDeviceAddr, unsigned long *comHandle);
	virtual DWORD CloseDevice();
	virtual DWORD ResetDevice(void);
	virtual DWORD SetOSALocalCtrl(void);
	virtual DWORD SetRBW(double dblRBW);
	virtual DWORD GetRBW(double* pdblRBW);
	virtual DWORD InitAmpTest(double dblStartWL,double dblStopWL,double dblRBW);
	virtual DWORD MeasureSource();
	virtual DWORD MeasureAmplifier(BOOL bScanSrcOnly = FALSE);
	virtual DWORD GetChannelCount(DWORD* pdwChannelCount);
	virtual DWORD GetChannelWaveLens(double* pdblWL,DWORD* pdwChannelCount);
	virtual DWORD GetChannelNF(double* pdblNF,DWORD* pdwChannelCount);
	virtual DWORD GetChannelGain(double* pdblGain,DWORD* pdwChannelCount);
	virtual DWORD GetChannelSNR(double* pdblSNR,DWORD* pdwChannelCount);
	virtual DWORD GetChannelSourcePower(double* pdblSourcePow, DWORD* pdwChannelCount);
	virtual DWORD SetAmpOffset(double dblSourceOffset, double dblAmpOffset);
	virtual DWORD GetAmpOffset(double &dblSourceOffset, double &dblAmpOffset);
	virtual DWORD GetEDFAResult(double *pdblSumSrcSigPwr, double *pdblSumAmpSigPwr, double *pdblSunGain);
	virtual DWORD GetEDFAChResult(DWORD *pwChCount, double *pdblChWL, double *pdblSrcpwr, double *pdblChGain, double *pdblChNF, 
						  double *pdblChAse,double *pdblGainFlatness, double *pdblMaxNF, double* pdblMaxGain, double* pdblMinGain);
	virtual DWORD InitSingleSweep(double dblStartWL, double dblStopWL, double dblRBW, DWORD dwSweepPoint);
	virtual DWORD RunSweep(double* pdblWL,double* pdblPower,char szSelTrace);
	virtual DWORD GetSweepData(double* pdblWL,double* pdblPower, char szSelTrace);
	virtual DWORD GetSingleSweepPoint(DWORD * pCount);
	virtual DWORD GetDeviceInfo(stDevInfo *stInfo);
	virtual DWORD SaveDatatoPC(LPCTSTR lpSavePath, LPCTSTR lpDataType, LPCTSTR lpFileType, char szSelTrace);
	virtual BOOL  GetErrorMessage(DWORD dwErrorCode, char *pszErrorMsg);
	virtual DWORD SetCalibration(DWORD dwCalibrationType);
	virtual DWORD GetZoomValue(double dbWLNM,double dbBWNM,double *pdbGetValue);

	virtual DWORD GetTotalPower(double &dblPow, char szSelTrace);
	virtual DWORD GetActualBW(double dblBwAmp, double &dblActBw);
	virtual DWORD SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle);

	DWORD   CompleteRequest();

	BOOL m_bNFLib;
	stScanSetting	m_stScanSetting;
	stEDFAResult	m_stEDFAResult;
	double	m_pdblScanData[2][SWEEPPOINT];
};


class COSA_AQ6317B : public COSAControl
{
public:
	virtual DWORD OpenDevice(stDevType stType, char* pszDeviceAddr, unsigned long *comHandle);
	virtual DWORD CloseDevice();
	virtual DWORD ResetDevice(void);
	virtual DWORD SetOSALocalCtrl(void);
	virtual DWORD SetRBW(double dblRBW);
	virtual DWORD GetRBW(double* pdblRBW);
	virtual DWORD InitAmpTest(double dblStartWL, double dblStopWL, double dblRBW);
	virtual DWORD MeasureSource();
	virtual DWORD MeasureAmplifier(BOOL bScanSrcOnly = FALSE);
	virtual DWORD GetChannelCount(DWORD* pdwChannelCount);
	virtual DWORD GetChannelWaveLens(double* pdblWL,DWORD* pdwChannelCount);
	virtual DWORD GetChannelNF(double* pdblNF,DWORD* pdwChannelCount);
	virtual DWORD GetChannelGain(double* pdblGain,DWORD* pdwChannelCount);
	virtual DWORD GetChannelSNR(double* pdblSNR,DWORD* pdwChannelCount);
	virtual DWORD GetChannelSourcePower(double* pdblSourcePow,DWORD* pdwChannelCount);
	virtual DWORD SetAmpOffset(double dblSourceOffset, double dblAmpOffset);
	virtual DWORD GetAmpOffset(double &dblSourceOffset, double &dblAmpOffset);
	virtual DWORD GetEDFAResult(double *pdblSumSrcSigPwr, double *pdblSumAmpSigPwr, double *pdblSunGain);
	virtual DWORD GetEDFAChResult(DWORD *pwChCount, double *pdblChWL, double *pdblSrcpwr, double *pdblChGain, double *pdblChNF, double *pdblChAse,
			double *pdblGainFlatness, double *pdblMaxNF, double* pdblMaxGain, double* pdblMinGain);
	virtual DWORD InitSingleSweep(double dblStartWL, double dblStopWL, double dblRBW, DWORD dwSweepPoint);
	virtual DWORD RunSweep(double* pdblWL,double* pdblPower,char szSelTrace);
	virtual DWORD GetSingleSweepPoint(DWORD * pCount);
	virtual DWORD GetSweepData(double* pdblWL,double* pdblPower, char szSelTrace);
	virtual DWORD GetDeviceInfo(stDevInfo *stInfo);
	virtual DWORD SaveDatatoPC(LPCTSTR lpSavePath, LPCTSTR lpDataType, LPCTSTR lpFileType, char szSelTrace);
	
	virtual DWORD SetCalibration(DWORD dwCalibrationType);
	virtual BOOL GetErrorMessage(DWORD dwErrorCode, char *pszErrorMsg);
	virtual DWORD GetTotalPower(double &dblPow, char szSelTrace);
	virtual DWORD GetActualBW(double dblBwAmp, double &dblActBw);
	virtual DWORD SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle);
	virtual DWORD GetZoomValue(double dbWLNM,double dbBWNM,double *pdbGetValue);

	void FinddoubleMaxMin(double *dbDataArry,double *dbMin,double *dbMax,int nLength);
    DWORD SetSweepRange(double dblStartWL, double dblStopWL);
	DWORD GetEDFATestResult(int nType);
    DWORD RunCalResult();
	DWORD CompleteRequest();//Check if the OSA busy,if busy then wait.
	DWORD GetGPIBAress(int *dblGpibAddress);
//	BOOL ResetOSA();//Executes a device reset to return the instrument to the known (default) status.
	DWORD SetAnalysisType(DWORD wAnalysisType = 1);//Set and start the type of analysis mode.
	DWORD SetPowerOffset(double dblOSAPowOffset);//Set the offset value for the level.
	DWORD GetPowerOffset(double* pdblOSAPowOffset);//Get the offset value of the level.
	DWORD SetWavelengthOffset(double dblWLOffset);//Set the offset value for the level wavelength.
	DWORD GetWavelengthOffset(double* pdblWLOffset);//Get the offset value of the level wavelength.
	DWORD SetWLOffsetTable(USHORT usWavelength,double dblWLOffset);//Set the wavelength offset table.
	DWORD GetWLOffsetTable(USHORT usWavelength,double* pdblWLOffset);//Get the wavelength offset table.
	DWORD SetPowOffsetTable(USHORT usWavelength,double dblPowOffset);//Set the level offset table.
	DWORD GetPowOffsetTable(USHORT usWavelength,double* pdblPowOffset);//Get the level offset table.
	DWORD SetAmpSrcSigOffset(double dblSrcSigOffset);
	//Set level offset values (signal light) for the NF analysis function.
	DWORD GetAmpSrcSigOffset(double* pdblSrcSigOffset);
	//Get level offset values (signal light) for the NF analysis function.
	DWORD SetAmpOutSigOffset(double dblOutSigOffset);//Set level offset values (output light) for the NF analysis function.
	DWORD GetAmpOutSigOffset(double* pdblOutSigOffset);//Get level offset values (output light) for the NF analysis function.
//	BOOL InitSingleSweep(double dblStartWL, double dblStopWL, double dblRBW, WORD dwSweepPoint);//Init the OSA before performing single scan.	
//	BOOL RunSweep(double* pdblSweepDataX,double* pdblSweepDataY,char szSelTrace);//perform a sweep and get the level axis data of specified trace.
	DWORD SetTraceAct(char szSelTrace);//set which trace active
	DWORD SetTraceAttribute(char szSelTrace, USHORT uiAttribute);//set the attribute of the given trace
	COSA_AQ6317B();
	virtual ~COSA_AQ6317B();

protected:
//	COplkGPIBDevice m_gpib;
	CCommunicationDLL m_Comm;
	double m_dblSRCPointWL[SWEEPPOINT];
	double m_dblSRCPointPower[SWEEPPOINT];
	double m_dblAmpPointWL[SWEEPPOINT];
	double m_dblAmpPointPower[SWEEPPOINT];
	double m_dblCHNF[SWEEPPOINT];
	double m_dblCHGain[SWEEPPOINT];
	double m_dblASE[SWEEPPOINT];
	double m_dblResoln[SWEEPPOINT];
	double m_dblMaxNF;
	double m_dblInputTotal;
	double m_dblOutputTotal;
	double m_dblOutputSignal;
	double m_dblGF;
	double m_dblMaxGain;
	double m_dblMinGain;
	double m_dblCenterWL[SWEEPPOINT];
	int		m_iChCount;
	double m_dblStartWL; 
	double m_dblStopWL;
	double m_dblRBW;
	DWORD m_dwSweepPoint;
	long m_lCommType;
};



#endif // !defined(AFX_OSACONTROL_H__8AD5CA80_E88A_4575_B33A_8EDFE709430E__INCLUDED_)
