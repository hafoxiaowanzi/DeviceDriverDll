// SantecTLS.cpp: implementation of the CSantecTLS class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\\include\\TLS.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSantecTLS::CSantecTLS()
{

}

CSantecTLS::~CSantecTLS()
{

}
DWORD CSantecTLS::SetTLSSlotIndex(int nSlotIndex)
{
	DWORD dwErrorCode = SUCCESS;
	m_nSlotIndex = nSlotIndex;
	return dwErrorCode;
}
DWORD CSantecTLS::SetOutputEnable(BOOL bEnable)
{
	DWORD dwErrorCode = SUCCESS;
	char szBuf[256];
	int nState = -1;
	
	try
	{
		ZeroMemory(szBuf,256);
		sprintf(szBuf,"pow:stat?\r\n");
		dwErrorCode = m_Comm.WriteDevice(szBuf,strlen(szBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_INITIAL;
		}
		
		Sleep(100);
		
		ZeroMemory(szBuf, sizeof(char)*256);
		dwErrorCode = m_Comm.ReadDevice(szBuf,256);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_INITIAL;
		}
		
		nState =atoi(szBuf);
		
		if (bEnable !=nState)
		{
			
			ZeroMemory(szBuf,sizeof(char)*256);
			sprintf(szBuf, "pow:stat %d\r\n", bEnable);
			dwErrorCode = m_Comm.WriteDevice(szBuf,strlen(szBuf));
			if (SUCCESS != dwErrorCode)
			{
				throw ERROR_INITIAL;
			}
			if (bEnable)
			{
				Sleep(40000);
			}
		}
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR|ERROR_INITIAL;
	}

    return dwErrorCode;
}

