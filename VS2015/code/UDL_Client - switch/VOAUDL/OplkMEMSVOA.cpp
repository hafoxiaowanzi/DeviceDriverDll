// OplkMEMSVOA.cpp: implementation of the COplkMEMSVOA class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\\include\\voa.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COplkMEMSVOA::COplkMEMSVOA()
{
//	m_hCommPort = INVALID_HANDLE_VALUE;
//	m_Comm = NULL;
//	m_Comm = new CCommunicationDLL;
}

COplkMEMSVOA::~COplkMEMSVOA()
{
//	delete m_Comm;
//	m_Comm = NULL;
}

/************************************************************************
*  函数名称:OpenDevice													*
*  功能: 打开连接设备													*
*  输入:																*
*		1.stType:设备类型结构体											*
*       2.pszDeviceAddr:通讯信息										*
*  输出数据类型:stDevType, char* 										*
*  输出:																*
*       comHandle:基础通讯接口Handle									*
*  输出数据类型:CommunicationHandle										*
*  返回值:																*
*             0: 函数执行成功。											*
*    0x80000012: 其他错误												*
*  返回值类型:DWORD														*
*  创建日期:2013-09-07													*
*  创建人:赵寒飞														*
*  修改：刘珍宏	Oct 23,2013												*
*************************************************************************/
DWORD COplkMEMSVOA::OpenDevice(char* pszDeviceAddr, unsigned long *comHandle)
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
*  函数名称: CloseDevice												*
*  功能:     关闭设备													*
*  输入: 无																*
*																		*
*  输入数据类型: 无														*
*  输出: 无																*
*  输出数据类型: 无												 		*
*  返回值:																*
*             0: 函数执行成功。											*
*    0x80000012: 其他错误												*
*  返回值类型:DWORD														*
*  创建日期:2013-09-07													*
*  创建人:赵寒飞														*
*  修改：刘珍宏	Oct 23,2013												*
*************************************************************************/
DWORD COplkMEMSVOA::CloseDevice()
{
	DWORD	dwErrorCode = SUCCESS;
	dwErrorCode = m_Comm.CloseDevice();
	
	return dwErrorCode;
}

/************************************************************************
*  函数名称: SetHandle													*
*  功能: 设置打开设备的句柄												*
*  输入:																*
*		1.stType:设备类型结构体											*
*       2.hHandle:句柄													*
*  输入数据类型:stDevType, HANDLE 										*
*  输出:																*
*       无																*
*  输出数据类型:无														*
*  返回值:																*
*             0: 函数执行成功。											*
*    0x80000012: 其他错误												*
*  返回值类型:DWORD														*
*  创建日期:2013-11-05													*
*  创建人: Xianjun Wang													*
*  修改：																*
*************************************************************************/
DWORD COplkMEMSVOA::SetHandle(char* pszDeviceAddr, unsigned long comHandle)
{
	DWORD	dwErrorCode = SUCCESS;
	
	dwErrorCode = m_Comm.SetDeviceHandle(pszDeviceAddr, comHandle);

	return dwErrorCode;
}


