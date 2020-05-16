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

COp8153A::COp8153A()
{
	
}

COp8153A::~COp8153A()
{
	
}
/***********************************************************************
*  ��������:OpenDevice                                                 *
*  ����: ���豸													   *
*  ����:                                                               *
*       1��pszDeviceAddr: �������豸��ַ�����ӷ�ʽ����Ϣ�����磺	   *
*  ������������:DWORD                                                  *
*  ���:                                                               *
*       ComHandle:���Handle������ʶ��ͬ �豸                        *
*  �����������:unsigned long                                          *
*  ����ֵ:                                                             *
*        ������                                                        *
*  ����ֵ����:DWORD                                                    *
*  ��������:2013-10-17                                                 *
*  ������:yanx                                                         *
*  �޸���ʷ:��                                                         *
************************************************************************/
DWORD COp8153A::OpenDevice(LPCTSTR pszDeviceAddr, unsigned long *ComHandle)
{
		char szBuf[100];
	DWORD dwErrorCode = SUCCESS;
	
	try
	{
		dwErrorCode = m_Comm.OpenDevice(pszDeviceAddr, *ComHandle);
		if(!dwErrorCode)
		{
			ZeroMemory(szBuf,100);
			sprintf(szBuf, "%s", "*RST\r\n");			
			dwErrorCode=m_Comm.WriteDevice(szBuf,strlen(szBuf));
			if(!dwErrorCode)
			{
				throw dwErrorCode;
			}
            ZeroMemory(szBuf,100);
			sprintf(szBuf, "%s", "*CLS\r\n");			
			dwErrorCode=m_Comm.WriteDevice(szBuf,strlen(szBuf));
			if(!dwErrorCode)
			{
				throw dwErrorCode;
			}
		}
	}
	catch (...)
	{
		return UNEXPECT_OCCUR;
	}
	
	return dwErrorCode;
}
/***********************************************************************
*  ��������:CloseDevice												   *
*  ����: �ر��豸   										           * 
*  ����:��															   *
*	������������:��													   *
*  ���: ��															   *
*  �������:��														   *
*  ����ֵ:                                                             *
*        ������                                                        *
*  ����ֵ����:DWORD                                                    *
*  ��������:2013-10-17                                                 *
*  ������:yanx                                                         *
*  �޸���ʷ:��                                                         *
************************************************************************/
DWORD COp8153A::CloseDevice()
{
	DWORD dwErrorCode;
	dwErrorCode=m_Comm.CloseDevice();
	return dwErrorCode;
}


DWORD COp8153A::PrepareScan(long lSlot,long lChIndex,stScanParam* lScanParam)
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

DWORD COp8153A::SetPMScanStart(long lSlot,long lChIndex)
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

DWORD COp8153A::getLambdaScanPMResult(long lSlot,long lChIndex,double* pdbPMArry)
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

DWORD COp8153A::SetPMScanStop(long lSlot,long lChIndex)
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


DWORD COp8153A::SetPMScanTriggerStop(long lSlot,long lChIndex)
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


