// TestUDLDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestUDL.h"
#include "TestUDLDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
typedef HRESULT (WINAPI * FREG)(); 
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestUDLDlg dialog

CTestUDLDlg::CTestUDLDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestUDLDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestUDLDlg)
	m_nTLSChIndex = 0;
	m_strValue = _T("");
	m_nPMChIndex = 0;
	m_strPMValue = _T("");
	m_nVOAChIndex = 0;
	m_strVOAValue = _T("");
	m_fTlsWav = 0.0;
	m_fTlsPower = 0.0;
	m_nTlsUnit = 0;
	m_strTlsMsg = _T("");
	m_bTlsOpen = FALSE;
	m_bTlsOpenCOH = FALSE;
	m_fPmWav = 0.0;
	m_nPMUnit = 0;
	m_nPmRange = 0;
	m_fPmTime = 0.0;
	m_fPmPower = 0.0;
	m_strPmMsg = _T("");
	m_strVOAMsg = _T("");
	m_bVoaEnable = FALSE;
	m_nOSAChIndex = 0;
	m_nOSAChCount = 0;
	m_fOSAGain = 0.0;
	m_strOSAMsg = _T("");
	m_fOSAOffset = 0.0;
	m_fOSAPower = 0.0;
	m_fOSAWav = 0.0;
	m_fOsaSNR = 0.0;
	m_fOsaRBW = 0.0;
	m_fOSAWavEnd = 0.0;
	m_nOSAPointCount = 0;
	m_bOurZoom = FALSE;
	m_fOSASrcOffset = 0.0;
	m_nPolChannel = 0;
	m_fPolAngle = 0.0f;
	m_nChamberChIndex = 0;
	m_fChamberTemp = 0.0f;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestUDLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestUDLDlg)
	DDX_Text(pDX, IDC_EDIT_TLS_CHANNEL, m_nTLSChIndex);
	DDV_MinMaxInt(pDX, m_nTLSChIndex, 0, 100);
	DDX_Text(pDX, IDC_EDIT_TLS_VALUE, m_strValue);
	DDX_Text(pDX, IDC_EDIT_PM_CHANNEL, m_nPMChIndex);
	DDV_MinMaxInt(pDX, m_nPMChIndex, 0, 100);
	DDX_Text(pDX, IDC_EDIT_PM_VALUE, m_strPMValue);
	DDX_Text(pDX, IDC_EDIT_VOA_CHANNEL, m_nVOAChIndex);
	DDV_MinMaxInt(pDX, m_nVOAChIndex, 0, 100);
	DDX_Text(pDX, IDC_EDIT_VOA_VALUE, m_strVOAValue);
	DDX_Text(pDX, IDC_EDIT_TLS_WAV, m_fTlsWav);
	DDX_Text(pDX, IDC_EDIT_TLS_POWER, m_fTlsPower);
	DDX_Text(pDX, IDC_EDIT_TLS_UNIT, m_nTlsUnit);
	DDX_Text(pDX, IDC_EDIT_TLS_MSG, m_strTlsMsg);
	DDX_Check(pDX, IDC_CHECK_OPEN, m_bTlsOpen);
	DDX_Check(pDX, IDC_CHECK_OPENCOH, m_bTlsOpenCOH);
	DDX_Text(pDX, IDC_EDIT_PM_WAV, m_fPmWav);
	DDX_Text(pDX, IDC_EDIT_PM_UNIT, m_nPMUnit);
	DDX_Text(pDX, IDC_EDIT_PM_RANGE, m_nPmRange);
	DDX_Text(pDX, IDC_EDIT_PM_TIME, m_fPmTime);
	DDX_Text(pDX, IDC_EDIT_PM_POWER, m_fPmPower);
	DDX_Text(pDX, IDC_EDIT_PM_MSG, m_strPmMsg);
	DDX_Text(pDX, IDC_EDIT_VOA_MSG, m_strVOAMsg);
	DDX_Check(pDX, IDC_CHECK_VOA_ENABLE, m_bVoaEnable);
	DDX_Text(pDX, IDC_EDIT_OSA_CH, m_nOSAChIndex);
	DDX_Text(pDX, IDC_EDIT_OSA_CH_COUNT, m_nOSAChCount);
	DDX_Text(pDX, IDC_EDIT_OSA_GAIN, m_fOSAGain);
	DDX_Text(pDX, IDC_EDIT_OSA_MSG, m_strOSAMsg);
	DDX_Text(pDX, IDC_EDIT_OSA_OFFSET, m_fOSAOffset);
	DDX_Text(pDX, IDC_EDIT_OSA_POWER, m_fOSAPower);
	DDX_Text(pDX, IDC_EDIT_OSA_WAV, m_fOSAWav);
	DDX_Text(pDX, IDC_EDIT_OSA_SNR, m_fOsaSNR);
	DDX_Text(pDX, IDC_EDIT_OSA_RBW, m_fOsaRBW);
	DDX_Text(pDX, IDC_EDIT_OSA_WAV2, m_fOSAWavEnd);
	DDX_Text(pDX, IDC_EDIT_OSA_POINT, m_nOSAPointCount);
	DDX_Check(pDX, IDC_CHECK_OURZOOM, m_bOurZoom);
	DDX_Text(pDX, IDC_EDIT_OSA_SRCOFFSET, m_fOSASrcOffset);
	DDX_Text(pDX, IDC_EDIT_POL_CHANNEL, m_nPolChannel);
	DDX_Text(pDX, IDC_EDIT_POL_ANGLE, m_fPolAngle);
	DDX_Text(pDX, IDC_EDIT_CHAMBER_CHANNEL, m_nChamberChIndex);
	DDX_Text(pDX, IDC_EDIT_CHAMBER_TEMP, m_fChamberTemp);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestUDLDlg, CDialog)
	//{{AFX_MSG_MAP(CTestUDLDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_BTN_OPEN, OnBtnOpen)
	ON_BN_CLICKED(IDC_BTN_SETTING_WL, OnBtnSettingWl)
	ON_BN_CLICKED(IDC_BTN_READ_PM, OnBtnReadPm)
	ON_BN_CLICKED(IDC_BTN_TLS_POWER, OnBtnTlsPower)
	ON_BN_CLICKED(IDC_BTN_TLS_ENABLE, OnBtnTlsEnable)
	ON_BN_CLICKED(IDC_BTN_TLS_UNIT, OnBtnTlsUnit)
	ON_BN_CLICKED(IDC_BTN_TLS_PARAMETERS, OnBtnTlsParameters)
	ON_BN_CLICKED(IDC_BTN_PM_WL, OnBtnPmWl)
	ON_BN_CLICKED(IDC_BTN_PM_UNIT, OnBtnPmUnit)
	ON_BN_CLICKED(IDC_BTN_PM_RANGE, OnBtnPmRange)
	ON_BN_CLICKED(IDC_BTN_PM_AVGTIME, OnBtnPmAvgtime)
	ON_BN_CLICKED(IDC_BTN_PM_PARAMTER, OnBtnPmParamter)
	ON_BN_CLICKED(IDC_BTN_VOA_WL, OnBtnVoaWl)
	ON_BN_CLICKED(IDC_BTN_VOA_ATTEN, OnBtnVoaAtten)
	ON_BN_CLICKED(IDC_BTN_VOA_READ_WL, OnBtnVoaReadWl)
	ON_BN_CLICKED(IDC_BTN_VOA_READ_ATTEN, OnBtnVoaReadAtten)
	ON_BN_CLICKED(IDC_BTN_TLS_CLOSE, OnBtnTlsClose)
	ON_BN_CLICKED(IDC_BTN_TLS_MSG, OnBtnTlsMsg)
	ON_BN_CLICKED(IDC_CHECK_OPEN, OnCheckOpen)
	ON_BN_CLICKED(IDC_CHECK_OPENCOH, OnCheckOpencoh)
	ON_BN_CLICKED(IDC_BTN_PM_RANGE2, OnBtnPmRange2)
	ON_BN_CLICKED(IDC_BTN_PM_ZERO, OnBtnPmZero)
	ON_BN_CLICKED(IDC_BTN_PM_MSG, OnBtnPmMsg)
	ON_BN_CLICKED(IDC_BTN_VOA_OFFSET, OnBtnVoaOffset)
	ON_BN_CLICKED(IDC_BTN_VOA_CLOSE, OnBtnVoaClose)
	ON_BN_CLICKED(IDC_BTN_VOA_RESET, OnBtnVoaReset)
	ON_BN_CLICKED(IDC_BTN_VOA_STATE, OnBtnVoaState)
	ON_BN_CLICKED(IDC_BTN_VOA_MSG, OnBtnVoaMsg)
	ON_BN_CLICKED(IDC_CHECK_VOA_ENABLE, OnCheckVoaEnable)
	ON_BN_CLICKED(IDC_BTN_OSA_SETRBW, OnBtnOsaSetrbw)
	ON_BN_CLICKED(IDC_BTN_OSA_GETRBW, OnBtnOsaGetrbw)
	ON_BN_CLICKED(IDC_BTN_OSA_CLOSE, OnBtnOsaClose)
	ON_BN_CLICKED(IDC_BTN_OSA_RESET, OnBtnOsaReset)
	ON_BN_CLICKED(IDC_BTN_OSA_INIT, OnBtnOsaInit)
	ON_BN_CLICKED(IDC_BTN_OSA_LCMODE, OnBtnOsaLcmode)
	ON_BN_CLICKED(IDC_BTN_OSA_SCAN, OnBtnOsaScan)
	ON_BN_CLICKED(IDC_BTN_OSA_SCANZOOM, OnBtnOsaScanzoom)
	ON_BN_CLICKED(IDC_BTN_OSA_CHCOUNT, OnBtnOsaChcount)
	ON_BN_CLICKED(IDC_BTN_OSA_WAV, OnBtnOsaWav)
	ON_BN_CLICKED(IDC_BTN_OSA_GAIN, OnBtnOsaGain)
	ON_BN_CLICKED(IDC_BTN_OSA_POWER, OnBtnOsaPower)
	ON_BN_CLICKED(IDC_BTN_OSA_SETOFFSET, OnBtnOsaSetoffset)
	ON_BN_CLICKED(IDC_BTN_OSA_SNR, OnBtnOsaSnr)
	ON_BN_CLICKED(IDC_BTN_OSA_GETOFFSET, OnBtnOsaGetoffset)
	ON_BN_CLICKED(IDC_BTN_OSA_ZOOM_RESULT, OnBtnOsaZoomResult)
	ON_BN_CLICKED(IDC_BTN_OSA_MSG, OnBtnOsaMsg)
	ON_BN_CLICKED(IDC_BTN_OSA_SAVE, OnBtnOsaSave)
	ON_BN_CLICKED(IDC_BTN_OSA_GETDATA, OnBtnOsaGetdata)
	ON_BN_CLICKED(IDC_BTN_OSA_GETDATAONCE, OnBtnOsaGetdataonce)
	ON_BN_CLICKED(IDC_BTN_OSA_NF, OnBtnOsaNf)
	ON_BN_CLICKED(IDC_BTN_OSA_RUN, OnBtnOsaRun)
	ON_BN_CLICKED(IDC_BTN_OSA_INITSINGLESCAN, OnBtnOsaInitsinglescan)
	ON_BN_CLICKED(IDC_BTN_OSA_SCAN_RESULT, OnBtnOsaScanResult)
	ON_BN_CLICKED(IDC_BTN_CLOSE, OnBtnClose)
	ON_BN_CLICKED(IDC_BTN_POL_POLAZIER, OnBtnPolPolazier)
	ON_BN_CLICKED(IDC_BTN_POL_POLAZIER2, OnBtnPolPolazier2)
	ON_BN_CLICKED(IDC_BTN_POL_POLAZIER3, OnBtnPolPolazier3)
	ON_BN_CLICKED(IDC_BTN_CHAMBER_CURRENT_TEMP, OnBtnChamberCurrentTemp)
	ON_BN_CLICKED(IDC_BTN_CHAMBER_SETTEP, OnBtnChamberSettep)
	ON_BN_CLICKED(IDC_BTN_CHAMBER_GETSETTEMP, OnBtnChamberGetsettemp)
	ON_BN_CLICKED(IDC_BTN_POL_GetPOLAZIER, OnBTNPOLGetPOLAZIER)
	ON_BN_CLICKED(IDC_BTN_COMTEST, OnBtnComtest)
	ON_BN_CLICKED(IDC_BTN_PM_GETWL, OnBtnPmGetwl)
	ON_BN_CLICKED(IDC_BTN_PM_GETUNIT, OnBtnPmGetunit)
	ON_BN_CLICKED(IDC_BTN_PM_GETAVGTIME, OnBtnPmGetavgtime)
	ON_BN_CLICKED(IDC_BTN_CLOSECOM, OnBtnClosecom)
	ON_BN_CLICKED(IDC_BTN_OPENCOM, OnBtnOpencom)
	ON_BN_CLICKED(IDC_BTN_PM_OFFSET, OnBtnPmOffset)
	ON_BN_CLICKED(IDC_BTN_PM_MAXMIN, OnBtnPmMaxmin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestUDLDlg message handlers

BOOL CTestUDLDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
    ::CoInitialize(NULL);
	//HRESULT hr 	=m_pTLS.CreateInstance( _T("UDL.DLM.ITLSInterface"));//启动组件

	HRESULT hr = m_pEngine.CreateInstance(__uuidof(EngineMgr));
	if (FAILED(hr))
	{
		_com_error e(hr);
		AfxMessageBox(e.ErrorMessage());

	}
	ASSERT( SUCCEEDED( hr ) );
    m_pEngine->RegisterUDL();

	hr 	=m_pTLS.CreateInstance(__uuidof(ITLSInterface));
    ASSERT( SUCCEEDED( hr ) );
	//hr 	=m_pTLS.CreateInstance( _T("UDL.ITLSInterface"));//启动组件
	
	hr 	=m_pPM.CreateInstance( __uuidof(IPMInterface));//启动组件
	ASSERT( SUCCEEDED( hr ) );

	hr 	=m_pVOA.CreateInstance( __uuidof(IVOAInterface));//启动组件
	ASSERT( SUCCEEDED( hr ) );

	hr 	=m_pOSA.CreateInstance( __uuidof(IOSAInterface));//启动组件
	ASSERT( SUCCEEDED( hr ) );

	hr 	=m_pPol.CreateInstance( __uuidof(IPolInterface));//启动组件
	ASSERT( SUCCEEDED( hr ) );
	
	hr 	=m_pScan.CreateInstance( __uuidof(ScanInterface));//启动组件
	ASSERT( SUCCEEDED( hr ) );
	
	hr 	=m_pChamber.CreateInstance( __uuidof(ChamberInterface));//启动组件
	ASSERT( SUCCEEDED( hr ) );

	hr   =m_pComDev.CreateInstance( __uuidof(IComDevInterface));//启动组件
	ASSERT( SUCCEEDED( hr ) );

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestUDLDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestUDLDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestUDLDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



void CTestUDLDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
    m_pEngine.Release();
	m_pTLS.Release();
	m_pPM.Release();
	m_pVOA.Release();
	m_pOSA.Release();
	m_pPol.Release();
	m_pScan.Release();
	m_pChamber.Release();
	m_pComDev.Release();
	::CoUninitialize();
	
	CDialog::OnClose();
}

