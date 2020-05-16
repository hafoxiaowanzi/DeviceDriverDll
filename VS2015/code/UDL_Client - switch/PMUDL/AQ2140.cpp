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

CAQ2140::CAQ2140()
{

}

CAQ2140::~CAQ2140()
{

}

DWORD CAQ2140::OpenDevice(LPCTSTR pszDeviceAddr, unsigned long *ComHandle)
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

DWORD CAQ2140::CloseDevice()
{
	DWORD dwErrorCode;
	dwErrorCode=m_Comm.CloseDevice();
	return dwErrorCode;
}

DWORD CAQ2140::GetPower(long lSlot,long IChan, double* pdbPowerValue)
{
	DWORD  dwErrorCode;
	TCHAR tszDataStream[32];
	TCHAR  szCmdString[1024];
    double  pdlPower = -60;
	CString strTemp;

	try
	{
		if(!SelectSlot(lSlot))
		{
			throw dwErrorCode|ERROR_PW;
		}
		ZeroMemory(tszDataStream, sizeof(tszDataStream));
		ZeroMemory(szCmdString, sizeof(szCmdString));
		sprintf(szCmdString,"OD%d\r\n", lSlot);

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
		
		strTemp.Format("%s",tszDataStream);
		CString strUnit = strTemp.Mid(3,1);
		CString strPower = strTemp.Right(strTemp.GetLength()-7);
		pdlPower = atof(strPower);

		//pdlPower = atof(tszDataStream); //dBm
	    *pdbPowerValue=pdlPower;
	}	
	catch(...)
	{
		return UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD CAQ2140::GetUnit(long lSlot,long IChan, long* piUnit)
{
	DWORD  dwErrorCode;
	TCHAR tszDataStream[32];
	TCHAR  szCmdString[1024];
	CString strTemp;

   try
	{
		ZeroMemory(tszDataStream, sizeof(tszDataStream));
		ZeroMemory(szCmdString, sizeof(szCmdString));
		sprintf(szCmdString,"OD%d\r\n",lSlot);

		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_PW;
		}

		dwErrorCode = m_Comm.ReadDevice(szCmdString, 1024);
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_PW;
		}
		strTemp = szCmdString;

		CString strUnit = strTemp.Mid(3,1);
		if(strUnit.CompareNoCase("O")==0)//W
		{
			*piUnit=0;
		}
		else if(strUnit.CompareNoCase("P")==0)//mW
		{
			*piUnit=1;
		}
		else if(strUnit.CompareNoCase("P")==0)//uW
		{
			*piUnit=2;
		}
		else if(strUnit.CompareNoCase("P")==0)//nW
		{
			*piUnit = 3;
		}
		else if(strUnit.CompareNoCase("P")==0)//pW
		{
			*piUnit = 4;
		}
		else if(strUnit.CompareNoCase("P")==0)//dBm
		{
			*piUnit = 5;
		}
	}	
	catch(...)
	{
		return UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}

DWORD CAQ2140::GetWavelength(long lSlot,long IChan, double* pdblWL)
{
	DWORD  dwErrorCode =SUCCESS;
	TCHAR tszDataStream[32];
	TCHAR  szCmdString[1024];

	try
	{
		if(!SelectSlot(lSlot))
		{
			throw dwErrorCode|ERROR_PW;
		}
		ZeroMemory(tszDataStream, sizeof(tszDataStream));
		ZeroMemory(szCmdString, sizeof(szCmdString));
		sprintf(szCmdString,"OS%d\r\n", lSlot);

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
	}	
	catch(...)
	{
		return UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}

DWORD CAQ2140::GetAverageTime( long lSlot,long IChan, double* pdblAverageTime)
{
	DWORD  dwErrorCode =SUCCESS;
	TCHAR tszDataStream[32];
	TCHAR  szCmdString[1024];

   try
	{

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

DWORD CAQ2140::GetRangeMode(long lSlot,long IChan, long* iPWMRangeMode)
{
	DWORD  dwErrorCode=SUCCESS;
	TCHAR tszDataStream[32];
	TCHAR  szCmdString[1024];
	double dblTemp = -60;

   try
	{

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
BOOL CAQ2140::SelectSlot(int nSlot)
{
    DWORD	dwErrorCode =SUCCESS;
	TCHAR	szCmdString[1024];

   try
	{
	   	ZeroMemory(szCmdString, sizeof(szCmdString));	
		sprintf(szCmdString, "C%d\r\n", nSlot);
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(dwErrorCode)
		{
			return FALSE;
		}
	}	
	catch(...)
	{
		return FALSE;
	}

	return TRUE;	

}


DWORD CAQ2140::GetGPIBAress(long  *dblGpibAddress)
{
    DWORD  dwErrorCode=SUCCESS;
	TCHAR tszDataStream[1024];
	long  dblAddress;

	try
	{

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

DWORD CAQ2140::SetGPIBAress(long dblGpibAddress)
{
    DWORD  dwErrorCode =SUCCESS;
	TCHAR tszDataStream[32];
	TCHAR  szCmdString[1024];
	
	try
	{

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


DWORD CAQ2140::SetUnit(long lSlot,long IChan, long IPWUMUnit)
{
    DWORD	dwErrorCode =SUCCESS;
	TCHAR	szCmdString[1024];

   try
	{
	   	if(!SelectSlot(lSlot))
		{
           return UNEXPECT_OCCUR;
		}
		ZeroMemory(szCmdString, sizeof(szCmdString));
	
		switch(IPWUMUnit) 
		{
		case 0:
			sprintf(szCmdString, "FB");
			break;
		case 1:
			sprintf(szCmdString, "FA");			
			break;
		case 2:
			sprintf(szCmdString, "FC");
			break;
		default:
			sprintf(szCmdString, "FB");
			break;
		}
      
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_UNIT;
		}
	}	
	catch(...)
	{
		return UNEXPECT_OCCUR;
	}

	return dwErrorCode;	
}


DWORD CAQ2140::SetCalibrationValue(long IChan, double dblCalValue)
{
    DWORD	dwErrorCode=SUCCESS;
	TCHAR	szCmdString[1024];

   try
	{

	}	
	catch(...)
	{
		return UNEXPECT_OCCUR;
	}

	return dwErrorCode;	
}

DWORD CAQ2140::GetCalibrationValue(long IChan, double* pdbCalValue)
{
	DWORD  dwErrorCode=SUCCESS;
	TCHAR tszDataStream[32];
	TCHAR  szCmdString[1024];
    double  pdlPower = 0;

	try
	{

	}	
	catch(...)
	{
		return UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

DWORD CAQ2140::SetWavelength(long lSlot,long IChan, double dblWL)
{
	DWORD	dwErrorCode;
	char	szCmdString[256];

	try
	{
		if(!SelectSlot(lSlot))
		{
			return FALSE;
		}
		int nWL = dblWL;	
		ZeroMemory(szCmdString, 256);
		
		sprintf(szCmdString,"W%04d\r\n", nWL);
		
		//Set the wavelength
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_WL;
		}
	}	
	catch(...)
	{
		return UNEXPECT_OCCUR;
	}

	return dwErrorCode;	
}

DWORD CAQ2140::SetAverageTime(long lSlot,long IChan, double IPWMAverageTime)
{
	DWORD	dwErrorCode = SUCCESS;
	TCHAR	szCmdString[1024];

   try
	{
	   int byTimes =(int)IPWMAverageTime;
	   if(!SelectSlot(lSlot))
	   {
		   return UNEXPECT_OCCUR;
	   }
		ZeroMemory(szCmdString, sizeof(szCmdString));
		switch(byTimes) 
		{
		case 1:
			sprintf(szCmdString, "AA");
			break;
		case 2:
			sprintf(szCmdString, "AB");
			break;
		case 5:
			sprintf(szCmdString, "AC");
			break;
		case 10:
			sprintf(szCmdString, "AD");
			break;
		case 20:
			sprintf(szCmdString, "AE");
			break;
		case 50:
			sprintf(szCmdString, "AF");
			break;
		case 100:
			sprintf(szCmdString, "AG");
			break;
		case 200:
			sprintf(szCmdString, "AH");
			break;
		default:
			sprintf(szCmdString, "AA");
			break;
		}
		dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_AVERIAGE_TIME;
		}
	}	
	catch(...)
	{
		return UNEXPECT_OCCUR;
	}

	return dwErrorCode;	
}
DWORD CAQ2140::SetRangeMode (long lSlot,long IChan, long IPWMRangeMode )
{  
	DWORD	dwErrorCode = SUCCESS ;
	TCHAR	szCmdString[1024];
	BOOL bAuto = TRUE;
	
	try
	{
	    if(!SelectSlot(lSlot))
		{
           return UNEXPECT_OCCUR;
		}
		if(IPWMRangeMode)
		{
			sprintf(szCmdString, "RA\r\n",lSlot);
			
			dwErrorCode = m_Comm.WriteDevice(szCmdString,strlen(szCmdString));
			if(dwErrorCode!=SUCCESS)
			{
				throw dwErrorCode|ERROR_RANGE_MODE;
			}		   
		}		
	}	
	catch(...)
	{
		return UNEXPECT_OCCUR;
	}
	
	return dwErrorCode;	
}


DWORD CAQ2140::SetParameters(long lSlot,long IChan, BOOL bAutoRang, double dblWL, double dblAverageTime, double dblPwrRange)
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
DWORD CAQ2140::Zero(long lSlot,long IChan)
{
	char chReadBuf[100];
	DWORD dwErrorCode=0;

	try
	{
	    if(!SelectSlot(lSlot))
		{
           return UNEXPECT_OCCUR;
		}
		ZeroMemory(chReadBuf, sizeof(char)*100);		
		sprintf(chReadBuf,"Z\r\n", lSlot);
		dwErrorCode=m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
	
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_AVERIAGE_TIME;
		}
	}
	catch(...)
	{
		return UNEXPECT_OCCUR;
	}
	
	return dwErrorCode;
}

DWORD CAQ2140::GetDeviceInfo(CHAR * pchInfo)
{
	//CString strTemp;
	char chReadBuf[100];
	DWORD dwErrorCode=0;
	try
	{			

	}
	catch(...)
	{
		return UNEXPECT_OCCUR;
	}
	
	return dwErrorCode;
}

DWORD CAQ2140::SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle)
{
	DWORD   dwErrorCode = SUCCESS;
    
	dwErrorCode = m_Comm.SetDeviceHandle(pszDeviceAddr, handle);

	return dwErrorCode;
}
DWORD CAQ2140::PrepareScan(long lSlot,long lChIndex,stScanParam* lScanParam)
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

DWORD CAQ2140::SetPMScanStart(long lSlot,long lChIndex)
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

DWORD CAQ2140::getLambdaScanPMResult(long lSlot,long lChIndex,double* pdbPMArry)
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

DWORD CAQ2140::SetPMScanStop(long lSlot,long lChIndex)
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


DWORD CAQ2140::SetPMScanTriggerStop(long lSlot,long lChIndex)
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
DWORD CAQ2140::GetPMMaxMinPower(long lSlot,long IChan,double *pdbGetMax,double *pdbGetMin)
{
	//CString strTemp;
	char chReadBuf[100];
	DWORD dwErrorCode=0;
	char * token =NULL;
	char szSpec[] =" ";

	try
	{	
		ZeroMemory(chReadBuf,100);
		sprintf(chReadBuf, "HD%d/MAX/MIN",lSlot);
		dwErrorCode = m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_AVERIAGE_TIME;
		}
		Sleep(200);
		dwErrorCode = m_Comm.ReadDevice(chReadBuf, 100);
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_PW;
		}
        
		token = strtok(chReadBuf,szSpec);
		ASSERT(token);
		token = strtok(NULL,szSpec);
        ASSERT(token);
        *pdbGetMax = atof(token);
		token = strtok(NULL,szSpec);
        ASSERT(token);
		*pdbGetMin = atof(token);

        	
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
DWORD CAQ2140::SetPMMaxMinPowerStart(long lSlot,long IChan)
{
	char chReadBuf[100];
	DWORD dwErrorCode=0;
	try
	{			
		if(SetAverageTime(lSlot,IChan,1)!=SUCCESS)
		{
			throw ERROR_PM;
		}

		ZeroMemory(chReadBuf,100);
		sprintf(chReadBuf, "TAB");
		dwErrorCode = m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_AVERIAGE_TIME;
		}

		ZeroMemory(chReadBuf,100);
		sprintf(chReadBuf, "RA");
		dwErrorCode = m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_AVERIAGE_TIME;
		}

		ZeroMemory(chReadBuf,100);
		sprintf(chReadBuf, "MO0");
		dwErrorCode = m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_AVERIAGE_TIME;
		}

		ZeroMemory(chReadBuf,100);
		sprintf(chReadBuf, "H1");
		dwErrorCode = m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_AVERIAGE_TIME;
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
DWORD CAQ2140::SetRange(long lSlot,long IChan, long lRange)
{
	DWORD dwErrorCode=SUCCESS;
	TCHAR	szCmdString[MAX_PATH];
	int nCurSlot = lSlot;
	try
	{			
		if (lRange > 30 || lRange < -90)
		{
			throw dwErrorCode|ERROR_OUT_RANGE;
		}
		lRange = lRange - (lRange%10);
		ZeroMemory(szCmdString, MAX_PATH);
		switch(lRange) 
		{
		case 30:
			{
				sprintf(szCmdString, "RC\r\n",nCurSlot, lRange);
			}
			break;
		case 20:
			{
				sprintf(szCmdString, "RD\r\n",nCurSlot, lRange);
			}
			break;
		case 10:
			{
				sprintf(szCmdString, "RE\r\n",nCurSlot, lRange);
			}
			break;
		case 0:
			{
				sprintf(szCmdString, "RF\r\n",nCurSlot, lRange);
			}
			break;
		case -10:
			{
				sprintf(szCmdString, "RG\r\n",nCurSlot, lRange);
			}
			break;
		case -20:
			{
				sprintf(szCmdString, "RH\r\n",nCurSlot, lRange);
			}
			break;
		case -30:
			{
				sprintf(szCmdString, "RI\r\n",nCurSlot, lRange);
			}
			break;
		case -40:
			{
				sprintf(szCmdString, "RJ\r\n",nCurSlot, lRange);
			}
			break;
		case -50:
			{
				sprintf(szCmdString, "RK\r\n",nCurSlot, lRange);
			}
			break;
		case -60:
			{
				sprintf(szCmdString, "RL\r\n",nCurSlot, lRange);
			}
			break;
		case -70:
			{
				sprintf(szCmdString, "RM\r\n",nCurSlot, lRange);
			}
			break;
		case -80:
			{
				sprintf(szCmdString, "RN\r\n",nCurSlot, lRange);
			}
			break;
		case -90:
			{
				sprintf(szCmdString, "RO\r\n",nCurSlot, lRange);
			}
			break;
		default:
			{
				sprintf(szCmdString, "RA\r\n",nCurSlot, lRange);
			}
						
			break;
		}
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
DWORD CAQ2140::SetPMMinMaxStop(long lSlot,long IChan)
{
	char chReadBuf[100];
	DWORD dwErrorCode=0;
	try
	{
		ZeroMemory(chReadBuf,100);
		sprintf(chReadBuf, "H0");
		dwErrorCode = m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_AVERIAGE_TIME;
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

DWORD CAQ2140::SetPMPowerOffset(long lSlot,long IChan,double dbPowerOffset)
{
	char chReadBuf[100];
	DWORD dwErrorCode=0;
	try
	{
		
		if(!SelectSlot(lSlot))
		{
			return FALSE;
		}
		//// 100MS 测试平均时间
		ZeroMemory(chReadBuf, 100 * sizeof(CHAR));
		sprintf(chReadBuf, "D%3.3f",dbPowerOffset);
		dwErrorCode = m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
		if(dwErrorCode!=SUCCESS)
		{
			throw dwErrorCode|ERROR_PMOFFSET;
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