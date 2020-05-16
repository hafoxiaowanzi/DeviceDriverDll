#include "stdafx.h"
#include "..\\include\\SwitchDll.h"

CEDFAGeneralSwitch4th::CEDFAGeneralSwitch4th()
{
	memset(m_LastErrorMsg, 0, 1024);
}

CEDFAGeneralSwitch4th::~CEDFAGeneralSwitch4th()
{

}

///////////////////////////////////////////////////////////////
//函数说明：
//    打开设备
//Add by wanxin
//20140821
//////////////////////////////////////////////////////////////
DWORD CEDFAGeneralSwitch4th::OpenDevice(LPCTSTR pszDeviceAddr, unsigned long *ComHandle)
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
DWORD CEDFAGeneralSwitch4th::CloseDevice()
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
DWORD CEDFAGeneralSwitch4th::SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle)
{
	DWORD   dwErrorCode = 0;
	//	LPCTSTR lpCommunicationInfo;

	dwErrorCode = m_DevComHandle.SetDeviceHandle(pszDeviceAddr, handle);
	return dwErrorCode;
}

void CEDFAGeneralSwitch4th::GetLastErrorMsg(char * errorMsg)
{
	memcpy_s(errorMsg, 1024, m_LastErrorMsg, strlen(m_LastErrorMsg));
}

BYTE CEDFAGeneralSwitch4th::CalChecksum(BYTE* pbBuffer, int nLength)
{
	BYTE bSum = 0;
	BYTE bCheckSum = 0;
	for (int i = 0;i < nLength;i++)
	{
		bSum += pbBuffer[i];
	}
	bCheckSum = 0xFF - bSum;
	return bCheckSum;
}

DWORD CEDFAGeneralSwitch4th::SetSingleSWPos(BYTE bySWIndex, //SW Number:1~M,0xFF; 0xFF:All SW set to the same Position
	BYTE byPos)
{
	BYTE sbBuffer[MAX_PATH];
	ZeroMemory(sbBuffer, MAX_PATH);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x09;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = 0x5a;
	sbBuffer[5] = 0x30;
	sbBuffer[6] = bySWIndex;
	sbBuffer[7] = byPos;

	BYTE bCheckSum = CalChecksum(sbBuffer, 8);

	sbBuffer[8] = bCheckSum;

	if (m_DevComHandle.WriteDevice(sbBuffer, 9)!=SUCCESS)
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
	if (sbBuffer[0] == 0xBD)
	{
		if (sbBuffer[3] != 0x00)
		{
			AnlysisErrorString(sbBuffer[3]);
			return ERROR_SWITCH;
		}
	}
	else
	{
		strcpy_s(m_LastErrorMsg, "未收到返回数据");
		return ERROR_SWITCH;
	}
	return SUCCESS;
}

void CEDFAGeneralSwitch4th::AnlysisErrorString(BYTE bStatus)
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

DWORD CEDFAGeneralSwitch4th::GetSingleSWPos(BYTE bySWIndex, //SW Number:1~M;
	BYTE &byPos)                  //Position
{
	BYTE sbBuffer[MAX_PATH];
	ZeroMemory(sbBuffer, MAX_PATH);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x08;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = 0xa5;
	sbBuffer[5] = 0x30;
	sbBuffer[6] = bySWIndex;

	BYTE bCheckSum = CalChecksum(sbBuffer, 7);

	sbBuffer[7] = bCheckSum;

	if (m_DevComHandle.WriteDevice(sbBuffer, 8) != SUCCESS)
	{
		strcpy_s(m_LastErrorMsg, "Get Switch Pos cmd error!");
		return ERROR_SWITCH;
	}

	ZeroMemory(sbBuffer, MAX_PATH);
	if (m_DevComHandle.ReadDevice((BYTE*)sbBuffer, MAX_PATH) != SUCCESS)
	{
		strcpy_s(m_LastErrorMsg, "Receive Switch Pos cmd error!");
		return ERROR_SWITCH;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return ERROR_SWITCH;
	}
	byPos = sbBuffer[7];
	return SUCCESS;
}
								   //MultiSW Control
