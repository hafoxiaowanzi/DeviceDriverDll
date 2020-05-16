#include "stdafx.h"
#include "..\\include\\SwitchDll.h"


CThreeSwitch1X18::CThreeSwitch1X18()
{
}


CThreeSwitch1X18::~CThreeSwitch1X18()
{
}

///////////////////////////////////////////////////////////////
//函数说明：
//    打开设备
//Add by wanxin
//20140821
//////////////////////////////////////////////////////////////
DWORD CThreeSwitch1X18::OpenDevice(LPCTSTR pszDeviceAddr, unsigned long *ComHandle)
{
	//CString strComPort;	
	DWORD   dwErrorCode;

	dwErrorCode = m_DevComHandle.OpenDevice(pszDeviceAddr, *ComHandle);
	if (dwErrorCode != SUCCESS)
	{
		return dwErrorCode;
	}
	return dwErrorCode;
}
/////////////////////////////////////////////////////////////
//函数说明：
//    关闭设备
//Add by wanxin
//20140821
//////////////////////////////////////////////////////////////
DWORD CThreeSwitch1X18::CloseDevice()
{
	DWORD   dwErrorCode;
	dwErrorCode = m_DevComHandle.CloseDevice();
	if (dwErrorCode != SUCCESS)
	{
		return dwErrorCode;
	}
	return dwErrorCode;
}
/////////////////////////////////////////////////////////////
//函数说明：
//    设置设备句柄指针
//Add by wanxin
//20140821
//////////////////////////////////////////////////////////////
DWORD CThreeSwitch1X18::SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle)
{
	DWORD   dwErrorCode = 0;
	//	LPCTSTR lpCommunicationInfo;

	dwErrorCode = m_DevComHandle.SetDeviceHandle(pszDeviceAddr, handle);
	return dwErrorCode;
}

void CThreeSwitch1X18::GetLastErrorMsg(char * errorMsg)
{
	memcpy_s(errorMsg, 1024, m_LastErrorMsg, strlen(m_LastErrorMsg));
}

void CThreeSwitch1X18::AnlysisErrorString(BYTE bStatus)
{
	switch (bStatus)
	{
	case 0x10:
	{
		strcpy_s(m_LastErrorMsg, "Command executed failed.");
	}
	break;
	case 0x11:
	{
		strcpy_s(m_LastErrorMsg, "INCOMPLETE.");
	}
	break;
	case 0x12:
	{
		strcpy_s(m_LastErrorMsg, "System BUSY.");
	}
	break;
	case 0x20:
	{
		strcpy_s(m_LastErrorMsg, "Message SyncHead Error / Reserved.");
	}
	break;
	case 0x21:
	{
		strcpy_s(m_LastErrorMsg, "Message Length Error.");
	}
	break;
	case 0x22:
	{
		strcpy_s(m_LastErrorMsg, "Message Status Error.");
	}
	break;
	case 0x23:
	{
		strcpy_s(m_LastErrorMsg, "Message Access Error.");
	}
	break;
	case 0x24:
	{
		strcpy_s(m_LastErrorMsg, "Message Object Error.");
	}
	break;
	case 0x25:
	{
		strcpy_s(m_LastErrorMsg, "Message Instance Error.");
	}
	break;
	case 0x26:
	{
		strcpy_s(m_LastErrorMsg, "Message Payload Error.");
	}
	break;
	case 0x27:
	{
		strcpy_s(m_LastErrorMsg, "Message Checksum Error.");
	}
	break;
	case 0x28:
	{
		strcpy_s(m_LastErrorMsg, "Sub Module not in or Error.");
	}
	break;
	default:
		break;
	}
}

BYTE CThreeSwitch1X18::CalChecksum(BYTE* pbBuffer, int nLength)
{
	BYTE bSum = 0;
	BYTE bCheckSum = 0;
	for (int i = 0; i < nLength; i++)
	{
		bSum += pbBuffer[i];
	}
	bCheckSum = 0xFF - bSum;
	return bCheckSum;
}

