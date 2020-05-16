
#include "stdafx.h"
#include "FuctionHead.h"
#include "AFXMT.H"
extern CCriticalSection m_lockDevice;
extern UDLSERVERLib::IEngineMgrPtr m_pEngine;
extern UDLSERVERLib::IChamberInterfacePtr m_ChamberPtr;
extern UDLSERVERLib::IIOSAInterfacePtr m_OSAPtr;
extern UDLSERVERLib::IIPMInterfacePtr m_PMPtr;
extern UDLSERVERLib::IIPolInterfacePtr m_PolPtr;
extern UDLSERVERLib::IITLSInterfacePtr m_TLSPtr;
extern UDLSERVERLib::IIVOAInterfacePtr m_VOAPtr;
extern UDLSERVERLib::IIComDevInterfacePtr m_ComPtr;
extern UDLSERVERLib::IScanInterfacePtr m_ScanPtr;

extern BOOL m_bQuit;
extern char g_szAppFolder[MAX_PATH];
extern BOOL g_bPreFinished ;
extern BOOL g_bComSendFlag;
extern BOOL g_bComRevFlag;

////////////////////////////////Engine Function//////////////////////////////////
BOOL LoadConfigCMD(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;			
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;			
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;			
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,1);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
 	CString strTemp;
	strTemp = token;
	strTemp.TrimLeft();
	strTemp.TrimRight();
	char szFile[MAX_PATH];
	ZeroMemory(szFile,sizeof(char)*MAX_PATH);
	sprintf(szFile,"%s",strTemp);
	PrintRevMsg(strTemp);
	m_lockDevice.Lock();
	hresult = m_pEngine->LoadConfiguration((_bstr_t)szFile);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_pEngine->GetGetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"LoadXML Successfully\r\n#");
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL OpenDevice(SOCKET s)
{
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	if(!g_bPreFinished)
	{
		SendErrorMsg(s,2);
		return FALSE;						
	}
	m_lockDevice.Lock();
	hresult = m_pEngine->OpenEngine();
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{
		CString strMsg;
        strMsg = (LPCSTR)m_pEngine->GetGetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ));
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"Open device Successfully\r\n#");
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}

////////////////////////////////TLS Function//////////////////////////////////
BOOL SetTLSWavelength(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	double dbWL;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;			
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 2)
	{
		SendErrorMsg(s,3);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	dbWL =  atof(token);


	m_lockDevice.Lock();
	hresult = m_TLSPtr->SetTLSWavelength(nChIndex,dbWL);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_TLSPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OK!\r\n#");
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}

BOOL SetTLSSourcePower(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	double dbPower;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 2)
	{
		SendErrorMsg(s,5);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	dbPower =  atof(token);
	m_lockDevice.Lock();
	hresult = m_TLSPtr->SetTLSSourcePower(nChIndex,dbPower);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_TLSPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OK!\r\n#");
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}

