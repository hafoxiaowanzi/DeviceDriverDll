// CommunicationDLL.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "..\\include\\CommunicationDLL.h"

#define GPIB 0
#define LAN 1
#define COM 2
#define USB 3


BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			break;
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }

    return TRUE;
}


// This is an example of an exported variable
COMMUNICATIONDLL_API int nCommunicationDLL=0;

// This is an example of an exported function.
COMMUNICATIONDLL_API int fnCommunicationDLL(void)
{

	return 42;
}

// This is the constructor of a class that has been exported.
// see CommunicationDLL.h for the class definition
CCommunicationDLL::CCommunicationDLL():m_commun(NULL)
{ 
/*	m_pvoid(NULL),if (NULL == m_pvoid)
	{
		m_pvoid = new void*[10];
		for (int nIndex = 0; nIndex < 10; nIndex++)
		{
			m_pvoid[nIndex] = NULL;
		}
	}

	if (NULL == m_pvoid[GPIB])
		m_pvoid[GPIB] = new CGpib;
	if (NULL == m_pvoid[LAN])
		m_pvoid[LAN] = new CLan;
	if (NULL == m_pvoid[COM])
		m_pvoid[COM] = new CComm;
	if (NULL == m_pvoid[USB])
		m_pvoid[USB] = new CUsb;*/
}

CCommunicationDLL::~CCommunicationDLL()
{
/*	if (NULL != m_pvoid[GPIB])
	{
		delete m_pvoid[GPIB];
		m_pvoid[GPIB] = NULL;
	}
	
	if (NULL != m_pvoid[LAN])
	{
		delete m_pvoid[LAN];
		m_pvoid[LAN] = NULL;
	}

	if (NULL != m_pvoid[COM])
	{
		delete m_pvoid[COM];
		m_pvoid[COM] = NULL;
	}

	if (NULL != m_pvoid[USB])
	{
		delete m_pvoid[USB];
		m_pvoid[USB] = NULL;
	}

	delete [] m_pvoid;
	m_pvoid = NULL;*/
}

string CCommunicationDLL::GetErrorMsg()
{
	return ((CCommunication*)m_commun)->GetErrorMsg();
}

