// UDLServer.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To merge the proxy/stub code into the object DLL, add the file 
//      dlldatax.c to the project.  Make sure precompiled headers 
//      are turned off for this file, and add _MERGE_PROXYSTUB to the 
//      defines for the project.  
//
//      If you are not running WinNT4.0 or Win95 with DCOM, then you
//      need to remove the following define from dlldatax.c
//      #define _WIN32_WINNT 0x0400
//
//      Further, if you are running MIDL without /Oicf switch, you also 
//      need to remove the following define from dlldatax.c.
//      #define USE_STUBLESS_PROXY
//
//      Modify the custom build rule for UDLServer.idl by adding the following 
//      files to the Outputs.
//          UDLServer_p.c
//          dlldata.c
//      To build a separate proxy/stub DLL, 
//      run nmake -f UDLServerps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "UDLServer.h"
#include "dlldatax.h"

#include "UDLServer_i.c"
#include "EngineMgr.h"
#include "DeviceManger.h"
#include "ITLSInterface.h"
#include "IPMInterface.h"
#include "IVOAInterface.h"
#include "IOSAInterface.h"
#include "IPolInterface.h"
#include "ScanInterface.h"
#include "ChamberInterface.h"
#include "IComDevInterface.h"
#include "ISwitchBoxInterface.h"

#ifdef _MERGE_PROXYSTUB
extern "C" HINSTANCE hProxyDll;
#endif

CComModule _Module;
CDeviceManger _DeviceManager;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_EngineMgr, CEngineMgr)
OBJECT_ENTRY(CLSID_ITLSInterface, CITLSInterface)
OBJECT_ENTRY(CLSID_IPMInterface, CIPMInterface)
OBJECT_ENTRY(CLSID_IVOAInterface, CIVOAInterface)
OBJECT_ENTRY(CLSID_IOSAInterface, CIOSAInterface)
OBJECT_ENTRY(CLSID_IPolInterface, CIPolInterface)
OBJECT_ENTRY(CLSID_ScanInterface, CScanInterface)
OBJECT_ENTRY(CLSID_ChamberInterface, CChamberInterface)
OBJECT_ENTRY(CLSID_IComDevInterface, CIComDevInterface)
OBJECT_ENTRY(CLSID_ISwitchBoxInterface, CISwitchBoxInterface)
END_OBJECT_MAP()

class CUDLServerApp : public CWinApp
{
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUDLServerApp)
	public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CUDLServerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CUDLServerApp, CWinApp)
	//{{AFX_MSG_MAP(CUDLServerApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CUDLServerApp theApp;

BOOL CUDLServerApp::InitInstance()
{
#ifdef _MERGE_PROXYSTUB
    hProxyDll = m_hInstance;
#endif
    _Module.Init(ObjectMap, m_hInstance, &LIBID_UDLSERVERLib);
    return CWinApp::InitInstance();
}

int CUDLServerApp::ExitInstance()
{
    _Module.Term();
    return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
#ifdef _MERGE_PROXYSTUB
    if (PrxDllCanUnloadNow() != S_OK)
        return S_FALSE;
#endif
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    return (AfxDllCanUnloadNow()==S_OK && _Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
#ifdef _MERGE_PROXYSTUB
    if (PrxDllGetClassObject(rclsid, riid, ppv) == S_OK)
        return S_OK;
#endif
    return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
#ifdef _MERGE_PROXYSTUB
    HRESULT hRes = PrxDllRegisterServer();
    if (FAILED(hRes))
        return hRes;
#endif
    // registers object, typelib and all interfaces in typelib
    return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
#ifdef _MERGE_PROXYSTUB
    PrxDllUnregisterServer();
#endif
    return _Module.UnregisterServer(TRUE);
}


