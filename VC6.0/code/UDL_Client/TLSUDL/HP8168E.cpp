#include "stdafx.h"
#include "math.h"
#include "..\\include\\TLS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// COp816XCtrl::COp816XCtrl - Constructor
CHP8168ETLS::CHP8168ETLS()
{

}

/////////////////////////////////////////////////////////////////////////////
// COp816XCtrl::~COp816XCtrl - Destructor

CHP8168ETLS::~CHP8168ETLS()
{
	// TODO: Cleanup your control's instance data here.

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
*  创建日期:2013-11-25                                                 *
*  创建人:Hanfei Zhao                                                  *
*  修改历史:无                                                         *
************************************************************************/
DWORD CHP8168ETLS::OpenDevice(LPCTSTR pszDeviceAddr, unsigned long *ComHandle)
{
	DWORD dwErrorCode = SUCCESS;

	try
	{
		dwErrorCode = m_Comm.OpenDevice(pszDeviceAddr, *ComHandle);
		if(SUCCESS != dwErrorCode)
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
		dwErrorCode = UNEXPECT_OCCUR|ERROR_OPEN;
	}

	return dwErrorCode;
}
/////////////////////////////////////////////////////////////////////////
//函数说明：
//    设置Aglient 81960A激光器的slot号
//Add by wanxin
//Time：20160308
/////////////////////////////////////////////////////////////////////////
DWORD  CHP8168ETLS::SetTLSSlotIndex(int nSlotIndex)
{
	DWORD dwErrorCode = SUCCESS;
	m_nSlotIndex = nSlotIndex;
    return dwErrorCode;
}
//////////////////////////////////////////////////////////////////
//函数说明：
//    设置激光器的CC模式
//Add by wanxin
//Time：20140807
//////////////////////////////////////////////////////////////
DWORD CHP8168ETLS::SetCoherenceControl(BOOL bEnable)
{
	DWORD dwErrorCode = SUCCESS;
	char chReadBuf[100];
	try
	{	
//		ZeroMemory(chReadBuf,100);
//		sprintf(chReadBuf, "SOUR%d:AM:STAT %d\r\n",m_nSlotIndex,bEnable);
//		dwErrorCode = m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
//		if (SUCCESS != dwErrorCode)
//		{
//			throw dwErrorCode|ERROR_COHERENCE_CONTROL;
//		} 
//
//		ZeroMemory(chReadBuf,100);
//		sprintf(chReadBuf, "SOUR%d:AM:SOUR COHC\r\n",m_nSlotIndex,bEnable);
//		dwErrorCode = m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
//		if (SUCCESS != dwErrorCode)
//		{
//			throw dwErrorCode|ERROR_COHERENCE_CONTROL;
//		} 
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR|ERROR_COHERENCE_CONTROL;
	}

	return dwErrorCode;	
}
//////////////////////////////////////////////////////////////////
//函数说明：
//    设置激光器的的波长
//Add by wanxin
//Time：20140807
//////////////////////////////////////////////////////////////
DWORD CHP8168ETLS::SetWavelength(long lChIndex, double dblWL)
{
	DWORD dwErrorCode = SUCCESS;
	char chReadBuf[100];
	try
	{
		ZeroMemory(chReadBuf, sizeof(char)*100);
		sprintf(chReadBuf, ":WAVE %.3fNM\r\n", dblWL);
		dwErrorCode = m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
		if (SUCCESS != dwErrorCode)
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
		dwErrorCode = UNEXPECT_OCCUR|ERROR_WL;
	}

	return dwErrorCode;
}
//////////////////////////////////////////////////////////////////
//函数说明：
//    设置激光器的的功率
//Add by wanxin
//Time：20140807
//////////////////////////////////////////////////////////////
DWORD CHP8168ETLS::SetSourcePower(long lChIndex, double dblPW)
{
	DWORD dwErrorCode = SUCCESS;
	char szBuf[256];

	try
	{
		ZeroMemory(szBuf,sizeof(char)*256);
		sprintf(szBuf, "SOUR:POW %.1fDBM\r\n",dblPW);
		dwErrorCode = m_Comm.WriteDevice(szBuf,strlen(szBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SRC_POW;
		} 
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR|ERROR_SRC_POW;
	}

	return dwErrorCode;
}
/////////////////////////////////////////////////////////////////////
//函数说明：
//    设置模块激光器最大输出光
//Add by wanxin
///////////////////////////////////////////////////////////////////////
DWORD CHP8168ETLS::SetMaxOutput(long lChIndex)
{
	
	DWORD dwErrorCode = SUCCESS;
	char chSendBuf[MAX_PATH];
	
	try
	{

	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR|ERROR_SRC_POW;
	}
	
	return dwErrorCode;
}
/////////////////////////////////////////////////////////////////////
//函数说明：
//    设置模块激光器频率
//Add by wanxin
///////////////////////////////////////////////////////////////////////
DWORD CHP8168ETLS::SetTLSFrequency(long lChIndex,double dblFrequrency)
{
	DWORD dwErrorCode = SUCCESS;
	char chSendBuf[MAX_PATH];
	
	try
	{
		int nFre =(int)dblFrequrency;
		ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"sour%d:am:freq %d\r\n",m_nSlotIndex,nFre);
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw "Send TLS Frequency error";
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR|ERROR_SRC_POW;
	}
	
	return dwErrorCode;
}

//////////////////////////////////////////////////////////////////
//函数说明：
//    设置激光器的的功率的单位
//Add by wanxin
//Time：20140807
//////////////////////////////////////////////////////////////
DWORD CHP8168ETLS::SetSourceUnit(long lChIndex, long lUnit)
{
	DWORD dwErrorCode = SUCCESS;
	char szBuf[256];
	try
	{
		ZeroMemory(szBuf,sizeof(char)*256);			
		sprintf(szBuf, "SOUR:POW:UNIT %d\r\n",lUnit);
		dwErrorCode = m_Comm.WriteDevice(szBuf,strlen(szBuf));
		if (SUCCESS != dwErrorCode)
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
		dwErrorCode = UNEXPECT_OCCUR|ERROR_OPEN;
	}

	return dwErrorCode;
}
//////////////////////////////////////////////////////////////////
//函数说明：
//    设置激光器的参数函数，高低光的使用采用该函数
//Add by wanxin
//Time：20140807
//////////////////////////////////////////////////////////////
DWORD CHP8168ETLS::SetParameters(long lChIndex, BOOL bLowSSE, double dblPower, double dblWavelength)
{
	DWORD dwErrorCode = SUCCESS;
	char chReadBuf[100];
	try
	{
		ZeroMemory(chReadBuf,sizeof(char)*100);
		sprintf(chReadBuf, "output 1\r\n");
		dwErrorCode = m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWITCH_CHANNEL;
		}

		if (bLowSSE)
		{							
// 			ZeroMemory(chReadBuf,sizeof(char)*100);
// 			sprintf(chReadBuf, "output0:path lows\r\n");
// 			dwErrorCode = m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
// 			if (SUCCESS != dwErrorCode)
// 			{
// 				throw dwErrorCode|ERROR_SWITCH_CHANNEL;
// 			}
		}
		else
		{
// 			ZeroMemory(chReadBuf,sizeof(char)*100);
// 			sprintf(chReadBuf, "output0:path high\r\n");
// 			dwErrorCode = m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
// 			if (SUCCESS != dwErrorCode)
// 			{
// 				throw dwErrorCode|ERROR_SWITCH_CHANNEL;
// 			}
		}

		dwErrorCode = SetSourcePower(lChIndex, dblPower);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode;
		}

		dwErrorCode = SetWavelength(lChIndex, dblWavelength);
		if (SUCCESS != dwErrorCode)
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
		dwErrorCode = UNEXPECT_OCCUR|ERROR_SWITCH_CHANNEL;
	}

	return dwErrorCode;
}
//////////////////////////////////////////////////////////////////
//函数说明：
//    设置激光器的激光器开启、关闭状态
//Add by wanxin
//Time：20140807
//////////////////////////////////////////////////////////////
DWORD CHP8168ETLS::SetOutputEnable(BOOL bEnable)
{
	DWORD dwErrorCode = SUCCESS;
	char chReadBuf[100];
	try
	{
		ZeroMemory(chReadBuf,sizeof(char)*100);
		sprintf(chReadBuf, "OUTP %d\r\n",bEnable);
		dwErrorCode = m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SWITCH_CHANNEL;
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR|ERROR_SWITCH_CHANNEL;
	}

	return dwErrorCode;
}
//////////////////////////////////////////////////////////////////
//函数说明：
//    设置激光器的MainFrame的handle句柄
//Add by wanxin
//Time：20140807
//////////////////////////////////////////////////////////////
DWORD CHP8168ETLS::SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle)
{
	DWORD dwErrorCode = SUCCESS;
	dwErrorCode = m_Comm.SetDeviceHandle(pszDeviceAddr, handle);

	return dwErrorCode;
}
//////////////////////////////////////////////////////////////////
//函数说明：
//    关闭该激光器MainFrame设备句柄
//Add by wanxin
//Time：20140807
//////////////////////////////////////////////////////////////
DWORD CHP8168ETLS::CloseDevice()
{
	DWORD dwErrorCode = SUCCESS;
	try
	{
		dwErrorCode = m_Comm.CloseDevice();
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR|ERROR_OPEN;
	}

	return dwErrorCode;
}
/////////////////////////////////////////////////////////
//函数说明：
//     获得激光器设置
//Add by wanxin
//Time：20140827
////////////////////////////////////////////////////////////
DWORD CHP8168ETLS::GetTLSSettings(long lChIndex,double* pdblWavelength,double* pdblPower,BYTE* pdCtrlState)
{
	DWORD dwErrorCode = SUCCESS;
	char chSendBuf[MAX_PATH];
	BYTE bStatus;
	try
	{				
		
		//获得波长
		ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"sour%d:wav?\r\n",m_nSlotIndex);
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_GET_TLS_RANGE;
		}

		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		dwErrorCode = m_Comm.ReadDevice(chSendBuf,MAX_PATH);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_GET_TLS_RANGE;
		}
		* pdblWavelength = atof(chSendBuf)*1E9;
		
		//获得功率
		ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"sour%d:pow?\n",m_nSlotIndex);
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_GET_TLS_RANGE;
		}
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		dwErrorCode = m_Comm.ReadDevice(chSendBuf,MAX_PATH);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_GET_TLS_RANGE;
		}
		* pdblPower = atof(chSendBuf);
		//获得开启状态
		ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"sour%d:output stat?\n",m_nSlotIndex);
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_GET_TLS_RANGE;
		}
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		dwErrorCode = m_Comm.ReadDevice(chSendBuf,MAX_PATH);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_GET_TLS_RANGE;
		}
		bStatus = atoi(chSendBuf);
		* pdCtrlState = bStatus;
		if (bStatus ==1) 
		{			
			//获得CC状态判断状态
			ZeroMemory(chSendBuf,MAX_PATH);
			sprintf(chSendBuf,"sour%d:am:sour?\n",m_nSlotIndex);
			dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
			if (SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_GET_TLS_RANGE;
			}
			ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
			dwErrorCode = m_Comm.ReadDevice(chSendBuf,MAX_PATH);
			if (SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_GET_TLS_RANGE;
			}
            bStatus = atoi(chSendBuf);
			if (bStatus ==1)
			{
				* pdCtrlState =2;
			}	
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR|ERROR_OPEN;
	}

	return dwErrorCode;
}
/////////////////////////////////////////////////////////////////
//函数说明：
//    读取TLS输出功率
//Add by wanxin
/////////////////////////////////////////////////////////////////
DWORD CHP8168ETLS::ReadTLSPower(double &dbPower)
{	
	char chSendBuf[MAX_PATH];
	DWORD dwErrorCode = SUCCESS;
	try
	{				
		
		ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"sour%d:pow?\n",m_nSlotIndex);
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_POWER;
		}	
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		dwErrorCode = m_Comm.ReadDevice(chSendBuf,MAX_PATH);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_POWER;
		}
		dbPower =atof(chSendBuf);
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR|ERROR_OPEN;
	}

	return dwErrorCode;
}

