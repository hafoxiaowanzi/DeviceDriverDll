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
SWITCHCONTROLDLL_API int nSwtichControlDll=0;

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

	if (SWITCH_EDFAGENERAL == lPolType)
	{
		//m_pSwitch = new CIT_1X2SW();	
	}
	else if (SWITCH_1X2 == lPolType)
	{
		//m_pSwitch = new CIT_1X8SW();	
	}
	else if (SWITCH_1X8 == lPolType)
	{
		//m_pSwitch = new COMS_1X64SW();	
	}
	else if (SWITCH_1X64 == lPolType)
	{
		//m_pSwitch = new COMS_1X64SW();	
	}
	else if (SWITCH_1X68 == lPolType)
	{
		//m_pSwitch = new COMS_1X64SW();	
	}
	else if (SWITCH_BOLA == lPolType)
	{
		//m_pSwitch = new COMS_1X64SW();	
	}
	else if (SWITCH_DT08 == lPolType)
	{
		//m_pSwitch = new COMS_1X64SW();	
	}
	else if (SWITCH_THREE1X18 == lPolType)
	{
		//m_pSwitch = new COMS_1X64SW();	
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

	if (SWITCH_EDFAGENERAL == lPolType)
	{
		//m_pSwitch = new CIT_1X2SW();	
	}
	else if (SWITCH_1X2 == lPolType)
	{
		//m_pSwitch = new CIT_1X8SW();	
	}
	else if (SWITCH_1X8 == lPolType)
	{
		//m_pSwitch = new COMS_1X64SW();	
	}
	else if (SWITCH_1X64 == lPolType)
	{
		//m_pSwitch = new COMS_1X64SW();	
	}
	else if (SWITCH_1X68 == lPolType)
	{
		//m_pSwitch = new COMS_1X64SW();	
	}
	else if (SWITCH_BOLA == lPolType)
	{
		//m_pSwitch = new COMS_1X64SW();	
	}
	else if (SWITCH_DT08 == lPolType)
	{
		//m_pSwitch = new COMS_1X64SW();	
	}
	else if (SWITCH_THREE1X18 == lPolType)
	{
		//m_pSwitch = new COMS_1X64SW();	
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

DWORD  CSwitchDll::SetSingleSWPos(long lChIndex, BYTE bySWIndex, BYTE byPos)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch != NULL)
	{
		dwErrorCode = m_pSwitch->SetSingleSWPos(bySWIndex,byPos);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}
DWORD  CSwitchDll::GetSingleSWPos(long lChIndex, BYTE bySWIndex, BYTE &byPos)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch != NULL)
	{
		dwErrorCode = m_pSwitch->GetSingleSWPos(bySWIndex, byPos);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}
DWORD  CSwitchDll::SetMultiSWPos(long lChIndex, BYTE *pbyPosArray, BYTE bySWCount)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch != NULL)
	{
		dwErrorCode = m_pSwitch->SetMultiSWPos(pbyPosArray, bySWCount);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
DWORD  CSwitchDll::GetMultiSWPos(long lChIndex, BYTE *pbyPosArray, BYTE bySWCount)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch != NULL)
	{
		dwErrorCode = m_pSwitch->GetMultiSWPos(pbyPosArray, bySWCount);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
DWORD  CSwitchDll::SetInputVOAAtten(long lChIndex, double dblAtten)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch != NULL)
	{
		dwErrorCode = m_pSwitch->SetInputVOAAtten(dblAtten);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
DWORD  CSwitchDll::GetInputVOAAtten(long lChIndex, double *pdblAtten)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch != NULL)
	{
		dwErrorCode = m_pSwitch->GetInputVOAAtten(pdblAtten);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}