void CTestUDLDlg::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void CTestUDLDlg::OnBtnOpen() 
{
    char szBuffer[MAX_PATH];
	GetCurrentDirectory(MAX_PATH,szBuffer);
	CString strConfigFile;
	strConfigFile.Format("%s\\UDLConfig.xml",szBuffer);
	
//	m_pEngine->SetUDLNET(TRUE);
//	CString strIPAddress;
//	strIPAddress.Format("172.16.143.95");
//    HRESULT hr2 = m_pEngine->ConnectToServer((_bstr_t)strIPAddress);
//	if (hr2 == S_FALSE)
//	{
//		AfxMessageBox(m_pEngine->GetGetLastMessage());
//		return;
//	}
	m_pEngine->LoadConfiguration((_bstr_t)strConfigFile);
	AfxMessageBox(m_pEngine->GetGetLastMessage());
	
	HRESULT hr = m_pEngine->OpenEngine();
	if (hr ==S_FALSE)
	{
		AfxMessageBox(m_pEngine->GetGetLastMessage());
	}
	AfxMessageBox(m_pEngine->GetGetLastMessage());
}

void CTestUDLDlg::OnBtnSettingWl() 
{
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}

	UpdateData(TRUE);

	HRESULT hr = m_pTLS->SetTLSWavelength(m_nTLSChIndex, m_fTlsWav);
	AfxMessageBox(m_pTLS->GetLastMessage());
}

