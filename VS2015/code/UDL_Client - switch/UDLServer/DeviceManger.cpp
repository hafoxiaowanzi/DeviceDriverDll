// DeviceManger.cpp: implementation of the CDeviceManger class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "DeviceManger.h"
//#include "tinyxml.h"
#include "Markup.h"

#define PDLSCANCOUNT 4

#pragma  comment(lib,"..\\lib\\UDL.Communication.lib")
#pragma  comment(lib,"..\\lib\\UDL.TLS.lib")
#pragma  comment(lib,"..\\lib\\UDL.PM.lib")
#pragma  comment(lib,"..\\lib\\UDL.OSA.lib")
#pragma  comment(lib,"..\\lib\\UDL.VOA.lib")
#pragma  comment(lib,"..\\lib\\UDL.Pol.lib")
#pragma  comment(lib,"..\\lib\\UDL.Chamber.lib")
#pragma  comment(lib,"..\\lib\\UDL.Switch.lib")

#pragma  comment(lib,"ws2_32.lib")

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDeviceManger::CDeviceManger()
{
	m_ptrMainFrame =NULL;
	m_nDeviceCount = 0;
	m_nTLSCount=0;
	m_nPMCount=0;
	m_nVOACount=0;
	m_nOSACount=0;
	m_nPolCount =0;
	m_nChamberCount =0;
	m_nComDev = 0;
	m_strErrorMsg = _T("No error");
	m_ctrlTLS.clear();
	m_ctrlPM.clear();
	m_ctrlVOA.clear();
	m_ctrlOSA.clear();
	m_ctrlPOL.clear();
	m_ctrlChamber.clear();
	m_ctrlComDev.clear();
	m_ctrlSwitch.clear();
	m_pstRefScanData = NULL;
	m_pstDoScanData = NULL;
	m_stScanData.m_pdblWavelengthArray =NULL;
	m_stScanData.m_pdwDataArrayAddr =NULL;
	m_bUseNet = FALSE;
	m_conn = INVALID_SOCKET;
}

CDeviceManger::~CDeviceManger()
{
	if(m_bUseNet)
	{
		closesocket(m_conn);
		m_conn =-1;
	}
	if (m_ptrMainFrame!=NULL)
	{
		delete [] m_ptrMainFrame;
		m_ptrMainFrame = NULL;
	}
	if(m_pstRefScanData !=NULL)
	{
		ReleaseAllocStruct(m_pstRefScanData);
	}
	if(m_pstDoScanData !=NULL)
	{
		ReleaseAllocStruct(m_pstDoScanData);
	}
	
	ReleaseAllocStruct(&m_stScanData);
	
	DestoryDevObject();	
}

////////////////////////////////////////////////////////////////
//函数说明：
//初始化，创建设备对象
//Add by haox
//Time：20140610
////////////////////////////////////////////////////////////////
BOOL CDeviceManger::InitDevObject()
{
	DestoryDevObject();
	m_ctrlTLS.clear();
	m_ctrlPM.clear();
	m_ctrlVOA.clear();
	m_ctrlOSA.clear();
	m_ctrlPOL.clear();
	m_ctrlChamber.clear();
	m_ctrlComDev.clear();	
	m_ctrlSwitch.clear();

	return TRUE;
}

////////////////////////////////////////////////////////////////
//函数说明：
//释放设备对象
//Add by haox
//Time：20140610
////////////////////////////////////////////////////////////////
void CDeviceManger::DestoryDevObject()
{	
	for (int i=0; i<m_ctrlTLS.size(); i++)
	{
		if (m_ctrlTLS[i]!=NULL)
		{
			m_ctrlTLS[i]->CloseDevice();
			delete m_ctrlTLS[i];
			m_ctrlTLS[i] = NULL;
		}		
	}
	
	for (i=0; i<m_ctrlPM.size(); i++)
	{				
		if (m_ctrlPM[i] !=NULL)
		{
			m_ctrlPM[i]->CloseDevice();
			delete m_ctrlPM[i];
			m_ctrlPM[i] = NULL;
		}								
	}
	
	for (i=0; i<m_ctrlVOA.size(); i++)
	{
		if (m_ctrlVOA[i] !=NULL) 
		{
			m_ctrlVOA[i]->CloseDevice();
			delete m_ctrlVOA[i];
			m_ctrlVOA[i]=NULL;
		}
		
	}
	
	for (i=0; i<m_ctrlOSA.size(); i++)
	{
		if (m_ctrlOSA[i]!=NULL)
		{
			m_ctrlOSA[i]->CloseDevice();
			delete m_ctrlOSA[i];
			m_ctrlOSA[i] = NULL;
		}
		
	}
	for (i=0; i<m_ctrlPOL.size(); i++)
	{
		if (m_ctrlPOL[i]!=NULL)
		{
			m_ctrlPOL[i]->CloseDevice();
			delete m_ctrlPOL[i];
			m_ctrlPOL[i] = NULL;
		}		
	}	
	for (i=0;i<m_ctrlChamber.size();i++)
	{
		if (m_ctrlChamber[i]!=NULL)
		{
			m_ctrlChamber[i]->CloseDevice();
			delete m_ctrlChamber[i];
			m_ctrlChamber[i]= NULL;
		}
	}
	
	for (i=0;i<m_ctrlComDev.size();i++)
	{
		if (m_ctrlComDev[i]!=NULL)
		{
			m_ctrlComDev[i]->CloseDevice();
			delete m_ctrlComDev[i];
			m_ctrlComDev[i]= NULL;
		}
	}	
	for(i=0;i<m_ctrlSwitch.size();i++)
	{
		if (m_ctrlSwitch[i]!=NULL)
		{
			m_ctrlSwitch[i]->CloseDevice();
			delete m_ctrlSwitch[i];
			m_ctrlSwitch[i]= NULL;
		}
	}
}


BOOL CDeviceManger::TestWriteFile()
{
	FILE * fPFile = NULL;
	char szPath[MAX_PATH];
	sprintf(szPath, "C:\\Public-T\\a.txt");
	//AFX_MANAGE_STATE(AfxGetStaticModuleState());
//	AfxMessageBox(szPath);
	fPFile = fopen(szPath, "a+");
	if (fPFile == NULL)
	{
		return ERROR_OSAMEARSOUREMODE1;
	}

	fprintf(fPFile, "aaaaa\n");
	fclose(fPFile);
	return SUCCESS;
}

////////////////////////////////////////////////////////////////
//函数说明：
//    加载设备XML文件，读取XML内容。同时根据读取到的设备数量
//开辟初始化函数内存
//Add by wanxin
//Time：20140303
////////////////////////////////////////////////////////////////
BOOL CDeviceManger::LoadConfigXML(LPCSTR lpstrFileName)
{
	CMarkup m_xml;
	//CString strFilaName;
	CString strTemp,strAttribute;
	int nTLSIndex =0 ,nPMIndex=0,nVOAIndex=0,nOSAIndex=0;
	int nPOLIndex=0,nChamberIndex=0,nComDevIndex=0;
	//strFilaName.Format("%s\\ConfigurationWizard.xml",m_strAppFolder);
	m_nTLSCount = 0;
	m_nPMCount = 0;
	m_nVOACount  = 0;
	m_nOSACount =0;
	m_nPolCount =0;
	m_nChamberCount =0;
	m_strErrorMsg =_T("No Error!");
	//TestWriteFile();
	if(m_bUseNet)
	{		
		//strTemp= ExtractFileName(lpstrFileName);
		if(!LoadConfigXMLForNET(lpstrFileName))
		{
			m_strErrorMsg =_T("Load Device XML File Error!");
			return FALSE;
		}
		return TRUE;
	}
	if(!m_xml.Load(lpstrFileName))
	{
		m_strErrorMsg =_T("Load Device XML File Error!");
		return FALSE;
	}
	
	m_xml.ResetPos();
    m_xml.IntoElem();
	if (m_xml.FindElem("MIMSUDL"))
	{
		//m_xml.IntoElem();
		m_xml.ResetChildPos();
		if (m_xml.FindChildElem("Property"))
		{
			m_xml.IntoElem();
			strAttribute = m_xml.GetAttrib("Name");
			if (strAttribute.CompareNoCase("DeviceConfig") ==0)
			{
				strAttribute = m_xml.GetAttrib("DeviceCount");
				m_nDeviceCount = atoi(strAttribute);
				if (m_nDeviceCount ==0)
				{
					m_strErrorMsg =_T("No Device in Read!");
					return FALSE;
				}
				if (m_ptrMainFrame!=NULL)
				{
					delete [] m_ptrMainFrame;
					m_ptrMainFrame = NULL;
				}
				m_ptrMainFrame = new stMainFrame[m_nDeviceCount];
				memset(m_ptrMainFrame, 0, sizeof(stMainFrame)*m_nDeviceCount);
				for (int nx=0;nx< m_nDeviceCount;nx++)
				{
					m_ptrMainFrame[nx].bMainFrameIsOPen =FALSE;
				}
				
				m_xml.ResetChildPos();
				for (int i=0;i<m_nDeviceCount;i++)
				{
					if (m_xml.FindChildElem("Device"))
					{
						m_xml.IntoElem();
						strAttribute = m_xml.GetAttrib("MainFrame");
						lstrcpy(m_ptrMainFrame[i].strCaption, strAttribute);
						
						strAttribute = m_xml.GetAttrib("nIndex");
						m_ptrMainFrame[i].nIndex = atoi(strAttribute);
						
						strAttribute = m_xml.GetAttrib("code");
						lstrcpy(m_ptrMainFrame[i].strCode, strAttribute);
						
						strAttribute = m_xml.GetAttrib("HWVesion");
						lstrcpy(m_ptrMainFrame[i].strHWVersion, strAttribute);
						
						strAttribute = m_xml.GetAttrib("FWVersion");
						lstrcpy(m_ptrMainFrame[i].strFWVersion, strAttribute);
						
						strAttribute = m_xml.GetAttrib("SN");
						lstrcpy(m_ptrMainFrame[i].strSN, strAttribute);
						
						m_xml.ResetChildPos();
						if(m_xml.FindChildElem("Item"))
						{
							m_xml.IntoElem();
							strAttribute = m_xml.GetAttrib("Online");
							m_ptrMainFrame[i].nOnLine = atoi(strAttribute);
							strAttribute = m_xml.GetAttrib("ComType");
							
							if (strAttribute.CompareNoCase("GPIB")==0)
							{
								m_ptrMainFrame[i].nComType= T_GPIB;
							}
							else if (strAttribute.CompareNoCase("SERIAL")==0) 
							{
								m_ptrMainFrame[i].nComType= T_SERIAL;
							}
							else if(strAttribute.CompareNoCase("LAN")==0)
							{
								m_ptrMainFrame[i].nComType= T_NET;
							}
							else if (strAttribute.CompareNoCase("USB")==0)
							{
								m_ptrMainFrame[i].nComType= T_USB;
							}
							else
							{
								m_strErrorMsg =_T("The Com Type Setting Error!");										
								return FALSE;
							}
							strAttribute = m_xml.GetAttrib("ComID");
							m_ptrMainFrame[i].nDevID = atoi(strAttribute);
							strAttribute = m_xml.GetAttrib("Address");
							lstrcpy(m_ptrMainFrame[i].strAddress, strAttribute);
							m_xml.OutOfElem();
						}
						else
						{
							m_strErrorMsg =_T("Read Device Manager File Error!");
							return FALSE;
						}
						
						if(m_xml.FindChildElem("Item"))
						{
							m_xml.IntoElem();
							strAttribute = m_xml.GetAttrib("SlotCount");
							m_ptrMainFrame[i].nSlotCount = atoi(strAttribute);
							strAttribute = m_xml.GetAttrib("BeginSlot");
							m_ptrMainFrame[i].nBeginSlotIndex = atoi(strAttribute);
							m_xml.OutOfElem();
						}
						else
						{
							m_strErrorMsg =_T("Read Device Manager File Error!");
							return FALSE;
						}
						
						for (int j=0;j<m_ptrMainFrame[i].nSlotCount;j++)
						{
							if(m_xml.FindChildElem("Slot"))
							{
								m_xml.IntoElem();								
								strAttribute = m_xml.GetAttrib("UseType");								
								if (strAttribute.CompareNoCase("TLS")==0)
								{
									strAttribute = m_xml.GetAttrib("Used");
									int nUse = atoi(strAttribute);
									if(nUse !=1)
									{
										m_xml.OutOfElem();
										continue;
									}
									int nSlotType = TAG_TLS;
									int nDevIndex = m_ptrMainFrame[i].nIndex;
									strAttribute = m_xml.GetAttrib("Index");
									int nCurSlotIndex = atoi(strAttribute);
									strAttribute = m_xml.GetAttrib("Caption");
									CString strCaption = strAttribute;
									strAttribute = m_xml.GetAttrib("HWVesino");
									CString strHWVersion = strAttribute;
									strAttribute = m_xml.GetAttrib("FWVesion");
									CString strFWVersion = strAttribute;
									strAttribute = m_xml.GetAttrib("SN");
									CString strSN = strAttribute;
									strAttribute = m_xml.GetAttrib("ChannelCount");
									int nChannelCount = atoi(strAttribute);
	
									if (nChannelCount >0 )
									{																				
										for (int m=0;m<nChannelCount;m++)
										{
											
											m_pTLSSlotInfo[nTLSIndex].nSlotType = TAG_TLS;									
											m_pTLSSlotInfo[nTLSIndex].nDevIndex = nDevIndex ;
											m_pTLSSlotInfo[nTLSIndex].nOnline = nUse;
											m_pTLSSlotInfo[nTLSIndex].nConfigIndex = nCurSlotIndex;
											m_pTLSSlotInfo[nTLSIndex].strCaption = strCaption;
											m_pTLSSlotInfo[nTLSIndex].strHWVersion = strHWVersion;
											m_pTLSSlotInfo[nTLSIndex].strFWVersion = strFWVersion;
											m_pTLSSlotInfo[nTLSIndex].strSN = strSN;
											m_pTLSSlotInfo[nTLSIndex].nChanelCout = nChannelCount;
											m_pTLSSlotInfo[nTLSIndex].nCurSlotIndex = nCurSlotIndex;
											m_pTLSSlotInfo[nTLSIndex].nLogicalChannel = nTLSIndex;
											
											if(m_xml.FindChildElem("Channel"))
											{
												m_xml.IntoElem();
												strAttribute = m_xml.GetAttrib("Used");
												int nUse = atoi(strAttribute);
												if(nUse !=1)
												{
													m_xml.OutOfElem();
													continue;
												}													
												
												strAttribute = m_xml.GetAttrib("Index");
												m_pTLSSlotInfo[nTLSIndex].chInfo.nCurChannel = atoi(strAttribute);
												strAttribute = m_xml.GetAttrib("Type");
												m_pTLSSlotInfo[nTLSIndex].chInfo.strType = strAttribute;
												m_pTLSSlotInfo[nTLSIndex].chInfo.nOnline = nUse;	
												m_xml.OutOfElem();
											}
											++nTLSIndex;
											m_nTLSCount = nTLSIndex;
										}
									}										
								}
								else if(strAttribute.CompareNoCase("PM")==0)
								{
									strAttribute = m_xml.GetAttrib("Used");
									int nUse = atoi(strAttribute);
									if(nUse !=1)
									{
										m_xml.OutOfElem();
										continue;
									}

		                            int nSlotType = TAG_PM;
									int nDevIndex = m_ptrMainFrame[i].nIndex;
									strAttribute = m_xml.GetAttrib("Index");
									int nCurSlotIndex = atoi(strAttribute);
									strAttribute = m_xml.GetAttrib("Caption");
									CString strCaption = strAttribute;
									strAttribute = m_xml.GetAttrib("HWVesino");
									CString strHWVersion = strAttribute;
									strAttribute = m_xml.GetAttrib("FWVesion");
									CString strFWVersion = strAttribute;
									strAttribute = m_xml.GetAttrib("SN");
									CString strSN = strAttribute;
									strAttribute = m_xml.GetAttrib("ChannelCount");
									int nChannelCount = atoi(strAttribute);
									
									if (nChannelCount >0 )
									{
										for (int m=0;m<nChannelCount;m++)
										{
											m_pPMSlotInfo[nPMIndex].nSlotType = nSlotType;
											m_pPMSlotInfo[nPMIndex].nDevIndex = nDevIndex;
											m_pPMSlotInfo[nPMIndex].nConfigIndex = nCurSlotIndex;
											m_pPMSlotInfo[nPMIndex].nOnline = nUse;
											m_pPMSlotInfo[nPMIndex].strCaption = strCaption;
											m_pPMSlotInfo[nPMIndex].strHWVersion = strHWVersion;
											m_pPMSlotInfo[nPMIndex].strFWVersion = strFWVersion;
											m_pPMSlotInfo[nPMIndex].strSN = strSN;
											m_pPMSlotInfo[nPMIndex].nChanelCout = nChannelCount;                                    										
											m_pPMSlotInfo[nPMIndex].nCurSlotIndex = nCurSlotIndex;//j + m_ptrMainFrame[i].nBeginSlotIndex;																				
											m_pPMSlotInfo[nPMIndex].nLogicalChannel = nPMIndex;
											
											if(m_xml.FindChildElem("Channel"))
											{
												m_xml.IntoElem();
												strAttribute = m_xml.GetAttrib("Used");
												int nUse = atoi(strAttribute);
												if(nUse !=1)
												{
													m_xml.OutOfElem();
													continue;
												}
												strAttribute = m_xml.GetAttrib("Index");
												m_pPMSlotInfo[nPMIndex].chInfo.nCurChannel = atoi(strAttribute);
												strAttribute = m_xml.GetAttrib("Type");
												m_pPMSlotInfo[nPMIndex].chInfo.strType = strAttribute;
												strAttribute = m_xml.GetAttrib("Used");
												m_pPMSlotInfo[nPMIndex].chInfo.nOnline = atoi(strAttribute);	
												m_xml.OutOfElem();
											}

											++nPMIndex;
											m_nPMCount = nPMIndex;
										}
									}
								}
								else if(strAttribute.CompareNoCase("VOA")==0)
								{
									strAttribute = m_xml.GetAttrib("Used");
									int nUse = atoi(strAttribute);
									if(nUse !=1)
									{
										m_xml.OutOfElem();
										continue;
									}

					                int nSlotType = TAG_VOA;
									int nDevIndex = m_ptrMainFrame[i].nIndex;
									strAttribute = m_xml.GetAttrib("Index");
									int nCurSlotIndex = atoi(strAttribute);
									strAttribute = m_xml.GetAttrib("Caption");
									CString strCaption = strAttribute;
									strAttribute = m_xml.GetAttrib("HWVesino");
									CString strHWVersion = strAttribute;
									strAttribute = m_xml.GetAttrib("FWVesion");
									CString strFWVersion = strAttribute;
									strAttribute = m_xml.GetAttrib("SN");
									CString strSN = strAttribute;
									strAttribute = m_xml.GetAttrib("ChannelCount");
									int nChannelCount = atoi(strAttribute);									
									
									if (nChannelCount >0 )
									{
										for (int m=0;m<nChannelCount;m++)
										{											
											m_pVOASlotInfo[nVOAIndex].nSlotType = nSlotType;							
											m_pVOASlotInfo[nVOAIndex].nDevIndex = nDevIndex;
											m_pVOASlotInfo[nVOAIndex].nConfigIndex = nCurSlotIndex;
											m_pVOASlotInfo[nVOAIndex].nOnline = nUse;
											m_pVOASlotInfo[nVOAIndex].strCaption = strCaption;
											m_pVOASlotInfo[nVOAIndex].strHWVersion = strHWVersion;
											m_pVOASlotInfo[nVOAIndex].strFWVersion = strFWVersion;
											m_pVOASlotInfo[nVOAIndex].strSN = strSN;
											m_pVOASlotInfo[nVOAIndex].nChanelCout = nChannelCount;
											m_pVOASlotInfo[nVOAIndex].nCurSlotIndex = nCurSlotIndex;
											m_pVOASlotInfo[nVOAIndex].nLogicalChannel = nVOAIndex;

											if(m_xml.FindChildElem("Channel"))
											{
												m_xml.IntoElem();
												int nUse = atoi(strAttribute);
												if(nUse !=1)
												{
													m_xml.OutOfElem();
													continue;
												}
												strAttribute = m_xml.GetAttrib("Index");
												m_pVOASlotInfo[nVOAIndex].chInfo.nCurChannel = atoi(strAttribute);
												strAttribute = m_xml.GetAttrib("Type");
												m_pVOASlotInfo[nVOAIndex].chInfo.strType = strAttribute;
												strAttribute = m_xml.GetAttrib("Used");
												m_pVOASlotInfo[nVOAIndex].chInfo.nOnline = atoi(strAttribute);	
												m_xml.OutOfElem();
											}	
											
											++nVOAIndex;
											m_nVOACount = nVOAIndex;
										}										
									}
								}
								else if(strAttribute.CompareNoCase("OSA")==0)
								{
									strAttribute = m_xml.GetAttrib("Used");
									int nUse = atoi(strAttribute);
									if(nUse !=1)
									{
										m_xml.OutOfElem();
										continue;
									}

								    int nSlotType = TAG_OSA;
									int nDevIndex = m_ptrMainFrame[i].nIndex;
									strAttribute = m_xml.GetAttrib("Index");
									int nCurSlotIndex = atoi(strAttribute);
									strAttribute = m_xml.GetAttrib("Caption");
									CString strCaption = strAttribute;
									strAttribute = m_xml.GetAttrib("HWVesino");
									CString strHWVersion = strAttribute;
									strAttribute = m_xml.GetAttrib("FWVesion");
									CString strFWVersion = strAttribute;
									strAttribute = m_xml.GetAttrib("SN");
									CString strSN = strAttribute;
									strAttribute = m_xml.GetAttrib("ChannelCount");
									int nChannelCount = atoi(strAttribute);
									
									if (nChannelCount >0 )
									{
										for (int m=0;m<nChannelCount;m++)
										{
											
											m_pOSASlotInfo[nOSAIndex].nSlotType = nSlotType;
											m_pOSASlotInfo[nOSAIndex].nDevIndex = nDevIndex;								
											m_pOSASlotInfo[nOSAIndex].nConfigIndex = nCurSlotIndex;
											m_pOSASlotInfo[nOSAIndex].nOnline = nUse;
											m_pOSASlotInfo[nOSAIndex].strCaption = strCaption;
											m_pOSASlotInfo[nOSAIndex].strHWVersion = strHWVersion;
											m_pOSASlotInfo[nOSAIndex].strFWVersion = strFWVersion;
											m_pOSASlotInfo[nOSAIndex].strSN = strSN;
											m_pOSASlotInfo[nOSAIndex].nChanelCout = nChannelCount;
											m_pOSASlotInfo[nOSAIndex].nCurSlotIndex = nCurSlotIndex;									
											m_pOSASlotInfo[nOSAIndex].nLogicalChannel = nOSAIndex;
											
											if(m_xml.FindChildElem("Channel"))
											{
												m_xml.IntoElem();
												strAttribute = m_xml.GetAttrib("Used");
												int nUse = atoi(strAttribute);
												if(nUse !=1)
												{
													m_xml.OutOfElem();
													continue;
												}
												strAttribute = m_xml.GetAttrib("Index");
												m_pOSASlotInfo[nOSAIndex].chInfo.nCurChannel = atoi(strAttribute);
												strAttribute = m_xml.GetAttrib("Type");
												m_pOSASlotInfo[nOSAIndex].chInfo.strType = strAttribute;
												strAttribute = m_xml.GetAttrib("Used");
												m_pOSASlotInfo[nOSAIndex].chInfo.nOnline = atoi(strAttribute);	
												m_xml.OutOfElem();
											}
											++nOSAIndex;
											m_nOSACount = nOSAIndex;											
										}										
									}																		
								}//偏振控制器								
								else if(strAttribute.CompareNoCase("PDL")==0)
								{
									strAttribute = m_xml.GetAttrib("Used");
									int nUse = atoi(strAttribute);
									if(nUse !=1)
									{
										m_xml.OutOfElem();
										continue;
									}

								    int nSlotType = TAG_POL;
									int nDevIndex = m_ptrMainFrame[i].nIndex;
									strAttribute = m_xml.GetAttrib("Index");
									int nCurSlotIndex = atoi(strAttribute);
									strAttribute = m_xml.GetAttrib("Caption");
									CString strCaption = strAttribute;
									strAttribute = m_xml.GetAttrib("HWVesino");
									CString strHWVersion = strAttribute;
									strAttribute = m_xml.GetAttrib("FWVesion");
									CString strFWVersion = strAttribute;
									strAttribute = m_xml.GetAttrib("SN");
									CString strSN = strAttribute;
									strAttribute = m_xml.GetAttrib("ChannelCount");
									int nChannelCount = atoi(strAttribute);
								
									if (nChannelCount >0 )
									{
										for (int m=0;m<nChannelCount;m++)
										{
											m_pPOLSlotInfo[nPOLIndex].nSlotType = nSlotType;
											m_pPOLSlotInfo[nPOLIndex].nDevIndex = nDevIndex;								
											m_pPOLSlotInfo[nPOLIndex].nConfigIndex = nCurSlotIndex;
											m_pPOLSlotInfo[nPOLIndex].nOnline = nUse;
											m_pPOLSlotInfo[nPOLIndex].strCaption = strCaption;
											m_pPOLSlotInfo[nPOLIndex].strHWVersion = strHWVersion;
											m_pPOLSlotInfo[nPOLIndex].strFWVersion = strFWVersion;
											m_pPOLSlotInfo[nPOLIndex].strSN = strSN;
											m_pPOLSlotInfo[nPOLIndex].nChanelCout = nChannelCount;
											m_pPOLSlotInfo[nPOLIndex].nCurSlotIndex = nCurSlotIndex;								
											m_pPOLSlotInfo[nPOLIndex].nLogicalChannel = nPOLIndex;	

											if(m_xml.FindChildElem("Channel"))
											{
												m_xml.IntoElem();
												strAttribute = m_xml.GetAttrib("Used");
												int nUse = atoi(strAttribute);
												if(nUse !=1)
												{
													m_xml.OutOfElem();
													continue;
												}
												strAttribute = m_xml.GetAttrib("Index");
												m_pPOLSlotInfo[nPOLIndex].chInfo.nCurChannel = atoi(strAttribute);
												strAttribute = m_xml.GetAttrib("Type");
												m_pPOLSlotInfo[nPOLIndex].chInfo.strType = strAttribute;
												strAttribute = m_xml.GetAttrib("Used");
												m_pPOLSlotInfo[nPOLIndex].chInfo.nOnline = atoi(strAttribute);	
												m_xml.OutOfElem();
											}
											++nPOLIndex;
											m_nPolCount = nPOLIndex;											
										}										
									}																		
								}
								else if(strAttribute.CompareNoCase("Chamber")==0)
								{
									strAttribute = m_xml.GetAttrib("Used");
									int nUse = atoi(strAttribute);
									if(nUse !=1)
									{
										m_xml.OutOfElem();
										continue;
									}

									int nSlotType = TAG_CHAMBER;
									int nDevIndex = m_ptrMainFrame[i].nIndex;
									strAttribute = m_xml.GetAttrib("Index");
									int nCurSlotIndex = atoi(strAttribute);
									strAttribute = m_xml.GetAttrib("Caption");
									CString strCaption = strAttribute;
									strAttribute = m_xml.GetAttrib("HWVesino");
									CString strHWVersion = strAttribute;
									strAttribute = m_xml.GetAttrib("FWVesion");
									CString strFWVersion = strAttribute;
									strAttribute = m_xml.GetAttrib("SN");
									CString strSN = strAttribute;
									strAttribute = m_xml.GetAttrib("ChannelCount");
									int nChannelCount = atoi(strAttribute);

									if (nChannelCount >0 )
									{
										for (int m=0;m<nChannelCount;m++)
										{
											
											m_pChamberSlotInfo[nChamberIndex].nSlotType = nSlotType;
											m_pChamberSlotInfo[nChamberIndex].nDevIndex = nDevIndex;								
											m_pChamberSlotInfo[nChamberIndex].nConfigIndex = nCurSlotIndex;
											m_pChamberSlotInfo[nChamberIndex].nOnline = nUse;
											m_pChamberSlotInfo[nChamberIndex].strCaption = strCaption;
											m_pChamberSlotInfo[nChamberIndex].strHWVersion = strHWVersion;
											m_pChamberSlotInfo[nChamberIndex].strFWVersion = strFWVersion;
											m_pChamberSlotInfo[nChamberIndex].strSN = strSN;
											m_pChamberSlotInfo[nChamberIndex].nChanelCout = nChannelCount;
											m_pChamberSlotInfo[nChamberIndex].nCurSlotIndex = nCurSlotIndex;									
											m_pChamberSlotInfo[nChamberIndex].nLogicalChannel = nChamberIndex;
											
											if(m_xml.FindChildElem("Channel"))
											{
												m_xml.IntoElem();
												strAttribute = m_xml.GetAttrib("Used");
												int nUse = atoi(strAttribute);
												if(nUse !=1)
												{
													m_xml.OutOfElem();
													continue;
												}
												strAttribute = m_xml.GetAttrib("Index");
												m_pChamberSlotInfo[nChamberIndex].chInfo.nCurChannel = atoi(strAttribute);
												strAttribute = m_xml.GetAttrib("Type");
												m_pChamberSlotInfo[nChamberIndex].chInfo.strType = strAttribute;
												strAttribute = m_xml.GetAttrib("Used");
												m_pChamberSlotInfo[nChamberIndex].chInfo.nOnline = atoi(strAttribute);	
												m_xml.OutOfElem();
											}
											++nChamberIndex;
											m_nChamberCount = nChamberIndex;											
										}										
									}																		
								}
								else if(strAttribute.CompareNoCase("ComDev")==0)
								{
									strAttribute = m_xml.GetAttrib("Used");
									int nUse = atoi(strAttribute);
									if(nUse !=1)
									{
										m_xml.OutOfElem();
										continue;
									}

									int nSlotType = TAG_COMDEV;
									int nDevIndex = m_ptrMainFrame[i].nIndex;
									strAttribute = m_xml.GetAttrib("Index");
									int nCurSlotIndex = atoi(strAttribute);
									strAttribute = m_xml.GetAttrib("Caption");
									CString strCaption = strAttribute;
									strAttribute = m_xml.GetAttrib("HWVesino");
									CString strHWVersion = strAttribute;
									strAttribute = m_xml.GetAttrib("FWVesion");
									CString strFWVersion = strAttribute;
									strAttribute = m_xml.GetAttrib("SN");
									CString strSN = strAttribute;
									strAttribute = m_xml.GetAttrib("ChannelCount");
									int nChannelCount = atoi(strAttribute);

									if (nChannelCount >0 )
									{
										for(int m=0;m<nChannelCount;m++)
										{											
											m_pComDevSlotInfo[nComDevIndex].nSlotType = nSlotType;
											m_pComDevSlotInfo[nComDevIndex].nDevIndex = nDevIndex;								
											m_pComDevSlotInfo[nComDevIndex].nConfigIndex = nCurSlotIndex;
											m_pComDevSlotInfo[nComDevIndex].nOnline = nUse;
											m_pComDevSlotInfo[nComDevIndex].strCaption = strCaption;
											m_pComDevSlotInfo[nComDevIndex].strHWVersion = strHWVersion;
											m_pComDevSlotInfo[nComDevIndex].strFWVersion = strFWVersion;
											m_pComDevSlotInfo[nComDevIndex].strSN = strSN;
											m_pComDevSlotInfo[nComDevIndex].nChanelCout = nChannelCount;
											m_pComDevSlotInfo[nComDevIndex].nCurSlotIndex = nCurSlotIndex;									
											m_pComDevSlotInfo[nComDevIndex].nLogicalChannel = nComDevIndex;
											if(m_xml.FindChildElem("Channel"))
											{
												m_xml.IntoElem();
												strAttribute = m_xml.GetAttrib("Used");
												int nUse = atoi(strAttribute);
												if(nUse !=1)
												{
													m_xml.OutOfElem();
													continue;
												}
												strAttribute = m_xml.GetAttrib("Index");
												m_pComDevSlotInfo[nComDevIndex].chInfo.nCurChannel = atoi(strAttribute);
												strAttribute = m_xml.GetAttrib("Type");
												m_pComDevSlotInfo[nComDevIndex].chInfo.strType = strAttribute;
												strAttribute = m_xml.GetAttrib("Used");
												m_pComDevSlotInfo[nComDevIndex].chInfo.nOnline = atoi(strAttribute);	
												m_xml.OutOfElem();
											}
											++nComDevIndex;
											m_nComDev = nComDevIndex;		
										}
									}																		
								}								
							}
							else
							{
								m_strErrorMsg =_T("Read Device Manager File Error!");									
								return FALSE;
							}
							m_xml.OutOfElem();
						}
						m_xml.OutOfElem();
					}					
				}
			}
			m_xml.OutOfElem();
		}
		else
		{
			m_strErrorMsg =_T("Read Device Manager File Error!");
			return FALSE;
		}			
		m_xml.OutOfElem();		
	}
	else
	{
		m_strErrorMsg =_T("Read Device Manager File Error!");
		return FALSE;
	}
	
	m_strErrorMsg = _T("No Error");
	
	return TRUE;
}


