// OSAControlDll.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "..\\include\\OSA.h"
#include "..\\include\\NFLib.h"
#include "..\\include\\OSAControlDll.h"


//long			m_lOSAType;
//
//BYTE			m_bNFMode;
//double			m_pdblScanData[2][5001];	// Agilent Max point is 10001
//double			m_dblSensitivity;
//LONG			m_lScanPoint;
//stScanSetting	m_stScanSetting;
//stEDFAResult	m_stEDFAResult;

#define CNET_TYPE_GPIB			0
#define CNET_TYPE_SERIALPORT	1
#define CNET_TYPE_NET			2
#define CNET_TYPE_USB			3

#define	SRC_SCAN				0
#define	AMP_SCAN				1

#define	ISS_MODE				0	/* ISS mode of agilent */
#define	NSM_MODE				1	/* Normal scan mode */

BOOL APIENTRY DllMain(HANDLE hModule,
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
OSACONTROLDLL_API int nOSAControlDll = 0;

// This is an example of an exported function.
OSACONTROLDLL_API int fnOSAControlDll(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see OSAControlDll.h for the class definition
COSADll::COSADll()
{
	m_pOSA = NULL;

	return;
}

COSADll::~COSADll()
{
	if (m_pOSA != NULL)
	{
		delete m_pOSA;
		m_pOSA = NULL;
	}
	return;
}
/************************************************************************
*  函数名称:OpenDevice													*
*  功能: 打开连接设备													*
*  输入:																*
*		1.stType:设备类型结构体											*
*       2.pszDeviceAddr:通讯信息										*
*  输出数据类型:stDevType, char* 										*
*  输出:																*
*       comHandle:基础通讯接口Handle									*
*  输出数据类型:CommunicationHandle										*
*  返回值:																*
*             0: 函数执行成功。											*
*    0x80000012: 其他错误												*
*  返回值类型:DWORD														*
*  创建日期:2013-09-17													*
*  创建人:赵寒飞														*
*  修改历史:无															*
*************************************************************************/
DWORD COSADll::OpenDevice(stDevType stType, char* pszDeviceAddr, unsigned long *comHandle)
{

	DWORD dwErrorCode = SUCCESS;

	try
	{
		if (m_pOSA != NULL)
		{
			delete m_pOSA;
			m_pOSA = NULL;
		}
		if (AQ_6370B == stType.bType)
		{
			//m_pOSA = (COSA_AQ6370B *)m_pvoid[AQ_6370B];
			m_pOSA = new COSA_AQ6370B();
		}
		else if (HP_86142 == stType.bType)
		{
			m_pOSA = new AgilentOSA();
		}
		else if (AQ_6317B == stType.bType)
		{
			m_pOSA = new COSA_AQ6317B();
		}
		else if (OTMS == stType.bType)
		{
			m_pOSA = new COSA_SHARE();
		}
		else
		{
			throw ERROR_COMMUNICATION_INFO;
		}

		dwErrorCode = m_pOSA->OpenDevice(stType, pszDeviceAddr, comHandle);
		if (SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA | dwErrorCode;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return ERROR_OSA | UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD COSADll::CloseDevice()
{
	DWORD dwErrorCode = SUCCESS;

	try
	{
		dwErrorCode = m_pOSA->CloseDevice();
		if (SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA | dwErrorCode;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = ERROR_OSA | UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD COSADll::ResetDevice(void)
{
	DWORD dwErrorCode = 0;

	try
	{
		dwErrorCode = m_pOSA->ResetDevice();
		if (SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA | dwErrorCode;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = ERROR_OSA | UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD COSADll::SetOSALocalCtrl(void)
{
	DWORD dwErrorCode = 0;

	try
	{
		if (m_pOSA == NULL)
		{
			throw UNEXPECT_OCCUR;
		}
		dwErrorCode = m_pOSA->SetOSALocalCtrl();
		if (SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA | dwErrorCode;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = ERROR_OSA | UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD COSADll::SetRBW(double dblRBW)
{
	DWORD dwErrorCode = 0;

	try
	{
		if (m_pOSA == NULL)
		{
			throw UNEXPECT_OCCUR;
		}
		dwErrorCode = m_pOSA->SetRBW(dblRBW);
		if (SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA | dwErrorCode;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = ERROR_OSA | UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD COSADll::GetRBW(double* pdblRBW)
{
	DWORD dwErrorCode = 0;

	try
	{
		if (m_pOSA == NULL)
		{
			throw UNEXPECT_OCCUR;
		}
		dwErrorCode = m_pOSA->GetRBW(pdblRBW);
		if (SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA | dwErrorCode;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = ERROR_OSA | UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD COSADll::InitAmpTest(double dblStartWL, double dblStopWL, double dblRBW)
{
	DWORD dwErrorCode = 0;

	try
	{
		if (m_pOSA == NULL)
		{
			throw UNEXPECT_OCCUR;
		}
		dwErrorCode = m_pOSA->InitAmpTest(dblStartWL, dblStopWL, dblRBW);
		if (SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA | dwErrorCode;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = ERROR_OSA | UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD COSADll::MeasureSource()
{
	DWORD dwErrorCode = 0;

	try
	{
		if (m_pOSA == NULL)
		{
			throw UNEXPECT_OCCUR;
		}
		dwErrorCode = m_pOSA->MeasureSource();
		if (SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA | dwErrorCode;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = ERROR_OSA | UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD COSADll::MeasureAmplifier(BOOL bScanSrcOnly)
{
	DWORD dwErrorCode = 0;

	try
	{
		if (m_pOSA == NULL)
		{
			throw UNEXPECT_OCCUR;
		}
		dwErrorCode = m_pOSA->MeasureAmplifier(bScanSrcOnly);
		if (SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA | dwErrorCode;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = ERROR_OSA | UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD COSADll::GetChannelCount(DWORD* pdwChannelCount)
{
	DWORD dwErrorCode = 0;

	try
	{
		if (m_pOSA == NULL)
		{
			throw UNEXPECT_OCCUR;
		}
		dwErrorCode = m_pOSA->GetChannelCount(pdwChannelCount);
		if (SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA | dwErrorCode;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = ERROR_OSA | UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD COSADll::GetChannelWaveLens(double* pdblWL, DWORD* pdwChannelCount)
{
	DWORD dwErrorCode = 0;

	try
	{
		if (m_pOSA == NULL)
		{
			throw UNEXPECT_OCCUR;
		}
		dwErrorCode = m_pOSA->GetChannelWaveLens(pdblWL, pdwChannelCount);
		if (SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA | dwErrorCode;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = ERROR_OSA | UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD COSADll::GetChannelNF(double* pdblNF, DWORD* pdwChannelCount)
{
	DWORD dwErrorCode = 0;

	try
	{
		if (m_pOSA == NULL)
		{
			throw UNEXPECT_OCCUR;
		}
		dwErrorCode = m_pOSA->GetChannelNF(pdblNF, pdwChannelCount);
		if (SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA | dwErrorCode;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = ERROR_OSA | UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD COSADll::GetChannelGain(double* pdblGain, DWORD* pdwChannelCount)
{
	DWORD dwErrorCode = 0;

	try
	{
		if (m_pOSA == NULL)
		{
			throw UNEXPECT_OCCUR;
		}
		dwErrorCode = m_pOSA->GetChannelGain(pdblGain, pdwChannelCount);
		if (SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA | dwErrorCode;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = ERROR_OSA | UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD COSADll::GetChannelSNR(double* pdblSNR, DWORD* pdwChannelCount)
{
	DWORD dwErrorCode = 0;

	try
	{
		if (m_pOSA == NULL)
		{
			throw UNEXPECT_OCCUR;
		}
		dwErrorCode = m_pOSA->GetChannelSNR(pdblSNR, pdwChannelCount);
		if (SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA | dwErrorCode;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = ERROR_OSA | UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD COSADll::GetChannelSourcePower(double* pdblSourcePow, DWORD* pdwChannelCount)
{
	DWORD dwErrorCode = 0;

	try
	{
		if (m_pOSA == NULL)
		{
			throw UNEXPECT_OCCUR;
		}
		dwErrorCode = m_pOSA->GetChannelSourcePower(pdblSourcePow, pdwChannelCount);
		if (SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA | dwErrorCode;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = ERROR_OSA | UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD COSADll::SetAmpOffset(double dblSourceOffset, double dblAmpOffset)
{
	DWORD dwErrorCode = 0;

	try
	{
		if (m_pOSA == NULL)
		{
			throw UNEXPECT_OCCUR;
		}
		dwErrorCode = m_pOSA->SetAmpOffset(dblSourceOffset, dblAmpOffset);
		if (SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA | dwErrorCode;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = ERROR_OSA | UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD COSADll::GetAmpOffset(double &dblSourceOffset, double &dblAmpOffset)
{
	DWORD dwErrorCode = 0;

	try
	{
		if (m_pOSA == NULL)
		{
			throw UNEXPECT_OCCUR;
		}
		dwErrorCode = m_pOSA->GetAmpOffset(dblSourceOffset, dblAmpOffset);
		if (SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA | dwErrorCode;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = ERROR_OSA | UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD COSADll::GetEDFAResult(double *pdblSumSrcSigPwr, double *pdblSumAmpSigPwr, double *pdblSunGain)
{
	DWORD dwErrorCode = 0;

	try
	{
		if (m_pOSA == NULL)
		{
			throw UNEXPECT_OCCUR;
		}
		dwErrorCode = m_pOSA->GetEDFAResult(pdblSumSrcSigPwr, pdblSumAmpSigPwr, pdblSunGain);
		if (SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA | dwErrorCode;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = ERROR_OSA | UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD COSADll::GetEDFAChResult(DWORD *pwChCount, double *pdblChWL, double *pdblSrcpwr, double *pdblChGain, double *pdblChNF, double *pdblChAse,
	double *pdblGainFlatness, double *pdblMaxNF, double* pdblMaxGain, double* pdblMinGain)
{
	DWORD dwErrorCode = 0;

	try
	{
		if (m_pOSA == NULL)
		{
			throw UNEXPECT_OCCUR;
		}
		dwErrorCode = m_pOSA->GetEDFAChResult(pwChCount, pdblChWL, pdblSrcpwr, pdblChGain, pdblChNF, pdblChAse,
			pdblGainFlatness, pdblMaxNF, pdblMaxGain, pdblMinGain);
		if (SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA | dwErrorCode;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = ERROR_OSA | UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD COSADll::InitSingleSweep(double dblStartWL, double dblStopWL, double dblRBW, DWORD dwSweepPoint)
{
	DWORD dwErrorCode = 0;

	try
	{
		if (m_pOSA == NULL)
		{
			throw UNEXPECT_OCCUR;
		}
		dwErrorCode = m_pOSA->InitSingleSweep(dblStartWL, dblStopWL, dblRBW, dwSweepPoint);
		if (SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA | dwErrorCode;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = ERROR_OSA | UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD COSADll::RunSweep(double* pdblWL, double* pdblPower, char szSelTrace)
{
	DWORD dwErrorCode = 0;

	try
	{
		if (m_pOSA == NULL)
		{
			throw UNEXPECT_OCCUR;
		}
		dwErrorCode = m_pOSA->RunSweep(pdblWL, pdblPower, szSelTrace);
		if (SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA | dwErrorCode;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = ERROR_OSA | UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD COSADll::GetSingleSweepPoint(DWORD * pdwPointCount)
{
	DWORD dwErrorCode = 0;

	try
	{
		if (m_pOSA == NULL)
		{
			throw UNEXPECT_OCCUR;
		}
		dwErrorCode = m_pOSA->GetSingleSweepPoint(pdwPointCount);
		if (SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA | dwErrorCode;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = ERROR_OSA | UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD COSADll::GetSweepData(double* pdblWL, double* pdblPower, char szSelTrace)
{
	DWORD dwErrorCode = 0;

	try
	{
		if (m_pOSA == NULL)
		{
			throw UNEXPECT_OCCUR;
		}
		dwErrorCode = m_pOSA->GetSweepData(pdblWL, pdblPower, szSelTrace);
		if (SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA | dwErrorCode;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = ERROR_OSA | UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD COSADll::GetDeviceInfo(stDevInfo *stInfo)
{
	DWORD dwErrorCode = 0;

	try
	{
		if (m_pOSA == NULL)
		{
			throw UNEXPECT_OCCUR;
		}
		dwErrorCode = m_pOSA->GetDeviceInfo(stInfo);
		if (SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA | dwErrorCode;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = ERROR_OSA | UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD COSADll::SaveDatatoPC(LPCTSTR lpSavePath, LPCTSTR lpDataType, LPCTSTR lpFileType, char szSelTrace)
{
	DWORD dwErrorCode = 0;

	try
	{
		if (m_pOSA == NULL)
		{
			throw UNEXPECT_OCCUR;
		}
		dwErrorCode = m_pOSA->SaveDatatoPC(lpSavePath, lpDataType, lpFileType, szSelTrace);
		if (SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA | dwErrorCode;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = ERROR_OSA | UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}


DWORD COSADll::SetCalibration(DWORD dwCalibrationType)
{
	DWORD dwErrorCode = 0;

	try
	{
		if (m_pOSA == NULL)
		{
			throw UNEXPECT_OCCUR;
		}
		dwErrorCode = m_pOSA->SetCalibration(dwCalibrationType);
		if (SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA | dwErrorCode;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = ERROR_OSA | UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD COSADll::GetTotalPower(double &dblPow, char szSelTrace)
{
	DWORD  dwErrorCode = SUCCESS;
	try
	{
		if (m_pOSA == NULL)
		{
			throw UNEXPECT_OCCUR;
		}
		dwErrorCode = m_pOSA->GetTotalPower(dblPow, szSelTrace);
		if (SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA | dwErrorCode;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = ERROR_OSA | UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD COSADll::GetActualBW(double dblBwAmp, double &dblActBw)
{
	DWORD  dwErrorCode = SUCCESS;
	try
	{
		if (m_pOSA == NULL)
		{
			throw UNEXPECT_OCCUR;
		}
		dwErrorCode = m_pOSA->GetActualBW(dblBwAmp, dblActBw);
		if (SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA | dwErrorCode;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = ERROR_OSA | UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

BOOL COSADll::GetErrorMessage(DWORD dwErrorCode, char *pszErrorMsg)
{

	return TRUE;
}
DWORD COSADll::SetHandle(stDevType stType, LPCTSTR pszDeviceAddr, unsigned long handle)
{
	DWORD dwErrorCode = SUCCESS;

	try
	{
		if (m_pOSA != NULL)
		{
			delete m_pOSA;
			m_pOSA = NULL;
		}
		if (AQ_6370B == stType.bType)
		{
			//m_pOSA = (COSA_AQ6370B *)m_pvoid[AQ_6370B];
			m_pOSA = new COSA_AQ6370B();
		}
		else if (HP_86142 == stType.bType)
		{
			m_pOSA = new AgilentOSA();
		}
		else if (AQ_6317B == stType.bType)
		{
			m_pOSA = new COSA_AQ6317B();
		}
		else
		{
			throw ERROR_COMMUNICATION_INFO;
		}
		dwErrorCode = m_pOSA->SetHandle(pszDeviceAddr, handle);
		if (SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA | dwErrorCode;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return ERROR_OSA | UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}
DWORD COSADll::GetZoomValue(double dbWLNM, double dbBWNM, double *pdbGetValue)
{
	DWORD dwErrorCode = SUCCESS;

	try
	{
		if (m_pOSA == NULL)
		{
			throw UNEXPECT_OCCUR;
		}
		dwErrorCode = m_pOSA->GetZoomValue(dbWLNM, dbBWNM, pdbGetValue);
		if (SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA | dwErrorCode;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return ERROR_OSA | UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}
DWORD COSADll::InitWDMTest(double dblStartWL, double dblStopWL, double dblRBW)
{
	DWORD dwErrorCode = SUCCESS;

	try
	{
		if (m_pOSA == NULL)
		{
			throw UNEXPECT_OCCUR;
		}
		dwErrorCode = m_pOSA->InitWDMTest(dblStartWL, dblStopWL, dblRBW);
		if (SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA | dwErrorCode;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return ERROR_OSA | UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}
DWORD COSADll::MeasureWDM()
{
	DWORD dwErrorCode = SUCCESS;

	try
	{
		if (m_pOSA == NULL)
		{
			throw UNEXPECT_OCCUR;
		}
		dwErrorCode = m_pOSA->MeasureWDM();
		if (SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA | dwErrorCode;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return ERROR_OSA | UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD COSADll::SetOSALock(int nTimeOut)
{
	DWORD dwErrorCode = SUCCESS;

	try
	{
		if (m_pOSA == NULL)
		{
			throw UNEXPECT_OCCUR;
		}
		dwErrorCode = m_pOSA->SetOSALock(nTimeOut);
		if (SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA | dwErrorCode;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return ERROR_OSA | UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}
DWORD COSADll::SetOSAUnlock()
{

	DWORD dwErrorCode = SUCCESS;

	try
	{
		if (m_pOSA == NULL)
		{
			throw UNEXPECT_OCCUR;
		}
		dwErrorCode = m_pOSA->SetOSAUnlock();
		if (SUCCESS != dwErrorCode)
		{
			throw ERROR_OSA | dwErrorCode;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return ERROR_OSA | UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}