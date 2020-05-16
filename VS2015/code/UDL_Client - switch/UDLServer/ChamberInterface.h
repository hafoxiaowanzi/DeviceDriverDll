// ChamberInterface.h : Declaration of the CChamberInterface

#ifndef __CHAMBERINTERFACE_H_
#define __CHAMBERINTERFACE_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CChamberInterface
class ATL_NO_VTABLE CChamberInterface : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CChamberInterface, &CLSID_ChamberInterface>,
	public IDispatchImpl<IChamberInterface, &IID_IChamberInterface, &LIBID_UDLSERVERLib>
{
public:
	CChamberInterface()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CHAMBERINTERFACE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CChamberInterface)
	COM_INTERFACE_ENTRY(IChamberInterface)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IChamberInterface
public:
	STDMETHOD(get_LastMessage)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(GetChamberCurrentTemp)(/*[in]*/long lChIndex,/*[out]*/double* dbCurrTemp);
	STDMETHOD(GetChamberSetPoint)(/*[in]*/long lChIndex,/*[out]*/double* dbSetPoint);
	STDMETHOD(SetChamberSetPoint)(/*[in]*/long lChIndex,/*[in]*/double dbSetPoint);
	STDMETHOD(SetChamberRunStart)(/*[in]*/long lChIndex);
	STDMETHOD(SetChamberRunStop)(/*[in]*/long lChIndex);
	STDMETHOD(CloseChamberDevice)(/*[in]*/long lChIndex);
	BSTR m_strMessage;
};

#endif //__CHAMBERINTERFACE_H_
