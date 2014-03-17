// Run.cpp : implementation file
//

#include "stdafx.h"
#include "YuanDao.h"
#include "Run.h"
#include "DMC5480.h"

#include "MotionControl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




extern BOOL glb_bServOn;

extern int glb_nSharpen_Time;
extern int glb_nSTime_Interval;
extern int glb_nHSpeed;
extern int glb_nLSpeed;
extern int glb_nIdleSpeed;
extern int glb_nAccSpeed;
extern int glb_nSwitchAngle;
extern int glb_nSwitchLength;
extern int glb_nCutDelay;
extern int glb_nDial;
extern BOOL glb_bDemo;
extern BOOL glb_bPump;

extern BOOL glb_bInit;
extern BOOL glb_bInitFinish;

extern BOOL glb_bRunPre;
extern BOOL glb_bRun;
extern BOOL glb_bRunFinish;

extern int **glb_piArray;
extern int glb_nCount;
extern int glb_i;
extern int glb_iPre;

extern CString glb_pathName;
extern CString glb_strWndTitle;

extern int g_motionCardState;
extern WORD g_Axis[3]; 
extern int g_nNumber[3];  //保存参数值的大小

extern BOOL glb_bContinue;	// 连续插补

extern BOOL glb_bCutStart;	// 图开始标志
extern BOOL glb_bOpenFlag;	// 开口标志
extern BOOL glb_bArcFlag;	// 圆弧标志

extern int glb_nReDistance[3];	// 相对距离
extern int glb_nAngle1;
extern int glb_nAngle2;
extern int glb_nAngle1_Pre;		// 角度1-前值
extern int glb_nAngle2_Pre;		// 角度2-前值

extern int glb_nDistance;
extern int glb_nAngleRun;		// 执行的角度

extern int glb_ReAngle;	// 角度差

extern BOOL glb_bMoveEnable;	//旋转后
extern BOOL glb_bRotateEnable;	//移动后

extern BOOL glb_bCylinderInit;	// 气缸初始化
extern BOOL glb_bHeadToUp;	// 机头准备上升

extern int glb_nPosMax_X;
extern int glb_nPosMax_Y;

/////////////////////////////////////////////////////////////////////////////
// CRun dialog


CRun::CRun(CWnd* pParent /*=NULL*/)
	: CDialog(CRun::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRun)
	m_sPositionC = _T("");
	m_sPositionX = _T("");
	m_sPositionY = _T("");
	//}}AFX_DATA_INIT
}


void CRun::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRun)
	DDX_Control(pDX, IDC_CUT_FILE_NAME, m_eCutFileName);
	DDX_Text(pDX, IDC_POSITIONC, m_sPositionC);
	DDX_Text(pDX, IDC_POSITIONX, m_sPositionX);
	DDX_Text(pDX, IDC_POSITIONY, m_sPositionY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRun, CDialog)
	//{{AFX_MSG_MAP(CRun)
	ON_BN_CLICKED(IDC_ORIGIN, OnOrigin)
	ON_BN_CLICKED(IDC_OPEN_CUT_FILE, OnOpenCutFile)
	ON_BN_CLICKED(IDC_AUTO_RUN, OnAutoRun)
	ON_BN_CLICKED(IDC_EMERGENCYSTOP, OnEmergencystop)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRun message handlers