DWORD CThreeSwitch1X18::SetSingleSWPos(BYTE bySWIndex, //SW Number:1~4
	BYTE byPos)
{
	char sbBuffer[MAX_PATH];

	if (bySWIndex < 1 || bySWIndex > 4)
	{
		strcpy_s(m_LastErrorMsg, 1024, "参数出错！");
		return ERROR_SWITCH;
	}

	if (byPos < 1 || byPos > 16)
	{
		strcpy_s(m_LastErrorMsg, 1024, "参数出错！");
		return ERROR_SWITCH;
	}

	//设置MFG模式
	ZeroMemory(sbBuffer, MAX_PATH);
	sprintf_s(sbBuffer, "seti2c 0 f8 00d64d4647434d44\r\n");
	if (m_DevComHandle.WriteDevice((BYTE*)sbBuffer, strlen(sbBuffer)) != SUCCESS)
	{
		strcpy_s(m_LastErrorMsg, "Send MFG Mode error!");
		return ERROR_SWITCH;
	}
	ZeroMemory(sbBuffer, MAX_PATH);
	if (m_DevComHandle.ReadDevice((BYTE*)sbBuffer, MAX_PATH) != SUCCESS)
	{
		strcpy_s(m_LastErrorMsg, "Receive MFG Mode cmd error!");
		return ERROR_SWITCH;
	}

	Sleep(100);

	if (bySWIndex == 4)
	{
		ZeroMemory(sbBuffer, MAX_PATH);
		sprintf_s(sbBuffer, "seti2c 0 f8 01430%d%02x\r\n", 2, 17);
		if (m_DevComHandle.WriteDevice((BYTE*)sbBuffer, strlen(sbBuffer)) != SUCCESS)
		{
			strcpy_s(m_LastErrorMsg, "Send Switch Channel cmd error!");
			return ERROR_SWITCH;
		}

		ZeroMemory(sbBuffer, MAX_PATH);
		if (m_DevComHandle.ReadDevice((BYTE*)sbBuffer, MAX_PATH) != SUCCESS)
		{
			strcpy_s(m_LastErrorMsg, "Receive Switch Channel cmd error!");
			return ERROR_SWITCH;
		}

		char*ptr = "";
		char* checkstr = "OK";
		ptr = strstr(sbBuffer, checkstr);
		if (ptr == NULL)
		{
			strcpy_s(m_LastErrorMsg, "Receive Switch Channel data error!");
			return ERROR_SWITCH;
		}
	}

	ZeroMemory(sbBuffer, MAX_PATH);
	sprintf_s(sbBuffer, "seti2c 0 f8 01430%d%02x\r\n", bySWIndex-1, byPos);
	if (m_DevComHandle.WriteDevice((BYTE*)sbBuffer, strlen(sbBuffer)) != SUCCESS)
	{
		strcpy_s(m_LastErrorMsg, "Send Switch Channel cmd error!");
		return ERROR_SWITCH;
	}

	ZeroMemory(sbBuffer, MAX_PATH);
	if (m_DevComHandle.ReadDevice((BYTE*)sbBuffer, MAX_PATH) != SUCCESS)
	{
		strcpy_s(m_LastErrorMsg, "Receive Switch Channel cmd error!");
		return ERROR_SWITCH;
	}

	char*ptr = "";
	char* checkstr = "OK";
	ptr = strstr(sbBuffer, checkstr);
	if (ptr == NULL)
	{
		strcpy_s(m_LastErrorMsg, "Receive Switch Channel data error!");
		return ERROR_SWITCH;
	}

	return SUCCESS;
}

