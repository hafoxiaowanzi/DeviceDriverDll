// VOAControl.h: interface for the CVOAControl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VOACONTROL_H__834550AF_F67F_4B67_ABC4_2C2C6A00A907__INCLUDED_)
#define AFX_VOACONTROL_H__834550AF_F67F_4B67_ABC4_2C2C6A00A907__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Communicationudl.h"
#include "UDLReturnCode.h"

#define HP_8156A 0
#define OPLK_VOA 1
#define A8164_VOA 2
#define OPLINKR153CHAKA 3
#define OPLINKDULVOA 4
#define AQ2200_311A  5
#define AQ3150       6
#define SANTECTLSVOA 7

class CVOAControl 
{
public:
	CVOAControl();
	virtual ~CVOAControl();
	virtual DWORD OpenDevice(char* pszDeviceAddr, unsigned long *comHandle) = 0;
	virtual DWORD CloseDevice() = 0;
	virtual DWORD SetHandle(char* pszDeviceAddr, unsigned long comHandle) = 0;
	virtual DWORD ResetDevice(void) = 0;
	virtual DWORD GetDeviceInfo(stDevInfo *stInfo) = 0;
	virtual DWORD SetWavelength(long lChIndex, double dblWL)=0;
	virtual DWORD GetWavelength(long lChIndex, double* pdblWL)=0;
    virtual DWORD SetAttenuation(long lChIndex, double dblAtten)=0;
	virtual DWORD GetAttenuation(long lChIndex, double* pdblAtten)=0;
	virtual DWORD SetEnableOutput(long lChIndex, BOOL bEnable)=0;
	virtual DWORD SetInputOffset(long lChIndex, double dblOffset)=0;
	virtual DWORD GetStatus(DWORD *dwStatus)=0;
	virtual BOOL GetErrorMessage(DWORD dwErrorCode, char *pszErrorMsg) = 0;

};

class CVOA_HP8156X : public CVOAControl
{
public:
	CVOA_HP8156X();
	virtual ~CVOA_HP8156X();

	virtual DWORD OpenDevice(char* pszDeviceAddr, unsigned long *comHandle);
	virtual DWORD CloseDevice();
	virtual DWORD SetHandle(char* pszDeviceAddr, unsigned long comHandle);
	virtual DWORD ResetDevice(void);
	virtual DWORD GetDeviceInfo(stDevInfo *stInfo);
	virtual DWORD SetWavelength(long lChIndex, double dblWL);
	virtual DWORD GetWavelength(long lChIndex, double* pdblWL);
    virtual DWORD SetAttenuation(long lChIndex, double dblAtten);
	virtual DWORD GetAttenuation(long lChIndex, double* pdblAtten);
	virtual DWORD SetEnableOutput(long lChIndex, BOOL bEnable);
	virtual DWORD SetInputOffset(long lChIndex, double dblOffset);
	virtual DWORD GetStatus(DWORD *dwStatus);
	virtual BOOL GetErrorMessage(DWORD dwErrorCode, char *pszErrorMsg);

protected:
	void CompleteRequest();//Check if the OSA busy,if busy then wait.
	char m_pszGlobleMsg[100];
	CCommunicationDLL m_Comm;
};

class COplkMEMSVOA : public CVOAControl  
{
public:
	COplkMEMSVOA();
	virtual ~COplkMEMSVOA();
	
	virtual DWORD OpenDevice(char* pszDeviceAddr, unsigned long *comHandle);
	virtual DWORD CloseDevice();
	virtual DWORD SetHandle(char* pszDeviceAddr, unsigned long comHandle);
	virtual DWORD SetWavelength(long lChIndex, double dblWL);
	virtual DWORD SetInputOffset(long lChIndex, double dblOffset);
	virtual DWORD SetEnableOutput(long lChIndex, BOOL bEnable);
	virtual DWORD SetAttenuation(long lChIndex, double dblAtten);
	virtual DWORD ResetDevice();
	virtual DWORD GetWavelength(long lChIndex, double *dblWL);
	virtual DWORD GetStatus(DWORD *dwStatus);
	virtual BOOL GetErrorMessage(DWORD dwErrorCode, char *pszErrorMsg);
	virtual DWORD GetDeviceInfo(stDevInfo *stInfo);
	virtual DWORD GetAttenuation(long lChIndex, double *dblAtten);

protected:
	CCommunicationDLL m_Comm;
};

