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

//MainFrame��Ϣ�ṹ��
typedef struct tagMainFrame
{
	BOOL  bMainFrameIsOPen;  //MainFrame�Ƿ��Ѿ��򿪱�־λ
	int nIndex;             //�豸��ţ���XML�豸�����ͬ
	int nOnLine;                //�豸�Ƿ�����
	int nComType;               //ͨ�ŷ�ʽ���ͣ�0 - ����GPIB, 1 - ������, 2 - ����NET, 3 - ����USB
	int nDevID;              //�豸��GPIB��TCPIP��ASRLͨѶID��
	int  nBeginSlotIndex;       //����Slot��ʼ��������
	int  nSlotCount;            //�ж��ٸ���������slot
	unsigned long  lMainFramHandle; //����Ǵ򿪵��豸�򱣴浱ǰ�豸handle
	TCHAR strCaption[100];         //MainFram����
	TCHAR strAddress[100];         //ͨ�ŵ�ַ,GPIB - 20,SERIAL - 1,115200,8,0,0
	TCHAR strHWVersion[50];		//Ӳ���汾��
	TCHAR strFWVersion[50];		//����汾��
	TCHAR strCode[50];			//�豸���к�
	TCHAR strSN[50];				//�豸SN��
}stMainFrame,*pstMainFrame;
//Channel��Ϣ�ṹ��
typedef struct tagChannelInfo 
{
	int nOnline;      //��channel�Ƿ����
	int nCurChannel;  //��ǰchannel����
	CString strType;  //channel����
}stChInfo,*pChInfo;

//Slot��Ϣ�ṹ��
typedef struct tagSlotInfo 
{
	int  nDevIndex;               //�豸��ţ���XML�豸�����ͬ
	int  nConfigIndex;            //����������
	int  nOnline;                //��ǰSlot�Ƿ�����,0�������ߣ�1��������   
    int  nSlotType;            //Slot ���ͣ�0- TLS ,1 -PM ,2 -VOA,3 -OSA,4-POL,5-Chamber
    int  nLogicalChannel;        //�߼���Channel����
	int  nChanelCout;            //����slot���м�������channel
	int  nCurSlotIndex;          //��ǰ����Slot��
	stChInfo  chInfo;            //ͨ�������Ϣ
	HANDLE  hMainFrameHandle;    //Slot��ӦMainFrame��ʵ�����
	CString strCaption;			//Slotģ������
    CString strHWVersion;		//Ӳ���汾��
	CString strFWVersion;		//����汾��
	CString strSN;				//�豸SN��
}stSlotInfo,*pstSlotInfo;

//����iTLA�������ṹ��
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
//����UC�������ṹ��
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
