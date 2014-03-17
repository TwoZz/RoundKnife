#if !defined(AFX_ALARM_H__269EB578_3DE0_448F_9722_BD7F23CFC248__INCLUDED_)
#define AFX_ALARM_H__269EB578_3DE0_448F_9722_BD7F23CFC248__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Alarm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAlarm dialog

class CAlarm : public CDialog
{
// Construction
public:
	CAlarm(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAlarm)
	enum { IDD = IDD_ALARM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlarm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAlarm)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALARM_H__269EB578_3DE0_448F_9722_BD7F23CFC248__INCLUDED_)