DWORD CEDFAGeneralSwitch4th::SetMultiSWPos(BYTE *pbyPosArray, //All SW Position:0~N,0xFF; 0xFF:Keep in place
	BYTE bySWCount)                   //SW Count
{
	for (int i = 0;i < bySWCount;i++)
	{
		if (pbyPosArray[i] != 0xFF)
		{
			if (SetSingleSWPos(i + 1, pbyPosArray[i]) !=SUCCESS)
				return ERROR_SWITCH;
		}
	}
	return SUCCESS;
}

DWORD CEDFAGeneralSwitch4th::GetMultiSWPos(BYTE *pbyPosArray, //All SW Position
	BYTE bySWCount)                   //SW Count
{
	for (int i = 0;i < bySWCount;i++)
	{
		if (SetSingleSWPos(i + 1, pbyPosArray[i]) != SUCCESS)
		{
			return ERROR_SWITCH;
		}
	}
	return SUCCESS;
}

									   //~~~~~~~~InputVOA Set~~~~~~~~~~~~~~~~~~~~~~~~~~~
									   //Input VOA Set
DWORD CEDFAGeneralSwitch4th::SetInputVOAAtten(double dblAtten)
{
	BYTE sbBuffer[MAX_PATH];
	ZeroMemory(sbBuffer, MAX_PATH);
	short sAtten = 0;
	sAtten = (short)(dblAtten * 100);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x0a;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = 0x5a;
	sbBuffer[5] = 0x20;
	sbBuffer[6] = 0x01;
	sbBuffer[7] = (BYTE)(0x00ff & (sAtten >> 8));
	sbBuffer[8] = (BYTE)(0x00ff & sAtten);

	BYTE bCheckSum = CalChecksum(sbBuffer, 9);

	sbBuffer[9] = bCheckSum;

	if (m_DevComHandle.WriteDevice(sbBuffer, 10) != SUCCESS)
	{
		strcpy_s(m_LastErrorMsg, "Send Input VOA Attenuation cmd error!");
		return ERROR_SWITCH;
	}

	ZeroMemory(sbBuffer, MAX_PATH);
	if (m_DevComHandle.ReadDevice((BYTE*)sbBuffer, MAX_PATH) != SUCCESS)
	{
		strcpy_s(m_LastErrorMsg, "Receive Input VOA Attenuation cmd error!");
		return ERROR_SWITCH;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return ERROR_SWITCH;
	}
	return SUCCESS;
}

