#include "stdafx.h"
#include "..\\include\\SwitchDll.h"


CBOLASwitch1XN::CBOLASwitch1XN()
{
	memset(m_LastErrorMsg, 0, 1024);
}


CBOLASwitch1XN::~CBOLASwitch1XN()
{
}

///////////////////////////////////////////////////////////////
//函数说明：
//    打开设备
//Add by wanxin
//20140821
//////////////////////////////////////////////////////////////
DWORD CBOLASwitch1XN::OpenDevice(LPCTSTR pszDeviceAddr, unsigned long *ComHandle)
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
DWORD CBOLASwitch1XN::CloseDevice()
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
DWORD CBOLASwitch1XN::SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle)
{
	DWORD   dwErrorCode = 0;
	//	LPCTSTR lpCommunicationInfo;

	dwErrorCode = m_DevComHandle.SetDeviceHandle(pszDeviceAddr, handle);
	return dwErrorCode;
}

void CBOLASwitch1XN::GetLastErrorMsg(char * errorMsg)
{
	memcpy_s(errorMsg, 1024, m_LastErrorMsg, strlen(m_LastErrorMsg));
}



void CBOLASwitch1XN::AnlysisErrorString(BYTE bStatus)
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

BYTE CBOLASwitch1XN::CalChecksum(BYTE* pbBuffer, int nLength)
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

DWORD CBOLASwitch1XN::SetSingleSWPos(BYTE bySWIndex, //SW Number:1~2
	BYTE byPos)
{
	BYTE sbBuffer[MAX_PATH];
	ZeroMemory(sbBuffer, MAX_PATH);

	sbBuffer[0] = byPos;

	if (m_DevComHandle.WriteDevice(sbBuffer, 1) != SUCCESS)
	{
		strcpy_s(m_LastErrorMsg, "Send Switch Channel cmd error!");
		return ERROR_SWITCH;
	}
	Sleep(500);

	ZeroMemory(sbBuffer, MAX_PATH);
	sbBuffer[0] = 42;
	if (m_DevComHandle.WriteDevice(sbBuffer, 1) != SUCCESS)
	{
		strcpy_s(m_LastErrorMsg, "Send Switch Channel cmd error!");
		return ERROR_SWITCH;
	}
	Sleep(100);

	ZeroMemory(sbBuffer, MAX_PATH);
	if (m_DevComHandle.ReadDevice(sbBuffer, MAX_PATH) != SUCCESS)
	{
		strcpy_s(m_LastErrorMsg, "Receive Switch Pos cmd error!");
		return ERROR_SWITCH;
	}

	if (sbBuffer[0] == 0x00)
	{
		strcpy_s(m_LastErrorMsg, "Receive Switch Pos Data error!");
		return ERROR_SWITCH;
	}

	if (sbBuffer[0] != byPos)
	{
		strcpy_s(m_LastErrorMsg, "Switch Pos Set error!");
		return ERROR_SWITCH;
	}

	return SUCCESS;
}

DWORD CBOLASwitch1XN::GetSingleSWPos(BYTE bySWIndex, //SW Number:1~2;
	BYTE &byPos)                  //Position
{
	char sbBuffer[MAX_PATH];
	ZeroMemory(sbBuffer, MAX_PATH);

	sbBuffer[0] = 42;

	if (m_DevComHandle.WriteDevice((BYTE*)sbBuffer, 1) != SUCCESS)
	{
		strcpy_s(m_LastErrorMsg, "Send Switch Channel cmd error!");
		return ERROR_SWITCH;
	}
	Sleep(100);

	ZeroMemory(sbBuffer, MAX_PATH);
	if (m_DevComHandle.ReadDevice((BYTE*)sbBuffer, MAX_PATH) != SUCCESS)
	{
		strcpy_s(m_LastErrorMsg, "Receive Switch Pos cmd error!");
		return ERROR_SWITCH;
	}

	if (sbBuffer[0] == 0x00)
	{
		strcpy_s(m_LastErrorMsg, "Receive Switch Pos Data error!");
		return ERROR_SWITCH;
	}
	byPos = sbBuffer[0];
	return SUCCESS;
}

//MultiSW Control
DWORD CBOLASwitch1XN::SetMultiSWPos(BYTE *pbyPosArray, //All SW Position:0~N,0xFF; 0xFF:Keep in place
	BYTE bySWCount)                   //SW Count
{
	return 0;
}

DWORD CBOLASwitch1XN::GetMultiSWPos(BYTE *pbyPosArray, //All SW Position
	BYTE bySWCount)                   //SW Count
{
	return 0;
}

//~~~~~~~~InputVOA Set~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Input VOA Set
DWORD CBOLASwitch1XN::SetInputVOAAtten(double dblAtten)
{
	return 0;
}
DWORD CBOLASwitch1XN::GetInputVOAAtten(double *pdblAtten)
{
	return 0;
}
//MSA VOA Set
DWORD CBOLASwitch1XN::SetMSAVOAAtten(double dblAtten)
{
	return 0;
}
DWORD CBOLASwitch1XN::GetMSAVOAAtten(double *pdblAtten)
{
	return 0;
}

