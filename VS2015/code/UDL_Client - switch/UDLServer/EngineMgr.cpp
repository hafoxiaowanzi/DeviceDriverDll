// EngineMgr.cpp : Implementation of CEngineMgr
#include "stdafx.h"
#include "UDLServer.h"
#include "EngineMgr.h"
#include "DeviceManger.h"

/////////////////////////////////////////////////////////////////////////////
// CEngineMgr
extern CDeviceManger _DeviceManager;
typedef HRESULT (WINAPI * FREG)(); 

STDMETHODIMP CEngineMgr::get_GetVersion(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
    *pVal = m_strVersion;
	DWORD dwVersion = ::GetVersion();
	return S_OK;
}

STDMETHODIMP CEngineMgr::put_GetVersion(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
    m_strVersion = newVal;
	
	return S_OK;
}

STDMETHODIMP CEngineMgr::get_GetLastMessage(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
		
	// TODO: Add your implementation code here
	*pVal = m_strMessage;
	return S_OK;
}

STDMETHODIMP CEngineMgr::put_GetLastMessage(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
		
	// TODO: Add your implementation code here
	m_strMessage = newVal;
	return S_OK;
}


STDMETHODIMP CEngineMgr::OpenEngine()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	
	if(!_DeviceManager.OpenDevice())
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
    m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
	return S_OK;
}

STDMETHODIMP CEngineMgr::LoadConfiguration(BSTR FileName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	CString strFileName;
    strFileName = FileName;	
	BOOL bRet = _DeviceManager.LoadConfigXML(strFileName);
	_DeviceManager.InitDevObject();
	if (!bRet)
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
    m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
	return S_OK;
}

STDMETHODIMP CEngineMgr::RegisterUDL()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
		
		// TODO: Add your implementation code here	
	TCHAR szWorkPath[ MAX_PATH ]; 
	::GetCurrentDirectory( sizeof(szWorkPath), szWorkPath ); // ���浱ǰ���̵Ĺ���Ŀ¼ 
	::SetCurrentDirectory(szWorkPath);  // �л��������Ŀ¼ 

	HMODULE hDLL = ::LoadLibrary("UDL.DLM.dll");  // ��̬װ����� 
	if(hDLL) 
	{ 
		
		FREG lpfunc = (FREG)::GetProcAddress( hDLL, _T("DllRegisterServer") );  // ȡ��ע�ắ��ָ�� 
		
		// ����Ƿ�ע�ᣬ����ȡ��"DllUnregisterServer"����ָ��     
		if ( lpfunc )   
			lpfunc();   // ִ��ע�ᡣ����Ϊ�˼򵥣�û���жϷ���ֵ     
		::FreeLibrary(hDLL); 
	} 
	::SetCurrentDirectory(szWorkPath); 
	return S_OK;
}

STDMETHODIMP CEngineMgr::SetUDLNET(BOOL bIsNet)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	_DeviceManager.SetUDLNET(bIsNet);
	return S_OK;  
}

STDMETHODIMP CEngineMgr::ConnectToServer(BSTR pstrIPAddress)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
    CString strIP;
	strIP = pstrIPAddress;
	if(!_DeviceManager.ConnectToServer(strIP))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}
