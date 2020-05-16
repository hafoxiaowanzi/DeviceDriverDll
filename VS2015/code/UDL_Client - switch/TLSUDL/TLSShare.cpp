// iTLALaser.cpp: implementation of the CiTLALaser class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\\include\\TLS.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTLSShare::CTLSShare()
{
	//	m_hCommPort = INVALID_HANDLE_VALUE;
}

CTLSShare::~CTLSShare()
{

}
DWORD CTLSShare::SetTLSSlotIndex(int nSlotIndex)
{
	DWORD dwErrorCode = SUCCESS;

	return dwErrorCode;
}



DWORD CTLSShare::LoadSocketDll()
{
	DWORD dwErrorCode = SUCCESS;
	try
	{
		//Load Socket communication interface
		HMODULE m_hInst = LoadLibrary("SockCommDll.dll");
		if (m_hInst == NULL)
		{
			throw ERROR_TLSHAREDLLLOAD;
		}
		getLastError = (GetLastErr)GetProcAddress(m_hInst, "GetError");
		if (getLastError == NULL)
		{
			throw ERROR_TLSHAREINTERFACE;
		}
		startSrv = (StartSrv)GetProcAddress(m_hInst, "StartService");
		if (startSrv == NULL)
		{
			throw ERROR_TLSHAREINTERFACE;
		}
		stopSrv = (StopSrv)GetProcAddress(m_hInst, "StopService");
		if (stopSrv == NULL)
		{
			throw ERROR_TLSHAREINTERFACE;
		}
		acqMsgCount = (AcqMsgCount)GetProcAddress(m_hInst, "AcquireMsgCount");
		if (acqMsgCount == NULL)
		{
			throw ERROR_TLSHAREINTERFACE;
		}
		acqClientCount = (AcqClientCount)GetProcAddress(m_hInst, "AcquireClientCount");
		if (acqClientCount == NULL)
		{
			throw ERROR_TLSHAREINTERFACE;
		}
		recvMsg = (RecvMsg)GetProcAddress(m_hInst, "ReceiveMsg");
		if (recvMsg == NULL)
		{
			throw ERROR_TLSHAREINTERFACE;
		}
		sendMsg = (SendMsg)GetProcAddress(m_hInst, "PostMsg");
		if (sendMsg == NULL)
		{
			throw ERROR_TLSHAREINTERFACE;
		}
	}
	catch (DWORD e)
	{
		dwErrorCode = UNEXPECT_OCCUR | e;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR | ERROR_TLSHAREDLLLOAD;
	}
	return dwErrorCode;
}

