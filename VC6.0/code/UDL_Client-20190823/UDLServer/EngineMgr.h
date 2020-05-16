// EngineMgr.h : Declaration of the CEngineMgr

#ifndef __ENGINEMGR_H_
#define __ENGINEMGR_H_

#include "resource.h"       // main symbols
#include "UDLServerCP.h"

/////////////////////////////////////////////////////////////////////////////
// CEngineMgr
class ATL_NO_VTABLE CEngineMgr : 
public CComObjectRootEx<CComSingleThreadModel>,
public CComCoClass<CEngineMgr, &CLSID_EngineMgr>,
public IConnectionPointContainerImpl<CEngineMgr>,
public IDispatchImpl<IEngineMgr, &IID_IEngineMgr, &LIBID_UDLSERVERLib>,
	public CProxy_IEngineMgrEvents< CEngineMgr >
{
public:
	CEngineMgr()
	{
		m_strVersion = SysAllocString(L"1.0.0.0");
		m_strMessage = SysAllocString(L"NO Error");
	}
	
	DECLARE_REGISTRY_RESOURCEID(IDR_ENGINEMGR)
		
		DECLARE_PROTECT_FINAL_CONSTRUCT()
		
		BEGIN_COM_MAP(CEngineMgr)
		COM_INTERFACE_ENTRY(IEngineMgr)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(IConnectionPointContainer)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
		END_COM_MAP()
		BEGIN_CONNECTION_POINT_MAP(CEngineMgr)
		END_CONNECTION_POINT_MAP()
				
		// IEngineMgr
public:
	STDMETHOD(ConnectToServer)(/*[in]*/ BSTR pstrIPAddress);
	STDMETHOD(SetUDLNET)(/*[in]*/BOOL bIsNet);
	STDMETHOD(RegisterUDL)();
	STDMETHOD(LoadConfiguration)(/*[in]*/ BSTR FileName);
	STDMETHOD(OpenEngine)();
	STDMETHOD(get_GetLastMessage)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_GetVersion)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_GetVersion)(/*[in]*/ BSTR newVal);
	STDMETHOD(put_GetLastMessage)(/*[out, retval]*/BSTR newVal);
protected:
	BSTR m_strMessage;
	BSTR m_strVersion;
	//CAglient8164Ctrl m_8164;
};

#endif //__ENGINEMGR_H_