CString CDeviceManger::GetErrorMsg()
{

    return m_strErrorMsg;
}
////////////////////////////////////////////////////////////////
//函数说明：
//    根据配置映射表，打开所有设备函数
//Add by wanxin
//Time：20140311
////////////////////////////////////////////////////////////////
BOOL CDeviceManger::OpenDevice()
{
	BOOL bRet = TRUE;
	m_strErrorMsg = _T("No Error");

	if(m_bUseNet)
	{
		if(!OpenDeviceForNET())
		{
			return FALSE;
		}
        return TRUE;
	}
	
    //首先根据设备个数及设备类型定义相应类型对象
	for(int i=0;i< m_nDeviceCount;i++)
	{
		if(m_ptrMainFrame[i].nOnLine)
		{
			switch(m_ptrMainFrame[i].nComType)
			{
			case T_GPIB:
				{
					m_strComAddress.Format("GPIB,%d,%s",m_ptrMainFrame[i].nDevID,m_ptrMainFrame[i].strAddress);
				}
				break;
			case T_SERIAL:
				{
					m_strComAddress.Format("COM,%s",m_ptrMainFrame[i].strAddress);
				}
				break;
			case T_NET:
				{
					m_strComAddress.Format("LAN,%d,%s",m_ptrMainFrame[i].nDevID,m_ptrMainFrame[i].strAddress);
				}
				break;
			case T_USB:
				{
					m_strComAddress.Format("USB,%s",m_ptrMainFrame[i].strAddress);
				}
				break;
			default:
				return FALSE;
			}
			if (m_nTLSCount!=0) 
			{
				if (!OpenTLS(i,m_strComAddress))
				{
					//m_strErrorMsg = _T("Open TLS Error!");
					bRet = FALSE;
				}
			}
			if (m_nPMCount!=0) 
			{
				if (!OpenPM(i,m_strComAddress)) 
				{
					//	m_strErrorMsg = _T("Open PM Error!");
					bRet = FALSE;
				}
			}
            
			if(m_nVOACount!=0)
			{
				if (!OpenVOA(i,m_strComAddress)) 
				{
					//m_strErrorMsg = _T("Open VOA Error!");
					bRet = FALSE;
				}
			}
			
			if(m_nOSACount!=0)
			{
				if (!OpenOSA(i,m_strComAddress)) 
				{
					//	m_strErrorMsg = _T("Open OSA Error!");
					bRet = FALSE;
				}
			}
			if(m_nPolCount!=0)
			{
				if (!OpenPOL(i,m_strComAddress)) 
				{
					//m_strErrorMsg = _T("Open POL Error!");
					bRet = FALSE;
				}
			}
			if (m_nChamberCount!=0)
			{
				if (!OpenChamber(i,m_strComAddress)) 
				{
					//m_strErrorMsg = _T("Open Chamber Error!");
					bRet = FALSE;
				}
			}
			if (m_nComDev !=0)
			{				
				if (!OpenComDev(i,m_strComAddress)) 
				{
					//m_strErrorMsg = _T("Open Com Device Error!");
					bRet = FALSE;
				}
			}
		}
		if (!bRet)
		{
			break;
		}
	}
	
	return bRet;
}
////////////////////////////////////////////////////////////////
//函数说明：
//    根据配置映射表，打开所有激光器设备
//Add by wanxin
//Time：20140311
////////////////////////////////////////////////////////////////
BOOL CDeviceManger::OpenTLS(int nDevIndex,LPCSTR lpAddress)
{
	stDevType s_DevInfo;
	DWORD dwErrorCode;
	CString strAddress,strTemp;
	unsigned long lHandle;
	strAddress = lpAddress;
	//如果是激光器
	for (int j=0;j<m_nTLSCount;j++)
	{
		if (m_ptrMainFrame[nDevIndex].nIndex == m_pTLSSlotInfo[j].nDevIndex && m_pTLSSlotInfo[j].nSlotType == TAG_TLS)
		{
			s_DevInfo.bNum =m_ptrMainFrame[nDevIndex].nIndex;
			strTemp = m_ptrMainFrame[nDevIndex].strCaption;
			strTemp.MakeUpper();
			if (lstrcmp(strTemp, "816X")==0)
			{
				s_DevInfo.bType = HP_816X;
			}
			else if (lstrcmp(strTemp, "ITLA")==0)
			{
				s_DevInfo.bType = OPLK_TLS;
			}
			else if (lstrcmp(strTemp, "SANTEC")==0)
			{
				s_DevInfo.bType = SANTEC_TLS;
			}
			else if (lstrcmp(strTemp, "81960A")==0)
			{
				s_DevInfo.bType = AGLIENT81960A;
			}
			else if (lstrcmp(strTemp, "AQ2200_136")==0)
			{
				s_DevInfo.bType = AQ2200_136;
			}
			else if (lstrcmp(strTemp, "HP8168E")==0)
			{
				s_DevInfo.bType = HP8168E;
			}
			else
			{
				m_strErrorMsg.Format("TLS Type Error,Error Code:%d",ERROR_TLS);
				return FALSE;
			}
			m_ctrlTLS.push_back(new CTLSDll);
            //ASSERT(m_pTLSSlotInfo[j]);
			if (m_pTLSSlotInfo[j].nOnline && m_ptrMainFrame[nDevIndex].bMainFrameIsOPen==FALSE) 
			{
				dwErrorCode = m_ctrlTLS[j]->OpenDevice(s_DevInfo,strAddress.GetBuffer(0),&lHandle);
				if (dwErrorCode !=SUCCESS)
				{
					m_strErrorMsg.Format("Open TLS error,Maybe address error,Error code:%d",dwErrorCode);
					return FALSE;
				}
				m_ptrMainFrame[nDevIndex].bMainFrameIsOPen = TRUE;
				m_ptrMainFrame[nDevIndex].lMainFramHandle = lHandle;
			}
			else if(m_pTLSSlotInfo[j].nOnline)
			{
				dwErrorCode=m_ctrlTLS[j]->SetHandle(s_DevInfo,strAddress.GetBuffer(0),m_ptrMainFrame[nDevIndex].lMainFramHandle);
				if (dwErrorCode !=SUCCESS)
				{
					m_strErrorMsg.Format("Open TLS error,Maybe address error,Error code:%d",dwErrorCode);
					return FALSE;
				}
			}
		}
	}
	
	//m_strErrorMsg = _T("No Error");
	
	return TRUE;
}
////////////////////////////////////////////////////////////////
//函数说明：
//    根据配置映射表，打开所有衰减器设备
//Add by wanxin
//Time：20140311
////////////////////////////////////////////////////////////////
BOOL CDeviceManger::OpenVOA(int nDevIndex,LPCSTR lpAddress)
{
	stDevType s_DevInfo;
	DWORD dwErrorCode;
	CString strAddress,strTemp;
	unsigned long lHandle;
	strAddress = lpAddress;
	
	for (int j=0;j<m_nVOACount;j++)
	{
		if (m_ptrMainFrame[nDevIndex].nIndex == m_pVOASlotInfo[j].nDevIndex && m_pVOASlotInfo[j].nSlotType == TAG_VOA)
		{
			
			memset(&s_DevInfo, 0, sizeof(s_DevInfo));
			s_DevInfo.bNum = m_ptrMainFrame[nDevIndex].nIndex;
			
			strTemp = m_ptrMainFrame[nDevIndex].strCaption;
			strTemp.MakeUpper();
			strTemp.TrimRight();
			strTemp.TrimLeft();
			if (lstrcmp(strTemp, "HP8156A")==0)
			{
				s_DevInfo.bType = HP_8156A;
			}
			else if (lstrcmp(strTemp, "OPLINK VOA")==0)
			{
				s_DevInfo.bType = OPLK_VOA;
			}
			else if (lstrcmp(strTemp, "816X")==0)
			{
				s_DevInfo.bType = A8164_VOA;
			}
			else if(lstrcmp(strTemp,"OPLINKR153CHAKA")==0)
			{
				s_DevInfo.bType = OPLINKR153CHAKA;
			}
			else if(lstrcmp(strTemp,"OPLINKDULVOA")==0)
			{
				s_DevInfo.bType = OPLINKDULVOA;
			}
			else if(lstrcmp(strTemp,"AQ2200_311A")==0)
			{
				s_DevInfo.bType = AQ2200_311A;
			}
			else if(lstrcmp(strTemp,"AQ3150")==0)
			{
				s_DevInfo.bType = AQ3150;
			}
			else if(lstrcmp(strTemp,"SANTEC")==0)
			{
				s_DevInfo.bType = SANTECTLSVOA;
			}
			else
			{
				m_strErrorMsg.Format("VOA Type Error,Error Code:%d",ERROR_VOA);
				return FALSE;
			}
			m_ctrlVOA.push_back(new CVOADll);
			if (m_pVOASlotInfo[j].nOnline && m_ptrMainFrame[nDevIndex].bMainFrameIsOPen==FALSE) 
			{				
				dwErrorCode = m_ctrlVOA[j]->OpenDevice(s_DevInfo,strAddress.GetBuffer(0),&lHandle);
				if (dwErrorCode !=SUCCESS)
				{
					m_strErrorMsg.Format("Open VOA error,Maybe address error,Error Code:%d",dwErrorCode);
					return FALSE;
				}
				
				m_ptrMainFrame[nDevIndex].bMainFrameIsOPen = TRUE;
				m_ptrMainFrame[nDevIndex].lMainFramHandle = lHandle;
			}
			else if(m_pVOASlotInfo[j].nOnline)
			{
				dwErrorCode=m_ctrlVOA[j]->SetHandle(s_DevInfo,strAddress.GetBuffer(0),m_ptrMainFrame[nDevIndex].lMainFramHandle);
				if (dwErrorCode !=SUCCESS)
				{
					m_strErrorMsg.Format("Open VOA error,Maybe address error,Error Code:%d",dwErrorCode);
					return FALSE;
				}
			}
		}
	}
	//m_strErrorMsg = _T("No Error");
	return TRUE;
}
////////////////////////////////////////////////////////////////
//函数说明：
//    根据配置映射表，打开所有功率计设备
//Add by wanxin
//Time：20140311
////////////////////////////////////////////////////////////////
BOOL CDeviceManger::OpenPM(int nDevIndex,LPCSTR lpAddress)
{
	stDevType s_DevInfo;
	DWORD dwErrorCode;
	CString strAddress;
	unsigned long lHandle;
	CString strTemp;
	strAddress = lpAddress;
	for (int j=0;j<m_nPMCount;j++)
	{
		if (m_ptrMainFrame[nDevIndex].nIndex == m_pPMSlotInfo[j].nDevIndex && m_pPMSlotInfo[j].nSlotType == TAG_PM)
		{			
			s_DevInfo.bNum =m_ptrMainFrame[nDevIndex].nIndex;
			strTemp = m_ptrMainFrame[nDevIndex].strCaption;
			strTemp.MakeUpper();
			if (lstrcmp(strTemp, "816X")==0)
			{
				s_DevInfo.bType = HP_8163A;
			}
			else if (lstrcmp(strTemp, "OPLINK PM")==0)
			{
				s_DevInfo.bType = OPLK_PM;
			}
			else if (lstrcmp(strTemp, "I1830C")==0)
			{
				s_DevInfo.bType = PM_I830C;
			}
			else if (lstrcmp(strTemp, "N7744")==0)
			{
				s_DevInfo.bType = PM_N7745;
			}
			else if (lstrcmp(strTemp, "N7745")==0)
			{
				s_DevInfo.bType = PM_N7745;
			}
			else if (lstrcmp(strTemp, "JH")==0)
			{
				s_DevInfo.bType = PM_JH;
			}
			else if(lstrcmp(strTemp, "OPLINKI1830C")==0)
			{
				s_DevInfo.bType = PM_OPLINKI1830C;
			}
			else if(lstrcmp(strTemp, "HP8153A")==0)
			{
				s_DevInfo.bType = HP_8153A;
			}
			else if(lstrcmp(strTemp, "AQ2200_215")==0)
			{
				s_DevInfo.bType = AQ2200_215;
			}
			else if(lstrcmp(strTemp, "AQ2140")==0)
			{
				s_DevInfo.bType = AQ2140;
			}
			else
			{
				m_strErrorMsg.Format("PM Type Error,Error Code:%d",ERROR_PM);
				return FALSE;
			}
			m_ctrlPM.push_back(new CPMDll);
			if (m_pPMSlotInfo[j].nOnline && m_ptrMainFrame[nDevIndex].bMainFrameIsOPen==FALSE) 
			{
				dwErrorCode = m_ctrlPM[j]->OpenDevice(s_DevInfo,strAddress.GetBuffer(0),&lHandle);
				if (dwErrorCode !=SUCCESS)
				{
					m_strErrorMsg.Format("Open PM error,Maybe address error,Error Code:%d",dwErrorCode);
					return FALSE;
				}
				m_ptrMainFrame[nDevIndex].bMainFrameIsOPen = TRUE;
				m_ptrMainFrame[nDevIndex].lMainFramHandle = lHandle;				
			}
			else if(m_pPMSlotInfo[j].nOnline)
			{				
				dwErrorCode=m_ctrlPM[j]->SetHandle(s_DevInfo,strAddress.GetBuffer(0),m_ptrMainFrame[nDevIndex].lMainFramHandle);
				if (dwErrorCode !=SUCCESS)
				{
					m_strErrorMsg.Format("Open PM error,Maybe address error,Error Code:%d",dwErrorCode);
					return FALSE;
				}
			}	
		}		
	}
	
	//m_strErrorMsg = _T("No Error");
	return TRUE;
}
////////////////////////////////////////////////////////////////
//函数说明：
//    根据配置映射表，打开所有OSA设备
//Add by wanxin
//Time：20140311
////////////////////////////////////////////////////////////////
BOOL CDeviceManger::OpenOSA(int nDevIndex,LPCSTR lpAddress)
{
	stDevType s_DevInfo;
	DWORD dwErrorCode;
	CString strAddress,strTemp;
	strAddress = lpAddress;
	unsigned long lHandle;
	
	for (int j=0;j<m_nOSACount;j++)
	{
		if (m_ptrMainFrame[nDevIndex].nIndex == m_pOSASlotInfo[j].nDevIndex && m_pOSASlotInfo[j].nSlotType == TAG_OSA)
		{
			s_DevInfo.bNum =m_ptrMainFrame[nDevIndex].nIndex; 
			strTemp = m_ptrMainFrame[nDevIndex].strCaption;
			strTemp.MakeUpper();
			if (lstrcmp(strTemp, "AGLIENT 86142")==0)
			{
				s_DevInfo.bType = HP_86142;
			}
			else if (lstrcmp(strTemp, "ANDO")==0)
			{
				s_DevInfo.bType = AQ_6370B;
			}
			else if (lstrcmp(strTemp, "AQ6317B")==0)
			{
				s_DevInfo.bType = AQ_6317B;
			}
			else
			{
				m_strErrorMsg.Format("OSA Type Error,Error Code:%d",ERROR_OSA);
				return FALSE;
			}
			m_ctrlOSA.push_back(new COSADll);

			if (m_pOSASlotInfo[j].nOnline && m_ptrMainFrame[nDevIndex].bMainFrameIsOPen==FALSE) 
			{
				dwErrorCode = m_ctrlOSA[j]->OpenDevice(s_DevInfo,strAddress.GetBuffer(0),&lHandle);
				if (dwErrorCode !=SUCCESS)
				{
					m_strErrorMsg.Format("Open OSA Error,Maybe address error,Errror code:%d",dwErrorCode);
					return FALSE;
				}
				m_ptrMainFrame[nDevIndex].bMainFrameIsOPen = TRUE;
				m_ptrMainFrame[nDevIndex].lMainFramHandle = lHandle;
				
			}
			else if(m_pOSASlotInfo[j].nOnline)
			{				
				dwErrorCode=m_ctrlOSA[j]->SetHandle(s_DevInfo,strAddress.GetBuffer(0),m_ptrMainFrame[nDevIndex].lMainFramHandle);
				if (dwErrorCode !=SUCCESS)
				{
					m_strErrorMsg.Format("Open OSA Error,Maybe address error,Errror code:%d",dwErrorCode);
					return FALSE;
				}
			}	
		}
	}
	//m_strErrorMsg = _T("No Error");
	return TRUE;
}

////////////////////////////////////////////////////////////////
//函数说明：
//    根据配置映射表，打开所有OSA设备
//Add by wanxin
//Time：20140311
////////////////////////////////////////////////////////////////
BOOL CDeviceManger::OpenPOL(int nDevIndex,LPCSTR lpAddress)
{
	stDevType s_DevInfo;
	DWORD dwErrorCode;
	CString strAddress,strTemp;
	strAddress = lpAddress;
	unsigned long lHandle;
	
	for (int j=0;j<m_nPolCount;j++)
	{
		if (m_ptrMainFrame[nDevIndex].nIndex == m_pPOLSlotInfo[j].nDevIndex && m_pPOLSlotInfo[j].nSlotType == TAG_POL)
		{
			s_DevInfo.bNum =m_ptrMainFrame[nDevIndex].nIndex;
			strTemp = m_ptrMainFrame[nDevIndex].strCaption;
			strTemp.MakeUpper();
			if (lstrcmp(strTemp, "HP8169")==0)
			{
				s_DevInfo.bType = HP_8169;
			}
			else if (lstrcmp(strTemp, "OPLINKR181")==0)
			{
				s_DevInfo.bType = OPLK_POL;
			}
			else
			{
				m_strErrorMsg.Format("Pol Type Error,Error Code:%d",ERROR_PDLD);
				return FALSE;
			}

			m_ctrlPOL.push_back(new CPolDll);

			if (m_pPOLSlotInfo[j].nOnline && m_ptrMainFrame[nDevIndex].bMainFrameIsOPen==FALSE) 
			{				
				dwErrorCode = m_ctrlPOL[j]->OpenDevice(s_DevInfo,strAddress.GetBuffer(0),&lHandle);
				if (dwErrorCode !=SUCCESS)
				{
					m_strErrorMsg.Format("Open POL Error,Maybe address error,Error Code:%d",dwErrorCode);
					return FALSE;
				}
				m_ptrMainFrame[nDevIndex].bMainFrameIsOPen = TRUE;
				m_ptrMainFrame[nDevIndex].lMainFramHandle = lHandle;
				
			}
			else if(m_pPOLSlotInfo[j].nOnline)
			{
				dwErrorCode=m_ctrlPOL[j]->SetHandle(s_DevInfo,strAddress.GetBuffer(0),m_ptrMainFrame[nDevIndex].lMainFramHandle);
				if (dwErrorCode !=SUCCESS)
				{
					m_strErrorMsg.Format("Open POL Error,Maybe address error,Error Code:%d",dwErrorCode);
					return FALSE;
				}
			}
		}
	}
	//m_strErrorMsg = _T("No Error");
	return TRUE;
}

