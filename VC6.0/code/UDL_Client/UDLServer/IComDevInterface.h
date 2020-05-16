// IComDevInterface.h : Declaration of the CIComDevInterface

#ifndef __ICOMDEVINTERFACE_H_
#define __ICOMDEVINTERFACE_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CIComDevInterface
class ATL_NO_VTABLE CIComDevInterface : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CIComDevInterface, &CLSID_IComDevInterface>,
	public IDispatchImpl<IIComDevInterface, &IID_IIComDevInterface, &LIBID_UDLSERVERLib>
{
public:
	CIComDevInterface()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ICOMDEVINTERFACE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CIComDevInterface)
	COM_INTERFACE_ENTRY(IIComDevInterface)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IIComDevInterface
public:
	STDMETHOD(get_LastMessage)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(OpenSerial)(/*[in]*/long lChIndex);
	STDMETHOD(CloseSerial)(/*[in]*/long lChIndex);
	STDMETHOD(ReadBuffer)(/*[in]*/long lChIndex,/*[out]*/BSTR* pBuffer,/*[in]*/DWORD dwBufferSize);
	STDMETHOD(WriteBuffer)(/*[in]*/long lChIndex,/*[in]*/BSTR pBuffer,/*[in]*/DWORD dwBufferSize);

	BSTR m_strMessage;
};

#endif //__ICOMDEVINTERFACE_H_
