// PolControl.h: interface for the PolControl class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_SWITCH_H__CAB1F721_3927_479F_A5AF_07759C01F635__INCLUDED_)
#define AFX_SWITCH_H__CAB1F721_3927_479F_A5AF_07759C01F635__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UDLReturnCode.h"
#include "Communicationudl.h"

typedef struct tagSerialPortConfig
{
	DWORD dwBaudRate;// 115200
	BYTE byByteSize;  // 8
	BYTE byParity;    // NOPARITY,
	BYTE byStopBits;  //ONESTOPBIT
}stSerialPortCfg, *pstSerialPortCfg;

class CSwitchControl 
{
public:
	CSwitchControl();
	virtual ~CSwitchControl();

	virtual DWORD OpenDevice(LPCTSTR pszDeviceAddr, unsigned long *ComHandle)=0;
	virtual DWORD CloseDevice()=0;
	virtual DWORD SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle)=0;
	//~~~~~~~~~General SW Control~~~~~~~~~~~~~~~~~~~~
	//Single SW Control
	virtual DWORD SetSingleSWPos(BYTE bySWIndex, //SW Number:1~M,0xFF; 0xFF:All SW set to the same Position
		BYTE byPos) = 0;                   //Position:0~N; 0:Block position
	virtual DWORD GetSingleSWPos(BYTE bySWIndex, //SW Number:1~M;
		BYTE &byPos) = 0;                  //Position
										   //MultiSW Control
	virtual DWORD SetMultiSWPos(BYTE *pbyPosArray, //All SW Position:0~N,0xFF; 0xFF:Keep in place
		BYTE bySWCount) = 0;                   //SW Count
	virtual DWORD GetMultiSWPos(BYTE *pbyPosArray, //All SW Position
		BYTE bySWCount) = 0;                   //SW Count

											   //~~~~~~~~InputVOA Set~~~~~~~~~~~~~~~~~~~~~~~~~~~
											   //Input VOA Set
	virtual DWORD SetInputVOAAtten(double dblAtten) = 0;
	virtual DWORD GetInputVOAAtten(double *pdblAtten) = 0;
	//MSA VOA Set
	virtual DWORD SetMSAVOAAtten(double dblAtten) = 0;
	virtual DWORD GetMSAVOAAtten(double *pdblAtten) = 0;

	//~~~~~~~~SW Path~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	/*******************************************************************************************
	*function:切换LDS光源
	*param1:bySrcIndex 切换到第几路，范围1~8
	*return:0--成功，其他--出错，出错可调用GetLastErrorMsg函数获取错误信息
	********************************************************************************************/
	virtual DWORD SetLDSSelection(BYTE bySrcIndex) = 0; //1~8;SW1
														//S1~8->IN1~17
														/*******************************************************************************************
														*function:设置DUT-in为输出
														*param1:byDutInIndex 切换到DUT-in的第几路，范围1~17
														*return:0--成功，其他--出错，出错可调用GetLastErrorMsg函数获取错误信息
														********************************************************************************************/
	virtual DWORD SetLDSToDutIn(BYTE byDutInIndex) = 0; //1~17;SW2+SW9
														//S1~8->Out1~18
														/*******************************************************************************************
														*function:设置DUT-out为输出
														*param1:byDutOutIndex 切换到DUT-out的第几路，范围1~18
														*return:0--成功，其他--出错，出错可调用GetLastErrorMsg函数获取错误信息
														********************************************************************************************/
	virtual DWORD SetLDSToDutOut(BYTE byDutOutIndex) = 0;//1~18;SW3+SW9
														 //OPM/OSA
														 /*******************************************************************************************
														 *function:设置monitor输出
														 *param1:byDestPos 切换到OSA\OPM，1-OSA；2-OPM
														 *return:0--成功，其他--出错，出错可调用GetLastErrorMsg函数获取错误信息
														 ********************************************************************************************/
	virtual DWORD SetLDSToMonPath(BYTE byDestPos) = 0;//1~2;SW4
													  /*******************************************************************************************
													  *function:设置归零输出
													  *param1:byDestPos 切换到OSA\OPM，1-OSA；2-OPM
													  *return:0--成功，其他--出错，出错可调用GetLastErrorMsg函数获取错误信息
													  ********************************************************************************************/
	virtual DWORD SetLDSToRefPath(BYTE byDestPos) = 0;//1~2;SW2+SW4+SW5+SW9

													  /*******************************************************************************************
													  *function:DUT-out作为输入，到OSA/OPM输出
													  *param1:byDutOutIndex DUT-out第几路作为输入，范围1~18
													  *param2:byDestPos 切换到OSA\OPM，1-OSA；2-OPM
													  *return:0--成功，其他--出错，出错可调用GetLastErrorMsg函数获取错误信息
													  ********************************************************************************************/
	virtual DWORD SetDutOutToDest(BYTE byDutOutIndex, BYTE byDestPos) = 0;//SW3+SW4+SW5+SW9

																		  /*******************************************************************************************
																		  *function:DUT-in作为输入，到OSA/OPM输出
																		  *param1:byDutInIndex DUT-in第几路作为输入，范围1~17
																		  *param2:byDestPos 切换到OSA\OPM，1-OSA；2-OPM
																		  *return:0--成功，其他--出错，出错可调用GetLastErrorMsg函数获取错误信息
																		  ********************************************************************************************/
	virtual DWORD SetDutInAsOutput(BYTE byDutInIndex, BYTE byDestPos) = 0;//SW2+SW4+SW5+SW9

																		  /*******************************************************************************************
																		  *function:DUT-out作为输入，out98连接EO1，到OSA/OPM输出
																		  *param1:byDutOutIndex DUT-out第几路作为输入，范围1~18
																		  *param2:byDestPos 切换到OSA\OPM，1-OSA；2-OPM
																		  *return:0--成功，其他--出错，出错可调用GetLastErrorMsg函数获取错误信息
																		  ********************************************************************************************/
	virtual DWORD SetDutOut98ToEO1(BYTE byDutOutIndex, BYTE byDestPos) = 0;//SW3+SW4+SW5+SW9;OUT_98 connect to EO1

																		   /*******************************************************************************************
																		   *function:DUT-in作为输入，In98连接EO1，到OSA/OPM输出
																		   *param1:byDutInIndex DUT-in第几路作为输入，范围1~17
																		   *param2:byDestPos 切换到OSA\OPM，1-OSA；2-OPM
																		   *return:0--成功，其他--出错，出错可调用GetLastErrorMsg函数获取错误信息
																		   ********************************************************************************************/
	virtual DWORD SetDutIn98AsOutputToEO1(BYTE byDutInIndex, BYTE byDestPos) = 0;//SW2+SW4+SW5+SW9；OUT_98 connect to EO1

																				 /*******************************************************************************************
																				 *function:MSA-In作为输入，MSA-Out作为输出
																				 *param1:byMsaInPort MSA-In第几路作为输入，范围1~8
																				 *param2:byMsaOutPort MSA-Out第几路作为输出，范围1~8
																				 *param3:dblMsaVOAAtten MSA-VOA衰减值
																				 *return:0--成功，其他--出错，出错可调用GetLastErrorMsg函数获取错误信息
																				 ********************************************************************************************/
	virtual DWORD SetMSAInToMSAOut(BYTE byMsaInPort, BYTE byMsaOutPort, double dblMsaVOAAtten) = 0; //MAS IN->MAS OUT //SW6+SW7+SW8

																									/*******************************************************************************************
																									*function:MSA-Out作为输入，经过1%分光，到OSA/OPM输出
																									*param1:byMsaOutPort MSA-Out第几路作为输入，范围1~8
																									*param2:byDestPos 切换到OSA\OPM，1-OSA；2-OPM
																									*return:0--成功，其他--出错，出错可调用GetLastErrorMsg函数获取错误信息
																									********************************************************************************************/
	virtual DWORD SetMSATapToDest(BYTE byMsaOutPort, BYTE byDestPos) = 0; //SW4+SW5+SW6+SW8

																		  /*******************************************************************************************
																		  *function:MSA-In作为输入，OSA/OPM作为输出
																		  *param1:byMsaInPort MSA-In第几路作为输入，范围1~8
																		  *param2:byDestPos 切换到OSA\OPM，1-OSA；2-OPM
																		  *return:0--成功，其他--出错，出错可调用GetLastErrorMsg函数获取错误信息
																		  ********************************************************************************************/
	virtual DWORD SetMSAInAsOutput(BYTE byMsaInPort, BYTE byDestPos) = 0; //SW4+SW5+SW7+SW8

																		  /*******************************************************************************************
																		  *function:MSA-Out作为输入，OSA/OPM作为输出
																		  *param1:byMsaOutPort MSA-Out第几路作为输入，范围1~8
																		  *param2:byDestPos 切换到OSA\OPM，1-OSA；2-OPM
																		  *return:0--成功，其他--出错，出错可调用GetLastErrorMsg函数获取错误信息
																		  ********************************************************************************************/
	virtual DWORD SetMSAOutAsOutput(BYTE byMsaOutPort, BYTE byDestPos) = 0; //SW4+SW5+SW6+SW8

																			/*******************************************************************************************
																			*function:MSA-Out作为输入，MOP98连接EO2，到OSA/OPM输出
																			*param1:byMsaOutPort MSA-Out第几路作为输入，范围1~8
																			*param2:byDestPos 切换到OSA\OPM，1-OSA；2-OPM
																			*return:0--成功，其他--出错，出错可调用GetLastErrorMsg函数获取错误信息
																			********************************************************************************************/
	virtual DWORD SetMSAOut98AsOutputToEO2(BYTE byMsaOutPort, BYTE byDestPos) = 0; //SW4+SW5+SW6+SW8;MOP_98 connect to EO2

																				   /*******************************************************************************************
																				   *function:EO1~3作为输入，到OSA/OPM输出
																				   *param1:byEOPort EO1~3为输入，范围1~3
																				   *param2:byDestPos 切换到OSA\OPM，1-OSA；2-OPM
																				   *return:0--成功，其他--出错，出错可调用GetLastErrorMsg函数获取错误信息
																				   ********************************************************************************************/
	virtual DWORD SetEOPortToDest(BYTE byEOPort, BYTE byDestPos) = 0; //EO1~3 SW4+SW5;

																	  //~~~~~~~~~~~~~Trigger~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
																	  //VOA Drive Trigger
	virtual DWORD SetVOATriggerOut(double dblStartAtten, double dblEndAtten, double dblStepAtten, WORD wOPMWaitTimeMs) = 0;
	//SW Drive Trigger
	virtual DWORD SetSWPathMapping(char *pchBinfileName) = 0;
	virtual DWORD SetSWTriggerPathScanStart(WORD wExitTimeOutSecond) = 0;
	//Query Scan Status
	//DWORD GetTriggerScanStatus(BYTE &byStatus);

	//~~~~~~~~GPIO Setting~~~~~~~~~~~~~~~~~~~~~~~~~~
	//Definition:0 - Input; 1 - Output;
	//if wAlarmIN==0(Input),set 0~15Bits to 0; if wAlarmIN==1(Output),set 0~15Bits to 1;
	//if wAlarmOut==0(Input),set 16~31Bits to 0; if wAlarmOut==1(Output),set 16~31Bits to 1;
	virtual DWORD SetGPIOStatus(WORD wAlarmIN, WORD wAlarmOut) = 0;
	virtual DWORD GetGPIOStatus(WORD *pwAlarmIN, WORD *pwAlarmOut) = 0;
	virtual DWORD SetGPIOVoltage(bool bVoltage5V = 1) = 0;
	//set GPIO Voltage output 5V(Default)/3.3V (bVoltage5V=0) 

	//~~~~~~~~UART Setting~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//Struct 
	//byUARTIndex =0Xff: ALL
	virtual DWORD SetUARTConfig(BYTE byUARTIndex, stSerialPortCfg stSerialPortCfgValue, DWORD dwTimeOut = 0) = 0;
	virtual DWORD WriteUARTData(BYTE byUARTIndex, BYTE* pbyBuffer, WORD wLength) = 0;
	virtual DWORD ReadUARTData(BYTE byUARTIndex, BYTE* pbyBuffer, WORD wLength, WORD *pwGetLength) = 0;

	//~~~~~~~~~BasicInfo~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//开关切换次数/校准日期/生产日期
	virtual DWORD GetDeviceInfo(pstDevInfo pstSWInfo) = 0;
	virtual DWORD GetSwitchingCnt(BYTE bySWIndex, DWORD *pdwSwitchingCnt) = 0; //只针对机械式开关
																			   //超过100次存一次,未满100次则不存

																			   //~~~~~~~~IL/WDL Value~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	virtual DWORD GetInputMinIL(BYTE bySWIndex, double * pdblGetMinIL) = 0;

	//Added 
	virtual DWORD SetBlockBySwitch(BYTE bySrcIndex) = 0; //SW1
};

