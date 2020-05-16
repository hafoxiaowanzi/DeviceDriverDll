// PMControlDll.cpp : Defines the entry polong for the DLL application.
//

#include "stdafx.h"
#include "..\\include\\PMControlDll.h"


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
PMCONTROLDLL_API int nPMControlDll=0;

// This is an example of an exported function.
PMCONTROLDLL_API int fnPMControlDll(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see PMControlDll.h for the class definition
CPMDll::CPMDll()
{ 
    m_pPm = NULL;
	return; 
}

CPMDll::~CPMDll()
{ 
	if (m_pPm!=NULL)
	{
		delete m_pPm;
		m_pPm = NULL;
	}
	return; 
}

DWORD CPMDll::OpenDevice(stDevType stType, LPCTSTR pszDeviceAddr, unsigned long *Comhandle)
{
	long lPMType=stType.bType;
	DWORD dwErrorCode = SUCCESS;
	if (m_pPm !=NULL)
	{
		delete m_pPm;
		m_pPm =NULL;
	}

	if (HP_8163A == lPMType) 
	{
		m_pPm = new COp8163A();	
	}
	else if (OPLK_PM == lPMType)
	{
		m_pPm = new OplinkPM();
	}
	else if(PM_I830C == lPMType)
	{
		m_pPm = new CPM1830C() ;
	}
	else if(PM_N7745 == lPMType)
	{
		m_pPm = new CN7745PM();
	}
	else if(PM_JH == lPMType)
	{
		m_pPm = new CPMJH();
	}
	else if(PM_OPLINKI1830C == lPMType)
	{
		m_pPm = new COplink1830C();
	}
	else if(HP_8153A == lPMType)
	{
		m_pPm = new COp8153A();
	}
	else if(AQ2200_215 == lPMType)
	{
		m_pPm = new CAQ2200_215();
	}
	else if(AQ2140 == lPMType)
	{
		m_pPm = new CAQ2140();
	}
	else  
	{
		return ERROR_COMMUNICATION_INFO;	
	}

	//m_pPm = m_pvoid+lPMType;
	dwErrorCode = m_pPm->OpenDevice(pszDeviceAddr, Comhandle);

	return dwErrorCode;
}

DWORD CPMDll::SetHandle(stDevType stType, LPCTSTR pszDeviceAddr, unsigned long handle)
{
	long lPMType=stType.bType;
	DWORD dwErrorCode = SUCCESS;

	
	if (HP_8163A == lPMType) 
	{
		m_pPm = new COp8163A();	
	}
	else if (OPLK_PM == lPMType)
	{	
		if(m_pPm==NULL)
		{
		    m_pPm = new OplinkPM();
		}
	}
	else if(PM_I830C == lPMType)
	{
		m_pPm = new CPM1830C() ;
	}
	else if(PM_N7745 == lPMType)
	{
		m_pPm = new CN7745PM();
	}
	else if(PM_JH == lPMType)
	{
		m_pPm = new CPMJH();
	}
	else if(PM_OPLINKI1830C == lPMType)
	{
		m_pPm = new COplink1830C();
	}
	else if(HP_8153A == lPMType)
	{
		m_pPm = new COp8153A();
	}
	else if(AQ2200_215 == lPMType)
	{
		m_pPm = new CAQ2200_215();
	}
	else if(AQ2140 == lPMType)
	{
		m_pPm = new CAQ2140();
	}
	else 
	{
		throw ERROR_COMMUNICATION_INFO;	
	}
	

	dwErrorCode =m_pPm->SetHandle(pszDeviceAddr, handle);
	if (dwErrorCode != SUCCESS) 
	{
		
	}

	return dwErrorCode;
}

DWORD CPMDll::ReadPower(long lslot,long iChan, double* pdbPowerValue)
{
	//iSlot从1开始，iChannel从1开始
	DWORD dwCode = SUCCESS;
    if (m_pPm!=NULL)
    {
		dwCode =m_pPm->GetPower(lslot,iChan, pdbPowerValue);
    }
	else
	{
        dwCode = UNEXPECT_OCCUR;
	}

	return dwCode;
}

DWORD CPMDll::GetWavelength(long lslot,long iChan, double* pdblWL)
{
	//iSlot从1开始，iChannel从0开始

	DWORD dwCode = SUCCESS;
    if (m_pPm!=NULL)
    {
		dwCode =m_pPm->GetWavelength(lslot, iChan,pdblWL);
    }
	else
	{
        dwCode = UNEXPECT_OCCUR;
	}
	
	return dwCode;
}

DWORD CPMDll::GetAverageTime(long lslot,long iChan, double* pdblAverageTime)
{
	//iSlot从1开始，iChannel从0开始
	DWORD dwCode = SUCCESS;
    if (m_pPm!=NULL)
    {
		dwCode =m_pPm->GetAverageTime(lslot,iChan, pdblAverageTime);
    }
	else
	{
        dwCode = UNEXPECT_OCCUR;
	}
	
	return dwCode;
}


DWORD CPMDll::GetRangeMode(long lslot,long iChan,  long* iPWMRangeMode)
{
	//iSlot从1开始，iChannel从0开始
	DWORD dwCode = SUCCESS;
    if (m_pPm!=NULL)
    {
		dwCode =m_pPm->GetRangeMode(lslot,iChan, iPWMRangeMode);
    }
	else
	{
        dwCode = UNEXPECT_OCCUR;
	}
	
	return dwCode;
}
DWORD CPMDll::GetUnit(long lslot,long iChan, long* piUnit)
{
	//iSlot从1开始，iChannel从0开始
	DWORD dwCode = SUCCESS;
    if (m_pPm!=NULL)
    {
		dwCode =m_pPm->GetUnit(lslot,iChan, piUnit);
    }
	else
	{
        dwCode = UNEXPECT_OCCUR;
	}
	
	return dwCode;
}

DWORD CPMDll::SetUnit(long lslot,long iChan, long iPWUnit)
{

	DWORD dwCode = SUCCESS;
    if (m_pPm!=NULL)
    {
		dwCode =m_pPm->SetUnit(lslot,iChan,iPWUnit);
    }
	else
	{
        dwCode = UNEXPECT_OCCUR;
	}
	
	return dwCode;
}

DWORD CPMDll::SetWavelength(long lslot,long iChan, double dblWL)
{

	DWORD dwCode = SUCCESS;
    if (m_pPm!=NULL)
    {
		dwCode =m_pPm->SetWavelength(lslot,iChan, dblWL);
    }
	else
	{
        dwCode = UNEXPECT_OCCUR;
	}


	return dwCode;
}

DWORD CPMDll::SetAverageTime(long lslot,long iChan,double dblPWAverageTime)
{
	DWORD dwCode = SUCCESS;
    if (m_pPm!=NULL)
    {
		dwCode =m_pPm->SetAverageTime(lslot,iChan, dblPWAverageTime);
    }
	else
	{
        dwCode = UNEXPECT_OCCUR;
	}

	return dwCode;
}

DWORD CPMDll::SetRangeMode(long lslot,long iChan, long iPWRangeMode)
{

	DWORD dwCode = SUCCESS;
    if (m_pPm!=NULL)
    {
		dwCode =m_pPm->SetRangeMode(lslot,iChan, iPWRangeMode);
    }
	else
	{
        dwCode = UNEXPECT_OCCUR;
	}
	

	return dwCode;
}
DWORD CPMDll::SetRange(long lSlot,long IChan, long lRange)
{
	DWORD dwCode = SUCCESS;
    if (m_pPm!=NULL)
    {
		dwCode =m_pPm->SetRange(lSlot,IChan, lRange);
    }
	else
	{
        dwCode = UNEXPECT_OCCUR;
	}
	

	return dwCode;
}

DWORD CPMDll::SetParameters(long lslot,long iChan, BOOL bAutoRang, double dblWL, double dblAverageTime, double dblPwrRange)
{
	DWORD dwCode = SUCCESS;
    if (m_pPm!=NULL)
    {
		dwCode =m_pPm->SetParameters(lslot,iChan, bAutoRang, dblWL, dblAverageTime, dblPwrRange);
    }
	else
	{
        dwCode = UNEXPECT_OCCUR;
	}
	

	return dwCode;
}

DWORD CPMDll::SetZero(long lslot,long iChan)
{

	DWORD dwCode = SUCCESS;
    if (m_pPm!=NULL)
    {
		dwCode =m_pPm->Zero(lslot,iChan);
    }
	else
	{
        dwCode = UNEXPECT_OCCUR;
	}
	
	return dwCode;
}

DWORD CPMDll::CloseDevice()
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pPm!=NULL)
    {
		dwErrorCode =m_pPm->CloseDevice();
    }
	else
	{
        dwErrorCode = UNEXPECT_OCCUR;
	}
	
	return dwErrorCode;
}

