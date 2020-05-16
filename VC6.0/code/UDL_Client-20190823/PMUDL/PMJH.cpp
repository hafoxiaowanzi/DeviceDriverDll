// PM1830C.cpp: implementation of the CPM1830C class.
//
//////////////////////////////////////////////////////////////////////
//UPDATE BY RIS 2013-9-22

#include "stdafx.h"
#include "..\\include\\PM.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPMJH::CPMJH()
{

}

CPMJH::~CPMJH()
{

}

DWORD CPMJH::ReadPower(long lSlot,long lChIndex, double* pdbReadPower)
{
	DWORD dwError;
	dwError = StartReadJHPower();
	if(dwError!=SUCCESS)
	{
		return ERROR_PW||dwError;
	}
	Sleep(100);
    dwError = ReadJHPower(lSlot,lChIndex,*pdbReadPower);
	if(dwError!=SUCCESS)
	{
		return ERROR_PW||dwError;
	}	
	return dwError;
}

DWORD CPMJH::GetPower(long lSlot,long IChan, double* pdblPowerValue)
{
	DWORD dwError;
	if (IChan ==0)
	{
		SelectCh(1);
	}
	else
	{
		SelectCh(2);
	}
	Sleep(3000);
	dwError = StartReadJHPower();
	if(dwError!=SUCCESS)
	{
		return ERROR_PW||dwError;
	}

    dwError = ReadJHPower(lSlot,IChan,*pdblPowerValue);
	if(dwError!=SUCCESS)
	{
		return ERROR_PW||dwError;
	}
	
	return dwError;

}

DWORD CPMJH::SetWavelength(long lSlot,long IChan,double dblWavelength)
{
	unsigned char send_buf[7];
    unsigned char cResult[9];
	unsigned char xor = 0;
	DWORD			dWavlength;
	DWORD         dwErrorCode;

	if (IChan ==0)
	{
		SelectCh(1);
	}
	else
	{
		SelectCh(2);
	}
	Sleep(3000);

	m_dbOldSetWL = dblWavelength + 0.4;
	dWavlength = (DWORD)m_dbOldSetWL;
	memset(cResult, 0x00, 9 * sizeof(unsigned char));
	send_buf[0]=(char)0xaa;
	send_buf[1]=(char)0xbb;
	send_buf[2]=(char)0xcc;
	send_buf[3]=(char)(0x07+IChan);//只针对通道1
	send_buf[4]=(char)(dWavlength / 256);
	send_buf[5]=(char)(dWavlength % 256);
	send_buf[6]=(char)(send_buf[1] ^ send_buf[2] ^ send_buf[3] ^ send_buf[4] ^ send_buf[5]);

	dwErrorCode = m_DevComHandle.WriteDevice((char *)send_buf,7);
	if(dwErrorCode!=SUCCESS)
	{
		return dwErrorCode;
	}
	
	Sleep(50);
	
    dwErrorCode = m_DevComHandle.ReadDevice((char *)cResult,9);
	if(dwErrorCode!=SUCCESS)
	{
		dwErrorCode = m_DevComHandle.ReadDevice((char *)cResult,9);
		if(dwErrorCode!=SUCCESS)
		{
			dwErrorCode = m_DevComHandle.WriteDevice((char *)send_buf,7);
			if(dwErrorCode!=SUCCESS)
			{
				return dwErrorCode;
			}
			dwErrorCode = m_DevComHandle.ReadDevice((char *)cResult,9);
			if(dwErrorCode!=SUCCESS)
			{
				dwErrorCode = m_DevComHandle.ReadDevice((char *)cResult,9);
				if(dwErrorCode!=SUCCESS)
				{
					return dwErrorCode;
				}
			}
		}
	
	}
	xor = cResult[1] ^ cResult[2] ^ cResult[3] ^ cResult[4] ^ cResult[5] ^ cResult[6] ^ cResult[7];
	
	if(cResult[0] == 0x55 && xor == cResult[8]) //数据校验成功
	{
		if(dWavlength != (DWORD)(cResult[2] * 256 + cResult[3])) 
			return ERROR_WL;
		else
			return SUCCESS;
	}
	else 
		return ERROR_WL;
	
	return dwErrorCode;
}

