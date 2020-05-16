// ChamberContrlDll.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "..\\include\\ChamberContrlDll.h"





BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			break;
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }

    return TRUE;
}


// This is an example of an exported variable
CHAMBERCONTROLDLL_API int nChamberDll=0;

// This is an example of an exported function.
CHAMBERCONTROLDLL_API int fnChamberDll(void)
{

	return 42;
}


CChamberDll::CChamberDll()
{
	m_pChamber = NULL;
}

CChamberDll::~CChamberDll()
{
	if (m_pChamber!=NULL)
	{
		delete m_pChamber;
		m_pChamber = NULL;
	}
}

DWORD CChamberDll::OpenDevice(stDevType stType, LPCTSTR pszDeviceAddr, unsigned long *Comhandle)
{
	long lChamberType=stType.bType;
	DWORD dwErrorCode = SUCCESS;
	if (m_pChamber!=NULL)
	{
		delete m_pChamber;
		m_pChamber = NULL;
	}
	if (HONGZHAN == lChamberType) 
	{
		m_pChamber = new CHZChamberContorl();	
	}
	else 
	{
		return ERROR_COMMUNICATION_INFO;	
	}

	//m_pPm = m_pvoid+lPMType;
	dwErrorCode = m_pChamber->OpenDevice(pszDeviceAddr,Comhandle);

	return dwErrorCode;
}

DWORD CChamberDll::SetHandle(stDevType stType, LPCTSTR pszDeviceAddr, unsigned long handle)
{
	long lChamberType=stType.bType;
	DWORD dwErrorCode = SUCCESS;
	
	if (HONGZHAN == lChamberType) 
	{
		m_pChamber = new CHZChamberContorl();	
	}
	else 
	{
		return ERROR_COMMUNICATION_INFO;	
	}
	

	dwErrorCode =m_pChamber->SetHandle(pszDeviceAddr, handle);

	return dwErrorCode;
}

DWORD  CChamberDll::CloseDevice()
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pChamber!=NULL)
	{
		dwErrorCode =m_pChamber->CloseDevice();
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;	
}
DWORD  CChamberDll::GetDeviceInfo(stDevInfo *stInfo)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pChamber!=NULL)
	{
		dwErrorCode =m_pChamber->GetDeviceInfo(stInfo);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	
	return dwErrorCode;	
}
DWORD  CChamberDll::SetChamberRunStop()
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pChamber!=NULL)
	{
		dwErrorCode =m_pChamber->SetChamberRunStop();
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	
	return dwErrorCode;	
}
DWORD  CChamberDll::SetChamberRunStart()
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pChamber!=NULL)
	{
		dwErrorCode =m_pChamber->SetChamberRunStart();
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	
	return dwErrorCode;	
}
DWORD  CChamberDll::SetChamberSetPoint(double dbSetPoint)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pChamber!=NULL)
	{
		dwErrorCode =m_pChamber->SetChamberSetPoint(dbSetPoint);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;	
}
DWORD  CChamberDll::GetChamberSetPoint(double* dbSetPoint)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pChamber!=NULL)
	{
		dwErrorCode =m_pChamber->GetChamberSetPoint(dbSetPoint);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	
	return dwErrorCode;	
}
DWORD  CChamberDll::GetChamberCurrentTemp(double *dbCurrTemp)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pChamber!=NULL)
	{
		dwErrorCode =m_pChamber->GetChamberCurrentTemp(dbCurrTemp);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	
	return dwErrorCode;	
}