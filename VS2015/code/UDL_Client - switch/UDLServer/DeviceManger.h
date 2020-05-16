// DeviceManger.h: interface for the CDeviceManger class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEVICEMANGER_H__CAAD3284_2FFA_4E63_9641_A32A7FF1EC43__INCLUDED_)
#define AFX_DEVICEMANGER_H__CAAD3284_2FFA_4E63_9641_A32A7FF1EC43__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\\include\\hearder.h"
#include "..\\include\\UDLReturnCode.h"
#include "..\\include\\TLSControlDll.h"
#include "..\\include\\PMControlDll.h"
#include "..\\include\\VOAControlDll.h"
#include "..\\include\\OSAControlDll.h"
#include "..\\include\\PolDll.h"
#include "..\\include\\ScanHeader.h"
#include "..\\include\\AlgorithmFunction.h"
#include "..\\include\\ChamberContrlDll.h"
#include "..\\include\\SwitchDll.h"

#include <vector>
#include <winsock2.h>

using namespace std;

class CDeviceManger  
{
public:
	CDeviceManger();
	virtual ~CDeviceManger();
	BOOL InitDevObject();
	BOOL LoadConfigXML(LPCSTR lpstrFileName);
	BOOL OpenDevice();
	CString GetErrorMsg();
	void SetUDLNET(BOOL bIsNet);
	BOOL ConnectToServer(LPCSTR lpstrIP);

	/////////////////////////////////////激光器相关函数////////////////////////////////////////////////////////////////////////////////////
    BOOL SetTLSWavelength(long lChIndex, double dblWL);
	BOOL SetTLSSourcePower(long lChIndex, double dblPW);
	BOOL SetTLSCoherenceControl(long lChIndex,BOOL bEnable);
	BOOL SetTLSSourceUnit(long lChIndex, long lUnit);
	BOOL SetTLSParameters(long lChIndex,BOOL bLowSSE,double dblPower, double dblWavelength);
	BOOL SetTLSOutputEnable(long lChIndex,BOOL bEnable);
	BOOL CloseTLSDevice(long lChIndex);

	////////////////////////////////////功率计相关函数////////////////////////////////////////////////////////////////////////////////////
	BOOL GetPMUnit(long iChan, long* piUnit);
	BOOL GetPMAverageTime(long iChan, double* pdblAverageTime);
	BOOL GetPMWavelength(long iChan, double* pdblWL);
	BOOL ReadPower(long iChan, double* pdbPowerValue);
	BOOL SetPMUnit(long iChan, long iPWUnit);
	BOOL SetPMWavelength(long iChan, double dblWL);
	BOOL SetPMAverageTime(long iChan, double dblPWAverageTime);
	BOOL SetPMRangeMode(long iChan, long iPWRangeMode);
	BOOL SetPMParameters(long iChan, BOOL bAutoRang, double dblWL, double dblAverageTime, double dblPwrRange);
	BOOL ClosePMDevice(long lChIndex);
	BOOL GetPMRangeMode(long iChan, long* iPWMRangeMode);
	BOOL SetPMZero(long iChan);
	BOOL GetPMDeviceInfo(long lChIndex,CHAR *pchInfo);
	BOOL SetPMMaxMinPowerStart(long lChIndex);
    BOOL GetPMMaxMinPower(long lChIndex,double *pdbGetMax,double *pdbGetMin);
	BOOL SetPMMaxMinPowerStop(long lChIndex);
	BOOL SetPMPowerOffset(long lChIndex,double dbPowerOffset);

	///////////////////////////////////////VOA相关函数///////////////////////////////////////////////////////////////////////////////////////
	BOOL CloseVOADevice(long lChIndex);
	BOOL ResetVOADevice(long lChIndex);
	BOOL SetVOAWavelength(long lChIndex, double dblWL);
	BOOL GetVOAWavelength(long lChIndex, double* pdblWL);
    BOOL SetVOAAttenuation(long lChIndex, double dblAtten);
	BOOL GetVOAAttenuation(long lChIndex, double* pdblAtten);
	BOOL SetVOAEnableOutput(long lChIndex, BOOL bEnable);
	BOOL SetVOAInputOffset(long lChIndex, double dblOffset);
	BOOL GetVOAStatus(long lChIndex,DWORD *dwStatus);

