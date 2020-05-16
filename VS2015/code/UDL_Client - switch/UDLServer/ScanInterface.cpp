// ScanInterface.cpp : Implementation of CScanInterface
#include "stdafx.h"
#include "UDLServer.h"
#include "ScanInterface.h"
#include "DeviceManger.h"

/////////////////////////////////////////////////////////////////////////////
// CScanInterface
extern CDeviceManger _DeviceManager;

STDMETHODIMP CScanInterface::PrepareScan(long lTLSChIndex, long lpScanParam)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	// TODO: Add your implementation code here
    stSetScanParam *pSetParam = (stSetScanParam *)lpScanParam;

	_DeviceManager.m_stScanParam.m_bDoPDL= pSetParam->m_bDoPDL;
	_DeviceManager.m_stScanParam.m_dbAlphaAngle= pSetParam->m_dbAlphaAngle;
	_DeviceManager.m_stScanParam.m_dblPWMPower= pSetParam->m_dblPWMPower;
	_DeviceManager.m_stScanParam.m_dblTLSPower= pSetParam->m_dblTLSPower;
	_DeviceManager.m_stScanParam.m_dblStartWL= pSetParam->m_dblStartWL;
	_DeviceManager.m_stScanParam.m_dblStepSize= pSetParam->m_dblStepSize;
	_DeviceManager.m_stScanParam.m_dblStopWL= pSetParam->m_dblStopWL;
	_DeviceManager.m_stScanParam.m_dwChannelCfgHigh= pSetParam->m_dwChannelCfgHigh;
	_DeviceManager.m_stScanParam.m_dwChannelCfgLow= pSetParam->m_dwChannelCfgLow;
	_DeviceManager.m_stScanParam.m_dwChannelNumber= pSetParam->m_dwChannelNumber;
	_DeviceManager.m_stScanParam.m_dwNumberOfScan= pSetParam->m_dwNumberOfScan;
	_DeviceManager.m_stScanParam.m_nAvgTime= pSetParam->m_nAvgTime;
    _DeviceManager.m_stScanParam.m_nPDLType= pSetParam->m_nPDLType;
	_DeviceManager.m_stScanParam.m_nPolChIndex= pSetParam->m_nPDocChIndex;
	_DeviceManager.m_stScanParam.m_nSpeed= pSetParam->m_nSpeed;

	if(!_DeviceManager.PrepareScan(lTLSChIndex))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
    pSetParam->m_dwSampleCount = _DeviceManager.m_stScanParam.m_dwSampleCount;

	return S_OK;
}

STDMETHODIMP CScanInterface::ExecuteScan(long lTLSChIndex, long lpScanRawDataPtr)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	POp816XRawData   pRawDataPtr = (POp816XRawData)lpScanRawDataPtr;
	if(!_DeviceManager.ExecuteScan(lTLSChIndex,(long)pRawDataPtr))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CScanInterface::ReleaseScan(long lTLSChIndex)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if(!_DeviceManager.ReleaseScan(lTLSChIndex))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CScanInterface::DoScanRef(long lTLSChIndex, long lpScanRawData)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
    POp816XRawData   pRawDataPtr = (POp816XRawData)lpScanRawData;
	_DeviceManager.m_pstRefScanData= pRawDataPtr;
	if(!_DeviceManager.DoScanRef(lTLSChIndex))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CScanInterface::DoScan(long lTLSChIndex, long lpScanRawData)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
    POp816XRawData   pRawDataPtr = (POp816XRawData)lpScanRawData;
	_DeviceManager.m_pstDoScanData= pRawDataPtr;
	if(!_DeviceManager.DoScan(lTLSChIndex))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CScanInterface::GetCalILResult(long lpScanResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
    POp816XRawData   pRawDataPtr = (POp816XRawData)lpScanResult;
	if(!_DeviceManager.GetCalILResult(pRawDataPtr))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CScanInterface::GetCalILAndPDLResult(long lpScanResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
    POp816XRawData   pRawDataPtr = (POp816XRawData)lpScanResult;
	if(!_DeviceManager.GetCalILAndPDLResult(pRawDataPtr))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;

}

STDMETHODIMP CScanInterface::ReleaseAllocStruct(long lpStructPtr)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
		
	// TODO: Add your implementation code here
	POp816XRawData   pRawDataPtr = (POp816XRawData)lpStructPtr;
	
	if(!_DeviceManager.GetCalILAndPDLResult(pRawDataPtr))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CScanInterface::get_LastMessage(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
    m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
    *pVal = m_strMessage;
	return S_OK;
}