BOOL CDeviceManger::OpenChamber(int nDevIndex,LPCSTR lpAddress)
{
	stDevType s_DevInfo;
	DWORD dwErrorCode;
	CString strAddress,strTemp;
	strAddress = lpAddress;
	unsigned long lHandle;
	
	for (int j=0;j<m_nChamberCount;j++)
	{
		if (m_ptrMainFrame[nDevIndex].nIndex == m_pChamberSlotInfo[j].nDevIndex && m_pChamberSlotInfo[j].nSlotType == TAG_CHAMBER)
		{
			s_DevInfo.bNum =m_ptrMainFrame[nDevIndex].nIndex;
			strTemp = m_ptrMainFrame[nDevIndex].strCaption;
			strTemp.MakeUpper();
			if (lstrcmp(strTemp, "HONGZHANCHAMBER")==0)
			{
				s_DevInfo.bType = HONGZHAN;
			}
			else
			{
				m_strErrorMsg.Format("Chamber Type Error,Error Code:%d",ERROR_CHAMBER);
				return FALSE;
			}

			m_ctrlChamber.push_back(new CChamberDll);

			if (m_pChamberSlotInfo[j].nOnline && m_ptrMainFrame[nDevIndex].bMainFrameIsOPen==FALSE) 
			{			
				dwErrorCode = m_ctrlChamber[j]->OpenDevice(s_DevInfo,strAddress.GetBuffer(0),&lHandle);
				if (dwErrorCode !=SUCCESS)
				{
					m_strErrorMsg.Format("Open Chamber Error,Maybe address error,Error Code:%d",dwErrorCode);
					return FALSE;
				}
				m_ptrMainFrame[nDevIndex].bMainFrameIsOPen = TRUE;
				m_ptrMainFrame[nDevIndex].lMainFramHandle = lHandle;
			}
			else if(m_pChamberSlotInfo[j].nOnline)
			{
				dwErrorCode=m_ctrlChamber[j]->SetHandle(s_DevInfo,strAddress.GetBuffer(0),m_ptrMainFrame[nDevIndex].lMainFramHandle);
				if (dwErrorCode !=SUCCESS)
				{
					m_strErrorMsg.Format("Open Chamber Error,Maybe address error,Error Code:%d",dwErrorCode);
					return FALSE;
				}
			}
		}
	}
	//m_strErrorMsg = _T("No Error");
	return TRUE;
}

BOOL CDeviceManger::OpenComDev(int nDevIndex,LPCSTR lpAddress)
{
	stDevType s_DevInfo;
	DWORD dwErrorCode;
	CString strAddress,strTemp;
	strAddress = lpAddress;
	unsigned long lHandle;
	
	for (int j=0;j<m_nComDev;j++)
	{
		if (m_ptrMainFrame[nDevIndex].nIndex == m_pComDevSlotInfo[j].nDevIndex && m_pComDevSlotInfo[j].nSlotType == TAG_COMDEV)
		{
			s_DevInfo.bNum =m_ptrMainFrame[nDevIndex].nIndex;
			strTemp = m_ptrMainFrame[nDevIndex].strCaption;
			strTemp.MakeUpper();
			if (lstrcmp(strTemp, "COMDEV")==0)
			{
				s_DevInfo.bType = 0;
			}
			else
			{
				m_strErrorMsg.Format("Device Type Error,Error Code:%d",ERROR_COMDEV);
				return FALSE;
			}
			m_ctrlComDev.push_back(new CCommunicationDLL);
			if (m_pComDevSlotInfo[j].nOnline && m_ptrMainFrame[nDevIndex].bMainFrameIsOPen==FALSE) 
			{			
				dwErrorCode = m_ctrlComDev[j]->OpenDevice(strAddress.GetBuffer(0),lHandle);
				if (dwErrorCode !=SUCCESS)
				{
					m_strErrorMsg.Format("Open Com Device Error,Maybe address error,Error Code:%d",dwErrorCode);
					return FALSE;
				}
				m_ptrMainFrame[nDevIndex].bMainFrameIsOPen = TRUE;
				m_ptrMainFrame[nDevIndex].lMainFramHandle = lHandle;
			}
			else if(m_pComDevSlotInfo[j].nOnline)
			{
				dwErrorCode=m_ctrlComDev[j]->SetDeviceHandle(strAddress.GetBuffer(0),m_ptrMainFrame[nDevIndex].lMainFramHandle);
				if (dwErrorCode !=SUCCESS)
				{
					m_strErrorMsg.Format("Open  Com Device Error,Maybe address error,Error Code:%d",dwErrorCode);
					return FALSE;
				}
			}
		}
	}
	return TRUE;
}

///////////////////////////////激光器相关函数//////////////////////////////////////////
BOOL CDeviceManger::SetTLSWavelength(long lChIndex, double dblWL)
{
	DWORD dwErrorCode;
    m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!SetTLSWavelengthForNET(lChIndex,dblWL))
		{
			return FALSE;
		}
		return TRUE;
	}

	if (lChIndex >= m_nTLSCount)
	{
		m_strErrorMsg.Format("The TLS Channel Number is Error");
		return FALSE;	
	}
	
	if (dblWL < 600 || dblWL > 2000) 
	{
		m_strErrorMsg.Format("Current Value is %.4f,Setting TLS Wavelength Out of Range",dblWL);
		return FALSE;
	}
    long lSlot = m_pTLSSlotInfo[lChIndex].nCurSlotIndex;
	m_ctrlTLS[lChIndex]->SetSlotIndex(lSlot);
	dwErrorCode = m_ctrlTLS[lChIndex]->SetWavelength(lSlot,dblWL);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Setting TLS Wavelength Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	return TRUE;
}
BOOL CDeviceManger::SetTLSSourcePower(long lChIndex, double dblPW)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!SetTLSSourcePowerForNET(lChIndex,dblPW))
		{
            return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nTLSCount)
	{
		m_strErrorMsg.Format("The TLS Channel Number is Error");
		return FALSE;	
	}
	if (dblPW < -200.0 || dblPW >1000.0)
	{
		m_strErrorMsg.Format("Current Value is %.4f,Setting TLS Power Out of Range",dblPW);
		return FALSE;
	}


	long lSlot = m_pTLSSlotInfo[lChIndex].nCurSlotIndex;
	m_ctrlTLS[lChIndex]->SetSlotIndex(lSlot);
	dwErrorCode = m_ctrlTLS[lChIndex]->SetSourcePower(lSlot,dblPW);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Setting TLS Source Power Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	return TRUE;	
}
BOOL CDeviceManger::SetTLSCoherenceControl(long lChIndex,BOOL bEnable)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!SetTLSCoherenceControlForNET(lChIndex,bEnable))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nTLSCount)
	{
		m_strErrorMsg.Format("The TLS Channel Number is Error");
		return FALSE;	
	}
	if (bEnable <0 || bEnable >1)
	{
		m_strErrorMsg.Format("Current Value is %d,Setting TLS Coherence Control Out of Range",bEnable);
		return FALSE; 
	}

	long lSlot = m_pTLSSlotInfo[lChIndex].nCurSlotIndex;
	m_ctrlTLS[lChIndex]->SetSlotIndex(lSlot);
	dwErrorCode = m_ctrlTLS[lChIndex]->SetCoherenceControl(bEnable);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Setting TLS Coherence Mode Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	m_strErrorMsg = _T("No Error");
	return TRUE;
}
BOOL CDeviceManger::SetTLSSourceUnit(long lChIndex, long lUnit)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!SetTLSSourceUnitForNET(lChIndex,lUnit))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nTLSCount)
	{
		m_strErrorMsg.Format("The TLS Channel Number is Error");
		return FALSE;	
	}
	if (lUnit > 10 || lUnit < 0)
	{
		m_strErrorMsg.Format("Current Value Is:%d,Setting TLS Source Unit Must less 10",lUnit);
		return FALSE;
	}


	long lSlot = m_pTLSSlotInfo[lChIndex].nCurSlotIndex;
	m_ctrlTLS[lChIndex]->SetSlotIndex(lSlot);
	dwErrorCode = m_ctrlTLS[lChIndex]->SetSourceUnit(lSlot,lUnit);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Setting TLS Source Unit Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	m_strErrorMsg = _T("No Error");
	return TRUE;	
}
BOOL CDeviceManger::SetTLSParameters(long lChIndex, BOOL bLowSSE,double dblPower, double dblWavelength)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!SetTLSParametersForNET(lChIndex,bLowSSE,dblPower,dblWavelength))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nTLSCount)
	{
		m_strErrorMsg.Format("The TLS Channel Number is Error");
		return FALSE;	
	}
	if (dblWavelength >2000|| dblWavelength < 600)
	{
		m_strErrorMsg.Format("Current Value Is:%.4f,Setting TLS WL Out of Range",dblWavelength);
		return FALSE;
	}
	if (dblPower < -200.0 || dblPower > 1000.0 )
	{
		m_strErrorMsg.Format("Current Value Is:%.4f,Setting TLS Power Out of Range",dblPower);
		return FALSE;
	}

	long lSlot = m_pTLSSlotInfo[lChIndex].nCurSlotIndex;
	m_ctrlTLS[lChIndex]->SetSlotIndex(lSlot);
	dwErrorCode = m_ctrlTLS[lChIndex]->SetParameters(lSlot,bLowSSE,dblPower,dblWavelength);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Setting TLS Parameters Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	m_strErrorMsg = _T("No Error");
	return TRUE;	
}
BOOL CDeviceManger::SetTLSOutputEnable(long lChIndex,BOOL bEnable)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!SetTLSOutputEnableForNET(lChIndex,bEnable))
		{
			return FALSE;
		}
		return TRUE;
	}

	if (lChIndex >= m_nTLSCount)
	{
		m_strErrorMsg.Format("The TLS Channel Number is Error");
		return FALSE;	
	}
	if (bEnable < 0 || bEnable > 1)
	{
		m_strErrorMsg.Format("Current Value Is:%d,Setting TLS OutPut Eenalbe Out of Range",bEnable);
		return FALSE;
	}
	
	long lSlot = m_pTLSSlotInfo[lChIndex].nCurSlotIndex;
	m_ctrlTLS[lChIndex]->SetSlotIndex(lSlot);
	dwErrorCode = m_ctrlTLS[lChIndex]->SetOutputEnable(bEnable);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Setting TLS Output Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	m_strErrorMsg = _T("No Error");
	return TRUE;	
}
BOOL CDeviceManger::CloseTLSDevice(long lChIndex)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!CloseTLSDeviceForNET(lChIndex))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nTLSCount)
	{
		m_strErrorMsg.Format("The TLS Channel Number is Error");
		return FALSE;	
	}

	long lSlot = m_pTLSSlotInfo[lChIndex].nCurSlotIndex;
	m_ctrlTLS[lChIndex]->SetSlotIndex(lSlot);
	dwErrorCode = m_ctrlTLS[lChIndex]->CloseDevice();
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Close TLS Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	m_strErrorMsg = _T("No Error");
	return TRUE;
}
/////////////////////////功率计相关函数//////////////////////////////////
BOOL CDeviceManger::GetPMUnit(long iChan, long* piUnit)
{
	DWORD dwErrorCode;	
	long lSlot,lChannel;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!GetPMUnitForNET(iChan,piUnit))
		{
			return FALSE;
		}
		return TRUE;
	}	
	if (iChan >= m_nPMCount)
	{
		m_strErrorMsg.Format("The PM Channel Number is Error");
		return FALSE;	
	}

	lSlot = m_pPMSlotInfo[iChan].nCurSlotIndex;
	lChannel= m_pPMSlotInfo[iChan].chInfo.nCurChannel;
	dwErrorCode = m_ctrlPM[iChan]->GetUnit(lSlot,lChannel,piUnit);
	
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Get PM Unit Mode Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	if (*piUnit < 0 || *piUnit > 10 )
	{
		m_strErrorMsg.Format("Current Value Is: %d,The PM Get Unit Out Of Range",*piUnit);
		return FALSE;	
	}
	m_strErrorMsg = _T("No Error");
	return TRUE;	
}
BOOL CDeviceManger::GetPMAverageTime(long iChan, double* pdblAverageTime)
{
	DWORD dwErrorCode;
	long lSlot,lChannel;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!GetPMAverageTimeForNET(iChan,pdblAverageTime))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (iChan >= m_nPMCount)
	{
		m_strErrorMsg.Format("The PM Channel Number is Error");
		return FALSE;	
	}

	lSlot = m_pPMSlotInfo[iChan].nCurSlotIndex;
	lChannel= m_pPMSlotInfo[iChan].chInfo.nCurChannel;
	dwErrorCode = m_ctrlPM[iChan]->GetAverageTime(lSlot,lChannel,pdblAverageTime);
	
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Get PM Averager Time Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	if (*pdblAverageTime <0.0 || *pdblAverageTime >100000000.0) 
	{
		m_strErrorMsg.Format("Current Value Is %lf,The PM Get Average Time Out Of Range",*pdblAverageTime);
		return FALSE;
	}
	return TRUE;	
}
BOOL CDeviceManger::GetPMWavelength(long iChan, double* pdblWL)
{
	DWORD dwErrorCode;
	long lSlot,lChannel;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!GetPMWavelengthForNET(iChan,pdblWL))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (iChan >= m_nPMCount)
	{
		m_strErrorMsg.Format("The PM Channel Number is Error");
		return FALSE;	
	}
	
	lSlot = m_pPMSlotInfo[iChan].nCurSlotIndex;
	lChannel= m_pPMSlotInfo[iChan].chInfo.nCurChannel;
	dwErrorCode = m_ctrlPM[iChan]->GetWavelength(lSlot,lChannel,pdblWL);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Get PM Wavelength Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	if (*pdblWL< 600.0||*pdblWL >2000.0)
	{
		m_strErrorMsg.Format("Current Value Is:%lf,The PM Get Wavelength Out Of Range",*pdblWL);
		return FALSE;
	}
	return TRUE;	
}
BOOL CDeviceManger::ReadPower(long iChan, double* pdbPowerValue)
{
	DWORD dwErrorCode;
	long lSlot,lChannel;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!ReadPowerForNET(iChan,pdbPowerValue))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (iChan >= m_nPMCount)
	{
		m_strErrorMsg.Format("The PM Channel Number is Error");
		return FALSE;	
	}

	lSlot = m_pPMSlotInfo[iChan].nCurSlotIndex;
	lChannel= m_pPMSlotInfo[iChan].chInfo.nCurChannel;
	dwErrorCode = m_ctrlPM[iChan]->ReadPower(lSlot,lChannel,pdbPowerValue);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Get PM Power Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	if (*pdbPowerValue < -200.0 || *pdbPowerValue >10000.0 )
	{
		m_strErrorMsg.Format("Current Value Is:%lf,The PM Get Power Out Of Range",*pdbPowerValue);
		return FALSE;
	}
	m_strErrorMsg = _T("No Error");
	return TRUE;
}
BOOL CDeviceManger::SetPMUnit(long iChan, long iPWUnit)
{
	DWORD dwErrorCode;
    long lSlot,lChannel;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!SetPMUnitForNET(iChan,iPWUnit))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (iChan >= m_nPMCount)
	{
		m_strErrorMsg.Format("The PM Channel Number is Error");
		return FALSE;	
	}
	
	if (iPWUnit >20 || iPWUnit < 0) 
	{
		m_strErrorMsg.Format("Setting PM Unit Mode Must 0 - 3");
		return FALSE;
	}
	
	lSlot = m_pPMSlotInfo[iChan].nCurSlotIndex;
	lChannel= m_pPMSlotInfo[iChan].chInfo.nCurChannel;
	dwErrorCode = m_ctrlPM[iChan]->SetUnit(lSlot,lChannel,iPWUnit);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Setting PM Unit Mode Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	m_strErrorMsg = _T("No Error");
	return TRUE;	
}
BOOL CDeviceManger::SetPMWavelength(long iChan, double dblWL)
{
	DWORD dwErrorCode;
	long lSlot,lChannel;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!SetPMWavelengthForNET(iChan,dblWL))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (iChan >= m_nPMCount)
	{
		m_strErrorMsg.Format("The PM Channel Number is Error");
		return FALSE;	
	}
	if (dblWL >20000 || dblWL < 600) 
	{
		m_strErrorMsg.Format("Current Value Is:%lf,Setting PM WL Out of Range",dblWL);
		return FALSE;
	}

	lSlot = m_pPMSlotInfo[iChan].nCurSlotIndex;
	lChannel= m_pPMSlotInfo[iChan].chInfo.nCurChannel;
	dwErrorCode = m_ctrlPM[iChan]->SetWavelength(lSlot,lChannel,dblWL);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Setting PM Wavelength Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	m_strErrorMsg = _T("No Error");
	return TRUE;	
}
BOOL CDeviceManger::SetPMAverageTime(long iChan, double dblPWAverageTime)
{
	DWORD dwErrorCode;
	long lSlot,lChannel;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!SetPMAverageTimeForNET(iChan,dblPWAverageTime))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (iChan >= m_nPMCount)
	{
		m_strErrorMsg.Format("The PM Channel Number is Error");
		return FALSE;	
	}
	
	if (dblPWAverageTime >20000 || dblPWAverageTime < 0.0) 
	{
		m_strErrorMsg.Format("Current Value Is %lf,Setting PM AverageTime Out of Range",dblPWAverageTime);
		return FALSE;
	}

	lSlot = m_pPMSlotInfo[iChan].nCurSlotIndex;
	lChannel= m_pPMSlotInfo[iChan].chInfo.nCurChannel;
	dwErrorCode = m_ctrlPM[iChan]->SetAverageTime(lSlot,lChannel,dblPWAverageTime);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Setting PM AverageTime Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	m_strErrorMsg = _T("No Error");
	return TRUE;	
}
BOOL CDeviceManger::SetPMRangeMode(long iChan, long iPWRangeMode)
{
	DWORD dwErrorCode;
	long lSlot,lChannel;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!SetPMRangeModeForNET(iChan,iPWRangeMode))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (iChan >= m_nPMCount)
	{
		m_strErrorMsg.Format("The PM Channel Number is Error");
		return FALSE;	
	}
	if (iPWRangeMode > 20 || iPWRangeMode < 0) 
	{
		m_strErrorMsg.Format("Setting PM Range Mode Error");
		return FALSE;
	}

	lSlot = m_pPMSlotInfo[iChan].nCurSlotIndex;
	lChannel= m_pPMSlotInfo[iChan].chInfo.nCurChannel;
	dwErrorCode = m_ctrlPM[iChan]->SetRangeMode(lSlot,lChannel,iPWRangeMode);
	if(dwErrorCode != SUCCESS)
	{
		m_strErrorMsg.Format("Setting PM Range Mode Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	return TRUE;	
}
BOOL CDeviceManger::SetPMParameters(long iChan, BOOL bAutoRang, double dblWL, double dblAverageTime, double dblPwrRange)
{
	DWORD dwErrorCode;
	long lSlot,lChannel;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!SetPMParametersForNET(iChan,bAutoRang,dblWL,dblAverageTime,dblPwrRange))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (iChan >= m_nPMCount)
	{
		m_strErrorMsg.Format("The PM Channel Number is Error");
		return FALSE;	
	}
	
	if (dblAverageTime >20000 || dblAverageTime < 0.0) 
	{
		m_strErrorMsg.Format("Setting PM AverageTime Out Of Range");
		return FALSE;
	}
	if (dblWL >2000 || dblWL < 600) 
	{
		m_strErrorMsg.Format("Setting PM WL Out Of Range");
		return FALSE;
	}
	if (bAutoRang >1 || bAutoRang < 0) 
	{
		m_strErrorMsg.Format("Setting PM Range Mode Must 0 Or 1");
		return FALSE;
	}

	lSlot = m_pPMSlotInfo[iChan].nCurSlotIndex;
	lChannel= m_pPMSlotInfo[iChan].chInfo.nCurChannel;
	dwErrorCode = m_ctrlPM[iChan]->SetParameters(lSlot,lChannel,bAutoRang,dblWL,dblAverageTime,dblPwrRange);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Setting PM Parameters Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}

	return TRUE;
}
BOOL CDeviceManger::ClosePMDevice(long lChIndex)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!ClosePMDeviceForNET(lChIndex))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nPMCount)
	{
		m_strErrorMsg.Format("The PM Channel Number is Error");
		return FALSE;	
	}

	dwErrorCode = m_ctrlPM[lChIndex]->CloseDevice();
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Close TLS Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	m_strErrorMsg = _T("No Error");
	return TRUE;	
}
BOOL CDeviceManger::GetPMRangeMode(long iChan, long* iPWMRangeMode)
{
	DWORD dwErrorCode;
	long lSlot,lChannel;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!GetPMRangeModeForNET(iChan,iPWMRangeMode))
		{
			return FALSE;
		}
		if (*iPWMRangeMode<0 || *iPWMRangeMode >1) 
		{
			m_strErrorMsg.Format("Current Value Is:%d,The PM Get Range Mode Out of Range ",*iPWMRangeMode);
			return FALSE;
		}
		return TRUE;
	}
	if (iChan >= m_nPMCount)
	{
		m_strErrorMsg.Format("The PM Channel Number is Error");
		return FALSE;	
	}

	lSlot = m_pPMSlotInfo[iChan].nCurSlotIndex;
	lChannel= m_pPMSlotInfo[iChan].chInfo.nCurChannel;
	dwErrorCode = m_ctrlPM[iChan]->GetRangeMode(lSlot,lChannel,iPWMRangeMode);
	
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Get PM Range Mode Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	if (*iPWMRangeMode<0 || *iPWMRangeMode >1) 
	{
		m_strErrorMsg.Format("Current Value Is:%d,The PM Get Range Mode Out of Range ",*iPWMRangeMode);
		return FALSE;
	}
	m_strErrorMsg = _T("No Error");
	return TRUE;
}
BOOL CDeviceManger::SetPMZero(long iChan)
{
	DWORD dwErrorCode;
	long lSlot,lChannel;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!SetPMZeroForNET(iChan))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (iChan >= m_nPMCount)
	{
		m_strErrorMsg.Format("The PM Channel Number is Error");
		return FALSE;	
	}

	lSlot = m_pPMSlotInfo[iChan].nCurSlotIndex;
	lChannel= m_pPMSlotInfo[iChan].chInfo.nCurChannel;
	dwErrorCode = m_ctrlPM[iChan]->SetZero(lSlot,lChannel);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Setting PM Zero Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	m_strErrorMsg = _T("No Error");
	return TRUE;	
}
BOOL CDeviceManger::GetPMDeviceInfo(long lChIndex,CHAR *pchInfo)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if (lChIndex >= m_nPMCount)
	{
		m_strErrorMsg.Format("The PM Channel Number is Error");
		return FALSE;	
	}
	dwErrorCode = m_ctrlPM[lChIndex]->GetDeviceInfo(pchInfo);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Get PM Devie Information Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	m_strErrorMsg = _T("No Error");
	return TRUE;	
}

BOOL CDeviceManger::SetPMMaxMinPowerStart(long lChIndex)
{
	DWORD dwErrorCode;
	long lSlot,lChannel;
    m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!SetPMMaxMinPowerStartForNET(lChIndex))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nPMCount)
	{
		m_strErrorMsg.Format("The PM Channel Number is Error");
		return FALSE;	
	}

	lSlot = m_pPMSlotInfo[lChIndex].nCurSlotIndex;
	lChannel= m_pPMSlotInfo[lChIndex].chInfo.nCurChannel;
	dwErrorCode = m_ctrlPM[lChIndex]->SetPMMaxMinPowerStart(lSlot,lChannel);
	
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Set PM Max Min Mode Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	return TRUE;
}

BOOL CDeviceManger::GetPMMaxMinPower(long lChIndex,double *pdbGetMax,double *pdbGetMin)
{
	DWORD dwErrorCode;
	long lSlot,lChannel;
    m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!GetPMMaxMinPowerForNET(lChIndex,pdbGetMax,pdbGetMin))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nPMCount)
	{
		m_strErrorMsg.Format("The PM Channel Number is Error");
		return FALSE;	
	}

	lSlot = m_pPMSlotInfo[lChIndex].nCurSlotIndex;
	lChannel= m_pPMSlotInfo[lChIndex].chInfo.nCurChannel;
	dwErrorCode = m_ctrlPM[lChIndex]->GetPMMaxMinPower(lSlot,lChannel,pdbGetMax,pdbGetMin);
	
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Get PM Max Min Power Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	return TRUE;
}
BOOL CDeviceManger::SetPMMaxMinPowerStop(long lChIndex)
{
	DWORD dwErrorCode;
	long lSlot,lChannel;
    m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!SetPMMaxMinPowerStop(lChIndex))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nPMCount)
	{
		m_strErrorMsg.Format("The PM Channel Number is Error");
		return FALSE;	
	}

	lSlot = m_pPMSlotInfo[lChIndex].nCurSlotIndex;
	lChannel= m_pPMSlotInfo[lChIndex].chInfo.nCurChannel;
	dwErrorCode = m_ctrlPM[lChIndex]->SetPMMaxMinPowerStop(lSlot,lChannel);
	
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Set PM Max Min Mode Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}

	return TRUE;
}


