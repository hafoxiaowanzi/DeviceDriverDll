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
COp816XCtrl::COp816XCtrl()
{

}

/////////////////////////////////////////////////////////////////////////////
// COp816XCtrl::~COp816XCtrl - Destructor

COp816XCtrl::~COp816XCtrl()
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
DWORD COp816XCtrl::OpenDevice(LPCTSTR pszDeviceAddr, unsigned long *ComHandle)
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
//////////////////////////////////////////////////////////////////
//����˵����
//    ���ü�����slot
//Add by wanxin
//Time��20140807
//////////////////////////////////////////////////////////////
DWORD COp816XCtrl::SetTLSSlotIndex(int nSlotIndex)
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
DWORD COp816XCtrl::SetCoherenceControl(BOOL bEnable)
{
	DWORD dwErrorCode = SUCCESS;
	char chReadBuf[100];
	try
	{	
		ZeroMemory(chReadBuf,100);
		sprintf(chReadBuf, "SOUR0:AM:STAT %d\r\n", bEnable);
		dwErrorCode = m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_COHERENCE_CONTROL;
		} 

		ZeroMemory(chReadBuf,100);
		sprintf(chReadBuf, "SOUR0:AM:SOUR COHC\r\n",bEnable);
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
DWORD COp816XCtrl::SetWavelength(long lChIndex, double dblWL)
{
	DWORD dwErrorCode = SUCCESS;
	char chReadBuf[100];
	try
	{
		ZeroMemory(chReadBuf, sizeof(char)*100);
		sprintf(chReadBuf, "wav %.3fnm\r\n",dblWL);
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
DWORD COp816XCtrl::SetSourcePower(long lChIndex, double dblPW)
{
	DWORD dwErrorCode = SUCCESS;
	char szBuf[256];

	try
	{
		ZeroMemory(szBuf,sizeof(char)*256);
		sprintf(szBuf, "sour:pow %.3fdbm\r\n", dblPW);
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
DWORD COp816XCtrl::SetMaxOutput(long lChIndex)
{
	
	DWORD dwErrorCode = SUCCESS;
	char chSendBuf[MAX_PATH];
	
	try
	{
		ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"sour0:pow max\r\n");
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw "Send TLS Max Power error";
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
//    ����ģ�鼤����Ƶ��
//Add by wanxin
///////////////////////////////////////////////////////////////////////
DWORD COp816XCtrl::SetTLSFrequency(long lChIndex,double dblFrequrency)
{
	DWORD dwErrorCode = SUCCESS;
	char chSendBuf[MAX_PATH];
	
	try
	{
		int nFre =(int)dblFrequrency;
		ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"sour0:am:freq %d\r\n",nFre);
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
DWORD COp816XCtrl::SetSourceUnit(long lChIndex, long lUnit)
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
//////////////////////////////////////////////////////////////////
//����˵����
//    ���ü������Ĳ����������ߵ͹��ʹ�ò��øú���
//Add by wanxin
//Time��20140807
//////////////////////////////////////////////////////////////
DWORD COp816XCtrl::SetParameters(long lChIndex, BOOL bLowSSE, double dblPower, double dblWavelength)
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
			ZeroMemory(chReadBuf,sizeof(char)*100);
			sprintf(chReadBuf, "output0:path lows\r\n");
			dwErrorCode = m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
			if (SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_SWITCH_CHANNEL;
			}
		}
		else
		{
			ZeroMemory(chReadBuf,sizeof(char)*100);
			sprintf(chReadBuf, "output0:path high\r\n");
			dwErrorCode = m_Comm.WriteDevice(chReadBuf,strlen(chReadBuf));
			if (SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_SWITCH_CHANNEL;
			}
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
DWORD COp816XCtrl::SetOutputEnable(BOOL bEnable)
{
	DWORD dwErrorCode = SUCCESS;
	char chReadBuf[100];
	try
	{
		ZeroMemory(chReadBuf,sizeof(char)*100);
		sprintf(chReadBuf, "output %d\r\n",bEnable);
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
DWORD COp816XCtrl::SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle)
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
DWORD COp816XCtrl::CloseDevice()
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
DWORD COp816XCtrl::GetTLSSettings(long lChIndex,double* pdblWavelength,double* pdblPower,BYTE* pdCtrlState)
{
	DWORD dwErrorCode = SUCCESS;
	char chSendBuf[MAX_PATH];
	BYTE bStatus;
	try
	{				
		
		//��ò���
		ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"sour0:wav?\r\n");
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
		sprintf(chSendBuf,"sour0:pow?\n");
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
		sprintf(chSendBuf,"output stat?\n");
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
			sprintf(chSendBuf,"sour0:am:sour?\n");
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
/////////////////////////////////////////////////////////
//����˵����
//     ���ģ�������С�Ĳ�����Χ
//Add by wanxin
//Time��20140807
////////////////////////////////////////////////////////////
DWORD COp816XCtrl::GetTLSWLRange(double &dbWLMin,double &dbWLMax)
{
	char chSendBuf[MAX_PATH];
	DWORD dwErrorCode = SUCCESS;
	try
	{				
		
		//�����С����range
		ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"sour0:wav? min\n");
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
		dbWLMin = atof(chSendBuf)*1E9;
		
		//�����󲨳�range
		ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"sour0:wav? max\n");
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
		dbWLMax = atof(chSendBuf)*1E9;				
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

//////////////////////////////////////////////////////
//����˵��
//    ���ɨ�����ʼ������Χ
//Add by wanxin
//Time:20140807
///////////////////////////////////////////////////////
DWORD COp816XCtrl::GetScanWLRange(double &dbStartWL,double &dbStopWL)
{
	char chSendBuf[MAX_PATH];
	int nCount;
	DWORD dwErrorCode = SUCCESS;
	try
	{								
		//��ȡɨ����ʼ����
		nCount = 0;		
		while (TRUE)
		{
			ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
			sprintf(chSendBuf, "sour0:wav:swe:star?\r\n");
			dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
			if (SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_TLS_SCAN_WLRANGE;
			}					
			ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
			dwErrorCode = m_Comm.ReadDevice(chSendBuf,MAX_PATH);
			if (SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_TLS_SCAN_WLRANGE;
			}
			
			dbStartWL = atof(chSendBuf)*1E9;
			if (dbStartWL > 0.0)
			{
				break;
			}
			nCount++;
			if (nCount > 100)
			{
				throw dwErrorCode|ERROR_TLS_SCAN_WLRANGE;
			}
		}
		//��ȡɨ��ֹͣ����
		nCount = 0;
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		while (TRUE)
		{
			ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
			sprintf(chSendBuf, "sour0:wav:swe:stop?\n");
			dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
			if (SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_TLS_SCAN_WLRANGE;
			}	
			ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
			dwErrorCode = m_Comm.ReadDevice(chSendBuf,MAX_PATH);
			if (SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_TLS_SCAN_WLRANGE;
			}
			
			dbStopWL = atof(chSendBuf)*1E9;
			if (dbStopWL > 0.0)
			{
				break;
			}
			nCount++;
			if (nCount > 100)
			{
				throw dwErrorCode|ERROR_TLS_SCAN_WLRANGE;
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
DWORD COp816XCtrl::ReadTLSPower(double &dbPower)
{	
	char chSendBuf[MAX_PATH];
	DWORD dwErrorCode = SUCCESS;
	try
	{				
		
		ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"sour0:pow?\n");
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

///////////////////////////////////////////////////////////////////////
//����˵����
//    ������õ�ɨ�����
//Add by wanxin
//Time:20140807
///////////////////////////////////////////////////////////////////////
BOOL COp816XCtrl::GetScanParameter(stScanParam *pSettingParam)
{
	char chSendBuf[MAX_PATH];
	double dbStartWL,dbStopWL;
	double dbTLSPower;
	DWORD dwErrorCode = SUCCESS;
	try
	{				
		
		//���ɨ�貨��
		dwErrorCode = GetScanWLRange(dbStartWL,dbStopWL);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_WLRANGE;
		}
		pSettingParam->m_dblStartWL = dbStartWL;
		pSettingParam->m_dblStopWL = dbStopWL;
		
		//���ɨ���speed
		ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"sour0:wav:swe:spe?\n");
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_WLRANGE;
		}	
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		dwErrorCode = m_Comm.ReadDevice(chSendBuf,MAX_PATH);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_WLRANGE;
		}
		double dbTemp = atof(chSendBuf);
		pSettingParam->m_nSpeed = (int)(dbTemp*1E9);
		
		//���ɨ���step
		ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"sour0:wav:swe:step?\n");
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_WLRANGE;
		}	
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		dwErrorCode = m_Comm.ReadDevice(chSendBuf,MAX_PATH);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_WLRANGE;
		}
		pSettingParam->m_dblStepSize = atof(chSendBuf);
		
		if (!ReadTLSPower(dbTLSPower))
		{
			throw "Read setting power error";
		}
		pSettingParam->m_dblTLSPower = dbTLSPower;
		
	}
	catch(char *pstrMsg)
	{
		AfxMessageBox(pstrMsg);
		return FALSE;
	}
	return TRUE;
}

///////////////////////////////////////////////////////////////////
//����˵����
//    �жϵ�ǰ��ɨ������Ƿ�仯,������õ���仯�Ĳ�ͬ�򷵻�FASLE
//    ����ж���ͬ�򷵻�TRUE
//Add by wanxin
///////////////////////////////////////////////////////////////////
BOOL COp816XCtrl::JudgeScanParameter()
{
	stScanParam stReadInof;
	BOOL bModify = FALSE;
	try
	{
		if (!GetScanParameter(&stReadInof))
		{
			throw"Read scan setting information error";
		}
		if (fabs(m_pScanParam->m_dblTLSPower - stReadInof.m_dblTLSPower)>0.1
			||fabs(m_pScanParam->m_dblStartWL-0.5 - stReadInof.m_dblStartWL)>0.1
			||fabs(m_pScanParam->m_dblStopWL+0.5 - stReadInof.m_dblStopWL)>0.1
			||fabs(m_pScanParam->m_dblStepSize - stReadInof.m_dblStepSize)>0.001
			||m_pScanParam->m_nSpeed != stReadInof.m_nSpeed)
		{
			bModify = FALSE;
		}
		else
		{
			bModify = TRUE;
		}
	}
	catch(...)
	{
		bModify = FALSE;
	}
	return bModify;
}

//////////////////////////////////////////////////
//����˵����
//    ���ü�����ɨ��ֹͣ����
//Add by wanxin
//////////////////////////////////////////////////
BOOL COp816XCtrl::SetScanStop()
{
	char chSendBuf[MAX_PATH];
	int nCount;
	int CurentFlag;
	DWORD dwErrorCode = SUCCESS;
	try
	{							
		
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		sprintf(chSendBuf, "sour0:wav:swe:flag?\n");
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw "Send read swe state error";
		}	

		nCount = 0;		
		while (TRUE)
		{
			ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
			dwErrorCode = m_Comm.ReadDevice(chSendBuf,MAX_PATH);
			if (SUCCESS != dwErrorCode)
			{
				throw "Send TLS scan stop error";
			}
			CurentFlag = atoi(chSendBuf);
			if (CurentFlag == 0)
			{
				break;
			}
			else
			{
				ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
				sprintf(chSendBuf, "sour0:wav:swe 0\n");
				dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
				if (SUCCESS != dwErrorCode)
				{
					throw "Send TLS scan stop error";
				}
				Sleep(2000);
				break;
			}
			nCount++;
			if (nCount > 100)
			{
				throw"Set TLS scan stop error";
			}
		}		
	}
	catch(char *pstrMsg)
	{
		AfxMessageBox(pstrMsg);
		return FALSE;
	}
	return TRUE;	
}

//////////////////////////////////////////////////////////////////////////
//����˵����
//    ����ɨ����ʼ����
//Add by wanxin
/////////////////////////////////////////////////////////////////////////
BOOL COp816XCtrl::SetScanWLRange(double dbWLStart,double dbWLStop)
{
	char chSendBuf[MAX_PATH];
	DWORD dwErrorCode = SUCCESS;
	try
	{				
		
		//���ÿ�ʼɨ�貨��
		ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"sour%d:wav:swe:star %.3fNM\n",dbWLStart);
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw "Send TLS scan stop error";
		}
		
		//����ֹͣɨ�貨��
		ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"sour%d:wav:swe:stop %.3fNM\n",dbWLStop);
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw "Send TLS scan stop error";
		}		
	}
	catch(char *pstrMsg)
	{
		AfxMessageBox(pstrMsg);
		return FALSE;
	}
	return TRUE;
}
/////////////////////////////////////////////////////////////////////
//����˵����
//    ����ģ�鼤���������
//Add by wanxin
///////////////////////////////////////////////////////////////////////
BOOL COp816XCtrl::SetTLSPower(double dbPower)
{
	char chSendBuf[MAX_PATH];
	DWORD dwErrorCode = SUCCESS;
	try
	{						
		ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"sour0:pow %.3fDBM\n",dbPower);
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

//////////////////////////////////////////////////////////////////
//����˵����
//    �رոü�����MainFrame�豸���
//Add by wanxin
//Time��20140807
//////////////////////////////////////////////////////////////
DWORD COp816XCtrl::PrepareScan(long lChIndex,stScanParam* lScanParam)
{
	char chSendBuf[MAX_PATH];
	double dbStartWL,dbStopWL;
	double dbReadStartWL,dbReadStopWL;
	DWORD dwErrorCode = SUCCESS;
	try
	{				
		m_pScanParam = lScanParam;
		if (!GetTLSWLRange(dbStartWL,dbStopWL))
        {
			throw dwErrorCode|ERROR_GET_TLS_RANGE;
        }
		if (m_pScanParam->m_dblStartWL < dbStartWL || m_pScanParam->m_dblStopWL > dbStopWL)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_WLRANGE;
		}
		//�������õ�ɨ�跶Χ��ɨ0.05nm
		dbStartWL = m_pScanParam->m_dblStartWL - 0.5;	
		dbStopWL = m_pScanParam->m_dblStopWL + 0.5;
		
		m_pScanParam->m_dwSampleCount  = (DWORD)((m_pScanParam->m_dblStopWL - m_pScanParam->m_dblStartWL)/m_pScanParam->m_dblStepSize + 0.5);		
		
		//����ɨ��ģʽΪcontinueģʽ
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		sprintf(chSendBuf, "sour0:wav:swe:mode cont\n");
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_GET_TLS_RANGE;
		}
		//����RepeatģʽΪonewģʽ
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		sprintf(chSendBuf, "sour%0:wav:swe:rep onew\n");
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_PREPARE;
		}
		//�жϵ�ǰɨ������Ƿ�
		if (!JudgeScanParameter())
		{
			// 		//���ܼ���������ɨ��״̬���ǲ���ɨ��״̬��
			// 		//�ȷ���ֹͣɨ��ָ��	
			if (!SetScanStop())
			{
				throw dwErrorCode|ERROR_TLS_SCAN_PREPARE;
			}
			//����ɨ�����ʼ����
			if (!SetScanWLRange(dbStartWL,dbStopWL))
			{
				throw dwErrorCode|ERROR_TLS_SCAN_PREPARE;
			}
			//�ض�ɨ�����ʼ����
			if (!GetScanWLRange(dbReadStartWL,dbReadStopWL))
			{
				throw dwErrorCode|ERROR_TLS_SCAN_PREPARE;
			}
			//�ж����õ�ɨ����ʼ�������õ���ʼ�����Ƿ���ͬ
			if (fabs(dbStartWL - dbReadStartWL) > 0.01 || fabs(dbStopWL - dbReadStopWL) > 0.01 )
			{
				throw dwErrorCode|ERROR_TLS_SCAN_PREPARE;
			}
			//����ɨ���ٶ�
			ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
			if (m_pScanParam->m_nSpeed > 40) 
			{
				sprintf(chSendBuf, "sour0:wav:swe:spe 0.5nm/s\n",m_pScanParam->m_nSpeed);
			}
			else
			{
				sprintf(chSendBuf, "sour0:wav:swe:spe %dnm/s\n",m_pScanParam->m_nSpeed);
			}
			
			dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
			if (SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_TLS_SCAN_PREPARE;
			}
			//����trigerɨ�貽��
			ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
			sprintf(chSendBuf, "sour0:wav:swe:step %.3fnm\n",m_pScanParam->m_dblStepSize);
			dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
			if (SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_TLS_SCAN_PREPARE;
			}
			
			//���ü������Ĺ���
			if (!SetTLSPower(m_pScanParam->m_dblTLSPower))
			{
				throw dwErrorCode|ERROR_TLS_SCAN_PREPARE;
			}
		}
		
		//���ɨ���trig����,����ֵ���ṹ��
//		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
//		sprintf(chSendBuf, "sour0:wav:swe:exp?\n");
//		dwErrorCode = m_Comm.WriteDevice(chSendBuf);
//		if (SUCCESS != dwErrorCode)
//		{
//			throw dwErrorCode|ERROR_TLS_SCAN_PREPARE;
//		}
//		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
//		dwErrorCode = m_Comm.ReadDevice(chSendBuf,MAX_PATH);
//		if (SUCCESS != dwErrorCode)
//		{
//			throw "Send TLS scan stop error";
//		}
//		m_dwScanPoint = atoi(chSendBuf) - 1;
		m_dwScanPoint = (DWORD)((dbStopWL - dbStartWL)/m_pScanParam->m_dblStepSize + 0.5)-1;
		
		//����trig��ģʽ
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		sprintf(chSendBuf, "trig0:conf 3\r\n");
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_PREPARE;
		}
		
		//����tripg����Ϊswsģʽ
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		sprintf(chSendBuf, "trig0:inp sws\r\n");
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_PREPARE;
		}
		//����trig���Ϊstfģʽ
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		sprintf(chSendBuf, "trig0:outp stf\r\n");
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_PREPARE;
		}
		//����ɨ�����ѭ������
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		sprintf(chSendBuf, "sour0:wav:swe:cycl 0\r\n");
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_PREPARE;
		}
		//����am��stateģʽΪ0
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		sprintf(chSendBuf, "sour0:am:stat 0\r\n");
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_PREPARE;
		}
		//����TLSΪLogģʽ
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		sprintf(chSendBuf, "sour0:wav:swe:llog 1\r\n");
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_PREPARE;
		}
        //������ɨ��ģʽ
		if(!ScanStart())
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
//////////////////////////////////////////////
//����˵����
//    ͨ��������trig������ɨ��
//Add by wanxin
//Time:20140807
////////////////////////////////////////////////
DWORD COp816XCtrl::SetScanStart(long lChIndex)
{
	char chSendBuf[MAX_PATH];
	int preFlag,CurentFlag;
	DWORD dwErrorCode = SUCCESS;
	try
	{				
		
		
		//��ȡFlag��־,���Flag%2 ==1������trig��ʼɨ��
		while(TRUE)
		{
			ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
			sprintf(chSendBuf, "sour%0:wav:swe:flag?\r\n");
			dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
			if (SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_TLS_SOFT_TRIGER;
			}
			Sleep(50);
			ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
			dwErrorCode = m_Comm.ReadDevice(chSendBuf,MAX_PATH);
			if (SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_TLS_SOFT_TRIGER;
			}
			
			preFlag = atoi(chSendBuf);
			if (preFlag%2==1)
			{
				break;
			}
		}
		ZeroMemory(chSendBuf,MAX_PATH);
		sprintf(chSendBuf,"sour0:wav:swe:soft\r\n");
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SOFT_TRIGER;
		}
		//��ȡFlag��־�����ǰ���FlagС�ڵ�ǰFlag����Ϊɨ�����
		while(TRUE)
		{
			ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
			sprintf(chSendBuf, "sour0:wav:swe:flag?\n");
			dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
			if (SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_TLS_SOFT_TRIGER;
			}
			Sleep(50);
			ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
			dwErrorCode = m_Comm.ReadDevice(chSendBuf,MAX_PATH);
			if (SUCCESS != dwErrorCode)
			{
				throw dwErrorCode|ERROR_TLS_SOFT_TRIGER;
			}
			CurentFlag = atoi(chSendBuf);			
			if (CurentFlag > preFlag)
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
////////////////////////////////////////////////////////////////
//����˵����
//    ͨ��������trig����������ɨ��
//Add by wanxin
//Time:2040807
////////////////////////////////////////////////////////////////
DWORD COp816XCtrl::ScanStart()
{
	char chSendBuf[MAX_PATH];
	DWORD dwErrorCode = SUCCESS;
	try
	{						
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		sprintf(chSendBuf, "sour0:wav:swe 1\r\n");
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_START;
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
////////////////////////////////////////////////////////////////
//����˵����
//    ͨ��������trig����������ɨ��
//Add by wanxin
//Time:2040807
////////////////////////////////////////////////////////////////
DWORD COp816XCtrl::SetScanStop(long lChIndex)
{
	char chSendBuf[MAX_PATH];
	DWORD dwErrorCode = SUCCESS;
	try
	{						
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		sprintf(chSendBuf, "sour0:wav:swe 0\r\n");
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_STOP;
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
///////////////////////////////////////////////////////////////////
//����˵����
//    ���ɨ�貨������
//Add by wanxin
///////////////////////////////////////////////////////////////////
DWORD COp816XCtrl::GetLamdaScanWLResult(long lChIndex,double* pdbWLAarry)
{
	char chSendBuf[MAX_PATH];
	PBYTE pbWLArry =  NULL;
	double* dbTemp;
	int nTemp;
	DWORD dwErrorCode = SUCCESS;
	try
	{	
		
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		sprintf(chSendBuf, "sour0:read:poin? llog\r\n");
		dwErrorCode = m_Comm.WriteDevice(chSendBuf,strlen(chSendBuf));
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_RESULT;
		}
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		dwErrorCode = m_Comm.ReadDevice(chSendBuf,MAX_PATH);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_RESULT;
		}
		nTemp = atoi(chSendBuf);
		
		//��TLSɨ�����ж�ȡ����
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		sprintf(chSendBuf,"sour%d:read:data:block? LLOG,0,%d",nTemp);
		dwErrorCode = m_Comm.ReadDevice(chSendBuf,MAX_PATH);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_RESULT;
		}
		if (pbWLArry == NULL)
		{
			pbWLArry = new BYTE[(nTemp)*8];
		}
		
		ZeroMemory(pbWLArry, sizeof(BYTE)*(nTemp)*8);
		dwErrorCode = m_Comm.ReadDevice(pbWLArry,nTemp*8);
		if (SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_TLS_SCAN_RESULT;
		}
		
		nTemp = pbWLArry[1] - '0' + 2;
		
		dbTemp = (double*)(pbWLArry+nTemp);
		
		for (int nIndex=0;nIndex < (int)m_pScanParam->m_dwSampleCount;nIndex++)
		{
			pdbWLAarry[nIndex] = dbTemp[nIndex]*1E9;		
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
	
	if (pbWLArry != NULL)
	{
		delete [] pbWLArry;
		pbWLArry = NULL;
	}
	
	return dwErrorCode;	 
}