void CTestUDLDlg::OnOK() 
{
	// TODO: Add extra validation here
	
//	CDialog::OnOK();
}

void CTestUDLDlg::OnBtnTlsPower() 
{
	UpdateData(TRUE);
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}
	
	UpdateData(TRUE);
	m_pTLS->SetTLSSourcePower(m_nTLSChIndex, m_fTlsPower);
	AfxMessageBox(m_pTLS->GetLastMessage());
}

void CTestUDLDlg::OnBtnTlsEnable() 
{
	UpdateData(TRUE);
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}

	CString strValue;
	UpdateData(TRUE);
	GetDlgItem(IDC_BTN_TLS_ENABLE)->GetWindowText(strValue);
	if (strValue == "开启出光")
	{
		m_pTLS->SetTLSOutputEnable(m_nTLSChIndex, 1);
		GetDlgItem(IDC_BTN_TLS_ENABLE)->SetWindowText("关闭出光");
	}
	else if(strValue =="关闭出光")
	{
		m_pTLS->SetTLSOutputEnable(m_nTLSChIndex, 0);
		GetDlgItem(IDC_BTN_TLS_ENABLE)->SetWindowText("开启出光");
	}
}

void CTestUDLDlg::OnBtnTlsUnit() 
{
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}

	UpdateData(TRUE);
	m_pTLS->SetTLSSourceUnit(m_nTLSChIndex, m_nTlsUnit);
	AfxMessageBox(m_pTLS->GetLastMessage());
}

