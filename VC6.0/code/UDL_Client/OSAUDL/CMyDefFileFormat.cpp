#include "stdafx.h"
#include "..\\include\\CMyDefFileFormat.h"
#include "stdio.h"


CCMyDefFileFormat::CCMyDefFileFormat()
{
}


CCMyDefFileFormat::~CCMyDefFileFormat()
{

}

//////////////////////////////////////////////////
//函数说明：
//    写OTDM Raw Data为binary文件
//Add by wanxin
//Time:2019/07/15
//////////////////////////////////////////////////
BOOL CCMyDefFileFormat::WriteOTMSFileData2Binary(LPCSTR lpstrFileName, stOTMSFileData stFileData)
{
	HANDLE hFile = INVALID_HANDLE_VALUE;
	char szMsg[MAX_PATH];
	BYTE* bWritePtr =NULL;
	stOSAScanRawBYTEData stWriteData;

	bWritePtr = (BYTE*)&stFileData.stFileHeader;

	hFile = (HANDLE)CreateFile(lpstrFileName, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, NULL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		ZeroMemory(szMsg, MAX_PATH);
		sprintf(szMsg, "Create File:%s error", lpstrFileName);
		return FALSE;
	}
	//写文件头部信息
	DWORD dwStLength = sizeof(stFileData.stFileHeader);
	DWORD writesize = 0;
	if (!WriteFile(hFile, bWritePtr, dwStLength, &writesize, NULL))
	{
		ZeroMemory(szMsg, MAX_PATH);
		sprintf(szMsg, "Write File:%s error", lpstrFileName);
		return FALSE;
	}
	//写数据体信息，这里需要将double转换成BYTE
	stWriteData.nPointCount = stFileData.stRawData.nPointCount;
	int nRawDataBYTELength = stFileData.stRawData.nPointCount * 4;
	stWriteData.bWLArry = (BYTE*)VirtualAlloc(NULL, nRawDataBYTELength, MEM_RESERVE, PAGE_READWRITE);
	ZeroMemory(stWriteData.bWLArry, nRawDataBYTELength);
	stWriteData.bPowerArry = (BYTE*)VirtualAlloc(NULL, nRawDataBYTELength, MEM_RESERVE, PAGE_READWRITE);
	ZeroMemory(stWriteData.bPowerArry, nRawDataBYTELength);
	stWriteData.bRBWArry = (BYTE*)VirtualAlloc(NULL, nRawDataBYTELength, MEM_RESERVE, PAGE_READWRITE);
	ZeroMemory(stWriteData.bRBWArry, nRawDataBYTELength);

	int j = 0;
	for (int i = 0;i < nRawDataBYTELength;i += 4)
	{
		DWORD dwTempValue = DWORD(stFileData.stRawData.pdblWL[j] * 1000);
		stWriteData.bWLArry[i] = 0xff & (dwTempValue >> 24);
		stWriteData.bWLArry[i+1] = 0xff & (dwTempValue >> 16);
		stWriteData.bWLArry[i+2] = 0xff & (dwTempValue >> 8);
		stWriteData.bWLArry[i+3] = 0xff & (dwTempValue);

		dwTempValue = DWORD(stFileData.stRawData.pdblPower[j] * 1000);
		stWriteData.bPowerArry[i] = 0xff & (dwTempValue >> 24);
		stWriteData.bPowerArry[i + 1] = 0xff & (dwTempValue >> 16);
		stWriteData.bPowerArry[i + 2] = 0xff & (dwTempValue >> 8);
		stWriteData.bPowerArry[i + 3] = 0xff & (dwTempValue);

		dwTempValue = DWORD(stFileData.stRawData.pdblRBW[j] * 1000);
		stWriteData.bRBWArry[i] = 0xff & (dwTempValue >> 24);
		stWriteData.bRBWArry[i + 1] = 0xff & (dwTempValue >> 16);
		stWriteData.bRBWArry[i + 2] = 0xff & (dwTempValue >> 8);
		stWriteData.bRBWArry[i + 3] = 0xff & (dwTempValue);
		j++;
	}

	bWritePtr = (BYTE*)&stWriteData;

	//写文件头部信息
	dwStLength = sizeof(stWriteData);
	writesize = 0;
	if (!WriteFile(hFile, bWritePtr, dwStLength, &writesize, NULL))
	{
		ZeroMemory(szMsg, MAX_PATH);
		sprintf(szMsg, "Write File:%s error", lpstrFileName);
		return FALSE;
	}

	if (hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFile);
	}

	return TRUE;
}
//////////////////////////////////////////////////////////////////
//函数说明：
//    从OTDM Raw data binary文件中读取数据复制给结构体
//Add by wanxin
//Time:2019/7/15
//////////////////////////////////////////////////////////////////
BOOL CCMyDefFileFormat::ReadOTMSFileDataFromBinFile(LPCSTR lpstrFileName, pOTMSFileData pData)
{
	HANDLE hFile = INVALID_HANDLE_VALUE;
	char szMsg[MAX_PATH];
	BYTE* bReadPtr = NULL;
	bReadPtr = (BYTE*)&pData->stFileHeader;

	hFile = (HANDLE)CreateFile(lpstrFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_BACKUP_SEMANTICS, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		ZeroMemory(szMsg, MAX_PATH);
		sprintf(szMsg, "Create File:%s error", lpstrFileName);
		return FALSE;
	}
	DWORD dwReadLength = sizeof(stOTMSFileHeader);
	DWORD readsize = 0;
	//读取文件头部
	if (!ReadFile(hFile, bReadPtr, dwReadLength, &readsize, NULL))
	{
		ZeroMemory(szMsg, MAX_PATH);
		sprintf(szMsg, "Read File:%s error", lpstrFileName);
		return FALSE;
	}
	WORD  wSampleCount = 0xff00 & (pData->stFileHeader.bSMPL[0] << 8);
	wSampleCount += pData->stFileHeader.bSMPL[1];
	stOSAScanRawBYTEData stData;
	stData.nPointCount = wSampleCount;

	stData.bWLArry = (BYTE*)VirtualAlloc(NULL, 4 * wSampleCount, MEM_RESERVE, PAGE_READWRITE);
	stData.bPowerArry = (BYTE*)VirtualAlloc(NULL, 4 * wSampleCount, MEM_RESERVE, PAGE_READWRITE);
	stData.bRBWArry = (BYTE*)VirtualAlloc(NULL, 4 * wSampleCount, MEM_RESERVE, PAGE_READWRITE);

	dwReadLength = sizeof(stData);

	bReadPtr = (BYTE*)&stData;
	if (!ReadFile(hFile, bReadPtr, dwReadLength, &readsize, NULL))
	{
		ZeroMemory(szMsg, MAX_PATH);
		sprintf(szMsg, "Read File:%s error", lpstrFileName);
		return FALSE;
	}

	if (hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFile);
	}

	pData->stRawData.nPointCount = wSampleCount;
	int j = 0;
	DWORD dwTempValue;
	for (int i = 0;i < wSampleCount * 4;i += 4)
	{
		dwTempValue = stData.bWLArry[i] << 24;
		dwTempValue += stData.bWLArry[i+1] << 16;
		dwTempValue += stData.bWLArry[i+2] << 8;
		dwTempValue += stData.bWLArry[i+3] ;
		pData->stRawData.pdblWL[j] = (double)dwTempValue / 1000.0;

		dwTempValue = stData.bPowerArry[i] << 24;
		dwTempValue += stData.bPowerArry[i + 1] << 16;
		dwTempValue += stData.bPowerArry[i + 2] << 8;
		dwTempValue += stData.bPowerArry[i + 3];
		pData->stRawData.pdblPower[j] = (double)dwTempValue / 1000.0;

		dwTempValue = stData.bRBWArry[i] << 24;
		dwTempValue += stData.bRBWArry[i + 1] << 16;
		dwTempValue += stData.bRBWArry[i + 2] << 8;
		dwTempValue += stData.bRBWArry[i + 3];
		pData->stRawData.pdblRBW[j] = (double)dwTempValue / 1000.0;
		j++;
	}

	return TRUE;
}
/////////////////////////////////////////////////////////////////////
//函数说明：
//    从OTDM Binary file中读取头部信息
//Add by wanxin
//Time：2019/7/15
////////////////////////////////////////////////////////////////////
BOOL CCMyDefFileFormat::ReadOTMSBinFileHeader(LPCSTR lpstrBinFile, pOTMSFileHeader pFileHeader)
{
	HANDLE hFile = INVALID_HANDLE_VALUE;
	char szMsg[MAX_PATH];
	BYTE* bReadPtr = NULL;
	bReadPtr = (BYTE*)pFileHeader;

	hFile = (HANDLE)CreateFile(lpstrBinFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_BACKUP_SEMANTICS, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		ZeroMemory(szMsg, MAX_PATH);
		sprintf(szMsg, "Create File:%s error", lpstrBinFile);
		return FALSE;
	}
	DWORD dwHeadSize = OTDMBINFILEHEADERLENGTH;
	DWORD readsize = 0;

	if (!ReadFile(hFile, bReadPtr, dwHeadSize, &readsize, NULL))
	{
		ZeroMemory(szMsg, MAX_PATH);
		sprintf(szMsg, "Read file header:%s error", lpstrBinFile);
		return FALSE;
	}

	if (hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFile);
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////
//函数说明：
//   从OTDM Binary文件中读取Raw Data数据
//Add by wanxin
//Time:2019/7/15
/////////////////////////////////////////////////////////////////////////
BOOL CCMyDefFileFormat::ReadOTMSBinRawData(LPCSTR lpstrBinFile, pOSAScanRawData pRawData)
{
	HANDLE hFile = INVALID_HANDLE_VALUE;
	char szMsg[MAX_PATH];
	BYTE* bReadPtr = NULL;
	stOSAScanRawBYTEData stData;
	bReadPtr = (BYTE*)&stData;

	hFile = (HANDLE)CreateFile(lpstrBinFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_BACKUP_SEMANTICS, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		ZeroMemory(szMsg, MAX_PATH);
		sprintf(szMsg, "Create File:%s error", lpstrBinFile);
		return FALSE;
	}

	DWORD dwFileSize = GetFileSize(hFile, NULL);
	DWORD dwPtr  = SetFilePointer(hFile, OTDMBINFILEHEADERLENGTH, NULL, FILE_CURRENT);
	if (dwPtr == INVALID_FILE_SIZE)
	{
		//获取出错码。
		ZeroMemory(szMsg, MAX_PATH);
		sprintf(szMsg, "Set file point error, Error code :%d", GetLastError());
		return FALSE;          
	}

	DWORD dwDataSize = dwFileSize - OTDMBINFILEHEADERLENGTH;
	DWORD readsize = 0;

	if (!ReadFile(hFile, bReadPtr, dwDataSize, &readsize, NULL))
	{
		ZeroMemory(szMsg, MAX_PATH);
		sprintf(szMsg, "Read file raw data:%s error", lpstrBinFile);
		return FALSE;
	}

	if (hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFile);
	}
	pRawData->nPointCount = stData.nPointCount;
	int j = 0;
	DWORD dwTempValue;
	for (int i = 0;i < stData.nPointCount * 4;i += 4)
	{
		dwTempValue = stData.bWLArry[i] << 24;
		dwTempValue += stData.bWLArry[i + 1] << 16;
		dwTempValue += stData.bWLArry[i + 2] << 8;
		dwTempValue += stData.bWLArry[i + 3];
		pRawData->pdblWL[j] = (double)dwTempValue / 1000.0;

		dwTempValue = stData.bPowerArry[i] << 24;
		dwTempValue += stData.bPowerArry[i + 1] << 16;
		dwTempValue += stData.bPowerArry[i + 2] << 8;
		dwTempValue += stData.bPowerArry[i + 3];
		pRawData->pdblPower[j] = (double)dwTempValue / 1000.0;

		dwTempValue = stData.bRBWArry[i] << 24;
		dwTempValue += stData.bRBWArry[i + 1] << 16;
		dwTempValue += stData.bRBWArry[i + 2] << 8;
		dwTempValue += stData.bRBWArry[i + 3];
		pRawData->pdblRBW[j] = (double)dwTempValue / 1000.0;
		j++;
	}

	return TRUE;
}


