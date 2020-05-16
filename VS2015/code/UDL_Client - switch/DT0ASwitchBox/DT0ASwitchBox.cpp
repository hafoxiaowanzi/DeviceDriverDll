// DT0ASwitchBox.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "DT0ASwitchBox.h"


/////////////////////////////////////////////////////////////
//函数说明：
//    打开第四代开关盒
//Add by wanxin
//20180124
//////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle)
{
	//CString strComPort;	
	DWORD   dwErrorCode = FALSE;

	dwErrorCode = m_DevComHandle.OpenDevice(pszDeviceAddr,*ComHandle);
	if (dwErrorCode != SUCCESS)
	{
		return FALSE;
	}	
	return TRUE;
}
/////////////////////////////////////////////////////////////
//函数说明：
//    关闭第四代开关盒
//Add by wanxin
//20180124
//////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::CloseDevice()
{
	DWORD   dwErrorCode =SUCCESS;
	dwErrorCode = m_DevComHandle.CloseDevice();
	if (dwErrorCode!=SUCCESS)
	{
		sprintf(m_strMsg,"Open Device error");
		return FALSE;
	}
	return TRUE;
}
/////////////////////////////////////////////////////////////
//函数说明：
//    设置设备句柄指针
//Add by wanxin
//20140821
//////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle)
{
	DWORD   dwErrorCode=SUCCESS;
    
	dwErrorCode = m_DevComHandle.SetDeviceHandle(pszDeviceAddr, handle);
	if (dwErrorCode!=SUCCESS)
	{
		sprintf(m_strMsg,"Set Device Handle error");
		return FALSE;
	}
	return TRUE;
}


char* CDT0ASwitchBox::GetMsgString()
{
	return (char*)&m_strMsg;
}

BYTE CDT0ASwitchBox::GetChecksum(BYTE* pbBuffer, int nLength)
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
void CDT0ASwitchBox::AnlysisErrorString(BYTE bStatus)
{
	switch (bStatus)
	{
	case 0x10:
	{
		sprintf(m_strMsg,"Command executed failed.");
	}
	break;
	case 0x11:
	{
		sprintf(m_strMsg,"INCOMPLETE.");
	}
	break;
	case 0x12:
	{
		sprintf(m_strMsg,"System BUSY.");
	}
	break;
	case 0x20:
	{
		sprintf(m_strMsg,"Message SyncHead Error / Reserved.");
	}
	break;
	case 0x21:
	{
		sprintf(m_strMsg,"Message Length Error.");
	}
	break;
	case 0x22:
	{
		sprintf(m_strMsg,"Message Status Error.");
	}
	break;
	case 0x23:
	{
		sprintf(m_strMsg,"Message Access Error.");
	}
	break;
	case 0x24:
	{
		sprintf(m_strMsg,"Message Object Error.");
	}
	break;
	case 0x25:
	{
		sprintf(m_strMsg,"Message Instance Error.");
	}
	break;
	case 0x26:
	{
		sprintf(m_strMsg,"Message Payload Error.");
	}
	break;
	case 0x27:
	{
		sprintf(m_strMsg,"Message Checksum Error.");
	}
	break;
	case 0x28:
	{
		sprintf(m_strMsg,"Sub Module not in or Error.");
	}
	break;
	}
}

////////////////////////////////////////////////////////////
//函数说明：
//    获得PN信息
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::GetPNInfo(char *pstrPN)
{
	DWORD dwErrorCode = SUCCESS;
	BYTE sbBuffer[MAX_PATH];
	BYTE bPN[16];
	ZeroMemory(sbBuffer, MAX_PATH);
	ZeroMemory(bPN, 16);
	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x08;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_READ;
	sbBuffer[5] = 0x02;
	sbBuffer[6] = 0x01;
	BYTE bCheckSum = GetChecksum(sbBuffer, 7);

	sbBuffer[7] = bCheckSum;

	dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 8);
	if (dwErrorCode !=SUCCESS)
	{
		sprintf(m_strMsg,"Send Get PN infomation cmd error!");
		return FALSE;
	}
	Sleep(50);
	ZeroMemory(sbBuffer, MAX_PATH);
	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH;
	if (dwErrorCode !=SUCCESS)
	{
		sprintf(m_strMsg,"Receive Get PN infomation cmd error!");
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}
	memcpy(bPN, sbBuffer + 7, 16);
    if(pstrPN==NULL)
	{
		sprintf(m_strMsg,"The pstrPN is NULL !");
		return FALSE;
	}
	strcpy(pstrPN,bPN);

	return TRUE;
}

////////////////////////////////////////////////////////////
//函数说明：
//    获得SN信息
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::GetSNInfo(char *pstrSN)
{
	BYTE sbBuffer[MAX_PATH];
	BYTE bValueTemp[16];
	DWORD dwErrorCode = SUCCESS;
	ZeroMemory(sbBuffer, MAX_PATH);
	
	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x08;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_READ;
	sbBuffer[5] = 0x03;
	sbBuffer[6] = 0x01;
	BYTE bCheckSum = GetChecksum(sbBuffer, 7);

	sbBuffer[7] = bCheckSum;
    dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 8);

	if (dwErrorCode != SUCCESS)
	{
		sprintf(m_strMsg,"Send Get PN information cmd error!");
		return FALSE;
	}
	Sleep(50);

	ZeroMemory(sbBuffer, MAX_PATH);
	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH));
	if (dwErrorCode != SUCCESS)
	{
		sprintf(m_strMsg,"Receive Get PN information cmd error!");
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}

	memcpy(bValueTemp, sbBuffer + 7, 16);
    if(pstrPN==NULL)
	{
		sprintf(m_strMsg,"The pstrSN is NULL !");
		return FALSE;
	}
	strcpy(pstrSN,bValueTemp);

	return TRUE;
}

////////////////////////////////////////////////////////////
//函数说明：
//    获得EquipmentNo信息
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::GetEquipmentInfo(char *pstrEquipment)
{
	DWORD dwErrorCode = SUCCESS;
	BYTE sbBuffer[MAX_PATH];
	BYTE bValueTemp[16];
	ZeroMemory(bValueTemp, 16);
	ZeroMemory(sbBuffer, MAX_PATH);
	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x08;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_READ;
	sbBuffer[5] = 0x04;
	sbBuffer[6] = 0x01;
	BYTE bCheckSum = GetChecksum(sbBuffer, 7);

	sbBuffer[7] = bCheckSum;

	dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 8);

	if (dwErrorCode != SUCCESS)
	{
		sprintf(m_strMsg,"Send Get Equipment infomation cmd error!");
		return FALSE;
	}
	Sleep(50);
	ZeroMemory(sbBuffer, MAX_PATH);
	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);

	if (dwErrorCode !=SUCCESS)
	{
		sprintf(m_strMsg,"Receive Get Equipment infomation cmd error!");
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}
	memcpy(bValueTemp, sbBuffer + 7, 16);
    if(pstrEquipment==NULL)
	{
		sprintf(m_strMsg,"The pstrEquipment is NULL !");
		return FALSE;
	}
	strcpy(pstrEquipment,bValueTemp);
	return TRUE;
}

