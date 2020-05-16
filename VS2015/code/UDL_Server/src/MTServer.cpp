/*

*/

#include "stdafx.h"
#include "MTServer.h"
#include "UDLCMDMsg.h"
//#include "CUDLServerHandle.h"
#include "FuctionHead.h"
#include "AFXMT.H"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWinApp theApp;
SOCKET server;
char m_EnterBuffer[MAX_PATH];
int g_nClientNumber=0;
using namespace std;

UDLSERVERLib::IEngineMgrPtr m_pEngine;
UDLSERVERLib::IChamberInterfacePtr m_ChamberPtr;
UDLSERVERLib::IIOSAInterfacePtr m_OSAPtr;
UDLSERVERLib::IIPMInterfacePtr m_PMPtr;
UDLSERVERLib::IIPolInterfacePtr m_PolPtr;
UDLSERVERLib::IITLSInterfacePtr m_TLSPtr;
UDLSERVERLib::IIVOAInterfacePtr m_VOAPtr;
UDLSERVERLib::IIComDevInterfacePtr m_ComPtr;
UDLSERVERLib::IScanInterfacePtr m_ScanPtr;

BOOL m_bQuit= FALSE;
char g_szAppFolder[MAX_PATH];
CCriticalSection m_lockDevice;
BOOL g_bPreFinished = FALSE;
BOOL g_answer =FALSE;
BOOL g_bComSendFlag = FALSE;;
BOOL g_bComRevFlag = FALSE;;

//#pragma comment(linker,"/subsystem:\"windows\" /entry:\"mainCRTStartup\"")


void PrintRevMsg(LPCSTR lpstrMsg)
{
	CTime m_time;
	m_time = CTime::GetCurrentTime();
	CString strMsg;
	strMsg.Format("%s - %s\n",m_time.Format("%Y-%m-%d %H:%M:%S"),lpstrMsg);
	printf("%s\n",strMsg);
}



BOOL WINAPI ConsoleHandler(DWORD msgType)
{
    if (msgType == CTRL_C_EVENT)
    {
        printf("Ctrl-C!\n");
        return TRUE;
    }
    else if (msgType == CTRL_CLOSE_EVENT)
    {
        printf("Close console window!\n");
		m_bQuit = TRUE;
        /* Note: The system gives you very limited time to exit in this condition */
        return TRUE;
    }
 
    /*
        Other messages:
        CTRL_BREAK_EVENT         Ctrl-Break pressed
        CTRL_LOGOFF_EVENT        User log off
        CTRL_SHUTDOWN_EVENT      System shutdown
    */
 
    return FALSE;
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;
	WSADATA wsaData;
    int wsaret=WSAStartup(0x202,&wsaData);
	if(wsaret!=0)
	{
		return 0;
	}
	HANDLE hMutex = CreateMutex(NULL, FALSE, "ONLY_ONE_PROCESS");
	if (hMutex == NULL)
	{
		AfxMessageBox("创建互斥信号错误");
		return 0;
	}
	if (hMutex && ERROR_ALREADY_EXISTS == GetLastError())
	{	  
		AfxMessageBox("UDL Server端已经运行,请关闭后再打开");
		return 0;	  
	}

	SetConsoleCtrlHandler(ConsoleHandler, TRUE);
	 
	PrintRevMsg("Server is now running......");
	char szBuffer[MAX_PATH];
    ZeroMemory(szBuffer,sizeof(MAX_PATH));
	gethostname(szBuffer,MAX_PATH);
	struct hostent *hp;
	hp = gethostbyname(szBuffer);

	ZeroMemory(szBuffer,sizeof(MAX_PATH));
	sprintf(szBuffer,"Server IP is: %s,Port is %d",inet_ntoa(*(struct in_addr *)hp->h_addr_list[0]),20248);
	PrintRevMsg(szBuffer);
	
	ZeroMemory(g_szAppFolder,MAX_PATH);
	GetCurrentDirectory(MAX_PATH,g_szAppFolder);
	if(!InitalUDLServer())
	{
		PrintRevMsg("Inital UDL Com error!!!");
		return 0;
	}
    PrintRevMsg("Inital UDL COM successfully!");
	AfxBeginThread(MTServerThread,0);
	while(!m_bQuit);
	closesocket(server);
	WSACleanup();
	if(!ReleaseUDLServer())
	{
		PrintRevMsg("Release UDL Com error!!!");
		return 0;
	}

	return nRetCode;
}

UINT  MTServerThread(LPVOID pParam)
{		
	
	sockaddr_in local;
	char szBuffer[MAX_PATH];

	local.sin_family=AF_INET;
	local.sin_addr.s_addr=INADDR_ANY;
	local.sin_port=htons((u_short)20248);

	server=socket(AF_INET,SOCK_STREAM,0);
	if(server==INVALID_SOCKET)
	{
		return 0;
	}
	//int iMode =1;
	//ioctlsocket(server,FIONBIO,(unsigned long FAR*)&iMode);
	
	if(bind(server,(sockaddr*)&local,sizeof(local))!=0)
	{
		return 0;
	}
	if(listen(server,10)!=0)
	{
		return 0;
	}

	SOCKET client;
	sockaddr_in from;
	int fromlen=sizeof(from);
    
	while(true)
	{		
		client=accept(server,(struct sockaddr*)&from,&fromlen);
		ZeroMemory(szBuffer,sizeof(char)*MAX_PATH);
		sprintf(szBuffer,"Client(%s) conect to server",inet_ntoa(from.sin_addr));
		PrintRevMsg(szBuffer);
		g_nClientNumber++;
		AfxBeginThread(ClientThread,(LPVOID)client);	
	}	

	return 0;
}
////////////////////////////////////////////////////////////////
//函数说明 ：
//    处理客户端发送过来的退格键
//Add by wanxin
//Time:20170317
////////////////////////////////////////////////////////////////
void HandleBackspaceChar(char * pszSrc,int nLength)
{
	if(pszSrc ==NULL ||nLength ==0 )
		return;
	CString strTemp;
	strTemp = pszSrc;
	while (TRUE)
	{
		int n = strTemp.Find('\b');
		if(n==-1)
		{
			break;
		}
		strTemp.Delete(n-1,2);	
	}
	ZeroMemory(pszSrc,sizeof(char)*nLength);
	strcpy(pszSrc,strTemp);
}