	/////////////////////////////////////OSA相关函数//////////////////////////////////////////////////////////////////////
	BOOL CloseOSADevice(long lChIndex);
	BOOL ResetOSADevice(long lChIndex);
	BOOL SetOSALocalCtrl(long lChIndex);
	BOOL SetOSARBW(long lChIndex,double dblRBW);
	BOOL GetOSARBW(long lChIndex,double* pdblRBW);
	BOOL InitOSAWDMTest(long lChIndex,double dblStartWL,double dblStopWL,double dblRBW);
	BOOL InitOSAAmpTest(long lChIndex,double dblStartWL,double dblStopWL,double dblRBW);
	BOOL MeasureOSAWDM(long lChIndex);
	BOOL MeasureOSASource(long lChIndex);
	BOOL MeasureOSAAmplifier(long lChIndex,BOOL bScanSrcOnly = FALSE);
	BOOL GetOSAChannelCount(long lChIndex,DWORD* pdwChannelCount);
	BOOL GetOSAChannelWaveLens(long lChIndex,double* pdblWL,DWORD* pdwChannelCount);
	BOOL GetOSAChannelNF(long lChIndex,double* pdblNF,DWORD* pdwChannelCount);
	BOOL GetOSAChannelGain(long lChIndex,double* pdblGain,DWORD* pdwChannelCount);
	BOOL GetOSAChannelSNR(long lChIndex,double* pdblSNR,DWORD* pdwChannelCount);
	BOOL GetOSAChannelSourcePower(long lChIndex,double* pdblSourcePow,DWORD* pdwChannelCount);
	BOOL SetOSAAmpOffset(long lChIndex,double dblSourceOffset, double dblAmpOffset);
	BOOL GetOSAAmpOffset(long lChIndex,double &dblSourceOffset, double &dblAmpOffset);
	BOOL GetOSAEDFAResult(long lChIndex,double *pdblSumSrcSigPwr, double *pdblSumAmpSigPwr, double *pdblSunGain);
	BOOL GetOSAEDFAChResult(long lChIndex,DWORD *pwChCount, double *pdblChWL, double *pdblSrcpwr, double *pdblChGain, double *pdblChNF, double *pdblChAse,
	double *pdblGainFlatness, double *pdblMaxNF, double* pdblMaxGain, double* pdblMinGain);
	BOOL InitOSASingleSweep(long lChIndex,double dblStartWL, double dblStopWL, double dblRBW, DWORD dwSweepPoint);
	BOOL InitOSARepeatSweep(long lChIndex, double dblStartWL, double dblStopWL, double dblRBW, DWORD dwSweepPoint);
	BOOL RunOSASweep(long lChIndex,double* pdblWL,double* pdblPower,char szSelTrace);
	BOOL GetSingleSweepPoint(long lChIndex,DWORD *pdwPointCount);
	BOOL GetOSASweepData(long lChIndex,double* pdblWL,double* pdblPower, char szSelTrace);
	BOOL SaveOSADataToPC(long lChIndex,LPCTSTR lpSavePath, LPCTSTR lpDataType, LPCTSTR lpFileType, char szSelTrace);	
	BOOL SetOSACalibration(long lChIndex,DWORD dwCalibrationType);
	BOOL GetZoomValue(long lChIndex,double dbWLNM,double dbBWNM,double *pdbGetValue);

