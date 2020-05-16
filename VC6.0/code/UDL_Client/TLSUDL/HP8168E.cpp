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
*  ��������:2013-11-25                                                 *
*  ������:Hanfei Zhao                                                  *
*  �޸���ʷ:��                                                         *
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
//����˵����
//    ����Aglient 81960A��������slot��
//Add by wanxin
//Time��20160308
/////////////////////////////////////////////////////////////////////////
DWORD  CHP8168ETLS::SetTLSSlotIndex(int nSlotIndex)
{
	DWORD dwErrorCode = SUCCESS;
	m_nSlotIndex = nSlotIndex;
    return dwErrorCode;
}
//////////////////////////////////////////////////////////////////
//����˵����
//    ���ü�������CCģʽ
//Add by wanxin
//Time��20140807
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
//����˵����
//    ���ü������ĵĲ���
//Add by wanxin
//Time��20140807
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
//����˵����
//    ���ü������ĵĹ���
//Add by wanxin
//Time��20140807
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
//����˵����
//    ����ģ�鼤������������
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
//����˵����
//    ����ģ�鼤����Ƶ��
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
//����˵����
//    ���ü������ĵĹ��ʵĵ�λ
//Add by wanxin
//Time��20140807
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
//����˵����
//    ���ü������Ĳ����������ߵ͹��ʹ�ò��øú���
//Add by wanxin
//Time��20140807
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
//����˵����
//    ���ü������ļ������������ر�״̬
//Add by wanxin
//Time��20140807
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
//����˵����
//    ���ü�������MainFrame��handle���
//Add by wanxin
//Time��20140807
//////////////////////////////////////////////////////////////
DWORD CHP8168ETLS::SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle)
{
	DWORD dwErrorCode = SUCCESS;
	dwErrorCode = m_Comm.SetDeviceHandle(pszDeviceAddr, handle);

	return dwErrorCode;
}
//////////////////////////////////////////////////////////////////
//����˵����
//    �رոü�����MainFrame�豸���
//Add by wanxin
//Time��20140807
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
//����˵����
//     ��ü���������
//Add by wanxin
//Time��20140827
////////////////////////////////////////////////////////////
DWORD CHP8168ETLS::GetTLSSettings(long lChIndex,double* pdblWavelength,double* pdblPower,BYTE* pdCtrlState)
{
	DWORD dwErrorCode = SUCCESS;
	char chSendBuf[MAX_PATH];
	BYTE bStatus;
	try
	{				
		
		//��ò���
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
		
		//��ù���
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
		//��ÿ���״̬
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
			//���CC״̬�ж�״̬
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
//����˵����
//    ��ȡTLS�������
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
//����˵����
//    ����ģ�鼤���������
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
//����˵����
//    �رոü�����MainFrame�豸���
//Add by wanxin
//Time��20140807
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
//����˵����
//    ���ɨ�貨������
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