BOOL CDeviceManger::SetPMPowerOffset(long lChIndex,double dbPowerOffset)
{
	DWORD dwErrorCode;
	long lSlot,lChannel;
    m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!SetPMPowerOffsetForNET(lChIndex,dbPowerOffset))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nPMCount)
	{
		m_strErrorMsg.Format("The PM Channel Number is Error");
		return FALSE;	
	}

	lSlot = m_pPMSlotInfo[lChIndex].nCurSlotIndex;
	lChannel= m_pPMSlotInfo[lChIndex].chInfo.nCurChannel;
	dwErrorCode = m_ctrlPM[lChIndex]->SetPMPowerOffset(lSlot,lChannel,dbPowerOffset);
	
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Set PM Offset Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}

	return TRUE;
}

/////////////////////////////VOA相关函数////////////////////////////////////////
BOOL CDeviceManger::CloseVOADevice(long lChIndex)
{
	DWORD dwErrorCode;
    m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!CloseVOADeviceForNET(lChIndex))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nVOACount)
	{
		m_strErrorMsg.Format("The VOA Channel Number is Error");
		return FALSE;	
	}
    
	dwErrorCode = m_ctrlVOA[lChIndex]->CloseDevice();
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Close VOA Device Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	m_strErrorMsg = _T("No Error");
	return TRUE;
}
BOOL CDeviceManger::ResetVOADevice(long lChIndex)
{
	DWORD dwErrorCode;
    m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!ResetVOADeviceForNET(lChIndex))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nVOACount)
	{
		m_strErrorMsg.Format("The VOA Channel Number is Error");
		return FALSE;	
	}

	dwErrorCode = m_ctrlVOA[lChIndex]->ResetDevice();
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Reset VOA Device Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	return TRUE;	
}
BOOL CDeviceManger::SetVOAWavelength(long lChIndex, double dblWL)
{
	DWORD dwErrorCode;
    m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!SetVOAWavelengthForNET(lChIndex,dblWL))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nVOACount)
	{
		m_strErrorMsg.Format("The VOA Channel Number is Error");
		return FALSE;	
	}
	if (dblWL >2000 || dblWL < 600) 
	{
		m_strErrorMsg.Format("Current Value Is:%lf,Setting VOA WL Out Of Range",dblWL);
		return FALSE;
	}
	long lSetChIndex = m_pVOASlotInfo[lChIndex].nCurSlotIndex;
	dwErrorCode = m_ctrlVOA[lChIndex]->SetWavelength(lSetChIndex,dblWL);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Setting VOA Wavelength Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	return TRUE;
}
BOOL CDeviceManger::GetVOAWavelength(long lChIndex, double* pdblWL)
{
	DWORD dwErrorCode;
    m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!GetVOAWavelengthForNET(lChIndex,pdblWL))
		{
			return FALSE;
		}
		return TRUE;
	}

	if (lChIndex >= m_nVOACount)
	{
		m_strErrorMsg.Format("The VOA Channel Number is Error");
		return FALSE;	
	}
    long lSetChIndex = m_pVOASlotInfo[lChIndex].nCurSlotIndex;
	dwErrorCode = m_ctrlVOA[lChIndex]->GetWavelength(lSetChIndex,pdblWL);
	
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Get VOA Wavelength Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	if (*pdblWL >2000 || *pdblWL < 600) 
	{
		m_strErrorMsg.Format("Current Value Is:%lf,Get VOA WL Out Of Range",*pdblWL);
		return FALSE;
	}
	return TRUE;
}
BOOL CDeviceManger::SetVOAAttenuation(long lChIndex, double dblAtten)
{
	DWORD dwErrorCode;
    m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!SetVOAAttenuationForNET(lChIndex,dblAtten))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nVOACount)
	{
		m_strErrorMsg.Format("The VOA Channel Number is Error");
		return FALSE;	
	}
	if (dblAtten < 0  || dblAtten > 200) 
	{
		m_strErrorMsg.Format("Current Value Is:%lf,Setting VOA Attenaution Out Of Range",dblAtten);
		return FALSE;
	}

	long lSetChIndex = m_pVOASlotInfo[lChIndex].nCurSlotIndex;
	dwErrorCode = m_ctrlVOA[lChIndex]->SetAttenuation(lSetChIndex,dblAtten);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Set VOA Attenuation Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	return TRUE;
}
BOOL CDeviceManger::GetVOAAttenuation(long lChIndex, double* pdblAtten)
{
	DWORD dwErrorCode;
    m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!GetVOAAttenuationForNET(lChIndex,pdblAtten))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nVOACount)
	{
		m_strErrorMsg.Format("The VOA Channel Number is Error");
		return FALSE;	
	}

	long lSetChIndex = m_pVOASlotInfo[lChIndex].nCurSlotIndex;
	dwErrorCode = m_ctrlVOA[lChIndex]->GetAttenuation(lSetChIndex,pdblAtten);
	
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Get VOA Attenuation Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	if (*pdblAtten < 0  || *pdblAtten > 200) 
	{
		m_strErrorMsg.Format("Current Value Is:%lf,Get VOA Attenaution Out Of Range",*pdblAtten);
		return FALSE;
	}

	return TRUE;	
}
BOOL CDeviceManger::SetVOAEnableOutput(long lChIndex, BOOL bEnable)
{
	DWORD dwErrorCode;
    m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!SetVOAEnableOutputForNET(lChIndex,bEnable))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nVOACount)
	{
		m_strErrorMsg.Format("The VOA Channel Number is Error");
		return FALSE;	
	}
	if (bEnable <0 || bEnable >1)
	{
		m_strErrorMsg.Format("Current Value Is:%lf,Setting VOA Enalbe Output Must 0 or 1",bEnable);
		return FALSE;
	}

	long lSetChIndex = m_pVOASlotInfo[lChIndex].nCurSlotIndex;
	dwErrorCode = m_ctrlVOA[lChIndex]->SetEnableOutput(lSetChIndex,bEnable);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Setting VOA Enable Out Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}

	return TRUE;
}
BOOL CDeviceManger::SetVOAInputOffset(long lChIndex, double dblOffset)
{
	DWORD dwErrorCode;
    m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!SetVOAInputOffsetForNET(lChIndex,dblOffset))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nVOACount)
	{
		m_strErrorMsg.Format("The VOA Channel Number is Error");
		return FALSE;	
	}
	if (dblOffset<0.0 || dblOffset >200.0)
	{
		m_strErrorMsg.Format("Current Value Is:%lf,Setting VOA InputOffse Output Range",dblOffset);
		return FALSE;
	}

	long lSetChIndex = m_pVOASlotInfo[lChIndex].nCurSlotIndex;
	dwErrorCode = m_ctrlVOA[lChIndex]->SetInputOffset(lSetChIndex,dblOffset);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Setting VOA Input Offset Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	return TRUE;
}
////////////////////////////////////////////OSA相关/////////////////////////////////
BOOL CDeviceManger::GetVOAStatus(long lChIndex,DWORD *dwStatus)
{
	DWORD dwErrorCode;
    m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!GetVOAStatusForNET(lChIndex,dwStatus))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nVOACount)
	{
		m_strErrorMsg.Format("The VOA Channel Number is Error");
		return FALSE;	
	}
    
	dwErrorCode = m_ctrlVOA[lChIndex]->GetStatus(dwStatus);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Get VOA Status Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	m_strErrorMsg = _T("No Error");
	return TRUE;	
}
/////////////////////////////////////////OSA相关函数///////////////////////////////////////
BOOL CDeviceManger::CloseOSADevice(long lChIndex)
{
	DWORD dwErrorCode;
    m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!CloseOSADeviceForNET(lChIndex))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nOSACount)
	{
		m_strErrorMsg.Format("The OSA Channel Number is Error");
		return FALSE;	
	}
	dwErrorCode = m_ctrlOSA[lChIndex]->CloseDevice();
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Close OSA Device Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	m_strErrorMsg = _T("No Error");
	return TRUE;	
}
BOOL CDeviceManger::ResetOSADevice(long lChIndex)
{
	DWORD dwErrorCode;
    m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!ResetOSADeviceForNET(lChIndex))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nOSACount)
	{
		m_strErrorMsg.Format("The OSA Channel Number is Error");
		return FALSE;	
	}
	dwErrorCode = m_ctrlOSA[lChIndex]->ResetDevice();
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Reset OSA Device Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	m_strErrorMsg = _T("No Error");
	return TRUE;	
}
BOOL CDeviceManger::SetOSALocalCtrl(long lChIndex)
{
	DWORD dwErrorCode;
    m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!SetOSALocalCtrlForNET(lChIndex))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nOSACount)
	{
		m_strErrorMsg.Format("The OSA Channel Number is Error");
		return FALSE;	
	}
	dwErrorCode = m_ctrlOSA[lChIndex]->SetOSALocalCtrl();
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Setting OSA Local control Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	m_strErrorMsg = _T("No Error");
	return TRUE;		
}
BOOL CDeviceManger::SetOSARBW(long lChIndex,double dblRBW)
{
	DWORD dwErrorCode;
    m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!SetOSARBWForNET(lChIndex,dblRBW))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nOSACount)
	{
		m_strErrorMsg.Format("The OSA Channel Number is Error");
		return FALSE;	
	}
	
	if (dblRBW < 0.0 || dblRBW > 10.0)
	{
		m_strErrorMsg.Format("Current Value Is:%lf,Set OSA RBW Out of Range",dblRBW);
		return FALSE;
	}
	dwErrorCode = m_ctrlOSA[lChIndex]->SetRBW(dblRBW);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Setting OSA RBW Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	m_strErrorMsg = _T("No Error");
	return TRUE;
}
BOOL CDeviceManger::GetOSARBW(long lChIndex,double* pdblRBW)
{
	DWORD dwErrorCode;
    m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!GetOSARBWForNET(lChIndex,pdblRBW))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nOSACount)
	{
		m_strErrorMsg.Format("The OSA Channel Number is Error");
		return FALSE;	
	}
	dwErrorCode = m_ctrlOSA[lChIndex]->GetRBW(pdblRBW);
	if (*pdblRBW < 0.0 || *pdblRBW > 10.0)
	{
		m_strErrorMsg.Format("Current Value Is:%lf,Get OSA RBW Out of Range",*pdblRBW);
		return FALSE;
	}
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Get OSA RBW Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	m_strErrorMsg = _T("No Error");
	return TRUE;	
}
BOOL CDeviceManger::InitOSAWDMTest(long lChIndex,double dblStartWL,double dblStopWL,double dblRBW)
{
	DWORD dwErrorCode;
    m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
	//	if(!InitOSAAmpTestForNET(lChIndex,dblStartWL,dblStopWL,dblRBW))
		{
			m_strErrorMsg = _T("The function not finished!");
			return FALSE;
		}
	//	return TRUE;
	}
	if (lChIndex >= m_nOSACount)
	{
		m_strErrorMsg.Format("The OSA Channel Number is Error");
		return FALSE;	
	}
	
	if (dblStartWL < 600 || dblStartWL >2000)
	{
		m_strErrorMsg.Format("Current Value Is:%lf,The OSA Start Wavelength Out of Range ",dblStartWL);
		return FALSE;
	}
	if (dblStopWL < 600 || dblStopWL >2000)
	{
		m_strErrorMsg.Format("Current Value Is:%lf,The OSA Stop Wavelength Out of Range ",dblStopWL);
		return FALSE;
	}
	if (dblRBW < 0.0 || dblRBW > 10.0)
	{
		m_strErrorMsg.Format("Current Value Is:%lf,The OSA RBW Out of Range",dblRBW);
		return FALSE;
	}
	dwErrorCode = m_ctrlOSA[lChIndex]->InitWDMTest(dblStartWL,dblStopWL,dblRBW);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Inital OSA WDM Test Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	return TRUE;	
}

BOOL CDeviceManger::InitOSAAmpTest(long lChIndex,double dblStartWL,double dblStopWL,double dblRBW)
{
	DWORD dwErrorCode;
    m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!InitOSAAmpTestForNET(lChIndex,dblStartWL,dblStopWL,dblRBW))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nOSACount)
	{
		m_strErrorMsg.Format("The OSA Channel Number is Error");
		return FALSE;	
	}
	
	if (dblStartWL < 600 || dblStartWL >2000)
	{
		m_strErrorMsg.Format("Current Value Is:%lf,The OSA Start Wavelength Out of Range ",dblStartWL);
		return FALSE;
	}
	if (dblStopWL < 600 || dblStopWL >2000)
	{
		m_strErrorMsg.Format("Current Value Is:%lf,The OSA Stop Wavelength Out of Range ",dblStopWL);
		return FALSE;
	}
	if (dblRBW < 0.0 || dblRBW > 10.0)
	{
		m_strErrorMsg.Format("Current Value Is:%lf,The OSA RBW Out of Range",dblRBW);
		return FALSE;
	}
	dwErrorCode = m_ctrlOSA[lChIndex]->InitAmpTest(dblStartWL,dblStopWL,dblRBW);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Inital OSA Amp Test Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	return TRUE;	
}
BOOL CDeviceManger::MeasureOSAWDM(long lChIndex)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
//		if(!MeasureOSASourceForNET(lChIndex))
//		{
//			return FALSE;
//		}
        m_strErrorMsg = _T("The function not finished!");
		return FALSE;
	}
	if (lChIndex >= m_nOSACount)
	{
		m_strErrorMsg.Format("The OSA Channel Number is Error");
		return FALSE;	
	}
	
	dwErrorCode = m_ctrlOSA[lChIndex]->MeasureWDM();
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Measure Source Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	m_strErrorMsg = _T("No Error");
	return TRUE;
}
BOOL CDeviceManger::MeasureOSASource(long lChIndex)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!MeasureOSASourceForNET(lChIndex))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nOSACount)
	{
		m_strErrorMsg.Format("The OSA Channel Number is Error");
		return FALSE;	
	}
	
	dwErrorCode = m_ctrlOSA[lChIndex]->MeasureSource();
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Measure Source Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	m_strErrorMsg = _T("No Error");
	return TRUE;	
}
BOOL CDeviceManger::MeasureOSAAmplifier(long lChIndex,BOOL bScanSrcOnly)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!MeasureOSAAmplifierForNET(lChIndex,bScanSrcOnly))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nOSACount)
	{
		m_strErrorMsg.Format("The OSA Channel Number is Error");
		return FALSE;	
	}
	
	dwErrorCode = m_ctrlOSA[lChIndex]->MeasureAmplifier(bScanSrcOnly);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Measure Amplifier Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	m_strErrorMsg = _T("No Error");
	return TRUE;
}
BOOL CDeviceManger::GetOSAChannelCount(long lChIndex,DWORD* pdwChannelCount)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!GetOSAChannelCountForNET(lChIndex,pdwChannelCount))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nOSACount)
	{
		m_strErrorMsg.Format("The OSA Channel Number is Error");
		return FALSE;	
	}
	
	dwErrorCode = m_ctrlOSA[lChIndex]->GetChannelCount(pdwChannelCount);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Get OSA Channel Count Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	if (*pdwChannelCount <0.0 || *pdwChannelCount > 10000.0)
	{
		m_strErrorMsg.Format("Current Value Is:%d,Get OSA Channel Count Out of Range",*pdwChannelCount);
		return FALSE;	
	}
	return TRUE;	
}
BOOL CDeviceManger::GetOSAChannelWaveLens(long lChIndex,double* pdblWL,DWORD* pdwChannelCount)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!GetOSAChannelWaveLensForNET(lChIndex,pdblWL,pdwChannelCount))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nOSACount)
	{
		m_strErrorMsg.Format("The OSA Channel Number is Error");
		return FALSE;	
	}
	dwErrorCode = m_ctrlOSA[lChIndex]->GetChannelWaveLens(pdblWL,pdwChannelCount);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Get OSA Channel Wavelength Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	return TRUE;	
}
BOOL CDeviceManger::GetOSAChannelNF(long lChIndex,double* pdblNF,DWORD* pdwChannelCount)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!GetOSAChannelNFForNET(lChIndex,pdblNF,pdwChannelCount))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nOSACount)
	{
		m_strErrorMsg.Format("The OSA Channel Number is Error");
		return FALSE;	
	}
	dwErrorCode = m_ctrlOSA[lChIndex]->GetChannelNF(pdblNF,pdwChannelCount);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Get OSA Channel NF Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	return TRUE;
}
BOOL CDeviceManger::GetOSAChannelGain(long lChIndex,double* pdblGain,DWORD* pdwChannelCount)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!GetOSAChannelGainForNET(lChIndex,pdblGain,pdwChannelCount))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nOSACount)
	{
		m_strErrorMsg.Format("The OSA Channel Number is Error");
		return FALSE;	
	}
	dwErrorCode = m_ctrlOSA[lChIndex]->GetChannelGain(pdblGain,pdwChannelCount);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Get OSA Channel Gain Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	return TRUE;	
}
BOOL CDeviceManger::GetOSAChannelSNR(long lChIndex,double* pdblSNR,DWORD* pdwChannelCount)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!GetOSAChannelSNRForNET(lChIndex,pdblSNR,pdwChannelCount))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nOSACount)
	{
		m_strErrorMsg.Format("The OSA Channel Number is Error");
		return FALSE;	
	}
	dwErrorCode = m_ctrlOSA[lChIndex]->GetChannelSNR(pdblSNR,pdwChannelCount);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Get OSA Channel SNR Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	return TRUE;	
}
BOOL CDeviceManger::GetOSAChannelSourcePower(long lChIndex,double* pdblSourcePow,DWORD* pdwChannelCount)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!GetOSAChannelSourcePowerForNET(lChIndex,pdblSourcePow,pdwChannelCount))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nOSACount)
	{
		m_strErrorMsg.Format("The OSA Channel Number is Error");
		return FALSE;	
	}
	dwErrorCode = m_ctrlOSA[lChIndex]->GetChannelSourcePower(pdblSourcePow,pdwChannelCount);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Get OSA Channel SNR Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	return TRUE;	
}
BOOL CDeviceManger::SetOSAAmpOffset(long lChIndex,double dblSourceOffset, double dblAmpOffset)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!SetOSAAmpOffsetForNET(lChIndex,dblSourceOffset,dblAmpOffset))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nOSACount)
	{
		m_strErrorMsg.Format("The OSA Channel Number is Error");
		return FALSE;	
	}
	dwErrorCode = m_ctrlOSA[lChIndex]->SetAmpOffset(dblSourceOffset,dblAmpOffset);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Setting OSA Amp Offset Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	return TRUE;	
}
BOOL CDeviceManger::GetOSAAmpOffset(long lChIndex,double &dblSourceOffset, double &dblAmpOffset)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!GetOSAAmpOffsetForNET(lChIndex,dblSourceOffset,dblAmpOffset))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nOSACount)
	{
		m_strErrorMsg.Format("The OSA Channel Number is Error");
		return FALSE;	
	}
	dwErrorCode = m_ctrlOSA[lChIndex]->GetAmpOffset(dblSourceOffset,dblAmpOffset);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Get OSA Amp Offset Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}

	return TRUE;
}
BOOL CDeviceManger::GetOSAEDFAResult(long lChIndex,double *pdblSumSrcSigPwr, double *pdblSumAmpSigPwr, double *pdblSunGain)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!GetOSAEDFAResultForNET(lChIndex,pdblSumSrcSigPwr,pdblSumAmpSigPwr,pdblSunGain))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nOSACount)
	{
		m_strErrorMsg.Format("The OSA Channel Number is Error");
		return FALSE;	
	}
	dwErrorCode = m_ctrlOSA[lChIndex]->GetEDFAResult(pdblSumSrcSigPwr,pdblSumAmpSigPwr,pdblSunGain);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Get OSA EDFA Result Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	return TRUE;	
}
BOOL CDeviceManger::GetOSAEDFAChResult(long lChIndex,DWORD *pwChCount, double *pdblChWL, double *pdblSrcpwr, double *pdblChGain, double *pdblChNF, double *pdblChAse,
									   double *pdblGainFlatness, double *pdblMaxNF, double* pdblMaxGain, double* pdblMinGain)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!GetOSAEDFAChResultForNET(lChIndex,pwChCount,pdblChWL,pdblSrcpwr,pdblChGain,pdblChNF,pdblChAse,pdblGainFlatness,pdblMaxNF,pdblMaxGain,pdblMinGain))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nOSACount)
	{
		m_strErrorMsg.Format("The OSA Channel Number is Error");
		return FALSE;	
	}
	dwErrorCode = m_ctrlOSA[lChIndex]->GetEDFAChResult(pwChCount,pdblChWL,pdblSrcpwr,pdblChGain,pdblChNF,pdblChAse,pdblGainFlatness,pdblMaxNF,pdblMaxGain,pdblMinGain);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Get OSA EDFA Channel Result Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}

	return TRUE;	
}
BOOL CDeviceManger::InitOSASingleSweep(long lChIndex,double dblStartWL, double dblStopWL, double dblRBW, DWORD dwSweepPoint)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!InitOSASingleSweepForNET(lChIndex,dblStartWL,dblStopWL,dblRBW,dwSweepPoint))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nOSACount)
	{
		m_strErrorMsg.Format("The OSA Channel Number is Error");
		return FALSE;	
	}
	dwErrorCode = m_ctrlOSA[lChIndex]->InitSingleSweep(dblStartWL,dblStopWL,dblRBW,dwSweepPoint);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Inital OSA Single Sweep Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}

	return TRUE;	
}

BOOL CDeviceManger::InitOSARepeatSweep(long lChIndex, double dblStartWL, double dblStopWL, double dblRBW, DWORD dwSweepPoint)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if (m_bUseNet)
	{
		if (!InitOSASingleSweepForNET(lChIndex, dblStartWL, dblStopWL, dblRBW, dwSweepPoint))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nOSACount)
	{
		m_strErrorMsg.Format("The OSA Channel Number is Error");
		return FALSE;
	}
	dwErrorCode = m_ctrlOSA[lChIndex]->InitSingleSweep(dblStartWL, dblStopWL, dblRBW, dwSweepPoint);
	if (dwErrorCode != SUCCESS)
	{
		m_strErrorMsg.Format("Inital OSA repeat Sweep Error,Error Code:%d", dwErrorCode);
		return FALSE;
	}

	return TRUE;
}


BOOL CDeviceManger::RunOSASweep(long lChIndex,double* pdblWL,double* pdblPower,char szSelTrace)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!RunOSASweepForNET(lChIndex,pdblWL,pdblPower,szSelTrace))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nOSACount)
	{
		m_strErrorMsg.Format("The OSA Channel Number is Error");
		return FALSE;	
	}
	dwErrorCode = m_ctrlOSA[lChIndex]->RunSweep(pdblWL,pdblPower,szSelTrace);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Run OSA Single Sweep Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	m_strErrorMsg = _T("No Error");
	return TRUE;	
}
BOOL CDeviceManger::GetSingleSweepPoint(long lChIndex,DWORD *pdwPointCount)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!GetSingleSweepPointForNET(lChIndex,pdwPointCount))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nOSACount)
	{
		m_strErrorMsg.Format("The OSA Channel Number is Error");
		return FALSE;	
	}
	dwErrorCode = m_ctrlOSA[lChIndex]->GetSingleSweepPoint(pdwPointCount);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Get OSA Single Sweep Point Count Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	return TRUE;
}

BOOL CDeviceManger::GetOSASweepData(long lChIndex,double* pdblWL,double* pdblPower, char szSelTrace)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!GetOSASweepDataForNET(lChIndex,pdblWL,pdblPower,szSelTrace))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nOSACount)
	{
		m_strErrorMsg.Format("The OSA Channel Number is Error");
		return FALSE;	
	}
	dwErrorCode = m_ctrlOSA[lChIndex]->GetSweepData(pdblWL,pdblPower,szSelTrace);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Get OSA Single Sweep Data Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}

	return TRUE;	
}

BOOL CDeviceManger::SaveOSADataToPC(long lChIndex,LPCTSTR lpSavePath, LPCTSTR lpDataType, LPCTSTR lpFileType, char szSelTrace)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!SaveOSADataToPCForNET(lChIndex,lpSavePath,lpDataType,lpFileType,szSelTrace))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nOSACount)
	{
		m_strErrorMsg.Format("The OSA Channel Number is Error");
		return FALSE;	
	}
	dwErrorCode = m_ctrlOSA[lChIndex]->SaveDatatoPC(lpSavePath,lpDataType,lpFileType,szSelTrace);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Save OSA Data To PC Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}

	return TRUE;	
}

BOOL CDeviceManger::SetOSACalibration(long lChIndex,DWORD dwCalibrationType)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!SetOSACalibrationForNET(lChIndex,dwCalibrationType))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nOSACount)
	{
		m_strErrorMsg.Format("The OSA Channel Number is Error");
		return FALSE;	
	}
	dwErrorCode = m_ctrlOSA[lChIndex]->SetCalibration(dwCalibrationType);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Setting OSA Calibration Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}

	return TRUE;	
}

BOOL CDeviceManger::GetZoomValue(long lChIndex,double dbWLNM,double dbBWNM,double *pdbGetValue)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!GetZoomValueForNET(lChIndex,dbWLNM,dbBWNM,pdbGetValue))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nOSACount)
	{
		m_strErrorMsg.Format("The OSA Channel Number is Error");
		return FALSE;	
	}
	dwErrorCode = m_ctrlOSA[lChIndex]->GetZoomValue(dbWLNM,dbBWNM,pdbGetValue);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Get OSA Zoom Value Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	m_strErrorMsg = _T("No Error");
	return TRUE;
}