/***********************************************************************
*  ��������:GetPower												   *
*  ����: ��ȡ����													   *
*  ����:															   *
*	1��iChan:ͨ����									 			       *
*	������������:long                                                   *
*  ���: pdblPowerValue                                                *
*  ������ͣ�double												       *
*  ����ֵ:                                                             *
*        ������                                                        *
*  ����ֵ����:DWORD                                                    *
*  ��������:2013-10-17                                                 *
*  ������:yanx                                                         *
*  �޸���ʷ:��                                                         *
************************************************************************/
DWORD COp8153A::GetPower(long lSlot,long IChan, double* pdbPowerValue)
{
	DWORD  dwErrorCode;
	TCHAR tszDataStream[32];
	TCHAR  szCmdString[1024];
    double  pdlPower;
	int nCurSlot = lSlot;
	try
	{
		
		ZeroMemory(szCmdString,1024);
		sprintf(szCmdString,"READ%d:POW?\r\n", nCurSlot);
		
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
*  ��������:GetUnit											           *
*  ����: ��ȡ��λ    										    	   *
*  ����:															   *
*	1��iChan:ͨ����													   *
*	������������:int												   *
*  ���: piUnit(0��ʾdBm��1��ʾmw)									   *
*  �������:int													       *
*  ����ֵ:                                                             *
*        ������                                                        *
*  ����ֵ����:DWORD                                                    *
*  ��������:2013-10-17                                                 *
*  ������:yanx                                                         *
*  �޸���ʷ:��                                                         *
************************************************************************/
DWORD COp8153A::GetUnit(long lSlot,long IChan, long* piUnit)
{
	DWORD  dwErrorCode;
	TCHAR tszDataStream[32];
	TCHAR  szCmdString[1024];
	
	int nCurSlot = lSlot;
	try
	{
		
		ZeroMemory(szCmdString,1024);
		sprintf(szCmdString,"sens%d:pow:unit?\r\n",nCurSlot);
		
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
*  ��������:GetWavelength											   *
*  ����: ��ȡ����    										    	   *
*  ����:															   *
*	1��iChan:ͨ����													   *
*	������������:int												   *
*  ���: pdblWL(��������λnm)							     		   *
*  �������:double													   *
*  ����ֵ:                                                             *
*        ������                                                        *
*  ����ֵ����:DWORD                                                    *
*  ��������:2013-10-17                                                 *
*  ������:yanx                                                         *
*  �޸���ʷ:��                                                         *
************************************************************************/
DWORD COp8153A::GetWavelength(long lSlot,long IChan, double* pdblWL)
{
	DWORD  dwErrorCode;
	TCHAR tszDataStream[32];
	TCHAR  szCmdString[1024];
	
	int nCurSlot = lSlot;
	try
	{
        ZeroMemory(szCmdString,1024);
		sprintf(szCmdString,"sens%d:pow:wave?\r\n",nCurSlot);
		
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
// 		{
// 			dwErrorCode=CompleteQuery();
// 		}
		
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
*  ��������:GetAverageTime											   *
*  ����: ��ȡƽ��ʱ��    										       *
*  ����:															   *
*	1��iChan:ͨ����													   *
*	������������:int												   *
*  ���: pdblAverageTime(ƽ��ʱ�䣬��λs)							   *
*  �������:double													   *
*  ����ֵ:                                                             *
*        ������                                                        *
*  ����ֵ����:DWORD                                                    *
*  ��������:2013-10-17                                                 *
*  ������:yanx                                                         *
*  �޸���ʷ:��                                                         *
************************************************************************/
DWORD COp8153A::GetAverageTime( long lSlot,long IChan, double* pdblAverageTime)
{
	DWORD  dwErrorCode;
	TCHAR tszDataStream[32];
	TCHAR  szCmdString[1024];
	int nCurSlot = lSlot;
	try
	{
        ZeroMemory(szCmdString,1024);
		sprintf(szCmdString,"sens%d:pow:atime?\r\n",nCurSlot);
		
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
*  ��������:GetRangeMode											   *
*  ����: ��ȡ��̬��Χ   										       *
*  ����:															   *
*	1��iChan:ͨ����													   *
*	������������:int												   *
*  ���: iPWMRangeMode(1:�Զ�;����ֵ:�ֶ�����ֵ;��λdBm)			   *
*  �������:int													       *
*  ����ֵ:                                                             *
*        ������                                                        *
*  ����ֵ����:DWORD                                                    *
*  ��������:2013-10-17                                                 *
*  ������:yanx                                                         *
*  �޸���ʷ:��                                                         *
************************************************************************/
DWORD COp8153A::GetRangeMode(long lSlot,long IChan, long* iPWMRangeMode)
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
			
			ZeroMemory(szCmdString,1024);	
			sprintf(szCmdString, "sens%d:pow:rang?\r\n",nCurSlot,iPMChannel);
			
			//Set the wavelength
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
*  ��������:CompleteQuery                                              *
*  ����: ѯ���Ƿ����,���ڼ��ģ���Ƿ��Ѿ��������					   *
*  ����: ��                                                            *
*  ������������:��                                                     *
*  ���: ��                                                            *
*  ����ֵ:                                                             *
*        ������                                                        *
*  ����ֵ����:DWORD                                                    *
*  ��������:2013-10-17                                                 *
*  ������:yanx                                                         *
*  �޸���ʷ:��                                                         *
************************************************************************/
DWORD COp8153A::CompleteQuery()
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
	}
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
DWORD COp8153A::GetGPIBAress(long  *dblGpibAddress)
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
DWORD COp8153A::SetGPIBAress(long dblGpibAddress)
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
*  ��������:SetUnit											           *
*  ����: ���õ�λ    										    	   *
*  ����:															   *
*	1��iChan:ͨ����													   *
*   2��	lPWMUnit:��λ��0:dBm;1:mw						               *
*	������������:int,int											   *
*  ���: ��															   *
*  �������:��													       *
*  ����ֵ:                                                             *
*        ������                                                        *
*  ����ֵ����:DWORD                                                    *
*  ��������:2013-10-17                                                 *
*  ������:yanx                                                         *
*  �޸���ʷ:��                                                         *
************************************************************************/
DWORD COp8153A::SetUnit(long lSlot,long IChan, long IPWUMUnit)
{
    DWORD	dwErrorCode;
	TCHAR	szCmdString[1024];
	
	int nCurSlot = lSlot;
	try
	{
		ZeroMemory(szCmdString, 1024);
		
		sprintf(szCmdString, "sens%d:pow:unit %d\r\n",nCurSlot, IPWUMUnit);
		
		//Set Enable or disable
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
/***********************************************************************
*  ��������:SetWavelength											   *
*  ����: ���ò���   										           * 
*  ����:															   *
*	1��iChan:ͨ����													   *
*	2��dblWavelength:����(nm)										   *
*	������������:int,double											   *
*  ���: ��															   *
*  �������:��														   *
*  ����ֵ:                                                             *
*        ������                                                        *
*  ����ֵ����:DWORD                                                    *
*  ��������:2013-10-17                                                 *
*  ������:yanx                                                         *
*  �޸���ʷ:��                                                         *
************************************************************************/
DWORD COp8153A::SetWavelength(long lSlot,long IChan, double dblWL)
{
	DWORD	dwErrorCode;
	TCHAR	szCmdString[1024];
	int nCurSlot = lSlot;
	try
	{
		ZeroMemory(szCmdString, 1024);
		
		sprintf(szCmdString, "sens%d:pow:wave %.1fnm\r\n",nCurSlot, dblWL);

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
/***********************************************************************
*  ��������:SetAverageTime											   *
*  ����: ����ƽ��ʱ��												   *
*  ����:															   *
*	1��iChan:ͨ����													   *
*   2��	dblAvgTime��ƽ��ʱ�䣨ms��							 		   *
*	������������:int��double                                           *
*  ���: pdblPowerValue                                                *
*  ������ͣ�double												       *
*  ����ֵ:                                                             *
*        ������                                                        *
*  ����ֵ����:DWORD                                                    *
*  ��������:2013-10-17                                                 *
*  ������:yanx                                                         *
*  �޸���ʷ:��                                                         *
************************************************************************/
DWORD COp8153A::SetAverageTime(long lSlot,long IChan, double IPWMAverageTime)
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
		
		sprintf(szCmdString, "sens%d:pow:atime %.3fms\r\n", nCurSlot, IPWMAverageTime);

		//Set the wavelength
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
/***********************************************************************
*  ��������:SetAverageTime											   *
*  ����: ����ƽ��ʱ��												   *
*  ����:															   *
*	1��iChan:ͨ����													   *
*   2��	dblAvgTime��ƽ��ʱ�䣨ms��							 		   *
*	������������:int��double                                           *
*  ���: pdblPowerValue                                                *
*  ������ͣ�double												       *
*  ����ֵ:                                                             *
*        ������                                                        *
*  ����ֵ����:DWORD                                                    *
*  ��������:2013-10-17                                                 *
*  ������:yanx                                                         *
*  �޸���ʷ:��                                                         *
************************************************************************/
DWORD COp8153A::SetRangeMode (long lSlot,long IChan, long IPWMRangeMode )

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
//����˵����
//    ���ù��ʼ�Range
//Add by wanxin
//Time:20140828
/////////////////////////////////////////////////////////////
DWORD COp8153A::SetRange(long lSlot,long IChan, long lRange)
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
*  ��������:SetParameters											   *
*  ����: ���ò���   										           * 
*  ����:															   *
*	1.IChan:ͨ����													   *
*	2.bAutoRang:�Ƿ����Զ�ģʽ									       *
*	3.dblWL:ͨ����											           *
*	4.dblAverageTime:ƽ��ʱ��									       *
*	5.dblPwrRange:��̬��Χ(������ֶ�)								   *
*	������������:int,BOOL,double,double,double						   *
*  ���: ��															   *
*  �������:��														   *
*  ����ֵ:                                                             *
*        ������                                                        *
*  ����ֵ����:DWORD                                                    *
*  ��������:2013-10-17                                                 *
*  ������:yanx                                                         *
*  �޸���ʷ:��                                                         *
************************************************************************/
DWORD COp8153A::SetParameters(long lSlot,long IChan, BOOL bAutoRang, double dblWL, double dblAverageTime, double dblPwrRange)
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
*  ��������:Zero													   *
*  ����: ��̽ͷ��������   										       * 
*  ����:��															   *
*	������������:��													   *
*  ���: ��															   *
*  �������:��														   *
*  ����ֵ:                                                             *
*        ������                                                        *
*  ����ֵ����:DWORD                                                    *
*  ��������:2013-10-17                                                 *
*  ������:yanx                                                         *
*  �޸���ʷ:��                                                         *
************************************************************************/
DWORD COp8153A::Zero(long lSlot,long IChan)
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
		
		sprintf(chReadBuf,"sens%d:corr:coll:zero\r\n",nCurSlot,IChan);

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
*  ��������:GetDeviceInfo											   *
*  ����: ��ȡ�豸��Ϣ   										       * 
*  ����:��															   *
*	������������:��													   *
*  ���: pchInfo													   *
*  �������:CHAR*													   *
*  ����ֵ:                                                             *
*        ������                                                        *
*  ����ֵ����:DWORD                                                    *
*  ��������:2013-10-17                                                 *
*  ������:yanx                                                         *
*  �޸���ʷ:��                                                         *
************************************************************************/
DWORD COp8153A::GetDeviceInfo(CHAR * pchInfo)
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

DWORD COp8153A::SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle)
{
	DWORD   dwErrorCode = SUCCESS;
	//	LPCTSTR lpCommunicationInfo;
    
	dwErrorCode = m_Comm.SetDeviceHandle(pszDeviceAddr, handle);
	return dwErrorCode;
}
///////////////////////////////////////////////////////////////////
//����˵����
//    ���ù��ʼ�Ϊ��������С����ģʽ�������Ӧ�������С����
//Add by wanxin
////////////////////////////////////////////////////////////////////////
DWORD COp8153A::GetPMMaxMinPower(long lSlot,long IChan,double *pdbGetMax,double *pdbGetMin)
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
//����˵����
//    ���ù��ʼ�Ϊ��������С����ģʽ
//Add by wanxin
////////////////////////////////////////////////////////////////////////
DWORD COp8153A::SetPMMaxMinPowerStart(long lSlot,long IChan)
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
DWORD COp8153A::SetPMMinMaxStop(long lSlot,long IChan)
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

DWORD COp8153A::SetPMPowerOffset(long lSlot,long IChan,double dbPowerOffset)
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