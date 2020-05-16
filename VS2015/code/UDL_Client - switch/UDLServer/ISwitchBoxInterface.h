// ISwitchBoxInterface.h : Declaration of the CISwitchBoxInterface

#ifndef __ISWITCHBOXINTERFACE_H_
#define __ISWITCHBOXINTERFACE_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CISwitchBoxInterface
class ATL_NO_VTABLE CISwitchBoxInterface : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CISwitchBoxInterface, &CLSID_ISwitchBoxInterface>,
	public IDispatchImpl<IISwitchBoxInterface, &IID_IISwitchBoxInterface, &LIBID_UDLSERVERLib>
{
public:
	CISwitchBoxInterface()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ISWITCHBOXINTERFACE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CISwitchBoxInterface)
	COM_INTERFACE_ENTRY(IISwitchBoxInterface)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IISwitchBoxInterface
public:
	STDMETHOD(get_LastMessage)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(SwitchPort2Port)(/*[in]*/int lChIndex,/*[in]*/int nInputPort, /*[in]*/int nOutputPort);
	STDMETHOD(CloseSwitchDevice)(/*[in]*/long lChIndex);
	STDMETHOD(OpenSwitchDevice)(/*[in]*/long lChIndex);

	BSTR m_strMessage;
};

#endif //__ISWITCHBOXINTERFACE_H_
