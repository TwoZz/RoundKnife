// YuanDaoDoc.cpp : implementation of the CYuanDaoDoc class
//

#include "stdafx.h"
#include "YuanDao.h"

#include "YuanDaoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CYuanDaoDoc

IMPLEMENT_DYNCREATE(CYuanDaoDoc, CDocument)

BEGIN_MESSAGE_MAP(CYuanDaoDoc, CDocument)
	//{{AFX_MSG_MAP(CYuanDaoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CYuanDaoDoc construction/destruction

CYuanDaoDoc::CYuanDaoDoc()
{
	// TODO: add one-time construction code here

}

CYuanDaoDoc::~CYuanDaoDoc()
{
}

BOOL CYuanDaoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CYuanDaoDoc serialization

void CYuanDaoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CYuanDaoDoc diagnostics

#ifdef _DEBUG
void CYuanDaoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CYuanDaoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CYuanDaoDoc commands
