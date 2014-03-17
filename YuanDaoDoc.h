// YuanDaoDoc.h : interface of the CYuanDaoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_YUANDAODOC_H__D63D55D6_D147_4C66_BDE0_542CFD8DA4D8__INCLUDED_)
#define AFX_YUANDAODOC_H__D63D55D6_D147_4C66_BDE0_542CFD8DA4D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CYuanDaoDoc : public CDocument
{
protected: // create from serialization only
	CYuanDaoDoc();
	DECLARE_DYNCREATE(CYuanDaoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CYuanDaoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CYuanDaoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CYuanDaoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YUANDAODOC_H__D63D55D6_D147_4C66_BDE0_542CFD8DA4D8__INCLUDED_)