void CRun::OnOrigin() 
{
	// TODO: Add your control notification handler code here
	glb_bInit = TRUE;
	glb_bInitFinish = FALSE;

	d5480_set_profile(Axis_X,1*fRateX,10*fRateX,glb_nAccSpeed*fRateX,glb_nAccSpeed*fRateX);
	d5480_set_s_profile(Axis_X,1.0);//设定S形截面的特性
	d5480_set_profile(Axis_Y,1*fRateY,50*fRateY,glb_nAccSpeed*fRateY,glb_nAccSpeed*fRateY);
	d5480_set_s_profile(Axis_Y,1.0);//设定S形截面的特性
	d5480_set_profile(Axis_C,1*fRateC,50*fRateC,glb_nAccSpeed*fRateC,glb_nAccSpeed*fRateC);
	d5480_set_s_profile(Axis_Y,1.0);//设定S形截面的特性

	d5480_config_home_mode(Axis_X,2,10*fRateX,3,1);//设置回零方式
	d5480_home_move(Axis_X);//回零动作
	d5480_config_home_mode(Axis_Y,1,50*fRateY,3,1);//设置回零方式
	d5480_home_move(Axis_Y);//回零动作
	d5480_config_home_mode(Axis_C,2,50*fRateC,3,1);//设置回零方式
	d5480_home_move(Axis_C);//回零动作


	//初始化IO
	d5480_write_outbit(0,OutPort_Cutter,!FALSE);
	d5480_write_outbit(0,Cylinder_Knife,!TRUE);
	d5480_write_outbit(0,Cylinder_M,!FALSE);
	d5480_write_outbit(0,Cylinder_A,!FALSE);
	d5480_write_outbit(0,Cylinder_Sharpen,!FALSE);
	//初始化轴
	d5480_emg_stop();
	Sleep(100);

// 	Sleep(100);
// 	BOOL bStatusX = d5480_check_done(Axis_X);
// 	BOOL bStatusY = d5480_check_done(Axis_Y);
// 	BOOL bStatusC = d5480_check_done(Axis_C);
// 	//while ((d5480_check_done(Axis_X)==1) && (d5480_check_done(Axis_Y)==1) && (d5480_check_done(Axis_C)==1))
// 	while ((bStatusX==0)|| (bStatusY==0) || (bStatusC==0))
// 	{
// 		bStatusX = d5480_check_done(Axis_X);
// 		bStatusY = d5480_check_done(Axis_Y);
// 		bStatusC = d5480_check_done(Axis_C);
// 	}
// 
// 	glb_bInit = FALSE;

}

void CRun::OnOpenCutFile() 
{
	// TODO: Add your control notification handler code here
	CString FileFilter="ProgarmList Files(*.plt)|*.plt|All Files(*.*)|*.*||";
	CFileDialog dlg(true,_T("plt"),NULL,OFN_HIDEREADONLY|OFN_FILEMUSTEXIST|OFN_OVERWRITEPROMPT, FileFilter, NULL );	
	int ret=dlg.DoModal();
	if (ret==IDOK)
	{
		if (glb_nCount > 0)	//先释放
		{
			for (int i=0; i<glb_nCount; i++)
			{
				delete[] glb_piArray[i];
			}
			delete[] glb_piArray;
		}

		//get path
		glb_pathName=dlg.GetPathName();	
		//glb_strProgramName = dlg.GetFileName();
		glb_strWndTitle = "Program";
		glb_strWndTitle = glb_strWndTitle + " — " + dlg.GetFileName();
		
		//open file for reading (Exception!)
		CFile file;
		CFileException e;
		if(!file.Open(glb_pathName, CFile::modeRead, &e) ) 
		{
			#ifdef _DEBUG
			afxDump <<"File could not be opened"<<e.m_cause<<"\n";
			#endif
		}        
		CString sAllbuf,sbuf;
		int nLen=file.GetLength();
// 		int nCount=0;
		char *cData;
		cData = new char[nLen];
		file.Read(cData,nLen);
		sAllbuf+= cData;

		glb_nCount = nLen/16;

		glb_piArray = new int*[glb_nCount];
		for (int i=0; i<glb_nCount; i++)
		{
			glb_piArray[i] = new int[2];
		}

		//
		glb_nPosMax_X = 0;
		glb_nPosMax_Y = 0;
		int nPosition[2];
		for (i=0; i<glb_nCount; i++)
		{
			sbuf= sAllbuf.Mid(i*16+2,5);
			nPosition[0] =  _ttoi(sbuf);
			glb_piArray[i][0] = nPosition[0];
			sbuf= sAllbuf.Mid(i*16+8,5);
			nPosition[1] =  _ttoi(sbuf);
			glb_piArray[i][1] = nPosition[1];

			if (glb_nPosMax_X < nPosition[0])
			{
				glb_nPosMax_X = nPosition[0];
			}
			if (glb_nPosMax_Y < nPosition[1])
			{
				glb_nPosMax_Y = nPosition[1];
			}
		}

// 		for (i=0; i<glb_nCount; i++)
// 		{
// 			delete[] glb_piArray[i];
// 		}
// 		delete[] glb_piArray;

		glb_i = 0;	//初始化裁剪位置
		glb_iPre = 0;	//初始化裁剪位置

        delete []cData;
		cData = NULL;
		file.Close();
		
		m_eCutFileName.SetWindowText(glb_pathName);
		SetWindowText(glb_strWndTitle);
	}
	
}

