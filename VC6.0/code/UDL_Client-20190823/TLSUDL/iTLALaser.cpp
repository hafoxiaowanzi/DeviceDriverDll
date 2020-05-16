// iTLALaser.cpp: implementation of the CiTLALaser class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\\include\\TLS.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CiTLALaser::CiTLALaser()
{
//	m_hCommPort = INVALID_HANDLE_VALUE;
	m_nTypeVerion = 1;
}

CiTLALaser::~CiTLALaser()
{

}
DWORD CiTLALaser::SetTLSSlotIndex(int nSlotIndex)
{
	DWORD dwErrorCode = SUCCESS;
	m_nSlotIndex = nSlotIndex;
	return dwErrorCode;
}

DWORD CiTLALaser::OpenDevice(LPCTSTR pszDeviceAddr, unsigned long *ComHandle) 
{
	DWORD dwErrorCode = SUCCESS;

	try
	{
		dwErrorCode = m_Comm.OpenDevice(pszDeviceAddr, *ComHandle);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode;
		}
        int nType;
		if (GetDeviceVersion(&nType)!=SUCCESS)
		{
			throw ERROR_OPEN;
		}
        m_nTypeVerion = nType;
        Sleep(100);
		if (!GetDeviceConfig())
		{
			throw ERROR_OPEN;
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

DWORD CiTLALaser::CloseDevice() 
{
	DWORD dwErrorCode = SUCCESS;
	dwErrorCode = m_Comm.CloseDevice();

	return dwErrorCode;
}

////////////////////////////////////////////////////////
//函数说明：
//    通过Info指令获得iTLA版本号，从而判断iTLA类型
//说明：
//      FW V1.0.0.0  nType =1
//      FW V2.0.0.0  nType =2
//      其他默认nType =1
//Add by wanxin
//Time：20150710
////////////////////////////////////////////////////////
DWORD CiTLALaser::GetDeviceVersion(int *nType)
{
	DWORD dwErrorCode = SUCCESS;
	int iChannel = 0;
	char pchRxData[20];
	char pchTxData[1024];
	char *token=NULL;
	char szSpec[] ="\r";
	char *token2=NULL;
	char szSpec2[]=":";
	char szTempBuffer[256];

	try
	{
		ZeroMemory(pchRxData, 20);
		sprintf(pchRxData, "%s", "\r\n");
		dwErrorCode = m_Comm.WriteDevice(pchRxData,strlen(pchRxData));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_OPEN;
		}
		Sleep(20);
		ZeroMemory(pchTxData, 1024);
		dwErrorCode = m_Comm.ReadDevice(pchTxData, 1024);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL;
		}
		ZeroMemory(pchRxData, 20);
		sprintf(pchRxData, "%s", "INFO\r\n");
		dwErrorCode = m_Comm.WriteDevice(pchRxData,strlen(pchRxData));
		if(SUCCESS != dwErrorCode)
		{
			dwErrorCode = m_Comm.WriteDevice(pchRxData,strlen(pchRxData));
			if(SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_OPEN;
			}
		}

		Sleep(1000);
		ZeroMemory(pchTxData, 1024);
		dwErrorCode = m_Comm.ReadDevice(pchTxData, 1024);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL;
		}
        token = strtok(pchTxData,szSpec);
		token = strtok(NULL,szSpec);
		token = strtok(NULL,szSpec);
		token = strtok(NULL,szSpec);
        token = strtok(NULL,szSpec);

		strcpy(szTempBuffer,token);

		token2 = strtok(szTempBuffer,szSpec2);
		token2 = strtok(NULL,szSpec2);
        *nType = atoi(token2);
     //   ZeroMemory(pchTxData, 1024);
	//	sprintf("%d",pchTxData);

	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR|ERROR_WL;
	}

	return dwErrorCode ;
}