class CSwitch1X2 :public CSwitchControl
{
public:
	CSwitch1X2();
	virtual ~CSwitch1X2();

	virtual DWORD OpenDevice(LPCTSTR pszDeviceAddr, unsigned long *ComHandle);
	virtual DWORD CloseDevice();
	virtual DWORD SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle);
	//M:Max SW Count
	//N:Max SW Port Count
	//X:Max VOA Count

	//~~~~~~~~~General SW Control~~~~~~~~~~~~~~~~~~~~
	//Single SW Control
	virtual DWORD SetSingleSWPos(BYTE bySWIndex, //SW Number:1~M,0xFF; 0xFF:All SW set to the same Position
		BYTE byPos);                   //Position:0~N; 0:Block position
	virtual DWORD GetSingleSWPos(BYTE bySWIndex, //SW Number:1~M;
		BYTE &byPos);                  //Position
									   //MultiSW Control
	virtual DWORD SetMultiSWPos(BYTE *pbyPosArray, //All SW Position:0~N,0xFF; 0xFF:Keep in place
		BYTE bySWCount);                   //SW Count
	virtual DWORD GetMultiSWPos(BYTE *pbyPosArray, //All SW Position
		BYTE bySWCount);                   //SW Count

										   //~~~~~~~~InputVOA Set~~~~~~~~~~~~~~~~~~~~~~~~~~~
										   //Input VOA Set
	virtual DWORD SetInputVOAAtten(double dblAtten);
	virtual DWORD GetInputVOAAtten(double *pdblAtten);
	//MSA VOA Set
	virtual DWORD SetMSAVOAAtten(double dblAtten);
	virtual DWORD GetMSAVOAAtten(double *pdblAtten);

	//~~~~~~~~SW Path~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	virtual DWORD SetLDSSelection(BYTE bySrcIndex); //1~8;SW1
													//S1~8->IN1~17
	virtual DWORD SetLDSToDutIn(BYTE byDutInIndex); //1~17;SW2+SW9
													//S1~8->Out1~18
	virtual DWORD SetLDSToDutOut(BYTE byDutOutIndex);//1~18;SW3+SW9
													 //OPM/OSA
	virtual DWORD SetLDSToMonPath(BYTE byDestPos);//1~2;SW4
	virtual DWORD SetLDSToRefPath(BYTE byDestPos);//1~2;SW2+SW4+SW5+SW9
	virtual DWORD SetDutOutToDest(BYTE byDutOutIndex, BYTE byDestPos);//SW3+SW4+SW5+SW9
	virtual DWORD SetDutInAsOutput(BYTE byDutInIndex, BYTE byDestPos);//SW2+SW4+SW5+SW9

	virtual DWORD SetDutOut98ToEO1(BYTE byDutOutIndex, BYTE byDestPos);//SW3+SW4+SW5+SW9;OUT_98 connect to EO1
	virtual DWORD SetDutIn98AsOutputToEO1(BYTE byDutInIndex, BYTE byDestPos);//SW2+SW4+SW5+SW9；OUT_98 connect to EO1
																			 //MAS IN->MAS OUT
	virtual DWORD SetMSAInToMSAOut(BYTE byMsaInPort, BYTE byMsaOutPort, double dblMsaVOAAtten); //SW6+SW7+SW8
	virtual DWORD SetMSATapToDest(BYTE byMsaOutPort, BYTE byDestPos); //SW4+SW5+SW6+SW8
	virtual DWORD SetMSAInAsOutput(BYTE byMsaInPort, BYTE byDestPos); //SW4+SW5+SW7+SW8
	virtual DWORD SetMSAOutAsOutput(BYTE byMsaOutPort, BYTE byDestPos); //SW4+SW5+SW6+SW8

	virtual DWORD SetMSAOut98AsOutputToEO2(BYTE byMsaOutPort, BYTE byDestPos); //SW4+SW5+SW6+SW8;MOP_98 connect to EO2

																			   //Expand Port
	virtual DWORD SetEOPortToDest(BYTE byEOPort, BYTE byDestPos); //EO1~3 SW4+SW5;

																  //~~~~~~~~~~~~~Trigger~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
																  //VOA Drive Trigger
	virtual DWORD SetVOATriggerOut(double dblStartAtten, double dblEndAtten, double dblStepAtten, WORD wOPMWaitTimeMs);
	//SW Drive Trigger
	virtual DWORD SetSWPathMapping(char *pchBinfileName);
	virtual DWORD SetSWTriggerPathScanStart(WORD wExitTimeOutSecond);
	//Query Scan Status
	//DWORD GetTriggerScanStatus(BYTE &byStatus);

	//~~~~~~~~GPIO Setting~~~~~~~~~~~~~~~~~~~~~~~~~~
	virtual DWORD SetGPIOConfig(DWORD dwCtrlPinBits, DWORD dwAlarmPinBits); //Bits Definition:0-Input; 1-Output;CtrlPin:32;AlarmPin:32
	virtual DWORD GetGPIOStatus(DWORD *pdwCtrlPinBits, DWORD *pdwAlarmPinBits);

	//~~~~~~~~UART Setting~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//Struct 
	//byUARTIndex =0Xff: ALL
	virtual DWORD SetUARTConfig(BYTE byUARTIndex, stSerialPortCfg stSerialPortCfgValue, DWORD dwTimeOut = 0);
	virtual DWORD WriteUARTData(BYTE byUARTIndex, BYTE* pbyBuffer, WORD wLength);
	virtual DWORD ReadUARTData(BYTE byUARTIndex, BYTE* pbyBuffer, WORD wLength, WORD *pwGetLength);

	//~~~~~~~~~BasicInfo~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//开关切换次数/校准日期/生产日期
	virtual DWORD GetDeviceInfo(pstDevInfo pstSWInfo);
	virtual DWORD GetSwitchingCnt(BYTE bySWIndex, DWORD *pdwSwitchingCnt); //只针对机械式开关

																		   //~~~~~~~~IL/WDL Value~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	virtual DWORD GetInputMinIL(BYTE bySWIndex, double * pdblGetMinIL);

	//Added 
	virtual DWORD SetBlockBySwitch(BYTE bySrcIndex); //SW1

													 //~~~~~~~~GPIO Setting~~~~~~~~~~~~~~~~~~~~~~~~~~
													 //Definition:0 - Input; 1 - Output;
													 //if wAlarmIN==0(Input),set 0~15Bits to 0; if wAlarmIN==1(Output),set 0~15Bits to 1;
													 //if wAlarmOut==0(Input),set 16~31Bits to 0; if wAlarmOut==1(Output),set 16~31Bits to 1;
	virtual DWORD SetGPIOStatus(WORD wAlarmIN, WORD wAlarmOut);
	virtual DWORD GetGPIOStatus(WORD *pwAlarmIN, WORD *pwAlarmOut);
	virtual DWORD SetGPIOVoltage(bool bVoltage5V = 1);
	//set GPIO Voltage output 5V(Default)/3.3V (bVoltage5V=0)

	//~~~~~~Just for Re-Calibration~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//ClearSwitchCnt(); //For mechanical SW EOL
	////VOA Control MFG Cmd
	//DWORD SetVOAxDAC(BYTE bInstance, WORD dwDAC);
	//DWORD GetVOAxDAC(BYTE bInstance, WORD* pwDAC);
	//DWORD GetVOAxMinIL(BYTE bInstance, double * pdbGetMinIL);
	//
	////SW Control MFG Cmd
	//DWORD SetSWDAC(BYTE bySWNum, SHORT sDACX, SHORT sDACY);
	//DWORD GetSWDAC(BYTE bySWNum, SHORT &sDACX, SHORT &sDACY);
	//DWORD SetSWTriggerDACScan(BYTE bySWNum, SHORT sStartDACX, SHORT sEndDACX, SHORT sStartDACY, SHORT sEndDACY, SHORT sStep);
