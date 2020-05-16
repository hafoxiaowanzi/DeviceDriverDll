// IOSAInterface.cpp : Implementation of CIOSAInterface
#include "stdafx.h"
#include "UDLServer.h"
#include "IOSAInterface.h"
#include "DeviceManger.h"

/////////////////////////////////////////////////////////////////////////////
// CIOSAInterface
extern CDeviceManger _DeviceManager;

STDMETHODIMP CIOSAInterface::CloseDevice(long lChIndex)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

		// TODO: Add your implementation code here
		if (!_DeviceManager.CloseOSADevice(lChIndex))
		{
			m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
			return S_FALSE;
		}
	return S_OK;
}

STDMETHODIMP CIOSAInterface::ResetDevice(long lChIndex)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

		// TODO: Add your implementation code here
		if (!_DeviceManager.ResetOSADevice(lChIndex))
		{
			m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
			return S_FALSE;
		}
	return S_OK;
}

STDMETHODIMP CIOSAInterface::SetOSALocalCtrl(long lChIndex)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

		// TODO: Add your implementation code here
		if (!_DeviceManager.SetOSALocalCtrl(lChIndex))
		{
			m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
			return S_FALSE;
		}
	return S_OK;
}

STDMETHODIMP CIOSAInterface::SetOSARBW(long lChIndex, double dblRBW)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

		// TODO: Add your implementation code here
		if (!_DeviceManager.SetOSARBW(lChIndex, dblRBW))
		{
			m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
			return S_FALSE;
		}
	return S_OK;
}

STDMETHODIMP CIOSAInterface::GetOSARBW(long lChIndex, double *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

		// TODO: Add your implementation code here
		if (!_DeviceManager.GetOSARBW(lChIndex, pVal))
		{
			m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
			return S_FALSE;
		}
	return S_OK;
}

STDMETHODIMP CIOSAInterface::InitOSAAmpTest(long lChIndex, double dblStartWL, double dblStopWL, double dblRBW)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

		// TODO: Add your implementation code here
		if (!_DeviceManager.InitOSAAmpTest(lChIndex, dblStartWL, dblStopWL, dblRBW))
		{
			m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
			return S_FALSE;
		}
	return S_OK;
}

STDMETHODIMP CIOSAInterface::MeasureSource(long lChIndex)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

		// TODO: Add your implementation code here
		if (!_DeviceManager.MeasureOSASource(lChIndex))
		{
			m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
			return S_FALSE;
		}
	return S_OK;
}

STDMETHODIMP CIOSAInterface::MeasureAmplifier(long lChIndex, BOOL bScanSrcOnly)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

		// TODO: Add your implementation code here
		if (!_DeviceManager.MeasureOSAAmplifier(lChIndex, bScanSrcOnly))
		{
			m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
			return S_FALSE;
		}
	return S_OK;
}

STDMETHODIMP CIOSAInterface::GetOSAChannelCount(long lChIndex, long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

		// TODO: Add your implementation code here
		DWORD dwCount;
	if (!_DeviceManager.GetOSAChannelCount(lChIndex, &dwCount))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	*pVal = dwCount;
	return S_OK;
}

//DEL STDMETHODIMP CIOSAInterface::get_OSAChannelWaveLens(long lChIndex, double *pVal)
//DEL {
//DEL 	AFX_MANAGE_STATE(AfxGetStaticModuleState())
//DEL 
//DEL 	// TODO: Add your implementation code here
//DEL 	DWORD dwCount;
//DEL     if(!_DeviceManager.GetOSAChannelWaveLens(lChIndex,pVal,&dwCount))
//DEL 	{
//DEL 		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
//DEL 		return S_FALSE;
//DEL 	}
//DEL 	return S_OK;
//DEL }

//DEL STDMETHODIMP CIOSAInterface::get_OSAChannelNF(long lChIndex, double *pVal)
//DEL {
//DEL 	AFX_MANAGE_STATE(AfxGetStaticModuleState())
//DEL 
//DEL 	// TODO: Add your implementation code here
//DEL 	DWORD dwCount;
//DEL     if(!_DeviceManager.GetOSAChannelNF(lChIndex,pVal,&dwCount))
//DEL 	{
//DEL 		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
//DEL 		return S_FALSE;
//DEL 	}
//DEL 	return S_OK;
//DEL }

//DEL STDMETHODIMP CIOSAInterface::get_OSAChannelGain(long lChIndex, double *pVal)
//DEL {
//DEL 	AFX_MANAGE_STATE(AfxGetStaticModuleState())
//DEL 
//DEL 	// TODO: Add your implementation code here
//DEL 	DWORD dwCount;
//DEL     if(!_DeviceManager.GetOSAChannelGain(lChIndex,pVal,&dwCount))
//DEL 	{
//DEL 		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
//DEL 		return S_FALSE;
//DEL 	}
//DEL 	return S_OK;
//DEL }