UINT COMSendThread(LPVOID pParam)
{
	pComParam  pstParam;
	char buff[2048];
	CString cmd,params;
	CString strMsg;
	pstParam = (pComParam)pParam;
	fd_set fdread;
	int n;
	FD_ZERO(&fdread);
	FD_SET(pstParam->s,&fdread);
	while(g_bComSendFlag)
	{
		ZeroMemory(buff,sizeof(char)*2048);
		if(FD_ISSET(pstParam->s,&fdread))
		{
			n=recv(pstParam->s,buff,2048,0);
			if(n==SOCKET_ERROR || n==0)			
				break;
			if(n > 0)
			{
				if(ParseCmd(buff,cmd,params))
				{
					cmd.TrimLeft();
					cmd.TrimRight();
					cmd.TrimRight('\r');
					cmd.TrimRight('\n');
					if(cmd == COMSEND)          
					{
						g_bComSendFlag = FALSE;
					}
					else
					{
						m_lockDevice.Lock();
						HRESULT hresult = m_ComPtr->WriteBuffer(pstParam->lChIndex,(_bstr_t)buff,strlen(buff));
						m_lockDevice.Unlock();
						if (hresult == S_FALSE)
						{	
							 //strMsg = (LPCSTR)m_ComPtr->GetLastMessage();
							ZeroMemory(buff,sizeof(char)*2048);
							sprintf(buff,"Com Send error!\r#");
							send(pstParam->s,buff,strlen(buff),0);
							return FALSE;
						}					
					}
				}
			}
		}
	}
	return 0;
}



UINT  ClientThread(LPVOID pParam)
{
	char buff[2048];
	char TempBuffer[2048];
	CString cmd;
	CString params;
	int n;
	BOOL auth=false;
	SOCKET client=(SOCKET)pParam;
	int iKeepAlive =1;
	setsockopt(client,SOL_SOCKET,SO_KEEPALIVE,(char*)&iKeepAlive,sizeof(iKeepAlive));
	fd_set fdread;
	FD_ZERO(&fdread);
	FD_SET(client,&fdread);
	if(g_nClientNumber > 1)
	{
		ZeroMemory(buff,sizeof(char)*2048);
		strcpy(buff,"One client has already connected, You will be disconnect.\r\n#");
		send(client,buff,strlen(buff),0);
		closesocket(client);
		return 0;
	}
	ZeroMemory(buff,sizeof(char)*2048);
	strcpy(buff,"#Server Ready.\r\n#");
	send(client,buff,strlen(buff),0);
	ZeroMemory(buff,sizeof(char)*2048);
	ZeroMemory(TempBuffer,sizeof(char)*2048);
	while(true)
	{
		ZeroMemory(buff,sizeof(char)*2048);
		if(FD_ISSET(client,&fdread))
		{
			n=recv(client,buff,2048,0);
			if(n==SOCKET_ERROR || n==0)			
				break;
			if(n > 0)
			{
				strcat(TempBuffer,buff);
				if(strstr(buff,"\r") !=NULL)
				{	
        			HandleBackspaceChar(TempBuffer,strlen(TempBuffer));
					ZeroMemory(buff,sizeof(char)*2048);
					strcpy(buff,TempBuffer);
					ZeroMemory(TempBuffer,sizeof(char)*2048);//清空缓存
					
					if(ParseCmd(buff,cmd,params))
					{
						if(!ResponseMsg(buff,cmd,client))
						{

						}
					}
					else
					{
						SendErrorMsg(client,0);
					}
				}
			}		
		}
		else
		{
			closesocket(client);
		}
	}		
	
	closesocket(client);
	return 0;
}

BOOL ResponseMsg(char* pBuffer,LPCSTR lpstrCMD,SOCKET s)
{
	CString strMsg;
    g_bComSendFlag = FALSE;
	g_bComRevFlag = FALSE;
	strMsg = pBuffer;
	strMsg.TrimLeft();
	strMsg.TrimRight();
	PrintRevMsg(strMsg);
	if(!HandleHelpMsg(strMsg.GetBuffer(0),lpstrCMD,s))
	{
		return FALSE;
	}
    if(!HandleEngineMsg(strMsg.GetBuffer(0),lpstrCMD,s))
	{
		return FALSE;
	}
	if(!HandleTLSMsg(strMsg.GetBuffer(0),lpstrCMD,s))
	{
		return FALSE;
	}
	if(!HandlePMMsg(strMsg.GetBuffer(0),lpstrCMD,s))
	{
		return FALSE;
	}
	if(!HandleVOAMsg(strMsg.GetBuffer(0),lpstrCMD,s))
	{
		return FALSE;
	}
	if(!HandlePOLMsg(strMsg.GetBuffer(0),lpstrCMD,s))
	{
		return FALSE;
	}
	if(!HandlechamberMsg(strMsg.GetBuffer(0),lpstrCMD,s))
	{
		return FALSE;
	}
	if(!HandleOSAMsg(strMsg.GetBuffer(0),lpstrCMD,s))
	{
		return FALSE;
	}
	if(!HandleDevMsg(strMsg.GetBuffer(0),lpstrCMD,s))
	{
		return FALSE;
	}
	if(!g_answer)
	{
		SendErrorMsg(s,0);
	}
	return TRUE;
}

BOOL ParseCmd(char *str, CString& cmd, CString& params)
{
	int n;
	CString tmp=str;	
	tmp.TrimLeft();
	tmp.TrimRight();	
	if((n=tmp.Find(' '))==-1)
	{
		tmp.MakeUpper();
	//	if(tmp!="QUIT")
	//		return false;
		cmd=tmp;
		return true;
	}		
	cmd=tmp.Left(n);
	params=tmp.Mid(n+1);
	cmd.MakeUpper();
	return true;
}