////////////////////////////////////////////偏振控制器/////////////////////////////////
BOOL CDeviceManger::ClosePolDevice(long lChIndex)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!ClosePolDeviceForNET(lChIndex))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nPolCount)
	{
		m_strErrorMsg.Format("The PolControl Channel Number is Error");
		return FALSE;	
	}

	dwErrorCode = m_ctrlPOL[lChIndex]->CloseDevice();
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Close POL Device Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}

	return TRUE;	
}
BOOL CDeviceManger::ResetPolDevice(long lChIndex)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!ResetPolDeviceForNET(lChIndex))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nPolCount)
	{
		m_strErrorMsg.Format("The PolControl Channel Number is Error");
		return FALSE;	
	}

	dwErrorCode = m_ctrlPOL[lChIndex]->ResetDevice();
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Reset POL Device Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	return TRUE;	
}
BOOL CDeviceManger::GetPolDeviceInfo(long lChIndex,stDevInfo *stInfo)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if (lChIndex >= m_nPolCount)
	{
		m_strErrorMsg.Format("The PolControl Channel Number is Error");
		return FALSE;	
	}
	dwErrorCode = m_ctrlPOL[lChIndex]->GetDeviceInfo(stInfo);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Get POL Device Info Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	return TRUE;
}
BOOL CDeviceManger::GetPolCurrentPOSPolarizer(long lChIndex,double * pdblAlphaP,double *pdblAlphaQ,double *pdblAlphaH)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!GetPolCurrentPOSPolarizerForNET(lChIndex,pdblAlphaP,pdblAlphaQ,pdblAlphaH))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nPolCount)
	{
		m_strErrorMsg.Format("The PolControl Channel Number is Error");
		return FALSE;	
	}

	dwErrorCode = m_ctrlPOL[lChIndex]->GetCurrentPOSPolarizer(pdblAlphaP,pdblAlphaQ,pdblAlphaH);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Get POL Current Polarizer Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	return TRUE;
}
BOOL CDeviceManger::SetPolALL(long lChIndex,double alphaP, double alphaQ, double alphaH)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!SetPolALLForNET(lChIndex,alphaP,alphaQ,alphaH))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nPolCount)
	{
		m_strErrorMsg.Format("The PolControl Channel Number is Error");
		return FALSE;	
	}

	dwErrorCode = m_ctrlPOL[lChIndex]->SetALL(alphaP,alphaQ,alphaH);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Set POL All Polarizer Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	return TRUE;
}
BOOL CDeviceManger::SetPolDiagonalAngles(long lChIndex,double AlphaPMax, double Wavelength)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!SetPolDiagonalAnglesForNET(lChIndex,AlphaPMax,Wavelength))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nPolCount)
	{
		m_strErrorMsg.Format("The PolControl Channel Number is Error");
		return FALSE;	
	}

	dwErrorCode = m_ctrlPOL[lChIndex]->SetDiagonalAngles(AlphaPMax,Wavelength);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Set POL Diagonal Angles Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}

	return TRUE;
}
BOOL CDeviceManger::SetPolHorizontalAngles(long lChIndex,double AlphaPMax, double Wavelength)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!SetPolDiagonalAnglesForNET(lChIndex,AlphaPMax,Wavelength))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nPolCount)
	{
		m_strErrorMsg.Format("The PolControl Channel Number is Error");
		return FALSE;	
	}

	dwErrorCode = m_ctrlPOL[lChIndex]->SetHorizontalAngles(AlphaPMax,Wavelength);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Set POL Horizontal Angles Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	return TRUE;
}
BOOL CDeviceManger::SetPolPOSHalf(long lChIndex,double alpha)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!SetPolPOSHalfForNET(lChIndex,alpha))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nPolCount)
	{
		m_strErrorMsg.Format("The PolControl Channel Number is Error");
		return FALSE;	
	}

	dwErrorCode = m_ctrlPOL[lChIndex]->SetPOSHalf(alpha);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Set POL Half Angles Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}

	return TRUE;
}
BOOL CDeviceManger::SetPolPOSPolarizer(long lChIndex,double alpha)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
    if(m_bUseNet)
	{
		if(!SetPolPOSPolarizerForNET(lChIndex,alpha))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nPolCount)
	{
		m_strErrorMsg.Format("The PolControl Channel Number is Error");
		return FALSE;	
	}

	dwErrorCode = m_ctrlPOL[lChIndex]->SetPOSPolarizer(alpha);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Set POL Polarizer Angles Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	return TRUE;
}
BOOL CDeviceManger::SetPolPOSQuarter(long lChIndex,double alpha)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!SetPolPOSQuarterForNET(lChIndex,alpha))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nPolCount)
	{
		m_strErrorMsg.Format("The PolControl Channel Number is Error");
		return FALSE;	
	}

	dwErrorCode = m_ctrlPOL[lChIndex]->SetPOSQuarter(alpha);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Set POL Quarter Angles Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}

	return TRUE;
}
BOOL CDeviceManger::SetPolRightHandCircularAngles(long lChIndex,double AlphaPMax, double Wavelength)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!SetPolRightHandCircularAnglesForNET(lChIndex,AlphaPMax,Wavelength))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nPolCount)
	{
		m_strErrorMsg.Format("The PolControl Channel Number is Error");
		return FALSE;	
	}

	dwErrorCode = m_ctrlPOL[lChIndex]->SetRightHandCircularAngles(AlphaPMax,Wavelength);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Set POL Right Hand Circular Angles Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}

	return TRUE;
}
BOOL CDeviceManger::SetPolVerticalAngles(long lChIndex,double AlphaPMax, double Wavelength)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!SetPolVerticalAnglesForNET(lChIndex,AlphaPMax,Wavelength))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nPolCount)
	{
		m_strErrorMsg.Format("The PolControl Channel Number is Error");
		return FALSE;	
	}

	dwErrorCode = m_ctrlPOL[lChIndex]->SetVerticalAngles(AlphaPMax,Wavelength);
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Set POL Vertical Angles Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}

	return TRUE;
}
///////////////////////////////////////////扫描部分有关/////////////////////////////////////
BOOL CDeviceManger::JudeDeviceWhetherScan(int nChannelIndex)
{
	BOOL bReturn = FALSE;
	//目前三种激光器都具备扫描功能
	for (int j=0;j<m_nPMCount;j++)
	{
		if (m_pPMSlotInfo[j].nLogicalChannel == nChannelIndex)
		{
			for(int i=0;i< m_nDeviceCount;i++)
			{
				if (m_ptrMainFrame[i].nIndex == m_pPMSlotInfo[j].nDevIndex && m_pPMSlotInfo[j].nSlotType == TAG_PM)
				{
					if (lstrcmp(m_ptrMainFrame[i].strCaption, "816X")==0 
						||lstrcmp(m_ptrMainFrame[i].strCaption, "N7744")==0
						||lstrcmp(m_ptrMainFrame[i].strCaption, "N7745")==0)
					{
						bReturn =  TRUE;
					}
					else
					{
						bReturn =  FALSE;
					}
					break;
				}			   
			}	
		}
	}
	return bReturn;
}

BOOL CDeviceManger::PrepareScan(long lTLSChIndex)
{
	DWORD dwErrorCode = ERROR_NOT_DOSCAN;
	long lSlot,lChannel;
	if (lTLSChIndex >= m_nTLSCount)
	{
		m_strErrorMsg.Format("The TLS Channel Number is Error");
		return FALSE;	
	}
	if (m_stScanParam.m_dwChannelNumber >= m_nPMCount)
	{
		m_strErrorMsg.Format("The PM Channel Number is Error");
		return FALSE;	
	}
	for (int i=0;i<m_stScanParam.m_dwChannelNumber;i++)
	{
		if (!JudeDeviceWhetherScan(i))
		{
			m_strErrorMsg.Format("PM Channel %d Can Not Do Scan Error,Error Code:%d",dwErrorCode);
			return FALSE;
		}
	}
	
	//初始化激光器
	dwErrorCode = m_ctrlTLS[lTLSChIndex]->PrepareScan(lTLSChIndex,&m_stScanParam);
    if (dwErrorCode !=SUCCESS)
	{
		m_strErrorMsg.Format("TLS Initial Scan Error,Error Code:%d",dwErrorCode);
		return FALSE;
    }
    //初始化功率计
	for (int nIndex =0;nIndex < m_stScanParam.m_dwChannelNumber;nIndex++)
	{
		if (!(m_stScanParam.m_dwChannelCfgLow & (1<<nIndex)))
		{
			continue;
		}
		lSlot = m_pPMSlotInfo[nIndex].nCurSlotIndex;
		lChannel= m_pPMSlotInfo[nIndex].chInfo.nCurChannel;
		dwErrorCode = m_ctrlPM[nIndex]->PrepareScan(lSlot,lChannel,&m_stScanParam);
		if (dwErrorCode !=SUCCESS)
		{
			m_strErrorMsg.Format("PM Initial Scan Error,Error Code:%d",dwErrorCode);
			return FALSE;
		}	
		
		dwErrorCode = m_ctrlPM[nIndex]->SetPMScanStart(lSlot,lChannel);
		if (dwErrorCode !=SUCCESS)
		{
			m_strErrorMsg.Format("TLS Initial Scan Error,Error Code:%d",dwErrorCode);
			return FALSE;
		}
	}
	
	return TRUE;
}

