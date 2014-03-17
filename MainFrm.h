// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_MAINFRM_H__153270D1_E717_4365_9605_CA0A130A8C3A__INCLUDED_)
#define AFX_MAINFRM_H__153270D1_E717_4365_9605_CA0A130A8C3A__INCLUDED_

#include "Alarm.h"


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	BOOL m_bDialConfirm;
	BOOL m_bHeadRotation;
	BOOL m_bMCylinder;
	BOOL m_bACylinder;
	BOOL m_bKnifeCylinder;
	BOOL m_bCutterRun;
	BOOL m_bSharpen;
	
	BOOL m_bPCylinder;
	BOOL m_bPMotor;

	CAlarm m_CAlarm;

	BOOL m_bStartBtn;
// Operations
public:
	void Reset(void);
	void Servo(void);
	void Init(void);
	void EmgOP(void);
	void AlarmOP(void);

	void Manual(void);
	void Dial(void);

	void AutoRun(void);
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__153270D1_E717_4365_9605_CA0A130A8C3A__INCLUDED_)
