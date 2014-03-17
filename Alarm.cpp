// Alarm.cpp : implementation file
//

#include "stdafx.h"
#include "YuanDao.h"
#include "Alarm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern BOOL glb_bAlarm;
extern BOOL glb_bAlarm_SX;
extern BOOL glb_bAlarm_SY;
extern BOOL glb_bAlarm_SC;

extern BOOL glb_bDataErr;

/////////////////////////////////////////////////////////////////////////////
// CAlarm dialog


CAlarm::CAlarm(CWnd* pParent /*=NULL*/)
	: CDialog(CAlarm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAlarm)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAlarm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAlarm)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAlarm, CDialog)
	//{{AFX_MSG_MAP(CAlarm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlarm message handlers


BOOL CAlarm::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if (glb_bAlarm_SX)
	{
		GetDlgItem(IDC_ALARM_V)->SetWindowText("X轴伺服报警！");
	} 
	else if (glb_bAlarm_SY)
	{
		GetDlgItem(IDC_ALARM_V)->SetWindowText("Y轴伺服报警！");
	} 
	else if (glb_bAlarm_SC)
	{
		GetDlgItem(IDC_ALARM_V)->SetWindowText("C轴伺服报警！");
	} 
	else if (glb_bDataErr)
	{
		GetDlgItem(IDC_ALARM_V)->SetWindowText("数据超限！");
	} 

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CAlarm::OnOK() 
{
	// TODO: Add extra validation here
	glb_bAlarm = FALSE;

	glb_bAlarm_SX = FALSE;
	glb_bAlarm_SY = FALSE;
	glb_bAlarm_SC = FALSE;
	glb_bDataErr = FALSE;
	
	CDialog::OnOK();
}