/////////////////////////////////////////////////////////////////
//函数说明：
//    根据制定文件名称转换OTDM Binary格式文件为CSV格式文件
//Add by wanxin
//Time:2019/07/15
/////////////////////////////////////////////////////////////////
BOOL CCMyDefFileFormat::ConvertOTMSFileBin2CSV(LPCSTR lpstrBinFile, LPCSTR lpstrCSVFile)
{
	char szMsg[MAX_PATH];
	stOTMSFileData stRawData;
	stRawData.stRawData.pdblWL = NULL;
	stRawData.stRawData.pdblPower = NULL;
	stRawData.stRawData.pdblRBW = NULL;

	if (!ReadOTMSBinFileHeader(lpstrBinFile, &stRawData.stFileHeader))
	{
		ZeroMemory(szMsg, MAX_PATH);
		sprintf(szMsg, "Read OTMS raw data header error");
		return FALSE;
	}

	WORD wSampleCount = stRawData.stFileHeader.bSMPL[1] << 8 + stRawData.stFileHeader.bSMPL[0];
	if (stRawData.stRawData.pdblWL == NULL)
	{
		stRawData.stRawData.pdblWL = (double*)VirtualAlloc(NULL, sizeof(double)*wSampleCount, MEM_RESERVE, PAGE_READWRITE);
		ZeroMemory(stRawData.stRawData.pdblWL, sizeof(double)*wSampleCount);
	}

	if (stRawData.stRawData.pdblPower == NULL)
	{
		stRawData.stRawData.pdblPower = (double*)VirtualAlloc(NULL, sizeof(double)*wSampleCount, MEM_RESERVE, PAGE_READWRITE);
		ZeroMemory(stRawData.stRawData.pdblPower, sizeof(double)*wSampleCount);
	}
	
	if (stRawData.stRawData.pdblRBW == NULL)
	{
		stRawData.stRawData.pdblRBW = (double*)VirtualAlloc(NULL, sizeof(double)*wSampleCount, MEM_RESERVE, PAGE_READWRITE);
		ZeroMemory(stRawData.stRawData.pdblRBW, sizeof(double)*wSampleCount);
	}

	if (!ReadOTMSBinRawData(lpstrBinFile, &stRawData.stRawData))
	{
		ZeroMemory(szMsg, MAX_PATH);
		sprintf(szMsg, "Read OTMS raw data error");
		return FALSE;
	}

	if (!WriteOTMSRawData2CSV(lpstrCSVFile, stRawData))
	{
		ZeroMemory(szMsg, MAX_PATH);
		sprintf(szMsg, "Write OTDM raw data csv file error");
		return FALSE;
	}

	if (stRawData.stRawData.pdblWL != NULL)
	{
		VirtualFree(stRawData.stRawData.pdblWL, 0, MEM_RELEASE);
	}

	if (stRawData.stRawData.pdblPower != NULL)
	{
		VirtualFree(stRawData.stRawData.pdblPower, 0, MEM_RELEASE);
	}

	if (stRawData.stRawData.pdblRBW != NULL)
	{
		VirtualFree(stRawData.stRawData.pdblRBW, 0, MEM_RELEASE);
	}

	return TRUE;
}

///////////////////////////////////////////////////////////////////
//函数说明：
//   根据给定的文件名称转换OTDM CSV文件格式为Binary文件格式
//暂时用不到，留好接口
//Add by wanxin
//Time:2018/07/15
///////////////////////////////////////////////////////////////////
BOOL CCMyDefFileFormat::ConvertOTMSFileCSV2Bin(LPCSTR lpstrCSVFile,LPCSTR lpstrBinFile )
{
	char szMsg[MAX_PATH];
	stOTMSFileData stRawData;
	stRawData.stRawData.pdblPower = NULL;
	stRawData.stRawData.pdblWL = NULL;
	stRawData.stRawData.pdblRBW = NULL;
	if (!ReadOTMSCSVFileHeader(lpstrCSVFile, &stRawData.stFileHeader))
	{
		ZeroMemory(szMsg, MAX_PATH);
		sprintf(szMsg, "Read OTMS CSV file header error");
		return FALSE;
	}
	WORD wSamplePointCount = 0xff00 & (stRawData.stFileHeader.bSMPL[0] << 8);
	wSamplePointCount += stRawData.stFileHeader.bSMPL[1];

	if (stRawData.stRawData.pdblWL == NULL)
	{
		stRawData.stRawData.pdblWL = (double*)VirtualAlloc(NULL, sizeof(double)*wSamplePointCount, MEM_RESERVE, PAGE_READWRITE);
		ZeroMemory(stRawData.stRawData.pdblWL, sizeof(double)*wSamplePointCount);
	}
	if (stRawData.stRawData.pdblPower == NULL)
	{
		stRawData.stRawData.pdblPower = (double*)VirtualAlloc(NULL, sizeof(double)*wSamplePointCount, MEM_RESERVE, PAGE_READWRITE);
		ZeroMemory(stRawData.stRawData.pdblPower, sizeof(double)*wSamplePointCount);
	}
	if (stRawData.stRawData.pdblRBW == NULL)
	{
		stRawData.stRawData.pdblRBW = (double*)VirtualAlloc(NULL, 4 * wSamplePointCount, MEM_RESERVE, PAGE_READWRITE);
		ZeroMemory(stRawData.stRawData.pdblRBW, sizeof(double)*wSamplePointCount);
	}

	if (!ReadOTMSCSVFileData(lpstrCSVFile, &stRawData))
	{
		ZeroMemory(szMsg, MAX_PATH);
		sprintf(szMsg, "Read OTMS CSV file error");
		return FALSE;
	}

	if (!WriteOTMSFileData2Binary(lpstrBinFile, stRawData))
	{
		ZeroMemory(szMsg, MAX_PATH);
		sprintf(szMsg, "Write OTMS bin file error");
		return FALSE;
	}
	if (stRawData.stRawData.pdblWL != NULL)
	{
		VirtualFree(stRawData.stRawData.pdblWL, 0, MEM_RELEASE);
	}
	if (stRawData.stRawData.pdblPower == NULL)
	{
		VirtualFree(stRawData.stRawData.pdblPower, 0, MEM_RELEASE);
	}
	if (stRawData.stRawData.pdblRBW == NULL)
	{
		VirtualFree(stRawData.stRawData.pdblRBW, 0, MEM_RELEASE);
	}

	return TRUE;
}

