#ifndef  __HEARDER_H__

#define  __HEARDER_H__

#ifndef DLLEXPORT
#define DLLEXPORT   __declspec( dllexport )
#endif
#ifndef DllImport
#define DllImport   __declspec( dllimport )
#endif

#include "visa.h"
#include "math.h"

enum eDevComType{T_GPIB=0,T_SERIAL,T_NET,T_USB};
enum eDevType{TAG_TLS=0,TAG_PM,TAG_VOA,TAG_OSA,TAG_POL,TAG_CHAMBER,TAG_COMDEV,TAG_SWITCH};
#define   DtValid_Range -35 
#define   DEVICE_MAX_CHANNEL 8

#define ALPHA_ERROR_VALUE -1111
#define MAX_SLOT_NUM 64
#define MAX_DEVICE_NUM 5

//MainFrame信息结构体
typedef struct tagMainFrame
{
	BOOL  bMainFrameIsOPen;  //MainFrame是否已经打开标志位
	int nIndex;             //设备序号，与XML设备序号相同
	int nOnLine;                //设备是否启用
	int nComType;               //通信方式类型：0 - 代表GPIB, 1 - 代表串口, 2 - 代表NET, 3 - 代表USB
	int nDevID;              //设备中GPIB、TCPIP、ASRL通讯ID号
	int  nBeginSlotIndex;       //物理Slot开始的索引号
	int  nSlotCount;            //有多少个物理索引slot
	unsigned long  lMainFramHandle; //如果是打开的设备则保存当前设备handle
	TCHAR strCaption[100];         //MainFram名称
	TCHAR strAddress[100];         //通信地址,GPIB - 20,SERIAL - 1,115200,8,0,0
	TCHAR strHWVersion[50];		//硬件版本号
	TCHAR strFWVersion[50];		//软件版本号
	TCHAR strCode[50];			//设备序列号
	TCHAR strSN[50];				//设备SN号
}stMainFrame,*pstMainFrame;
//Channel信息结构体
typedef struct tagChannelInfo 
{
	int nOnline;      //该channel是否可用
	int nCurChannel;  //当前channel索引
	CString strType;  //channel描述
}stChInfo,*pChInfo;

//Slot信息结构体
typedef struct tagSlotInfo 
{
	int  nDevIndex;               //设备序号，与XML设备序号相同
	int  nConfigIndex;            //配置索引号
	int  nOnline;                //当前Slot是否在线,0代表在线，1代表不在线   
    int  nSlotType;            //Slot 类型，0- TLS ,1 -PM ,2 -VOA,3 -OSA,4-POL,5-Chamber
    int  nLogicalChannel;        //逻辑上Channel索引
	int  nChanelCout;            //物理slot含有几个物理channel
	int  nCurSlotIndex;          //当前物理Slot号
	stChInfo  chInfo;            //通道相关信息
	HANDLE  hMainFrameHandle;    //Slot对应MainFrame的实例句柄
	CString strCaption;			//Slot模块名称
    CString strHWVersion;		//硬件版本号
	CString strFWVersion;		//软件版本号
	CString strSN;				//设备SN号
}stSlotInfo,*pstSlotInfo;

//定义iTLA激光器结构体
typedef struct tagiTLAConfigInof
{
	double dbMinPower;
	double dbMaxPower;
	int nMinChannelNum;
	int nMaxChannelNum;
	int nMinFrequency;
	int nMaxFrequency;
	int nFrequencyGrid;
}stiTLAConfigInfo,*piTLAConfigInfo;
//定义UC激光器结构体
typedef struct TagUCConfigInof
{
	double dbMinPower;
	double dbMaxPower;
	int nChannelNum;
	int nMinFrequency;
	int nMaxFrequency;
	int nFrequencyStep;
	double nMinwavelenth;
	double nMaxwavelenth;
	double nwavelenthStep;
}stUCConfigInfo,*pUCConfigInfo;

#endif