class CVOA_Aglient8164 : public CVOAControl
{
public:
	CVOA_Aglient8164();
	virtual ~CVOA_Aglient8164();

	virtual DWORD OpenDevice(char* pszDeviceAddr, unsigned long *comHandle);
	virtual DWORD CloseDevice();
	virtual DWORD SetHandle(char* pszDeviceAddr, unsigned long comHandle);
	virtual DWORD ResetDevice(void);
	virtual DWORD GetDeviceInfo(stDevInfo *stInfo);
	virtual DWORD SetWavelength(long lChIndex, double dblWL);
	virtual DWORD GetWavelength(long lChIndex, double* pdblWL);
    virtual DWORD SetAttenuation(long lChIndex, double dblAtten);
	virtual DWORD GetAttenuation(long lChIndex, double* pdblAtten);
	virtual DWORD SetEnableOutput(long lChIndex, BOOL bEnable);
	virtual DWORD SetInputOffset(long lChIndex, double dblOffset);
	virtual DWORD GetStatus(DWORD *dwStatus);
	virtual BOOL GetErrorMessage(DWORD dwErrorCode, char *pszErrorMsg);

protected:
	void CompleteRequest();//Check if the OSA busy,if busy then wait.
	char m_pszGlobleMsg[100];
	CCommunicationDLL m_Comm;
};


class COplkR153VOA : public CVOAControl  
{
public:
	COplkR153VOA();
	virtual ~COplkR153VOA();
	
	virtual DWORD OpenDevice(char* pszDeviceAddr, unsigned long *comHandle);
	virtual DWORD CloseDevice();
	virtual DWORD SetHandle(char* pszDeviceAddr, unsigned long comHandle);
	virtual DWORD SetWavelength(long lChIndex, double dblWL);
	virtual DWORD SetInputOffset(long lChIndex, double dblOffset);
	virtual DWORD SetEnableOutput(long lChIndex, BOOL bEnable);
	virtual DWORD SetAttenuation(long lChIndex, double dblAtten);
	virtual DWORD ResetDevice();
	virtual DWORD GetWavelength(long lChIndex, double *dblWL);
	virtual DWORD GetStatus(DWORD *dwStatus);
	virtual BOOL  GetErrorMessage(DWORD dwErrorCode, char *pszErrorMsg);
	virtual DWORD GetDeviceInfo(stDevInfo *stInfo);
	virtual DWORD GetAttenuation(long lChIndex, double *dblAtten);

protected:
	CCommunicationDLL m_Comm;
};

class COplkDulVOA : public CVOAControl  
{
public:
	COplkDulVOA();
	virtual ~COplkDulVOA();
	
	virtual DWORD OpenDevice(char* pszDeviceAddr, unsigned long *comHandle);
	virtual DWORD CloseDevice();
	virtual DWORD SetHandle(char* pszDeviceAddr, unsigned long comHandle);
	virtual DWORD SetWavelength(long lChIndex, double dblWL);
	virtual DWORD SetInputOffset(long lChIndex, double dblOffset);
	virtual DWORD SetEnableOutput(long lChIndex, BOOL bEnable);
	virtual DWORD SetAttenuation(long lChIndex, double dblAtten);
	virtual DWORD ResetDevice();
	virtual DWORD GetWavelength(long lChIndex, double *dblWL);
	virtual DWORD GetStatus(DWORD *dwStatus);
	virtual BOOL  GetErrorMessage(DWORD dwErrorCode, char *pszErrorMsg);
	virtual DWORD GetDeviceInfo(stDevInfo *stInfo);
	virtual DWORD GetAttenuation(long lChIndex, double *dblAtten);

