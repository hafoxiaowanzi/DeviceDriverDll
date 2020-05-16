// IPMInterface.cpp : Implementation of CIPMInterface
#include "stdafx.h"
#include "UDLServer.h"
#include "IPMInterface.h"
#include "DeviceManger.h"

/////////////////////////////////////////////////////////////////////////////
// CIPMInterface
extern CDeviceManger _DeviceManager;

STDMETHODIMP CIPMInterface::GetUnit(long lChan, long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	long lGetUint;

    if(!_DeviceManager.GetPMUnit(lChan,&lGetUint))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
	*pVal = lGetUint;

	return S_OK;
}

STDMETHODIMP CIPMInterface::SetUnit(long lChan, long newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	long lGetUint;
	lGetUint = newVal;

    if(!_DeviceManager.SetPMUnit(lChan,lGetUint))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
	return S_OK;
}

STDMETHODIMP CIPMInterface::GetAverageTime(long lChan, double *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	double dbSetAvgTime;

    if(!_DeviceManager.GetPMAverageTime(lChan,&dbSetAvgTime))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
	*pVal = dbSetAvgTime;
	return S_OK;
}

STDMETHODIMP CIPMInterface::SetAverageTime(long lChan, double newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

    if(!_DeviceManager.SetPMAverageTime(lChan,newVal))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
	return S_OK;
}

STDMETHODIMP CIPMInterface::GetWavelength(long lChan, double *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	double dbSetWL;

    if(!_DeviceManager.GetPMWavelength(lChan,&dbSetWL))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
	*pVal = dbSetWL;
	return S_OK;
}

STDMETHODIMP CIPMInterface::SetWavelength(long lChan, double newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
    if(!_DeviceManager.SetPMWavelength(lChan,newVal))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
	return S_OK;
}

STDMETHODIMP CIPMInterface::GetPower(long lChan, double *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	double dbPower;

    if(!_DeviceManager.ReadPower(lChan,&dbPower))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
	*pVal = dbPower;
	return S_OK;
}

//DEL STDMETHODIMP CIPMInterface::put_Power(long lChan, double newVal)
//DEL {
//DEL 	AFX_MANAGE_STATE(AfxGetStaticModuleState())
//DEL 
//DEL 	// TODO: Add your implementation code here
//DEL 
//DEL 	return S_OK;
//DEL }

STDMETHODIMP CIPMInterface::GetRangeMode(long lChan, long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
    long lModel;
	if(!_DeviceManager.GetPMRangeMode(lChan,&lModel))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
	*pVal = lModel;

	return S_OK;
}

STDMETHODIMP CIPMInterface::SetRangeMode(long lChan, long newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if(!_DeviceManager.SetPMRangeMode(lChan,newVal))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
	return S_OK;
}

STDMETHODIMP CIPMInterface::SetParameters(long lChan, BOOL bAutoRange, double dblWL, double dblAvgTime, double dblPMRange)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if(!_DeviceManager.SetPMParameters(lChan,bAutoRange,dblWL,dblAvgTime,dblPMRange))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
	return S_OK;
}

STDMETHODIMP CIPMInterface::SetZero(long lChan)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if(!_DeviceManager.SetPMZero(lChan))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
	return S_OK;
}

STDMETHODIMP CIPMInterface::get_LastMessage(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
    *pVal = m_strMessage;
	return S_OK;
}

STDMETHODIMP CIPMInterface::CloseDevice(long lChan)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if(!_DeviceManager.ClosePMDevice(lChan))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
	return S_OK;
}

//DEL STDMETHODIMP CIPMInterface::GetPMDeviceInfo(long lChIndex, BSTR *pstrDescription)
//DEL {
//DEL 	AFX_MANAGE_STATE(AfxGetStaticModuleState())
//DEL 
//DEL 	// TODO: Add your implementation code here
//DEL 
//DEL 	return S_OK;
//DEL }

STDMETHODIMP CIPMInterface::SetPMMaxMinPowerStart(long lChan)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if(!_DeviceManager.SetPMMaxMinPowerStart(lChan))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
	return S_OK;
}

STDMETHODIMP CIPMInterface::GetPMMaxMinPower(long lChIndex, double *pdbGetMax, double *pdbGetMin)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if(!_DeviceManager.GetPMMaxMinPower(lChIndex,pdbGetMax,pdbGetMin))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
	return S_OK;
}

STDMETHODIMP CIPMInterface::SetPMMaxMinPowerStop(long lChan)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if(!_DeviceManager.SetPMMaxMinPowerStop(lChan))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
	return S_OK;
}

STDMETHODIMP CIPMInterface::SetPMPowerOffset(long lChan, double newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if(!_DeviceManager.SetPMPowerOffset(lChan,newVal))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
	return S_OK;
}
