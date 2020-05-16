// OSA_AQ6370B.cpp: implementation of the COSA_AQ6370B class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\\include\OSA.h"
#include "math.h"
#include <string>
#include "winsock.h"
using namespace std;


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
//#define new DEBUG_NEW

#endif

#define RXMINLENS 128
#define RXMAXLENS 1024
#define TXLENS 1024
#define MAXSWEEPDATA 

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COSA_SHARE::COSA_SHARE()
{
	m_dblStartWL = 1520.0;
	m_dblStopWL = 1570.0;
	m_dblRBW = 0.2;
	m_dwSweepPoint = SWEEPPOINT;
	m_lCommType = 0;
}

COSA_SHARE::~COSA_SHARE()
{

}


DWORD COSA_SHARE::LoadSocketDll()
{
	DWORD dwErrorCode = SUCCESS;
	try
	{
		//Load Socket communication interface
		HMODULE m_hInst = LoadLibrary("SockCommDll.dll");
		if (m_hInst == NULL)
		{
			throw ERROR_OSASHAREDLLLOAD;
		}
		getLastError = (GetLastErr)GetProcAddress(m_hInst, "GetError");
		if (getLastError == NULL)
		{
			throw ERROR_OSASHAREINTERFACE;
		}
		startSrv = (StartSrv)GetProcAddress(m_hInst, "StartService");
		if (startSrv == NULL)
		{
			throw ERROR_OSASHAREINTERFACE;
		}
		stopSrv = (StopSrv)GetProcAddress(m_hInst, "StopService");
		if (stopSrv == NULL)
		{
			throw ERROR_OSASHAREINTERFACE;
		}
		acqMsgCount = (AcqMsgCount)GetProcAddress(m_hInst, "AcquireMsgCount");
		if (acqMsgCount == NULL)
		{
			throw ERROR_OSASHAREINTERFACE;
		}
		acqClientCount = (AcqClientCount)GetProcAddress(m_hInst, "AcquireClientCount");
		if (acqClientCount == NULL)
		{
			throw ERROR_OSASHAREINTERFACE;
		}
		recvMsg = (RecvMsg)GetProcAddress(m_hInst, "ReceiveMsg");
		if (recvMsg == NULL)
		{
			throw ERROR_OSASHAREINTERFACE;
		}
		sendMsg = (SendMsg)GetProcAddress(m_hInst, "PostMsg");
		if (sendMsg == NULL)
		{
			throw ERROR_OSASHAREINTERFACE;
		}
	}
	catch (DWORD e)
	{
		dwErrorCode = UNEXPECT_OCCUR | e;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR | ERROR_OSASHAREDLLLOAD;
	}
	return dwErrorCode;


}