	 ///////////////////////////////////////偏振控制器相关//////////////////////////////////////////////////////////////
	BOOL ClosePolDevice(long lChIndex);
	BOOL ResetPolDevice(long lChIndex);
	BOOL GetPolDeviceInfo(long lChIndex,stDevInfo *stInfo);
	BOOL GetPolCurrentPOSPolarizer(long lChIndex,double * pdblAlphaP,double *pdblAlphaQ,double *pdblAlphaH);
	BOOL SetPolALL(long lChIndex,double alphaP, double alphaQ, double alphaH);
	BOOL SetPolDiagonalAngles(long lChIndex,double AlphaPMax, double Wavelength);
	BOOL SetPolHorizontalAngles(long lChIndex,double AlphaPMax, double Wavelength);
	BOOL SetPolPOSHalf(long lChIndex,double alpha);
	BOOL SetPolPOSPolarizer(long lChIndex,double alpha);
	BOOL SetPolPOSQuarter(long lChIndex,double alpha);
	BOOL SetPolRightHandCircularAngles(long lChIndex,double AlphaPMax, double Wavelength);
	BOOL SetPolVerticalAngles(long lChIndex,double AlphaPMax, double Wavelength);

    //////////////////////////////////////////扫描相关函数/////////////////////////////////////////////////////////////
	BOOL PrepareScan(long lTLSChIndex);
	BOOL ExecuteScan(long lTLSChIndex,long lpScanRawDataPtr);
	BOOL ReleaseScan(long lTLSChIndex);
	BOOL DoScanRef(long lTLSChIndex);
	BOOL DoScan(long lTLSChIndex);
	BOOL ReleaseAllocStruct(POp816XRawData pData);
	BOOL GetCalILResult(POp816XRawData pCalData);
	BOOL GetCalILAndPDLResult(POp816XRawData pCalData);

	//////////////////////////////////////////循环箱控制函数//////////////////////////////////////////////////////////
	BOOL  CloseChamberDevice(long lChIndex);
	BOOL  GetChamberDeviceInfo(long lChIndex,stDevInfo *stInfo);
	BOOL  SetChamberRunStop(long lChIndex);
	BOOL  SetChamberRunStart(long lChIndex);
	BOOL  SetChamberSetPoint(long lChIndex,double dbSetPoint);
	BOOL  GetChamberSetPoint(long lChIndex,double* dbSetPoint);
	BOOL  GetChamberCurrentTemp(long lChIndex,double *dbCurrTemp);

	///////////////////////////////////////////串口通讯类函数/////////////////////////////////////////////////////////
	BOOL  WriteDevComBuffer(long lChIndex,unsigned char* pOutBuffer, DWORD dwBufferSize);
	BOOL  ReadDevComBuffer(long lChIndex,unsigned char* pInBuffer, DWORD dwBufferSize);
	BOOL  CloseDevDevice(long lChIndex);
	BOOL  OpenDevDevice(long lChIndex);

	/////////////////////////////////////////开关盒控制函数//////////////////////////////////////////////////////////
	BOOL  CloseSwitchDevice(long lChIndex);
	BOOL  OpenSwitchDevice(long lChIndex);
    BOOL  SwitchPort2Port(int lChIndex,int nInputPort, int nOutputPort);


	BOOL TestWriteFile();


public:
  
	int m_nDeviceCount;

	pstMainFrame  m_ptrMainFrame;
	stSlotInfo   m_pTLSSlotInfo[MAX_SLOT_NUM];
	int          m_nTLSCount;
	stSlotInfo   m_pPMSlotInfo[MAX_SLOT_NUM];
	int          m_nPMCount;
	stSlotInfo   m_pVOASlotInfo[MAX_SLOT_NUM];
	int          m_nVOACount;
	stSlotInfo   m_pOSASlotInfo[MAX_SLOT_NUM];
	int          m_nOSACount;
	stSlotInfo   m_pPOLSlotInfo[MAX_SLOT_NUM];
	int          m_nPolCount;
	stSlotInfo   m_pChamberSlotInfo[MAX_SLOT_NUM];
	int          m_nChamberCount;
	stSlotInfo   m_pComDevSlotInfo[MAX_SLOT_NUM];
	int          m_nComDev;
	stSlotInfo   m_pSwitchSlotInfo[MAX_SLOT_NUM];
	int          m_nSwitchCount;

   
	vector<CTLSDll*> m_ctrlTLS;
	vector<CPMDll*> m_ctrlPM;
	vector<CVOADll*> m_ctrlVOA;
	vector<COSADll*> m_ctrlOSA;
	vector<CPolDll*> m_ctrlPOL;
	vector<CChamberDll*> m_ctrlChamber;
	vector<CCommunicationDLL*> m_ctrlComDev;
	vector<CSwitchDll*> m_ctrlSwitch;
//	CSwitchDll m_ctrlSwitch;


