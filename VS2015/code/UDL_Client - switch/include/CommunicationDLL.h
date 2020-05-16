
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the COMMUNICATIONDLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// COMMUNICATIONDLL_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef COMMUNICATIONDLL_EXPORTS
#define COMMUNICATIONDLL_API __declspec(dllexport)
#else
#define COMMUNICATIONDLL_API __declspec(dllimport)
#endif

#ifndef COMMUNICATION_HEADER
#define COMMUNICATION_HEADER

#include "..\\include\\Communication.h"
#include "..\\include\\UDLReturnCode.h"

// This class is exported from the CommunicationDLL.dll
class COMMUNICATIONDLL_API CCommunicationDLL 
{
public:
	CCommunicationDLL();
	virtual ~CCommunicationDLL();
	// TODO: add your methods here.
	DWORD OpenDevice(LPCTSTR lpCommunicationInfo, unsigned long &commHandle);
	DWORD CloseDevice();
	DWORD WriteDevice(PVOID pWriteBuffer, DWORD dwWriteLength);
	DWORD ReadDevice(PVOID pREadBuffer, DWORD dwReadLength);
	DWORD SetDeviceHandle(LPCTSTR lpCommunicationInfo, unsigned long pHandle);
	DWORD ClearDevice();
	string GetErrorMsg();

private:
	DWORD m_dwErrorCode;
	void *m_commun;
//	void **m_pvoid;
};

extern COMMUNICATIONDLL_API int nCommunicationDLL;

COMMUNICATIONDLL_API int fnCommunicationDLL(void);

#endif