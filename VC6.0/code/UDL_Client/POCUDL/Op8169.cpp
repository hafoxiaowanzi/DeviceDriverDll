// Op8169.cpp: implementation of the Op8169 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\\include\\PolDll.h"
#include "math.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COp8169::COp8169()
{

}

COp8169::~COp8169()
{

}
/////////////////////////////////////////////////////////////
//函数说明：
//    打开设备
//Add by wanxin
//20140821
//////////////////////////////////////////////////////////////
DWORD COp8169::OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle)
{
	//CString strComPort;	
	DWORD   dwErrorCode;

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
DWORD COp8169::CloseDevice()
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
DWORD COp8169::SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle)
{
	DWORD   dwErrorCode=0;
//	LPCTSTR lpCommunicationInfo;
    
	dwErrorCode = m_DevComHandle.SetDeviceHandle(pszDeviceAddr, handle);
	return dwErrorCode;
}
/////////////////////////////////////////////////////////////
//函数说明：
//    等待设备完成
//Add by wanxin
//20140821
//////////////////////////////////////////////////////////////
void COp8169::CompleteRequest()
{
	CHAR pszStatus[8];
	ZeroMemory(pszStatus,8);
	do
	{
		m_DevComHandle.WriteDevice("*OPC?\r\n", strlen("*OPC?\r\n"));
		Sleep(20);
		ZeroMemory(pszStatus,8);
		m_DevComHandle.ReadDevice(pszStatus, 8);
	}
	while(!strchr(pszStatus, '1'));
}
/////////////////////////////////////////////////////////////
//函数说明：
//    重置设备
//Add by wanxin
//20140821
//////////////////////////////////////////////////////////////
DWORD COp8169::ResetDevice()
{
	DWORD dwErrorCode = FALSE;
	try
	{
		dwErrorCode = m_DevComHandle.WriteDevice("*RST\r\n",strlen("*RST\r\n"));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_RESET;
		}
		CompleteRequest();
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
DWORD COp8169::GetDeviceInfo(stDevInfo *stInfo)
{
	DWORD dwErrorCode = FALSE;
	try
	{
		dwErrorCode = m_DevComHandle.WriteDevice("*IDN?\r\n",strlen("*IDN?\r\n"));
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
//    获得当前偏振角度
//Add by wanxin
//20140821
//////////////////////////////////////////////////////////////
DWORD  COp8169::GetCurrentPOSPolarizer(double * pdblAlphaP,double *pdblAlphaQ,double *pdblAlphaH )
{
	DWORD dwErrorCode = FALSE;
	char chReadBuf[100];
	try
	{
		dwErrorCode = m_DevComHandle.WriteDevice("POS:POL?\r\n",strlen("POS:POL?\r\n"));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PDL_GETPOS;
		}
		ZeroMemory(chReadBuf, sizeof(char)*100);
		dwErrorCode=m_DevComHandle.ReadDevice(chReadBuf,100);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW;
		}		
		*pdblAlphaP = atof(chReadBuf);	

		dwErrorCode = m_DevComHandle.WriteDevice("POS:QUAR?\r\n",strlen("POS:QUAR?\r\n"));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PDL_GETPOS;
		}
		ZeroMemory(chReadBuf, sizeof(char)*100);
		dwErrorCode=m_DevComHandle.ReadDevice(chReadBuf,100);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW;
		}		
		*pdblAlphaQ = atof(chReadBuf);	

		dwErrorCode = m_DevComHandle.WriteDevice("POS:HALF?\r\n",strlen("POS:HALF?\r\n"));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PDL_GETPOS;
		}
		ZeroMemory(chReadBuf, sizeof(char)*100);
		dwErrorCode=m_DevComHandle.ReadDevice(chReadBuf,100);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW;
		}		
		*pdblAlphaH = atof(chReadBuf);	

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
DWORD  COp8169::SetALL(double alphaP, double alphaQ, double alphaH)
{
	DWORD dwErrorCode = FALSE;
	char chReadBuf[MAX_PATH];
	try
	{
		ZeroMemory(chReadBuf, sizeof(char)*MAX_PATH);
		sprintf(chReadBuf,"POS:POL %8.2f;:POS:QUARTER %8.2f;:POS:HALF %8.2f\r\n",alphaP,alphaQ,alphaH);
		dwErrorCode = m_DevComHandle.WriteDevice(chReadBuf,strlen(chReadBuf));
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
DWORD  COp8169::SetDiagonalAngles(double AlphaPMax, double Wavelength)
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
DWORD  COp8169::SetHorizontalAngles(double AlphaPMax, double Wavelength)
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
DWORD  COp8169::SetPOSHalf(double alpha)
{
	DWORD dwErrorCode = FALSE;
	char chReadBuf[MAX_PATH];
	try
	{
		ZeroMemory(chReadBuf, sizeof(char)*MAX_PATH);
		sprintf(chReadBuf,"POS:HALF %8.2f\r\n" ,alpha);
		dwErrorCode = m_DevComHandle.WriteDevice(chReadBuf,strlen(chReadBuf));
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
DWORD  COp8169::SetPOSPolarizer(double alpha)
{
	DWORD dwErrorCode = FALSE;
	char chReadBuf[MAX_PATH];
	try
	{
		ZeroMemory(chReadBuf, sizeof(char)*MAX_PATH);
		sprintf(chReadBuf,"POS:POL %8.2f\r\n" ,alpha);
		dwErrorCode = m_DevComHandle.WriteDevice(chReadBuf,strlen(chReadBuf));
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
DWORD  COp8169::SetPOSQuarter(double alpha)
{
	DWORD dwErrorCode = FALSE;
	char chReadBuf[MAX_PATH];
	try
	{
		ZeroMemory(chReadBuf, sizeof(char)*MAX_PATH);
		sprintf(chReadBuf,"POS:QUAR %8.2f\r\n" ,alpha);
		dwErrorCode = m_DevComHandle.WriteDevice(chReadBuf,strlen(chReadBuf));
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
DWORD  COp8169::SetRightHandCircularAngles(double AlphaPMax, double Wavelength)
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
DWORD  COp8169::SetVerticalAngles(double AlphaPMax, double Wavelength)
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
