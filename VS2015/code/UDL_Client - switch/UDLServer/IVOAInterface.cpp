// IVOAInterface.cpp : Implementation of CIVOAInterface
#include "stdafx.h"
#include "UDLServer.h"
#include "IVOAInterface.h"
#include "DeviceManger.h"

/////////////////////////////////////////////////////////////////////////////
// CIVOAInterface
extern CDeviceManger _DeviceManager;

STDMETHODIMP CIVOAInterface::CloseVOADevice(long lChIndex)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
   if(!_DeviceManager.CloseVOADevice(lChIndex))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CIVOAInterface::ResetVOADevice(long lChIndex)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
   if(!_DeviceManager.ResetVOADevice(lChIndex))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CIVOAInterface::SetVOAWavelength(long lChIndex, double dblWL)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
   if(!_DeviceManager.SetVOAWavelength(lChIndex,dblWL))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CIVOAInterface::GetVOAWavelength(long lChIndex, double *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
   if(!_DeviceManager.GetVOAWavelength(lChIndex,pVal))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CIVOAInterface::SetVOAAttenuation(long lChIndex, double dblAtten)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
    if(!_DeviceManager.SetVOAAttenuation(lChIndex,dblAtten))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CIVOAInterface::GetVOAAttenuation(long lChIndex, double *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
    if(!_DeviceManager.GetVOAAttenuation(lChIndex,pVal))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CIVOAInterface::SetVOAEnableOutput(long lChIndex, BOOL bEanble)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
    if(!_DeviceManager.SetVOAEnableOutput(lChIndex,bEanble))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CIVOAInterface::SetVOAInputOffset(long lChIndex, double dblOffset)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
    if(!_DeviceManager.SetVOAInputOffset(lChIndex,dblOffset))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CIVOAInterface::GetVOAStatus(long lChIndex, long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	DWORD dwStatus;
    if(!_DeviceManager.GetVOAStatus(lChIndex,&dwStatus))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	*pVal = dwStatus;
	return S_OK;
}

STDMETHODIMP CIVOAInterface::get_LastMessage(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
    m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
	*pVal = m_strMessage;
	return S_OK;
}
