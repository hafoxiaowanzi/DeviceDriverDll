// ScanInterface.h : Declaration of the CScanInterface

#ifndef __SCANINTERFACE_H_
#define __SCANINTERFACE_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CScanInterface
class ATL_NO_VTABLE CScanInterface : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CScanInterface, &CLSID_ScanInterface>,
	public IDispatchImpl<IScanInterface, &IID_IScanInterface, &LIBID_UDLSERVERLib>
{
public:
	CScanInterface()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SCANINTERFACE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CScanInterface)
	COM_INTERFACE_ENTRY(IScanInterface)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IScanInterface
public:
	STDMETHOD(get_LastMessage)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(ReleaseAllocStruct)(/*[in]*/long lpStructPtr);
	STDMETHOD(GetCalILAndPDLResult)(/*[in]*/long  lpScanResult);
	STDMETHOD(GetCalILResult)(/*[in]*/long lpScanResult);
	STDMETHOD(DoScan)(/*[in]*/long lTLSChIndex,/*[in]*/long lpScanRawData);
	STDMETHOD(DoScanRef)(/*[in]*/long lTLSChIndex,/*[in]*/long lpScanRawData);
	STDMETHOD(ReleaseScan)(/*[in]*/long lTLSChIndex);
	STDMETHOD(ExecuteScan)(/*[in]*/long lTLSChIndex,/*[in]*/long lpScanRawDataPtr);
	STDMETHOD(PrepareScan)(/*[in]*/long lTLSChIndex,/*[in]*/long lpScanParam);
	BSTR  m_strMessage;
};

#endif //__SCANINTERFACE_H_