DWORD CPMJH::GetWavelength(long lSlot,long IChan,double *pdbWL)
{	
	DWORD dwErrorCode = 0;
	return dwErrorCode;
}

DWORD CPMJH::SetRangeMode(long lSlot,long IChan,long bAuto)
{	
	DWORD dwErrorCode = 0;
	return dwErrorCode;
}
DWORD CPMJH::SetRange(long lSlot,long IChan, long lRange)
{	
	DWORD dwErrorCode = 0;
	return dwErrorCode;	
}
DWORD CPMJH::GetRangeMode(long lSlot,long IChan,long *iPWMRangeMode)
{	
	DWORD dwErrorCode = 0;
	return dwErrorCode;	
}

DWORD CPMJH::SetMode(long lSlot,long lChIndex,DWORD dwMode)
{	
	DWORD dwErrorCode = 0;
	return dwErrorCode;
}

DWORD CPMJH::GetMode(long lSlot,long lChIndex,DWORD &dwMode)
{	
	DWORD dwErrorCode = 0;
	return dwErrorCode;	
}

DWORD CPMJH::SetParameters(long lSlot,long IChan, BOOL bAutoRange, double dblWavelength, double dblAvgTile, double dblPwrRange)
{
	DWORD dwErrorCode = 0;
	dwErrorCode = SetWavelength(lSlot,IChan,dblWavelength);
	
	return dwErrorCode;
}

DWORD CPMJH::SetUnit(long lSlot,long IChan,long lPWMUnit)
{
	unsigned char send_buf[7];
	unsigned char cResult[9];
	unsigned char xor = 0;
	BYTE		bUnitsIndex;
	DWORD       dwErrorCode;
	if (IChan ==0)
	{
		SelectCh(1);
	}
	else
	{
		SelectCh(2);
	}
	memset(cResult, 0x00, 9 * sizeof(unsigned char));
	switch(lPWMUnit)
	{
	case 1:// w
		bUnitsIndex = 0x01;
		break;
	case 2://dB
		bUnitsIndex = 0x02;
		break;
	case 3://dBm
		bUnitsIndex = 0x00;
		break;
	case 4://REF
		bUnitsIndex = 0x03;
		break;
	default:
		return ERROR_UNIT;
	}
	send_buf[0]=(char)0xaa;
	send_buf[1]=(char)0xbb;
	send_buf[2]=(char)0xcc;
	send_buf[3]=(char)(0x09+IChan);//只设置通道1
	send_buf[4]=(char)bUnitsIndex;
	send_buf[5]=(char)0;
	send_buf[6]=(char)(send_buf[1] ^ send_buf[2] ^ send_buf[3] ^ send_buf[4] ^ send_buf[5]);
	dwErrorCode = m_DevComHandle.WriteDevice((char *)send_buf, 7);
	if (dwErrorCode!=SUCCESS)
	{
		return dwErrorCode;
	}
	Sleep(50);
	dwErrorCode = m_DevComHandle.ReadDevice((char *)cResult,9);
	if(dwErrorCode!=SUCCESS)
	{
		return dwErrorCode;
	}
	else
	{
		xor = cResult[1] ^ cResult[2] ^ cResult[3] ^ cResult[4] ^ cResult[5] ^ cResult[6] ^ cResult[7];
		
		if(cResult[0] == 0x55 && xor == cResult[8]) //数据校验成功
		{
			if(cResult[4] != bUnitsIndex) 
				return ERROR_UNIT;
			else
				return SUCCESS;
		}
		else 
			return ERROR_UNIT;
	}
	return dwErrorCode;
}

DWORD CPMJH::GetUnit(long lSlot,long IChan,long *piUnit)
{	
	DWORD dwErrorCode = 0;
	return dwErrorCode;		
}