BOOL HandleHelpMsg(char* pBuffer,LPCSTR lpstrCMD,SOCKET s)
{
	char * token =NULL;
	char szSpec[] =" ";
	CString strCMD;
	strCMD = lpstrCMD;
	strCMD.TrimLeft();
	strCMD.TrimRight();
	strCMD.TrimRight('\r');
	strCMD.TrimRight('\n');
	if(strCMD== CMDHELP)          
	{
		g_answer = TRUE;
		token = strtok(pBuffer,szSpec);
		ASSERT(token);
        token = strtok(NULL,szSpec);
        strCMD =token;
		strCMD.TrimRight();
		strCMD.TrimLeft();
		strCMD.MakeUpper();
		if(strCMD.CompareNoCase("Engine")==0)//激光器
		{
			SendEngineInfo(s);
		}
		else if(strCMD.CompareNoCase("TLS")==0)//激光器
		{
			SendTLSInfo(s);
		}
		else if(strCMD.CompareNoCase("PM")==0)//功率计
		{
           SendPMInfo(s);
		}
		else if(strCMD.CompareNoCase("VOA")==0)//功率计
		{
           SendVOAInfo(s);
		}
		else if(strCMD.CompareNoCase("OSA")==0)//OSA
		{
           SendOSAInfo(s);
		}
		else if(strCMD.CompareNoCase("CHAMBER")==0)//CHAMBER
		{
			SendChamberInfo(s);
		}
		else if(strCMD.CompareNoCase("POL")==0)//CHAMBER
		{
            SendPOLInfo(s);
		}
		else if(strCMD.CompareNoCase("COM")==0)//SERIAL
		{
            SendComInfo(s);
		}
		else
		{
            SendHelpInfo(s);
		}
	}

    return TRUE;
}
BOOL HandleEngineMsg(char* pBuffer,LPCSTR lpstrCMD,SOCKET s)
{
	char * token =NULL;
	char szSpec[] =" ";
	CString strCMD;
	CString strBuffer;
	strCMD = lpstrCMD;
	strCMD.TrimLeft();
	strCMD.TrimRight();
	strBuffer = pBuffer;
	if(lpstrCMD == CMDHELP)          
	{
		SendHelpInfo(s);
	}
	if(strCMD== CMDENGINE)          
	{
		g_answer = TRUE;
		token = strtok(pBuffer,szSpec);
		ASSERT(token);
        token = strtok(NULL,szSpec);
        strCMD =token;
		strCMD.TrimRight();
		strCMD.TrimLeft();
		strCMD.MakeUpper();
		if(strCMD.CompareNoCase("LOADXML")==0)//设置激光器波长
		{
			g_bPreFinished = FALSE;
			if(!LoadConfigCMD(strBuffer.GetBuffer(0),s))
			{
				return FALSE;
			}
			g_bPreFinished = TRUE;
		}
		else if(strCMD.CompareNoCase("OPENDEVICE")==0)//设置激光器波长
		{
			if(!OpenDevice(s))
			{
				return FALSE;
			}
		}
		else if(strCMD.CompareNoCase("VER")==0)//设置激光器波长
		{
			if(!OpenDevice(s))
			{
				return FALSE;
			}
		}
		else 
		{
			SendErrorMsg(s,-1);
		}
	}

    return TRUE;
}


BOOL SendBufferBy1M(SOCKET s, char * str, int nLength)
{
	long lTemplength = nLength;
	int nGetLength = 0;
	long lGetLenth = 0;
	char szBuffer[1024];
	char *pTemp  = str;
	while (TRUE)
	{
		ZeroMemory(szBuffer,sizeof(char)*1024);
		if(lTemplength < 1024)
		{			
			nGetLength = send(s,pTemp,lTemplength,0);
			lGetLenth += nGetLength;
			if(lGetLenth != nLength)
			{
                ZeroMemory(szBuffer,sizeof(char)*1024);
				sprintf(szBuffer,"send length is not equal the fact lenght");
				PrintRevMsg(szBuffer);
			}
			break;
		}
        else
		{
			nGetLength = send(s,pTemp,1024,0);
		}
		pTemp += nGetLength;
		lTemplength -=nGetLength;
		lGetLenth += nGetLength;
	}
    return TRUE;
}


BOOL SendFile(SOCKET s, CString fname)
{	
	CFile f;
	BOOL p=f.Open(fname,CFile::modeRead);	
	char buff[1024];
	int y;
	int x;
	if(!p)
		return false;
	while(true)
	{		
		y=f.Read(buff,1024);
		x=send(s,buff,y,0);		
		if(y<1024)
		{
			f.Close();
			break;
		}			
	}	

	return true;
}

bool InitalUDLServer()
{
	::CoInitialize(NULL);

	HRESULT hr = m_pEngine.CreateInstance(__uuidof(EngineMgr));
	if (FAILED(hr))
	{
		_com_error e(hr);
		//AfxMessageBox(e.ErrorMessage());
		printf("%s\r\n",e.ErrorMessage());
		return false;
	}
	ASSERT( SUCCEEDED( hr ) );

	hr 	=m_TLSPtr.CreateInstance(__uuidof(ITLSInterface)); //TLS
	if (FAILED(hr))
	{
		_com_error e(hr);
		//AfxMessageBox(e.ErrorMessage());
		printf("%s\r\n",e.ErrorMessage());
		return false;
	}
    ASSERT( SUCCEEDED( hr ) );

	hr 	=m_PMPtr.CreateInstance( __uuidof(IPMInterface));//PM
	if (FAILED(hr))
	{
		_com_error e(hr);
		printf("%s\r\n",e.ErrorMessage());
		return false;
	}
	ASSERT( SUCCEEDED( hr ) );

	hr 	=m_VOAPtr.CreateInstance( __uuidof(IVOAInterface));//VOA
	if (FAILED(hr))
	{
		_com_error e(hr);
		printf("%s\r\n",e.ErrorMessage());
		return false;
	}
	ASSERT( SUCCEEDED( hr ) );

	hr 	=m_OSAPtr.CreateInstance( __uuidof(IOSAInterface));//OSA
	if (FAILED(hr))
	{
		_com_error e(hr);
		printf("%s\r\n",e.ErrorMessage());
		return false;
	}
	ASSERT( SUCCEEDED( hr ) );

	hr 	=m_PolPtr.CreateInstance( __uuidof(IPolInterface));//启动组件
	if (FAILED(hr))
	{
		_com_error e(hr);
		printf("%s\r\n",e.ErrorMessage());
		return false;
	}
	ASSERT( SUCCEEDED( hr ) );
	
	hr 	=m_ScanPtr.CreateInstance( __uuidof(ScanInterface));//启动组件
	if (FAILED(hr))
	{
		_com_error e(hr);
		printf("%s\r\n",e.ErrorMessage());
		return false;
	}
	ASSERT( SUCCEEDED( hr ) );
	
	hr 	=m_ChamberPtr.CreateInstance( __uuidof(ChamberInterface));//启动组件
	if (FAILED(hr))
	{
		_com_error e(hr);
		printf("%s\r\n",e.ErrorMessage());
		return false;
	}	
	ASSERT( SUCCEEDED( hr ) );

	hr   =m_ComPtr.CreateInstance( __uuidof(IComDevInterface));//启动组件
	if (FAILED(hr))
	{
		_com_error e(hr);
		printf("%s\r\n",e.ErrorMessage());
		return false;
	}
	ASSERT( SUCCEEDED( hr ) );

	return true;
}

