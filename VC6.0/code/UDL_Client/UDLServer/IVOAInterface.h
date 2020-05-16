// IVOAInterface.h : Declaration of the CIVOAInterface

#ifndef __IVOAINTERFACE_H_
#define __IVOAINTERFACE_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CIVOAInterface
class ATL_NO_VTABLE CIVOAInterface : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CIVOAInterface, &CLSID_IVOAInterface>,
	public IDispatchImpl<IIVOAInterface, &IID_IIVOAInterface, &LIBID_UDLSERVERLib>
{
public:
	CIVOAInterface()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_IVOAINTERFACE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CIVOAInterface)
	COM_INTERFACE_ENTRY(IIVOAInterface)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IIVOAInterface
public:
	STDMETHOD(get_LastMessage)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(GetVOAStatus)(/*[in]*/long lChIndex, /*[out, retval]*/ long *pVal);
	STDMETHOD(SetVOAInputOffset)(/*[in]*/long lChIndex,/*[in]*/ double dblOffset);
	STDMETHOD(SetVOAEnableOutput)(/*[in]*/long lChIndex,/*[in]*/BOOL bEanble);
	STDMETHOD(GetVOAAttenuation)(/*[in]*/long lChIndex, /*[out, retval]*/ double *pVal);
	STDMETHOD(SetVOAAttenuation)(/*[in]*/long lChIndex,/*[in]*/double dblAtten);
	STDMETHOD(GetVOAWavelength)(/*[In]*/long lChIndex, /*[out, retval]*/ double *pVal);
	STDMETHOD(SetVOAWavelength)(/*[in]*/ long lChIndex,/*[in]*/double dblWL);
	STDMETHOD(ResetVOADevice)(/*[in]*/long lChIndex);
	STDMETHOD(CloseVOADevice)(/*[in]*/long lChIndex);
	BSTR m_strMessage;
};

#endif //__IVOAINTERFACE_H_