BOOL CDeviceManger::ExecuteScan(long lTLSChIndex,long lpScanRawDataPtr)
{
	stOp816XRawData m_ScanResult;
	stOp816XRawData stTempData;
	int nScanCount,nFlag;
	int nFirstRange;
	int nPMSettingRange;
	double* pdbWLArry[2]={NULL,NULL};
	double* pdbPMArry[2]={NULL,NULL};
	BOOL bSuccess = FALSE;
	CString strTemp;
	long lSlot,lChannel;
	DWORD dwErrorCode = SUCCESS;
	try
	{		
		m_ScanResult.m_pdblWavelengthArray = NULL;
		m_ScanResult.m_pdwDataArrayAddr  = NULL;
		stTempData.m_pdblWavelengthArray = NULL;
		stTempData.m_pdwDataArrayAddr = NULL;
		POp816XRawData pRawData = (POp816XRawData)lpScanRawDataPtr;
		ASSERT(pRawData->m_pdblWavelengthArray);
        //实际扫描点数
		DWORD dwRealPointCount = (DWORD)((m_stScanParam.m_dblStopWL - m_stScanParam.m_dblStartWL)/m_stScanParam.m_dblStepSize);
		
		for (DWORD i =0;i<dwRealPointCount;i++)
		{
			pRawData->m_pdblWavelengthArray[i] =  m_stScanParam.m_dblStartWL +i*m_stScanParam.m_dblStepSize;
		}
		//根据输入PM功率计算初始扫描Range
        nPMSettingRange = (int)(m_stScanParam.m_dblPWMPower/10)*10;
		nFirstRange = nPMSettingRange;
		
        //如果m_ScanParam.m_dwNumberOfScan>1,则表示进行多个Range叠加
		nScanCount = 1;
		nFlag = 0;
		for (DWORD nScanIndex=0;nScanIndex <= m_stScanParam.m_dwNumberOfScan;nScanIndex++ )
		{
			for (int nIndex =0;nIndex < m_stScanParam.m_dwChannelNumber;nIndex++)
			{
				if (!(m_stScanParam.m_dwChannelCfgLow & (1<<nIndex)))
				{
					continue;
				}
				lSlot = m_pPMSlotInfo[nIndex].nCurSlotIndex;
				lChannel= m_pPMSlotInfo[nIndex].chInfo.nCurChannel;
				dwErrorCode = m_ctrlPM[nIndex]->PrepareScan(lSlot,lChannel,&m_stScanParam);
				if (dwErrorCode !=SUCCESS)
				{
					strTemp.Format("PM Initial Scan Error,Error Code:%d",dwErrorCode);
					throw strTemp.GetBuffer(0);
				}	
				dwErrorCode = m_ctrlPM[nIndex]->SetRange(lSlot,lChannel,nPMSettingRange);
				if (dwErrorCode !=SUCCESS)
				{
					strTemp.Format("PM Set Range Error,Error Code:%d",dwErrorCode);
					throw strTemp.GetBuffer(0);
				}
				dwErrorCode = m_ctrlPM[nIndex]->SetPMScanStart(lSlot,lChannel);
				if (dwErrorCode !=SUCCESS)
				{
					strTemp.Format("TLS Initial Scan Error,Error Code:%d",dwErrorCode);
					throw strTemp.GetBuffer(0);
				}
			}
			//发送扫描trig
			dwErrorCode = m_ctrlTLS[lTLSChIndex]->SetScanStart(lTLSChIndex);
			if (dwErrorCode !=SUCCESS)
			{
				strTemp.Format("TLS Initial Scan Error,Error Code:%d",dwErrorCode);
				throw strTemp.GetBuffer(0);
			}
			if (nScanIndex > 0)
			{
				//获得扫描波长
				if (stTempData.m_pdblWavelengthArray ==NULL)
				{
					stTempData.m_pdblWavelengthArray = (double*)VirtualAlloc(NULL,sizeof(double)*m_stScanParam.m_dwSampleCount,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
					dwErrorCode =m_ctrlTLS[lTLSChIndex]->GetLamdaScanWLResult(lTLSChIndex,stTempData.m_pdblWavelengthArray );
					if (dwErrorCode!=SUCCESS)
					{
						strTemp.Format("Get TLS Scan WL Error,Error Code:%d",dwErrorCode);
						throw strTemp.GetBuffer(0);
					}
				}
				//获得通道扫描数据
				if (stTempData.m_pdwDataArrayAddr ==NULL)
				{
					stTempData.m_pdwDataArrayAddr = (DWORD*)VirtualAlloc(NULL,sizeof(DWORD)*m_stScanParam.m_dwChannelNumber,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
					for (DWORD i=0;i<m_stScanParam.m_dwChannelNumber;i++)
					{					
						if (!(m_stScanParam.m_dwChannelCfgLow & (1<<i)))
						{
							continue;
						}
						
						double* pGetData = (double*)VirtualAlloc(NULL,sizeof(double)*m_stScanParam.m_dwSampleCount,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
						stTempData.m_pdwDataArrayAddr[i] = (DWORD)pGetData;	
						lSlot = m_pPMSlotInfo[nIndex].nCurSlotIndex;
						lChannel= m_pPMSlotInfo[nIndex].chInfo.nCurChannel;
						
						dwErrorCode = m_ctrlPM[nIndex]->getLambdaScanPMResult(lSlot,lChannel,pGetData);
						if (dwErrorCode !=SUCCESS)
						{
							strTemp.Format("Get PM Scan Data Error,Error Code:%d",dwErrorCode);
							throw strTemp.GetBuffer(0);
						}
						//进行两个Range的叠加
						double *pdbTemp =(double*)m_ScanResult.m_pdwDataArrayAddr[i];
						m_Algorith.GetMergeArray(pdbTemp,pGetData,nFirstRange,20,m_stScanParam.m_dwSampleCount);
						double *dbpTempData = (double*)pRawData->m_pdwDataArrayAddr[i];
						m_Algorith.LinearFitRaw(m_ScanResult.m_pdblWavelengthArray,pdbTemp,m_stScanParam.m_dwSampleCount,
							pRawData->m_pdblWavelengthArray,dwRealPointCount,dbpTempData);	
					}
				}
			}
			else
			{
				//获得扫描波长
				if (m_ScanResult.m_pdblWavelengthArray ==NULL)
				{
					m_ScanResult.m_pdblWavelengthArray = (double*)VirtualAlloc(NULL,sizeof(double)*m_stScanParam.m_dwSampleCount,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
					dwErrorCode =m_ctrlTLS[lTLSChIndex]->GetLamdaScanWLResult(lTLSChIndex,stTempData.m_pdblWavelengthArray );
					if (dwErrorCode!=SUCCESS)
					{
						strTemp.Format("Get TLS Scan WL Error,Error Code:%d",dwErrorCode);
						throw strTemp.GetBuffer(0);
					}
				}
				//获得通道扫描数据
				if (m_ScanResult.m_pdwDataArrayAddr ==NULL)
				{
					m_ScanResult.m_pdwDataArrayAddr = (DWORD*)VirtualAlloc(NULL,sizeof(DWORD)*m_stScanParam.m_dwChannelNumber,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
					for (DWORD i=0;i<m_stScanParam.m_dwChannelNumber;i++)
					{
						if (!(m_stScanParam.m_dwChannelCfgLow & (1<<i)))
						{
							continue;
						}
						
						double* pGetData = (double*)VirtualAlloc(NULL,sizeof(double)*m_stScanParam.m_dwSampleCount,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
						m_ScanResult.m_pdwDataArrayAddr[i] =(DWORD)pGetData;	
						
						lSlot = m_pPMSlotInfo[nIndex].nCurSlotIndex;
						lChannel= m_pPMSlotInfo[nIndex].chInfo.nCurChannel;
						
						dwErrorCode = m_ctrlPM[nIndex]->getLambdaScanPMResult(lSlot,lChannel,pGetData);
						if (dwErrorCode !=SUCCESS)
						{
							strTemp.Format("Get PM Scan Data Error,Error Code:%d",dwErrorCode);
							throw strTemp.GetBuffer(0);
						}
						if (m_Algorith.JudgePowerRangeIsOK(pGetData,m_stScanParam.m_dwSampleCount)) 
						{
							nScanCount = 0;
						}
						else
						{
							nScanCount = 1;
						}
						nFlag |= nScanCount;
						if (nScanCount ==0)
						{
							//线性内插
							double *dbpTempData = (double*)pRawData->m_pdwDataArrayAddr[i];
							m_Algorith.LinearFitRaw(m_ScanResult.m_pdblWavelengthArray,pGetData,m_stScanParam.m_dwSampleCount,
								pRawData->m_pdblWavelengthArray,dwRealPointCount,dbpTempData);		
						}						
					}
					
					m_stScanParam.m_dwNumberOfScan = nFlag;				
				}			
			}
			
			nPMSettingRange -= 20;
		}
		bSuccess = TRUE;
	}
	catch (char* pszMsg)
	{
		m_strErrorMsg = pszMsg;
		bSuccess =  FALSE;
	}
	if (m_ScanResult.m_pdblWavelengthArray !=NULL)
	{
		VirtualFree(m_ScanResult.m_pdblWavelengthArray,0,MEM_RELEASE);
		m_ScanResult.m_pdblWavelengthArray = NULL;
	}
	if (m_ScanResult.m_pdwDataArrayAddr !=NULL)
	{
		double* pGetData;
		for (DWORD i=0;i<m_stScanParam.m_dwChannelNumber;i++)
		{
			pGetData = (double*)m_ScanResult.m_pdwDataArrayAddr[i];
			VirtualFree(pGetData,0,MEM_RELEASE);
			pGetData  =NULL;
		}
		VirtualFree(m_ScanResult.m_pdwDataArrayAddr,0,MEM_RELEASE);
		m_ScanResult.m_pdwDataArrayAddr = NULL;
	}
	if (stTempData.m_pdblWavelengthArray !=NULL)
	{
		VirtualFree(m_ScanResult.m_pdblWavelengthArray,0,MEM_RELEASE);
		m_ScanResult.m_pdblWavelengthArray = NULL;
	}
	if (stTempData.m_pdwDataArrayAddr !=NULL)
	{
		double* pGetData;
		for (DWORD i=0;i<m_stScanParam.m_dwChannelNumber;i++)
		{
			pGetData = (double*)stTempData.m_pdwDataArrayAddr[i];
			VirtualFree(pGetData,0,MEM_RELEASE);
			pGetData  =NULL;
		}
		VirtualFree(stTempData.m_pdwDataArrayAddr,0,MEM_RELEASE);
		stTempData.m_pdwDataArrayAddr = NULL;
	}
	return bSuccess;
}

BOOL CDeviceManger::ReleaseScan(long lTLSChIndex)
{
	DWORD dwErrorCode = ERROR_NOT_DOSCAN;
	long lSlot,lChannel;
	if (lTLSChIndex >= m_nTLSCount)
	{
		m_strErrorMsg.Format("The TLS Channel Number is Error");
		return FALSE;	
	}
	if (m_stScanParam.m_dwChannelNumber >= m_nPMCount)
	{
		m_strErrorMsg.Format("The PM Channel Number is Error");
		return FALSE;	
	}
	
	//初始化激光器
	dwErrorCode = m_ctrlTLS[lTLSChIndex]->SetScanStop(lTLSChIndex);
    if (dwErrorCode !=SUCCESS)
	{
		m_strErrorMsg.Format("TLS Scan Stop Error,Error Code:%d",dwErrorCode);
		return FALSE;
    }
    //初始化功率计
	for (int nIndex =0;nIndex < m_stScanParam.m_dwChannelNumber;nIndex++)
	{
		if (!(m_stScanParam.m_dwChannelCfgLow & (1<<nIndex)))
		{
			continue;
		}
		lSlot = m_pPMSlotInfo[nIndex].nCurSlotIndex;
		lChannel= m_pPMSlotInfo[nIndex].chInfo.nCurChannel;
		dwErrorCode = m_ctrlPM[nIndex]->SetPMScanStop(lSlot,lChannel);
		if (dwErrorCode !=SUCCESS)
		{
			m_strErrorMsg.Format("PM Scan Stop Error,Error Code:%d",dwErrorCode);
			return FALSE;
		}
		dwErrorCode = m_ctrlPM[nIndex]->SetPMScanTriggerStop(lSlot,lChannel);
		if (dwErrorCode !=SUCCESS)
		{
			m_strErrorMsg.Format("PM Trigger Stop Error,Error Code:%d",dwErrorCode);
			return FALSE;
		}
	}
	
	return TRUE;	
}
///////////////////////////////////////////////////////////////////////////////
//函数说明：
//    根据扫描的偏振态数，计算平均扫描功率
//Add by wanxin
//////////////////////////////////////////////////////////////////////////////
BOOL CDeviceManger::CalAveragePower(POp816XRawData stScanData,int nSweepCount)
{
	double *pdbTempArry = NULL;
	double dbTemp = 0.0;
	DWORD dwScanPoint;
	dwScanPoint =  m_stScanParam.m_dwSampleCount;
	
	for(DWORD dwChannelIndex = 0;dwChannelIndex < m_stScanParam.m_dwChannelNumber;dwChannelIndex++)
	{
		if((m_stScanParam.m_dwChannelCfgLow & (1 << dwChannelIndex)))
		{
			pdbTempArry = (double*)(stScanData->m_pdwDataArrayAddr[dwChannelIndex]);
			
			for (DWORD dwIndex =0;dwIndex < dwScanPoint;dwIndex++)
			{
				dbTemp = 0.0;
				for (int nIndex =0;nIndex < nSweepCount;nIndex++)
				{
					//double * pdbTempData = pdbTempArry[(nIndex+1)*dwScanPoint];
					dbTemp +=  pdbTempArry[(nIndex+1)*dwScanPoint+dwIndex];
				}
				//dbTemp = pdblData1[dwIndex] + pdblData2[dwIndex] + pdblData3[dwIndex] + pdblData3[dwIndex];
                pdbTempArry[dwIndex] = dbTemp / nSweepCount;
			}
		}
	}
	
	return TRUE;
}

BOOL CDeviceManger::DoTLSN7744Scan(long lTLSChIndex,int nType)
{
	CString strFileName;
	CString strPath,strTemp;
	
	BOOL bSucess =FALSE;
	double dbAlphaAngle;
	int   nPolChIndex;	
	POp816XRawData   pstScanPtr =NULL;
	try
	{
		if (nType ==0)
		{
            pstScanPtr = m_pstRefScanData;
		}
		else if(nType ==1)
		{
			pstScanPtr = m_pstDoScanData;
		}
		
		dbAlphaAngle = m_stScanParam.m_dbAlphaAngle;
		nPolChIndex =  m_stScanParam.m_nPolChIndex;
		//初始化扫描
		if (!PrepareScan(lTLSChIndex))
		{
			throw "Initial TLS And PM Scan Error";
		}
		
		//如果采用带PDL扫描，即扫描4次取平均功率
		if (m_stScanParam.m_bDoPDL)
		{
			AllocPDLScanStruct(pstScanPtr);
			//开辟读取扫描数据的空间
			AllocScanStruct(&m_stScanData);
			double  dblCentralWL = (m_stScanParam.m_dblStopWL+m_stScanParam.m_dblStartWL)/2;
			
			//扫描4个偏振态
			for (int nSweepIndex=0;nSweepIndex<PDLSCANCOUNT;nSweepIndex++)
			{		
				switch (nSweepIndex)
				{
				case 0:
					// set the HP8169A horizontal angles here
					SetPolHorizontalAngles(nPolChIndex,dbAlphaAngle,dblCentralWL);
					break;				
				case 1:
					// set the HP8169A vertical angles here
					SetPolVerticalAngles(nPolChIndex,dbAlphaAngle,dblCentralWL);
					break;				
				case 2:
					// set the HP8169A Diagonal angles here
					SetPolDiagonalAngles(nPolChIndex,dbAlphaAngle,dblCentralWL);
					break;				
				case 3:
					// set the HP8169A right hand circular angles here
					SetPolRightHandCircularAngles(nPolChIndex,dbAlphaAngle,dblCentralWL);
					break;
				}
				//执行扫描并获得扫描数据
				if (!ExecuteScan(lTLSChIndex,(long)&m_stScanData))
				{
					throw" Execute Scan Error";
				}
				for(DWORD dwChannelIndex = 0;dwChannelIndex < m_stScanParam.m_dwChannelNumber;dwChannelIndex ++)
				{
					if((m_stScanParam.m_dwChannelCfgLow & (1 << dwChannelIndex)))
					{
						double *pdblDataArray = (double*)(pstScanPtr->m_pdwDataArrayAddr[dwChannelIndex]) + ((nSweepIndex+1)*m_stScanParam.m_dwSampleCount);
						double *pdbTempData = (double*)m_stScanData.m_pdwDataArrayAddr[dwChannelIndex];
						for(DWORD dwSampleIndex = 0; dwSampleIndex < m_stScanParam.m_dwSampleCount; dwSampleIndex ++)
						{
							pdblDataArray[dwSampleIndex] = pdbTempData[dwSampleIndex];
							pstScanPtr->m_pdblWavelengthArray[dwSampleIndex] = m_stScanData.m_pdblWavelengthArray[dwSampleIndex];
						}
					}
				}
			}			
			
			//计算平均功率,保存测试结果数据
			if (!CalAveragePower(pstScanPtr,PDLSCANCOUNT))
			{
				throw "Calculate Average Power Error";
			}			
		}
		else
		{	
			AllocScanStruct(pstScanPtr);		
			//执行扫描并获得扫描数据
			if (!ExecuteScan(lTLSChIndex,(long)pstScanPtr))
			{
				throw" Execute Scan Error";
			}
		}
		bSucess = TRUE;
	}
	catch (char* pstrMsg)
	{
		m_strErrorMsg = pstrMsg;
		bSucess = FALSE;
	}
    ReleaseAllocStruct(&m_stScanData);
	return bSucess;	
}
//////////////////////////////////////////////////////////////////
//函数说明：
//    如果是采用8169扫描PDL，开辟结构体空间函数
// 数组0: the average Power array
// 数组1: the horizontal power array
// 数组2: the vertical power array
// 数组3: the diagonal power array
// 数组4: the right hand circuital power array
//Add by wanxin
//////////////////////////////////////////////////////////////////
void CDeviceManger::AllocPDLScanStruct(POp816XRawData pData)
{
	
	int nScanPoint = m_stScanParam.m_dwSampleCount;
	
	if (pData->m_pdblWavelengthArray!=NULL)
	{
		VirtualFree(pData->m_pdblWavelengthArray,0,MEM_RELEASE);
		pData->m_pdblWavelengthArray = NULL;
	}
	if (pData->m_pdwDataArrayAddr !=NULL)
	{
		for (int nChannelIndex=0;nChannelIndex<m_stScanParam.m_dwChannelNumber;nChannelIndex++)
		{
			if((m_stScanParam.m_dwChannelCfgLow & (1 << nChannelIndex)))
			{
				double *pTemp = (double*)pData->m_pdwDataArrayAddr[nChannelIndex];
				if(pTemp !=NULL)
				{
					VirtualFree(pTemp,0,MEM_RELEASE);
					pTemp = NULL;
				}				
			}
		}	
		VirtualFree(pData->m_pdwDataArrayAddr,0,MEM_RELEASE);
		pData->m_pdwDataArrayAddr = NULL;
	}
	
	if (pData->m_pdblWavelengthArray ==NULL) 
	{
		pData->m_pdblWavelengthArray =(double*)VirtualAlloc(NULL,nScanPoint*sizeof(double)
			,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
		ZeroMemory(pData->m_pdblWavelengthArray,sizeof(double)*nScanPoint);
	}
	if (pData->m_pdwDataArrayAddr==NULL)
	{
		pData->m_pdwDataArrayAddr=(DWORD*)VirtualAlloc(NULL,m_stScanParam.m_dwChannelNumber*sizeof(DWORD),MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
		
		for (int nChannelIndex=0;nChannelIndex<m_stScanParam.m_dwChannelNumber;nChannelIndex++)
		{			
			if((m_stScanParam.m_dwChannelCfgLow & (1 << nChannelIndex)))
			{
				double* pdbData = (double*)VirtualAlloc(NULL,5*nScanPoint*sizeof(double),MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
				ZeroMemory(pdbData,sizeof(double)*nScanPoint*5);
				pData->m_pdwDataArrayAddr[nChannelIndex] = (DWORD)pdbData;	
			}
		}
	}
}
///////////////////////////////////////////////////////////
//函数说明：
//    开辟扫描结构体需要的空间
//Add by wanxin
//////////////////////////////////////////////////////////
void CDeviceManger::AllocScanStruct(POp816XRawData pData)
{
	int nScanPoint = m_stScanParam.m_dwSampleCount;
	if (pData->m_pdblWavelengthArray!=NULL)
	{
		VirtualFree(pData->m_pdblWavelengthArray,0,MEM_RELEASE);
        pData->m_pdblWavelengthArray = NULL;
	}
	if (pData->m_pdwDataArrayAddr !=NULL)
	{
		for (int nChannelIndex=0;nChannelIndex<m_stScanParam.m_dwChannelNumber;nChannelIndex++)
		{
			if((m_stScanParam.m_dwChannelCfgLow & (1 << nChannelIndex)))
			{
				double *pTemp = (double*)pData->m_pdwDataArrayAddr[nChannelIndex];
				if(pTemp!=NULL)
				{
					VirtualFree(pTemp,0,MEM_RELEASE);
					pTemp = NULL;
				}
				
			}
		}	
        VirtualFree(pData->m_pdwDataArrayAddr,0,MEM_RELEASE);
		pData->m_pdwDataArrayAddr = NULL;
	}
	
	if (pData->m_pdblWavelengthArray ==NULL) 
	{
		pData->m_pdblWavelengthArray =(double*)VirtualAlloc(NULL,nScanPoint*sizeof(double)
			,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
		ZeroMemory(pData->m_pdblWavelengthArray,sizeof(double)*nScanPoint);
	}
	if (pData->m_pdwDataArrayAddr==NULL)
	{
		pData->m_pdwDataArrayAddr=(DWORD*)VirtualAlloc(NULL,m_stScanParam.m_dwChannelNumber*sizeof(DWORD),MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
		
		for (int nChannelIndex=0;nChannelIndex<m_stScanParam.m_dwChannelNumber;nChannelIndex++)
		{
			if((m_stScanParam.m_dwChannelCfgLow & (1 << nChannelIndex)))
			{
				double* pdbData = (double*)VirtualAlloc(NULL,nScanPoint*sizeof(double),MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
				ZeroMemory(pdbData,sizeof(double)*nScanPoint);
				pData->m_pdwDataArrayAddr[nChannelIndex] = (DWORD)pdbData;
			}
		}
	}	
}
///////////////////////////////////////////////////////////
//函数说明：
//    释放扫描结构体需要的空间
//Add by wanxin
//Time:20131221
//////////////////////////////////////////////////////////
BOOL CDeviceManger::ReleaseAllocStruct(POp816XRawData pData)
{
	try
	{
		int nScanPoint = m_stScanParam.m_dwSampleCount;
		if (pData->m_pdblWavelengthArray !=NULL) 
		{
			VirtualFree(pData->m_pdblWavelengthArray,0,MEM_RELEASE);
			pData->m_pdblWavelengthArray  = NULL;
		}
		if (pData->m_pdwDataArrayAddr!=NULL)
		{
			
			if (pData->m_pdblWavelengthArray!=NULL)
			{
				VirtualFree(pData->m_pdblWavelengthArray,0,MEM_RELEASE);
				pData->m_pdblWavelengthArray = NULL;
			}
			if (pData->m_pdwDataArrayAddr !=NULL)
			{
				for (int nChannelIndex=0;nChannelIndex<m_stScanParam.m_dwChannelNumber;nChannelIndex++)
				{
					if((m_stScanParam.m_dwChannelCfgLow & (1 << nChannelIndex)))
					{
						double *pTemp = (double*)pData->m_pdwDataArrayAddr[nChannelIndex];
						VirtualFree(pTemp,0,MEM_RELEASE);
					}
				}	
				VirtualFree(pData->m_pdwDataArrayAddr,0,MEM_RELEASE);
				pData->m_pdwDataArrayAddr = NULL;
			}
		}
	}
	catch (...)
	{
		m_strErrorMsg="Release Struct Error";
		return FALSE;
	}
	
	return TRUE;
}
BOOL CDeviceManger::DoScanRef(long lTLSChIndex)
{
	CString        strTemp;
	CString          strFileName,strMsg;
	if(m_stScanParam.m_nPDLType == 0)
	{
		//        //采用com组件扫描归零
		//		if(!DoAgServerRef())
		//		{
		//			return FALSE;
		//		}
	}
	else if(m_stScanParam.m_nPDLType == 1)
	{        
		//扫描归零
		if (!DoTLSN7744Scan(lTLSChIndex,0))
        {
			return FALSE ;
        }
	}
	return TRUE;
}

BOOL CDeviceManger::DoScan(long lTLSChIndex)
{
	CString        strTemp;
	CString          strFileName,strMsg;
	if(m_stScanParam.m_nPDLType == 0)
	{
		//        //采用com组件扫描归零
		//		if(!DoAgServerRef())
		//		{
		//			return FALSE;
		//		}
	}
	else if(m_stScanParam.m_nPDLType == 1)
	{        
		//扫描归零
		if (!DoTLSN7744Scan(lTLSChIndex,1))
        {
			return FALSE ;
        }
	}
	return TRUE;
}

BOOL CDeviceManger::GetCalILResult(POp816XRawData pCalData)
{
	AllocScanStruct(pCalData);
	//计算IL和PDL
	if (!CalTestResult(m_pstRefScanData,m_pstDoScanData,pCalData))
	{
		m_strErrorMsg = " Calculate IL Result Error";
		return FALSE;
	}
	return TRUE;	
}

BOOL CDeviceManger::GetCalILAndPDLResult(POp816XRawData pCalData)
{
	AllocPDLScanStruct(pCalData);
	if (!m_stScanParam.m_bDoPDL)
	{
		m_strErrorMsg = " Don't Do PDL Scan, Can not Cal IL AND PDL";
		return FALSE;
	}
	//计算IL和PDL
	if (!CalTestResult(m_pstRefScanData,m_pstDoScanData,pCalData))
	{
		m_strErrorMsg = " Calculate PDL And IL Result Error";
		return FALSE;
	}
	return TRUE;
}
//////////////////////////////////////////////////////////////////////////////
//函数说明：
//    计算TLS +8169 + N7744最终扫描后输出结果数据
//Add by wanxin
//Time:20140312
////////////////////////////////////////////////////////////////////////////////
BOOL CDeviceManger::CalTestResult(POp816XRawData pRefData,POp816XRawData pScanData,POp816XRawData pResult)
{
	double *pdbRefArry = NULL;
	double *pdbScanArry = NULL;
	double *pdbResult = NULL;
	double *pdbWL = NULL;
	double dbTemp = 0.0;
	DWORD dwScanPoint;
	dwScanPoint = m_stScanParam.m_dwSampleCount;
	
	ASSERT(pRefData);
	ASSERT(pScanData);
	ASSERT(pResult);
	if (m_stScanParam.m_bDoPDL) 
	{
		//计算差损
		for(DWORD dwChannelIndex = 0;dwChannelIndex < m_stScanParam.m_dwChannelNumber;dwChannelIndex ++)
		{
			if(m_stScanParam.m_dwChannelCfgLow & (1 << dwChannelIndex))
			{
				pdbRefArry = (double*)pRefData->m_pdwDataArrayAddr[dwChannelIndex];
				pdbScanArry =(double*)pScanData->m_pdwDataArrayAddr[dwChannelIndex];
				pdbResult =(double*)pResult->m_pdwDataArrayAddr[dwChannelIndex];
				
				for (DWORD dwIndex =0;dwIndex < dwScanPoint;dwIndex++)
				{
					//波长
                    pResult->m_pdblWavelengthArray[dwIndex] = pScanData->m_pdblWavelengthArray[dwIndex];
                    //计算平均功率差损
					pdbResult[dwIndex] = pdbRefArry[dwIndex] - pdbScanArry[dwIndex];
				}
				if(!CalculatePDL(dwScanPoint,pdbRefArry,pdbScanArry,pdbResult))
				{
					return FALSE;
				}
			}
		}	
	}
    else
	{
		//计算差损
		for(DWORD dwChannelIndex = 0;dwChannelIndex < m_stScanParam.m_dwChannelNumber;dwChannelIndex ++)
		{
			if(m_stScanParam.m_dwChannelCfgLow & (1 << dwChannelIndex))
			{
				pdbRefArry = (double*)pRefData->m_pdwDataArrayAddr[dwChannelIndex];
				pdbScanArry =(double*)pScanData->m_pdwDataArrayAddr[dwChannelIndex];
				pdbResult =(double*)pResult->m_pdwDataArrayAddr[dwChannelIndex];
				
				for (DWORD dwIndex =0;dwIndex < dwScanPoint;dwIndex++)
				{
					//波长
                    pResult->m_pdblWavelengthArray[dwIndex] = pScanData->m_pdblWavelengthArray[dwIndex];
                    //计算平均功率差损
					pdbResult[dwIndex] = pdbRefArry[dwIndex]- pdbScanArry[dwIndex];
				}
			}
		}
	}
	
	return TRUE;
}
////////////////////////////////////////////////////////////////////
//函数说明：
//    计算PDL函数
//Add by wanxin
//20140312
///////////////////////////////////////////////////////////////////
BOOL CDeviceManger::CalculatePDL(DWORD dwSampleCount, double* pRefRawData,  double* pTestRawData, double* pResultRawData)
{
	BOOL   bFunctionOK = FALSE;
	double  Pa, Pb, Pc, Pd, P1, P2, P3, P4;
	double T1, T2, T3, T4, m11, m12, m13, m14;
	double TempSqrt, Tmax, Tmin; 
	double * m_Pas,*m_Pbs,*m_Pcs,*m_Pds;
	double * m_tPas,*m_tPbs,*m_tPcs,*m_tPds;
	double * pResult;
	CString strTemp;
	
	try
	{
		if(pRefRawData == NULL)
		{
			throw "Ref Data Empty";
		}
		if(pTestRawData == NULL)
		{
			throw "Test Data Empty";
		}
		if(pResultRawData == NULL)
		{
			throw "Result Struct Empty";
		}
		
		
		m_Pas	 = ((double*)pRefRawData) + dwSampleCount;
		m_Pbs	 = ((double*)pRefRawData) + dwSampleCount*2;
		m_Pcs	 = ((double*)pRefRawData) + dwSampleCount*3;
		m_Pds	 = ((double*)pRefRawData) + dwSampleCount*4;
		
		m_tPas	 = ((double*)pTestRawData) + dwSampleCount;
		m_tPbs	 = ((double*)pTestRawData) + dwSampleCount*2;
		m_tPcs	 = ((double*)pTestRawData) + dwSampleCount*3;
		m_tPds	 = ((double*)pTestRawData) + dwSampleCount*4;
		
		pResult = ((double*)pResultRawData) + dwSampleCount;
		// calculate the PDL value
		for (DWORD i = 0; i < dwSampleCount; i++)
		{
			Pa = pow(10, m_Pas[i]/10.0);
			Pb = pow(10, m_Pbs[i]/10.0);
			Pc = pow(10, m_Pcs[i]/10.0);
			Pd = pow(10, m_Pds[i]/10.0);
			
			P1 = pow(10, m_tPas[i]/10.0);
			P2 = pow(10, m_tPbs[i]/10.0);
			P3 = pow(10, m_tPcs[i]/10.0);
			P4 = pow(10, m_tPds[i]/10.0);
			
			T1 = P1 / Pa;
			T2 = P2 / Pb;
			T3 = P3 / Pc;
			T4 = P4 / Pd;
			
			m11 = (T1+T2) / 2.0;
			m12 = (T1-T2) / 2.0;
			m13 = T3-m11;
			m14 = T4-m11;
			
			
			if((m12 * m12 + m13 * m13 + m14 * m14)<0)
			{
				throw "Calculate PDL Other Error";
			}
			
			TempSqrt = sqrt(m12 * m12 + m13 * m13 + m14 * m14);
			
			Tmax	 = m11 + TempSqrt;
			Tmin	 = m11 - TempSqrt;
			
			pResult[i] = 10.0*log10(fabs(Tmax / Tmin));
		}
		
		// until to here the function is OK now
		bFunctionOK = TRUE;
	}
	catch(TCHAR* ptszErrorMsg)
	{
		bFunctionOK = FALSE;
		m_strErrorMsg = ptszErrorMsg;
	}
	catch(...)
	{
		m_strErrorMsg ="Calculate PDL Error";
		bFunctionOK = FALSE;
	}	
	return bFunctionOK;	
}
///////////////////////////////////循环箱///////////////////////////////////////
BOOL  CDeviceManger::CloseChamberDevice(long lChIndex)
{
	DWORD dwErrorCode;	
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!CloseChamberDeviceForNET(lChIndex))
		{
			return FALSE;
		}
		return TRUE;
	}
	if (lChIndex >= m_nChamberCount)
	{
		m_strErrorMsg.Format("The Chamber Channel Number is Error");
		return FALSE;	
	}

	dwErrorCode = m_ctrlChamber[lChIndex]->CloseDevice();
	
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Close Chamber Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	m_strErrorMsg = _T("No Error");
	return TRUE;	
}
BOOL  CDeviceManger::GetChamberDeviceInfo(long lChIndex,stDevInfo *stInfo)
{
	DWORD dwErrorCode;	
	m_strErrorMsg = _T("No Error");
	if (lChIndex >= m_nChamberCount)
	{
		m_strErrorMsg.Format("The Chamber Channel Number is Error");
		return FALSE;	
	}
	dwErrorCode = m_ctrlChamber[lChIndex]->GetDeviceInfo(stInfo);
	
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Get Chamber Device Info Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	m_strErrorMsg = _T("No Error");
	return TRUE;	
}
BOOL  CDeviceManger::SetChamberRunStop(long lChIndex)
{
	DWORD dwErrorCode;	
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!SetChamberRunStopForNET(lChIndex))
		{
			return FALSE;
		}
		return TRUE;
	}	
	if (lChIndex >= m_nChamberCount)
	{
		m_strErrorMsg.Format("The Chamber Channel Number is Error");
		return FALSE;	
	}

	dwErrorCode = m_ctrlChamber[lChIndex]->SetChamberRunStop();
	
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Set Chamber Run Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	m_strErrorMsg = _T("No Error");
	return TRUE;	
}
BOOL  CDeviceManger::SetChamberRunStart(long lChIndex)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!SetChamberRunStartForNET(lChIndex))
		{
			return FALSE;
		}
		return TRUE;
	}	
	if (lChIndex >= m_nChamberCount)
	{
		m_strErrorMsg.Format("The Chamber Channel Number is Error");
		return FALSE;	
	}

	dwErrorCode = m_ctrlChamber[lChIndex]->SetChamberRunStart();
	
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Set Chamber Run Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	m_strErrorMsg = _T("No Error");
	return TRUE;	
}
BOOL  CDeviceManger::SetChamberSetPoint(long lChIndex,double dbSetPoint)
{
	DWORD dwErrorCode;	
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!SetChamberSetPointForNET(lChIndex,dbSetPoint))
		{
			return FALSE;
		}
		return TRUE;
	}	
	if (lChIndex >= m_nChamberCount)
	{
		m_strErrorMsg.Format("The Chamber Channel Number is Error");
		return FALSE;	
	}
	
	dwErrorCode = m_ctrlChamber[lChIndex]->SetChamberSetPoint(dbSetPoint);
	
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Set Chamber Temp Point Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	return TRUE;
}
BOOL  CDeviceManger::GetChamberSetPoint(long lChIndex,double* dbSetPoint)
{
	DWORD dwErrorCode;	
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!GetChamberSetPointForNET(lChIndex,dbSetPoint))
		{
			return FALSE;
		}
		return TRUE;
	}	
	if (lChIndex >= m_nChamberCount)
	{
		m_strErrorMsg.Format("The Chamber Channel Number is Error");
		return FALSE;	
	}

	dwErrorCode = m_ctrlChamber[lChIndex]->GetChamberSetPoint(dbSetPoint);
	
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Get Chamber Temp Point Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	
	return TRUE;
}
BOOL  CDeviceManger::GetChamberCurrentTemp(long lChIndex,double *dbCurrTemp)
{
	DWORD dwErrorCode;	
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!GetChamberCurrentTempForNET(lChIndex,dbCurrTemp))
		{
			return FALSE;
		}
		return TRUE;
	}	
	if (lChIndex >= m_nChamberCount)
	{
		m_strErrorMsg.Format("The Chamber Channel Number is Error");
		return FALSE;	
	}

	dwErrorCode = m_ctrlChamber[lChIndex]->GetChamberCurrentTemp(dbCurrTemp);
	
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Set Chamber Current Temp Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	
	return TRUE;
}
/////////////////////////////////////////串口操作函数//////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
//函数说明:
//    写相应通道串口内容
//Add by wanxin
//Time:20170308
////////////////////////////////////////////////////////////
BOOL  CDeviceManger::WriteDevComBuffer(long lChIndex,unsigned char* pOutBuffer, DWORD dwBufferSize)
{
	DWORD dwErrorCode;	
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!WriteDevComBufferForNET(lChIndex,pOutBuffer,dwBufferSize))
		{
			return FALSE;
		}
		return TRUE;
	}	
	if (lChIndex >= m_nComDev)
	{
		m_strErrorMsg.Format("The Serial Device Channel Number is Error");
		return FALSE;	
	}

	dwErrorCode = m_ctrlComDev[lChIndex]->WriteDevice(pOutBuffer,dwBufferSize);
	
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Write Buffer Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	return TRUE;
	
}
/////////////////////////////////////////////////////////////
//函数说明:
//    读取相应通道串口内容
//Add by wanxin
//Time:20170308
////////////////////////////////////////////////////////////
BOOL  CDeviceManger::ReadDevComBuffer(long lChIndex,unsigned char* pInBuffer, DWORD dwBufferSize)
{
	DWORD dwErrorCode;	
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!ReadDevComBufferForNET(lChIndex,pInBuffer,dwBufferSize))
		{
			return FALSE;
		}
		return TRUE;
	}	
	if (lChIndex >= m_nComDev)
	{
		m_strErrorMsg.Format("The Serial Device Channel Number is Error");
		return FALSE;	
	}

	dwErrorCode = m_ctrlComDev[lChIndex]->ReadDevice(pInBuffer,dwBufferSize);
	
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Read Buffer Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	return TRUE;
	
}
/////////////////////////////////////////////////////////////
//函数说明:
//    关闭相应通道串口
//Add by wanxin
//Time:20170308
////////////////////////////////////////////////////////////
BOOL  CDeviceManger::CloseDevDevice(long lChIndex)
{
	DWORD dwErrorCode;	
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!CloseDevDeviceForNET(lChIndex))
		{
			return FALSE;
		}
		return TRUE;
	}	
	if (lChIndex >= m_nComDev)
	{
		m_strErrorMsg.Format("The Com Device Channel Number is Error");
		return FALSE;	
	}
	
	for (int j=0;j<m_nDeviceCount;j++)
	{
		if (m_ptrMainFrame[j].nIndex == m_pComDevSlotInfo[lChIndex].nDevIndex && m_pComDevSlotInfo[lChIndex].nSlotType == TAG_COMDEV)
		{
			dwErrorCode = m_ctrlComDev[lChIndex]->CloseDevice();			
			if(dwErrorCode!=SUCCESS)
			{
				m_strErrorMsg.Format("Open serial port Error,Error Code:%d",dwErrorCode);
				return FALSE;
			}
			m_ptrMainFrame[j].bMainFrameIsOPen = FALSE;
		}
	}

	return TRUE;
}
/////////////////////////////////////////////////////////////
//函数说明:
//    打开相应通道串口
//Add by wanxin
//Time:20170308
////////////////////////////////////////////////////////////
BOOL  CDeviceManger::OpenDevDevice(long lChIndex)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!OpenDevDeviceForNET(lChIndex))
		{
			return FALSE;
		}
		return TRUE;
	}	
	if (lChIndex >= m_nComDev)
	{
		m_strErrorMsg.Format("The Com Device Channel Number is Error");
		return FALSE;	
	}
	
	stDevType s_DevInfo;
	CString strAddress,strTemp;
//	strAddress = lpAddress;
	unsigned long lHandle;
	
	for (int j=0;j<m_nDeviceCount;j++)
	{
		strAddress.Format("COM,%s",m_ptrMainFrame[j].strAddress);
		if (m_ptrMainFrame[j].nIndex == m_pComDevSlotInfo[lChIndex].nDevIndex && m_pComDevSlotInfo[lChIndex].nSlotType == TAG_COMDEV)
		{
			s_DevInfo.bNum =m_ptrMainFrame[j].nIndex;
			strTemp = m_ptrMainFrame[j].strCaption;
			strTemp.MakeUpper();
			if (lstrcmp(strTemp, "COMDEV")==0)
			{
				s_DevInfo.bType = 0;
			}
			else
			{
				m_strErrorMsg.Format("Device Type Error,Error Code:%d",ERROR_COMDEV);
				return FALSE;
			}
			if (m_pComDevSlotInfo[lChIndex].nOnline && m_ptrMainFrame[j].bMainFrameIsOPen==FALSE) 
			{			
				dwErrorCode = m_ctrlComDev[lChIndex]->OpenDevice(strAddress.GetBuffer(0),lHandle);
				if (dwErrorCode !=SUCCESS)
				{
					m_strErrorMsg.Format("Open Com Device Error,Error Code:%d",dwErrorCode);
					return FALSE;
				}
			}
			else if(m_pComDevSlotInfo[lChIndex].nOnline)
			{
				dwErrorCode=m_ctrlComDev[lChIndex]->SetDeviceHandle(strAddress.GetBuffer(0),m_ptrMainFrame[j].lMainFramHandle);
				if (dwErrorCode !=SUCCESS)
				{
					m_strErrorMsg.Format("Open  Com Device Error,Error Code:%d",dwErrorCode);
					return FALSE;
				}
			}
		}
	}
	return TRUE;
}

