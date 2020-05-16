// Aglient8164.cpp: implementation of the CAglient8164Ctrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\\include\\Aglient8164.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CAglient8164Ctrl::CAglient8164Ctrl()
{
    m_nPMBeginSlotIndex = 1;
	m_dwScanPoint = 0;
	m_bSaveScanRawData = FALSE;
	//m_MainFrameInfo.pSlot = NULL;
}

CAglient8164Ctrl::~CAglient8164Ctrl()
{
//	if (m_MainFrameInfo.pSlot !=NULL)
//	{
//		delete [] m_MainFrameInfo.pSlot;
//		m_MainFrameInfo.pSlot = NULL;
//	}

}
//////////////////////////////////////////////////////////////////
//����˵����
//    �����ʼ���ṹ��
//Add by wanxin
//////////////////////////////////////////////////////////////////
void CAglient8164Ctrl::SetDeviceParameter(pDeviceInital pInital)
{
	ASSERT(pInital);
	m_stDeviceIniatal.nComType = pInital->nComType;
	m_stDeviceIniatal.nDevIndex = pInital->nDevIndex;
	m_stDeviceIniatal.strAddress = pInital->strAddress;
}

/////////////////////////////////////////////////////////////////////////////
//����˵����
//    ��������Aglient 81690Aģ�飬��ģ���������8163A/B��
//    8164,8166��MainFrame
//���ߣ�wanxin wang
//ʱ�䣺2012-11-20     
///////////////////////////////////////////////////////////////////////////////
BOOL CAglient8164Ctrl::OpenDevice()
{
	ViChar szDeviceDescriptor[VI_FIND_BUFLEN];
	int nType = m_stDeviceIniatal.nComType;
	try
	{
		//��visa����Դ������
		status = viOpenDefaultRM (&defaultRM);
		if(!DeviceStatusOK(status))
		     throw"open visa RM error";

		if (nType < 0 ||nType > 10)
		{
			throw"Comunication type setting error";
		}
		
		//����ͨѶ���ͽ�������
		switch (nType)
		{
		case T_GPIB:
			{
                sprintf(szDeviceDescriptor,"GPIB%d::%s::INSTR",m_stDeviceIniatal.nDevIndex,m_stDeviceIniatal.strAddress);	
			}
			break;
		case T_NET:
			{
				sprintf(szDeviceDescriptor,"TCPIP%d::%s::INSTR",m_stDeviceIniatal.nDevIndex,m_stDeviceIniatal.strAddress);		
			}
			break;
		case T_USB:
			{
                sprintf(szDeviceDescriptor,"USB%d::INSTR",m_stDeviceIniatal.nDevIndex);
			}
			break;
		case T_SERIAL:
			{
                sprintf(szDeviceDescriptor,"ASRL%d::INSTR",m_stDeviceIniatal.nDevIndex);
			}
			break;
		default:
			throw "Input the communication type error";
			break;
		}	
		status = viOpen(defaultRM, szDeviceDescriptor,VI_NULL, VI_NULL, &m_hAglient81960A);
		if(!DeviceStatusOK(status))
			throw"Open Aglient 81960A moudle error";

		//���MainFrame��Ϣ
        ZeroMemory(&m_MainFrameInfo,sizeof(stMainFrame));
		if (!GetMainFrameInfo(&m_MainFrameInfo))
		{
           throw"Get MainFrame Info error";
		}
		//���Slot��Ϣ
		if (!GetSlotInfo(&m_MainFrameInfo))
		{
			throw"Get Slot Info error";
		}
	}
	catch (char* pstrMsg)
	{
		AfxMessageBox(pstrMsg);
		return FALSE;
	}
	return TRUE;
}
/////////////////////////////////////////////////////////
//����˵����
//    �жϷ���״̬����
//////////////////////////////////////////////////////////
BOOL CAglient8164Ctrl::DeviceStatusOK(ViStatus viStatus)	
{
	return (viStatus >= VI_SUCCESS);
}
///////////////////////////////////////////////////////////////
//����˵����
//    �ر�visa��Դ������
///////////////////////////////////////////////////////////////
void CAglient8164Ctrl::CloseDevice()
{
    if (m_hAglient81960A !=NULL)
    {
		viClose(m_hAglient81960A);
    }
	if (defaultRM != NULL)
    {
		viClose(defaultRM);
    }
}
////////////////////////////////////////////////////////////////
//����˵����
//    ��ʼ�����������������������á��������򿪼����
//Add by wanxin
///////////////////////////////////////////////////////////////
BOOL CAglient8164Ctrl::InitalDeive()
{
	char szSenBuf[MAX_PATH];
	ViUInt32 nGetLength;
	try
	{					
		//�жϼ������Ƿ�����
		ZeroMemory(szSenBuf, sizeof(char)*MAX_PATH);
		sprintf(szSenBuf, "LOCK?");
		status =viWrite(m_hAglient81960A,(unsigned char*)szSenBuf,strlen(szSenBuf),&nGetLength);		
		if (!DeviceStatusOK(status))
		{
			throw "Send read TLS lock error";
		}
		ZeroMemory(szSenBuf, sizeof(char)*MAX_PATH);
		status = viRead(m_hAglient81960A,(unsigned char*)szSenBuf,MAX_PATH,&nGetLength);
		if (!DeviceStatusOK(status)) 
		{
			throw "Read TLS lock error";
		}
		ASSERT(szSenBuf);
		int nStatus = atoi(szSenBuf);
		if (nStatus != 0)
		{		
			ZeroMemory(szSenBuf, sizeof(char)*MAX_PATH);
			sprintf(szSenBuf, "LOCK 0,1234\n");
			status =viWrite(m_hAglient81960A,(unsigned char*)szSenBuf,strlen(szSenBuf),&nGetLength);		
			if (!DeviceStatusOK(status))
			{
				throw "Send TLS unlock error";
			}
		}
		ZeroMemory(szSenBuf, sizeof(szSenBuf));
		sprintf(szSenBuf, "*RST\n");
		status =viWrite(m_hAglient81960A,(unsigned char*)szSenBuf,strlen(szSenBuf),&nGetLength);
		if (!DeviceStatusOK(status))
		{
			throw "Send read laser whether lack error";
 		}
		Sleep(5000);
	}
	catch (char* pstrMsg)
	{
		AfxMessageBox(pstrMsg);
		return FALSE;
	}
	return TRUE;
}