////////////////////////////////////////////////////////////
//函数说明：
//    获得HW Version信息
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::GetHWInfo(char *pstrHWVersion)
{
	DWORD dwErrorCode = SUCCESS;
	BYTE sbBuffer[MAX_PATH];
	BYTE bValueTemp[8];
	ZeroMemory(bValueTemp, 8);
	ZeroMemory(sbBuffer, MAX_PATH);
	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x08;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_READ;
	sbBuffer[5] = 0x05;
	sbBuffer[6] = 0x01;
	BYTE bCheckSum = GetChecksum(sbBuffer, 7);

	sbBuffer[7] = bCheckSum;

    dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 8);

	if (!dwErrorCode !=SUCCESS)
	{
		sprintf(m_strMsg,"Send Get HW infomation cmd error!");
		return FALSE;
	}
	Sleep(50);

	ZeroMemory(sbBuffer, MAX_PATH);
	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);
	if (dwErrorCode!=SUCCESS)
	{
		sprintf(m_strMsg,"Receive Get HW infomation cmd error!");
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}
	memcpy(bValueTemp, sbBuffer + 7, 8);
    if(pstrEquipment==NULL)
	{
		sprintf(m_strMsg,"The pstrHWVersion is NULL !");
		return FALSE;
	}
	strcpy(pstrHWVersion,bValueTemp);
	return TRUE;
}
////////////////////////////////////////////////////////////
//函数说明：
//    获得FW Version信息
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::GetFWInfo(char *pstrFWVersion)
{
	BYTE sbBuffer[MAX_PATH];
	BYTE bValueTemp[8];
	ZeroMemory(bValueTemp, 8);
	ZeroMemory(sbBuffer, MAX_PATH);
	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x08;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_READ;
	sbBuffer[5] = 0x06;
	sbBuffer[6] = 0x01;
	BYTE bCheckSum = GetChecksum(sbBuffer, 7);
	sbBuffer[7] = bCheckSum;
	DWORD dwErrorCode = SUCCESS;

	dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 8);

	if (!dwErrorCode !=SUCCESS)
	{
		sprintf(m_strMsg,"Send Get FW infomation cmd error!");
		return FALSE;
	}

	Sleep(50);

	ZeroMemory(sbBuffer, MAX_PATH);
	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);
	if (dwErrorCode!=SUCCESS)
	{
		sprintf(m_strMsg,"Receive Get FW infomation cmd error!");
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}
	memcpy(bValueTemp, sbBuffer + 7, 8);
    if(pstrFWVersion==NULL)
	{
		sprintf(m_strMsg,"The pstrFWVersion is NULL !");
		return FALSE;
	}
	strcpy(pstrFWVersion,bValueTemp);
	return TRUE;
}
////////////////////////////////////////////////////////////
//函数说明：
//    获得Oplink FW Version信息
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::GetOplinkFWInfo(char *pstrOplinkVersion)
{
	BYTE sbBuffer[MAX_PATH];
	BYTE bValueTemp[8];
	ZeroMemory(bValueTemp, 8);
	ZeroMemory(sbBuffer, MAX_PATH);
	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x08;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_READ;
	sbBuffer[5] = 0x07;
	sbBuffer[6] = 0x01;
	BYTE bCheckSum = GetChecksum(sbBuffer, 7);
	sbBuffer[7] = bCheckSum;

	DWORD dwErrorCode = SUCCESS;

	dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 8);

	if (!dwErrorCode !=SUCCESS)
	{
		sprintf(m_strMsg,"Send Get Oplink FW infomation cmd error!");
		return FALSE;
	}

	Sleep(50);

	ZeroMemory(sbBuffer, MAX_PATH);

	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);
	if (dwErrorCode!=SUCCESS)
	{
		sprintf(m_strMsg,"Receive Get Oplink FW infomation cmd error!");
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}
	memcpy(bValueTemp, sbBuffer + 7, 8);
    if(pstrOplinkVersion==NULL)
	{
		sprintf(m_strMsg,"The pstrOplinkVersion is NULL !");
		return FALSE;
	}
	strcpy(pstrOplinkVersion,bValueTemp);
	return TRUE;
}
////////////////////////////////////////////////////////////
//函数说明：
//    获取MFG生产日志
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::GetMFGDateInfo(char* pstrMFGDate)
{
	BYTE sbBuffer[MAX_PATH];
	BYTE bValueTemp[32];
	ZeroMemory(bValueTemp, 32);
	ZeroMemory(sbBuffer, MAX_PATH);
	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x08;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_READ;
	sbBuffer[5] = 0x01;
	sbBuffer[6] = 0x01;
	BYTE bCheckSum = GetChecksum(sbBuffer, 7);

	sbBuffer[7] = bCheckSum;

	DWORD dwErrorCode = SUCCESS;

	dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 8);

	if (!dwErrorCode !=SUCCESS)
	{
		sprintf(m_strMsg,"Send get MFG date infomation cmd error!");
		return FALSE;
	}

	Sleep(50);
	ZeroMemory(sbBuffer, MAX_PATH);

	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);
	if (dwErrorCode!=SUCCESS)
	{
		sprintf(m_strMsg,"Receive get MFG date infomation error!");
		return FALSE;
	}

	if (sbBuffer[3]!= 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}

	ZeroMemory(bValueTemp, 32);
	memcpy(bValueTemp, sbBuffer + 95, 16);
    if(pstrMFGDate==NULL)
	{
		sprintf(m_strMsg,"The pstrMFGDate is NULL !");
		return FALSE;
	}
	strcpy(pstrMFGDate,bValueTemp);

	return TRUE;
}
////////////////////////////////////////////////////////////
//函数说明：
//    设置 Input端shutter VOA 衰减值
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::SetInputVOAAtten(double dbAtten)
{
	BYTE sbBuffer[MAX_PATH];
	short sAtten = 0;
	ZeroMemory(sbBuffer, MAX_PATH);
	sAtten = (short)(dbAtten*100);
	
	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x0A;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_WRITE;
	sbBuffer[5] = 0x20;
	sbBuffer[6] = 0x01;
	sbBuffer[7] = (BYTE)(0x00ff & (sAtten>>8));
	sbBuffer[8] = (BYTE)(0x00ff & sAtten);
	BYTE bCheckSum = GetChecksum(sbBuffer, 9);
	
	sbBuffer[9] = bCheckSum;
	
	DWORD dwErrorCode = SUCCESS;
	
	dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 10);
		
	if (!dwErrorCode !=SUCCESS)
	{
		sprintf(m_strMsg,"Send Input VOA Attenuation cmd error!");
		return FALSE;
	}


	Sleep(50);
	ZeroMemory(sbBuffer, MAX_PATH);

	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);
	if (dwErrorCode!=SUCCESS)
	{
		sprintf(m_strMsg,"Receive Input VOA Attenuation cmd error!");
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}

	return TRUE;
}

////////////////////////////////////////////////////////////
//函数说明：
//    读取Input端shutter VOA 衰减值
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::GetInputVOAAtten(double *pdbAtten)
{
	BYTE sbBuffer[MAX_PATH];
	short sAtten = 0;
	ZeroMemory(sbBuffer, MAX_PATH);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x08;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_READ;
	sbBuffer[5] = 0x20;
	sbBuffer[6] = 0x01;
	BYTE bCheckSum = GetChecksum(sbBuffer, 7);

	sbBuffer[7] = bCheckSum;

	DWORD dwErrorCode = SUCCESS;
	
	dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 8);
		
	if (!dwErrorCode !=SUCCESS)
	{
		sprintf(m_strMsg,"Send Input VOA Attenuation cmd error!");
		return FALSE;
	}

	Sleep(50);

	ZeroMemory(sbBuffer, MAX_PATH);

	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);
	if (dwErrorCode!=SUCCESS)
	{
		sprintf(m_strMsg,"Receive Get Input VOA Attenuation cmd error!");
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}

	sAtten = 0xff00 & (sbBuffer[7] << 8);
	sAtten += 0x00ff & (sbBuffer[8]);

	*pdbAtten = sAtten / 100.0;

	return TRUE;
}


////////////////////////////////////////////////////////////
//函数说明：
//    设置MSA端shutter VOA 衰减值
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::SetMSAVOAAtten(double dbAtten)
{
	BYTE sbBuffer[MAX_PATH];
	short sAtten = 0;
	ZeroMemory(sbBuffer, MAX_PATH);
	sAtten = (short)(dbAtten * 100);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x0A;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_WRITE;
	sbBuffer[5] = 0x21;
	sbBuffer[6] = 0x01;
	sbBuffer[7] = (BYTE)(0x00ff & (sAtten >> 8));
	sbBuffer[8] = (BYTE)(0x00ff & sAtten);
	BYTE bCheckSum = GetChecksum(sbBuffer, 9);

	sbBuffer[9] = bCheckSum;

	DWORD dwErrorCode = SUCCESS;
	
	dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 10);
		
	if (!dwErrorCode !=SUCCESS)
	{
		sprintf(m_strMsg,"Send MSA VOA Attenuation cmd error!");
		return FALSE;
	}

	Sleep(50);

	ZeroMemory(sbBuffer, MAX_PATH);
	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);
	if (dwErrorCode!=SUCCESS)
	{
		sprintf(m_strMsg,"Receive MSA VOA Attenuation cmd error!");
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}

	return TRUE;
}

////////////////////////////////////////////////////////////
//函数说明：
//    读取Input端shutter VOA 衰减值
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::GetMSAVOAAtten(double *pdbAtten)
{
	BYTE sbBuffer[MAX_PATH];
	short sAtten = 0;
	ZeroMemory(sbBuffer, MAX_PATH);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x08;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_READ;
	sbBuffer[5] = 0x21;
	sbBuffer[6] = 0x01;
	BYTE bCheckSum = GetChecksum(sbBuffer, 7);

	sbBuffer[7] = bCheckSum;

	DWORD dwErrorCode = SUCCESS;
	
	dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 8);	
	if (!dwErrorCode !=SUCCESS)
	{
		sprintf(m_strMsg,"Send Get MSA VOA Attenuation cmd error!");
		return FALSE;
	}

	Sleep(50);

	ZeroMemory(sbBuffer, MAX_PATH);
	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);
	if (dwErrorCode!=SUCCESS)
	{
		sprintf(m_strMsg,"Receive Get MSA VOA Attenuation cmd error!");
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}

	sAtten = 0xff00 & (sbBuffer[7] << 8);
	sAtten += 0x00ff & (sbBuffer[8]);

	*pdbAtten = sAtten / 100.0;

	return TRUE;
}

