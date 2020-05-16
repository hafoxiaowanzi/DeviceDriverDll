#ifndef __FUNCTION_H__
#define __FUNCTION_H__


typedef struct tagCOMParam
{
   long lChIndex;
   SOCKET s;
}stComParam,*pComParam;


bool InitalUDLServer();//初始化UDL组件各个接口指针
bool ReleaseUDLServer();//释放UDL组件各个接口指针

void PrintRevMsg(LPCSTR lpstrMsg);
UINT MTServerThread(LPVOID pParam);
void HandleBackspaceChar(char * pszSrc,int nLength);
UINT ClientThread(LPVOID pParam);
UINT COMSendThread(LPVOID pParam);
BOOL ParseCmd(char *str, CString& cmd, CString& params);
BOOL SendBufferBy1M(SOCKET s, char * str, int nLength);
BOOL SendFile(SOCKET s, CString fname);

void SendHelpInfo(SOCKET s);
BOOL SendErrorMsg(SOCKET s,int nMsgType);
BOOL ResponseMsg(char* pBuffer,LPCSTR lpstrCMD,SOCKET s);
BOOL HandleHelpMsg(char* pBuffer,LPCSTR lpstrCMD,SOCKET s);
BOOL HandleEngineMsg(char* pBuffer,LPCSTR lpstrCMD,SOCKET s);
BOOL HandleTLSMsg(char* pBuffer,LPCSTR lpstrCMD,SOCKET s);
BOOL HandlePMMsg(char* pBuffer,LPCSTR lpstrCMD,SOCKET s);
BOOL HandleVOAMsg(char* pBuffer,LPCSTR lpstrCMD,SOCKET s);
BOOL HandlePOLMsg(char* pBuffer,LPCSTR lpstrCMD,SOCKET s);
BOOL HandlechamberMsg(char* pBuffer,LPCSTR lpstrCMD,SOCKET s);
BOOL HandleOSAMsg(char* pBuffer,LPCSTR lpstrCMD,SOCKET s);
BOOL HandleDevMsg(char* pBuffer,LPCSTR lpstrCMD,SOCKET s);

//////////////////////////////Engine Function//////////////////////////////////////
void SendEngineInfo(SOCKET s);
BOOL LoadConfigCMD(char *Buff,SOCKET s);
BOOL OpenDevice(SOCKET s);
//////////////////////////////TLS Function/////////////////////////////////////////
void SendTLSInfo(SOCKET s);
BOOL SetTLSWavelength(char *Buff,SOCKET s);
BOOL SetTLSSourcePower(char *Buff,SOCKET s);
BOOL SetTLSCoherenceControl(char *Buff,SOCKET s);
BOOL SetTLSSourceUnit(char *Buff,SOCKET s);
BOOL SetTLSParameters(char *Buff,SOCKET s);
BOOL SetTLSOutputEnable(char *Buff,SOCKET s);
BOOL CloseTLSDevice(char *Buff,SOCKET s);
//////////////////////////////PM Function///////////////////////////////////////
void SendPMInfo(SOCKET s);
BOOL GetPMUnit(char *Buff,SOCKET s);
BOOL GetPMAverageTime(char *Buff,SOCKET s);
BOOL GetPMWavelength(char *Buff,SOCKET s);
BOOL ReadPower(char *Buff,SOCKET s);
BOOL SetPMUnit(char *Buff,SOCKET s);
BOOL SetPMWavelength(char *Buff,SOCKET s);
BOOL SetPMAverageTime(char *Buff,SOCKET s);
BOOL SetPMRangeMode(char *Buff,SOCKET s);
BOOL SetPMParameters(char *Buff,SOCKET s);
BOOL ClosePMDevice(char *Buff,SOCKET s);
BOOL GetPMRangeMode(char *Buff,SOCKET s);
BOOL SetPMZero(char *Buff,SOCKET s);
BOOL SetPMMaxMinPowerStart(char *Buff,SOCKET s);
BOOL GetPMMaxMinPower(char *Buff,SOCKET s);
BOOL SetPMMaxMinPowerStop(char *Buff,SOCKET s);