private:
		char m_LastErrorMsg[1024];
		CCommunicationDLL m_DevComHandle;
};

class CSwitch1X64 :public CSwitchControl
{
public:
	CSwitch1X64();
	virtual ~CSwitch1X64();

	virtual void GetLastErrorMsg(char * errorMsg);

	virtual DWORD OpenDevice(LPCTSTR pszDeviceAddr, unsigned long *ComHandle);
	virtual DWORD CloseDevice();
	virtual DWORD SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle);

	//~~~~~~~~~General SW Control~~~~~~~~~~~~~~~~~~~~
	//Single SW Control
	virtual DWORD SetSingleSWPos(BYTE bySWIndex, //SW Number:1
		BYTE byPos);                   //Position:0~N; 0:Block position
	virtual DWORD GetSingleSWPos(BYTE bySWIndex, //SW Number:1
		BYTE &byPos);                  //Position

	virtual DWORD SetMultiSWPos(BYTE *pbyPosArray, //All SW Position:0~N,0xFF; 0xFF:Keep in place
		BYTE bySWCount);                   //SW Count
	virtual DWORD GetMultiSWPos(BYTE *pbyPosArray, //All SW Position
		BYTE bySWCount);                   //SW Count

										   //~~~~~~~~InputVOA Set~~~~~~~~~~~~~~~~~~~~~~~~~~~
										   //Input VOA Set
	virtual DWORD SetInputVOAAtten(double dblAtten);
	virtual DWORD GetInputVOAAtten(double *pdblAtten);
	//MSA VOA Set
	virtual DWORD SetMSAVOAAtten(double dblAtten);
	virtual DWORD GetMSAVOAAtten(double *pdblAtten);

	//~~~~~~~~SW Path~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	virtual DWORD SetLDSSelection(BYTE bySrcIndex); //1~8;SW1
													//S1~8->IN1~17
	virtual DWORD SetLDSToDutIn(BYTE byDutInIndex); //1~17;SW2+SW9
													//S1~8->Out1~18
	virtual DWORD SetLDSToDutOut(BYTE byDutOutIndex);//1~18;SW3+SW9
													 //OPM/OSA
	virtual DWORD SetLDSToMonPath(BYTE byDestPos);//1~2;SW4
	virtual DWORD SetLDSToRefPath(BYTE byDestPos);//1~2;SW2+SW4+SW5+SW9
	virtual DWORD SetDutOutToDest(BYTE byDutOutIndex, BYTE byDestPos);//SW3+SW4+SW5+SW9
	virtual DWORD SetDutInAsOutput(BYTE byDutInIndex, BYTE byDestPos);//SW2+SW4+SW5+SW9

	virtual DWORD SetDutOut98ToEO1(BYTE byDutOutIndex, BYTE byDestPos);//SW3+SW4+SW5+SW9;OUT_98 connect to EO1
	virtual DWORD SetDutIn98AsOutputToEO1(BYTE byDutInIndex, BYTE byDestPos);//SW2+SW4+SW5+SW9；OUT_98 connect to EO1
																			 //MAS IN->MAS OUT
	virtual DWORD SetMSAInToMSAOut(BYTE byMsaInPort, BYTE byMsaOutPort, double dblMsaVOAAtten); //SW6+SW7+SW8
	virtual DWORD SetMSATapToDest(BYTE byMsaOutPort, BYTE byDestPos); //SW4+SW5+SW6+SW8
	virtual DWORD SetMSAInAsOutput(BYTE byMsaInPort, BYTE byDestPos); //SW4+SW5+SW7+SW8
	virtual DWORD SetMSAOutAsOutput(BYTE byMsaOutPort, BYTE byDestPos); //SW4+SW5+SW6+SW8

	virtual DWORD SetMSAOut98AsOutputToEO2(BYTE byMsaOutPort, BYTE byDestPos); //SW4+SW5+SW6+SW8;MOP_98 connect to EO2

																			   //Expand Port
	virtual DWORD SetEOPortToDest(BYTE byEOPort, BYTE byDestPos); //EO1~3 SW4+SW5;

																  //~~~~~~~~~~~~~Trigger~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
																  //VOA Drive Trigger
	virtual DWORD SetVOATriggerOut(double dblStartAtten, double dblEndAtten, double dblStepAtten, WORD wOPMWaitTimeMs);
	//SW Drive Trigger
	virtual DWORD SetSWPathMapping(char *pchBinfileName);
	virtual DWORD SetSWTriggerPathScanStart(WORD wExitTimeOutSecond);
	//Query Scan Status
	//DWORD GetTriggerScanStatus(BYTE &byStatus);

	//~~~~~~~~GPIO Setting~~~~~~~~~~~~~~~~~~~~~~~~~~
	//Definition:0 - Input; 1 - Output;
	//if wAlarmIN==0(Input),set 0~15Bits to 0; if wAlarmIN==1(Output),set 0~15Bits to 1;
	//if wAlarmOut==0(Input),set 16~31Bits to 0; if wAlarmOut==1(Output),set 16~31Bits to 1;
	virtual DWORD SetGPIOStatus(WORD wAlarmIN, WORD wAlarmOut);
	virtual DWORD GetGPIOStatus(WORD *pwAlarmIN, WORD *pwAlarmOut);
	virtual DWORD SetGPIOVoltage(bool bVoltage5V = 1);
	//set GPIO Voltage output 5V(Default)/3.3V (bVoltage5V=0) 

	//~~~~~~~~UART Setting~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//Struct 
	//byUARTIndex =0Xff: ALL
	virtual DWORD SetUARTConfig(BYTE byUARTIndex, stSerialPortCfg stSerialPortCfgValue, DWORD dwTimeOut = 0);
	virtual DWORD WriteUARTData(BYTE byUARTIndex, BYTE* pbyBuffer, WORD wLength);
	virtual DWORD ReadUARTData(BYTE byUARTIndex, BYTE* pbyBuffer, WORD wLength, WORD *pwGetLength);

	//~~~~~~~~~BasicInfo~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//开关切换次数/校准日期/生产日期
	virtual DWORD GetDeviceInfo(pstDevInfo pstSWInfo);
	virtual DWORD GetSwitchingCnt(BYTE bySWIndex, DWORD *pdwSwitchingCnt); //只针对机械式开关

																		   //~~~~~~~~IL/WDL Value~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	virtual DWORD GetInputMinIL(BYTE bySWIndex, double * pdblGetMinIL);

	//Added 
	virtual DWORD SetBlockBySwitch(BYTE bySrcIndex); //SW1
