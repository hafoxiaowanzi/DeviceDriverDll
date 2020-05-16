#include "stdafx.h"
#include "..\\include\\SwitchDll.h"


CDualSwitch1X68::CDualSwitch1X68()
{
	memset(m_LastErrorMsg, 0, 1024);
}


CDualSwitch1X68::~CDualSwitch1X68()
{
}

///////////////////////////////////////////////////////////////
//函数说明：
//    打开设备
//Add by wanxin
//20140821
//////////////////////////////////////////////////////////////
DWORD CDualSwitch1X68::OpenDevice(LPCTSTR pszDeviceAddr, unsigned long *ComHandle)
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
DWORD CDualSwitch1X68::CloseDevice()
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
DWORD CDualSwitch1X68::SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle)
{
	DWORD   dwErrorCode = 0;
	//	LPCTSTR lpCommunicationInfo;

	dwErrorCode = m_DevComHandle.SetDeviceHandle(pszDeviceAddr, handle);
	return dwErrorCode;
}


void CDualSwitch1X68::GetLastErrorMsg(char * errorMsg)
{
	memcpy_s(errorMsg, 1024, m_LastErrorMsg, strlen(m_LastErrorMsg));
}

void CDualSwitch1X68::AnlysisErrorString(BYTE bStatus)
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

BYTE CDualSwitch1X68::CalChecksum(BYTE* pbBuffer, int nLength)
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