////////////////////////////////////////////////////////////
//函数说明：
//    设置VOAx 衰减值
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::SetVOAxAtten(BYTE bInstance,double dbAtten)
{
	BYTE sbBuffer[MAX_PATH];
	short sAtten = 0;
	ZeroMemory(sbBuffer, MAX_PATH);
	sAtten = (short)(dbAtten * 100);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x0A;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_WRITE;
	sbBuffer[5] = 0x22;
	sbBuffer[6] = bInstance;
	sbBuffer[7] = (BYTE)(0x00ff & (sAtten >> 8));
	sbBuffer[8] = (BYTE)(0x00ff & sAtten);
	BYTE bCheckSum = GetChecksum(sbBuffer, 9);

	sbBuffer[9] = bCheckSum;

	DWORD dwErrorCode = SUCCESS;
	
	dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 10);	
	if (!dwErrorCode !=SUCCESS)
	{
		sprintf(m_strMsg,"Send VOAx Attenuation cmd error!");
		return FALSE;
	}

	Sleep(50);

	ZeroMemory(sbBuffer, MAX_PATH);
	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);
	if (dwErrorCode!=SUCCESS)
	{
		sprintf(m_strMsg,"Receive VOAx Attenuation cmd error!");
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}

	return TRUE;
}


////////////////////////////////////////////////////////////
//函数说明：
//    设置VOAx 衰减值
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::SetVOAxAttenToDiffrentValue(double dbAtten1,double dbAtten2)
{
	BYTE sbBuffer[MAX_PATH];
	short sAtten1 = 0;
	short sAtten2 = 0;
	ZeroMemory(sbBuffer, MAX_PATH);
	sAtten1 = (short)(dbAtten1 * 100);
	sAtten2 = (short)(dbAtten2 * 100);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x0C;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_WRITE;
	sbBuffer[5] = 0x22;
	sbBuffer[6] = 0xFF;
	sbBuffer[7] = (BYTE)(0x00ff & (sAtten1 >> 8));
	sbBuffer[8] = (BYTE)(0x00ff & sAtten1);
	sbBuffer[9] = (BYTE)(0x00ff & (sAtten2 >> 8));
	sbBuffer[10] = (BYTE)(0x00ff & sAtten2);

	BYTE bCheckSum = GetChecksum(sbBuffer, 11);

	sbBuffer[11] = bCheckSum;

	DWORD dwErrorCode = SUCCESS;
	
	dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 12);	
	if (!dwErrorCode !=SUCCESS)
	{
		sprintf(m_strMsg,"Send VOAx Attenuation Different Value cmd error!");
		return FALSE;
	}

	Sleep(50);

	ZeroMemory(sbBuffer, MAX_PATH);
	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);
	if (dwErrorCode!=SUCCESS)
	{
	    sprintf(m_strMsg,"Receive  Attenuation Different Value cmd error!");
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}

	return TRUE;
}

////////////////////////////////////////////////////////////
//函数说明：
//    读取VOAx 衰减值
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::GetVOAxAtten(BYTE bInstance,double *pdbAtten)
{
	BYTE sbBuffer[MAX_PATH];
	short sAtten = 0;
	ZeroMemory(sbBuffer, MAX_PATH);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x08;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_READ;
	sbBuffer[5] = 0x22;
	sbBuffer[6] = bInstance;
	BYTE bCheckSum = GetChecksum(sbBuffer, 7);

	sbBuffer[7] = bCheckSum;

	DWORD dwErrorCode = SUCCESS;
	
	dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 8);	
	if (!dwErrorCode !=SUCCESS)
	{
		sprintf(m_strMsg,"Send Get VOA Attenuation cmd error!");
		return FALSE;
	}
	Sleep(50);
	ZeroMemory(sbBuffer, MAX_PATH);
	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);
	if (dwErrorCode!=SUCCESS)
	{
		sprintf(m_strMsg,"Receive Get VOA Attenuation cmd error!");
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}

	sAtten = 0xff00 & (sbBuffer[7] << 8);
	sAtten += 0x00ff & (sbBuffer[8]);
	*pdbAtten = sAtten/100.0;

	return TRUE;
}


////////////////////////////////////////////////////////////
//函数说明：
//    读取VOAx 衰减值
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::GetAllVOAAtten(double *pdbAtten1,double*pdbAtten2)
{
	BYTE sbBuffer[MAX_PATH];
	short sAtten = 0;
	ZeroMemory(sbBuffer, MAX_PATH);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x08;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_READ;
	sbBuffer[5] = 0x22;
	sbBuffer[6] = 0xFF;
	BYTE bCheckSum = GetChecksum(sbBuffer, 7);

	sbBuffer[7] = bCheckSum;

	DWORD dwErrorCode = SUCCESS;
	
	dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 8);	
	if (!dwErrorCode !=SUCCESS)
	{
		sprintf(m_strMsg,"Send Get All VOA Attenuation cmd error!");
		return FALSE;
	}

	Sleep(50);
	ZeroMemory(sbBuffer, MAX_PATH);
	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);
	if (dwErrorCode!=SUCCESS)
	{
		sprintf(m_strMsg,"Receive Get All VOA Attenuation cmd error!");
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}

	sAtten = 0xff00 & (sbBuffer[7] << 8);
	sAtten += 0x00ff & (sbBuffer[8]);
	*pdbAtten1 = sAtten / 100.0;

	sAtten = 0;
	sAtten = 0xff00 & (sbBuffer[9] << 8);
	sAtten += 0x00ff & (sbBuffer[10]);
	*pdbAtten2 = sAtten / 100.0;

	return TRUE;
}

////////////////////////////////////////////////////////////
//函数说明：
//    设置VOAx 衰减值
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::SetVOAxDAC(BYTE bInstance,WORD dwDAC)
{
	BYTE sbBuffer[MAX_PATH];

	ZeroMemory(sbBuffer, MAX_PATH);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x0A;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_WRITE;
	sbBuffer[5] = 0x2E;
	sbBuffer[6] = bInstance;
	sbBuffer[7] = (BYTE)(0x00ff & (dwDAC >> 8));
	sbBuffer[8] = (BYTE)(0x00ff & dwDAC);

	BYTE bCheckSum = GetChecksum(sbBuffer, 9);

	sbBuffer[9] = bCheckSum;

	DWORD dwErrorCode = SUCCESS;
	
	dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 10);	
	if (!dwErrorCode !=SUCCESS)
	{
	   sprintf(m_strMsg,"Send VOAx DAC cmd error!");
		return FALSE;
	}
	
	Sleep(50);
	ZeroMemory(sbBuffer, MAX_PATH);
	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);
	if (dwErrorCode!=SUCCESS)
	{
		sprintf(m_strMsg,"Receive VOAx DAC cmd error!");
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}

	return TRUE;
}

////////////////////////////////////////////////////////////
//函数说明：
//    读取VOAx DAC
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::GetVOAxDAC(BYTE bInstance,WORD* pwDAC)
{
	BYTE sbBuffer[MAX_PATH];
	WORD wValue = 0;
	ZeroMemory(sbBuffer, MAX_PATH);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x08;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_READ;
	sbBuffer[5] = 0x2E;
	sbBuffer[6] = bInstance;
	BYTE bCheckSum = GetChecksum(sbBuffer, 7);

	sbBuffer[7] = bCheckSum;

	DWORD dwErrorCode = SUCCESS;
	dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 8);	
	if (!dwErrorCode !=SUCCESS)
	{
		sprintf(m_strMsg,"Send Get VOAx DAC cmd error!");
		return FALSE;
	}

	Sleep(50);

	ZeroMemory(sbBuffer, MAX_PATH);
	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);
	if (dwErrorCode!=SUCCESS)
	{ 
		sprintf(m_strMsg,"Receive Get VOAx DAC cmd error!");
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}

	wValue = 0xff00 & (sbBuffer[7] << 8);
	wValue += 0x00ff & (sbBuffer[8]);
	*pwDAC = wValue;

	return TRUE;
}

////////////////////////////////////////////////////////////
//函数说明：
//    设置VOAx 衰减值
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::SetVOAxDACToDiffrentValue(WORD dwDAC1, WORD dwDAC2, WORD dwDAC3, WORD dwDAC4 )
{
	BYTE sbBuffer[MAX_PATH];
	short sAtten1 = 0;
	short sAtten2 = 0;
	ZeroMemory(sbBuffer, MAX_PATH);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x10;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_WRITE;
	sbBuffer[5] = 0x2E;
	sbBuffer[6] = 0xFF;
	sbBuffer[7] = (BYTE)(0x00ff & (dwDAC1 >> 8));
	sbBuffer[8] = (BYTE)(0x00ff & dwDAC1);
	sbBuffer[9] = (BYTE)(0x00ff & (dwDAC2 >> 8));
	sbBuffer[10] = (BYTE)(0x00ff & dwDAC2);
	sbBuffer[11] = (BYTE)(0x00ff & (dwDAC3 >> 8));
	sbBuffer[12] = (BYTE)(0x00ff & dwDAC3);
	sbBuffer[13] = (BYTE)(0x00ff & (dwDAC4 >> 8));
	sbBuffer[14] = (BYTE)(0x00ff & dwDAC4);

	BYTE bCheckSum = GetChecksum(sbBuffer, 15);

	sbBuffer[15] = bCheckSum;

	DWORD dwErrorCode = SUCCESS;
	dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 16);	
	if (!dwErrorCode !=SUCCESS)
	{
	    sprintf(m_strMsg,"Send VOAx DAC Different Value cmd error!");
		return FALSE;
	}

	Sleep(50);
	ZeroMemory(sbBuffer, MAX_PATH);
	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);
	if (dwErrorCode!=SUCCESS)
	{
	    sprintf(m_strMsg,"Receive  VOAx DAC Different Value cmd error!");
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}

	return TRUE;
}


