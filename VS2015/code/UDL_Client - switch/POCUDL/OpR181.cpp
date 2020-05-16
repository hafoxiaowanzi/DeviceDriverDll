// Op8169.cpp: implementation of the Op8169 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\\include\\PolDll.h"
#include "math.h"

#define	PolaNum	0
#define	QuatNum	2
#define	HalfNum	3
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COpR181::COpR181()
{

}

COpR181::~COpR181()
{

}

DWORD COpR181::SetMotorZero(BYTE bMotorIndex)
{
    CString strTemp;
	unsigned char pchData[32];
	int nCount =0;
	
	DWORD dwErrorCode = SUCCESS;
	try
	{
		strTemp.Format("dzero %d\r", bMotorIndex);
		dwErrorCode = m_DevComHandle.WriteDevice((unsigned char*)(LPCTSTR)strTemp,strTemp.GetLength());
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_RESET;
		}
		while(1)
		{
			Sleep(20);
			ZeroMemory(pchData, sizeof(char)*32);
			dwErrorCode=m_DevComHandle.ReadDevice(pchData,32);
			if (SUCCESS == dwErrorCode)
			{
				break;
			}
			if (nCount >10)
			{
				throw  dwErrorCode|ERROR_PDL_STEP;
			}
			nCount++;
		}
	}
	catch(DWORD dwError)
	{
		return ERROR_PDLD | dwError;
	}
	catch(...)
	{
		return ERROR_PDLD|UNEXPECT_OCCUR;
	}
	
	return dwErrorCode;	
}

DWORD COpR181::SetToTargetStep(BYTE bMotorIdx, WORD wTargetStep)
{
	CString strTemp;
	unsigned char pchData[32];
	int nCount =0;
	DWORD dwErrorCode = SUCCESS;
	try
	{
		strTemp.Format("STAR %d %d\r", bMotorIdx, wTargetStep);
		dwErrorCode = m_DevComHandle.WriteDevice((unsigned char*)(LPCTSTR)strTemp,strTemp.GetLength());
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PDL_STEP;
		}
		while(1)
		{
			Sleep(20);
			ZeroMemory(pchData, sizeof(char)*32);
			dwErrorCode=m_DevComHandle.ReadDevice(pchData,32);
			if (SUCCESS == dwErrorCode)
			{
				break;
			}
			if (nCount >10)
			{
				throw  dwErrorCode|ERROR_PDL_STEP;
			}
			nCount++;
		}
	}
	catch(DWORD dwError)
	{
		return ERROR_PDLD | dwError;
	}
	catch(...)
	{
		return ERROR_PDLD|UNEXPECT_OCCUR;
	}
	
	return dwErrorCode;	
}

BOOL COpR181::SetToTargetAngle(BYTE bMotorIdx, WORD wTargetAngle)
{
	CString strTemp;
	unsigned char pchData[32];
	int nCount =0;
	
	DWORD dwErrorCode = SUCCESS;
	try
	{
		// 给指定的电机设置一定的角度
		strTemp.Format("SANGLE %d %d\r", bMotorIdx, wTargetAngle);
		dwErrorCode = m_DevComHandle.WriteDevice((unsigned char*)(LPCTSTR)strTemp,strTemp.GetLength());
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PDL_SETANGLE;
		}
		while(1)
		{
			Sleep(20);
			ZeroMemory(pchData, sizeof(char)*32);
			dwErrorCode=m_DevComHandle.ReadDevice(pchData,32);
			if (SUCCESS == dwErrorCode)
			{
				break;
			}
			if (nCount >10)
			{
               throw  dwErrorCode|ERROR_PDL_SETANGLE;
			}
			nCount++;
		}
	}
	catch(DWORD dwError)
	{
		return ERROR_PDLD | dwError;
	}
	catch(...)
	{
		return ERROR_PDLD|UNEXPECT_OCCUR;
	}
	
	return dwErrorCode;	
}

WORD COpR181::GetAngle(BYTE bMotorIdx)
{
	CString strTemp;
	unsigned char pchData[32];
	WORD wAngle;
	DWORD dwErrorCode = FALSE;
	int nCount =0;
	
	strTemp.Format("GANGLE %d\r", bMotorIdx);
	dwErrorCode = m_DevComHandle.WriteDevice((unsigned char*)(LPCTSTR)strTemp,strTemp.GetLength());
	if(SUCCESS != dwErrorCode)
	{
		return (WORD)ERROR_VALUE;
	}
	while(1)
	{
		Sleep(20);
		ZeroMemory(pchData, sizeof(char)*32);
		dwErrorCode=m_DevComHandle.ReadDevice(pchData,32);
		if (SUCCESS == dwErrorCode)
		{
			break;
		}
		if (nCount >10)
		{
			return (WORD)ERROR_VALUE;
		}
		nCount++;
	}	
    strTemp = pchData;
	wAngle = atoi(strTemp);
	return wAngle;
}


