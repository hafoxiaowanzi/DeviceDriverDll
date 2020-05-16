#include "stdafx.h"
#include "..\\include\\SwitchDll.h"

CSwitch1X2::CSwitch1X2()
{

}

CSwitch1X2::~CSwitch1X2()
{

}

///////////////////////////////////////////////////////////////
//函数说明：
//    打开设备
//Add by wanxin
//20140821
//////////////////////////////////////////////////////////////
DWORD CSwitch1X2::OpenDevice(LPCTSTR pszDeviceAddr, unsigned long *ComHandle)
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
DWORD CSwitch1X2::CloseDevice()
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
DWORD CSwitch1X2::SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle)
{
	DWORD   dwErrorCode = 0;
	//	LPCTSTR lpCommunicationInfo;

	dwErrorCode = m_DevComHandle.SetDeviceHandle(pszDeviceAddr, handle);
	return dwErrorCode;
}

DWORD CSwitch1X2::SetSingleSWPos(BYTE bySWIndex, //SW Number:1
	BYTE byPos)
{
	BYTE sbBuffer[MAX_PATH];
	ZeroMemory(sbBuffer, MAX_PATH);

	if (byPos == 1)
	{
		////2A 30 30 30 39 30 31 30 31 30 30 30 30 4B 0D
		sbBuffer[0] = 0x2A;
		sbBuffer[1] = 0x30;
		sbBuffer[2] = 0x30;
		sbBuffer[3] = 0x30;
		sbBuffer[4] = 0x39;
		sbBuffer[5] = 0x30;
		sbBuffer[6] = 0x31;
		sbBuffer[7] = 0x30;
		sbBuffer[8] = 0x31;
		sbBuffer[9] = 0x30;
		sbBuffer[10] = 0x30;
		sbBuffer[11] = 0x30;
		sbBuffer[12] = 0x30;
		sbBuffer[13] = 0x4B;
		sbBuffer[14] = 0x0D;
	}
	else if(byPos == 2)
	{
		////2A 30 30 30 39 30 31 30 32 30 30 30 30 4D 0D
		sbBuffer[0] = 0x2A;
		sbBuffer[1] = 0x30;
		sbBuffer[2] = 0x30;
		sbBuffer[3] = 0x30;
		sbBuffer[4] = 0x39;
		sbBuffer[5] = 0x30;
		sbBuffer[6] = 0x32;
		sbBuffer[7] = 0x30;
		sbBuffer[8] = 0x32;
		sbBuffer[9] = 0x30;
		sbBuffer[10] = 0x30;
		sbBuffer[11] = 0x30;
		sbBuffer[12] = 0x30;
		sbBuffer[13] = 0x4D;
		sbBuffer[14] = 0x0D;
	}
	else
	{
		strcpy_s(m_LastErrorMsg, 1024, "参数出错！");
		return ERROR_SWITCH;
	}

	if (m_DevComHandle.WriteDevice(sbBuffer, 15) != SUCCESS)
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

	if (sbBuffer[13] != 0x4C && sbBuffer[14] != 0x5E)
	{
		strcpy_s(m_LastErrorMsg, "Set 1X2SW Error");
		return ERROR_SWITCH;
	}
	return SUCCESS;
}

DWORD CSwitch1X2::GetSingleSWPos(BYTE bySWIndex, //SW Number:1~M;
	BYTE &byPos)                  //Position
{
	return 0;
}
								   //MultiSW Control
DWORD CSwitch1X2::SetMultiSWPos(BYTE *pbyPosArray, //All SW Position:0~N,0xFF; 0xFF:Keep in place
	BYTE bySWCount)                   //SW Count
{
	return 0;
}

DWORD CSwitch1X2::GetMultiSWPos(BYTE *pbyPosArray, //All SW Position
	BYTE bySWCount)                   //SW Count
{
	return 0;
}

									   //~~~~~~~~InputVOA Set~~~~~~~~~~~~~~~~~~~~~~~~~~~
									   //Input VOA Set
DWORD CSwitch1X2::SetInputVOAAtten(double dblAtten)
{
	return 0;
}
DWORD CSwitch1X2::GetInputVOAAtten(double *pdblAtten)
{
	return 0;
}
//MSA VOA Set
DWORD CSwitch1X2::SetMSAVOAAtten(double dblAtten)
{
	return 0;
}
DWORD CSwitch1X2::GetMSAVOAAtten(double *pdblAtten)
{
	return 0;
}

//~~~~~~~~SW Path~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
DWORD CSwitch1X2::SetLDSSelection(BYTE bySrcIndex) //1~8;SW1
{
	return 0;
}
												//S1~8->IN1~17
DWORD CSwitch1X2::SetLDSToDutIn(BYTE byDutInIndex) //1~17;SW2+SW9
{
	return 0;
}
												//S1~8->Out1~18
DWORD CSwitch1X2::SetLDSToDutOut(BYTE byDutOutIndex)//1~18;SW3+SW9
{
	return 0;
}
												 //OPM/OSA