////////////////////////////////////////////////////////////
//函数说明：
//    读取VOAx DAC
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::GetAllVOADAC(WORD* pwDAC1, WORD* pwDAC2, WORD* pwDAC3, WORD* pwDAC4)
{
	BYTE sbBuffer[MAX_PATH];
	WORD wValue = 0;
	ZeroMemory(sbBuffer, MAX_PATH);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x08;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_READ;
	sbBuffer[5] = 0x2E;
	sbBuffer[6] = 0xFF;
	BYTE bCheckSum = GetChecksum(sbBuffer, 7);

	sbBuffer[7] = bCheckSum;

	DWORD dwErrorCode = SUCCESS;
	dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 10);	
	if (!dwErrorCode !=SUCCESS)
	{
	    sprintf(m_strMsg,"Send Get VOAx DAC cmd error!");
		return FALSE;
	}

	Sleep(50);

	ZeroMemory(sbBuffer, MAX_PATH);
	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);
	if (dwErrorCode!=SUCCESS)
	{
	    	sprintf(m_strMsg,"Receive Get VOAx DAC cmd error!");
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}

	wValue = 0xff00 & (sbBuffer[7] << 8);
	wValue += 0x00ff & (sbBuffer[8]);
	*pwDAC1 = wValue;

	wValue = 0xff00 & (sbBuffer[9] << 8);
	wValue += 0x00ff & (sbBuffer[10]);
	*pwDAC2 = wValue;

	wValue = 0xff00 & (sbBuffer[11] << 8);
	wValue += 0x00ff & (sbBuffer[12]);
	*pwDAC3 = wValue;

	wValue = 0xff00 & (sbBuffer[13] << 8);
	wValue += 0x00ff & (sbBuffer[14]);
	*pwDAC4 = wValue;

	return TRUE;
}

////////////////////////////////////////////////////////////
//函数说明：
//    读取VOAx Min IL
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::GetVOAxMinIL(BYTE bInstance, double * pdbGetMinIL)
{
	BYTE sbBuffer[MAX_PATH];
	short sAtten = 0;
	ZeroMemory(sbBuffer, MAX_PATH);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x08;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_READ;
	sbBuffer[5] = 0x2F;
	sbBuffer[6] = bInstance;
	BYTE bCheckSum = GetChecksum(sbBuffer, 7);

	sbBuffer[7] = bCheckSum;

	DWORD dwErrorCode = SUCCESS;
	dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 8);	
	if (!dwErrorCode !=SUCCESS)
	{
	    sprintf(m_strMsg,"Send Get VOAx Min IL cmd error!");
		return FALSE;
	}

	Sleep(50);
	ZeroMemory(sbBuffer, MAX_PATH);
	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);
	if (dwErrorCode!=SUCCESS)
	{
	    sprintf(m_strMsg,"Receive Get VOAx Min IL cmd error!");
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}

	sAtten = 0xff00 & (sbBuffer[7] << 8);
	sAtten += 0x00ff & (sbBuffer[8]);

	*pdbGetMinIL = sAtten / 100.0;

	return TRUE;
}

////////////////////////////////////////////////////////////
//函数说明：
//    读取VOAx Min IL
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::GetAllVOAMinIL( double * pdbGetMinIL1,double*pdbGetMinIL2,double*pdbGetMinIL3)
{
	BYTE sbBuffer[MAX_PATH];
	short sAtten = 0;
	ZeroMemory(sbBuffer, MAX_PATH);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x08;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_READ;
	sbBuffer[5] = 0x2F;
	sbBuffer[6] = 0xFF;
	BYTE bCheckSum = GetChecksum(sbBuffer, 7);

	sbBuffer[7] = bCheckSum;

	DWORD dwErrorCode = SUCCESS;
	dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 8);	
	if (!dwErrorCode !=SUCCESS)
	{
	    sprintf(m_strMsg,"Send Get All VOAx Min IL cmd error!");
		return FALSE;
	}
	Sleep(50);
	ZeroMemory(sbBuffer, MAX_PATH);
	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);
	if (dwErrorCode!=SUCCESS)
	{
	    sprintf(m_strMsg,"Receive Get All VOAx Min IL cmd error!");
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}

	sAtten = 0xff00 & (sbBuffer[7] << 8);
	sAtten += 0x00ff & (sbBuffer[8]);

	*pdbGetMinIL1 = sAtten / 100.0;

	sAtten = 0;
	sAtten = 0xff00 & (sbBuffer[9] << 8);
	sAtten += 0x00ff & (sbBuffer[10]);
	*pdbGetMinIL2 = sAtten / 100.0;

	sAtten = 0;
	sAtten = 0xff00 & (sbBuffer[9] << 8);
	sAtten += 0x00ff & (sbBuffer[10]);
	*pdbGetMinIL3 = sAtten / 100.0;

	return TRUE;
}


////////////////////////////////////////////////////////////
//函数说明：
//    设置1-9 Switch Channel
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::SetSwitchChannel(BYTE bInstance,BYTE bChannel)
{
	BYTE sbBuffer[MAX_PATH];
	short sAtten1 = 0;
	short sAtten2 = 0;
	ZeroMemory(sbBuffer, MAX_PATH);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x09;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_WRITE;
	sbBuffer[5] = 0x30;
	sbBuffer[6] = bInstance;
	sbBuffer[7] = bChannel;

	BYTE bCheckSum = GetChecksum(sbBuffer, 8);

	sbBuffer[8] = bCheckSum;

	DWORD dwErrorCode = SUCCESS;
	dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 9);	
	if (!dwErrorCode !=SUCCESS)
	{
	    sprintf(m_strMsg,"Send Switchx Channel cmd error!");
		return FALSE;
	}
	
	Sleep(50);
	ZeroMemory(sbBuffer, MAX_PATH);
	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);
	if (dwErrorCode!=SUCCESS)
	{
	    sprintf(m_strMsg,"Receive Switchx Channel cmd error!");
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}

	return TRUE;
}

////////////////////////////////////////////////////////////
//函数说明：
//    读取Switchx Channel
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::GetSwitchChannel(BYTE bInstance,BYTE* bGetChIndex)
{
	BYTE sbBuffer[MAX_PATH];
	short sAtten = 0;
	ZeroMemory(sbBuffer, MAX_PATH);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x08;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_READ;
	sbBuffer[5] = 0x30;
	sbBuffer[6] = bInstance;
	BYTE bCheckSum = GetChecksum(sbBuffer, 7);

	sbBuffer[7] = bCheckSum;

	DWORD dwErrorCode = SUCCESS;
	dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 8);	
	if (!dwErrorCode !=SUCCESS)
	{
	    sprintf(m_strMsg,"Send Switchx Channel cmd error!");
		return FALSE;
	}

	Sleep(50);
	ZeroMemory(sbBuffer, MAX_PATH);
	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);
	if (dwErrorCode!=SUCCESS)
	{
	    sprintf(m_strMsg,"Receive Get Switch Channel cmd error!");
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}

	*bGetChIndex = sbBuffer[7];

	return TRUE;
}

////////////////////////////////////////////////////////////
//函数说明：
//    设置1-9 Switch diffrent Channel
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::SetAllSwitchToDifferentChannel( BYTE bChannel,BYTE bChanne2, BYTE bChanne3, BYTE bChanne4, BYTE bChanne5, BYTE bChanne6, BYTE bChanne7, BYTE bChanne8, BYTE bChanne9)
{
	BYTE sbBuffer[MAX_PATH];
	short sAtten1 = 0;
	short sAtten2 = 0;
	ZeroMemory(sbBuffer, MAX_PATH);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x11;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_WRITE;
	sbBuffer[5] = 0x30;
	sbBuffer[6] = 0xff;
	sbBuffer[7] = bChannel;
	sbBuffer[8] = bChanne2;
	sbBuffer[9] = bChanne3;
	sbBuffer[10] = bChanne4;
	sbBuffer[11] = bChanne5;
	sbBuffer[12] = bChanne6;
	sbBuffer[13] = bChanne7;
	sbBuffer[14] = bChanne8;
	sbBuffer[15] = bChanne9;

	BYTE bCheckSum = GetChecksum(sbBuffer, 16);

	sbBuffer[16] = bCheckSum;

	DWORD dwErrorCode = SUCCESS;
	dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 17);	
	if (!dwErrorCode !=SUCCESS)
	{
	   sprintf(m_strMsg,"Send All Switchx Channel cmd error!");
		return FALSE;
	}

	Sleep(50);
	ZeroMemory(sbBuffer, MAX_PATH);
	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);
	if (dwErrorCode!=SUCCESS)
	{
		sprintf(m_strMsg,"Receive  All Switchx Channel cmd error!");
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}

	return TRUE;
}