//DEL STDMETHODIMP CIOSAInterface::get_OSAChannelSNR(long lChIndex, double *pVal)
//DEL {
//DEL 	AFX_MANAGE_STATE(AfxGetStaticModuleState())
//DEL 
//DEL 	// TODO: Add your implementation code here
//DEL 	DWORD dwCount;
//DEL     if(!_DeviceManager.GetOSAChannelSNR(lChIndex,pVal,&dwCount))
//DEL 	{
//DEL 		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
//DEL 		return S_FALSE;
//DEL 	}
//DEL 	return S_OK;
//DEL }

//DEL STDMETHODIMP CIOSAInterface::get_OSAChannelSourcePower(long lChIndex, double *pVal)
//DEL {
//DEL 	AFX_MANAGE_STATE(AfxGetStaticModuleState())
//DEL 
//DEL 	// TODO: Add your implementation code here
//DEL 	DWORD dwCount;
//DEL     if(!_DeviceManager.GetOSAChannelSourcePower(lChIndex,pVal,&dwCount))
//DEL 	{
//DEL 		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
//DEL 		return S_FALSE;
//DEL 	}
//DEL 	return S_OK;
//DEL }

STDMETHODIMP CIOSAInterface::SetOSAAmpOffset(long lChIndex, double dblSourceOffset, double dblAmpOffset)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

		// TODO: Add your implementation code here
		if (!_DeviceManager.SetOSAAmpOffset(lChIndex, dblSourceOffset, dblAmpOffset))
		{
			m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
			return S_FALSE;
		}
	return S_OK;
}

STDMETHODIMP CIOSAInterface::GetOSAAmpOffset(long lChIndex, double *pdblSourceOffSet, double *pdblAmpOffset)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

		// TODO: Add your implementation code here
		if (!_DeviceManager.GetOSAAmpOffset(lChIndex, *pdblSourceOffSet, *pdblAmpOffset))
		{
			m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
			return S_FALSE;
		}
	return S_OK;
}
STDMETHODIMP CIOSAInterface::GetOSAEDFAResult(long lChIndex, double *pdblSumSrcSigPwr, double *pdblSumAmpSigPwr, double *pdblSumGain)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

		// TODO: Add your implementation code here
		if (!_DeviceManager.GetOSAEDFAResult(lChIndex, pdblSumSrcSigPwr, pdblSumAmpSigPwr, pdblSumGain))
		{
			m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
			return S_FALSE;
		}
	return S_OK;
}

STDMETHODIMP CIOSAInterface::GetOSAEDFAChResult(long lChIndex, long *pwChCount, double *pdblChWL, double *pdblSrcpwr, double *pdblChGain, double *pdblChNF, double *pdblChAse, double *pdbGainFlatness, double *pdblMaxNF, double *pdblMaxGain, double *pdblMinGain)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

		// TODO: Add your implementation code here
		DWORD dwGetChCount;
	if (!_DeviceManager.GetOSAEDFAChResult(lChIndex, &dwGetChCount, pdblChWL, pdblSrcpwr, pdblChGain, pdblChNF, pdblChAse, pdbGainFlatness, pdblMaxNF, pdblMaxGain, pdblMinGain))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	*pwChCount = dwGetChCount;
	return S_OK;
}

STDMETHODIMP CIOSAInterface::InitOSASingleSweep(long lChIndex, double dblStartWL, double dblStopWL, double dblRBW, long lSweepPointCount)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

		// TODO: Add your implementation code here
		if (!_DeviceManager.InitOSASingleSweep(lChIndex, dblStartWL, dblStopWL, dblRBW, lSweepPointCount))
		{
			m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
			return S_FALSE;
		}
	return S_OK;
}


STDMETHODIMP CIOSAInterface::RunOSASweep(long lChIndex, double *pdblWL, double *pdblPower, BSTR szSelTrace)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

		// TODO: Add your implementation code here
		CString strTemp;
	char szBuf;
	strTemp = szSelTrace;
	szBuf = strTemp.GetAt(0);
	if (!_DeviceManager.RunOSASweep(lChIndex, pdblWL, pdblPower, szBuf))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CIOSAInterface::GetOSASweepData(long lChIndex, double *pdblWL, double *pdblPower, BSTR szSelTrace)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

		// TODO: Add your implementation code here
		CString strTemp;
	char szBuf;
	strTemp = szSelTrace;
	szBuf = strTemp.GetAt(0);
	if (!_DeviceManager.GetOSASweepData(lChIndex, pdblWL, pdblPower, szBuf))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CIOSAInterface::SetOSACalibration(long lChIndex, long lCalibrationType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

		// TODO: Add your implementation code here
		if (!_DeviceManager.SetOSACalibration(lChIndex, lCalibrationType))
		{
			m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
			return S_FALSE;
		}
	return S_OK;
}

