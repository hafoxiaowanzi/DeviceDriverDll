// ChamberInterface.cpp : Implementation of CChamberInterface
#include "stdafx.h"
#include "UDLServer.h"
#include "ChamberInterface.h"
#include "DeviceManger.h"

/////////////////////////////////////////////////////////////////////////////
// CChamberInterface
extern CDeviceManger _DeviceManager;

STDMETHODIMP CChamberInterface::CloseChamberDevice(long lChIndex)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if(!_DeviceManager.CloseChamberDevice(lChIndex))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CChamberInterface::SetChamberRunStop(long lChIndex)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if(!_DeviceManager.SetChamberRunStop(lChIndex))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CChamberInterface::SetChamberRunStart(long lChIndex)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if(!_DeviceManager.SetChamberRunStart(lChIndex))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CChamberInterface::SetChamberSetPoint(long lChIndex, double dbSetPoint)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if(!_DeviceManager.SetChamberSetPoint(lChIndex,dbSetPoint))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CChamberInterface::GetChamberSetPoint(long lChIndex, double *dbSetPoint)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if(!_DeviceManager.GetChamberSetPoint(lChIndex,dbSetPoint))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CChamberInterface::GetChamberCurrentTemp(long lChIndex, double *dbCurrTemp)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if(!_DeviceManager.GetChamberCurrentTemp(lChIndex,dbCurrTemp))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CChamberInterface::get_LastMessage(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
    m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
    *pVal = m_strMessage;
	return S_OK;
}
