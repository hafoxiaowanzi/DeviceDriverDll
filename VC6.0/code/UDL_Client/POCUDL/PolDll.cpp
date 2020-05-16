// PolDll.cpp: implementation of the CPolDll class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\\include\\PolDll.h"

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
POLCONTROLDLL_API int nPolControlDll=0;

// This is an example of an exported function.
POLCONTROLDLL_API int fnPolControlDll(void)
{
	return 42;
}

CPolDll::CPolDll()
{
	m_pPol = NULL;
}

CPolDll::~CPolDll()
{
	if (m_pPol!=NULL)
	{
		delete m_pPol;
		m_pPol = NULL;
	}
}
DWORD CPolDll::OpenDevice(stDevType stType, LPCTSTR pszDeviceAddr, unsigned long *Comhandle)
{
	long lPolType=stType.bType;
	DWORD dwErrorCode = SUCCESS;

	if (HP_8169 == lPolType) 
	{
		m_pPol = new COp8169();	
	}
	else if (OPLK_POL == lPolType)
	{
		m_pPol = new COpR181();	
	}
	else if (N8876 == lPolType)
	{

	}
	else 
	{
		return ERROR_COMMUNICATION_INFO;	
	}

	dwErrorCode = m_pPol->OpenDevice(pszDeviceAddr, Comhandle);

	return dwErrorCode;
}

DWORD CPolDll::SetHandle(stDevType stType, LPCTSTR pszDeviceAddr, unsigned long handle)
{
	long lPolType=stType.bType;
	DWORD dwErrorCode = SUCCESS;

	if (HP_8169 == lPolType) 
	{
		m_pPol = new COp8169();	
	}
	else if (OPLK_POL == lPolType)
	{
		m_pPol = new COpR181();	
	}
	else if (N8876 == lPolType)
	{

	}
	else 
	{
		return ERROR_COMMUNICATION_INFO;	
	}
	
	dwErrorCode =m_pPol->SetHandle(pszDeviceAddr, handle);

	return dwErrorCode;
}
DWORD  CPolDll::CloseDevice()
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pPol!=NULL)
	{
		dwErrorCode =m_pPol->CloseDevice();
	}
	else
	{
		dwErrorCode =UNEXPECT_OCCUR;
	}


	return dwErrorCode;
}

DWORD  CPolDll::ResetDevice()
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pPol!=NULL)
	{
		dwErrorCode =m_pPol->ResetDevice();
	}
	else
	{
		dwErrorCode =UNEXPECT_OCCUR;
	}
	

	return dwErrorCode;
}
DWORD  CPolDll::GetDeviceInfo(stDevInfo *stInfo)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pPol!=NULL)
	{
		dwErrorCode =m_pPol->GetDeviceInfo(stInfo);
	}
	else
	{
		dwErrorCode =UNEXPECT_OCCUR;
	}
	

	return dwErrorCode;
}
DWORD  CPolDll::GetCurrentPOSPolarizer(double * pdblAlphaP,double *pdblAlphaQ,double *pdblAlphaH)
{
    DWORD dwErrorCode = SUCCESS;
	if (m_pPol!=NULL)
	{
		dwErrorCode =m_pPol->GetCurrentPOSPolarizer(pdblAlphaP,pdblAlphaQ,pdblAlphaH);
	}
	else
	{
		dwErrorCode =UNEXPECT_OCCUR;
	}


	return dwErrorCode;
}
DWORD  CPolDll::SetALL(double alphaP, double alphaQ, double alphaH)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pPol!=NULL)
	{
		dwErrorCode =m_pPol->SetALL(alphaP,alphaQ,alphaH);
	}
	else
	{
		dwErrorCode =UNEXPECT_OCCUR;
	}


	return dwErrorCode;
}
DWORD  CPolDll::SetDiagonalAngles(double AlphaPMax, double Wavelength)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pPol!=NULL)
	{
		dwErrorCode =m_pPol->SetDiagonalAngles(AlphaPMax,Wavelength);
	}
	else
	{
		dwErrorCode =UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}
DWORD  CPolDll::SetHorizontalAngles(double AlphaPMax, double Wavelength)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pPol!=NULL)
	{
		dwErrorCode =m_pPol->SetHorizontalAngles(AlphaPMax,Wavelength);
	}
	else
	{
		dwErrorCode =UNEXPECT_OCCUR;
	}


	return dwErrorCode;
}
DWORD  CPolDll::SetPOSHalf(double alpha)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pPol!=NULL)
	{
		dwErrorCode =m_pPol->SetPOSHalf(alpha);
	}
	else
	{
		dwErrorCode =UNEXPECT_OCCUR;
	}
	

	return dwErrorCode;
}
DWORD  CPolDll::SetPOSPolarizer(double alpha)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pPol!=NULL)
	{
		dwErrorCode =m_pPol->SetPOSPolarizer(alpha);
	}
	else
	{
		dwErrorCode =UNEXPECT_OCCUR;
	}
	

	return dwErrorCode;
}
DWORD  CPolDll::SetPOSQuarter(double alpha)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pPol!=NULL)
	{
		dwErrorCode =m_pPol->SetPOSQuarter(alpha);
	}
	else
	{
		dwErrorCode =UNEXPECT_OCCUR;
	}
	

	return dwErrorCode;
}
DWORD  CPolDll::SetRightHandCircularAngles(double AlphaPMax, double Wavelength)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pPol!=NULL)
	{
		dwErrorCode =m_pPol->SetRightHandCircularAngles(AlphaPMax,Wavelength);
	}
	else
	{
		dwErrorCode =UNEXPECT_OCCUR;
	}
	
	
	return dwErrorCode;
}
DWORD  CPolDll::SetVerticalAngles(double AlphaPMax, double Wavelength)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pPol!=NULL)
	{
		dwErrorCode =m_pPol->SetRightHandCircularAngles(AlphaPMax,Wavelength);
	}
	else
	{
		dwErrorCode =UNEXPECT_OCCUR;
	}


	return dwErrorCode;
}