	stOp816XRawData   m_stScanData;
	POp816XRawData   m_pstRefScanData;
	POp816XRawData   m_pstDoScanData;
    stScanParam   m_stScanParam;
	
private:
	CAlgorithmFunction m_Algorith;	
	CString m_strErrorMsg;
	CString m_strComAddress;
	BOOL m_bUseNet;
	SOCKET m_conn;
	fd_set m_fdread;
	
	void DestoryDevObject();
	BOOL OpenTLS(int nDevIndex,LPCSTR lpAddress);
	BOOL OpenPM(int nDevIndex,LPCSTR lpAddress);
	BOOL OpenVOA(int nDevIndex,LPCSTR lpAddress);
	BOOL OpenOSA(int nDevIndex,LPCSTR lpAddress);
	BOOL OpenPOL(int nDevIndex,LPCSTR lpAddress);
	BOOL OpenChamber(int nDevIndex,LPCSTR lpAddress);
	BOOL OpenComDev(int nDevIndex,LPCSTR lpAddress);
	BOOL JudeDeviceWhetherScan(int nChannelIndex);
	BOOL DoTLSN7744Scan(long lTLSChIndex,int nType);
	void AllocPDLScanStruct(POp816XRawData pData);
	void AllocScanStruct(POp816XRawData pData);
	BOOL CalAveragePower(POp816XRawData stScanData,int nSweepCount);
	BOOL CalTestResult(POp816XRawData pRefData,POp816XRawData pScanData,POp816XRawData pResult);
	BOOL CalculatePDL(DWORD dwSampleCount, double* pRefRawData,  double* pTestRawData, double* pResultRawData);
	BOOL InitialNet();
	BOOL SendNetBuffer(char* pszBuffer,int nBufferlength);
	BOOL ReadNetBuffer(char* pszBuffer,int nBufferLength,int &nGetLenght);
	BOOL SendBufferBy1M( char * str, int nLength);
	
    ///////////////////////Engine网络///////////////////////////////////////////////////
	BOOL LoadConfigXMLForNET(LPCSTR lpstrFileName);
	CString ExtractFileName(LPCSTR lpstrFilePath);
	BOOL OpenDeviceForNET();

	//////////////////////激光器网络///////////////////////////////////////////////////
	BOOL SetTLSWavelengthForNET(long lChIndex, double dblWL);
	BOOL SetTLSSourcePowerForNET(long lChIndex, double dblPW);
	BOOL SetTLSCoherenceControlForNET(long lChIndex,BOOL bEnable);
	BOOL SetTLSSourceUnitForNET(long lChIndex, long lUnit);
	BOOL SetTLSParametersForNET(long lChIndex,BOOL bLowSSE,double dblPower, double dblWavelength);
	BOOL SetTLSOutputEnableForNET(long lChIndex, BOOL bEnable);
	BOOL CloseTLSDeviceForNET(long lChIndex);

