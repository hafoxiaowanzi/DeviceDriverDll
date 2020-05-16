// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the OPLKGPIB_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// OPLKGPIB_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.

//#pragma comment(lib, "..//library//OSAControl.lib")

#ifndef COMMUNICATION_DLL
#define COMMUNICATION_DLL __declspec(dllimport)


class COMMUNICATION_DLL CCommunicationDLL
{

public:
	CCommunicationDLL();
	virtual ~CCommunicationDLL();
	DWORD OpenDevice(LPCTSTR lpCommunicationInfo, unsigned long &commHandle);
	DWORD CloseDevice();
	DWORD WriteDevice(PVOID pWriteBuffer, DWORD dwWriteLength);
	DWORD ReadDevice(PVOID pREadBuffer, DWORD dwReadLength);
	DWORD SerialPollDevice(PCHAR pbSPByte);
	DWORD WaitForCompletion(WORD wMask);

	DWORD IsRequestCompleted();
	DWORD GetDeviceError(PSTR pszErrorMessage);
	DWORD ClearDevice();
	DWORD SetDeviceHandle(LPCTSTR lpCommunicationInfo, unsigned long pHandle);

private:
	DWORD m_dwErrorCode;
	void *m_commun;
	void **m_pvoid;

};
#endif