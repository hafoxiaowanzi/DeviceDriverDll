// Op8163A1.cpp: implementation of the CAQ2200_215 class.
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

CAQ2200_215::CAQ2200_215()
{

}

CAQ2200_215::~CAQ2200_215()
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
DWORD CAQ2200_215::OpenDevice(LPCTSTR pszDeviceAddr, unsigned long *ComHandle)
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
DWORD CAQ2200_215::CloseDevice()
{
	DWORD dwErrorCode;
	dwErrorCode=m_Comm.CloseDevice();
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
DWORD CAQ2200_215::GetPower(long lSlot,long IChan, double* pdbPowerValue)
{
	DWORD  dwErrorCode;
	TCHAR tszDataStream[32];
	TCHAR  szCmdString[1024];
    double  pdlPower = -60;

	try
	{
		ZeroMemory(tszDataStream, sizeof(tszDataStream));
		ZeroMemory(szCmdString, sizeof(szCmdString));
		sprintf(szCmdString,":fetc%d:pow?\r\n", lSlot);

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
		
		dwErrorCode=CompleteQuery();
	
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
DWORD CAQ2200_215::GetUnit(long lSlot,long IChan, long* piUnit)
{
	DWORD  dwErrorCode;
	TCHAR tszDataStream[32];
	TCHAR  szCmdString[1024];

   try
	{
		ZeroMemory(tszDataStream, sizeof(tszDataStream));
		ZeroMemory(szCmdString, sizeof(szCmdString));
		sprintf(szCmdString,":sens%d:pow:unit?\r\n",lSlot);

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
		
		dwErrorCode=CompleteQuery();
	
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_PW;
		}

	    *piUnit=atoi(tszDataStream);
	}	
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
DWORD CAQ2200_215::GetWavelength(long lSlot,long IChan, double* pdblWL)
{
	DWORD  dwErrorCode;
	TCHAR tszDataStream[32];
	TCHAR  szCmdString[1024];

   try
	{
		ZeroMemory(tszDataStream, sizeof(tszDataStream));
		ZeroMemory(szCmdString, sizeof(szCmdString));
		sprintf(szCmdString,":sens%d:pow:wav?\r\n", lSlot);
	    
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
DWORD CAQ2200_215::GetAverageTime( long lSlot,long IChan, double* pdblAverageTime)
{
	DWORD  dwErrorCode;
	TCHAR tszDataStream[32];
	TCHAR  szCmdString[1024];

   try
	{
	    ZeroMemory(tszDataStream, sizeof(tszDataStream));
		ZeroMemory(szCmdString, sizeof(szCmdString));
		sprintf(szCmdString,":sens%d:pow:atim?\r\n", lSlot);
	    
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
DWORD CAQ2200_215::GetRangeMode(long lSlot,long IChan, long* iPWMRangeMode)
{
	DWORD  dwErrorCode;
	TCHAR tszDataStream[32];
	TCHAR  szCmdString[1024];
	double dblTemp = -60;

   try
	{
		ZeroMemory(tszDataStream, sizeof(tszDataStream));
		ZeroMemory(szCmdString, sizeof(szCmdString));
	   
		sprintf(szCmdString,":sens%d:pow:rang:auto?\r\n", lSlot);

		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_RANGE_MODE;
		}
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

		if(*iPWMRangeMode==0)
		{
			ZeroMemory(tszDataStream, sizeof(tszDataStream));
			ZeroMemory(szCmdString, sizeof(szCmdString));
			sprintf(szCmdString, "sens%d:pow:rang?\r\n", IChan);

			dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
			if(dwErrorCode)
			{
				return dwErrorCode|ERROR_RANGE_MODE;
			}
			dwErrorCode = m_Comm.ReadDevice(tszDataStream, 32);
			if(dwErrorCode)
			{
				return dwErrorCode|ERROR_RANGE_MODE;
			}

			dblTemp=atof(tszDataStream);
			*iPWMRangeMode=(int)dblTemp;
		}
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
DWORD CAQ2200_215::CompleteQuery()
{
	DWORD dwErrorCode = SUCCESS;
	CHAR pszStatus[8];
	long lIndex = 0;

	try
	{
		do
		{
			dwErrorCode = m_Comm.WriteDevice("*OPC?\r\n",strlen("*OPC?\r\n"));
			if (SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_WAIT_FOR_COMPLETION;
			}
			Sleep(20);
			ZeroMemory(pszStatus, sizeof(pszStatus));
			dwErrorCode = m_Comm.ReadDevice(pszStatus, 8);
			if (SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_WAIT_FOR_COMPLETION;
			}
			lIndex++;

			//如果5分钟后，操作还未完成，返回超时错误
			if (lIndex > 150000)
			{
				return ERROR_RUN_OVERTIME;
			}
		}while(!strchr(pszStatus, '1'));
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR|ERROR_WAIT_FOR_COMPLETION;
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
DWORD CAQ2200_215::GetGPIBAress(long  *dblGpibAddress)
{
    DWORD  dwErrorCode;
	TCHAR tszDataStream[1024];
	long  dblAddress;

	try
	{
		ZeroMemory(tszDataStream, sizeof(tszDataStream));
		dwErrorCode = m_Comm.WriteDevice(":SYST:COMM:GPIB:ADDR?\r\n",strlen("SYST:COMM:GPIB:ADDR?\r\n"));
		if(dwErrorCode)
		{
			return dwErrorCode;
		}

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
DWORD CAQ2200_215::SetGPIBAress(long dblGpibAddress)
{
    DWORD  dwErrorCode;
	TCHAR tszDataStream[32];
	TCHAR  szCmdString[1024];
	
	try
	{
		ZeroMemory(tszDataStream, sizeof(tszDataStream));
		ZeroMemory(szCmdString, sizeof(szCmdString));
		sprintf(szCmdString, ":SYST:COMM:GPIB:ADDR %d\r\n",dblGpibAddress);
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(dwErrorCode)
		{
			return dwErrorCode;
		}
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
DWORD CAQ2200_215::SetUnit(long lSlot,long IChan, long IPWUMUnit)
{
    DWORD	dwErrorCode;
	TCHAR	szCmdString[1024];

   try
	{
		ZeroMemory(szCmdString, sizeof(szCmdString));
	
		sprintf(szCmdString, ":sens%d:pow:unit %d\r\n", lSlot, IPWUMUnit);

		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_UNIT;
		}

		dwErrorCode = CompleteQuery();
	}	
	catch(...)
	{
		return UNEXPECT_OCCUR;
	}

	return dwErrorCode;	
}

/***********************************************************************
*  函数名称:SetCalibrationValue											           *
*  功能: 设置单位    										    	   *
*  输入:															   *
*	1、iChan:通道号													   *
*   2、	dblCalValue:校准值						               *
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
DWORD CAQ2200_215::SetCalibrationValue(long IChan, double dblCalValue)
{
    DWORD	dwErrorCode;
	TCHAR	szCmdString[1024];

   try
	{
		ZeroMemory(szCmdString, sizeof(szCmdString));
	
		sprintf(szCmdString, ":sens%d:corr %.2f\r\n", IChan, dblCalValue);

		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_UNIT;
		}

		dwErrorCode = CompleteQuery();
	}	
	catch(...)
	{
		return UNEXPECT_OCCUR;
	}

	return dwErrorCode;	
}

/***********************************************************************
*  函数名称:GetCalibrationValue												   *
*  功能: 读取功率													   *
*  输入:															   *
*	1、iChan:通道号									 			       *
*	输入数据类型:long                                                   *
*  输出: pdbCalValue                                                *
*  输出类型：double												       *
*  返回值:                                                             *
*        错误码                                                        *
*  返回值类型:DWORD                                                    *
*  创建日期:2013-10-17                                                 *
*  创建人:yanx                                                         *
*  修改历史:无                                                         *
************************************************************************/
DWORD CAQ2200_215::GetCalibrationValue(long IChan, double* pdbCalValue)
{
	DWORD  dwErrorCode;
	TCHAR tszDataStream[32];
	TCHAR  szCmdString[1024];
    double  pdlPower = 0;

	try
	{
		ZeroMemory(tszDataStream, sizeof(tszDataStream));
		ZeroMemory(szCmdString, sizeof(szCmdString));	   
		sprintf(szCmdString,":sens%d:corr?\r\n", IChan);
	   
	    
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_CH_PW_OFFSET;
		}
		dwErrorCode = m_Comm.ReadDevice(tszDataStream, 32);
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_CH_PW_OFFSET;
		}
		
		dwErrorCode=CompleteQuery();
	
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_CH_PW_OFFSET;
		}

		pdlPower = atof(tszDataStream); 
	    *pdbCalValue = pdlPower;
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
DWORD CAQ2200_215::SetWavelength(long lSlot,long IChan, double dblWL)
{
	DWORD	dwErrorCode;
	TCHAR	szCmdString[1024];

   try
	{
		ZeroMemory(szCmdString, sizeof(szCmdString));
		
		sprintf(szCmdString, ":sens%d:pow:wav %.1fnm\r\n", lSlot, dblWL);
				

		//Set the wavelength
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_WL;
		}

		dwErrorCode=CompleteQuery();
	}	
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
DWORD CAQ2200_215::SetAverageTime(long lSlot,long IChan, double IPWMAverageTime)
{
	DWORD	dwErrorCode = SUCCESS;
	TCHAR	szCmdString[1024];

   try
	{
		ZeroMemory(szCmdString, sizeof(szCmdString));

		sprintf(szCmdString, ":sens%d:pow:atim %.3fms\r\n", lSlot, IPWMAverageTime);

		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_AVERIAGE_TIME;
		}

		dwErrorCode = CompleteQuery();
	}	
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
DWORD CAQ2200_215::SetRangeMode (long lSlot,long IChan, long IPWMRangeMode )

{  
	DWORD	dwErrorCode = SUCCESS ;
	TCHAR	szCmdString[1024];
	BOOL bAuto = TRUE;

   try
	{
		ZeroMemory(szCmdString, sizeof(szCmdString));

		if(IPWMRangeMode==1)
		{
			bAuto=TRUE;
		}
		else
		{
			bAuto=FALSE;
		}

		sprintf(szCmdString, ":sens%d:pow:rang:auto %d\r\n", lSlot, bAuto);

		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_RANGE_MODE;
		}

		dwErrorCode=CompleteQuery();

		if(!bAuto)
		{
			//如果是手动，设置手动设置值
			ZeroMemory(szCmdString, sizeof(szCmdString));
			sprintf(szCmdString, ":sens%d:pow:rang %ddbm\r\n", lSlot, IPWMRangeMode);

			dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
			if(dwErrorCode)
			{
				return dwErrorCode|ERROR_RANGE_MODE;
			}

			dwErrorCode=CompleteQuery();
		}
		
	}	
	catch(...)
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
DWORD CAQ2200_215::SetParameters(long lSlot,long IChan, BOOL bAutoRang, double dblWL, double dblAverageTime, double dblPwrRange)
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
DWORD CAQ2200_215::Zero(long lSlot,long IChan)
{
	char chReadBuf[100];
	DWORD dwErrorCode;

	try
	{
		ZeroMemory(chReadBuf, sizeof(char)*100);
		
		sprintf(chReadBuf,":sens%d:corr:coll:zero\r\n", lSlot);
		dwErrorCode=m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
	
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_AVERIAGE_TIME;
		}

		dwErrorCode = CompleteQuery();	
	}
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
DWORD CAQ2200_215::GetDeviceInfo(CHAR * pchInfo)
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
		dwErrorCode = CompleteQuery();

		if (dwErrorCode)
		{
			return dwErrorCode;
		}

		memcpy(pchInfo,chReadBuf,100);
	}
	catch(...)
	{
		return UNEXPECT_OCCUR;
	}
	
	return dwErrorCode;
}

DWORD CAQ2200_215::SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle)
{
	DWORD   dwErrorCode = SUCCESS;
    
	dwErrorCode = m_Comm.SetDeviceHandle(pszDeviceAddr, handle);

	return dwErrorCode;
}
DWORD CAQ2200_215::PrepareScan(long lSlot,long lChIndex,stScanParam* lScanParam)
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

DWORD CAQ2200_215::SetPMScanStart(long lSlot,long lChIndex)
{	
    char szBuf[MAX_PATH];
	DWORD dwErrorCode =SUCCESS;
	int nCurSlot = lSlot;
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

DWORD CAQ2200_215::getLambdaScanPMResult(long lSlot,long lChIndex,double* pdbPMArry)
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

DWORD CAQ2200_215::SetPMScanStop(long lSlot,long lChIndex)
{
	char chReadBuf[MAX_PATH];
	CString strTemp;
	DWORD dwErrorCode =SUCCESS;
	int nCurSlot = lSlot;
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


DWORD CAQ2200_215::SetPMScanTriggerStop(long lSlot,long lChIndex)
{
	char chReadBuf[MAX_PATH];
	CString strTemp;
	DWORD dwErrorCode =SUCCESS;
	int nCurSlot = lSlot;
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
DWORD CAQ2200_215::GetPMMaxMinPower(long lSlot,long IChan,double *pdbGetMax,double *pdbGetMin)
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
DWORD CAQ2200_215::SetPMMaxMinPowerStart(long lSlot,long IChan)
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
////////////////////////////////////////////////////////////
//函数说明：
//    设置功率计Range
//Add by wanxin
//Time:20140828
/////////////////////////////////////////////////////////////
DWORD CAQ2200_215::SetRange(long lSlot,long IChan, long lRange)
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
DWORD CAQ2200_215::SetPMMinMaxStop(long lSlot,long IChan)
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
DWORD CAQ2200_215::SetPMPowerOffset(long lSlot,long IChan,double dbPowerOffset)
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