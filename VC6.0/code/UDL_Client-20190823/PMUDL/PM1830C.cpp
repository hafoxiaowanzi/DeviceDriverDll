// PM1830C.cpp: implementation of the CPM1830C class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\\include\\PM.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPM1830C::CPM1830C()
{
}

CPM1830C::~CPM1830C()
{

}
/***********************************************************************
*  函数名称:GetPower												   *
*  功能: 读取功率													   *
*  输入:															   *
*	1、IChan:通道号									 			       *
*	输入数据类型:long                                                   *
*  输出: pdblPowerValue                                                *
*  输出类型：double												       *
*  返回值:                                                             *
*        错误码                                                        *
*  返回值类型:DWORD                                                    *
*  创建日期:2013-10-21                                                 *
*  创建人:ris                                                          *
*  修改历史:无                                                         *
************************************************************************/
DWORD CPM1830C::GetPower(long lSlot,long IChan, double* pdblPowerValue)
{
//	CString	strSend;
	WORD wIndex = 0;
	char	chRet[256];
	BOOL bSuc = FALSE;
	DWORD dwErrorCode;
	char strSend[MAX_PATH];
	ZeroMemory(strSend, sizeof(strSend));
	sprintf(strSend, "%s", "D?\r");

	for (long iLoop = 0; iLoop < 10; iLoop++) 
	{
		dwErrorCode = m_DevComHandle.WriteDevice((char*)strSend,strlen(strSend));
		if (dwErrorCode!=SUCCESS)
		{
			continue;
		}
		ZeroMemory(chRet, 256);
		dwErrorCode = m_DevComHandle.ReadDevice((char*)chRet, 256);
		if (dwErrorCode==SUCCESS)
		{
			bSuc =TRUE;
			break;
		}
	}
	
	if (!bSuc) 
	{
		return ERROR_PW|dwErrorCode;
	}

	*pdblPowerValue = atof(chRet);

	return dwErrorCode;
}
/***********************************************************************
*  函数名称:SetWavelength											   *
*  功能: 设置波长   										           * 
*  输入:															   *
*	1、IChan:通道号													   *
*	2、dblWavelength:波长(nm)										   *
*	输入数据类型:int,double											   *
*  输出: 无															   *
*  输出类型:无														   *
*  返回值:                                                             *
*        错误码                                                        *
*  返回值类型:DWORD                                                    *
*  创建日期:2013-10-21                                                 *
*  创建人:ris                                                          *
*  修改历史:无                                                         *
************************************************************************/
DWORD CPM1830C::SetWavelength(long lSlot,long IChan,double dblWavelength)
{
	//CString	strSend;
	DWORD   dwErrorCode;
	char strSend[MAX_PATH];
	ZeroMemory(strSend, sizeof(strSend));
	sprintf(strSend, "w%.0f\r", dblWavelength);
	dwErrorCode = m_DevComHandle.WriteDevice(strSend,strlen(strSend));
	if (dwErrorCode!=SUCCESS)
		return ERROR_WL|dwErrorCode;
	
	Sleep(2000);
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
*  创建人:ris                                                          *
*  修改历史:无                                                         *
************************************************************************/
DWORD CPM1830C::GetWavelength(long lSlot,long IChan,double *pdblWL)
{
	//CString	strSend;
	DWORD   dwErrorCode;
	char strSend[MAX_PATH];
	ZeroMemory(strSend, sizeof(strSend));
	sprintf(strSend, "%s", "W?\r");
	//strSend.Format("W?\r");

	dwErrorCode = m_DevComHandle.WriteDevice(strSend,strlen(strSend));
	if (dwErrorCode != SUCCESS)
		return dwErrorCode|ERROR_WL;
	
	char chRet[256];
	ZeroMemory(chRet, 256 * sizeof(char));
	dwErrorCode = m_DevComHandle.ReadDevice((char*)chRet, 256);
	if (dwErrorCode != SUCCESS)
		return dwErrorCode|ERROR_WL;

	*pdblWL = atof(chRet);

	return dwErrorCode;
}
/***********************************************************************
*  函数名称:SetRangeMode											   *
*  功能: 设置动态范围    											   *
*  输入:															   *
*	1、IChan:通道号													   *
*   2、	bAtuo:模式(1:自动;其他值:手动设置档位值,0为1档位)              *
*	输入数据类型:int,int											   *
*  输出: 无															   *
*  输出类型:无													       *
*  返回值:                                                             *
*        错误码                                                        *
*  返回值类型:DWORD                                                    *
*  创建日期:2013-10-17                                                 *
*  创建人:ris                                                          *
*  修改历史:无                                                         *
************************************************************************/
DWORD CPM1830C::SetRangeMode(long lSlot,long IChan, long bAtuo)
{
	//CString	strSend;
	DWORD   dwErrorCode = SUCCESS;
	BOOL bAuto;

	if((bAtuo<0)||(bAtuo>8))
		return ERROR_RANGE_MODE|dwErrorCode;
	if(bAtuo==1)
	{
		bAuto=0;
	}
	else if(bAtuo==0)
	{
		bAuto=1;
	}
	else
	{
		bAuto=bAtuo;
	}

	char strSend[MAX_PATH];
	ZeroMemory(strSend, sizeof(strSend));
	sprintf(strSend, "R%d\r", bAuto);

	dwErrorCode = m_DevComHandle.WriteDevice(strSend,strlen(strSend));
	if (dwErrorCode != dwErrorCode)
		return ERROR_RANGE_MODE|dwErrorCode;
	
	return dwErrorCode;
}

////////////////////////////////////////////////////////////
//函数说明：
//    设置功率计Range
//Add by wanxin
//Time:20140828
/////////////////////////////////////////////////////////////
DWORD CPM1830C::SetRange(long lSlot,long IChan, long lRange)
{
	DWORD dwErrorCode=SUCCESS;
	TCHAR	szCmdString[MAX_PATH];
	try
	{			
		if (lRange <0 || lRange >8)
		{
			throw dwErrorCode|ERROR_OUT_RANGE;
		}			
		
		ZeroMemory(szCmdString, sizeof(szCmdString));
		sprintf(szCmdString, "R%d\r", lRange);
		
		dwErrorCode = m_DevComHandle.WriteDevice(szCmdString,strlen(szCmdString));

		if (dwErrorCode!=SUCCESS)
		{
			throw  ERROR_PW_RANGE|dwErrorCode;
		}		
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
*  函数名称:GetRangeMode											   *
*  功能: 读取动态范围   										       *
*  输入:															   *
*	1、iChan:通道号													   *
*	输入数据类型:int												   *
*  输出: iPWMRangeMode	(1:自动;其他值:手动设置档位值,0为1档位)		   *
*  输出类型:int													       *
*  返回值:                                                             *
*        错误码                                                        *
*  返回值类型:DWORD                                                    *
*  创建日期:2013-10-17                                                 *
*  创建人:ris                                                         *
*  修改历史:无                                                         *
************************************************************************/
DWORD CPM1830C::GetRangeMode(long lSlot,long IChan, long* iPWMRangeMode)
{
	//CString	strSend;
	DWORD   dwErrorCode;
	char strSend[MAX_PATH];
	ZeroMemory(strSend, sizeof(strSend));
	sprintf(strSend, "%s", "R?\r");
//	strSend.Format("R?\r");

	dwErrorCode = m_DevComHandle.WriteDevice(strSend,strlen(strSend));
	if (dwErrorCode != SUCCESS)
		return ERROR_RANGE_MODE|dwErrorCode;
	
	char	chRet[256];
	ZeroMemory(chRet, 256 * sizeof(char));
	dwErrorCode = m_DevComHandle.ReadDevice((char*)chRet, 256);
	if (dwErrorCode != SUCCESS)
		return ERROR_RANGE_MODE|dwErrorCode;

	if(atoi(chRet)==0)
	{
		*iPWMRangeMode=1;
	}
	else if(atoi(chRet)==1)
	{
		*iPWMRangeMode=0;
	}
	else
	{
		*iPWMRangeMode = atoi(chRet);
	}

	return dwErrorCode;
}
/***********************************************************************
*  函数名称:SetUnit											           *
*  功能: 设置单位    										    	   *
*  输入:															   *
*	1、IChan:通道号													   *
*   2、	lPWMUnit:单位。0:dBm;1:mw;2:dB;3:dBm;4:Ref					   *
*	输入数据类型:int,int											   *
*  输出: 无															   *
*  输出类型:无													       *
*  返回值:                                                             *
*        错误码                                                        *
*  返回值类型:DWORD                                                    *
*  创建日期:2013-10-17                                                 *
*  创建人:ris                                                          *
*  修改历史:无                                                         *
************************************************************************/
DWORD CPM1830C::SetUnit(long lSlot,long IChan,long lPWMUnit)
{
	//CString	strSend;
	DWORD   dwErrorCode;

	if(lPWMUnit==0)
	{
		lPWMUnit=3;
	}
	char strSend[MAX_PATH];
	ZeroMemory(strSend, sizeof(strSend));
	sprintf(strSend, "U%d\r", lPWMUnit);
//	strSend.Format("U%d\r", lPWMUnit);

	dwErrorCode = m_DevComHandle.WriteDevice(strSend,strlen(strSend));

	if (dwErrorCode != SUCCESS)
		return ERROR_UNIT|dwErrorCode;
	
	return dwErrorCode;
}
/***********************************************************************
*  函数名称:GetUnit											           *
*  功能: 读取单位    										    	   *
*  输入:															   *
*	1、IChan:通道号													   *
*	输入数据类型:int												   *
*  输出: piUnit(0表示dBm，1表示w,2表示dB,4表示Ref)				     *
*  输出类型:int													       *
*  返回值:                                                             *
*        错误码                                                        *
*  返回值类型:DWORD                                                    *
*  创建日期:2013-10-17                                                 *
*  创建人:ris                                                          *
*  修改历史:无                                                         *
************************************************************************/
DWORD CPM1830C::GetUnit(long lSlot,long IChan, long* piUnit)
{
	//CString	strSend;
	DWORD   dwErrorCode;
	char strSend[MAX_PATH];
	ZeroMemory(strSend, sizeof(strSend));
	sprintf(strSend, "%s", "U?\r");
	//strSend.Format("U?\r");

	dwErrorCode = m_DevComHandle.WriteDevice(strSend,strlen(strSend));

	if (dwErrorCode != SUCCESS)
		return ERROR_UNIT|dwErrorCode;
	
	char	chRet[256];
	ZeroMemory(chRet, 256 * sizeof(char));
	dwErrorCode = m_DevComHandle.ReadDevice((char*)chRet, 256);
	if (dwErrorCode != SUCCESS)
		return ERROR_UNIT|dwErrorCode;

	if(atoi(chRet)==3)
	{
		*piUnit =0;
	}
	else
	{
		*piUnit = atoi(chRet);
	}
	return dwErrorCode;
} 
/***********************************************************************
*  函数名称:GetAverageTime											   *
*  功能: 读取平均时间    										       *
*  输入:															   *
*	1、iChan:通道号													   *
*	输入数据类型:int												   *
*  输出: pdblAverageTime(1=Slow; 2=medium; 3=fast)					   *
*  输出类型:double													   *
*  返回值:                                                             *
*        错误码                                                        *
*  返回值类型:DWORD                                                    *
*  创建日期:2013-10-17                                                 *
*  创建人:ris                                                          *
*  修改历史:无                                                         *
************************************************************************/
DWORD CPM1830C::SetAverageTime(long lSlot,long IChan, double dblAvgTime)
{
	//CString	strSend;
	DWORD   dwErrorCode;
	char strSend[MAX_PATH];
	ZeroMemory(strSend, sizeof(strSend));
	sprintf(strSend, "F%.0f\r", dblAvgTime);
//	strSend.Format("F%.0f\r", dblAvgTime);
    dwErrorCode = m_DevComHandle.WriteDevice(strSend,strlen(strSend));
	if (dwErrorCode!=SUCCESS)
		return dwErrorCode|ERROR_AVERIAGE_TIME;
	
	return dwErrorCode;
}
/***********************************************************************
*  函数名称:GetAverageTime											   *
*  功能: 读取平均时间    										       *
*  输入:															   *
*	1、IChan:通道号													   *
*	输入数据类型:int												   *
*  输出: pdblAverageTime(1=Slow; 2=medium; 3=fast)					   *
*  输出类型:double													   *
*  返回值:                                                             *
*        错误码                                                        *
*  返回值类型:DWORD                                                    *
*  创建日期:2013-10-21                                                 *
*  创建人:ris                                                          *
*  修改历史:无                                                         *
************************************************************************/
DWORD CPM1830C::GetAverageTime(long lSlot,long IChan, double* pdblAverageTime)
{
	//CString	strSend;
	DWORD   dwErrorCode;
	char strSend[MAX_PATH];
	ZeroMemory(strSend, sizeof(strSend));
	sprintf(strSend, "%s", "F?\r");
//	strSend.Format("F?\r");

	dwErrorCode = m_DevComHandle.WriteDevice(strSend,strlen(strSend));
	if (dwErrorCode!=SUCCESS)
		return dwErrorCode|ERROR_AVERIAGE_TIME;
	
	char	chRet[256];
	ZeroMemory(chRet, 256 * sizeof(char));
	dwErrorCode = m_DevComHandle.ReadDevice((char*)chRet, 256);
	if (dwErrorCode!=SUCCESS)
		return dwErrorCode|ERROR_AVERIAGE_TIME;

	*pdblAverageTime = atof(chRet);

	return dwErrorCode;
}
/***********************************************************************
*  函数名称:SetEcho      											   *
*  功能:                										       *
*  输入:															   *
*	1、bEchoOff:通道号												   *
*	输入数据类型:BOOL												   *
*  输出: 无															   *
*  输出类型:无													       *
*  返回值:                                                             *
*        TRUE:成功;FALSE:失败                                          *
*  返回值类型:DWORD                                                    *
*  创建日期:2013-10-21                                                 *
*  创建人:ris                                                          *
*  修改历史:无                                                         *
************************************************************************/
BOOL CPM1830C::SetEcho(BOOL bEchoOff)
{
	//CString	strSend;
	char strSend[MAX_PATH];
	ZeroMemory(strSend, sizeof(strSend));
	
	if (bEchoOff)
		sprintf(strSend, "%s", "E0\r");
//		strSend = "E0\r";
	else
		sprintf(strSend, "%s", "E1\r");
//		strSend = "E1\r";

	if (!m_DevComHandle.WriteDevice(strSend,strlen(strSend)))
		return FALSE;

	return TRUE;
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
*  创建日期:2013-10-21                                                 *
*  创建人:ris                                                          *
*  修改历史:无                                                         *
************************************************************************/
DWORD CPM1830C::CloseDevice()
{
	DWORD   dwErrorCode;
	dwErrorCode = m_DevComHandle.CloseDevice();
	if (dwErrorCode!=SUCCESS)
	{
		return dwErrorCode;
	}
	return dwErrorCode;
}
/***********************************************************************
*  函数名称:SetStoRef      											   *
*  功能:                										       *
*  输入:无															   *
*	输入数据类型:无  												   *
*  输出: 无															   *
*  输出类型:无													       *
*  返回值:                                                             *
*        TRUE:成功;FALSE:失败                                          *
*  返回值类型:DWORD                                                    *
*  创建日期:2013-10-21                                                 *
*  创建人:ris                                                          *
*  修改历史:无                                                         *
************************************************************************/
BOOL CPM1830C::SetStoRef()
{
	if(!SetUnit(1,1,2))
	{
		return FALSE;
	}
	//CString	strSend;
	char strSend[MAX_PATH];
	ZeroMemory(strSend, sizeof(strSend));
	sprintf(strSend, "%s", "S\r");
//	strSend.Format("S\r");

	if (!m_DevComHandle.WriteDevice(strSend,strlen(strSend)))
		return FALSE;

	return TRUE;
}
/***********************************************************************
*  函数名称:Zero													   *
*  功能: 对探头进行清零   										       * 
*  输入:无															   *
*	输入数据类型:无													   *
*  输出: 无															   *
*  输出类型:无														   *
*  返回值:                                                             *
*        错误码                                                        *
*  返回值类型:DWORD                                                    *
*  创建日期:2013-10-21                                                 *
*  创建人:ris                                                          *
*  修改历史:无                                                         *
************************************************************************/
DWORD CPM1830C::Zero(long lSlot,long IChan)   
{
	//CString	strSend;
	DWORD   dwErrorCode;
	char strSend[MAX_PATH];
	ZeroMemory(strSend, sizeof(strSend));
	sprintf(strSend, "%s", "Z1\r");
//	strSend.Format("Z1\r");
	dwErrorCode = m_DevComHandle.WriteDevice(strSend,strlen(strSend));
	
	return dwErrorCode;	
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
*  创建日期:2013-10-21                                                 *
*  创建人:ris                                                         *
*  修改历史:无                                                         *
************************************************************************/
DWORD CPM1830C::OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle)
{
	//CString strComPort;	
	DWORD   dwErrorCode;

	dwErrorCode = m_DevComHandle.OpenDevice(pszDeviceAddr,*ComHandle);
	
	return dwErrorCode;
}
/***********************************************************************
*  函数名称:SetParameters											   *
*  功能: 设置参数   										           * 
*  输入:															   *
*	1.IChan:通道号													   *
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
*  创建日期:2013-10-21                                                 *
*  创建人:ris                                                        *
*  修改历史:无                                                         *
************************************************************************/
DWORD CPM1830C::SetParameters(long lSlot,long IChan, BOOL bAutoRange, double dblWavelength, double dblAvgTile, double dblPwrRange)
{
	//CString strTemp;
	DWORD   dwErrorCode;
	dwErrorCode = SetRangeMode(lSlot,IChan,bAutoRange);
	if (dwErrorCode!=SUCCESS)
	{
		return dwErrorCode;
	}

//    long nTime= (int)dblAvgTile;
	dwErrorCode = SetAverageTime(lSlot,IChan,dblAvgTile);
	if (dwErrorCode!=SUCCESS)
	{
		return dwErrorCode;
	}

//	long nWL=(int)dblWavelength;
	dwErrorCode = SetWavelength(lSlot,IChan,dblWavelength);
	if (dwErrorCode!=SUCCESS)
	{
		return dwErrorCode;
	}
	Sleep(2000);
	
	return SUCCESS;
}

/***********************************************************************
*  函数名称:SetUnit											           *
*  备注:此功能尚未开通                                             *
************************************************************************/
DWORD CPM1830C::SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle)
{
	DWORD   dwErrorCode = SUCCESS;
//	LPCTSTR lpCommunicationInfo;
    
	dwErrorCode = m_DevComHandle.SetDeviceHandle(pszDeviceAddr, handle);
	return dwErrorCode;
}

/***********************************************************************
*  函数名称:SetUnit											           *
*  备注:该PM此功能尚未开通                                             *
************************************************************************/
//DWORD CPM1830C::SetMode(long lChIndex,DWORD dwMode)
//{
//	DWORD dwErrorCode=0;
//	return dwErrorCode;
//}
/***********************************************************************
*  函数名称:SetUnit											           *
*  备注:该PM此功能尚未开通                                             *
************************************************************************/
//DWORD CPM1830C::GetMode(long lChIndex,DWORD &dwMode)
//{
//	DWORD dwErrorCode=0;
//	return dwErrorCode;
//}
/***********************************************************************
*  函数名称:SetUnit											           *
*  备注:该PM此功能尚未开通                                             *
************************************************************************/
DWORD CPM1830C::GetDeviceInfo(CHAR * pchInfo)
{
	DWORD dwErrorCode=0;
	return dwErrorCode;
}


DWORD CPM1830C::PrepareScan(long lSlot,long lChIndex,stScanParam* lScanParam)
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

DWORD CPM1830C::SetPMScanStart(long lSlot,long lChIndex)
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

DWORD CPM1830C::getLambdaScanPMResult(long lSlot,long lChIndex,double* pdbPMArry)
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

DWORD CPM1830C::SetPMScanStop(long lSlot,long lChIndex)
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


DWORD CPM1830C::SetPMScanTriggerStop(long lSlot,long lChIndex)
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
DWORD CPM1830C::GetPMMaxMinPower(long lSlot,long IChan,double *pdbGetMax,double *pdbGetMin)
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
DWORD CPM1830C::SetPMMaxMinPowerStart(long lSlot,long IChan)
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
DWORD CPM1830C::SetPMMinMaxStop(long lSlot,long IChan)
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
DWORD CPM1830C::SetPMPowerOffset(long lSlot,long IChan,double dbPowerOffset)
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