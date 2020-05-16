// IComDevInterface.cpp : Implementation of CIComDevInterface
#include "stdafx.h"
#include "UDLServer.h"
#include "IComDevInterface.h"
#include "DeviceManger.h"
/////////////////////////////////////////////////////////////////////////////
// CIComDevInterface
extern CDeviceManger _DeviceManager;

STDMETHODIMP CIComDevInterface::WriteBuffer(long lChIndex, BSTR pBuffer, DWORD dwBufferSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	CString strTemp  = pBuffer;
	unsigned char * ptemp = (unsigned char * )strTemp.GetBuffer(0);
    if(!_DeviceManager.WriteDevComBuffer(lChIndex,ptemp,dwBufferSize))
  	{
  		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
  		return S_FALSE;
  	}
	strTemp.ReleaseBuffer(0);
	return S_OK;
}

STDMETHODIMP CIComDevInterface::ReadBuffer(long lChIndex, BSTR *pBuffer, DWORD dwBufferSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
		
	// TODO: Add your implementation code here
	CString strMsg;
	strMsg.Empty();
	unsigned char * pValue =NULL;
	pValue	= (unsigned char *)VirtualAlloc(NULL,sizeof(unsigned char)*dwBufferSize,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
	ZeroMemory(pValue,sizeof(unsigned char)*dwBufferSize);
    if(!_DeviceManager.ReadDevComBuffer(lChIndex,pValue,dwBufferSize))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	strMsg = pValue;
	*pBuffer = strMsg.AllocSysString();	
	strMsg.ReleaseBuffer(0);
	if(pValue !=NULL)
	{
		VirtualFree(pValue,0,MEM_RELEASE);
		pValue = NULL;
	}

	return S_OK;
}

//DEL STDMETHODIMP CIComDevInterface::get_LastMessage(BSTR *pVal)
//DEL {
//DEL 	AFX_MANAGE_STATE(AfxGetStaticModuleState())
//DEL     
//DEL 	// TODO: Add your implementation code here
//DEL     m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
//DEL 	*pVal = m_strMessage;
//DEL 	return S_OK;
//DEL }

STDMETHODIMP CIComDevInterface::CloseSerial(long lChIndex)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
    if(!_DeviceManager.CloseDevDevice(lChIndex))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CIComDevInterface::OpenSerial(long lChIndex)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
    if(!_DeviceManager.OpenDevDevice(lChIndex))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CIComDevInterface::get_LastMessage(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
		
	// TODO: Add your implementation code here
	m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
	*pVal = m_strMessage;
	return S_OK;
}