DWORD CPMJH::SetAverageTime(long lSlot,long IChan,double dblAvgTime)
{	
	DWORD dwErrorCode = 0;
	return dwErrorCode;	
}

DWORD CPMJH::GetAverageTime(long lSlot,long IChan,double *dblAverageTime)
{	
	DWORD dwErrorCode = 0;
	return dwErrorCode;		
}

DWORD CPMJH::Zero(long lSlot,long IChan)
{	
	DWORD dwErrorCode = 0;
	return dwErrorCode;	
}

DWORD CPMJH::ReadJHPower(long lSlot,long lChIndex,double &dblPower)
{
	char	      c1[4];
	unsigned char send_buf[7];
	unsigned char cResult[9];
	unsigned char xor = 0;
	float			fTempValue = -99.0;
	float           fTempValue2 = -99.0;
	DWORD dwErrorCode;
	memset(cResult, 0x00, 9 * sizeof(unsigned char));

	send_buf[0]=(char)0xaa;
	send_buf[1]=(char)0x07;
	send_buf[2]=(char)0;
	send_buf[3]=(char)0;
	send_buf[4]=(char)0;
	send_buf[5]=(char)0;
	send_buf[6]=(char)0x07;
    
//	viWrite(vi, (unsigned char *)send_buf, 7, &dwCount);
	dwErrorCode = m_DevComHandle.WriteDevice((char*)send_buf,7);
	if(dwErrorCode!=SUCCESS)
	{
		return dwErrorCode;
	}

	Sleep(10);
	
	if (lChIndex ==0)
	{
		dwErrorCode = m_DevComHandle.ReadDevice((char*)cResult,9);
		if(dwErrorCode==SUCCESS)
		{
			c1[0] = cResult[4];
			c1[1] = cResult[5];
			c1[2] = cResult[6];
			c1[3] = cResult[7];
			
			fTempValue = *(float*)(c1);
			dblPower = fTempValue;
		}
		else
			return dwErrorCode;
		
		dwErrorCode = m_DevComHandle.ReadDevice((char*)cResult,9);
		if(dwErrorCode==SUCCESS)
		{
			c1[0] = cResult[4];
			c1[1] = cResult[5];
			c1[2] = cResult[6];
			c1[3] = cResult[7];
			fTempValue2 = *(float *)(c1);
		}
		else
			return dwErrorCode;
	}
	else if(lChIndex ==1)
	{

		dwErrorCode = m_DevComHandle.ReadDevice((char*)cResult,9);
		if(dwErrorCode==SUCCESS)
		{
			c1[0] = cResult[4];
			c1[1] = cResult[5];
			c1[2] = cResult[6];
			c1[3] = cResult[7];
			
			fTempValue = *(float*)(c1);
		}
		else
			return dwErrorCode;


		dwErrorCode = m_DevComHandle.ReadDevice((char*)cResult,9);
		if(dwErrorCode==SUCCESS)
		{
			c1[0] = cResult[4];
			c1[1] = cResult[5];
			c1[2] = cResult[6];
			c1[3] = cResult[7];
			fTempValue2 = *(float *)(c1);
			dblPower = fTempValue2;
		}
		else
			return dwErrorCode;
	}

	return dwErrorCode;
}

DWORD CPMJH::StartReadJHPower()
{
	unsigned char send_buf[7];
	unsigned char cResult[9];
	unsigned char xor = 0;
	DWORD dwErrorCode;

	memset(cResult, 0x00, 9 * sizeof(unsigned char));

	send_buf[0]=(char)0xaa;
	send_buf[1]=(char)0x08;
	send_buf[2]=(char)0;
	send_buf[3]=(char)0;
	send_buf[4]=(char)0;
	send_buf[5]=(char)0;
	send_buf[6]=(char)0x08;
    
	dwErrorCode = m_DevComHandle.WriteDevice((char *)send_buf,7);
	if(dwErrorCode!=SUCCESS)
	{
		return dwErrorCode;
	}

	Sleep(200);
	
	dwErrorCode = m_DevComHandle.ReadDevice((char *)cResult,9);
	if(dwErrorCode==SUCCESS)	//读取成功
	{
		if(cResult[1] == 0x05 && cResult[2] == 0x01)
			return SUCCESS;
		else
			return ERROR_PW;
	}
	else
		return dwErrorCode;
}

