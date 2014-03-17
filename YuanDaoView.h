// YuanDaoView.h : interface of the CYuanDaoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_YUANDAOVIEW_H__2264198E_46C2_42E0_9A79_89E692283950__INCLUDED_)
#define AFX_YUANDAOVIEW_H__2264198E_46C2_42E0_9A79_89E692283950__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CYuanDaoView : public CView
{
protected: // create from serialization only
	CYuanDaoView();
	DECLARE_DYNCREATE(CYuanDaoView)

// Attributes
public:
	CYuanDaoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CYuanDaoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CYuanDaoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CYuanDaoView)
	afx_msg void OnSetCheck();
	afx_msg void OnRun();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in YuanDaoView.cpp
inline CYuanDaoDoc* CYuanDaoView::GetDocument()
   { return (CYuanDaoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YUANDAOVIEW_H__2264198E_46C2_42E0_9A79_89E692283950__INCLUDED_)
