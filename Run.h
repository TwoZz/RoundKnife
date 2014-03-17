#if !defined(AFX_RUN_H__8ACCC90F_24EA_48CA_9CDD_3F51A90D9543__INCLUDED_)
#define AFX_RUN_H__8ACCC90F_24EA_48CA_9CDD_3F51A90D9543__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Run.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRun dialog

class CRun : public CDialog
{
// Construction
public:
	CRun(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRun)
	enum { IDD = IDD_RUN };
	CEdit	m_eCutFileName;
	CString	m_sPositionC;
	CString	m_sPositionX;
	CString	m_sPositionY;
	//}}AFX_DATA

	//BOOL m_bHeadUp;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRun)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRun)
	afx_msg void OnOrigin();
	afx_msg void OnOpenCutFile();
	afx_msg void OnAutoRun();
	afx_msg void OnEmergencystop();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RUN_H__8ACCC90F_24EA_48CA_9CDD_3F51A90D9543__INCLUDED_)
