#ifndef _JSONMSGStRUCT_H_
#define _JSONMSGStRUCT_H_

#include <WINSOCK.H>
#include <list>
#include <vector>
//��ϢЭ��
//{
//"platform": "FSSCAN",
//"USERID" : " ",
//"CLIENTID" : "",
//"TYPE" : {
//"MSGTYPE": "SCAN",
//	"MSG" : {
//	"MSG1": {"key":"DeviceType",value:"OSA"},
//	"MSG2": {"key":"wavelength",value:"1550.12"},
//   ....,
//},
//}
#define COMMDLL_CLIENTTYPE      0
#define COMMDLL_SERVERTTYPE     1

#define LENGTH_256B             256
#define LENGTH_128B             128
#define IP_DEFAULT			    ("127.0.0.1")

//typedef struct MsgData
//{
//	std::string strKey;
//	std::string strValue;
//}stMsgData, *pstMsgData;
//
//struct CommMsgPackage
//{
//	std::string strPlatForm;        //ƽ̨��Ϣ
//	std::string strSlot;             //Slot��
//	std::string strUserID;          //�ͻ�ID(�ͻ��������������)
//	std::string strClientID;        //������ϢĿ���ַ
//	std::string strIPAddress;       //IP��ַ
//	std::string strPort;            //�˿�
//	std::string strMsgType;         //��Ϣ����
//	std::string strTime;            //ʱ���
//	std::list<stMsgData> MsgList;   //��Ϣ����
//};

typedef struct MsgData
{
	char* strKey;
	char* strValue;
}stMsgData, *pstMsgData;

typedef struct STSOCKINITINFO
{
	//Service Type
	int nType;
	//Socket Port
	unsigned short us_Port;
	//Server IP, NULL means the IP is 127.0.0.1
	char pszSrvIP[LENGTH_128B];

	STSOCKINITINFO operator=(STSOCKINITINFO& info)
	{
		this->nType = info.nType;
		this->us_Port = info.us_Port;
		if (info.pszSrvIP)
			if (strlen(this->pszSrvIP) >= strlen(info.pszSrvIP))
				memcpy(this->pszSrvIP,info.pszSrvIP,sizeof(info.pszSrvIP));

		return *this;
	}
}stSockInfo, *pstSockInfo;

//STSOCKINITINFO
//stSockInfo, *pstSockInfo
//class CCommMsgPackage
//{
//private:
//		std::string strPlatForm;        //ƽ̨��Ϣ
//		std::string strSlot;             //Slot��
//		std::string strUserID;          //�ͻ�ID(�ͻ��������������)
//		std::string strClientID;        //������ϢĿ���ַ
//		std::string strIPAddress;       //IP��ַ
//		std::string strPort;            //�˿�
//		std::string strMsgType;         //��Ϣ����
//		std::string strTime;            //ʱ���
//		std::list<stMsgData> MsgList;   //��Ϣ����
//public:
//	    virtual bool GetHeadValue(std::string strKey, std::string strValue);
//		virtual bool SetHeadValue(std::string strKey, std::string strValue);
//		virtual bool GetMsgValue(std::string strMsgID, std::string strKey, std::string strValue);
//};

struct CommMsgPackage
{
	char  strPlatForm[LENGTH_256B];        //ƽ̨��Ϣ
	char  strSlot[LENGTH_256B];            //Slot��
	char  strUserID[LENGTH_256B];          //�ͻ�ID(�ͻ��������������)
	char  strClientID[LENGTH_256B];        //������ϢĿ���ַ
	char  strIPAddress[LENGTH_256B];       //IP��ַ
	char  strPort[LENGTH_256B];            //�˿�
	char  strMsgType[LENGTH_256B];         //��Ϣ����
	char  strTime[LENGTH_256B];            //ʱ���
	//��Ϣָ������
	int   nMsgCount;
	MsgData  *MsgList;  
	//����
	CommMsgPackage operator=(CommMsgPackage& srcPack)
	{
		memcpy(strPlatForm, srcPack.strPlatForm, sizeof(char)*LENGTH_256B);
		memcpy(strSlot , srcPack.strSlot, sizeof(char)*LENGTH_256B);
		memcpy(strUserID , srcPack.strUserID, sizeof(char)*LENGTH_256B);
		memcpy(strClientID, srcPack.strClientID, sizeof(char)*LENGTH_256B);
		memcpy(strIPAddress, srcPack.strIPAddress, sizeof(char)*LENGTH_256B);
		memcpy(strPort, srcPack.strPort, sizeof(char)*LENGTH_256B);
		memcpy(strMsgType, srcPack.strMsgType, sizeof(char)*LENGTH_256B);
		memcpy(strTime, srcPack.strTime, sizeof(char)*LENGTH_256B);
		nMsgCount = srcPack.nMsgCount;
		if (nMsgCount)
		{
			MsgList = new MsgData[nMsgCount];
			if (srcPack.MsgList != NULL)
			{
				for (int index = 0; index < nMsgCount; index++)
				{
					int len;
					if (srcPack.MsgList[index].strKey)
					{
						len = strlen(srcPack.MsgList[index].strKey) + 1;
						MsgList[index].strKey = new char[len];
						memcpy(MsgList[index].strKey, srcPack.MsgList[index].strKey, len * sizeof(char));
					}
					if (srcPack.MsgList[index].strValue)
					{
						len = strlen(srcPack.MsgList[index].strValue) + 1;
						MsgList[index].strValue = new char[len];
						memcpy(MsgList[index].strValue, srcPack.MsgList[index].strValue, len * sizeof(char));
					}
				}
			}
		}
		return *this;
	}

	//�ͷŴ����ߵ��ڴ�
    virtual void Release()
	{
		if (!this->MsgList)
		{
			nMsgCount = 0;
			return;
		}
		for (int index = 0; index < this->nMsgCount; index++)
		{
			if (MsgList[index].strKey)
			{
				delete[] MsgList[index].strKey;
				MsgList[index].strKey = NULL;
			}
			if (MsgList[index].strValue)
			{
				delete[] MsgList[index].strValue;
				MsgList[index].strValue = NULL;
			}
		}
		delete[] this->MsgList;
		this->MsgList = NULL;
	}
};

//Fuction Define
typedef BOOL(*StartSrv)(stSockInfo stInitSock);       //��ʼ������
typedef BOOL(*SendMsg)(CommMsgPackage* MsgPackage);   //����Ϣ
typedef BOOL(*RecvMsg)(CommMsgPackage** MsgPackage);   //����Ϣ
typedef void(*GetDllVer)(LPVOID pszVersion, LPVOID pszCompileDate);    //�汾��Ϣ
typedef LPVOID(*GetLastErr)(LPVOID* lpszErr);         //
typedef BOOL(*StopSrv)(void);                         //��ֹ����
typedef int(*AcqMsgCount)(void);                      //��Ϣ�б���Ŀ
typedef int(*AcqClientCount)(void);                   //(�ͻ���/��������)�б� ��Ŀ


#endif