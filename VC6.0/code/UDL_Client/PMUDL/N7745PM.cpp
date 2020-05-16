// N7745PM.cpp: implementation of the CN7745PM class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\\include\\PM.h"
#include"math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define GPIB_TYPE   0
#define COM_TYPE    1
#define USB_TYPE    2
#define NET_TYPE    3

CN7745PM::CN7745PM()
{
//   m_DevHandle =NULL;
//   bHasSaveOriginalData =false;
//   m_pScanParam =NULL;
//  m_bTLSHasPM =false;
//  m_TLSChannelCount =-1;
//   m_nPMSampleCount =0;
//   m_pPMInfo = NULL;
	m_bDummyAutoEnbale = FALSE;
	m_dblPMAvgTime = 100;
}

CN7745PM::~CN7745PM()
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
DWORD CN7745PM::OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle)
{
	char szBuf[MAX_PATH];
	DWORD dwErrorCode =SUCCESS;
	try
	{

		dwErrorCode=m_Comm.OpenDevice(pszDeviceAddr,*ComHandle);
		if(SUCCESS == dwErrorCode)
		{			
			ZeroMemory(szBuf,MAX_PATH);
			sprintf(szBuf,"*RST\r\n");			
			dwErrorCode=m_Comm.WriteDevice(szBuf,strlen(szBuf));
			if (SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_OPEN;
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

   return dwErrorCode;
}

DWORD CN7745PM::PrepareScan(long lSlot,long lChIndex,stScanParam* lScanParam)
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
		sprintf(szBuf, "sens%d:pow:wav %.3fnm\r\n",nCurSlot,dbWL);
		dwErrorCode=m_Comm.WriteDevice(szBuf,strlen(szBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PM_SCAN_PARPARE;
		}
		//设置功率计为wm
		ZeroMemory(szBuf, sizeof(char)*MAX_PATH);
		sprintf(szBuf, "sens%d:pow:unit 1\r\n",nCurSlot);
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
		sprintf(szBuf, "sens%d:func:par:logg %d,%dus\r\n",lSlot,m_dwScanPoint,m_pScanParam->m_nAvgTime);
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

DWORD CN7745PM::SetPMScanStart(long lSlot,long lChIndex)
{	
    char szBuf[MAX_PATH];
	DWORD dwErrorCode =SUCCESS;
	int nCurSlot = lSlot;
	try
	{
		ZeroMemory(szBuf,MAX_PATH);
		sprintf(szBuf,"sens%d:func:stat logg,star\r\n",nCurSlot);
		dwErrorCode=m_Comm.WriteDevice(szBuf,sizeof(szBuf));
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

DWORD CN7745PM::getLambdaScanPMResult(long lSlot,long lChIndex,double* pdbPMArry)
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
		dwErrorCode=m_Comm.WriteDevice(chReadBuf,sizeof(chReadBuf));
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
		sprintf(chReadBuf,"sens%d:func:res?\r\n",nCurSlot);
		dwErrorCode=m_Comm.WriteDevice(chReadBuf,sizeof(chReadBuf));
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
		
		dwErrorCode=m_Comm.WriteDevice(chReadBuf,sizeof(chReadBuf));
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

DWORD CN7745PM::SetPMScanStop(long lSlot,long lChIndex)
{
	char chReadBuf[MAX_PATH];
	CString strTemp;
	DWORD dwErrorCode =SUCCESS;
	int nCurSlot = lSlot;
	try
	{
		ZeroMemory(chReadBuf,sizeof(char)*MAX_PATH);		
        sprintf(chReadBuf,"sens%d:func:stat logg,stop\r\n",nCurSlot);
				
		dwErrorCode=m_Comm.WriteDevice(chReadBuf,sizeof(chReadBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PM_SCAN_STOP;
		}	

		ZeroMemory(chReadBuf, sizeof(char)*MAX_PATH);
		sprintf(chReadBuf, "sens%d:func:stat?\r\n",nCurSlot);
		dwErrorCode=m_Comm.WriteDevice(chReadBuf,sizeof(chReadBuf));
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


DWORD CN7745PM::SetPMScanTriggerStop(long lSlot,long lChIndex)
{
	char chReadBuf[MAX_PATH];
	CString strTemp;
	DWORD dwErrorCode =SUCCESS;
	int nCurSlot = lSlot;
	try
	{
		ZeroMemory(chReadBuf, sizeof(char)*MAX_PATH);
		sprintf(chReadBuf,"trig%d:inp ign\r\n",nCurSlot);
		dwErrorCode=m_Comm.WriteDevice(chReadBuf,sizeof(chReadBuf));
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
DWORD CN7745PM::CompleteQuery()
{
    char szSendBuf[MAX_PATH];
	long nStatus =-1;
	DWORD dwErrorCode = SUCCESS;
	try
	{
		ZeroMemory(szSendBuf,MAX_PATH);
		sprintf(szSendBuf,"*OPC?\r\n");
		dwErrorCode=m_Comm.WriteDevice(szSendBuf,strlen(szSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WAIT_FOR_COMPLETION;
		}
		ZeroMemory(szSendBuf,MAX_PATH*sizeof(char));
		dwErrorCode=m_Comm.ReadDevice(szSendBuf,MAX_PATH);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WAIT_FOR_COMPLETION;
		}
		nStatus =atoi(szSendBuf);
		if (nStatus != 1)
		{
			throw ERROR_PM|ERROR_WAIT_FOR_COMPLETION;
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
        return UNEXPECT_OCCUR;
	}
    return dwErrorCode;
}

//bool CN7745PM::SetRangeAndReaPower(long lSlot,long iChan,int nRange,double &dbReadPower)
//{
//	char chReadBuf[100];
//	DWORD dwErrorCode=SUCCESS;
//	int nCurSlot = lSlot;
//	try
//	{
//		if(!SetRange(lSlot,iChan,nRange))
//		{
//			throw "Set pm range error";
//		}
//		Sleep(50);
//		ZeroMemory(chReadBuf, sizeof(char)*100);
//		sprintf(chReadBuf,"fetc%d:pow?\r\n",nCurSlot);
//		dwErrorCode=m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
//		if (SUCCESS != dwErrorCode)
//		{
//			throw "Send read pm power error";
//		}
//		ZeroMemory(chReadBuf, sizeof(char)*100);
//		dwErrorCode=m_Comm.ReadDevice(chReadBuf,100);
//		if (SUCCESS != dwErrorCode)
//		{
//			throw "Read pm power error";
//		}
//		dbReadPower =  atof(chReadBuf);	
//	}
//	catch (char* pstrMsg)
//	{
//		return false;
//	}
//    return true;
//}

DWORD CN7745PM::ReadPower(long lSlot,long iChan, double* pdblPower)
{
	char chReadBuf[100];
	DWORD dwErrorCode=SUCCESS;
	int nCurSlot = lSlot;
	try
	{
		ZeroMemory(chReadBuf, sizeof(char)*100);
		sprintf(chReadBuf,"fetc%d:pow?\r\n",nCurSlot);
		dwErrorCode=m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW;
		}
		Sleep(20);
		ZeroMemory(chReadBuf, sizeof(char)*100);
		dwErrorCode=m_Comm.ReadDevice(chReadBuf,100);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_PW;
		}

		*pdblPower = atof(chReadBuf);
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
////////////////////////////////////////////////////////////////////////////////
//函数说明:
//    N7745读取功率函数，这里需要注意
//N7744和N7745功率计当设置range为auto模式时会存在一定问题，需要
//人工设置到manual模式，然后根据功率实现逻辑上的自动range
//Add by wanxin
//Time:20170217
//////////////////////////////////////////////////////////////////////////////
DWORD CN7745PM::GetPower(long lSlot,long iChan, double *pdblPowerValue)
{
	DWORD dwErrorCode=SUCCESS;
	int nCurSlot = lSlot;
	double dbCurrPower;
	BOOL bPowerLimitRng = FALSE;
	double dblPowerRng;
	try
	{		
		if(m_bDummyAutoEnbale)
		{
			while(1)
			{	
				if(GetRange(lSlot,iChan,dblPowerRng)!=SUCCESS)
				{
					throw dwErrorCode|ERROR_PW;
				}
				if(ReadPower(lSlot,iChan,&dbCurrPower)!=SUCCESS)
				{
					throw dwErrorCode|ERROR_PW;
				}
				if(bPowerLimitRng==TRUE)
				{
					break;
				}
				if(dbCurrPower < (dblPowerRng+3) && dbCurrPower > (dblPowerRng-30))
				{
					break;
				}
				else
				{
					if(dbCurrPower > 10.0)
					{
						dblPowerRng=10;
						bPowerLimitRng =TRUE;
					}
					else if(dbCurrPower<=10.0 && dbCurrPower > 0.0)
					{
						dblPowerRng=10;
						bPowerLimitRng =TRUE;
					}
					else if(dbCurrPower<=0.0 && dbCurrPower>-10.0)
					{
						dblPowerRng = 0;
						bPowerLimitRng =TRUE;
					}
					else if(dbCurrPower<=-10.0 && dbCurrPower>-20.0)
					{
						dblPowerRng = -10;
						bPowerLimitRng =TRUE;
					}
					else if(dbCurrPower<=-20.0 && dbCurrPower>-30.0)
					{
						dblPowerRng = -20;
						bPowerLimitRng =TRUE;
					}
					else
					{
						dblPowerRng = -30;
						bPowerLimitRng =TRUE;
					}
					
					long lTemp  = (long)dblPowerRng;
					if(SetRange(lSlot,iChan,lTemp)!=SUCCESS)
					{
						throw dwErrorCode|ERROR_PW;
					}
					Sleep(2500);					
				}
				DWORD dwTemp = (DWORD)(m_dblPMAvgTime +10);
				Sleep(dwTemp);
			}
			*pdblPowerValue = dbCurrPower;
		}
		else
		{
            if(ReadPower(lSlot,iChan,pdblPowerValue)!=SUCCESS)
			{
				throw dwErrorCode|ERROR_PW;
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
DWORD CN7745PM::SetAverageTime(long lSlot,long iChan,double dblAvgTime)
{
	char chReadBuf[100];
	DWORD dwErrorCode=SUCCESS;
	int nCurSlot = lSlot;
	try
	{
		m_dblPMAvgTime = dblAvgTime;
		ZeroMemory(chReadBuf, sizeof(char)*100);
		sprintf(chReadBuf,"sens%d:pow:atim %.3fms\r\n",nCurSlot,dblAvgTime);
		dwErrorCode=m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
		if (dwErrorCode!=SUCCESS)
		{
			throw dwErrorCode|ERROR_AVERIAGE_TIME;
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
*  函数名称:SetRangeMode											   *
*  功能: 设置动态范围    											   *
*  输入:															   *
*	1、iChan:通道号													   *
*   2、	IPWMRangeMode:模式。1：自动，其他数字：手动设置成相应的动态范围*
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
DWORD CN7745PM::SetRangeMode(long lSlot,long iChan, long IPWMRangeMode)
{
	DWORD dwErrorCode=SUCCESS;
	BOOL bAuto;
	TCHAR	szCmdString[MAX_PATH];
	int nCurSlot = lSlot;
	try
	{	
		//m_dblAutoPowerRng = 10;
		//这里为了避免N7744自动档位出现问题，不管是manula档位还是
		//Auto档位都设置正manual档位
	    ZeroMemory(szCmdString, MAX_PATH);
		sprintf(szCmdString, "sens%d:pow:rang:auto 0\r\n",nCurSlot);
		
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(dwErrorCode!=SUCCESS)
		{
			throw dwErrorCode|ERROR_RANGE_MODE;
		}
		if(IPWMRangeMode==1)
		{
			bAuto=TRUE;
			m_bDummyAutoEnbale = TRUE;
//			long lTempRng = (long)m_dblAutoPowerRng;
//			if(SetRange(lSlot,iChan,lTempRng)!=SUCCESS)
//			{
//				throw dwErrorCode|ERROR_RANGE_MODE;
//			}
		}
		else
		{
			bAuto=FALSE;
			m_bDummyAutoEnbale = FALSE;
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


////////////////////////////////////////////////////////////
//函数说明：
//    设置功率计Range
//Add by wanxin
//Time:20140828
/////////////////////////////////////////////////////////////
DWORD CN7745PM::GetRange(long lSlot,long IChan, double &dblRange)
{
	DWORD dwErrorCode=SUCCESS;
	TCHAR	szCmdString[MAX_PATH];
	int nCurSlot = lSlot;
	try
	{						
		ZeroMemory(szCmdString, MAX_PATH);
		sprintf(szCmdString, "sens%d:pow:rang?\r\n",nCurSlot);
		
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(dwErrorCode!=SUCCESS)
		{
			throw dwErrorCode|ERROR_RANGE_MODE;
		}	

		ZeroMemory(szCmdString, MAX_PATH);
		dwErrorCode=m_Comm.ReadDevice(szCmdString,MAX_PATH);
		if (dwErrorCode!=SUCCESS)
		{
			throw dwErrorCode|ERROR_UNIT;
		}

        dblRange = atof(szCmdString);

		if (dblRange > 10 || dblRange < -30)
		{
			throw dwErrorCode|ERROR_OUT_RANGE;
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

////////////////////////////////////////////////////////////
//函数说明：
//    设置功率计Range
//Add by wanxin
//Time:20140828
/////////////////////////////////////////////////////////////
DWORD CN7745PM::SetRange(long lSlot,long IChan, long lRange)
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
		sprintf(szCmdString, "sens%d:pow:rang %dDBM\r\n",nCurSlot, lRange);
		
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
DWORD CN7745PM::SetUnit(long lSlot,long iChan, long lPWMUnit)
{
//	//CString strTemp;
	char chReadBuf[100];
	DWORD dwErrorCode=SUCCESS;
	int nCurSlot = lSlot;
	try
	{		
		ZeroMemory(chReadBuf, sizeof(char)*100);
		sprintf(chReadBuf,"sens%d:pow:unit %d\r\n",nCurSlot,lPWMUnit);
		dwErrorCode=m_Comm.WriteDevice(chReadBuf,sizeof(chReadBuf));
		if (dwErrorCode!=SUCCESS)
		{
			throw dwErrorCode|ERROR_UNIT;
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
DWORD CN7745PM::GetUnit(long lSlot,long iChan, long* piUnit)
{
	//	//CString strTemp;
	char chReadBuf[100];
	DWORD dwErrorCode=SUCCESS;
	int nCurSlot = lSlot;
	try
	{
		ZeroMemory(chReadBuf, sizeof(char)*100);
		sprintf(chReadBuf,"sens%d:pow:unit?\r\n",nCurSlot);
		dwErrorCode=m_Comm.WriteDevice(chReadBuf,sizeof(chReadBuf));
		if (dwErrorCode)
		{
			return dwErrorCode|ERROR_UNIT;
		}
		ZeroMemory(chReadBuf, sizeof(char)*100);
		dwErrorCode=m_Comm.ReadDevice(chReadBuf,32);
		if (dwErrorCode!=SUCCESS)
		{
			throw dwErrorCode|ERROR_UNIT;
		}

		*piUnit=atoi(chReadBuf);
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
DWORD CN7745PM::GetWavelength(long lSlot,long iChan, double* pdblWL)
{
	//CString strTemp;
	char chReadBuf[100];
	DWORD dwErrorCode=SUCCESS;
	int nCurSlot = lSlot;
	try
	{		
		ZeroMemory(chReadBuf, sizeof(char)*100);
		sprintf(chReadBuf,"sens%d:pow:wav?\r\n",nCurSlot);
		dwErrorCode=m_Comm.WriteDevice(chReadBuf,sizeof(chReadBuf));
		if (dwErrorCode)
		{
			throw dwErrorCode|ERROR_UNIT;
		}
		ZeroMemory(chReadBuf, sizeof(char)*100);
		dwErrorCode=m_Comm.ReadDevice(chReadBuf,32);
		if (dwErrorCode!=SUCCESS)
		{
			throw dwErrorCode|ERROR_UNIT;
		}

		*pdblWL=atof(chReadBuf)*1e9;
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
DWORD CN7745PM::GetAverageTime(long lSlot,long iChan, double* pdblAverageTime)
{
	//CString strTemp;
	char chReadBuf[100];
	DWORD dwErrorCode=SUCCESS;
	int nCurSlot = lSlot;
	try
	{		
		ZeroMemory(chReadBuf, sizeof(char)*100);
		sprintf(chReadBuf,"sens%d:pow:atim?\r\n",nCurSlot);
		dwErrorCode=m_Comm.WriteDevice(chReadBuf,sizeof(chReadBuf));
		if (dwErrorCode!=SUCCESS)
		{
			throw dwErrorCode|ERROR_UNIT;
		}
		ZeroMemory(chReadBuf, sizeof(char)*100);
		dwErrorCode=m_Comm.ReadDevice(chReadBuf,100);
		if (dwErrorCode!=SUCCESS)
		{
			throw dwErrorCode|ERROR_UNIT;
		}

		*pdblAverageTime=(atof(chReadBuf)*1000);
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
*  输出: iPWMRangeMode(1:自动;其他值:手动设置值;单位dBm)			   *
*  输出类型:int													       *
*  返回值:                                                             *
*        错误码                                                        *
*  返回值类型:DWORD                                                    *
*  创建日期:2013-10-17                                                 *
*  创建人:yanx                                                         *
*  修改历史:无                                                         *
************************************************************************/
DWORD CN7745PM::GetRangeMode(long lSlot,long iChan, long* iPWMRangeMode)
{
	//CString strTemp;
	char chReadBuf[100];
	DWORD dwErrorCode=SUCCESS;
	int nCurSlot = lSlot;
	int nRangeMode=0;
	try
	{
		m_Comm.ClearDevice();
		ZeroMemory(chReadBuf, sizeof(char)*100);
		sprintf(chReadBuf,"sens%d:pow:rang:auto?\r\n",nCurSlot);
		dwErrorCode=m_Comm.WriteDevice(chReadBuf,sizeof(chReadBuf));
		if (dwErrorCode!=SUCCESS)
		{
			throw dwErrorCode|ERROR_UNIT;
		}
		ZeroMemory(chReadBuf, sizeof(char)*100);
		dwErrorCode=m_Comm.ReadDevice(chReadBuf,32);
		if (dwErrorCode!=SUCCESS)
		{
			throw dwErrorCode|ERROR_UNIT;
		}
		nRangeMode=atoi(chReadBuf);

		if(m_bDummyAutoEnbale)
		{
			* iPWMRangeMode = 1;
		}
		else
		{
			* iPWMRangeMode =nRangeMode;
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
DWORD CN7745PM::SetWavelength(long lSlot,long iChan, double dblWavelength)
{
	//CString strTemp;
	char chReadBuf[100];
	DWORD dwErrorCode=SUCCESS;
	int nCurSlot = lSlot;
	try
	{
		
		ZeroMemory(chReadBuf, sizeof(char)*100);
		sprintf(chReadBuf,"sens%d:pow:wav %.1fnm\r\n",nCurSlot,dblWavelength);
		dwErrorCode=m_Comm.WriteDevice(chReadBuf,sizeof(chReadBuf));
		if (dwErrorCode!=SUCCESS)
		{
			throw dwErrorCode|ERROR_WL;
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
DWORD CN7745PM::SetParameters(long lSlot,long iChan, BOOL bAutoRange, double dblWavelength, double dblAvgTile, double dblPwrRange)
{
	//CString strTemp;
	DWORD dwErrorCode=SUCCESS;
	try
	{
		dwErrorCode=SetWavelength(lSlot,iChan,dblWavelength);
		if (dwErrorCode!=SUCCESS)
		{
			throw dwErrorCode;
		}
        m_dblPMAvgTime = dblAvgTile;
		dwErrorCode=SetAverageTime(lSlot,iChan,dblAvgTile);
		if (dwErrorCode!=SUCCESS)
		{
			throw dwErrorCode;
		}
		if (bAutoRange) 
		{
			dwErrorCode=SetRangeMode(lSlot,iChan,bAutoRange);
		}
		else
		{
			dwErrorCode=SetRangeMode(lSlot,iChan,(int)(dblPwrRange+0.5));
		}
		
		if (dwErrorCode !=SUCCESS)
		{
			throw dwErrorCode;
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
DWORD CN7745PM::CloseDevice()
{
	DWORD dwErrorCode;
	dwErrorCode=m_Comm.CloseDevice();
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
DWORD CN7745PM::Zero(long lSlot,long iChan)
{
	//CString strTemp;
	char chReadBuf[100];
	DWORD dwErrorCode;
    int nCurSlot = lSlot;
	try
	{
		
		ZeroMemory(chReadBuf, sizeof(char)*100);
		sprintf(chReadBuf,"sens%d:corr:coll:zero\r\n",nCurSlot);

		dwErrorCode=m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
		if (dwErrorCode!=SUCCESS)
		{
			throw dwErrorCode;
		}
	
		if (dwErrorCode!=SUCCESS)
		{
			throw dwErrorCode;
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
DWORD CN7745PM::GetDeviceInfo(CHAR * pchInfo)
{
	//CString strTemp;
	char chReadBuf[100];
	DWORD dwErrorCode=0;
	try
	{			
		m_Comm.ClearDevice();
		ZeroMemory(chReadBuf, sizeof(char)*100);
		sprintf(chReadBuf,"*IDN?\r\n");
				
		dwErrorCode=m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
		if (dwErrorCode!=SUCCESS)
		{
			throw dwErrorCode|ERROR_PW;
		}
		ZeroMemory(chReadBuf, sizeof(char)*100);
		dwErrorCode=m_Comm.ReadDevice(chReadBuf,100);
		if (dwErrorCode!=SUCCESS)
		{
			throw dwErrorCode|ERROR_PW;
		}

		strncpy(pchInfo,chReadBuf,100);
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

DWORD CN7745PM::SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle)
{
	DWORD   dwErrorCode = SUCCESS;
    
	dwErrorCode = m_Comm.SetDeviceHandle(pszDeviceAddr, handle);
	return dwErrorCode;
}
///////////////////////////////////////////////////////////////////
//函数说明：
//    获得相应的最大、最小功率
//Add by wanxin
////////////////////////////////////////////////////////////////////////
DWORD CN7745PM::GetPMMaxMinPower(long lSlot,long IChan,double *pdbGetMax,double *pdbGetMin)
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
		sprintf(chSendBuf,"sens%d:func:res?\n",lSlot);
		
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

DWORD CN7745PM::SetPMMinMaxStop(long lSlot,long IChan)
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
///////////////////////////////////////////////////////////////////
//函数说明：
//    设置功率计为获得最大、最小功率模式
//Add by wanxin
////////////////////////////////////////////////////////////////////////
DWORD CN7745PM::SetPMMaxMinPowerStart(long lSlot,long IChan)
{
	char chReadBuf[100];
	DWORD dwErrorCode=0;
	try
	{
		ZeroMemory(chReadBuf, sizeof(char)*100);
		sprintf(chReadBuf,"sens%d:func:par:minm cont\r\n",lSlot);

		dwErrorCode=m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
		if (dwErrorCode!=SUCCESS)
		{
			throw dwErrorCode;
		}
	
		ZeroMemory(chReadBuf, sizeof(char)*100);
		sprintf(chReadBuf,"sens%d:func:stat minm,star\r\n",lSlot);

		dwErrorCode=m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
		if (dwErrorCode!=SUCCESS)
		{
			throw dwErrorCode;
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
DWORD CN7745PM::SetPMPowerOffset(long lSlot,long IChan,double dbPowerOffset)
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