	/////////////////////功率计网络/////////////////////////////////////////////////////
	BOOL GetPMUnitForNET(long iChan, long* piUnit);
	BOOL GetPMAverageTimeForNET(long iChan, double* pdblAverageTime);
	BOOL GetPMWavelengthForNET(long iChan, double* pdblWL);
	BOOL ReadPowerForNET(long iChan, double* pdbPowerValue);
	BOOL SetPMUnitForNET(long iChan, long iPWUnit);
	BOOL SetPMWavelengthForNET(long iChan, double dblWL);
	BOOL SetPMAverageTimeForNET(long iChan, double dblPWAverageTime);
	BOOL SetPMRangeModeForNET(long iChan, long iPWRangeMode);
	BOOL SetPMParametersForNET(long iChan, BOOL bAutoRang, double dblWL, double dblAverageTime, double dblPwrRange);
	BOOL ClosePMDeviceForNET(long lChIndex);
	BOOL GetPMRangeModeForNET(long iChan, long* iPWMRangeMode);
	BOOL SetPMZeroForNET(long iChan);
	BOOL SetPMMaxMinPowerStartForNET(long lChIndex);
    BOOL GetPMMaxMinPowerForNET(long lChIndex,double *pdbGetMax,double *pdbGetMin);
	BOOL SetPMMaxMinPowerStopForNET(long lChIndex);
	BOOL SetPMPowerOffsetForNET(long lChIndex,double dbPowerOffset);

	//////////////////////////VOA网络函数/////////////////////////////////////////////////
	BOOL CloseVOADeviceForNET(long lChIndex);
	BOOL ResetVOADeviceForNET(long lChIndex);
	BOOL SetVOAWavelengthForNET(long lChIndex, double dblWL);
	BOOL GetVOAWavelengthForNET(long lChIndex, double* pdblWL);
    BOOL SetVOAAttenuationForNET(long lChIndex, double dblAtten);
	BOOL GetVOAAttenuationForNET(long lChIndex, double* pdblAtten);
	BOOL SetVOAEnableOutputForNET(long lChIndex, BOOL bEnable);
	BOOL SetVOAInputOffsetForNET(long lChIndex, double dblOffset);
	BOOL GetVOAStatusForNET(long lChIndex,DWORD *dwStatus);

	//////////////////////////////偏振控制器网络函数/////////////////////////////////////
	BOOL ClosePolDeviceForNET(long lChIndex);
	BOOL ResetPolDeviceForNET(long lChIndex);
	BOOL GetPolDeviceInfoForNET(long lChIndex,stDevInfo *stInfo);
	BOOL GetPolCurrentPOSPolarizerForNET(long lChIndex,double * pdblAlphaP,double *pdblAlphaQ,double *pdblAlphaH);
	BOOL SetPolALLForNET(long lChIndex,double alphaP, double alphaQ, double alphaH);
	BOOL SetPolDiagonalAnglesForNET(long lChIndex,double AlphaPMax, double Wavelength);
	BOOL SetPolHorizontalAnglesForNET(long lChIndex,double AlphaPMax, double Wavelength);
	BOOL SetPolPOSHalfForNET(long lChIndex,double alpha);
	BOOL SetPolPOSPolarizerForNET(long lChIndex,double alpha);
	BOOL SetPolPOSQuarterForNET(long lChIndex,double alpha);
	BOOL SetPolRightHandCircularAnglesForNET(long lChIndex,double AlphaPMax, double Wavelength);
	BOOL SetPolVerticalAnglesForNET(long lChIndex,double AlphaPMax, double Wavelength);

	//////////////循环箱控制网络函数/////////////////////////////////////////////
	BOOL  CloseChamberDeviceForNET(long lChIndex);
	BOOL  GetChamberDeviceInfoForNET(long lChIndex,stDevInfo *stInfo);
	BOOL  SetChamberRunStopForNET(long lChIndex);
	BOOL  SetChamberRunStartForNET(long lChIndex);
	BOOL  SetChamberSetPointForNET(long lChIndex,double dbSetPoint);
	BOOL  GetChamberSetPointForNET(long lChIndex,double* dbSetPoint);
	BOOL  GetChamberCurrentTempForNET(long lChIndex,double *dbCurrTemp);

	////////////////通信接口网络函数///////////////////////////////////////////////////////////////
	BOOL  WriteDevComBufferForNET(long lChIndex,unsigned char* pOutBuffer, DWORD dwBufferSize);
	BOOL  ReadDevComBufferForNET(long lChIndex,unsigned char* pInBuffer, DWORD dwBufferSize);
	BOOL  CloseDevDeviceForNET(long lChIndex);
	BOOL  OpenDevDeviceForNET(long lChIndex);