DWORD CSwitch1X2::SetLDSToMonPath(BYTE byDestPos)//1~2;SW4
{
	return 0;
}
DWORD CSwitch1X2::SetLDSToRefPath(BYTE byDestPos)//1~2;SW2+SW4+SW5+SW9
{
	return 0;
}
DWORD CSwitch1X2::SetDutOutToDest(BYTE byDutOutIndex, BYTE byDestPos)//SW3+SW4+SW5+SW9
{
	return 0;
}
DWORD CSwitch1X2::SetDutInAsOutput(BYTE byDutInIndex, BYTE byDestPos)//SW2+SW4+SW5+SW9
{
	return 0;
}

DWORD CSwitch1X2::SetDutOut98ToEO1(BYTE byDutOutIndex, BYTE byDestPos)//SW3+SW4+SW5+SW9;OUT_98 connect to EO1
{
	return 0;
}
DWORD CSwitch1X2::SetDutIn98AsOutputToEO1(BYTE byDutInIndex, BYTE byDestPos)//SW2+SW4+SW5+SW9；OUT_98 connect to EO1
{
	return 0;
}
																		 //MAS IN->MAS OUT
DWORD CSwitch1X2::SetMSAInToMSAOut(BYTE byMsaInPort, BYTE byMsaOutPort, double dblMsaVOAAtten) //SW6+SW7+SW8
{
	return 0;
}
DWORD CSwitch1X2::SetMSATapToDest(BYTE byMsaOutPort, BYTE byDestPos) //SW4+SW5+SW6+SW8
{
	return 0;
}
DWORD CSwitch1X2::SetMSAInAsOutput(BYTE byMsaInPort, BYTE byDestPos) //SW4+SW5+SW7+SW8
{
	return 0;
}
DWORD CSwitch1X2::SetMSAOutAsOutput(BYTE byMsaOutPort, BYTE byDestPos) //SW4+SW5+SW6+SW8
{
	return 0;
}

DWORD CSwitch1X2::SetMSAOut98AsOutputToEO2(BYTE byMsaOutPort, BYTE byDestPos) //SW4+SW5+SW6+SW8;MOP_98 connect to EO2
{
	return 0;
}

																		   //Expand Port
DWORD CSwitch1X2::SetEOPortToDest(BYTE byEOPort, BYTE byDestPos) //EO1~3 SW4+SW5;
{
	return 0;
}

															  //~~~~~~~~~~~~~Trigger~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
															  //VOA Drive Trigger
DWORD CSwitch1X2::SetVOATriggerOut(double dblStartAtten, double dblEndAtten, double dblStepAtten, WORD wOPMWaitTimeMs)
{
	return 0;
}
//SW Drive Trigger
DWORD CSwitch1X2::SetSWPathMapping(char *pchBinfileName)
{
	return 0;
}
DWORD CSwitch1X2::SetSWTriggerPathScanStart(WORD wExitTimeOutSecond)
{
	return 0;
}
//Query Scan Status
//DWORD GetTriggerScanStatus(BYTE &byStatus);

//~~~~~~~~GPIO Setting~~~~~~~~~~~~~~~~~~~~~~~~~~
DWORD CSwitch1X2::SetGPIOConfig(DWORD dwCtrlPinBits, DWORD dwAlarmPinBits) //Bits Definition:0-Input; 1-Output;CtrlPin:32;AlarmPin:32
{
	return 0;
}
DWORD CSwitch1X2::GetGPIOStatus(DWORD *pdwCtrlPinBits, DWORD *pdwAlarmPinBits)
{
	return 0;
}

//~~~~~~~~UART Setting~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Struct 
//byUARTIndex =0Xff: ALL
DWORD CSwitch1X2::SetUARTConfig(BYTE byUARTIndex, stSerialPortCfg stSerialPortCfgValue, DWORD dwTimeOut)
{
	return 0;
}
DWORD CSwitch1X2::WriteUARTData(BYTE byUARTIndex, BYTE* pbyBuffer, WORD wLength)
{
	return 0;
}
DWORD CSwitch1X2::ReadUARTData(BYTE byUARTIndex, BYTE* pbyBuffer, WORD wLength, WORD *pwGetLength)
{
	return 0;
}

//~~~~~~~~~BasicInfo~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//开关切换次数/校准日期/生产日期
DWORD CSwitch1X2::GetDeviceInfo(pstDevInfo pstSWInfo)
{
	return 0;
}
DWORD CSwitch1X2::GetSwitchingCnt(BYTE bySWIndex, DWORD *pdwSwitchingCnt) //只针对机械式开关
{
	return 0;
}

																	   //~~~~~~~~IL/WDL Value~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
DWORD CSwitch1X2::GetInputMinIL(BYTE bySWIndex, double * pdblGetMinIL)
{
	return 0;
}

//~~~~~~~~GPIO Setting~~~~~~~~~~~~~~~~~~~~~~~~~~
//看协议只有32为，但是ctrl+Alarm需要32位
DWORD CSwitch1X2::SetGPIOStatus(WORD wAlarmIN, WORD wAlarmOut)
{
	return 0;
}

DWORD CSwitch1X2::GetGPIOStatus(WORD *pwAlarmIN, WORD *pwAlarmOut)
{
	return 0;
}

DWORD CSwitch1X2::SetGPIOVoltage(bool bVoltage5V)
{
	return 0;
}

DWORD CSwitch1X2::SetBlockBySwitch(BYTE bySrcIndex)
{
	return 0;
}