/////////////////////////////////////////////////////////////
//函数说明：
//    打开设备
//Add by wanxin
//20140821
//////////////////////////////////////////////////////////////
DWORD COpR181::OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle)
{
	//CString strComPort;	
	DWORD   dwErrorCode = FALSE;

	dwErrorCode = m_DevComHandle.OpenDevice(pszDeviceAddr,*ComHandle);
	if (dwErrorCode != SUCCESS)
	{
		return dwErrorCode;
	}	
	return dwErrorCode;
}
/////////////////////////////////////////////////////////////
//函数说明：
//    关闭设备
//Add by wanxin
//20140821
//////////////////////////////////////////////////////////////
DWORD COpR181::CloseDevice()
{
	DWORD   dwErrorCode;
	dwErrorCode = m_DevComHandle.CloseDevice();
	if (dwErrorCode!=SUCCESS)
	{
		return dwErrorCode;
	}
	return dwErrorCode;
}
/////////////////////////////////////////////////////////////
//函数说明：
//    设置设备句柄指针
//Add by wanxin
//20140821
//////////////////////////////////////////////////////////////
DWORD COpR181::SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle)
{
	DWORD   dwErrorCode=0;
//	LPCTSTR lpCommunicationInfo;
    
	dwErrorCode = m_DevComHandle.SetDeviceHandle(pszDeviceAddr, handle);
	return dwErrorCode;
}

/////////////////////////////////////////////////////////////
//函数说明：
//    重置设备
//Add by wanxin
//20140821
//////////////////////////////////////////////////////////////
DWORD COpR181::ResetDevice()
{
	DWORD dwErrorCode = FALSE;
	try
	{
		dwErrorCode = SetMotorZero(PolaNum);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_RESET;
		}
		dwErrorCode = SetMotorZero(QuatNum);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_RESET;
		}
		dwErrorCode = SetMotorZero(HalfNum);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_RESET;
		}
	}
	catch(DWORD dwError)
	{
		return ERROR_PDLD | dwError;
	}
	catch(...)
	{
		return ERROR_PDLD|UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}
/////////////////////////////////////////////////////////////
//函数说明：
//    获得设备信息
//Add by wanxin
//20140821
//////////////////////////////////////////////////////////////
DWORD COpR181::GetDeviceInfo(stDevInfo *stInfo)
{
	DWORD dwErrorCode = FALSE;
	try
	{
//		dwErrorCode = m_DevComHandle.WriteDevice("*IDN?\r\n",strlen("*IDN?\r\n"));
//		if(SUCCESS != dwErrorCode)
//		{
//			throw dwErrorCode|ERROR_RESET;
//		}

	}
	catch(DWORD dwError)
	{
		return ERROR_PDLD | dwError;
	}
	catch(...)
	{
		return ERROR_PDLD|UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}
/////////////////////////////////////////////////////////////
//函数说明：
//    获得当前偏振角度
//Add by wanxin
//20140821
//////////////////////////////////////////////////////////////
DWORD  COpR181::GetCurrentPOSPolarizer(double * pdblAlphaP,double *pdblAlphaQ,double *pdblAlphaH)
{
	DWORD dwErrorCode = FALSE;
	try
	{	
		* pdblAlphaP = GetAngle(PolaNum) / 100.0;
		if (* pdblAlphaP ==ERROR_VALUE)
		{
			throw dwErrorCode|ERROR_PDL_GETPOS;
		}
		
		*pdblAlphaQ = GetAngle(QuatNum) / 100.0;
		if (*pdblAlphaQ ==ERROR_VALUE)
		{
			throw dwErrorCode|ERROR_PDL_GETPOS;
		}
		
		*pdblAlphaH = GetAngle(HalfNum) / 100.0;
		if (*pdblAlphaH ==ERROR_VALUE)
		{
			throw dwErrorCode|ERROR_PDL_GETPOS;
		}
		
	}
	catch(DWORD dwError)
	{
		return ERROR_PDLD | dwError;
	}
	catch(...)
	{
		return ERROR_PDLD|UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}
/////////////////////////////////////////////////////////////
//函数说明：
//    设置所有角度
//Add by wanxin
//20140821
//////////////////////////////////////////////////////////////
DWORD  COpR181::SetALL(double alphaP, double alphaQ, double alphaH)
{
	DWORD dwErrorCode = FALSE;
	try
	{
		dwErrorCode =SetToTargetAngle(PolaNum, (WORD) (alphaP*100));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PDL_SETANGLE;
		}
		dwErrorCode= SetToTargetAngle(QuatNum, (WORD) (alphaQ*100));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PDL_SETANGLE;
		}
		dwErrorCode = SetToTargetAngle(HalfNum, (WORD) (alphaH*100));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PDL_SETANGLE;
		}
	}
	catch(DWORD dwError)
	{
		return ERROR_PDLD | dwError;
	}
	catch(...)
	{
		return ERROR_PDLD|UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}