bool ReleaseUDLServer()
{
	if(m_pEngine!=NULL)
	{
		m_pEngine.Release();
	}
	if(m_TLSPtr!=NULL)
	{
		m_TLSPtr.Release();
	}
	if(m_PMPtr!=NULL)
	{
		m_PMPtr.Release();
	}
	if(m_VOAPtr!=NULL)
	{
		m_VOAPtr.Release();
	}
	if(m_OSAPtr!=NULL)
	{
		m_OSAPtr.Release();
	}
	if(m_PolPtr!=NULL)
	{
		m_PolPtr.Release();
	}
	if(m_ScanPtr!=NULL)
	{
		m_ScanPtr.Release();
	}
	if(m_ChamberPtr!=NULL)
	{
		m_ChamberPtr.Release();
	}
	if(m_ComPtr!=NULL)
	{
		m_ComPtr.Release();
	}

	::CoUninitialize();

    return true;
}

BOOL SendErrorMsg(SOCKET s,int nMsgType)
{
	char szSendBuffer[256];
	
	switch(nMsgType) 
	{
	case -1:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			strcpy(szSendBuffer,"Please using: Help [TSL]|[PM]|[OSA]|[POL]|[CHAMBER]|[COM]to see the detail\r\n#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 0:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			strcpy(szSendBuffer,"!Invalid command.\r\n#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 1:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Param number error. Must in 1 - 20\r\n#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 2:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"XML file not load. Please loadxml first\r\n#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 3:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"SET TLS wavelenth param error\r\n#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 4:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Command format error\r\n#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 5:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"SET TLS power param error\r\n#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 6:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"SET TLS coherence control param error\r\n#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 7:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"SET TLS unit param error\r\n#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 8:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"SET TLS Parameters param error\r\n#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 9:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"SET TLS OutputEnable param error\r\n#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 10:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"SET TLS close param error\r\n#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 11:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Get PM unit param error\r\n#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 12:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Get PM average time param error\r\n#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 13:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Get PM wavelenth param error\r\n#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 14:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Get PM power param error\r\n#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 15:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set PM unit param error\r\n#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 16:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set PM wavelength param error\r\n#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 17:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set PM average time param error\r\n#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 18:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set PM range mode param error\r\n#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 19:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set PM parameters param error\r\n#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 20:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set PM close device param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 21:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Get PM range mode param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 22:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set PM zero param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 23:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set PM max min start param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 24:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Get PM max min power param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 25:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set PM max min stop param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 26:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set VOA close device param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 27:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set VOA reset device param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 28:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set VOA wavelength param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 29:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Get VOA wavelength param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 30:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set VOA attenuation param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 31:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Get VOA attenuation param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 32:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set VOA enable param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 33:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set VOA input offset param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 34:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set Pol close device param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 35:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set Pol reset device param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 36:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Get Pol POSPolarizer param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 37:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set Pol all pos param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;	
	case 38:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set Pol diagonal angles param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 39:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set Pol horizontal angles param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 40:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set Pol half angles param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 41:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set Pol polarizer angles param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;	
	case 42:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set Pol quarter angles param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 43:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set Pol righthand circular angles param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 44:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set Pol vertical angles param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 45:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set Chamber close device param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 46:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set Chamber run stop param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;	
	case 47:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set Chamber run start param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;	
	case 48:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set Chamber point param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;	
	case 49:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Get Chamber point param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;	
	case 50:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Get Chamber temperature param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 51:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set OSA close device param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 52:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set OSA reset device param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 53:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set OSA loacal control param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 54:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set OSA RBW param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 55:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Get OSA RBW param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 56:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set OSA inital test param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 57:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set OSA measure source param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 58:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set OSA measure amplifier param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 59:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Get OSA channel count param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 60:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set OSA amplifier offset param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 61:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Get OSA amplifier offset param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 62:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set OSA initial sweep param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 63:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set OSA run sweep param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 64:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Save OSA data to PC param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 65:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Set OSA calibrate param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 66:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Get OSA zoom value param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 67:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Get OSA sweep point count param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 68:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Get OSA edfa result param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 69:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Get OSA sweep data param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 70:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Close serial param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 71:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Open serial param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	case 72:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Send serial param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
	case 73:
		{
			ZeroMemory(szSendBuffer,sizeof(char)*256);
			sprintf(szSendBuffer,"Read serial param error\r#");
			send(s,szSendBuffer,strlen(szSendBuffer),0);
		}
		break;
	}
    return TRUE;
}
void SendHelpInfo(SOCKET s)
{
	char szSendBuffer[256];
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"###############################Help Info##################################\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);	
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"Help [Engine] -- UDL Engine function information\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"Help [TLS] -- TLS function information\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"Help [PM]-- PM function information\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"Help [OSA] -- OSA function information\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"Help [POL] -- PDL function information\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"Help [CHAMBER] -- Chamber function information\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"Help [COM] -- Com function information\r\n#");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
}
void SendEngineInfo(SOCKET s)
{
	char szSendBuffer[256];
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"###############################Engine Info##############################\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);

	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"Engine loadxml 1 [xml file name] -- Load xml config file on server\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"Engine opendevice -- Open all device\r\n#");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
//	ZeroMemory(szSendBuffer,sizeof(char)*256);
//	sprintf(szSendBuffer,"Engine verison -- Get UDL verison\r");
//	send(s,szSendBuffer,strlen(szSendBuffer),0);
//	ZeroMemory(szSendBuffer,sizeof(char)*256);
//	sprintf(szSendBuffer,"Engine geterrormsg -- Get error message\r\n#");
//	send(s,szSendBuffer,strlen(szSendBuffer),0);
}
void SendTLSInfo(SOCKET s)
{
	char szSendBuffer[256];
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"###############################TLS Info##############################\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);

	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"TLS SWL 2 [channel] [WL] -- Set TLS wavelenght\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"TLS SPOWER 2 [channel] [power] -- Set TLS power\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"TLS SCONHERENCE 2 [channel] [0|1]-- Set TLS Corherence control\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"TLS SUNIT 2 [channel] [0|1] -- Set TLS Unit\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"TLS SOUPT 2 [channel] [0|1] -- Set TLS output enable\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"TLS SPARAM 4 [channel] [0|1] [power] [WL] -- Set TLS parameters\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"TLS SCLOSE 1 [channel] -- Set TLS close\r\n#");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	
}
/////////////////////////////////////////TLS Function////////////////////////////////////////////
BOOL HandleTLSMsg(char* pBuffer,LPCSTR lpstrCMD,SOCKET s)
{
	char * token =NULL;
	char szSpec[] =" ";
	CString strCMD;
	CString strBuffer;
	strCMD = lpstrCMD;
	strCMD.TrimLeft();
	strCMD.TrimRight();
	strBuffer = pBuffer;
	if(strCMD== CMDTLS)          
	{
		if(!g_bPreFinished)
		{
			SendErrorMsg(s,2);
			return FALSE;						
		}
		g_answer = TRUE;
		token = strtok(pBuffer,szSpec);
		ASSERT(token);
        token = strtok(NULL,szSpec);
        strCMD =token;
		strCMD.TrimRight();
		strCMD.TrimLeft();
		strCMD.MakeUpper();
		if(strCMD.CompareNoCase("SWL")==0)//设置激光器波长
		{
           if(!SetTLSWavelength(strBuffer.GetBuffer(0),s))
		   {
			   return FALSE;
		   }
		}
        else if(strCMD.CompareNoCase("SPOWER")==0)
		{
           if(!SetTLSSourcePower(strBuffer.GetBuffer(0),s))
		   {
			   return FALSE;
		   }
		}
	    else if(strCMD.CompareNoCase("SCONHERENCE")==0)
		{
           if(!SetTLSCoherenceControl(strBuffer.GetBuffer(0),s))
		   {
			   return FALSE;
		   }
		}	
	    else if(strCMD.CompareNoCase("SUNIT")==0)
		{
           if(!SetTLSSourceUnit(strBuffer.GetBuffer(0),s))
		   {
			   return FALSE;
		   }
		}
		else if(strCMD.CompareNoCase("SPARAM")==0)
		{
           if(!SetTLSParameters(strBuffer.GetBuffer(0),s))
		   {
			   return FALSE;
		   }
		}
		else if(strCMD.CompareNoCase("SOUPT")==0)
		{
           if(!SetTLSOutputEnable(strBuffer.GetBuffer(0),s))
		   {
			   return FALSE;
		   }
		}
		else if(strCMD.CompareNoCase("SCLOSE")==0)
		{
           if(!CloseTLSDevice(strBuffer.GetBuffer(0),s))
		   {
			   return FALSE;
		   }
		}
		else
		{
			SendErrorMsg(s,-1);
		}
	}

    return TRUE;
}