//////////////////////////////VOA Function/////////////////////////////////
void SendVOAInfo(SOCKET s);
BOOL CloseVOADevice(char *Buff,SOCKET s);
BOOL ResetVOADevice(char *Buff,SOCKET s);
BOOL SetVOAWavelength(char *Buff,SOCKET s);
BOOL GetVOAWavelength(char *Buff,SOCKET s);
BOOL SetVOAAttenuation(char *Buff,SOCKET s);
BOOL GetVOAAttenuation(char *Buff,SOCKET s);
BOOL SetVOAEnableOutput(char *Buff,SOCKET s);
BOOL SetVOAInputOffset(char *Buff,SOCKET s);
BOOL GetVOAStatus(char *Buff,SOCKET s);

//////////////////////////////PDL Function/////////////////////////////////
void SendPOLInfo(SOCKET s);
BOOL ClosePolDevice(char *Buff,SOCKET s);
BOOL ResetPolDevice(char *Buff,SOCKET s);
BOOL GetPolCurrentPOSPolarizer(char *Buff,SOCKET s);
BOOL SetPolALL(char *Buff,SOCKET s);
BOOL SetPolDiagonalAngles(char *Buff,SOCKET s);
BOOL SetPolHorizontalAngles(char *Buff,SOCKET s);
BOOL SetPolPOSHalf(char *Buff,SOCKET s);
BOOL SetPolPOSPolarizer(char *Buff,SOCKET s);
BOOL SetPolPOSQuarter(char *Buff,SOCKET s);
BOOL SetPolRightHandCircularAngles(char *Buff,SOCKET s);
BOOL SetPolVerticalAngles(char *Buff,SOCKET s);

//////////////////////////////Chamber Function///////////////////////////////
void  SendChamberInfo(SOCKET s);
BOOL  CloseChamberDevice(char *Buff,SOCKET s);
BOOL  SetChamberRunStop(char *Buff,SOCKET s);
BOOL  SetChamberRunStart(char *Buff,SOCKET s);
BOOL  SetChamberSetPoint(char *Buff,SOCKET s);
BOOL  GetChamberSetPoint(char *Buff,SOCKET s);
BOOL  GetChamberCurrentTemp(char *Buff,SOCKET s);

///////////////////////////////OSA Function/////////////////////////////////
void SendOSAInfo(SOCKET s);
BOOL CloseOSADevice(char *Buff,SOCKET s);
BOOL ResetOSADevice(char *Buff,SOCKET s);
BOOL SetOSALocalCtrl(char *Buff,SOCKET s);
BOOL SetOSARBW(char *Buff,SOCKET s);
BOOL GetOSARBW(char *Buff,SOCKET s);
BOOL InitOSAAmpTest(char *Buff,SOCKET s);
BOOL MeasureOSASource(char *Buff,SOCKET s);
BOOL MeasureOSAAmplifier(char *Buff,SOCKET s);
BOOL GetOSAChannelCount(char *Buff,SOCKET s);
BOOL GetOSAChannelWaveLens(char *Buff,SOCKET s);
BOOL GetOSAChannelNF(char *Buff,SOCKET s);
BOOL GetOSAChannelGain(char *Buff,SOCKET s);
BOOL GetOSAChannelSNR(char *Buff,SOCKET s);
BOOL GetOSAChannelSourcePower(char *Buff,SOCKET s);
BOOL SetOSAAmpOffset(char *Buff,SOCKET s);
BOOL GetOSAAmpOffset(char *Buff,SOCKET s);
BOOL GetOSAEDFAResult(char *Buff,SOCKET s);
BOOL GetOSAEDFAChResult(char *Buff,SOCKET s);
BOOL InitOSASingleSweep(char *Buff,SOCKET s);
BOOL RunOSASweep(char *Buff,SOCKET s);
BOOL GetSingleSweepPoint(char *Buff,SOCKET s);
BOOL GetOSASweepData(char *Buff,SOCKET s);
BOOL SaveOSADataToPC(char *Buff,SOCKET s);	
BOOL SetOSACalibration(char *Buff,SOCKET s);
BOOL GetZoomValue(char *Buff,SOCKET s);

///////////////////////////////Serial Function/////////////////////////////////
void SendComInfo(SOCKET s);
BOOL OpenCom(char *Buff,SOCKET s);
BOOL CloseCom(char *Buff,SOCKET s);
BOOL ComWrite(char *Buff,SOCKET s);
BOOL ComRead(char *Buff,SOCKET s);
#endif