////////////////////////////////////////////////////////
//函数说明：
//   获得当前时间字符串
//Add by wanxin
//Time:20190702
////////////////////////////////////////////////////////////
void COSA_SHARE::GetCurTimeString(char* szpTimeBuffer)
{
	SYSTEMTIME f_t_time;
	GetLocalTime(&f_t_time);
	assert(szpTimeBuffer);
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
void COSA_SHARE::GetCurIPAddress(char *pstrIP)
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
void COSA_SHARE::GetMSGHeader(CommMsgPackage *pSendMsg)
{
	;(pSendMsg);

	sprintf_s(pSendMsg->strPlatForm, "OSASHARE");
	sprintf_s(pSendMsg->strMsgType, "REG");

	strcpy(pSendMsg->strIPAddress, m_stOSAShare.szSrvIP);
	strcpy(pSendMsg->strPort, m_stOSAShare.szPort);
	strcpy(pSendMsg->strSlot, m_stOSAShare.szSlot);
	strcpy(pSendMsg->strClientID, m_stOSAShare.szClientID);
	strcpy(pSendMsg->strUserID, m_stOSAShare.szUserID);
	char szTime[256];
	GetCurTimeString(szTime);
	strcpy(pSendMsg->strTime, szTime);
	//char szIP[256];
	//ZeroMemory(szIP, 256);
	//GetCurIPAddress(szIP);
	//strcpy(pSendMsg->strIPAddress, szIP);
}

////////////////////////////////////////////////////////////
//函数说明：
//   通过传入的结构体，与OSA共享服务器端建立连接
//Add by wanxin
//Time:2019/7/18
/////////////////////////////////////////////////////////////
DWORD COSA_SHARE::OpenDevice(stDevType stType, char* pszDeviceAddr, unsigned long *comHandle)
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
		assert(token);
		memset(stInfo.pszSrvIP, 0, LENGTH_128B);
		strcpy(stInfo.pszSrvIP, token);
		memset(m_stOSAShare.szSrvIP, 0, LENGTH_256B);
		strcpy(m_stOSAShare.szSrvIP, stInfo.pszSrvIP);

		token = strtok(NULL, szSpec);
		assert(token);
		stInfo.us_Port = atoi(token);
		memset(m_stOSAShare.szPort, 0, LENGTH_256B);
		strcpy(m_stOSAShare.szPort, token);

		token = strtok(NULL, szSpec);
		assert(token);
		memset(firstMsg->strSlot, 0, LENGTH_256B);
		strcpy(firstMsg->strSlot, token);
		memset(m_stOSAShare.szSlot, 0, LENGTH_256B);
		strcpy(m_stOSAShare.szSlot, token);

		token = strtok(NULL, szSpec);
		assert(token);
		memset(firstMsg->strUserID, 0, LENGTH_256B);
		strcpy(firstMsg->strUserID, token);
		memset(m_stOSAShare.szUserID, 0, LENGTH_256B);
		strcpy(m_stOSAShare.szUserID, token);

		token = strtok(NULL, szSpec);
		assert(token);
		memset(firstMsg->strClientID, 0, LENGTH_256B);
		strcpy(firstMsg->strClientID, token);
		memset(m_stOSAShare.szClientID, 0, LENGTH_256B);
		strcpy(m_stOSAShare.szClientID, token);

		if (!startSrv(stInfo))
		{
			throw ERROR_OSASHARESTARTSRV;
		}

		//Register Client
		sprintf_s(firstMsg->strPlatForm, "OSASHARE");
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
			throw ERROR_OSASHAREREG;
		}
		int nCount = 0;
		while (1)
		{
			if (nCount > 200)
			{
				throw ERROR_OSASHAREREG;
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
						throw ERROR_OSASHAREREG;
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


DWORD COSA_SHARE::CloseDevice()
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

		BOOL  bRetrun = FALSE;
		while (1)
		{
			if (bRetrun)
			{
				break;
			}
			if (!sendMsg(firstMsg))
			{
				throw ERROR_OSASHARESETCLOSE;
			}

			int nCount = 0;
			while (1)
			{
				if (nCount > 200)
				{
					throw ERROR_OSASHARESETCLOSE;
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
							throw ERROR_OSASHARESETCLOSE;
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
		dwErrorCode = UNEXPECT_OCCUR | ERROR_OSASHARESETCLOSE;
	}

	delete[] firstMsg->MsgList->strValue;
	delete[] firstMsg->MsgList->strKey;
	delete firstMsg->MsgList;
	delete firstMsg;

	return dwErrorCode;
}

///////////////////////////////////////////////////////////////////
//函数说明：
//   获得扫描光信号通道数
//Add by wanxin
//Time:2019/7/18
///////////////////////////////////////////////////////////////////
DWORD COSA_SHARE::GetChannelCount(DWORD* pdwChannelCount)
{
	DWORD dwErrorCode = SUCCESS;
	CommMsgPackage *firstMsg = NULL;
	char szTempBuffer[MAX_PATH];
	char *token = NULL;
	char szSpec[] = ",";


	try
	{
		firstMsg = new CommMsgPackage();
		GetMSGHeader(firstMsg);
		strcpy(firstMsg->strMsgType, "GET");
		firstMsg->nMsgCount = 1;
		firstMsg->MsgList = new MsgData;

		firstMsg->MsgList->strKey = new char[256];
		ZeroMemory(firstMsg->MsgList->strKey, 256);
		firstMsg->MsgList->strValue = new char[256];
		ZeroMemory(firstMsg->MsgList->strValue, 256);
		sprintf(firstMsg->MsgList->strKey, "CHCOUNT");


		BOOL  bRetrun = FALSE;
		while (1)
		{
			if (bRetrun)
			{
				break;
			}
			if (!sendMsg(firstMsg))
			{
				throw ERROR_OSASHAREGETCHCOUNT;
			}
			int nCount = 0;
			while (1)
			{
				if (nCount > 200)
				{
					throw ERROR_OSASHAREGETCHCOUNT;
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
						memset(szTempBuffer, 0, MAX_PATH);
						strcpy(szTempBuffer, getMsg->MsgList->strValue);
						token = strtok(szTempBuffer, szSpec);
						assert(token);
						if (strcmp(token, "BUSY") == 0)
						{
							bRetrun = FALSE;
							break;
						}
						else if (strcmp(token, "OK") == 0)
						{
							token = strtok(NULL, szSpec);//获得返回值
							assert(token);
							*pdwChannelCount = atoi(token);
							bRetrun = TRUE;
							break;
						}
						else
						{
							throw ERROR_OSASHAREGETCHCOUNT;
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
		dwErrorCode = UNEXPECT_OCCUR | ERROR_OSASHAREGETCHCOUNT;
	}


	delete[] firstMsg->MsgList->strValue;
	delete[] firstMsg->MsgList->strKey;
	delete firstMsg->MsgList;
	delete firstMsg;

	return dwErrorCode;
}
////////////////////////////////////////////////////////////////////////
//函数说明
//   从指定的文件夹路径下读取相应文件获得相应数据
//Add by wanxin
//Time:20197/18
////////////////////////////////////////////////////////////////////////
BOOL COSA_SHARE::ReadOSACHScanData(LPCSTR lpstrFileName, pOSAChData pData)
{
	HANDLE hFile = INVALID_HANDLE_VALUE;
	char szMsg[MAX_PATH];
	BYTE* bReadPtr = NULL;
	bReadPtr = (BYTE*)pData;

	hFile = (HANDLE)CreateFile(lpstrFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_BACKUP_SEMANTICS, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		ZeroMemory(szMsg, MAX_PATH);
		sprintf(szMsg, "Create File:%s error", lpstrFileName);
		return FALSE;
	}

	DWORD dwFileSize = GetFileSize(hFile, NULL);
	DWORD readsize = 0;

	if (!ReadFile(hFile, bReadPtr, dwFileSize, &readsize, NULL))
	{
		ZeroMemory(szMsg, MAX_PATH);
		sprintf(szMsg, "Read file raw data:%s error", lpstrFileName);
		return FALSE;
	}

	if (hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFile);
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////
//函数说明：
//   获得扫描信号通道波行数组
//Add by wanxin
//Time:2019/7/18
///////////////////////////////////////////////////////////////////////
DWORD COSA_SHARE::GetChannelWaveLens(double* pdblWavelens, DWORD* pdwChannelCount)
{
	DWORD dwErrorCode = SUCCESS;
	CommMsgPackage *firstMsg = NULL;
	char szTempBuffer[MAX_PATH];
	char *token = NULL;
	char szSpec[] = ",";
	char szFileName[MAX_PATH];

	try
	{
		firstMsg = new CommMsgPackage();
		GetMSGHeader(firstMsg);
		strcpy(firstMsg->strMsgType, "GET");
		firstMsg->nMsgCount = 1;
		firstMsg->MsgList = new MsgData;

		firstMsg->MsgList->strKey = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strKey, MAX_PATH);
		firstMsg->MsgList->strValue = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strValue, MAX_PATH);
		sprintf(firstMsg->MsgList->strKey, "CHWL");

		BOOL  bRetrun = FALSE;
		while (1)
		{
			if (bRetrun)
			{
				break;
			}
			if (!sendMsg(firstMsg))
			{
				throw ERROR_OSASHAREGETCHCOUNT;
			}
			int nCount = 0;
			while (1)
			{
				if (nCount > 200)
				{
					throw ERROR_OSASHAREGETCHCOUNT;
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
						memset(szTempBuffer, 0, MAX_PATH);
						strcpy(szTempBuffer, getMsg->MsgList->strValue);
						token = strtok(szTempBuffer, szSpec);
						assert(token);
						if (strcmp(token, "BUSY") == 0)
						{
							bRetrun = FALSE;
							break;
						}
						else if (strcmp(token, "OK") == 0)
						{
							token = strtok(NULL, szSpec);
							assert(token);
							strcpy(szFileName, token);//获得返回值
							bRetrun = TRUE;
							break;
						}
						else
						{
							throw ERROR_OSASHAREGETCHCOUNT;
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
		//从路径中读取数据信息，并赋值
		stOSAChData  stGetData;
		stGetData.pdbChData = pdblWavelens;
		if (!ReadOSACHScanData(szFileName, &stGetData))
		{
			throw ERROR_OSASHAREREADCHSCANDATA;
		}
		*pdwChannelCount = stGetData.nChCount;
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR | ERROR_OSASHAREGETCHCOUNT;
	}

	delete[] firstMsg->MsgList->strValue;
	delete[] firstMsg->MsgList->strKey;
	delete firstMsg->MsgList;
	delete firstMsg;

	return dwErrorCode;
}

///////////////////////////////////////////////////////////////////////
//函数说明：
//    获得OSA通道扫描NF数据
//Add by wanxin
//Time：2019/7/18
////////////////////////////////////////////////////////////////////
DWORD COSA_SHARE::GetChannelNF(double* pdblNF, DWORD* pdwChannelCount)
{
	DWORD dwErrorCode = SUCCESS;
	CommMsgPackage *firstMsg = NULL;
	char szTempBuffer[MAX_PATH];
	char *token = NULL;
	char szSpec[] = ",";
	char szFileName[MAX_PATH];

	try
	{
		firstMsg = new CommMsgPackage();
		GetMSGHeader(firstMsg);
		strcpy(firstMsg->strMsgType, "GET");
		firstMsg->nMsgCount = 1;
		firstMsg->MsgList = new MsgData;

		firstMsg->MsgList->strKey = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strKey, MAX_PATH);
		firstMsg->MsgList->strValue = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strValue, MAX_PATH);
		sprintf(firstMsg->MsgList->strKey, "CHNF");

		BOOL  bRetrun = FALSE;
		while (1)
		{
			if (bRetrun)
			{
				break;
			}
			if (!sendMsg(firstMsg))
			{
				throw ERROR_OSASHAREGETCHNF;
			}
			int nCount = 0;
			while (1)
			{
				if (nCount > 200)
				{
					throw ERROR_OSASHAREGETCHNF;
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
						memset(szTempBuffer, 0, MAX_PATH);
						strcpy(szTempBuffer, getMsg->MsgList->strValue);
						token = strtok(szTempBuffer, szSpec);
						assert(token);
						if (strcmp(token, "BUSY") == 0)
						{
							bRetrun = FALSE;
							break;
						}
						else if (strcmp(token, "OK") == 0)
						{
							token = strtok(NULL, szSpec);
							assert(token);
							strcpy(szFileName, token);//获得返回值
							bRetrun = TRUE;
							break;
						}
						else
						{
							throw ERROR_OSASHAREGETCHNF;
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
		//从路径中读取数据信息，并赋值
		stOSAChData  stGetData;
		stGetData.pdbChData = pdblNF;
		if (!ReadOSACHScanData(szFileName, &stGetData))
		{
			throw ERROR_OSASHAREREADCHSCANDATA;
		}
		*pdwChannelCount = stGetData.nChCount;
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR | ERROR_OSASHAREGETCHNF;
	}

	delete[] firstMsg->MsgList->strValue;
	delete[] firstMsg->MsgList->strKey;
	delete firstMsg->MsgList;
	delete firstMsg;

	return dwErrorCode;
}

////////////////////////////////////////////////////////////////////////
//函数说明：
//    获得OSA扫描通道的Gain数据
//Add by wanxin
//Time:2019/7/18
/////////////////////////////////////////////////////////////////////////
DWORD COSA_SHARE::GetChannelGain(double* pdblGain, DWORD* pdwChannelCount)
{
	DWORD dwErrorCode = SUCCESS;
	CommMsgPackage *firstMsg = NULL;
	char szTempBuffer[MAX_PATH];
	char *token = NULL;
	char szSpec[] = ",";
	char szFileName[MAX_PATH];

	try
	{
		firstMsg = new CommMsgPackage();
		GetMSGHeader(firstMsg);
		strcpy(firstMsg->strMsgType, "GET");
		firstMsg->nMsgCount = 1;
		firstMsg->MsgList = new MsgData;

		firstMsg->MsgList->strKey = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strKey, MAX_PATH);
		firstMsg->MsgList->strValue = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strValue, MAX_PATH);
		sprintf(firstMsg->MsgList->strKey, "CHGAIN");

		BOOL  bRetrun = FALSE;
		while (1)
		{
			if (bRetrun)
			{
				break;
			}
			if (!sendMsg(firstMsg))
			{
				throw ERROR_OSASHAREGETGAIN;
			}
			int nCount = 0;
			while (1)
			{
				if (nCount > 200)
				{
					throw ERROR_OSASHAREGETGAIN;
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
						memset(szTempBuffer, 0, MAX_PATH);
						strcpy(szTempBuffer, getMsg->MsgList->strValue);
						token = strtok(szTempBuffer, szSpec);
						assert(token);
						if (strcmp(token, "BUSY") == 0)
						{
							bRetrun = FALSE;
							break;
						}
						else if (strcmp(token, "OK") == 0)
						{
							token = strtok(NULL, szSpec);
							assert(token);
							strcpy(szFileName, token);//获得返回值
							bRetrun = TRUE;
							break;
						}
						else
						{
							throw ERROR_OSASHAREGETGAIN;
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
		//从路径中读取数据信息，并赋值
		stOSAChData  stGetData;
		stGetData.pdbChData = pdblGain;
		if (!ReadOSACHScanData(szFileName, &stGetData))
		{
			throw ERROR_OSASHAREREADCHSCANDATA;
		}
		*pdwChannelCount = stGetData.nChCount;
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR | ERROR_OSASHAREGETGAIN;
	}

	delete[] firstMsg->MsgList->strValue;
	delete[] firstMsg->MsgList->strKey;
	delete firstMsg->MsgList;
	delete firstMsg;

	return dwErrorCode;
}

////////////////////////////////////////////////////////////////////////////
//函数说明：
//    获得OSA通道扫描的SNR数据
//Add by wanxin
//Time:2019/7/18
///////////////////////////////////////////////////////////////////////////
DWORD COSA_SHARE::GetChannelSNR(double* pdblSNR, DWORD* pdwChannelCount)
{
	DWORD dwErrorCode = SUCCESS;
	CommMsgPackage *firstMsg = NULL;
	char szTempBuffer[MAX_PATH];
	char *token = NULL;
	char szSpec[] = ",";
	char szFileName[MAX_PATH];

	try
	{
		firstMsg = new CommMsgPackage();
		GetMSGHeader(firstMsg);
		strcpy(firstMsg->strMsgType, "GET");
		firstMsg->nMsgCount = 1;
		firstMsg->MsgList = new MsgData;

		firstMsg->MsgList->strKey = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strKey, MAX_PATH);
		firstMsg->MsgList->strValue = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strValue, MAX_PATH);
		sprintf(firstMsg->MsgList->strKey, "CHGAIN");

		BOOL  bRetrun = FALSE;
		while (1)
		{
			if (bRetrun)
			{
				break;
			}
			if (!sendMsg(firstMsg))
			{
				throw ERROR_OSASHAREGETGAIN;
			}
			int nCount = 0;
			while (1)
			{
				if (nCount > 200)
				{
					throw ERROR_OSASHAREGETGAIN;
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
						memset(szTempBuffer, 0, MAX_PATH);
						strcpy(szTempBuffer, getMsg->MsgList->strValue);
						token = strtok(szTempBuffer, szSpec);
						assert(token);
						if (strcmp(token, "BUSY") == 0)
						{
							bRetrun = FALSE;
							break;
						}
						else if (strcmp(token, "OK") == 0)
						{
							token = strtok(NULL, szSpec);
							assert(token);
							strcpy(szFileName, token);//获得返回值
							bRetrun = TRUE;
							break;
						}
						else
						{
							throw ERROR_OSASHAREGETGAIN;
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
		//从路径中读取数据信息，并赋值
		stOSAChData  stGetData;
		stGetData.pdbChData = pdblSNR;
		if (!ReadOSACHScanData(szFileName, &stGetData))
		{
			throw ERROR_OSASHAREREADCHSCANDATA;
		}
		*pdwChannelCount = stGetData.nChCount;
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR | ERROR_OSASHAREGETGAIN;
	}

	delete[] firstMsg->MsgList->strValue;
	delete[] firstMsg->MsgList->strKey;
	delete firstMsg->MsgList;
	delete firstMsg;

	return dwErrorCode;
}

////////////////////////////////////////////////////////////////////
//函数说明：
//    获得OSA扫描通道源功率
//Add by wanxin
//Time:2019/7/19
//////////////////////////////////////////////////////////////////////
DWORD COSA_SHARE::GetChannelSourcePower(double* pdblSourcePow, DWORD* pdwChannelCount)
{
	DWORD dwErrorCode = SUCCESS;
	CommMsgPackage *firstMsg = NULL;
	char szTempBuffer[MAX_PATH];
	char *token = NULL;
	char szSpec[] = ",";
	char szFileName[MAX_PATH];

	try
	{
		firstMsg = new CommMsgPackage();
		GetMSGHeader(firstMsg);
		strcpy(firstMsg->strMsgType, "GET");
		firstMsg->nMsgCount = 1;
		firstMsg->MsgList = new MsgData;

		firstMsg->MsgList->strKey = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strKey, MAX_PATH);
		firstMsg->MsgList->strValue = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strValue, MAX_PATH);
		sprintf(firstMsg->MsgList->strKey, "CHPOWER");

		BOOL  bRetrun = FALSE;
		while (1)
		{
			if (bRetrun)
			{
				break;
			}
			if (!sendMsg(firstMsg))
			{
				throw ERROR_OSASHAREGETPOWER;
			}
			int nCount = 0;
			while (1)
			{
				if (nCount > 200)
				{
					throw ERROR_OSASHAREGETPOWER;
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
						memset(szTempBuffer, 0, MAX_PATH);
						strcpy(szTempBuffer, getMsg->MsgList->strValue);
						token = strtok(szTempBuffer, szSpec);
						assert(token);
						if (strcmp(token, "BUSY") == 0)
						{
							bRetrun = FALSE;
							break;
						}
						else if (strcmp(token, "OK") == 0)
						{
							token = strtok(NULL, szSpec);
							assert(token);
							strcpy(szFileName, token);//获得返回值
							bRetrun = TRUE;
							break;
						}
						else
						{
							throw ERROR_OSASHAREGETPOWER;
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
		//从路径中读取数据信息，并赋值
		stOSAChData  stGetData;
		stGetData.pdbChData = pdblSourcePow;
		if (!ReadOSACHScanData(szFileName, &stGetData))
		{
			throw ERROR_OSASHAREREADCHSCANDATA;
		}
		*pdwChannelCount = stGetData.nChCount;
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR | ERROR_OSASHAREGETPOWER;
	}

	delete[] firstMsg->MsgList->strValue;
	delete[] firstMsg->MsgList->strKey;
	delete firstMsg->MsgList;
	delete firstMsg;

	return dwErrorCode;
}

//////////////////////////////////////////////////////////////
//函数说明：
//   初始化扫描
//Add by wanxin
//Time:2019/7/19
//////////////////////////////////////////////////////////
DWORD COSA_SHARE::InitSingleSweep(double dblStartWL, double dblStopWL, double dblRBW, DWORD dwSweepPoint)
{
	DWORD dwErrorCode = SUCCESS;
	CommMsgPackage *firstMsg = NULL;
	char szTempBuffer[MAX_PATH];
	char *token = NULL;
	char szSpec[] = ",";
	char szFileName[MAX_PATH];

	try
	{
		firstMsg = new CommMsgPackage();
		GetMSGHeader(firstMsg);
		strcpy(firstMsg->strMsgType, "SET");
		firstMsg->nMsgCount = 1;
		firstMsg->MsgList = new MsgData;

		firstMsg->MsgList->strKey = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strKey, MAX_PATH);
		firstMsg->MsgList->strValue = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strValue, MAX_PATH);
		sprintf(firstMsg->MsgList->strKey, "INITSW");

		sprintf(firstMsg->MsgList->strValue, "%.3f,%.3f,%.4f,%d", dblStartWL, dblStopWL, dblRBW, dwSweepPoint);

		BOOL  bRetrun = FALSE;
		while (1)
		{
			if (bRetrun)
			{
				break;
			}
			if (!sendMsg(firstMsg))
			{
				throw ERROR_OSASHARESETINISW;
			}
			int nCount = 0;
			while (1)
			{
				if (nCount > 200)
				{
					throw ERROR_OSASHARESETINISW;
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
							throw ERROR_OSASHARESETINISW;
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
		dwErrorCode = UNEXPECT_OCCUR | ERROR_OSASHARESETINISW;
	}

	return dwErrorCode;
}


DWORD COSA_SHARE::InitOSARepeatSweep(double dblStartWL, double dblStopWL, double dblRBW, DWORD dwSweepPoint)
{

	DWORD dwErrorCode = SUCCESS;
	CommMsgPackage *firstMsg = NULL;
	char szTempBuffer[MAX_PATH];
	char *token = NULL;
	char szSpec[] = ",";
	char szFileName[MAX_PATH];

	try
	{
		firstMsg = new CommMsgPackage();
		GetMSGHeader(firstMsg);
		strcpy(firstMsg->strMsgType, "SET");
		firstMsg->nMsgCount = 1;
		firstMsg->MsgList = new MsgData;

		firstMsg->MsgList->strKey = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strKey, MAX_PATH);
		firstMsg->MsgList->strValue = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strValue, MAX_PATH);
		sprintf(firstMsg->MsgList->strKey, "INITSWREPEAT");

		sprintf(firstMsg->MsgList->strValue, "%.3f,%.3f,%.4f,%d", dblStartWL, dblStopWL, dblRBW, dwSweepPoint);

		BOOL  bRetrun = FALSE;
		while (1)
		{
			if (bRetrun)
			{
				break;
			}
			if (!sendMsg(firstMsg))
			{
				throw ERROR_OSASHARESETINISW;
			}
			int nCount = 0;
			while (1)
			{
				if (nCount > 200)
				{
					throw ERROR_OSASHARESETINISW;
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
							throw ERROR_OSASHARESETINISW;
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
		dwErrorCode = UNEXPECT_OCCUR | ERROR_OSASHARESETINISW;
	}

	return dwErrorCode;
}


//////////////////////////////////////////////////////////////
//函数说明：
//   复位OSA
//Add by wanxin
//Time:2019/7/22
//////////////////////////////////////////////////////////////
DWORD COSA_SHARE::ResetDevice()
{
	DWORD dwErrorCode = SUCCESS;
	CommMsgPackage *firstMsg = NULL;
	char szTempBuffer[MAX_PATH];
	char *token = NULL;
	char szSpec[] = ",";
	char szFileName[MAX_PATH];

	try
	{
		firstMsg = new CommMsgPackage();
		GetMSGHeader(firstMsg);
		strcpy(firstMsg->strMsgType, "SET");
		firstMsg->nMsgCount = 1;
		firstMsg->MsgList = new MsgData;

		firstMsg->MsgList->strKey = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strKey, MAX_PATH);
		firstMsg->MsgList->strValue = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strValue, MAX_PATH);
		sprintf(firstMsg->MsgList->strKey, "RESET");

		sprintf(firstMsg->MsgList->strValue, "%d", 1);

		BOOL  bRetrun = FALSE;
		while (1)
		{
			if (bRetrun)
			{
				break;
			}
			if (!sendMsg(firstMsg))
			{
				throw ERROR_OSASHARERESETDEVICE;
			}
			int nCount = 0;
			while (1)
			{
				if (nCount > 200)
				{
					throw ERROR_OSASHARERESETDEVICE;
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
							throw ERROR_OSASHARERESETDEVICE;
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
		dwErrorCode = UNEXPECT_OCCUR | ERROR_OSASHARERESETDEVICE;
	}

	return dwErrorCode;
}
/////////////////////////////////////////////////////////////////////////////
//函数说明：
//   获取Amp total power的 offset
//Add by wanxin
//Time:2019/7/22
///////////////////////////////////////////////////////////////////////////////
DWORD COSA_SHARE::GetAmpOffset(double &dblSourceOffset, double &dblAmpOffset)
{
	DWORD dwErrorCode = SUCCESS;
	CommMsgPackage *firstMsg = NULL;
	char szTempBuffer[MAX_PATH];
	char *token = NULL;
	char szSpec[] = ",";
	char szFileName[MAX_PATH];

	try
	{
		firstMsg = new CommMsgPackage();
		GetMSGHeader(firstMsg);
		strcpy(firstMsg->strMsgType, "GET");
		firstMsg->nMsgCount = 1;
		firstMsg->MsgList = new MsgData;

		firstMsg->MsgList->strKey = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strKey, MAX_PATH);
		firstMsg->MsgList->strValue = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strValue, MAX_PATH);
		sprintf(firstMsg->MsgList->strKey, "AMPOFFSET");

		BOOL  bRetrun = FALSE;
		while (1)
		{
			if (bRetrun)
			{
				break;
			}
			if (!sendMsg(firstMsg))
			{
				throw ERROR_OSASHAREGETAMPOFFSET;
			}
			int nCount = 0;
			while (1)
			{
				if (nCount > 200)
				{
					throw ERROR_OSASHAREGETAMPOFFSET;
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
						memset(szTempBuffer, 0, MAX_PATH);
						strcpy(szTempBuffer, getMsg->MsgList->strValue);
						token = strtok(szTempBuffer, szSpec);
						assert(token);
						if (strcmp(token, "BUSY") == 0)
						{
							bRetrun = FALSE;
							break;
						}
						else if (strcmp(token, "OK") == 0)
						{
							token = strtok(NULL, szSpec);
							assert(token);
							dblSourceOffset = atof(token);
							token = strtok(NULL, szSpec);
							assert(token);
							dblAmpOffset = atof(token);
							bRetrun = TRUE;
							break;
						}
						else
						{
							throw ERROR_OSASHAREGETAMPOFFSET;
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
		dwErrorCode = UNEXPECT_OCCUR | ERROR_OSASHAREGETPOWER;
	}

	delete[] firstMsg->MsgList->strValue;
	delete[] firstMsg->MsgList->strKey;
	delete firstMsg->MsgList;
	delete firstMsg;

	return dwErrorCode;
}

////////////////////////////////////////////////////////////////////////////
//函数说明：
//   设置OSA Total Power源和放大Offset
//Add by wanxin
//Time:2019/7/22
///////////////////////////////////////////////////////////////////////////
DWORD COSA_SHARE::SetAmpOffset(double dblSourceOffset, double dblAmpOffset)
{
	DWORD dwErrorCode = SUCCESS;
	CommMsgPackage *firstMsg = NULL;
	char szTempBuffer[MAX_PATH];

	try
	{
		m_stScanSetting.m_dblSrcOffset = dblSourceOffset;
		m_stScanSetting.m_dblAmpOffset = dblAmpOffset;
		firstMsg = new CommMsgPackage();
		GetMSGHeader(firstMsg);
		strcpy(firstMsg->strMsgType, "SET");
		firstMsg->nMsgCount = 1;
		firstMsg->MsgList = new MsgData;

		firstMsg->MsgList->strKey = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strKey, MAX_PATH);
		firstMsg->MsgList->strValue = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strValue, MAX_PATH);
		sprintf(firstMsg->MsgList->strKey, "AMPOFFSET");

		sprintf(firstMsg->MsgList->strValue, "%.4f,%.4f", dblSourceOffset, dblAmpOffset);

		BOOL  bRetrun = FALSE;
		while (1)
		{
			if (bRetrun)
			{
				break;
			}
			if (!sendMsg(firstMsg))
			{
				throw ERROR_OSASHARESETAMPOFFSET;
			}
			int nCount = 0;
			while (1)
			{
				if (nCount > 200)
				{
					throw ERROR_OSASHARESETAMPOFFSET;
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
							throw ERROR_OSASHARESETAMPOFFSET;
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
		dwErrorCode = UNEXPECT_OCCUR | ERROR_OSASHARESETAMPOFFSET;
	}

	return dwErrorCode;
}
///////////////////////////////////////////////////////////////////////////
//函数说明：
//   设置OSA Locak控制
//Add by wanxin
//Time:2019/7/22
////////////////////////////////////////////////////////////////////////////
DWORD COSA_SHARE::SetOSALocalCtrl()
{
	DWORD dwErrorCode = SUCCESS;
	CommMsgPackage *firstMsg = NULL;
	char szTempBuffer[MAX_PATH];

	try
	{
		firstMsg = new CommMsgPackage();
		GetMSGHeader(firstMsg);
		strcpy(firstMsg->strMsgType, "SET");
		firstMsg->nMsgCount = 1;
		firstMsg->MsgList = new MsgData;

		firstMsg->MsgList->strKey = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strKey, MAX_PATH);
		firstMsg->MsgList->strValue = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strValue, MAX_PATH);
		sprintf(firstMsg->MsgList->strKey, "LOCALCTRL");

		sprintf(firstMsg->MsgList->strValue, "%d", 1);

		BOOL  bRetrun = FALSE;
		while (1)
		{
			if (bRetrun)
			{
				break;
			}
			if (!sendMsg(firstMsg))
			{
				throw ERROR_OSASHARESETLOCALCTRL;
			}
			int nCount = 0;
			while (1)
			{
				if (nCount > 200)
				{
					throw ERROR_OSASHARESETLOCALCTRL;
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
							throw ERROR_OSASHARESETLOCALCTRL;
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
		dwErrorCode = UNEXPECT_OCCUR | ERROR_OSASHARESETLOCALCTRL;
	}

	return dwErrorCode;
}

////////////////////////////////////////////////////////////////////////
//函数说明
//   从指定的文件夹路径下读取相应文件获得相应数据
//Add by wanxin
//Time:20197/18
////////////////////////////////////////////////////////////////////////
BOOL COSA_SHARE::ReadOSAScanData(LPCSTR lpstrFileName, pOSAScanData pData)
{
	HANDLE hFile = INVALID_HANDLE_VALUE;
	char szMsg[MAX_PATH];
	BYTE* bReadPtr = NULL;
	bReadPtr = (BYTE*)pData;

	hFile = (HANDLE)CreateFile(lpstrFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_BACKUP_SEMANTICS, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		ZeroMemory(szMsg, MAX_PATH);
		sprintf(szMsg, "Create File:%s error", lpstrFileName);
		return FALSE;
	}

	DWORD dwFileSize = GetFileSize(hFile, NULL);
	DWORD readsize = 0;

	if (!ReadFile(hFile, bReadPtr, dwFileSize, &readsize, NULL))
	{
		ZeroMemory(szMsg, MAX_PATH);
		sprintf(szMsg, "Read file raw data:%s error", lpstrFileName);
		return FALSE;
	}

	if (hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFile);
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////
//函数说明：
//   运行OSA扫描函数，返回扫描点数
//Add by wanxin
//Time:2019/7/22
////////////////////////////////////////////////////////////////////////////////
DWORD COSA_SHARE::RunSweep(double* pdblSweepDataX, double* pdblSweepDataY, char szSelTrace)
{
	DWORD dwErrorCode = SUCCESS;
	CommMsgPackage *firstMsg = NULL;
	char szTempBuffer[MAX_PATH];
	char *token = NULL;
	char szSpec[] = ",";
	char szFileName[MAX_PATH];

	try
	{
		firstMsg = new CommMsgPackage();
		GetMSGHeader(firstMsg);
		strcpy(firstMsg->strMsgType, "GET");
		firstMsg->nMsgCount = 1;
		firstMsg->MsgList = new MsgData;

		firstMsg->MsgList->strKey = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strKey, MAX_PATH);
		firstMsg->MsgList->strValue = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strValue, MAX_PATH);
		sprintf(firstMsg->MsgList->strKey, "RUNSW");
		sprintf(firstMsg->MsgList->strValue, "%c", szSelTrace);

		BOOL  bRetrun = FALSE;
		while (1)
		{
			if (bRetrun)
			{
				break;
			}
			if (!sendMsg(firstMsg))
			{
				throw ERROR_OSASHAREGETRUNSW;
			}
			int nCount = 0;
			while (1)
			{
				if (nCount > 200)
				{
					throw ERROR_OSASHAREGETRUNSW;
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
						memset(szTempBuffer, 0, MAX_PATH);
						strcpy(szTempBuffer, getMsg->MsgList->strValue);
						token = strtok(szTempBuffer, szSpec);
						assert(token);
						if (strcmp(token, "BUSY") == 0)
						{
							bRetrun = FALSE;
							break;
						}
						else if (strcmp(token, "OK") == 0)
						{
							token = strtok(NULL, szSpec);
							assert(token);
							strcpy(szFileName, token);//获得返回值
							bRetrun = TRUE;
							break;
						}
						else
						{
							throw ERROR_OSASHAREGETRUNSW;
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
		//从路径中读取数据信息，并赋值
		stOSAScanData  stGetData;
		stGetData.pdbSrcX = pdblSweepDataX;
		stGetData.pdbSrcY = pdblSweepDataY;
		if (!ReadOSAScanData(szFileName, &stGetData))
		{
			throw ERROR_OSASHAREGETRUNSW;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR | ERROR_OSASHAREGETRUNSW;
	}

	delete[] firstMsg->MsgList->strValue;
	delete[] firstMsg->MsgList->strKey;
	delete firstMsg->MsgList;
	delete firstMsg;

	return dwErrorCode;
}
/////////////////////////////////////////////////////////////
//函数说明：
//    从OSA中获得单次扫描的点数
//Add by wanxin
//Time：20150520
/////////////////////////////////////////////////////////////
DWORD COSA_SHARE::GetSingleSweepPoint(DWORD * pCount)
{
	DWORD dwErrorCode = SUCCESS;
	CommMsgPackage *firstMsg = NULL;
	char szTempBuffer[MAX_PATH];
	char *token = NULL;
	char szSpec[] = ",";
	char szFileName[MAX_PATH];

	try
	{
		firstMsg = new CommMsgPackage();
		GetMSGHeader(firstMsg);
		strcpy(firstMsg->strMsgType, "GET");
		firstMsg->nMsgCount = 1;
		firstMsg->MsgList = new MsgData;

		firstMsg->MsgList->strKey = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strKey, MAX_PATH);
		firstMsg->MsgList->strValue = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strValue, MAX_PATH);
		sprintf(firstMsg->MsgList->strKey, "SWPOINTCOUNT");

		BOOL  bRetrun = FALSE;
		while (1)
		{
			if (bRetrun)
			{
				break;
			}
			if (!sendMsg(firstMsg))
			{
				throw ERROR_OSASHAREGETSWPOINTCOUNT;
			}
			int nCount = 0;
			while (1)
			{
				if (nCount > 200)
				{
					throw ERROR_OSASHAREGETSWPOINTCOUNT;
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
						memset(szTempBuffer, 0, MAX_PATH);
						strcpy(szTempBuffer, getMsg->MsgList->strValue);
						token = strtok(szTempBuffer, szSpec);
						assert(token);
						if (strcmp(token, "BUSY") == 0)
						{
							bRetrun = FALSE;
							break;
						}
						else if (strcmp(token, "OK") == 0)
						{
							token = strtok(NULL, szSpec);
							assert(token);
							*pCount = atol(token);
							bRetrun = TRUE;
							break;
						}
						else
						{
							throw ERROR_OSASHAREGETSWPOINTCOUNT;
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
		dwErrorCode = UNEXPECT_OCCUR | ERROR_OSASHAREGETSWPOINTCOUNT;
	}

	delete[] firstMsg->MsgList->strValue;
	delete[] firstMsg->MsgList->strKey;
	delete firstMsg->MsgList;
	delete firstMsg;

	return dwErrorCode;
}
////////////////////////////////////////////////////////////////////////////////////
//函数说明：
//   初始化OSA放大测试
//Add by wanxin
//Time:2019/7/23
///////////////////////////////////////////////////////////////////////////////////
DWORD COSA_SHARE::InitAmpTest(double dblStartWL, double dblStopWL, double dblRBW)
{
	DWORD dwErrorCode = SUCCESS;
	CommMsgPackage *firstMsg = NULL;
	char szTempBuffer[MAX_PATH];

	try
	{

		m_stScanSetting.m_dblStartWL = dblStartWL;
		m_stScanSetting.m_dblStopWL = dblStopWL;
		m_stScanSetting.m_dblRBW = dblRBW;

		firstMsg = new CommMsgPackage();
		GetMSGHeader(firstMsg);
		strcpy(firstMsg->strMsgType, "SET");
		firstMsg->nMsgCount = 1;
		firstMsg->MsgList = new MsgData;

		firstMsg->MsgList->strKey = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strKey, MAX_PATH);
		firstMsg->MsgList->strValue = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strValue, MAX_PATH);
		sprintf(firstMsg->MsgList->strKey, "LOCALCTRL");

		sprintf(firstMsg->MsgList->strValue, "%.3f,%.3f,%.4f", dblStartWL, dblStopWL, dblRBW);

		BOOL  bRetrun = FALSE;
		while (1)
		{
			if (bRetrun)
			{
				break;
			}
			if (!sendMsg(firstMsg))
			{
				throw ERROR_OSASHARESETINITAMP;
			}
			int nCount = 0;
			while (1)
			{
				if (nCount > 200)
				{
					throw ERROR_OSASHARESETINITAMP;
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
							throw ERROR_OSASHARESETINITAMP;
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
		dwErrorCode = UNEXPECT_OCCUR | ERROR_OSASHARESETINITAMP;
	}

	return dwErrorCode;
}
/////////////////////////////////////////////////////////////
//函数说明：
//   设置OSA RBW
//Add by wanxin
//Time:2019/7/23
////////////////////////////////////////////////////////////
DWORD COSA_SHARE::SetRBW(double dblRBW)
{
	DWORD dwErrorCode = SUCCESS;
	CommMsgPackage *firstMsg = NULL;
	char szTempBuffer[MAX_PATH];

	try
	{
		firstMsg = new CommMsgPackage();
		GetMSGHeader(firstMsg);
		strcpy(firstMsg->strMsgType, "SET");
		firstMsg->nMsgCount = 1;
		firstMsg->MsgList = new MsgData;

		firstMsg->MsgList->strKey = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strKey, MAX_PATH);
		firstMsg->MsgList->strValue = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strValue, MAX_PATH);
		sprintf(firstMsg->MsgList->strKey, "RBW");

		sprintf(firstMsg->MsgList->strValue, "%.4f", dblRBW);

		BOOL  bRetrun = FALSE;
		while (1)
		{
			if (bRetrun)
			{
				break;
			}
			if (!sendMsg(firstMsg))
			{
				throw ERROR_OSASHARESETRBW;
			}
			int nCount = 0;
			while (1)
			{
				if (nCount > 200)
				{
					throw ERROR_OSASHARESETRBW;
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
							throw ERROR_OSASHARESETRBW;
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
		dwErrorCode = UNEXPECT_OCCUR | ERROR_OSASHARESETRBW;
	}

	return dwErrorCode;
}
/////////////////////////////////////////////////////////////////////
//函数说明：
//   获得RBW
//Add by wanxin
//Time:2019/7/23
///////////////////////////////////////////////////////////////////////
DWORD COSA_SHARE::GetRBW(double* pdblRBW)
{
	DWORD dwErrorCode = SUCCESS;
	CommMsgPackage *firstMsg = NULL;
	char szTempBuffer[MAX_PATH];
	char *token = NULL;
	char szSpec[] = ",";
	char szFileName[MAX_PATH];

	try
	{
		firstMsg = new CommMsgPackage();
		GetMSGHeader(firstMsg);
		strcpy(firstMsg->strMsgType, "GET");
		firstMsg->nMsgCount = 1;
		firstMsg->MsgList = new MsgData;

		firstMsg->MsgList->strKey = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strKey, MAX_PATH);
		firstMsg->MsgList->strValue = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strValue, MAX_PATH);
		sprintf(firstMsg->MsgList->strKey, "RBW");

		BOOL  bRetrun = FALSE;
		while (1)
		{
			if (bRetrun)
			{
				break;
			}
			if (!sendMsg(firstMsg))
			{
				throw ERROR_OSASHAREGETRBW;
			}
			int nCount = 0;
			while (1)
			{
				if (nCount > 200)
				{
					throw ERROR_OSASHAREGETRBW;
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
						memset(szTempBuffer, 0, MAX_PATH);
						strcpy(szTempBuffer, getMsg->MsgList->strValue);
						token = strtok(szTempBuffer, szSpec);
						assert(token);
						if (strcmp(token, "BUSY") == 0)
						{
							bRetrun = FALSE;
							break;
						}
						else if (strcmp(token, "OK") == 0)
						{
							token = strtok(NULL, szSpec);
							assert(token);
							*pdblRBW = atof(token);
							bRetrun = TRUE;
							break;
						}
						else
						{
							throw ERROR_OSASHAREGETRBW;
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
		dwErrorCode = UNEXPECT_OCCUR | ERROR_OSASHAREGETRBW;
	}

	delete[] firstMsg->MsgList->strValue;
	delete[] firstMsg->MsgList->strKey;
	delete firstMsg->MsgList;
	delete firstMsg;

	return dwErrorCode;
}

////////////////////////////////////////////////////////////////////
//函数说明：
//   根据复制文件读取文件并调用NF Lib库进行扫源计算
//Add by wanxin
//Time:2019/07/26
/////////////////////////////////////////////////////////////////////
BOOL COSA_SHARE::CalNFLibMeasureSource(LPCSTR lpstrFileName)
{
	char szMsg[MAX_PATH];
	char szLocalFile[MAX_PATH];
	stOTMSFileData stData;
	try
	{
		ZeroMemory(szLocalFile, MAX_PATH);
		sprintf(szLocalFile, "./SRCF.bin");
		if (!CopyFile(lpstrFileName, szLocalFile, FALSE))
		{
			throw "从服务器上复制扫源数据文件存在错误";
		}
		if (!m_DefFileObj.ReadOTMSBinFileHeader(szLocalFile, &stData.stFileHeader))
		{
			throw"读取扫源文件信息头存在错误";
		}
		WORD wSampleCount = stData.stFileHeader.bSMPL[0] << 8;
		wSampleCount += stData.stFileHeader.bSMPL[1];

		stData.stRawData.nPointCount = wSampleCount;
		stData.stRawData.pdblWL = (double*)VirtualAlloc(NULL, sizeof(double)*wSampleCount, MEM_RESERVE, PAGE_READWRITE);
		stData.stRawData.pdblPower = (double*)VirtualAlloc(NULL, sizeof(double)*wSampleCount, MEM_RESERVE, PAGE_READWRITE);
		stData.stRawData.pdblRBW = (double*)VirtualAlloc(NULL, sizeof(double)*wSampleCount, MEM_RESERVE, PAGE_READWRITE);

		if (!m_DefFileObj.ReadOTMSFileDataFromBinFile(szLocalFile, &stData))
		{
			throw"读取扫源文件原始数据存在错误";
		}

		ZeroMemory(&m_pdblScanData[SRC_SCAN], m_dwSweepPoint * sizeof(double));
		for (DWORD i = 0; i < m_dwSweepPoint; i++)
		{
			m_pdblScanData[SRC_SCAN][i] += m_dblSRCPointPower[i];
		}

		WORD	wChCount = 0;
		m_stEDFAResult.m_dblSumSrcSigPwr = GetSrcChPower(m_stScanSetting.m_dblStartWL,
			m_stScanSetting.m_dblStopWL,
			m_stScanSetting.m_dblSrcOffset,
			(WORD)m_dwSweepPoint,
			m_pdblScanData[SRC_SCAN],
			m_stEDFAResult.m_pdblChWL,
			m_stEDFAResult.m_pdblSrcPwr,
			&wChCount);
	}
	catch (char*pstrMsg)
	{
		ZeroMemory(szMsg, MAX_PATH);
		sprintf(szMsg, "%s",pstrMsg);
		return FALSE;
	}


	if (stData.stRawData.pdblWL != NULL)
	{
		VirtualFree(stData.stRawData.pdblWL, 0, MEM_RELEASE);
	}
	if (stData.stRawData.pdblPower != NULL)
	{
		VirtualFree(stData.stRawData.pdblPower, 0, MEM_RELEASE);
	}
	if (stData.stRawData.pdblRBW != NULL)
	{
		VirtualFree(stData.stRawData.pdblRBW, 0, MEM_RELEASE);
	}
	return TRUE;
}


////////////////////////////////////////////////////////////////////////
//函数说明：
//   扫描函数，这里需要单独处理，采用自己算法
//Add by wanxin
//Time:2019/7/23
///////////////////////////////////////////////////////////////////////
DWORD COSA_SHARE::MeasureSource()
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	char *token = NULL;
	char szSpec[] = ",";
	CommMsgPackage *firstMsg = NULL;
	char szTempBuffer[MAX_PATH + 3];
	char szFileName[MAX_PATH];
	try
	{
		firstMsg = new CommMsgPackage();
		GetMSGHeader(firstMsg);
		strcpy(firstMsg->strMsgType, "SET");
		firstMsg->nMsgCount = 1;
		firstMsg->MsgList = new MsgData;

		firstMsg->MsgList->strKey = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strKey, MAX_PATH);
		firstMsg->MsgList->strValue = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strValue, MAX_PATH);
		sprintf(firstMsg->MsgList->strKey, "MEASURESOURCE");

		BOOL  bRetrun = FALSE;
		while (1)
		{
			if (bRetrun)
			{
				break;
			}
			if (!sendMsg(firstMsg))
			{
				throw ERROR_OSASHARESETMEASURESOURCE;
			}
			int nCount = 0;
			while (1)
			{
				if (nCount > 200)
				{
					throw ERROR_OSASHARESETMEASURESOURCE;
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
						memset(szTempBuffer, 0, MAX_PATH + 3);
						strcpy(szTempBuffer, getMsg->MsgList->strValue);
						token = strtok(szTempBuffer, szSpec);
						assert(token);
						if (strcmp(token, "BUSY") == 0)
						{
							bRetrun = FALSE;
							break;
						}
						else if (strcmp(token, "OK") == 0)
						{
							token = strtok(NULL, szSpec);
							assert(token);
							strcpy(szFileName, token);
							bRetrun = TRUE;
							break;
						}
						else
						{
							throw ERROR_OSASHARESETMEASURESOURCE;
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

		//客户端从server端复制文件并
		if (!CalNFLibMeasureSource(szFileName))
		{
			throw ERROR_OSASHARESETMEASURESOURCE;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}


////////////////////////////////////////////////////////////////////
//函数说明：
//   调用NF计算函数计算EDFA放大结果
//Add by wanxin
//Time:2019/7/26
////////////////////////////////////////////////////////////////////
BOOL COSA_SHARE::CalNFLibMeasureAmp(LPCSTR lpstrFileName)
{
	char szMsg[MAX_PATH];
	char szLocalFile[MAX_PATH];
	stOTMSFileData stData;
	try
	{
		ZeroMemory(szLocalFile, MAX_PATH);
		sprintf(szLocalFile, "./AMPF.bin");
		if (!CopyFile(lpstrFileName, szLocalFile, FALSE))
		{
			throw "从服务器上复制扫放大数据文件存在错误";
		}
		if (!m_DefFileObj.ReadOTMSBinFileHeader(szLocalFile, &stData.stFileHeader))
		{
			throw"读取扫放大文件信息头存在错误";
		}
		WORD wSampleCount = stData.stFileHeader.bSMPL[0] << 8;
		wSampleCount += stData.stFileHeader.bSMPL[1];

		stData.stRawData.nPointCount = wSampleCount;
		stData.stRawData.pdblWL = (double*)VirtualAlloc(NULL, sizeof(double)*wSampleCount, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
		stData.stRawData.pdblPower = (double*)VirtualAlloc(NULL, sizeof(double)*wSampleCount, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
		stData.stRawData.pdblRBW = (double*)VirtualAlloc(NULL, sizeof(double)*wSampleCount, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

		if (!m_DefFileObj.ReadOTMSFileDataFromBinFile(szLocalFile, &stData))
		{
			throw"读取扫放大文件原始数据存在错误";
		}

		for (DWORD i = 0; i < m_dwSweepPoint; i++)
		{
			m_pdblScanData[AMP_SCAN][i] += m_dblSRCPointPower[i];
		}

		if (!GetNormalModeEDFAResult(m_stScanSetting, &m_stEDFAResult, m_pdblScanData[SRC_SCAN], m_pdblScanData[AMP_SCAN], SWEEPPOINT))
		{
			throw ERROR_SWEEP_DATA;
		}
	}
	catch (char*pstrMsg)
	{
		ZeroMemory(szMsg, MAX_PATH);
		sprintf(szMsg, "%s", pstrMsg);
		return FALSE;
	}

	if (stData.stRawData.pdblWL != NULL)
	{
		VirtualFree(stData.stRawData.pdblWL, 0, MEM_RELEASE);
	}
	if (stData.stRawData.pdblPower != NULL)
	{
		VirtualFree(stData.stRawData.pdblPower, 0, MEM_RELEASE);
	}
	if (stData.stRawData.pdblRBW != NULL)
	{
		VirtualFree(stData.stRawData.pdblRBW, 0, MEM_RELEASE);
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////
//函数说明：
//   扫放大功能函数，这里采用自己NF算法
//Add by wanxin
//Time:2019/7/23
//////////////////////////////////////////////////////////////////
DWORD COSA_SHARE::MeasureAmplifier(BOOL bScanSrcOnly)
{
	DWORD dwErrorCode = SUCCESS;
	CHAR szCmdString[TXLENS];
	char *token = NULL;
	char szSpec[] = ",";
	CommMsgPackage *firstMsg = NULL;
	char szTempBuffer[MAX_PATH + 3];
	char szFileName[MAX_PATH];
	try
	{
		firstMsg = new CommMsgPackage();
		GetMSGHeader(firstMsg);
		strcpy(firstMsg->strMsgType, "SET");
		firstMsg->nMsgCount = 1;
		firstMsg->MsgList = new MsgData;

		firstMsg->MsgList->strKey = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strKey, MAX_PATH);
		firstMsg->MsgList->strValue = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strValue, MAX_PATH);
		sprintf(firstMsg->MsgList->strKey, "MEASUREAMP");

		BOOL  bRetrun = FALSE;
		while (1)
		{
			if (bRetrun)
			{
				break;
			}
			if (!sendMsg(firstMsg))
			{
				throw ERROR_OSASHARESETMEASUREAMP;
			}
			int nCount = 0;
			while (1)
			{
				if (nCount > 200)
				{
					throw ERROR_OSASHARESETMEASUREAMP;
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
						memset(szTempBuffer, 0, MAX_PATH + 3);
						strcpy(szTempBuffer, getMsg->MsgList->strValue);
						token = strtok(szTempBuffer, szSpec);
						assert(token);
						if (strcmp(token, "BUSY") == 0)
						{
							bRetrun = FALSE;
							break;
						}
						else if (strcmp(token, "OK") == 0)
						{
							token = strtok(NULL, szSpec);
							assert(token);
							strcpy(szFileName, token);
							bRetrun = TRUE;
							break;
						}
						else
						{
							throw ERROR_OSASHARESETMEASUREAMP;
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

		//客户端从server端复制文件并
		if (!CalNFLibMeasureAmp(szFileName))
		{
			throw ERROR_OSASHARESETMEASUREAMP;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}
////////////////////////////////////////////////////////////////////////
//函数说明：
//   获得扫源和放大后的total power EDFA结果
//Add by wanxin
//Time:2019/7/23
////////////////////////////////////////////////////////////////////////
DWORD COSA_SHARE::GetEDFAResult(double *pdblSumSrcSigPwr, double *pdblSumAmpSigPwr, double *pdblSunGain)
{
	DWORD dwErrorCode = SUCCESS;
	CommMsgPackage *firstMsg = NULL;
	char szTempBuffer[MAX_PATH];
	char *token = NULL;
	char szSpec[] = ",";
	char szFileName[MAX_PATH];

	try
	{
		firstMsg = new CommMsgPackage();
		GetMSGHeader(firstMsg);
		strcpy(firstMsg->strMsgType, "GET");
		firstMsg->nMsgCount = 1;
		firstMsg->MsgList = new MsgData;

		firstMsg->MsgList->strKey = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strKey, MAX_PATH);
		firstMsg->MsgList->strValue = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strValue, MAX_PATH);
		sprintf(firstMsg->MsgList->strKey, "EDFARESULT");

		BOOL  bRetrun = FALSE;
		while (1)
		{
			if (bRetrun)
			{
				break;
			}
			if (!sendMsg(firstMsg))
			{
				throw ERROR_OSASHAREGETEDFARESULT;
			}
			int nCount = 0;
			while (1)
			{
				if (nCount > 200)
				{
					throw ERROR_OSASHAREGETEDFARESULT;
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
						memset(szTempBuffer, 0, MAX_PATH);
						strcpy(szTempBuffer, getMsg->MsgList->strValue);
						token = strtok(szTempBuffer, szSpec);
						assert(token);
						if (strcmp(token, "BUSY") == 0)
						{
							bRetrun = FALSE;
							break;
						}
						else if (strcmp(token, "OK") == 0)
						{
							token = strtok(NULL, szSpec);
							assert(token);
							*pdblSumSrcSigPwr = atof(token);

							token = strtok(NULL, szSpec);
							assert(token);
							*pdblSumAmpSigPwr = atof(token);

							token = strtok(NULL, szSpec);
							assert(token);
							*pdblSunGain = atof(token);

							bRetrun = TRUE;
							break;
						}
						else
						{
							throw ERROR_OSASHAREGETEDFARESULT;
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
		dwErrorCode = UNEXPECT_OCCUR | ERROR_OSASHAREGETRBW;
	}

	delete[] firstMsg->MsgList->strValue;
	delete[] firstMsg->MsgList->strKey;
	delete firstMsg->MsgList;
	delete firstMsg;
	return  dwErrorCode;
}
//////////////////////////////////////////////////////////////////////////////////////////
//函数说明：
//   获得EDFA扫源、扫放大通道的EDFA result
//Add by wanxin
//Time:2019/7/23
/////////////////////////////////////////////////////////////////////////////////////////
DWORD COSA_SHARE::GetEDFAChResult(DWORD *pwChCount, double *pdblChWL, double *pdblSrcpwr,
	double *pdblChGain, double *pdblChNF, double *pdblChAse,
	double *pdblGainFlatness, double *pdblMaxNF, double* pdblMaxGain, double* pdblMinGain)
{


	return SUCCESS;
}

//////////////////////////////////////////////////////////////////////////////////////
//函数说明：
//   按照设定格式保存数据到计算机对应路径中
//Add by wanxin
//Time:2019/7/23
/////////////////////////////////////////////////////////////////////////////////////
DWORD COSA_SHARE::SaveDatatoPC(LPCTSTR lpSavePath, LPCTSTR lpDataType, LPCTSTR lpFileType, char szSelTrace)
{
	DWORD dwErrorCode = 0;
	TCHAR	chSend[MAX_PATH];
	TCHAR	chReceive[MAX_COMM_FIELD] = { "" };
	long	iCount = 0;
	CHAR	*pchBMPData;
	int iBmpLength;
	int iBit;
	int iReadCount;
	DWORD dwSpareCount;
	DWORD			dwBytesReturned;
	TCHAR	chFileName[MAX_PATH];
	HANDLE	hFile;

	try
	{

	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}

	return dwErrorCode;
}


DWORD COSA_SHARE::GetDeviceInfo(stDevInfo *stInfo)
{
	DWORD dwErrorCode = 0;

	return dwErrorCode;
}

BOOL COSA_SHARE::GetErrorMessage(DWORD dwErrorCode, char *pszErrorMsg)
{
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//函数说明：
//   通过读取文件获取扫描数据
//Add by wanxin
//Time:2019/7/23
//////////////////////////////////////////////////////////////////////////////
DWORD COSA_SHARE::GetSweepData(double* pdblWL, double* pdblPower, char szSelTrace)
{
	DWORD dwErrorCode = SUCCESS;
	CommMsgPackage *firstMsg = NULL;
	char szTempBuffer[MAX_PATH];
	char *token = NULL;
	char szSpec[] = ",";
	char szFileName[MAX_PATH];

	try
	{
		firstMsg = new CommMsgPackage();
		GetMSGHeader(firstMsg);
		strcpy(firstMsg->strMsgType, "GET");
		firstMsg->nMsgCount = 1;
		firstMsg->MsgList = new MsgData;

		firstMsg->MsgList->strKey = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strKey, MAX_PATH);
		firstMsg->MsgList->strValue = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strValue, MAX_PATH);
		sprintf(firstMsg->MsgList->strKey, "SWDATA");
		sprintf(firstMsg->MsgList->strValue, "%c", szSelTrace);

		BOOL  bRetrun = FALSE;
		while (1)
		{
			if (bRetrun)
			{
				break;
			}
			if (!sendMsg(firstMsg))
			{
				throw ERROR_OSASHAREGETSWDATA;
			}
			int nCount = 0;
			while (1)
			{
				if (nCount > 200)
				{
					throw ERROR_OSASHAREGETSWDATA;
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
						memset(szTempBuffer, 0, MAX_PATH);
						strcpy(szTempBuffer, getMsg->MsgList->strValue);
						token = strtok(szTempBuffer, szSpec);
						assert(token);
						if (strcmp(token, "BUSY") == 0)
						{
							bRetrun = FALSE;
							break;
						}
						else if (strcmp(token, "OK") == 0)
						{
							token = strtok(NULL, szSpec);
							assert(token);
							strcpy(szFileName, token);//获得返回值
							bRetrun = TRUE;
							break;
						}
						else
						{
							throw ERROR_OSASHAREGETSWDATA;
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
		//从路径中读取数据信息，并赋值
		stOSAScanData  stGetData;
		stGetData.pdbSrcX = pdblWL;
		stGetData.pdbSrcY = pdblPower;
		if (!ReadOSAScanData(szFileName, &stGetData))
		{
			throw ERROR_OSASHAREGETSWDATA;
		}
	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR | ERROR_OSASHAREGETSWDATA;
	}

	delete[] firstMsg->MsgList->strValue;
	delete[] firstMsg->MsgList->strKey;
	delete firstMsg->MsgList;
	delete firstMsg;

	return dwErrorCode;
}

///////////////////////////////////////////////////////////////
//函数说明：
//    进行OSA自校准
//Add by wanxin
//Time:2019/7/23
///////////////////////////////////////////////////////////////
DWORD COSA_SHARE::SetCalibration(DWORD dwCalibrationType)
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

		firstMsg->MsgList->strKey = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strKey, MAX_PATH);
		firstMsg->MsgList->strValue = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strValue, MAX_PATH);
		sprintf(firstMsg->MsgList->strKey, "OSACAL");
		sprintf(firstMsg->MsgList->strValue, "%d", 1);

		BOOL  bRetrun = FALSE;
		while (1)
		{
			if (bRetrun)
			{
				break;
			}
			if (!sendMsg(firstMsg))
			{
				throw ERROR_OSASHARESETCAL;
			}
			int nCount = 0;
			while (1)
			{
				if (nCount > 200)
				{
					throw ERROR_OSASHARESETCAL;
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
							throw ERROR_OSASHARESETCAL;
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
		dwErrorCode = UNEXPECT_OCCUR | ERROR_OSASHARESETCAL;
	}

	delete[] firstMsg->MsgList->strValue;
	delete[] firstMsg->MsgList->strKey;
	delete firstMsg->MsgList;
	delete firstMsg;

	return dwErrorCode;
}
//////////////////////////////////////////////////////////////////////
//函数说明：
//   获得扫描曲线的Total power
//Add bywanxin
//Time:2019/7/23
//////////////////////////////////////////////////////////////////////
DWORD COSA_SHARE::GetTotalPower(double &dblPow, char szSelTrace)
{
	DWORD  dwErrorCode = SUCCESS;
	CHAR szDataStream[RXMINLENS];
	char  szCmdString[TXLENS];

	try
	{
		//set result format to ASCII

	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}



///////////////////////////////////////////////////////////////////////
//函数说明：
//   获得Zoom Value的值
//Add by wanxin
//Time:2019/7/23
//////////////////////////////////////////////////////////////////////
DWORD COSA_SHARE::GetZoomValue(double dbWLNM, double dbBWNM, double *pdbGetValue)
{
	DWORD dwErrorCode = SUCCESS;
	CommMsgPackage *firstMsg = NULL;
	char szTempBuffer[MAX_PATH];
	char *token = NULL;
	char szSpec[] = ",";
	char szFileName[MAX_PATH];

	try
	{
		firstMsg = new CommMsgPackage();
		GetMSGHeader(firstMsg);
		strcpy(firstMsg->strMsgType, "GET");
		firstMsg->nMsgCount = 1;
		firstMsg->MsgList = new MsgData;

		firstMsg->MsgList->strKey = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strKey, MAX_PATH);
		firstMsg->MsgList->strValue = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strValue, MAX_PATH);
		sprintf(firstMsg->MsgList->strKey, "ZOOMVALUE");
		sprintf(firstMsg->MsgList->strValue, "%.3f,%.4f", dbWLNM, dbBWNM);

		BOOL  bRetrun = FALSE;
		while (1)
		{
			if (bRetrun)
			{
				break;
			}
			if (!sendMsg(firstMsg))
			{
				throw ERROR_OSASHAREGETZOOMVALUE;
			}
			int nCount = 0;
			while (1)
			{
				if (nCount > 200)
				{
					throw ERROR_OSASHAREGETZOOMVALUE;
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
						memset(szTempBuffer, 0, MAX_PATH);
						strcpy(szTempBuffer, getMsg->MsgList->strValue);
						token = strtok(szTempBuffer, szSpec);
						assert(token);
						if (strcmp(token, "BUSY") == 0)
						{
							bRetrun = FALSE;
							break;
						}
						else if (strcmp(token, "OK") == 0)
						{
							token = strtok(NULL, szSpec);
							assert(token);
							*pdbGetValue = atof(token);
							bRetrun = TRUE;
							break;
						}
						else
						{
							throw ERROR_OSASHAREGETZOOMVALUE;
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
		dwErrorCode = UNEXPECT_OCCUR | ERROR_OSASHAREGETZOOMVALUE;
	}

	delete[] firstMsg->MsgList->strValue;
	delete[] firstMsg->MsgList->strKey;
	delete firstMsg->MsgList;
	delete firstMsg;

	return dwErrorCode;
}

DWORD COSA_SHARE::SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle)
{
	DWORD dwErrorCode = SUCCESS;

	return dwErrorCode;
}
///////////////////////////////////////////////////////////////////////////
//函数说明：
//   获得放大的实际RBW
//Add by wanxin
//Time：2019/7/23
/////////////////////////////////////////////////////////////////////////
DWORD COSA_SHARE::GetActualBW(double dblBwAmp, double &dblActBw)
{
	DWORD dwErrorCode = SUCCESS;
	CommMsgPackage *firstMsg = NULL;
	char szTempBuffer[MAX_PATH];
	char *token = NULL;
	char szSpec[] = ",";
	char szFileName[MAX_PATH];

	try
	{
		firstMsg = new CommMsgPackage();
		GetMSGHeader(firstMsg);
		strcpy(firstMsg->strMsgType, "GET");
		firstMsg->nMsgCount = 1;
		firstMsg->MsgList = new MsgData;

		firstMsg->MsgList->strKey = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strKey, MAX_PATH);
		firstMsg->MsgList->strValue = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strValue, MAX_PATH);
		sprintf(firstMsg->MsgList->strKey, "ACTUALRBW");
		sprintf(firstMsg->MsgList->strValue, "%.4f", dblBwAmp);

		BOOL  bRetrun = FALSE;
		while (1)
		{
			if (bRetrun)
			{
				break;
			}
			if (!sendMsg(firstMsg))
			{
				throw ERROR_OSASHAREGETACTUALBW;
			}
			int nCount = 0;
			while (1)
			{
				if (nCount > 200)
				{
					throw ERROR_OSASHAREGETACTUALBW;
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
						memset(szTempBuffer, 0, MAX_PATH);
						strcpy(szTempBuffer, getMsg->MsgList->strValue);
						token = strtok(szTempBuffer, szSpec);
						assert(token);
						if (strcmp(token, "BUSY") == 0)
						{
							bRetrun = FALSE;
							break;
						}
						else if (strcmp(token, "OK") == 0)
						{
							token = strtok(NULL, szSpec);
							assert(token);
							dblActBw = atof(token);
							bRetrun = TRUE;
							break;
						}
						else
						{
							throw ERROR_OSASHAREGETACTUALBW;
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
		dwErrorCode = UNEXPECT_OCCUR | ERROR_OSASHAREGETACTUALBW;
	}

	delete[] firstMsg->MsgList->strValue;
	delete[] firstMsg->MsgList->strKey;
	delete firstMsg->MsgList;
	delete firstMsg;

	return dwErrorCode;
}

////////////////////////////////////////////////////////////
//函数说明：
//   设置OSA的SENSE模式,1-Normal，2-MID,3-H1，4-H2,5-H3
//Add by wanxin
//Time:2019/7/24
///////////////////////////////////////////////////////////
DWORD COSA_SHARE::SetOSASenseMode(int nMode)
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

		firstMsg->MsgList->strKey = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strKey, MAX_PATH);
		firstMsg->MsgList->strValue = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strValue, MAX_PATH);
		sprintf(firstMsg->MsgList->strKey, "SENSE");
		sprintf(firstMsg->MsgList->strValue, "%d", nMode);

		BOOL  bRetrun = FALSE;
		while (1)
		{
			if (bRetrun)
			{
				break;
			}
			if (!sendMsg(firstMsg))
			{
				throw ERROR_OSASHARESETSENSE;
			}
			int nCount = 0;
			while (1)
			{
				if (nCount > 200)
				{
					throw ERROR_OSASHARESETSENSE;
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
							throw ERROR_OSASHARESETSENSE;
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
		dwErrorCode = UNEXPECT_OCCUR | ERROR_OSASHARESETSENSE;
	}

	delete[] firstMsg->MsgList->strValue;
	delete[] firstMsg->MsgList->strKey;
	delete firstMsg->MsgList;
	delete firstMsg;

	return dwErrorCode;
}


//////////////////////////////////////////////////////////////////////////////////////
//函数说明：
//    初始化WDM测试
//Add by wanxin
//Time：2018/03/13
/////////////////////////////////////////////////////////////////////////////
DWORD COSA_SHARE::InitWDMTest(double dblStartWL, double dblStopWL, double dblRBW)
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

		firstMsg->MsgList->strKey = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strKey, MAX_PATH);
		firstMsg->MsgList->strValue = new char[MAX_PATH];
		ZeroMemory(firstMsg->MsgList->strValue, MAX_PATH);
		sprintf(firstMsg->MsgList->strKey, "INITWDMTEST");
		sprintf(firstMsg->MsgList->strValue, "%.3f,%.3f,%.3f", dblStartWL, dblStopWL, dblRBW);

		BOOL  bRetrun = FALSE;
		while (1)
		{
			if (bRetrun)
			{
				break;
			}
			if (!sendMsg(firstMsg))
			{
				throw ERROR_OSASHARESETSENSE;
			}
			int nCount = 0;
			while (1)
			{
				if (nCount > 200)
				{
					throw ERROR_OSASHARESETSENSE;
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
							throw ERROR_OSASHARESETSENSE;
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
		dwErrorCode = UNEXPECT_OCCUR | ERROR_OSASHARESETSENSE;
	}

	delete[] firstMsg->MsgList->strValue;
	delete[] firstMsg->MsgList->strKey;
	delete firstMsg->MsgList;
	delete firstMsg;

	return dwErrorCode;
}
//////////////////////////////////////////////////////////////////////////////////////
//函数说明：
//    进行WDM扫描
//Add by wanxin
//Time：2018/03/13
/////////////////////////////////////////////////////////////////////////////
DWORD COSA_SHARE::MeasureWDM()
{
	DWORD dwErrorCode = SUCCESS;
	CHAR *pszDataStream = NULL;
	CHAR szCmdString[TXLENS];
	ZeroMemory(szCmdString, TXLENS * sizeof(CHAR));
	LPSTR pszToken = " ,\t\n", pszNewData = NULL;
	try
	{

	}
	catch (DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	VirtualFree(pszDataStream, 0, MEM_RELEASE);

	return dwErrorCode;
}
/////////////////////////////////////////////////////////
//函数说明：
//   设置OSA为Lock状态
//Add by wanxin
//Time:20190828
/////////////////////////////////////////////////////////
DWORD COSA_SHARE::SetOSALock(int nTimeOut)
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

		sprintf(firstMsg->MsgList->strValue, "%d", nTimeOut);
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

/////////////////////////////////////////////////////////////
//函数说明：
//    设置OSA UnLock
//Add by wanxin
//Time:20190828
////////////////////////////////////////////////////////////
DWORD COSA_SHARE::SetOSAUnlock()
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