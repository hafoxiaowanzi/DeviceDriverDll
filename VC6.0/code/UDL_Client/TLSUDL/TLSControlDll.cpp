// TLSControlDll.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "..\\include\\TLS.h"
#include "..\\include\\TLSControlDll.h"


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
TLSCONTROLDLL_API int nTLSControlDll=0;

// This is an example of an exported function.
TLSCONTROLDLL_API int fnTLSControlDll(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see TLSControlDll.h for the class definition
CTLSDll::CTLSDll():m_pTLS(NULL)
{	

}

CTLSDll::~CTLSDll()
{ 
    if (m_pTLS!=NULL)
	{
		delete m_pTLS;
		m_pTLS =NULL;
    }

	return;
}

DWORD CTLSDll::OpenDevice(stDevType stType, LPCTSTR pszDeviceAddr,unsigned long *ComHandle)
{
	long lType = stType.bType;
	DWORD dwErrorCode = SUCCESS;

	if (m_pTLS !=NULL)
	{
		delete m_pTLS;
		m_pTLS =NULL;
	}

	if (HP_816X == lType) 
	{
		m_pTLS = new COp816XCtrl();
	}
	else if (OPLK_TLS == lType)
	{
		m_pTLS = new CiTLALaser();
	}
	else if(AGLIENT81960A ==lType)
	{
	   m_pTLS = new COp81960A();
	}
	else if(SANTEC_TLS == lType)
	{
		m_pTLS =  new CSantecTLS();
	} 
	else if(AQ2200_136 == lType)
	{
		m_pTLS =  new CAQ2200_136();
	}
	else if(HP8168E == lType)
	{
		m_pTLS =  new CHP8168ETLS();
	}
	else 
	{
		throw ERROR_COMMUNICATION_INFO;	
	}

	dwErrorCode = m_pTLS->OpenDevice(pszDeviceAddr, ComHandle);

	return dwErrorCode;
}

DWORD CTLSDll::SetHandle(stDevType stType, LPCTSTR pszDeviceAddr,unsigned long ComHandle)
{
	long lType = stType.bType;
	DWORD dwErrorCode = SUCCESS;

	if (m_pTLS !=NULL)
	{
		delete m_pTLS;
		m_pTLS =NULL;
	}

	if (HP_816X == lType) 
	{
		m_pTLS = new COp816XCtrl();
	}
	else if (OPLK_TLS == lType)
	{
		m_pTLS = new CiTLALaser();
	}
	else if(AGLIENT81960A ==lType)
	{
	   m_pTLS = new COp81960A();
	}
	else if(SANTEC_TLS == lType)
	{
		m_pTLS =  new CSantecTLS();
	}
	else if(AQ2200_136 == lType)
	{
		m_pTLS =  new CAQ2200_136();
	}
	else if(HP8168E == lType)
	{
		m_pTLS =  new CHP8168ETLS();
	}
	else 
	{
		throw ERROR_COMMUNICATION_INFO;	
	}

	dwErrorCode = ((CTLSControl *)m_pTLS)->SetHandle(pszDeviceAddr, ComHandle);

	return dwErrorCode;
}

DWORD CTLSDll::SetWavelength(long lChIndex, double dblWL)
{
	DWORD dwErrorCode = SUCCESS;
    if (m_pTLS!=NULL)
    {
		dwErrorCode = ((CTLSControl *)m_pTLS)->SetWavelength(lChIndex, dblWL);
    }
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;		
	}

	return dwErrorCode;
}

DWORD CTLSDll::SetSourcePower(long lChIndex, double dblPW)
{
	DWORD dwErrorCode = SUCCESS;
    if (m_pTLS!=NULL)
    {
		dwErrorCode = ((CTLSControl *)m_pTLS)->SetSourcePower(lChIndex, dblPW);
    }
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;		
	}
	
	return dwErrorCode;
}

DWORD CTLSDll::SetCoherenceControl(BOOL bEnable)
{
	DWORD dwErrorCode = SUCCESS;
    if (m_pTLS!=NULL)
    {
		dwErrorCode = ((CTLSControl *)m_pTLS)->SetCoherenceControl(bEnable);
    }
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;		
	}
	
	return dwErrorCode;
}

