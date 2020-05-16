// IOSAInterface.h : Declaration of the CIOSAInterface

#ifndef __IOSAINTERFACE_H_
#define __IOSAINTERFACE_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CIOSAInterface
class ATL_NO_VTABLE CIOSAInterface : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CIOSAInterface, &CLSID_IOSAInterface>,
	public IDispatchImpl<IIOSAInterface, &IID_IIOSAInterface, &LIBID_UDLSERVERLib>
{
public:
	CIOSAInterface()
	{
		
	}

DECLARE_REGISTRY_RESOURCEID(IDR_IOSAINTERFACE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CIOSAInterface)
	COM_INTERFACE_ENTRY(IIOSAInterface)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IIOSAInterface
public:
	//STDMETHOD(InitOSARepeatSweep)(/*[in]*/long lChIndex,/*[in]*/ double dblStartWL,/*[in]*/ double dblStopWL,/*[in]*/ double dblRBW,/*[in]*/long lSweepPointCount);
	STDMETHOD(MeasureOSAWDM)(/*[in]*/long lChIndex);
	STDMETHOD(InitOSAWDMTest)(/*[in]*/long lChIndex,/*[in]*/double dblStartWL,/*[in]*/double dblStopWL,/*[in]*/double dblRBW);
	STDMETHOD(GetOSASingleSweepPoint)(/*[in]*/ long lChIndex,/*[out]*/ long* pVal);
	STDMETHOD(GetOSAZoomValue)(/*[in]*/long lChIndex,/*[in]*/double dbWLNM,/*[in]*/double dbBWNM,/*[out]*/double* pdbGetValue);
	STDMETHOD(GetChannelSourcePower)(/*[in]*/long lChIndex,/*[out]*/double* pdblSourcePower,/*[out]*/DWORD* pdwChannelCount);
	STDMETHOD(GetChannelSNR)(/*[in]*/long lChIndex,/*[out]*/double* pdblSNR,/*[out]*/DWORD* pdwChannelCount);
	STDMETHOD(GetChannelGain)(/*[in]*/long lChIndex,/*[out]*/double* pdblGain,/*[out]*/DWORD* pdwChannelCount);
	STDMETHOD(GetChannelNF)(/*[in]*/long lChIndex,/*[out]*/double* pdblNF,/*[out]*/DWORD* pdwChannelCount);
	STDMETHOD(GetChannelWaveLens)(/*[in]*/long lChanIndex,/*[out]*/double* pdblWL,/*[out]*/DWORD* pdwlChanneCount);
	STDMETHOD(ChannelWaveLens)(/*[out]*/double * pdblWL,/*[out]*/DWORD* pdwChannelCount);
	STDMETHOD(get_LastMessage)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(SaveOSADataToPC)(/*[in]*/long lChIndex,/*[in]*/BSTR lpSavePath,/*[in]*/BSTR lpDataType,/*[in]*/BSTR  lpFileType,/*[in]*/BSTR szSelTrace);
	STDMETHOD(SetOSACalibration)(/*[in]*/long lChIndex,/*[in]*/long lCalibrationType);
	STDMETHOD(GetOSASweepData)(/*[in]*/long lChIndex,/*[out]*/double* pdblWL,/*[out]*/double * pdblPower,/*[in]*/BSTR szSelTrace);
	STDMETHOD(RunOSASweep)(/*[in]*/long lChIndex,/*[out]*/double *pdblWL,/*[out]*/double* pdblPower,/*[in]*/ BSTR szSelTrace);
//	STDMETHOD(RunOSASweep)(/*[in]*/long lChIndex,/*[out]*/double *pdblWL,/*[out]*/double* pdblPower,/*[in]*/ char szSelTrace);
	STDMETHOD(InitOSASingleSweep)(/*[in]*/long lChIndex,/*[in]*/ double dblStartWL,/*[in]*/ double dblStopWL,/*[in]*/ double dblRBW,/*[in]*/long lSweepPointCount);
	STDMETHOD(GetOSAEDFAChResult)(/*[in]*/long lChIndex,/*[out]*/long *pwChCount, /*[out]*/double *pdblChWL,/*[out]*/ double *pdblSrcpwr,/*[out]*/ double *pdblChGain,/*[out]*/ double *pdblChNF, /*[out]*/double *pdblChAse, /*[out]*/ double* pdbGainFlatness,/*[out]*/double*pdblMaxNF,/*[out]*/double* pdblMaxGain,/*[out]*/ double* pdblMinGain);
	STDMETHOD(GetOSAAmpOffset)(/*[in]*/ long lChIndex,/*[out]*/double*pdblSourceOffSet,/*[out]*/double* pdblAmpOffset);
//	STDMETHOD(SaveOSADataToPC)(/*[in]*/long lChIndex,/*[in]*/BSTR lpSavePath,/*[in]*/BSTR lpDataType,/*[in]*/BSTR  lpFileType,/*[in]*/char szSelTrace);
//	STDMETHOD(SetOSACalibration)(/*[in]*/long lChIndex,/*[in]*/long lCalibrationType);
//	STDMETHOD(GetOSASweepData)(/*[in]*/long lChIndex,/*[out]*/double* pdblWL,/*[out]*/double * pdblPower,/*[in]*/char szSelTrace);
//	STDMETHOD(RunOSASweep)(/*[in]*/long lChIndex,/*[out]*/double *pdblWL,/*[out]*/double* pdblPower,/*[in]*/ char szSelTrace);
//	STDMETHOD(InitOSASingleSweep)(/*[in]*/long lChIndex,/*[in]*/ double dblStartWL,/*[in]*/ double dblStopWL,/*[in]*/ double dblRBW,/*[in]*/long lSweepPointCount);
//	STDMETHOD(GetOSAEDFAChResult)(/*[in]*/long lChIndex,/*[out]*/long *pwChCount, /*[out]*/double *pdblChWL,/*[out]*/ double *pdblSrcpwr,/*[out]*/ double *pdblChGain,/*[out]*/ double *pdblChNF, /*[out]*/double *pdblChAse, /*[out]*/ double* pdbGainFlatness,/*[out]*/double*pdblMaxNF,/*[out]*/double *pdblMaxGain,/*[out]*/ double *pdblMinGain);
	STDMETHOD(GetOSAEDFAResult)(/*[in]*/long lChIndex,/*[out]*/ double* pdblSumSrcSigPwr,/*[out]*/double* pdblSumAmpSigPwr,/*[out]*/double* pdblSumGain);
	STDMETHOD(SetOSAAmpOffset)(/*[in]*/long lChIndex,/*[in]*/double dblSourceOffset,/*[in]*/double dblAmpOffset);
	STDMETHOD(GetOSAChannelCount)(/*[in]*/long lChIndex, /*[out, retval]*/ long *pVal);
	STDMETHOD(MeasureAmplifier)(/*[in]*/long lChIndex,/*[in]*/BOOL bScanSrcOnly);
	STDMETHOD(MeasureSource)(/*[in]*/long lChIndex);
	STDMETHOD(InitOSAAmpTest)(/*[in]*/long lChIndex,/*[in]*/ double dblStartWL,/*[in]*/ double dblStopWL,/*[in]*/ double dblRBW);
	STDMETHOD(GetOSARBW)(/*[in]*/long lChIndex, /*[out, retval]*/ double *pVal);
	STDMETHOD(SetOSARBW)(/*[in]*/ long lChIndex,/*[in]*/double dblRBW);
	STDMETHOD(SetOSALocalCtrl)(/*[in]*/long lChIndex);
	STDMETHOD(ResetDevice)(/*[in]*/long lChIndex);
	STDMETHOD(CloseDevice)(/*[in]*/long lChIndex);
	BSTR m_strMessage;
	STDMETHOD(InitOSARepeatSweep)(LONG lChIndex, DOUBLE dblStartWL, DOUBLE dblStopWL, DOUBLE dblRBW, LONG lSweepPointCount);
};

#endif //__IOSAINTERFACE_H_
