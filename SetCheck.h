#if !defined(AFX_SETCHECK_H__B0FD6486_ACE2_445A_B333_34EFA054D558__INCLUDED_)
#define AFX_SETCHECK_H__B0FD6486_ACE2_445A_B333_34EFA054D558__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetCheck.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetCheck dialog

class CSetCheck : public CDialog
{
// Construction
public:
	CSetCheck(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetCheck)
	enum { IDD = IDD_SET_CHECK };
	CButton	m_btnStartLamp;
	CButton	m_btnOriginLamp;
	CButton	m_btnEmergencyLamp;
	CButton	m_btnSharpen;
	CButton	m_btnCutterRun;
	CButton	m_btnKnifeCylinder;
	CButton	m_btnACylinder;
	CButton	m_btnMCylinder;
	CButton	m_btnHeadRotation;
	CSpinButtonCtrl	m_DialSpin;
	int		m_nSharpen_Time;
	int		m_nSTime_Interval;
	int		m_nHSpeed;
	int		m_nLSpeed;
	int		m_nIdleSpeed;
	int		m_nAccSpeed;
	int		m_nSwitchAngle;
	int		m_nSwitchLength;
	int		m_nCutDelay;
	int		m_nDial;
	BOOL	m_bDemo;
	BOOL	m_bPump;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetCheck)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL m_bHeadRotation;
	BOOL m_bMCylinder;
	BOOL m_bACylinder;
	BOOL m_bKnifeCylinder;
	BOOL m_bCutterRun;
	BOOL m_bSharpen;
	BOOL m_bEmergencyLamp;
	BOOL m_bOriginLamp;
	BOOL m_bStartLamp;

	BOOL m_bPCylinder;
	BOOL m_bPMotor;

	int m_nAxis;
	BOOL m_bLogic;
	long m_nSpeed;
	double	m_nAcc;
	double	m_nDec;
	//double	m_nSPara;


	// Generated message map functions
	//{{AFX_MSG(CSetCheck)
	virtual BOOL OnInitDialog();
	afx_msg void OnMCylinder();
	afx_msg void OnSharpen();
	afx_msg void OnHeadRotation();
	afx_msg void OnACylinder();
	afx_msg void OnKnifeCylinder();
	afx_msg void OnCutterRun();
	afx_msg void OnEmergencyLamp();
	afx_msg void OnOriginLamp();
	afx_msg void OnStartLamp();
	afx_msg void OnDialConfirm();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETCHECK_H__B0FD6486_ACE2_445A_B333_34EFA054D558__INCLUDED_)