BOOL SetTLSCoherenceControl(char *Buff,SOCKET s)
{

	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	int nEnable;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 2)
	{
		SendErrorMsg(s,6);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	nEnable =  atoi(token);
	m_lockDevice.Lock();
	hresult = m_TLSPtr->SetTLSCoherenceControl(nChIndex,nEnable);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_TLSPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OK!\r\n#");
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL SetTLSSourceUnit(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	int nUnit;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 2)
	{
		SendErrorMsg(s,7);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	nUnit =  atoi(token);
	m_lockDevice.Lock();
	hresult = m_TLSPtr->SetTLSSourceUnit(nChIndex,nUnit);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_TLSPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OK!\r\n#");
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL SetTLSParameters(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	int bLowSSE;
	double dblPower;
	double dblWavelength;

	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 4)
	{
		SendErrorMsg(s,8);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	bLowSSE =  atoi(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	dblPower =  atof(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	dblWavelength =  atof(token);

	m_lockDevice.Lock();
	hresult = m_TLSPtr->SetTLSParameters(nChIndex,bLowSSE,dblPower,dblWavelength);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_TLSPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OK!\r\n#");
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}

BOOL SetTLSOutputEnable(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	int bEnable;

	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 2)
	{
		SendErrorMsg(s,9);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	bEnable =  atoi(token);

	m_lockDevice.Lock();
	hresult = m_TLSPtr->SetTLSOutputEnable(nChIndex,bEnable);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_TLSPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OK!\r\n#");
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}

BOOL CloseTLSDevice(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,10);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	m_lockDevice.Lock();
	hresult = m_TLSPtr->CloseTLSDevice(nChIndex);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_TLSPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OK!\r\n#");
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
///////////////////////////PM Function////////////////////////////////////
BOOL GetPMUnit(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	long nUnit;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,11);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	m_lockDevice.Lock();
	hresult = m_PMPtr->GetUnit(nChIndex,&nUnit);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_PMPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"PM:Unit:%d\r\n#",nUnit);
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL GetPMAverageTime(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	double dblva;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,12);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	m_lockDevice.Lock();
	hresult = m_PMPtr->GetAverageTime(nChIndex,&dblva);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_PMPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"PM:AVG:%lf\r\n#",dblva);
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL GetPMWavelength(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	double dblva;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,13);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	m_lockDevice.Lock();
	hresult = m_PMPtr->GetWavelength(nChIndex,&dblva);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_PMPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"PM:WAV:%lf\r\n#",dblva);
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL ReadPower(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	double dblva;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,14);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	m_lockDevice.Lock();
	hresult = m_PMPtr->GetPower(nChIndex,&dblva);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_PMPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"PM:POW:%lf\r\n#",dblva);
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL SetPMUnit(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	int nUnit;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 2)
	{
		SendErrorMsg(s,15);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nUnit = atol(token);

	m_lockDevice.Lock();
	hresult = m_PMPtr->SetUnit(nChIndex,nUnit);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_PMPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OK!\r\n#");
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL SetPMWavelength(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	double dbWav;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 2)
	{
		SendErrorMsg(s,16);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    dbWav = atof(token);

    //printf("Set PM %d channel WL %lf",nChIndex,dbWav);
	m_lockDevice.Lock();
	hresult = m_PMPtr->SetWavelength(nChIndex,dbWav);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_PMPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OK!\r\n#");
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}

BOOL SetPMAverageTime(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	double dbAvgtime;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 2)
	{
		SendErrorMsg(s,17);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    dbAvgtime = atof(token);

	m_lockDevice.Lock();
	hresult = m_PMPtr->SetAverageTime(nChIndex,dbAvgtime);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_PMPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OK!\r\n#");
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL SetPMRangeMode(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	long lVal;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 2)
	{
		SendErrorMsg(s,18);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    lVal = atol(token);

	m_lockDevice.Lock();
	hresult = m_PMPtr->SetRangeMode(nChIndex,lVal);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_PMPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OK!\r\n#");
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL SetPMParameters(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	long lAutoRange;
	double dbWL;
	double dbavgtime;
	double dbRange;

	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 5)
	{
		SendErrorMsg(s,19);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    lAutoRange = atol(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    dbWL = atof(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    dbavgtime = atof(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    dbRange = atof(token);

	m_lockDevice.Lock();
	hresult = m_PMPtr->SetParameters(nChIndex,lAutoRange,dbWL,dbavgtime,dbRange);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_PMPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OK!\r\n#");
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL ClosePMDevice(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,20);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	m_lockDevice.Lock();
	hresult = m_PMPtr->CloseDevice(nChIndex);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_PMPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OK!\r\n#");
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL GetPMRangeMode(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	long lRangeMode;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,21);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	m_lockDevice.Lock();
	hresult = m_PMPtr->GetRangeMode(nChIndex,&lRangeMode);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_PMPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"PM:RANGEMODE:%ld\r\n#",lRangeMode);
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL SetPMZero(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,22);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	m_lockDevice.Lock();
	hresult = m_PMPtr->SetZero(nChIndex);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_PMPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OK!\r\n#");
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL SetPMMaxMinPowerStart(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,23);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	m_lockDevice.Lock();
	hresult = m_PMPtr->SetPMMaxMinPowerStart(nChIndex);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_PMPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OK!\r\n#");
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL GetPMMaxMinPower(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	double dbMax;
	double dbMin;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,24);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	m_lockDevice.Lock();
	hresult = m_PMPtr->GetPMMaxMinPower(nChIndex,&dbMax,&dbMin);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_PMPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"PM:MAXMINPOW:%lf,%lf\r\n#",dbMax,dbMin);
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL SetPMMaxMinPowerStop(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,25);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	m_lockDevice.Lock();
	hresult = m_PMPtr->SetPMMaxMinPowerStop(nChIndex);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_PMPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OK!\r\n#");
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
/////////////////////////VOA Function////////////////////////////////////////
BOOL CloseVOADevice(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,26);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	m_lockDevice.Lock();
	hresult = m_VOAPtr->CloseVOADevice(nChIndex);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_VOAPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OK!\r\n#");
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL ResetVOADevice(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,27);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	m_lockDevice.Lock();
	hresult = m_VOAPtr->ResetVOADevice(nChIndex);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_VOAPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OK!\r\n#");
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL SetVOAWavelength(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	double dbWL;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 2)
	{
		SendErrorMsg(s,28);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    dbWL = atof(token);	
	m_lockDevice.Lock();
	hresult = m_VOAPtr->SetVOAWavelength(nChIndex,dbWL);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_VOAPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OK!\r\n#");
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL GetVOAWavelength(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	double dbWL;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,29);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	m_lockDevice.Lock();
	hresult = m_VOAPtr->GetVOAWavelength(nChIndex,&dbWL);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_VOAPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"VOA:WAV:%lf\r\n#",dbWL);
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL SetVOAAttenuation(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	double dbAtten;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 2)
	{
		SendErrorMsg(s,30);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    dbAtten = atof(token);	
	
	m_lockDevice.Lock();
	hresult = m_VOAPtr->SetVOAAttenuation(nChIndex,dbAtten);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_VOAPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OK!\r\n#");
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL GetVOAAttenuation(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	double dbVal;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,31);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	m_lockDevice.Lock();
	hresult = m_VOAPtr->GetVOAAttenuation(nChIndex,&dbVal);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_VOAPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	sprintf(szSendBuffer,"VOA:ATT:%lf\r\n#",dbVal);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL SetVOAEnableOutput(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	long lVal;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 2)
	{
		SendErrorMsg(s,32);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    lVal = atol(token);	
	m_lockDevice.Lock();
	hresult = m_VOAPtr->SetVOAEnableOutput(nChIndex,lVal);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_VOAPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	sprintf(szSendBuffer,"OK!\r\n#");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL SetVOAInputOffset(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	long lVal;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 2)
	{
		SendErrorMsg(s,33);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    lVal = atol(token);	
	
	m_lockDevice.Lock();
	hresult = m_VOAPtr->SetVOAInputOffset(nChIndex,lVal);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_VOAPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	sprintf(szSendBuffer,"OK!\r\n#");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL GetVOAStatus(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	long lVal=0;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,31);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	m_lockDevice.Lock();
	hresult = m_VOAPtr->GetVOAStatus(nChIndex,&lVal);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_VOAPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	sprintf(szSendBuffer,"VOA:STATUS:%ld\r\n#",lVal);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}

///////////////////////////////////PDL Function///////////////////////////////
BOOL ClosePolDevice(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,34);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	m_lockDevice.Lock();
	hresult = m_PolPtr->ClosePolDevice(nChIndex);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_PolPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	sprintf(szSendBuffer,"OK!\r\n#");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL ResetPolDevice(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,35);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	m_lockDevice.Lock();
	hresult = m_PolPtr->ResetPolDevice(nChIndex);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_PolPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	sprintf(szSendBuffer,"OK!\r\n#");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL GetPolCurrentPOSPolarizer(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	double dbP=0.0;
	double dbQ=0.0;
	double dbalpha=0.0;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,36);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	m_lockDevice.Lock();
	hresult = m_PolPtr->GetPolCurrentPOSPolarizer(nChIndex,&dbP,&dbQ,&dbalpha);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_PolPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	sprintf(szSendBuffer,"POL:POS:%lf,%lf,%lf\r\n#",dbP,dbQ,dbalpha);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL SetPolALL(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	double dbP;
	double dbQ;
	double dbAlpha;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 4)
	{
		SendErrorMsg(s,37);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    dbP = atof(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    dbQ = atof(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    dbAlpha = atof(token);

	m_lockDevice.Lock();
	hresult = m_PolPtr->SetPolALL(nChIndex,dbP,dbQ,dbAlpha);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_PolPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	sprintf(szSendBuffer,"OK!\r\n#");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL SetPolDiagonalAngles(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	double dbPMax;
	double dbWL;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 3)
	{
		SendErrorMsg(s,38);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    dbPMax = atof(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    dbWL = atof(token);

	m_lockDevice.Lock();
	hresult = m_PolPtr->SetPolDiagonalAngles(nChIndex,dbPMax,dbWL);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_PolPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	sprintf(szSendBuffer,"OK!\r\n#");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL SetPolHorizontalAngles(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	double dbPMax;
	double dbWL;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 3)
	{
		SendErrorMsg(s,39);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    dbPMax = atof(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    dbWL = atof(token);

	m_lockDevice.Lock();
	hresult = m_PolPtr->SetPolHorizontalAngles(nChIndex,dbPMax,dbWL);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_PolPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	sprintf(szSendBuffer,"OK!\r\n#");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL SetPolPOSHalf(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	double dbPMax;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 2)
	{
		SendErrorMsg(s,40);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    dbPMax = atof(token);

	m_lockDevice.Lock();
	hresult = m_PolPtr->SetPolPOSHalf(nChIndex,dbPMax);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_PolPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	sprintf(szSendBuffer,"OK!\r\n#");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL SetPolPOSPolarizer(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	double dbPMax;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 2)
	{
		SendErrorMsg(s,41);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    dbPMax = atof(token);

	m_lockDevice.Lock();
	hresult = m_PolPtr->SetPolPOSPolarizer(nChIndex,dbPMax);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_PolPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	sprintf(szSendBuffer,"OK!\r\n#");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL SetPolPOSQuarter(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	double dbPMax;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 2)
	{
		SendErrorMsg(s,42);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    dbPMax = atof(token);

	m_lockDevice.Lock();
	hresult = m_PolPtr->SetPolPOSQuarter(nChIndex,dbPMax);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_PolPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	sprintf(szSendBuffer,"OK!\r\n#");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL SetPolRightHandCircularAngles(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	double dbPMax;
	double dbWL;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 3)
	{
		SendErrorMsg(s,43);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    dbPMax = atof(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    dbWL = atof(token);

	m_lockDevice.Lock();
	hresult = m_PolPtr->SetPolRightHandCircularAngles(nChIndex,dbPMax,dbWL);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_PolPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	sprintf(szSendBuffer,"OK!\r\n#");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL SetPolVerticalAngles(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	double dbPMax;
	double dbWL;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 3)
	{
		SendErrorMsg(s,44);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    dbPMax = atof(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    dbWL = atof(token);

	m_lockDevice.Lock();
	hresult = m_PolPtr->SetPolVerticalAngles(nChIndex,dbPMax,dbWL);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_PolPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	sprintf(szSendBuffer,"OK!\r\n#");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}

/////////////////////////////////////Chamber Funcation///////////////////////////
BOOL  CloseChamberDevice(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,45);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	m_lockDevice.Lock();
	hresult = m_ChamberPtr->CloseChamberDevice(nChIndex);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_ChamberPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	sprintf(szSendBuffer,"OK!\r\n#");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL  SetChamberRunStop(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,46);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	m_lockDevice.Lock();
	hresult = m_ChamberPtr->SetChamberRunStop(nChIndex);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_ChamberPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	sprintf(szSendBuffer,"OK!\r\n#");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL  SetChamberRunStart(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,47);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	m_lockDevice.Lock();
	hresult = m_ChamberPtr->SetChamberRunStart(nChIndex);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_ChamberPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	sprintf(szSendBuffer,"OK!\r\n#");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL  SetChamberSetPoint(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	double dbVal;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 2)
	{
		SendErrorMsg(s,48);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    dbVal = atof(token);

	m_lockDevice.Lock();
	hresult = m_ChamberPtr->SetChamberSetPoint(nChIndex,dbVal);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_ChamberPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	sprintf(szSendBuffer,"OK!\r\n#");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL  GetChamberSetPoint(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	double dbVal;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,49);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	m_lockDevice.Lock();
	hresult = m_ChamberPtr->GetChamberSetPoint(nChIndex,&dbVal);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_ChamberPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	sprintf(szSendBuffer,"CHAMBER:POINT:%lf\r\n#",dbVal);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL  GetChamberCurrentTemp(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	double dbVal;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,50);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	m_lockDevice.Lock();
	hresult = m_ChamberPtr->GetChamberCurrentTemp(nChIndex,&dbVal);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_ChamberPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	sprintf(szSendBuffer,"CHAMBER:TEMP:%lf\r\n#",dbVal);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;	
}

///////////////////////////////////OSA Funcation/////////////////////////////////
BOOL CloseOSADevice(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,51);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	m_lockDevice.Lock();
	hresult = m_OSAPtr->CloseDevice(nChIndex);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_OSAPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OK!\r\n#");
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL ResetOSADevice(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,52);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	m_lockDevice.Lock();
	hresult = m_OSAPtr->ResetDevice(nChIndex);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_OSAPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OK!\r\n#");
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL SetOSALocalCtrl(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,53);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	m_lockDevice.Lock();
	hresult = m_OSAPtr->SetOSALocalCtrl(nChIndex);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_OSAPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OK!\r\n#");
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);

	return TRUE;
}
BOOL SetOSARBW(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	double dbVal;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 2)
	{
		SendErrorMsg(s,54);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    dbVal = atof(token);
	
	m_lockDevice.Lock();
	hresult = m_OSAPtr->SetOSARBW(nChIndex,dbVal);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_OSAPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OK!\r\n#");
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL GetOSARBW(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	double dbVal;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,55);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);
	
	m_lockDevice.Lock();
	hresult = m_OSAPtr->GetOSARBW(nChIndex,&dbVal);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_OSAPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OSA:RBW:%lf\r\n#",dbVal);
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;	
}
BOOL InitOSAAmpTest(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	double dbStartWL;
	double dbStopWL;
	double dbRBW;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 4)
	{
		SendErrorMsg(s,56);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);
	
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    dbStartWL = atof(token);
	
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    dbStopWL = atof(token);
	
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    dbRBW = atof(token);
	
	m_lockDevice.Lock();
	hresult = m_OSAPtr->InitOSAAmpTest(nChIndex,dbStartWL,dbStopWL,dbRBW);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_OSAPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OK!\r\n#");
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL MeasureOSASource(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;

	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,57);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);
	
	m_lockDevice.Lock();
	hresult = m_OSAPtr->MeasureSource(nChIndex);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_OSAPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OK!\r\n#");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	PrintRevMsg(szSendBuffer);
	return TRUE;
}
BOOL MeasureOSAAmplifier(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
    long lScanSrc=0;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 2)
	{
		SendErrorMsg(s,58);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    lScanSrc = atol(token);
	
	m_lockDevice.Lock();
	hresult = m_OSAPtr->MeasureAmplifier(nChIndex,lScanSrc);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_OSAPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OK!\r\n#");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	PrintRevMsg(szSendBuffer);
	return TRUE;
}
BOOL GetOSAChannelCount(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
    long lVal=0;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,59);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);
	
	m_lockDevice.Lock();
	hresult = m_OSAPtr->GetOSAChannelCount(nChIndex,&lVal);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_OSAPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	if(lVal > 256)
	{
        strMsg.Format("Get Channel count more than 256");
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;		
	}
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OSA:CHAN:COUNT:%ld\r\n#",lVal);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	PrintRevMsg(szSendBuffer);
	return TRUE;
}

BOOL GetOSAChannelWaveLens(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
    double pdbWL[256];
	unsigned long lPointCount;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,59);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);
	lPointCount = 0;
	m_lockDevice.Lock();
	hresult = m_OSAPtr->GetChannelWaveLens(nChIndex,pdbWL,&lPointCount);
	m_lockDevice.Unlock();

	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_OSAPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	if(lPointCount > 256)
	{
        strMsg.Format("Get Channel count more than 256");
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;		
	}
    strTemp.Empty();
	for(int nIndex=0;nIndex<lPointCount;nIndex++)
	{
		ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
		sprintf(szSendBuffer,"%lf,",pdbWL[nIndex]);
        strTemp +=szSendBuffer;
	}
	strTemp +="\r\n#";
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OSA:CH:WLCOUNT:%ld,%ld\r",lPointCount,strTemp.GetLength());
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,32,0);
	SendBufferBy1M(s,strTemp.GetBuffer(0),strTemp.GetLength());
	strTemp.ReleaseBuffer(0);
	return TRUE;

}
BOOL GetOSAChannelNF(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
    double pdbVal[256];
	unsigned long lPointCount;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,59);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);
	lPointCount = 0;
	m_lockDevice.Lock();
	hresult = m_OSAPtr->GetChannelNF(nChIndex,pdbVal,&lPointCount);
	m_lockDevice.Unlock();

	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_OSAPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	if(lPointCount > 256)
	{
        strMsg.Format("Get Channel count more than 256");
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;		
	}
    strTemp.Empty();
	for(int nIndex=0;nIndex<lPointCount;nIndex++)
	{
		ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
		sprintf(szSendBuffer,"%lf,",pdbVal[nIndex]);
        strTemp +=szSendBuffer;
	}
	strTemp +="\r\n#";
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OSA:CH:NFCOUNT:%ld,%ld\r",lPointCount,strTemp.GetLength());
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,32,0);
	SendBufferBy1M(s,strTemp.GetBuffer(0),strTemp.GetLength());
	strTemp.ReleaseBuffer(0);
	return TRUE;
}
BOOL GetOSAChannelGain(char *Buff,SOCKET s)
{
 	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
    double pdbVal[256];
	unsigned long lPointCount;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,59);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);
	lPointCount = 0;
	m_lockDevice.Lock();
	hresult = m_OSAPtr->GetChannelGain(nChIndex,pdbVal,&lPointCount);
	m_lockDevice.Unlock();

	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_OSAPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	if(lPointCount > 256)
	{
        strMsg.Format("Get Channel count more than 256");
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;		
	}
    strTemp.Empty();
	for(int nIndex=0;nIndex<lPointCount;nIndex++)
	{
		ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
		sprintf(szSendBuffer,"%lf,",pdbVal[nIndex]);
        strTemp +=szSendBuffer;
	}
	strTemp +="\r\n#";
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OSA:CH:GAINCOUNT:%ld,%ld\r",lPointCount,strTemp.GetLength());
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,32,0);
	SendBufferBy1M(s,strTemp.GetBuffer(0),strTemp.GetLength());
	strTemp.ReleaseBuffer(0);
	return TRUE;
}
BOOL GetOSAChannelSNR(char *Buff,SOCKET s)
{
    char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
    double pdbVal[256];
	unsigned long lPointCount;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,59);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);
	lPointCount = 0;
	m_lockDevice.Lock();
	hresult = m_OSAPtr->GetChannelSNR(nChIndex,pdbVal,&lPointCount);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_OSAPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	if(lPointCount > 256)
	{
        strMsg.Format("Get Channel count more than 256");
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;		
	}
	strTemp.Empty();
	for(int nIndex=0;nIndex<lPointCount;nIndex++)
	{
		ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
		sprintf(szSendBuffer,"%lf,",pdbVal[nIndex]);
        strTemp +=szSendBuffer;
	}
	strTemp +="\r\n#";
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OSA:CH:SNRCOUNT:%ld,%ld\r",lPointCount,strTemp.GetLength());
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,32,0);
	SendBufferBy1M(s,strTemp.GetBuffer(0),strTemp.GetLength());
	strTemp.ReleaseBuffer(0);
	return TRUE;
}
BOOL GetOSAChannelSourcePower(char *Buff,SOCKET s)
{
    char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
    double pdbVal[256];
	unsigned long lPointCount;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,59);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);
	lPointCount = 0;
	m_lockDevice.Lock();
	hresult = m_OSAPtr->GetChannelSourcePower(nChIndex,pdbVal,&lPointCount);
	m_lockDevice.Unlock();

	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_OSAPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	if(lPointCount > 256)
	{
        strMsg.Format("Get Channel count more than 256");
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;		
	}
	strTemp.Empty();
	for(int nIndex=0;nIndex<lPointCount;nIndex++)
	{
		ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
		sprintf(szSendBuffer,"%lf,",pdbVal[nIndex]);
        strTemp +=szSendBuffer;
	}
	strTemp +="\r\n#";
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OSA:CH:POWCOUNT:%ld,%ld\r",lPointCount,strTemp.GetLength());
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,32,0);
	SendBufferBy1M(s,strTemp.GetBuffer(0),strTemp.GetLength());
	strTemp.ReleaseBuffer(0);
	
	return TRUE;
}
BOOL SetOSAAmpOffset(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
    double dbSourceOffset=0.0;
	double dbAmpOffset =0.0;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 3)
	{
		SendErrorMsg(s,60);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    dbSourceOffset = atof(token);
	
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    dbAmpOffset = atof(token);

	m_lockDevice.Lock();
	hresult = m_OSAPtr->SetOSAAmpOffset(nChIndex,dbSourceOffset,dbAmpOffset);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_OSAPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
    ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OK!\r\n#");
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL GetOSAAmpOffset(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
    double dbSourceOffset=0.0;
	double dbAmpOffset =0.0;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,61);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	m_lockDevice.Lock();
	hresult = m_OSAPtr->GetOSAAmpOffset(nChIndex,&dbSourceOffset,&dbAmpOffset);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_OSAPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OSA:AMP:OFFSET:%lf,%lf\r\n#",dbSourceOffset,dbAmpOffset);
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL GetOSAEDFAResult(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
    double dbSourcePower;
	double dbAmpPower;
	double dbSumGain;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,68);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	m_lockDevice.Lock();
	hresult = m_OSAPtr->GetOSAEDFAResult(nChIndex,&dbSourcePower,&dbAmpPower,&dbSumGain);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_OSAPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OSA:AMP:RESULT:%lf,%lf,%lf\r\n#",dbSourcePower,dbAmpPower,dbSumGain);
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL GetOSAEDFAChResult(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	long lPointCount;
    long lChCount;
	double * pdbWLArry=NULL;
	double * pdbSrcPower =NULL;
	double * pdbGainArry =NULL;
	double * pdbNFArry =NULL;
	double * pdbASEArry =NULL;
	double * pdbGainFlatness =NULL;
	double dbMaxNF;
	double dbMaxGain;
	double dbMinGain;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,68);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);
	m_lockDevice.Lock();
	hresult = m_OSAPtr->GetOSAChannelCount(nChIndex,&lPointCount);
	m_lockDevice.Unlock();
	pdbWLArry= (double*)VirtualAlloc(NULL,sizeof(double)*lPointCount,MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	pdbSrcPower =(double*)VirtualAlloc(NULL,sizeof(double)*lPointCount,MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	pdbGainArry =(double*)VirtualAlloc(NULL,sizeof(double)*lPointCount,MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	pdbNFArry =(double*)VirtualAlloc(NULL,sizeof(double)*lPointCount,MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	pdbASEArry =(double*)VirtualAlloc(NULL,sizeof(double)*lPointCount,MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	pdbGainFlatness =(double*)VirtualAlloc(NULL,sizeof(double)*lPointCount,MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	m_lockDevice.Lock();
	hresult = m_OSAPtr->GetOSAEDFAChResult(nChIndex,&lChCount,pdbWLArry,pdbSrcPower,pdbGainArry,pdbNFArry,pdbASEArry,pdbGainFlatness,&dbMaxNF,&dbMaxGain,&dbMinGain);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_OSAPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );

	if(lPointCount > 256)
	{
        strMsg.Format("Get Channel count more than 256");
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;		
	}
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OSA:AMP:CHCOUNT:%ld\r",lChCount);
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,32,0);
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OSA:AMP:MaxNF:%.5f\r",dbMaxNF);
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,32,0);
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OSA:AMP:MaxGain:%.5f\r",dbMaxGain);
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,32,0);
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OSA:AMP:MinGain:%.5f\r",dbMinGain);
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,32,0);
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OSA:AMP:GainFlatness:%.5f\r",dbMinGain);
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,32,0);

	//发送波长
	strTemp.Empty();
	for(int nIndex=0;nIndex<lChCount;nIndex++)
	{
		ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
		sprintf(szSendBuffer,"%.5f,",pdbWLArry[nIndex]);
        strTemp +=szSendBuffer;
	}
	strTemp +="\r\n#";
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OSA:CH:WL:%ld,%ld\r",lChCount,strTemp.GetLength());
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,32,0);
	SendBufferBy1M(s,strTemp.GetBuffer(0),strTemp.GetLength());
	strTemp.ReleaseBuffer(0);

	//发送功率
	strTemp.Empty();
	for(nIndex=0;nIndex<lChCount;nIndex++)
	{
		ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
		sprintf(szSendBuffer,"%.5f,",pdbSrcPower[nIndex]);
        strTemp +=szSendBuffer;
	}
	strTemp +="\r\n#";
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OSA:CH:POW:%ld,%ld\r",lChCount,strTemp.GetLength());
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,32,0);
	SendBufferBy1M(s,strTemp.GetBuffer(0),strTemp.GetLength());
	strTemp.ReleaseBuffer(0);

	//发送Gain
	strTemp.Empty();
	for(nIndex=0;nIndex<lChCount;nIndex++)
	{
		ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
		sprintf(szSendBuffer,"%.5f,",pdbGainArry[nIndex]);
        strTemp +=szSendBuffer;
	}
	strTemp +="\r\n#";
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OSA:CH:GAIN:%ld,%ld\r",lChCount,strTemp.GetLength());
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,32,0);
	SendBufferBy1M(s,strTemp.GetBuffer(0),strTemp.GetLength());
	strTemp.ReleaseBuffer(0);

	//发送NF
	strTemp.Empty();
	for(nIndex=0;nIndex<lChCount;nIndex++)
	{
		ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
		sprintf(szSendBuffer,"%.5f,",pdbNFArry[nIndex]);
        strTemp +=szSendBuffer;
	}
	strTemp +="\r\n#";
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OSA:CH:NF:%ld,%ld\r",lChCount,strTemp.GetLength());
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,32,0);
	SendBufferBy1M(s,strTemp.GetBuffer(0),strTemp.GetLength());
	strTemp.ReleaseBuffer(0);

	//发送ASE
	strTemp.Empty();
	for(nIndex=0;nIndex<lChCount;nIndex++)
	{
		ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
		sprintf(szSendBuffer,"%.5f,",pdbASEArry[nIndex]);
        strTemp +=szSendBuffer;
	}
	strTemp +="\r\n#";
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OSA:CH:ASE:%ld,%ld\r",lChCount,strTemp.GetLength());
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,32,0);
	SendBufferBy1M(s,strTemp.GetBuffer(0),strTemp.GetLength());
	strTemp.ReleaseBuffer(0);

	VirtualFree(pdbWLArry,0,MEM_RELEASE);
	VirtualFree(pdbSrcPower,0,MEM_RELEASE);
	VirtualFree(pdbGainArry,0,MEM_RELEASE);
	VirtualFree(pdbNFArry,0,MEM_RELEASE);
	VirtualFree(pdbASEArry,0,MEM_RELEASE);
	VirtualFree(pdbGainFlatness,0,MEM_RELEASE);

	return TRUE;
}
BOOL InitOSASingleSweep(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
    double dbStartWL;
	double dbStopWL;
	double dbRBW;
	long lSweepPoint;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 5)
	{
		SendErrorMsg(s,62);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    dbStartWL = atof(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    dbStopWL = atof(token);

    token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    dbRBW = atof(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    lSweepPoint = atol(token);

	m_lockDevice.Lock();
	hresult = m_OSAPtr->InitOSASingleSweep(nChIndex,dbStartWL,dbStopWL,dbRBW,lSweepPoint);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_OSAPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OK!\r\n#");
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}

BOOL RunOSASweep(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
    CString strTrac;
	double * pdbWLArry = NULL;
	double * pdbPowerArry = NULL;
	long lSweepPoint;

	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 2)
	{
		SendErrorMsg(s,63);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    strTrac = token;

	m_lockDevice.Lock();
	m_OSAPtr->GetOSASingleSweepPoint(nChIndex,&lSweepPoint);
	m_lockDevice.Unlock();

	pdbWLArry = (double*)VirtualAlloc(NULL,sizeof(double)*lSweepPoint,MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	pdbPowerArry = (double*)VirtualAlloc(NULL,sizeof(double)*lSweepPoint,MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	
	m_lockDevice.Lock();
	hresult = m_OSAPtr->RunOSASweep(nChIndex,pdbWLArry,pdbPowerArry,(_bstr_t)strTrac);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_OSAPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
    //发送波长
	strTemp.Empty();
	for(int nIndex=0;nIndex<lSweepPoint;nIndex++)
	{
		ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
		sprintf(szSendBuffer,"%.4f,",pdbWLArry[nIndex]);
        strTemp +=szSendBuffer;
	}
	strTemp +="\r\n#";
	
	char *pszBuffer = strTemp.GetBuffer(0);
	int length= strTemp.GetLength();
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OSA:SWEEP:WL:%ld,%ld\r",lSweepPoint,length);
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,32,0);
	SendBufferBy1M(s,pszBuffer,length);
//	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
//	sprintf(szSendBuffer,"\r\n#");
//	PrintRevMsg(szSendBuffer);
	
	//发送功率
	strTemp.Empty();
	for(nIndex=0;nIndex<lSweepPoint;nIndex++)
	{
		ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
		sprintf(szSendBuffer,"%.4f,",pdbPowerArry[nIndex]);
        strTemp +=szSendBuffer;
	}
	strTemp +="\r\n#";
	pszBuffer = strTemp.GetBuffer(0);
	length = strTemp.GetLength();
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OSA:SWEEP:POW:%ld,%ld\r",lSweepPoint,length);
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,32,0);
	SendBufferBy1M(s,pszBuffer,length);
    
//	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
//	sprintf(szSendBuffer,"\r\n#");
//	PrintRevMsg(szSendBuffer);

	VirtualFree(pdbWLArry,0,MEM_RELEASE);
	pdbWLArry = NULL;
	VirtualFree(pdbPowerArry,0,MEM_RELEASE);
	pdbPowerArry = NULL;
	return TRUE;
}

BOOL GetSingleSweepPoint(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
    long lPointCount;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,67);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	m_lockDevice.Lock();
	hresult = m_OSAPtr->GetOSASingleSweepPoint(nChIndex,&lPointCount);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_OSAPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OSA:SWEEP:COUNT:%ld\r\n#",lPointCount);
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL GetOSASweepData(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	CString strSelTrace;
    double * pdbWL =NULL;
	double * pdPower=NULL;
	long lPointCount;

	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 2)
	{
		SendErrorMsg(s,69);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    strSelTrace = token;
	
	m_lockDevice.Lock();
	hresult = m_OSAPtr->GetOSASingleSweepPoint(nChIndex,&lPointCount);
	m_lockDevice.Unlock();
	
    pdbWL = (double*)VirtualAlloc(NULL,sizeof(double)*lPointCount,MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	pdPower = (double*)VirtualAlloc(NULL,sizeof(double)*lPointCount,MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	m_lockDevice.Lock();
	hresult = m_OSAPtr->GetOSASweepData(nChIndex,pdbWL,pdPower,(_bstr_t)strSelTrace);
	m_lockDevice.Unlock();

	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_OSAPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
    //发送波长
	strTemp.Empty();
	for(int nIndex=0;nIndex<lPointCount;nIndex++)
	{
		ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
		sprintf(szSendBuffer,"%.4f,",pdbWL[nIndex]);
        strTemp +=szSendBuffer;
	}
	strTemp +="\r#";
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OSA:SWEEP:WL:%ld,%ld\r",lPointCount,strTemp.GetLength());
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,32,0);
	SendBufferBy1M(s,strTemp.GetBuffer(0),strTemp.GetLength());
	strTemp.ReleaseBuffer(0);
	
	//发送功率
	strTemp.Empty();
	for(nIndex=0;nIndex<lPointCount;nIndex++)
	{
		ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
		sprintf(szSendBuffer,"%.4f,",pdPower[nIndex]);
        strTemp +=szSendBuffer;
	}
	strTemp +="\r\n#";
	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OSA:SWEEP:POW:%ld,%ld\r",lPointCount,strTemp.GetLength());
	PrintRevMsg(szSendBuffer);
	send(s,szSendBuffer,32,0);
	SendBufferBy1M(s,strTemp.GetBuffer(0),strTemp.GetLength());
	strTemp.ReleaseBuffer(0);

	VirtualFree(pdbWL,0,MEM_RELEASE);
	pdbWL = NULL;
	VirtualFree(pdPower,0,MEM_RELEASE);
	pdPower = NULL;
	return TRUE;
}
BOOL SaveOSADataToPC(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
    CString strSavePath;
	CString strDataType;
	CString strFileTye;
	CString strSelTrace;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 5)
	{
		SendErrorMsg(s,64);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    strSavePath = token;

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    strDataType = token;

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    strFileTye = token;

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    strSelTrace = token;

	m_lockDevice.Lock();
	hresult = m_OSAPtr->SaveOSADataToPC(nChIndex,(_bstr_t)strSavePath,(_bstr_t)strDataType,(_bstr_t)strFileTye,(_bstr_t)strSelTrace);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_OSAPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	sprintf(szSendBuffer,"OK!\r\n#");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL SetOSACalibration(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	long lType;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 2)
	{
		SendErrorMsg(s,65);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    lType = atol(token);
	m_lockDevice.Lock();
	hresult = m_OSAPtr->SetOSACalibration(nChIndex,lType);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_OSAPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	sprintf(szSendBuffer,"OK!\r\n#");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL GetZoomValue(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	double dbWLNM;
	double dbRBWNM;
	double dbVal;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 3)
	{
		SendErrorMsg(s,66);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    dbWLNM = atof(token);

    token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    dbRBWNM = atof(token);

	m_lockDevice.Lock();
	hresult = m_OSAPtr->GetOSAZoomValue(nChIndex,dbWLNM,dbRBWNM,&dbVal);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        strMsg = (LPCSTR)m_OSAPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r\n#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	sprintf(szSendBuffer,"OSA:ZOOM:%lf\r\n#",dbVal);
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
///////////////////////////////////////Serial Function/////////////////////////////////
void SendComInfo(SOCKET s)
{
    char szSendBuffer[256];
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"###############################Comunication Info##############################\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);

	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"COM SEND 3 [channel] [length] [context] -- Send context\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"COM READ 2 [channel] [length] -- Read context\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);

	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"COM SOPEN 1 [channel] -- Open\r");
	send(s,szSendBuffer,strlen(szSendBuffer),0);

	ZeroMemory(szSendBuffer,sizeof(char)*256);
	sprintf(szSendBuffer,"COM SCLOSE 1 [channel] -- Close\r#");
	send(s,szSendBuffer,strlen(szSendBuffer),0);

}
BOOL OpenCom(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,71);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	m_lockDevice.Lock();
	hresult = m_ComPtr->OpenSerial(nChIndex);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        //strMsg = (LPCSTR)m_ComPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	sprintf(szSendBuffer,"OK!\r#");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL CloseCom(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 1)
	{
		SendErrorMsg(s,70);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	m_lockDevice.Lock();
	hresult = m_ComPtr->CloseSerial(nChIndex);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
        //strMsg = (LPCSTR)m_ComPtr->GetLastMessage();
		sprintf(szSendBuffer,"%s\r#",strMsg);
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
	ASSERT( SUCCEEDED( hresult ) );
	sprintf(szSendBuffer,"OK!\r#");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	return TRUE;
}
BOOL ComWrite(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	CString strMsg;
	CString strTemp;
	int nChIndex;
	stComParam stParm;
	strTemp = Buff;
    token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 3)
	{
		SendErrorMsg(s,71);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);
	stParm.lChIndex = nChIndex;
	stParm.s = s;

	CWinThread *thread;
	thread = AfxBeginThread(COMSendThread,(LPVOID)&stParm);
	WaitForSingleObject(thread->m_hThread,INFINITE);
    ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"OK!\r#");
	send(s,szSendBuffer,strlen(szSendBuffer),0);
	
	return TRUE;
}
BOOL ComRead(char *Buff,SOCKET s)
{
	char *token =NULL;
	char szSpec[] =" ";
	char szSendBuffer[MAX_PATH];
	HRESULT hresult;
	CString strMsg;
	CString strTemp;
	int nChIndex;
    unsigned long nReadLength;
	token = strtok(Buff,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
	ASSERT(token);
	int nParam = atoi(token);
	if(nParam != 2)
	{
		SendErrorMsg(s,72);
		return FALSE;
	}
	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nChIndex = atol(token);

	token = strtok(NULL,szSpec);
	if(token==NULL)
	{
        SendErrorMsg(s,4);
		return FALSE;		
	}
    nReadLength = atol(token);
    
	//开始接收数据	
	m_lockDevice.Lock();
	BSTR pValue;
 
	hresult = m_ComPtr->ReadBuffer(nChIndex,&pValue,nReadLength);
	m_lockDevice.Unlock();
	if (hresult == S_FALSE)
	{	
		ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
		sprintf(szSendBuffer,"Com Received error!\r#");
		send(s,szSendBuffer,strlen(szSendBuffer),0);
		return FALSE;
	}
    strTemp.Empty();
	strTemp = pValue;

	ZeroMemory(szSendBuffer,sizeof(char)*MAX_PATH);
	sprintf(szSendBuffer,"COM:%ld",strTemp.GetLength());
    send(s,szSendBuffer,64,0);
	SendBufferBy1M(s,strTemp.GetBuffer(0),strTemp.GetLength());
	strTemp.ReleaseBuffer(0);
	SysFreeString(pValue);

//	ASSERT( SUCCEEDED( hresult ) );
//	_bstr_t b = pVal;
//	//int nLen = ::SysStringByteLen(pVal);
//	int nBytes = ::WideCharToMultiByte(CP_ACP,0,pVal,NULL,NULL,NULL,NULL,NULL);
//	char * pBuffer = b;
//	sprintf(szSendBuffer,"COM:%ld,",nBytes);
//	send(s,szSendBuffer,20,0);
//	send(s,pBuffer,nBytes,0);
//	sprintf(szSendBuffer,",\r#");
//	send(s,szSendBuffer,strlen(szSendBuffer),0);
//	::SysFreeString(pVal);	


	return TRUE;
}