	BOOL SetWorkMode(long lChIndex,int nWorkMode,double dbValue);

protected:
	CCommunicationDLL m_Comm;
};

class CAQ2200_311A : public CVOAControl
{
public:
	CAQ2200_311A();
	virtual ~CAQ2200_311A();

	virtual DWORD OpenDevice(char* pszDeviceAddr, unsigned long *comHandle);
	virtual DWORD CloseDevice();
	virtual DWORD SetHandle(char* pszDeviceAddr, unsigned long comHandle);
	virtual DWORD ResetDevice(void);
	virtual DWORD GetDeviceInfo(stDevInfo *stInfo);
	virtual DWORD SetWavelength(long lChIndex, double dblWL);
	virtual DWORD GetWavelength(long lChIndex, double* pdblWL);
    virtual DWORD SetAttenuation(long lChIndex, double dblAtten);
	virtual DWORD GetAttenuation(long lChIndex, double* pdblAtten);
	virtual DWORD SetEnableOutput(long lChIndex, BOOL bEnable);
	virtual DWORD SetInputOffset(long lChIndex, double dblOffset);
	virtual DWORD GetStatus(DWORD *dwStatus);
	virtual BOOL GetErrorMessage(DWORD dwErrorCode, char *pszErrorMsg);

protected:
	DWORD CompleteRequest();//Check if the OSA busy,if busy then wait.
	char m_pszGlobleMsg[100];
	CCommunicationDLL m_Comm;
};

class CAQ3150: public CVOAControl
{
public:
	CAQ3150();
	virtual ~CAQ3150();

	virtual DWORD OpenDevice(char* pszDeviceAddr, unsigned long *comHandle);
	virtual DWORD CloseDevice();
	virtual DWORD SetHandle(char* pszDeviceAddr, unsigned long comHandle);
	virtual DWORD ResetDevice(void);
	virtual DWORD GetDeviceInfo(stDevInfo *stInfo);
	virtual DWORD SetWavelength(long lChIndex, double dblWL);
	virtual DWORD GetWavelength(long lChIndex, double* pdblWL);
    virtual DWORD SetAttenuation(long lChIndex, double dblAtten);
	virtual DWORD GetAttenuation(long lChIndex, double* pdblAtten);
	virtual DWORD SetEnableOutput(long lChIndex, BOOL bEnable);
	virtual DWORD SetInputOffset(long lChIndex, double dblOffset);
	virtual DWORD GetStatus(DWORD *dwStatus);
	virtual BOOL  GetErrorMessage(DWORD dwErrorCode, char *pszErrorMsg);

protected:
	char m_pszGlobleMsg[100];
	CCommunicationDLL m_Comm;
};


class CSantectTLSVOA : public CVOAControl  
{
public:
	CSantectTLSVOA();
	virtual ~CSantectTLSVOA();
	
	virtual DWORD OpenDevice(char* pszDeviceAddr, unsigned long *comHandle);
	virtual DWORD CloseDevice();
	virtual DWORD SetHandle(char* pszDeviceAddr, unsigned long comHandle);
	virtual DWORD SetWavelength(long lChIndex, double dblWL);
	virtual DWORD SetInputOffset(long lChIndex, double dblOffset);
	virtual DWORD SetEnableOutput(long lChIndex, BOOL bEnable);
	virtual DWORD SetAttenuation(long lChIndex, double dblAtten);
	virtual DWORD ResetDevice();
	virtual DWORD GetWavelength(long lChIndex, double *dblWL);
	virtual DWORD GetStatus(DWORD *dwStatus);
	virtual BOOL  GetErrorMessage(DWORD dwErrorCode, char *pszErrorMsg);
	virtual DWORD GetDeviceInfo(stDevInfo *stInfo);
	virtual DWORD GetAttenuation(long lChIndex, double *dblAtten);

protected:
	CCommunicationDLL m_Comm;
};

#endif // !defined(AFX_VOACONTROL_H__834550AF_F67F_4B67_ABC4_2C2C6A00A907__INCLUDED_)