DWORD CEDFAGeneralSwitch4th::GetInputVOAAtten(double *pdblAtten)
{
	BYTE sbBuffer[MAX_PATH];
	ZeroMemory(sbBuffer, MAX_PATH);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x08;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = 0xa5;
	sbBuffer[5] = 0x20;
	sbBuffer[6] = 0x01;

	BYTE bCheckSum = CalChecksum(sbBuffer, 7);

	sbBuffer[7] = bCheckSum;

	if (m_DevComHandle.WriteDevice(sbBuffer, 8) != SUCCESS)
	{
		strcpy_s(m_LastErrorMsg, "Send Get Input VOA Attenuation cmd error!");
		return ERROR_SWITCH;
	}

	ZeroMemory(sbBuffer, MAX_PATH);
	if (m_DevComHandle.ReadDevice((BYTE*)sbBuffer, MAX_PATH) != SUCCESS)
	{
		strcpy_s(m_LastErrorMsg, "Receive Get Input VOA Attenuation cmd error!");
		return ERROR_SWITCH;
	}

	if (sbBuffer[3] != 0x00)
	{
	AnlysisErrorString(sbBuffer[3]);
	return ERROR_SWITCH;
	}

	short sAtten = 0xff00 & (sbBuffer[7] << 8);
	sAtten += 0x00ff & (sbBuffer[8]);

	*pdblAtten = sAtten / 100.0;
	return SUCCESS;
}
//MSA VOA Set
DWORD CEDFAGeneralSwitch4th::SetMSAVOAAtten(double dblAtten)
{
	BYTE sbBuffer[MAX_PATH];
	ZeroMemory(sbBuffer, MAX_PATH);
	short sAtten = 0;
	sAtten = (short)(dblAtten * 100);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x0a;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = 0x5a;
	sbBuffer[5] = 0x21;
	sbBuffer[6] = 0x01;
	sbBuffer[7] = (BYTE)(0x00ff & (sAtten >> 8));
	sbBuffer[8] = (BYTE)(0x00ff & sAtten);

	BYTE bCheckSum = CalChecksum(sbBuffer, 9);

	sbBuffer[9] = bCheckSum;

	if (m_DevComHandle.WriteDevice(sbBuffer, 10) != SUCCESS)
	{
		strcpy_s(m_LastErrorMsg, "Send MSA VOA Attenuation cmd error!");
		return ERROR_SWITCH;
	}

	ZeroMemory(sbBuffer, MAX_PATH);
	if (m_DevComHandle.ReadDevice((BYTE*)sbBuffer, MAX_PATH) != SUCCESS)
	{
		strcpy_s(m_LastErrorMsg, "Receive MSA VOA Attenuation cmd error!");
		return ERROR_SWITCH;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return ERROR_SWITCH;
	}
	return SUCCESS;
}
DWORD CEDFAGeneralSwitch4th::GetMSAVOAAtten(double *pdblAtten)
{
	BYTE sbBuffer[MAX_PATH];
	ZeroMemory(sbBuffer, MAX_PATH);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x08;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = 0xa5;
	sbBuffer[5] = 0x21;
	sbBuffer[6] = 0x01;

	BYTE bCheckSum = CalChecksum(sbBuffer, 7);

	sbBuffer[7] = bCheckSum;

	if (m_DevComHandle.WriteDevice(sbBuffer, 8) != SUCCESS)
	{
		strcpy_s(m_LastErrorMsg, "Send Get Input VOA Attenuation cmd error!");
		return ERROR_SWITCH;
	}

	ZeroMemory(sbBuffer, MAX_PATH);
	if (m_DevComHandle.ReadDevice((BYTE*)sbBuffer, MAX_PATH) != SUCCESS)
	{
		strcpy_s(m_LastErrorMsg, "Receive Get Input VOA Attenuation cmd error!");
		return ERROR_SWITCH;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return ERROR_SWITCH;
	}

	short sAtten = 0xff00 & (sbBuffer[7] << 8);
	sAtten += 0x00ff & (sbBuffer[8]);

	*pdblAtten = sAtten / 100.0;
	return SUCCESS;
}

//~~~~~~~~SW Path~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
DWORD CEDFAGeneralSwitch4th::SetLDSSelection(BYTE bySrcIndex) //1~8;SW1
{
	if (bySrcIndex < 1|| bySrcIndex > 8)
	{
		strcpy_s(m_LastErrorMsg, 1024, "参数出错！");
		return ERROR_SWITCH;
	}
	return SetSingleSWPos(1, bySrcIndex-1);	
}
												//S1~8->IN1~17
