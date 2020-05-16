// CIPolInterface.cpp : Implementation of CIPolInterface
#include "stdafx.h"
#include "UDLServer.h"
#include "IPolInterface.h"
#include "DeviceManger.h"

/////////////////////////////////////////////////////////////////////////////
// CIPolInterface
extern CDeviceManger _DeviceManager;

STDMETHODIMP CIPolInterface::ClosePolDevice(long lChIndex)
{	
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
		
	// TODO: Add your implementation code here
	if(!_DeviceManager.ClosePolDevice(lChIndex))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CIPolInterface::ResetPolDevice(long lChIndex)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if(!_DeviceManager.ResetPolDevice(lChIndex))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CIPolInterface::GetPolCurrentPOSPolarizer(long lChIndex, double * pdblAlphaP,double *pdblAlphaQ,double *pdblAlphaH)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	double dbalpha1,dbalpha2,dbalpha3;
	if(!_DeviceManager.GetPolCurrentPOSPolarizer(lChIndex,&dbalpha1,&dbalpha2,&dbalpha3))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	* pdblAlphaP = dbalpha1;
	*pdblAlphaQ = dbalpha2;
	*pdblAlphaH = dbalpha3;
	return S_OK;
}

STDMETHODIMP CIPolInterface::SetPolALL(long lChIndex, double alphaP, double alphaQ, double alp)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if(!_DeviceManager.SetPolALL(lChIndex,alphaP,alphaQ,alp))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}



STDMETHODIMP CIPolInterface::SetPolDiagonalAngles(long lChIndex, double AlphaPMax, double Wavelength)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if(!_DeviceManager.SetPolDiagonalAngles(lChIndex,AlphaPMax,Wavelength))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CIPolInterface::SetPolHorizontalAngles(long lChIndex, double AlphaPMax, double Wavelength)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if(!_DeviceManager.SetPolHorizontalAngles(lChIndex,AlphaPMax,Wavelength))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CIPolInterface::SetPolPOSHalf(long lChIndex, double alpha)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if(!_DeviceManager.SetPolPOSHalf(lChIndex,alpha))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CIPolInterface::SetPolPOSPolarizer(long lChIndex, double alpha)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if(!_DeviceManager.SetPolPOSPolarizer(lChIndex,alpha))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CIPolInterface::SetPolPOSQuarter(long lChIndex, double alpha)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if(!_DeviceManager.SetPolPOSQuarter(lChIndex,alpha))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CIPolInterface::SetPolRightHandCircularAngles(long lChIndex,double AlphaPMax, double Wavelength)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if(!_DeviceManager.SetPolRightHandCircularAngles(lChIndex,AlphaPMax,Wavelength))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CIPolInterface::SetPolVerticalAngles(long lChIndex, double AlphaPMax, double Wavelength)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if(!_DeviceManager.SetPolRightHandCircularAngles(lChIndex,AlphaPMax,Wavelength))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CIPolInterface::get_LastMessage(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
    m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
    *pVal = m_strMessage;
	return S_OK;
}
