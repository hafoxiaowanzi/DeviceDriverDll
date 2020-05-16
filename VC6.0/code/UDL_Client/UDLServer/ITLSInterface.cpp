// ITLSInterface.cpp : Implementation of CITLSInterface
#include "stdafx.h"
#include "UDLServer.h"
#include "ITLSInterface.h"
#include "DeviceManger.h"

/////////////////////////////////////////////////////////////////////////////
// CITLSInterface
extern CDeviceManger _DeviceManager;

STDMETHODIMP CITLSInterface::SetTLSWavelength(long lChIndex, double dblWL)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
    if(!_DeviceManager.SetTLSWavelength(lChIndex,dblWL))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
	return S_OK;
}

//DEL STDMETHODIMP CITLSInterface::get_LastMessage(BSTR *pVal)
//DEL {
//DEL 	AFX_MANAGE_STATE(AfxGetStaticModuleState())
//DEL 
//DEL 	// TODO: Add your implementation code here
//DEL     *pVal = m_strMessage;
//DEL 	return S_OK;
//DEL }

//DEL STDMETHODIMP CITLSInterface::put_LastMessage(BSTR newVal)
//DEL {
//DEL 	AFX_MANAGE_STATE(AfxGetStaticModuleState())
//DEL 
//DEL 	// TODO: Add your implementation code here
//DEL     m_strMessage = newVal;
//DEL 	return S_OK;
//DEL }

STDMETHODIMP CITLSInterface::SetTLSSourcePower(long lChIndex, double dblPW)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
    if(!_DeviceManager.SetTLSSourcePower(lChIndex,dblPW))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
	return S_OK;
}

STDMETHODIMP CITLSInterface::SetTLSCoherenceControl(long lChIndex, BOOL bEnable)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
   if(!_DeviceManager.SetTLSCoherenceControl(lChIndex,bEnable))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
   m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
	return S_OK;
}

STDMETHODIMP CITLSInterface::SetTLSSourceUnit(long lChIndex, long lUnit)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
   if(!_DeviceManager.SetTLSSourceUnit(lChIndex,lUnit))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
   m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
	return S_OK;
}

STDMETHODIMP CITLSInterface::SetTLSParameters(long lChIndex, long lLowSSE,double dblPower, double dblWavelength)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
   if(!_DeviceManager.SetTLSParameters(lChIndex,lLowSSE,dblPower,dblWavelength))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
   m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
	return S_OK;
}

STDMETHODIMP CITLSInterface::SetTLSOutputEnable(long lChIndex, BOOL bEnable)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
   if(!_DeviceManager.SetTLSOutputEnable(lChIndex,bEnable))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
    m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
	return S_OK;
}

STDMETHODIMP CITLSInterface::CloseTLSDevice(long lChIndex)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
   if(!_DeviceManager.CloseTLSDevice(lChIndex))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
    m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
	return S_OK;
}



STDMETHODIMP CITLSInterface::get_LastMessage(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
    *pVal = m_strMessage;
	return S_OK;
}
