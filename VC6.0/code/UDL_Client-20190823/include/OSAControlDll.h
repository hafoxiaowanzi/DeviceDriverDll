
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the OSACONTROLDLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// OSACONTROLDLL_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef OSACONTROLDLL_EXPORTS
#define OSACONTROLDLL_API __declspec(dllexport)
#else
#define OSACONTROLDLL_API __declspec(dllimport)
#endif

#ifndef MACRO_DATA_SRTUCT_HEADER
#define MACRO_DATA_SRTUCT_HEADER

#include "..\\include\\OSA.h"
#include "..\\include\\UDLReturnCode.h"

#define HP_86142				0
#define AQ_6370B				1
#define AQ_6317B                2


// This class is exported from the OSAControlDll.dll
class OSACONTROLDLL_API COSADll 
{
public:
	COSADll();
	virtual ~COSADll();
	// TODO: add your methods here.
	DWORD OpenDevice(stDevType stType, char* pszDeviceAddr, unsigned long *comHandle);
	DWORD CloseDevice();
	DWORD ResetDevice(void);
	DWORD SetOSALocalCtrl(void);
	DWORD SetRBW(double dblRBW);
	DWORD GetRBW(double* pdblRBW);
	DWORD InitAmpTest(double dblStartWL,double dblStopWL,double dblRBW);
	DWORD MeasureSource();
	DWORD MeasureAmplifier(BOOL bScanSrcOnly = FALSE);
	DWORD GetChannelCount(DWORD* pdwChannelCount);
	DWORD GetChannelWaveLens(double* pdblWL,DWORD* pdwChannelCount);
	DWORD GetChannelNF(double* pdblNF,DWORD* pdwChannelCount);
	DWORD GetChannelGain(double* pdblGain,DWORD* pdwChannelCount);
	DWORD GetChannelSNR(double* pdblSNR,DWORD* pdwChannelCount);
	DWORD GetChannelSourcePower(double* pdblSourcePow,DWORD* pdwChannelCount);
	DWORD SetAmpOffset(double dblSourceOffset, double dblAmpOffset);
	DWORD GetAmpOffset(double &dblSourceOffset, double &dblAmpOffset);
	DWORD GetEDFAResult(double *pdblSumSrcSigPwr, double *pdblSumAmpSigPwr, double *pdblSunGain);
	DWORD GetEDFAChResult(DWORD *pwChCount, double *pdblChWL, double *pdblSrcpwr, double *pdblChGain, double *pdblChNF, double *pdblChAse,
			double *pdblGainFlatness, double *pdblMaxNF, double* pdblMaxGain, double* pdblMinGain);
	DWORD InitSingleSweep(double dblStartWL, double dblStopWL, double dblRBW, DWORD dwSweepPoint);
	DWORD RunSweep(double* pdblWL,double* pdblPower,char szSelTrace);
	DWORD GetSingleSweepPoint(DWORD * pdwPointCount);
	DWORD GetSweepData(double* pdblWL,double* pdblPower, char szSelTrace);
	DWORD GetDeviceInfo(stDevInfo *stInfo);
	DWORD SaveDatatoPC(LPCTSTR lpSavePath, LPCTSTR lpDataType, LPCTSTR lpFileType, char szSelTrace);
	DWORD SetHandle(stDevType stType, LPCTSTR pszDeviceAddr, unsigned long handle);
	
	DWORD SetCalibration(DWORD dwCalibrationType);
	DWORD GetTotalPower(double &dblPow, char szSelTrace);
	DWORD GetActualBW(double dblBwAmp, double &dblActBw);
	BOOL GetErrorMessage(DWORD dwErrorCode, char *pszErrorMsg);
	DWORD GetZoomValue(double dbWLNM,double dbBWNM,double *pdbGetValue);

private:
//	AgilentOSA *g_OpHP81642;
//	COSA_AQ6370B *g_OpAQ6370B;
//	COSAControl *g_pOSA;

	COSAControl *m_pOSA;
//	void **m_pvoid;

};

//extern OSACONTROLDLL_API int nOSAControlDll;

//OSACONTROLDLL_API int fnOSAControlDll(void);
#endif