DWORD CEDFAGeneralSwitch4th::SetLDSToDutIn(BYTE byDutInIndex) //1~17;SW2+SW9
{
	if (byDutInIndex < 1 || byDutInIndex > 17)
	{
		strcpy_s(m_LastErrorMsg, 1024, "参数出错！");
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(9, 0) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(2, byDutInIndex) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	return SUCCESS;
}
												//S1~8->Out1~18
DWORD CEDFAGeneralSwitch4th::SetLDSToDutOut(BYTE byDutOutIndex)//1~18;SW3+SW9
{
	if (byDutOutIndex < 1 || byDutOutIndex > 18)
	{
		strcpy_s(m_LastErrorMsg, 1024, "参数出错！");
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(9, 1) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(3, byDutOutIndex) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	return SUCCESS;
}
												 //OPM/OSA
DWORD CEDFAGeneralSwitch4th::SetLDSToMonPath(BYTE byDestPos)//1~2;SW4
{
	if (byDestPos < 1 || byDestPos > 2)
	{
		strcpy_s(m_LastErrorMsg, 1024, "参数出错！");
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(4, byDestPos-1) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	return SUCCESS;
}
DWORD CEDFAGeneralSwitch4th::SetLDSToRefPath(BYTE byDestPos)//1~2;SW2+SW4+SW5+SW9
{
	if (byDestPos < 1 || byDestPos > 2)
	{
		strcpy_s(m_LastErrorMsg, 1024, "参数出错！");
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(2, 18) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(9, 0) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(5, 1) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(4, byDestPos-1) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	return SUCCESS;
}
DWORD CEDFAGeneralSwitch4th::SetDutOutToDest(BYTE byDutOutIndex, BYTE byDestPos)//SW3+SW4+SW5+SW9
{
	if (byDutOutIndex < 1 || byDutOutIndex > 18)
	{
		strcpy_s(m_LastErrorMsg, 1024, "参数出错！");
		return ERROR_SWITCH;
	}
	if (byDestPos < 1 || byDestPos > 2)
	{
		strcpy_s(m_LastErrorMsg, 1024, "参数出错！");
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(3, byDutOutIndex) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(9, 0) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(5, 0) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(4, byDestPos-1) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	return SUCCESS;
}
DWORD CEDFAGeneralSwitch4th::SetDutInAsOutput(BYTE byDutInIndex, BYTE byDestPos)//SW2+SW4+SW5+SW9
{
	if (byDutInIndex < 1 || byDutInIndex > 17)
	{
		strcpy_s(m_LastErrorMsg, 1024, "参数出错！");
		return ERROR_SWITCH;
	}
	if (byDestPos < 1 || byDestPos > 2)
	{
		strcpy_s(m_LastErrorMsg, 1024, "参数出错！");
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(2, byDutInIndex) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(9, 1) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(5, 0) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(4, byDestPos-1) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	return SUCCESS;
}

DWORD CEDFAGeneralSwitch4th::SetDutOut98ToEO1(BYTE byDutOutIndex, BYTE byDestPos)//SW3+SW4+SW5+SW9;OUT_98 connect to EO1
{
	if (byDutOutIndex < 1 || byDutOutIndex > 18)
	{
		strcpy_s(m_LastErrorMsg, 1024, "参数出错！");
		return ERROR_SWITCH;
	}
	if (byDestPos < 1 || byDestPos > 2)
	{
		strcpy_s(m_LastErrorMsg, 1024, "参数出错！");
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(3, byDutOutIndex) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(9, 0) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(5, 5) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(4, byDestPos-1) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	return SUCCESS;
}
DWORD CEDFAGeneralSwitch4th::SetDutIn98AsOutputToEO1(BYTE byDutInIndex, BYTE byDestPos)//SW2+SW4+SW5+SW9；OUT_98 connect to EO1
{
	if (byDutInIndex < 1 || byDutInIndex > 17)
	{
		strcpy_s(m_LastErrorMsg, 1024, "参数出错！");
		return ERROR_SWITCH;
	}
	if (byDestPos < 1 || byDestPos > 2)
	{
		strcpy_s(m_LastErrorMsg, 1024, "参数出错！");
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(2, byDutInIndex) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(9, 1) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(5, 5) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(4, byDestPos-1) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	return SUCCESS;
}
																		 //MAS IN->MAS OUT
DWORD CEDFAGeneralSwitch4th::SetMSAInToMSAOut(BYTE byMsaInPort, BYTE byMsaOutPort, double dblMsaVOAAtten) //SW6+SW7+SW8
{
	if (byMsaInPort < 1 || byMsaInPort > 8)
	{
		strcpy_s(m_LastErrorMsg, 1024, "参数出错！");
		return ERROR_SWITCH;
	}
	if (byMsaOutPort < 1 || byMsaOutPort > 8)
	{
		strcpy_s(m_LastErrorMsg, 1024, "参数出错！");
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(7, byMsaInPort-1) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(8, 0) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(6, byMsaOutPort-1) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	if (SetMSAVOAAtten(dblMsaVOAAtten) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	return SUCCESS;
}
DWORD CEDFAGeneralSwitch4th::SetMSATapToDest(BYTE byMsaOutPort, BYTE byDestPos) //SW4+SW5+SW6+SW8
{
	if (byMsaOutPort < 1 || byMsaOutPort > 8)
	{
		strcpy_s(m_LastErrorMsg, 1024, "参数出错！");
		return ERROR_SWITCH;
	}
	if (byDestPos < 1 || byDestPos > 2)
	{
		strcpy_s(m_LastErrorMsg, 1024, "参数出错！");
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(6, byMsaOutPort - 1) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(8, 0) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(5, 2) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(4, byDestPos - 1) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	return SUCCESS;
}
DWORD CEDFAGeneralSwitch4th::SetMSAInAsOutput(BYTE byMsaInPort, BYTE byDestPos) //SW4+SW5+SW7+SW8
{
	if (byMsaInPort < 1 || byMsaInPort > 8)
	{
		strcpy_s(m_LastErrorMsg, 1024, "参数出错！");
		return ERROR_SWITCH;
	}
	if (byDestPos < 1 || byDestPos > 2)
	{
		strcpy_s(m_LastErrorMsg, 1024, "参数出错！");
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(7, byMsaInPort-1) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(8, 1) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(5, 4) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(4, byDestPos-1) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	return SUCCESS;
}
DWORD CEDFAGeneralSwitch4th::SetMSAOutAsOutput(BYTE byMsaOutPort, BYTE byDestPos) //SW4+SW5+SW6+SW8
{
	if (byMsaOutPort < 1 || byMsaOutPort > 8)
	{
		strcpy_s(m_LastErrorMsg, 1024, "参数出错！");
		return ERROR_SWITCH;
	}
	if (byDestPos < 1 || byDestPos > 2)
	{
		strcpy_s(m_LastErrorMsg, 1024, "参数出错！");
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(6, byMsaOutPort-1) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(8, 1) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(5, 3) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(4, byDestPos-1) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	return SUCCESS;
}

DWORD CEDFAGeneralSwitch4th::SetMSAOut98AsOutputToEO2(BYTE byMsaOutPort, BYTE byDestPos) //SW4+SW5+SW6+SW8;MOP_98 connect to EO2
{
	if (byMsaOutPort < 1 || byMsaOutPort > 8)
	{
		strcpy_s(m_LastErrorMsg, 1024, "参数出错！");
		return ERROR_SWITCH;
	}
	if (byDestPos < 1 || byDestPos > 2)
	{
		strcpy_s(m_LastErrorMsg, 1024, "参数出错！");
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(6, byMsaOutPort-1) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(8, 1) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(5, 6) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	if (SetSingleSWPos(4, byDestPos-1) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	return SUCCESS;
}
																   //Expand Port
DWORD CEDFAGeneralSwitch4th::SetEOPortToDest(BYTE byEOPort, BYTE byDestPos) //EO1~3 SW4+SW5;
{
	if (byEOPort < 1 || byEOPort > 3)
	{
		strcpy_s(m_LastErrorMsg, 1024, "参数出错！");
		return ERROR_SWITCH;
	}
	if (byDestPos < 1 || byDestPos > 2)
	{
		strcpy_s(m_LastErrorMsg, 1024, "参数出错！");
		return ERROR_SWITCH;
	}
	//byEOPort=1时为EO1，SW5需要切换到5，EO2-6，EO3-7
	if (SetSingleSWPos(5, byEOPort+4) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	
	if (SetSingleSWPos(4, byDestPos - 1) != SUCCESS)
	{
		return ERROR_SWITCH;
	}
	return SUCCESS;
}

															  //~~~~~~~~~~~~~Trigger~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//暂不支持														  //VOA Drive Trigger
DWORD CEDFAGeneralSwitch4th::SetVOATriggerOut(double dblStartAtten, double dblEndAtten, double dblStepAtten, WORD wOPMWaitTimeMs)
{
	return SUCCESS;
}
//暂不支持
//SW Drive Trigger
DWORD CEDFAGeneralSwitch4th::SetSWPathMapping(char *pchBinfileName)
{
	return SUCCESS;
}
//暂不支持
DWORD CEDFAGeneralSwitch4th::SetSWTriggerPathScanStart(WORD wExitTimeOutSecond)
{
	return SUCCESS;
}
//Query Scan Status
//DWORD GetTriggerScanStatus(BYTE &byStatus);

//~~~~~~~~GPIO Setting~~~~~~~~~~~~~~~~~~~~~~~~~~
//看协议只有32为，但是ctrl+Alarm需要32位
DWORD CEDFAGeneralSwitch4th::SetGPIOStatus(WORD wAlarmIN, WORD wAlarmOut)
{
	return SUCCESS;
}

DWORD CEDFAGeneralSwitch4th::GetGPIOStatus(WORD *pwAlarmIN, WORD *pwAlarmOut)
{
	return SUCCESS;
}

DWORD CEDFAGeneralSwitch4th::SetGPIOVoltage(bool bVoltage5V)
{
	return SUCCESS;
}

//~~~~~~~~UART Setting~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Struct 
//byUARTIndex =0Xff: ALL
DWORD CEDFAGeneralSwitch4th::SetUARTConfig(BYTE byUARTIndex, stSerialPortCfg stSerialPortCfgValue, DWORD dwTimeOut)
{
	BYTE sbBuffer[MAX_PATH];
	ZeroMemory(sbBuffer, MAX_PATH);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x13;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = 0x5a;
	sbBuffer[5] = 0x50;
	sbBuffer[6] = byUARTIndex;
	sbBuffer[7] = (BYTE)(0x000000ff & (stSerialPortCfgValue.dwBaudRate>>24));
	sbBuffer[8] = (BYTE)(0x000000ff & (stSerialPortCfgValue.dwBaudRate>>16));
	sbBuffer[9] = (BYTE)(0x000000ff & (stSerialPortCfgValue.dwBaudRate>>8));
	sbBuffer[10] = (BYTE)(0x000000ff & stSerialPortCfgValue.dwBaudRate);
	sbBuffer[11] = stSerialPortCfgValue.byByteSize;
	sbBuffer[12] = stSerialPortCfgValue.byParity;
	sbBuffer[13] = stSerialPortCfgValue.byStopBits;
	sbBuffer[14] = (BYTE)(0x000000ff & (dwTimeOut >> 24));
	sbBuffer[15] = (BYTE)(0x000000ff & (dwTimeOut >> 16));
	sbBuffer[16] = (BYTE)(0x000000ff & (dwTimeOut >> 8));
	sbBuffer[17] = (BYTE)(0x000000ff & dwTimeOut);


	BYTE bCheckSum = CalChecksum(sbBuffer, 18);

	sbBuffer[18] = bCheckSum;

	if (m_DevComHandle.WriteDevice(sbBuffer, 19) != SUCCESS)
	{
		strcpy_s(m_LastErrorMsg, "Get Device Info cmd error!");
		return ERROR_SWITCH;
	}
	
	ZeroMemory(sbBuffer, MAX_PATH);
	if (m_DevComHandle.ReadDevice((BYTE*)sbBuffer, MAX_PATH) != SUCCESS)
	{
		strcpy_s(m_LastErrorMsg, "Receive Device Info cmd error!");
		return ERROR_SWITCH;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return ERROR_SWITCH;
	}
	return SUCCESS;
}
DWORD CEDFAGeneralSwitch4th::WriteUARTData(BYTE byUARTIndex, BYTE* pbyBuffer, WORD wLength)
{
	BYTE sbBuffer[MAX_PATH];
	ZeroMemory(sbBuffer, MAX_PATH);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = wLength + 8;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = 0x5a;
	sbBuffer[5] = 0x51;
	sbBuffer[6] = byUARTIndex;
	for (int i = 0;i < wLength;i++)
	{
		sbBuffer[7 + i] = pbyBuffer[i];
	}

	BYTE bCheckSum = CalChecksum(sbBuffer, wLength+7);

	sbBuffer[wLength + 7] = bCheckSum;

	if (m_DevComHandle.WriteDevice(sbBuffer, wLength+8) != SUCCESS)
	{
		strcpy_s(m_LastErrorMsg, "Write UART Data cmd error!");
		return ERROR_SWITCH;
	}
	
	ZeroMemory(sbBuffer, MAX_PATH);
	if (m_DevComHandle.ReadDevice((BYTE*)sbBuffer, MAX_PATH) != SUCCESS)
	{
		strcpy_s(m_LastErrorMsg, "Receive Write UART Data cmd error!");
		return ERROR_SWITCH;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return ERROR_SWITCH;
	}
	return SUCCESS;
}
//要返回的数据是什么，先发送，后接收？
DWORD CEDFAGeneralSwitch4th::ReadUARTData(BYTE byUARTIndex, BYTE* pbyBuffer, WORD wLength, WORD *pwGetLength)
{
	BYTE sbBuffer[MAX_PATH];
	ZeroMemory(sbBuffer, MAX_PATH);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x08;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = 0xa5;
	sbBuffer[5] = 0x51;
	sbBuffer[6] = byUARTIndex;

	BYTE bCheckSum = CalChecksum(sbBuffer, 7);
	sbBuffer[7] = bCheckSum;

	if (m_DevComHandle.WriteDevice(sbBuffer, 8) != SUCCESS)
	{
		strcpy_s(m_LastErrorMsg, "Send Read UART Data cmd error!");
		return ERROR_SWITCH;
	}

	ZeroMemory(sbBuffer, MAX_PATH);
	if (m_DevComHandle.ReadDevice((BYTE*)sbBuffer, MAX_PATH) != SUCCESS)
	{
		strcpy_s(m_LastErrorMsg, "Read UART Data cmd error!");
		return ERROR_SWITCH;
	}

	//解析串口读到的数据
	
	return SUCCESS;
}

//~~~~~~~~~BasicInfo~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//开关切换次数/校准日期/生产日期
DWORD CEDFAGeneralSwitch4th::GetDeviceInfo(pstDevInfo pstSWInfo)
{
	BYTE sbBuffer[MAX_PATH];
	ZeroMemory(sbBuffer, MAX_PATH);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x09;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = 0xa5;
	sbBuffer[5] = 0x01;
	sbBuffer[6] = 0x01;
	sbBuffer[7] = 0x08;

	BYTE bCheckSum = CalChecksum(sbBuffer, 8);

	sbBuffer[8] = bCheckSum;

	if (m_DevComHandle.WriteDevice(sbBuffer, 9)!=SUCCESS)
	{
		strcpy_s(m_LastErrorMsg, "Get Device Info cmd error!");
		return ERROR_SWITCH;
	}
	
	ZeroMemory(sbBuffer, MAX_PATH);
	if (m_DevComHandle.ReadDevice((BYTE*)sbBuffer, MAX_PATH) != SUCCESS)
	{
		strcpy_s(m_LastErrorMsg, "Receive Device Info cmd error!");
		return ERROR_SWITCH;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return ERROR_SWITCH;
	}
	if (pstSWInfo == NULL)
	{
		strcpy_s(m_LastErrorMsg, "");
		return ERROR_SWITCH;
	}
	memcpy_s(pstSWInfo->pszSerialNum, 256, sbBuffer + 16, 16);
	memcpy_s(pstSWInfo->pszHWVer, 256, sbBuffer + 64, 8);
	memcpy_s(pstSWInfo->pszFWVer, 256, sbBuffer + 72, 8);
	memcpy_s(pstSWInfo->pszMFDate, 256, sbBuffer + 88, 16);
	memcpy_s(pstSWInfo->pszName, 256, sbBuffer + 32, 32);
	return SUCCESS;
}
//暂不支持
DWORD CEDFAGeneralSwitch4th::GetSwitchingCnt(BYTE bySWIndex, DWORD *pdwSwitchingCnt) //只针对机械式开关
{
	return SUCCESS;
}

//待讨论																	   //~~~~~~~~IL/WDL Value~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
DWORD CEDFAGeneralSwitch4th::GetInputMinIL(BYTE bySWIndex, double * pdblGetMinIL)
{
	return SUCCESS;
}

DWORD CEDFAGeneralSwitch4th::SetBlockBySwitch(BYTE bySrcIndex)
{
	return SUCCESS;
}