DWORD CiTLALaser::SetWavelength(long lChIndex, double dblWavelength)
{
	DWORD dwErrorCode = SUCCESS;
	int iChannel = 0;
	char pchRxData[20];
	char pchTxData[256];
	char pchData[20];
	
	try
	{
		if (m_nTypeVerion ==1)
		{
			double dblChannel = (299792458.0/dblWavelength - m_lMinFrequency)/m_lFrequencyGrid + 1;
			
			iChannel = (int)dblChannel;
			
			if (iChannel < 0)
			{
				throw ERROR_WL_RANGE;
			}
			
			if (dblChannel - iChannel > 0.5) 
			{
				iChannel++;
			}
			
			ZeroMemory(pchRxData, 20 * sizeof(char));
			sprintf(pchRxData, "SCH 1 %d\r\n", iChannel);
			
			dwErrorCode = m_Comm.WriteDevice(pchRxData,strlen(pchRxData));
			if(SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_WL;
			}
			int iCnt =0;
			for(;;)		
			{
				
				if((iCnt++)>5)	
				{	
					break;		
				}
				
				Sleep(1000);
				
				ZeroMemory(pchTxData, 256*sizeof(char));
				
				if (m_Comm.ReadDevice(pchTxData, 256)==SUCCESS ) 	
				{				
					if((pchTxData[0]==0x3E)||(pchTxData[1]==0x3E)||(pchTxData[2]==0x3E))	
					{		
						break;	
					}	
				}	
			}
			
			ZeroMemory(pchRxData, 20);
			sprintf(pchRxData, "%s", "SCH\r\n");
			
			dwErrorCode = m_Comm.WriteDevice(pchRxData,strlen(pchRxData));
			if(SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_WL;
			}
			
			Sleep(10);
			ZeroMemory(pchTxData, 256);
			
			dwErrorCode = m_Comm.ReadDevice(pchTxData, 256);
			if(SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_WL;
			}
			
			ZeroMemory(pchData, 20 * sizeof(char));
			if (atol(strncat(pchData, pchTxData+8, strlen(pchTxData)-8)) != iChannel) 
			{
				throw ERROR_WL;
			}
		}
		else
		{
			ZeroMemory(pchRxData, sizeof(pchData));
			sprintf(pchRxData, "SWL 1 %.2f\r", dblWavelength);
			
			DWORD dwBufferSize = strlen(pchRxData);
			dwErrorCode = m_Comm.WriteDevice(pchRxData, dwBufferSize);			
			if(SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_WL;
			}
			
			int iCnt =0;
			for(;;)		
			{
				
				if((iCnt++)>5)	
				{	
					break;		
				}
				
				Sleep(1000);
				
				ZeroMemory(pchTxData, 256*sizeof(char));
				
				if (m_Comm.ReadDevice(pchTxData, 256)==SUCCESS ) 	
				{				
					if((pchTxData[0]==0x3E)||(pchTxData[1]==0x3E)||(pchTxData[2]==0x3E))	
					{		
						break;	
					}	
				}	
			}
			
			ZeroMemory(pchRxData, sizeof(pchData));
			sprintf(pchRxData, "%s", "SWL\r");
			
			dwBufferSize = strlen(pchRxData);
			dwErrorCode = m_Comm.WriteDevice(pchRxData, dwBufferSize);
			if(SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_WL;
			}
			
			Sleep(10);
			ZeroMemory(pchTxData, 256);	
			dwErrorCode = m_Comm.ReadDevice(pchTxData, 256);
			if(SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_WL;
			}
			
			ZeroMemory(pchData, sizeof(pchData));
			double dblBackWl = atof(strncat(pchData, pchTxData+8, strlen(pchTxData)-8));
			
			if ( fabs(dblBackWl - dblWavelength) > 0.1) 
			{
				throw ERROR_WL;
			}	
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

DWORD CiTLALaser::SetSourcePower(long lChIndex, double dblPower)
{
	DWORD dwErrorCode = SUCCESS;
	char pchRxData[20];
	char pchTxData[20];
	char pchData[20];
	double dblReadPower = -100;

	try
	{
		if (dblPower > m_dblMaxPower || dblPower < m_dblMinPower) 
		{
			throw ERROR_PW_RANGE;
		}

		ZeroMemory(pchRxData, 20 * sizeof(char));
		sprintf(pchRxData, "SPWR 1 %.2f\r\n", dblPower);

		dwErrorCode = m_Comm.WriteDevice(pchRxData,strlen(pchRxData));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SRC_POW;
		}

		Sleep(10);
		ZeroMemory(pchTxData, 20);
		dwErrorCode = m_Comm.ReadDevice(pchTxData, 20);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SRC_POW;
		}

		ZeroMemory(pchRxData, 20);
		sprintf(pchRxData, "%s", "SPWR\r\n");

		Sleep(10);
		dwErrorCode = m_Comm.WriteDevice(pchRxData,strlen(pchRxData));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SRC_POW;
		}

		Sleep(10);
		ZeroMemory(pchTxData, 20);
		dwErrorCode = m_Comm.ReadDevice(pchTxData, 20);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SRC_POW;
		}

		ZeroMemory(pchData, 20 * sizeof(char));
		dblReadPower = atof(strncat(pchData, pchTxData+9, strlen(pchTxData)-9));

		if (dblReadPower - dblPower > 0.02 && dblReadPower - dblPower < -0.02) 
		{
			throw ERROR_SRC_POW;
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
DWORD CiTLALaser::SetMaxOutput(long lChIndex)
{
	DWORD dwErrorCode = SUCCESS;
	char pchRxData[20];
	char pchTxData[20];
	char pchData[20];
	double dblReadPower = -100;

	try
	{
		ZeroMemory(pchRxData, 20 * sizeof(char));
		sprintf(pchRxData, "SPWR 1 %.2f\r\n", m_dblMaxPower);

		dwErrorCode = m_Comm.WriteDevice(pchRxData,strlen(pchRxData));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SRC_POW;
		}

		Sleep(10);
		ZeroMemory(pchTxData, 20);
		dwErrorCode = m_Comm.ReadDevice(pchTxData, 20);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SRC_POW;
		}

		ZeroMemory(pchRxData, 20);
		sprintf(pchRxData, "%s", "SPWR\r\n");

		Sleep(10);
		dwErrorCode = m_Comm.WriteDevice(pchRxData,strlen(pchRxData));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SRC_POW;
		}

		Sleep(10);
		ZeroMemory(pchTxData, 20);
		dwErrorCode = m_Comm.ReadDevice(pchTxData, 20);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SRC_POW;
		}

		ZeroMemory(pchData, 20 * sizeof(char));
		dblReadPower = atof(strncat(pchData, pchTxData+9, strlen(pchTxData)-9));

		if (dblReadPower - m_dblMaxPower > 0.02 && dblReadPower - m_dblMaxPower < -0.02) 
		{
			throw ERROR_SRC_POW;
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
DWORD CiTLALaser::SetTLSFrequency(long lChIndex,double dblFrequrency)
{
	DWORD dwErrorCode = SUCCESS;
	int iChannel = 0;
	char pchRxData[20];
	char pchTxData[256];
	char pchData[20];

	try
	{
		double dblChannel = (dblFrequrency - m_lMinFrequency)/m_lFrequencyGrid + 1;

		iChannel = (int)dblChannel;

		if (iChannel < 0)
		{
			throw ERROR_WL_RANGE;
		}

		if (dblChannel - iChannel > 0.5) 
		{
			iChannel++;
		}

		ZeroMemory(pchRxData, 20 * sizeof(char));
		sprintf(pchRxData, "SCH 1 %d\r\n", iChannel);

		dwErrorCode = m_Comm.WriteDevice(pchRxData,strlen(pchRxData));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL;
		}

		Sleep(1000);

		ZeroMemory(pchRxData, 20);
		sprintf(pchRxData, "%s", "SCH\r\n");

		dwErrorCode = m_Comm.WriteDevice(pchRxData,strlen(pchRxData));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL;
		}

		Sleep(10);
		ZeroMemory(pchTxData, 256);

		dwErrorCode = m_Comm.ReadDevice(pchTxData, 256);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL;
		}

		ZeroMemory(pchData, 20 * sizeof(char));
		if (atol(strncat(pchData, pchTxData+8, strlen(pchTxData)-8)) != iChannel) 
		{
			throw ERROR_WL;
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
DWORD CiTLALaser::GetTLSSettings(long lChIndex,double* pdblWavelength,double* pdblPower,BYTE* pdCtrlState)
{

	DWORD dwErrorCode = SUCCESS;
	int iChannel = 0;
	char pchRxData[20];
	char pchTxData[256];
	char pchData[20];

	try
	{
		
		ZeroMemory(pchRxData, 20);
		sprintf(pchRxData, "%s", "SCH\r\n");

		dwErrorCode = m_Comm.WriteDevice(pchRxData,strlen(pchRxData));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL;
		}

		Sleep(10);
		ZeroMemory(pchTxData, 256);

		dwErrorCode = m_Comm.ReadDevice(pchTxData, 256);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_WL;
		}

		ZeroMemory(pchData, 20 * sizeof(char));
 		iChannel = atol(strncat(pchData, pchTxData+8, strlen(pchTxData)-8));
		//计算波长
		//double dblChannel = (dblFrequrency - m_lMinFrequency)/m_lFrequencyGrid + 1;
        * pdblWavelength = 299792458.0/((iChannel*m_lFrequencyGrid)+m_lMinFrequency);

		ZeroMemory(pchRxData, 20);
		sprintf(pchRxData, "%s", "SPWR\r\n");

		Sleep(10);
		dwErrorCode = m_Comm.WriteDevice(pchRxData,strlen(pchRxData));
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SRC_POW;
		}

		Sleep(10);
		ZeroMemory(pchTxData, 20);
		dwErrorCode = m_Comm.ReadDevice(pchTxData, 20);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_SRC_POW;
		}

		ZeroMemory(pchData, 20 * sizeof(char));
		* pdblPower = atof(strncat(pchData, pchTxData+9, strlen(pchTxData)-9));
        * pdCtrlState =1;

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
BOOL CiTLALaser::GetDeviceConfig()
{
	char pchRxData[20];
	char pchTxData[1024];
	char pchData[256];
	TCHAR		pchSeps[] = "\r";
	TCHAR		*pchToken = NULL;

	ZeroMemory(pchRxData, 20 * sizeof(char));
	sprintf(pchRxData, "%s", "CONFIG\r\n");

	if (SUCCESS != m_Comm.WriteDevice(pchRxData,strlen(pchRxData))) 
	{
		return FALSE;
	}

	Sleep(1000);
	ZeroMemory(pchTxData, 1024);
	if (SUCCESS != m_Comm.ReadDevice(pchTxData, 1024)) 
	{
		return FALSE;
	}

//	ITLA Built-in Count: 1
//	ITLA Min Set Power:  7.00 dBm
//	ITLA Max Set Power:  13.00 dBm
//	ITLA Min Channel:    1
//	ITLA Max Channel:    89
//	ITLA Min Frequency:  191700.0 GHz
//	ITLA Max Frequency:  196100.0 GHz
//	ITLA Frequency Grid: 50.0 GHz
//	ITLA Min Wave"

	pchToken = strtok(pchTxData, pchSeps);
	pchToken = strtok(NULL, pchSeps);

	ZeroMemory(pchData, 256 * sizeof(char));
	m_dblMinPower = atof(strncat(pchData, pchToken+21, strlen(pchToken)-24));

	pchToken = strtok(NULL, pchSeps);
	ZeroMemory(pchData, 256 * sizeof(char));
	m_dblMaxPower = atof(strncat(pchData, pchToken+21, strlen(pchToken)-24));

	pchToken = strtok(NULL, pchSeps);
	ZeroMemory(pchData, 256 * sizeof(char));
	m_lMinChannelNum = atol(strncat(pchData, pchToken+21, strlen(pchToken)-21));

	pchToken = strtok(NULL, pchSeps);
	ZeroMemory(pchData, 256 * sizeof(char));
	m_lMaxChannelNum = atol(strncat(pchData, pchToken+21, strlen(pchToken)-21));

	pchToken = strtok(NULL, pchSeps);
	ZeroMemory(pchData, 256 * sizeof(char));
	m_lMinFrequency = atol(strncat(pchData, pchToken+21, strlen(pchToken)-24));

	pchToken = strtok(NULL, pchSeps);
	ZeroMemory(pchData, 256 * sizeof(char));
	m_lMaxFrequency = atol(strncat(pchData, pchToken+21, strlen(pchToken)-24));

	pchToken = strtok(NULL, pchSeps);
	ZeroMemory(pchData, 256 * sizeof(char));
	m_lFrequencyGrid = atol(strncat(pchData, pchToken+21, strlen(pchToken)-24));

	return TRUE;
}