/////////////////////////////////////////////////////////////
//函数说明：
//    设置对角角度
//Add by wanxin
//20140821
//////////////////////////////////////////////////////////////
DWORD  COpR181::SetDiagonalAngles(double AlphaPMax, double Wavelength)
{
	DWORD dwErrorCode = FALSE;
	try
	{
		double alphaP,alphaQ,alphaH;
		if (!m_compensate.GetLinearDiagonalAngles(AlphaPMax,Wavelength,&alphaP,&alphaQ,&alphaH))
		{
			throw dwErrorCode|ERROR_PDL_SETANGLE;
		}	
		dwErrorCode = SetALL(alphaP,alphaQ,alphaH);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PDL_SETANGLE;
		}
	}
	catch(DWORD dwError)
	{
		return ERROR_PDLD | dwError;
	}
	catch(...)
	{
		return ERROR_PDLD|UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}
/////////////////////////////////////////////////////////////
//函数说明：
//    设置水平角度
//Add by wanxin
//20140821
//////////////////////////////////////////////////////////////
DWORD  COpR181::SetHorizontalAngles(double AlphaPMax, double Wavelength)
{
	DWORD dwErrorCode = FALSE;
	try
	{
		double alphaP,alphaQ,alphaH;
		if (!m_compensate.GetLinearHorizontalAngles(AlphaPMax,Wavelength,&alphaP,&alphaQ,&alphaH))
		{
			throw dwErrorCode|ERROR_PDL_SETANGLE;
		}	
		dwErrorCode = SetALL(alphaP,alphaQ,alphaH);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PDL_SETANGLE;
		}
	}
	catch(DWORD dwError)
	{
		return ERROR_PDLD | dwError;
	}
	catch(...)
	{
		return ERROR_PDLD|UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}
/////////////////////////////////////////////////////////////
//函数说明：
//    设置1/2角度
//Add by wanxin
//20140821
//////////////////////////////////////////////////////////////
DWORD  COpR181::SetPOSHalf(double alpha)
{
	DWORD dwErrorCode = FALSE;
	try
	{
		dwErrorCode = SetToTargetAngle(HalfNum, (WORD) (alpha*100));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PDL_SETANGLE;
		}
	}
	catch(DWORD dwError)
	{
		return ERROR_PDLD | dwError;
	}
	catch(...)
	{
		return ERROR_PDLD|UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

/////////////////////////////////////////////////////////////
//函数说明：
//    设置起偏角度
//Add by wanxin
//20140821
//////////////////////////////////////////////////////////////
DWORD  COpR181::SetPOSPolarizer(double alpha)
{
	DWORD dwErrorCode = FALSE;
	try
	{
		dwErrorCode = SetToTargetAngle(PolaNum, (WORD) (alpha*100));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PDL_SETANGLE;
		}
	}
	catch(DWORD dwError)
	{
		return ERROR_PDLD | dwError;
	}
	catch(...)
	{
		return ERROR_PDLD|UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}
/////////////////////////////////////////////////////////////
//函数说明：
//    设置1/4角度
//Add by wanxin
//20140821
//////////////////////////////////////////////////////////////
DWORD  COpR181::SetPOSQuarter(double alpha)
{
	DWORD dwErrorCode = FALSE;
	try
	{
		dwErrorCode = SetToTargetAngle(QuatNum, (WORD) (alpha*100));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PDL_SETANGLE;
		}
	}
	catch(DWORD dwError)
	{
		return ERROR_PDLD | dwError;
	}
	catch(...)
	{
		return ERROR_PDLD|UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}
/////////////////////////////////////////////////////////////
//函数说明：
//    设置右旋角度
//Add by wanxin
//20140821
//////////////////////////////////////////////////////////////
DWORD  COpR181::SetRightHandCircularAngles(double AlphaPMax, double Wavelength)
{
	DWORD dwErrorCode = FALSE;
	try
	{
		double alphaP,alphaQ,alphaH;
		if (!m_compensate.GetLinearRightHandCircularAngles(AlphaPMax,Wavelength,&alphaP,&alphaQ,&alphaH))
		{
			throw dwErrorCode|ERROR_PDL_SETANGLE;
		}	
		dwErrorCode = SetALL(alphaP,alphaQ,alphaH);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PDL_SETANGLE;
		}
	}
	catch(DWORD dwError)
	{
		return ERROR_PDLD | dwError;
	}
	catch(...)
	{
		return ERROR_PDLD|UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}
/////////////////////////////////////////////////////////////
//函数说明：
//    设置垂直角度
//Add by wanxin
//20140821
//////////////////////////////////////////////////////////////
DWORD  COpR181::SetVerticalAngles(double AlphaPMax, double Wavelength)
{
	DWORD dwErrorCode = FALSE;
	try
	{
		double alphaP,alphaQ,alphaH;
		if (!m_compensate.GetLinearVerticalAngles(AlphaPMax,Wavelength,&alphaP,&alphaQ,&alphaH))
		{
			throw dwErrorCode|ERROR_PDL_SETANGLE;
		}	
		dwErrorCode = SetALL(alphaP,alphaQ,alphaH);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PDL_SETANGLE;
		}
	}
	catch(DWORD dwError)
	{
		return ERROR_PDLD | dwError;
	}
	catch(...)
	{
		return ERROR_PDLD|UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}