void CTestUDLDlg::OnBtnTlsParameters() 
{
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}
	
	UpdateData(TRUE);
	m_pTLS->SetTLSParameters(m_nTLSChIndex,TRUE, m_fTlsPower, m_fTlsWav);
	AfxMessageBox(m_pTLS->GetLastMessage());
}

void CTestUDLDlg::OnBtnPmWl() 
{
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}
	
	UpdateData(TRUE);
	if(m_pPM->SetWavelength(m_nPMChIndex, m_fPmWav)!=S_OK)
	{
		AfxMessageBox(m_pPM->GetLastMessage());
	}
	AfxMessageBox(m_pPM->GetLastMessage());
}

void CTestUDLDlg::OnBtnPmUnit() 
{
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}
	
	UpdateData(TRUE);
	m_pPM->SetUnit(m_nPMChIndex, m_nPMUnit);
	AfxMessageBox(m_pPM->GetLastMessage());	
}

void CTestUDLDlg::OnBtnPmRange() 
{
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}

	UpdateData(TRUE);
	m_pPM->SetRangeMode(m_nPMChIndex, m_nPmRange);
	AfxMessageBox(m_pPM->GetLastMessage());	
}

void CTestUDLDlg::OnBtnPmAvgtime() 
{
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}

	UpdateData(TRUE);
	m_pPM->SetAverageTime(m_nPMChIndex, m_fPmTime);
	AfxMessageBox(m_pPM->GetLastMessage());	
}

void CTestUDLDlg::OnBtnPmParamter() 
{
	UpdateData(TRUE);
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}

	UpdateData(TRUE);
	m_pPM->SetParameters(m_nPMChIndex, m_nPmRange, m_fPmWav, m_fPmTime, m_fPmPower);
	AfxMessageBox(m_pPM->GetLastMessage());
}


void CTestUDLDlg::OnBtnReadPm() 
{
    UpdateData(TRUE);
	double dbPower;
	CString strPower;

//	for(int i =0;i<10;i++)
	{
		m_pPM->GetPower(m_nPMChIndex,&dbPower);
		
		strPower.Format("%.4f",dbPower);
		GetDlgItem(IDC_EDIT_PM_POWER)->SetWindowText(strPower);
		Sleep(100);
	}

	//AfxMessageBox(m_pPM->GetLastMessage());
}

void CTestUDLDlg::OnBtnVoaWl() 
{
	// TODO: Add your control notification handler code here
	double  dbSetWL;
	UpdateData(TRUE);
	dbSetWL = atof(m_strVOAValue);
	m_pVOA->SetVOAWavelength(m_nVOAChIndex,dbSetWL);
	AfxMessageBox(m_pVOA->GetLastMessage());
}

void CTestUDLDlg::OnBtnVoaAtten() 
{
	// TODO: Add your control notification handler code here
	double  dbSetAtten;
	UpdateData(TRUE);
	dbSetAtten = atof(m_strVOAValue);
	m_pVOA->SetVOAAttenuation(m_nVOAChIndex,dbSetAtten);
	AfxMessageBox(m_pVOA->GetLastMessage());	
}

void CTestUDLDlg::OnBtnVoaReadWl() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	double dbWL;
	m_pVOA->GetVOAWavelength(m_nVOAChIndex,&dbWL);
	CString strValue;
	strValue.Format("%.3f",dbWL);
	GetDlgItem(IDC_BTN_VOA_READ_WL)->SetWindowText(strValue);
	AfxMessageBox(m_pVOA->GetLastMessage());
}

void CTestUDLDlg::OnBtnVoaReadAtten() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	double dbValue;
	m_pVOA->GetVOAAttenuation(m_nVOAChIndex,&dbValue);
	CString strValue;
	strValue.Format("%.3f",dbValue);
	GetDlgItem(IDC_BTN_VOA_READ_ATTEN)->SetWindowText(strValue);
	AfxMessageBox(m_pVOA->GetLastMessage());
}


void CTestUDLDlg::OnBtnTlsClose() 
{
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}
	
	UpdateData(TRUE);
	m_pTLS->CloseTLSDevice(m_nTLSChIndex);
}

void CTestUDLDlg::OnBtnTlsMsg() 
{
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}

	m_strTlsMsg = (LPCSTR)m_pTLS->GetLastMessage();
	UpdateData(FALSE);
}


void CTestUDLDlg::OnCheckOpen() 
{
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		UpdateData(FALSE);
		return;
	}
	
	UpdateData(TRUE);
	m_pTLS->SetTLSOutputEnable(m_nTLSChIndex, m_bTlsOpen);
}

void CTestUDLDlg::OnCheckOpencoh() 
{
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		UpdateData(FALSE);
		return;
	}
	
	UpdateData(TRUE);
	m_pTLS->SetTLSCoherenceControl(m_nTLSChIndex, m_bTlsOpenCOH);
}

void CTestUDLDlg::OnBtnPmRange2() 
{
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}
	long lRange;
	CString strValue;
	m_pPM->GetRangeMode(m_nPMChIndex,&lRange);
	m_nPmRange = lRange;
	UpdateData(FALSE);
    strValue.Format("%ld",lRange);
	GetDlgItem(IDC_BTN_PM_RANGE2)->SetWindowText(strValue);	
	AfxMessageBox(m_pPM->GetLastMessage());	
}

void CTestUDLDlg::OnBtnPmZero() 
{
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}
	
	m_pPM->SetZero(m_nPMChIndex);
}

void CTestUDLDlg::OnBtnPmMsg() 
{
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}

	m_strPmMsg = (LPCSTR)m_pPM->GetLastMessage();
	UpdateData(FALSE);	
}