////////////////////////////////////////////////////////////
//函数说明：
//    读取All Switchx Channel
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::GetAllSwitchChannel(BYTE* bGetChArry)
{
	BYTE sbBuffer[MAX_PATH];
	short sAtten = 0;
	ZeroMemory(sbBuffer, MAX_PATH);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x08;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_READ;
	sbBuffer[5] = 0x30;
	sbBuffer[6] = 0xFF;

	BYTE bCheckSum = GetChecksum(sbBuffer, 7);

	sbBuffer[7] = bCheckSum;
    DWORD dwErrorCode = SUCCESS;
	dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 8);	
	if (!dwErrorCode !=SUCCESS)
	{
	    sprintf(m_strMsg,"Send Get All Switch Channel cmd error!");
		return FALSE;
	}

	Sleep(50);
	ZeroMemory(sbBuffer, MAX_PATH);
	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);
	if (dwErrorCode!=SUCCESS)
	{
			sprintf(m_strMsg,"Receive Get All Switch Channel cmd error!");
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}

	bGetChArry[0] = sbBuffer[7];
	bGetChArry[1] = sbBuffer[8];
	bGetChArry[2] = sbBuffer[9];
	bGetChArry[3] = sbBuffer[10];
	bGetChArry[4] = sbBuffer[11];
	bGetChArry[5] = sbBuffer[12];
	bGetChArry[6] = sbBuffer[13];
	bGetChArry[7] = sbBuffer[14];
	bGetChArry[8] = sbBuffer[15];

	return TRUE;
}
////////////////////////////////////////////////////////////
//函数说明：
//    读取Switchx Actual Channel,有底层反馈
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::GetSwitchActualChannel(BYTE bInstance, BYTE* bGetChIndex)
{
	BYTE sbBuffer[MAX_PATH];
	short sAtten = 0;
	ZeroMemory(sbBuffer, MAX_PATH);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x08;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_READ;
	sbBuffer[5] = 0x31;
	sbBuffer[6] = bInstance;

	BYTE bCheckSum = GetChecksum(sbBuffer, 7);

	sbBuffer[7] = bCheckSum;

	DWORD dwErrorCode = SUCCESS;
	dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 8);	
	if (!dwErrorCode !=SUCCESS)
	{
	    sprintf(m_strMsg,"Send Get Switch actual Channel cmd error!");
		return FALSE;
	}

	Sleep(50);
	ZeroMemory(sbBuffer, MAX_PATH);
	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);
	if (dwErrorCode!=SUCCESS)
	{
		sprintf(m_strMsg,"Receive Get Switch actual Channel cmd error!");
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}

	*bGetChIndex = sbBuffer[7];

	return TRUE;
}

////////////////////////////////////////////////////////////
//函数说明：
//    读取All Switchx Channel
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::GetAllSwitchActualChannel(BYTE* bGetChArry)
{
	BYTE sbBuffer[MAX_PATH];
	short sAtten = 0;
	ZeroMemory(sbBuffer, MAX_PATH);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x08;
	sbBuffer[2] = 0x08;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_READ;
	sbBuffer[5] = 0x30;
	sbBuffer[6] = 0xFF;


	BYTE bCheckSum = GetChecksum(sbBuffer, 7);

	sbBuffer[7] = bCheckSum;

	DWORD dwErrorCode = SUCCESS;
	dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 8);	
	if (!dwErrorCode !=SUCCESS)
	{
	   sprintf(m_strMsg,"Send Get All Switch Channel cmd error!");
		return FALSE;
	}


	Sleep(50);
	ZeroMemory(sbBuffer, MAX_PATH);
	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);
	if (dwErrorCode!=SUCCESS)
	{
		sprintf(m_strMsg,"Receive Get All Switch actual Channel cmd error!");
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}

	bGetChArry[0] = sbBuffer[7];
	bGetChArry[1] = sbBuffer[8];
	bGetChArry[2] = sbBuffer[9];
	bGetChArry[3] = sbBuffer[10];
	bGetChArry[4] = sbBuffer[11];
	bGetChArry[5] = sbBuffer[12];
	bGetChArry[6] = sbBuffer[13];
	bGetChArry[7] = sbBuffer[14];
	bGetChArry[8] = sbBuffer[15];

	return TRUE;
}

////////////////////////////////////////////////////////////
//函数说明：
//    读取Input path IL
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::GetInputMinIL(double * pdbGetMinIL)
{
	BYTE sbBuffer[MAX_PATH];
	short sAtten = 0;
	ZeroMemory(sbBuffer, MAX_PATH);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x08;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_READ;
	sbBuffer[5] = 0x3D;
	sbBuffer[6] = 0x01;

	BYTE bCheckSum = GetChecksum(sbBuffer, 7);

	sbBuffer[7] = bCheckSum;

	DWORD dwErrorCode = SUCCESS;
	dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 8);	
	if (!dwErrorCode !=SUCCESS)
	{
	    sprintf(m_strMsg,"Send Get Input Min IL cmd error!");
		return FALSE;
	}

	Sleep(50);
	ZeroMemory(sbBuffer, MAX_PATH);
	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);
	if (dwErrorCode!=SUCCESS)
	{
		sprintf(m_strMsg,"Receive Get Input Min IL cmd error!");
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}

	sAtten = 0xff00 & (sbBuffer[7] << 8);
	sAtten += 0x00ff & (sbBuffer[8]);

	*pdbGetMinIL = sAtten / 100.0;

	return TRUE;
}
////////////////////////////////////////////////////////////
//函数说明：
//    读取Out path IL
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::GetOutputMinIL(double * pdbGetMinIL)
{
	BYTE sbBuffer[MAX_PATH];
	short sAtten = 0;
	ZeroMemory(sbBuffer, MAX_PATH);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x08;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_READ;
	sbBuffer[5] = 0x2F;
	sbBuffer[6] = 0x3E;

	BYTE bCheckSum = GetChecksum(sbBuffer, 7);

	DWORD dwErrorCode = SUCCESS;
	dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 8);	
	if (!dwErrorCode !=SUCCESS)
	{
	   sprintf(m_strMsg,"Send Get Output Min IL cmd error!");
		return FALSE;
	}
	Sleep(50);
	ZeroMemory(sbBuffer, MAX_PATH);
	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);
	if (dwErrorCode!=SUCCESS)
	{
			sprintf(m_strMsg,"Receive Get Output Min IL cmd error!");
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}

	sAtten = 0xff00 & (sbBuffer[7] << 8);
	sAtten += 0x00ff & (sbBuffer[8]);

	*pdbGetMinIL = sAtten / 100.0;

	return TRUE;
}

////////////////////////////////////////////////////////////
//函数说明：
//    读取MAS path IL
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::GetMSAMinIL(double * pdbGetMinIL)
{
	BYTE sbBuffer[MAX_PATH];
	short sAtten = 0;
	ZeroMemory(sbBuffer, MAX_PATH);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x08;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_READ;
	sbBuffer[5] = 0x2F;
	sbBuffer[6] = 0x3F;

	BYTE bCheckSum = GetChecksum(sbBuffer, 7);

	sbBuffer[7] = bCheckSum;
	
	DWORD dwErrorCode = SUCCESS;
	dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 8);	
	if (!dwErrorCode !=SUCCESS)
	{
	    sprintf(m_strMsg,"Send Get MSA Min IL cmd error!");
		return FALSE;
	}

	Sleep(50);
	ZeroMemory(sbBuffer, MAX_PATH);
	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);
	if (dwErrorCode!=SUCCESS)
	{
		sprintf(m_strMsg,"Receive Get MSA Min IL cmd error!");
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}

	sAtten = 0xff00 & (sbBuffer[7] << 8);
	sAtten += 0x00ff & (sbBuffer[8]);

	*pdbGetMinIL = sAtten / 100.0;

	return TRUE;
}

////////////////////////////////////////////////////////////
//函数说明：
//    设置GPIO状态，Input or Output，int型 4个字节1-32bit
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::ConfigureGPIO(long nStatus)
{
	BYTE sbBuffer[MAX_PATH];
	short sAtten1 = 0;
	short sAtten2 = 0;
	ZeroMemory(sbBuffer, MAX_PATH);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x08;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_WRITE;
	sbBuffer[5] = 0x40;
	sbBuffer[6] = 0xFF;
	sbBuffer[7] = (BYTE)(0x000000ff & nStatus>>24);
	sbBuffer[8] = (BYTE)(0x000000ff & nStatus >> 16);
	sbBuffer[9] = (BYTE)(0x000000ff & nStatus >> 8);
	sbBuffer[10] = (BYTE)(0x000000ff & nStatus );

	BYTE bCheckSum = GetChecksum(sbBuffer,11);

	sbBuffer[11] = bCheckSum;

	DWORD dwErrorCode = SUCCESS;
	dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 12);	
	if (!dwErrorCode !=SUCCESS)
	{
	    sprintf(m_strMsg,"Send Switchx Channel cmd error!");
		return FALSE;
	}
	Sleep(50);
	ZeroMemory(sbBuffer, MAX_PATH);
	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);
	if (dwErrorCode!=SUCCESS)
	{
		sprintf(m_strMsg,"Receive Switchx Channel cmd error!");
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}

	return TRUE;
}

