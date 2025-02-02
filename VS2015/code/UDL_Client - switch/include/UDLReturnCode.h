#ifndef UDL_RETURN_CODE_HEADER
#define UDL_RETURN_CODE_HEADER

#define DATA_TYPE_TRACE "TRACE"
#define DATA_TYPE_ALLTRACE "ATRACE"
#define DATA_TYPE_GRAPHICS "GRAPHICS"
#define DATA_TYPE_DATA "DATA"

#define FILE_TYPE_BMP "BMP"
#define FILE_TYPE_CSV "CSV"

// Define a structure for bit-wise access
typedef struct tagDeviceType
{
	BYTE     bType;         /* Mainframe Type */
	BYTE     bNum;         /* Mainframe Serial Number*/
}stDevType, *pstDevType;

typedef struct tagModule
{
	BYTE     bSlot;         /* Mainframe slot number */
	BYTE     bChan;         /* Slot channel */
}stModule, *pstModule;

typedef struct tagDeviceInformation
{
	char pszName[256];
	char pszSerialNum[256];
	char pszFWVer[256];
	char pszHWVer[256];
	char pszMFDate[256];
}stDevInfo, *pstDevInfo;

typedef union tagDevCfg
{
	DWORD          dwDeviceCfg;
	stDevType      Mainframe;
	stModule       Module;
}DEVCFG;

#define SUCCESS 0

#define UNEXPECT_OCCUR				0x000000FF
#define ERROR_VALUE			        0xFFFFFFFF

//Device type

enum PMDEVICEERROR
{
	ERROR_PM = 0x20000000,
	ERROR_AVERIAGE_TIME,
	ERROR_PW,
	ERROR_UNIT,
	ERROR_PMOFFSET,
};

enum VOADEVICEERROR
{
	ERROR_VOA = 0x30000000,
	ERROR_ATTEN,
	ERROR_ENABLE,
	ERROR_DISENABLE,
	ERROR_ATTEN_OFFSET,
	ERROR_STATUS,
	ERROR_INFO,
};

enum TLSDEVICEERROR
{
	ERROR_TLS = 0x40000000,
	ERROR_WL,
	ERROR_COHERENCE_CONTROL,
	ERROR_SRC_POW,

};
enum POCDEVICEERROR
{
	ERROR_PDLD = 0x50000000,
	ERROR_PDL_GETPOS,
	ERROR_PDL_SETANGLE,
	ERROR_PDL_STEP,
	ERROR_NOT_DOSCAN,
	ERROR_OUT_RANGE,

};
enum CHAMBERDEVICEERROR
{
	ERROR_CHAMBER = 0x60000000,
	ERROR_CHAMBER_RUNSTOP,
	ERROR_CHAMBER_RUNSTART,
	ERROR_CHAMBER_SETTEMP,
	ERROR_CHAMBER_GETSETTEMP,
	ERROR_CHAMBER_GETCURRENTTEMP,

};
enum OSADEVICEERROR
{
	ERROR_OSA = 0x10000000,
	ERROR_OSAGETASE,
	ERROR_OSAINITAMPMODE0,
	ERROR_OSAINITAMPMODE1,
	ERROR_OSAINITAMPMODE2,
	ERROR_OSAMEARSOUREMODE0,
	ERROR_OSAMEARSOUREMODE1,
	ERROR_OSAMEARSOUREMODE2,
	EEROR_OSASETAMPFILEPATH,
	EEROR_OSAGETAMPFILEPATH,
	ERROR_OSAMEARAMPMODE0,
	ERROR_OSAMEARAMPMODE1,
	ERROR_OSAMEARAMPMODE2,
	ERROR_OSAGETCHRBW,
	ERROR_OSASRCFILE,
	ERROR_OSAAMPCFILE,
	ERROR_RBW,
	ERROR_RESET,
	ERROR_ANALYSIS,
	ERROR_PW_OFFSET,
	ERROR_WL_COUNT,
	ERROR_NF,
	ERROR_GAIN,
	ERROR_SNR,
	ERROR_SRC_PW_OFFSET,
	ERROR_AMP_PW_OFFSET,
	ERROR_WL_OFFSET,
	ERROR_CH_WL_OFFSET,
	ERROR_CH_PW_OFFSET,
	ERROR_SENS,
	ERROR_SWEEP_DATA,
	ERROR_SWEEP_MODE,
	ERROR_INITIAL,
	ERROR_LOCAL_CONTROL,
	ERROR_SWEEP,
	ERROR_WROK_MODE,
	ERROR_ADDRESS,
	ERROR_TRACE,
	ERROR_TRACE_ATTRIBUTE,
	ERROR_SAVE_DATA,
	ERROR_RANGE_MODE,
	ERROR_NF_LIB_CALCULATE,
	EEROR_OSAGETCALFILEPATH,
	EEROR_OSAGETSRCFILEPATH,
	EEROR_OSAGETOACFILEPATH,
};