DWORD CPMDll::GetDeviceInfo(CHAR *pchInfo)
{
	DWORD dwCode = SUCCESS;
	if (m_pPm!=NULL)
    {
		dwCode =m_pPm->GetDeviceInfo(pchInfo);
    }
	else
	{
        dwCode = UNEXPECT_OCCUR;
	}

	
	return dwCode;
}
DWORD CPMDll::PrepareScan(long lSlot,long lChIndex,stScanParam* lScanParam)
{
	DWORD dwCode = SUCCESS;
	if (m_pPm!=NULL)
    {
		dwCode =m_pPm->PrepareScan(lSlot,lChIndex,lScanParam);
    }
	else
	{
        dwCode = UNEXPECT_OCCUR;
	}

	
	return dwCode;
}
DWORD CPMDll::SetPMScanStart(long lSlot,long lChIndex)
{
	DWORD dwCode = SUCCESS;
	
	if (m_pPm!=NULL)
    {
		dwCode =m_pPm->SetPMScanStart(lSlot,lChIndex);
    }
	else
	{
        dwCode = UNEXPECT_OCCUR;
	}
	return dwCode;
}
DWORD CPMDll::getLambdaScanPMResult(long lSlot,long lChIndex,double* pdbPMArry)
{
	DWORD dwCode = SUCCESS;
		
	if (m_pPm!=NULL)
    {
		dwCode =m_pPm->getLambdaScanPMResult(lSlot,lChIndex,pdbPMArry);	
    }
	else
	{
        dwCode = UNEXPECT_OCCUR;
	}

	return dwCode;	
}
DWORD CPMDll::SetPMScanStop(long lSlot,long lChIndex)
{
	DWORD dwCode = SUCCESS;
	if (m_pPm!=NULL)
    {
		dwCode =m_pPm->SetPMScanStop(lSlot,lChIndex);
    }
	else
	{
        dwCode = UNEXPECT_OCCUR;
	}
		
	return dwCode;	
}
DWORD CPMDll::SetPMScanTriggerStop(long lSlot,long lChIndex)
{
	DWORD dwCode = SUCCESS;
	if (m_pPm!=NULL)
    {
		dwCode =m_pPm->SetPMScanTriggerStop(lSlot,lChIndex);
    }
	else
	{
        dwCode = UNEXPECT_OCCUR;
	}
	
	return dwCode;		
}
DWORD CPMDll::SetPMMaxMinPowerStart(long lSlot,long lChIndex)
{
	DWORD dwCode = SUCCESS;
	if (m_pPm!=NULL)
    {
		dwCode =m_pPm->SetPMMaxMinPowerStart(lSlot,lChIndex);
    }
	else
	{
        dwCode = UNEXPECT_OCCUR;
	}
	
	return dwCode;		
}
DWORD CPMDll::GetPMMaxMinPower(long lSlot,long lChIndex,double *pdbGetMax,double *pdbGetMin)
{
	DWORD dwCode = SUCCESS;
	if (m_pPm!=NULL)
    {
		dwCode =m_pPm->GetPMMaxMinPower(lSlot,lChIndex,pdbGetMax,pdbGetMin);
    }
	else
	{
        dwCode = UNEXPECT_OCCUR;
	}
	
	return dwCode;		
}
DWORD CPMDll::SetPMMaxMinPowerStop(long lSlot,long lChIndex)
{
	DWORD dwCode = SUCCESS;
	if (m_pPm!=NULL)
    {
		dwCode =m_pPm->SetPMMinMaxStop(lSlot,lChIndex);
    }
	else
	{
        dwCode = UNEXPECT_OCCUR;
	}
	
	return dwCode;		
}
DWORD CPMDll::SetPMPowerOffset(long lSlot,long IChan,double dbPowerOffset)
{
	DWORD dwCode = SUCCESS;
	if (m_pPm!=NULL)
    {
		dwCode =m_pPm->SetPMPowerOffset(lSlot,IChan,dbPowerOffset);
    }
	else
	{
        dwCode = UNEXPECT_OCCUR;
	}
	
	return dwCode;
}