////////////////////////////////////////////////////////////
//函数说明：
//    读取 GPIO 状态
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::GetGPIOConfigure(long * plStatus)
{
	BYTE sbBuffer[MAX_PATH];
	long lTemp = 0;
	ZeroMemory(sbBuffer, MAX_PATH);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x08;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_READ;
	sbBuffer[5] = 0x40;
	sbBuffer[6] = 0xFF;

	BYTE bCheckSum = GetChecksum(sbBuffer, 7);

	sbBuffer[7] = bCheckSum;

	DWORD dwErrorCode = SUCCESS;
	dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 12);	
	if (!dwErrorCode !=SUCCESS)
	{
	    sprintf(m_strMsg,"Send Get GPIO Configure cmd error!");
		return FALSE;
	}

	Sleep(50);
	ZeroMemory(sbBuffer, MAX_PATH);
	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);
	if (dwErrorCode!=SUCCESS)
	{
		sprintf(m_strMsg,"Receive Get GPIO Configure cmd error!");
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}

	lTemp = 0xff000000 & (sbBuffer[7] << 24);
	lTemp += 0x00ff0000 & (sbBuffer[8] <<16);
	lTemp += 0x0000ff00 & (sbBuffer[9] << 8);
	lTemp += 0x000000ff & (sbBuffer[10]);

	*plStatus = lTemp;

	return TRUE;
}

////////////////////////////////////////////////////////////
//函数说明：
//    设置GPIOx low or high
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::ConfigureGPIOx(BYTE bInstance,BOOL bStatus)
{
	BYTE sbBuffer[MAX_PATH];
	short sAtten1 = 0;
	short sAtten2 = 0;
	ZeroMemory(sbBuffer, MAX_PATH);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x08;
	sbBuffer[2] = 0x08;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_WRITE;
	sbBuffer[5] = 0x40;
	sbBuffer[6] = bInstance;
	sbBuffer[7] = (BYTE)bStatus;

	BYTE bCheckSum = GetChecksum(sbBuffer, 8);

	sbBuffer[8] = bCheckSum;

	DWORD dwErrorCode = SUCCESS;
	dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 9);	
	if (!dwErrorCode !=SUCCESS)
	{
	    sprintf(m_strMsg,"Send GPIOx Status cmd error!");
		return FALSE;
	}

	Sleep(50);
	ZeroMemory(sbBuffer, MAX_PATH);
	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);
	if (dwErrorCode!=SUCCESS)
	{
		sprintf(m_strMsg,"Receive GPIO Status cmd error!");
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}

	return TRUE;
}

///////////////////////////////////////////////////////////
//函数说明：
//    读取GPIOx状态 low or high
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::GetGPIOxSetPoint(BYTE bInstance, BYTE* bStatus)
{
	BYTE sbBuffer[MAX_PATH];
	short sAtten1 = 0;
	short sAtten2 = 0;
	ZeroMemory(sbBuffer, MAX_PATH);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x08;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_READ;
	sbBuffer[5] = 0x41;
	sbBuffer[6] = bInstance;
	sbBuffer[7] = 0x00;

	BYTE bCheckSum = GetChecksum(sbBuffer, 8);

	sbBuffer[8] = bCheckSum;

	DWORD dwErrorCode = SUCCESS;
	dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 9);	
	if (!dwErrorCode !=SUCCESS)
	{
	    sprintf(m_strMsg,"Send GPIOx Status cmd error!");
		return FALSE;
	}

	Sleep(50);
	ZeroMemory(sbBuffer, MAX_PATH);
	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);
	if (dwErrorCode!=SUCCESS)
	{
		sprintf(m_strMsg,"Receive GPIOx Status cmd error!");
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}
	*bStatus = sbBuffer[7];
	return TRUE;
}


////////////////////////////////////////////////////////////
//函数说明：
//    设置GPIOx状态 low or high
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::SetAllInputGPIOPoint(long lStatus)
{
	BYTE sbBuffer[MAX_PATH];
	short sAtten1 = 0;
	short sAtten2 = 0;
	ZeroMemory(sbBuffer, MAX_PATH);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x08;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_WRITE;
	sbBuffer[5] = 0x41;
	sbBuffer[6] = 0xFF;
	sbBuffer[7] = (BYTE)(0x000000ff & lStatus >> 24);
	sbBuffer[8] = (BYTE)(0x000000ff & lStatus >> 16);
	sbBuffer[9] = (BYTE)(0x000000ff & lStatus >> 8);
	sbBuffer[10] = (BYTE)(0x000000ff & lStatus);

	BYTE bCheckSum = GetChecksum(sbBuffer, 11);

	sbBuffer[11] = bCheckSum;

	DWORD dwErrorCode = SUCCESS;
	dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 12);	
	if (!dwErrorCode !=SUCCESS)
	{
	    sprintf(m_strMsg,"Send GPIOx Status cmd error!");
		return FALSE;
	}

	Sleep(50);
	ZeroMemory(sbBuffer, MAX_PATH);
	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);
	if (dwErrorCode!=SUCCESS)
	{
		sprintf(m_strMsg,"Receive All Input GPIO Status cmd error!");
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}

	return TRUE;
}

////////////////////////////////////////////////////////////
//函数说明：
//    读取 GPIO 状态
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::GetAllInputGPIOPoint(long * plStatus)
{
	BYTE sbBuffer[MAX_PATH];
	long lTemp = 0;
	ZeroMemory(sbBuffer, MAX_PATH);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x08;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_READ;
	sbBuffer[5] = 0x2F;
	sbBuffer[6] = 0x41;

	BYTE bCheckSum = GetChecksum(sbBuffer, 7);

	sbBuffer[7] = bCheckSum;


	DWORD dwErrorCode = SUCCESS;
	dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 8);	
	if (!dwErrorCode !=SUCCESS)
	{
	    sprintf(m_strMsg,"Send Get GPIO Configure cmd error!");
		return FALSE;
	}

	Sleep(50);
	ZeroMemory(sbBuffer, MAX_PATH);
	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);
	if (dwErrorCode!=SUCCESS)
	{
		sprintf(m_strMsg,"Receive Get GPIO Configure cmd error!");
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}

	lTemp = 0xff000000 & (sbBuffer[7] << 24);
	lTemp += 0x00ff0000 & (sbBuffer[8] << 16);
	lTemp += 0x0000ff00 & (sbBuffer[9] << 8);
	lTemp += 0x000000ff & (sbBuffer[10]);

	*plStatus = lTemp;

	return TRUE;
}

///////////////////////////////////////////////////////////
//函数说明：
//    读取GPIOx Status
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::GetGPIOxStatus(BYTE bInstance, BYTE* bStatus)
{
	BYTE sbBuffer[MAX_PATH];
	short sAtten1 = 0;
	short sAtten2 = 0;
	ZeroMemory(sbBuffer, MAX_PATH);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x08;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_READ;
	sbBuffer[5] = 0x42;
	sbBuffer[6] = bInstance;

	BYTE bCheckSum = GetChecksum(sbBuffer, 7);

	sbBuffer[7] = bCheckSum;

	DWORD dwErrorCode = SUCCESS;
	dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 8);	
	if (!dwErrorCode !=SUCCESS)
	{
	    sprintf(m_strMsg,"Send GPIOx Status cmd error!");
		return FALSE;
	}


	Sleep(50);
	ZeroMemory(sbBuffer, MAX_PATH);
	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);
	if (dwErrorCode!=SUCCESS)
	{
		sprintf(m_strMsg,"Receive GPIO Status cmd error!");
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}
	*bStatus = sbBuffer[7];
	return TRUE;
}
///////////////////////////////////////////////////////////
//函数说明：
//    设置开关盒中的串口
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::ConfigUARTx(BYTE bInstance, DWORD dwBaudRate, BYTE bByteSize, BYTE bParity, BYTE bStopBits, DWORD dwTimeOut)
{
	BYTE sbBuffer[MAX_PATH];
	short sAtten1 = 0;
	short sAtten2 = 0;
	ZeroMemory(sbBuffer, MAX_PATH);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x08;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_WRITE;
	sbBuffer[5] = 0x50;
	sbBuffer[6] = 0xFF;
	sbBuffer[7] = (BYTE)(0x000000ff & dwBaudRate >> 24);
	sbBuffer[8] = (BYTE)(0x000000ff & dwBaudRate >> 16);
	sbBuffer[9] = (BYTE)(0x000000ff & dwBaudRate >> 8);
	sbBuffer[10] = (BYTE)(0x000000ff & dwBaudRate);
	sbBuffer[11] = bByteSize;
	sbBuffer[12] = bParity;
	sbBuffer[13] = bStopBits;
	sbBuffer[14] = (BYTE)(0x000000ff & dwTimeOut >> 24);
	sbBuffer[15] = (BYTE)(0x000000ff & dwTimeOut >> 16);
	sbBuffer[16] = (BYTE)(0x000000ff & dwTimeOut >> 8);
	sbBuffer[17] = (BYTE)(0x000000ff & dwTimeOut);

	BYTE bCheckSum = GetChecksum(sbBuffer, 18);

	sbBuffer[18] = bCheckSum;

	DWORD dwErrorCode = SUCCESS;
	dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 19);	
	if (!dwErrorCode !=SUCCESS)
	{
	    sprintf(m_strMsg,"Send Configure UART cmd error!");
		return FALSE;
	}
	Sleep(50);
	ZeroMemory(sbBuffer, MAX_PATH);
	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);
	if (dwErrorCode!=SUCCESS)
	{
		sprintf(m_strMsg,"Receive Configure UART cmd error!");
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}

	return TRUE;
}