private:
	CCommunicationDLL m_DevComHandle;
	char m_LastErrorMsg[1024];
	BYTE CalChecksum(BYTE* pbBuffer, int nLength);
	void AnlysisErrorString(BYTE bStatus);
};

class CBOLASwitch1XN :public CSwitchControl
{
public:
	CBOLASwitch1XN();
	virtual ~CBOLASwitch1XN();

	virtual DWORD OpenDevice(LPCTSTR pszDeviceAddr, unsigned long *ComHandle);
	virtual DWORD CloseDevice();
	virtual DWORD SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle);

	virtual void GetLastErrorMsg(char * errorMsg);

	//~~~~~~~~~General SW Control~~~~~~~~~~~~~~~~~~~~
	//Single SW Control
	virtual DWORD SetSingleSWPos(BYTE bySWIndex, //SW Number:1~2
		BYTE byPos);                   //Position:0~N; 0:Block position
	virtual DWORD GetSingleSWPos(BYTE bySWIndex, //SW Number:1~2
		BYTE &byPos);                  //Position

	virtual DWORD SetMultiSWPos(BYTE *pbyPosArray, //All SW Position:0~N,0xFF; 0xFF:Keep in place
		BYTE bySWCount);                   //SW Count
	virtual DWORD GetMultiSWPos(BYTE *pbyPosArray, //All SW Position
		BYTE bySWCount);                   //SW Count

										   //~~~~~~~~InputVOA Set~~~~~~~~~~~~~~~~~~~~~~~~~~~
										   //Input VOA Set
	virtual DWORD SetInputVOAAtten(double dblAtten);
	virtual DWORD GetInputVOAAtten(double *pdblAtten);
	//MSA VOA Set
	virtual DWORD SetMSAVOAAtten(double dblAtten);
	virtual DWORD GetMSAVOAAtten(double *pdblAtten);

	//~~~~~~~~SW Path~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	virtual DWORD SetLDSSelection(BYTE bySrcIndex); //1~8;SW1
													//S1~8->IN1~17
	virtual DWORD SetLDSToDutIn(BYTE byDutInIndex); //1~17;SW2+SW9
													//S1~8->Out1~18
	virtual DWORD SetLDSToDutOut(BYTE byDutOutIndex);//1~18;SW3+SW9
													 //OPM/OSA
	virtual DWORD SetLDSToMonPath(BYTE byDestPos);//1~2;SW4
	virtual DWORD SetLDSToRefPath(BYTE byDestPos);//1~2;SW2+SW4+SW5+SW9
	virtual DWORD SetDutOutToDest(BYTE byDutOutIndex, BYTE byDestPos);//SW3+SW4+SW5+SW9
	virtual DWORD SetDutInAsOutput(BYTE byDutInIndex, BYTE byDestPos);//SW2+SW4+SW5+SW9

	virtual DWORD SetDutOut98ToEO1(BYTE byDutOutIndex, BYTE byDestPos);//SW3+SW4+SW5+SW9;OUT_98 connect to EO1
	virtual DWORD SetDutIn98AsOutputToEO1(BYTE byDutInIndex, BYTE byDestPos);//SW2+SW4+SW5+SW9；OUT_98 connect to EO1
																			 //MAS IN->MAS OUT
	virtual DWORD SetMSAInToMSAOut(BYTE byMsaInPort, BYTE byMsaOutPort, double dblMsaVOAAtten); //SW6+SW7+SW8
	virtual DWORD SetMSATapToDest(BYTE byMsaOutPort, BYTE byDestPos); //SW4+SW5+SW6+SW8
	virtual DWORD SetMSAInAsOutput(BYTE byMsaInPort, BYTE byDestPos); //SW4+SW5+SW7+SW8
	virtual DWORD SetMSAOutAsOutput(BYTE byMsaOutPort, BYTE byDestPos); //SW4+SW5+SW6+SW8

	virtual DWORD SetMSAOut98AsOutputToEO2(BYTE byMsaOutPort, BYTE byDestPos); //SW4+SW5+SW6+SW8;MOP_98 connect to EO2

																			   //Expand Port
	virtual DWORD SetEOPortToDest(BYTE byEOPort, BYTE byDestPos); //EO1~3 SW4+SW5;

																  //~~~~~~~~~~~~~Trigger~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
																  //VOA Drive Trigger
	virtual DWORD SetVOATriggerOut(double dblStartAtten, double dblEndAtten, double dblStepAtten, WORD wOPMWaitTimeMs);
	//SW Drive Trigger
	virtual DWORD SetSWPathMapping(char *pchBinfileName);
	virtual DWORD SetSWTriggerPathScanStart(WORD wExitTimeOutSecond);
	//Query Scan Status
	//DWORD GetTriggerScanStatus(BYTE &byStatus);

	//~~~~~~~~GPIO Setting~~~~~~~~~~~~~~~~~~~~~~~~~~
	//Definition:0 - Input; 1 - Output;
	//if wAlarmIN==0(Input),set 0~15Bits to 0; if wAlarmIN==1(Output),set 0~15Bits to 1;
	//if wAlarmOut==0(Input),set 16~31Bits to 0; if wAlarmOut==1(Output),set 16~31Bits to 1;
	virtual DWORD SetGPIOStatus(WORD wAlarmIN, WORD wAlarmOut);
	virtual DWORD GetGPIOStatus(WORD *pwAlarmIN, WORD *pwAlarmOut);
	virtual DWORD SetGPIOVoltage(bool bVoltage5V = 1);
	//set GPIO Voltage output 5V(Default)/3.3V (bVoltage5V=0) 

	//~~~~~~~~UART Setting~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//Struct 
	//byUARTIndex =0Xff: ALL
	virtual DWORD SetUARTConfig(BYTE byUARTIndex, stSerialPortCfg stSerialPortCfgValue, DWORD dwTimeOut = 0);
	virtual DWORD WriteUARTData(BYTE byUARTIndex, BYTE* pbyBuffer, WORD wLength);
	virtual DWORD ReadUARTData(BYTE byUARTIndex, BYTE* pbyBuffer, WORD wLength, WORD *pwGetLength);

	//~~~~~~~~~BasicInfo~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//开关切换次数/校准日期/生产日期
	virtual DWORD GetDeviceInfo(pstDevInfo pstSWInfo);
	virtual DWORD GetSwitchingCnt(BYTE bySWIndex, DWORD *pdwSwitchingCnt); //只针对机械式开关

																		   //~~~~~~~~IL/WDL Value~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	virtual DWORD GetInputMinIL(BYTE bySWIndex, double * pdblGetMinIL);

	//Added 
	virtual DWORD SetBlockBySwitch(BYTE bySrcIndex); //SW1