DWORD CSwitchDll::SetMSAVOAAtten(long lChIndex, double dblAtten)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch != NULL)
	{
		dwErrorCode = m_pSwitch->SetMSAVOAAtten(dblAtten);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
DWORD CSwitchDll::GetMSAVOAAtten(long lChIndex, double *pdblAtten)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch != NULL)
	{
		dwErrorCode = m_pSwitch->GetMSAVOAAtten(pdblAtten);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
DWORD CSwitchDll::SetLDSSelection(long lChIndex, BYTE bySrcIndex)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch != NULL)
	{
		dwErrorCode = m_pSwitch->SetLDSSelection(bySrcIndex);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
DWORD CSwitchDll::SetLDSToDutIn(long lChIndex, BYTE byDutInIndex)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch != NULL)
	{
		dwErrorCode = m_pSwitch->SetLDSToDutIn(byDutInIndex);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
DWORD CSwitchDll::SetLDSToDutOut(long lChIndex, BYTE byDutOutIndex)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch != NULL)
	{
		dwErrorCode = m_pSwitch->SetLDSToDutOut(byDutOutIndex);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
DWORD CSwitchDll::SetLDSToMonPath(long lChIndex, BYTE byDestPos)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch != NULL)
	{
		dwErrorCode = m_pSwitch->SetLDSToMonPath(byDestPos);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
DWORD CSwitchDll::SetLDSToRefPath(long lChIndex, BYTE byDestPos)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch != NULL)
	{
		dwErrorCode = m_pSwitch->SetLDSToRefPath(byDestPos);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
DWORD CSwitchDll::SetDutOutToDest(long lChIndex, BYTE byDutOutIndex, BYTE byDestPos)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch != NULL)
	{
		dwErrorCode = m_pSwitch->SetDutOutToDest(byDutOutIndex, byDestPos);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
DWORD CSwitchDll::SetDutInAsOutput(long lChIndex, BYTE byDutInIndex, BYTE byDestPos)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch != NULL)
	{
		dwErrorCode = m_pSwitch->SetDutInAsOutput(byDutInIndex, byDestPos);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
DWORD CSwitchDll::SetDutOut98ToEO1(long lChIndex, BYTE byDutOutIndex, BYTE byDestPos)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch != NULL)
	{
		dwErrorCode = m_pSwitch->SetDutOut98ToEO1(byDutOutIndex, byDestPos);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
DWORD CSwitchDll::SetDutIn98AsOutputToEO1(long lChIndex, BYTE byDutInIndex, BYTE byDestPos)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch != NULL)
	{
		dwErrorCode = m_pSwitch->SetDutIn98AsOutputToEO1(byDutInIndex, byDestPos);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
DWORD CSwitchDll::SetMSAInToMSAOut(long lChIndex, BYTE byMsaInPort, BYTE byMsaOutPort, double dblMsaVOAAtten)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch != NULL)
	{
		dwErrorCode = m_pSwitch->SetMSAInToMSAOut(byMsaInPort, byMsaOutPort, dblMsaVOAAtten);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
DWORD CSwitchDll::SetMSATapToDest(long lChIndex, BYTE byMsaOutPort, BYTE byDestPos)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch != NULL)
	{
		dwErrorCode = m_pSwitch->SetMSATapToDest(byMsaOutPort, byDestPos);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
DWORD CSwitchDll::SetMSAInAsOutput(long lChIndex, BYTE byMsaInPort, BYTE byDestPos)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch != NULL)
	{
		dwErrorCode = m_pSwitch->SetMSAInAsOutput(byMsaInPort, byDestPos);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
DWORD CSwitchDll::SetMSAOutAsOutput(long lChIndex, BYTE byMsaOutPort, BYTE byDestPos)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch != NULL)
	{
		dwErrorCode = m_pSwitch->SetMSAOutAsOutput(byMsaOutPort, byDestPos);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
DWORD CSwitchDll::SetMSAOut98AsOutputToEO2(long lChIndex, BYTE byMsaOutPort, BYTE byDestPos)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch != NULL)
	{
		dwErrorCode = m_pSwitch->SetMSAOut98AsOutputToEO2(byMsaOutPort, byDestPos);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
DWORD CSwitchDll::SetEOPortToDest(long lChIndex, BYTE byEOPort, BYTE byDestPos)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch != NULL)
	{
		dwErrorCode = m_pSwitch->SetEOPortToDest(byEOPort, byDestPos);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
DWORD CSwitchDll::SetVOATriggerOut(long lChIndex, double dblStartAtten, double dblEndAtten, double dblStepAtten, WORD wOPMWaitTimeMs)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch != NULL)
	{
		dwErrorCode = m_pSwitch->SetVOATriggerOut(dblStartAtten, dblEndAtten, dblStepAtten, wOPMWaitTimeMs);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
DWORD CSwitchDll::SetSWPathMapping(long lChIndex, char *pchBinfileName)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch != NULL)
	{
		dwErrorCode = m_pSwitch->SetSWPathMapping(pchBinfileName);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
DWORD CSwitchDll::SetSWTriggerPathScanStart(long lChIndex, WORD wExitTimeOutSecond)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch != NULL)
	{
		dwErrorCode = m_pSwitch->SetSWTriggerPathScanStart(wExitTimeOutSecond);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
DWORD CSwitchDll::SetGPIOConfig(long lChIndex, DWORD dwCtrlPinBits, DWORD dwAlarmPinBits)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch != NULL)
	{
		//dwErrorCode = m_pSwitch->SetGPIOConfig(dwCtrlPinBits, dwAlarmPinBits);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
DWORD CSwitchDll::GetGPIOStatus(long lChIndex, WORD *pdwCtrlPinBits, WORD *pdwAlarmPinBits)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch != NULL)
	{
		dwErrorCode = m_pSwitch->GetGPIOStatus(pdwCtrlPinBits, pdwAlarmPinBits);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
DWORD CSwitchDll::SetUARTConfig(long lChIndex, BYTE byUARTIndex, stSerialPortCfg stSerialPortCfgValue, DWORD dwTimeOut)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch != NULL)
	{
		dwErrorCode = m_pSwitch->SetUARTConfig(byUARTIndex, stSerialPortCfgValue, dwTimeOut);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
DWORD CSwitchDll::WriteUARTData(long lChIndex, BYTE byUARTIndex, BYTE* pbyBuffer, WORD wLength)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch != NULL)
	{
		dwErrorCode = m_pSwitch->WriteUARTData(byUARTIndex, pbyBuffer, wLength);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
DWORD CSwitchDll::ReadUARTData(long lChIndex, BYTE byUARTIndex, BYTE* pbyBuffer, WORD wLength, WORD *pwGetLength)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch != NULL)
	{
		dwErrorCode = m_pSwitch->ReadUARTData(byUARTIndex, pbyBuffer, wLength, pwGetLength);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
DWORD CSwitchDll::GetDeviceInfo(long lChIndex, pstDevInfo pstSWInfo)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch != NULL)
	{
		dwErrorCode = m_pSwitch->GetDeviceInfo(pstSWInfo);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
DWORD CSwitchDll::GetSwitchingCnt(long lChIndex, BYTE bySWIndex, DWORD *pdwSwitchingCnt)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch != NULL)
	{
		dwErrorCode = m_pSwitch->GetSwitchingCnt(bySWIndex, pdwSwitchingCnt);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
DWORD CSwitchDll::GetInputMinIL(long lChIndex, BYTE bySWIndex, double * pdblGetMinIL)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch != NULL)
	{
		dwErrorCode = m_pSwitch->GetInputMinIL(bySWIndex, pdblGetMinIL);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
DWORD CSwitchDll::SetBlockBySwitch(long lChIndex, BYTE bySrcIndex)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch != NULL)
	{
		dwErrorCode = m_pSwitch->SetBlockBySwitch(bySrcIndex);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
DWORD CSwitchDll::SetGPIOStatus(long lChIndex, WORD wAlarmIN, WORD wAlarmOut)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch != NULL)
	{
		dwErrorCode = m_pSwitch->SetGPIOStatus(wAlarmIN, wAlarmOut);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
DWORD CSwitchDll::GetGPIOStatus(long lChIndex, WORD *pwAlarmIN, WORD *pwAlarmOut)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch != NULL)
	{
		dwErrorCode = m_pSwitch->GetGPIOStatus(pwAlarmIN, pwAlarmOut);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
DWORD CSwitchDll::SetGPIOVoltage(long lChIndex, bool bVoltage5V)
{
	DWORD dwErrorCode = SUCCESS;
	if (m_pSwitch != NULL)
	{
		dwErrorCode = m_pSwitch->SetGPIOVoltage(bVoltage5V);
	}
	else
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}