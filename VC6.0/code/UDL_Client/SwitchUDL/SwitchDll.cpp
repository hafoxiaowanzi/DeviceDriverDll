// PolDll.cpp: implementation of the CPolDll class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\\include\\SwitchDll.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}
// This is an example of an exported variable
SWITCHCONTROLDLL_API int nSwitchControlDll=0;

// This is an example of an exported function.
SWITCHCONTROLDLL_API int fnSwtichControlDll(void)
{
	return 42;
}

CSwitchDll::CSwitchDll()
{
	m_pSwitch = NULL;
}

CSwitchDll::~CSwitchDll()
{
	if (m_pSwitch!=NULL)
	{
		delete m_pSwitch;
		m_pSwitch = NULL;
	}
}
DWORD CSwitchDll::OpenDevice(stDevType stType, LPCTSTR pszDeviceAddr, unsigned long *Comhandle)
{
	long lPolType=stType.bType;
	DWORD dwErrorCode = SUCCESS;

	if (IT_1X2SW == lPolType) 
	{
		m_pSwitch = new CIT_1X2SW();	
	}
	else if (IT_1X8SW == lPolType)
	{
		m_pSwitch = new CIT_1X8SW();	
	}
	else if (OMS_1X64SW == lPolType)
	{
		m_pSwitch = new COMS_1X64SW();	
	}
	else 
	{
		return ERROR_COMMUNICATION_INFO;	
	}

	dwErrorCode = m_pSwitch->OpenDevice(pszDeviceAddr, Comhandle);

	return dwErrorCode;
}

DWORD CSwitchDll::SetHandle(stDevType stType, LPCTSTR pszDeviceAddr, unsigned long handle)
{
	long lPolType=stType.bType;
	DWORD dwErrorCode = SUCCESS;

	if (IT_1X2SW == lPolType) 
	{
		m_pSwitch = new CIT_1X2SW();	
	}
	else if (IT_1X8SW == lPolType)
	{
		m_pSwitch = new CIT_1X8SW();	
	}
	else if (OMS_1X64SW == lPolType)
	{
		m_pSwitch = new COMS_1X64SW();	
	}
	else 
	{
		return ERROR_COMMUNICATION_INFO;	
	}
	
	dwErrorCode =m_pSwitch->SetHandle(pszDeviceAddr, handle);

	return dwErrorCode;
}
DWORD  CSwitchDll::CloseDevice()
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch!=NULL)
	{
		dwErrorCode =m_pSwitch->CloseDevice();
	}
	else
	{
		dwErrorCode =UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD  CSwitchDll::SwitchPort2Port(int nSwitchIndex,int nInputPort, int nOutputPort)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch!=NULL)
	{
		dwErrorCode =m_pSwitch->SwitchPort2Port(nSwitchIndex,nInputPort,nOutputPort);
	}
	else
	{
		dwErrorCode =UNEXPECT_OCCUR;
	}

	return dwErrorCode;

}