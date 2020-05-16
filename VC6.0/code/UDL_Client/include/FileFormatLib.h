#pragma once
#ifndef __FILEFORMAT__H
#define __FILEFORMAT__H


#define FILE_NAME_SRC "SRCF.bin"
#define FILE_NAME_AMP "AMPF.bin"
#define FILE_NAME_CALF "CALF.bin"
#define FILE_NAME_OACF "OACF.bin"
//Scan Raw Data

typedef struct tagScanRawData
{
	int nPointCount;
	double * pdblWL;
	double * pdblPower;
	double * pdblRBW;
}stOSAScanRawData,*pOSAScanRawData;

typedef struct tagScanRawBYTEData
{
	int  nPointCount;
	BYTE*  bWLArry;             //波长 WL1 - WLn，4字节，数值=波长*1000
	BYTE*  bPowerArry;          //功率 P1 - Pn，4字节，数值=功率*1000
	BYTE*  bRBWArry;            //RBW RBW1 - RBWn，4字节，数值=RBW*1000
}stOSAScanRawBYTEData, *pOSAScanRawBYTEData;

//OTMS file header
typedef struct tagOTMSFileHeader
{
	BYTE bFileType[4];           //文件类型
	BYTE bFileVer[4];            //文件版本
	BYTE bFileSize[4];         //文件长度,整个文件长度包括头部
	BYTE bCRC32[4];              //CRC32校验，不包含头部
	BYTE bSMPL[2];               //扫描点数
	BYTE bSENS[2];               //OSA探测sensitive选择 1-Normal,2-MID,3-H1,4-H2,5-H3
	BYTE bChopMode[2];           //0-OFF,1-ON
	BYTE bAvgTime[2];            //默认1
	BYTE bREFLEVEL[2];           //REF设置，0-Auto,1-Manual
	BYTE bLogScale[2];           //Log Scale x.x 默认10.0dB x 10
	BYTE bResOffset[2];          //测试结果数据偏移量
	BYTE bRawOffset[2];          //有效数据偏移量
	BYTE bStartWL[4];            //起始波长 x 1000
	BYTE bStopWL[4];             //终止波长 x 1000
	BYTE bRBW[2];                //RBW设定值 x 100
	BYTE bMEASWL[2];             //0-AIR,1-VACUUM
	BYTE bThreshLevel[2];        //波长区分阈值，默认20dB
	BYTE bModeDiff[2];           //默认3dB
	BYTE bOffsetIN[2];           //源总功率Offset x 100
	BYTE bOffsetOUT[2];          //放大总功率Offset x 100
	BYTE bASEALGO[2];            //0-AutoFix,1-Manual Fix,2-Auto CIR,3-Manual CIR,默认1
	BYTE bFittingArea[2];        // >=200G 0.6nm，<100G 0.4nm
	BYTE bFittingALGO[2];        //ASE插值方式,0-LINEAR,1-GAUSS,2-LORENZ,3-3RD POLY,4-4TH POLY,5-5TH POLY,默认值0
	BYTE bRESBW[2];              //0-Measured，1-Cal Data
	BYTE bShotNoise[2];          //0-OFF,1-ON
	BYTE bOSNRREQ[2];            //光源最低OSNR要求，用来卡多波光源是否OK
								 ////////////64 byte///////////////////////////////////
	BYTE bServerID[8];           //OTDM Server ID
	BYTE bClientID[8];           //Client ID
	BYTE bTestOper[8];           //操作员工号
	BYTE bTestStamp[8];          //操作时间戳
	BYTE bSWName[16];            //软件名称
	BYTE bSWVer[8];              //软件版本
	BYTE bSWRD[8];               //软件发布日期
								 ////////////64 byte////////////////////////////////////
	BYTE bClientTPName[16];      //Client TP Name
	BYTE bClientTPVer[8];        //Client TP Version
	BYTE bClientTPRD[8];         //Client TP Release Date
	BYTE bUDLVer[8];             //UDL Version
	BYTE bUDLRD[8];              //UDL Release Date
	BYTE bOSAType[16];           //OSA类型
								 ////////////64 byte///////////////////////////////////
	BYTE bOSASN[16];             //OSA SerialNumber
	BYTE bOSAFWVer[16];          //OSA FW版本
	BYTE bOSWType[16];            //光开关类型
	BYTE bOSWSN[16];              //光开关SerialNumber
								  ////////////64 byte//////////////////////////////////
	BYTE bOSWFWVer[16];           //光开关FW版本
	BYTE bOSWChConfig[16];        //光开关通道配置  
	BYTE bClientOSWType[16];      //Client OSW Type
	BYTE bClientOSWSN[16];        //Client OSW SN
								  ////////////64 byte/////////////////////////////////
	BYTE bClientOSWFWVer[16];     //Client OSW FW Version
	BYTE bClientOSWChConfig[16];  //Client OSW Channel Config
	BYTE bClientOPMType[16];      //Client OPM Type
	BYTE bClientOPMSN[16];        //Client OPM SN
								  ////////////64 byte////////////////////////////////
	BYTE bClientOPMFWVer[16];     //Client OPM FW Version
	BYTE bClientOPMSlot[16];      //Client OPM Slot
	BYTE bResvered[96];          //保留字节全部填写0x00
}stOTMSFileHeader, *pOTMSFileHeader;