////////////////////////////////////////开关盒驱动/////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//函数说明：
//    关闭开关盒
//Add by wanxin
//Time: 2017-12-28
//////////////////////////////////////////////////////////////////////////////////////////
BOOL  CDeviceManger::CloseSwitchDevice(long lChIndex)
{
	DWORD dwErrorCode;	
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!CloseSwitchDeviceForNET(lChIndex))
		{
			return FALSE;
		}
		return TRUE;
	}	
	if (lChIndex >= m_nSwitchCount)
	{
		m_strErrorMsg.Format("The Device Channel Number is Error");
		return FALSE;	
	}
	
	for (int j=0;j<m_nDeviceCount;j++)
	{
		if (m_ptrMainFrame[j].nIndex == m_pSwitchSlotInfo[lChIndex].nDevIndex && m_pSwitchSlotInfo[lChIndex].nSlotType == TAG_SWITCH)
		{
			dwErrorCode = m_ctrlSwitch[lChIndex]->CloseDevice();			
			if(dwErrorCode!=SUCCESS)
			{
				m_strErrorMsg.Format("Close Switch Error,Error Code:%d",dwErrorCode);
				return FALSE;
			}
			m_ptrMainFrame[j].bMainFrameIsOPen = FALSE;
		}
	}

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////
//函数说明：
//    打开开关盒
//Add by wanxin
//Time: 2017-12-38
/////////////////////////////////////////////////////////////////////////////////////////
BOOL  CDeviceManger::OpenSwitchDevice(long lChIndex)
{
	DWORD dwErrorCode;
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!OpenSwitchDeviceForNET(lChIndex))
		{
			return FALSE;
		}
		return TRUE;
	}	
	if (lChIndex >= m_nComDev)
	{
		m_strErrorMsg.Format("The Switch Channel Number is Error");
		return FALSE;	
	}
	
	stDevType s_DevInfo;
	CString strAddress,strTemp;

	unsigned long lHandle;
	
	for (int j=0;j<m_nDeviceCount;j++)
	{
		strAddress.Format("COM,%s",m_ptrMainFrame[j].strAddress);
		if (m_ptrMainFrame[j].nIndex == m_pSwitchSlotInfo[lChIndex].nDevIndex && m_pSwitchSlotInfo[lChIndex].nSlotType == TAG_SWITCH)
		{
			s_DevInfo.bNum =m_ptrMainFrame[j].nIndex;
			strTemp = m_ptrMainFrame[j].strCaption;
			strTemp.MakeUpper();
			if (lstrcmp(strTemp, "IT_1X2SW")==0)
			{
				s_DevInfo.bType = IT_1X2SW;
			}
			else if (lstrcmp(strTemp, "OMS_1X64SW")==0)
			{
				s_DevInfo.bType = OMS_1X64SW;
			}
			else if (lstrcmp(strTemp, "IT_1X8SW")==0)
			{
				s_DevInfo.bType = IT_1X8SW;
			}
			else
			{
				m_strErrorMsg.Format("TLS Type Error,Error Code:%d",ERROR_TLS);
				return FALSE;
			}
			if (m_pSwitchSlotInfo[lChIndex].nOnline && m_ptrMainFrame[j].bMainFrameIsOPen==FALSE) 
			{			
				dwErrorCode = m_ctrlSwitch[lChIndex]->OpenDevice(s_DevInfo,strAddress.GetBuffer(0),&lHandle);
				if (dwErrorCode !=SUCCESS)
				{
					m_strErrorMsg.Format("Open Switch Device Error,Error Code:%d",dwErrorCode);
					return FALSE;
				}
			}
			else if(m_pComDevSlotInfo[lChIndex].nOnline)
			{
				dwErrorCode=m_ctrlSwitch[lChIndex]->SetHandle(s_DevInfo,strAddress.GetBuffer(0),m_ptrMainFrame[j].lMainFramHandle);
				if (dwErrorCode !=SUCCESS)
				{
					m_strErrorMsg.Format("Open  Switch Device Error,Error Code:%d",dwErrorCode);
					return FALSE;
				}
			}
		}
	}
	return TRUE;
}
//////////////////////////////////////////////////////////////////////////////////////////
//函数说明：
//    切换开关盒
//Add by wanxin
//Time: 2017-12-28
/////////////////////////////////////////////////////////////////////////////////////////
BOOL  CDeviceManger::SwitchPort2Port(int lChIndex,int nInputPort, int nOutputPort)
{
	DWORD dwErrorCode;	
	m_strErrorMsg = _T("No Error");
	if(m_bUseNet)
	{
		if(!SwitchPort2Port(lChIndex,nInputPort,nOutputPort))
		{
			return FALSE;
		}
		return TRUE;
	}	
	if (lChIndex >= m_nSwitchCount)
	{
		m_strErrorMsg.Format("The Switch Channel Number is Error");
		return FALSE;	
	}

	dwErrorCode = m_ctrlSwitch[lChIndex]->SwitchPort2Port(nInputPort,nOutputPort);
	
	if(dwErrorCode!=SUCCESS)
	{
		m_strErrorMsg.Format("Read Buffer Error,Error Code:%d",dwErrorCode);
		return FALSE;
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////
//函数说明:
//    设置UDL是否使用网络通信
//Add by wanxin
//Time:20170228
////////////////////////////////////////////////////////////
void CDeviceManger::SetUDLNET(BOOL bIsNet)
{
	m_bUseNet = bIsNet;
}
/////////////////////////////////////////////////////////////
//函数说明:
//    初始化网络通信
//Add by wanxin
//Time:20170228
////////////////////////////////////////////////////////////
BOOL CDeviceManger::InitialNet()
{
	WSADATA wsaData;
	
	int wsaret=WSAStartup(0x101,&wsaData);
	if(wsaret)	
		return 0;
	shutdown(m_conn,SD_BOTH);
	closesocket(m_conn);
	m_conn=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(m_conn==INVALID_SOCKET)
		return FALSE;
    return TRUE;
}
/////////////////////////////////////////////////////////////
//函数说明:
//    与服务器建立连接
//Add by wanxin
//Time:20170228
////////////////////////////////////////////////////////////
BOOL CDeviceManger::ConnectToServer(LPCSTR lpstrIP)
{
	struct hostent *hp;
	unsigned int addr;
	struct sockaddr_in server;
	m_strErrorMsg = _T("No Error");
	if(!m_bUseNet)
	{
		m_strErrorMsg="Please use SetUDLNET to set NET type!";
		return FALSE;
	}
	if(!InitialNet())
	{
		m_strErrorMsg="Inital socket error!";
		return FALSE;
	}
	if(inet_addr(lpstrIP)==INADDR_NONE)
	{
		hp=gethostbyname(lpstrIP);
	}
	else
	{
		addr=inet_addr(lpstrIP);
		hp=gethostbyaddr((char*)&addr,sizeof(addr),AF_INET);
	}
	if(hp==NULL)
	{
		closesocket(m_conn);
		m_strErrorMsg="The IP Address error!";
		return FALSE;
	}
	int nNETTimeout =180000; //设置套接字超时时间3分钟
	setsockopt(m_conn,SOL_SOCKET,SO_SNDTIMEO,(char*)&nNETTimeout,sizeof(int));
	setsockopt(m_conn,SOL_SOCKET,SO_RCVTIMEO,(char*)&nNETTimeout,sizeof(int));
	
	server.sin_addr.s_addr=*((unsigned long*)hp->h_addr);
	server.sin_family=AF_INET;
	server.sin_port=htons(20248);
	if(connect(m_conn,(struct sockaddr*)&server,sizeof(server)))
	{
		m_strErrorMsg="Connect to server error!";
		closesocket(m_conn);
		return FALSE;	
	}
	int iKeepAlive =1;
	setsockopt(m_conn,SOL_SOCKET,SO_KEEPALIVE,(char*)&iKeepAlive,sizeof(iKeepAlive));
	
	FD_ZERO(&m_fdread);
	FD_SET(m_conn,&m_fdread);
	char szBuffer[2048];
	ZeroMemory(szBuffer,sizeof(char)*2048);
	int nGetLength;

	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	
	if(strstr(szBuffer,"#Server Ready")==NULL)
	{
		m_strErrorMsg="Connect to server error!";
		closesocket(m_conn);
		return FALSE;	
	}
	return TRUE;
}
/////////////////////////////////////////////////////////////
//函数说明:
//    通过网络发送buffer信息
//Add by wanxin
//Time:20170228
////////////////////////////////////////////////////////////
BOOL CDeviceManger::SendNetBuffer(char* pszBuffer,int nBufferlength)
{
	int nh =send(m_conn,pszBuffer,nBufferlength,0);
	if(nh ==-1)
		return FALSE;
	return TRUE;
}
/////////////////////////////////////////////////////////////
//函数说明:
//    通过网络接收buffer信息
//Add by wanxin
//Time:20170228
////////////////////////////////////////////////////////////
BOOL CDeviceManger::ReadNetBuffer(char* pszBuffer,int nBufferLength,int &nGetLenght)
{
//	char szBuffer[2048];
//	int nLineCount;
	nGetLenght = 0;
	if(FD_ISSET(m_conn,&m_fdread))
	{
		nGetLenght = recv(m_conn,pszBuffer,nBufferLength,0);
		if(nGetLenght <=0)
			return FALSE;
	}
	else
	{
		return FALSE;
	}

    return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////////
BOOL CDeviceManger::LoadConfigXMLForNET(LPCSTR lpstrFileName)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"engine loadxml 1 %s\r",lpstrFileName);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"LoadXML Successfully")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	
	return TRUE;
}
CString  CDeviceManger::ExtractFileName(LPCSTR lpstrFilePath)
{
	CString temp,strFileName;
	//char szBuf[MAX_PATH];
	int pos = -1;
	//GetModuleFileName(NULL,szBuf,MAX_PATH);
    strFileName = lpstrFilePath;
	pos = strFileName.ReverseFind('\\');
	temp = strFileName.Mid(pos+1,strFileName.GetLength());
	return temp;
}

BOOL CDeviceManger::OpenDeviceForNET()
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"engine opendevice\r");
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"Open device Successfully")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	
	return TRUE;
}
BOOL CDeviceManger::SetTLSWavelengthForNET(long lChIndex, double dblWL)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"TLS SWL 2 %d %lf\r",lChIndex,dblWL);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	
	return TRUE;
}

BOOL CDeviceManger::SetTLSSourcePowerForNET(long lChIndex, double dblPW)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"TLS SPOWER 2 %d %lf\r",lChIndex,dblPW);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	
	return TRUE;
}

BOOL CDeviceManger::SetTLSCoherenceControlForNET(long lChIndex,BOOL bEnable)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"TLS SCONHERENECE 2 %d %d\r",lChIndex,bEnable);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	
	return TRUE;

}
BOOL CDeviceManger::SetTLSSourceUnitForNET(long lChIndex, long lUnit)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"TLS SUNIT 2 %d %d\r",lChIndex,lUnit);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	
	return TRUE;

}
BOOL CDeviceManger::SetTLSParametersForNET(long lChIndex,BOOL bLowSSE,double dblPower, double dblWavelength)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"TLS SPARAM 4 %d %d %lf %lf\r",lChIndex,bLowSSE,dblPower,dblWavelength);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	
	return TRUE;
}

BOOL CDeviceManger::SetTLSOutputEnableForNET(long lChIndex, BOOL bEnable)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"TLS SOUPT 2 %d %d\r",lChIndex,bEnable);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	
	return TRUE;

}
BOOL CDeviceManger::CloseTLSDeviceForNET(long lChIndex)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"TLS SCLOSE 1 %d\r",lChIndex);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	
	return TRUE;	
}
/////////////////////////////////////功率计网络驱动函数////////////////////////////////////
BOOL CDeviceManger::GetPMUnitForNET(long iChan, long* piUnit)
{
	char szBuffer[2048];
	char *token=NULL;
	char szSpec[]=":";
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"PM GUNIT 1 %d\r",iChan);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"PM:Unit")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
    token = strtok(szBuffer,szSpec);
	ASSERT(token);
	token = strtok(NULL,szSpec);
	ASSERT(token);
	token =  strtok(NULL,szSpec);
	CString strTemp = token;
	strTemp.TrimLeft();
	strTemp.TrimRight();
	* piUnit = atol(strTemp);

	return TRUE;
}
BOOL CDeviceManger::GetPMAverageTimeForNET(long iChan, double* pdblAverageTime)
{
	char szBuffer[2048];
	char *token=NULL;
	char szSpec[]=":";
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"PM GAVGTIME 1 %d\r",iChan);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"PM:AVG")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
    token = strtok(szBuffer,szSpec);
	ASSERT(token);
	token = strtok(NULL,szSpec);
	ASSERT(token);
	token =  strtok(NULL,szSpec);
	CString strTemp = token;
	strTemp.TrimLeft();
	strTemp.TrimRight();
	* pdblAverageTime = atof(strTemp);

	return TRUE;
}
BOOL CDeviceManger::GetPMWavelengthForNET(long iChan, double* pdblWL)
{
	char szBuffer[2048];
	char *token=NULL;
	char szSpec[]=":";
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"PM GWL 1 %d\r",iChan);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"PM:WAV")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
    token = strtok(szBuffer,szSpec);
	ASSERT(token);
	token = strtok(NULL,szSpec);
	ASSERT(token);
	token =  strtok(NULL,szSpec);
	CString strTemp = token;
	strTemp.TrimLeft();
	strTemp.TrimRight();
	* pdblWL = atof(strTemp);

	return TRUE;
}

BOOL CDeviceManger::ReadPowerForNET(long iChan, double* pdbPowerValue)
{
	char szBuffer[2048];
	char *token=NULL;
	char szSpec[]=":";
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"PM GPOWER 1 %d\r",iChan);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}

	if(strstr(szBuffer,"PM:POW")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
    token = strtok(szBuffer,szSpec);
	ASSERT(token);
	token = strtok(NULL,szSpec);
	ASSERT(token);
	token =  strtok(NULL,szSpec);
	CString strTemp = token;
	strTemp.TrimLeft();
	strTemp.TrimRight();
	* pdbPowerValue = atof(strTemp);

	return TRUE;
}
BOOL CDeviceManger::SetPMUnitForNET(long iChan, long iPWUnit)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"PM SUNIT 2 %d %d\r",iChan,iPWUnit);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;
}
BOOL CDeviceManger::SetPMWavelengthForNET(long iChan, double dblWL)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"PM SWL 2 %d %lf\r",iChan,dblWL);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;
}
BOOL CDeviceManger::SetPMAverageTimeForNET(long iChan, double dblPWAverageTime)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"PM SAVGTIME 2 %d %lf\r",iChan,dblPWAverageTime);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;
}
BOOL CDeviceManger::SetPMRangeModeForNET(long iChan, long iPWRangeMode)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"PM SRANGEMODE 2 %d %ld\r",iChan,iPWRangeMode);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;
}
BOOL CDeviceManger::SetPMParametersForNET(long iChan, BOOL bAutoRang, double dblWL, double dblAverageTime, double dblPwrRange)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"PM SPARAM 5 %d %d %lf %lf %lf\r",iChan,bAutoRang,dblWL,dblAverageTime,dblPwrRange);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;
}
BOOL CDeviceManger::ClosePMDeviceForNET(long lChIndex)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"PM SCLOSE 1 %d\r",lChIndex);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;
}
BOOL CDeviceManger::GetPMRangeModeForNET(long iChan, long* iPWMRangeMode)
{
	char szBuffer[2048];
	char *token=NULL;
	char szSpec[]=":";
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"PM GRANGEMODE 1 %d\r",iChan);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}

	if(strstr(szBuffer,"PM:RANGEMODE")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
    token = strtok(szBuffer,szSpec);
	ASSERT(token);
	token = strtok(NULL,szSpec);
	ASSERT(token);
	token =  strtok(NULL,szSpec);
	CString strTemp = token;
	strTemp.TrimLeft();
	strTemp.TrimRight();
	*iPWMRangeMode = atol(strTemp);	
	return TRUE;
}
BOOL CDeviceManger::SetPMZeroForNET(long iChan)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"PM SZERO 1 %d\r",iChan);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;	
}
BOOL CDeviceManger::SetPMMaxMinPowerStartForNET(long lChIndex)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"PM SMAXMINSTART 1 %d\r",lChIndex);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;	
}
BOOL CDeviceManger::GetPMMaxMinPowerForNET(long lChIndex,double *pdbGetMax,double *pdbGetMin)
{
	char szBuffer[2048];
	char *token=NULL;
	char *token2=NULL;
	char szSpec[]=":";
	CString strTemp;
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"PM GMAXMINPOWER 1 %d\r",lChIndex);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}

	if(strstr(szBuffer,"PM:MAXMINPOW:")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
    token = strtok(szBuffer,szSpec);
	ASSERT(token);
	token = strtok(NULL,szSpec);
	ASSERT(token);
	token =  strtok(NULL,szSpec);
	token2 = strtok(token,",");
	ASSERT(token2);
	strTemp	= token2;
	strTemp.TrimLeft();
	strTemp.TrimRight();
	*pdbGetMax = atof(token2);

	token2 = strtok(NULL,",");
	ASSERT(token2);
	strTemp	= token2;
	strTemp.TrimLeft();
	strTemp.TrimRight();
	*pdbGetMin = atof(token2);

	return TRUE;	
}
BOOL CDeviceManger::SetPMMaxMinPowerStopForNET(long lChIndex)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"PM SMAXMINSTOP 1 %d\r",lChIndex);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;	
}


BOOL CDeviceManger::SetPMPowerOffsetForNET(long lChIndex,double dbPowerOffset)
{
	char szBuffer[2048];
	char *token=NULL;
	char *token2=NULL;
	char szSpec[]=":";
	CString strTemp;
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"PM SPOWEROFFSET 2 %d %.3f\r",lChIndex,dbPowerOffset);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}

	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}

	return TRUE;
	
}

/////////////////////////////////////VOA网络函数///////////////////////////
BOOL CDeviceManger::CloseVOADeviceForNET(long lChIndex)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"VOA SCLOSE 1 %d\r",lChIndex);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;
	
}
BOOL CDeviceManger::ResetVOADeviceForNET(long lChIndex)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"VOA SRESET 1 %d\r",lChIndex);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;
}
BOOL CDeviceManger::SetVOAWavelengthForNET(long lChIndex, double dblWL)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"VOA SWL 2 %d %lf\r",lChIndex,dblWL);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;
}
BOOL CDeviceManger::GetVOAWavelengthForNET(long lChIndex, double* pdblWL)
{
	char szBuffer[2048];
	char *token=NULL;
	char *token2=NULL;
	char szSpec[]=":";
	CString strTemp;
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"VOA GWL 1 %d\r",lChIndex);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}

	if(strstr(szBuffer,"VOA:WAV")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
    token = strtok(szBuffer,szSpec);
	ASSERT(token);
	token = strtok(NULL,szSpec);
	ASSERT(token);
	token =  strtok(NULL,szSpec);
	strTemp	= token;
	strTemp.TrimLeft();
	strTemp.TrimRight();
	* pdblWL = atof(token);

	return TRUE;
}
BOOL CDeviceManger::SetVOAAttenuationForNET(long lChIndex, double dblAtten)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"VOA SATTEN 2 %d %lf\r",lChIndex,dblAtten);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;
}
BOOL CDeviceManger::GetVOAAttenuationForNET(long lChIndex, double* pdblAtten)
{
	char szBuffer[2048];
	char *token=NULL;
	char *token2=NULL;
	char szSpec[]=":";
	CString strTemp;
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"VOA GATTEN 1 %d\r",lChIndex);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}

	if(strstr(szBuffer,"VOA:ATT")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
    token = strtok(szBuffer,szSpec);
	ASSERT(token);
	token = strtok(NULL,szSpec);
	ASSERT(token);
	token =  strtok(NULL,szSpec);
	strTemp	= token;
	strTemp.TrimLeft();
	strTemp.TrimRight();
	* pdblAtten = atof(token);

	return TRUE;
}
BOOL CDeviceManger::SetVOAEnableOutputForNET(long lChIndex, BOOL bEnable)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"VOA SENABLE 2 %d %d\r",lChIndex,bEnable);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;
}
BOOL CDeviceManger::SetVOAInputOffsetForNET(long lChIndex, double dblOffset)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"VOA SOFFSET 2 %d %lf\r",lChIndex,dblOffset);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;
}
BOOL CDeviceManger::GetVOAStatusForNET(long lChIndex,DWORD *dwStatus)
{
	char szBuffer[2048];
	char *token=NULL;
	char *token2=NULL;
	char szSpec[]=":";
	CString strTemp;
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"VOA GSTATUS 1 %d\r",lChIndex);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}

	if(strstr(szBuffer,"VOA:STATUS")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
    token = strtok(szBuffer,szSpec);
	ASSERT(token);
	token = strtok(NULL,szSpec);
	ASSERT(token);
	token =  strtok(NULL,szSpec);
	strTemp	= token;
	strTemp.TrimLeft();
	strTemp.TrimRight();
	* dwStatus = atol(token);
	
	return TRUE;
}
//////////////////////////////////////////////////偏振控制网络函数/////////////////////////////////////
BOOL CDeviceManger::ClosePolDeviceForNET(long lChIndex)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"POL SCLOSE 1 %d\r",lChIndex);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;	
}
BOOL CDeviceManger::ResetPolDeviceForNET(long lChIndex)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"POL SRESET 1 %d\r",lChIndex);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;	
}

BOOL CDeviceManger::GetPolCurrentPOSPolarizerForNET(long lChIndex,double * pdblAlphaP,double *pdblAlphaQ,double *pdblAlphaH)
{
	char szBuffer[2048];
	char *token=NULL;
	char *token2=NULL;
	char szSpec[]=":";
	CString strTemp;
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"POL GCURPOS 1 %d\r",lChIndex);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}

	if(strstr(szBuffer,"POL:POS")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
    token = strtok(szBuffer,szSpec);
	ASSERT(token);
	token = strtok(NULL,szSpec);
	ASSERT(token);
	token =  strtok(NULL,szSpec);

	token2 = strtok(token,",");
	ASSERT(token2);
	strTemp	= token2;
	strTemp.TrimLeft();
	strTemp.TrimRight();
	* pdblAlphaP = atof(token2);
	token2 = strtok(NULL,",");
	ASSERT(token2);
	strTemp	= token2;
	strTemp.TrimLeft();
	strTemp.TrimRight();
	* pdblAlphaQ = atof(token2);
	token2 = strtok(NULL,",");
	ASSERT(token2);
	strTemp	= token2;
	strTemp.TrimLeft();
	strTemp.TrimRight();
	* pdblAlphaH = atof(token2);

	return TRUE;
}
BOOL CDeviceManger::SetPolALLForNET(long lChIndex,double alphaP, double alphaQ, double alphaH)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"POL SALL 4 %d %lf %lf %lf\r",lChIndex,alphaP,alphaQ,alphaH);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;
}
BOOL CDeviceManger::SetPolDiagonalAnglesForNET(long lChIndex,double AlphaPMax, double Wavelength)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"POL SDIAGANGLE 3 %d %lf %lf\r",lChIndex,AlphaPMax,Wavelength);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;
}
BOOL CDeviceManger::SetPolHorizontalAnglesForNET(long lChIndex,double AlphaPMax, double Wavelength)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"POL SHORANGLE 3 %d %lf %lf\r",lChIndex,AlphaPMax,Wavelength);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;
}
BOOL CDeviceManger::SetPolPOSHalfForNET(long lChIndex,double alpha)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"POL SHALFANGLE 2 %d %lf\r",lChIndex,alpha);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;
}
BOOL CDeviceManger::SetPolPOSPolarizerForNET(long lChIndex,double alpha)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"POL SPOSANGLE 2 %d %lf\r",lChIndex,alpha);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;
}

BOOL CDeviceManger::SetPolPOSQuarterForNET(long lChIndex,double alpha)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"POL SQUATERANGLE 2 %d %lf\r",lChIndex,alpha);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;
}
BOOL CDeviceManger::SetPolRightHandCircularAnglesForNET(long lChIndex,double AlphaPMax, double Wavelength)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"POL SRIGHTHANDANGLE 3 %d %lf %lf\r",lChIndex,AlphaPMax,Wavelength);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;
}
BOOL CDeviceManger::SetPolVerticalAnglesForNET(long lChIndex,double AlphaPMax, double Wavelength)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"POL SVERTICALANGLE 3 %d %lf %lf\r",lChIndex,AlphaPMax,Wavelength);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;
}

BOOL  CDeviceManger::CloseChamberDeviceForNET(long lChIndex)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"CHAMBER SCLOSE 1 %d\r",lChIndex);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;
}