DWORD CThreeSwitch1X18::GetSingleSWPos(BYTE bySWIndex, //SW Number:1~3;
	BYTE &byPos)                  //Position
{
	char sbBuffer[MAX_PATH];

	if (bySWIndex < 1 || bySWIndex > 4)
	{
		strcpy_s(m_LastErrorMsg, 1024, "参数出错！");
		return ERROR_SWITCH;
	}

	//设置MFG模式
	ZeroMemory(sbBuffer, MAX_PATH);
	sprintf_s(sbBuffer, "seti2c 0 f8 00d64d4647434d44\r\n");
	if (m_DevComHandle.WriteDevice((BYTE*)sbBuffer, strlen(sbBuffer)) != SUCCESS)
	{
		strcpy_s(m_LastErrorMsg, "Send MFG Mode error!");
		return ERROR_SWITCH;
	}
	ZeroMemory(sbBuffer, MAX_PATH);
	if (m_DevComHandle.ReadDevice((BYTE*)sbBuffer, MAX_PATH) != SUCCESS)
	{
		strcpy_s(m_LastErrorMsg, "Receive MFG Mode cmd error!");
		return ERROR_SWITCH;
	}

	Sleep(100);

	ZeroMemory(sbBuffer, MAX_PATH);
	sprintf_s(sbBuffer, "seti2c 0 f8 018a0%d\r\n", bySWIndex-1);
	if (m_DevComHandle.WriteDevice((BYTE*)sbBuffer, strlen(sbBuffer)) != SUCCESS)
	{
		strcpy_s(m_LastErrorMsg, "Send Switch Channel cmd error!");
		return ERROR_SWITCH;
	}
	ZeroMemory(sbBuffer, MAX_PATH);
	if (m_DevComHandle.ReadDevice((BYTE*)sbBuffer, MAX_PATH) != SUCCESS)
	{
		strcpy_s(m_LastErrorMsg, "Receive Switch Pos cmd error!");
		return ERROR_SWITCH;
	}

	ZeroMemory(sbBuffer, MAX_PATH);
	sprintf_s(sbBuffer, "SETI2C 0 F8 018B\r\n");
	if (m_DevComHandle.WriteDevice((BYTE*)sbBuffer, strlen(sbBuffer)) != SUCCESS)
	{
		strcpy_s(m_LastErrorMsg, "Send Switch Channel cmd error!");
		return ERROR_SWITCH;
	}
	ZeroMemory(sbBuffer, MAX_PATH);
	if (m_DevComHandle.ReadDevice((BYTE*)sbBuffer, MAX_PATH) != SUCCESS)
	{
		strcpy_s(m_LastErrorMsg, "Receive Switch Pos cmd error!");
		return ERROR_SWITCH;
	}

	ZeroMemory(sbBuffer, MAX_PATH);
	sprintf_s(sbBuffer, "geti2c 0 f8 1\r\n");
	if (m_DevComHandle.WriteDevice((BYTE*)sbBuffer, strlen(sbBuffer)) != SUCCESS)
	{
		strcpy_s(m_LastErrorMsg, "Send Switch Channel cmd error!");
		return ERROR_SWITCH;
	}
	ZeroMemory(sbBuffer, MAX_PATH);
	if (m_DevComHandle.ReadDevice((BYTE*)sbBuffer, MAX_PATH) != SUCCESS)
	{
		strcpy_s(m_LastErrorMsg, "Receive Switch Pos cmd error!");
		return ERROR_SWITCH;
	}

	sprintf_s(sbBuffer, "%c%c", sbBuffer[0], sbBuffer[1]);
	byPos = (BYTE)strtol((char*)sbBuffer, NULL, 16);

	return SUCCESS;
}

//MultiSW Control
DWORD CThreeSwitch1X18::SetMultiSWPos(BYTE *pbyPosArray, //All SW Position:0~N,0xFF; 0xFF:Keep in place
	BYTE bySWCount)                   //SW Count
{
	return 0;
}

DWORD CThreeSwitch1X18::GetMultiSWPos(BYTE *pbyPosArray, //All SW Position
	BYTE bySWCount)                   //SW Count
{
	return 0;
}

//~~~~~~~~InputVOA Set~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Input VOA Set
DWORD CThreeSwitch1X18::SetInputVOAAtten(double dblAtten)
{
	return 0;
}
DWORD CThreeSwitch1X18::GetInputVOAAtten(double *pdblAtten)
{
	return 0;
}
//MSA VOA Set
DWORD CThreeSwitch1X18::SetMSAVOAAtten(double dblAtten)
{
	return 0;
}
DWORD CThreeSwitch1X18::GetMSAVOAAtten(double *pdblAtten)
{
	return 0;
}

//~~~~~~~~SW Path~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
DWORD CThreeSwitch1X18::SetLDSSelection(BYTE bySrcIndex) //1~8;SW1
{
	return 0;
}
//S1~8->IN1~17
DWORD CThreeSwitch1X18::SetLDSToDutIn(BYTE byDutInIndex) //1~17;SW2+SW9
{
	return 0;
}
//S1~8->Out1~18
DWORD CThreeSwitch1X18::SetLDSToDutOut(BYTE byDutOutIndex)//1~18;SW3+SW9
{
	return 0;
}
//OPM/OSA
DWORD CThreeSwitch1X18::SetLDSToMonPath(BYTE byDestPos)//1~2;SW4
{
	return 0;
}
DWORD CThreeSwitch1X18::SetLDSToRefPath(BYTE byDestPos)//1~2;SW2+SW4+SW5+SW9
{
	return 0;
}
DWORD CThreeSwitch1X18::SetDutOutToDest(BYTE byDutOutIndex, BYTE byDestPos)//SW3+SW4+SW5+SW9
{
	return 0;
}
DWORD CThreeSwitch1X18::SetDutInAsOutput(BYTE byDutInIndex, BYTE byDestPos)//SW2+SW4+SW5+SW9
{
	return 0;
}

