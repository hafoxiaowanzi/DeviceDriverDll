// VOAControlDll.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "..\\include\\VOAControlDll.h"

//#include "VOAControl.h"
//#include "OplkMEMSVOA.h"
//#include "Hp8156A.h"	
////


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
VOACONTROLDLL_API int nVOAControlDll=0;

// This is an example of an exported function.
VOACONTROLDLL_API int fnVOAControlDll(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see VOAControlDll.h for the class definition
CVOADll::CVOADll():m_pVOA(NULL)
{ 
  m_pVOA =NULL;
}

CVOADll::~CVOADll()
{ 
   if (m_pVOA!=NULL)
   {
	   delete m_pVOA;
	   m_pVOA =NULL;
   }

	return;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DWORD CVOADll::OpenDevice(stDevType stType, char* pszDeviceAddr, unsigned long *comHandle)
{
	DWORD dwErrorCode = SUCCESS;

	try
	{	
		
		if (m_pVOA !=NULL)
		{
			delete m_pVOA;
			m_pVOA = NULL;
		}
		if (HP_8156A == stType.bType)
		{
			m_pVOA = new CVOA_HP8156X() ;
		}
		else if (OPLK_VOA == stType.bType)
		{
			m_pVOA = new COplkMEMSVOA();
		}
		else if(A8164_VOA == stType.bType )
		{
			m_pVOA = new CVOA_Aglient8164();
		}
		else if(OPLINKR153CHAKA == stType.bType)
		{
			m_pVOA = new COplkR153VOA();
		}
		else if(OPLINKDULVOA == stType.bType)
		{
			m_pVOA = new COplkDulVOA();
		}
		else if(AQ2200_311A ==stType.bType)
		{
			m_pVOA = new CAQ2200_311A();
		}
		else if(AQ3150 ==stType.bType)
		{
			m_pVOA = new CAQ3150();
		}
		else if(SANTECTLSVOA ==stType.bType)
		{
			m_pVOA = new CSantectTLSVOA();
		}
		else
		{
			throw ERROR_COMMUNICATION_INFO;
		}

		dwErrorCode = ((CVOAControl *)m_pVOA)->OpenDevice(pszDeviceAddr, comHandle);
		if (SUCCESS != dwErrorCode) 
		{
	    	throw dwErrorCode;
		}
	}
	catch (DWORD dwError) 
	{
		dwErrorCode = ERROR_VOA | dwError;
	}
	catch (...)
	{
		return ERROR_VOA|UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD CVOADll::SetHandle(stDevType stType, char* pszDeviceAddr, unsigned long comHandle)
{
	DWORD dwErrorCode = SUCCESS;

	try
	{
		if (m_pVOA !=NULL)
		{
			delete m_pVOA;
			m_pVOA = NULL;
		}
		if (HP_8156A == stType.bType)
		{
			m_pVOA = new CVOA_HP8156X() ;
		}
		else if (OPLK_VOA == stType.bType)
		{
			m_pVOA = new COplkMEMSVOA();
		}
		else if(A8164_VOA == stType.bType )
		{
			m_pVOA = new CVOA_Aglient8164();
		}
		else if(OPLINKR153CHAKA == stType.bType)
		{
			m_pVOA = new COplkR153VOA();
		}
		else if(AQ2200_311A ==stType.bType)
		{
			m_pVOA = new CAQ2200_311A();
		}
		else if(SANTECTLSVOA ==stType.bType)
		{
			m_pVOA = new CSantectTLSVOA();
		}
		else
		{
			throw ERROR_COMMUNICATION_INFO;
		}
		
		dwErrorCode = ((CVOAControl *)m_pVOA)->SetHandle(pszDeviceAddr, comHandle);
		if (SUCCESS != dwErrorCode) 
		{
	    	throw ERROR_VOA|dwErrorCode;
		}

	}
	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return ERROR_VOA|UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD CVOADll::CloseDevice()
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pVOA!=NULL)
	{
		dwErrorCode = ((CVOAControl *)m_pVOA)->CloseDevice();
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	

	return dwErrorCode;
}

DWORD CVOADll::ResetDevice(void)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pVOA!=NULL)
	{
		dwErrorCode = ((CVOAControl *)m_pVOA)->ResetDevice();
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	
	return dwErrorCode;
}

DWORD CVOADll::GetDeviceInfo(stDevInfo *stInfo)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pVOA!=NULL)
	{
		dwErrorCode = ((CVOAControl *)m_pVOA)->GetDeviceInfo(stInfo);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}

DWORD CVOADll::SetWavelength(long lChIndex, double dblWL)
{
	DWORD dwErrorCode = SUCCESS;

	try
	{
		if (m_pVOA!=NULL)
		{
			dwErrorCode = ((CVOAControl *)m_pVOA)->SetWavelength(lChIndex, dblWL);
		}
		else
		{
			dwErrorCode = UNEXPECT_OCCUR;
		}
		
		if (SUCCESS != dwErrorCode) 
		{
	    	throw ERROR_VOA|dwErrorCode;
		}
	}
	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return ERROR_VOA|UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD CVOADll::GetWavelength(long lChIndex, double *dblWL)
{
   	DWORD dwErrorCode = SUCCESS;

	try
	{
		if (m_pVOA!=NULL)
		{
			dwErrorCode = ((CVOAControl *)m_pVOA)->GetWavelength(lChIndex, dblWL);
		}
		else
		{
			dwErrorCode = UNEXPECT_OCCUR;
		}
		
		if (SUCCESS != dwErrorCode) 
		{
	    	throw ERROR_VOA|dwErrorCode;
		}

	}
	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return ERROR_VOA|UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD CVOADll::SetAttenuation(long lChIndex, double dblAtten)
{
  	DWORD dwErrorCode = SUCCESS;

	try
	{
		if (m_pVOA!=NULL)
		{
			dwErrorCode = ((CVOAControl *)m_pVOA)->SetAttenuation(lChIndex,dblAtten);
		}
		else
		{
			dwErrorCode = UNEXPECT_OCCUR;
		}
	
		if (SUCCESS != dwErrorCode) 
		{
	    	throw ERROR_VOA|dwErrorCode;
		}

	}
	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return ERROR_VOA|UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD CVOADll::GetAttenuation(long lChIndex, double *dblAtten)
{ 
   	DWORD dwErrorCode = SUCCESS;

	try
	{
		if (m_pVOA!=NULL)
		{
			dwErrorCode = ((CVOAControl *)m_pVOA)->GetAttenuation(lChIndex,dblAtten);
		}
		else
		{
			dwErrorCode = UNEXPECT_OCCUR;
		}
		
		if (SUCCESS != dwErrorCode) 
		{
			throw ERROR_VOA|dwErrorCode;
		}

	}
	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return ERROR_VOA|UNEXPECT_OCCUR;
	}

	return dwErrorCode;

}

DWORD CVOADll::SetEnableOutput(long lChIndex, BOOL bEnable)
{
  	DWORD dwErrorCode = SUCCESS;

	try
	{
		if (m_pVOA!=NULL)
		{
			dwErrorCode = ((CVOAControl *)m_pVOA)->SetEnableOutput(lChIndex,bEnable);
		}
		else
		{
			dwErrorCode = UNEXPECT_OCCUR;
		}
		
		if (SUCCESS != dwErrorCode) 
		{
	    	throw ERROR_VOA|dwErrorCode;
		}

	}
	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return ERROR_VOA|UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD CVOADll::SetInputOffset(long lChIndex, double dblOffset)
{
  	DWORD dwErrorCode = SUCCESS;

	try
	{
		if (m_pVOA!=NULL)
		{
			dwErrorCode = ((CVOAControl *)m_pVOA)->SetInputOffset(lChIndex,dblOffset);
		}
		else
		{
			dwErrorCode = UNEXPECT_OCCUR;
		}
		
		if (SUCCESS != dwErrorCode) 
		{
	    	throw ERROR_VOA|dwErrorCode;
		}

	}
	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return ERROR_VOA|UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD CVOADll::GetStatus(DWORD *dwStatus)
{
	DWORD dwErrorCode = SUCCESS;

	try
	{
		if (m_pVOA!=NULL)
		{
			dwErrorCode = ((CVOAControl *)m_pVOA)->GetStatus(dwStatus);
		}
		else
		{
			dwErrorCode = UNEXPECT_OCCUR;
		}
	
		if (SUCCESS != dwErrorCode) 
		{
	    	throw ERROR_VOA|dwErrorCode;
		}

	}
	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return ERROR_VOA|UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

BOOL CVOADll::GetErrorMessage(DWORD dwErrorCode, char *pszErrorMsg)
{
	return TRUE;

}