BOOL  CDeviceManger::SetChamberRunStopForNET(long lChIndex)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"CHAMBER STOP 1 %d\r",lChIndex);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;	
}
BOOL  CDeviceManger::SetChamberRunStartForNET(long lChIndex)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"CHAMBER SSTART 1 %d\r",lChIndex);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;	
}
BOOL  CDeviceManger::SetChamberSetPointForNET(long lChIndex,double dbSetPoint)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"CHAMBER SPOINT 2 %d %.3f\r",lChIndex,dbSetPoint);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;	
}
BOOL  CDeviceManger::GetChamberSetPointForNET(long lChIndex,double* dbSetPoint)
{
	char szBuffer[2048];
	char *token=NULL;
	char szSpec[]=":";
	CString strTemp;
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"CHAMBER GPOINT 1 %d\r",lChIndex);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}

	if(strstr(szBuffer,"CHAMBER:POINT")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
    token = strtok(szBuffer,szSpec);
	ASSERT(token);
	token = strtok(NULL,szSpec);
	ASSERT(token);
	token =  strtok(NULL,szSpec);
	strTemp = token;
	strTemp.TrimLeft();
	strTemp.TrimRight();
    * dbSetPoint = atof(strTemp);
	
	return TRUE;	
}
BOOL  CDeviceManger::GetChamberCurrentTempForNET(long lChIndex,double *dbCurrTemp)
{
	char szBuffer[2048];
	char *token=NULL;
	char szSpec[]=":";
	CString strTemp;
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"CHAMBER GPOINT 1 %d\r",lChIndex);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}

	if(strstr(szBuffer,"CHAMBER:TEMP")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
    token = strtok(szBuffer,szSpec);
	ASSERT(token);
	token = strtok(NULL,szSpec);
	ASSERT(token);
	token =  strtok(NULL,szSpec);
	strTemp = token;
	strTemp.TrimLeft();
	strTemp.TrimRight();
    * dbCurrTemp = atof(strTemp);
	
	return TRUE;	
}

BOOL CDeviceManger::SendBufferBy1M( char * str, int nLength)
{
	long lTemplength = nLength;
	int nGetLength = 0;
	long lGetLenth = 0;
	char szBuffer[1024];
	char *pTemp  = str;
	while (TRUE)
	{
		ZeroMemory(szBuffer,sizeof(char)*1024);
		if(lTemplength < 1024)
		{			
			nGetLength = send(m_conn,pTemp,lTemplength,0);
			lGetLenth += nGetLength;
			if(lGetLenth != nLength)
			{
				ASSERT(lTemplength);
			}
			break;
		}
        else
		{
			nGetLength = send(m_conn,pTemp,1024,0);
		}
		pTemp += nGetLength;
		lTemplength -=nGetLength;
		lGetLenth += nGetLength;
	}
    return TRUE;
}

//////////////////////////////////////通信接口//////////////////////////////////
BOOL  CDeviceManger::WriteDevComBufferForNET(long lChIndex,unsigned char* pOutBuffer, DWORD dwBufferSize)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"COM SEND 3 %d %d\r",lChIndex,dwBufferSize);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(200);
	if(!SendBufferBy1M((char*)pOutBuffer,dwBufferSize))
	{
		m_strErrorMsg.Format("Send  %s error!",pOutBuffer);
		return FALSE;
	}
	Sleep(200);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"COMSEND\r");
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;		
}
BOOL  CDeviceManger::ReadDevComBufferForNET(long lChIndex,unsigned char* pInBuffer, DWORD dwBufferSize)
{
	char szBuffer[2048];
	char * pszReadBuffer = NULL;
	char *token=NULL;
	char szSpec[]=":";
	CString strTemp;
	int nTotalLength;
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"COM READ 2 %d %d\r",lChIndex,dwBufferSize);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*64);
	if(!ReadNetBuffer((char*)szBuffer,64,nGetLength))
	{
		if(!ReadNetBuffer((char*)szBuffer,64,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"COM:")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
    token = strtok(szBuffer,szSpec);
	ASSERT(token);
	token = strtok(NULL,szSpec);
	ASSERT(token);
	nTotalLength = atoi(token);

	pszReadBuffer = (char*)VirtualAlloc(NULL,sizeof(char)*nTotalLength,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
    ZeroMemory(pszReadBuffer,sizeof(char)*nTotalLength);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	int nLineCount =nTotalLength;
	int nTempCount =0;
	while(TRUE)
	{
		if(nLineCount < 2048 )
		{
			if(!ReadNetBuffer((char*)szBuffer,nLineCount,nGetLength))
			{
				if(!ReadNetBuffer((char*)szBuffer,nLineCount,nGetLength))
				{
					m_strErrorMsg.Format("Receive buffer error!");
					return FALSE;	   
				}
			}
			nTempCount += nGetLength;
			strncat(pszReadBuffer,szBuffer,nLineCount);			
			break;
		}
		else 
		{
			if(!ReadNetBuffer((char*)szBuffer,2048,nGetLength))
			{
				if(!ReadNetBuffer((char*)szBuffer,nTotalLength,nGetLength))
				{
					m_strErrorMsg.Format("Receive buffer error!");
					return FALSE;	   
				}
			}
		}
		nLineCount -= 2048;
		nTempCount += nGetLength;
		strncat(pszReadBuffer,szBuffer,2048);
	}
    if(nTempCount!=nTotalLength)
	{
		m_strErrorMsg.Format("Receive buffer length is not equal actual length!");
		return FALSE;	 
	}
	ASSERT(pInBuffer);
	memcpy(pInBuffer,pszReadBuffer,nTotalLength);
	if(pszReadBuffer!=NULL)
	{
		VirtualFree(pszReadBuffer,0,MEM_RELEASE);
		pszReadBuffer = 0;
	}
	
	return TRUE;	
}
BOOL  CDeviceManger::CloseDevDeviceForNET(long lChIndex)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"COM SCLOSE 1 %d\r",lChIndex);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;	
}
BOOL  CDeviceManger::OpenDevDeviceForNET(long lChIndex)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"COM SOPEN 1 %d\r",lChIndex);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;	
}

BOOL CDeviceManger::CloseOSADeviceForNET(long lChIndex)
{

	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"OSA SCLOSE 1 %d\r",lChIndex);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;
	
}
BOOL CDeviceManger::ResetOSADeviceForNET(long lChIndex)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"OSA SRESET 1 %d\r",lChIndex);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;	
}
BOOL CDeviceManger::SetOSALocalCtrlForNET(long lChIndex)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"OSA SLOCALCTRL 1 %d\r",lChIndex);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;	
}
BOOL CDeviceManger::SetOSARBWForNET(long lChIndex,double dblRBW)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"OSA SRBW 2 %d %lf\r",lChIndex,dblRBW);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;	
}
BOOL CDeviceManger::GetOSARBWForNET(long lChIndex,double* pdblRBW)
{
	char szBuffer[2048];
	char *token=NULL;
	char szSpec[]=":";
	CString strTemp;
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"OSA GRBW 1 %d\r",lChIndex);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}

	if(strstr(szBuffer,"OSA:RBW")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
    token = strtok(szBuffer,szSpec);
	ASSERT(token);
	token = strtok(NULL,szSpec);
	ASSERT(token);
	token =  strtok(NULL,szSpec);
	strTemp = token;
	strTemp.TrimLeft();
	strTemp.TrimRight();
    * pdblRBW = atof(strTemp);
	
	return TRUE;	
}
BOOL CDeviceManger::InitOSAAmpTestForNET(long lChIndex,double dblStartWL,double dblStopWL,double dblRBW)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"OSA SINIAMP 4 %d %lf %lf %lf\r",lChIndex,dblStartWL,dblStopWL,dblRBW);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;	
}
BOOL CDeviceManger::MeasureOSASourceForNET(long lChIndex)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"OSA SAMPSOURCE 1 %d\r",lChIndex);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;	
}
BOOL CDeviceManger::MeasureOSAAmplifierForNET(long lChIndex,BOOL bScanSrcOnly)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"OSA SAMP 2 %d %d\r",lChIndex,bScanSrcOnly);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;		
}
BOOL CDeviceManger::GetOSAChannelCountForNET(long lChIndex,DWORD* pdwChannelCount)
{
	char szBuffer[2048];
	char *token=NULL;
	char szSpec[]=":";
	CString strTemp;
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"OSA GCHCOUNT 1 %d\r",lChIndex);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}

	if(strstr(szBuffer,"OSA:CHAN:COUNT")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
    token = strtok(szBuffer,szSpec);
	ASSERT(token);
	token = strtok(NULL,szSpec);
	ASSERT(token);
	token =  strtok(NULL,szSpec);
	ASSERT(token);
	token =  strtok(NULL,szSpec);
	strTemp = token;
	strTemp.TrimLeft();
	strTemp.TrimRight();
    * pdwChannelCount = atoi(strTemp);
	
	return TRUE;	
}

BOOL CDeviceManger::ReceiveArryAndAnlysis(const char* lpstr,double*pdbArry,int& nPointCount)
{
    char szBuffer[1024];
	char *token = NULL;
	char szSpec[]=":";
	char *token2 = NULL;
	int nReturnLength;
	char *szBufferptr;
	int nGetLength;
//	float fPreTemp;
	ZeroMemory(szBuffer,sizeof(char)*1024);
	if(!ReadNetBuffer(szBuffer,32,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,32,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	
	if(strstr(szBuffer,lpstr)==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
    token = strtok(szBuffer,szSpec);
	ASSERT(token);
	token = strtok(NULL,szSpec);
	ASSERT(token);
	token =  strtok(NULL,szSpec);
	ASSERT(token);
	token =  strtok(NULL,szSpec);

	token2 = strtok(token,",");
	ASSERT(token2);
	long lChCount = atol(token2);
	nPointCount = lChCount;
	token2 = strtok(NULL,",");
	ASSERT(token2);
	long lBufferLength = atol(token2);
	nReturnLength = lChCount;
	
	szBufferptr = (char*)VirtualAlloc(NULL,sizeof(char)*lBufferLength,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
	ZeroMemory(szBufferptr,sizeof(char)*lBufferLength);
	
	long lTemplength = lBufferLength;
	long lGetLenth = 0;
	CTime  m_start,m_end;
	m_start =::GetCurrentTime();
	while (TRUE)
	{
		ZeroMemory(szBuffer,sizeof(char)*1024);

		if(!ReadNetBuffer(szBuffer,1024,nGetLength))
		{
			if(!ReadNetBuffer(szBuffer,1024,nGetLength))
			{
				m_strErrorMsg.Format("Receive buffer error!");
				return FALSE;	   
			}
		}
		strncat(szBufferptr,szBuffer,nGetLength);
		lGetLenth += nGetLength;
        lTemplength-= nGetLength;
		
		if(lGetLenth == lBufferLength)
		{
			break;
		}
		if(lTemplength ==0)
		{
           break;
		}
		
	}
	
    token = strtok(szBufferptr,",");
	ASSERT(token);
    pdbArry[0] = atof(token);
	for(int i=1;i < lChCount; i++)
	{
		token = strtok(NULL,",");
		if(token == NULL)
		{
			m_strErrorMsg.Format("the %d point strtok buffer error!",i);
			return FALSE;
		}
		
        pdbArry[i] = atof(token);
	}

    VirtualFree(szBufferptr,0,MEM_RELEASE);
	szBufferptr = NULL;

    return TRUE;
}

BOOL CDeviceManger::GetOSAChannelWaveLensForNET(long lChIndex,double* pdblWL,DWORD* pdwChannelCount)
{
	char szBuffer[1024];
	char *token=NULL;
	char *token2=NULL;
	char szSpec[]=":";
    char * szBufferptr = NULL;
	CString strTemp;
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*1024);
	sprintf(szBuffer,"OSA GCHWL 1 %d\r",lChIndex);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
    if(!ReceiveArryAndAnlysis("OSA:CH:WLCOUNT",pdblWL,nGetLength))
	{
	    return FALSE;	
	}
    * pdwChannelCount = nGetLength;
	
	return TRUE;	
}
BOOL CDeviceManger::GetOSAChannelNFForNET(long lChIndex,double* pdblNF,DWORD* pdwChannelCount)
{
	char szBuffer[1024];
	char *token=NULL;
	char *token2=NULL;
	char szSpec[]=":";
    char * szBufferptr = NULL;
	CString strTemp;
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*1024);
	sprintf(szBuffer,"OSA GCHNF 1 %d\r",lChIndex);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
    if(!ReceiveArryAndAnlysis("OSA:CH:NFCOUNT",pdblNF,nGetLength))
	{
	    return FALSE;	
	}
    * pdwChannelCount = nGetLength;
	
	return TRUE;	
}
BOOL CDeviceManger::GetOSAChannelGainForNET(long lChIndex,double* pdblGain,DWORD* pdwChannelCount)
{
	char szBuffer[1024];
	char *token=NULL;
	char *token2=NULL;
	char szSpec[]=":";
    char * szBufferptr = NULL;
	CString strTemp;
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*1024);
	sprintf(szBuffer,"OSA GCHGAIN 1 %d\r",lChIndex);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
    if(!ReceiveArryAndAnlysis("OSA:CH:GAINCOUNT",pdblGain,nGetLength))
	{
	    return FALSE;	
	}
    * pdwChannelCount = nGetLength;
	
	return TRUE;		
}
BOOL CDeviceManger::GetOSAChannelSNRForNET(long lChIndex,double* pdblSNR,DWORD* pdwChannelCount)
{
	char szBuffer[1024];
	char *token=NULL;
	char *token2=NULL;
	char szSpec[]=":";
    char * szBufferptr = NULL;
	CString strTemp;
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*1024);
	sprintf(szBuffer,"OSA GCHSNR 1 %d\r",lChIndex);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);

    if(!ReceiveArryAndAnlysis("OSA:CH:SNRCOUNT",pdblSNR,nGetLength))
	{
	    return FALSE;	
	}
    * pdwChannelCount = nGetLength;
	
	return TRUE;	
}
BOOL CDeviceManger::GetOSAChannelSourcePowerForNET(long lChIndex,double* pdblSourcePow,DWORD* pdwChannelCount)
{
	char szBuffer[1024];
	char *token=NULL;
	char *token2=NULL;
	char szSpec[]=":";
    char * szBufferptr = NULL;
	CString strTemp;
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*1024);
	sprintf(szBuffer,"OSA GCHSPOW 1 %d\r",lChIndex);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
    if(!ReceiveArryAndAnlysis("OSA:CH:POWCOUNT",pdblSourcePow,nGetLength))
	{
	    return FALSE;	
	}
	
	return TRUE;	
}
BOOL CDeviceManger::SetOSAAmpOffsetForNET(long lChIndex,double dblSourceOffset, double dblAmpOffset)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"OSA SAPMOFFSET 3 %d %lf %lf\r",lChIndex,dblSourceOffset,dblAmpOffset);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;
}
BOOL CDeviceManger::GetOSAAmpOffsetForNET(long lChIndex,double &dblSourceOffset, double &dblAmpOffset)
{
	char szBuffer[2048];
	char *token=NULL;
	char szSpec[]=":";
	char *token2=NULL;
	CString strTemp;
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"OSA GAMPOFFSET 1 %d\r",lChIndex);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}

	if(strstr(szBuffer,"OSA:AMP:OFFSET")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
    token = strtok(szBuffer,szSpec);
	ASSERT(token);
	token = strtok(NULL,szSpec);
	ASSERT(token);
	token =  strtok(NULL,szSpec);

	token2 = strtok(token,",");
	ASSERT(token2);
	strTemp = token2;
	strTemp.TrimLeft();
	strTemp.TrimRight();
    dblSourceOffset = atof(strTemp);

	token2 = strtok(NULL,",");
	ASSERT(token2);
	strTemp = token2;
	strTemp.TrimLeft();
	strTemp.TrimRight();
    dblAmpOffset = atof(strTemp);
	
	return TRUE;	
}
BOOL CDeviceManger::GetOSAEDFAResultForNET(long lChIndex,double *pdblSumSrcSigPwr, double *pdblSumAmpSigPwr, double *pdblSunGain)
{
	char szBuffer[2048];
	char *token=NULL;
	char szSpec[]=":";
	char *token2=NULL;
	CString strTemp;
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"OSA GEDFARESULT 1 %d\r",lChIndex);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}

	if(strstr(szBuffer,"OSA:AMP:RESULT")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
    token = strtok(szBuffer,szSpec);
	ASSERT(token);
	token = strtok(NULL,szSpec);
	ASSERT(token);
	token =  strtok(NULL,szSpec);
	ASSERT(token);
	token =  strtok(NULL,szSpec);
	token2 = strtok(token,",");
	ASSERT(token2);
	strTemp = token2;
	strTemp.TrimLeft();
	strTemp.TrimRight();
    *pdblSumSrcSigPwr = atof(strTemp);

	token2 = strtok(NULL,",");
	ASSERT(token2);
	strTemp = token2;
	strTemp.TrimLeft();
	strTemp.TrimRight();
    *pdblSumAmpSigPwr = atof(strTemp);

	token2 = strtok(NULL,",");
	ASSERT(token2);
	strTemp = token2;
	strTemp.TrimLeft();
	strTemp.TrimRight();
    *pdblSunGain = atof(strTemp);
	
	return TRUE;	
}

BOOL CDeviceManger::GetOSAEDFAChResultForNET(long lChIndex,DWORD *pwChCount, double *pdblChWL, double *pdblSrcpwr, double *pdblChGain, double *pdblChNF, double *pdblChAse,
											 double *pdblGainFlatness, double *pdblMaxNF, double* pdblMaxGain, double* pdblMinGain)
{

	char szBuffer[1024];
	char *token=NULL;
	char *token2=NULL;
	char szSpec[]=":";
    char * szBufferptr = NULL;
	CString strTemp;
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*1024);
	sprintf(szBuffer,"OSA GEDFACHRESULT 1 %d\r",lChIndex);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*1024);
	if(!ReadNetBuffer(szBuffer,32,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,32,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	
	if(strstr(szBuffer,"OSA:AMP:CHCOUNT")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
    token = strtok(szBuffer,szSpec);
	ASSERT(token);
	token = strtok(NULL,szSpec);
	ASSERT(token);
	token =  strtok(NULL,szSpec);
	ASSERT(token);
	token =  strtok(NULL,szSpec);	
    *pwChCount = atoi(token);

	ZeroMemory(szBuffer,sizeof(char)*1024);
	if(!ReadNetBuffer(szBuffer,32,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,32,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OSA:AMP:MaxNF")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
    token = strtok(szBuffer,szSpec);
	ASSERT(token);
	token = strtok(NULL,szSpec);
	ASSERT(token);
	token =  strtok(NULL,szSpec);
	ASSERT(token);
	token =  strtok(NULL,szSpec);	
    *pdblMaxNF = atoi(token);

	ZeroMemory(szBuffer,sizeof(char)*1024);
	if(!ReadNetBuffer(szBuffer,32,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,32,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OSA:AMP:MaxGain")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
    token = strtok(szBuffer,szSpec);
	ASSERT(token);
	token = strtok(NULL,szSpec);
	ASSERT(token);
	token =  strtok(NULL,szSpec);
	ASSERT(token);
	token =  strtok(NULL,szSpec);	
    *pdblMaxGain = atof(token);

	ZeroMemory(szBuffer,sizeof(char)*1024);
	if(!ReadNetBuffer(szBuffer,32,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,32,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OSA:AMP:MinGain")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
    token = strtok(szBuffer,szSpec);
	ASSERT(token);
	token = strtok(NULL,szSpec);
	ASSERT(token);
	token =  strtok(NULL,szSpec);
	ASSERT(token);
	token =  strtok(NULL,szSpec);	
    *pdblMinGain = atof(token);

	ZeroMemory(szBuffer,sizeof(char)*1024);
	if(!ReadNetBuffer(szBuffer,32,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,32,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OSA:AMP:GainFlatness")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
    token = strtok(szBuffer,szSpec);
	ASSERT(token);
	token = strtok(NULL,szSpec);
	ASSERT(token);
	token =  strtok(NULL,szSpec);
	ASSERT(token);
	token =  strtok(NULL,szSpec);	
    *pdblGainFlatness = atof(token);

	if(!ReceiveArryAndAnlysis("OSA:CH:WL",pdblChWL,nGetLength))
	{
		return FALSE;
	}

	if(!ReceiveArryAndAnlysis("OSA:CH:POW",pdblSrcpwr,nGetLength))
	{
		return FALSE;
	}	

	if(!ReceiveArryAndAnlysis("OSA:CH:GAIN",pdblChGain,nGetLength))
	{
		return FALSE;
	}

	if(!ReceiveArryAndAnlysis("OSA:CH:NF",pdblChNF,nGetLength))
	{
		return FALSE;
	}

	if(!ReceiveArryAndAnlysis("OSA:CH:ASE",pdblChAse,nGetLength))
	{
		return FALSE;
	}
	return TRUE;
	
}
BOOL CDeviceManger::InitOSASingleSweepForNET(long lChIndex,double dblStartWL, double dblStopWL, double dblRBW, DWORD dwSweepPoint)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"OSA SINISWEEP 5 %d %lf %lf %lf %d\r",lChIndex,dblStartWL,dblStopWL,dblRBW,dwSweepPoint);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;
}
BOOL CDeviceManger::RunOSASweepForNET(long lChIndex,double* pdblWL,double* pdblPower,char szSelTrace)
{
	char szBuffer[1024];
	char *token=NULL;
	char *token2=NULL;
	char szSpec[]=":";
    char * szBufferptr = NULL;
	CString strTemp;
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*1024);
	sprintf(szBuffer,"OSA SRUNSWEEP 2 %d %c\r",lChIndex,szSelTrace);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
    if(!ReceiveArryAndAnlysis("OSA:SWEEP:WL",pdblWL,nGetLength))
	{
	    return FALSE;	
	}
	
	if(!ReceiveArryAndAnlysis("OSA:SWEEP:POW",pdblPower,nGetLength))
	{
	    return FALSE;	
	}

	return TRUE;		
}
BOOL CDeviceManger::GetSingleSweepPointForNET(long lChIndex,DWORD *pdwPointCount)
{
	char szBuffer[2048];
	char *token=NULL;
	char szSpec[]=":";
	char *token2=NULL;
	CString strTemp;
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"OSA GSWEEPPOINT 1 %d\r",lChIndex);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}

	if(strstr(szBuffer,"OSA:AMP:RESULT")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
    token = strtok(szBuffer,szSpec);
	ASSERT(token);
	token = strtok(NULL,szSpec);
	ASSERT(token);
	token =  strtok(NULL,szSpec);
	ASSERT(token);
	strTemp = token;
	strTemp.TrimLeft();
	strTemp.TrimRight();
    *pdwPointCount = atof(strTemp);
	
	return TRUE;	
}
BOOL CDeviceManger::GetOSASweepDataForNET(long lChIndex,double* pdblWL,double* pdblPower, char szSelTrace)
{	
	char szBuffer[1024];
	char *token=NULL;
	char *token2=NULL;
	char szSpec[]=":";
    char * szBufferptr = NULL;
	CString strTemp;
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*1024);
	sprintf(szBuffer,"OSA GSWEEPDATA 2 %d %c\r",lChIndex,szSelTrace);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
    if(!ReceiveArryAndAnlysis("OSA:SWEEP:WL",pdblWL,nGetLength))
	{
	    return FALSE;	
	}
	if(!ReceiveArryAndAnlysis("OSA:SWEEP:POW",pdblPower,nGetLength))
	{
	    return FALSE;	
	}

	return TRUE;
}
BOOL CDeviceManger::SaveOSADataToPCForNET(long lChIndex,LPCTSTR lpSavePath, LPCTSTR lpDataType, LPCTSTR lpFileType, char szSelTrace)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"OSA SSAVEDATATOPC 5 %d %s %s %s %s %c\r",lChIndex,lpSavePath,lpDataType,lpFileType,szSelTrace);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;	
	
}
BOOL CDeviceManger::SetOSACalibrationForNET(long lChIndex,DWORD dwCalibrationType)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"OSA SCALIBRATE 2 %d %d\r",lChIndex,dwCalibrationType);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;	
}
BOOL CDeviceManger::GetZoomValueForNET(long lChIndex,double dbWLNM,double dbBWNM,double *pdbGetValue)
{
	char szBuffer[2048];
	char *token=NULL;
	char szSpec[]=":";
	char *token2=NULL;
	CString strTemp;
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"OSA GZOOMVALUE 1 %d %lf %lf\r",lChIndex,dbWLNM,dbBWNM);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}

	if(strstr(szBuffer,"OSA:AMP:RESULT")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
    token = strtok(szBuffer,szSpec);
	ASSERT(token);
	token = strtok(NULL,szSpec);
	ASSERT(token);
	token =  strtok(NULL,szSpec);
	ASSERT(token);
	strTemp = token;
	strTemp.TrimLeft();
	strTemp.TrimRight();
    *pdbGetValue = atof(strTemp);	
	return TRUE;	
}

////////////////SwtichBox网络函数///////////////////////////////////////////////////////////////
BOOL  CDeviceManger::CloseSwitchDeviceForNET(long lChIndex)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"SWITCH SCLOSE 1 %d\r",lChIndex);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;	
}
BOOL  CDeviceManger::OpenSwitchDeviceForNET(long lChIndex)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"SWITCH SOPEN 1 %d\r",lChIndex);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	return TRUE;	
}
BOOL  CDeviceManger::SwitchPort2PortForNET(int lChIndex,int nInputPort, int nOutputPort)
{
	char szBuffer[2048];
	int nGetLength;
	ZeroMemory(szBuffer,sizeof(char)*2048);
	sprintf(szBuffer,"SWITCH CH 3 %d %d %d\r",lChIndex,nInputPort,nOutputPort);
	if(!SendNetBuffer(szBuffer,strlen(szBuffer)))
	{
		m_strErrorMsg.Format("Send  %s error!",szBuffer);
		return FALSE;
	}
	Sleep(100);
	ZeroMemory(szBuffer,sizeof(char)*2048);
	if(!ReadNetBuffer(szBuffer,2048,nGetLength))
	{
		if(!ReadNetBuffer(szBuffer,2048,nGetLength))
		{
			m_strErrorMsg.Format("Receive buffer error!");
			return FALSE;	   
		}
	}
	if(strstr(szBuffer,"OK!")==NULL)
	{
		m_strErrorMsg = szBuffer;
		return FALSE;
	}
	
	return TRUE;

}