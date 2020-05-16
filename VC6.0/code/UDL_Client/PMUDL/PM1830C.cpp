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
*  ��������:GetPower												   *
*  ����: ��ȡ����													   *
*  ����:															   *
*	1��IChan:ͨ����									 			       *
*	������������:long                                                   *
*  ���: pdblPowerValue                                                *
*  ������ͣ�double												       *
*  ����ֵ:                                                             *
*        ������                                                        *
*  ����ֵ����:DWORD                                                    *
*  ��������:2013-10-21                                                 *
*  ������:ris                                                          *
*  �޸���ʷ:��                                                         *
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
*  ��������:SetWavelength											   *
*  ����: ���ò���   										           * 
*  ����:															   *
*	1��IChan:ͨ����													   *
*	2��dblWavelength:����(nm)										   *
*	������������:int,double											   *
*  ���: ��															   *
*  �������:��														   *
*  ����ֵ:                                                             *
*        ������                                                        *
*  ����ֵ����:DWORD                                                    *
*  ��������:2013-10-21                                                 *
*  ������:ris                                                          *
*  �޸���ʷ:��                                                         *
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
*  ��������:GetWavelength											   *
*  ����: ��ȡ����    										    	   *
*  ����:															   *
*	1��IChan:ͨ����													   *
*	������������:int												   *
*  ���: pdblWL(��������λnm)							     		   *
*  �������:double													   *
*  ����ֵ:                                                             *
*        ������                                                        *
*  ����ֵ����:DWORD                                                    *
*  ��������:2013-10-17                                                 *
*  ������:ris                                                          *
*  �޸���ʷ:��                                                         *
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
*  ��������:SetRangeMode											   *
*  ����: ���ö�̬��Χ    											   *
*  ����:															   *
*	1��IChan:ͨ����													   *
*   2��	bAtuo:ģʽ(1:�Զ�;����ֵ:�ֶ����õ�λֵ,0Ϊ1��λ)              *
*	������������:int,int											   *
*  ���: ��															   *
*  �������:��													       *
*  ����ֵ:                                                             *
*        ������                                                        *
*  ����ֵ����:DWORD                                                    *
*  ��������:2013-10-17                                                 *
*  ������:ris                                                          *
*  �޸���ʷ:��                                                         *
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
//����˵����
//    ���ù��ʼ�Range
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
*  ��������:GetRangeMode											   *
*  ����: ��ȡ��̬��Χ   										       *
*  ����:															   *
*	1��iChan:ͨ����													   *
*	������������:int												   *
*  ���: iPWMRangeMode	(1:�Զ�;����ֵ:�ֶ����õ�λֵ,0Ϊ1��λ)		   *
*  �������:int													       *
*  ����ֵ:                                                             *
*        ������                                                        *
*  ����ֵ����:DWORD                                                    *
*  ��������:2013-10-17                                                 *
*  ������:ris                                                         *
*  �޸���ʷ:��                                                         *
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
*  ��������:SetUnit											           *
*  ����: ���õ�λ    										    	   *
*  ����:															   *
*	1��IChan:ͨ����													   *
*   2��	lPWMUnit:��λ��0:dBm;1:mw;2:dB;3:dBm;4:Ref					   *
*	������������:int,int											   *
*  ���: ��															   *
*  �������:��													       *
*  ����ֵ:                                                             *
*        ������                                                        *
*  ����ֵ����:DWORD                                                    *
*  ��������:2013-10-17                                                 *
*  ������:ris                                                          *
*  �޸���ʷ:��                                                         *
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
*  ��������:GetUnit											           *
*  ����: ��ȡ��λ    										    	   *
*  ����:															   *
*	1��IChan:ͨ����													   *
*	������������:int												   *
*  ���: piUnit(0��ʾdBm��1��ʾw,2��ʾdB,4��ʾRef)				     *
*  �������:int													       *
*  ����ֵ:                                                             *
*        ������                                                        *
*  ����ֵ����:DWORD                                                    *
*  ��������:2013-10-17                                                 *
*  ������:ris                                                          *
*  �޸���ʷ:��                                                         *
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
*  ��������:GetAverageTime											   *
*  ����: ��ȡƽ��ʱ��    										       *
*  ����:															   *
*	1��iChan:ͨ����													   *
*	������������:int												   *
*  ���: pdblAverageTime(1=Slow; 2=medium; 3=fast)					   *
*  �������:double													   *
*  ����ֵ:                                                             *
*        ������                                                        *
*  ����ֵ����:DWORD                                                    *
*  ��������:2013-10-17                                                 *
*  ������:ris                                                          *
*  �޸���ʷ:��                                                         *
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
*  ��������:GetAverageTime											   *
*  ����: ��ȡƽ��ʱ��    										       *
*  ����:															   *
*	1��IChan:ͨ����													   *
*	������������:int												   *
*  ���: pdblAverageTime(1=Slow; 2=medium; 3=fast)					   *
*  �������:double													   *
*  ����ֵ:                                                             *
*        ������                                                        *
*  ����ֵ����:DWORD                                                    *
*  ��������:2013-10-21                                                 *
*  ������:ris                                                          *
*  �޸���ʷ:��                                                         *
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
*  ��������:SetEcho      											   *
*  ����:                										       *
*  ����:															   *
*	1��bEchoOff:ͨ����												   *
*	������������:BOOL												   *
*  ���: ��															   *
*  �������:��													       *
*  ����ֵ:                                                             *
*        TRUE:�ɹ�;FALSE:ʧ��                                          *
*  ����ֵ����:DWORD                                                    *
*  ��������:2013-10-21                                                 *
*  ������:ris                                                          *
*  �޸���ʷ:��                                                         *
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
*  ��������:CloseDevice												   *
*  ����: �ر��豸   										           * 
*  ����:��															   *
*	������������:��													   *
*  ���: ��															   *
*  �������:��														   *
*  ����ֵ:                                                             *
*        ������                                                        *
*  ����ֵ����:DWORD                                                    *
*  ��������:2013-10-21                                                 *
*  ������:ris                                                          *
*  �޸���ʷ:��                                                         *
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
*  ��������:SetStoRef      											   *
*  ����:                										       *
*  ����:��															   *
*	������������:��  												   *
*  ���: ��															   *
*  �������:��													       *
*  ����ֵ:                                                             *
*        TRUE:�ɹ�;FALSE:ʧ��                                          *
*  ����ֵ����:DWORD                                                    *
*  ��������:2013-10-21                                                 *
*  ������:ris                                                          *
*  �޸���ʷ:��                                                         *
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
*  ��������:Zero													   *
*  ����: ��̽ͷ��������   										       * 
*  ����:��															   *
*	������������:��													   *
*  ���: ��															   *
*  �������:��														   *
*  ����ֵ:                                                             *
*        ������                                                        *
*  ����ֵ����:DWORD                                                    *
*  ��������:2013-10-21                                                 *
*  ������:ris                                                          *
*  �޸���ʷ:��                                                         *
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
*  ��������:2013-10-21                                                 *
*  ������:ris                                                         *
*  �޸���ʷ:��                                                         *
************************************************************************/
DWORD CPM1830C::OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle)
{
	//CString strComPort;	
	DWORD   dwErrorCode;

	dwErrorCode = m_DevComHandle.OpenDevice(pszDeviceAddr,*ComHandle);
	
	return dwErrorCode;
}
/***********************************************************************
*  ��������:SetParameters											   *
*  ����: ���ò���   										           * 
*  ����:															   *
*	1.IChan:ͨ����													   *
*	2.bAutoRange:�Ƿ����Զ�ģʽ									       *
*	3.dblWavelength:ͨ����											   *
*	4.dblAvgTile:ƽ��ʱ��									           *
*	5.dblPwrRange:��̬��Χ(������ֶ�)								   *
*	������������:int,BOOL,double,double,double						   *
*  ���: ��															   *
*  �������:��														   *
*  ����ֵ:                                                             *
*        ������                                                        *
*  ����ֵ����:DWORD                                                    *
*  ��������:2013-10-21                                                 *
*  ������:ris                                                        *
*  �޸���ʷ:��                                                         *
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
*  ��������:SetUnit											           *
*  ��ע:�˹�����δ��ͨ                                             *
************************************************************************/
DWORD CPM1830C::SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle)
{
	DWORD   dwErrorCode = SUCCESS;
//	LPCTSTR lpCommunicationInfo;
    
	dwErrorCode = m_DevComHandle.SetDeviceHandle(pszDeviceAddr, handle);
	return dwErrorCode;
}

/***********************************************************************
*  ��������:SetUnit											           *
*  ��ע:��PM�˹�����δ��ͨ                                             *
************************************************************************/
//DWORD CPM1830C::SetMode(long lChIndex,DWORD dwMode)
//{
//	DWORD dwErrorCode=0;
//	return dwErrorCode;
//}
/***********************************************************************
*  ��������:SetUnit											           *
*  ��ע:��PM�˹�����δ��ͨ                                             *
************************************************************************/
//DWORD CPM1830C::GetMode(long lChIndex,DWORD &dwMode)
//{
//	DWORD dwErrorCode=0;
//	return dwErrorCode;
//}
/***********************************************************************
*  ��������:SetUnit											           *
*  ��ע:��PM�˹�����δ��ͨ                                             *
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
//����˵����
//    ���ù��ʼ�Ϊ��������С����ģʽ�������Ӧ�������С����
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
//����˵����
//    ���ù��ʼ�Ϊ��������С����ģʽ
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