STDMETHODIMP CIOSAInterface::SaveOSADataToPC(long lChIndex, BSTR lpSavePath, BSTR lpDataType, BSTR lpFileType, BSTR szSelTrace)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

		// TODO: Add your implementation code here
		CString strSavePath, strDataType, strFileType, strTemp;
	strSavePath = lpSavePath;
	strDataType = lpDataType;
	strFileType = lpFileType;
	strTemp = szSelTrace;
	char szBuf = strTemp.GetAt(0);
	if (!_DeviceManager.SaveOSADataToPC(lChIndex, strSavePath, strDataType, strFileType, szBuf))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CIOSAInterface::get_LastMessage(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

		// TODO: Add your implementation code here
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
	*pVal = m_strMessage;
	return S_OK;
}

STDMETHODIMP CIOSAInterface::ChannelWaveLens(double *pdblWL, DWORD *pdwChannelCount)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

		// TODO: Add your implementation code here

		return S_OK;
}


STDMETHODIMP CIOSAInterface::GetChannelWaveLens(long lChanIndex, double *pdblWL, DWORD *pdwlChanneCount)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

		// TODO: Add your implementation code here
		if (!_DeviceManager.GetOSAChannelWaveLens(lChanIndex, pdblWL, pdwlChanneCount))
		{
			m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
			return S_FALSE;
		}

	return S_OK;
}

STDMETHODIMP CIOSAInterface::GetChannelNF(long lChIndex, double *pdblNF, DWORD *pdwChannelCount)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

		// TODO: Add your implementation code here
		if (!_DeviceManager.GetOSAChannelNF(lChIndex, pdblNF, pdwChannelCount))
		{
			m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
			return S_FALSE;
		}
	return S_OK;
}

STDMETHODIMP CIOSAInterface::GetChannelGain(long lChIndex, double *pdblGain, DWORD *pdwChannelCount)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

		// TODO: Add your implementation code here
		if (!_DeviceManager.GetOSAChannelGain(lChIndex, pdblGain, pdwChannelCount))
		{
			m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
			return S_FALSE;
		}
	return S_OK;
}

STDMETHODIMP CIOSAInterface::GetChannelSNR(long lChIndex, double *pdblSNR, DWORD *pdwChannelCount)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

		// TODO: Add your implementation code here
		if (!_DeviceManager.GetOSAChannelSNR(lChIndex, pdblSNR, pdwChannelCount))
		{
			m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
			return S_FALSE;
		}
	return S_OK;
}

STDMETHODIMP CIOSAInterface::GetChannelSourcePower(long lChIndex, double *pdblSourcePower, DWORD *pdwChannelCount)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

		// TODO: Add your implementation code here
		if (!_DeviceManager.GetOSAChannelSourcePower(lChIndex, pdblSourcePower, pdwChannelCount))
		{
			m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
			return S_FALSE;
		}
	return S_OK;
}

STDMETHODIMP CIOSAInterface::GetOSAZoomValue(long lChIndex, double dbWLNM, double dbBWNM, double *pdbGetValue)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

		// TODO: Add your implementation code here
		if (!_DeviceManager.GetZoomValue(lChIndex, dbWLNM, dbBWNM, pdbGetValue))
		{
			m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
			return S_FALSE;
		}
	return S_OK;
}

STDMETHODIMP CIOSAInterface::GetOSASingleSweepPoint(long lChIndex, long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

		// TODO: Add your implementation code here
		DWORD dwPoint;
	if (!_DeviceManager.GetSingleSweepPoint(lChIndex, &dwPoint))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	*pVal = dwPoint;
	return S_OK;
}

STDMETHODIMP CIOSAInterface::InitOSAWDMTest(long lChIndex, double dblStartWL, double dblStopWL, double dblRBW)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

		// TODO: Add your implementation code here
		if (!_DeviceManager.InitOSAWDMTest(lChIndex, dblStartWL, dblStopWL, dblRBW))
		{
			m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
			return S_FALSE;
		}
	return S_OK;
}

STDMETHODIMP CIOSAInterface::MeasureOSAWDM(long lChIndex)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

		// TODO: Add your implementation code here
		if (!_DeviceManager.MeasureOSAWDM(lChIndex))
		{
			m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
			return S_FALSE;
		}
	return S_OK;
}

//STDMETHODIMP CIOSAInterface::InitOSARepeatSweep(long lChIndex,double dblStartWL, double dblStopWL,double dblRBW,long lSweepPointCount)
//{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())
//
//		// TODO: Add your implementation code here
//		if (!_DeviceManager.InitOSARepeatSweep(lChIndex, dblStartWL, dblStopWL, dblRBW, lSweepPointCount))
//		{
//			m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
//			return S_FALSE;
//		}
//	return S_OK;
//}


STDMETHODIMP CIOSAInterface::InitOSARepeatSweep(LONG lChIndex, DOUBLE dblStartWL, DOUBLE dblStopWL, DOUBLE dblRBW, LONG lSweepPointCount)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your implementation code here

	if (!_DeviceManager.InitOSARepeatSweep(lChIndex, dblStartWL, dblStopWL, dblRBW, lSweepPointCount))
	{
		m_strMessage = _DeviceManager.GetErrorMsg().AllocSysString();
		return S_FALSE;
	}
	return S_OK;
}