///////////////////////////////////////////////////////////
//函数说明：
//    设置开关盒中的串口
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::ConfigAllUART(DWORD dwBaudRate, BYTE bByteSize , BYTE bParity, BYTE bStopBits, DWORD dwTimeOut)
{
	BYTE sbBuffer[MAX_PATH];
	short sAtten1 = 0;
	short sAtten2 = 0;
	ZeroMemory(sbBuffer, MAX_PATH);

	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x08;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_READ;
	sbBuffer[5] = 0x50;
	sbBuffer[6] = 0xFF;
	sbBuffer[7] = (BYTE)(0x000000ff & dwBaudRate >> 24);
	sbBuffer[8] = (BYTE)(0x000000ff & dwBaudRate >> 16);
	sbBuffer[9] = (BYTE)(0x000000ff & dwBaudRate >> 8);
	sbBuffer[10] = (BYTE)(0x000000ff & dwBaudRate);
	sbBuffer[11] = bByteSize;
	sbBuffer[12] = bParity;
	sbBuffer[13] = bStopBits;
	sbBuffer[14] = (BYTE)(0x000000ff & dwTimeOut >> 24);
	sbBuffer[15] = (BYTE)(0x000000ff & dwTimeOut >> 16);
	sbBuffer[16] = (BYTE)(0x000000ff & dwTimeOut >> 8);
	sbBuffer[17] = (BYTE)(0x000000ff & dwTimeOut);

	BYTE bCheckSum = GetChecksum(sbBuffer, 18);

	sbBuffer[18] = bCheckSum;

	DWORD dwErrorCode = SUCCESS;
	dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 19);	
	if (!dwErrorCode !=SUCCESS)
	{
	    sprintf(m_strMsg,"Send Configure UART cmd error!");
		return FALSE;
	}

	Sleep(50);
	ZeroMemory(sbBuffer, MAX_PATH);
	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);
	if (dwErrorCode!=SUCCESS)
	{
		sprintf(m_strMsg,"Receive Configure UART cmd error!");
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		return FALSE;
	}

	return TRUE;
}
///////////////////////////////////////////////////////////
//函数说明：
//    开关盒中的UARTx 发送函数
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::WriteUARTxMessage(BYTE bInstance, BYTE* pBuffer, int nLength)
{
	BYTE *pbBuffer=NULL;
	if (*pbBuffer == NULL)
	{
		pbBuffer = (BYTE*)VirtualAlloc(NULL, 8 + nLength, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	}
	ZeroMemory(pbBuffer, 8 + nLength);

	pbBuffer[0] = 0xBD;
	pbBuffer[1] = 0x00;
	pbBuffer[2] = 0x08;
	pbBuffer[3] = 0x00;
	pbBuffer[4] = CMD_WRITE;
	pbBuffer[5] = 0x51;
	pbBuffer[6] = bInstance;
	for (int i = 0;i < nLength;i++)
	{
		pbBuffer[7+i] = pBuffer[i];
	}
	
	BYTE bCheckSum = GetChecksum(pbBuffer, nLength+7);

	pbBuffer[nLength + 7] = bCheckSum;
    DWORD dwErrorCode = SUCCESS;
	dwErrorCode = m_DevComHandle.WriteDevice((char*)pbBuffer, nLength + 8);	
	if (!dwErrorCode !=SUCCESS)
	{
	   	sprintf(m_strMsg,"Send Configure UART cmd error!");
		if (pbBuffer != NULL)
		{
			VirtualFree(pbBuffer, 0, MEM_RELEASE);
			pbBuffer = NULL;
		}
		return FALSE;
	}
	Sleep(50);
	char sbBuffer[MAX_PATH];
	ZeroMemory(sbBuffer, MAX_PATH);

	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);
	if (dwErrorCode!=SUCCESS)
	{
		sprintf(m_strMsg,"Receive Configure UART cmd error!");
		if (pbBuffer != NULL)
		{
			VirtualFree(pbBuffer, 0, MEM_RELEASE);
			pbBuffer = NULL;
		}
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		sprintf(m_strMsg,"Receive Configure UART cmd error!");
		if (pbBuffer != NULL)
		{
			VirtualFree(pbBuffer, 0, MEM_RELEASE);
			pbBuffer = NULL;
		}
		return FALSE;
	}
	if (pbBuffer != NULL)
	{
		VirtualFree(pbBuffer, 0, MEM_RELEASE);
		pbBuffer = NULL;
	}
	return TRUE;
}
///////////////////////////////////////////////////////////
//函数说明：
//    开关盒中的UARTx接收函数
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::ReadUARTxMessage(BYTE bInstance, BYTE* pBuffer, int nLength, int &nGetLength)
{
	BYTE sbBuffer[MAX_PATH];
	int nTempLength = 0;
	ZeroMemory(sbBuffer, MAX_PATH);
	sbBuffer[0] = 0xBD;
	sbBuffer[1] = 0x00;
	sbBuffer[2] = 0x08;
	sbBuffer[3] = 0x00;
	sbBuffer[4] = CMD_READ;
	sbBuffer[5] = 0x51;
	sbBuffer[6] = bInstance;

	BYTE bCheckSum = GetChecksum(sbBuffer,7);
	sbBuffer[7] = bCheckSum;

	DWORD dwErrorCode = SUCCESS;
	dwErrorCode = m_DevComHandle.WriteDevice((char*)sbBuffer, 8);	
	if (!dwErrorCode !=SUCCESS)
	{
	    sprintf(m_strMsg,"Send Configure UART cmd error!");
		return FALSE;
	}

	BYTE *pbBuffer = NULL;
	if (*pbBuffer == NULL)
	{
		pbBuffer = (BYTE*)VirtualAlloc(NULL, 8 + 1024, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	}
	ZeroMemory(pbBuffer, 8 + 1024);

	dwErrorCode = m_DevComHandle.ReadDevice((char*)pbBuffer, 8 + 1024);
	if (dwErrorCode!=SUCCESS)
	{
		sprintf(m_strMsg,"Receive Configure UART cmd error!");
		if (pbBuffer != NULL)
		{
			VirtualFree(pbBuffer, 0, MEM_RELEASE);
			pbBuffer = NULL;
		}
		return FALSE;
	}

	
	nTempLength = (0xff00 & (pbBuffer[1] << 8));
	nTempLength += (0x00ff & (pbBuffer[2]));
	nGetLength = nTempLength - 8;

	if (nLength < nGetLength)
	{
		sprintf(m_strMsg,"Receive Buffer Length To Less!");
		if (pbBuffer != NULL)
		{
			VirtualFree(pbBuffer, 0, MEM_RELEASE);
			pbBuffer = NULL;
		}
		return FALSE;
	}
	memcpy(pBuffer, pbBuffer + 7, nGetLength);
	
	if (pbBuffer != NULL)
	{
		VirtualFree(pbBuffer, 0, MEM_RELEASE);
		pbBuffer = NULL;
	}
	return TRUE;
}

///////////////////////////////////////////////////////////
//函数说明：
//    开关盒中的所有UART发送函数
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::WriteAllUARTMessage(BYTE* pBuffer, int nLength)
{
	BYTE *pbBuffer = NULL;
	if (*pbBuffer == NULL)
	{
		pbBuffer = (BYTE*)VirtualAlloc(NULL, 8 + nLength, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	}
	ZeroMemory(pbBuffer, 8 + nLength);

	pbBuffer[0] = 0xBD;
	pbBuffer[1] = 0x00;
	pbBuffer[2] = 0x08;
	pbBuffer[3] = 0x00;
	pbBuffer[4] = CMD_WRITE;
	pbBuffer[5] = 0x51;
	pbBuffer[6] = 0xFF;
	for (int i = 0;i < nLength;i++)
	{
		pbBuffer[7 + i] = pBuffer[i];
	}

	BYTE bCheckSum = GetChecksum(pbBuffer, nLength + 7);

	pbBuffer[nLength + 7] = bCheckSum;

	DWORD dwErrorCode = SUCCESS;
	dwErrorCode = m_DevComHandle.WriteDevice((char*)pbBuffer, nLength + 8);	
	if (!dwErrorCode !=SUCCESS)
	{
	    sprintf(m_strMsg,"Send Configure UART cmd error!");
		if (pbBuffer != NULL)
		{
			VirtualFree(pbBuffer, 0, MEM_RELEASE);
			pbBuffer = NULL;
		}
		return FALSE;
	}

	Sleep(50);
	char sbBuffer[MAX_PATH];
	ZeroMemory(sbBuffer, MAX_PATH);
	dwErrorCode = m_DevComHandle.ReadDevice((char*)sbBuffer, MAX_PATH);
	if (dwErrorCode!=SUCCESS)
	{
		sprintf(m_strMsg,"Receive Configure UART cmd error!");
		if (pbBuffer != NULL)
		{
			VirtualFree(pbBuffer, 0, MEM_RELEASE);
			pbBuffer = NULL;
		}
		return FALSE;
	}

	if (sbBuffer[3] != 0x00)
	{
		AnlysisErrorString(sbBuffer[3]);
		if (pbBuffer != NULL)
		{
			VirtualFree(pbBuffer, 0, MEM_RELEASE);
			pbBuffer = NULL;
		}
		return FALSE;
	}
	if (pbBuffer != NULL)
	{
		VirtualFree(pbBuffer, 0, MEM_RELEASE);
		pbBuffer = NULL;
	}
	return TRUE;
}
///////////////////////////////////////////////////////////
//函数说明：
//    切换Input端通道 8X17 , 8进17出
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::SetSwitchToInputPath(int nChInput, int n2X2Ch, int nChOutput)
{
	if (nChInput > 8)
	{
		m_strMsg.Format("输入端通输入道号不能大于8");
		return FALSE;
	}

	if (nChInput > 18)
	{
		m_strMsg.Format("输入端通输出道号不能大于18");
		return FALSE;
	}
	//切换SW1
	if (!SetSwitchChannel(1, nChInput))
	{
		return FALSE;
	}

    //切换SW9
	if (!SetSwitchChannel(9, n2X2Ch))
	{
		return FALSE;
	}

	//切换SW2
	if (!SetSwitchChannel(2, nChOutput))
	{
		return FALSE;
	}
	return TRUE;
}

///////////////////////////////////////////////////////////
//函数说明：
//    切换输出端通道 18X2 ,这里n2X2Ch 1为 OPM，0 
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::SetSwitchToOutputPath(int nChInput, int n2X2Ch, int nChOutput)
{
	if (nChInput > 18)
	{
		m_strMsg.Format("输入端通输入道号不能大于18");
		return FALSE;
	}

	if (nChInput > 2)
	{
		m_strMsg.Format("输入端通输出道号不能大于18");
		return FALSE;
	}
	//切换SW3
	if (!SetSwitchChannel(3, nChInput))
	{
		return FALSE;
	}

	//切换SW9
	if (!SetSwitchChannel(9, n2X2Ch))
	{
		return FALSE;
	}

	//切换SW5到第7通道
	if (!SetSwitchChannel(5, 6))
	{
		return FALSE;
	}

	//切换SW4
	if (!SetSwitchChannel(4, nChOutput))
	{
		return FALSE;
	}
	return TRUE;
}

///////////////////////////////////////////////////////////
//函数说明：
//    切换MSA通道
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::SetSwitchToMSAInToMSAOut(int nChInput,int nChOutput)
{
	if (nChInput > 8)
	{
		m_strMsg.Format("输入端通输入道号不能大于8");
		return FALSE;
	}

	if (nChInput > 8)
	{
		m_strMsg.Format("输入端通输出道号不能大于8");
		return FALSE;
	}
	//切换SW3
	if (!SetSwitchChannel(6, nChInput))
	{
		return FALSE;
	}

	//切换SW8
	if (!SetSwitchChannel(8, 0))
	{
		return FALSE;
	}

	//切换SW7
	if (!SetSwitchChannel(7, nChOutput))
	{
		return FALSE;
	}
	return TRUE;
}

///////////////////////////////////////////////////////////
//函数说明：
//    切换扩展通道
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::SetSwitchToExpendPath(int nChInput, int nChOutput)
{
	if (nChInput > 8)
	{
		m_strMsg.Format("输入端通输入道号不能大于8");
		return FALSE;
	}
	//切换SW3
	if (!SetSwitchChannel(5, nChInput))
	{
		return FALSE;
	}

	//切换SW4
	if (!SetSwitchChannel(4, nChOutput))
	{
		return FALSE;
	}
	return TRUE;
}

///////////////////////////////////////////////////////////
//函数说明：
//    切换MSAInToExpand(OPM or OSA)
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::SetSwitchMSAIToExtendPath(int nChInput, int nChOutput)
{
	if (nChInput > 8)
	{
		m_strMsg.Format("输入端通输入道号不能大于8");
		return FALSE;
	}

	if (nChOutput > 2)
	{
		m_strMsg.Format("输出端道号不能大于2");
		return FALSE;
	}
	//切换SW7
	if (!SetSwitchChannel(7, nChInput))
	{
		return FALSE;
	}

	//切换SW8
	if (!SetSwitchChannel(8, 1))
	{
		return FALSE;
	}

	//切换SW5
	if (!SetSwitchChannel(5, 3))
	{
		return FALSE;
	}

	//切换SW4
	if (!SetSwitchChannel(4, nChOutput))
	{
		return FALSE;
	}
	return TRUE;
}


///////////////////////////////////////////////////////////
//函数说明：
//    切换MSAInToExpand(OPM or OSA)
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::SetSwitchMSAIMonitorPath(int nChInput, int nChOutput)
{
	if (nChInput > 8)
	{
		m_strMsg.Format("输入端通输入道号不能大于8");
		return FALSE;
	}

	if (nChOutput > 2)
	{
		m_strMsg.Format("输出端道号不能大于2");
		return FALSE;
	}
	//切换SW7
	if (!SetSwitchChannel(7, nChInput))
	{
		return FALSE;
	}

	//切换SW5
	if (!SetSwitchChannel(5, 5))
	{
		return FALSE;
	}

	//切换SW4
	if (!SetSwitchChannel(4, nChOutput))
	{
		return FALSE;
	}
	return TRUE;
}

///////////////////////////////////////////////////////////
//函数说明：
//    切换MSAOutToExpand(OPM or OSA)
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::SetSwitchMSAOToExtendPath(int nChInput, int nChOutput)
{
	if (nChInput > 8)
	{
		m_strMsg.Format("输入端通输入道号不能大于8");
		return FALSE;
	}

	if (nChOutput > 2)
	{
		m_strMsg.Format("输出端道号不能大于2");
		return FALSE;
	}
	//切换SW6
	if (!SetSwitchChannel(6, nChInput))
	{
		return FALSE;
	}

	//切换SW8
	if (!SetSwitchChannel(8, 1))
	{
		return FALSE;
	}

	//切换SW5
	if (!SetSwitchChannel(5, 4))
	{
		return FALSE;
	}

	//切换SW4
	if (!SetSwitchChannel(4, nChOutput))
	{
		return FALSE;
	}
	return TRUE;
}

///////////////////////////////////////////////////////////
//函数说明：
//    切换 Sx To Monitor path（OPM or OSA) 
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::SetSwitchSxInToMonitor(int nChInput, int nChOutput)
{
	if (nChInput > 8)
	{
		m_strMsg.Format("输入端通输入道号不能大于8");
		return FALSE;
	}

	if (nChOutput > 2)
	{
		m_strMsg.Format("输出端道号不能大于2");
		return FALSE;
	}
	//切换SW1
	if (!SetSwitchChannel(1, nChInput))
	{
		return FALSE;
	}

	//切换SW4
	if (!SetSwitchChannel(4, nChOutput))
	{
		return FALSE;
	}
	return TRUE;
}

///////////////////////////////////////////////////////////
//函数说明：
//    切换Reference path（OPM or OSA) 
//Add by wanxin
//Time:20170601
////////////////////////////////////////////////////////////
BOOL CDT0ASwitchBox::SetSwitchReferencePath(int nChOutput)
{
	if (nChOutput > 2)
	{
		m_strMsg.Format("输出端道号不能大于2");
		return FALSE;
	}
	//切换SW2
	if (!SetSwitchChannel(2, 18))
	{
		return FALSE;
	}

	//切换SW5
	if (!SetSwitchChannel(4, 6))
	{
		return FALSE;
	}

	//切换SW4
	if (!SetSwitchChannel(4, nChOutput))
	{
		return FALSE;
	}
	return TRUE;
}