void SendPMInfo(SOCKET s)
{
	char szSendBuffer[256];
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"###############################PM Info##############################\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);

	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"PM GUNIT 1 [channel] -- Get PM uint\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"PM GAVGTIME 1 [channel] -- Get PM averager time\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"PM GWL 1 [channel] -- Get PM wavelength\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"PM GPOWER 1 [channel] -- Get PM power\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"PM GRANGEMODE 1 [channel] -- Get PM range mode\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"PM SUNIT 2 [channel] [0|1] -- Set PM unit\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"PM SWL 2 [channel] [WL] -- Set PM wavelength\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"PM SAVGTIME 2 [channel] [avgtime] -- Set PM read power average time\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"PM SRANGEMODE 2 [channel] [0|1] -- Set PM range mode\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"PM SPARAM 5 [channel] [rangeauto(0|1)] [WL] [avgtime] [range]-- Set PM parameters\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"PM SCLOS 1 [channel] -- Set PM clsoe\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"PM SZERO 1 [channel] -- Set PM zero\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"PM SMAXMINSTART 1 [channel] -- Set PM min max mode start\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"PM GMAXMINPOWER 1 [channel] -- Get PM min max power\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"PM SMAXMINSTOP 1 [channel] -- Set PM min max mode stop\r\n#");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	
}
/////////////////////////////////////////PM Function////////////////////////////////////////////
BOOL HandlePMMsg(char* pBuffer,LPCSTR lpstrCMD,SOCKET s)
{
	char * token =NULL;
	char szSpec[] =" ";
	CString strCMD;
	CString strBuffer;
	strCMD = lpstrCMD;
	strCMD.TrimLeft();
	strCMD.TrimRight();
	strBuffer = pBuffer;
	if(strCMD == CMDPM)          
	{
		if(!g_bPreFinished)
		{
			SendErrorMsg(s,2);
			return FALSE;						
		}
		g_answer = TRUE;
		token = strtok(pBuffer,szSpec);
		ASSERT(token);
        token = strtok(NULL,szSpec);
        strCMD =token;
		strCMD.TrimRight();
		strCMD.TrimLeft();
		strCMD.MakeUpper();
		if(strCMD.CompareNoCase("GUNIT")==0)//设置激光器波长
		{
			if(!GetPMUnit(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
        else if(strCMD.CompareNoCase("GAVGTIME")==0)
		{
			if(!GetPMAverageTime(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
	    else if(strCMD.CompareNoCase("GWL")==0)
		{
			if(!GetPMWavelength(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}	
	    else if(strCMD.CompareNoCase("GPOWER")==0)
		{
			if(!ReadPower(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
		else if(strCMD.CompareNoCase("GRANGEMODE")==0)
		{
			if(!GetPMRangeMode(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}			
		}
		else if(strCMD.CompareNoCase("SUNIT")==0)
		{
			if(!SetPMUnit(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
		else if(strCMD.CompareNoCase("SWL")==0)
		{
			if(!SetPMWavelength(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}	
		}
		else if(strCMD.CompareNoCase("SAVGTIME")==0)
		{
			if(!SetPMAverageTime(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}		
		}
		else if(strCMD.CompareNoCase("SRANGEMODE")==0)
		{
			if(!SetPMRangeMode(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}			
		}
		else if(strCMD.CompareNoCase("SPARAM")==0)
		{
			if(!SetPMParameters(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}			
		}
		else if(strCMD.CompareNoCase("SCLOSE")==0)
		{
			if(!ClosePMDevice(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}				
		}
		else if(strCMD.CompareNoCase("SZERO")==0)
		{
			if(!SetPMZero(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}			
		}
		else if(strCMD.CompareNoCase("SMAXMINSTART")==0)
		{
			if(!SetPMMaxMinPowerStart(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}			
		}
		else if(strCMD.CompareNoCase("GMAXMINPOWER")==0)
		{
			if(!GetPMMaxMinPower(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}			
		}
		else if(strCMD.CompareNoCase("SMAXMINSTOP")==0)
		{
			if(!SetPMMaxMinPowerStop(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}			
		}
		else 
		{
			SendErrorMsg(s,-1);
		}
	}

    return TRUE;
}

void SendVOAInfo(SOCKET s)
{
	char szSendBuffer[256];
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"###############################VOA Info##############################\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);

	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"VOA SCLOSE 1 [channel] -- Set VOA clsoe\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"VOA SRESET 1 [channel] -- Set VOA reset\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"VOA SWL 2 [channel] [WL] -- Set VOA wavelength\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"VOA GWL 1 [channel] -- Get VOA wavelength\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"VOA SATTEN 1 [channel] -- Set VOA attenuation\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"VOA SENABLE 2 [channel] [0|1] -- Set VOA out enable\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"VOA SOFFSET 2 [channel] [offset] -- Set VOA offset\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"VOA GSTATUS 1 [channel] -- Get VOA status\r#");
	send(s,szSendBuffer,strlen(szSendBuffer),0);	
}
/////////////////////////////////////////VOA Function////////////////////////////////////////////
BOOL HandleVOAMsg(char* pBuffer,LPCSTR lpstrCMD,SOCKET s)
{
	char * token =NULL;
	char szSpec[] =" ";
	CString strCMD;
	CString strBuffer;
	strCMD = lpstrCMD;
	strCMD.TrimLeft();
	strCMD.TrimRight();	
	strBuffer = pBuffer;
	if(strCMD == CMDVOA)          
	{
		if(!g_bPreFinished)
		{
			SendErrorMsg(s,2);
			return FALSE;						
		}
		g_answer = TRUE;
		token = strtok(pBuffer,szSpec);
		ASSERT(token);
        token = strtok(NULL,szSpec);
        strCMD =token;		
		strCMD.TrimRight();
		strCMD.TrimLeft();
		strCMD.MakeUpper();
		if(strCMD.CompareNoCase("SCLOSE")==0)
		{
			if(!CloseVOADevice(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
        else if(strCMD.CompareNoCase("SRESET")==0)
		{
			if(!ResetVOADevice(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
	    else if(strCMD.CompareNoCase("SWL")==0)
		{
			if(!SetVOAWavelength(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}	
	    else if(strCMD.CompareNoCase("GWL")==0)
		{
			if(!GetVOAWavelength(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
		else if(strCMD.CompareNoCase("SATTEN")==0)
		{
			if(!SetVOAAttenuation(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}			
		}
		else if(strCMD.CompareNoCase("GATTEN")==0)
		{
			if(!GetVOAAttenuation(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
		else if(strCMD.CompareNoCase("SENABLE")==0)
		{
			if(!SetVOAEnableOutput(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}	
		}
		else if(strCMD.CompareNoCase("SOFFSET")==0)
		{
			if(!SetVOAInputOffset(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}		
		}
		else if(strCMD.CompareNoCase("GSTATUS")==0)
		{
			if(!GetVOAStatus(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}			
		}
		else 
		{
			SendErrorMsg(s,-1);
		}
	}
	return TRUE;
}
void SendPOLInfo(SOCKET s)
{
	char szSendBuffer[256];
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"###############################POL Info##############################\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);

	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"POL SCLOSE 1 [channel] -- Set Pol clsoe\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"POL SRESET 1 [channel] -- Set Pol reset\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"POL GCURPOS 1 [channel] -- Get Pol current polarizer\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"POL SALL 4 [channel] [p] [q] [ahpla] -- Set Pol all angle\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"POL SDIAGANGLE 3 [channel] [DiagonalAngles] [WL] -- Set Pol diagonal angle\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"POL SHORANGLE 3 [channel] [HorizontalAngles] [WL] -- Set Pol horizontal angle\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"POL SHALFANGLE 2 [channel] [half] -- Set Pol half angle\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"POL SPOSANGLE 2 [channel] [POSPolarizer] -- Set Pol polarizer\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);	
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"POL SQUATERANGLE 2 [channel] [quaterangle] -- Set Pol quater angle\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"POL SRIGHTHANDANGLE 3 [channel] [righthandangle] [WL] -- Set Pol right hand angle\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"POL SVERTICALANGLE 3 [channel] [verticalangle] [WL] -- Set Pol vertical angle\r#");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
}
//////////////////////////////////////////POL Function//////////////////////////////////////
BOOL HandlePOLMsg(char* pBuffer,LPCSTR lpstrCMD,SOCKET s)
{
	char * token =NULL;
	char szSpec[] =" ";
	CString strCMD;
	CString strBuffer;
	strCMD = lpstrCMD;
	strCMD.TrimLeft();
	strCMD.TrimRight();
	strBuffer = pBuffer;
	if(strCMD == CMDPOL)          
	{
		if(!g_bPreFinished)
		{
			SendErrorMsg(s,2);
			return FALSE;						
		}
		g_answer = TRUE;
		token = strtok(pBuffer,szSpec);
		ASSERT(token);
        token = strtok(NULL,szSpec);
        strCMD =token;
		strCMD.TrimRight();
		strCMD.TrimLeft();
		strCMD.MakeUpper();
		if(strCMD.CompareNoCase("SCLOSE")==0)
		{
			if(!ClosePolDevice(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
        else if(strCMD.CompareNoCase("SRESET")==0)
		{
			if(!ResetPolDevice(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
	    else if(strCMD.CompareNoCase("GCURPOS")==0)
		{
			if(!GetPolCurrentPOSPolarizer(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}	
	    else if(strCMD.CompareNoCase("SALL")==0)
		{
			if(!SetPolALL(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
		else if(strCMD.CompareNoCase("SDIAGANGLE")==0)
		{
			if(!SetPolDiagonalAngles(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}			
		}
		else if(strCMD.CompareNoCase("SHORANGLE")==0)
		{
			if(!SetPolHorizontalAngles(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
		else if(strCMD.CompareNoCase("SHALFANGLE")==0)
		{
			if(!SetPolPOSHalf(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}	
		}
		else if(strCMD.CompareNoCase("SPOSANGLE")==0)
		{
			if(!SetPolPOSPolarizer(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}		
		}
		else if(strCMD.CompareNoCase("SQUATERANGLE")==0)
		{
			if(!SetPolPOSQuarter(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}			
		}
		else if(strCMD.CompareNoCase("SRIGHTHANDANGLE")==0)
		{
			if(!SetPolRightHandCircularAngles(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}			
		}
		else if(strCMD.CompareNoCase("SVERTICALANGLE")==0)
		{
			if(!SetPolVerticalAngles(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}			
		}
		else 
		{
			SendErrorMsg(s,-1);
		}
	}
	return TRUE;
}

void SendChamberInfo(SOCKET s)
{
	char szSendBuffer[256];
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"###############################Chamber Info##############################\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);

	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"CHAMBER SCLOSE 1 [channel] -- Set chamber clsoe\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"CHAMBER STOP 1 [channel] -- Set chamber run stop\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"CHAMBER SSTART 1 [channel] -- Set chamber run start\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"CHAMBER SPOINT 2 [channel] [point] -- Set chamber temperature point\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"CHAMBER GPOINT 1 [channel] -- Get chamber setting point\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"CHAMBER GTEMPERATURE 1 [channel] -- Get chamber current temperature\r#");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
}
//////////////////////////////////////Chamber function///////////////////////////////////
BOOL HandlechamberMsg(char* pBuffer,LPCSTR lpstrCMD,SOCKET s)
{
	char * token =NULL;
	char szSpec[] =" ";
	CString strCMD;
	CString strBuffer;
	strCMD = lpstrCMD;
	strCMD.TrimLeft();
	strCMD.TrimRight();
	strBuffer = pBuffer;
	if(strCMD == CMDCHAMBER)          
	{
		if(!g_bPreFinished)
		{
			SendErrorMsg(s,2);
			return FALSE;						
		}
		g_answer = TRUE;
		token = strtok(pBuffer,szSpec);
		ASSERT(token);
        token = strtok(NULL,szSpec);
        strCMD =token;
		strCMD.TrimRight();
		strCMD.TrimLeft();
		strCMD.MakeUpper();
		if(strCMD.CompareNoCase("SCLOSE")==0)
		{
			if(!CloseChamberDevice(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
        else if(strCMD.CompareNoCase("SSTOP")==0)
		{
			if(!SetChamberRunStop(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
	    else if(strCMD.CompareNoCase("SSTART")==0)
		{
			if(!SetChamberRunStart(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}	
	    else if(strCMD.CompareNoCase("SPOINT")==0)
		{
			if(!SetChamberSetPoint(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
		else if(strCMD.CompareNoCase("GPOINT")==0)
		{
			if(!GetChamberSetPoint(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}			
		}
		else if(strCMD.CompareNoCase("GTEMPERATURE")==0)
		{
			if(!GetChamberCurrentTemp(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
		else 
		{
			SendErrorMsg(s,-1);
		}
	}
	return TRUE;
}
void SendOSAInfo(SOCKET s)
{
	char szSendBuffer[256];
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"###############################OSA Info##############################\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);

	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"OSA SCLOSE 1 [channel] -- Set OSA clsoe\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"OSA SRESET 1 [channel] -- Set OSA reset\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"OSA SLOCALCTRL 1 [channel] -- Set OSA local control\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"OSA SRBW 2 [channel] [RBW] -- Set OSA RBW\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"OSA GRBW 1 [channel] -- Get OSA RBW\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"OSA SINIAMP 4 [channel] [StartWL] [EndWL] [RBW] -- Set OSA initial AMP test\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"OSA SAMPSOURCE 1 [channel] -- Set OSA amplifier source\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"OSA SAMP 2 [channel] [bSelfArithmetic(0|1)]-- Set OSA amplifier funcation\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"OSA GCHCOUNT 1 [channel] -- Get OSA channel count\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"OSA GCHWL 1 [channel] -- Get OSA channel wavelength\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"OSA GCHNF 1 [channel] -- Get OSA channel NF\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"OSA GCHGAIN 1 [channel] -- Get OSA channel gain\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"OSA GCHSNR 1 [channel] -- Get OSA channel SNR\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"OSA GCHSPOW 1 [channel] -- Get OSA channel source power\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"OSA SAPMOFFSET 3 [channel] [sourceoffset] [ampoffset] -- Set OSA amplifier offset\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"OSA GAMPOFFSET 1 [channel] -- Get OSA amplifier offset\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"OSA GEDFARESULT 1 [channel] -- Get OSA edfa result\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"OSA GEDFACHRESULT 1 [channel] -- Get OSA edfa channel result\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"OSA SINISWEEP 5 [channel] [startWL] [stopWL] [RBW] [pointcount]-- Set OSA initial sweep\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"OSA SRUNSWEEP 2 [channel] [szTrace] -- Set OSA run sweep\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"OSA GSWEEPPOINT 1 [channel] -- Get OSA sweep point count\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"OSA GSWEEPDATA 2 [channel] [szTrace] -- Get OSA sweep data\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"OSA SSAVEDATATOPC 5 [channel] [savepath] [datatype] [filetype] [seltrace] -- Set OSA save data to pc\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"OSA SCALIBRATE 1 [channel] -- Set OSA calibrate\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"OSA GZOOMVALUE 3 [channel] [WLNM] [RBWNM] -- Get OSA zoom value\r#");
	send(s,szSendBuffer,strlen(szSendBuffer),0);

}
/////////////////////////////////////////////////////OSA Function/////////////////////////////////
BOOL HandleOSAMsg(char* pBuffer,LPCSTR lpstrCMD,SOCKET s)
{
	char * token =NULL;
	char szSpec[] =" ";
	CString strCMD;
	CString strBuffer;
	strCMD = lpstrCMD;
	strCMD.TrimLeft();
	strCMD.TrimRight();
	strBuffer = pBuffer;
	if(strCMD == CMDOSA)          
	{
		if(!g_bPreFinished)
		{
			SendErrorMsg(s,2);
			return FALSE;						
		}
		g_answer = TRUE;
		token = strtok(pBuffer,szSpec);
		ASSERT(token);
        token = strtok(NULL,szSpec);
        strCMD =token;
		strCMD.TrimRight();
		strCMD.TrimLeft();
		strCMD.MakeUpper();
		if(strCMD.CompareNoCase("SCLOSE")==0)
		{
			if(!CloseOSADevice(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
        else if(strCMD.CompareNoCase("SRESET")==0)
		{
			if(!ResetOSADevice(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
	    else if(strCMD.CompareNoCase("SLOCALCTRL")==0)
		{
			if(!SetOSALocalCtrl(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}	
	    else if(strCMD.CompareNoCase("SRBW")==0)
		{
			if(!SetOSARBW(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
		else if(strCMD.CompareNoCase("GRBW")==0)
		{
			if(!GetOSARBW(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}			
		}
		else if(strCMD.CompareNoCase("SINIAMP")==0)
		{
			if(!InitOSAAmpTest(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
		else if(strCMD.CompareNoCase("SAMPSOURCE")==0)
		{
			if(!MeasureOSASource(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
		else if(strCMD.CompareNoCase("SAMP")==0)
		{
			if(!MeasureOSAAmplifier(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
		else if(strCMD.CompareNoCase("GCHCOUNT")==0)
		{
			if(!GetOSAChannelCount(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
		else if(strCMD.CompareNoCase("GCHWL")==0)
		{
			if(!GetOSAChannelWaveLens(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
		else if(strCMD.CompareNoCase("GCHNF")==0)
		{
			if(!GetOSAChannelNF(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
		else if(strCMD.CompareNoCase("GCHGAIN")==0)
		{
			if(!GetOSAChannelGain(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
		else if(strCMD.CompareNoCase("GCHSNR")==0)
		{
			if(!GetOSAChannelSNR(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
		else if(strCMD.CompareNoCase("GCHSPOW")==0)
		{
			if(!GetOSAChannelSourcePower(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
		else if(strCMD.CompareNoCase("SAPMOFFSET")==0)
		{
			if(!SetOSAAmpOffset(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
		else if(strCMD.CompareNoCase("GAMPOFFSET")==0)
		{
			if(!GetOSAAmpOffset(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
		else if(strCMD.CompareNoCase("GEDFARESULT")==0)
		{
			if(!GetOSAEDFAResult(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
		else if(strCMD.CompareNoCase("GEDFACHRESULT")==0)
		{
			if(!GetOSAEDFAChResult(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
		else if(strCMD.CompareNoCase("SINISWEEP")==0)
		{
			if(!InitOSASingleSweep(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
		else if(strCMD.CompareNoCase("SRUNSWEEP")==0)
		{
			if(!RunOSASweep(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
		else if(strCMD.CompareNoCase("GSWEEPPOINT")==0)
		{
			if(!GetSingleSweepPoint(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
		else if(strCMD.CompareNoCase("GSWEEPDATA")==0)
		{
			if(!GetOSASweepData(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
		else if(strCMD.CompareNoCase("SSAVEDATATOPC")==0)
		{
			if(!SaveOSADataToPC(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
		else if(strCMD.CompareNoCase("SCALIBRATE")==0)
		{
			if(!SetOSACalibration(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
		else if(strCMD.CompareNoCase("GZOOMVALUE")==0)
		{
			if(!GetZoomValue(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
		else 
		{
			SendErrorMsg(s,-1);
		}
	}
	return TRUE;
}
BOOL HandleDevMsg(char* pBuffer,LPCSTR lpstrCMD,SOCKET s)
{
	char * token =NULL;
	char szSpec[] =" ";
	CString strCMD;
	CString strBuffer;
	strCMD = lpstrCMD;
	strCMD.TrimLeft();
	strCMD.TrimRight();
	strBuffer = pBuffer;
	if(strCMD == CMDCOM)          
	{
		if(!g_bPreFinished)
		{
			SendErrorMsg(s,2);
			return FALSE;						
		}
		g_answer = TRUE;
		token = strtok(pBuffer,szSpec);
		ASSERT(token);
        token = strtok(NULL,szSpec);
        strCMD =token;
		strCMD.TrimRight();
		strCMD.TrimLeft();
		strCMD.MakeUpper();
		if(strCMD.CompareNoCase("SEND")==0)
		{
			g_bComSendFlag = TRUE;
			if(!ComWrite(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
        else if(strCMD.CompareNoCase("READ")==0)
		{
			g_bComRevFlag = TRUE;
			if(!ComRead(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
		else if(strCMD.CompareNoCase("SOPEN")==0)
		{
			if(!OpenCom(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
		else if(strCMD.CompareNoCase("SCLOSE")==0)
		{
			if(!CloseCom(strBuffer.GetBuffer(0),s))
			{
               return FALSE;
			}
		}
		else 
		{
			SendErrorMsg(s,-1);
		}
	}
	return TRUE;
}
