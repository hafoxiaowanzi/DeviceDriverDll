// OplinkPM.cpp: implementation of the OplinkPM class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\\include\\PM.h"
//#include <WINSOCK.H>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
OplinkPM::OplinkPM()
{

}

OplinkPM::~OplinkPM()
{

}
/***********************************************************************
*  函数名称:OpenDevice                                                 *
*  功能: 打开设备													   *
*  输入:                                                               *
*       1、pszDeviceAddr: 包含了设备地址，连接方式等信息。例如：	   *
*  输入数据类型:DWORD                                                  *
*  输出:                                                               *
*       ComHandle:输出Handle，用于识别不同 设备                        *
*  输出数据类型:unsigned long                                          *
*  返回值:                                                             *
*        错误码                                                        *
*  返回值类型:DWORD                                                    *
*  创建日期:2013-10-17                                                 *
*  创建人:yanx                                                         *
*  修改历史:无                                                         *
************************************************************************/
DWORD OplinkPM::OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle)
{
	DWORD dwErrorCode;
//	WORD wAddr;
	TCHAR szBuf[MAX_PATH]={0};
	try
	{
		dwErrorCode=m_Comm.OpenDevice(pszDeviceAddr, *ComHandle);
	}
	catch(...)
	{
		return UNEXPECT_OCCUR;
	}

	return dwErrorCode;	
}
/***********************************************************************
*  函数名称:SetWavelength											   *
*  功能: 设置波长   										           * 
*  输入:															   *
*	1、iChan:通道号													   *
*	2、dblWL:波长(nm)										           *
*	输入数据类型:int,double											   *
*  输出: 无															   *
*  输出类型:无														   *
*  返回值:                                                             *
*        错误码                                                        *
*  返回值类型:DWORD                                                    *
*  创建日期:2013-10-17                                                 *
*  创建人:yanx                                                         *
*  修改历史:无                                                         *
************************************************************************/
DWORD OplinkPM::SetWavelength(long lSlot,long IChan, double dblWL)
{
	DWORD dwErrorCode;
	CHAR pchCmd[MAX_PATH];
	CHAR chReadBuf[MAX_PATH];
	long lTempWL;
	long lWL;
	long iPMSlot;
	long iPMChannel;

    try
	{
	   iPMSlot=(IChan-1)/2;
	   iPMChannel=(IChan-1)%2;
		if(dblWL<850)
		{
			dblWL=850;
		}
		else if(dblWL>1640)
		{
			dblWL=1640;
		}
		lWL=(long)(dblWL*10000);

		ZeroMemory(pchCmd, MAX_PATH);
		sprintf(pchCmd, "SENS%d,CHAN%d:POW:WAV %dnm\r\n", lSlot, IChan, lWL);
		dwErrorCode=m_Comm.WriteDevice(pchCmd,strlen(pchCmd));
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_WL;
		}

		Sleep(100);

		ZeroMemory(pchCmd, MAX_PATH);
		sprintf(pchCmd, "SENS%d,CHAN%d:POW:WAV?\r\n", lSlot, IChan);
		dwErrorCode=m_Comm.WriteDevice(pchCmd,strlen(pchCmd));
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_WL;
		}
		Sleep(100);
		ZeroMemory(chReadBuf, MAX_PATH);
		dwErrorCode=m_Comm.ReadDevice(chReadBuf,MAX_PATH);
		
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_WL;
		}

		lTempWL = atol(chReadBuf);

		lTempWL = (long)(lTempWL + 0.5);

		if(lTempWL != lWL)
		{
			return FALSE;
		}
	}
	catch(...)
	{
		return UNEXPECT_OCCUR;
	}

	return dwErrorCode;	
}

