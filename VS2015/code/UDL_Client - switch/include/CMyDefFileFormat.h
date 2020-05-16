#pragma once

#include "OpCRC32.h"
#include "FileFormatLib.h"
#include "NFlib.h"

#define  OTDMBINFILEHEADERLENGTH 0x000200

class CCMyDefFileFormat
{
public:
	CCMyDefFileFormat();
	virtual ~CCMyDefFileFormat();

	BOOL WriteOTMSFileData2Binary(LPCSTR lpstrFileName, stOTMSFileData stFileData);
	BOOL ReadOTMSFileDataFromBinFile(LPCSTR lpstrFileName, pOTMSFileData pData);
	BOOL ReadOTMSBinFileHeader(LPCSTR lpstrBinFile, pOTMSFileHeader pFileHeader);
	BOOL ReadOTMSBinRawData(LPCSTR lpstrBinFile, pOSAScanRawData pRawData);
	BOOL ConvertOTMSFileBin2CSV(LPCSTR lpstrBinFile, LPCSTR lpstrCSVFile);
	BOOL ConvertOTMSFileCSV2Bin(LPCSTR lpstrCSVFile,LPCSTR lpstrBinFile);
	BOOL WriteOTMSRawData2CSV(LPCSTR lpstrCSVFile, stOTMSFileData stFileData);
	BOOL ReadOTMSCSVFileHeader(LPCSTR lpstrCSVFile, pOTMSFileHeader pFileHeader);
	BOOL ReadOTMSCSVFileData(LPCSTR lpstrCSVFile, pOTMSFileData pFileData);
	DWORD CalculateOTMSRawDataCRC32(stOSAScanRawData stData);

	BOOL WriteCALFFileData2Binary(LPCSTR lpstrFileName, stCALFFileData stFileData);
	BOOL ReadCALFFileDataFromBinFile(LPCSTR lpstrFileName, pCALFFileData pData);

	BOOL WriteOACFFileData2Binary(LPCSTR lpstrFileName, stOACFFileData stFileData);
	BOOL ReadOACFFileDataFromBinFile(LPCSTR lpstrFileName, pOACFFileData pData);

	void RealseAllocOSAScanRawData(stOSAScanRawData stData);
	BOOL GetOSAFile(pOTMSFileData pstData, LPCSTR strFolderName, stScanSetting	&stScanSetting);
	BOOL SetOSAFile(stOTMSFileData stData, LPCSTR strFolderName, stScanSetting stScanSetting, int iSweepPoints);
	void DoubleToByte(double dblValue, BYTE *pbyValue, BYTE byLenght);
	void ByteTODouble(BYTE *pbyValue, double *pdblValue, BYTE byLenght);
	BOOL FindFolder(LPCSTR strFolderPath);
public:
	COpCRC32  m_opCRC32;
	stOTMSFileData  m_stFileInfo;
};