enum COMINTERFACEERROR
{
	ERROR_COMDEV = 0x70000000,
	ERROR_COMMUNICATION_INFO,
	ERROR_COMMUNICATION_GPIB,
	ERROR_COMMUNICATION_LAN,
	ERROR_COMMUNICATION_COM,
	ERROR_COMMUNICATION_USB,
	ERROR_WRITE,
	ERROR_READ,
	ERROR_OPEN,
	ERROR_CLOSE,
	ERROR_SERIALPOLL,
	ERROR_WAIT_FOR_COMPLETION,
	ERROR_CLEAR,
	ERROR_REQ_COMPLETION,
	ERROR_GET_ERRORINFO,
	ERROR_LOGIN,
	ERROR_RUN_OVERTIME,
};
enum SWITCHBOXDEVICEERROR
{
	ERROR_SWITCHBOX = 0x80000000,
	ERROR_SWITCH_CHANNEL,
	ERROR_SWITCHSELECT,
	ERROR_SWITCH,

};
enum TLSSCANERROR
{
	ERROR_SWEEP_POINT = 0x90000000,
	ERROR_PW_RANGE,
	ERROR_WL_RANGE,
	ERROR_GET_TLS_RANGE,
	ERROR_TLS_SCAN_WLRANGE,
	ERROR_TLS_SCAN_PREPARE,
	ERROR_TLS_SCAN_POWER,
	ERROR_TLS_SOFT_TRIGER,
	ERROR_TLS_SCAN_START,
	ERROR_TLS_SCAN_RESULT,
	ERROR_PM_SCAN_PARPARE,
	ERROR_PM_SCAN_RESULT,
	ERROR_TLS_SCAN_STOP,
	ERROR_PM_SCAN_STOP,
	ERROR_PM_TRIGER_STOP,

};


enum COMMONERROR
{
	ERROR_BUFFER_OVER = 0xF0000001,
	ERROR_PTR_NULL,
	ERROR_FILE_OPEN,
	ERROR_FILE_READ,
	ERROR_FILE_WRITE,
};

enum TLSHAREERROR
{
	ERROR_TLSHAREDLLLOAD = 0X00000049,
	ERROR_TLSHAREINTERFACE,
	ERROR_TLSSHARESTARTSRV,
	ERROR_TLSSHARESENDMSG,
	ERROR_TLSSHARESTOPSRV,
	ERROR_TLSSHAREREG,
	ERROR_TLSSHARESETWL,
	ERROR_TLSSHARESETPOWER,
	ERROR_TLSSHARESETPARAM,
	ERROR_TLSSHARESETUNIT,
	ERROR_TLSSHARESETENABLE,
	EEROR_TLSSHARESETCOHERENCE,
	ERROR_TLSSHARESETLOCK,
	ERROR_TLSSHARESETUNLOCK,
	ERROR_TLSSHARESETCLOSE,


};

enum OSASHAREERROR {
	ERROR_OSASHAREDLLLOAD = 0X00000100,
	ERROR_OSASHAREINTERFACE,
	ERROR_OSASHARESTARTSRV,
	ERROR_OSASHARESENDMSG,
	ERROR_OSASHARESTOPSRV,
	ERROR_OSASHAREREG,
	ERROR_OSASHARESETCLOSE,
	ERROR_OSASHAREGETCHCOUNT,
	ERROR_OSASHAREREADCHSCANDATA,
	ERROR_OSASHAREGETCHNF,
	ERROR_OSASHAREGETGAIN,
	ERROR_OSASHAREGETPOWER,
	ERROR_OSASHARESETINISW,
	ERROR_OSASHARERESETDEVICE,
	ERROR_OSASHAREGETAMPOFFSET,
	ERROR_OSASHARESETAMPOFFSET,
	ERROR_OSASHARESETLOCALCTRL,
	ERROR_OSASHAREGETRUNSW,
	ERROR_OSASHAREGETSWPOINTCOUNT,
	ERROR_OSASHARESETINITAMP,
	ERROR_OSASHARESETRBW,
	ERROR_OSASHAREGETRBW,
	ERROR_OSASHAREGETEDFARESULT,
	ERROR_OSASHAREGETSWDATA,
	ERROR_OSASHARESETCAL,
	ERROR_OSASHAREGETZOOMVALUE,
	ERROR_OSASHAREGETACTUALBW,
	ERROR_OSASHARESETSENSE,
	ERROR_OSASHARESETMEASURESOURCE,
	ERROR_OSASHARESETMEASUREAMP,
	ERROR_OSASHARESETINITWDMTEST,
	ERROR_OSASHARESETMEASUREWDM,
	
};





#endif