/***********************************************************************
*  函数名称:GetPower												   *
*  功能: 读取功率													   *
*  输入:															   *
*	1、iChan:通道号									 			       *
*	输入数据类型:long                                                   *
*  输出: pdblPower                                                     *
*  输出类型：double*												   *
*  返回值:                                                             *
*        错误码                                                        *
*  返回值类型:DWORD                                                    *
*  创建日期:2013-10-17                                                 *
*  创建人:yanx                                                         *
*  修改历史:无                                                         *
************************************************************************/
DWORD OplinkPM::GetPower(long lSlot,long IChan, double *pdblPower)
{
	TCHAR pchCmd[MAX_PATH];

	TCHAR chReadBuf[MAX_PATH];

	DWORD dwErrorCode;

    try
	{
		ZeroMemory(pchCmd, MAX_PATH);
		sprintf(pchCmd, "SENS%d,CHAN%d:POW:READ?\r\n", lSlot, IChan);
		dwErrorCode=m_Comm.WriteDevice(pchCmd,strlen(pchCmd));
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_PM;
		}
		Sleep(100);
		ZeroMemory(chReadBuf, MAX_PATH);
		dwErrorCode=m_Comm.ReadDevice(chReadBuf,MAX_PATH);
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_PW;
		}
		*pdblPower=atof(chReadBuf);

	}
//	catch (char*strMsg)
//	{
//		return UNEXPECT_OCCUR;
//	}
	catch(...)
	{
		return UNEXPECT_OCCUR;
	}
	
	return dwErrorCode;
}
/***********************************************************************
*  函数名称:GetDeviceInfo											   *
*  备注:该PM此功能尚未开通                                             *
************************************************************************/
DWORD OplinkPM::GetUnit(long lSlot,long IChan, long *piUnit)
{
	DWORD dwErrorCode=0;

	*piUnit=0;
	
	return dwErrorCode;
}
/***********************************************************************
*  函数名称:GetDeviceInfo											   *
*  备注:该PM此功能尚未开通                                             *
************************************************************************/
DWORD OplinkPM::GetAverageTime(long lSlot,long IChan, double *pdblAverageTime)
{
	DWORD dwErrorCode=0;

	*pdblAverageTime=0;
	
	return dwErrorCode;
}
/***********************************************************************
*  函数名称:GetDeviceInfo											   *
*  备注:该PM此功能尚未开通                                             *
************************************************************************/
DWORD OplinkPM::GetRangeMode(long lSlot,long IChan,  long* iPWMRangeMode)
{
	DWORD dwErrorCode=0;

	*iPWMRangeMode=0;
	
	return dwErrorCode;
}
/***********************************************************************
*  函数名称:GetWavelength											   *
*  功能: 读取波长    										    	   *
*  输入:															   *
*	1、IChan:通道号													   *
*	输入数据类型:int												   *
*  输出: pdblWL(波长，单位nm)							     		   *
*  输出类型:double													   *
*  返回值:                                                             *
*        错误码                                                        *
*  返回值类型:DWORD                                                    *
*  创建日期:2013-10-17                                                 *
*  创建人:yanx                                                         *
*  修改历史:无                                                         *
************************************************************************/
DWORD OplinkPM::GetWavelength(long lSlot,long IChan, double *pdblWL)
{
	TCHAR pchCmd[MAX_PATH];

	TCHAR chReadBuf[MAX_PATH];

	DWORD dwErrorCode;


    try
	{
		ZeroMemory(pchCmd, MAX_PATH);
		sprintf(pchCmd, "SENS%d,CHAN%d:POW:READ?", lSlot, IChan);
		dwErrorCode=m_Comm.WriteDevice(pchCmd,strlen(pchCmd));
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_PM;
		}
		Sleep(100);
		dwErrorCode=m_Comm.ReadDevice(chReadBuf,MAX_PATH);
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_PW;
		}
		*pdblWL=(double)(atol(chReadBuf)/10000);

	}
//	catch (char*strMsg)
//	{
//		return UNEXPECT_OCCUR;
//	}
	catch(...)
	{
		return UNEXPECT_OCCUR;
	}
	
	return dwErrorCode;
}