    ////////////////SwtichBox网络函数///////////////////////////////////////////////////////////////
	BOOL  CloseSwitchDeviceForNET(long lChIndex);
	BOOL  OpenSwitchDeviceForNET(long lChIndex);
    BOOL  SwitchPort2PortForNET(int lChIndex,int nInputPort, int nOutputPort);

	//////////////OSA接口网络函数///////////////////////////////////////
	BOOL CloseOSADeviceForNET(long lChIndex);
	BOOL ResetOSADeviceForNET(long lChIndex);
	BOOL SetOSALocalCtrlForNET(long lChIndex);
	BOOL SetOSARBWForNET(long lChIndex,double dblRBW);
	BOOL GetOSARBWForNET(long lChIndex,double* pdblRBW);
	BOOL InitOSAAmpTestForNET(long lChIndex,double dblStartWL,double dblStopWL,double dblRBW);
	BOOL MeasureOSASourceForNET(long lChIndex);
	BOOL MeasureOSAAmplifierForNET(long lChIndex,BOOL bScanSrcOnly = FALSE);
	BOOL GetOSAChannelCountForNET(long lChIndex,DWORD* pdwChannelCount);
	BOOL GetOSAChannelWaveLensForNET(long lChIndex,double* pdblWL,DWORD* pdwChannelCount);
	BOOL GetOSAChannelNFForNET(long lChIndex,double* pdblNF,DWORD* pdwChannelCount);
	BOOL GetOSAChannelGainForNET(long lChIndex,double* pdblGain,DWORD* pdwChannelCount);
	BOOL GetOSAChannelSNRForNET(long lChIndex,double* pdblSNR,DWORD* pdwChannelCount);
	BOOL GetOSAChannelSourcePowerForNET(long lChIndex,double* pdblSourcePow,DWORD* pdwChannelCount);
	BOOL SetOSAAmpOffsetForNET(long lChIndex,double dblSourceOffset, double dblAmpOffset);
	BOOL GetOSAAmpOffsetForNET(long lChIndex,double &dblSourceOffset, double &dblAmpOffset);
	BOOL GetOSAEDFAResultForNET(long lChIndex,double *pdblSumSrcSigPwr, double *pdblSumAmpSigPwr, double *pdblSunGain);
	BOOL GetOSAEDFAChResultForNET(long lChIndex,DWORD *pwChCount, double *pdblChWL, double *pdblSrcpwr, double *pdblChGain, double *pdblChNF, double *pdblChAse,
	double *pdblGainFlatness, double *pdblMaxNF, double* pdblMaxGain, double* pdblMinGain);
	BOOL InitOSASingleSweepForNET(long lChIndex,double dblStartWL, double dblStopWL, double dblRBW, DWORD dwSweepPoint);
	BOOL RunOSASweepForNET(long lChIndex,double* pdblWL,double* pdblPower,char szSelTrace);
	BOOL GetSingleSweepPointForNET(long lChIndex,DWORD *pdwPointCount);
	BOOL GetOSASweepDataForNET(long lChIndex,double* pdblWL,double* pdblPower, char szSelTrace);
	BOOL SaveOSADataToPCForNET(long lChIndex,LPCTSTR lpSavePath, LPCTSTR lpDataType, LPCTSTR lpFileType, char szSelTrace);	
	BOOL SetOSACalibrationForNET(long lChIndex,DWORD dwCalibrationType);
	BOOL GetZoomValueForNET(long lChIndex,double dbWLNM,double dbBWNM,double *pdbGetValue);
	BOOL ReceiveArryAndAnlysis(const char* lpstr,double*pdbArry,int& nPointCount);

};

#endif // !defined(AFX_DEVICEMANGER_H__CAAD3284_2FFA_4E63_9641_A32A7FF1EC43__INCLUDED_)