///////////////////////////////////////////////////////////////////
//����˵����
//    ͨ������*IDN?ָ���ѯ��ǰMainFrame����
//Add by wanxin
////////////////////////////////////////////////////////////////////
BOOL CAglient8164Ctrl::GetMainFrameInfo(pstMainFrame pInfo)
{
	char chSendBuf[MAX_PATH];
	ViUInt32 nGetLength =-1;
	CString strTemp;
	try
	{
		ASSERT(pInfo);
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		sprintf(chSendBuf, "*IDN?\n");
		status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);
		if (!DeviceStatusOK(status))
		{
			throw "Send *IDN? error";
		}
		ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
		status = viRead(m_hAglient81960A,(unsigned char*)chSendBuf,MAX_PATH,&nGetLength);
		if (!DeviceStatusOK(status)) 
		{
			throw "Read *IDN? error";
		}
		strcpy(pInfo->szMainFrame,chSendBuf);
		strTemp = chSendBuf;
		if (strTemp.IsEmpty())
		{
			throw"Read MainFrame Info empty";
		}
		else
		{
			//����MainFrame���ͺ�ȷ��slot��Ϣ
			//����slot��Ϣ�ṹ��ռ�
			if (strTemp.Find("8164")!=-1)
			{
				pInfo->nBeginSlotIndex =0;
				pInfo->nSlotCount = 6;
				if (pInfo->pSlot == NULL)
				{
					pInfo->pSlot = new stSlotInfo[6];
				}				
			}
			else if (strTemp.Find("8163")!=-1)
			{
				pInfo->nBeginSlotIndex = 1;
				pInfo->nSlotCount = 3;
				if (pInfo->pSlot == NULL)
				{
					pInfo->pSlot = new stSlotInfo[3];
				}
			}
			else if (strTemp.Find("8166"))
			{
				pInfo->nBeginSlotIndex = 1;
				pInfo->nSlotCount = 17;
				if (pInfo->pSlot == NULL)
				{
					pInfo->pSlot = new stSlotInfo[17];
				}
			}
		}
	}
	catch ( char* pstrMsg)
	{
		AfxMessageBox(pstrMsg);
		return FALSE;
	}
	return TRUE;
}
/////////////////////////////////////////////////////////////////
//����˵����
//    ���slotģ����Ϣ
//Add by wanxin
/////////////////////////////////////////////////////////////////
BOOL CAglient8164Ctrl::GetSlotInfo(pstMainFrame pInfo)
{
	char chSendBuf[MAX_PATH];
	ViUInt32 nGetLength =-1;
	CString strTemp;
	try
	{
		ASSERT(pInfo);

		for(int nIndex = pInfo->nBeginSlotIndex;nIndex < pInfo->nSlotCount;nIndex++)
		{
			//��ѯģ���Ƿ�Ϊ����
			ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
			sprintf(chSendBuf, "SLOT%d:EMPT?\n",nIndex);
			status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);
			if (!DeviceStatusOK(status))
			{
				throw "Send SLOT:EMPT error";
			}
			ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
			status = viRead(m_hAglient81960A,(unsigned char*)chSendBuf,MAX_PATH,&nGetLength);
			if (!DeviceStatusOK(status)) 
			{
				throw "Read  SLOT:EMPT error";
			}
			ASSERT(chSendBuf);
			pInfo->pSlot[nIndex].bOnline = atoi(chSendBuf);

			if (pInfo->pSlot[nIndex].bOnline ==0 ) 
			{
				//��ѯģ������				
				ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
				sprintf(chSendBuf, "SLOT%d:IDN?\n",nIndex);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);
				if (!DeviceStatusOK(status))
				{
					throw "Send SLOT:IDN? error";
				}
				ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
				status = viRead(m_hAglient81960A,(unsigned char*)chSendBuf,MAX_PATH,&nGetLength);
				if (!DeviceStatusOK(status)) 
				{
					throw "Read  SLOT:IDN? error";
				}
				strcpy(pInfo->pSlot[nIndex].szSlotCaption,chSendBuf);
				strTemp = chSendBuf;
				if (strTemp.Find("81960A")!=-1)
				{
                    pInfo->pSlot[nIndex].nChanelCout = 1;
					pInfo->pSlot[nIndex].nCurSlotIndex = nIndex;
					pInfo->pSlot[nIndex].nCurChannel = nIndex;
					pInfo->pSlot[nIndex].nDeviceType = TAG_TLS;
				}
				else if (strTemp.Find("81618A")!=-1)
				{
                    pInfo->pSlot[nIndex].nChanelCout = 1;
					pInfo->pSlot[nIndex].nCurSlotIndex = nIndex;
					pInfo->pSlot[nIndex].nCurChannel = 0;
					pInfo->pSlot[nIndex].nDeviceType = TAG_PM;
				}
				else if(strTemp.Find("81619A")!=-1)
				{
                    pInfo->pSlot[nIndex].nChanelCout = 2;
					pInfo->pSlot[nIndex].nCurSlotIndex = nIndex;
					pInfo->pSlot[nIndex].nCurChannel = 1;
					pInfo->pSlot[nIndex].nDeviceType = TAG_PM;
				}
				else if (strTemp.Find("8164")!=-1)
				{
                    pInfo->pSlot[nIndex].nChanelCout = 1;
					pInfo->pSlot[nIndex].nCurSlotIndex = nIndex;
					pInfo->pSlot[nIndex].nCurChannel = 0;
					pInfo->pSlot[nIndex].nDeviceType = TAG_TLS;
				}
				else if (strTemp.Find("81680A")!=-1)
				{
                    pInfo->pSlot[nIndex].nChanelCout = 1;
					pInfo->pSlot[nIndex].nCurSlotIndex = nIndex;
					pInfo->pSlot[nIndex].nCurChannel = 0;
					pInfo->pSlot[nIndex].nDeviceType = TAG_TLS;
				}
			}
		}
	}
	catch ( char* pstrMsg)
	{
		AfxMessageBox(pstrMsg);
		return FALSE;
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////
//����˵����
//    �򿪼�����
//Add by wanxin
/////////////////////////////////////////////////////////////
BOOL CAglient8164Ctrl::SetLaserOn( BOOL bOpen)
{
	char chSendBuf[MAX_PATH];
	ViUInt32 nGetLength;
	int nState =-1;
	int nCount;
	CString strTemp;
	try
	{
		
		for (int nIndex =m_MainFrameInfo.nBeginSlotIndex;nIndex <m_MainFrameInfo.nSlotCount;nIndex++)
		{
			//����豸����
			if (m_MainFrameInfo.pSlot[nIndex].bOnline ==0
				&&m_MainFrameInfo.pSlot[nIndex].nDeviceType == TAG_TLS
				&&m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex !=0)
			{
				//���ü�����״̬
				ZeroMemory(chSendBuf,MAX_PATH);
				sprintf(chSendBuf,"sour%d:pow:stat %d\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex,bOpen);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Send laser state command error";
				}
				//��ȡ������״̬
				ZeroMemory(chSendBuf,MAX_PATH);
				sprintf(chSendBuf,"sour%d:pow:stat?\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Read laser state error";
				}
				nCount = 0;
				while(TRUE)
				{
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					viRead(m_hAglient81960A,(unsigned char*)chSendBuf,MAX_PATH,&nGetLength);
					if (atoi(chSendBuf) == bOpen )
					{
						break;
					}
					nCount++;
					if (nCount > 10)
					{
						throw"Read laser state error";
					}
				}				
			}
			else if (m_MainFrameInfo.pSlot[nIndex].bOnline ==0&&m_MainFrameInfo.pSlot[nIndex].nDeviceType == TAG_TLS
				&& m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex==0)
			{
				//���ü�����״̬
				ZeroMemory(chSendBuf,MAX_PATH);
				sprintf(chSendBuf,"sour%d:pow:stat %d\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex,bOpen);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Send laser state command error";
				}
				//��ȡ������״̬
				ZeroMemory(chSendBuf,MAX_PATH);
				sprintf(chSendBuf,"sour%d:pow:stat?\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Read laser state error";
				}
				nCount = 0;
				while(TRUE)
				{
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					viRead(m_hAglient81960A,(unsigned char*)chSendBuf,MAX_PATH,&nGetLength);
					if (atoi(chSendBuf) == bOpen )
					{
						break;
					}
					nCount++;
					if (nCount > 10)
					{
						throw"Read laser state error";
					}
				}
				if (bOpen) //���ø߹⹦��
				{
					ZeroMemory(chSendBuf,MAX_PATH);
					sprintf(chSendBuf,"output%d:path high\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send laser state command error";
					}
				}
				else //���õ͹⹦��
				{
					ZeroMemory(chSendBuf,MAX_PATH);
					sprintf(chSendBuf,"output%d:path lows\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send laser state command error";
					}
				}
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
/////////////////////////////////////////////////////////////////////
//����˵����
//    ����ģ�鼤���������
//Add by wanxin
///////////////////////////////////////////////////////////////////////
BOOL CAglient8164Ctrl::SetTLSPower(double dbPower)
{
	char chSendBuf[MAX_PATH];
	ViUInt32 nGetLength;
	try
	{				
		for (int nIndex = m_MainFrameInfo.nBeginSlotIndex;nIndex <m_MainFrameInfo.nSlotCount;nIndex++)
		{
			//����豸����
			if (m_MainFrameInfo.pSlot[nIndex].bOnline ==0
				&&m_MainFrameInfo.pSlot[nIndex].nDeviceType == TAG_TLS)
			{
				ZeroMemory(chSendBuf,MAX_PATH);
				sprintf(chSendBuf,"sour%d:pow %.3fDBM\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex,dbPower);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Send set laser power command error";
				}
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
/////////////////////////////////////////////////////////////////
//����˵����
//    ��ȡTLS�������
//Add by wanxin
/////////////////////////////////////////////////////////////////
BOOL CAglient8164Ctrl::ReadTLSPower(double &dbPower)
{	
	char chSendBuf[MAX_PATH];
	ViUInt32 nGetLength;
	CString strTemp;
	try
	{				
		for (int nIndex = m_MainFrameInfo.nBeginSlotIndex;nIndex <m_MainFrameInfo.nSlotCount;nIndex++)
		{
			//����豸����
			if (m_MainFrameInfo.pSlot[nIndex].bOnline ==0
				&&m_MainFrameInfo.pSlot[nIndex].nDeviceType == TAG_TLS)
			{
				ZeroMemory(chSendBuf,MAX_PATH);
				sprintf(chSendBuf,"sour%d:pow?\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Send read laser power command error";
				}
				ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
				status = viRead(m_hAglient81960A,(unsigned char*)chSendBuf,MAX_PATH,&nGetLength);
				if (!DeviceStatusOK(status)) 
				{
					throw "Read the laser power error";
				}
				ASSERT(chSendBuf);
				dbPower =atof(chSendBuf);
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
///////////////////////////////////////////////////////////////////
//����˵����
//    ���ü�����ģ�鲨������
//Add by wanxin
//////////////////////////////////////////////////////////////////
BOOL CAglient8164Ctrl::SetTLSWavelength(double dblWavelength)
{
	char chSendBuf[MAX_PATH];
	ViUInt32 nGetLength;
	try
	{			
		for (int nIndex = m_MainFrameInfo.nBeginSlotIndex;nIndex < m_MainFrameInfo.nSlotCount;nIndex++)
		{
			//����豸����
			if (m_MainFrameInfo.pSlot[nIndex].bOnline ==0
				&&m_MainFrameInfo.pSlot[nIndex].nDeviceType == TAG_TLS)
			{
				ZeroMemory(chSendBuf,MAX_PATH);
				sprintf(chSendBuf,"sour%d:wav %.3fnm\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex,dblWavelength);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);	
//				Sleep(5);
//				if (!DeviceStatusOK(status))
//				{
//					throw "Send set WL command error";
//				}
				
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
//////////////////////////////////////////////////////////////////////
//����˵����
//    ��ȡ���õĲ���
//Add by wanxin
//////////////////////////////////////////////////////////////////////
BOOL CAglient8164Ctrl::ReadSetTLSWavelength(double &dbWL)
{
	char chSendBuf[MAX_PATH];
	ViUInt32 nGetLength;
	int nState =-1;
	CString strTemp;
	try
	{				
		for (int nIndex = m_MainFrameInfo.nBeginSlotIndex;nIndex < m_MainFrameInfo.nSlotCount;nIndex++)
		{
			//����豸����
			if (m_MainFrameInfo.pSlot[nIndex].bOnline ==0
				&&m_MainFrameInfo.pSlot[nIndex].nDeviceType == TAG_TLS)
			{
				ZeroMemory(chSendBuf,MAX_PATH);
				sprintf(chSendBuf,"sour%d:wav?\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Send Read Laser WL error";
				}
				ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
				status = viRead(m_hAglient81960A,(unsigned char*)chSendBuf,MAX_PATH,&nGetLength);
				if (!DeviceStatusOK(status)) 
				{
					throw "Read the Laser WL error";
				}
				ASSERT(chSendBuf);
				dbWL =atof(chSendBuf);
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

void CAglient8164Ctrl::YieldToPeers()
{
	MSG	msg;
	while(::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
	{
		if(!AfxGetThread()->PumpMessage())
			break;
	}
}
///////////////////////////////////////////////////////////////////
//����˵����
//    ���ɨ�貨������
//Add by wanxin
///////////////////////////////////////////////////////////////////
BOOL CAglient8164Ctrl::GetLamdaScanWLResult(double* pdbWLAarry)
{
	char chSendBuf[MAX_PATH];
	CString strTemp;
	PBYTE pbWLArry =  NULL;
	double* dbTemp;
	int nTemp;
	ViUInt32 nGetLength;
	try
	{	
		for (int nIndex = m_MainFrameInfo.nBeginSlotIndex;nIndex < m_MainFrameInfo.nSlotCount;nIndex++)
		{
			//����豸����
			if (m_MainFrameInfo.pSlot[nIndex].bOnline ==0
				&&m_MainFrameInfo.pSlot[nIndex].nDeviceType == TAG_TLS)
			{
				ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
				sprintf(chSendBuf, "sour%d:read:poin? llog\n",nIndex);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Send  Read scan point llog command error";
				}
				
				ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
				status = viRead(m_hAglient81960A,(unsigned char*)chSendBuf,MAX_PATH,&nGetLength);
				if (!DeviceStatusOK(status)) 
				{
					throw "Read scan point count error";
				}
				nTemp = atoi(chSendBuf);
				
				//��TLSɨ�����ж�ȡ����
				ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
				sprintf(chSendBuf,"sour%d:read:data:block? LLOG,0,%d",nIndex,nTemp);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Read scan point error";
				}
				if (pbWLArry == NULL)
				{
					pbWLArry = new BYTE[(nTemp)*8];
				}
				
				ZeroMemory(pbWLArry, sizeof(BYTE)*(nTemp)*8);
				status = viRead(m_hAglient81960A,(unsigned char*)pbWLArry,nTemp*8,&nGetLength);
				if (!DeviceStatusOK(status)) 
				{
					throw "Read scan point error";
				}
				ASSERT(pbWLArry);
				nTemp = pbWLArry[1] - '0' + 2;
				
				dbTemp = (double*)(pbWLArry+nTemp);
				
				for (DWORD nIndex=0;nIndex <m_dwScanPoint-1;nIndex++)
				{
					pdbWLAarry[nIndex] = dbTemp[nIndex]*1e9;		
				}
				
				if (pbWLArry != NULL)
				{
					delete [] pbWLArry;
					pbWLArry = NULL;
				}
			}						
		}		
	}
	catch (char* pstrMsg)
	{
       AfxMessageBox(pstrMsg);
	   return FALSE;
	}
	return TRUE;
}
//////////////////////////////////////////////////////////
//����˵����
//    ����81960A ������ʵ�λ
//Add by wanxin
//////////////////////////////////////////////////////////
BOOL CAglient8164Ctrl::SetTLSPowerUnit(BOOL bdBm)
{
	char chSendBuf[MAX_PATH];
	ViUInt32 nGetLength;
	try
	{		
		for (int nIndex = m_MainFrameInfo.nBeginSlotIndex;nIndex <m_MainFrameInfo.nSlotCount;nIndex++)
		{
			//����豸����
			if (m_MainFrameInfo.pSlot[nIndex].bOnline ==0
				&&m_MainFrameInfo.pSlot[nIndex].nDeviceType == TAG_TLS)
			{
				ZeroMemory(chSendBuf,MAX_PATH);
				sprintf(chSendBuf,"sour%d:pow:unit %d\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex,bdBm);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				Sleep(5);
				if (!DeviceStatusOK(status))
				{
					throw "Send set power unit error";
				}
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
////////////////////////////////////////////////////////////
//����˵����
//     ��ѯ�������
//Add by wanxin
////////////////////////////////////////////////////////////
BOOL CAglient8164Ctrl::Completequery()
{
	char chSendBuf[MAX_PATH];
	ViUInt32 nGetLength;
	CString strTemp;
	try
	{		
		while(TRUE)
		{
			ZeroMemory(chSendBuf,MAX_PATH);
			sprintf(chSendBuf,"*OPC?\n");
			status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
			if (!DeviceStatusOK(status))
			{
				throw "Send *OPC? error";
			}
			Sleep(10);
			ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
			status = viRead(m_hAglient81960A,(unsigned char*)chSendBuf,MAX_PATH,&nGetLength);
			if (!DeviceStatusOK(status)) 
			{
				throw "Read *OPC? error";
			}
			int nStatus = atoi(chSendBuf);
			if (nStatus ==1)
			{
				break;
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
/////////////////////////////////////////////////////////////
//����˵����
//    ��������ɨ���ʼ������
//Add by wanxin
////////////////////////////////////////////////////////////
BOOL CAglient8164Ctrl::PrepareScan(long lScanParam)
{
	char chSendBuf[MAX_PATH];
	CString strTemp;
	double dbStartWL,dbStopWL;
	double dbReadStartWL,dbReadStopWL;
	ViUInt32 nGetLength;	
	try
	{				
		m_pScanParam = (PScanParam)lScanParam;
		if (!GetTLSWLRange(dbStartWL,dbStopWL))
        {
			throw"Get TLS max and min WL range error";
        }
		if (m_pScanParam->m_dblStartWL < dbStartWL || m_pScanParam->m_dblStopWL > dbStopWL)
		{
			throw"Setting scan WL range error";
		}
		//�������õ�ɨ�跶Χ��ɨ0.05nm
		dbStartWL = m_pScanParam->m_dblStartWL - 0.5;	
		dbStopWL = m_pScanParam->m_dblStopWL + 0.5;

		m_pScanParam->m_dwSampleCount  = (DWORD)((m_pScanParam->m_dblStopWL - m_pScanParam->m_dblStartWL)/m_pScanParam->m_dblStepSize + 0.5);

		for (int nIndex = m_MainFrameInfo.nBeginSlotIndex;nIndex <m_MainFrameInfo.nSlotCount;nIndex++)
		{
			//����豸����
			if (m_MainFrameInfo.pSlot[nIndex].bOnline ==0
				&&m_MainFrameInfo.pSlot[nIndex].nDeviceType == TAG_TLS)
			{
				//���˫��ɨ���־ΪTRUE����ʵ��˫��ɨ�裬����ʵ�е���ɨ��
				if (m_bTwowayScan)
				{
					//����ɨ��ģʽΪstepģʽ
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					sprintf(chSendBuf, "sour%d:wav:swe:mode step\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send  TLS scan mode error";
					}
					//����RepeatģʽΪTWOWAY 
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					sprintf(chSendBuf, "sour%d:wav:swe:rep twow\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send  TLS scan mode error";
					}
					//����ɨ��ģʽΪcontinueģʽ
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					sprintf(chSendBuf, "sour%d:wav:swe:mode cont\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send  TLS scan mode error";
					}
				}
				else
				{
					//����ɨ��ģʽΪcontinueģʽ
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					sprintf(chSendBuf, "sour%d:wav:swe:mode cont\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send  TLS scan mode error";
					}
					//����RepeatģʽΪonewģʽ
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					sprintf(chSendBuf, "sour%d:wav:swe:rep onew\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send  TLS scan mode error";
					}
				}
				
				if (!JudgeScanParameter())
				{
					// 		//���ܼ���������ɨ��״̬���ǲ���ɨ��״̬��
					// 		//�ȷ���ֹͣɨ��ָ��	
					if (!SetScanStop())
					{
						throw "Send read laser WL error";
					}
					//����ɨ�����ʼ����
					if (!SetScanWLRange(dbStartWL,dbStopWL))
					{
						throw"Setting scan WL range error";
					}
					//�ض�ɨ�����ʼ����
					if (!GetScanWLRange(dbReadStartWL,dbReadStopWL))
					{
						throw"Read Scan WL Range error";
					}
					//�ж����õ�ɨ����ʼ�������õ���ʼ�����Ƿ���ͬ
					if (fabs(dbStartWL - dbReadStartWL) > 0.01 || fabs(dbStopWL - dbReadStopWL) > 0.01 )
					{
						throw"Scan WL range error";
					}
					//����ɨ���ٶ�
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					if (m_pScanParam->m_nSpeed > 40) 
					{
                        sprintf(chSendBuf, "sour%d:wav:swe:spe 0.5nm/s\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex,m_pScanParam->m_nSpeed);
					}
					else
					{
                        sprintf(chSendBuf, "sour%d:wav:swe:spe %dnm/s\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex,m_pScanParam->m_nSpeed);
					}
					
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send  TLS scan speed command error";
					}
					//����trigerɨ�貽��
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					sprintf(chSendBuf, "sour%d:wav:swe:step %.3fnm\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex,m_pScanParam->m_dblStepSize);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send  TLS scan step command error";
					}
					//���ü������Ĺ���
					if (!SetTLSPower(m_pScanParam->m_dblTLSPower))
					{
						throw "Setting TLS power error";
					}
				}
				
				//���ɨ���trig����,����ֵ���ṹ��
				ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
				sprintf(chSendBuf, "sour%d:wav:swe:exp?\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);
				if (!DeviceStatusOK(status))
				{
					throw "Send  TLS scan exp error";
				}
				ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
				status = viRead(m_hAglient81960A,(unsigned char*)chSendBuf,MAX_PATH,&nGetLength);
				if (!DeviceStatusOK(status))
				{
					throw "Read  TLS scan exp error";
				}
				m_dwScanPoint = atoi(chSendBuf) - 1;
				
				//����trig��ģʽ
				ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
				sprintf(chSendBuf, "trig%d:conf 3\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Send TLS scan trig mode error";
				}
				
				//����tripg����Ϊswsģʽ
				ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
				sprintf(chSendBuf, "trig%d:inp sws\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Send  TLS trig out stf mode error";
				}
				//����trig���Ϊstfģʽ
				ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
				sprintf(chSendBuf, "trig%d:outp stf\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Send  TLS trig out stf mode error";
				}
				//����ɨ�����ѭ������
				ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
				sprintf(chSendBuf, "sour%d:wav:swe:cycl 0\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Send  TLS scan cycle error";
				}
				//����am��stateģʽΪ0
				ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
				sprintf(chSendBuf, "sour%d:am:stat 0\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Send  TLS am state mode error";
				}
				//����TLSΪLogģʽ
				ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
				sprintf(chSendBuf, "sour%d:wav:swe:llog 1\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Send TLS scan log mode error";
				}
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
////////////////////////////////////////////////////////////////
//����˵����
//    ͨ��������trig����������ɨ��
//Add by wanxin
////////////////////////////////////////////////////////////////
BOOL CAglient8164Ctrl::SetScanStart()
{
	char chSendBuf[MAX_PATH];
	ViUInt32 nGetLength;
	try
	{						
		for (int nIndex = m_MainFrameInfo.nBeginSlotIndex;nIndex <m_MainFrameInfo.nSlotCount;nIndex++)
		{
			//����豸����
			if (m_MainFrameInfo.pSlot[nIndex].bOnline ==0
				&&m_MainFrameInfo.pSlot[nIndex].nDeviceType == TAG_TLS)
			{
				ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
				sprintf(chSendBuf, "sour%d:wav:swe 1\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Send  scan begin error";
				}
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
//////////////////////////////////////////////
//����˵����
//    ͨ��������trig������ɨ��
//Add by wanxin
////////////////////////////////////////////////
BOOL CAglient8164Ctrl::SendSoftTrig()
{
	char chSendBuf[MAX_PATH];
	ViUInt32 nGetLength;
	int preFlag,CurentFlag;
	try
	{				
		
		
		for (int nIndex = m_MainFrameInfo.nBeginSlotIndex;nIndex < m_MainFrameInfo.nSlotCount;nIndex++)
		{
			//����豸����
			if (m_MainFrameInfo.pSlot[nIndex].bOnline ==0
				&&m_MainFrameInfo.pSlot[nIndex].nDeviceType == TAG_TLS)
			{
				//��ȡFlag��־,���Flag%2 ==1������trig��ʼɨ��
				while(TRUE)
				{
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					sprintf(chSendBuf, "sour%d:wav:swe:flag?\n",nIndex);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send  Read scan point count error";
					}
					
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					viRead(m_hAglient81960A,(unsigned char*)chSendBuf,MAX_PATH,&nGetLength);
					preFlag = atoi(chSendBuf);
					if (preFlag%2==1)
					{
						break;
					}
				}
				ZeroMemory(chSendBuf,MAX_PATH);
				sprintf(chSendBuf,"sour%d:wav:swe:soft\n",nIndex);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Send soft trig error";
				}
				//��ȡFlag��־�����ǰ���FlagС�ڵ�ǰFlag����Ϊɨ�����
				while(TRUE)
				{
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					sprintf(chSendBuf, "wav:swe:flag?\n");
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send  Read scan point count error";
					}
					
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					viRead(m_hAglient81960A,(unsigned char*)chSendBuf,MAX_PATH,&nGetLength);
					CurentFlag = atoi(chSendBuf);			
					if (CurentFlag > preFlag)
					{
						break;
					}
				}
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
//////////////////////////////////////////////////
//����˵����
//    ���ü�����ɨ��ֹͣ����
//Add by wanxin
//////////////////////////////////////////////////
BOOL CAglient8164Ctrl::SetScanStop()
{
	char chSendBuf[MAX_PATH];
	ViUInt32 nGetLength;
	int nCount;
	int CurentFlag;
	try
	{					
		
		for (int nIndex = m_MainFrameInfo.nBeginSlotIndex;nIndex <m_MainFrameInfo.nSlotCount;nIndex++)
		{
			//����豸����
			if (m_MainFrameInfo.pSlot[nIndex].bOnline ==0
				&&m_MainFrameInfo.pSlot[nIndex].nDeviceType == TAG_TLS)
			{
				ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
				sprintf(chSendBuf, "sour%d:wav:swe:flag?\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Send read swe state error";
				}
				nCount = 0;		
				while (TRUE)
				{
					YieldToPeers();
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					viRead(m_hAglient81960A,(unsigned char*)chSendBuf,MAX_PATH,&nGetLength);
					CurentFlag = atoi(chSendBuf);
					if (CurentFlag == 0)
					{
						break;
					}
					else
					{
						ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
						sprintf(chSendBuf, "sour%d:wav:swe 0\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
						status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
						if (!DeviceStatusOK(status))
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
		}
	}
	catch(char *pstrMsg)
	{
		AfxMessageBox(pstrMsg);
		return FALSE;
	}
	return TRUE;	
}
//////////////////////////////////////////////////////
//����˵��
//    ���ɨ�����ʼ������Χ
//Add by wanxin
///////////////////////////////////////////////////////
BOOL CAglient8164Ctrl::GetScanWLRange(double &dbStartWL,double &dbStopWL)
{
	char chSendBuf[MAX_PATH];
	ViUInt32 nGetLength;
	int nCount;
	try
	{						
		for (int nIndex = m_MainFrameInfo.nBeginSlotIndex;nIndex <m_MainFrameInfo.nSlotCount;nIndex++)
		{
			//����豸����
			if (m_MainFrameInfo.pSlot[nIndex].bOnline ==0
				&&m_MainFrameInfo.pSlot[nIndex].nDeviceType == TAG_TLS)
			{
				
				//��ȡɨ����ʼ����
				nCount = 0;		
				while (TRUE)
				{
					YieldToPeers();
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					sprintf(chSendBuf, "sour%d:wav:swe:star?\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
					viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);					
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					viRead(m_hAglient81960A,(unsigned char*)chSendBuf,MAX_PATH,&nGetLength);
					
					dbStartWL = atof(chSendBuf)*1E9;
					if (dbStartWL > 0.0)
					{
						break;
					}
					nCount++;
					if (nCount > 100)
					{
						throw"Read TLS scan start WL error";
					}
				}
				//��ȡɨ��ֹͣ����
				nCount = 0;
				ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
				while (TRUE)
				{
					YieldToPeers();
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					sprintf(chSendBuf, "sour%d:wav:swe:stop?\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
					viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);	
					viRead(m_hAglient81960A,(unsigned char*)chSendBuf,MAX_PATH,&nGetLength);
					
					dbStopWL = atof(chSendBuf)*1E9;
					if (dbStopWL > 0.0)
					{
						break;
					}
					nCount++;
					if (nCount > 100)
					{
						throw"Read TLS scan stop WL error";
					}
				}
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
////////////////////////////////////////////////////////
//����˵����
//    �����Ƿ����˫��ɨ��
//Add by wanxin
////////////////////////////////////////////////////////
void CAglient8164Ctrl::SetTwowayScan(BOOL bTwoway)
{
   m_bTwowayScan = bTwoway;

}
/////////////////////////////////////////////////////////
//����˵����
//     ���ģ�������С�Ĳ�����Χ
//Add by wanxin
////////////////////////////////////////////////////////////
BOOL CAglient8164Ctrl::GetTLSWLRange(double &dbWLMin,double &dbWLMax)
{
	char chSendBuf[MAX_PATH];
	ViUInt32 nGetLength;
	CString strTemp;
	try
	{				
		
		for (int nIndex = m_MainFrameInfo.nBeginSlotIndex;nIndex <m_MainFrameInfo.nSlotCount;nIndex++)
		{
			//����豸����
			if (m_MainFrameInfo.pSlot[nIndex].bOnline ==0
				&&m_MainFrameInfo.pSlot[nIndex].nDeviceType == TAG_TLS)
			{
				//�����С����range
				ZeroMemory(chSendBuf,MAX_PATH);
				sprintf(chSendBuf,"sour%d:wav? min\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Send wav min command error";
				}
				ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
				status = viRead(m_hAglient81960A,(unsigned char*)chSendBuf,MAX_PATH,&nGetLength);
				if (!DeviceStatusOK(status)) 
				{
					throw "Read wav min error";
				}
				dbWLMin = atof(chSendBuf)*1E9;
				
				//�����󲨳�range
				ZeroMemory(chSendBuf,MAX_PATH);
				sprintf(chSendBuf,"sour%d:wav? max\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Send wav max command error";
				}
				ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
				status = viRead(m_hAglient81960A,(unsigned char*)chSendBuf,MAX_PATH,&nGetLength);
				if (!DeviceStatusOK(status)) 
				{
					throw "Read wav max error";
				}
				dbWLMax = atof(chSendBuf)*1E9;				
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
BOOL CAglient8164Ctrl::SetScanWLRange(double dbWLStart,double dbWLStop)
{
	char chSendBuf[MAX_PATH];
	ViUInt32 nGetLength;
	CString strTemp;
	try
	{				
		for (int nIndex = m_MainFrameInfo.nBeginSlotIndex;nIndex <m_MainFrameInfo.nSlotCount;nIndex++)
		{
			//����豸����
			if (m_MainFrameInfo.pSlot[nIndex].bOnline ==0
				&&m_MainFrameInfo.pSlot[nIndex].nDeviceType == TAG_TLS)
			{
				//���ÿ�ʼɨ�貨��
				ZeroMemory(chSendBuf,MAX_PATH);
				sprintf(chSendBuf,"sour%d:wav:swe:star %.3fNM\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex,dbWLStart);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Send scan start WL command error";
				}
				
				//����ֹͣɨ�貨��
				ZeroMemory(chSendBuf,MAX_PATH);
				sprintf(chSendBuf,"sour%d:wav:swe:stop %.3fNM\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex,dbWLStop);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Send scan stop WL command error";
				}
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
///////////////////////////////////////////////////////////////////
//����˵����
//    �жϵ�ǰ��ɨ������Ƿ�仯,������õ���仯�Ĳ�ͬ�򷵻�FASLE
//    ����ж���ͬ�򷵻�TRUE
//Add by wanxin
///////////////////////////////////////////////////////////////////
BOOL CAglient8164Ctrl::JudgeScanParameter()
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
	catch(char *pstrMsg)
	{
		AfxMessageBox(pstrMsg);
		bModify = FALSE;
	}
	return bModify;
}
///////////////////////////////////////////////////////////////////////
//����˵����
//    ������õ�ɨ�����
//Add by wanxin
///////////////////////////////////////////////////////////////////////
BOOL CAglient8164Ctrl::GetScanParameter(PScanParam pSettingParam)
{
	char chSendBuf[MAX_PATH];
	ViUInt32 nGetLength;
	CString strTemp;
	double dbStartWL,dbStopWL;
	double dbTLSPower;
	try
	{				
		
		for (int nIndex = m_MainFrameInfo.nBeginSlotIndex;nIndex <m_MainFrameInfo.nSlotCount;nIndex++)
		{
			//����豸����
			if (m_MainFrameInfo.pSlot[nIndex].bOnline ==0
				&&m_MainFrameInfo.pSlot[nIndex].nDeviceType == TAG_TLS)
			{
				//���ɨ�貨��
				if (!GetScanWLRange(dbStartWL,dbStopWL))
				{
					throw"Get scan WL error";
				}
				pSettingParam->m_dblStartWL = dbStartWL;
				pSettingParam->m_dblStopWL = dbStopWL;
				
				//���ɨ���speed
				ZeroMemory(chSendBuf,MAX_PATH);
				sprintf(chSendBuf,"sour%d:wav:swe:spe?\n",nIndex);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Send read speed command error";
				}
				ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
				status = viRead(m_hAglient81960A,(unsigned char*)chSendBuf,MAX_PATH,&nGetLength);
				if (!DeviceStatusOK(status)) 
				{
					throw "Read speed error";
				}
				double dbTemp = atof(chSendBuf);
				pSettingParam->m_nSpeed = (int)(dbTemp*1E9);
				
				//���ɨ���step
				ZeroMemory(chSendBuf,MAX_PATH);
				sprintf(chSendBuf,"sour%d:wav:swe:step?\n",nIndex);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Send read step command error";
				}
				ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
				status = viRead(m_hAglient81960A,(unsigned char*)chSendBuf,MAX_PATH,&nGetLength);
				if (!DeviceStatusOK(status)) 
				{
					throw "Read step error";
				}
				pSettingParam->m_dblStepSize = atof(chSendBuf);
				
				if (!ReadTLSPower(dbTLSPower))
				{
					throw"Read setting power error";
				}
				pSettingParam->m_dblTLSPower = dbTLSPower;
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
/////////////////////////////////////////////////////////////////////////
//����˵����
//    ���������ɨ��������ýṹ�塢Slot��ʼ������
//    ��ʼ�����ʼ�ģ��ɨ���������
//Add by wanxin
/////////////////////////////////////////////////////////////////////////
BOOL CAglient8164Ctrl::PrepareSenseScan(long lScanParam,int nSlotIndex)
{
   	char chSendBuf[MAX_PATH];
	ViUInt32 nGetLength;
	CString strTemp;
	char* token=NULL;
    char sep[]=",";
	int nCount=0;
	double dbWL;
	int nAtimTime;
	try
	{
		m_pScanParam = (PScanParam)lScanParam;
		m_nPMBeginSlotIndex = nSlotIndex;
		dbWL = (m_pScanParam->m_dblStartWL+m_pScanParam->m_dblStopWL)/2;
		nAtimTime = (int)(((m_pScanParam->m_dblStopWL - m_pScanParam->m_dblStartWL)/(double)m_pScanParam->m_nSpeed/m_pScanParam->m_dwSampleCount)*1E6);
		if (nAtimTime < 100)
		{
			throw"The PM Average Scan Time Error";
		}
		for (int nIndex=m_MainFrameInfo.nBeginSlotIndex;nIndex < m_MainFrameInfo.nSlotCount;nIndex++)
		{
			//ͨ���ò��������жϵ�ǰchannel�Ƿ���Ҫ����ɨ��
			//����¼����
			//�ж�����Ϊ�� ͨ����1 channel  0001
			//                   2 channel  0010
			//                   3 channel  0100
			//���Ϊ������ÿһ��bit����1

			if (m_MainFrameInfo.pSlot[nIndex].bOnline ==0
				&&m_MainFrameInfo.pSlot[nIndex].nDeviceType == TAG_PM)
			{
				
				if (m_MainFrameInfo.pSlot[nIndex].nChanelCout > 1)
				{
					if(!(m_pScanParam->m_dwChannelCfgLow & (1 << (nIndex))))
						 continue;
					ZeroMemory(chSendBuf,sizeof(char)*MAX_PATH);
					sprintf(chSendBuf,"sens%d:func:stat logg,stop\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send set log stop error";
					}		
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					sprintf(chSendBuf, "sens%d:pow:gain:auto 0\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send init cont mode error";
					}
					//����RangeΪManualģʽ
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					sprintf(chSendBuf, "sens%d:pow:rang:auto 0\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send range auto mode error";
					}
					
					//���õ�ǰͨ����Range��Rangeֻ��������
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					sprintf(chSendBuf, "sens%d:pow:rang %dDBM\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex,(int)m_pScanParam->m_dblPWMPower);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send range auto mode error";
					}
					//���ù��ʼ�Ϊwm
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					sprintf(chSendBuf, "sens%d:chan%d:pow:unit 1\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex,1);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send power unit error";
					}

					//���ù��ʼƲ���
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					sprintf(chSendBuf, "sens%d:chan%d:pow:wav %.3fnm\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex,1,dbWL);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send PM WL error";
					}

					//���ù��ʼ�Ϊwm
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					sprintf(chSendBuf, "sens%d:chan%d:pow:unit 1\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex,2);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send power unit error";
					}
					
					//���ù��ʼƲ���
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					sprintf(chSendBuf, "sens%d:chan%d:pow:wav %.3fnm\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex,2,dbWL);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send PM WL error";
					}

					//���ù��ʼ�Ϊwm
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					sprintf(chSendBuf, "sens%d:chan%d:pow:unit 1\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex,2);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send power unit error";
					}
					
					//����AverageTime
					ZeroMemory(chSendBuf,sizeof(char)*MAX_PATH);
					sprintf(chSendBuf,"sens%d:pow:atim 100us\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send average Time error";
					}
					
					ZeroMemory(chSendBuf,sizeof(char)*MAX_PATH);
					sprintf(chSendBuf,"trig%d:inp sme\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send trig inp mme error";
					}
					
					//���ù��ʼ�ɨ�����
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					sprintf(chSendBuf, "sens%d:func:par:logg %d,100us",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex,m_dwScanPoint);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send trig sme error";
					}
				}
				else
				{
					if(!(m_pScanParam->m_dwChannelCfgLow & (1 << (nIndex))))
						 continue;
					ZeroMemory(chSendBuf,sizeof(char)*MAX_PATH);
					sprintf(chSendBuf,"sens%d:func:stat logg,stop\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send set log stop error";
					}		
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					sprintf(chSendBuf, "sens%d:pow:gain:auto 0\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send init cont mode error";
					}
					//����RangeΪManualģʽ
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					sprintf(chSendBuf, "sens%d:pow:rang:auto 0\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send range auto mode error";
					}
					
					//���õ�ǰͨ����Range��Rangeֻ��������
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					sprintf(chSendBuf, "sens%d:pow:rang %dDBM\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex,(int)m_pScanParam->m_dblPWMPower);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send range auto mode error";
					}
					//���ù��ʼ�Ϊwm
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					sprintf(chSendBuf, "sens%d:pow:unit 1\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send power unit error";
					}
					
					//����AverageTime
					ZeroMemory(chSendBuf,sizeof(char)*MAX_PATH);
					sprintf(chSendBuf,"sens%d:pow:atim 100us\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send average Time error";
					}
					
					ZeroMemory(chSendBuf,sizeof(char)*MAX_PATH);
					sprintf(chSendBuf,"trig%d:inp sme\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send trig inp mme error";
					}
					
					//���ù��ʼ�ɨ�����
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					sprintf(chSendBuf, "sens%d:func:par:logg %d,100us",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex,m_dwScanPoint);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send trig sme error";
					}				
				}	
			}
		}			
	}
	catch (char* pstrMsg)
	{ 
		AfxMessageBox(pstrMsg);
        return FALSE;
	}
	return TRUE;	
}
///////////////////////////////////////////////
//����˵����
//    ���ù��ʼ�ģ�鿪ʼ����ɨ�蹦�ʵ�
//Add by wanxin
/////////////////////////////////////////////////
BOOL CAglient8164Ctrl::SetPMScanBegin()
{
	char chSendBuf[MAX_PATH];
	CString strTemp;
	ViUInt32 nGetLength;
	try
	{
		for (int nIndex=m_MainFrameInfo.nBeginSlotIndex;nIndex < m_MainFrameInfo.nSlotCount;nIndex++)
		{						
			if (m_MainFrameInfo.pSlot[nIndex].bOnline ==0
				&&m_MainFrameInfo.pSlot[nIndex].nDeviceType == TAG_PM)
			{
				
				ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
				sprintf(chSendBuf,"sens%d:func:stat logg,star\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Send fun log start error";
				}
				
				//��ѯɨ��״̬�Ƿ�Ϊstablity��Progress״̬
				ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
				sprintf(chSendBuf, "sens%d:func:stat?",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Read fun state error";
				}
				int nCount =0;
				while(TRUE)
				{
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					viRead(m_hAglient81960A,(unsigned char*)chSendBuf,MAX_PATH,&nGetLength);
					
					strTemp.Format("%s",chSendBuf);

					if (strTemp.Find("LOGGING_STABILITY,PROGRESS") != -1)
					{			
						break;
					}
					
					if (nCount > 10)
					{
						throw"PM's mode is not LOGGING_STABILITY,PROGRESS";
					}
					nCount++;
				}
			}
		}		
	}
	catch (char* pstrMsg)
	{
		AfxMessageBox(pstrMsg);
		return FALSE;
	}
	return TRUE;
}
////////////////////////////////////////////////////////////////////////
//����˵����
//    ���ɨ�蹦�ʵ㺯��
//Add by wanxin
///////////////////////////////////////////////////////////////////////
BOOL CAglient8164Ctrl::getLambdaScanPMResult(int nSlotIndex,int nChannel,double* pdbPMArry)
{
	char chReadBuf[MAX_PATH];
	int nTempLen;
	PBYTE pbyBuf=NULL;
	CString strTemp;
	float fPreTemp=0.0;
	double dbPMTemp;
	float *pfPowerArray;
	ViUInt32 nGetLength;
	
	try
	{	

		//��ѯLog״̬
		while(TRUE)
		{
			sprintf(chReadBuf,"sens%d:func:stat?",nSlotIndex);
			status =viWrite(m_hAglient81960A,(unsigned char*)chReadBuf,strlen(chReadBuf),&nGetLength);		
			if (!DeviceStatusOK(status))
			{
				throw "Send fun log start error";
			}
			//��ȡ����ɨ������м���������
			ZeroMemory(chReadBuf,MAX_PATH*sizeof(char));	
			status = viRead(m_hAglient81960A,(unsigned char*)chReadBuf,MAX_PATH,&nGetLength);
			if (!DeviceStatusOK(status)) 
			{
				throw "Read fun state error";
			} 
			strTemp = chReadBuf;
			if (strTemp.Find("LOGGING_STABILITY,COMPLETE")!=-1)
			{
				break;
			}
		}
	
		//��ȡɨ����
		sprintf(chReadBuf,"sens%d:chan%d:func:res?",nSlotIndex,nChannel);
		status =viWrite(m_hAglient81960A,(unsigned char*)chReadBuf,strlen(chReadBuf),&nGetLength);		
		if (!DeviceStatusOK(status))
		{
			throw "Send fun log start error";
		}
		//��ȡ����ɨ������м���������
		ZeroMemory(chReadBuf,MAX_PATH*sizeof(char));	
		status = viRead(m_hAglient81960A,(unsigned char*)chReadBuf,2,&nGetLength);
		if (!DeviceStatusOK(status)) 
		{
			throw "Read fun state error";
		} 
		nTempLen = chReadBuf[1] - '0';
		//��ȡ���ݳ���
		ZeroMemory(chReadBuf, sizeof(chReadBuf));
		status = viRead(m_hAglient81960A,(unsigned char*)chReadBuf,nTempLen,&nGetLength);
		if (!DeviceStatusOK(status)) 
		{
			throw "Read fun state error";
		} 
		nTempLen =atoi(chReadBuf);
		//�����ȡ���ݿռ�
		if (pbyBuf ==NULL)
		{
			pbyBuf = new BYTE[nTempLen] ;
		}
			
		ZeroMemory(pbyBuf, sizeof(BYTE)*nTempLen);
		
		status = viRead(m_hAglient81960A,(unsigned char*)pbyBuf,nTempLen,&nGetLength);
		if (!DeviceStatusOK(status)) 
		{
			throw "Read fun state error";
		}
		pfPowerArray =(float*)pbyBuf;		
		
		if (m_dwScanPoint < (DWORD)nTempLen/4)
		{
			throw "��ǰɨ�貨������С�ڹ��ʵ���";
		}
		//���㹦����mwת����dBm				
		for (int nIndex=0;nIndex < nTempLen/4;nIndex ++)
		{			
			fPreTemp = *(pfPowerArray+nIndex);
			dbPMTemp =10*log10(fPreTemp*1000);
			pdbPMArry[nIndex] = dbPMTemp;
		}
		if (pbyBuf !=NULL)
		{
			delete [] pbyBuf;
		}
	}
	catch (char* pstrMsg)
	{
        AfxMessageBox(pstrMsg);
		return FALSE;
	}
	return TRUE;
}

////////////////////////////////////////////////////////////
//����˵����
//    ��ɨ����ɺ���Ҫ����TrigΪignoreģʽ
//Add by wanxin
/////////////////////////////////////////////////////////////
BOOL CAglient8164Ctrl::SetTrigIngnore(int nChannel)
{
	char chSendBuf[MAX_PATH];
	ViUInt32 nGetLength;

	try
	{
		ZeroMemory(chSendBuf,sizeof(char)*MAX_PATH);
		sprintf(chSendBuf,"trig%d:inp ign",nChannel);
		status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
		if (!DeviceStatusOK(status))
		{
			throw "Send set trig ignore error";
		}
	}
	catch (char*pstrMsg)
	{
		AfxMessageBox(pstrMsg);
		return FALSE;
	}
	return TRUE;
}
//////////////////////////////////////////////////
//����˵����
//    ֹͣ���ʼ�ɨ���LogΪstopģʽ
//    ���LogΪstopģʽ�����ѯ���ʼ�״̬Ϊ
//    NONE,PROGRESS
//Add by wanxin
///////////////////////////////////////////////////
BOOL CAglient8164Ctrl::SetPMScanStop()
{
	char chSendBuf[MAX_PATH];
	ViUInt32 nGetLength;
	CString strTemp;
	
	try
	{		
		for (int nIndex=m_MainFrameInfo.nBeginSlotIndex;nIndex < m_MainFrameInfo.nSlotCount;nIndex++)
		{					
			if (m_MainFrameInfo.pSlot[nIndex].bOnline ==0
				&&m_MainFrameInfo.pSlot[nIndex].nDeviceType == TAG_PM)
			{						
				if(!(m_pScanParam->m_dwChannelCfgLow & (1 << (nIndex - 1))))
				    continue;
				
				//ֹͣLogΪstopģʽ
				ZeroMemory(chSendBuf,sizeof(char)*MAX_PATH);
				sprintf(chSendBuf,"sens%d:func:stat logg,stop\n",nIndex);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Send set log stop error";
				}
				Sleep(2000);
				//��ѯ���ʼƵ�ǰ״̬
				sprintf(chSendBuf,"sens%d:func:stat?",nIndex);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Read  fun state error";
				}
				int nCount =0;
				while(TRUE)
				{
					ZeroMemory(chSendBuf,MAX_PATH*sizeof(char));	
					viRead(m_hAglient81960A,(unsigned char*)chSendBuf,MAX_PATH,&nGetLength);
					strTemp = chSendBuf;
					if (strTemp.Find("NONE,PROGRESS")!=-1)
					{
						break;
						//throw"Stop Log scan��the state is not NONE, PROGRESS";
					}
					if (nCount > 60)
					{
						throw"Stop Log scan��the state is not NONE, PROGRESS";
					}
					nCount++;
				}
			}
		}
	}
	catch (char*pstrMsg)
	{
		AfxMessageBox(pstrMsg);
		return FALSE;
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//����˵����
//    ��ȡ����ͨ���Ĺ���
//Add by wanxin
//////////////////////////////////////////////////////////////////////////
BOOL CAglient8164Ctrl::ReadPower(long lSlotIndex,double &dblPowerValue)
{
	char chSendBuf[MAX_PATH];
	ViUInt32 nGetLength;

	try
	{
		ZeroMemory(chSendBuf,sizeof(char)*MAX_PATH);
		sprintf(chSendBuf,"fetc%d:pow?\n",lSlotIndex);
		status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
		if (!DeviceStatusOK(status))
		{
			throw "Send  fun log start error";
		}

		ZeroMemory(chSendBuf, sizeof(chSendBuf));
		status = viRead(m_hAglient81960A,(unsigned char*)chSendBuf,MAX_PATH,&nGetLength);
		if (!DeviceStatusOK(status)) 
		{
			throw "Read  fun state error";
		}
		ASSERT(chSendBuf);
		dblPowerValue = atof(chSendBuf);
	}
	catch (char*pstrMsg)
	{
		AfxMessageBox(pstrMsg);
		return FALSE;
	}
	return TRUE;
}

///////////////////////////////////////////////////////
//����˵����
//    ���ù��ʼ�channel����ʱ��
//Add by wanxin
///////////////////////////////////////////////////////
BOOL CAglient8164Ctrl::SetPWMAverageTime(long lSlotIndex, double dblAvgTime)
{
	char chSendBuf[MAX_PATH];
	ViUInt32 nGetLength;

	try
	{
		ZeroMemory(chSendBuf,sizeof(char)*MAX_PATH);
		sprintf(chSendBuf,"sens%d:pow:atim %.3fms\n",lSlotIndex);
		status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
		if (!DeviceStatusOK(status))
		{
			throw "Send  averag time error";
		}
	}
	catch (char*pstrMsg)
	{
		AfxMessageBox(pstrMsg);
		return FALSE;
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////
//����˵����
//    ����range ģʽ
//Add by wanxin
////////////////////////////////////////////////////////////////////////////
BOOL CAglient8164Ctrl::SetPWMRangeMode(long lSlotIndex, long bAtuo)
{
	char chSendBuf[MAX_PATH];
	ViUInt32 nGetLength;

	try
	{
		ZeroMemory(chSendBuf,sizeof(char)*MAX_PATH);
		sprintf(chSendBuf,"sens%d:pow:rang:auto %d\n",lSlotIndex,bAtuo);
		status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
		if (!DeviceStatusOK(status))
		{
			throw "Send  rang mode error";
		}
	}
	catch (char*pstrMsg)
	{
		AfxMessageBox(pstrMsg);
		return FALSE;
	}
	return TRUE;
}
////////////////////////////////////////////////////////////////
//����˵����
//    ���ù��ʼƵ�λ
//Add by wanxin
//////////////////////////////////////////////////////////////////
BOOL CAglient8164Ctrl::SetPWMUnit(long lSlotIndex, long lPWMUnit)
{
	char chSendBuf[MAX_PATH];
	ViUInt32 nGetLength;

	try
	{
		ZeroMemory(chSendBuf,sizeof(char)*MAX_PATH);
		sprintf(chSendBuf,"sens%d:pow:unit %d\n",lSlotIndex,lPWMUnit);
		status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
		if (!DeviceStatusOK(status))
		{
			throw "Send set  unit error";
		}
	}
	catch (char*pstrMsg)
	{
		AfxMessageBox(pstrMsg);
		return FALSE;
	}
	return TRUE;
}

///////////////////////////////////////////////////////////
//����˵����
//    ���ù��ʼ�ͨ���Ĳ���
//Add by wanxin
/////////////////////////////////////////////////////////////////
BOOL CAglient8164Ctrl::SetPWMWavelength(long lSlotIndex, double dblWavelength)
{
	char chSendBuf[MAX_PATH];
	ViUInt32 nGetLength;

	try
	{
		ZeroMemory(chSendBuf,sizeof(char)*MAX_PATH);
		sprintf(chSendBuf,"sens%d:pow:wav %.1fnm\n",lSlotIndex,dblWavelength);
		status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
		if (!DeviceStatusOK(status))
		{
			throw "Send set WL error";
		}
	}
	catch (char*pstrMsg)
	{
		AfxMessageBox(pstrMsg);
		return FALSE;
	}
	return TRUE;
}
////////////////////////////////////////////////////////////
//����˵����
//    ������ɨ�裬�����ı�ɨ���Range����
//Add by wanxin
/////////////////////////////////////////////////////////////
BOOL CAglient8164Ctrl::ModifyScanRange(int nRange)
{
	char chSendBuf[MAX_PATH];
	ViUInt32 nGetLength;
	
	try
	{
		ASSERT(m_pScanParam);
		for (int nIndex=m_MainFrameInfo.nBeginSlotIndex;nIndex < m_MainFrameInfo.nSlotCount;nIndex++)
		{			
			if (m_MainFrameInfo.pSlot[nIndex].bOnline ==0
				&&m_MainFrameInfo.pSlot[nIndex].nDeviceType == TAG_PM)
			{			
				
				if(!(m_pScanParam->m_dwChannelCfgLow & (1 << (nIndex-1))))
					continue;
				ZeroMemory(chSendBuf,sizeof(char)*MAX_PATH);
				sprintf(chSendBuf,"sens%d:func:stat logg,stop\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Send set log stop error";
				}
				ZeroMemory(chSendBuf,sizeof(char)*MAX_PATH);
				sprintf(chSendBuf,"sens%d:pow:rang %dDBM\n",nIndex,nRange);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Send set range error";
				}
			}
		}
	}
	catch (char*pstrMsg)
	{
		AfxMessageBox(pstrMsg);
		return FALSE;
	}
	return TRUE;
}
////////////////////////////////////////////////////////////
//����˵��:
//    ִ��ɨ�裬�����ɨ������
//Add by wanxin
///////////////////////////////////////////////////////////
BOOL CAglient8164Ctrl::ExecuteScan(POp816XRawData pRawData)
{
	stOp816XRawData m_ScanResult;
	stOp816XRawData stTempData;
	int nScanCount,nFlag;
	int nFirstRange;
	int nPMSettingRange; 
	double* pdbWLArry[2]={NULL,NULL};
	double* pdbPMArry[2]={NULL,NULL};
		
	try
	{
		m_ScanResult.m_pdblWavelengthArray = NULL;
		m_ScanResult.m_pdwDataArrayAddr  = NULL;
		stTempData.m_pdblWavelengthArray = NULL;
		stTempData.m_pdwDataArrayAddr = NULL;
		ASSERT(pRawData->m_pdblWavelengthArray);
        //�������ɨ������channel�������豸Slot��Ӧ��ϵ
		CreateChVsSlotRelation(m_stChSlot);
        //ʵ��ɨ�����
		for (DWORD i =0;i<m_pScanParam->m_dwSampleCount;i++)
		{
           pRawData->m_pdblWavelengthArray[i] =  m_pScanParam->m_dblStartWL +i*m_pScanParam->m_dblStepSize;
		}
		//��������PM���ʼ����ʼɨ��Range
        nPMSettingRange = (int)(m_pScanParam->m_dblPWMPower/10)*10;
		nFirstRange = nPMSettingRange;

        //���m_ScanParam.m_dwNumberOfScan>1,���ʾ���ж��Range����
		nScanCount = 1;
		nFlag = 0;
		for (DWORD nScanIndex=0;nScanIndex <= m_pScanParam->m_dwNumberOfScan;nScanIndex++ )
		{
			//�ı�ɨ��Range
			if (!ModifyScanRange(nPMSettingRange))
			{
				throw"Set PM Range error";
			}
			if (!SetPMScanBegin())
			{
				throw "PM begin scan error";
			}
			//����ɨ��trig
			if (!SendSoftTrig())
			{
				throw"Send Sotf trig error";
			}
			if (nScanIndex > 0)
			{
				//���ɨ�貨��
				if (stTempData.m_pdblWavelengthArray ==NULL)
				{
					stTempData.m_pdblWavelengthArray = (double*)VirtualAlloc(NULL,sizeof(double)*m_dwScanPoint,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
					if (!GetLamdaScanWLResult(stTempData.m_pdblWavelengthArray ))
					{
						throw"Read Scan WL Data error";
					}
				}
				//���ͨ��ɨ������
				if (stTempData.m_pdwDataArrayAddr ==NULL)
				{
					stTempData.m_pdwDataArrayAddr = (DWORD*)VirtualAlloc(NULL,sizeof(DWORD)*m_pScanParam->m_dwChannelNumber,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
					for (DWORD i=0;i<m_pScanParam->m_dwChannelNumber;i++)
					{
						double* pGetData = (double*)VirtualAlloc(NULL,sizeof(double)*m_dwScanPoint,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
						stTempData.m_pdwDataArrayAddr[i] = (DWORD)pGetData;	
						
						if (m_pScanParam->m_dwChannelCfgLow & 1<<i)
						{
							
							if (!getLambdaScanPMResult(m_stChSlot[i].nCurSlotIndex,m_stChSlot[i].nCurChIndex,pGetData))
							{
								throw"Get PM Scan Data error";
							}							
							
							if (m_bSaveScanRawData)
							{
								if (!SaveScanRawData(nScanIndex,i,stTempData.m_pdblWavelengthArray,pGetData,m_dwScanPoint))
								{
									throw"Save Scan Raw Data error";
								}
							}
						}
						
						//��������Range�ĵ���
						double *pdbTemp =(double*)m_ScanResult.m_pdwDataArrayAddr[i];
						m_algorth.GetMergeArray(pdbTemp,pGetData,nFirstRange,DtValid_Range,m_dwScanPoint);
						double *dbpTempData = (double*)pRawData->m_pdwDataArrayAddr[i];
						m_algorth.LinearFitRaw(m_ScanResult.m_pdblWavelengthArray,pdbTemp,m_dwScanPoint,
							pRawData->m_pdblWavelengthArray,m_pScanParam->m_dwSampleCount,dbpTempData);
						
					}
				}
			}
			else
			{
				//���ɨ�貨��
				if (m_ScanResult.m_pdblWavelengthArray ==NULL)
				{
					m_ScanResult.m_pdblWavelengthArray = (double*)VirtualAlloc(NULL,sizeof(double)*m_dwScanPoint,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
					if (!GetLamdaScanWLResult(m_ScanResult.m_pdblWavelengthArray))
					{
						throw"Read Scan WL Data error";
					}
				}
				//���ͨ��ɨ������
				if (m_ScanResult.m_pdwDataArrayAddr ==NULL)
				{
					m_ScanResult.m_pdwDataArrayAddr = (DWORD*)VirtualAlloc(NULL,sizeof(DWORD)*m_pScanParam->m_dwChannelNumber,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
					for (DWORD i=0;i<m_pScanParam->m_dwChannelNumber;i++)
					{
						double* pGetData = (double*)VirtualAlloc(NULL,sizeof(double)*m_dwScanPoint,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
						m_ScanResult.m_pdwDataArrayAddr[i] =(DWORD)pGetData;	
						
						if (m_pScanParam->m_dwChannelCfgLow & 1<<i)
						{
							if (!getLambdaScanPMResult(m_stChSlot[i].nCurSlotIndex,m_stChSlot[i].nCurChIndex,pGetData))
							{
								throw"Get PM Scan Data error";
							}	
							if (JudgePowerRangeIsOK(pGetData,m_dwScanPoint)) 
							{
								nScanCount = 0;
							}
							else
							{
								nScanCount = 1;
							}
							nFlag |= nScanCount;
							if (m_bSaveScanRawData)
							{
								if (!SaveScanRawData(nScanIndex,i,m_ScanResult.m_pdblWavelengthArray,pGetData,m_dwScanPoint))
								{
									throw"Save Scan Raw Data error";
								}
							}
							if (nScanCount ==0)
							{
								//�����ڲ�
								double *dbpTempData = (double*)pRawData->m_pdwDataArrayAddr[i];
								m_algorth.LinearFitRaw(m_ScanResult.m_pdblWavelengthArray,pGetData,m_dwScanPoint,
									pRawData->m_pdblWavelengthArray,m_pScanParam->m_dwSampleCount,dbpTempData);		
							}

						}
					
					}
					
					m_pScanParam->m_dwNumberOfScan = nFlag;				
				}			
			}

			nPMSettingRange -= m_nPMRangeOffset;
		}
		
		if (m_ScanResult.m_pdblWavelengthArray !=NULL)
		{
			VirtualFree(m_ScanResult.m_pdblWavelengthArray,0,MEM_RELEASE);
			m_ScanResult.m_pdblWavelengthArray = NULL;
		}
		if (m_ScanResult.m_pdwDataArrayAddr !=NULL)
		{
			double* pGetData;
			for (DWORD i=0;i<m_pScanParam->m_dwChannelNumber;i++)
			{
				pGetData = (double*)m_ScanResult.m_pdwDataArrayAddr[i];
				VirtualFree(pGetData,0,MEM_RELEASE);
				pGetData  =NULL;
			}
			VirtualFree(m_ScanResult.m_pdwDataArrayAddr,0,MEM_RELEASE);
			m_ScanResult.m_pdwDataArrayAddr = NULL;
		}
		if (stTempData.m_pdblWavelengthArray !=NULL)
		{
			VirtualFree(m_ScanResult.m_pdblWavelengthArray,0,MEM_RELEASE);
			m_ScanResult.m_pdblWavelengthArray = NULL;
		}
		if (stTempData.m_pdwDataArrayAddr !=NULL)
		{
			double* pGetData;
			for (DWORD i=0;i<m_pScanParam->m_dwChannelNumber;i++)
			{
				pGetData = (double*)stTempData.m_pdwDataArrayAddr[i];
				VirtualFree(pGetData,0,MEM_RELEASE);
				pGetData  =NULL;
			}
			VirtualFree(stTempData.m_pdwDataArrayAddr,0,MEM_RELEASE);
			stTempData.m_pdwDataArrayAddr = NULL;
		}
	}
	catch (char* pszMsg)
	{
		AfxMessageBox(pszMsg);
		return FALSE;
	}
	return TRUE;
}
///////////////////////////////////////////////////////////
//����˵����
//    ����8164��������˥��
//Add by wanxin
/////////////////////////////////////////////////////////////////
BOOL CAglient8164Ctrl::SetTLSAttenuation(double dbSetValue)
{
	char chSendBuf[MAX_PATH];
	ViUInt32 nGetLength;

	try
	{
		for (int nIndex=m_MainFrameInfo.nBeginSlotIndex;nIndex < m_MainFrameInfo.nSlotCount;nIndex++)
		{			
			if (m_MainFrameInfo.pSlot[nIndex].bOnline ==0
				&&m_MainFrameInfo.pSlot[nIndex].nDeviceType == TAG_TLS)
			{
				ZeroMemory(chSendBuf,sizeof(char)*MAX_PATH);
				sprintf(chSendBuf,"sour%d:pow:att %.2f\n",nIndex,dbSetValue);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Send set TLS Atten error";
				}
			}
		}
	}
	catch (char*pstrMsg)
	{
		AfxMessageBox(pstrMsg);
		return FALSE;
	}
	return TRUE;
}
void CAglient8164Ctrl::SetSaveRawData(BOOL bSave)
{
	m_bSaveScanRawData = bSave;
}
BOOL CAglient8164Ctrl::SaveScanRawData(int nScanIndex,int nChannel,double*pdbWL,double*pdbReadPower,int nPointCount)
{
	char szBuf[MAX_PATH];
	FILE* fpFile= NULL;
	CString strFileName,strTemp;
	try
	{
		GetCurrentDirectory(MAX_PATH,szBuf);
		strFileName.Format("%s\\ScanRawData_%d_Ch%d.csv",szBuf,nScanIndex,nChannel);
		fpFile =fopen(strFileName,"w+");
		if (fpFile==NULL)
		{
			throw"Open Scan Raw Data error";
		}
		strTemp.Format("WL,Power\n");
		fprintf(fpFile,"%s",strTemp);
		
		for (int i=0;i<nPointCount;i++)
		{
			strTemp.Format("%lf,%lf",pdbWL[i],pdbReadPower[i]);
			fprintf(fpFile,"%s\n",strTemp);
		}
		if (fpFile !=NULL)
		{
			fclose(fpFile);	
		}
	}
	catch(char* pstrMsg)
	{
		AfxMessageBox(pstrMsg);
		return FALSE;
	}
    return TRUE;
}
///////////////////////////////////////////////////////
//����˵����
//    ���ݻ�ù��ʵ��жϵ�ǰRange�Ƿ�OK��
//    okֻɨһ��Range����OKɨ����Range����
//Add by wanxin
///////////////////////////////////////////////////////
BOOL CAglient8164Ctrl::JudgePowerRangeIsOK(double * pdbPowerData,int nPoint)
{
	double dbMWPower;
	for (int nIndex =0;nIndex < nPoint;nIndex ++)
	{
        dbMWPower = (double)pow(10,pdbPowerData[nIndex]/10);
		if (dbMWPower < 0.0)
		{
			return FALSE;
		}
	}
	return TRUE;
}
void CAglient8164Ctrl::SetScanRangeOffset(int nOffset)
{
	m_nPMRangeOffset = nOffset;
}
/////////////////////////////////////////////////////////////////
//����˵����
//    ��������ɨ��ͨ���������豸slot�š�channel�Ŷ�Ӧ��ϵ
//Add by wanxin
/////////////////////////////////////////////////////////////////
void CAglient8164Ctrl::CreateChVsSlotRelation(pstChVsSlot pData)
{
	int nChannel;
	nChannel = 0;
	for (int nIndex = m_MainFrameInfo.nBeginSlotIndex;nIndex < m_MainFrameInfo.nSlotCount;nIndex++)
	{
		if (m_MainFrameInfo.pSlot[nIndex].bOnline ==0
			&&m_MainFrameInfo.pSlot[nIndex].nDeviceType == TAG_PM)
		{
			if (m_MainFrameInfo.pSlot[nIndex].nChanelCout > 1)
			{
                pData[nIndex].nLogicalChIndex = nChannel;
				pData[nIndex].nCurSlotIndex = nIndex;			
				pData[nIndex].nCurChIndex = 1;
				nChannel ++;

				pData[nIndex].nLogicalChIndex = nChannel;
				pData[nIndex].nCurSlotIndex = nIndex;			
				pData[nIndex].nCurChIndex = 2;
			}
			else
			{
                pData[nIndex].nLogicalChIndex = nChannel;
				pData[nIndex].nCurSlotIndex = nIndex;			
				pData[nIndex].nCurChIndex = 1;
			}

			nChannel ++;
		}
		
	}
}