/************************************************************************
*  函数名称: GetAttenuation												*
*  功能: 读取VOA通道衰减值												*
*  输入:																*
*		lChIndex: VOA通道号												*
*  输入数据类型: long			 										*
*  输出:																*
*       dblAtten: 衰减													*
*  输出数据类型:double *												*
*  返回值:																*
*             0: 函数执行成功。											*
*    0x80000012: 其他错误												*
*  返回值类型: DWORD													*
*  创建日期: 2013-11-05													*
*  创建人: Xianjun Wang													*
*  修改：																*
*************************************************************************/
DWORD COplkMEMSVOA::GetAttenuation(long lChIndex, double *dblAtten)
{
	DWORD dwErrorCode = SUCCESS;
    char pchTxData[50];
	char pchRxData[100];
	BYTE bIndex;
	CHAR pchTemp[256];

	try
	{
		ZeroMemory(pchTxData, 50);
		sprintf(pchTxData, "ATTEN\r\n");
		// 写读取衰减的命令
		dwErrorCode = m_Comm.WriteDevice(pchTxData, 7);
		if(SUCCESS != dwErrorCode)
		{
//			strcpy(m_pszGlobleMsg, "写VOA指令错误");
			throw dwErrorCode | ERROR_ATTEN;
		}

		ZeroMemory(pchRxData, 32);
		
		bIndex = 0;
		while(bIndex < 10)
		{
			Sleep(30);
			// 读取衰减
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
//			strcpy(m_pszGlobleMsg, "读VOA数据错误");
			throw dwErrorCode | ERROR_ATTEN;
		}

		ZeroMemory(pchTemp, 256);
		// 数据处理
		for(int i=10, j = 0; pchRxData[i] != '\r' && i<16; i++)
		{
			pchTemp[j] = pchRxData[i];
			j++;
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
*  函数名称: GetDeviceInfo												*
*  功能: 读取VOA设备信息												*
*  输入:																*
*		无																*
*  输入数据类型: 无		 												*
*  输出:																*
*       stInfo: VOA信息结构指针											*
*  输出数据类型: stDevInfo												*
*  返回值:																*
*             0: 函数执行成功。											*
*    0x80000012: 其他错误												*
*  返回值类型: DWORD													*
*  创建日期: 2013-11-05													*
*  创建人: Xianjun Wang													*
*  修改：																*
*************************************************************************/
DWORD COplkMEMSVOA::GetDeviceInfo(stDevInfo *stInfo)
{
	DWORD dwErrorCode = SUCCESS;
	char pchTxData[50];
	char pchRxData[100];
	BYTE bIndex, byComLen;

	try
	{
		ZeroMemory(pchTxData, 50);
		sprintf(pchTxData, "INFO\r\n");
		byComLen = strlen(pchTxData);

		// Send 'INFO' command to VOA device
		dwErrorCode = m_Comm.WriteDevice(pchTxData, byComLen);
		if(SUCCESS != dwErrorCode)
		{
			//strcpy(m_pszGlobleMsg, "发送获取VOA设备信息指令错误");
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
			//strcpy(m_pszGlobleMsg, "读VOA设备信息错误");
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
*  函数名称: GetErrorMessage											*
*  功能: 读取VOA设备信息, (未实施!!)									*
*  输入:																*
*		dwErrorCode: 错误码												*
*  输入数据类型: DWORD	 												*
*  输出:																*
*       pszErrorMsg: VOA错误信息结构指针								*
*  输出数据类型: char													*
*  返回值:																*
*             0: 函数执行成功。											*
*    0x80000012: 其他错误												*
*  返回值类型: DWORD													*
*  创建日期: 2013-11-05													*
*  创建人: Xianjun Wang													*
*  修改：																*
*************************************************************************/
BOOL COplkMEMSVOA::GetErrorMessage(DWORD dwErrorCode, char *pszErrorMsg)
{
	if (pszErrorMsg != NULL)
	{
//		strcpy(pszErrorMsg, m_pszGlobleMsg);
//		memset(m_pszGlobleMsg, 0, 100);
	}
	return TRUE;
}

/************************************************************************
*  函数名称: GetStatus													*
			此VOA似无相应功能, 待日后再增加
*  创建日期: 2013-11-06													*
*  创建人: Xianjun Wang													*
*  修改：																*
*************************************************************************/
DWORD COplkMEMSVOA::GetStatus(DWORD *dwStatus)
{
	//{"INFO", "SN", "TEMP", "MONVOL", "ATTEN", "CHMODE", "WAVEFORM", "INPWR", "OUTPWR"};
	*dwStatus = 0;
	return SUCCESS;
}

/************************************************************************
*  函数名称: GetWavelength												*
*  功能: 读取VOA波长													*
*  输入:																*
*		lChIndex: VOA通道												*
*  输入数据类型: long	 												*
*  输出:																*
*       dblWL: 当前通道波长值											*
*  输出数据类型: double *												*
*  返回值:																*
*             0: 函数执行成功。											*
*    0x80000012: 其他错误												*
*  返回值类型: DWORD													*
*  创建日期: 2013-11-06													*
*  创建人: Xianjun Wang													*
*  修改：																*
*************************************************************************/
DWORD COplkMEMSVOA::GetWavelength(long lChIndex, double *dblWL)
{
	DWORD dwErrorCode = SUCCESS;
	char pchTxData[50], pchRxData[100];
	char pchTemp[256];
	BYTE bIndex, bTxDataLength;
	int	 nTemp = 0;

	try
	{
		ZeroMemory(pchTxData, 50);
		sprintf(pchTxData, "WAVEFORM\r\n");

		bTxDataLength = strlen((const char *)pchTxData);

		dwErrorCode = m_Comm.WriteDevice(pchTxData, bTxDataLength);
		if(SUCCESS != dwErrorCode)
		{
//			strcpy(m_pszGlobleMsg, "发送读取VOA波长指令错误");
			throw ERROR_WL | dwErrorCode;
		}

		ZeroMemory(pchRxData, 32);
		
		bIndex = 0;
		while(bIndex < 10)
		{
			dwErrorCode = m_Comm.ReadDevice(pchRxData, 20);
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
//			strcpy(m_pszGlobleMsg, "读取VOA波长错误");
			throw ERROR_WL | dwErrorCode;
		}

		ZeroMemory(pchTemp, 256);
		for(int i=9, j = 0; pchRxData[i] != '\r' && i<16; i++)
		{
			pchTemp[j] = pchRxData[i];
			j++;
		}

		*dblWL = atof(pchTemp);
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
*  函数名称: ResetDevice												*
*  功能: VOA复位, 将调用设置通道衰减函数将衰减值设置为0					*
*  输入:																*
*		无																*
*  输入数据类型: 无		 												*
*  输出:																*
*		无																*
*  输出数据类型: 无		 												*
*  返回值:																*
*             0: 函数执行成功。											*
*    0x80000012: 其他错误												*
*  返回值类型: DWORD													*
*  创建日期: 2013-11-06													*
*  创建人: Xianjun Wang													*
*  修改：																*
*************************************************************************/
DWORD COplkMEMSVOA::ResetDevice()
{
	return SetAttenuation(1, 0.0);
}

/************************************************************************
*  函数名称: SetAttenuation												*
*  功能: 设置VOA通道衰减												*
*  输入:																*
*		lChIndex: VOA通道；dblAtten: 衰减值								*
*  输入数据类型: long；double											*
*  输出:																*
*       无																*
*  输出数据类型:														*
*  返回值:																*
*             0: 函数执行成功。											*
*    0x80000012: 其他错误												*
*  返回值类型: DWORD													*
*  创建日期: 2013-11-06													*
*  创建人: Xianjun Wang													*
*  修改：																*
*************************************************************************/
DWORD COplkMEMSVOA::SetAttenuation(long lChIndex, double dblAtten)
{
	DWORD dwErrorCode = SUCCESS;
	char pchTemp[256];
	char bRxData[100];
	BYTE bIndex, bTxDataLength;
	double dblGetAtten;
	int nTemp = 0;

	try
	{
		ZeroMemory(pchTemp, sizeof(pchTemp));
		sprintf(pchTemp, "CHMODE 1 CA %.2f\r\n", dblAtten);

		bTxDataLength = strlen(pchTemp);
		dwErrorCode = m_Comm.WriteDevice(pchTemp, bTxDataLength);
		if(SUCCESS != dwErrorCode)
		{
//			strcpy(m_pszGlobleMsg, "发送只是VOA衰减指令错误");
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
//			strcpy(m_pszGlobleMsg, "读取VOA衰减错误");
			return ERROR_ATTEN | dwErrorCode;
		}

		if (fabs(dblGetAtten - dblAtten) >= 0.1) 
		{
//			sprintf(m_pszGlobleMsg, "设置衰减 %.2f 失败!", dblAtten);
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
*  函数名称: SetEnableOutput											*
			此VOA似无相应功能, 待日后再增加
*  创建日期: 2013-11-06													*
*  创建人: Xianjun Wang													*
*  修改：																*
*************************************************************************/
DWORD COplkMEMSVOA::SetEnableOutput(long lChIndex, BOOL bEnable)
{
	return SUCCESS;
}

/************************************************************************
*  函数名称: SetEnableOutput											*
			此VOA似无相应功能, 待日后再增加
*  创建日期: 2013-11-06													*
*  创建人: Xianjun Wang													*
*  修改：																*
*************************************************************************/
DWORD COplkMEMSVOA::SetInputOffset(long lChIndex, double dblOffset)
{
	return SUCCESS;
}

/************************************************************************
*  函数名称: SetWavelength												*
*  功能: 设置VOA波长，!!函数操作成功，但实际波长未变!!					*
*  输入:																*
*		lChIndex: VOA通道; dblWL: 波长值								*
*  输入数据类型: long; double											*
*  输出:																*
*       无																*
*  输出数据类型:														*
*  返回值:																*
*             0: 函数执行成功。											*
*    0x80000012: 其他错误												*
*  返回值类型: DWORD													*
*  创建日期: 2013-11-06													*
*  创建人: Xianjun Wang													*
*  修改：																*
*************************************************************************/
DWORD COplkMEMSVOA::SetWavelength(long lChIndex, double dblWL)
{
	DWORD dwErrorCode = SUCCESS;
    char pchTxData[50];
	char pchRxData[100];
	BYTE bIndex, bTxDataLength;
	int	 nTemp = 0;

	try
	{
		ZeroMemory(pchTxData, 50);
		sprintf(pchTxData, "WAVEFORM %.2f\r\n", dblWL);

		bTxDataLength = strlen((const char *)pchTxData);

		dwErrorCode = m_Comm.WriteDevice(pchTxData, bTxDataLength);
		if(SUCCESS != dwErrorCode)
		{
//			strcpy(m_pszGlobleMsg, "设置VOA波长指令错误");
			throw dwErrorCode | ERROR_WL;
		}

		ZeroMemory(pchRxData, 32);
		
		bIndex = 0;
		while(bIndex < 150)
		{
			dwErrorCode = m_Comm.ReadDevice(pchRxData, 10);
			if(SUCCESS != dwErrorCode)
			{
				bIndex ++;
				continue;
			}
			else
				break;
		}
		if (bIndex == 150)
		{
//			strcpy(m_pszGlobleMsg, "设置波长后获取VOA反馈信息错误");
			throw dwErrorCode | ERROR_WL;
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
*  函数名称: WriteBuffer												*
*  功能: 写串口															*
*  输入:																*
*		pOutBuffer: 待写数据; dwBufferSize: 待写数据长度				*
*  输入数据类型: unsigned char *; DWORD									*
*  输出:																*
*       无																*
*  输出数据类型:														*
*  返回值:																*
*             TRUE: 函数执行成功。										*
*			  FALSE: 其他错误											*
*  返回值类型: BOOL														*
*  创建日期: 2013-11-06													*
*  创建人: Xianjun Wang													*
*  修改：																*
*************************************************************************/
//BOOL COplkMEMSVOA::WriteBuffer(unsigned char *pOutBuffer, DWORD dwBufferSize)
//{
//	DWORD dwBytesWritten;
//
//	if(m_hCommPort == INVALID_HANDLE_VALUE)
//		return FALSE;
//
//	// Clear the TX and RX buffer Error information
//	if (!PurgeComm(m_hCommPort, PURGE_TXCLEAR | PURGE_RXCLEAR))
//	{
//		return FALSE;
//	}
//
//	WriteFile(m_hCommPort, pOutBuffer, dwBufferSize, &dwBytesWritten, NULL);
//	if(dwBytesWritten != dwBufferSize)
//		return FALSE;
//
//	return TRUE;
//}

/************************************************************************
*  函数名称: WriteBuffer												*
*  功能: 写串口															*
*  输入:																*
*		dwBufferSize: 将读数据长度										*
*  输入数据类型: DWORD													*
*  输出:																*
*       pInBuffer: 读数据缓冲											*
*  输出数据类型: unsigned char *										*
*  返回值:																*
*             TRUE: 函数执行成功。										*
*			  FALSE: 其他错误											*
*  返回值类型: BOOL														*
*  创建日期: 2013-11-06													*
*  创建人: Xianjun Wang													*
*  修改：																*
*************************************************************************/
//BOOL COplkMEMSVOA::ReadBuffer(unsigned char *pInBuffer, DWORD dwBufferSize)
//{
//	DWORD dwBytesRead;
//
//	if(m_hCommPort == INVALID_HANDLE_VALUE)
//		return FALSE;
//
//	ReadFile(m_hCommPort, pInBuffer, dwBufferSize, &dwBytesRead, NULL);
//
//	// if the received buffer is empty, return FALSE
//	if(dwBytesRead == 0)
//		return FALSE;
//
//	return TRUE;
//}