void CTestUDLDlg::OnBtnVoaOffset() 
{
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}

	UpdateData(TRUE);

	double fOffset;
	fOffset = atof(m_strVOAValue);
	m_pVOA->SetVOAInputOffset(m_nVOAChIndex, fOffset);			
	AfxMessageBox(m_pVOA->GetLastMessage());	
}

void CTestUDLDlg::OnBtnVoaClose() 
{
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}

	UpdateData(TRUE);
	m_pVOA->CloseVOADevice(m_nVOAChIndex);	
	AfxMessageBox(m_pVOA->GetLastMessage());
}

void CTestUDLDlg::OnBtnVoaReset() 
{
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}

	UpdateData(TRUE);
	m_pVOA->ResetVOADevice(m_nVOAChIndex);
	AfxMessageBox(m_pVOA->GetLastMessage());
}

void CTestUDLDlg::OnBtnVoaState() 
{
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}

	UpdateData(TRUE);
	long lValue; 	
	CString strValue;
	m_pVOA->GetVOAStatus(m_nVOAChIndex,&lValue);
	strValue.Format("%ld",lValue);
	GetDlgItem(IDC_BTN_VOA_STATE)->SetWindowText(strValue);	
	UpdateData(FALSE);
}

void CTestUDLDlg::OnBtnVoaMsg() 
{
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}

	m_strVOAMsg = (LPCSTR)m_pVOA->GetLastMessage();
	UpdateData(FALSE);
}

void CTestUDLDlg::OnCheckVoaEnable() 
{
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		UpdateData(FALSE);
		return;
	}
	
	UpdateData();
	m_pVOA->SetVOAEnableOutput(m_nVOAChIndex, m_bVoaEnable);
	AfxMessageBox(m_pVOA->GetLastMessage());
}

void CTestUDLDlg::OnBtnOsaSetrbw() 
{
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}
	
	UpdateData(TRUE);
	m_pOSA->SetOSARBW(m_nOSAChIndex, m_fOsaRBW);

}

void CTestUDLDlg::OnBtnOsaGetrbw() 
{
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}
	
	UpdateData(TRUE);
	double dbGetRBW;
	
	m_pOSA->GetOSARBW(m_nOSAChIndex,&dbGetRBW);
	m_fOsaRBW = dbGetRBW;
	UpdateData(FALSE);
	AfxMessageBox(m_pOSA->GetLastMessage());
}

void CTestUDLDlg::OnBtnOsaClose() 
{
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}
	
	m_pOSA->CloseDevice(m_nOSAChIndex);
	AfxMessageBox(m_pOSA->GetLastMessage());
}

void CTestUDLDlg::OnBtnOsaReset() 
{
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}
	
	m_pOSA->ResetDevice(m_nOSAChIndex);
	AfxMessageBox(m_pOSA->GetLastMessage());
}

void CTestUDLDlg::OnBtnOsaInit() 
{
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}
	
	UpdateData();
	m_pOSA->InitOSAAmpTest(m_nOSAChIndex, m_fOSAWav, m_fOSAWavEnd, m_fOsaRBW);
	AfxMessageBox(m_pOSA->GetLastMessage());
}

void CTestUDLDlg::OnBtnOsaLcmode() 
{
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}
	
	UpdateData();
	m_pOSA->SetOSALocalCtrl(m_nOSAChIndex);
	AfxMessageBox(m_pOSA->GetLastMessage());
}

void CTestUDLDlg::OnBtnOsaScan() 
{
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}
	
	UpdateData();
	m_pOSA->MeasureSource(m_nOSAChIndex);
	AfxMessageBox(m_pOSA->GetLastMessage());
}

void CTestUDLDlg::OnBtnOsaScanzoom() 
{
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}
	
	UpdateData();
	m_pOSA->MeasureAmplifier(m_nOSAChIndex, m_bOurZoom);
	AfxMessageBox(m_pOSA->GetLastMessage());
}

void CTestUDLDlg::OnBtnOsaChcount() 
{
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}
	
	UpdateData();
	long lChCount;
	m_pOSA->GetOSAChannelCount(m_nOSAChIndex,&lChCount);
	m_nOSAChCount = lChCount;
	UpdateData(FALSE);
	AfxMessageBox(m_pOSA->GetLastMessage());
}

void CTestUDLDlg::OnBtnOsaWav() 
{
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}

	UpdateData();
	double listWav[96];
	DWORD dwCount;
	m_pOSA->raw_GetChannelWaveLens(m_nOSAChIndex, listWav, &dwCount);

	m_fOSAWav = listWav[m_nOSAChIndex];
	UpdateData(FALSE);
	AfxMessageBox(m_pOSA->GetLastMessage());
}

void CTestUDLDlg::OnBtnOsaGain() 
{
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}

	UpdateData();
	double listGain[96];
	DWORD dwCount;
	m_pOSA->GetChannelGain(m_nOSAChIndex, listGain, &dwCount);

	m_fOSAGain = listGain[m_nOSAChIndex];
	UpdateData(FALSE);
	AfxMessageBox(m_pOSA->GetLastMessage());
}

void CTestUDLDlg::OnBtnOsaPower() 
{
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}

	UpdateData();
	double listPower[96];
	DWORD dwCount;
	m_pOSA->GetChannelSourcePower(m_nOSAChIndex, listPower, &dwCount);

	m_fOSAPower = listPower[m_nOSAChIndex];
	UpdateData(FALSE);
	AfxMessageBox(m_pOSA->GetLastMessage());
}

void CTestUDLDlg::OnBtnOsaSetoffset() 
{
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}

	UpdateData();
	m_pOSA->SetOSAAmpOffset(m_nOSAChIndex, m_fOSASrcOffset, m_fOSAOffset);
	AfxMessageBox(m_pOSA->GetLastMessage());
}

void CTestUDLDlg::OnBtnOsaSnr() 
{
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}

	UpdateData();
	double listSNR[96];
	DWORD dwCount;
	m_pOSA->GetChannelSNR(m_nOSAChIndex, listSNR, &dwCount);

	m_fOsaSNR = listSNR[m_nOSAChIndex];
	UpdateData(FALSE);
	AfxMessageBox(m_pOSA->GetLastMessage());
}