DWORD CTLSDll::SetSourceUnit(long lChIndex, long lUnit)
{
	DWORD dwErrorCode = SUCCESS;
    if (m_pTLS!=NULL)
    {
		dwErrorCode = ((CTLSControl *)m_pTLS)->SetSourceUnit(lChIndex, lUnit);
    }
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;		
	}
	
	return dwErrorCode;
}

DWORD CTLSDll::SetParameters(long lChIndex,BOOL bLowSSE, double dblPower, double dblWavelength)
{
	DWORD dwErrorCode = SUCCESS;
    if (m_pTLS!=NULL)
    {
		dwErrorCode = ((CTLSControl *)m_pTLS)->SetParameters(lChIndex, bLowSSE,dblPower, dblWavelength);
    }
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;		
	}
	
	return dwErrorCode;
}

DWORD CTLSDll::SetOutputEnable(BOOL bEnable)
{
	DWORD dwErrorCode = SUCCESS;
    if (m_pTLS!=NULL)
    {
		dwErrorCode = ((CTLSControl *)m_pTLS)->SetOutputEnable(bEnable);
    }
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;		
	}
	
	return dwErrorCode;
}

DWORD CTLSDll::CloseDevice()
{
	DWORD dwErrorCode = SUCCESS;
    if (m_pTLS!=NULL)
    {
		dwErrorCode = ((CTLSControl *)m_pTLS)->CloseDevice();
    }
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;		
	}
	
	return dwErrorCode;
}

DWORD CTLSDll::PrepareScan(long lChIndex,stScanParam* lScanParam)
{
	DWORD dwErrorCode = SUCCESS;	
	if (m_pTLS!=NULL)
    {
		dwErrorCode = ((CTLSControl *)m_pTLS)->PrepareScan(lChIndex,lScanParam);
    }
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;		
	}
	
	return dwErrorCode;	
}
DWORD CTLSDll::SetScanStart(long lChIndex)
{
	DWORD dwErrorCode = SUCCESS;	
	if (m_pTLS!=NULL)
    {
		dwErrorCode = ((CTLSControl *)m_pTLS)->SetScanStart(lChIndex);
    }
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;		
	}
	
	return dwErrorCode;		
}
DWORD CTLSDll::SetScanStop(long lChIndex)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pTLS!=NULL)
    {
		dwErrorCode = ((CTLSControl *)m_pTLS)->SetScanStop(lChIndex);
    }
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;		
	}
	
	return dwErrorCode;		
}
DWORD CTLSDll::GetLamdaScanWLResult(long lChIndex,double* pdbWLAarry)
{
	DWORD dwErrorCode = SUCCESS;	
	if (m_pTLS!=NULL)
    {
		dwErrorCode = ((CTLSControl *)m_pTLS)->GetLamdaScanWLResult(lChIndex,pdbWLAarry);
    }
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;		
	}
	
	return dwErrorCode;	
}
DWORD CTLSDll::SetMaxOutput(long lChIndex)
{
	DWORD dwErrorCode = SUCCESS;	
	if (m_pTLS!=NULL)
    {
		dwErrorCode = ((CTLSControl *)m_pTLS)->SetMaxOutput(lChIndex);
    }
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;		
	}

	return dwErrorCode;	
}
DWORD CTLSDll::SetTLSFrequency(long lChIndex,double dblFrequrency)
{
	DWORD dwErrorCode = SUCCESS;	
	if (m_pTLS!=NULL)
    {
		dwErrorCode = ((CTLSControl *)m_pTLS)->SetTLSFrequency(lChIndex,dblFrequrency);
    }
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;		
	}
	
	return dwErrorCode;	
}

DWORD CTLSDll::SetSlotIndex(long lSlotIndex)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pTLS!=NULL)
    {
		dwErrorCode = ((CTLSControl *)m_pTLS)->SetTLSSlotIndex(lSlotIndex);
    }
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;		
	}
	
	return dwErrorCode;		
}
DWORD CTLSDll::GetTLSSettings(long lChIndex,double* pdblWavelength,double* pdblPower,BYTE* pdCtrlState)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pTLS!=NULL)
    {
		dwErrorCode = ((CTLSControl *)m_pTLS)->GetTLSSettings(lChIndex,pdblWavelength,pdblPower,pdCtrlState);
    }
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;		
	}
	
	return dwErrorCode;	
}