private:
	CCommunicationDLL m_DevComHandle;
	char m_LastErrorMsg[1024];
	BYTE CalChecksum(BYTE* pbBuffer, int nLength);
	void AnlysisErrorString(BYTE bStatus);
};

class CDualSwitch1X68 :public CSwitchControl
{
public:
	CDualSwitch1X68();
	virtual ~CDualSwitch1X68();

	virtual DWORD OpenDevice(LPCTSTR pszDeviceAddr, unsigned long *ComHandle);
	virtual DWORD CloseDevice();
	virtual DWORD SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle);

	virtual void GetLastErrorMsg(char * errorMsg);

	//~~~~~~~~~General SW Control~~~~~~~~~~~~~~~~~~~~
	//Single SW Control
	virtual DWORD SetSingleSWPos(BYTE bySWIndex, //SW Number:1~2
		BYTE byPos);                   //Position:0~N; 0:Block position
	virtual DWORD GetSingleSWPos(BYTE bySWIndex, //SW Number:1~2
		BYTE &byPos);                  //Position

	virtual DWORD SetMultiSWPos(BYTE *pbyPosArray, //All SW Position:0~N,0xFF; 0xFF:Keep in place
		BYTE bySWCount);                   //SW Count
	virtual DWORD GetMultiSWPos(BYTE *pbyPosArray, //All SW Position
		BYTE bySWCount);                   //SW Count

										   //~~~~~~~~InputVOA Set~~~~~~~~~~~~~~~~~~~~~~~~~~~
										   //Input VOA Set
	virtual DWORD SetInputVOAAtten(double dblAtten);
	virtual DWORD GetInputVOAAtten(double *pdblAtten);
	//MSA VOA Set
	virtual DWORD SetMSAVOAAtten(double dblAtten);
	virtual DWORD GetMSAVOAAtten(double *pdblAtten);

	//~~~~~~~~SW Path~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	virtual DWORD SetLDSSelection(BYTE bySrcIndex); //1~8;SW1
													//S1~8->IN1~17
	virtual DWORD SetLDSToDutIn(BYTE byDutInIndex); //1~17;SW2+SW9
													//S1~8->Out1~18
	virtual DWORD SetLDSToDutOut(BYTE byDutOutIndex);//1~18;SW3+SW9
													 //OPM/OSA
	virtual DWORD SetLDSToMonPath(BYTE byDestPos);//1~2;SW4
	virtual DWORD SetLDSToRefPath(BYTE byDestPos);//1~2;SW2+SW4+SW5+SW9
	virtual DWORD SetDutOutToDest(BYTE byDutOutIndex, BYTE byDestPos);//SW3+SW4+SW5+SW9
	virtual DWORD SetDutInAsOutput(BYTE byDutInIndex, BYTE byDestPos);//SW2+SW4+SW5+SW9

	virtual DWORD SetDutOut98ToEO1(BYTE byDutOutIndex, BYTE byDestPos);//SW3+SW4+SW5+SW9;OUT_98 connect to EO1
	virtual DWORD SetDutIn98AsOutputToEO1(BYTE byDutInIndex, BYTE byDestPos);//SW2+SW4+SW5+SW9；OUT_98 connect to EO1
																			 //MAS IN->MAS OUT
	virtual DWORD SetMSAInToMSAOut(BYTE byMsaInPort, BYTE byMsaOutPort, double dblMsaVOAAtten); //SW6+SW7+SW8
	virtual DWORD SetMSATapToDest(BYTE byMsaOutPort, BYTE byDestPos); //SW4+SW5+SW6+SW8
	virtual DWORD SetMSAInAsOutput(BYTE byMsaInPort, BYTE byDestPos); //SW4+SW5+SW7+SW8
	virtual DWORD SetMSAOutAsOutput(BYTE byMsaOutPort, BYTE byDestPos); //SW4+SW5+SW6+SW8

	virtual DWORD SetMSAOut98AsOutputToEO2(BYTE byMsaOutPort, BYTE byDestPos); //SW4+SW5+SW6+SW8;MOP_98 connect to EO2

																			   //Expand Port
	virtual DWORD SetEOPortToDest(BYTE byEOPort, BYTE byDestPos); //EO1~3 SW4+SW5;

																  //~~~~~~~~~~~~~Trigger~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
																  //VOA Drive Trigger
	virtual DWORD SetVOATriggerOut(double dblStartAtten, double dblEndAtten, double dblStepAtten, WORD wOPMWaitTimeMs);
	//SW Drive Trigger
	virtual DWORD SetSWPathMapping(char *pchBinfileName);
	virtual DWORD SetSWTriggerPathScanStart(WORD wExitTimeOutSecond);
	//Query Scan Status
	//DWORD GetTriggerScanStatus(BYTE &byStatus);

	//~~~~~~~~GPIO Setting~~~~~~~~~~~~~~~~~~~~~~~~~~
	//Definition:0 - Input; 1 - Output;
	//if wAlarmIN==0(Input),set 0~15Bits to 0; if wAlarmIN==1(Output),set 0~15Bits to 1;
	//if wAlarmOut==0(Input),set 16~31Bits to 0; if wAlarmOut==1(Output),set 16~31Bits to 1;
	virtual DWORD SetGPIOStatus(WORD wAlarmIN, WORD wAlarmOut);
	virtual DWORD GetGPIOStatus(WORD *pwAlarmIN, WORD *pwAlarmOut);
	virtual DWORD SetGPIOVoltage(bool bVoltage5V = 1);
	//set GPIO Voltage output 5V(Default)/3.3V (bVoltage5V=0) 

	//~~~~~~~~UART Setting~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//Struct 
	//byUARTIndex =0Xff: ALL
	virtual DWORD SetUARTConfig(BYTE byUARTIndex, stSerialPortCfg stSerialPortCfgValue, DWORD dwTimeOut = 0);
	virtual DWORD WriteUARTData(BYTE byUARTIndex, BYTE* pbyBuffer, WORD wLength);
	virtual DWORD ReadUARTData(BYTE byUARTIndex, BYTE* pbyBuffer, WORD wLength, WORD *pwGetLength);

	//~~~~~~~~~BasicInfo~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//开关切换次数/校准日期/生产日期
	virtual DWORD GetDeviceInfo(pstDevInfo pstSWInfo);
	virtual DWORD GetSwitchingCnt(BYTE bySWIndex, DWORD *pdwSwitchingCnt); //只针对机械式开关

																		   //~~~~~~~~IL/WDL Value~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	virtual DWORD GetInputMinIL(BYTE bySWIndex, double * pdblGetMinIL);

	//Added 
	virtual DWORD SetBlockBySwitch(BYTE bySrcIndex); //SW1