DWORD CPMJH::StopReadJHPower()
{
	unsigned char send_buf[7];
	unsigned char cResult[9];
	unsigned char xor = 0;
	DWORD dwErrorCode;

	memset(cResult, 0x00, 9 * sizeof(unsigned char));

	send_buf[0]=(char)0xaa;
	send_buf[1]=(char)0x09;
	send_buf[2]=(char)0;
	send_buf[3]=(char)0;
	send_buf[4]=(char)0;
	send_buf[5]=(char)0;
	send_buf[6]=(char)0x09;
    
	dwErrorCode = m_DevComHandle.WriteDevice((char *)send_buf,7);
	if(dwErrorCode!=SUCCESS)
	{
		return dwErrorCode;
	}
	Sleep(10);

	dwErrorCode = m_DevComHandle.ReadDevice((char *)cResult,9);
	if(dwErrorCode==SUCCESS)	//读取成功
	{
		if(cResult[1] == 0x05 && cResult[2] == 0x01)
			return SUCCESS;
		else
			return ERROR_PW;
	}
	else
		return dwErrorCode;
}

DWORD CPMJH::SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle)
{
	DWORD   dwErrorCode=0;
//	LPCTSTR lpCommunicationInfo;
    
	dwErrorCode = m_DevComHandle.SetDeviceHandle(pszDeviceAddr, handle);
	return dwErrorCode;
}

DWORD CPMJH::CloseDevice()
{
	DWORD   dwErrorCode;
	dwErrorCode = m_DevComHandle.CloseDevice();
	if (dwErrorCode!=SUCCESS)
	{
		return dwErrorCode;
	}
	return dwErrorCode;
}

DWORD CPMJH::OpenDevice(LPCTSTR pszDeviceAddr,unsigned long *ComHandle)
{
	//CString strComPort;	
	DWORD   dwErrorCode;

	dwErrorCode = m_DevComHandle.OpenDevice(pszDeviceAddr,*ComHandle);
	if (dwErrorCode != SUCCESS)
	{
		return dwErrorCode;
	}	
	return dwErrorCode;
}

DWORD CPMJH::GetDeviceInfo(CHAR * pchInfo)
{
	DWORD dwErrorCode=0;
	return dwErrorCode;
}
DWORD CPMJH::SelectCh(int nChIndex)
{
	int nCount;
	unsigned char send_buf[7];
	unsigned char cResult[9];
	unsigned char xor = 0;
	DWORD dwErrorCode;

	memset(cResult, 0x00, 9 * sizeof(unsigned char));
	nCount = 0;
	while (TRUE)
	{
		send_buf[0]=(char)0xaa;
		send_buf[1]=(char)0xbb;
		send_buf[2]=(char)0xcc;
		send_buf[3]=(char)0x06;//只针对通道1
		send_buf[4]=(char)0x00;
		send_buf[5]=(char)0x00;
		send_buf[6]=(char)(send_buf[1] ^ send_buf[2] ^ send_buf[3] ^ send_buf[4] ^ send_buf[5]);
		
		dwErrorCode = m_DevComHandle.WriteDevice((char *)send_buf,7);
		if(dwErrorCode!=SUCCESS)
		{
			return dwErrorCode;
		}
		
		Sleep(50);
		
		//		if(viRead(vi, (unsigned char *)cResult, 9, &dwCount) >= VI_SUCCESS)	//读取成功
		dwErrorCode = m_DevComHandle.ReadDevice((char *)cResult,9);
		if(dwErrorCode!=SUCCESS)
		{
			dwErrorCode = m_DevComHandle.ReadDevice((char *)cResult,9);
			if(dwErrorCode!=SUCCESS)
			{
				dwErrorCode = m_DevComHandle.WriteDevice((char *)send_buf,7);
				if(dwErrorCode!=SUCCESS)
				{
					return dwErrorCode;
				}
				dwErrorCode = m_DevComHandle.ReadDevice((char *)cResult,9);
				if(dwErrorCode!=SUCCESS)
				{
					dwErrorCode = m_DevComHandle.ReadDevice((char *)cResult,9);
					if(dwErrorCode!=SUCCESS)
					{
						return dwErrorCode;
					}
				}
			}
			
		}
		xor = cResult[1] ^ cResult[2] ^ cResult[3] ^ cResult[4] ^ cResult[5] ^ cResult[6] ^ cResult[7];
		if(cResult[0] == 0x55 && xor == cResult[8]) //数据校验成功
		{
			if(cResult[5] == nChIndex)
			{					
				break;
			}	
		}
		Sleep(2000);

		nCount++;
		if(nCount > 10)
		{
			break;
		}
	}
	return dwErrorCode;
}
DWORD CPMJH::PrepareScan(long lSlot,long lChIndex,stScanParam* lScanParam)
{
	CString strTemp;
	char* token=NULL;
	char sep[]=",";
	int nCount=0;
	DWORD dwErrorCode =SUCCESS;
	
	try
	{
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return UNEXPECT_OCCUR;
	}
	
	return dwErrorCode;		
}