DWORD CDualSwitch1X68::SetSingleSWPos(BYTE bySWIndex, //SW Number:1~2
	BYTE byPos)
{
	char sbBuffer[MAX_PATH];
	ZeroMemory(sbBuffer, MAX_PATH);

	sprintf_s(sbBuffer, "SetCh %d %d", bySWIndex, byPos);

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

DWORD CDualSwitch1X68::GetSingleSWPos(BYTE bySWIndex, //SW Number:1~2;
	BYTE &byPos)                  //Position
{
	char sbBuffer[MAX_PATH];
	ZeroMemory(sbBuffer, MAX_PATH);

	sprintf_s(sbBuffer, "GetCh %d", bySWIndex);

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

	byPos = sbBuffer[0];
	return SUCCESS;
}

//MultiSW Control
DWORD CDualSwitch1X68::SetMultiSWPos(BYTE *pbyPosArray, //All SW Position:0~N,0xFF; 0xFF:Keep in place
	BYTE bySWCount)                   //SW Count
{
	return 0;
}

DWORD CDualSwitch1X68::GetMultiSWPos(BYTE *pbyPosArray, //All SW Position
	BYTE bySWCount)                   //SW Count
{
	return 0;
}

//~~~~~~~~InputVOA Set~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Input VOA Set
DWORD CDualSwitch1X68::SetInputVOAAtten(double dblAtten)
{
	return 0;
}
DWORD CDualSwitch1X68::GetInputVOAAtten(double *pdblAtten)
{
	return 0;
}
//MSA VOA Set
DWORD CDualSwitch1X68::SetMSAVOAAtten(double dblAtten)
{
	return 0;
}
DWORD CDualSwitch1X68::GetMSAVOAAtten(double *pdblAtten)
{
	return 0;
}

//~~~~~~~~SW Path~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
DWORD CDualSwitch1X68::SetLDSSelection(BYTE bySrcIndex) //1~8;SW1
{
	return 0;
}
//S1~8->IN1~17
DWORD CDualSwitch1X68::SetLDSToDutIn(BYTE byDutInIndex) //1~17;SW2+SW9
{
	return 0;
}
//S1~8->Out1~18
DWORD CDualSwitch1X68::SetLDSToDutOut(BYTE byDutOutIndex)//1~18;SW3+SW9
{
	return 0;
}
//OPM/OSA
DWORD CDualSwitch1X68::SetLDSToMonPath(BYTE byDestPos)//1~2;SW4
{
	return 0;
}
DWORD CDualSwitch1X68::SetLDSToRefPath(BYTE byDestPos)//1~2;SW2+SW4+SW5+SW9
{
	return 0;
}
DWORD CDualSwitch1X68::SetDutOutToDest(BYTE byDutOutIndex, BYTE byDestPos)//SW3+SW4+SW5+SW9
{
	return 0;
}
DWORD CDualSwitch1X68::SetDutInAsOutput(BYTE byDutInIndex, BYTE byDestPos)//SW2+SW4+SW5+SW9
{
	return 0;
}

DWORD CDualSwitch1X68::SetDutOut98ToEO1(BYTE byDutOutIndex, BYTE byDestPos)//SW3+SW4+SW5+SW9;OUT_98 connect to EO1
{
	return 0;
}
DWORD CDualSwitch1X68::SetDutIn98AsOutputToEO1(BYTE byDutInIndex, BYTE byDestPos)//SW2+SW4+SW5+SW9；OUT_98 connect to EO1
{
	return 0;
}
//MAS IN->MAS OUT
DWORD CDualSwitch1X68::SetMSAInToMSAOut(BYTE byMsaInPort, BYTE byMsaOutPort, double dblMsaVOAAtten) //SW6+SW7+SW8
{
	return 0;
}
DWORD CDualSwitch1X68::SetMSATapToDest(BYTE byMsaOutPort, BYTE byDestPos) //SW4+SW5+SW6+SW8
{
	return 0;
}
DWORD CDualSwitch1X68::SetMSAInAsOutput(BYTE byMsaInPort, BYTE byDestPos) //SW4+SW5+SW7+SW8
{
	return 0;
}
DWORD CDualSwitch1X68::SetMSAOutAsOutput(BYTE byMsaOutPort, BYTE byDestPos) //SW4+SW5+SW6+SW8
{
	return 0;
}

DWORD CDualSwitch1X68::SetMSAOut98AsOutputToEO2(BYTE byMsaOutPort, BYTE byDestPos) //SW4+SW5+SW6+SW8;MOP_98 connect to EO2
{
	return 0;
}

//Expand Port
DWORD CDualSwitch1X68::SetEOPortToDest(BYTE byEOPort, BYTE byDestPos) //EO1~3 SW4+SW5;
{
	return 0;
}

//~~~~~~~~~~~~~Trigger~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//VOA Drive Trigger
DWORD CDualSwitch1X68::SetVOATriggerOut(double dblStartAtten, double dblEndAtten, double dblStepAtten, WORD wOPMWaitTimeMs)
{
	return 0;
}
//SW Drive Trigger
DWORD CDualSwitch1X68::SetSWPathMapping(char *pchBinfileName)
{
	return 0;
}
DWORD CDualSwitch1X68::SetSWTriggerPathScanStart(WORD wExitTimeOutSecond)
{
	return 0;
}
//Query Scan Status
//DWORD GetTriggerScanStatus(BYTE &byStatus);

//~~~~~~~~GPIO Setting~~~~~~~~~~~~~~~~~~~~~~~~~~
//看协议只有32为，但是ctrl+Alarm需要32位
DWORD CDualSwitch1X68::SetGPIOStatus(WORD wAlarmIN, WORD wAlarmOut)
{
	return SUCCESS;
}

DWORD CDualSwitch1X68::GetGPIOStatus(WORD *pwAlarmIN, WORD *pwAlarmOut)
{
	return SUCCESS;
}

DWORD CDualSwitch1X68::SetGPIOVoltage(bool bVoltage5V)
{
	return SUCCESS;
}


//~~~~~~~~UART Setting~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Struct 
//byUARTIndex =0Xff: ALL
DWORD CDualSwitch1X68::SetUARTConfig(BYTE byUARTIndex, stSerialPortCfg stSerialPortCfgValue, DWORD dwTimeOut)
{
	return 0;
}
DWORD CDualSwitch1X68::WriteUARTData(BYTE byUARTIndex, BYTE* pbyBuffer, WORD wLength)
{
	return 0;
}
DWORD CDualSwitch1X68::ReadUARTData(BYTE byUARTIndex, BYTE* pbyBuffer, WORD wLength, WORD *pwGetLength)
{
	return 0;
}

//~~~~~~~~~BasicInfo~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//开关切换次数/校准日期/生产日期
DWORD CDualSwitch1X68::GetDeviceInfo(pstDevInfo pstSWInfo)
{
	return 0;
}
DWORD CDualSwitch1X68::GetSwitchingCnt(BYTE bySWIndex, DWORD *pdwSwitchingCnt) //只针对机械式开关
{
	return 0;
}

//~~~~~~~~IL/WDL Value~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
DWORD CDualSwitch1X68::GetInputMinIL(BYTE bySWIndex, double * pdblGetMinIL)
{
	return 0;
}

DWORD CDualSwitch1X68::SetBlockBySwitch(BYTE bySrcIndex)
{
	return 0;
}