DWORD CiTLALaser::SetParameters(long lChIndex, BOOL bLowSSE,double dblPower, double dblWavelength)
{
	DWORD dwErrorCode = SUCCESS;

	return dwErrorCode;
}

DWORD CiTLALaser::SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle)
{
	DWORD dwErrorCode = SUCCESS;
	dwErrorCode = m_Comm.SetDeviceHandle(pszDeviceAddr, handle);

	return dwErrorCode;
}

DWORD CiTLALaser::SetCoherenceControl(BOOL bEnable)
{
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

DWORD CiTLALaser::SetSourceUnit(long lChIndex, long dblAtten)
{
	DWORD dwErrorCode = SUCCESS;
	char szBuf[256];
	try
	{
		ZeroMemory(szBuf,sizeof(char)*256);			
//		sprintf(szBuf, "POW:UNIT 0\r\n");
//		dwErrorCode = m_Comm.WriteDevice(szBuf);
//		if (SUCCESS != dwErrorCode)
//		{
//			throw dwErrorCode|ERROR_UNIT;
//		}
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

DWORD CiTLALaser::SetOutputEnable(BOOL bEnable)
{
	DWORD dwErrorCode = SUCCESS;
	char szBuf[256];
	
	try
	{
		if (m_nTypeVerion ==1)
		{
			
		}
		else
		{
			ZeroMemory(szBuf, 256);
			sprintf(szBuf, "%s", "STATE 1 %d \r\n");
			
			dwErrorCode = m_Comm.WriteDevice(szBuf,strlen(szBuf));
			if(SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_WL;
			}
			
			Sleep(10);
			ZeroMemory(szBuf, 256);
			
			dwErrorCode = m_Comm.ReadDevice(szBuf, 256);
			if(SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_WL;
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



//////////////////////////////////////////////////////////////////
//函数说明：
//   初始化iTLA激光器扫描
//Add by wanxin
//Time：20140807
//////////////////////////////////////////////////////////////
DWORD CiTLALaser::PrepareScan(long lChIndex,stScanParam* lScanParam)
{
	char chSendBuf[MAX_PATH];
	DWORD dwErrorCode = SUCCESS;
	try
	{
		
		//设置iTLA扫描带宽,默认是50G
		ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"STEP %d\r\n",1);
		if (SUCCESS != m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf))) 
		{
			dwErrorCode = ERROR_TLS_SCAN_PREPARE;
		}
        //设置开始通道
		ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"SBEGCH 1 %d\r\n",1);
		if (SUCCESS != m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf))) 
		{
			dwErrorCode = ERROR_TLS_SCAN_PREPARE;
		}
        //设置终止通道
	    ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"SENDCH 1 %d\r\n",m_lMaxChannelNum);
		if (SUCCESS != m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf))) 
		{
			dwErrorCode = ERROR_TLS_SCAN_PREPARE;
		}
		//设置trig时间
        ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"STIME %d\r\n",30);
		if (SUCCESS != m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf))) 
		{
			dwErrorCode = ERROR_TLS_SCAN_PREPARE;
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
//    开始激光器扫描
//Add by wanxin
//Time：20140807
//////////////////////////////////////////////////////////////
DWORD CiTLALaser::SetScanStart(long lChIndex)
{
	char chSendBuf[MAX_PATH];
	DWORD dwErrorCode = SUCCESS;
	CString strTemp;
	
	try
	{
		
		//设置iTLA扫描带宽,默认是50G
		ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"smode 1 s\r\n");
		if (SUCCESS != m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf))) 
		{
			dwErrorCode = ERROR_TLS_SCAN_PREPARE;
		}
		Sleep(100);
		int nCount=0;
		while (TRUE)
		{
			ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
			if (SUCCESS != m_Comm.ReadDevice(chSendBuf, MAX_PATH)) 
			{
				return FALSE;
			}

			if (strTemp.Find("SCAN OK")!=-1) 
			{
				break;
			}
			nCount++;
			if (nCount > 60)
			{
				return FALSE;
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
//////////////////////////////////////////////////////////////////
//函数说明：
//    开始激光器扫描
//Add by wanxin
//Time：20140807
//////////////////////////////////////////////////////////////
DWORD CiTLALaser::SetScanStop(long lChIndex)
{
	DWORD dwErrorCode = SUCCESS;
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
		dwErrorCode = UNEXPECT_OCCUR|ERROR_OPEN;
	}
	
	return dwErrorCode;
}
//////////////////////////////////////////////////
//函数说明：
//     根据iTLA设置channel获得WL
//Add by wanxin
//Time：20140807
///////////////////////////////////////////////////
DWORD CiTLALaser::GetLamdaScanWLResult(long lChIndex,double* pdbWLAarry)
{
   DWORD dwErrorCode = SUCCESS;
	try
	{
		int nCount =0;
		for (int nIndex=1;nIndex<=97;nIndex++)
		{
			pdbWLAarry[nCount] = 299792458.0/(m_lMinFrequency +nIndex*m_lFrequencyGrid);
			nCount++;
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