DWORD CSantecTLS::OpenDevice(LPCTSTR pszDeviceAddr, unsigned long *ComHandle) 
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szBuf[256];

	try
	{
		dwErrorCode = m_Comm.OpenDevice(pszDeviceAddr, *ComHandle);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode;
		}

		ZeroMemory(szBuf,sizeof(char)*256);
		sprintf(szBuf,"*RST\r\n");
		dwErrorCode = m_Comm.WriteDevice(szBuf,strlen(szBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw ERROR_INITIAL;
		}

//		ZeroMemory(szBuf,sizeof(char)*256);
//		sprintf(szBuf,"*TST?");
//		if (!m_Comm.WriteDevice((char*)szBuf))
//		{
//			throw "TLS发送自测试指令错误";
//		}
//		ZeroMemory(szBuf,sizeof(char)*256);
//		if (!m_Comm.ReadDevice((char*)szBuf,256))
//		{
//			throw "TLS读取自测试结果错误";
//		}
//		nState = atoi(szBuf);
//		if (nState != 0)
//		{
//            throw "TLS自测试结果反馈异常";
//		}
		dwErrorCode = SetOutputEnable(TRUE);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_INITIAL;
		}
		
		ZeroMemory(szBuf, sizeof(char)*256);
		sprintf(szBuf,"POW:ATT:AUT 1\r\n");
		dwErrorCode = m_Comm.WriteDevice(szBuf,strlen(szBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_INITIAL;
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

//void CSantecTLS::SetGPIBAddress(long laddress)
//{
////   m_lGPIBAddress = laddress;
//}

/*DWORD CSantecTLS::GetDeviceDescription(char *szBuf, int nsize)
{
	DWORD dwErrorCode = SUCCESS;
	char tempbuf[100];
//	CString strTemp;
	try
	{
		//查询TLS信息
		ZeroMemory(tempbuf,100);
		sprintf(tempbuf,"*IDN?");
		if (!m_Comm.WriteDevice((char*)tempbuf)) 
		{
			throw "写GPIB信息指令错误";
		}
		if (!m_Comm.ReadDevice(szBuf,nsize))
		{
			throw "查询TLS的信息错误";
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
	
    return true;
}*/

/*BOOL CSantecTLS::GetAttenuation(double &dbPower)
{
	char chReadBuf[100];
	try
	{				
			
		ZeroMemory(chReadBuf, sizeof(char)*100);
		sprintf(chReadBuf,"POW:ATT?");
		if (!m_Comm.WriteDevice(chReadBuf))
		{
			throw "发送读取衰减指令错误";
		}
		ZeroMemory(chReadBuf, sizeof(char)*100);
		if (!m_Comm.ReadDevice(chReadBuf,100))
		{
			throw "读取衰减值错误";
		}
		dbPower = atof(chReadBuf);	
	}
	catch (char*strMsg)
	{
		::MessageBox(NULL,strMsg,"提示",MB_OK);
		return false;
	}
	return true;
}*/

DWORD CSantecTLS::SetSourcePower(long lChIndex, double dbPower)
{
	DWORD dwErrorCode = SUCCESS;
	char szBuf[256];

	try
	{
		ZeroMemory(szBuf,sizeof(char)*256);
		sprintf(szBuf, "POW %.3f\r\n",dbPower);
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
		dwErrorCode = UNEXPECT_OCCUR|ERROR_OPEN;
	}

	return dwErrorCode;
}

DWORD CSantecTLS::SetMaxOutput(long lChIndex)
{
	DWORD dwErrorCode = SUCCESS;
	char szBuf[256];

	try
	{
		ZeroMemory(szBuf,sizeof(char)*256);
		sprintf(szBuf, "POW %.3f\r\n",12.0);
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
		dwErrorCode = UNEXPECT_OCCUR|ERROR_OPEN;
	}

	return dwErrorCode;
}
DWORD CSantecTLS::SetTLSFrequency(long lChIndex,double dblFrequrency)
{
	DWORD dwErrorCode = SUCCESS;
	char szBuf[256];

	try
	{
		ZeroMemory(szBuf,sizeof(char)*256);
		sprintf(szBuf, "FREQ %.4f\r\n",dblFrequrency);
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
DWORD CSantecTLS::GetTLSSettings(long lChIndex,double* pdblWavelength,double* pdblPower,BYTE* pdCtrlState)
{
	DWORD dwErrorCode = SUCCESS;
	BYTE bStatus;
	char chSendBuf[MAX_PATH];
	try
	{				
		
		//获得波长
		ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"WAV?\r\n");
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
		sprintf(chSendBuf,"POW?\r\n");
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
		sprintf(chSendBuf,"pow:stat?\r\n");
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
			sprintf(chSendBuf,"COHC?\r\n");
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
DWORD CSantecTLS::SetSourceUnit(long lChIndex, long lUnit)
{
	DWORD dwErrorCode = SUCCESS;
	char szBuf[256];
	try
	{
		ZeroMemory(szBuf,sizeof(char)*256);			
		sprintf(szBuf, "POW:UNIT %d\r\n", lUnit);
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

DWORD CSantecTLS::SetWavelength(long lIndex, double dblWavelength)
{
	DWORD dwErrorCode = SUCCESS;
	char chReadBuf[100];
	try
	{
		ZeroMemory(chReadBuf, sizeof(char)*100);
		sprintf(chReadBuf, "wav %.3f\r\n", dblWavelength);
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
		dwErrorCode = UNEXPECT_OCCUR|ERROR_OPEN;
	}

	return dwErrorCode;
}

DWORD CSantecTLS::SetCoherenceControl(BOOL bEnable)
{
	DWORD dwErrorCode = SUCCESS;
	char chReadBuf[100];
	try
	{	
		ZeroMemory(chReadBuf, sizeof(chReadBuf));
		sprintf(chReadBuf,"COHC %d\r\n",bEnable);
		dwErrorCode = m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_COHERENCE_CONTROL;
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

DWORD CSantecTLS::SetParameters(long lIndex, BOOL bLowSSE,double dblPower, double dblWavelength)
{
	DWORD dwErrorCode = SUCCESS;
	char szBuf[256];
	try
	{
		ZeroMemory(szBuf,sizeof(char)*256);			
		sprintf(szBuf, "POW:UNIT 0\r\n");
		dwErrorCode = m_Comm.WriteDevice(szBuf,strlen(szBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_UNIT;
		}

		ZeroMemory(szBuf,sizeof(char)*256);
		sprintf(szBuf, "POW:ATT:AUT 1\r\n");
		dwErrorCode = m_Comm.WriteDevice(szBuf,strlen(szBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WROK_MODE;
		}
		
		ZeroMemory(szBuf, sizeof(char)*256);
		sprintf(szBuf, "wav %.3f\r\n", dblWavelength);
		dwErrorCode = m_Comm.WriteDevice(szBuf,strlen(szBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL;
		} 
		
		ZeroMemory(szBuf,sizeof(char)*256);
		sprintf(szBuf, "POW %.3f\r\n", dblPower);
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
		dwErrorCode = UNEXPECT_OCCUR|ERROR_OPEN;
	}

	return dwErrorCode;
}

DWORD CSantecTLS::PrepareScan(long lChIndex,stScanParam* lScanParam)
{
	char chSendBuf[100];
	double dbSpeed; 
	double dbStartWL,dbStopWL;
    DWORD dwErrorCode = SUCCESS;
	
	ZeroMemory(chSendBuf, sizeof(char)*100);
	try
	{
		m_pScanParam =lScanParam;	
		if (m_pScanParam->m_dblStartWL < 1510.0 || m_pScanParam->m_dblStopWL >1610.0)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_WLRANGE;
		}
		dbStartWL = m_pScanParam->m_dblStartWL - 0.02;
		
		dbStopWL = m_pScanParam->m_dblStopWL + 0.02;

		dbSpeed = m_pScanParam->m_dblStepSize*1000;  

		//激光器扫描点数
		m_pScanParam->m_dwSampleCount = (int)((m_pScanParam->m_dblStopWL - m_pScanParam->m_dblStartWL) / m_pScanParam->m_dblStepSize);
		m_dwScanPoint = (int)((dbStopWL - dbStartWL) / m_pScanParam->m_dblStepSize);	 				
		if (m_dwScanPoint > 20000)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_PREPARE;
		}     
		
		//设置激光器的功率
		if (!SetSourcePower(lChIndex,m_pScanParam->m_dblTLSPower))
		{
			throw dwErrorCode|ERROR_TLS_SCAN_PREPARE;
		}
		//设置激光器Trigger模式为Step模式
		ZeroMemory(chSendBuf, sizeof(char)*100);
		sprintf(chSendBuf, "TRIG: OUTP 3");
		if (!m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf)))
		{
			throw dwErrorCode|ERROR_TLS_SCAN_PREPARE;
		}	    
		//设置扫描速度
		ZeroMemory(chSendBuf, sizeof(char)*100);
		sprintf(chSendBuf, "wav:swe:spe %.1f",dbSpeed );//
		if (!m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf)))
		{
			throw dwErrorCode|ERROR_TLS_SCAN_PREPARE;
		}
		//设置triger扫描步长
		ZeroMemory(chSendBuf, sizeof(char)*100);
		sprintf(chSendBuf, "trig:outp:step %.3f", m_pScanParam->m_dblStepSize);
		if (!m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf)))
		{
			throw dwErrorCode|ERROR_TLS_SCAN_PREPARE;
		}
		//设置扫描开始波长
		ZeroMemory(chSendBuf, sizeof(char)*100);
		sprintf(chSendBuf, "wav:swe:star %.3f", m_pScanParam->m_dblStartWL);
		if (!m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf)))
		{
			throw dwErrorCode|ERROR_TLS_SCAN_PREPARE;
		}
		//设置扫描停止波长
		ZeroMemory(chSendBuf, sizeof(char)*100);
		sprintf(chSendBuf, "wav:swe:stop %f", m_pScanParam->m_dblStopWL);
		if (!m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf)))
		{
			throw dwErrorCode|ERROR_TLS_SCAN_PREPARE;
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

DWORD CSantecTLS::SetScanStart(long lChIndex)
{
	char chReadBuf[100];
	DWORD dwErrorCode = SUCCESS;
	try
	{	
		//开始激光器扫描		
		if (!m_Comm.WriteDevice("wav:swe 1\r\n",strlen("wav:swe 1\r\n")))
		{
			throw dwErrorCode|ERROR_TLS_SCAN_START;
		}
		Sleep(50);
		while (TRUE)
		{
			m_Comm.WriteDevice("wav:swe?\r\n",strlen("wav:swe?\r\n"));
			ZeroMemory(chReadBuf, 100);
			if (!m_Comm.ReadDevice(chReadBuf, 100))
			{
				throw dwErrorCode|ERROR_TLS_SCAN_START;
			}
			if (chReadBuf[0] == '0')
			{
				break;
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
DWORD CSantecTLS::SetScanStop(long lChIndex)
{
	char chReadBuf[100];
	DWORD dwErrorCode = SUCCESS;
	try
	{	
		//开始激光器扫描		
		if (!m_Comm.WriteDevice("wav:swe 0\r\n",strlen("wav:swe 0\r\n")))
		{
			throw dwErrorCode|ERROR_TLS_SCAN_STOP;
		}
		Sleep(50);
		while (TRUE)
		{
			m_Comm.WriteDevice("wav:swe?\r\n",strlen("wav:swe?\r\n"));
			ZeroMemory(chReadBuf, 100);
			if (!m_Comm.ReadDevice(chReadBuf, 100))
			{
				throw dwErrorCode|ERROR_TLS_SCAN_START;
			}
			if (chReadBuf[0] == '0')
			{
				break;
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

DWORD CSantecTLS::GetLamdaScanWLResult(long lChIndex,double* pdbWLAarry)
{
	char chReadBuf[100];
	CString strTemp;
	int nLength ;
	int nWLCount;
	PBYTE pbWLArry =  NULL;
	int *nWLTempArray = NULL;
	int nTemp;
	double dbWLTemp;
	DWORD dwErrorCode = SUCCESS;
	try
	{
		//从TLS扫描结果中读取点数
		if(!m_Comm.WriteDevice("read:poin?\r\n",strlen("read:poin?\r\n")))
		{ 
			throw dwErrorCode|ERROR_TLS_SCAN_RESULT;
		}		
		ZeroMemory(chReadBuf, sizeof(char)*100);
		if (!m_Comm.ReadDevice(chReadBuf, 100))
		{
			throw dwErrorCode|ERROR_TLS_SCAN_RESULT;
		}
		ASSERT(chReadBuf);
		nWLCount = atoi(chReadBuf);
		//读取波长数据
		if (!m_Comm.WriteDevice("read:dat?",strlen("read:dat?")))
		{
			throw dwErrorCode|ERROR_TLS_SCAN_RESULT;
		}
		//读取波长数的位数
		ZeroMemory(chReadBuf, sizeof(char)*100);
		if(!m_Comm.ReadDevice(chReadBuf, 2))
		{
			throw dwErrorCode|ERROR_TLS_SCAN_RESULT;
		}
		ASSERT(chReadBuf);
		int nTempLen = chReadBuf[1] - '0';
		//读取多少波长点数
		ZeroMemory(chReadBuf, sizeof(char)*100);
		if(!m_Comm.ReadDevice(chReadBuf, nTempLen))
		{
			throw dwErrorCode|ERROR_TLS_SCAN_RESULT;			
		}
		ASSERT(chReadBuf);
		nLength = atoi(chReadBuf);
		pbWLArry = new BYTE[nLength];
		//读取波长
		if (!m_Comm.ReadDevice(pbWLArry, nLength))
		{
			throw dwErrorCode|ERROR_TLS_SCAN_RESULT;
		}	
						
		for (int nIndex=0;nIndex < nLength;nIndex+=4)
		{
            nTemp = (pbWLArry[nIndex+3]<<24)+(pbWLArry[nIndex+2]<<16)+(pbWLArry[nIndex+1]<<8)+pbWLArry[nIndex];
            dbWLTemp = (double)nTemp/10000;
			pdbWLAarry[nIndex] = dbWLTemp;		
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
	if (pbWLArry!=NULL)
	{
		delete []pbWLArry;
		pbWLArry =NULL;
	}
	
	return dwErrorCode;
}
DWORD CSantecTLS::CloseDevice()
{
	DWORD dwErrorCode = SUCCESS;
	dwErrorCode = m_Comm.CloseDevice();

	return dwErrorCode;   
}

DWORD CSantecTLS::SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle)
{
	DWORD dwErrorCode = SUCCESS;
	dwErrorCode = m_Comm.SetDeviceHandle(pszDeviceAddr, handle);

	return dwErrorCode;
}

DWORD CSantecTLS::SetTLSLock(long lChIndex, int nTimeOut, double dbSetWL)
{
	DWORD dwErrorCode = SUCCESS;

	try
	{

	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR | ERROR_TLSSHARESETLOCK;
	}

	return dwErrorCode;
}
DWORD CSantecTLS::SetTLSUnlock(long lChIndex)
{
	DWORD dwErrorCode = SUCCESS;

	try
	{

	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR | ERROR_TLSSHARESETUNLOCK;
	}

	return dwErrorCode;;
}