//OTMS file 
typedef struct tagOTMSFileData
{
	stOTMSFileHeader stFileHeader;       //File Header
	stOSAScanRawData    stRawData;          //Scan Raw data
}stOTMSFileData, *pOTMSFileData;

typedef struct tagCALFFileData
{
	BYTE bFileType[4];           //文件类型
	BYTE bFileVer[4];            //文件版本
	BYTE bFileSize[4];           //文件长度,整个文件长度包括头部
	BYTE bCRC32[4];              //CRC32校验，不包含头部
	BYTE bWLCount[4];			 //波长数
	BYTE bOffsetIN[4];			 //In OFFSET
	BYTE bOffsetOut[4];			 //Out OFFSET
	BYTE bReserved[4];			 //保留位
	double *pdblWL;				 //具体波长数据
	double *pdblInOffset;        //具体IN OFFSET
	double *pdblOutOffset;       //具体Out OFFSET

}stCALFFileData, *pCALFFileData;

//OACF file 
typedef struct tagOACFFileData
{
	BYTE bFileType[4];           //文件类型
	BYTE bFileVer[4];            //文件版本
	BYTE bFileSize[4];           //文件长度,整个文件长度包括头部
	BYTE bCRC32[4];              //CRC32校验，不包含头部
	BYTE bWLCount[4];			 //波长数
	BYTE bReserved[12];			 //保留位
	double *pdblWL;				 //具体波长数据
	double *pdbASELeftOffset;    //具体ASE OFFSET
	double *pdblASERightOffset;  //具体ASE OFFSET

}stOACFFileData, *pOACFFileData;


typedef BOOL(*WriteOTMSBinFile)(LPCSTR lpstrFileName, stOTMSFileData stFileData);
typedef BOOL(*ReadOTMSBinFile)(LPCSTR lpstrFileName, pOTMSFileData pData);
typedef BOOL(*ReadOTMSBinHeader)(LPCSTR lpstrBinFile, pOTMSFileHeader pFileHeader);
typedef BOOL(*ReadOTMSBinRawData)(LPCSTR lpstrBinFile, stOSAScanRawData pRawData);
typedef BOOL(*OTMSBin2CSV)(LPCSTR lpstrBinFile, LPCSTR lpstrCSVFile);
typedef BOOL(*OTMSCSV2Bin)(LPCSTR lpstrCSVFile, LPCSTR lpstrBinFile);
typedef BOOL(*WriteOTMSCSVFile)(LPCSTR lpstrCSVFile, stOTMSFileData stFileData);
typedef BOOL(*ReadOTMSCSVHeader)(LPCSTR lpstrCSVFile, pOTMSFileHeader pFileHeader);
typedef BOOL(*ReadOTMSCSVRawData)(LPCSTR lpstrCSVFile, pOTMSFileData pFileData);
typedef DWORD(*CalcOTMSRawDataCRC32)(stOSAScanRawData stData);




#endif // !__FILEFORMAT__H