//~~~~~~~~SW Path~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
DWORD CBOLASwitch1XN::SetLDSSelection(BYTE bySrcIndex) //1~8;SW1
{
	return 0;
}
//S1~8->IN1~17
DWORD CBOLASwitch1XN::SetLDSToDutIn(BYTE byDutInIndex) //1~17;SW2+SW9
{
	return 0;
}
//S1~8->Out1~18
DWORD CBOLASwitch1XN::SetLDSToDutOut(BYTE byDutOutIndex)//1~18;SW3+SW9
{
	return 0;
}
//OPM/OSA
DWORD CBOLASwitch1XN::SetLDSToMonPath(BYTE byDestPos)//1~2;SW4
{
	return 0;
}
DWORD CBOLASwitch1XN::SetLDSToRefPath(BYTE byDestPos)//1~2;SW2+SW4+SW5+SW9
{
	return 0;
}
DWORD CBOLASwitch1XN::SetDutOutToDest(BYTE byDutOutIndex, BYTE byDestPos)//SW3+SW4+SW5+SW9
{
	return 0;
}
DWORD CBOLASwitch1XN::SetDutInAsOutput(BYTE byDutInIndex, BYTE byDestPos)//SW2+SW4+SW5+SW9
{
	return 0;
}

DWORD CBOLASwitch1XN::SetDutOut98ToEO1(BYTE byDutOutIndex, BYTE byDestPos)//SW3+SW4+SW5+SW9;OUT_98 connect to EO1
{
	return 0;
}
DWORD CBOLASwitch1XN::SetDutIn98AsOutputToEO1(BYTE byDutInIndex, BYTE byDestPos)//SW2+SW4+SW5+SW9；OUT_98 connect to EO1
{
	return 0;
}
//MAS IN->MAS OUT
DWORD CBOLASwitch1XN::SetMSAInToMSAOut(BYTE byMsaInPort, BYTE byMsaOutPort, double dblMsaVOAAtten) //SW6+SW7+SW8
{
	return 0;
}
DWORD CBOLASwitch1XN::SetMSATapToDest(BYTE byMsaOutPort, BYTE byDestPos) //SW4+SW5+SW6+SW8
{
	return 0;
}
DWORD CBOLASwitch1XN::SetMSAInAsOutput(BYTE byMsaInPort, BYTE byDestPos) //SW4+SW5+SW7+SW8
{
	return 0;
}
DWORD CBOLASwitch1XN::SetMSAOutAsOutput(BYTE byMsaOutPort, BYTE byDestPos) //SW4+SW5+SW6+SW8
{
	return 0;
}

DWORD CBOLASwitch1XN::SetMSAOut98AsOutputToEO2(BYTE byMsaOutPort, BYTE byDestPos) //SW4+SW5+SW6+SW8;MOP_98 connect to EO2
{
	return 0;
}

//Expand Port
DWORD CBOLASwitch1XN::SetEOPortToDest(BYTE byEOPort, BYTE byDestPos) //EO1~3 SW4+SW5;
{
	return 0;
}

//~~~~~~~~~~~~~Trigger~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//VOA Drive Trigger
DWORD CBOLASwitch1XN::SetVOATriggerOut(double dblStartAtten, double dblEndAtten, double dblStepAtten, WORD wOPMWaitTimeMs)
{
	return 0;
}
//SW Drive Trigger
DWORD CBOLASwitch1XN::SetSWPathMapping(char *pchBinfileName)
{
	return 0;
}
DWORD CBOLASwitch1XN::SetSWTriggerPathScanStart(WORD wExitTimeOutSecond)
{
	return 0;
}
//Query Scan Status
//DWORD GetTriggerScanStatus(BYTE &byStatus);

//~~~~~~~~GPIO Setting~~~~~~~~~~~~~~~~~~~~~~~~~~
//看协议只有32为，但是ctrl+Alarm需要32位
DWORD CBOLASwitch1XN::SetGPIOStatus(WORD wAlarmIN, WORD wAlarmOut)
{
	return SUCCESS;
}

DWORD CBOLASwitch1XN::GetGPIOStatus(WORD *pwAlarmIN, WORD *pwAlarmOut)
{
	return SUCCESS;
}

DWORD CBOLASwitch1XN::SetGPIOVoltage(bool bVoltage5V)
{
	return SUCCESS;
}


//~~~~~~~~UART Setting~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Struct 
//byUARTIndex =0Xff: ALL
DWORD CBOLASwitch1XN::SetUARTConfig(BYTE byUARTIndex, stSerialPortCfg stSerialPortCfgValue, DWORD dwTimeOut)
{
	return 0;
}
DWORD CBOLASwitch1XN::WriteUARTData(BYTE byUARTIndex, BYTE* pbyBuffer, WORD wLength)
{
	return 0;
}
DWORD CBOLASwitch1XN::ReadUARTData(BYTE byUARTIndex, BYTE* pbyBuffer, WORD wLength, WORD *pwGetLength)
{
	return 0;
}

//~~~~~~~~~BasicInfo~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//开关切换次数/校准日期/生产日期
DWORD CBOLASwitch1XN::GetDeviceInfo(pstDevInfo pstSWInfo)
{
	return 0;
}
DWORD CBOLASwitch1XN::GetSwitchingCnt(BYTE bySWIndex, DWORD *pdwSwitchingCnt) //只针对机械式开关
{
	return 0;
}

//~~~~~~~~IL/WDL Value~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
DWORD CBOLASwitch1XN::GetInputMinIL(BYTE bySWIndex, double * pdblGetMinIL)
{
	return 0;
}

DWORD CBOLASwitch1XN::SetBlockBySwitch(BYTE bySrcIndex)
{
	return 0;
}