void CTestUDLDlg::OnBtnOsaGetoffset() 
{
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}

	UpdateData();
	m_pOSA->GetOSAAmpOffset(m_nOSAChIndex, &m_fOSASrcOffset, &m_fOSAOffset);
	UpdateData(FALSE);
	AfxMessageBox(m_pOSA->GetLastMessage());
}

void CTestUDLDlg::OnBtnOsaZoomResult() 
{
	
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}
	
	UpdateData();
	double dbSource,dbAmp,dbSumGain;
	m_pOSA->GetOSAEDFAResult(m_nOSAChIndex, &dbSource, &dbAmp,&dbSumGain);
	CString strTemp;
	strTemp.Format("Source power:%lf,Amp Power:%lf, Sum Gain:%lf",dbSource,dbAmp,dbSumGain);
	AfxMessageBox(strTemp);
	UpdateData(FALSE);
	AfxMessageBox(m_pOSA->GetLastMessage());
		
}

void CTestUDLDlg::OnBtnOsaMsg() 
{
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}

	m_strOSAMsg = (LPCSTR)m_pOSA->GetLastMessage();
	UpdateData(FALSE);
}

void CTestUDLDlg::OnBtnOsaSave() 
{
    m_pOSA->SaveOSADataToPC(0,"D://","TRACE","CSV","C");
	//
}

