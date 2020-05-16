// ISwitchBoxInterface.cpp : Implementation of CISwitchBoxInterface
#include "stdafx.h"
#include "UDLServer.h"
#include "ISwitchBoxInterface.h"
#include "DeviceManger.h"
/////////////////////////////////////////////////////////////////////////////
// CISwitchBoxInterface
extern CDeviceManger _DeviceManager;

STDMETHODIMP CISwitchBoxInterface::OpenSwitchDevice(long lChIndex)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if(!_DeviceManager.OpenSwitchDevice(lChIndex))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CISwitchBoxInterface::CloseSwitchDevice(long lChIndex)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if(!_DeviceManager.CloseSwitchDevice(lChIndex))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CISwitchBoxInterface::SwitchPort2Port(int lChIndex, int nInputPort, int nOutputPort)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if(!_DeviceManager.SwitchPort2Port(lChIndex,nInputPort,nOutputPort))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CISwitchBoxInterface::get_LastMessage(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
    m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
    *pVal = m_strMessage;
	return S_OK;
}