/***********************************************************************
*  函数名称:SetCalibrate											   *
*  功能: 设置当前功率为0dBm（校准用）   							   * 
*  输入:															   *
*      IChan:通道													   *
*	输入数据类型:int												   *
*  输出: 无															   *
*  输出类型:无														   *
*  返回值:                                                             *
*        错误码                                                        *
*  返回值类型:DWORD                                                    *
*  创建日期:2013-10-17                                                 *
*  创建人:yanx                                                         *
*  修改历史:无                                                         *
************************************************************************/
DWORD OplinkPM::SetCalibrate(long lSlot,long IChan)
{
	char pchCmd[256];
//	char pchTemp[256];
//	char recvBuf[256];
//	WORD wSendLen;
	DWORD dwErrorCode;

    try
	{
		ZeroMemory(pchCmd, 256);
		sprintf(pchCmd, "SENS%d,CHAN%d:POW:SETCAL:00000000", lSlot, IChan);
		dwErrorCode=m_Comm.WriteDevice(pchCmd,strlen(pchCmd));
	}
	catch (...) {
		return UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

/***********************************************************************
*  函数名称:CloseDevice												   *
*  功能: 关闭设备   										           * 
*  输入:无															   *
*	输入数据类型:无													   *
*  输出: 无															   *
*  输出类型:无														   *
*  返回值:                                                             *
*        错误码                                                        *
*  返回值类型:DWORD                                                    *
*  创建日期:2013-10-17                                                 *
*  创建人:yanx                                                         *
*  修改历史:无                                                         *
************************************************************************/
DWORD OplinkPM::CloseDevice()
{
	DWORD dwErrorCode;
	dwErrorCode=m_Comm.CloseDevice();

	return dwErrorCode;
}
/***********************************************************************
*  函数名称:SetParameters											   *
*  功能: 设置参数   										           * 
*  输入:															   *
*	1.iChan:通道号													   *
*	2.bAutoRange:是否是自动模式									       *
*	3.dblWavelength:通道号											   *
*	4.dblAvgTile:平均时间									           *
*	5.dblPwrRange:动态范围(如果是手动)								   *
*	输入数据类型:int,BOOL,double,double,double						   *
*  输出: 无															   *
*  输出类型:无														   *
*  返回值:                                                             *
*        错误码                                                        *
*  返回值类型:DWORD                                                    *
*  创建日期:2013-10-17                                                 *
*  创建人:yanx                                                         *
*  修改历史:无                                                         *
************************************************************************/
DWORD OplinkPM::SetParameters(long lSlot,long IChan, BOOL bAutoRange,double dblWavelength, double dblAvgTime, double dblPwrRange)
{
	DWORD	dwErrorCode;
	try
	{
		// Set PWM Wavelength
		dwErrorCode=SetWavelength(lSlot,IChan, dblWavelength);

		if(dwErrorCode)
		{
			return dwErrorCode;
		}
		// Set PWM to a-uto-range
		dwErrorCode=SetRangeMode(lSlot,IChan, bAutoRange);
		if(dwErrorCode)
		{
			return dwErrorCode;
		}
		// Set PWM average time 1ms
		dwErrorCode=SetAverageTime(lSlot,IChan,dblAvgTime);
	}	
	catch(...)
	{
		return UNEXPECT_OCCUR;
	}

	return dwErrorCode;	
}
/***********************************************************************
*  函数名称:SetUnit											           *
*  备注:该PM此功能尚未开通                                             *
************************************************************************/
DWORD OplinkPM::SetUnit(long lSlot,long IChan,long lPWMUnit)
{
	DWORD dwErrorCode=0;
	return dwErrorCode;
}
/***********************************************************************
*  函数名称:SetAverageTime											           *
*  备注:该PM此功能尚未开通                                             *
************************************************************************/
DWORD OplinkPM::SetAverageTime(long lSlot,long IChan, double dblAvgTime)
{
	DWORD dwErrorCode=0;
	return dwErrorCode;
}
/***********************************************************************
*  函数名称:SetRangeMode											   *
*  备注:该PM此功能尚未开通                                             *
************************************************************************/
DWORD OplinkPM::SetRangeMode(long lSlot,long IChan, long bAutoRange)
{
	DWORD dwErrorCode=0;
	
	return dwErrorCode;
}
////////////////////////////////////////////////////////////
//函数说明：
//    设置功率计Range
//Add by wanxin
//Time:20140828
/////////////////////////////////////////////////////////////
DWORD OplinkPM::SetRange(long lSlot,long IChan, long lRange)
{
	DWORD dwErrorCode=SUCCESS;
	try
	{			
	
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}

/***********************************************************************
*  函数名称:Zero											           *
*  备注:该PM此功能尚未开通                                             *
************************************************************************/
DWORD OplinkPM::Zero(long lSlot,long IChan)
{
	DWORD dwErrorCode=0;
	return dwErrorCode;
}

/***********************************************************************
*  函数名称:GetDeviceInfo											   *
*  备注:该PM此功能尚未开通                                             *
************************************************************************/
DWORD OplinkPM::GetDeviceInfo(CHAR * pchInfo)
{
	DWORD dwErrorCode=0;
	return dwErrorCode;
}

DWORD OplinkPM::SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle)
{
	DWORD   dwErrorCode = SUCCESS;
    
	dwErrorCode = m_Comm.SetDeviceHandle(pszDeviceAddr, handle);
	return dwErrorCode;
}
DWORD OplinkPM::PrepareScan(long lSlot,long lChIndex,stScanParam* lScanParam)
{
	CString strTemp;
	char* token=NULL;
	char sep[]=",";
	int nCount=0;
	DWORD dwErrorCode =SUCCESS;
	
	try
	{

	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return UNEXPECT_OCCUR;
	}
	
	return dwErrorCode;		
}

DWORD OplinkPM::SetPMScanStart(long lSlot,long lChIndex)
{	
	DWORD dwErrorCode =SUCCESS;
	try
	{
		
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return UNEXPECT_OCCUR;
	}
	
	return dwErrorCode;	
}

DWORD OplinkPM::getLambdaScanPMResult(long lSlot,long lChIndex,double* pdbPMArry)
{
	DWORD dwErrorCode =SUCCESS;
	PBYTE pbyBuf=NULL;
	CString strTemp;
	try
	{
					
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return UNEXPECT_OCCUR;
	}
	
	if (pbyBuf)
	{
		delete [] pbyBuf ;
	}
	
	return dwErrorCode;		
}

DWORD OplinkPM::SetPMScanStop(long lSlot,long lChIndex)
{
	CString strTemp;
	DWORD dwErrorCode =SUCCESS;
	try
	{

	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return UNEXPECT_OCCUR;
	}
	return dwErrorCode;	
}


DWORD OplinkPM::SetPMScanTriggerStop(long lSlot,long lChIndex)
{
	CString strTemp;
	DWORD dwErrorCode =SUCCESS;
	try
	{

	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return UNEXPECT_OCCUR;
	}
	return dwErrorCode;	
}
///////////////////////////////////////////////////////////////////
//函数说明：
//    设置功率计为获得最大、最小功率模式，获得相应的最大、最小功率
//Add by wanxin
////////////////////////////////////////////////////////////////////////
DWORD OplinkPM::GetPMMaxMinPower(long lSlot,long IChan,double *pdbGetMax,double *pdbGetMin)
{
	//CString strTemp;
	char chReadBuf[100];
	DWORD dwErrorCode=0;
	try
	{			

	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
///////////////////////////////////////////////////////////////////
//函数说明：
//    设置功率计为获得最大、最小功率模式
//Add by wanxin
////////////////////////////////////////////////////////////////////////
DWORD OplinkPM::SetPMMaxMinPowerStart(long lSlot,long IChan)
{
	char chReadBuf[100];
	DWORD dwErrorCode=0;
	try
	{			

	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return UNEXPECT_OCCUR;
	}
	return dwErrorCode;	
}
DWORD OplinkPM::SetPMMinMaxStop(long lSlot,long IChan)
{
	char chReadBuf[100];
	DWORD dwErrorCode=0;
	try
	{			
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
DWORD OplinkPM::SetPMPowerOffset(long lSlot,long IChan,double dbPowerOffset)
{
	char chReadBuf[100];
	DWORD dwErrorCode=0;
	try
	{			
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}