private:
	CCommunicationDLL m_DevComHandle;
	char m_LastErrorMsg[1024];
	BYTE CalChecksum(BYTE* pbBuffer, int nLength);
	void AnlysisErrorString(BYTE bStatus);
};

class CDT08Switch1XN :public CSwitchControl
{
public:
	CDT08Switch1XN();
	virtual ~CDT08Switch1XN();

	virtual void GetLastErrorMsg(char * errorMsg);

	virtual DWORD OpenDevice(LPCTSTR pszDeviceAddr, unsigned long *ComHandle);
	virtual DWORD CloseDevice();
	virtual DWORD SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle);

	//~~~~~~~~~General SW Control~~~~~~~~~~~~~~~~~~~~
	//Single SW Control
	virtual DWORD SetSingleSWPos(BYTE bySWIndex, //SW Number:1
		BYTE byPos);                   //Position:0~N; 0:Block position
	virtual DWORD GetSingleSWPos(BYTE bySWIndex, //SW Number:1
		BYTE &byPos);                  //Position

	virtual DWORD SetMultiSWPos(BYTE *pbyPosArray, //All SW Position:0~N,0xFF; 0xFF:Keep in place
		BYTE bySWCount);                   //SW Count
	virtual DWORD GetMultiSWPos(BYTE *pbyPosArray, //All SW Position
		BYTE bySWCount);                   //SW Count

										   //~~~~~~~~InputVOA Set~~~~~~~~~~~~~~~~~~~~~~~~~~~
										   //Input VOA Set
	virtual DWORD SetInputVOAAtten(double dblAtten);
	virtual DWORD GetInputVOAAtten(double *pdblAtten);
	//MSA VOA Set
	virtual DWORD SetMSAVOAAtten(double dblAtten);
	virtual DWORD GetMSAVOAAtten(double *pdblAtten);

	//~~~~~~~~SW Path~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	virtual DWORD SetLDSSelection(BYTE bySrcIndex); //1~8;SW1
													//S1~8->IN1~17
	virtual DWORD SetLDSToDutIn(BYTE byDutInIndex); //1~17;SW2+SW9
													//S1~8->Out1~18
	virtual DWORD SetLDSToDutOut(BYTE byDutOutIndex);//1~18;SW3+SW9
													 //OPM/OSA
	virtual DWORD SetLDSToMonPath(BYTE byDestPos);//1~2;SW4
	virtual DWORD SetLDSToRefPath(BYTE byDestPos);//1~2;SW2+SW4+SW5+SW9
	virtual DWORD SetDutOutToDest(BYTE byDutOutIndex, BYTE byDestPos);//SW3+SW4+SW5+SW9
	virtual DWORD SetDutInAsOutput(BYTE byDutInIndex, BYTE byDestPos);//SW2+SW4+SW5+SW9

	virtual DWORD SetDutOut98ToEO1(BYTE byDutOutIndex, BYTE byDestPos);//SW3+SW4+SW5+SW9;OUT_98 connect to EO1
	virtual DWORD SetDutIn98AsOutputToEO1(BYTE byDutInIndex, BYTE byDestPos);//SW2+SW4+SW5+SW9；OUT_98 connect to EO1
																			 //MAS IN->MAS OUT
	virtual DWORD SetMSAInToMSAOut(BYTE byMsaInPort, BYTE byMsaOutPort, double dblMsaVOAAtten); //SW6+SW7+SW8
	virtual DWORD SetMSATapToDest(BYTE byMsaOutPort, BYTE byDestPos); //SW4+SW5+SW6+SW8
	virtual DWORD SetMSAInAsOutput(BYTE byMsaInPort, BYTE byDestPos); //SW4+SW5+SW7+SW8
	virtual DWORD SetMSAOutAsOutput(BYTE byMsaOutPort, BYTE byDestPos); //SW4+SW5+SW6+SW8

	virtual DWORD SetMSAOut98AsOutputToEO2(BYTE byMsaOutPort, BYTE byDestPos); //SW4+SW5+SW6+SW8;MOP_98 connect to EO2

																			   //Expand Port
	virtual DWORD SetEOPortToDest(BYTE byEOPort, BYTE byDestPos); //EO1~3 SW4+SW5;

																  //~~~~~~~~~~~~~Trigger~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
																  //VOA Drive Trigger
	virtual DWORD SetVOATriggerOut(double dblStartAtten, double dblEndAtten, double dblStepAtten, WORD wOPMWaitTimeMs);
	//SW Drive Trigger
	virtual DWORD SetSWPathMapping(char *pchBinfileName);
	virtual DWORD SetSWTriggerPathScanStart(WORD wExitTimeOutSecond);
	//Query Scan Status
	//DWORD GetTriggerScanStatus(BYTE &byStatus);

	//~~~~~~~~GPIO Setting~~~~~~~~~~~~~~~~~~~~~~~~~~
	//Definition:0 - Input; 1 - Output;
	//if wAlarmIN==0(Input),set 0~15Bits to 0; if wAlarmIN==1(Output),set 0~15Bits to 1;
	//if wAlarmOut==0(Input),set 16~31Bits to 0; if wAlarmOut==1(Output),set 16~31Bits to 1;
	virtual DWORD SetGPIOStatus(WORD wAlarmIN, WORD wAlarmOut);
	virtual DWORD GetGPIOStatus(WORD *pwAlarmIN, WORD *pwAlarmOut);
	virtual DWORD SetGPIOVoltage(bool bVoltage5V = 1);
	//set GPIO Voltage output 5V(Default)/3.3V (bVoltage5V=0) 

	//~~~~~~~~UART Setting~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//Struct 
	//byUARTIndex =0Xff: ALL
	virtual DWORD SetUARTConfig(BYTE byUARTIndex, stSerialPortCfg stSerialPortCfgValue, DWORD dwTimeOut = 0);
	virtual DWORD WriteUARTData(BYTE byUARTIndex, BYTE* pbyBuffer, WORD wLength);
	virtual DWORD ReadUARTData(BYTE byUARTIndex, BYTE* pbyBuffer, WORD wLength, WORD *pwGetLength);

	//~~~~~~~~~BasicInfo~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//开关切换次数/校准日期/生产日期
	virtual DWORD GetDeviceInfo(pstDevInfo pstSWInfo);
	virtual DWORD GetSwitchingCnt(BYTE bySWIndex, DWORD *pdwSwitchingCnt); //只针对机械式开关

																		   //~~~~~~~~IL/WDL Value~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	virtual DWORD GetInputMinIL(BYTE bySWIndex, double * pdblGetMinIL);

	//Added 
	virtual DWORD SetBlockBySwitch(BYTE bySrcIndex); //SW1