void CRun::OnAutoRun() 
{
	// TODO: Add your control notification handler code here

	if (FALSE == glb_bInitFinish)
	{
		glb_bRun = FALSE;
		//glb_bRunFinish = TRUE;
		AfxMessageBox("未原点复归！");
	} 
	else if (glb_nCount>0)
	{
		//初始化IO
		d5480_write_outbit(0,OutPort_Cutter,!FALSE);
		d5480_write_outbit(0,Cylinder_Knife,!TRUE);
		d5480_write_outbit(0,Cylinder_M,!FALSE);
		d5480_write_outbit(0,Cylinder_A,!FALSE);
		d5480_write_outbit(0,Cylinder_Sharpen,!FALSE);
		//初始化轴
		d5480_emg_stop();
		Sleep(100);
		
		glb_bRunPre = TRUE;
		d5480_write_outbit(0,OutPort_StartLamp,!glb_bRunPre);

		glb_i = 0;	//初始化裁剪位置
		glb_iPre = glb_i;	//初始化裁剪位置
	}
	
}

void CRun::OnEmergencystop() 
{
	// TODO: Add your control notification handler code here
	d5480_write_outbit(0,OutPort_Cutter,!FALSE);
	d5480_write_outbit(0,Cylinder_Knife,!TRUE);
	d5480_write_outbit(0,Cylinder_M,!FALSE);
	d5480_write_outbit(0,Cylinder_A,!FALSE);
	d5480_write_outbit(0,Cylinder_Sharpen,!FALSE);

	d5480_emg_stop();
	glb_bInit = FALSE;
	glb_bRun = FALSE;
	g_motionCardState = MOTION_CARD_STOP;  //停止系统运行			

}

void CRun::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	double dPositionX = d5480_get_position(Axis_X)/100.0;
	double dPositionY = d5480_get_position(Axis_Y)/100.0;
	double dPositionC = d5480_get_position(Axis_C)/100.0;

	m_sPositionX.Format("%.2f",dPositionX);
	m_sPositionY.Format("%.2f",dPositionY);
	m_sPositionC.Format("%.2f",dPositionC);
	//sprintf((char*)m_sPositionX,"%f",dPositionX);
	//sprintf(m_sPositionY,"%f",dPositionY);
	//sprintf(m_sPositionC,"%f",dPositionC);

	GetDlgItem(IDC_POSITIONX)->SetWindowText(m_sPositionX);
	GetDlgItem(IDC_POSITIONY)->SetWindowText(m_sPositionY);
	GetDlgItem(IDC_POSITIONC)->SetWindowText(m_sPositionC);

	//UpdateData(FALSE);
	
	CDialog::OnTimer(nIDEvent);
}

BOOL CRun::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//m_bHeadUp = FALSE;

	m_eCutFileName.SetWindowText(glb_pathName);
	SetWindowText(glb_strWndTitle);

	SetTimer(0,10,NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRun::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(0);
	
	CDialog::OnClose();
}
