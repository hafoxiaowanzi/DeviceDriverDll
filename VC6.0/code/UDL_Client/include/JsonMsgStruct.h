#ifndef _JSONMSGStRUCT_H_
#define _JSONMSGStRUCT_H_

#include <WINSOCK.H>
#include <list>
#include <vector>
//消息协议
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
//	std::string strPlatForm;        //平台消息
//	std::string strSlot;             //Slot号
//	std::string strUserID;          //客户ID(客户端与服务器定义)
//	std::string strClientID;        //发送消息目标地址
//	std::string strIPAddress;       //IP地址
//	std::string strPort;            //端口
//	std::string strMsgType;         //消息类型
//	std::string strTime;            //时间戳
//	std::list<stMsgData> MsgList;   //消息链表
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
//		std::string strPlatForm;        //平台消息
//		std::string strSlot;             //Slot号
//		std::string strUserID;          //客户ID(客户端与服务器定义)
//		std::string strClientID;        //发送消息目标地址
//		std::string strIPAddress;       //IP地址
//		std::string strPort;            //端口
//		std::string strMsgType;         //消息类型
//		std::string strTime;            //时间戳
//		std::list<stMsgData> MsgList;   //消息链表
//public:
//	    virtual bool GetHeadValue(std::string strKey, std::string strValue);
//		virtual bool SetHeadValue(std::string strKey, std::string strValue);
//		virtual bool GetMsgValue(std::string strMsgID, std::string strKey, std::string strValue);
//};

struct CommMsgPackage
{
	char  strPlatForm[LENGTH_256B];        //平台消息
	char  strSlot[LENGTH_256B];            //Slot号
	char  strUserID[LENGTH_256B];          //客户ID(客户端与服务器定义)
	char  strClientID[LENGTH_256B];        //发送消息目标地址
	char  strIPAddress[LENGTH_256B];       //IP地址
	char  strPort[LENGTH_256B];            //端口
	char  strMsgType[LENGTH_256B];         //消息类型
	char  strTime[LENGTH_256B];            //时间戳
	//消息指针数组
	int   nMsgCount;
	MsgData  *MsgList;  
	//拷贝
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

	//释放创建者的内存
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
typedef BOOL(*StartSrv)(stSockInfo stInitSock);       //初始化服务
typedef BOOL(*SendMsg)(CommMsgPackage* MsgPackage);   //发消息
typedef BOOL(*RecvMsg)(CommMsgPackage** MsgPackage);   //收消息
typedef void(*GetDllVer)(LPVOID pszVersion, LPVOID pszCompileDate);    //版本信息
typedef LPVOID(*GetLastErr)(LPVOID* lpszErr);         //
typedef BOOL(*StopSrv)(void);                         //终止服务
typedef int(*AcqMsgCount)(void);                      //消息列表数目
typedef int(*AcqClientCount)(void);                   //(客户端/服务器端)列表 数目


#endif