void CTestUDLDlg::OnBtnOsaGetdata() 
{
	// TODO: Add your control notification handler code here
	FILE *fpFile=NULL;
	CString strFileName;
	CString strTemp;
	char szBuf[MAX_PATH];
	UpdateData();
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}
	double *dbwl=NULL,*dbPower=NULL;
	if (dbwl ==NULL)
	{
		dbwl = (double*)VirtualAlloc(NULL,sizeof(double)*m_nOSAPointCount,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
		ZeroMemory(dbwl,sizeof(double)*m_nOSAPointCount);
	}
	if (dbPower ==NULL)
	{
		dbPower = (double*)VirtualAlloc(NULL,sizeof(double)*m_nOSAPointCount,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
		ZeroMemory(dbPower,sizeof(double)*m_nOSAPointCount);
	}

	UpdateData(TRUE);
	m_pOSA->GetOSASweepData(m_nOSAChIndex,dbwl,dbPower,"A");

	GetCurrentDirectory(MAX_PATH,szBuf);
	strFileName.Format("%s\\data_1.csv",szBuf);

    fpFile = fopen(strFileName.GetBuffer(0),"w+");
	for (int i=0;i<m_nOSAPointCount;i++)
	{
		strTemp.Format("%lf,%lf",dbwl[i],dbPower[i]);
		fprintf(fpFile,"%s\n",strTemp);
	}

	if (fpFile!=NULL)
	{
		fclose(fpFile);
	}

	AfxMessageBox(m_pOSA->GetLastMessage());
	if(dbwl!=NULL)
	{
		VirtualFree(dbwl,0,MEM_RELEASE);
	}
	if(dbPower!=NULL)
	{
		VirtualFree(dbPower,0,MEM_RELEASE);
	}
}

void CTestUDLDlg::OnBtnOsaGetdataonce() 
{
	// TODO: Add your control notification handler code here
	
}

void CTestUDLDlg::OnBtnOsaNf() 
{
	// TODO: Add your control notification handler code here
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}
	double *dbwl=NULL,*dbPower=NULL,*dbNF=NULL;
//	if (dbwl ==NULL)
//	{
//		dbwl = (double*)VirtualAlloc(NULL,sizeof(double)*1000,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
//	}
//	if (dbPower ==NULL)
//	{
//		dbPower = (double*)VirtualAlloc(NULL,sizeof(double)*1000,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
//	}
	if (dbNF ==NULL)
	{
		dbNF = (double*)VirtualAlloc(NULL,sizeof(double)*1000,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
	}
	
	UpdateData(TRUE);
	DWORD dwChanCount;
	m_pOSA->GetChannelNF(m_nOSAChIndex,dbNF,&dwChanCount);
	AfxMessageBox(m_pOSA->GetLastMessage());
	if(dbNF!=NULL)
	{
		VirtualFree(dbNF,0,MEM_RELEASE);
	}
}

void CTestUDLDlg::OnBtnOsaRun() 
{
	// TODO: Add your control notification handler code here
	FILE *fpFile=NULL;
	CString strFileName;
	CString strTemp;
	char szBuf[MAX_PATH];
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}
	double *dbwl=NULL,*dbPower=NULL;
	if (dbwl ==NULL)
	{
		dbwl = (double*)VirtualAlloc(NULL,sizeof(double)*m_nOSAPointCount,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
		ZeroMemory(dbwl,sizeof(double)*m_nOSAPointCount);
	}
	if (dbPower ==NULL)
	{
		dbPower = (double*)VirtualAlloc(NULL,sizeof(double)*m_nOSAPointCount,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
		ZeroMemory(dbPower,sizeof(double)*m_nOSAPointCount);
	}

	UpdateData(TRUE);
	m_pOSA->RunOSASweep(m_nOSAChIndex,dbwl,dbPower,"A");

	GetCurrentDirectory(MAX_PATH,szBuf);
	strFileName.Format("%s\\data.csv",szBuf);

    fpFile = fopen(strFileName.GetBuffer(0),"w+");
	for (int i=0;i<m_nOSAPointCount;i++)
	{
		strTemp.Format("%lf,%lf",dbwl[i],dbPower[i]);
		fprintf(fpFile,"%s\n",strTemp);
	}

	if (fpFile!=NULL)
	{
		fclose(fpFile);
	}

	AfxMessageBox(m_pOSA->GetLastMessage());
	if(dbwl!=NULL)
	{
		VirtualFree(dbwl,0,MEM_RELEASE);
	}
	if(dbPower!=NULL)
	{
		VirtualFree(dbPower,0,MEM_RELEASE);
	}
}

void CTestUDLDlg::OnBtnOsaInitsinglescan() 
{
	// TODO: Add your control notification handler code here
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}
	
	UpdateData(TRUE);
	m_pOSA->InitOSASingleSweep(m_nOSAChIndex,m_fOSAWav,m_fOSAWavEnd, m_fOsaRBW,m_nOSAPointCount);
	AfxMessageBox(m_pOSA->GetLastMessage());
}

void CTestUDLDlg::OnBtnOsaScanResult() 
{
	// TODO: Add your control notification handler code here
	FILE *fpFile=NULL;
	CString strFileName;
	CString strTemp;
	
	char szBuf[MAX_PATH];
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}
	double *dbwl=NULL,*dbPower=NULL;
	double *dbGain =NULL;
	double *dbNF =NULL,*dbASE =NULL;
	if (dbwl ==NULL)
	{
		dbwl = (double*)VirtualAlloc(NULL,sizeof(double)*256,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
		ZeroMemory(dbwl,sizeof(double)*256);
	}
	if (dbPower ==NULL)
	{
		dbPower = (double*)VirtualAlloc(NULL,sizeof(double)*256,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
		ZeroMemory(dbPower,sizeof(double)*256);
	}
	if (dbGain ==NULL)
	{
		dbGain = (double*)VirtualAlloc(NULL,sizeof(double)*256,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
		ZeroMemory(dbGain,sizeof(double)*256);
	}
	if (dbNF ==NULL)
	{
		dbNF = (double*)VirtualAlloc(NULL,sizeof(double)*256,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
		ZeroMemory(dbGain,sizeof(double)*256);
	}
	if (dbASE ==NULL)
	{
		dbASE = (double*)VirtualAlloc(NULL,sizeof(double)*256,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
		ZeroMemory(dbGain,sizeof(double)*256);
	}

	UpdateData(TRUE);
	long lChCount=0;
	double dbFlateness;
	double dbMaxNf;
	double dbMaxGain;
	double dbMinGain;
	m_pOSA->GetOSAEDFAChResult(m_nOSAChIndex,&lChCount,dbwl,dbPower,dbGain,dbNF,dbASE,&dbFlateness,&dbMaxNf,&dbMaxGain,&dbMinGain);

	GetCurrentDirectory(MAX_PATH,szBuf);
	strFileName.Format("%s\\data_CH.csv",szBuf);

    fpFile = fopen(strFileName.GetBuffer(0),"w");
	strTemp.Format("Flatness,%lf",dbFlateness);
	fprintf(fpFile,"%s\n",strTemp);
	strTemp.Format("MaxNF,%lf",dbMaxNf);
	fprintf(fpFile,"%s\n",strTemp);
	strTemp.Format("MaxGain,%lf",dbMaxGain);
	fprintf(fpFile,"%s\n",strTemp);
		strTemp.Format("MinGain,%lf",dbMinGain);
	fprintf(fpFile,"%s\n",strTemp);
	for (int i=0;i<lChCount;i++)
	{
		strTemp.Format("%lf,%lf,%lf,%lf,%lf",dbwl[i],dbPower[i],dbGain[i],dbNF[i],dbASE[i]);
		fprintf(fpFile,"%s\n",strTemp);
	}

	if (fpFile!=NULL)
	{
		fclose(fpFile);
	}

	AfxMessageBox(m_pOSA->GetLastMessage());
	if(dbwl!=NULL)
	{
		VirtualFree(dbwl,0,MEM_RELEASE);
	}
	if(dbPower!=NULL)
	{
		VirtualFree(dbPower,0,MEM_RELEASE);
	}	
	if(dbGain!=NULL)
	{
		VirtualFree(dbGain,0,MEM_RELEASE);
	}
	if(dbNF!=NULL)
	{
		VirtualFree(dbNF,0,MEM_RELEASE);
	}
	if(dbASE!=NULL)
	{
		VirtualFree(dbASE,0,MEM_RELEASE);
	}	
}

void CTestUDLDlg::OnBtnClose() 
{
	// TODO: Add your control notification handler code here	UpdateData(TRUE);
	m_pPM->CloseDevice(m_nPMChIndex);
}

void CTestUDLDlg::OnBtnPolPolazier() 
{
	// TODO: Add your control notification handler code here
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}

	UpdateData(TRUE);
	m_pPol->SetPolPOSPolarizer(m_nPolChannel,m_fPolAngle);
	AfxMessageBox(m_pPol->GetLastMessage());	
}

void CTestUDLDlg::OnBtnPolPolazier2() 
{
	// TODO: Add your control notification handler code here
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}

	UpdateData(TRUE);
	m_pPol->SetPolPOSHalf(m_nPolChannel,m_fPolAngle);
	AfxMessageBox(m_pPol->GetLastMessage());
}

void CTestUDLDlg::OnBtnPolPolazier3() 
{
	// TODO: Add your control notification handler code here
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}

	UpdateData(TRUE);
	m_pPol->SetPolPOSQuarter(m_nPolChannel,m_fPolAngle);
	AfxMessageBox(m_pOSA->GetLastMessage());
}

void CTestUDLDlg::OnBtnChamberCurrentTemp() 
{
	// TODO: Add your control notification handler code here
	double dbGetTemp;
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}

	UpdateData(TRUE);
	m_pChamber->GetChamberCurrentTemp (m_nChamberChIndex,&dbGetTemp);
	AfxMessageBox(m_pChamber->GetLastMessage());
	m_fChamberTemp = (float)dbGetTemp;
}

void CTestUDLDlg::OnBtnChamberSettep() 
{
	// TODO: Add your control notification handler code here
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}

	UpdateData(TRUE);
	m_pChamber->SetChamberSetPoint (m_nChamberChIndex,m_fChamberTemp);
	AfxMessageBox(m_pChamber->GetLastMessage());	
}

void CTestUDLDlg::OnBtnChamberGetsettemp() 
{
	// TODO: Add your control notification handler code here
	double dbGetTemp;
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}

	UpdateData(TRUE);
	m_pChamber->GetChamberSetPoint (m_nChamberChIndex,&dbGetTemp);
	AfxMessageBox(m_pChamber->GetLastMessage());
	m_fChamberTemp = (float)dbGetTemp;
}