private:
	CCommunicationDLL m_DevComHandle;
	char m_LastErrorMsg[1024];
	BYTE CalChecksum(BYTE* pbBuffer, int nLength);
	void AnlysisErrorString(BYTE bStatus);
};

class CEDFAGeneralSwitch4th :public CSwitchControl
{
public:
	CEDFAGeneralSwitch4th();
	virtual ~CEDFAGeneralSwitch4th();

	virtual DWORD OpenDevice(LPCTSTR pszDeviceAddr, unsigned long *ComHandle);
	virtual DWORD CloseDevice();
	virtual DWORD SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle);

	virtual void GetLastErrorMsg(char * errorMsg);
	//M:Max SW Count
	//N:Max SW Port Count
	//X:Max VOA Count

	//~~~~~~~~~General SW Control~~~~~~~~~~~~~~~~~~~~
	//Single SW Control
	virtual DWORD SetSingleSWPos(BYTE bySWIndex, //SW Number:1~M,0xFF; 0xFF:All SW set to the same Position
		BYTE byPos);                   //Position:0~N; 0:Block position
	virtual DWORD GetSingleSWPos(BYTE bySWIndex, //SW Number:1~M;
		BYTE &byPos);                  //Position
									   //MultiSW Control
	virtual DWORD SetMultiSWPos(BYTE *pbyPosArray, //All SW Position:0~N,0xFF; 0xFF:Keep in place
		BYTE bySWCount);                   //SW Count
	virtual DWORD GetMultiSWPos(BYTE *pbyPosArray, //All SW Position
		BYTE bySWCount);                   //SW Count

										   //~~~~~~~~InputVOA Set~~~~~~~~~~~~~~~~~~~~~~~~~~~
										   //Input VOA Set
	virtual DWORD SetInputVOAAtten(double dblAtten);
	virtual DWORD GetInputVOAAtten(double *pdblAtten);
	//MSA VOA Set
	virtual DWORD SetMSAVOAAtten(double dblAtten);
	virtual DWORD GetMSAVOAAtten(double *pdblAtten);

	//~~~~~~~~SW Path~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	virtual DWORD SetLDSSelection(BYTE bySrcIndex); //1~8;SW1
													//S1~8->IN1~17
	virtual DWORD SetLDSToDutIn(BYTE byDutInIndex); //1~17;SW2+SW9
													//S1~8->Out1~18
	virtual DWORD SetLDSToDutOut(BYTE byDutOutIndex);//1~18;SW3+SW9
													 //OPM/OSA
	virtual DWORD SetLDSToMonPath(BYTE byDestPos);//1~2;SW4
	virtual DWORD SetLDSToRefPath(BYTE byDestPos);//1~2;SW2+SW4+SW5+SW9
	virtual DWORD SetDutOutToDest(BYTE byDutOutIndex, BYTE byDestPos);//SW3+SW4+SW5+SW9
	virtual DWORD SetDutInAsOutput(BYTE byDutInIndex, BYTE byDestPos);//SW2+SW4+SW5+SW9

	virtual DWORD SetDutOut98ToEO1(BYTE byDutOutIndex, BYTE byDestPos);//SW3+SW4+SW5+SW9;OUT_98 connect to EO1
	virtual DWORD SetDutIn98AsOutputToEO1(BYTE byDutInIndex, BYTE byDestPos);//SW2+SW4+SW5+SW9；IN_98 connect to EO1
																			 //MAS IN->MAS OUT
	virtual DWORD SetMSAInToMSAOut(BYTE byMsaInPort, BYTE byMsaOutPort, double dblMsaVOAAtten); //SW6+SW7+SW8
	virtual DWORD SetMSATapToDest(BYTE byMsaOutPort, BYTE byDestPos); //SW4+SW5+SW6+SW8
	virtual DWORD SetMSAInAsOutput(BYTE byMsaInPort, BYTE byDestPos); //SW4+SW5+SW7+SW8
	virtual DWORD SetMSAOutAsOutput(BYTE byMsaOutPort, BYTE byDestPos); //SW4+SW5+SW6+SW8

	virtual DWORD SetMSAOut98AsOutputToEO2(BYTE byMsaOutPort, BYTE byDestPos); //SW4+SW5+SW6+SW8;MOP_98 connect to EO2

																			   //Expand Port
	virtual DWORD SetEOPortToDest(BYTE byEOPort, BYTE byDestPos); //EO1~3 SW4+SW5;

																  //~~~~~~~~~~~~~Trigger~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
																  //VOA Drive Trigger
	virtual DWORD SetVOATriggerOut(double dblStartAtten, double dblEndAtten, double dblStepAtten, WORD wOPMWaitTimeMs);
	//SW Drive Trigger
	virtual DWORD SetSWPathMapping(char *pchBinfileName);
	virtual DWORD SetSWTriggerPathScanStart(WORD wExitTimeOutSecond);
	//Query Scan Status
	//DWORD GetTriggerScanStatus(BYTE &byStatus);

	//~~~~~~~~GPIO Setting~~~~~~~~~~~~~~~~~~~~~~~~~~
	//Definition:0 - Input; 1 - Output;
	//if wAlarmIN==0(Input),set 0~15Bits to 0; if wAlarmIN==1(Output),set 0~15Bits to 1;
	//if wAlarmOut==0(Input),set 16~31Bits to 0; if wAlarmOut==1(Output),set 16~31Bits to 1;
	virtual DWORD SetGPIOStatus(WORD wAlarmIN, WORD wAlarmOut);
	virtual DWORD GetGPIOStatus(WORD *pwAlarmIN, WORD *pwAlarmOut);
	virtual DWORD SetGPIOVoltage(bool bVoltage5V = 1);
	//set GPIO Voltage output 5V(Default)/3.3V (bVoltage5V=0) 

	//~~~~~~~~UART Setting~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//Struct 
	//byUARTIndex =0Xff: ALL
	virtual DWORD SetUARTConfig(BYTE byUARTIndex, stSerialPortCfg stSerialPortCfgValue, DWORD dwTimeOut = 0);
	virtual DWORD WriteUARTData(BYTE byUARTIndex, BYTE* pbyBuffer, WORD wLength);
	virtual DWORD ReadUARTData(BYTE byUARTIndex, BYTE* pbyBuffer, WORD wLength, WORD *pwGetLength);

	//~~~~~~~~~BasicInfo~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//开关切换次数/校准日期/生产日期
	virtual DWORD GetDeviceInfo(pstDevInfo pstSWInfo);
	virtual DWORD GetSwitchingCnt(BYTE bySWIndex, DWORD *pdwSwitchingCnt); //只针对机械式开关

																		   //~~~~~~~~IL/WDL Value~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	virtual DWORD GetInputMinIL(BYTE bySWIndex, double * pdblGetMinIL);

	//Added 
	virtual DWORD SetBlockBySwitch(BYTE bySrcIndex); //SW1