DWORD CThreeSwitch1X18::SetDutOut98ToEO1(BYTE byDutOutIndex, BYTE byDestPos)//SW3+SW4+SW5+SW9;OUT_98 connect to EO1
{
	return 0;
}
DWORD CThreeSwitch1X18::SetDutIn98AsOutputToEO1(BYTE byDutInIndex, BYTE byDestPos)//SW2+SW4+SW5+SW9；OUT_98 connect to EO1
{
	return 0;
}
//MAS IN->MAS OUT
DWORD CThreeSwitch1X18::SetMSAInToMSAOut(BYTE byMsaInPort, BYTE byMsaOutPort, double dblMsaVOAAtten) //SW6+SW7+SW8
{
	return 0;
}
DWORD CThreeSwitch1X18::SetMSATapToDest(BYTE byMsaOutPort, BYTE byDestPos) //SW4+SW5+SW6+SW8
{
	return 0;
}
DWORD CThreeSwitch1X18::SetMSAInAsOutput(BYTE byMsaInPort, BYTE byDestPos) //SW4+SW5+SW7+SW8
{
	return 0;
}
DWORD CThreeSwitch1X18::SetMSAOutAsOutput(BYTE byMsaOutPort, BYTE byDestPos) //SW4+SW5+SW6+SW8
{
	return 0;
}

DWORD CThreeSwitch1X18::SetMSAOut98AsOutputToEO2(BYTE byMsaOutPort, BYTE byDestPos) //SW4+SW5+SW6+SW8;MOP_98 connect to EO2
{
	return 0;
}

//Expand Port
DWORD CThreeSwitch1X18::SetEOPortToDest(BYTE byEOPort, BYTE byDestPos) //EO1~3 SW4+SW5;
{
	return 0;
}

//~~~~~~~~~~~~~Trigger~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//VOA Drive Trigger
DWORD CThreeSwitch1X18::SetVOATriggerOut(double dblStartAtten, double dblEndAtten, double dblStepAtten, WORD wOPMWaitTimeMs)
{
	return 0;
}
//SW Drive Trigger
DWORD CThreeSwitch1X18::SetSWPathMapping(char *pchBinfileName)
{
	return 0;
}
DWORD CThreeSwitch1X18::SetSWTriggerPathScanStart(WORD wExitTimeOutSecond)
{
	return 0;
}
//Query Scan Status
//DWORD GetTriggerScanStatus(BYTE &byStatus);

//~~~~~~~~GPIO Setting~~~~~~~~~~~~~~~~~~~~~~~~~~
//看协议只有32为，但是ctrl+Alarm需要32位
DWORD CThreeSwitch1X18::SetGPIOStatus(WORD wAlarmIN, WORD wAlarmOut)
{
	return 0;
}

DWORD CThreeSwitch1X18::GetGPIOStatus(WORD *pwAlarmIN, WORD *pwAlarmOut)
{
	return 0;
}

DWORD CThreeSwitch1X18::SetGPIOVoltage(bool bVoltage5V)
{
	return 0;
}


//~~~~~~~~UART Setting~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Struct 
//byUARTIndex =0Xff: ALL
DWORD CThreeSwitch1X18::SetUARTConfig(BYTE byUARTIndex, stSerialPortCfg stSerialPortCfgValue, DWORD dwTimeOut)
{
	return 0;
}
DWORD CThreeSwitch1X18::WriteUARTData(BYTE byUARTIndex, BYTE* pbyBuffer, WORD wLength)
{
	return 0;
}
DWORD CThreeSwitch1X18::ReadUARTData(BYTE byUARTIndex, BYTE* pbyBuffer, WORD wLength, WORD *pwGetLength)
{
	return 0;
}

//~~~~~~~~~BasicInfo~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//开关切换次数/校准日期/生产日期
DWORD CThreeSwitch1X18::GetDeviceInfo(pstDevInfo pstSWInfo)
{
	return 0;
}
DWORD CThreeSwitch1X18::GetSwitchingCnt(BYTE bySWIndex, DWORD *pdwSwitchingCnt) //只针对机械式开关
{
	return 0;
}

//~~~~~~~~IL/WDL Value~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
DWORD CThreeSwitch1X18::GetInputMinIL(BYTE bySWIndex, double * pdblGetMinIL)
{
	return 0;
}

DWORD CThreeSwitch1X18::SetBlockBySwitch(BYTE bySrcIndex)
{
	return 0;
}