// YuanDaoView.cpp : implementation of the CYuanDaoView class
//

#include "stdafx.h"
#include "YuanDao.h"

#include "YuanDaoDoc.h"
#include "YuanDaoView.h"


#include "SetCheck.h"
#include "Run.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CYuanDaoView

IMPLEMENT_DYNCREATE(CYuanDaoView, CView)

BEGIN_MESSAGE_MAP(CYuanDaoView, CView)
	//{{AFX_MSG_MAP(CYuanDaoView)
	ON_COMMAND(ID_SET_CHECK, OnSetCheck)
	ON_COMMAND(ID_RUN, OnRun)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CYuanDaoView construction/destruction

CYuanDaoView::CYuanDaoView()
{
	// TODO: add construction code here

}

CYuanDaoView::~CYuanDaoView()
{
}

BOOL CYuanDaoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CYuanDaoView drawing

void CYuanDaoView::OnDraw(CDC* pDC)
{
	CYuanDaoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CYuanDaoView printing

BOOL CYuanDaoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CYuanDaoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CYuanDaoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CYuanDaoView diagnostics

#ifdef _DEBUG
void CYuanDaoView::AssertValid() const
{
	CView::AssertValid();
}

void CYuanDaoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CYuanDaoDoc* CYuanDaoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CYuanDaoDoc)));
	return (CYuanDaoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CYuanDaoView message handlers

void CYuanDaoView::OnSetCheck() 
{
	// TODO: Add your command handler code here
	CSetCheck SetCheck;
	SetCheck.DoModal();
}

void CYuanDaoView::OnRun() 
{
	// TODO: Add your command handler code here
	CRun Run;
	Run.DoModal();
}


