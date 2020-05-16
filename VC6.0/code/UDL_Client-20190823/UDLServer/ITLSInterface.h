// ITLSInterface.h : Declaration of the CITLSInterface

#ifndef __ITLSINTERFACE_H_
#define __ITLSINTERFACE_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CITLSInterface
class ATL_NO_VTABLE CITLSInterface : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CITLSInterface, &CLSID_ITLSInterface>,
	public IDispatchImpl<IITLSInterface, &IID_IITLSInterface, &LIBID_UDLSERVERLib>
{
public:
	CITLSInterface()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ITLSINTERFACE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CITLSInterface)
	COM_INTERFACE_ENTRY(IITLSInterface)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IITLSInterface
public:
	STDMETHOD(SetTLSWavelength)(/*[in]*/ long lChIndex,/*[in]*/ double dblWL);
	STDMETHOD(get_LastMessage)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(CloseTLSDevice)(/*[in]*/ long lChIndex);
	STDMETHOD(SetTLSOutputEnable)(/*[in]*/long lChIndex,/*[in]*/ BOOL bEnable);
	STDMETHOD(SetTLSParameters)(/*[in]*/long lChIndex,/*[in]*/long lLowSSE,/*[in]*/double dblPower,/*[int]*/ double dblWavelength);
	STDMETHOD(SetTLSSourceUnit)(/*[in]*/long lChIndex,/*[in]*/ long lUnit);
	STDMETHOD(SetTLSCoherenceControl)(/*[in]*/ long lChIndex,/*[in]*/ BOOL bEnable);
	STDMETHOD(SetTLSSourcePower)(/*[in]*/ long lChIndex,/*[in]*/ double dblPW);
	BSTR m_strMessage;
};

#endif //__ITLSINTERFACE_H_
