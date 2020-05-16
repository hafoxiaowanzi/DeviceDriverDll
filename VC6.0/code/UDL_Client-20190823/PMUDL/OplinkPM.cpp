// OplinkPM.cpp: implementation of the OplinkPM class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\\include\\PM.h"
//#include <WINSOCK.H>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
OplinkPM::OplinkPM()
{

}

OplinkPM::~OplinkPM()
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
DWORD OplinkPM::OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle)
{
	DWORD dwErrorCode;
//	WORD wAddr;
	TCHAR szBuf[MAX_PATH]={0};
	try
	{
		dwErrorCode=m_Comm.OpenDevice(pszDeviceAddr, *ComHandle);
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
*	2��dblWL:����(nm)										           *
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
DWORD OplinkPM::SetWavelength(long lSlot,long IChan, double dblWL)
{
	DWORD dwErrorCode;
	CHAR pchCmd[MAX_PATH];
	CHAR chReadBuf[MAX_PATH];
	long lTempWL;
	long lWL;
	long iPMSlot;
	long iPMChannel;

    try
	{
	   iPMSlot=(IChan-1)/2;
	   iPMChannel=(IChan-1)%2;
		if(dblWL<850)
		{
			dblWL=850;
		}
		else if(dblWL>1640)
		{
			dblWL=1640;
		}
		lWL=(long)(dblWL*10000);

		ZeroMemory(pchCmd, MAX_PATH);
		sprintf(pchCmd, "SENS%d,CHAN%d:POW:WAV %dnm\r\n", lSlot, IChan, lWL);
		dwErrorCode=m_Comm.WriteDevice(pchCmd,strlen(pchCmd));
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_WL;
		}

		Sleep(100);

		ZeroMemory(pchCmd, MAX_PATH);
		sprintf(pchCmd, "SENS%d,CHAN%d:POW:WAV?\r\n", lSlot, IChan);
		dwErrorCode=m_Comm.WriteDevice(pchCmd,strlen(pchCmd));
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_WL;
		}
		Sleep(100);
		ZeroMemory(chReadBuf, MAX_PATH);
		dwErrorCode=m_Comm.ReadDevice(chReadBuf,MAX_PATH);
		
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_WL;
		}

		lTempWL = atol(chReadBuf);

		lTempWL = (long)(lTempWL + 0.5);

		if(lTempWL != lWL)
		{
			return FALSE;
		}
	}
	catch(...)
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
*  ���: pdblPower                                                     *
*  ������ͣ�double*												   *
*  ����ֵ:                                                             *
*        ������                                                        *
*  ����ֵ����:DWORD                                                    *
*  ��������:2013-10-17                                                 *
*  ������:yanx                                                         *
*  �޸���ʷ:��                                                         *
************************************************************************/
DWORD OplinkPM::GetPower(long lSlot,long IChan, double *pdblPower)
{
	TCHAR pchCmd[MAX_PATH];

	TCHAR chReadBuf[MAX_PATH];

	DWORD dwErrorCode;

    try
	{
		ZeroMemory(pchCmd, MAX_PATH);
		sprintf(pchCmd, "SENS%d,CHAN%d:POW:READ?\r\n", lSlot, IChan);
		dwErrorCode=m_Comm.WriteDevice(pchCmd,strlen(pchCmd));
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_PM;
		}
		Sleep(100);
		ZeroMemory(chReadBuf, MAX_PATH);
		dwErrorCode=m_Comm.ReadDevice(chReadBuf,MAX_PATH);
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_PW;
		}
		*pdblPower=atof(chReadBuf);

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
*  ��������:GetDeviceInfo											   *
*  ��ע:��PM�˹�����δ��ͨ                                             *
************************************************************************/
DWORD OplinkPM::GetUnit(long lSlot,long IChan, long *piUnit)
{
	DWORD dwErrorCode=0;

	*piUnit=0;
	
	return dwErrorCode;
}
/***********************************************************************
*  ��������:GetDeviceInfo											   *
*  ��ע:��PM�˹�����δ��ͨ                                             *
************************************************************************/
DWORD OplinkPM::GetAverageTime(long lSlot,long IChan, double *pdblAverageTime)
{
	DWORD dwErrorCode=0;

	*pdblAverageTime=0;
	
	return dwErrorCode;
}
/***********************************************************************
*  ��������:GetDeviceInfo											   *
*  ��ע:��PM�˹�����δ��ͨ                                             *
************************************************************************/
DWORD OplinkPM::GetRangeMode(long lSlot,long IChan,  long* iPWMRangeMode)
{
	DWORD dwErrorCode=0;

	*iPWMRangeMode=0;
	
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
*  ������:yanx                                                         *
*  �޸���ʷ:��                                                         *
************************************************************************/
DWORD OplinkPM::GetWavelength(long lSlot,long IChan, double *pdblWL)
{
	TCHAR pchCmd[MAX_PATH];

	TCHAR chReadBuf[MAX_PATH];

	DWORD dwErrorCode;


    try
	{
		ZeroMemory(pchCmd, MAX_PATH);
		sprintf(pchCmd, "SENS%d,CHAN%d:POW:READ?", lSlot, IChan);
		dwErrorCode=m_Comm.WriteDevice(pchCmd,strlen(pchCmd));
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_PM;
		}
		Sleep(100);
		dwErrorCode=m_Comm.ReadDevice(chReadBuf,MAX_PATH);
		if(dwErrorCode)
		{
			return dwErrorCode|ERROR_PW;
		}
		*pdblWL=(double)(atol(chReadBuf)/10000);

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
*  ��������:SetCalibrate											   *
*  ����: ���õ�ǰ����Ϊ0dBm��У׼�ã�   							   * 
*  ����:															   *
*      IChan:ͨ��													   *
*	������������:int												   *
*  ���: ��															   *
*  �������:��														   *
*  ����ֵ:                                                             *
*        ������                                                        *
*  ����ֵ����:DWORD                                                    *
*  ��������:2013-10-17                                                 *
*  ������:yanx                                                         *
*  �޸���ʷ:��                                                         *
************************************************************************/
DWORD OplinkPM::SetCalibrate(long lSlot,long IChan)
{
	char pchCmd[256];
//	char pchTemp[256];
//	char recvBuf[256];
//	WORD wSendLen;
	DWORD dwErrorCode;

    try
	{
		ZeroMemory(pchCmd, 256);
		sprintf(pchCmd, "SENS%d,CHAN%d:POW:SETCAL:00000000", lSlot, IChan);
		dwErrorCode=m_Comm.WriteDevice(pchCmd,strlen(pchCmd));
	}
	catch (...) {
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
DWORD OplinkPM::CloseDevice()
{
	DWORD dwErrorCode;
	dwErrorCode=m_Comm.CloseDevice();

	return dwErrorCode;
}
/***********************************************************************
*  ��������:SetParameters											   *
*  ����: ���ò���   										           * 
*  ����:															   *
*	1.iChan:ͨ����													   *
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
*  ��������:2013-10-17                                                 *
*  ������:yanx                                                         *
*  �޸���ʷ:��                                                         *
************************************************************************/
DWORD OplinkPM::SetParameters(long lSlot,long IChan, BOOL bAutoRange,double dblWavelength, double dblAvgTime, double dblPwrRange)
{
	DWORD	dwErrorCode;
	try
	{
		// Set PWM Wavelength
		dwErrorCode=SetWavelength(lSlot,IChan, dblWavelength);

		if(dwErrorCode)
		{
			return dwErrorCode;
		}
		// Set PWM to a-uto-range
		dwErrorCode=SetRangeMode(lSlot,IChan, bAutoRange);
		if(dwErrorCode)
		{
			return dwErrorCode;
		}
		// Set PWM average time 1ms
		dwErrorCode=SetAverageTime(lSlot,IChan,dblAvgTime);
	}	
	catch(...)
	{
		return UNEXPECT_OCCUR;
	}

	return dwErrorCode;	
}
/***********************************************************************
*  ��������:SetUnit											           *
*  ��ע:��PM�˹�����δ��ͨ                                             *
************************************************************************/
DWORD OplinkPM::SetUnit(long lSlot,long IChan,long lPWMUnit)
{
	DWORD dwErrorCode=0;
	return dwErrorCode;
}
/***********************************************************************
*  ��������:SetAverageTime											           *
*  ��ע:��PM�˹�����δ��ͨ                                             *
************************************************************************/
DWORD OplinkPM::SetAverageTime(long lSlot,long IChan, double dblAvgTime)
{
	DWORD dwErrorCode=0;
	return dwErrorCode;
}
/***********************************************************************
*  ��������:SetRangeMode											   *
*  ��ע:��PM�˹�����δ��ͨ                                             *
************************************************************************/
DWORD OplinkPM::SetRangeMode(long lSlot,long IChan, long bAutoRange)
{
	DWORD dwErrorCode=0;
	
	return dwErrorCode;
}
////////////////////////////////////////////////////////////
//����˵����
//    ���ù��ʼ�Range
//Add by wanxin
//Time:20140828
/////////////////////////////////////////////////////////////
DWORD OplinkPM::SetRange(long lSlot,long IChan, long lRange)
{
	DWORD dwErrorCode=SUCCESS;
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
*  ��������:Zero											           *
*  ��ע:��PM�˹�����δ��ͨ                                             *
************************************************************************/
DWORD OplinkPM::Zero(long lSlot,long IChan)
{
	DWORD dwErrorCode=0;
	return dwErrorCode;
}

/***********************************************************************
*  ��������:GetDeviceInfo											   *
*  ��ע:��PM�˹�����δ��ͨ                                             *
************************************************************************/
DWORD OplinkPM::GetDeviceInfo(CHAR * pchInfo)
{
	DWORD dwErrorCode=0;
	return dwErrorCode;
}

DWORD OplinkPM::SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle)
{
	DWORD   dwErrorCode = SUCCESS;
    
	dwErrorCode = m_Comm.SetDeviceHandle(pszDeviceAddr, handle);
	return dwErrorCode;
}
DWORD OplinkPM::PrepareScan(long lSlot,long lChIndex,stScanParam* lScanParam)
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

DWORD OplinkPM::SetPMScanStart(long lSlot,long lChIndex)
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

DWORD OplinkPM::getLambdaScanPMResult(long lSlot,long lChIndex,double* pdbPMArry)
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

DWORD OplinkPM::SetPMScanStop(long lSlot,long lChIndex)
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


DWORD OplinkPM::SetPMScanTriggerStop(long lSlot,long lChIndex)
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
DWORD OplinkPM::GetPMMaxMinPower(long lSlot,long IChan,double *pdbGetMax,double *pdbGetMin)
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
DWORD OplinkPM::SetPMMaxMinPowerStart(long lSlot,long IChan)
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
DWORD OplinkPM::SetPMMinMaxStop(long lSlot,long IChan)
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
DWORD OplinkPM::SetPMPowerOffset(long lSlot,long IChan,double dbPowerOffset)
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