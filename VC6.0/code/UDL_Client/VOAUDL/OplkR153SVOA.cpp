// OplkMEMSVOA.cpp: implementation of the COplkMEMSVOA class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\\include\\voa.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COplkR153VOA::COplkR153VOA()
{
//	m_hCommPort = INVALID_HANDLE_VALUE;
//	m_Comm = NULL;
//	m_Comm = new CCommunicationDLL;
}

COplkR153VOA::~COplkR153VOA()
{
//	delete m_Comm;
//	m_Comm = NULL;
}

/************************************************************************
*  ��������:OpenDevice													*
*  ����: �������豸													*
*  ����:																*
*		1.stType:�豸���ͽṹ��											*
*       2.pszDeviceAddr:ͨѶ��Ϣ										*
*  �����������:stDevType, char* 										*
*  ���:																*
*       comHandle:����ͨѶ�ӿ�Handle									*
*  �����������:CommunicationHandle										*
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*    0x80000012: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-07													*
*  ������:�Ժ���														*
*  �޸ģ������	Oct 23,2013												*
*************************************************************************/
DWORD COplkR153VOA::OpenDevice(char* pszDeviceAddr, unsigned long *comHandle)
{
	DWORD dwErrorCode = SUCCESS;

    try
	{
		dwErrorCode = m_Comm.OpenDevice(pszDeviceAddr, *comHandle);
		if (SUCCESS != dwErrorCode)
		{
			return ERROR_VOA | dwErrorCode;
		}
	}
	catch(...)
	{
		return UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

/************************************************************************
*  ��������: CloseDevice												*
*  ����:     �ر��豸													*
*  ����: ��																*
*																		*
*  ������������: ��														*
*  ���: ��																*
*  �����������: ��												 		*
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*    0x80000012: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-09-07													*
*  ������:�Ժ���														*
*  �޸ģ������	Oct 23,2013												*
*************************************************************************/
DWORD COplkR153VOA::CloseDevice()
{
	DWORD	dwErrorCode = SUCCESS;
	dwErrorCode = m_Comm.CloseDevice();
	
	return dwErrorCode;
}

/************************************************************************
*  ��������: SetHandle													*
*  ����: ���ô��豸�ľ��												*
*  ����:																*
*		1.stType:�豸���ͽṹ��											*
*       2.hHandle:���													*
*  ������������:stDevType, HANDLE 										*
*  ���:																*
*       ��																*
*  �����������:��														*
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*    0x80000012: ��������												*
*  ����ֵ����:DWORD														*
*  ��������:2013-11-05													*
*  ������: Xianjun Wang													*
*  �޸ģ�																*
*************************************************************************/
DWORD COplkR153VOA::SetHandle(char* pszDeviceAddr, unsigned long comHandle)
{
	DWORD	dwErrorCode = SUCCESS;
	
	dwErrorCode = m_Comm.SetDeviceHandle(pszDeviceAddr, comHandle);

	return dwErrorCode;
}


/************************************************************************
*  ��������: GetAttenuation												*
*  ����: ��ȡVOAͨ��˥��ֵ												*
*  ����:																*
*		lChIndex: VOAͨ����												*
*  ������������: long			 										*
*  ���:																*
*       dblAtten: ˥��													*
*  �����������:double *												*
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*    0x80000012: ��������												*
*  ����ֵ����: DWORD													*
*  ��������: 2013-11-05													*
*  ������: Xianjun Wang													*
*  �޸ģ�																*
*************************************************************************/
DWORD COplkR153VOA::GetAttenuation(long lChIndex, double *dblAtten)
{
	DWORD dwErrorCode = SUCCESS;
    char pchTxData[50];
	char pchRxData[100];
	BYTE bIndex;
	CHAR pchTemp[256];

	try
	{
		ZeroMemory(pchTxData, 50);
		sprintf(pchTxData, "sens%d:chan0:att:read?\r\n",lChIndex);
		// д��ȡ˥��������
		dwErrorCode = m_Comm.WriteDevice(pchTxData, strlen(pchTxData));
		if(SUCCESS != dwErrorCode)
		{
//			strcpy(m_pszGlobleMsg, "дVOAָ�����");
			throw dwErrorCode | ERROR_ATTEN;
		}

		ZeroMemory(pchRxData, 32);
		
		bIndex = 0;
		while(bIndex < 10)
		{
			Sleep(30);
			// ��ȡ˥��
			dwErrorCode = m_Comm.ReadDevice(pchRxData, 20);
			if(SUCCESS != dwErrorCode)
			{
				bIndex ++;
				continue;
			}
			else
			{
				break;
			}
		}
		if (bIndex == 10)
		{
//			strcpy(m_pszGlobleMsg, "��VOA���ݴ���");
			throw dwErrorCode | ERROR_ATTEN;
		}

		ZeroMemory(pchTemp, 256);
		for(int i=0;i<4;i++)
		{
			pchTemp[i] = pchRxData[i];
		}
			
		*dblAtten = atof(pchTemp);
	}
	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

/************************************************************************
*  ��������: GetDeviceInfo												*
*  ����: ��ȡVOA�豸��Ϣ												*
*  ����:																*
*		��																*
*  ������������: ��		 												*
*  ���:																*
*       stInfo: VOA��Ϣ�ṹָ��											*
*  �����������: stDevInfo												*
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*    0x80000012: ��������												*
*  ����ֵ����: DWORD													*
*  ��������: 2013-11-05													*
*  ������: Xianjun Wang													*
*  �޸ģ�																*
*************************************************************************/
DWORD COplkR153VOA::GetDeviceInfo(stDevInfo *stInfo)
{
	DWORD dwErrorCode = SUCCESS;
	char pchTxData[50];
	char pchRxData[100];
	BYTE bIndex, byComLen;

	try
	{
		ZeroMemory(pchTxData, 50);
		sprintf(pchTxData, "sens0:chan0:att:info?\r\n");
		byComLen = strlen(pchTxData);

		// Send 'INFO' command to VOA device
		dwErrorCode = m_Comm.WriteDevice(pchTxData, byComLen);
		if(SUCCESS != dwErrorCode)
		{
			//strcpy(m_pszGlobleMsg, "���ͻ�ȡVOA�豸��Ϣָ�����");
			throw ERROR_INFO | dwErrorCode;
		}

		ZeroMemory(pchRxData, 100);
		
		bIndex = 0;
		// Get info from VOA device
		while(bIndex < 10)
		{
			Sleep(30);
			dwErrorCode = m_Comm.ReadDevice(pchRxData, 100);
			if(SUCCESS != dwErrorCode)
			{
				bIndex ++;
				continue;
			}
			else
				break;
		}
		if (bIndex == 10)
		{
			//strcpy(m_pszGlobleMsg, "��VOA�豸��Ϣ����");
			throw ERROR_INFO | dwErrorCode;
		}

		// Write data from reading to struct
		if (stInfo != NULL)
		{
			strcpy((char *)stInfo, pchRxData);
			/*
			stInfo->pszName;
			stInfo->pszSerialNum;
			stInfo->pszMFDate;
			stInfo->pszHWVer;
			stInfo->pszFWVer;
			*/
		}
	}
	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

/************************************************************************
*  ��������: GetErrorMessage											*
*  ����: ��ȡVOA�豸��Ϣ, (δʵʩ!!)									*
*  ����:																*
*		dwErrorCode: ������												*
*  ������������: DWORD	 												*
*  ���:																*
*       pszErrorMsg: VOA������Ϣ�ṹָ��								*
*  �����������: char													*
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*    0x80000012: ��������												*
*  ����ֵ����: DWORD													*
*  ��������: 2013-11-05													*
*  ������: Xianjun Wang													*
*  �޸ģ�																*
*************************************************************************/
BOOL COplkR153VOA::GetErrorMessage(DWORD dwErrorCode, char *pszErrorMsg)
{
	if (pszErrorMsg != NULL)
	{
//		strcpy(pszErrorMsg, m_pszGlobleMsg);
//		memset(m_pszGlobleMsg, 0, 100);
	}
	return TRUE;
}

/************************************************************************
*  ��������: GetStatus													*
			��VOA������Ӧ����, ���պ�������
*  ��������: 2013-11-06													*
*  ������: Xianjun Wang													*
*  �޸ģ�																*
*************************************************************************/
DWORD COplkR153VOA::GetStatus(DWORD *dwStatus)
{
	//{"INFO", "SN", "TEMP", "MONVOL", "ATTEN", "CHMODE", "WAVEFORM", "INPWR", "OUTPWR"};
	*dwStatus = 0;
	return SUCCESS;
}

/************************************************************************
*  ��������: GetWavelength												*
*  ����: ��ȡVOA����													*
*  ����:																*
*		lChIndex: VOAͨ��												*
*  ������������: long	 												*
*  ���:																*
*       dblWL: ��ǰͨ������ֵ											*
*  �����������: double *												*
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*    0x80000012: ��������												*
*  ����ֵ����: DWORD													*
*  ��������: 2013-11-06													*
*  ������: Xianjun Wang													*
*  �޸ģ�																*
*************************************************************************/
DWORD COplkR153VOA::GetWavelength(long lChIndex, double *dblWL)
{
	DWORD dwErrorCode = SUCCESS;
	char pchTxData[50], pchRxData[100];
	char pchTemp[256];
	BYTE bIndex, bTxDataLength;
	int	 nTemp = 0;

	try
	{

	}
	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}

	return dwErrorCode;
}

/************************************************************************
*  ��������: ResetDevice												*
*  ����: VOA��λ, ����������ͨ��˥��������˥��ֵ����Ϊ0					*
*  ����:																*
*		��																*
*  ������������: ��		 												*
*  ���:																*
*		��																*
*  �����������: ��		 												*
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*    0x80000012: ��������												*
*  ����ֵ����: DWORD													*
*  ��������: 2013-11-06													*
*  ������: Xianjun Wang													*
*  �޸ģ�																*
*************************************************************************/
DWORD COplkR153VOA::ResetDevice()
{
	return SetAttenuation(1, 0.0);
}

/************************************************************************
*  ��������: SetAttenuation												*
*  ����: ����VOAͨ��˥��												*
*  ����:																*
*		lChIndex: VOAͨ����dblAtten: ˥��ֵ								*
*  ������������: long��double											*
*  ���:																*
*       ��																*
*  �����������:														*
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*    0x80000012: ��������												*
*  ����ֵ����: DWORD													*
*  ��������: 2013-11-06													*
*  ������: Xianjun Wang													*
*  �޸ģ�																*
*************************************************************************/
DWORD COplkR153VOA::SetAttenuation(long lChIndex, double dblAtten)
{
	DWORD dwErrorCode = SUCCESS;
	char pchTemp[256];
	char bRxData[100];
	BYTE bIndex, bTxDataLength;
	double dblGetAtten;
	int nTempValue;
	int nTemp = 0;

	try
	{
		ZeroMemory(pchTemp, sizeof(pchTemp));
		sprintf(pchTemp, "sens%d:chan0:att:setvoa %.2f\r\n",lChIndex, dblAtten);

		bTxDataLength = strlen(pchTemp);
		dwErrorCode = m_Comm.WriteDevice(pchTemp, bTxDataLength);
		if(SUCCESS != dwErrorCode)
		{
			throw ERROR_ATTEN | dwErrorCode;
		}

		ZeroMemory(bRxData, 32);
		
		bIndex = 0;
		while(bIndex < 150)
		{
			dwErrorCode = m_Comm.ReadDevice(bRxData, 10);
			if(SUCCESS != dwErrorCode)
			{
				bIndex ++;
				continue;
			}
			else
				break;
		}

		Sleep(20);
		dwErrorCode = GetAttenuation(lChIndex, &dblGetAtten);
		if (SUCCESS != dwErrorCode)
		{
			return ERROR_ATTEN | dwErrorCode;
		}

		if (fabs(dblGetAtten - dblAtten) >= 0.1) 
		{
			return ERROR_VOA | ERROR_ATTEN;
		}
	}
	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
    
	return dwErrorCode;
}

/************************************************************************
*  ��������: SetEnableOutput											*
			��VOA������Ӧ����, ���պ�������
*  ��������: 2013-11-06													*
*  ������: Xianjun Wang													*
*  �޸ģ�																*
*************************************************************************/
DWORD COplkR153VOA::SetEnableOutput(long lChIndex, BOOL bEnable)
{
	return SUCCESS;
}

/************************************************************************
*  ��������: SetEnableOutput											*
			��VOA������Ӧ����, ���պ�������
*  ��������: 2013-11-06													*
*  ������: Xianjun Wang													*
*  �޸ģ�																*
*************************************************************************/
DWORD COplkR153VOA::SetInputOffset(long lChIndex, double dblOffset)
{
	return SUCCESS;
}

/************************************************************************
*  ��������: SetWavelength												*
*  ����: ����VOA������!!���������ɹ�����ʵ�ʲ���δ��!!					*
*  ����:																*
*		lChIndex: VOAͨ��; dblWL: ����ֵ								*
*  ������������: long; double											*
*  ���:																*
*       ��																*
*  �����������:														*
*  ����ֵ:																*
*             0: ����ִ�гɹ���											*
*    0x80000012: ��������												*
*  ����ֵ����: DWORD													*
*  ��������: 2013-11-06													*
*  ������: Xianjun Wang													*
*  �޸ģ�																*
*************************************************************************/
DWORD COplkR153VOA::SetWavelength(long lChIndex, double dblWL)
{
	DWORD dwErrorCode = SUCCESS;
    char pchTxData[50];
	char pchRxData[100];
	BYTE bIndex, bTxDataLength;
	int	 nTemp = 0;

	try
	{
		ZeroMemory(pchTxData, sizeof(pchTxData));

		sprintf(pchTxData, "sens%d:chan0:att:WAV %lf\r\n",lChIndex, dblWL);

		bTxDataLength = strlen(pchTxData);
		dwErrorCode = m_Comm.WriteDevice(pchTxData, bTxDataLength);
		if(SUCCESS != dwErrorCode)
		{
			throw ERROR_ATTEN | dwErrorCode;
		}
	}
	catch (DWORD dwError) 
	{
		dwErrorCode = dwError;
	}
	catch(...)
	{
		dwErrorCode = UNEXPECT_OCCUR;
	}
    
	return dwErrorCode;
}

