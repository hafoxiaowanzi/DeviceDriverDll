// TestUDLDlg.h : header file
//

#if !defined(AFX_TESTUDLDLG_H__B5952AE9_E7D5_456F_8F95_0F020C8D6560__INCLUDED_)
#define AFX_TESTUDLDLG_H__B5952AE9_E7D5_456F_8F95_0F020C8D6560__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////
// CTestUDLDlg dialog

class CTestUDLDlg : public CDialog
{
// Construction
public:
	CTestUDLDlg(CWnd* pParent = NULL);	// standard constructor

	UDLSERVERLib::IEngineMgrPtr m_pEngine;
	
//	IEngineMgr m_pEngine;
	UDLSERVERLib::IITLSInterfacePtr m_pTLS;
	UDLSERVERLib::IIPMInterfacePtr  m_pPM;
	UDLSERVERLib::IIVOAInterfacePtr m_pVOA;
	UDLSERVERLib::IIOSAInterfacePtr m_pOSA;
	UDLSERVERLib::IIPolInterfacePtr   m_pPol;
	UDLSERVERLib::IScanInterfacePtr    m_pScan;
	UDLSERVERLib::IChamberInterfacePtr m_pChamber;
	UDLSERVERLib::IIComDevInterfacePtr m_pComDev;

// Dialog Data
	//{{AFX_DATA(CTestUDLDlg)
	enum { IDD = IDD_TESTUDL_DIALOG };
	int		m_nTLSChIndex;
	CString	m_strValue;
	int		m_nPMChIndex;
	CString	m_strPMValue;
	int		m_nVOAChIndex;
	CString	m_strVOAValue;
	double	m_fTlsWav;
	double	m_fTlsPower;
	int		m_nTlsUnit;
	CString	m_strTlsMsg;
	BOOL	m_bTlsOpen;
	BOOL	m_bTlsOpenCOH;
	double	m_fPmWav;
	int		m_nPMUnit;
	int		m_nPmRange;
	double	m_fPmTime;
	double	m_fPmPower;
	CString	m_strPmMsg;
	CString	m_strVOAMsg;
	BOOL	m_bVoaEnable;
	int		m_nOSAChIndex;
	long	m_nOSAChCount;
	double	m_fOSAGain;
	CString	m_strOSAMsg;
	double	m_fOSAOffset;
	double	m_fOSAPower;
	double	m_fOSAWav;
	double	m_fOsaSNR;
	double	m_fOsaRBW;
	double	m_fOSAWavEnd;
	long	m_nOSAPointCount;
	BOOL	m_bOurZoom;
	double	m_fOSASrcOffset;
	int		m_nPolChannel;
	float	m_fPolAngle;
	int		m_nChamberChIndex;
	float	m_fChamberTemp;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestUDLDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestUDLDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnOpenDevice();
	afx_msg void OnClose();
	afx_msg void OnCancelMode();
	afx_msg void OnBtnReadTlsWl();
	afx_msg void OnBtnOpen();
	afx_msg void OnBtnSettingWl();
	afx_msg void OnBtnReadPm();
	virtual void OnOK();
	afx_msg void OnBtnTlsPower();
	afx_msg void OnBtnTlsEnable();
	afx_msg void OnBtnTlsUnit();
	afx_msg void OnBtnTlsParameters();
	afx_msg void OnBtnPmWl();
	afx_msg void OnBtnPmUnit();
	afx_msg void OnBtnPmRange();
	afx_msg void OnBtnPmAvgtime();
	afx_msg void OnBtnPmParamter();
	afx_msg void OnBtnVoaWl();
	afx_msg void OnBtnVoaAtten();
	afx_msg void OnBtnVoaReadWl();
	afx_msg void OnBtnVoaReadAtten();
	afx_msg void OnBtnTlsClose();
	afx_msg void OnBtnTlsMsg();
	afx_msg void OnCheckOpen();
	afx_msg void OnCheckOpencoh();
	afx_msg void OnBtnPmRange2();
	afx_msg void OnBtnPmZero();
	afx_msg void OnBtnPmMsg();
	afx_msg void OnBtnVoaOffset();
	afx_msg void OnBtnVoaClose();
	afx_msg void OnBtnVoaReset();
	afx_msg void OnBtnVoaState();
	afx_msg void OnBtnVoaMsg();
	afx_msg void OnCheckVoaEnable();
	afx_msg void OnBtnOsaSetrbw();
	afx_msg void OnBtnOsaGetrbw();
	afx_msg void OnBtnOsaClose();
	afx_msg void OnBtnOsaReset();
	afx_msg void OnBtnOsaInit();
	afx_msg void OnBtnOsaLcmode();
	afx_msg void OnBtnOsaScan();
	afx_msg void OnBtnOsaScanzoom();
	afx_msg void OnBtnOsaChcount();
	afx_msg void OnBtnOsaWav();
	afx_msg void OnBtnOsaGain();
	afx_msg void OnBtnOsaPower();
	afx_msg void OnBtnOsaSetoffset();
	afx_msg void OnBtnOsaSnr();
	afx_msg void OnBtnOsaGetoffset();
	afx_msg void OnBtnOsaZoomResult();
	afx_msg void OnBtnOsaMsg();
	afx_msg void OnBtnOsaSave();
	afx_msg void OnBtnOsaGetdata();
	afx_msg void OnBtnOsaGetdataonce();
	afx_msg void OnBtnOsaNf();
	afx_msg void OnBtnOsaRun();
	afx_msg void OnBtnOsaInitsinglescan();
	afx_msg void OnBtnOsaScanResult();
	afx_msg void OnBtnClose();
	afx_msg void OnBtnPolPolazier();
	afx_msg void OnBtnPolPolazier2();
	afx_msg void OnBtnPolPolazier3();
	afx_msg void OnBtnChamberCurrentTemp();
	afx_msg void OnBtnChamberSettep();
	afx_msg void OnBtnChamberGetsettemp();
	afx_msg void OnBTNPOLGetPOLAZIER();
	afx_msg void OnBtnComtest();
	afx_msg void OnBtnPmGetwl();
	afx_msg void OnBtnPmGetunit();
	afx_msg void OnBtnPmGetavgtime();
	afx_msg void OnBtnClosecom();
	afx_msg void OnBtnOpencom();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTUDLDLG_H__B5952AE9_E7D5_456F_8F95_0F020C8D6560__INCLUDED_)
