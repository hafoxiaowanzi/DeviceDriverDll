// Op8163A1.cpp: implementation of the COp8163A class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\\include\\PM.h"
#include "math.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COp8163A::COp8163A()
{
	
}

COp8163A::~COp8163A()
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
DWORD COp8163A::OpenDevice(LPCTSTR pszDeviceAddr, unsigned long *ComHandle)
{
	//	char szBuf[100];
	DWORD dwErrorCode = SUCCESS;
	
	try
	{
		dwErrorCode = m_Comm.OpenDevice(pszDeviceAddr, *ComHandle);
		if(!dwErrorCode)
		{
			//			sprintf(szBuf, "%s", "*RST\r\n");
			//			
			//			dwErrorCode=m_Comm.WriteDevice(szBuf);
			//			if(!dwErrorCode)
			//			{
			//				 //待用
			//			}
			//		
			//			dwErrorCode=CompleteQuery();
		}
	}
	catch (...)
	{
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
DWORD COp8163A::CloseDevice()
{
	DWORD dwErrorCode;
	dwErrorCode=m_Comm.CloseDevice();
	return dwErrorCode;
}


DWORD COp8163A::PrepareScan(long lSlot,long lChIndex,stScanParam* lScanParam)
{
	char szBuf[MAX_PATH];
	CString strTemp;
	char* token=NULL;
	char sep[]=",";
	int nCount=0;
	double dbWL;
	DWORD dwErrorCode =SUCCESS;
	int nCurSlot = lSlot;
	
	try
	{
		m_pScanParam = lScanParam;
		//激扫描点数
		m_dwScanPoint = (int)((m_pScanParam->m_dblStopWL - m_pScanParam->m_dblStartWL) / m_pScanParam->m_dblStepSize +0.5);	
		m_pScanParam->m_dwSampleCount = m_dwScanPoint;
		
		m_pScanParam->m_nAvgTime = (int)((1/m_pScanParam->m_nSpeed)*m_pScanParam->m_dblStepSize);
		
		dbWL = (m_pScanParam->m_dblStartWL+m_pScanParam->m_dblStopWL)/2;
		ZeroMemory(szBuf, sizeof(char)*MAX_PATH);
		sprintf(szBuf, "sens%d:pow:rang:auto?\r\n",nCurSlot);
		dwErrorCode=m_Comm.WriteDevice(szBuf,strlen(szBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PM_SCAN_PARPARE;
		}
		ZeroMemory(szBuf, sizeof(char)*MAX_PATH);
		dwErrorCode=m_Comm.ReadDevice(szBuf,MAX_PATH);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PM_SCAN_PARPARE;
		}
		int nRange= atoi(szBuf);
		if (nRange != 0)
		{
			ZeroMemory(szBuf, sizeof(char)*MAX_PATH);
			sprintf(szBuf, "sens%d:pow:rang:auto 0\r\n",nCurSlot);
			dwErrorCode=m_Comm.WriteDevice(szBuf,strlen(szBuf));
			if (SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_PM_SCAN_PARPARE;
			}
		}
		//设置AverageTime
		ZeroMemory(szBuf,sizeof(char)*MAX_PATH);
		sprintf(szBuf,"sens%d:pow:atim %dus\r\n",nCurSlot,m_pScanParam->m_nAvgTime);
		dwErrorCode=m_Comm.WriteDevice(szBuf,strlen(szBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PM_SCAN_PARPARE;
		}
		//设置功率计的波长
		ZeroMemory(szBuf, sizeof(char)*MAX_PATH);
		sprintf(szBuf, "sens%d:chan%d:pow:wav %.3fnm\r\n",nCurSlot,lChIndex,dbWL);
		dwErrorCode=m_Comm.WriteDevice(szBuf,strlen(szBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PM_SCAN_PARPARE;
		}
		//设置功率计为wm
		ZeroMemory(szBuf, sizeof(char)*MAX_PATH);
		sprintf(szBuf, "sens%d:chan%d:pow:unit 1\r\n",nCurSlot,lChIndex);
		dwErrorCode=m_Comm.WriteDevice(szBuf,strlen(szBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PM_SCAN_PARPARE;
		}
		//设置功率计trigger模式可用
		ZeroMemory(szBuf, sizeof(char)*MAX_PATH);
		sprintf(szBuf, "trig%d:inp sme\r\n",nCurSlot);
		dwErrorCode=m_Comm.WriteDevice(szBuf,strlen(szBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PM_SCAN_PARPARE;
		}				//设置功率计扫描点数
		ZeroMemory(szBuf, sizeof(char)*MAX_PATH);
		sprintf(szBuf, "sens%d:func:par:logg %d,%dus\r\n",nCurSlot,m_dwScanPoint,m_pScanParam->m_nAvgTime);
		dwErrorCode=m_Comm.WriteDevice(szBuf,strlen(szBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PM_SCAN_PARPARE;
		}
		ZeroMemory(szBuf, sizeof(char)*MAX_PATH);
		sprintf(szBuf, "sens%d:func:stat?\r\n",nCurSlot);
		dwErrorCode=m_Comm.WriteDevice(szBuf,strlen(szBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PM_SCAN_PARPARE;
		}
		ZeroMemory(szBuf, sizeof(char)*MAX_PATH);
		dwErrorCode=m_Comm.ReadDevice(szBuf,MAX_PATH);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PM_SCAN_PARPARE;
		}
		strTemp = szBuf;
		if (strTemp.Find("LOGGING_STABILITY,PROGRESS")==-1)
		{
			throw dwErrorCode|ERROR_PM_SCAN_PARPARE;
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

DWORD COp8163A::SetPMScanStart(long lSlot,long lChIndex)
{	
    char szBuf[MAX_PATH];
	DWORD dwErrorCode =SUCCESS;
	int nCurSlot = lSlot;
	try
	{
		ZeroMemory(szBuf,MAX_PATH);
		sprintf(szBuf,"sens%d:func:stat logg,star\r\n",nCurSlot);
		dwErrorCode=m_Comm.WriteDevice(szBuf,strlen(szBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PM_SCAN_PARPARE;
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

DWORD COp8163A::getLambdaScanPMResult(long lSlot,long lChIndex,double* pdbPMArry)
{
    char chReadBuf[MAX_PATH];
	DWORD dwErrorCode =SUCCESS;
	int nTempLen;
	PBYTE pbyBuf=NULL;
	float *pfPowerArray;
	float fPreTemp;
	double dbPMTemp;
	CString strTemp;
	int nCurSlot = lSlot;
	try
	{
		ZeroMemory(chReadBuf,sizeof(char)*MAX_PATH);
		sprintf(chReadBuf,"sens%d:func:stat?\r\n",nCurSlot);			
		dwErrorCode=m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PM_SCAN_RESULT;
		}
		ZeroMemory(chReadBuf,MAX_PATH*sizeof(char));	
		dwErrorCode=m_Comm.ReadDevice(chReadBuf,MAX_PATH);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PM_SCAN_RESULT;
		}
		strTemp = chReadBuf;
		if (strTemp.Find("LOGGING_STABILITY,COMPLETE")==-1) 
		{
			throw dwErrorCode|ERROR_PM_SCAN_RESULT;
		}
		ZeroMemory(chReadBuf,MAX_PATH*sizeof(char));
		sprintf(chReadBuf,"sens%d:chan%d:func:res?\r\n",nCurSlot,lChIndex);
		dwErrorCode=m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PM_SCAN_RESULT;
		}
		
		ZeroMemory(chReadBuf,MAX_PATH*sizeof(char));	
		dwErrorCode=m_Comm.ReadDevice(chReadBuf,2);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PM_SCAN_RESULT;
		}
		nTempLen = chReadBuf[1] - '0';		
		ZeroMemory(chReadBuf, MAX_PATH*sizeof(char));
		dwErrorCode=m_Comm.ReadDevice(chReadBuf,nTempLen);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PM_SCAN_RESULT;
		}
		nTempLen =atoi(chReadBuf);
		pbyBuf = new BYTE[nTempLen] ;	
		ZeroMemory(pbyBuf, sizeof(BYTE)*nTempLen);
								
		dwErrorCode=m_Comm.ReadDevice(chReadBuf,nTempLen);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PM_SCAN_RESULT;
		}
		pfPowerArray =(float*)pbyBuf;			
		
		ZeroMemory(chReadBuf,sizeof(char)*MAX_PATH);
		sprintf(chReadBuf,"sens%d:func:stat?\r\n",nCurSlot);
		
		dwErrorCode=m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PM_SCAN_RESULT;
		}
		ZeroMemory(chReadBuf,MAX_PATH*sizeof(char));	
		dwErrorCode=m_Comm.ReadDevice(chReadBuf,MAX_PATH);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PM_SCAN_RESULT;
		} 
		strTemp = chReadBuf;
		if (strTemp.Find("LOGGING_STABILITY,COMPLETE")==-1) 
		{
			throw dwErrorCode|ERROR_PM_SCAN_RESULT;
		}
		
		
		for (int nIndex=0;nIndex < nTempLen/4;nIndex ++)
		{			
			fPreTemp = *(pfPowerArray+nIndex);
			if (fPreTemp<0)
			{
				pdbPMArry[nIndex] = -200;
			}
			else
			{
				dbPMTemp =10*log10(fPreTemp*1000);
				pdbPMArry[nIndex] = dbPMTemp;		
			}
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
	
	if (pbyBuf)
	{
		delete [] pbyBuf ;
	}
	
	return dwErrorCode;		
}

DWORD COp8163A::SetPMScanStop(long lSlot,long lChIndex)
{
	char chReadBuf[MAX_PATH];
	CString strTemp;
	DWORD dwErrorCode =SUCCESS;
	int nCurSlot = lSlot;
	try
	{
		ZeroMemory(chReadBuf,sizeof(char)*MAX_PATH);		
        sprintf(chReadBuf,"sens%d:func:stat logg,stop\r\n",nCurSlot);
		
		dwErrorCode=m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PM_SCAN_STOP;
		}	
		
		ZeroMemory(chReadBuf, sizeof(char)*MAX_PATH);
		sprintf(chReadBuf, "sens%d:func:stat?\r\n",nCurSlot);
		dwErrorCode=m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PM_SCAN_STOP;
		}
		ZeroMemory(chReadBuf, sizeof(char)*MAX_PATH);
		dwErrorCode=m_Comm.ReadDevice(chReadBuf,MAX_PATH);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PM_SCAN_RESULT;
		} 
		strTemp = chReadBuf;
		if (strTemp.Find("NONE,PROGRESS") ==-1)
		{
			throw dwErrorCode|ERROR_PM_SCAN_RESULT;
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


DWORD COp8163A::SetPMScanTriggerStop(long lSlot,long lChIndex)
{
	char chReadBuf[MAX_PATH];
	CString strTemp;
	DWORD dwErrorCode =SUCCESS;
	int nCurSlot = lSlot;
	try
	{
		ZeroMemory(chReadBuf, sizeof(char)*MAX_PATH);
		sprintf(chReadBuf,"trig%d:inp ign\r\n",nCurSlot);
		dwErrorCode=m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PM_TRIGER_STOP;
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
*  函数名称:GetPower												   *
*  功能: 读取功率													   *
*  输入:															   *
*	1、iChan:通道号									 			       *
*	输入数据类型:long                                                   *
*  输出: pdblPowerValue                                                *
*  输出类型：double												       *
*  返回值:                                                             *
*        错误码                                                        *
*  返回值类型:DWORD                                                    *
*  创建日期:2013-10-17                                                 *
*  创建人:yanx                                                         *
*  修改历史:无                                                         *
************************************************************************/
DWORD COp8163A::GetPower(long lSlot,long IChan, double* pdbPowerValue)
{
	DWORD  dwErrorCode;
	TCHAR tszDataStream[32];
	TCHAR  szCmdString[1024];
    double  pdlPower;
	int nCurSlot = lSlot;
	try
	{
		
		ZeroMemory(szCmdString,1024);
		sprintf(szCmdString,"FETCH%d:CHAN%d:POW?\r\n", nCurSlot, IChan);
		
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_PW;
		}
		dwErrorCode = m_Comm.ReadDevice(tszDataStream, 32);
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_PW;
		}
		
		//		if(GPIB_TYPE==m_byConnectType)
		{
		//	dwErrorCode=CompleteQuery();
		}
		
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_PW;
		}
		
		pdlPower = atof(tszDataStream); //dBm
		*pdbPowerValue=pdlPower;
	}	
	catch(...)
	{
		return UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
/***********************************************************************
*  函数名称:GetUnit											           *
*  功能: 读取单位    										    	   *
*  输入:															   *
*	1、iChan:通道号													   *
*	输入数据类型:int												   *
*  输出: piUnit(0表示dBm，1表示mw)									   *
*  输出类型:int													       *
*  返回值:                                                             *
*        错误码                                                        *
*  返回值类型:DWORD                                                    *
*  创建日期:2013-10-17                                                 *
*  创建人:yanx                                                         *
*  修改历史:无                                                         *
************************************************************************/
DWORD COp8163A::GetUnit(long lSlot,long IChan, long* piUnit)
{
	DWORD  dwErrorCode;
	TCHAR tszDataStream[32];
	TCHAR  szCmdString[1024];
	
	int nCurSlot = lSlot;
	try
	{
		
		ZeroMemory(szCmdString,1024);
		sprintf(szCmdString,"sens%d:chan%d:pow:unit?\r\n",nCurSlot, IChan);
		
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_PW;
		}
		dwErrorCode = m_Comm.ReadDevice(tszDataStream, 32);
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_PW;
		}
		
		//		if(GPIB_TYPE==m_byConnectType)
		{
			dwErrorCode=CompleteQuery();
		}
		
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_PW;
		}
		
		*piUnit=atoi(tszDataStream);
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
*  函数名称:GetWavelength											   *
*  功能: 读取波长    										    	   *
*  输入:															   *
*	1、iChan:通道号													   *
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
DWORD COp8163A::GetWavelength(long lSlot,long IChan, double* pdblWL)
{
	DWORD  dwErrorCode;
	TCHAR tszDataStream[32];
	TCHAR  szCmdString[1024];
	
	int nCurSlot = lSlot;
	try
	{
        ZeroMemory(szCmdString,1024);
		sprintf(szCmdString,"sens%d:chan%d:pow:wav?\r\n",nCurSlot, IChan);
		
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_PW;
		}
		dwErrorCode = m_Comm.ReadDevice(tszDataStream, 32);
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_PW;
		}
		
		//		if(GPIB_TYPE==m_byConnectType)
		{
			dwErrorCode=CompleteQuery();
		}
		
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_PW;
		}
		
		*pdblWL=atof(tszDataStream)*1e9;
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
*  函数名称:GetAverageTime											   *
*  功能: 读取平均时间    										       *
*  输入:															   *
*	1、iChan:通道号													   *
*	输入数据类型:int												   *
*  输出: pdblAverageTime(平均时间，单位s)							   *
*  输出类型:double													   *
*  返回值:                                                             *
*        错误码                                                        *
*  返回值类型:DWORD                                                    *
*  创建日期:2013-10-17                                                 *
*  创建人:yanx                                                         *
*  修改历史:无                                                         *
************************************************************************/
DWORD COp8163A::GetAverageTime( long lSlot,long IChan, double* pdblAverageTime)
{
	DWORD  dwErrorCode;
	TCHAR tszDataStream[32];
	TCHAR  szCmdString[1024];
	int nCurSlot = lSlot;
	try
	{
        ZeroMemory(szCmdString,1024);
		sprintf(szCmdString,"sens%d:chan%d:pow:atim?\r\n",nCurSlot, IChan);
		
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_PW;
		}
		dwErrorCode = m_Comm.ReadDevice(tszDataStream, 32);
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_PW;
		}
		
		//		if(GPIB_TYPE==m_byConnectType)
		{
			dwErrorCode=CompleteQuery();
		}
		
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_PW;
		}
		
		*pdblAverageTime=(atof(tszDataStream)*1000);
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
*  函数名称:GetRangeMode											   *
*  功能: 读取动态范围   										       *
*  输入:															   *
*	1、iChan:通道号													   *
*	输入数据类型:int												   *
*  输出: iPWMRangeMode(1:自动;其他值:手动设置值;单位dBm)			   *
*  输出类型:int													       *
*  返回值:                                                             *
*        错误码                                                        *
*  返回值类型:DWORD                                                    *
*  创建日期:2013-10-17                                                 *
*  创建人:yanx                                                         *
*  修改历史:无                                                         *
************************************************************************/
DWORD COp8163A::GetRangeMode(long lSlot,long IChan, long* iPWMRangeMode)
{
	DWORD  dwErrorCode;
	TCHAR tszDataStream[32];
	TCHAR  szCmdString[1024];
	
	long iPMSlot;
	long iPMChannel;
	double dblTemp;
	int nCurSlot = lSlot;
	try
	{
		iPMSlot=(IChan-1)/2+1;
		iPMChannel=(IChan-1)%2+1;
		
		ZeroMemory(szCmdString,1024);
		sprintf(szCmdString,"sens%d:pow:rang:auto?\r\n",nCurSlot);
		
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_RANGE_MODE;
		}
		ZeroMemory(tszDataStream,32);
		dwErrorCode = m_Comm.ReadDevice(tszDataStream, 32);
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_RANGE_MODE;
		}
		
		//		if(GPIB_TYPE==m_byConnectType)
		{
			dwErrorCode=CompleteQuery();
		}
		
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_RANGE_MODE;
		}
		
		*iPWMRangeMode=atoi(tszDataStream);
		
//		if(*iPWMRangeMode==0)
//		{
//			
//			ZeroMemory(szCmdString,1024);	
//			sprintf(szCmdString, "sens%d:chan%d:pow:rang?\r\n",nCurSlot,iPMChannel);
//			
//			//Set the wavelength
//			dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
//			if(dwErrorCode)
//			{
//				return dwErrorCode|ERROR_RANGE_MODE;
//			}
//			dwErrorCode = m_Comm.ReadDevice(tszDataStream, 32);
//			if(dwErrorCode)
//			{
//				return dwErrorCode|ERROR_RANGE_MODE;
//			}
//			dblTemp=atof(tszDataStream);
//			*iPWMRangeMode=(int)dblTemp;
//		}
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
*  函数名称:CompleteQuery                                              *
*  功能: 询问是否完成,用于检查模块是否已经运行完毕					   *
*  输入: 无                                                            *
*  输入数据类型:无                                                     *
*  输出: 无                                                            *
*  返回值:                                                             *
*        错误码                                                        *
*  返回值类型:DWORD                                                    *
*  创建日期:2013-10-17                                                 *
*  创建人:yanx                                                         *
*  修改历史:无                                                         *
************************************************************************/
DWORD COp8163A::CompleteQuery()
{
	char szSendBuf[MAX_PATH];
	long nStatus =-1;
	DWORD dwErrorCode;
	WORD wCount=0;
	try
	{
		//		if(m_byConnectType==GPIB_TYPE)
		{
		    ZeroMemory(szSendBuf,MAX_PATH);
			sprintf(szSendBuf,"*OPC?\r\n");
			
			dwErrorCode=m_Comm.WriteDevice(szSendBuf,strlen(szSendBuf));
			if (dwErrorCode)
			{
				return dwErrorCode|ERROR_WAIT_FOR_COMPLETION;
			}
			ZeroMemory(szSendBuf,MAX_PATH*sizeof(char));
			dwErrorCode=m_Comm.ReadDevice(szSendBuf, MAX_PATH);
			if (dwErrorCode)
			{
				return dwErrorCode|ERROR_WAIT_FOR_COMPLETION;
			}
			nStatus =atoi(szSendBuf);
			if (nStatus != 1)
			{
				return ERROR_PM|ERROR_WAIT_FOR_COMPLETION;
			}
		}
		//		else
		//		{
		//			sprintf(szSendBuf,"*OPC?\r\n");
		//		
		//			dwErrorCode=m_Comm.WriteDevice(szSendBuf);
		//			if (dwErrorCode)
		//			{
		//				return dwErrorCode|ERROR_WAIT_FOR_COMPLETION;
		//			}
		//			ZeroMemory(szSendBuf,MAX_PATH*sizeof(char));
		//			do {
		//				dwErrorCode=m_Comm.ReadDevice(szSendBuf,MAX_PATH);
		//				Sleep(100);
		//				wCount++;
		//				if(wCount>200)
		//					return ERROR_PM|ERROR_WAIT_FOR_COMPLETION;
		//
		//			} while(dwErrorCode);
		//			
		//			nStatus =atoi(szSendBuf);
		//			if (nStatus != 1)
		//			{
		//				return ERROR_PM|ERROR_WAIT_FOR_COMPLETION;
		//			}
		//		}
	}
	//	catch(char* szMsg)
	//	{
	//        return UNEXPECT_OCCUR;
	//	}
	catch(...)
	{
		return UNEXPECT_OCCUR;
	}
	
    return dwErrorCode;
}

/********************************************************************************
* Function Name: GetGPIBAress													*
* Function:	Get the GPIB Address of the Lighwave Multimeter						*
* Input:																		*
*		None													                *
* Output:																		*
*	    1. dblGpibAddress														*	
* Return Value:																	*
*		0: GetGPIBAress False													*
*		1: GetGPIBAress TRUE													*
* Return Type: BOOL																*
* Create Data: 2010-12-9														*
* Creator:  																	*
* Revision History: None														*
*********************************************************************************/
DWORD COp8163A::GetGPIBAress(long  *dblGpibAddress)
{
    DWORD  dwErrorCode;
	TCHAR tszDataStream[32];
	long  dblAddress;
	
	try
	{
		//Get the wavelength
		ZeroMemory(tszDataStream, 32);
		sprintf(tszDataStream,"SYST:COMM:GPIB:ADDR?\r\n");
		dwErrorCode = m_Comm.WriteDevice(tszDataStream,strlen(tszDataStream));
		if(dwErrorCode)
		{
			return dwErrorCode;
		}
		ZeroMemory(tszDataStream, 32);
		dwErrorCode = m_Comm.ReadDevice(tszDataStream, 32);
		if(dwErrorCode)
		{
			return dwErrorCode;
		}	
		
		dblAddress = atoi(tszDataStream); //Meter
        *dblGpibAddress=dblAddress;
		
		dwErrorCode=CompleteQuery();
	}	
	//	catch(char* pszErrorMessage)
	//	{
	//		return UNEXPECT_OCCUR;
	//	}
	catch(...)
	{
		return UNEXPECT_OCCUR;
	}
	
	return dwErrorCode;	
	
}
/********************************************************************************
* Function Name: SetGPIBAress													*
* Function:	 Set the GPIB Address of the Lighwave Multimeter					*
* Input:																		*
*		1. dblGpibAddress														*
* Output:																		*
*		None																	*	
* Return Value:																	*
*		0: SetGPIBAress False													*
*		1: SetGPIBAress TRUE													*
* Return Type: BOOL																*
* Create Data: 2010-12-9														*
* Creator:  																	*
* Revision History: None														*
*********************************************************************************/
DWORD COp8163A::SetGPIBAress(long dblGpibAddress)
{
    DWORD  dwErrorCode;
	TCHAR tszDataStream[32];
	TCHAR  szCmdString[1024];
	
	try
	{
		//Get the wavelength
	    ZeroMemory(szCmdString, 1024);
		sprintf(szCmdString, "SYST:COMM:GPIB:ADDR %d\r\n",dblGpibAddress);
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(dwErrorCode)
		{
			return dwErrorCode;
		}
		ZeroMemory(tszDataStream, 32);
		dwErrorCode = m_Comm.ReadDevice(tszDataStream, 32);
		if(dwErrorCode)
		{
			return dwErrorCode;
		}	
		dwErrorCode =CompleteQuery();
	}	
	//	catch(char* pszErrorMessage)
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
*  函数名称:SetUnit											           *
*  功能: 设置单位    										    	   *
*  输入:															   *
*	1、iChan:通道号													   *
*   2、	lPWMUnit:单位。0:dBm;1:mw						               *
*	输入数据类型:int,int											   *
*  输出: 无															   *
*  输出类型:无													       *
*  返回值:                                                             *
*        错误码                                                        *
*  返回值类型:DWORD                                                    *
*  创建日期:2013-10-17                                                 *
*  创建人:yanx                                                         *
*  修改历史:无                                                         *
************************************************************************/
DWORD COp8163A::SetUnit(long lSlot,long IChan, long IPWUMUnit)
{
    DWORD	dwErrorCode;
	TCHAR	szCmdString[1024];
	
	int nCurSlot = lSlot;
	try
	{
		ZeroMemory(szCmdString, 1024);
		
		sprintf(szCmdString, "sens%d:chan%d:pow:unit %d\r\n",nCurSlot, IChan, IPWUMUnit);
		
		//Set Enable or disable
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_UNIT;
		}
		
		//		if(GPIB_TYPE==m_byConnectType)
		{
	//		dwErrorCode = CompleteQuery();
		}
	}	
	//	catch(char* pszErrorMessage)
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
*  函数名称:SetWavelength											   *
*  功能: 设置波长   										           * 
*  输入:															   *
*	1、iChan:通道号													   *
*	2、dblWavelength:波长(nm)										   *
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
DWORD COp8163A::SetWavelength(long lSlot,long IChan, double dblWL)
{
	DWORD	dwErrorCode;
	TCHAR	szCmdString[1024];
	int nCurSlot = lSlot;
	try
	{
		ZeroMemory(szCmdString, 1024);
		
		sprintf(szCmdString, "sens%d:chan%d:pow:wav %.1fnm\r\n",nCurSlot, IChan, dblWL);

		//Set the wavelength
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_WL;
		}
		
		//		if(GPIB_TYPE==m_byConnectType)
		{
		//	dwErrorCode=CompleteQuery();
		}
	}	
	//	catch(char* pszErrorMessage)
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
*  函数名称:SetAverageTime											   *
*  功能: 设置平均时间												   *
*  输入:															   *
*	1、iChan:通道号													   *
*   2、	dblAvgTime：平均时间（ms）							 		   *
*	输入数据类型:int，double                                           *
*  输出: pdblPowerValue                                                *
*  输出类型：double												       *
*  返回值:                                                             *
*        错误码                                                        *
*  返回值类型:DWORD                                                    *
*  创建日期:2013-10-17                                                 *
*  创建人:yanx                                                         *
*  修改历史:无                                                         *
************************************************************************/
DWORD COp8163A::SetAverageTime(long lSlot,long IChan, double IPWMAverageTime)
{
	DWORD	dwErrorCode;
	TCHAR	szCmdString[1024];
	
	long iPMSlot;
	long iPMChannel;
	int nCurSlot = lSlot;
	try
	{
		iPMSlot=(IChan-1)/2+1;
		iPMChannel=(IChan-1)%2+1;
		ZeroMemory(szCmdString, 1024);
		
		sprintf(szCmdString, "sens%d:pow:atim %.3fms\r\n", nCurSlot, IPWMAverageTime);

		//Set the wavelength
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_AVERIAGE_TIME;
		}
		
		//		if(GPIB_TYPE==m_byConnectType)
		{
		//	dwErrorCode = CompleteQuery();
		}
		
	}	
	//	catch(char* pszErrorMessage)
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
*  函数名称:SetAverageTime											   *
*  功能: 设置平均时间												   *
*  输入:															   *
*	1、iChan:通道号													   *
*   2、	dblAvgTime：平均时间（ms）							 		   *
*	输入数据类型:int，double                                           *
*  输出: pdblPowerValue                                                *
*  输出类型：double												       *
*  返回值:                                                             *
*        错误码                                                        *
*  返回值类型:DWORD                                                    *
*  创建日期:2013-10-17                                                 *
*  创建人:yanx                                                         *
*  修改历史:无                                                         *
************************************************************************/
DWORD COp8163A::SetRangeMode (long lSlot,long IChan, long IPWMRangeMode )

{  
	DWORD	dwErrorCode ;
	TCHAR	szCmdString[1024];
	BOOL bAuto;
	
	int nCurSlot = lSlot;
	try
	{
		ZeroMemory(szCmdString, 256);
		if(IPWMRangeMode==1)
		{
			bAuto=TRUE;
		}
		else
		{
			bAuto=FALSE;
		}
		ZeroMemory(szCmdString,1024);
		sprintf(szCmdString, "sens%d:pow:rang:auto %d\r\n",nCurSlot, bAuto);
		
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_RANGE_MODE;
		}
	}	
	catch(...)
	{
		return UNEXPECT_OCCUR;
	}
	
	return dwErrorCode;	
}
////////////////////////////////////////////////////////////
//函数说明：
//    设置功率计Range
//Add by wanxin
//Time:20140828
/////////////////////////////////////////////////////////////
DWORD COp8163A::SetRange(long lSlot,long IChan, long lRange)
{
	DWORD dwErrorCode=SUCCESS;
	TCHAR	szCmdString[MAX_PATH];
	int nCurSlot = lSlot;
	try
	{			
		if (lRange > 10 || lRange < -30)
		{
			throw dwErrorCode|ERROR_OUT_RANGE;
		}			
		ZeroMemory(szCmdString, MAX_PATH);
		sprintf(szCmdString, "sens%d:pow:rang %ddbm\r\n",nCurSlot, lRange);
		
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(dwErrorCode!=SUCCESS)
		{
			throw dwErrorCode|ERROR_RANGE_MODE;
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
*  函数名称:SetParameters											   *
*  功能: 设置参数   										           * 
*  输入:															   *
*	1.IChan:通道号													   *
*	2.bAutoRang:是否是自动模式									       *
*	3.dblWL:通道号											           *
*	4.dblAverageTime:平均时间									       *
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
DWORD COp8163A::SetParameters(long lSlot,long IChan, BOOL bAutoRang, double dblWL, double dblAverageTime, double dblPwrRange)
{   
	DWORD	dwErrorCode;
	
	try
	{
		
		
		// Set PWM Wavelength
		dwErrorCode=SetWavelength(lSlot,IChan, dblWL);
		
		if(dwErrorCode)
		{
			return dwErrorCode;
		}
		// Set PWM to a-uto-range
		dwErrorCode=SetRangeMode(lSlot,IChan, bAutoRang);
		if(dwErrorCode)
		{
			return dwErrorCode;
		}
		// Set PWM average time 1ms
		dwErrorCode=SetAverageTime(lSlot,IChan, dblAverageTime);
	}	
	catch(...)
	{
		return UNEXPECT_OCCUR;
	}
	
	return dwErrorCode;	
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
*  创建日期:2013-10-17                                                 *
*  创建人:yanx                                                         *
*  修改历史:无                                                         *
************************************************************************/
DWORD COp8163A::Zero(long lSlot,long IChan)
{
	//CString strTemp;
	char chReadBuf[100];
	DWORD dwErrorCode;
	long iPMSlot;
	long iPMChannel;
	int nCurSlot = lSlot;
	try
	{
		iPMSlot=(IChan-1)/2+1;
		iPMChannel=(IChan-1)%2+1;
		ZeroMemory(chReadBuf, sizeof(char)*100);
		
		sprintf(chReadBuf,"sens%d:chan%d:corr:coll:zero\r\n",nCurSlot,IChan);

		dwErrorCode=m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
		
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_AVERIAGE_TIME;
		}
		
		dwErrorCode = CompleteQuery();	
	}
	//	catch (char *strMsg)
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
*  功能: 获取设备信息   										       * 
*  输入:无															   *
*	输入数据类型:无													   *
*  输出: pchInfo													   *
*  输出类型:CHAR*													   *
*  返回值:                                                             *
*        错误码                                                        *
*  返回值类型:DWORD                                                    *
*  创建日期:2013-10-17                                                 *
*  创建人:yanx                                                         *
*  修改历史:无                                                         *
************************************************************************/
DWORD COp8163A::GetDeviceInfo(CHAR * pchInfo)
{
	//CString strTemp;
	char chReadBuf[100];
	DWORD dwErrorCode=0;
	try
	{			
		ZeroMemory(chReadBuf, sizeof(char)*100);
		m_Comm.ClearDevice();
		
		
		sprintf(chReadBuf,"*IDN?\r\n");
	
		dwErrorCode=m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
		if (dwErrorCode!=0)
		{
			return dwErrorCode|ERROR_PW;
		}
		ZeroMemory(chReadBuf, sizeof(char)*100);
		dwErrorCode=m_Comm.ReadDevice(chReadBuf,100);
		if (dwErrorCode!=0)
		{
			return dwErrorCode|ERROR_PW;
		}
		//		if(GPIB_TYPE==m_byConnectType)
		{
			dwErrorCode = CompleteQuery();
		}
		
		if (dwErrorCode)
		{
			return dwErrorCode;
		}
		
		strncpy(pchInfo,chReadBuf,100);
	}
	catch(...)
	{
		return UNEXPECT_OCCUR;
	}
	
	return dwErrorCode;
}

DWORD COp8163A::SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle)
{
	DWORD   dwErrorCode = SUCCESS;
	//	LPCTSTR lpCommunicationInfo;
    
	dwErrorCode = m_Comm.SetDeviceHandle(pszDeviceAddr, handle);
	return dwErrorCode;
}
///////////////////////////////////////////////////////////////////
//函数说明：
//    设置功率计为获得最大、最小功率模式，获得相应的最大、最小功率
//Add by wanxin
////////////////////////////////////////////////////////////////////////
DWORD COp8163A::GetPMMaxMinPower(long lSlot,long IChan,double *pdbGetMax,double *pdbGetMin)
{
	//CString strTemp;
	char chSendBuf[MAX_PATH];
	char szTempBuf[MAX_PATH];
	char sz1TempBuf[MAX_PATH];
	CString strTemp;
	double pdbMinPower;
	double pdbMaxPower;
	char *token=NULL;
	char *token2=NULL;
	char szSpec1[]=":"; 
	char szSpec2[]=",";
	DWORD dwErrorCode=0;
	try
	{			
		ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"sens%d:chan%d:func:res?\n",lSlot,IChan);
		
		dwErrorCode=m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (dwErrorCode!=SUCCESS)
		{
			throw dwErrorCode;
		}
		
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		dwErrorCode=m_Comm.ReadDevice(chSendBuf,MAX_PATH);
		if (dwErrorCode!=SUCCESS)
		{
			throw dwErrorCode|ERROR_PW;
		}
		
		token = strtok(chSendBuf,szSpec2);
		ASSERT(token);
		ZeroMemory(szTempBuf,MAX_PATH);
		sprintf(szTempBuf,"%s",token);//MIN
		
		token2 = strtok(NULL,szSpec2);
		ASSERT(token2);
		ZeroMemory(sz1TempBuf,MAX_PATH);
		sprintf(sz1TempBuf,"%s",token2);//MAX
		
		token2 = strtok(szTempBuf,szSpec1);//:
		ASSERT(token2);
		token2 = strtok(NULL,szSpec1);
		pdbMinPower = atof(token2);
		*pdbGetMin = pdbMinPower;
		
		token2 = strtok(sz1TempBuf,szSpec1);//:
		ASSERT(token2);
		token2 = strtok(NULL,szSpec1);
		pdbMaxPower= atof(token2);
		*pdbGetMax = pdbMaxPower;
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
DWORD COp8163A::SetPMMaxMinPowerStart(long lSlot,long IChan)
{
	char chReadBuf[100];
	DWORD dwErrorCode=0;
	try
	{	
	    ZeroMemory(chReadBuf, 100);
		sprintf(chReadBuf, "sens1:func:par:minm CONT\r\n",lSlot);
		dwErrorCode = m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
		if(dwErrorCode)
		{
			return dwErrorCode;
		}

        Sleep(100);

	    ZeroMemory(chReadBuf, 100);
		sprintf(chReadBuf, "sens%d:func:stat logg,star\r\n",lSlot);
		dwErrorCode = m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
		if(dwErrorCode)
		{
			return dwErrorCode;
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
DWORD COp8163A::SetPMMinMaxStop(long lSlot,long IChan)
{
	char chReadBuf[100];
	DWORD dwErrorCode=0;
	try
	{			
	    ZeroMemory(chReadBuf, 100);
		sprintf(chReadBuf, "sens%d:func:stat logg,stop\r\n",lSlot);
		dwErrorCode = m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
		if(dwErrorCode)
		{
			return dwErrorCode;
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
DWORD COp8163A::SetPMPowerOffset(long lSlot,long IChan,double dbPowerOffset)
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