/////////////////////////////////////////////////////////////////////
//函数说明：
//    设置模块激光输出功率
//Add by wanxin
///////////////////////////////////////////////////////////////////////
BOOL CHP8168ETLS::SetTLSPower(double dbPower)
{
	char chSendBuf[MAX_PATH];
	DWORD dwErrorCode = SUCCESS;
	try
	{						
		ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"sour%d:pow %.3fDBM\n",m_nSlotIndex,dbPower);
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw "Send TLS Power error";
		}		
	}
	catch(char *pstrMsg)
	{
		AfxMessageBox(pstrMsg);
		return FALSE;
	}
	return TRUE;
}
DWORD CHP8168ETLS::SetScanStart(long lChIndex)
{
	char chSendBuf[MAX_PATH];
	DWORD dwErrorCode = SUCCESS;
	try
	{						
		
	}
	catch(char *pstrMsg)
	{
		AfxMessageBox(pstrMsg);
		return FALSE;
	}
	return TRUE;
}
DWORD CHP8168ETLS::SetScanStop(long lChIndex)
{
	char chSendBuf[MAX_PATH];
	DWORD dwErrorCode = SUCCESS;
	try
	{						
		
	}
	catch(char *pstrMsg)
	{
		AfxMessageBox(pstrMsg);
		return FALSE;
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////
//函数说明：
//    关闭该激光器MainFrame设备句柄
//Add by wanxin
//Time：20140807
//////////////////////////////////////////////////////////////
DWORD CHP8168ETLS::PrepareScan(long lChIndex,stScanParam* lScanParam)
{
	char chSendBuf[MAX_PATH];
	double dbStartWL,dbStopWL;
	double dbReadStartWL,dbReadStopWL;
	DWORD dwErrorCode = SUCCESS;
	try
	{				

	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR|ERROR_OPEN;
	}
	
	return dwErrorCode;
}


//////////////////////////////////////////////////////////////////
//函数说明：
//    获得扫描波长函数
//Add by wanxin
///////////////////////////////////////////////////////////////////
DWORD CHP8168ETLS::GetLamdaScanWLResult(long lChIndex,double* pdbWLAarry)
{
	char chSendBuf[MAX_PATH];
	PBYTE pbWLArry =  NULL;
	double* dbTemp;
	int nTemp;
	DWORD dwErrorCode = SUCCESS;
	try
	{	
		

	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR|ERROR_OPEN;
	}
	
	if (pbWLArry != NULL)
	{
		delete [] pbWLArry;
		pbWLArry = NULL;
	}
	
	return dwErrorCode;	 
}