void CTestUDLDlg::OnBTNPOLGetPOLAZIER() 
{
	// TODO: Add your control notification handler code here
		if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}

	UpdateData(TRUE);
	double dbAlphP,dbAlphQ,dbAlphH;
	m_pPol->GetPolCurrentPOSPolarizer(m_nPolChannel,&dbAlphP,&dbAlphQ,&dbAlphH);
	AfxMessageBox(m_pOSA->GetLastMessage());
}

void CTestUDLDlg::OnBtnComtest() 
{
	// TODO: Add your control notification handler code here
	char szBuf[MAX_PATH];
	CString strTemp;
	for(int i=0;i<1000;i++)
	{
		ZeroMemory(szBuf,MAX_PATH);
		sprintf(szBuf,"sch 1 1\r\n");
		//	szBuf[0]=0x69;
		//	szBuf[1]=0x6E;
		//	szBuf[2]=0x66;
		//	szBuf[3]=0x6F;
		//	szBuf[4]=0x0D;
		//	szBuf[5]=0x0A;
		
		HRESULT hr = m_pComDev->WriteBuffer(0,szBuf,strlen(szBuf));
		if (hr ==S_FALSE)
		{
			AfxMessageBox("发送信息错误!");
		}
		//	ZeroMemory(szBuf,MAX_PATH);
		
		BSTR pValue;
		//pValue = strTemp.AllocSysString();
		hr = m_pComDev->ReadBuffer(0,&pValue,1024);
		if (hr ==S_FALSE)
		{
			AfxMessageBox(m_pOSA->GetLastMessage());
			return;
		}
		strTemp.Empty();
		strTemp = pValue;
		//	AfxMessageBox(strTemp);
		SysFreeString(pValue);
		
		
//		ZeroMemory(szBuf,MAX_PATH);
//		sprintf(szBuf,"*IDN?\r\n");	     
//		hr = m_pComDev->WriteBuffer(1,szBuf,strlen(szBuf));
//		if (hr ==S_FALSE)
//		{
//			AfxMessageBox("发送信息错误!");
//		}
//		//	ZeroMemory(szBuf,MAX_PATH);
//		//pValue = strTemp.AllocSysString();
//		hr = m_pComDev->ReadBuffer(1,&pValue,1024);
//		if (hr ==S_FALSE)
//		{
//			AfxMessageBox(m_pOSA->GetLastMessage());
//			return;
//		}
//		_bstr_t b = pValue;
//		char *p = b;
//		strTemp.Empty();
//		strTemp = pValue;
//		AfxMessageBox(strTemp);
//		SysFreeString(pValue);
	}
	
	
}

void CTestUDLDlg::OnBtnPmGetwl() 
{
	// TODO: Add your control notification handler code here
	if (m_pEngine == NULL)
	{
		AfxMessageBox("请先打开设备！");
		return;
	}
	
	UpdateData(TRUE);
	if(m_pPM->GetWavelength(m_nPMChIndex, &m_fPmWav)!=S_OK)
	{
		AfxMessageBox(m_pPM->GetLastMessage());
	}
	CString strValue;
	strValue.Format("%.5f",m_fPmWav);
	GetDlgItem(IDC_BTN_PM_GETWL)->SetWindowText(strValue);
	
}

void CTestUDLDlg::OnBtnPmGetunit() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	long lUnit =-1;
	m_pPM->GetUnit(m_nPMChIndex, &lUnit);
	CString strValue;
	strValue.Format("%ld",lUnit);
	GetDlgItem(IDC_BTN_PM_GETUNIT)->SetWindowText(strValue);
	AfxMessageBox(m_pPM->GetLastMessage());	
}

void CTestUDLDlg::OnBtnPmGetavgtime() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	double dbAvgTime=0;
	m_pPM->GetAverageTime(m_nPMChIndex, &dbAvgTime);
	CString strValue;
	strValue.Format("%.2f",dbAvgTime);
	GetDlgItem(IDC_BTN_PM_GETAVGTIME)->SetWindowText(strValue);
	AfxMessageBox(m_pPM->GetLastMessage());		
}

void CTestUDLDlg::OnBtnClosecom() 
{
	// TODO: Add your control notification handler code here
	HRESULT hr = m_pComDev->CloseSerial(0);
	if (hr ==S_FALSE)
	{
		AfxMessageBox("发送信息错误!");
	}
	AfxMessageBox(m_pComDev->GetLastMessage());
}

void CTestUDLDlg::OnBtnOpencom() 
{
	// TODO: Add your control notification handler code here
	HRESULT hr = m_pComDev->OpenSerial(0);
	if (hr ==S_FALSE)
	{
		AfxMessageBox("发送信息错误!");
	}
	AfxMessageBox(m_pComDev->GetLastMessage());	
}

void CTestUDLDlg::OnBtnPmOffset() 
{
	// TODO: Add your control notification handler code here
	HRESULT hr = m_pPM->SetPMPowerOffset(0,2.0);
	if (hr != S_OK)
	{
		AfxMessageBox("发送信息错误!");
	}
	AfxMessageBox(m_pComDev->GetLastMessage());		
}

void CTestUDLDlg::OnBtnPmMaxmin() 
{
	// TODO: Add your control notification handler code here
	double dbMax,dbMin;
	HRESULT hr = m_pPM->SetPMMaxMinPowerStart(0);
	if (hr ==S_FALSE)
	{
		AfxMessageBox("发送信息错误!");
	}
    for(int i=0;i<50;i++)
	{
		hr = m_pPM->GetPMMaxMinPower(0,&dbMax,&dbMin);
		if (hr ==S_FALSE)
		{
			AfxMessageBox("发送信息错误!");
		}
		Sleep(200);
	}
	hr = m_pPM->SetPMMaxMinPowerStop(0);
	if (hr ==S_FALSE)
	{
		AfxMessageBox("发送信息错误!");
	}
	AfxMessageBox(m_pComDev->GetLastMessage());		
}