////////////////////////////////////////////////////////
//函数说明：
//   获得当前时间字符串
//Add by wanxin
//Time:20190702
////////////////////////////////////////////////////////////
void CTLSShare::GetCurTimeString(char* szpTimeBuffer)
{
	SYSTEMTIME f_t_time;
	GetLocalTime(&f_t_time);
	ASSERT(szpTimeBuffer);
	sprintf(szpTimeBuffer, "%04d%02d%02d%02d%02d%02d",
		f_t_time.wYear,
		f_t_time.wMonth,
		f_t_time.wDay,
		f_t_time.wHour,
		f_t_time.wMinute,
		f_t_time.wSecond);
}
///////////////////////////////////////////////////////////////
//函数说明：
//   获得主机当前IP地址
//Add by wanxin
//Time:20190702
//////////////////////////////////////////////////////////////
void CTLSShare::GetCurIPAddress(char *pstrIP)
{
	char buf[128] = { 0 };
	char *local_ip = NULL;
	if (gethostname(buf, sizeof(buf)) == 0)
	{
		struct hostent *temp_he;
		temp_he = gethostbyname(buf);
		if (temp_he)
		{
			for (int i = 0; temp_he->h_addr_list[i]; i++)
			{
				local_ip = NULL;
				local_ip = inet_ntoa(*(struct in_addr *)(temp_he->h_addr_list[i]));
				if (local_ip)
				{
					strcpy(pstrIP, local_ip);
					if (strcmp("127.0.0.1", pstrIP) < 0)
					{
						break;
					}
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////
//函数说明：
//   通过成员变量填充发送消息结构体头部信息
//Add by wanxin
//Time:20190702
////////////////////////////////////////////////////////////////
void CTLSShare::GetMSGHeader(CommMsgPackage *pSendMsg)
{
	ASSERT(pSendMsg);

	sprintf_s(pSendMsg->strPlatForm, "TLSSHARE");
	sprintf_s(pSendMsg->strMsgType, "REG");

	strcpy(pSendMsg->strIPAddress, m_stTLShare.szSrvIP);
	strcpy(pSendMsg->strPort, m_stTLShare.szPort);
	strcpy(pSendMsg->strSlot, m_stTLShare.szSlot);
	strcpy(pSendMsg->strClientID, m_stTLShare.szClientID);
	strcpy(pSendMsg->strUserID, m_stTLShare.szUserID);
	char szTime[256];
	GetCurTimeString(szTime);
	strcpy(pSendMsg->strTime, szTime);
	//char szIP[256];
	//ZeroMemory(szIP, 256);
	//GetCurIPAddress(szIP);
	//strcpy(pSendMsg->strIPAddress, szIP);
}

/////////////////////////////////////////////////////////////
//函数说明：
//   与服务器建立连接
//pszDeviceAddr地址信息顺序时“IP,Port,slot,userid,clientid”
//Add by wanxin
//Time:20190702
////////////////////////////////////////////////////////////
DWORD CTLSShare::OpenDevice(LPCTSTR pszDeviceAddr, unsigned long *ComHandle)
{
	DWORD dwErrorCode = SUCCESS;
	char* token = NULL;
	char szSpec[] = ",";
	stSockInfo  stInfo;
	stInfo.nType = 0;
	CommMsgPackage *firstMsg = NULL;

	try
	{
		firstMsg = new CommMsgPackage();

		dwErrorCode = LoadSocketDll();
		if (dwErrorCode != SUCCESS)
		{
			throw dwErrorCode;
		}

		token = strtok((char*)pszDeviceAddr, szSpec);
		ASSERT(token);
		ZeroMemory(stInfo.pszSrvIP, LENGTH_128B);
		strcpy(stInfo.pszSrvIP, token);
		ZeroMemory(m_stTLShare.szSrvIP, LENGTH_256B);
		strcpy(m_stTLShare.szSrvIP, stInfo.pszSrvIP);

		token = strtok(NULL, szSpec);
		ASSERT(token);
		stInfo.us_Port = atoi(token);
		ZeroMemory(m_stTLShare.szPort, LENGTH_256B);
		strcpy(m_stTLShare.szPort, token);

		token = strtok(NULL, szSpec);
		ASSERT(token);
		ZeroMemory(firstMsg->strSlot, LENGTH_256B);
		strcpy(firstMsg->strSlot, token);
		ZeroMemory(m_stTLShare.szSlot, LENGTH_256B);
		strcpy(m_stTLShare.szSlot, token);

		token = strtok(NULL, szSpec);
		ASSERT(token);
		ZeroMemory(firstMsg->strUserID, LENGTH_256B);
		strcpy(firstMsg->strUserID, token);
		ZeroMemory(m_stTLShare.szUserID, LENGTH_256B);
		strcpy(m_stTLShare.szUserID, token);

		token = strtok(NULL, szSpec);
		ASSERT(token);
		ZeroMemory(firstMsg->strClientID, LENGTH_256B);
		strcpy(firstMsg->strClientID, token);
		ZeroMemory(m_stTLShare.szClientID, LENGTH_256B);
		strcpy(m_stTLShare.szClientID, token);

		if (!startSrv(stInfo))
		{
			throw ERROR_TLSSHARESTARTSRV;
		}

		//Register Client
		sprintf_s(firstMsg->strPlatForm, "TLSHARE");
		firstMsg->MsgList = new MsgData[1];
		firstMsg->nMsgCount = 1;
		sprintf_s(firstMsg->strMsgType, "REG");

		strcpy(firstMsg->strIPAddress, stInfo.pszSrvIP);
		sprintf(firstMsg->strPort, "%d", stInfo.us_Port);

		//生成日期信息
		char f_trace_data[256] = "";
		GetCurTimeString(f_trace_data);
		strcpy(firstMsg->strTime, f_trace_data);

		firstMsg->MsgList->strKey = new char[1];
		strcpy(firstMsg->MsgList->strKey, "");
		firstMsg->MsgList->strValue = new char[1];
		strcpy(firstMsg->MsgList->strValue, "");

		if (!sendMsg(firstMsg))
		{
			throw ERROR_TLSSHAREREG;
		}
		int nCount = 0;
		while (1)
		{
			if (nCount > 200)
			{
				throw ERROR_TLSSHAREREG;
			}
			CommMsgPackage *getMsg = NULL;
			if (!recvMsg(&getMsg))
			{
				Sleep(300);
				nCount++;
				continue;
			}
			if (getMsg != NULL)
			{
				if (strcmp(getMsg->strTime, firstMsg->strTime) == 0)
				{
                    if (strcmp(getMsg->MsgList->strValue, "Reg Successful") == 0)
					{
						break;
					}
					else
					{
						throw ERROR_TLSSHAREREG;
					}
				}
				else
				{
					Sleep(300);
					nCount++;
					continue;
				}
			}
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR | ERROR_OPEN;
	}

	delete[] firstMsg->MsgList->strValue;
	delete[] firstMsg->MsgList->strKey;
	delete firstMsg->MsgList;
	delete firstMsg;

	return dwErrorCode;
}

DWORD CTLSShare::CloseDevice()
{
	DWORD dwErrorCode = SUCCESS;
	CommMsgPackage *firstMsg = NULL;
	try
	{
		firstMsg = new CommMsgPackage();

		GetMSGHeader(firstMsg);

		strcpy(firstMsg->strMsgType, "SET");
		firstMsg->nMsgCount = 1;
		firstMsg->MsgList = new MsgData;

		firstMsg->MsgList->strKey = new char[256];
		ZeroMemory(firstMsg->MsgList->strKey, 256);
		firstMsg->MsgList->strValue = new char[256];
		ZeroMemory(firstMsg->MsgList->strValue, 256);
		sprintf(firstMsg->MsgList->strKey, "CLOSE");

		sprintf(firstMsg->MsgList->strValue, "NULL");

		BOOL  bRetrun =FALSE;
		while (1)
		{
			if(bRetrun)
			{
				break;
			}
			if (!sendMsg(firstMsg))
			{
				throw ERROR_TLSSHARESETCLOSE;
			}

			int nCount = 0;
			while (1)
			{
				if (nCount > 200)
				{
					throw ERROR_TLSSHARESETCLOSE;
				}
				bRetrun = FALSE;
				CommMsgPackage *getMsg = NULL;
				if (!recvMsg(&getMsg))
				{
					Sleep(300);
					nCount++;
					continue;
				}
				if (getMsg != NULL)
				{
					if (strcmp(getMsg->strTime, firstMsg->strTime) == 0)
					{
						if (strcmp(getMsg->MsgList->strValue, "BUSY") == 0)
						{
							bRetrun = FALSE;
							break;
						}
						else if (strcmp(getMsg->MsgList->strValue, "OK") == 0)
						{
							bRetrun = TRUE;
							break;
						}
						else
						{
							throw ERROR_TLSSHARESETCLOSE;
						}
					}
					else
					{
						Sleep(300);
						nCount++;
						continue;
					}
				}
			}
			Sleep(2000);
		}

	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR | ERROR_TLSSHARESETENABLE;
	}

	return dwErrorCode;
}
////////////////////////////////////////////////////////////////////
//函数说明：
//    设置激光器波长
//Add by wanxin
//Time：20190702
//////////////////////////////////////////////////////////////////
DWORD CTLSShare::SetWavelength(long lChIndex, double dblWavelength)
{
	DWORD dwErrorCode = SUCCESS;
	CommMsgPackage *firstMsg = NULL;

	try
	{
		firstMsg = new CommMsgPackage();

		GetMSGHeader(firstMsg);

		strcpy(firstMsg->strMsgType, "SET");
		firstMsg->nMsgCount = 1;
		firstMsg->MsgList = new MsgData;

		firstMsg->MsgList->strKey = new char[256];
		ZeroMemory(firstMsg->MsgList->strKey, 256);
		firstMsg->MsgList->strValue = new char[256];
		ZeroMemory(firstMsg->MsgList->strValue, 256);
		sprintf(firstMsg->MsgList->strKey, "WL");

		sprintf(firstMsg->MsgList->strValue, "%.2f", dblWavelength);

		BOOL  bRetrun = FALSE;
		while (1)
		{
			if (bRetrun)
			{
				break;
			}
			if (!sendMsg(firstMsg))
			{
				throw ERROR_TLSSHARESETWL;
			}
			int nCount = 0;
			while (1)
			{
				if (nCount > 200)
				{
					throw ERROR_TLSSHARESETWL;
				}
				bRetrun = FALSE;
				CommMsgPackage *getMsg = NULL;
				if (!recvMsg(&getMsg))
				{
					Sleep(300);
					nCount++;
					continue;
				}
				if (getMsg != NULL)
				{
					if (strcmp(getMsg->strTime, firstMsg->strTime) == 0)
					{
						if (strcmp(getMsg->MsgList->strValue, "BUSY") == 0)
						{
							bRetrun = FALSE;
							break;
						}
						else if (strcmp(getMsg->MsgList->strValue, "OK") == 0)
						{
							bRetrun = TRUE;
							break;
						}
						else
						{
							throw ERROR_TLSSHARESETWL;
						}
					}
					else
					{
						Sleep(300);
						nCount++;
						continue;
					}
				}
			}
			Sleep(2000);
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR | ERROR_WL;
	}
	delete[] firstMsg->MsgList->strValue;
	delete[] firstMsg->MsgList->strKey;
	delete firstMsg->MsgList;
	delete firstMsg;

	return dwErrorCode;
}
///////////////////////////////////////////////////////////////////
//函数说明：
//    设置共享激光器功率
//Add by wanxin
//Time:20190702
///////////////////////////////////////////////////////////////////
DWORD CTLSShare::SetSourcePower(long lChIndex, double dblPower)
{
	DWORD dwErrorCode = SUCCESS;
	CommMsgPackage *firstMsg = NULL;
	try
	{
		firstMsg = new CommMsgPackage();

		GetMSGHeader(firstMsg);

		strcpy(firstMsg->strMsgType, "SET");
		firstMsg->nMsgCount = 1;
		firstMsg->MsgList = new MsgData;

		firstMsg->MsgList->strKey = new char[256];
		ZeroMemory(firstMsg->MsgList->strKey, 256);
		firstMsg->MsgList->strValue = new char[256];
		ZeroMemory(firstMsg->MsgList->strValue, 256);
		sprintf(firstMsg->MsgList->strKey, "POWER");

		sprintf(firstMsg->MsgList->strValue, "%.2f", dblPower);
		SYSTEMTIME f_t_time;
		GetLocalTime(&f_t_time);

		BOOL  bRetrun = FALSE;
		while (1)
		{
			if (bRetrun)
			{
				break;
			}
			if (!sendMsg(firstMsg))
			{
				throw ERROR_TLSSHARESETPOWER;
			}
			int nCount = 0;
			while (1)
			{
				if (nCount > 200)
				{
					throw ERROR_TLSSHARESETPOWER;
				}
				bRetrun = FALSE;
				CommMsgPackage *getMsg = NULL;
				if (!recvMsg(&getMsg))
				{
					Sleep(300);
					nCount++;
					continue;
				}
				if (getMsg != NULL)
				{
					if (strcmp(getMsg->strTime, firstMsg->strTime) == 0)
					{
						if (strcmp(getMsg->MsgList->strValue, "BUSY") == 0)
						{
							bRetrun = FALSE;
							break;
						}
						else if (strcmp(getMsg->MsgList->strValue, "OK") == 0)
						{
							bRetrun = TRUE;
							break;
						}
						else
						{
							throw ERROR_TLSSHARESETPOWER;
						}
					}
					else
					{
						Sleep(300);
						nCount++;
						continue;
					}
				}
			}
		}
		Sleep(2000);
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR | ERROR_TLSSHARESETPOWER;
	}

	delete[] firstMsg->MsgList->strValue;
	delete[] firstMsg->MsgList->strKey;
	delete firstMsg->MsgList;
	delete firstMsg;

	return dwErrorCode;
}
DWORD CTLSShare::SetMaxOutput(long lChIndex)
{
	DWORD dwErrorCode = SUCCESS;
	try
	{
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR | ERROR_WL;
	}

	return dwErrorCode;
}
DWORD CTLSShare::SetTLSFrequency(long lChIndex, double dblFrequrency)
{
	DWORD dwErrorCode = SUCCESS;


	try
	{

	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR | ERROR_WL;
	}

	return dwErrorCode;
}
DWORD CTLSShare::GetTLSSettings(long lChIndex, double* pdblWavelength, double* pdblPower, BYTE* pdCtrlState)
{

	DWORD dwErrorCode = SUCCESS;

	try
	{

	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR | ERROR_WL;
	}

	return dwErrorCode;

}

////////////////////////////////////////////////////////////////
//函数说明：
//   设置共享激光器参数
//Add by wanxin
//Time:20190702
///////////////////////////////////////////////////////////////
DWORD CTLSShare::SetParameters(long lChIndex, BOOL bLowSSE, double dblPower, double dblWavelength)
{
	DWORD dwErrorCode = SUCCESS;
	CommMsgPackage *firstMsg = NULL;
	try
	{
		firstMsg = new CommMsgPackage();

		GetMSGHeader(firstMsg);

		strcpy(firstMsg->strMsgType, "SET");
		firstMsg->nMsgCount = 1;
		firstMsg->MsgList = new MsgData;

		firstMsg->MsgList->strKey = new char[256];
		ZeroMemory(firstMsg->MsgList->strKey, 256);
		firstMsg->MsgList->strValue = new char[256];
		ZeroMemory(firstMsg->MsgList->strValue, 256);
		sprintf(firstMsg->MsgList->strKey, "PARAM");

		sprintf(firstMsg->MsgList->strValue, "%d,%.2f,%.2f", bLowSSE, dblPower, dblWavelength);
		SYSTEMTIME f_t_time;
		GetLocalTime(&f_t_time);

		BOOL  bRetrun = FALSE;
		while (1)
		{
			if (bRetrun)
			{
				break;
			}
			if (!sendMsg(firstMsg))
			{
				throw ERROR_TLSSHARESETPARAM;
			}

			int nCount = 0;
			while (1)
			{
				if (nCount > 200)
				{
					throw ERROR_TLSSHARESETPARAM;
				}
				bRetrun = FALSE;
				CommMsgPackage *getMsg = NULL;
				if (!recvMsg(&getMsg))
				{
					Sleep(300);
					nCount++;
					continue;
				}
				if (getMsg != NULL)
				{
					if (strcmp(getMsg->strTime, firstMsg->strTime) == 0)
					{
						if (strcmp(getMsg->MsgList->strValue, "BUSY") == 0)
						{
							bRetrun = FALSE;
							break;
						}
						else if (strcmp(getMsg->MsgList->strValue, "OK") == 0)
						{
							bRetrun = TRUE;
							break;
						}
						else
						{
							throw ERROR_TLSSHARESETPARAM;
						}
					}
					else
					{
						Sleep(300);
						nCount++;
						continue;
					}
				}
			}
			Sleep(2000);
		}

	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR | ERROR_TLSSHARESETPARAM;
	}

	delete[] firstMsg->MsgList->strValue;
	delete[] firstMsg->MsgList->strKey;
	delete firstMsg->MsgList;
	delete firstMsg;

	return dwErrorCode;
}

DWORD CTLSShare::SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle)
{
	DWORD dwErrorCode = SUCCESS;
	//dwErrorCode = m_Comm.SetDeviceHandle(pszDeviceAddr, handle);

	return dwErrorCode;
}

DWORD CTLSShare::SetCoherenceControl(BOOL bEnable)
{
	DWORD dwErrorCode = SUCCESS;
	CommMsgPackage *firstMsg = NULL;
	try
	{
		firstMsg = new CommMsgPackage();

		GetMSGHeader(firstMsg);

		strcpy(firstMsg->strMsgType, "SET");
		firstMsg->nMsgCount = 1;
		firstMsg->MsgList = new MsgData;

		firstMsg->MsgList->strKey = new char[256];
		ZeroMemory(firstMsg->MsgList->strKey, 256);
		firstMsg->MsgList->strValue = new char[256];
		ZeroMemory(firstMsg->MsgList->strValue, 256);
		sprintf(firstMsg->MsgList->strKey, "COHERENCE");

		sprintf(firstMsg->MsgList->strValue, "%d", bEnable);
		SYSTEMTIME f_t_time;
		GetLocalTime(&f_t_time);

		BOOL  bRetrun = FALSE;
		while (1)
		{
			if (bRetrun)
			{
				break;
			}
			if (!sendMsg(firstMsg))
			{
				throw EEROR_TLSSHARESETCOHERENCE;
			}

			int nCount = 0;
			while (1)
			{
				if (nCount > 200)
				{
					throw EEROR_TLSSHARESETCOHERENCE;
				}
				bRetrun = FALSE;
				CommMsgPackage *getMsg = NULL;
				if (!recvMsg(&getMsg))
				{
					Sleep(300);
					nCount++;
					continue;
				}
				if (getMsg != NULL)
				{
					if (strcmp(getMsg->strTime, firstMsg->strTime) == 0)
					{
						if (strcmp(getMsg->MsgList->strValue, "BUSY") == 0)
						{
							bRetrun = FALSE;
							break;
						}
						else if (strcmp(getMsg->MsgList->strValue, "OK") == 0)
						{
							bRetrun = TRUE;
							break;
						}
						else
						{
							throw EEROR_TLSSHARESETCOHERENCE;
						}
					}
					else
					{
						Sleep(300);
						nCount++;
						continue;
					}
				}
			}
			Sleep(2000);
		}
		
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR | EEROR_TLSSHARESETCOHERENCE;
	}

	delete[] firstMsg->MsgList->strValue;
	delete[] firstMsg->MsgList->strKey;
	delete firstMsg->MsgList;
	delete firstMsg;

	return dwErrorCode;
}

DWORD CTLSShare::SetSourceUnit(long lChIndex, long dblAtten)
{
	DWORD dwErrorCode = SUCCESS;
	CommMsgPackage *firstMsg = NULL;
	try
	{
		firstMsg = new CommMsgPackage();

		GetMSGHeader(firstMsg);

		strcpy(firstMsg->strMsgType, "SET");
		firstMsg->nMsgCount = 1;
		firstMsg->MsgList = new MsgData;

		firstMsg->MsgList->strKey = new char[256];
		ZeroMemory(firstMsg->MsgList->strKey, 256);
		firstMsg->MsgList->strValue = new char[256];
		ZeroMemory(firstMsg->MsgList->strValue, 256);
		sprintf(firstMsg->MsgList->strKey, "UNIT");

		sprintf(firstMsg->MsgList->strValue, "%d", dblAtten);

		BOOL  bRetrun = FALSE;
		while (1)
		{
			if (bRetrun)
			{
				break;
			}
			if (!sendMsg(firstMsg))
			{
				throw ERROR_TLSSHARESETUNIT;
			}
			int nCount = 0;
			while (1)
			{
				if (nCount > 200)
				{
					throw ERROR_TLSSHARESETUNIT;
				}
				bRetrun = FALSE;
				CommMsgPackage *getMsg = NULL;
				if (!recvMsg(&getMsg))
				{
					Sleep(300);
					nCount++;
					continue;
				}
				if (getMsg != NULL)
				{
					if (strcmp(getMsg->strTime, firstMsg->strTime) == 0)
					{
						if (strcmp(getMsg->MsgList->strValue, "BUSY") == 0)
						{
							bRetrun = FALSE;
							break;
						}
						else if (strcmp(getMsg->MsgList->strValue, "OK") == 0)
						{
							bRetrun = TRUE;
							break;
						}
						else
						{
							throw ERROR_TLSSHARESETUNIT;
						}
					}
					else
					{
						Sleep(300);
						nCount++;
						continue;
					}
				}
			}
			Sleep(2000);
		}
		
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR | ERROR_TLSSHARESETUNIT;
	}

	delete[] firstMsg->MsgList->strValue;
	delete[] firstMsg->MsgList->strKey;
	delete firstMsg->MsgList;
	delete firstMsg;

	return dwErrorCode;
}

DWORD CTLSShare::SetOutputEnable(BOOL bEnable)
{
	DWORD dwErrorCode = SUCCESS;
	CommMsgPackage *firstMsg = NULL;
	try
	{
		firstMsg = new CommMsgPackage();

		GetMSGHeader(firstMsg);

		strcpy(firstMsg->strMsgType, "SET");
		firstMsg->nMsgCount = 1;
		firstMsg->MsgList = new MsgData;

		firstMsg->MsgList->strKey = new char[256];
		ZeroMemory(firstMsg->MsgList->strKey, 256);
		firstMsg->MsgList->strValue = new char[256];
		ZeroMemory(firstMsg->MsgList->strValue, 256);
		sprintf(firstMsg->MsgList->strKey, "ENABLE");

		sprintf(firstMsg->MsgList->strValue, "%d", bEnable);
		SYSTEMTIME f_t_time;
		GetLocalTime(&f_t_time);

		BOOL  bRetrun = FALSE;
		while (1)
		{
			if (bRetrun)
			{
				break;
			}
			if (!sendMsg(firstMsg))
			{
				throw ERROR_TLSSHARESETENABLE;
			}
			int nCount = 0;
			while (1)
			{
				if (nCount > 200)
				{
					throw ERROR_TLSSHARESETENABLE;
				}
				bRetrun = FALSE;
				CommMsgPackage *getMsg = NULL;
				if (!recvMsg(&getMsg))
				{
					Sleep(300);
					nCount++;
					continue;
				}
				if (getMsg != NULL)
				{
					if (strcmp(getMsg->strTime, firstMsg->strTime) == 0)
					{
						if (strcmp(getMsg->MsgList->strValue, "BUSY") == 0)
						{
							bRetrun = FALSE;
							break;
						}
						else if (strcmp(getMsg->MsgList->strValue, "OK") == 0)
						{
							bRetrun = TRUE;
							break;
						}
						else
						{
							throw ERROR_TLSSHARESETENABLE;
						}
					}
					else
					{
						Sleep(300);
						nCount++;
						continue;
					}
				}
			}
			Sleep(2000);
		}

	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR | ERROR_TLSSHARESETENABLE;
	}


	delete[] firstMsg->MsgList->strValue;
	delete[] firstMsg->MsgList->strKey;
	delete firstMsg->MsgList;
	delete firstMsg;

	return dwErrorCode;
}



//////////////////////////////////////////////////////////////////
//函数说明：
//   初始化iTLA激光器扫描
//Add by wanxin
//Time：20140807
//////////////////////////////////////////////////////////////
DWORD CTLSShare::PrepareScan(long lChIndex, stScanParam* lScanParam)
{
	char chSendBuf[MAX_PATH];
	DWORD dwErrorCode = SUCCESS;
	try
	{

	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR | ERROR_OPEN;
	}

	return dwErrorCode;
}
//////////////////////////////////////////////////////////////////
//函数说明：
//    开始激光器扫描
//Add by wanxin
//Time：20140807
//////////////////////////////////////////////////////////////
DWORD CTLSShare::SetScanStart(long lChIndex)
{
	char chSendBuf[MAX_PATH];
	DWORD dwErrorCode = SUCCESS;
	CString strTemp;

	try
	{


	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR | ERROR_OPEN;
	}

	return dwErrorCode;
}
//////////////////////////////////////////////////////////////////
//函数说明：
//    开始激光器扫描
//Add by wanxin
//Time：20140807
//////////////////////////////////////////////////////////////
DWORD CTLSShare::SetScanStop(long lChIndex)
{
	DWORD dwErrorCode = SUCCESS;
	CString strTemp;

	try
	{

	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR | ERROR_OPEN;
	}

	return dwErrorCode;
}
//////////////////////////////////////////////////
//函数说明：
//     根据iTLA设置channel获得WL
//Add by wanxin
//Time：20140807
///////////////////////////////////////////////////
DWORD CTLSShare::GetLamdaScanWLResult(long lChIndex, double* pdbWLAarry)
{
	DWORD dwErrorCode = SUCCESS;
	try
	{

	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR | ERROR_OPEN;
	}

	return dwErrorCode;
}

DWORD CTLSShare::SetTLSLock(long lChIndex, int nTimeOut,double dbSetWL)
{
	DWORD dwErrorCode = SUCCESS;
	CommMsgPackage *firstMsg = NULL;
	try
	{
		firstMsg = new CommMsgPackage();

		GetMSGHeader(firstMsg);

		strcpy(firstMsg->strMsgType, "LOCK");
		firstMsg->nMsgCount = 1;
		firstMsg->MsgList = new MsgData;

		firstMsg->MsgList->strKey = new char[256];
		ZeroMemory(firstMsg->MsgList->strKey, 256);
		firstMsg->MsgList->strValue = new char[256];
		ZeroMemory(firstMsg->MsgList->strValue, 256);
		sprintf(firstMsg->MsgList->strKey, "LOCK");

		sprintf(firstMsg->MsgList->strValue, "%d,%lf", nTimeOut, dbSetWL);
		SYSTEMTIME f_t_time;
		GetLocalTime(&f_t_time);

		BOOL  bRetrun = FALSE;
		while (1)
		{
			if (bRetrun)
			{
				break;
			}
			if (!sendMsg(firstMsg))
			{
				throw ERROR_TLSSHARESETLOCK;
			}

			int nCount = 0;
			while (1)
			{
				if (nCount > 200)
				{
					throw ERROR_TLSSHARESETLOCK;
				}
				bRetrun = FALSE;
				CommMsgPackage *getMsg = NULL;
				if (!recvMsg(&getMsg))
				{
					Sleep(300);
					nCount++;
					continue;
				}
				if (getMsg != NULL)
				{
					if (strcmp(getMsg->strTime, firstMsg->strTime) == 0)
					{
						if (strcmp(getMsg->MsgList->strValue, "BUSY") == 0)
						{
							bRetrun = FALSE;
							break;
						}
						else if (strcmp(getMsg->MsgList->strValue, "OK") == 0)
						{
							bRetrun = TRUE;
							break;
						}
						else
						{
							throw ERROR_TLSSHARESETLOCK;
						}
					}
					else
					{
						Sleep(300);
						nCount++;
						continue;
					}
				}
			}

			Sleep(2000);
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR | ERROR_TLSSHARESETLOCK;
	}

	delete[] firstMsg->MsgList->strValue;
	delete[] firstMsg->MsgList->strKey;
	delete firstMsg->MsgList;
	delete firstMsg;

	return dwErrorCode;
}
DWORD CTLSShare::SetTLSUnlock(long lChIndex)
{
	DWORD dwErrorCode = SUCCESS;
	CommMsgPackage *firstMsg = NULL;
	try
	{
		firstMsg = new CommMsgPackage();

		GetMSGHeader(firstMsg);

		strcpy(firstMsg->strMsgType, "UNLOCK");
		firstMsg->nMsgCount = 1;
		firstMsg->MsgList = new MsgData;

		firstMsg->MsgList->strKey = new char[256];
		ZeroMemory(firstMsg->MsgList->strKey, 256);
		firstMsg->MsgList->strValue = new char[256];
		ZeroMemory(firstMsg->MsgList->strValue, 256);
		sprintf(firstMsg->MsgList->strKey, "UNLOCK");

		sprintf(firstMsg->MsgList->strValue, "NULL");
		SYSTEMTIME f_t_time;
		GetLocalTime(&f_t_time);

		BOOL  bRetrun = FALSE;
		while (1)
		{
			if (bRetrun)
			{
				break;
			}
			if (!sendMsg(firstMsg))
			{
				throw ERROR_TLSSHARESETUNLOCK;
			}

			int nCount = 0;
			while (1)
			{
				if (nCount > 200)
				{

					throw ERROR_TLSSHARESETUNLOCK;
				}
				bRetrun = FALSE;
				CommMsgPackage *getMsg = NULL;
				if (!recvMsg(&getMsg))
				{
					Sleep(300);
					nCount++;
					continue;
				}
				if (getMsg != NULL)
				{
					if (strcmp(getMsg->strTime, firstMsg->strTime) == 0)
					{
						if (strcmp(getMsg->MsgList->strValue, "BUSY") == 0)
						{
							bRetrun = FALSE;
							break;
						}
						else if (strcmp(getMsg->MsgList->strValue, "OK") == 0)
						{
							bRetrun = TRUE;
							break;
						}
						else
						{
							throw ERROR_TLSSHARESETUNLOCK;
						}
					}
					else
					{
						Sleep(300);
						nCount++;
						continue;
					}
				}
			}
			Sleep(2000);
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR | ERROR_TLSSHARESETUNLOCK;
	}

	delete[] firstMsg->MsgList->strValue;
	delete[] firstMsg->MsgList->strKey;
	delete firstMsg->MsgList;
	delete firstMsg;

	return dwErrorCode;;
}