/************************************************************************
*  ��������:OpenDevice													*
*  ����: �������豸													*
*  ����:																*
*		lpCommunicationInfo ͨѶ��Ϣ��COM/GPIB/LAN/USB��				*
*	1.Type: GPIB, board index, Primary address, Secondary address		*
*		lpCommunicationInfo = "GPIB,0,23,0"								*
*	2.Type: LAN, board index, IP address, Port, Login name, Login Password	*
*		lpCommunicationInfo = "LAN,0,192.168.x.x,80, NA, NA"			*
*	3.Type:COM, COM number, Baud rate, Byte size, Parity, Stop bit		*
*		lpCommunicationInfo = "COM,1,9600,8,0,0" or						*
*		"COM,1,9600"(Default: Byte size = 8, Parity = 0, Stop bit = 0)	*
*  ������������:LPCTSTR													*
*  ���:																*
*       commHandle ����ͨѶ�ӿ�Handle									*
*  �����������:CommunicationHandle										*
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD CCommunicationDLL::OpenDevice(LPCTSTR lpCommunicationInfo, unsigned long &commHandle)
{
	TCHAR ptchCommuType[20] = {0};
	long lFlagCount = 0;
	long lTypeLen = 0;
	m_dwErrorCode = 0;

	for (UINT n = 0; n < strlen(lpCommunicationInfo); n++)
	{
		if (lpCommunicationInfo[n] == ',')
		{
			if (0 == lFlagCount)
			{
				lTypeLen = n;
			}
			lFlagCount++;
		}
	}

	if (lTypeLen > 5)
	{
		return ERROR_COMMUNICATION_INFO;
	}
	else
	{
		memcpy(ptchCommuType, lpCommunicationInfo, lTypeLen);
	}

	if (m_commun !=NULL)
	{
		delete m_commun;
		m_commun = NULL;
	}


	//"GPIB,0,23,0,0"
	//Type, GPIB board index, Primary GPIB address, Secondary GPIB address, NF Mode
	if (0 == memcmp(ptchCommuType, "GPIB", 4))
	{
		m_dwErrorCode = ERROR_COMMUNICATION_GPIB;
		m_commun = new CGpib(); //(CGpib *)m_pvoid[GPIB];

		if (lFlagCount > 4)
		{
			return ERROR_COMMUNICATION_GPIB|ERROR_COMMUNICATION_INFO;
		}
	}
	//"LAN,0,192.168.x.x,80, , "
	//Type, board index, IP address, Port, Login name, Login Password
	else if (0 == memcmp(ptchCommuType, "LAN", 3))
	{
		m_dwErrorCode = ERROR_COMMUNICATION_LAN;
		m_commun = new CLan();//(CLan *)m_pvoid[LAN];

		if (lFlagCount < 2)
		{
			return ERROR_COMMUNICATION_LAN|ERROR_COMMUNICATION_INFO;
		}
	}
	//"COM,1,9600,8,0,0" or "COM,1,9600"(Byte size = 8, Parity = 0, Stop bit = 0)
	//Type, COM number, Baud rate, Byte size, Parity, Stop bit
	else if (0 == memcmp(ptchCommuType, "COM", 3))
	{
		m_dwErrorCode = ERROR_COMMUNICATION_COM;
		m_commun = new CComm();//(CComm *)m_pvoid[COM];

		if (lFlagCount != 5&&lFlagCount != 2)
		{
			return ERROR_COMMUNICATION_COM|ERROR_COMMUNICATION_INFO;
		}
	}
	else if (0 == memcmp(ptchCommuType, "USB", 3))
	{
		m_dwErrorCode = ERROR_COMMUNICATION_USB;
		m_commun = new CUsb(); //(CUsb *)m_pvoid[USB];
	}
	else 
	{
		return ERROR_COMMUNICATION_INFO;
	}

	if (!((CCommunication*)m_commun)->Open(&lpCommunicationInfo[lTypeLen+1]))
	{
		return m_dwErrorCode|ERROR_OPEN;
	}

	if (0 == memcmp(ptchCommuType, "GPIB", 4))
	{
		commHandle = ((CGpib*)m_commun)->m_hGPIB; //((CGpib *)m_pvoid[GPIB])->m_hGPIB;
	}
	else if (0 == memcmp(ptchCommuType, "LAN", 3))
	{
		commHandle = ((CLan*)m_commun)->m_hSocket;//((CLan *)m_pvoid[LAN])->m_hSocket;
	}
	else if (0 == memcmp(ptchCommuType, "COM", 3))
	{
		commHandle = (unsigned long)((CComm*)m_commun)->m_hCommPort;//(unsigned long)((CComm *)m_pvoid[COM])->m_hCommPort;
	}
	else if (0 == memcmp(ptchCommuType, "USB", 3))
	{
		commHandle = ((CUsb*)m_commun)->m_usb;// ((CUsb *)m_pvoid[USB])->m_usb;
	}

	return SUCCESS;
}

/************************************************************************
*  ��������:CloseDevice													*
*  ����:�ر��豸����													*
*  ����:��																*
*  ������������:��														*
*  ���:��																*
*  �����������:��														*
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD CCommunicationDLL::CloseDevice()
{
	if (!((CCommunication*)m_commun)->Close())
	{
		return m_dwErrorCode|ERROR_CLOSE;
	}

	return SUCCESS;
}

/************************************************************************
*  ��������:WriteDevice													*
*  ����:д������豸													*
*  ����:																*
*		1.pWriteBuffer д����������										*
*		2.dwWriteLength ����ȣ��������ֵΪ0�������¼�������ȣ�	*
*  ������������:PVOID��DWORD											*
*  ���:��																*
*  �����������:��														*
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD CCommunicationDLL::WriteDevice(PVOID pWriteBuffer, DWORD dwWriteLength)
{
	if (!((CCommunication*)m_commun)->Write(pWriteBuffer, dwWriteLength))
	{
		return m_dwErrorCode|ERROR_WRITE;
	}

	return SUCCESS;
}

/************************************************************************
*  ��������:ReadDevice													*
*  ����:��ȡ�豸������Ϣ												*
*  ����:																*
*		dwReadLength ��ȡ������Ϣ���ݵĳ���								*
*  ������������:DWORD													*
*  ���:																*
*		pREadBuffer ������Ϣ��������									*
*  �����������:PVOID													*
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD CCommunicationDLL::ReadDevice(PVOID pREadBuffer, DWORD dwReadLength)
{
	if (!((CCommunication*)m_commun)->Read(pREadBuffer, dwReadLength))
	{
		return m_dwErrorCode|ERROR_READ;
	}
	return SUCCESS;
}

/************************************************************************
*  ��������:ClearDevice													*
*  ����:����豸ͨѶBUFFER												*
*  ����:��																*
*  ������������:��														*
*  ���:��																*
*  �����������:��														*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD CCommunicationDLL::ClearDevice()
{
	if (!((CCommunication*)m_commun)->Clear())
	{
		return m_dwErrorCode|ERROR_CLEAR;
	}
	return SUCCESS;
}

/************************************************************************
*  ��������:SetDeviceHandle												*
*  ����:����豸ͨѶBUFFER												*
*  ����:��																*
*  ������������:��														*
*  ���:��																*
*  �����������:��														*
*  ����ֵ:																*
*             0: ����ִ�гɹ�											*
*    0xXXXXXXXX: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-17													*
*  ������:�Ժ���														*
*  �޸���ʷ:��															*
*************************************************************************/
DWORD CCommunicationDLL::SetDeviceHandle(LPCTSTR lpCommunicationInfo, unsigned long pHandle)
{
	TCHAR ptchCommuType[5] = "";
	m_dwErrorCode = 0;
	long lFlagCount = 0;
	long lTypeLen = 0;
    
	for (UINT n = 0; n < strlen(lpCommunicationInfo); n++)
	{
		if (lpCommunicationInfo[n] == ',')
		{
			if (0 == lFlagCount) 
			{
				lTypeLen = n;
			}
			lFlagCount++;
		}
	}

	if (lTypeLen > 5)
	{
		return ERROR_COMMUNICATION_INFO;
	}
	else
	{
		memcpy(ptchCommuType, lpCommunicationInfo, lTypeLen);
	}
	if (m_commun !=NULL)
	{
		delete m_commun;
		m_commun = NULL;
	}
		//"GPIB,0,23,0"
	//Type, GPIB board index, Primary GPIB address, Secondary GPIB address
	if (0 == memcmp(ptchCommuType, "GPIB", 4))
	{
		m_dwErrorCode = ERROR_COMMUNICATION_GPIB;
		m_commun = new CGpib();//(CGpib *)m_pvoid[GPIB];

		if (lFlagCount != 3)
		{
			return ERROR_COMMUNICATION_GPIB|ERROR_COMMUNICATION_INFO;
		}
	}
	//"LAN,0,192.168.x.x,80, , "
	//Type, board index, IP address, Port, Login name, Login Password
	else if (0 == memcmp(ptchCommuType, "LAN", 3))
	{
		m_dwErrorCode = ERROR_COMMUNICATION_LAN;
		m_commun = new CLan();//(CLan *)m_pvoid[LAN];
		if (lFlagCount < 3 )
		{
			return ERROR_COMMUNICATION_LAN|ERROR_COMMUNICATION_INFO;
		}
	}
	//"COM,1,9600,8,0,0" or "COM,1,9600"(Byte size = 8, Parity = 0, Stop bit = 0)
	//Type, COM number, Baud rate, Byte size, Parity, Stop bit
	else if (0 == memcmp(ptchCommuType, "COM", 3))
	{
		m_dwErrorCode = ERROR_COMMUNICATION_COM;
		m_commun = new CComm();//(CComm *)m_pvoid[COM];
		if (lFlagCount != 5&&lFlagCount != 2)
		{
			return ERROR_COMMUNICATION_COM|ERROR_COMMUNICATION_INFO;
		}
	}
	else if (0 == memcmp(ptchCommuType, "USB", 3))
	{
		m_dwErrorCode = ERROR_COMMUNICATION_USB;
		m_commun = new CUsb();//(CUsb *)m_pvoid[USB];
	}
	else 
	{
		return ERROR_COMMUNICATION_INFO;
	}
    
	((CCommunication*)m_commun)->SetHandle(pHandle);

	return SUCCESS;
}

