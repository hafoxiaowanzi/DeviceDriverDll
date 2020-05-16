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
//函数说明：
//    输入初始化结构体
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
//函数说明：
//    用来连接Aglient 81690A模块，该模块可以用于8163A/B、
//    8164,8166等MainFrame
//作者：wanxin wang
//时间：2012-11-20     
///////////////////////////////////////////////////////////////////////////////
BOOL CAglient8164Ctrl::OpenDevice()
{
	ViChar szDeviceDescriptor[VI_FIND_BUFLEN];
	int nType = m_stDeviceIniatal.nComType;
	try
	{
		//打开visa的资源管理器
		status = viOpenDefaultRM (&defaultRM);
		if(!DeviceStatusOK(status))
		     throw"open visa RM error";

		if (nType < 0 ||nType > 10)
		{
			throw"Comunication type setting error";
		}
		
		//根据通讯类型建立连接
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

		//获得MainFrame信息
        ZeroMemory(&m_MainFrameInfo,sizeof(stMainFrame));
		if (!GetMainFrameInfo(&m_MainFrameInfo))
		{
           throw"Get MainFrame Info error";
		}
		//获得Slot信息
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
//函数说明：
//    判断返回状态函数
//////////////////////////////////////////////////////////
BOOL CAglient8164Ctrl::DeviceStatusOK(ViStatus viStatus)	
{
	return (viStatus >= VI_SUCCESS);
}
///////////////////////////////////////////////////////////////
//函数说明：
//    关闭visa资源管理器
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
//函数说明：
//    初始化激光器包括：激光器重置、解锁、打开激光等
//Add by wanxin
///////////////////////////////////////////////////////////////
BOOL CAglient8164Ctrl::InitalDeive()
{
	char szSenBuf[MAX_PATH];
	ViUInt32 nGetLength;
	try
	{					
		//判断激光器是否被锁定
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
//函数说明：
//    通过发送*IDN?指令查询当前MainFrame类型
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
			//根据MainFrame的型号确定slot信息
			//开辟slot信息结构体空间
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
//函数说明：
//    获得slot模块信息
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
			//查询模块是否为在线
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
				//查询模块类型				
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
//函数说明：
//    打开激光器
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
			//如果设备在线
			if (m_MainFrameInfo.pSlot[nIndex].bOnline ==0
				&&m_MainFrameInfo.pSlot[nIndex].nDeviceType == TAG_TLS
				&&m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex !=0)
			{
				//设置激光器状态
				ZeroMemory(chSendBuf,MAX_PATH);
				sprintf(chSendBuf,"sour%d:pow:stat %d\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex,bOpen);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Send laser state command error";
				}
				//读取激光器状态
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
				//设置激光器状态
				ZeroMemory(chSendBuf,MAX_PATH);
				sprintf(chSendBuf,"sour%d:pow:stat %d\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex,bOpen);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Send laser state command error";
				}
				//读取激光器状态
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
				if (bOpen) //设置高光功率
				{
					ZeroMemory(chSendBuf,MAX_PATH);
					sprintf(chSendBuf,"output%d:path high\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send laser state command error";
					}
				}
				else //设置低光功率
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
//函数说明：
//    设置模块激光输出功率
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
			//如果设备在线
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
//函数说明：
//    读取TLS输出功率
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
			//如果设备在线
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
//函数说明：
//    设置激光器模块波长波长
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
			//如果设备在线
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
//函数说明：
//    读取设置的波长
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
			//如果设备在线
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
//函数说明：
//    获得扫描波长函数
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
			//如果设备在线
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
				
				//从TLS扫描结果中读取点数
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
//函数说明：
//    设置81960A 输出功率单位
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
			//如果设备在线
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
//函数说明：
//     查询操作完成
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
//函数说明：
//    用来进行扫描初始化函数
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
		//根据设置的扫描范围多扫0.05nm
		dbStartWL = m_pScanParam->m_dblStartWL - 0.5;	
		dbStopWL = m_pScanParam->m_dblStopWL + 0.5;

		m_pScanParam->m_dwSampleCount  = (DWORD)((m_pScanParam->m_dblStopWL - m_pScanParam->m_dblStartWL)/m_pScanParam->m_dblStepSize + 0.5);

		for (int nIndex = m_MainFrameInfo.nBeginSlotIndex;nIndex <m_MainFrameInfo.nSlotCount;nIndex++)
		{
			//如果设备在线
			if (m_MainFrameInfo.pSlot[nIndex].bOnline ==0
				&&m_MainFrameInfo.pSlot[nIndex].nDeviceType == TAG_TLS)
			{
				//如果双向扫描标志为TRUE，则实行双向扫描，否则实行单向扫描
				if (m_bTwowayScan)
				{
					//设置扫描模式为step模式
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					sprintf(chSendBuf, "sour%d:wav:swe:mode step\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send  TLS scan mode error";
					}
					//设置Repeat模式为TWOWAY 
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					sprintf(chSendBuf, "sour%d:wav:swe:rep twow\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send  TLS scan mode error";
					}
					//设置扫描模式为continue模式
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
					//设置扫描模式为continue模式
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					sprintf(chSendBuf, "sour%d:wav:swe:mode cont\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send  TLS scan mode error";
					}
					//设置Repeat模式为onew模式
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
					// 		//不管激光器是在扫描状态还是不在扫描状态，
					// 		//先发送停止扫描指令	
					if (!SetScanStop())
					{
						throw "Send read laser WL error";
					}
					//设置扫描的起始波长
					if (!SetScanWLRange(dbStartWL,dbStopWL))
					{
						throw"Setting scan WL range error";
					}
					//回读扫描的起始波长
					if (!GetScanWLRange(dbReadStartWL,dbReadStopWL))
					{
						throw"Read Scan WL Range error";
					}
					//判断设置的扫描起始波长与获得的起始波长是否相同
					if (fabs(dbStartWL - dbReadStartWL) > 0.01 || fabs(dbStopWL - dbReadStopWL) > 0.01 )
					{
						throw"Scan WL range error";
					}
					//设置扫描速度
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
					//设置triger扫描步长
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					sprintf(chSendBuf, "sour%d:wav:swe:step %.3fnm\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex,m_pScanParam->m_dblStepSize);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send  TLS scan step command error";
					}
					//设置激光器的功率
					if (!SetTLSPower(m_pScanParam->m_dblTLSPower))
					{
						throw "Setting TLS power error";
					}
				}
				
				//获得扫描的trig点数,并赋值给结构体
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
				
				//设置trig的模式
				ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
				sprintf(chSendBuf, "trig%d:conf 3\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Send TLS scan trig mode error";
				}
				
				//设置tripg输入为sws模式
				ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
				sprintf(chSendBuf, "trig%d:inp sws\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Send  TLS trig out stf mode error";
				}
				//设置trig输出为stf模式
				ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
				sprintf(chSendBuf, "trig%d:outp stf\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Send  TLS trig out stf mode error";
				}
				//设置扫描最大循环次数
				ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
				sprintf(chSendBuf, "sour%d:wav:swe:cycl 0\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Send  TLS scan cycle error";
				}
				//设置am的state模式为0
				ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
				sprintf(chSendBuf, "sour%d:am:stat 0\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Send  TLS am state mode error";
				}
				//设置TLS为Log模式
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
//函数说明：
//    通过触发软trig命令来启动扫描
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
			//如果设备在线
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
//函数说明：
//    通过发送软trig来驱动扫描
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
			//如果设备在线
			if (m_MainFrameInfo.pSlot[nIndex].bOnline ==0
				&&m_MainFrameInfo.pSlot[nIndex].nDeviceType == TAG_TLS)
			{
				//读取Flag标志,如果Flag%2 ==1，则发送trig开始扫描
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
				//读取Flag标志，如果前面的Flag小于当前Flag则认为扫描完成
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
//函数说明：
//    设置激光器扫描停止函数
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
			//如果设备在线
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
//函数说明
//    获得扫描的起始波长范围
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
			//如果设备在线
			if (m_MainFrameInfo.pSlot[nIndex].bOnline ==0
				&&m_MainFrameInfo.pSlot[nIndex].nDeviceType == TAG_TLS)
			{
				
				//读取扫描起始波长
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
				//读取扫描停止波长
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
//函数说明：
//    设置是否进行双向扫描
//Add by wanxin
////////////////////////////////////////////////////////
void CAglient8164Ctrl::SetTwowayScan(BOOL bTwoway)
{
   m_bTwowayScan = bTwoway;

}
/////////////////////////////////////////////////////////
//函数说明：
//     获得模块最大最小的波长范围
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
			//如果设备在线
			if (m_MainFrameInfo.pSlot[nIndex].bOnline ==0
				&&m_MainFrameInfo.pSlot[nIndex].nDeviceType == TAG_TLS)
			{
				//获得最小波长range
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
				
				//获得最大波长range
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
//函数说明：
//    设置扫描起始波长
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
			//如果设备在线
			if (m_MainFrameInfo.pSlot[nIndex].bOnline ==0
				&&m_MainFrameInfo.pSlot[nIndex].nDeviceType == TAG_TLS)
			{
				//设置开始扫描波长
				ZeroMemory(chSendBuf,MAX_PATH);
				sprintf(chSendBuf,"sour%d:wav:swe:star %.3fNM\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex,dbWLStart);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Send scan start WL command error";
				}
				
				//设置停止扫描波长
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
//函数说明：
//    判断当前的扫描参数是否变化,如果设置的与变化的不同则返回FASLE
//    如果判断相同则返回TRUE
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
//函数说明：
//    获得设置的扫描参数
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
			//如果设备在线
			if (m_MainFrameInfo.pSlot[nIndex].bOnline ==0
				&&m_MainFrameInfo.pSlot[nIndex].nDeviceType == TAG_TLS)
			{
				//获得扫描波长
				if (!GetScanWLRange(dbStartWL,dbStopWL))
				{
					throw"Get scan WL error";
				}
				pSettingParam->m_dblStartWL = dbStartWL;
				pSettingParam->m_dblStopWL = dbStopWL;
				
				//获得扫描的speed
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
				
				//获得扫描的step
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
//函数说明：
//    根据输入的扫描参数设置结构体、Slot开始索引号
//    初始化功率计模块扫描参数设置
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
			//通过该参数进行判断当前channel是否需要进行扫描
			//并记录数据
			//判断依据为： 通道：1 channel  0001
			//                   2 channel  0010
			//                   3 channel  0100
			//如果为总数：每一个bit都置1

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
					//设置Range为Manual模式
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					sprintf(chSendBuf, "sens%d:pow:rang:auto 0\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send range auto mode error";
					}
					
					//设置当前通道的Range，Range只能是整数
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					sprintf(chSendBuf, "sens%d:pow:rang %dDBM\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex,(int)m_pScanParam->m_dblPWMPower);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send range auto mode error";
					}
					//设置功率计为wm
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					sprintf(chSendBuf, "sens%d:chan%d:pow:unit 1\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex,1);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send power unit error";
					}

					//设置功率计波长
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					sprintf(chSendBuf, "sens%d:chan%d:pow:wav %.3fnm\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex,1,dbWL);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send PM WL error";
					}

					//设置功率计为wm
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					sprintf(chSendBuf, "sens%d:chan%d:pow:unit 1\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex,2);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send power unit error";
					}
					
					//设置功率计波长
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					sprintf(chSendBuf, "sens%d:chan%d:pow:wav %.3fnm\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex,2,dbWL);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send PM WL error";
					}

					//设置功率计为wm
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					sprintf(chSendBuf, "sens%d:chan%d:pow:unit 1\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex,2);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send power unit error";
					}
					
					//设置AverageTime
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
					
					//设置功率计扫描点数
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
					//设置Range为Manual模式
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					sprintf(chSendBuf, "sens%d:pow:rang:auto 0\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send range auto mode error";
					}
					
					//设置当前通道的Range，Range只能是整数
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					sprintf(chSendBuf, "sens%d:pow:rang %dDBM\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex,(int)m_pScanParam->m_dblPWMPower);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send range auto mode error";
					}
					//设置功率计为wm
					ZeroMemory(chSendBuf, sizeof(char)*MAX_PATH);
					sprintf(chSendBuf, "sens%d:pow:unit 1\n",m_MainFrameInfo.pSlot[nIndex].nCurSlotIndex);
					status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
					if (!DeviceStatusOK(status))
					{
						throw "Send power unit error";
					}
					
					//设置AverageTime
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
					
					//设置功率计扫描点数
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
//函数说明：
//    设置功率计模块开始接收扫描功率点
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
				
				//查询扫描状态是否为stablity，Progress状态
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
//函数说明：
//    获得扫描功率点函数
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

		//查询Log状态
		while(TRUE)
		{
			sprintf(chReadBuf,"sens%d:func:stat?",nSlotIndex);
			status =viWrite(m_hAglient81960A,(unsigned char*)chReadBuf,strlen(chReadBuf),&nGetLength);		
			if (!DeviceStatusOK(status))
			{
				throw "Send fun log start error";
			}
			//读取返回扫描点数有几个数构成
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
	
		//读取扫描结果
		sprintf(chReadBuf,"sens%d:chan%d:func:res?",nSlotIndex,nChannel);
		status =viWrite(m_hAglient81960A,(unsigned char*)chReadBuf,strlen(chReadBuf),&nGetLength);		
		if (!DeviceStatusOK(status))
		{
			throw "Send fun log start error";
		}
		//读取返回扫描点数有几个数构成
		ZeroMemory(chReadBuf,MAX_PATH*sizeof(char));	
		status = viRead(m_hAglient81960A,(unsigned char*)chReadBuf,2,&nGetLength);
		if (!DeviceStatusOK(status)) 
		{
			throw "Read fun state error";
		} 
		nTempLen = chReadBuf[1] - '0';
		//读取数据长度
		ZeroMemory(chReadBuf, sizeof(chReadBuf));
		status = viRead(m_hAglient81960A,(unsigned char*)chReadBuf,nTempLen,&nGetLength);
		if (!DeviceStatusOK(status)) 
		{
			throw "Read fun state error";
		} 
		nTempLen =atoi(chReadBuf);
		//定义读取数据空间
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
			throw "当前扫描波长点数小于功率点数";
		}
		//计算功率由mw转换到dBm				
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
//函数说明：
//    当扫描完成后需要设置Trig为ignore模式
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
//函数说明：
//    停止功率计扫描的Log为stop模式
//    如果Log为stop模式，则查询功率计状态为
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
				
				//停止Log为stop模式
				ZeroMemory(chSendBuf,sizeof(char)*MAX_PATH);
				sprintf(chSendBuf,"sens%d:func:stat logg,stop\n",nIndex);
				status =viWrite(m_hAglient81960A,(unsigned char*)chSendBuf,strlen(chSendBuf),&nGetLength);		
				if (!DeviceStatusOK(status))
				{
					throw "Send set log stop error";
				}
				Sleep(2000);
				//查询功率计当前状态
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
						//throw"Stop Log scan，the state is not NONE, PROGRESS";
					}
					if (nCount > 60)
					{
						throw"Stop Log scan，the state is not NONE, PROGRESS";
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
//函数说明：
//    读取单个通道的功率
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
//函数说明：
//    设置功率计channel采样时间
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
//函数说明：
//    设置range 模式
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
//函数说明：
//    设置功率计单位
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
//函数说明：
//    设置功率计通道的波长
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
//函数说明：
//    如果多次扫描，用来改变扫描的Range函数
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
//函数说明:
//    执行扫描，并获得扫描数据
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
        //创建获得扫描数据channel索引与设备Slot对应关系
		CreateChVsSlotRelation(m_stChSlot);
        //实际扫描点数
		for (DWORD i =0;i<m_pScanParam->m_dwSampleCount;i++)
		{
           pRawData->m_pdblWavelengthArray[i] =  m_pScanParam->m_dblStartWL +i*m_pScanParam->m_dblStepSize;
		}
		//根据输入PM功率计算初始扫描Range
        nPMSettingRange = (int)(m_pScanParam->m_dblPWMPower/10)*10;
		nFirstRange = nPMSettingRange;

        //如果m_ScanParam.m_dwNumberOfScan>1,则表示进行多个Range叠加
		nScanCount = 1;
		nFlag = 0;
		for (DWORD nScanIndex=0;nScanIndex <= m_pScanParam->m_dwNumberOfScan;nScanIndex++ )
		{
			//改变扫描Range
			if (!ModifyScanRange(nPMSettingRange))
			{
				throw"Set PM Range error";
			}
			if (!SetPMScanBegin())
			{
				throw "PM begin scan error";
			}
			//发送扫描trig
			if (!SendSoftTrig())
			{
				throw"Send Sotf trig error";
			}
			if (nScanIndex > 0)
			{
				//获得扫描波长
				if (stTempData.m_pdblWavelengthArray ==NULL)
				{
					stTempData.m_pdblWavelengthArray = (double*)VirtualAlloc(NULL,sizeof(double)*m_dwScanPoint,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
					if (!GetLamdaScanWLResult(stTempData.m_pdblWavelengthArray ))
					{
						throw"Read Scan WL Data error";
					}
				}
				//获得通道扫描数据
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
						
						//进行两个Range的叠加
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
				//获得扫描波长
				if (m_ScanResult.m_pdblWavelengthArray ==NULL)
				{
					m_ScanResult.m_pdblWavelengthArray = (double*)VirtualAlloc(NULL,sizeof(double)*m_dwScanPoint,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
					if (!GetLamdaScanWLResult(m_ScanResult.m_pdblWavelengthArray))
					{
						throw"Read Scan WL Data error";
					}
				}
				//获得通道扫描数据
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
								//线性内插
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
//函数说明：
//    设置8164激光器的衰减
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
//函数说明：
//    根据获得功率点判断当前Range是否OK，
//    ok只扫一个Range，不OK扫两个Range叠加
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
//函数说明：
//    用来生成扫描通道索引与设备slot号、channel号对应关系
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