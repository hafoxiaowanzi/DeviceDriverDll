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
	BYTE*  bWLArry;             //���� WL1 - WLn��4�ֽڣ���ֵ=����*1000
	BYTE*  bPowerArry;          //���� P1 - Pn��4�ֽڣ���ֵ=����*1000
	BYTE*  bRBWArry;            //RBW RBW1 - RBWn��4�ֽڣ���ֵ=RBW*1000
}stOSAScanRawBYTEData, *pOSAScanRawBYTEData;

//OTMS file header
typedef struct tagOTMSFileHeader
{
	BYTE bFileType[4];           //�ļ�����
	BYTE bFileVer[4];            //�ļ��汾
	BYTE bFileSize[4];         //�ļ�����,�����ļ����Ȱ���ͷ��
	BYTE bCRC32[4];              //CRC32У�飬������ͷ��
	BYTE bSMPL[2];               //ɨ�����
	BYTE bSENS[2];               //OSA̽��sensitiveѡ�� 1-Normal,2-MID,3-H1,4-H2,5-H3
	BYTE bChopMode[2];           //0-OFF,1-ON
	BYTE bAvgTime[2];            //Ĭ��1
	BYTE bREFLEVEL[2];           //REF���ã�0-Auto,1-Manual
	BYTE bLogScale[2];           //Log Scale x.x Ĭ��10.0dB x 10
	BYTE bResOffset[2];          //���Խ������ƫ����
	BYTE bRawOffset[2];          //��Ч����ƫ����
	BYTE bStartWL[4];            //��ʼ���� x 1000
	BYTE bStopWL[4];             //��ֹ���� x 1000
	BYTE bRBW[2];                //RBW�趨ֵ x 100
	BYTE bMEASWL[2];             //0-AIR,1-VACUUM
	BYTE bThreshLevel[2];        //����������ֵ��Ĭ��20dB
	BYTE bModeDiff[2];           //Ĭ��3dB
	BYTE bOffsetIN[2];           //Դ�ܹ���Offset x 100
	BYTE bOffsetOUT[2];          //�Ŵ��ܹ���Offset x 100
	BYTE bASEALGO[2];            //0-AutoFix,1-Manual Fix,2-Auto CIR,3-Manual CIR,Ĭ��1
	BYTE bFittingArea[2];        // >=200G 0.6nm��<100G 0.4nm
	BYTE bFittingALGO[2];        //ASE��ֵ��ʽ,0-LINEAR,1-GAUSS,2-LORENZ,3-3RD POLY,4-4TH POLY,5-5TH POLY,Ĭ��ֵ0
	BYTE bRESBW[2];              //0-Measured��1-Cal Data
	BYTE bShotNoise[2];          //0-OFF,1-ON
	BYTE bOSNRREQ[2];            //��Դ���OSNRҪ���������ನ��Դ�Ƿ�OK
								 ////////////64 byte///////////////////////////////////
	BYTE bServerID[8];           //OTDM Server ID
	BYTE bClientID[8];           //Client ID
	BYTE bTestOper[8];           //����Ա����
	BYTE bTestStamp[8];          //����ʱ���
	BYTE bSWName[16];            //�������
	BYTE bSWVer[8];              //����汾
	BYTE bSWRD[8];               //�����������
								 ////////////64 byte////////////////////////////////////
	BYTE bClientTPName[16];      //Client TP Name
	BYTE bClientTPVer[8];        //Client TP Version
	BYTE bClientTPRD[8];         //Client TP Release Date
	BYTE bUDLVer[8];             //UDL Version
	BYTE bUDLRD[8];              //UDL Release Date
	BYTE bOSAType[16];           //OSA����
								 ////////////64 byte///////////////////////////////////
	BYTE bOSASN[16];             //OSA SerialNumber
	BYTE bOSAFWVer[16];          //OSA FW�汾
	BYTE bOSWType[16];            //�⿪������
	BYTE bOSWSN[16];              //�⿪��SerialNumber
								  ////////////64 byte//////////////////////////////////
	BYTE bOSWFWVer[16];           //�⿪��FW�汾
	BYTE bOSWChConfig[16];        //�⿪��ͨ������  
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
	BYTE bResvered[96];          //�����ֽ�ȫ����д0x00
}stOTMSFileHeader, *pOTMSFileHeader;

//OTMS file 
typedef struct tagOTMSFileData
{
	stOTMSFileHeader stFileHeader;       //File Header
	stOSAScanRawData    stRawData;          //Scan Raw data
}stOTMSFileData, *pOTMSFileData;

typedef struct tagCALFFileData
{
	BYTE bFileType[4];           //�ļ�����
	BYTE bFileVer[4];            //�ļ��汾
	BYTE bFileSize[4];           //�ļ�����,�����ļ����Ȱ���ͷ��
	BYTE bCRC32[4];              //CRC32У�飬������ͷ��
	BYTE bWLCount[4];			 //������
	BYTE bOffsetIN[4];			 //In OFFSET
	BYTE bOffsetOut[4];			 //Out OFFSET
	BYTE bReserved[4];			 //����λ
	double *pdblWL;				 //���岨������
	double *pdblInOffset;        //����IN OFFSET
	double *pdblOutOffset;       //����Out OFFSET

}stCALFFileData, *pCALFFileData;

//OACF file 
typedef struct tagOACFFileData
{
	BYTE bFileType[4];           //�ļ�����
	BYTE bFileVer[4];            //�ļ��汾
	BYTE bFileSize[4];           //�ļ�����,�����ļ����Ȱ���ͷ��
	BYTE bCRC32[4];              //CRC32У�飬������ͷ��
	BYTE bWLCount[4];			 //������
	BYTE bReserved[12];			 //����λ
	double *pdblWL;				 //���岨������
	double *pdbASELeftOffset;    //����ASE OFFSET
	double *pdblASERightOffset;  //����ASE OFFSET

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



