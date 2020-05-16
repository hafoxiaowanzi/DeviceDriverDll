#include "stdafx.h"
#include "..\\include\\Chamber.h"
#include "math.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHZChamberContorl::CHZChamberContorl()
{
	
}

CHZChamberContorl::~CHZChamberContorl()
{
	
}
/////////////////////////////////////////////////////////////
//函数说明：
//    打开设备
//Add by wanxin
//20140821
//////////////////////////////////////////////////////////////
DWORD CHZChamberContorl::OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle)
{
	//CString strComPort;	
	DWORD   dwErrorCode;
	
	dwErrorCode = m_DevComHandle.OpenDevice(pszDeviceAddr,*ComHandle);	
	return dwErrorCode;
}
/////////////////////////////////////////////////////////////
//函数说明：
//    关闭设备
//Add by wanxin
//20140821
//////////////////////////////////////////////////////////////
DWORD CHZChamberContorl::CloseDevice()
{
	DWORD   dwErrorCode;
	dwErrorCode = m_DevComHandle.CloseDevice();
	return dwErrorCode;
}
/////////////////////////////////////////////////////////////
//函数说明：
//    设置设备句柄指针
//Add by wanxin
//20140821
//////////////////////////////////////////////////////////////
DWORD CHZChamberContorl::SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle)
{
	DWORD   dwErrorCode=0;
	
	dwErrorCode = m_DevComHandle.SetDeviceHandle(pszDeviceAddr, handle);
	return dwErrorCode;
}
/////////////////////////////////////////////////////////////
//函数说明：
//    重置设备
//Add by wanxin
//20140821
//////////////////////////////////////////////////////////////
DWORD CHZChamberContorl::ResetDevice()
{
	DWORD dwErrorCode = FALSE;
	try
	{
		//		dwErrorCode = m_DevComHandle.WriteDevice("*RST\r\n",strlen("*RST\r\n"));
		//		if(SUCCESS != dwErrorCode)
		//		{
		//			throw dwErrorCode|ERROR_RESET;
		//		}
		//		CompleteRequest();
	}
	catch(DWORD dwError)
	{
		return ERROR_CHAMBER | dwError;
	}
	catch(...)
	{
		return ERROR_CHAMBER|UNEXPECT_OCCUR;
	}
	
	return dwErrorCode;
}
/////////////////////////////////////////////////////////////
//函数说明：
//    获得设备信息
//Add by wanxin
//20140821
//////////////////////////////////////////////////////////////
DWORD CHZChamberContorl::GetDeviceInfo(stDevInfo *stInfo)
{
	DWORD dwErrorCode = FALSE;
	try
	{
		//		dwErrorCode = m_DevComHandle.WriteDevice("*IDN?\r\n",strlen("*IDN?\r\n"));
		//		if(SUCCESS != dwErrorCode)
		//		{
		//			throw dwErrorCode|ERROR_RESET;
		//		}
		
	}
	catch(DWORD dwError)
	{
		return ERROR_CHAMBER | dwError;
	}
	catch(...)
	{
		return ERROR_CHAMBER|UNEXPECT_OCCUR;
	}
	
	return dwErrorCode;
}
DWORD  CHZChamberContorl::SetChamberRunStop()
{
	BYTE	byTxBuf[MAX_PATH];
	BYTE	byRxBuf[MAX_PATH];
	BYTE	byCmdLen;
	char    strWrite[MAX_PATH];
	
	DWORD dwErrorCode = FALSE;
	try
	{
		ZeroMemory(strWrite, MAX_PATH);
		sprintf(strWrite, ".01WRD,02,0104,0001,0101,000498");
		//strWrite = ".01WRD,02,0104,0001,0101,000498";
		
		ZeroMemory(byTxBuf, MAX_PATH);
//		LPTSTR lpstrWrite =	strWrite.GetBuffer(strWrite.GetLength());
//		ASSERT(lpstrWrite != NULL);
//		if(lpstrWrite == NULL)
//		{
//			throw dwErrorCode|ERROR_CHAMBER_RUNSTOP;
//		}
		int nCmdLen = strlen(strWrite);
		for (int i = 0 ;i<nCmdLen;i++)
		{
			if(i==0)
			{
				byTxBuf[i] = 0x02;
			}
			else
			{
				byTxBuf[i] = strWrite[i];
			}
		}
		byTxBuf[i] = 0X0D;
		byTxBuf[i+1] = 0X0A;
		byCmdLen = nCmdLen+2;
		
		//strWrite.ReleaseBuffer();
		
		dwErrorCode = m_DevComHandle.WriteDevice((char*)byTxBuf,byCmdLen);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_CHAMBER_RUNSTOP;
		}
		
		
		//	byCmdLen = MODBUS_READ_LENGTH ;   // read back 2 byte in this case
		// OK write reponse  = write buffer                         
		byCmdLen = 64;		
		ZeroMemory(byRxBuf, MAX_PATH);
		
		Sleep(20);
		
		dwErrorCode = m_DevComHandle.ReadDevice((char*)byTxBuf,byCmdLen);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_CHAMBER_RUNSTOP;
		}
		
		
		if(byRxBuf[7]!='O' && byRxBuf[8]!='K')
		{
			throw dwErrorCode|ERROR_CHAMBER_RUNSTOP;
		}
	}
	catch(DWORD dwError)
	{
		return ERROR_CHAMBER | dwError;
	}
	catch(...)
	{
		return ERROR_CHAMBER|UNEXPECT_OCCUR;
	}
	
	return dwErrorCode;
	
}
DWORD CHZChamberContorl::SetChamberRunStart()
{
	
	BYTE	byTxBuf[MAX_PATH];
	BYTE	byRxBuf[MAX_PATH];
	BYTE	byCmdLen;
	//CString strWrite;
	char    strWrite[MAX_PATH];
	
	DWORD dwErrorCode = FALSE;
	try
	{
		ZeroMemory(strWrite, MAX_PATH);
		sprintf(strWrite,".01WRD,02,0104,0001,0101,000195");
		//strWrite = ".01WRD,02,0104,0001,0101,000195";
		
		ZeroMemory(byTxBuf, MAX_PATH);
//		LPTSTR lpstrWrite =	strWrite.GetBuffer(strWrite.GetLength());
//		ASSERT(lpstrWrite != NULL);
//		if(lpstrWrite == NULL)
//		{
//			throw dwErrorCode|ERROR_CHAMBER_RUNSTART;
//		}
		int nCmdLen = strlen(strWrite);
		for (int i = 0 ;i<nCmdLen;i++)
		{
			if(i==0)
			{
				byTxBuf[i] = 0x02;
			}
			else
			{
				byTxBuf[i] = strWrite[i];
			}
		}
		byTxBuf[i] = 0X0D;
		byTxBuf[i+1] = 0X0A;
		byCmdLen = nCmdLen+2;
		
	//	strWrite.ReleaseBuffer();
		
		dwErrorCode = m_DevComHandle.WriteDevice((char*)byTxBuf,byCmdLen);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_CHAMBER_RUNSTART;
		}
		
		
		//	byCmdLen = MODBUS_READ_LENGTH ;   // read back 2 byte in this case
		// OK write reponse  = write buffer                         
		byCmdLen = 64;		
		ZeroMemory(byRxBuf, MAX_PATH);
		
		Sleep(20);
		
		dwErrorCode = m_DevComHandle.ReadDevice((char*)byTxBuf,byCmdLen);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_CHAMBER_RUNSTART;
		}
		
		
		if(byRxBuf[7]!='O' && byRxBuf[8]!='K')
		{
			throw dwErrorCode|ERROR_CHAMBER_RUNSTART;
		}
	}
	catch(DWORD dwError)
	{
		return ERROR_CHAMBER | dwError;
	}
	catch(...)
	{
		return ERROR_CHAMBER|UNEXPECT_OCCUR;
	}
	
	return dwErrorCode;
	
	
}
DWORD CHZChamberContorl::SetChamberSetPoint(double dbSetPoint)
{	
	BYTE	byTxBuf[MAX_PATH];
	BYTE	byRxBuf[MAX_PATH];
	BYTE	byCmdLen;
	char    strWrite[MAX_PATH];
	WORD	wSetPointValue = 0;
//	CString strSetPoint;
	char    szSetPoint[MAX_PATH];
	
	
	DWORD dwErrorCode = FALSE;
	try
	{
		ZeroMemory(strWrite,sizeof(char)*MAX_PATH);
		ZeroMemory(szSetPoint,sizeof(char)*MAX_PATH);
		wSetPointValue = (WORD)dbSetPoint*10;
		
		sprintf(szSetPoint,"%04X",wSetPointValue);
	//	strSetPoint.Format("%04X",wSetPointValue);
		if(strlen(szSetPoint) != 4)
		{
			throw dwErrorCode|ERROR_CHAMBER_SETTEMP;
		}
		
		//strWrite = ".01WSD,05,0200,0001,0190,FE3E,FE3E,FE3E";
		sprintf(strWrite,".01WSD,05,0200,0001,0190,FE3E,FE3E,FE3E");
		
		ZeroMemory(byTxBuf, MAX_PATH);
//		LPTSTR lpstrWrite =	strWrite.GetBuffer(strWrite.GetLength());
//		ASSERT(lpstrWrite != NULL);
//		if(lpstrWrite == NULL)
//		{
//			throw dwErrorCode|ERROR_CHAMBER_SETTEMP;
//		}
		
//		LPTSTR lpSetPoint = strSetPoint.GetBuffer(strSetPoint.GetLength());
//		ASSERT(lpSetPoint != NULL);
//		if(lpSetPoint == NULL)
//		{
//			throw dwErrorCode|ERROR_CHAMBER_SETTEMP;
//		}
		
		int nCmdLen = strlen(strWrite);
		BYTE byCheckSum = 0;
		for (int i = 0 ;i<nCmdLen;i++)
		{
			if(i==0)
			{
				byTxBuf[i] = 0x02;
			}
			else if(i >19 && i<24)
			{
				byTxBuf[i] = szSetPoint[i-20];
			}
			else
			{
				byTxBuf[i] = strWrite[i];
			}
			if(i >0)
			{
				byCheckSum+=byTxBuf[i];
			}			
		}
		//strSetPoint.ReleaseBuffer();
		//strWrite.ReleaseBuffer();
		ZeroMemory(szSetPoint,sizeof(char)*MAX_PATH);
	//	strSetPoint.Format("%02X",byCheckSum);
		sprintf(szSetPoint,"%02X",byCheckSum);
//		LPTSTR lpCheckSum = strSetPoint.GetBuffer(strSetPoint.GetLength());
//		ASSERT(lpCheckSum != NULL);
//		if(lpCheckSum == NULL)
//		{
//			throw dwErrorCode|ERROR_CHAMBER_SETTEMP;
//		}
		byTxBuf[i] = szSetPoint[0];
		byTxBuf[i+1] = szSetPoint[1];
		
		byTxBuf[i+2] = 0X0D;
		byTxBuf[i+3] = 0X0A;
		byCmdLen = nCmdLen+4;
		//strSetPoint.ReleaseBuffer();
		
		dwErrorCode = m_DevComHandle.WriteDevice((char*)byTxBuf,byCmdLen);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_CHAMBER_SETTEMP;
		}                      
		byCmdLen = 64;		
		ZeroMemory(byRxBuf, MAX_PATH);
		
		Sleep(100);
		
		dwErrorCode = m_DevComHandle.ReadDevice((char*)byTxBuf,byCmdLen);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_CHAMBER_SETTEMP;
		}
		
		
		if(byRxBuf[7]!='O' && byRxBuf[8]!='K')
		{
			throw dwErrorCode|ERROR_CHAMBER_SETTEMP;
		}
		
		if(!SetChamberRunStart())
		{
			throw dwErrorCode|ERROR_CHAMBER_SETTEMP;
		}	
	}
	catch(DWORD dwError)
	{
		return ERROR_CHAMBER | dwError;
	}
	catch(...)
	{
		return ERROR_CHAMBER|UNEXPECT_OCCUR;
	}
	
	return dwErrorCode;
	
}
DWORD CHZChamberContorl::GetChamberSetPoint(double* dbSetPoint)
{
	BYTE	byTxBuf[MAX_PATH];
	BYTE	byRxBuf[MAX_PATH];
	BYTE	byCmdLen;
	char    strWrite[MAX_PATH];
	
	DWORD dwErrorCode = FALSE;
	try
	{
		ZeroMemory(strWrite,sizeof(char)*MAX_PATH);
		sprintf(strWrite,".01RRD,30,1,2,10,12,13,14,20,21,25,26,27,28,29,30,31,32,33,34,39,101,104,122,200,201,202,203,204,902,911,91299");
		//strWrite = ".01RRD,30,1,2,10,12,13,14,20,21,25,26,27,28,29,30,31,32,33,34,39,101,104,122,200,201,202,203,204,902,911,91299";
		
		ZeroMemory(byTxBuf, MAX_PATH);
//		LPTSTR lpstrWrite =	strWrite.GetBuffer(strWrite.GetLength());
//		ASSERT(lpstrWrite != NULL);
//		if(lpstrWrite == NULL)
//		{
//			throw dwErrorCode|ERROR_CHAMBER_GETSETTEMP;
//		}
		
		int nCmdLen = strlen(strWrite);
		for (int i = 0 ;i<nCmdLen;i++)
		{
			if(i==0)
			{
				byTxBuf[i] = 0x02;
			}
			else
			{
				byTxBuf[i] = strWrite[i];
			}
			
		}
		byTxBuf[i] = 0X0D;
		byTxBuf[i+1] = 0X0A;
		byCmdLen = nCmdLen+2;
		
	//	strWrite.ReleaseBuffer();
		
		
		dwErrorCode = m_DevComHandle.WriteDevice((char*)byTxBuf,byCmdLen);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_CHAMBER_GETSETTEMP;
		}                      
		byCmdLen = 64;		
		ZeroMemory(byRxBuf, MAX_PATH);
		
		Sleep(100);
		
		dwErrorCode = m_DevComHandle.ReadDevice((char*)byTxBuf,byCmdLen);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_CHAMBER_GETSETTEMP;
		}
		
		
		if(byRxBuf[7]!='O' && byRxBuf[8]!='K')
		{
			throw dwErrorCode|ERROR_CHAMBER_GETSETTEMP;
		}
		
		char chtemp[4];
		ZeroMemory(chtemp,4*sizeof(char));
		chtemp[0] = byRxBuf[15];
		chtemp[1] = byRxBuf[16];
		chtemp[2] = byRxBuf[17];
		chtemp[3] = byRxBuf[18];
		//	int nCurrentTemp = 0;
		short sTemp = 0;
		sscanf(chtemp,"%x",&sTemp);
		//	sscanf(chtemp,"%x",&nCurrentTemp);
		* dbSetPoint = (double)sTemp/10.0;
		if(* dbSetPoint < -200 || * dbSetPoint > 100)
		{
			throw dwErrorCode|ERROR_CHAMBER_GETSETTEMP;
		}
	}
	catch(DWORD dwError)
	{
		return ERROR_CHAMBER | dwError;
	}
	catch(...)
	{
		return ERROR_CHAMBER|UNEXPECT_OCCUR;
	}
	
	return dwErrorCode;
}
DWORD CHZChamberContorl::GetChamberCurrentTemp(double *dbCurrTemp)
{
	BYTE	byTxBuf[MAX_PATH];
	BYTE	byRxBuf[MAX_PATH];
	BYTE	byCmdLen;
	char    strWrite[MAX_PATH];
	int nCmdLen;
	
	DWORD dwErrorCode = FALSE;
	try
	{
		ZeroMemory(strWrite,sizeof(char)*MAX_PATH);
		sprintf(strWrite,".01RRD,30,1,2,10,12,13,14,20,21,25,26,27,28,29,30,31,32,33,34,39,101,104,122,200,201,202,203,204,902,911,91299");
	//	strWrite = ".01RRD,30,1,2,10,12,13,14,20,21,25,26,27,28,29,30,31,32,33,34,39,101,104,122,200,201,202,203,204,902,911,91299";
		
		ZeroMemory(byTxBuf, MAX_PATH);
//		LPTSTR lpstrWrite =	strWrite.GetBuffer(strWrite.GetLength());
//		ASSERT(lpstrWrite != NULL);
//		if(lpstrWrite == NULL)
//		{
//			throw dwErrorCode|ERROR_CHAMBER_GETCURRENTTEMP;
//		}
		
		nCmdLen = strlen(strWrite);
		for (int i = 0 ;i<nCmdLen;i++)
		{
			if(i==0)
			{
				byTxBuf[i] = 0x02;
			}
			else
			{
				byTxBuf[i] = strWrite[i];
			}
			
		}
		byTxBuf[i] = 0X0D;
		byTxBuf[i+1] = 0X0A;
		byCmdLen = nCmdLen+2;
		
		//strWrite.ReleaseBuffer();
		
		dwErrorCode = m_DevComHandle.WriteDevice((char*)byTxBuf,byCmdLen);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_CHAMBER_GETCURRENTTEMP;
		}                      
		byCmdLen = 64;		
		ZeroMemory(byRxBuf, MAX_PATH);
		
		Sleep(100);
		
		dwErrorCode = m_DevComHandle.ReadDevice((char*)byTxBuf,byCmdLen);
		if(SUCCESS != dwErrorCode)
		{
			throw dwErrorCode|ERROR_CHAMBER_GETCURRENTTEMP;
		}
		
		
		if(byRxBuf[7]!='O' && byRxBuf[8]!='K')
		{
			throw dwErrorCode|ERROR_CHAMBER_GETCURRENTTEMP;
		}
		
		char chtemp[4];
		ZeroMemory(chtemp,4*sizeof(char));
		chtemp[0] = byRxBuf[10];
		chtemp[1] = byRxBuf[11];
		chtemp[2] = byRxBuf[12];
		chtemp[3] = byRxBuf[13];
		short nCurrentTemp = 0;
		sscanf(chtemp,"%x",&nCurrentTemp);
		*dbCurrTemp = (double)nCurrentTemp/10.0;
		if(*dbCurrTemp < -200 || *dbCurrTemp > 100)
		{
			throw dwErrorCode|ERROR_CHAMBER_GETCURRENTTEMP;
		}
	}
	catch(DWORD dwError)
	{
		return ERROR_CHAMBER | dwError;
	}
	catch(...)
	{
		return ERROR_CHAMBER|UNEXPECT_OCCUR;
	}
	
	return dwErrorCode;
}