////////////////////////////////////////////////////////////////////////
//函数说明：
//   读取OTMS CSV File Header
//Add by wanxin
//Time:2019/7/24
//////////////////////////////////////////////////////////////////////
BOOL CCMyDefFileFormat::ReadOTMSCSVFileHeader(LPCSTR lpstrCSVFile, pOTMSFileHeader pFileHeader)
{
	FILE * fpFile = NULL;
	char szBuffer[1024];
	char szMsg[MAX_PATH];
	DWORD dwDataOffset;
	char *token = NULL;
	char szSpec[] = ",";

	if ((fpFile = fopen(lpstrCSVFile, "r")) == NULL)
	{
		ZeroMemory(szMsg, MAX_PATH);
		sprintf(szMsg, "Open file:%s error", lpstrCSVFile);
		return FALSE;
	}

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);
	assert(token);
	token = strtok(NULL, szSpec);//File Size Title
	assert(token);
	token = strtok(NULL, szSpec);//File Size
	assert(token);
	sprintf((char*)pFileHeader->bFileType, "%s", token);

	token = strtok(NULL, szSpec);//File Ver Title
	assert(token);
	token = strtok(NULL, szSpec);//File Ver
	assert(token);
	DWORD dwFileVer = atol(token);
	pFileHeader->bFileVer[0] = 0xff & (dwFileVer << 24);
	pFileHeader->bFileVer[1] = 0xff & (dwFileVer << 16);
	pFileHeader->bFileVer[2] = 0xff & (dwFileVer << 8);
	pFileHeader->bFileVer[3] = 0xff & (dwFileVer);

	token = strtok(NULL, szSpec);//File size Title
	assert(token);
	token = strtok(NULL, szSpec);//File size
	assert(token);
	DWORD dwFileSize = atol(token);
	pFileHeader->bFileSize[0] = 0xff & (dwFileSize << 24);
	pFileHeader->bFileSize[1] = 0xff & (dwFileSize << 16);
	pFileHeader->bFileSize[2] = 0xff & (dwFileSize << 8);
	pFileHeader->bFileSize[3] = 0xff & (dwFileSize);

	token = strtok(NULL, szSpec);//File CRC32 Title
	assert(token);
	token = strtok(NULL, szSpec);//File CRC32
	assert(token);
	DWORD dwCRC32 = atol(token);
	pFileHeader->bCRC32[0] = 0xff & (dwCRC32 << 24);
	pFileHeader->bCRC32[1] = 0xff & (dwCRC32 << 16);
	pFileHeader->bCRC32[2] = 0xff & (dwCRC32 << 8);
	pFileHeader->bCRC32[3] = 0xff & (dwCRC32);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);
	assert(token);
	token = strtok(NULL, szSpec);//SMPL Title
	assert(token);
	token = strtok(NULL, szSpec);//SMPL
	assert(token);
	WORD wSampleCount = atoi(token);
	pFileHeader->bSMPL[0] = 0xff & (wSampleCount << 8);
	pFileHeader->bSMPL[1] = 0xff & (wSampleCount);

	token = strtok(NULL, szSpec);//SENS Title
	assert(token);
	token = strtok(NULL, szSpec);//SENS
	assert(token);
	WORD wSense = atoi(token);
	pFileHeader->bSENS[0] = 0xff & (wSense << 8);
	pFileHeader->bSENS[1] = 0xff & (wSense);

	token = strtok(NULL, szSpec);//Chop Title
	assert(token);
	token = strtok(NULL, szSpec);//Chop
	assert(token);
	WORD wChopMode = atoi(token);
	pFileHeader->bChopMode[0] = 0xff & (wChopMode << 8);
	pFileHeader->bChopMode[1] = 0xff & (wChopMode);

	token = strtok(NULL, szSpec);//AverageTime Title
	assert(token);
	token = strtok(NULL, szSpec);//AverageTime
	assert(token);
	WORD wAverageTime = atoi(token);
	pFileHeader->bAvgTime[0] = 0xff & (wAverageTime << 8);
	pFileHeader->bAvgTime[1] = 0xff & (wAverageTime);

	token = strtok(NULL, szSpec);//REFLEVEL Title
	assert(token);
	token = strtok(NULL, szSpec);//REFLEVEL
	assert(token);
	WORD wRefLevel = atoi(token);
	pFileHeader->bREFLEVEL[0] = 0xff & (wRefLevel << 8);
	pFileHeader->bREFLEVEL[1] = 0xff & (wRefLevel);

	token = strtok(NULL, szSpec);//Log Scale Title
	assert(token);
	token = strtok(NULL, szSpec);//Log Scale
	assert(token);
	WORD wLogScale = atoi(token);
	pFileHeader->bLogScale[0] = 0xff & (wLogScale << 8);
	pFileHeader->bLogScale[1] = 0xff & (wLogScale);

	token = strtok(NULL, szSpec);//Result data offset Title
	assert(token);
	token = strtok(NULL, szSpec);//Result data offset
	assert(token);
	WORD wResOffset = atoi(token);
	pFileHeader->bResOffset[0] = 0xff & (wResOffset << 8);
	pFileHeader->bResOffset[1] = 0xff & (wResOffset);

	token = strtok(NULL, szSpec);//Raw data offset Title
	assert(token);
	token = strtok(NULL, szSpec);//Raw data offset
	assert(token);
	WORD wRawDataOffset = atoi(token);
	pFileHeader->bRawOffset[0] = 0xff & (wRawDataOffset << 8);
	pFileHeader->bRawOffset[1] = 0xff & (wRawDataOffset);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);
	assert(token);
	token = strtok(NULL, szSpec);//Start WL Title
	assert(token);
	token = strtok(NULL, szSpec);//Start WL
	assert(token);
	DWORD  dwStartWL = atol(token);
	pFileHeader->bStartWL[0] = 0xff & (dwStartWL << 24);
	pFileHeader->bStartWL[1] = 0xff & (dwStartWL << 16);
	pFileHeader->bStartWL[2] = 0xff & (dwStartWL << 8);
	pFileHeader->bStartWL[3] = 0xff & (dwStartWL);

	token = strtok(NULL, szSpec);//Stop WL Title
	assert(token);
	token = strtok(NULL, szSpec);//Stop WL
	assert(token);
	DWORD  dwStopWL = atol(token);
	pFileHeader->bStopWL[0] = 0xff & (dwStopWL << 24);
	pFileHeader->bStopWL[1] = 0xff & (dwStopWL << 16);
	pFileHeader->bStopWL[2] = 0xff & (dwStopWL << 8);
	pFileHeader->bStopWL[3] = 0xff & (dwStopWL);

	token = strtok(NULL, szSpec);//RES Title
	assert(token);
	token = strtok(NULL, szSpec);//RES
	assert(token);
	WORD  wRes = atoi(token);
	pFileHeader->bRESBW[0] = 0xff & (wRes << 8);
	pFileHeader->bRESBW[1] = 0xff & (wRes);

	token = strtok(NULL, szSpec);//MEAS WL Title
	assert(token);
	token = strtok(NULL, szSpec);//MEAS WL
	assert(token);
	WORD  wMeas = atoi(token);
	pFileHeader->bMEASWL[0] = 0xff & (wMeas << 8);
	pFileHeader->bMEASWL[1] = 0xff & (wMeas);

	token = strtok(NULL, szSpec);//Thresh level Title
	assert(token);
	token = strtok(NULL, szSpec);//Thresh level
	assert(token);
	WORD  wThreshlevel = atoi(token);
	pFileHeader->bThreshLevel[0] = 0xff & (wThreshlevel << 8);
	pFileHeader->bThreshLevel[1] = 0xff & (wThreshlevel);

	token = strtok(NULL, szSpec);//Mode Diff Title
	assert(token);
	token = strtok(NULL, szSpec);//Mode Diff
	assert(token);
	WORD  wModeDiff = atoi(token);
	pFileHeader->bModeDiff[0] = 0xff & (wModeDiff << 8);
	pFileHeader->bModeDiff[1] = 0xff & (wModeDiff);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);
	assert(token);
	token = strtok(NULL, szSpec);//Offset In Title
	assert(token);
	token = strtok(NULL, szSpec);//Offset In
	assert(token);
	WORD  wOffsetIn = atol(token);
	pFileHeader->bOffsetIN[0] = 0xff & (wOffsetIn << 8);
	pFileHeader->bOffsetIN[1] = 0xff & (wOffsetIn);

	token = strtok(NULL, szSpec);//Offset Out Title
	assert(token);
	token = strtok(NULL, szSpec);//Offset Out
	assert(token);
	WORD  wOffsetOut = atol(token);
	pFileHeader->bOffsetOUT[0] = 0xff & (wOffsetOut << 8);
	pFileHeader->bOffsetOUT[1] = 0xff & (wOffsetOut);

	token = strtok(NULL, szSpec);//ASE ALGO Title
	assert(token);
	token = strtok(NULL, szSpec);//ASE ALGO
	assert(token);
	WORD  wASEALGO = atol(token);
	pFileHeader->bASEALGO[0] = 0xff & (wASEALGO << 8);
	pFileHeader->bASEALGO[1] = 0xff & (wASEALGO);

	token = strtok(NULL, szSpec);//Fitting ALGO Title
	assert(token);
	token = strtok(NULL, szSpec);//Fitting ALGO
	assert(token);
	WORD  wFittingALGO = atol(token);
	pFileHeader->bFittingALGO[0] = 0xff & (wFittingALGO << 8);
	pFileHeader->bFittingALGO[1] = 0xff & (wFittingALGO);

	token = strtok(NULL, szSpec);//RES BW Title
	assert(token);
	token = strtok(NULL, szSpec);//RES BW
	assert(token);
	WORD  wResBW = atol(token);
	pFileHeader->bRESBW[0] = 0xff & (wResBW << 8);
	pFileHeader->bRESBW[1] = 0xff & (wResBW);

	token = strtok(NULL, szSpec);//Shot Noise Title
	assert(token);
	token = strtok(NULL, szSpec);//Shot Noise
	assert(token);
	WORD  wShotNoise = atol(token);
	pFileHeader->bShotNoise[0] = 0xff & (wShotNoise << 8);
	pFileHeader->bShotNoise[1] = 0xff & (wShotNoise);

	token = strtok(NULL, szSpec);//OSNR REQ Title
	assert(token);
	token = strtok(NULL, szSpec);//OSNR REQ
	assert(token);
	WORD  wOSNRREQ = atol(token);
	pFileHeader->bOSNRREQ[0] = 0xff & (wOSNRREQ << 8);
	pFileHeader->bOSNRREQ[1] = 0xff & (wOSNRREQ);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//OTMS Server ID Title
	assert(token);
	token = strtok(NULL, szSpec);//OTMS Server ID
	assert(token);
	sprintf((char*)pFileHeader->bServerID, "%s", token);

	token = strtok(NULL, szSpec);//Client ID Title
	assert(token);
	token = strtok(NULL, szSpec);//Client ID
	assert(token);
	sprintf((char*)pFileHeader->bClientID, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//Test Operator Title
	assert(token);
	token = strtok(NULL, szSpec);//Test Operator
	assert(token);
	sprintf((char*)pFileHeader->bTestOper, "%s", token);

	token = strtok(NULL, szSpec);//Test Time Title
	assert(token);
	token = strtok(NULL, szSpec);//Test Time
	assert(token);
	sprintf((char*)pFileHeader->bTestStamp, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//Server Name Title
	assert(token);
	token = strtok(NULL, szSpec);//Server Name
	assert(token);
	sprintf((char*)pFileHeader->bSWName, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//Server Version Title
	assert(token);
	token = strtok(NULL, szSpec);//Server Version
	assert(token);
	sprintf((char*)pFileHeader->bSWVer, "%s", token);

	token = strtok(NULL, szSpec);//Server Release Date Title
	assert(token);
	token = strtok(NULL, szSpec);//Server Release Date
	assert(token);
	sprintf((char*)pFileHeader->bSWRD, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//Client TP Name Title
	assert(token);
	token = strtok(NULL, szSpec);//Client TP Name
	assert(token);
	sprintf((char*)pFileHeader->bClientTPName, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//Client TP Version Title
	assert(token);
	token = strtok(NULL, szSpec);//Client TP Version
	assert(token);
	sprintf((char*)pFileHeader->bClientTPVer, "%s", token);

	token = strtok(NULL, szSpec);//Client TP Release Date Title
	assert(token);
	token = strtok(NULL, szSpec);//Client TP Release Date
	assert(token);
	sprintf((char*)pFileHeader->bClientTPRD, "%s", token);


	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//UDL Version Title
	assert(token);
	token = strtok(NULL, szSpec);//UDL Version
	assert(token);
	sprintf((char*)pFileHeader->bUDLVer, "%s", token);

	token = strtok(NULL, szSpec);//UDL Release Date Title
	assert(token);
	token = strtok(NULL, szSpec);//UDL Release Date
	assert(token);
	sprintf((char*)pFileHeader->bUDLVer, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//OSA Type Title
	assert(token);
	token = strtok(NULL, szSpec);//OSA Type
	assert(token);
	sprintf((char*)pFileHeader->bOSAType, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//OSA SN Title
	assert(token);
	token = strtok(NULL, szSpec);//OSA SN
	assert(token);
	sprintf((char*)pFileHeader->bOSASN, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//OSA FW VER Title
	assert(token);
	token = strtok(NULL, szSpec);//OSA FW VER
	assert(token);
	sprintf((char*)pFileHeader->bOSAFWVer, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//Server OSW Typpe Title
	assert(token);
	token = strtok(NULL, szSpec);//Server OSW Typpe
	assert(token);
	sprintf((char*)pFileHeader->bOSWType, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//Server OSW SN Title
	assert(token);
	token = strtok(NULL, szSpec);//Server OSW SN
	assert(token);
	sprintf((char*)pFileHeader->bOSWSN, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//Server OSW FW VER Title
	assert(token);
	token = strtok(NULL, szSpec);//Server OSW FW VER
	assert(token);
	sprintf((char*)pFileHeader->bOSWFWVer, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//Server OSW Channel Config Title
	assert(token);
	token = strtok(NULL, szSpec);//Server OSW Channel Config
	assert(token);
	sprintf((char*)pFileHeader->bOSWChConfig, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//Client OSW Type Title
	assert(token);
	token = strtok(NULL, szSpec);//Client OSW Type
	assert(token);
	sprintf((char*)pFileHeader->bClientOSWType, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//Client OSW SN Title
	assert(token);
	token = strtok(NULL, szSpec);//Client OSW SN
	assert(token);
	sprintf((char*)pFileHeader->bClientOSWSN, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//Client OSW FW VER Title
	assert(token);
	token = strtok(NULL, szSpec);//Client OSW FW VER
	assert(token);
	sprintf((char*)pFileHeader->bClientOSWFWVer, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//Client OSW Channel Config Title
	assert(token);
	token = strtok(NULL, szSpec);//Client OSW Channel Config
	assert(token);
	sprintf((char*)pFileHeader->bClientOSWChConfig, "%s", token);


	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//Client OPM Type Title
	assert(token);
	token = strtok(NULL, szSpec);//Client OPM Type
	assert(token);
	sprintf((char*)pFileHeader->bClientOPMType, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//Client OPM SN Title
	assert(token);
	token = strtok(NULL, szSpec);//Client OPM SN
	assert(token);
	sprintf((char*)pFileHeader->bClientOPMSN, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//Client OPM FW VER
	assert(token);
	token = strtok(NULL, szSpec);//Client OPM FW VER
	assert(token);
	sprintf((char*)pFileHeader->bClientOPMFWVer, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//Client OPM Slot
	assert(token);
	token = strtok(NULL, szSpec);//Client OPM Slot
	assert(token);
	sprintf((char*)pFileHeader->bClientOPMSlot, "%s", token);

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////
//函数说明：
//   从ODTM CSV文件中读取相应的数据
//暂时用不到，留好接口以后使用
//Add by wanxin
//Time:2019/7/17
/////////////////////////////////////////////////////////////////////////////
BOOL CCMyDefFileFormat::ReadOTMSCSVFileData(LPCSTR lpstrCSVFile, pOTMSFileData pFileData)
{
	FILE * fpFile = NULL;
	char szBuffer[1024];
	char szMsg[MAX_PATH];
	DWORD dwDataOffset;
	char *token = NULL;
	char szSpec[] = ",";

	if ((fpFile = fopen(lpstrCSVFile, "r")) == NULL)
	{
		ZeroMemory(szMsg, MAX_PATH);
		sprintf(szMsg, "Open file:%s error", lpstrCSVFile);
		return FALSE;
	}

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);
	assert(token);
	token = strtok(NULL, szSpec);//File Size Title
	assert(token);
	token = strtok(NULL, szSpec);//File Size
	assert(token);
	sprintf((char*)pFileData->stFileHeader.bFileType, "%s", token);

	token = strtok(NULL, szSpec);//File Ver Title
	assert(token);
	token = strtok(NULL, szSpec);//File Ver
	assert(token);
	DWORD dwFileVer = atol(token);
	pFileData->stFileHeader.bFileVer[0] = 0xff & (dwFileVer << 24);
	pFileData->stFileHeader.bFileVer[1] = 0xff & (dwFileVer << 16);
	pFileData->stFileHeader.bFileVer[2] = 0xff & (dwFileVer << 8);
	pFileData->stFileHeader.bFileVer[3] = 0xff & (dwFileVer);

	token = strtok(NULL, szSpec);//File size Title
	assert(token);
	token = strtok(NULL, szSpec);//File size
	assert(token);
	DWORD dwFileSize = atol(token);
	pFileData->stFileHeader.bFileSize[0] = 0xff & (dwFileSize << 24);
	pFileData->stFileHeader.bFileSize[1] = 0xff & (dwFileSize << 16);
	pFileData->stFileHeader.bFileSize[2] = 0xff & (dwFileSize << 8);
	pFileData->stFileHeader.bFileSize[3] = 0xff & (dwFileSize);

	token = strtok(NULL, szSpec);//File CRC32 Title
	assert(token);
	token = strtok(NULL, szSpec);//File CRC32
	assert(token);
	DWORD dwCRC32 = atol(token);
	pFileData->stFileHeader.bCRC32[0] = 0xff & (dwCRC32 << 24);
	pFileData->stFileHeader.bCRC32[1] = 0xff & (dwCRC32 << 16);
	pFileData->stFileHeader.bCRC32[2] = 0xff & (dwCRC32 << 8);
	pFileData->stFileHeader.bCRC32[3] = 0xff & (dwCRC32);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);
	assert(token);
	token = strtok(NULL, szSpec);//SMPL Title
	assert(token);
	token = strtok(NULL, szSpec);//SMPL
	assert(token);
	WORD wSampleCount =  atoi(token);
	pFileData->stFileHeader.bSMPL[0] = 0xff & (wSampleCount << 8);
	pFileData->stFileHeader.bSMPL[1] = 0xff & (wSampleCount );

	token = strtok(NULL, szSpec);//SENS Title
	assert(token);
	token = strtok(NULL, szSpec);//SENS
	assert(token);
	WORD wSense = atoi(token);
	pFileData->stFileHeader.bSENS[0] = 0xff & (wSense << 8);
	pFileData->stFileHeader.bSENS[1] = 0xff & (wSense);

	token = strtok(NULL, szSpec);//Chop Title
	assert(token);
	token = strtok(NULL, szSpec);//Chop
	assert(token);
	WORD wChopMode = atoi(token);
	pFileData->stFileHeader.bChopMode[0] = 0xff & (wChopMode << 8);
	pFileData->stFileHeader.bChopMode[1] = 0xff & (wChopMode);

	token = strtok(NULL, szSpec);//AverageTime Title
	assert(token);
	token = strtok(NULL, szSpec);//AverageTime
	assert(token);
	WORD wAverageTime = atoi(token);
	pFileData->stFileHeader.bAvgTime[0] = 0xff & (wAverageTime << 8);
	pFileData->stFileHeader.bAvgTime[1] = 0xff & (wAverageTime);

	token = strtok(NULL, szSpec);//REFLEVEL Title
	assert(token);
	token = strtok(NULL, szSpec);//REFLEVEL
	assert(token);
	WORD wRefLevel = atoi(token);
	pFileData->stFileHeader.bREFLEVEL[0] = 0xff & (wRefLevel << 8);
	pFileData->stFileHeader.bREFLEVEL[1] = 0xff & (wRefLevel);

	token = strtok(NULL, szSpec);//Log Scale Title
	assert(token);
	token = strtok(NULL, szSpec);//Log Scale
	assert(token);
	WORD wLogScale = atoi(token);
	pFileData->stFileHeader.bLogScale[0] = 0xff & (wLogScale << 8);
	pFileData->stFileHeader.bLogScale[1] = 0xff & (wLogScale);

	token = strtok(NULL, szSpec);//Result data offset Title
	assert(token);
	token = strtok(NULL, szSpec);//Result data offset
	assert(token);
	WORD wResOffset = atoi(token);
	pFileData->stFileHeader.bResOffset[0] = 0xff & (wResOffset << 8);
	pFileData->stFileHeader.bResOffset[1] = 0xff & (wResOffset);

	token = strtok(NULL, szSpec);//Raw data offset Title
	assert(token);
	token = strtok(NULL, szSpec);//Raw data offset
	assert(token);
	WORD wRawDataOffset = atoi(token);
	pFileData->stFileHeader.bRawOffset[0] = 0xff & (wRawDataOffset << 8);
	pFileData->stFileHeader.bRawOffset[1] = 0xff & (wRawDataOffset);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);
	assert(token);
	token = strtok(NULL, szSpec);//Start WL Title
	assert(token);
	token = strtok(NULL, szSpec);//Start WL
	assert(token);
	DWORD  dwStartWL = atol(token);
	pFileData->stFileHeader.bStartWL[0] = 0xff & (dwStartWL << 24);
	pFileData->stFileHeader.bStartWL[1] = 0xff & (dwStartWL << 16);
	pFileData->stFileHeader.bStartWL[2] = 0xff & (dwStartWL << 8);
	pFileData->stFileHeader.bStartWL[3] = 0xff & (dwStartWL);

	token = strtok(NULL, szSpec);//Stop WL Title
	assert(token);
	token = strtok(NULL, szSpec);//Stop WL
	assert(token);
	DWORD  dwStopWL = atol(token);
	pFileData->stFileHeader.bStopWL[0] = 0xff & (dwStopWL << 24);
	pFileData->stFileHeader.bStopWL[1] = 0xff & (dwStopWL << 16);
	pFileData->stFileHeader.bStopWL[2] = 0xff & (dwStopWL << 8);
	pFileData->stFileHeader.bStopWL[3] = 0xff & (dwStopWL);

	token = strtok(NULL, szSpec);//RES Title
	assert(token);
	token = strtok(NULL, szSpec);//RES
	assert(token);
	WORD  wRes = atoi(token);
	pFileData->stFileHeader.bRESBW[0] = 0xff & (wRes << 8);
	pFileData->stFileHeader.bRESBW[1] = 0xff & (wRes);

	token = strtok(NULL, szSpec);//MEAS WL Title
	assert(token);
	token = strtok(NULL, szSpec);//MEAS WL
	assert(token);
	WORD  wMeas = atoi(token);
	pFileData->stFileHeader.bMEASWL[0] = 0xff & (wMeas << 8);
	pFileData->stFileHeader.bMEASWL[1] = 0xff & (wMeas);

	token = strtok(NULL, szSpec);//Thresh level Title
	assert(token);
	token = strtok(NULL, szSpec);//Thresh level
	assert(token);
	WORD  wThreshlevel = atoi(token);
	pFileData->stFileHeader.bThreshLevel[0] = 0xff & (wThreshlevel << 8);
	pFileData->stFileHeader.bThreshLevel[1] = 0xff & (wThreshlevel);

	token = strtok(NULL, szSpec);//Mode Diff Title
	assert(token);
	token = strtok(NULL, szSpec);//Mode Diff
	assert(token);
	WORD  wModeDiff = atoi(token);
	pFileData->stFileHeader.bModeDiff[0] = 0xff & (wModeDiff << 8);
	pFileData->stFileHeader.bModeDiff[1] = 0xff & (wModeDiff);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);
	assert(token);
	token = strtok(NULL, szSpec);//Offset In Title
	assert(token);
	token = strtok(NULL, szSpec);//Offset In
	assert(token);
	WORD  wOffsetIn = atol(token);
	pFileData->stFileHeader.bOffsetIN[0] = 0xff & (wOffsetIn << 8);
	pFileData->stFileHeader.bOffsetIN[1] = 0xff & (wOffsetIn);

	token = strtok(NULL, szSpec);//Offset Out Title
	assert(token);
	token = strtok(NULL, szSpec);//Offset Out
	assert(token);
	WORD  wOffsetOut = atol(token);
	pFileData->stFileHeader.bOffsetOUT[0] = 0xff & (wOffsetOut << 8);
	pFileData->stFileHeader.bOffsetOUT[1] = 0xff & (wOffsetOut);

	token = strtok(NULL, szSpec);//ASE ALGO Title
	assert(token);
	token = strtok(NULL, szSpec);//ASE ALGO
	assert(token);
	WORD  wASEALGO = atol(token);
	pFileData->stFileHeader.bASEALGO[0] = 0xff & (wASEALGO << 8);
	pFileData->stFileHeader.bASEALGO[1] = 0xff & (wASEALGO);

	token = strtok(NULL, szSpec);//Fitting ALGO Title
	assert(token);
	token = strtok(NULL, szSpec);//Fitting ALGO
	assert(token);
	WORD  wFittingALGO = atol(token);
	pFileData->stFileHeader.bFittingALGO[0] = 0xff & (wFittingALGO << 8);
	pFileData->stFileHeader.bFittingALGO[1] = 0xff & (wFittingALGO);

	token = strtok(NULL, szSpec);//RES BW Title
	assert(token);
	token = strtok(NULL, szSpec);//RES BW
	assert(token);
	WORD  wResBW = atol(token);
	pFileData->stFileHeader.bRESBW[0] = 0xff & (wResBW << 8);
	pFileData->stFileHeader.bRESBW[1] = 0xff & (wResBW);

	token = strtok(NULL, szSpec);//Shot Noise Title
	assert(token);
	token = strtok(NULL, szSpec);//Shot Noise
	assert(token);
	WORD  wShotNoise = atol(token);
	pFileData->stFileHeader.bShotNoise[0] = 0xff & (wShotNoise << 8);
	pFileData->stFileHeader.bShotNoise[1] = 0xff & (wShotNoise);

	token = strtok(NULL, szSpec);//OSNR REQ Title
	assert(token);
	token = strtok(NULL, szSpec);//OSNR REQ
	assert(token);
	WORD  wOSNRREQ = atol(token);
	pFileData->stFileHeader.bOSNRREQ[0] = 0xff & (wOSNRREQ << 8);
	pFileData->stFileHeader.bOSNRREQ[1] = 0xff & (wOSNRREQ);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//OTMS Server ID Title
	assert(token);
	token = strtok(NULL, szSpec);//OTMS Server ID
	assert(token);
	sprintf((char*)pFileData->stFileHeader.bServerID, "%s", token);

	token = strtok(NULL, szSpec);//Client ID Title
	assert(token);
	token = strtok(NULL, szSpec);//Client ID
	assert(token);
	sprintf((char*)pFileData->stFileHeader.bClientID, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//Test Operator Title
	assert(token);
	token = strtok(NULL, szSpec);//Test Operator
	assert(token);
	sprintf((char*)pFileData->stFileHeader.bTestOper, "%s", token);

	token = strtok(NULL, szSpec);//Test Time Title
	assert(token);
	token = strtok(NULL, szSpec);//Test Time
	assert(token);
	sprintf((char*)pFileData->stFileHeader.bTestStamp, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//Server Name Title
	assert(token);
	token = strtok(NULL, szSpec);//Server Name
	assert(token);
	sprintf((char*)pFileData->stFileHeader.bSWName, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//Server Version Title
	assert(token);
	token = strtok(NULL, szSpec);//Server Version
	assert(token);
	sprintf((char*)pFileData->stFileHeader.bSWVer, "%s", token);

	token = strtok(NULL, szSpec);//Server Release Date Title
	assert(token);
	token = strtok(NULL, szSpec);//Server Release Date
	assert(token);
	sprintf((char*)pFileData->stFileHeader.bSWRD, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//Client TP Name Title
	assert(token);
	token = strtok(NULL, szSpec);//Client TP Name
	assert(token);
	sprintf((char*)pFileData->stFileHeader.bClientTPName, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//Client TP Version Title
	assert(token);
	token = strtok(NULL, szSpec);//Client TP Version
	assert(token);
	sprintf((char*)pFileData->stFileHeader.bClientTPVer, "%s", token);

	token = strtok(NULL, szSpec);//Client TP Release Date Title
	assert(token);
	token = strtok(NULL, szSpec);//Client TP Release Date
	assert(token);
	sprintf((char*)pFileData->stFileHeader.bClientTPRD, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//UDL Version Title
	assert(token);
	token = strtok(NULL, szSpec);//UDL Version
	assert(token);
	sprintf((char*)pFileData->stFileHeader.bUDLVer, "%s", token);

	token = strtok(NULL, szSpec);//UDL Release Date Title
	assert(token);
	token = strtok(NULL, szSpec);//UDL Release Date
	assert(token);
	sprintf((char*)pFileData->stFileHeader.bUDLVer, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//OSA Type Title
	assert(token);
	token = strtok(NULL, szSpec);//OSA Type
	assert(token);
	sprintf((char*)pFileData->stFileHeader.bOSAType, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//OSA SN Title
	assert(token);
	token = strtok(NULL, szSpec);//OSA SN
	assert(token);
	sprintf((char*)pFileData->stFileHeader.bOSASN, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//OSA FW VER Title
	assert(token);
	token = strtok(NULL, szSpec);//OSA FW VER
	assert(token);
	sprintf((char*)pFileData->stFileHeader.bOSAFWVer, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//Server OSW Typpe Title
	assert(token);
	token = strtok(NULL, szSpec);//Server OSW Typpe
	assert(token);
	sprintf((char*)pFileData->stFileHeader.bOSWType, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//Server OSW SN Title
	assert(token);
	token = strtok(NULL, szSpec);//Server OSW SN
	assert(token);
	sprintf((char*)pFileData->stFileHeader.bOSWSN, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//Server OSW FW VER Title
	assert(token);
	token = strtok(NULL, szSpec);//Server OSW FW VER
	assert(token);
	sprintf((char*)pFileData->stFileHeader.bOSWFWVer, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//Server OSW Channel Config Title
	assert(token);
	token = strtok(NULL, szSpec);//Server OSW Channel Config
	assert(token);
	sprintf((char*)pFileData->stFileHeader.bOSWChConfig, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//Client OSW Type Title
	assert(token);
	token = strtok(NULL, szSpec);//Client OSW Type
	assert(token);
	sprintf((char*)pFileData->stFileHeader.bClientOSWType, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//Client OSW SN Title
	assert(token);
	token = strtok(NULL, szSpec);//Client OSW SN
	assert(token);
	sprintf((char*)pFileData->stFileHeader.bClientOSWSN, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//Client OSW FW VER Title
	assert(token);
	token = strtok(NULL, szSpec);//Client OSW FW VER
	assert(token);
	sprintf((char*)pFileData->stFileHeader.bClientOSWFWVer, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//Client OSW Channel Config Title
	assert(token);
	token = strtok(NULL, szSpec);//Client OSW Channel Config
	assert(token);
	sprintf((char*)pFileData->stFileHeader.bClientOSWChConfig, "%s", token);


	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//Client OPM Type Title
	assert(token);
	token = strtok(NULL, szSpec);//Client OPM Type
	assert(token);
	sprintf((char*)pFileData->stFileHeader.bClientOPMType, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//Client OPM SN Title
	assert(token);
	token = strtok(NULL, szSpec);//Client OPM SN
	assert(token);
	sprintf((char*)pFileData->stFileHeader.bClientOPMSN, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//Client OPM FW VER
	assert(token);
	token = strtok(NULL, szSpec);//Client OPM FW VER
	assert(token);
	sprintf((char*)pFileData->stFileHeader.bClientOPMFWVer, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile);
	token = strtok(szBuffer, szSpec);//Client OPM Slot
	assert(token);
	token = strtok(NULL, szSpec);//Client OPM Slot
	assert(token);
	sprintf((char*)pFileData->stFileHeader.bClientOPMSlot, "%s", token);

	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile); //.......
	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile); //Resvered
	ZeroMemory(szBuffer, 1024);
	fgets(szBuffer, 1024, fpFile); //标题

	//原始数据
	int nCount = 0;
	while (1)
	{
		ZeroMemory(szBuffer, 1024);
		if (fgets(szBuffer, 1024, fpFile) == NULL)
		{
			break;
		}
		token = strtok(szBuffer, szSpec);
		assert(token);
		pFileData->stRawData.pdblWL[nCount] = atof(token)/1000.0;

		token = strtok(NULL, szSpec);
		assert(token);
		pFileData->stRawData.pdblPower[nCount] = atof(token)/1000.0;

		token = strtok(NULL, szSpec);
		assert(token);
		pFileData->stRawData.pdblRBW[nCount] = atof(token) /1000.0;
		nCount++;
	}
	pFileData->stRawData.nPointCount = nCount;

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////
//函数说明：
//   写ODTM Raw data为CSV文件
//Add by wanxin
//Time:2019/7/16
//////////////////////////////////////////////////////////////////////////
BOOL CCMyDefFileFormat::WriteOTMSRawData2CSV(LPCSTR lpstrCSVFile, stOTMSFileData stFileData)
{
	FILE * fpFile = NULL;
	char szBuffer[1024];
	char szMsg[MAX_PATH];
	DWORD dwDataOffset;

	if ((fpFile = fopen(lpstrCSVFile, "w")) == NULL)
	{
		ZeroMemory(szMsg, MAX_PATH);
		sprintf(szMsg, "Open file:%s error" , lpstrCSVFile);
		return FALSE;
	}
	DWORD dwFileSize = stFileData.stFileHeader.bFileSize[0] << 24;
	dwFileSize += stFileData.stFileHeader.bFileSize[1] << 16;
	dwFileSize += stFileData.stFileHeader.bFileSize[2] << 8;
	dwFileSize += stFileData.stFileHeader.bFileSize[3];

	DWORD dwCRC32  = stFileData.stFileHeader.bCRC32[0] << 24;
	dwCRC32 += stFileData.stFileHeader.bCRC32[1] << 16;
	dwCRC32 += stFileData.stFileHeader.bCRC32[2] << 8;
	dwCRC32 += stFileData.stFileHeader.bCRC32[3];

	sprintf(szBuffer, "0x000000,File Type,%s,File VER,%s,File Size,%d,CRC32,%X", stFileData.stFileHeader.bFileType, stFileData.stFileHeader.bFileSize,
		dwFileSize, dwCRC32);
	fprintf(fpFile, "%s\n", szBuffer);

	WORD wSampleCount = stFileData.stFileHeader.bSMPL[0] << 8;
	wSampleCount += stFileData.stFileHeader.bSMPL[1];
	WORD wSense = stFileData.stFileHeader.bSENS[0]<< 8;
	wSense += stFileData.stFileHeader.bSENS[1];
	WORD wChopMode = stFileData.stFileHeader.bChopMode[0] << 8;
	wChopMode += stFileData.stFileHeader.bChopMode[1];
	WORD wAvgTime = stFileData.stFileHeader.bAvgTime[0] << 8;
	wAvgTime += stFileData.stFileHeader.bAvgTime[1];
	WORD wREFLEVEL = stFileData.stFileHeader.bREFLEVEL[0] << 8;
	wREFLEVEL += stFileData.stFileHeader.bREFLEVEL[1];
	WORD wLogScale = stFileData.stFileHeader.bLogScale[0] << 8;
	wLogScale += stFileData.stFileHeader.bLogScale[1];
	WORD wResultOffset = stFileData.stFileHeader.bResOffset[0] << 8;
	wResultOffset += stFileData.stFileHeader.bResOffset[1];
	WORD wRawDataOffset = stFileData.stFileHeader.bRawOffset[0] << 8;
	wRawDataOffset += stFileData.stFileHeader.bRawOffset[1];
	
	sprintf(szBuffer, "0x000010,SMPL,%d,SENS,%d,Chop Mode,%d,Average times,%d,REF LEVEL,%d,Log Scale,%d,Result data offset,%d,Raw data offset,%d", 
		wSampleCount, wSense, wChopMode, wAvgTime, wREFLEVEL, wLogScale, wResultOffset, wRawDataOffset);
	fprintf(fpFile, "%s\n", szBuffer);

	DWORD dwStartWL = stFileData.stFileHeader.bStartWL[0] << 24;
	dwStartWL += stFileData.stFileHeader.bStartWL[1] << 16;
	dwStartWL += stFileData.stFileHeader.bStartWL[2] << 8;
	dwStartWL += stFileData.stFileHeader.bStartWL[3] ;
	DWORD dwStopWL = stFileData.stFileHeader.bStopWL[0] << 24;
	dwStartWL += stFileData.stFileHeader.bStopWL[1] << 16;
	dwStartWL += stFileData.stFileHeader.bStopWL[2] << 8;
	dwStartWL += stFileData.stFileHeader.bStopWL[3];
	WORD wRES = stFileData.stFileHeader.bRBW[0] << 8;
	wRES += stFileData.stFileHeader.bRBW[1];
	WORD wMEASWL = stFileData.stFileHeader.bMEASWL[0] << 8;
	wMEASWL += stFileData.stFileHeader.bMEASWL[1];
	WORD wTHRESLEVEL = stFileData.stFileHeader.bThreshLevel[0] << 8;
	wTHRESLEVEL += stFileData.stFileHeader.bThreshLevel[1];
	WORD wModeDiff = stFileData.stFileHeader.bModeDiff[0] <<8;
	wModeDiff += stFileData.stFileHeader.bModeDiff[1];

	sprintf(szBuffer, "0x000020,StartWL,%d,StopWL,%d,RES,%d,MEAS,%d,REF LEVEL,%d,THRESH LEVEL,%d,MODE DIFF,%d",
		dwStartWL, dwStopWL, wRES, wMEASWL, wTHRESLEVEL, wModeDiff);
	fprintf(fpFile, "%s\n", szBuffer);

	WORD wOffsetIN = stFileData.stFileHeader.bOffsetIN[0] << 8;
	wOffsetIN += stFileData.stFileHeader.bOffsetIN[1];
	WORD wOffsetOut = stFileData.stFileHeader.bOffsetOUT[0] << 8;
	wOffsetOut += stFileData.stFileHeader.bOffsetOUT[1];
	WORD wASEALGO = stFileData.stFileHeader.bASEALGO[0]<<8;
	wASEALGO += stFileData.stFileHeader.bASEALGO[1];
    WORD wFittingArea = stFileData.stFileHeader.bFittingArea[0] << 8;
	wASEALGO += stFileData.stFileHeader.bFittingArea[1];
	WORD wFittingALGO = stFileData.stFileHeader.bFittingALGO[0] << 8;
	wFittingALGO += stFileData.stFileHeader.bFittingALGO[1];
	WORD wRESBW = stFileData.stFileHeader.bRESBW[0] << 8;
	wRESBW += stFileData.stFileHeader.bRESBW[1];
	WORD wShotNoise = stFileData.stFileHeader.bShotNoise[0] << 8;
	wShotNoise += stFileData.stFileHeader.bShotNoise[1];
	WORD wOSNRREQ = stFileData.stFileHeader.bOSNRREQ[0] << 8;
	wOSNRREQ += stFileData.stFileHeader.bOSNRREQ[1];

	sprintf(szBuffer, "0x000030,Offset(IN),%d,Offset(Out),%d,ASE ALGO,%d,Fitting Area,%d,Fitting ALGO,%d,RES BW,%d,Shot Noise,%d,OSNR REQ,%d",
		wOffsetIN, wOffsetOut, wASEALGO, wFittingArea, wFittingALGO, wRESBW, wShotNoise, wOSNRREQ);
	fprintf(fpFile, "%s\n", szBuffer);

	sprintf(szBuffer, "0x000040,OTDM Server ID:%s,Client ID:%s", stFileData.stFileHeader.bServerID, stFileData.stFileHeader.bClientID);
	fprintf(fpFile, "%s\n", szBuffer);

	sprintf(szBuffer, "0x000050,Test Operator:%s,Test Time Stamp:%s", stFileData.stFileHeader.bTestOper, stFileData.stFileHeader.bTestStamp);
	fprintf(fpFile, "%s\n", szBuffer);

	sprintf(szBuffer, "0x000060,Software Name:%s", stFileData.stFileHeader.bSWName);
	fprintf(fpFile, "%s\n", szBuffer);

	sprintf(szBuffer, "0x000070,Software Version:%s,Software Release Date:%s", stFileData.stFileHeader.bSWVer, stFileData.stFileHeader.bSWRD);
	fprintf(fpFile, "%s\n", szBuffer);

	sprintf(szBuffer, "0x000080,Client TP Name:%s", stFileData.stFileHeader.bClientTPName);
	fprintf(fpFile, "%s\n", szBuffer);
	
	sprintf(szBuffer, "0x000090,Client TP Version:%s,Client TP Release Date:%s", stFileData.stFileHeader.bClientTPVer, stFileData.stFileHeader.bClientTPRD);
	fprintf(fpFile, "%s\n", szBuffer);
	
	sprintf(szBuffer, "0x0000A0,UDL Version:%s,UDL Release Date:%s", stFileData.stFileHeader.bUDLVer, stFileData.stFileHeader.bUDLVer);
	fprintf(fpFile, "%s\n", szBuffer);

	sprintf(szBuffer, "0x0000B0,OSA Type:%s", stFileData.stFileHeader.bOSAType);
	fprintf(fpFile, "%s\n", szBuffer);

	sprintf(szBuffer, "0x0000C0,OSA SN:%s", stFileData.stFileHeader.bOSASN);
	fprintf(fpFile, "%s\n", szBuffer);

	sprintf(szBuffer, "0x000D0,OSA FW VER:%s", stFileData.stFileHeader.bOSAFWVer);
	fprintf(fpFile, "%s\n", szBuffer);

	sprintf(szBuffer, "0x000E0,Server OSW Type:%s", stFileData.stFileHeader.bOSWType);
	fprintf(fpFile, "%s\n", szBuffer);

	sprintf(szBuffer, "0x000F0,Server OSW SN:%s", stFileData.stFileHeader.bOSWSN);
	fprintf(fpFile, "%s\n", szBuffer);

	sprintf(szBuffer, "0x000100,Server OSW FW VER:%s", stFileData.stFileHeader.bOSWFWVer);
	fprintf(fpFile, "%s\n", szBuffer);

	sprintf(szBuffer, "0x000110,Server OSW Channel Config:%s", stFileData.stFileHeader.bOSWChConfig);
	fprintf(fpFile, "%s\n", szBuffer);

	sprintf(szBuffer, "0x000120,Client OSW Type:%s", stFileData.stFileHeader.bClientOSWType);
	fprintf(fpFile, "%s\n", szBuffer);

	sprintf(szBuffer, "0x000130,Client OSW SN:%s", stFileData.stFileHeader.bClientOSWSN);
	fprintf(fpFile, "%s\n", szBuffer);

	sprintf(szBuffer, "0x000140,Client OSW FW VER:%s", stFileData.stFileHeader.bClientOSWFWVer);
	fprintf(fpFile, "%s\n", szBuffer);

	sprintf(szBuffer, "0x000150,Client OSW Channel Config:%s", stFileData.stFileHeader.bClientOSWChConfig);
	fprintf(fpFile, "%s\n", szBuffer);

	sprintf(szBuffer, "0x000160,Client OPM Type:%s", stFileData.stFileHeader.bClientOPMType);
	fprintf(fpFile, "%s\n", szBuffer);

	sprintf(szBuffer, "0x000170,Client OPM SN:%s", stFileData.stFileHeader.bClientOPMSN);
	fprintf(fpFile, "%s\n", szBuffer);

	sprintf(szBuffer, "0x000180,Client OPM FW VER:%s", stFileData.stFileHeader.bClientOPMFWVer);
	fprintf(fpFile, "%s\n", szBuffer);

	sprintf(szBuffer, "0x000190,Client OPM Slot:%s", stFileData.stFileHeader.bClientOPMSlot);
	fprintf(fpFile, "%s\n", szBuffer);

	sprintf(szBuffer, "...,...");
	fprintf(fpFile, "\n");

	sprintf(szBuffer, "0x0001F0,Reserved");
	fprintf(fpFile, "\n");

	//保存Raw 
	stFileData.stRawData.nPointCount = wSampleCount;

	for (int i = 0;i < wSampleCount;i++)
	{

	}

	sprintf(szBuffer, "WL,Power,RBW");
	fprintf(fpFile, "\n");
	//WL
	for (i = 0;i < wSampleCount;i+=4)
	{
		DWORD  dwWL = stFileData.stRawData.pdblWL[i] * 1000;
		DWORD  dwPower = stFileData.stRawData.pdblPower[i] * 1000;
		DWORD  dwRBW = stFileData.stRawData.pdblRBW[i] * 1000;

		sprintf(szBuffer, "%d,%d,%d", dwWL, dwPower, dwRBW);
		fprintf(fpFile, "%s\n", szBuffer);
	}

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////
//函数说明：
//   计算OTMS Raw Data的CRC32校验码
//Add by wanxin
//Time:2019/7/23
///////////////////////////////////////////////////////////////////////////
DWORD CCMyDefFileFormat::CalculateOTMSRawDataCRC32(stOSAScanRawData stData)
{
	DWORD dwCRC32;
	DWORD dwValue=0;
	DWORD * pdwTempArry = NULL;
	int nPointCount = stData.nPointCount;
	int nArryLength = nPointCount * sizeof(DWORD);

	stOSAScanRawBYTEData stbData;
	stbData.nPointCount = stData.nPointCount;
	stbData.bWLArry= (BYTE*)VirtualAlloc(NULL,sizeof(char)*stbData.nPointCount*4,MEM_RESERVE,PAGE_READWRITE);
	stbData.bPowerArry = (BYTE*)VirtualAlloc(NULL, sizeof(char)*stbData.nPointCount * 4, MEM_RESERVE, PAGE_READWRITE);
	stbData.bRBWArry = (BYTE*)VirtualAlloc(NULL, sizeof(char)*stbData.nPointCount * 4, MEM_RESERVE, PAGE_READWRITE);
	int j = 0;
	DWORD dwTempValue;
	for (int i = 0;i < stbData.nPointCount * 4;i += 4)
	{
		dwTempValue = (DWORD)(stData.pdblWL[j] * 1000);
		stbData.bWLArry[i] = 0xff &(dwTempValue >> 24);
		stbData.bWLArry[i+1] = 0xff &(dwTempValue >> 16);
		stbData.bWLArry[i+2] = 0xff &(dwTempValue >> 8);
		stbData.bWLArry[i+3] = 0xff & dwTempValue ;

		dwTempValue = (DWORD)(stData.pdblPower[j] * 1000);
		stbData.bPowerArry[i] = 0xff & (dwTempValue >> 24);
		stbData.bPowerArry[i+1] = 0xff & (dwTempValue >> 16);
		stbData.bPowerArry[i+2] = 0xff & (dwTempValue >> 8);
		stbData.bPowerArry[i+3] = 0xff & dwTempValue;

		dwTempValue = (DWORD)(stData.pdblRBW[j] * 1000);
		stbData.bRBWArry[i] = 0xff & (dwTempValue >> 24);
		stbData.bRBWArry[i+1] = 0xff & (dwTempValue >> 16);
		stbData.bRBWArry[i+2] = 0xff & (dwTempValue >> 8);
		stbData.bRBWArry[i+3] = 0xff & dwTempValue;
	}


	m_opCRC32.InitCRC32();

	for (i = 0;i < nArryLength;i++)
	{
		dwCRC32 = m_opCRC32.GetThisCRC(stbData.bWLArry[i]);
	}

	for (i = 0;i < nArryLength;i++)
	{
		dwCRC32 = m_opCRC32.GetThisCRC(stbData.bPowerArry[i]);
	}

	for (i = 0;i < nArryLength;i++)
	{
		dwCRC32 = m_opCRC32.GetThisCRC(stbData.bRBWArry[i]);
	}

	return dwCRC32;
}

////////////////////////////////////////////////////////////////////////////
//函数说明：
//   write CALF Raw Data的数据
//Add by kemingc
//Time:2019/8/8
///////////////////////////////////////////////////////////////////////////
BOOL CCMyDefFileFormat::WriteCALFFileData2Binary(LPCSTR lpstrFileName, stCALFFileData stFileData)
{
	BOOL bRes = FALSE;
	HANDLE hFile = INVALID_HANDLE_VALUE;
	char szMsg[MAX_PATH];
	BYTE* bWritePtr = NULL;
	DWORD writesize = 0;
	DWORD dwStLength = 0, dwFileLenght = 0;

	try
	{

		hFile = (HANDLE)CreateFile(lpstrFileName, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, NULL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			ZeroMemory(szMsg, MAX_PATH);
			sprintf(szMsg, "Create File:%s error", lpstrFileName);
			throw szMsg;
		}

		//写数据体信息，这里需要将double转换成BYTE
		dwFileLenght = stFileData.bWLCount[0] << 24;
		dwFileLenght += stFileData.bWLCount[1] << 16;
		dwFileLenght += stFileData.bWLCount[2] << 8;
		dwFileLenght += stFileData.bWLCount[3];

		int nRawDataBYTELength = dwFileLenght * 4;//32byte为前面的byte值的大小
		bWritePtr = (BYTE*)VirtualAlloc(NULL, nRawDataBYTELength * 3 + 32, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

		memcpy(&bWritePtr[0], &stFileData.bFileType[0], 4);
		memcpy(&bWritePtr[4], &stFileData.bFileVer[0], 4);
		memcpy(&bWritePtr[8], &stFileData.bFileSize[0], 4);
		memcpy(&bWritePtr[12], &stFileData.bCRC32[0], 4);
		memcpy(&bWritePtr[16], &stFileData.bWLCount[0], 4);
		memcpy(&bWritePtr[20], &stFileData.bOffsetIN[0], 4);
		memcpy(&bWritePtr[24], &stFileData.bOffsetOut[0], 4);
		memcpy(&bWritePtr[28], &stFileData.bReserved[0], 4);

		int j = 0;
		for (int i = 32; i < nRawDataBYTELength + 32; i += 4)
		{
			DWORD dwTempValue = DWORD(stFileData.pdblWL[j] * 1000);
			bWritePtr[i + 0] = 0xff & (dwTempValue >> 24);
			bWritePtr[i + 1] = 0xff & (dwTempValue >> 16);
			bWritePtr[i + 2] = 0xff & (dwTempValue >> 8);
			bWritePtr[i + 3] = 0xff & (dwTempValue);

			int iFlag1Index = nRawDataBYTELength;
			dwTempValue = DWORD(stFileData.pdblInOffset[j] * 1000);
			bWritePtr[iFlag1Index + i + 0] = 0xff & (dwTempValue >> 24);
			bWritePtr[iFlag1Index + i + 1] = 0xff & (dwTempValue >> 16);
			bWritePtr[iFlag1Index + i + 2] = 0xff & (dwTempValue >> 8);
			bWritePtr[iFlag1Index + i + 3] = 0xff & (dwTempValue);

			int iFlag2Index = nRawDataBYTELength * 2;
			dwTempValue = DWORD(stFileData.pdblOutOffset[j] * 1000);
			bWritePtr[iFlag2Index + i + 0] = 0xff & (dwTempValue >> 24);
			bWritePtr[iFlag2Index + i + 1] = 0xff & (dwTempValue >> 16);
			bWritePtr[iFlag2Index + i + 2] = 0xff & (dwTempValue >> 8);
			bWritePtr[iFlag2Index + i + 3] = 0xff & (dwTempValue);
			j++;
		}

		dwStLength = nRawDataBYTELength * 3 + 32;
		writesize = 0;
		if (!WriteFile(hFile, bWritePtr, dwStLength, &writesize, NULL))
		{
			ZeroMemory(szMsg, MAX_PATH);
			sprintf(szMsg, "Write File:%s error", lpstrFileName);
			throw szMsg;
		}

		bRes = TRUE;
	}
	catch (char *pszErr)
	{
		//m_strErrMsg = pszErr;
	}

	if (hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFile);
		hFile = INVALID_HANDLE_VALUE;
	}

	if (NULL != bWritePtr)
	{
		VirtualFree(bWritePtr, 0, MEM_RELEASE);
		bWritePtr = NULL;
	}

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////
//函数说明：
//   read CALF Raw Data的数据
//Add by kemingc
//Time:2019/8/8
///////////////////////////////////////////////////////////////////////////
BOOL CCMyDefFileFormat::ReadCALFFileDataFromBinFile(LPCSTR lpstrFileName, pCALFFileData pData)
{

	BOOL bRes = FALSE;
	HANDLE hFile = INVALID_HANDLE_VALUE;
	char szMsg[MAX_PATH];
	BYTE* bReadPtr = NULL;
	DWORD dwSampleCount = 0, dwReadLength = 0, readsize = 0;

	try
	{

		hFile = (HANDLE)CreateFile(lpstrFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		if (hFile == INVALID_HANDLE_VALUE)
		{
			ZeroMemory(szMsg, MAX_PATH);
			sprintf(szMsg, "Create File:%s error", lpstrFileName);
			throw szMsg;
		}

		dwReadLength = sizeof(*pData);
		dwReadLength -= 12;
		readsize = 0;

		bReadPtr = (BYTE*)VirtualAlloc(NULL, dwReadLength, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
		//bReadPtr = (BYTE*)&stData.bWLArry[0];
		if (!ReadFile(hFile, bReadPtr, dwReadLength, &readsize, NULL))
		{
			ZeroMemory(szMsg, MAX_PATH);
			sprintf(szMsg, "Read File:%s error", lpstrFileName);
			throw szMsg;
		}

		dwSampleCount = bReadPtr[16] << 24;
		dwSampleCount += bReadPtr[17] << 16;
		dwSampleCount += bReadPtr[18] << 8;
		dwSampleCount += bReadPtr[19];

		memcpy(&pData->bWLCount, &bReadPtr[16], 4);
		//	memcpy(&pData->bFileType, &bReadPtr[0], 4);

		bReadPtr = (BYTE*)VirtualAlloc(NULL, dwSampleCount * 4 * 3, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
		dwReadLength = dwSampleCount * 4 * 3;

		if (!ReadFile(hFile, bReadPtr, dwReadLength, &readsize, NULL))
		{
			ZeroMemory(szMsg, MAX_PATH);
			sprintf(szMsg, "Read File:%s error", lpstrFileName);
			throw szMsg;
		}
		if (hFile != INVALID_HANDLE_VALUE)
		{
			CloseHandle(hFile);
			hFile = INVALID_HANDLE_VALUE;
		}

		int j = 0;
		DWORD dwTempValue;
		for (int i = 0; i < dwSampleCount * 4; i += 4)
		{
			dwTempValue = bReadPtr[i] << 24;
			dwTempValue += bReadPtr[i + 1] << 16;
			dwTempValue += bReadPtr[i + 2] << 8;
			dwTempValue += bReadPtr[i + 3];
			pData->pdblWL[j] = (double)dwTempValue / 1000.0;

			int iFlag1Index = dwSampleCount * 4;
			dwTempValue = bReadPtr[iFlag1Index + i] << 24;
			dwTempValue += bReadPtr[iFlag1Index + i + 1] << 16;
			dwTempValue += bReadPtr[iFlag1Index + i + 2] << 8;
			dwTempValue += bReadPtr[iFlag1Index + i + 3];
			pData->pdblInOffset[j] = (double)(*((long*)&dwTempValue)) / 1000.0;

			int iFlag2Index = dwSampleCount * 4 * 2;
			dwTempValue = bReadPtr[iFlag2Index + i] << 24;
			dwTempValue += bReadPtr[iFlag2Index + i + 1] << 16;
			dwTempValue += bReadPtr[iFlag2Index + i + 2] << 8;
			dwTempValue += bReadPtr[iFlag2Index + i + 3];
			pData->pdblOutOffset[j] = (double)(*((long*)&dwTempValue)) / 1000.0;
			j++;
		}

		bRes = TRUE;
	}
	catch (char *pszErr)
	{
		//m_strErrMsg = pszErr;
	}

	if (NULL != bReadPtr)
	{
		VirtualFree(bReadPtr, 0, MEM_RELEASE);
		bReadPtr = NULL;
	}

	return TRUE;
}


////////////////////////////////////////////////////////////////////////////
//函数说明：
//   write OACF Raw Data的数据
//Add by kemingc
//Time:2019/8/8
///////////////////////////////////////////////////////////////////////////
BOOL CCMyDefFileFormat::WriteOACFFileData2Binary(LPCSTR lpstrFileName, stOACFFileData stFileData)
{
	BOOL bRes = FALSE;
	HANDLE hFile = INVALID_HANDLE_VALUE;
	char szMsg[MAX_PATH];
	BYTE* bWritePtr = NULL;
	DWORD writesize = 0;
	DWORD dwStLength = 0, dwFileLenght = 0;

	try
	{

		hFile = (HANDLE)CreateFile(lpstrFileName, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, NULL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			ZeroMemory(szMsg, MAX_PATH);
			sprintf(szMsg, "Create File:%s error", lpstrFileName);
			throw szMsg;
		}

		//写数据体信息，这里需要将double转换成BYTE
		dwFileLenght = stFileData.bWLCount[0] << 24;
		dwFileLenght += stFileData.bWLCount[1] << 16;
		dwFileLenght += stFileData.bWLCount[2] << 8;
		dwFileLenght += stFileData.bWLCount[3];

		int nRawDataBYTELength = dwFileLenght * 4;//32byte为前面的byte值的大小

		bWritePtr = (BYTE*)VirtualAlloc(NULL, nRawDataBYTELength * 3 + 32, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

		memcpy(&bWritePtr[0], &stFileData.bFileType[0], 4);
		memcpy(&bWritePtr[4], &stFileData.bFileVer[0], 4);
		memcpy(&bWritePtr[8], &stFileData.bFileSize[0], 4);
		memcpy(&bWritePtr[12], &stFileData.bCRC32[0], 4);
		memcpy(&bWritePtr[16], &stFileData.bWLCount[0], 4);
		memcpy(&bWritePtr[20], &stFileData.bReserved[0], 12);

		int j = 0;
		for (int i = 32; i < nRawDataBYTELength + 32; i += 4)
		{
			DWORD dwTempValue = DWORD(stFileData.pdblWL[j] * 1000);
			bWritePtr[i + 0] = 0xff & (dwTempValue >> 24);
			bWritePtr[i + 1] = 0xff & (dwTempValue >> 16);
			bWritePtr[i + 2] = 0xff & (dwTempValue >> 8);
			bWritePtr[i + 3] = 0xff & (dwTempValue);

			int iFlag1Index = nRawDataBYTELength;
			dwTempValue = DWORD(stFileData.pdbASELeftOffset[j] * 1000);
			bWritePtr[iFlag1Index + i + 0] = 0xff & (dwTempValue >> 24);
			bWritePtr[iFlag1Index + i + 1] = 0xff & (dwTempValue >> 16);
			bWritePtr[iFlag1Index + i + 2] = 0xff & (dwTempValue >> 8);
			bWritePtr[iFlag1Index + i + 3] = 0xff & (dwTempValue);

			int iFlag2Index = nRawDataBYTELength * 2;
			dwTempValue = DWORD(stFileData.pdblASERightOffset[j] * 1000);
			bWritePtr[iFlag2Index + i + 0] = 0xff & (dwTempValue >> 24);
			bWritePtr[iFlag2Index + i + 1] = 0xff & (dwTempValue >> 16);
			bWritePtr[iFlag2Index + i + 2] = 0xff & (dwTempValue >> 8);
			bWritePtr[iFlag2Index + i + 3] = 0xff & (dwTempValue);
			j++;
		}

		dwStLength = nRawDataBYTELength * 3 + 32;
		writesize = 0;
		if (!WriteFile(hFile, bWritePtr, dwStLength, &writesize, NULL))
		{
			ZeroMemory(szMsg, MAX_PATH);
			sprintf(szMsg, "Write File:%s error", lpstrFileName);
			throw szMsg;
		}

		bRes = TRUE;
	}
	catch (char *pszErr)
	{
		//m_strErrMsg = pszErr;
	}

	if (hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFile);
		hFile = INVALID_HANDLE_VALUE;
	}

	if (NULL != bWritePtr)
	{
		VirtualFree(bWritePtr, 0, MEM_RELEASE);
		bWritePtr = NULL;
	}

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////
//函数说明：
//   read OACF Raw Data的数据
//Add by kemingc
//Time:2019/8/8
///////////////////////////////////////////////////////////////////////////
BOOL CCMyDefFileFormat::ReadOACFFileDataFromBinFile(LPCSTR lpstrFileName, pOACFFileData pData)
{
	BOOL bRes = FALSE;
	HANDLE hFile = INVALID_HANDLE_VALUE;
	char szMsg[MAX_PATH];
	BYTE* bReadPtr = NULL;
	DWORD dwSampleCount = 0, dwReadLength = 0, readsize = 0;

	try
	{
		hFile = (HANDLE)CreateFile(lpstrFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		if (hFile == INVALID_HANDLE_VALUE)
		{
			ZeroMemory(szMsg, MAX_PATH);
			sprintf(szMsg, "Create File:%s error", lpstrFileName);
			throw szMsg;
		}

		dwReadLength = sizeof(*pData);
		dwReadLength -= 12;
		readsize = 0;

		bReadPtr = (BYTE*)VirtualAlloc(NULL, dwReadLength, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
		//bReadPtr = (BYTE*)&stData.bWLArry[0];
		if (!ReadFile(hFile, bReadPtr, dwReadLength, &readsize, NULL))
		{
			ZeroMemory(szMsg, MAX_PATH);
			sprintf(szMsg, "Read File:%s error", lpstrFileName);
			throw szMsg;
		}

		dwSampleCount = bReadPtr[16] << 24;
		dwSampleCount += bReadPtr[17] << 16;
		dwSampleCount += bReadPtr[18] << 8;
		dwSampleCount += bReadPtr[19];
		memcpy(&pData->bWLCount, &bReadPtr[16], 4);

		bReadPtr = (BYTE*)VirtualAlloc(NULL, dwSampleCount * 4 * 3, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
		dwReadLength = dwSampleCount * 4 * 3;

		bReadPtr = (BYTE*)VirtualAlloc(NULL, dwReadLength, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
		//bReadPtr = (BYTE*)&stData.bWLArry[0];
		if (!ReadFile(hFile, bReadPtr, dwReadLength, &readsize, NULL))
		{
			ZeroMemory(szMsg, MAX_PATH);
			sprintf(szMsg, "Read File:%s error", lpstrFileName);
			throw szMsg;
		}

		if (hFile != INVALID_HANDLE_VALUE)
		{
			CloseHandle(hFile);
			hFile = INVALID_HANDLE_VALUE;
		}

		int j = 0;
		DWORD dwTempValue;

		for (int i = 0; i < dwSampleCount * 4; i += 4)
		{
			dwTempValue = bReadPtr[i] << 24;
			dwTempValue += bReadPtr[i + 1] << 16;
			dwTempValue += bReadPtr[i + 2] << 8;
			dwTempValue += bReadPtr[i + 3];
			pData->pdblWL[j] = (double)dwTempValue / 1000.0;

			int iFlag1Index = dwSampleCount * 4;
			dwTempValue = bReadPtr[iFlag1Index + i] << 24;
			dwTempValue += bReadPtr[iFlag1Index + i + 1] << 16;
			dwTempValue += bReadPtr[iFlag1Index + i + 2] << 8;
			dwTempValue += bReadPtr[iFlag1Index + i + 3];
			pData->pdbASELeftOffset[j] = (double)(*((long*)&dwTempValue)) / 1000.0;

			int iFlag2Index = dwSampleCount * 4 * 2;
			dwTempValue = bReadPtr[iFlag2Index + i] << 24;
			dwTempValue += bReadPtr[iFlag2Index + i + 1] << 16;
			dwTempValue += bReadPtr[iFlag2Index + i + 2] << 8;
			dwTempValue += bReadPtr[iFlag2Index + i + 3];
			pData->pdblASERightOffset[j] = (double)(*((long*)&dwTempValue)) / 1000.0;
			j++;
		}

		bRes = TRUE;
	}
	catch (char *pszErr)
	{
		//m_strErrMsg = pszErr;
	}

	if (NULL != bReadPtr)
	{
		VirtualFree(bReadPtr, 0, MEM_RELEASE);
		bReadPtr = NULL;
	}

	return TRUE;
}

void CCMyDefFileFormat::RealseAllocOSAScanRawData(stOSAScanRawData stData)
{
	if (stData.pdblWL != NULL)
	{
		VirtualFree(stData.pdblWL, 0, MEM_RELEASE);
		stData.pdblWL = NULL;
	}
	if (stData.pdblPower != NULL)
	{
		VirtualFree(stData.pdblPower, 0, MEM_RELEASE);
		stData.pdblPower = NULL;
	}
	if (stData.pdblRBW != NULL)
	{
		VirtualFree(stData.pdblRBW, 0, MEM_RELEASE);
		stData.pdblRBW = NULL;
	}
}