DWORD CPMJH::SetPMScanStart(long lSlot,long lChIndex)
{	
	DWORD dwErrorCode =SUCCESS;
	try
	{
		
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return UNEXPECT_OCCUR;
	}
	
	return dwErrorCode;	
}

DWORD CPMJH::getLambdaScanPMResult(long lSlot,long lChIndex,double* pdbPMArry)
{

	DWORD dwErrorCode =SUCCESS;
	PBYTE pbyBuf=NULL;
	CString strTemp;
	try
	{
					
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return UNEXPECT_OCCUR;
	}
	
	if (pbyBuf)
	{
		delete [] pbyBuf ;
	}
	
	return dwErrorCode;		
}

DWORD CPMJH::SetPMScanStop(long lSlot,long lChIndex)
{
	CString strTemp;
	DWORD dwErrorCode =SUCCESS;
	try
	{

	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return UNEXPECT_OCCUR;
	}
	return dwErrorCode;	
}


DWORD CPMJH::SetPMScanTriggerStop(long lSlot,long lChIndex)
{
	CString strTemp;
	DWORD dwErrorCode =SUCCESS;
	try
	{

	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return UNEXPECT_OCCUR;
	}
	return dwErrorCode;	
}
///////////////////////////////////////////////////////////////////
//函数说明：
//    设置功率计为获得最大、最小功率模式，获得相应的最大、最小功率
//Add by wanxin
////////////////////////////////////////////////////////////////////////
DWORD CPMJH::GetPMMaxMinPower(long lSlot,long IChan,double *pdbGetMax,double *pdbGetMin)
{
	//CString strTemp;
	char chReadBuf[100];
	DWORD dwErrorCode=0;
	try
	{			

	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
///////////////////////////////////////////////////////////////////
//函数说明：
//    设置功率计为获得最大、最小功率模式
//Add by wanxin
////////////////////////////////////////////////////////////////////////
DWORD CPMJH::SetPMMaxMinPowerStart(long lSlot,long IChan)
{
	char chReadBuf[100];
	DWORD dwErrorCode=0;
	try
	{			

	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return UNEXPECT_OCCUR;
	}
	return dwErrorCode;	
}
DWORD CPMJH::SetPMMinMaxStop(long lSlot,long IChan)
{
	char chReadBuf[100];
	DWORD dwErrorCode=0;
	try
	{			
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}
DWORD CPMJH::SetPMPowerOffset(long lSlot,long IChan,double dbPowerOffset)
{
	char chReadBuf[100];
	DWORD dwErrorCode=0;
	try
	{			
	}
	catch(DWORD dwError)
	{
		dwErrorCode = dwError;
	}
	catch (...)
	{
		return UNEXPECT_OCCUR;
	}
	return dwErrorCode;
}