private:
	CCommunicationDLL m_DevComHandle;
	char m_LastErrorMsg[1024];
	BYTE CalChecksum(BYTE* pbBuffer, int nLength);
	void AnlysisErrorString(BYTE bStatus);

	//~~~~~~Just for Re-Calibration~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//ClearSwitchCnt(); //For mechanical SW EOL
	////VOA Control MFG Cmd
	//DWORD SetVOAxDAC(BYTE bInstance, WORD dwDAC);
	//DWORD GetVOAxDAC(BYTE bInstance, WORD* pwDAC);
	//DWORD GetVOAxMinIL(BYTE bInstance, double * pdbGetMinIL);
	//
	////SW Control MFG Cmd
	//DWORD SetSWDAC(BYTE bySWNum, SHORT sDACX, SHORT sDACY);
	//DWORD GetSWDAC(BYTE bySWNum, SHORT &sDACX, SHORT &sDACY);
	//DWORD SetSWTriggerDACScan(BYTE bySWNum, SHORT sStartDACX, SHORT sEndDACX, SHORT sStartDACY, SHORT sEndDACY, SHORT sStep);
};

class CThreeSwitch1X18 :public CSwitchControl
{
public:
	CThreeSwitch1X18();
	virtual ~CThreeSwitch1X18();

	virtual DWORD OpenDevice(LPCTSTR pszDeviceAddr, unsigned long *ComHandle);
	virtual DWORD CloseDevice();
	virtual DWORD SetHandle(LPCTSTR pszDeviceAddr, unsigned long handle);


	virtual void GetLastErrorMsg(char * errorMsg);

	//~~~~~~~~~General SW Control~~~~~~~~~~~~~~~~~~~~
	//Single SW Control
	virtual DWORD SetSingleSWPos(BYTE bySWIndex, //SW Number:1
		BYTE byPos);                   //Position:0~N; 0:Block position
	virtual DWORD GetSingleSWPos(BYTE bySWIndex, //SW Number:1
		BYTE &byPos);                  //Position

	virtual DWORD SetMultiSWPos(BYTE *pbyPosArray, //All SW Position:0~N,0xFF; 0xFF:Keep in place
		BYTE bySWCount);                   //SW Count
	virtual DWORD GetMultiSWPos(BYTE *pbyPosArray, //All SW Position
		BYTE bySWCount);                   //SW Count
        								   //~~~~~~~~InputVOA Set~~~~~~~~~~~~~~~~~~~~~~~~~~~
										   //Input VOA Set
	virtual DWORD SetInputVOAAtten(double dblAtten);
	virtual DWORD GetInputVOAAtten(double *pdblAtten);
	//MSA VOA Set
	virtual DWORD SetMSAVOAAtten(double dblAtten);
	virtual DWORD GetMSAVOAAtten(double *pdblAtten);

	//~~~~~~~~SW Path~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	virtual DWORD SetLDSSelection(BYTE bySrcIndex); //1~8;SW1
													//S1~8->IN1~17
	virtual DWORD SetLDSToDutIn(BYTE byDutInIndex); //1~17;SW2+SW9
													//S1~8->Out1~18
	virtual DWORD SetLDSToDutOut(BYTE byDutOutIndex);//1~18;SW3+SW9
													 //OPM/OSA
	virtual DWORD SetLDSToMonPath(BYTE byDestPos);//1~2;SW4
	virtual DWORD SetLDSToRefPath(BYTE byDestPos);//1~2;SW2+SW4+SW5+SW9
	virtual DWORD SetDutOutToDest(BYTE byDutOutIndex, BYTE byDestPos);//SW3+SW4+SW5+SW9
	virtual DWORD SetDutInAsOutput(BYTE byDutInIndex, BYTE byDestPos);//SW2+SW4+SW5+SW9

	virtual DWORD SetDutOut98ToEO1(BYTE byDutOutIndex, BYTE byDestPos);//SW3+SW4+SW5+SW9;OUT_98 connect to EO1
	virtual DWORD SetDutIn98AsOutputToEO1(BYTE byDutInIndex, BYTE byDestPos);//SW2+SW4+SW5+SW9；OUT_98 connect to EO1
																			 //MAS IN->MAS OUT
	virtual DWORD SetMSAInToMSAOut(BYTE byMsaInPort, BYTE byMsaOutPort, double dblMsaVOAAtten); //SW6+SW7+SW8
	virtual DWORD SetMSATapToDest(BYTE byMsaOutPort, BYTE byDestPos); //SW4+SW5+SW6+SW8
	virtual DWORD SetMSAInAsOutput(BYTE byMsaInPort, BYTE byDestPos); //SW4+SW5+SW7+SW8
	virtual DWORD SetMSAOutAsOutput(BYTE byMsaOutPort, BYTE byDestPos); //SW4+SW5+SW6+SW8

	virtual DWORD SetMSAOut98AsOutputToEO2(BYTE byMsaOutPort, BYTE byDestPos); //SW4+SW5+SW6+SW8;MOP_98 connect to EO2

																			   //Expand Port
	virtual DWORD SetEOPortToDest(BYTE byEOPort, BYTE byDestPos); //EO1~3 SW4+SW5;

																  //~~~~~~~~~~~~~Trigger~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
																  //VOA Drive Trigger
	virtual DWORD SetVOATriggerOut(double dblStartAtten, double dblEndAtten, double dblStepAtten, WORD wOPMWaitTimeMs);
	//SW Drive Trigger
	virtual DWORD SetSWPathMapping(char *pchBinfileName);
	virtual DWORD SetSWTriggerPathScanStart(WORD wExitTimeOutSecond);
	//Query Scan Status
	//DWORD GetTriggerScanStatus(BYTE &byStatus);

	//~~~~~~~~GPIO Setting~~~~~~~~~~~~~~~~~~~~~~~~~~
	//Definition:0 - Input; 1 - Output;
	//if wAlarmIN==0(Input),set 0~15Bits to 0; if wAlarmIN==1(Output),set 0~15Bits to 1;
	//if wAlarmOut==0(Input),set 16~31Bits to 0; if wAlarmOut==1(Output),set 16~31Bits to 1;
	virtual DWORD SetGPIOStatus(WORD wAlarmIN, WORD wAlarmOut);
	virtual DWORD GetGPIOStatus(WORD *pwAlarmIN, WORD *pwAlarmOut);
	virtual DWORD SetGPIOVoltage(bool bVoltage5V = 1);
	//set GPIO Voltage output 5V(Default)/3.3V (bVoltage5V=0) 

	//~~~~~~~~UART Setting~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//Struct 
	//byUARTIndex =0Xff: ALL
	virtual DWORD SetUARTConfig(BYTE byUARTIndex, stSerialPortCfg stSerialPortCfgValue, DWORD dwTimeOut = 0);
	virtual DWORD WriteUARTData(BYTE byUARTIndex, BYTE* pbyBuffer, WORD wLength);
	virtual DWORD ReadUARTData(BYTE byUARTIndex, BYTE* pbyBuffer, WORD wLength, WORD *pwGetLength);

	//~~~~~~~~~BasicInfo~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//开关切换次数/校准日期/生产日期
	virtual DWORD GetDeviceInfo(pstDevInfo pstSWInfo);
	virtual DWORD GetSwitchingCnt(BYTE bySWIndex, DWORD *pdwSwitchingCnt); //只针对机械式开关

																		   //~~~~~~~~IL/WDL Value~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	virtual DWORD GetInputMinIL(BYTE bySWIndex, double * pdblGetMinIL);

	//Added 
	virtual DWORD SetBlockBySwitch(BYTE bySrcIndex); //SW1

private:
	CCommunicationDLL m_DevComHandle;
	char m_LastErrorMsg[1024];
	BYTE CalChecksum(BYTE* pbBuffer, int nLength);
	void AnlysisErrorString(BYTE bStatus);
};


#endif // !defined(AFX_PMCONTROL_H__8F680F2C_8DBB_4C0B_9B88_30A551A22F82__INCLUDED_)