// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "YuanDao.h"
#include "MotionControl.h"
#include "DMC5480.h"

#include <math.h>  

#include "Alarm.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern BOOL glb_bAlarm;
extern BOOL glb_bAlarm_SX;
extern BOOL glb_bAlarm_SY;
extern BOOL glb_bAlarm_SC;

extern BOOL glb_bEmgStatus;	// 急停状态


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
extern BOOL glb_bPause;

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
extern int glb_nStart_X;
extern int glb_nStart_Y;

extern BOOL glb_bDataErr;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	//////////////////////////////////////////////////////////////////////////
	//初始化IO
	d5480_write_outbit(0,OutPort_Cutter,!FALSE);
	d5480_write_outbit(0,Cylinder_Knife,!TRUE);
	d5480_write_outbit(0,Cylinder_M,!FALSE);
	d5480_write_outbit(0,Cylinder_A,!FALSE);
	d5480_write_outbit(0,Cylinder_Sharpen,!FALSE);

	d5480_write_outbit(0,OutPort_StartLamp,!FALSE);
	d5480_write_outbit(0,OutPort_OriginLamp,!FALSE);
	d5480_write_outbit(0,OutPort_Alarm,!FALSE);
	d5480_write_outbit(0,OutPort_PowerLamp,!FALSE);
	d5480_write_outbit(0,OutPort_PumpLamp,!FALSE);
	d5480_write_outbit(0,OutPort_EMGLamp,!FALSE);

	

	//设定脉冲模式及逻辑方向
	d5480_set_pulse_outmode( Axis_X, 5);
	//Sleep(50);
	d5480_set_pulse_outmode( Axis_Y, 5);
	//Sleep(50);
	d5480_set_pulse_outmode( Axis_C, 5);

	d5480_config_EL_PIN(Axis_X, 1, 0);
	d5480_config_EL_PIN(Axis_Y, 1, 0);
	d5480_config_EL_PIN(Axis_C, 0, 0);

	d5480_config_ALM_PIN(Axis_X,1, 1, 0);
	d5480_config_ALM_PIN(Axis_Y,1, 1, 0);
	d5480_config_ALM_PIN(Axis_C,1, 1, 0);

	///////
	SetTimer(0,10,NULL);
	m_bDialConfirm = FALSE;
	m_bHeadRotation = FALSE;
	m_bMCylinder = FALSE;
	m_bACylinder = FALSE;
	m_bKnifeCylinder = FALSE;
	m_bCutterRun = FALSE;
	m_bSharpen = FALSE;

	m_bPCylinder = FALSE;
	m_bPMotor = FALSE;

	m_bStartBtn = FALSE;

	glb_nPosMax_X = 0;
	glb_nPosMax_Y = 0;

	//////////////////////////////////////////////////////////////////////////

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::Reset(void)
{
	//再启动
	if ((!TRUE == d5480_read_inbit(0,InPort_Reset)) && (TRUE == glb_bAlarm))
	{
		glb_bAlarm = FALSE;

		d5480_write_outbit(0,OutPort_ERC_X,!TRUE);
		d5480_write_outbit(0,OutPort_ERC_Y,!TRUE);
		d5480_write_outbit(0,OutPort_ERC_C,!TRUE);
		Sleep(100);
		d5480_write_outbit(0,OutPort_ERC_X,!FALSE);
		d5480_write_outbit(0,OutPort_ERC_Y,!FALSE);
		d5480_write_outbit(0,OutPort_ERC_C,!FALSE);
		
		glb_bRunPre = FALSE;
		glb_bRun = FALSE;
		glb_bRunFinish = FALSE;
		glb_bPause = FALSE;
	}
}

void CMainFrame::Servo(void)
{
	//Servo On 
	if ((!TRUE == d5480_read_inbit(0,InPort_PowerOn)) && (FALSE == glb_bServOn))
	{
		d5480_write_SEVON_PIN(Axis_X,0);
		d5480_write_SEVON_PIN(Axis_Y,0);
		d5480_write_SEVON_PIN(Axis_C,0);
		
		d5480_write_outbit(0,OutPort_PowerLamp,FALSE);
		glb_bServOn = TRUE;
	}
	else if (((BOOL)(!FALSE) == d5480_read_inbit(0,InPort_PowerOn)) && (TRUE == glb_bServOn))
	{
		d5480_write_SEVON_PIN(Axis_X,1);
		d5480_write_SEVON_PIN(Axis_Y,1);
		d5480_write_SEVON_PIN(Axis_C,1);
		
		d5480_write_outbit(0,OutPort_PowerLamp,TRUE);
		glb_bServOn = FALSE;
		d5480_write_outbit(0,OutPort_OriginLamp,!FALSE);
		glb_bInitFinish = FALSE;
	}
}

void CMainFrame::Init(void)
{
	//原点复归
	if ((TRUE == glb_bServOn) && (FALSE == glb_bInit) && ((!TRUE) == d5480_read_inbit(0,InPort_Shift)) && ((!TRUE) == d5480_read_inbit(0,InPort_Start)))
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

		//////////////////////////////////////////////////////////////////////////
		glb_bInit = TRUE;
		glb_bInitFinish = FALSE;
		d5480_write_outbit(0,OutPort_OriginLamp,!FALSE);
		
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
	}
	
	
	// 原点复归完成后状态初始化
	if ((TRUE == glb_bInit) && (d5480_check_done(Axis_X)==1) && (d5480_check_done(Axis_Y)==1) && (d5480_check_done(Axis_C)==1))
	{
		glb_bInit = FALSE;
		d5480_set_position(Axis_X,0);
		d5480_set_position(Axis_Y,0);
		d5480_set_position(Axis_C,0);
		glb_bInitFinish = TRUE;
		d5480_write_outbit(0,OutPort_OriginLamp,!TRUE);

		glb_bRunPre = FALSE;
		glb_bRun = FALSE;
		glb_bRunFinish = FALSE;
		glb_bPause = FALSE;

		glb_i = 0;	//初始化裁剪位置
		glb_iPre = glb_i;	//初始化裁剪位置
	}	
}

void CMainFrame::EmgOP(void)
{
	//急停处理
	if ((FALSE == glb_bEmgStatus) && ((TRUE == d5480_read_inbit(0,InPort_PowerOn)))) // 急停
	{
		glb_bEmgStatus = TRUE;
		
		d5480_write_outbit(0,OutPort_Cutter,!FALSE);
		d5480_write_outbit(0,Cylinder_Knife,!TRUE);
		d5480_write_outbit(0,Cylinder_M,!FALSE);
		d5480_write_outbit(0,Cylinder_A,!FALSE);
		d5480_write_outbit(0,Cylinder_Sharpen,!FALSE);
		
		if (glb_bRun)
		{
			glb_bPause = TRUE;
		}

		d5480_emg_stop();
		glb_bInit = FALSE;
		glb_bRun = FALSE;
		g_motionCardState = MOTION_CARD_STOP;  //停止系统运行			
		
	}
	if ((TRUE == glb_bEmgStatus) && ((FALSE == d5480_read_inbit(0,InPort_PowerOn)))) // 取消急停
	{
		glb_bEmgStatus = FALSE;

		if (glb_bPause)
		{
			glb_bRunPre = TRUE;
			d5480_write_outbit(0,OutPort_StartLamp,!glb_bRunPre);
		}
	}
}

void CMainFrame::AlarmOP(void)
{
	glb_bAlarm_SX = (BOOL)d5480_read_inbit(0,InPort_ALM_X);
	glb_bAlarm_SY = (BOOL)d5480_read_inbit(0,InPort_ALM_Y);
	glb_bAlarm_SC = (BOOL)d5480_read_inbit(0,InPort_ALM_C);

	if ((FALSE==glb_bAlarm) && (glb_bAlarm_SX||glb_bAlarm_SY||glb_bAlarm_SC||glb_bDataErr))
	{
		glb_bAlarm = TRUE;

		m_CAlarm.DoModal();
	}

// 	if (nAlarmX)
// 	{
// 		//AfxMessageBox("X轴伺服报警！");
// 	} 
// 	else if (nAlarmY)
// 	{
// 		//AfxMessageBox("Y轴伺服报警！");
// 	} 
// 	else if (nAlarmC)
// 	{
// 		//AfxMessageBox("C轴伺服报警！");
// 	} 

}

void CMainFrame::Dial(void)
{
	// 拨码处理
	if ((!TRUE) == d5480_read_inbit(0,InPort_CodeConfirm))
	{
		if(FALSE == m_bDialConfirm)
		{
			m_bDialConfirm = TRUE;
			int nDialP0,nDialP1,nDialP2,nDialP3,nDial;
			nDialP0 = !d5480_read_inbit(0,InPort_Code1);
			nDialP1 = !d5480_read_inbit(0,InPort_Code2);
			nDialP2 = !d5480_read_inbit(0,InPort_Code3);
			nDialP3 = !d5480_read_inbit(0,InPort_Code4);
			nDial = nDialP3*8 + nDialP2*4 + nDialP1*2 + nDialP0;
			switch (nDial)
			{
			case 0:
				break;
			case 1:
				if (m_bHeadRotation)
				{
					m_bHeadRotation = FALSE;
					
					d5480_imd_stop(Axis_C);
					//d5480_decel_stop(m_nAxis,m_nDec);		
					//d5480_emg_stop();	//全部急停
					
				}
				else
				{
					m_bHeadRotation = TRUE;
					
					if ((d5480_check_done( Axis_C ))&0x02 == 1) //已经在运动中
						return; 
					
					//设定脉冲模式及逻辑方向（此处脉冲模式固定为P+D方向：脉冲+方向）	
					//d5480_set_pulse_outmode( m_nAxis, 5);
					
					//设定T形截面的特性
					d5480_set_profile(Axis_C,0,(long)(36*fRateC),glb_nAccSpeed*fRateC,glb_nAccSpeed*fRateC);
					d5480_set_s_profile(Axis_C,1.0);//设定S形截面的特性
					//int	dir = 1;//0:负方向	1：正方向
					d5480_vmove( Axis_C, 1,(long)(36*fRateC));	
				}
				break;
			case 2:
				if (m_bMCylinder)
				{
					m_bMCylinder = FALSE;
					d5480_write_outbit(0,Cylinder_M,!m_bMCylinder);
				}
				else
				{
					m_bMCylinder = TRUE;
					d5480_write_outbit(0,Cylinder_M,!m_bMCylinder);
				}
				break;
			case 3:
				if (m_bACylinder)
				{
					m_bACylinder = FALSE;
					d5480_write_outbit(0,Cylinder_A,!m_bACylinder);
				} 
				else
				{
					m_bACylinder = TRUE;
					d5480_write_outbit(0,Cylinder_A,!m_bACylinder);
				}
				break;
			case 4:
				if (m_bKnifeCylinder)
				{
					m_bKnifeCylinder = FALSE;
					d5480_write_outbit(0,Cylinder_Knife,!m_bKnifeCylinder);
				} 
				else
				{
					m_bKnifeCylinder = TRUE;
					d5480_write_outbit(0,Cylinder_Knife,!m_bKnifeCylinder);
				}
				break;
			case 5:
				if (m_bCutterRun)
				{
					m_bCutterRun = FALSE;
					d5480_write_outbit(0,OutPort_Cutter,!m_bCutterRun);
				} 
				else
				{
					m_bCutterRun = TRUE;
					d5480_write_outbit(0,OutPort_Cutter,!m_bCutterRun);
				}
				break;
			case 6:
				if (m_bSharpen)
				{
					m_bSharpen = FALSE;
					d5480_write_outbit(0,Cylinder_Knife,0);
					d5480_write_outbit(0,OutPort_Cutter,!m_bSharpen);
					d5480_write_outbit(0,Cylinder_Sharpen,!m_bSharpen);
				} 
				else
				{
					m_bSharpen = TRUE;
					d5480_write_outbit(0,Cylinder_Knife,0);
					d5480_write_outbit(0,OutPort_Cutter,!m_bSharpen);
					d5480_write_outbit(0,Cylinder_Sharpen,!m_bSharpen);
				}
				break;
			case 7:
				if (m_bPCylinder)
				{
					m_bPCylinder = FALSE;
					d5480_write_outbit(0,OutPort_PCylinder,!m_bPCylinder);
				} 
				else
				{
					m_bPCylinder = TRUE;
					d5480_write_outbit(0,OutPort_PCylinder,!m_bPCylinder);
				}
				break;
			case 8:
				if (m_bPMotor)
				{
					m_bPMotor = FALSE;
					d5480_write_outbit(0,OutPort_PMotor,!m_bPMotor);
				} 
				else
				{
					m_bPMotor = TRUE;
					d5480_write_outbit(0,OutPort_PMotor,!m_bPMotor);
				}
				break;
			case 9:
				if ((!m_bPCylinder) && (!m_bPMotor))
				{
					m_bPCylinder = TRUE;
					d5480_write_outbit(0,OutPort_PCylinder,!m_bPCylinder);
					m_bPMotor = TRUE;
					d5480_write_outbit(0,OutPort_PMotor,!m_bPMotor);
					Sleep(PumpTime);
					m_bPCylinder = FALSE;
					d5480_write_outbit(0,OutPort_PCylinder,!m_bPCylinder);
					m_bPMotor = FALSE;
					d5480_write_outbit(0,OutPort_PMotor,!m_bPMotor);
				} 
				break;
			default:
				break;
			}
		}
	}
	else
	{
		m_bDialConfirm = FALSE;
	}
}

void CMainFrame::Manual(void)
{
	//方向键功能
	//X
	if ((FALSE == d5480_read_inbit(0,InPort_XP)))	//X+
	{
		if ((FALSE == d5480_read_inbit(0,InPort_Shift)))
		{
			//if (1 == d5480_check_done(Axis_X))
			{
				d5480_set_profile(Axis_X,5*fRateX,glb_nIdleSpeed*fRateX,glb_nAccSpeed*fRateX,glb_nAccSpeed*fRateX);
				d5480_set_s_profile(Axis_X,1.0);//设定S形截面的特性
				d5480_vmove(Axis_X, 1, glb_nIdleSpeed*fRateX);
			}
		} 
		else
		{
			//if (1 == d5480_check_done(Axis_X))
			{
				d5480_set_profile(Axis_X,1*fRateX,5*fRateX,glb_nAccSpeed*fRateX,glb_nAccSpeed*fRateX);
				d5480_set_s_profile(Axis_X,1.0);//设定S形截面的特性
				d5480_vmove(Axis_X, 1, 5*fRateX);
			}
		}
	}
	else if ((FALSE == d5480_read_inbit(0,InPort_XN)))	//X-
	{
		if ((FALSE == d5480_read_inbit(0,InPort_Shift)))
		{
			//if (1 == d5480_check_done(Axis_X))
			{
				d5480_set_profile(Axis_X,5*fRateX,glb_nIdleSpeed*fRateX,glb_nAccSpeed*fRateX,glb_nAccSpeed*fRateX);
				d5480_set_s_profile(Axis_X,1.0);//设定S形截面的特性
				d5480_vmove(Axis_X, 0, glb_nIdleSpeed*fRateX);
			}
		} 
		else
		{
			//if (1 == d5480_check_done(Axis_X))
			{
				d5480_set_profile(Axis_X,1*fRateX,5*fRateX,glb_nAccSpeed*fRateX,glb_nAccSpeed*fRateX);
				d5480_set_s_profile(Axis_X,1.0);//设定S形截面的特性
				d5480_vmove(Axis_X, 0, 5*fRateX);
			}
		}
	}
	else if((TRUE != glb_bInit) && (TRUE != glb_bRun)) //if(0 == d5480_check_done(Axis_X))
	{
		d5480_decel_stop(Axis_X,glb_nAccSpeed*fRateX);
		//d5480_imd_stop(Axis_X);
	}
	
	//Y
	if ((FALSE == d5480_read_inbit(0,InPort_YP)))	//Y+
	{
		if ((FALSE == d5480_read_inbit(0,InPort_Shift)))
		{
			//if (1 == d5480_check_done(Axis_Y))
			{
				d5480_set_profile(Axis_Y,5*fRateY,glb_nIdleSpeed*fRateY,glb_nAccSpeed*fRateY,glb_nAccSpeed*fRateY);
				d5480_set_s_profile(Axis_Y,1.0);//设定S形截面的特性
				d5480_vmove(Axis_Y, 1, glb_nIdleSpeed*fRateY);
			}
		} 
		else
		{
			//if (1 == d5480_check_done(Axis_Y))
			{
				d5480_set_profile(Axis_Y,1*fRateY,5*fRateY,glb_nAccSpeed*fRateY,glb_nAccSpeed*fRateY);
				d5480_set_s_profile(Axis_Y,1.0);//设定S形截面的特性
				d5480_vmove(Axis_Y, 1, 5*fRateY);
			}
		}
	}
	else if ((FALSE == d5480_read_inbit(0,InPort_YN)))	//Y-
	{
		if ((FALSE == d5480_read_inbit(0,InPort_Shift)))
		{
			//if (1 == d5480_check_done(Axis_Y))
			{
				d5480_set_profile(Axis_Y,5*fRateY,glb_nIdleSpeed*fRateY,glb_nAccSpeed*fRateY,glb_nAccSpeed*fRateY);
				d5480_set_s_profile(Axis_Y,1.0);//设定S形截面的特性
				d5480_vmove(Axis_Y, 0, glb_nIdleSpeed*fRateY);
			}
		} 
		else
		{
			//if (1 == d5480_check_done(Axis_Y))
			{
				d5480_set_profile(Axis_Y,1*fRateY,5*fRateY,glb_nAccSpeed*fRateY,glb_nAccSpeed*fRateY);
				d5480_set_s_profile(Axis_Y,1.0);//设定S形截面的特性
				d5480_vmove(Axis_Y, 0, 5*fRateY);
			}
		}
	}
	else if((TRUE != glb_bInit) && (TRUE != glb_bRun))//if(0 == d5480_check_done(Axis_Y))
	{
		d5480_decel_stop(Axis_Y,glb_nAccSpeed*fRateY);
		//d5480_imd_stop(Axis_Y);
	}
}

void CMainFrame::AutoRun(void)
{
	//启动前准备
	if (((!TRUE) == d5480_read_inbit(0,InPort_Start)) && ((!TRUE) != d5480_read_inbit(0,InPort_Shift)))
	{
		if (FALSE == m_bStartBtn)	// 考虑运动范围确认，来回一次
		{
			m_bStartBtn = TRUE;

			if (glb_bRun)	// 运动中暂停
			{
				d5480_write_outbit(0,OutPort_Cutter,!FALSE);
				d5480_write_outbit(0,Cylinder_Knife,!TRUE);
				d5480_write_outbit(0,Cylinder_M,!FALSE);
				d5480_write_outbit(0,Cylinder_A,!FALSE);
				d5480_write_outbit(0,Cylinder_Sharpen,!FALSE);

				d5480_emg_stop();
				//glb_bInit = FALSE;
				glb_bRun = FALSE;
				g_motionCardState = MOTION_CARD_STOP;  //停止系统运行			

				glb_bPause = TRUE;

				glb_bRunPre = TRUE;
				d5480_write_outbit(0,OutPort_StartLamp,!glb_bRunPre);
			} 
			else
			{
				if (glb_bPause)	//暂停后重启
				{
					//glb_bPause = FALSE;

					glb_bRunPre = FALSE;
					d5480_write_outbit(0,OutPort_StartLamp,!glb_bRunPre);

					//////////////////////////////////////////////////////////////////////////
					if (glb_i>2)
					{
 						glb_i = glb_i-2;

						//if ((glb_piArray[glb_i-1][0] != glb_piArray[glb_i][0]) || (glb_piArray[glb_i-1][1] != glb_piArray[glb_i][1]))
						{
							glb_piArray[glb_i-1][0] = glb_piArray[glb_i][0];
							glb_piArray[glb_i-1][1] = glb_piArray[glb_i][1];
							glb_i--;
						}												
					}
					else
					{
						glb_i = 0;
					}

					//glb_i = 0;	//初始化裁剪位置
					glb_iPre = glb_i;	//初始化裁剪位置
					glb_bRun = TRUE;
					//glb_bRunFinish = FALSE;
					glb_bCylinderInit = FALSE;
					glb_bCutStart = FALSE;
					glb_bMoveEnable = TRUE;
					glb_bRotateEnable = FALSE;
					
					//设定T形截面的特性
					d5480_set_profile(Axis_C,0,360*2*fRateC,glb_nAccSpeed*fRateC*20,glb_nAccSpeed*fRateC*20);
					d5480_set_s_profile(Axis_C,1.0);//设定S形截面的特性
					
					//设置插补速度模式
					d5480_set_vector_profile(0,1.0,glb_nHSpeed*fRateX,glb_nAccSpeed*fRateX,glb_nAccSpeed*fRateX);      
					//设置连续插补模式
					//d5480_conti_set_mode(0, 0, glb_nLSpeed*fRateX, 20, glb_nAccSpeed*fRateX);
					
					if (g_motionCardState == MOTION_CARD_STOP)
					{
						g_motionCardState = MOTION_CARD_MOVE; //设置系统为运行状态
					}
					else
					{
						if (g_motionCardState == MOTION_CARD_PAUSE)
						{
							//开始连续插补
							d5480_conti_start_list(0);
							//设置系统为运行状态
							g_motionCardState = MOTION_CARD_MOVE;
						} 
						else  //系统当前为运行状态
						{
							return;
						}
					}		
				}
				else	//启动自动裁剪
				{
					if ((TRUE == glb_bRunPre) && (FALSE == glb_bRun))
					{
						glb_nStart_X = d5480_get_position(Axis_X);	// 单位0.01mm
						glb_nStart_Y = d5480_get_position(Axis_Y);
						if ((glb_nStart_X+glb_nPosMax_X*fPRate) > 1600*100)
						{
							glb_bDataErr = TRUE;
							return;
						} 
						else if ((glb_nStart_Y+glb_nPosMax_Y*fPRate) > 1000*100)
						{
							glb_bDataErr = TRUE;
							return;
						} 
						
						glb_bRunPre = FALSE;
						d5480_write_outbit(0,OutPort_StartLamp,!glb_bRunPre);
						
						//////////////////////////////////////////////////////////////////////////
						glb_i = 0;	//初始化裁剪位置
						glb_iPre = glb_i;	//初始化裁剪位置
						glb_bRun = TRUE;
						//glb_bRunFinish = FALSE;
						glb_bCylinderInit = FALSE;
						glb_bCutStart = FALSE;
						glb_bMoveEnable = TRUE;
						glb_bRotateEnable = FALSE;
						
						//设定T形截面的特性
						d5480_set_profile(Axis_C,0,360*2*fRateC,glb_nAccSpeed*fRateC*20,glb_nAccSpeed*fRateC*20);
						d5480_set_s_profile(Axis_C,1.0);//设定S形截面的特性
						
						//设置插补速度模式
						d5480_set_vector_profile(0,1.0,glb_nHSpeed*fRateX,glb_nAccSpeed*fRateX,glb_nAccSpeed*fRateX);      
						//设置连续插补模式
						//d5480_conti_set_mode(0, 0, glb_nLSpeed*fRateX, 20, glb_nAccSpeed*fRateX);
						
						if (g_motionCardState == MOTION_CARD_STOP)
						{
							g_motionCardState = MOTION_CARD_MOVE; //设置系统为运行状态
						}
						else
						{
							if (g_motionCardState == MOTION_CARD_PAUSE)
							{
								//开始连续插补
								d5480_conti_start_list(0);
								//设置系统为运行状态
								g_motionCardState = MOTION_CARD_MOVE;
							} 
							else  //系统当前为运行状态
							{
								return;
							}
						}		
					}
					
				}				
			}

		}
	} 
	else
	{
		m_bStartBtn = FALSE;
	}

	//////////////////////////////////////////////////////////////////////////
	//如果系统当前为运行状态，就调用自动运行执行处理函数
	if (g_motionCardState == MOTION_CARD_MOVE)   
	{
 		if ((0 == glb_i) || glb_bPause) // 数据头
		{
			glb_bPause = FALSE;

			glb_bCutStart = FALSE;
			glb_bOpenFlag = FALSE;
			glb_bHeadToUp = FALSE;

			//先运动前准备
			d5480_write_outbit(0,Cylinder_Knife,!TRUE);	// 挑布
			//磨刀一次


			if (glb_bContinue == TRUE) //连续插补启动
			{
				d5480_conti_close_list(0);  //关闭连续缓存区
				glb_bContinue = FALSE;
			}
			//checkdone
			if(d5480_check_done(Axis_X) == 1 && d5480_check_done(Axis_Y) == 1 && d5480_check_done(Axis_C) == 1)
			{
				d5480_line2(Axis_X,(long)(glb_nStart_X+Offset_C_X+glb_piArray[glb_i][0]*fPRate),
					Axis_Y,(long)(glb_nStart_Y+Offset_C_Y+glb_piArray[glb_i][1]*fPRate),MOTION_ABSOLUTE);//两轴直线
				glb_i++;
				glb_bRotateEnable = TRUE;
				glb_bMoveEnable = FALSE;
				//glb_bRotateEnable = FALSE;
				//glb_bMoveEnable = TRUE;
			}
		} 
		else //if(glb_i<glb_nCount)
		{			
			if (glb_iPre != glb_i)
			{
				if(glb_i<glb_nCount)
				{
					if ((glb_piArray[glb_i][0]==glb_piArray[glb_i-1][0]) && (glb_piArray[glb_i][1]==glb_piArray[glb_i-1][1]))
					{
						glb_bCutStart = !glb_bCutStart;
						glb_bOpenFlag = TRUE;
						glb_i++;
						if (FALSE == glb_bCutStart)
						{
							glb_bHeadToUp = TRUE;
						}
					}
				}
				
				if((glb_i<glb_nCount-1) && (TRUE == glb_bCutStart))
				{
					//int nAbsA,nAbsB;
					// 角度2
					if ((glb_piArray[glb_i][0]==glb_piArray[glb_i-1][0]) && (glb_piArray[glb_i][1]>glb_piArray[glb_i-1][1]))
					{
						glb_nAngle2 = 90;
					} 
					else if ((glb_piArray[glb_i][0]==glb_piArray[glb_i-1][0]) && (glb_piArray[glb_i][1]<glb_piArray[glb_i-1][1]))
					{
// 						nAbsA = abs(glb_nAngle2_Pre-270);
// 						nAbsB = abs(glb_nAngle2_Pre+90);
// 						if (nAbsA<nAbsB)
// 						{
// 							glb_nAngle2 = 270;
// 						} 
// 						else
// 						{
// 							glb_nAngle2 = -90;
// 						}
						glb_nAngle2 = -90;
					}
					else if ((glb_piArray[glb_i][0]<glb_piArray[glb_i-1][0]) && (glb_piArray[glb_i][1]==glb_piArray[glb_i-1][1]))
					{
						glb_nAngle2 = 180;
					}
					else if ((glb_piArray[glb_i][0]>glb_piArray[glb_i-1][0]) && (glb_piArray[glb_i][1]==glb_piArray[glb_i-1][1]))
					{
						glb_nAngle2 = 0;
					}
					else
					{
						//glb_nAngle2 = (int)(atan2(glb_piArray[glb_i][1],glb_piArray[glb_i][0])* 180/3.14159);
						glb_nAngle2 = (int)(atan2((glb_piArray[glb_i][1]-glb_piArray[glb_i-1][1]),(glb_piArray[glb_i][0]-glb_piArray[glb_i-1][0]))* 180/3.14159);
					}
					
// 					if ((glb_piArray[glb_i][0]<glb_piArray[glb_i-1][0]) && (glb_nAngle2>0) && (glb_nAngle2<90))
// 					{
// 						glb_nAngle2 += 180;
// 					} 
// 					else if ((glb_piArray[glb_i][0]>glb_piArray[glb_i-1][0]) && (glb_nAngle2<0))
// 					{
// 						glb_nAngle2 += 360;
// 					}
// 					else if ((glb_piArray[glb_i][0]<glb_piArray[glb_i-1][0]) && (glb_nAngle2<0))
// 					{
// 						glb_nAngle2 += 180;
// 					}

// 					if ((glb_piArray[glb_i][0]<glb_piArray[glb_i-1][0]) && (glb_nAngle2>0) && (glb_nAngle2<90))
// 					{
// 						glb_nAngle2 -= 180;
// 					} 
// 					else if ((glb_piArray[glb_i][0]<glb_piArray[glb_i-1][0]) && (glb_nAngle2<0))
// 					{
// 						glb_nAngle2 += 180;
// 					}
					
					// 角度1
					if ((glb_piArray[glb_i-1][0]==glb_piArray[glb_i-2][0]) && (glb_piArray[glb_i-1][1]>glb_piArray[glb_i-2][1]))
					{
						glb_nAngle1 = 90;
					} 
					else if ((glb_piArray[glb_i-1][0]==glb_piArray[glb_i-2][0]) && (glb_piArray[glb_i-1][1]<glb_piArray[glb_i-2][1]))
					{
// 						nAbsA = abs(glb_nAngle1_Pre-270);
// 						nAbsB = abs(glb_nAngle1_Pre+90);
// 						if (nAbsA<nAbsB)
// 						{
// 							glb_nAngle1 = 270;
// 						} 
// 						else
// 						{
// 							glb_nAngle1 = -90;
// 						}
						glb_nAngle1 = -90;
					}
					else if ((glb_piArray[glb_i-1][0]<glb_piArray[glb_i-2][0]) && (glb_piArray[glb_i-1][1]==glb_piArray[glb_i-2][1]))
					{
						glb_nAngle1 = 180;
					}
					else if ((glb_piArray[glb_i-1][0]>glb_piArray[glb_i-2][0]) && (glb_piArray[glb_i-1][1]==glb_piArray[glb_i-2][1]))
					{
						glb_nAngle1 = 0;
					}
					else
					{
						//glb_nAngle1 = (int)(atan2(glb_piArray[glb_i-1][1],glb_piArray[glb_i-1][0])* 180/3.14159);
						glb_nAngle1 = (int)(atan2((glb_piArray[glb_i-1][1]-glb_piArray[glb_i-2][1]),(glb_piArray[glb_i-1][0]-glb_piArray[glb_i-2][0]))* 180/3.14159);
					}
					
// 					if ((glb_piArray[glb_i-1][0]<glb_piArray[glb_i-2][0]) && (glb_nAngle1>0) && (glb_nAngle1<90))
// 					{
// 						glb_nAngle1 += 180;
// 					} 
// 					else if ((glb_piArray[glb_i-1][0]>glb_piArray[glb_i-2][0]) && (glb_nAngle1<0))
// 					{
// 						glb_nAngle1 += 360;
// 					}
// 					else if ((glb_piArray[glb_i-1][0]<glb_piArray[glb_i-2][0]) && (glb_nAngle1<0))
// 					{
// 						glb_nAngle1 += 180;
// 					}

// 					if ((glb_piArray[glb_i-1][0]<glb_piArray[glb_i-2][0]) && (glb_nAngle1>0) && (glb_nAngle1<90))
// 					{
// 						glb_nAngle1 -= 180;
// 					} 
// 					else if ((glb_piArray[glb_i-1][0]<glb_piArray[glb_i-2][0]) && (glb_nAngle1<0))
// 					{
// 						glb_nAngle1 += 180;
// 					}
					
					glb_nAngle2_Pre = glb_nAngle2;
					glb_nAngle1_Pre = glb_nAngle1;


					//
					glb_ReAngle = glb_nAngle2 - glb_nAngle1;
					if (glb_ReAngle<0)
						glb_ReAngle = -glb_ReAngle;
					if(glb_ReAngle>180)
						glb_ReAngle = 360-glb_ReAngle;
					
					int nDistanceX = glb_piArray[glb_i][0]-glb_piArray[glb_i-1][0];
					int nDistanceY = glb_piArray[glb_i][1]-glb_piArray[glb_i-1][1];
					glb_nDistance = (int)sqrt(nDistanceX*nDistanceX + nDistanceY*nDistanceY);
					
					if ((glb_ReAngle<glb_nSwitchAngle) && (glb_nDistance*fPRate<glb_nSwitchLength*100) && (!glb_bOpenFlag))
					{
 						glb_bArcFlag = TRUE;	// 圆弧标志
						if (glb_bContinue == FALSE)  //连续插补没有启动
						{
							while(d5480_check_done(Axis_X) != 1|| d5480_check_done(Axis_Y) != 1 || d5480_check_done(Axis_C) != 1);
						}
					}
					else
					{
						glb_bArcFlag = FALSE;
					}				
				}
				else	// if(glb_i<glb_nCount-1)
				{
					glb_bArcFlag = FALSE;
				}

				glb_iPre = glb_i;
			}

			if (TRUE == glb_bArcFlag)	// 圆弧
			{
				glb_nReDistance[0] = glb_piArray[glb_i][0]-glb_piArray[glb_i-1][0];
				glb_nReDistance[0] = (int)(glb_nReDistance[0]*fPRate);
				glb_nReDistance[1] = glb_piArray[glb_i][1]-glb_piArray[glb_i-1][1];
				glb_nReDistance[1] = (int)(glb_nReDistance[1]*fPRate);
				glb_nReDistance[2] = glb_nAngle2 - glb_nAngle1;
				if(glb_nReDistance[2]>180)
					glb_nReDistance[2] = glb_nReDistance[2] - 360;
				if(glb_nReDistance[2]<-180)
					glb_nReDistance[2] = glb_nReDistance[2] + 360;
				glb_nReDistance[2] = glb_nReDistance[2]*fPRateC;
				
				if (glb_bContinue == FALSE)  //连续插补没有启动
				{	
					//checkdone
					//if(d5480_check_done(Axis_X) == 1 && d5480_check_done(Axis_Y) == 1 && d5480_check_done(Axis_C) == 1)
					{
						//Sleep(200);
						//设置插补速度模式
						//d5480_set_vector_profile(0,1.0,glb_nLSpeed*fRateX,glb_nAccSpeed*fRateX,glb_nAccSpeed*fRateX);      
						
						//打开连续插补缓冲区
						d5480_conti_open_list(3, g_Axis);
						//开始连续插补
						d5480_conti_start_list(0);
						glb_bContinue = TRUE;
					}
				}
				
				int nRemain = d5480_conti_check_remain_space(0);
				if (nRemain > 0)
				{
					d5480_conti_lines(3, g_Axis,(long *)glb_nReDistance,MOTION_RELATIVE);
					//d5480_line3(g_Axis,(long)glb_nReDistance[0],(long)glb_nReDistance[1],(long)glb_nReDistance[2],MOTION_RELATIVE);
					glb_i++;
				}
			} 
			// 直线
			else //if(d5480_check_done(Axis_X) == 1 && d5480_check_done(Axis_Y) == 1 && d5480_check_done(Axis_C) == 1)
			{
				//
				if (TRUE == glb_bOpenFlag)	// 开切点
				{
					//checkdone
					if(d5480_check_done(Axis_X) == 1 && d5480_check_done(Axis_Y) == 1 && d5480_check_done(Axis_C) == 1)
					{
						if (TRUE == glb_bCutStart)	// 图开始
						{
							if ((TRUE == glb_bMoveEnable)/* || (glb_i<3)*/) // 保证裁片切换旋转后再下刀
							{
								glb_bOpenFlag = FALSE;
								
								if(!glb_bDemo)
									d5480_write_outbit(0,OutPort_Cutter,!TRUE);
								Sleep(glb_nCutDelay*100);
								d5480_write_outbit(0,Cylinder_M,!TRUE);
								Sleep(glb_nCutDelay*100);
								d5480_write_outbit(0,Cylinder_A,!TRUE);
								Sleep(glb_nCutDelay*100);
								if(!glb_bDemo)
								{
									d5480_write_outbit(0,Cylinder_Knife,!FALSE);	// 挑布放下
									Sleep(glb_nCutDelay*100);
								}
							}
						} 
						else	// 图结束
						{
							glb_bOpenFlag = FALSE;
							
							d5480_write_outbit(0,OutPort_Cutter,!FALSE);
							d5480_write_outbit(0,Cylinder_Knife,!TRUE);	// 挑布收起
							Sleep(glb_nCutDelay*100);
							d5480_write_outbit(0,Cylinder_A,!FALSE);
							Sleep(glb_nCutDelay*100);
							d5480_write_outbit(0,Cylinder_M,!FALSE);
							Sleep(glb_nCutDelay*100);
							glb_bCylinderInit = TRUE;
							//if(glb_i<glb_nCount-1)
							//	glb_i++;
							glb_bHeadToUp = FALSE;
						}
					}
				}

				//
				if (glb_bContinue == TRUE) //连续插补启动
				{
					//设置插补速度模式
					//d5480_set_vector_profile(0,1.0,glb_nHSpeed*fRateX,glb_nAccSpeed*fRateX,glb_nAccSpeed*fRateX);      

					d5480_conti_close_list(0);  //关闭连续缓存区
					glb_bContinue = FALSE;
				}

				if (glb_i<glb_nCount)
				{					
					if((TRUE == glb_bMoveEnable) && (!glb_bHeadToUp))
					{						
						//checkdone
						if(d5480_check_done(Axis_X) == 1 && d5480_check_done(Axis_Y) == 1 && d5480_check_done(Axis_C) == 1)
						{
							d5480_line2(Axis_X,(long)(glb_nStart_X+Offset_C_X+glb_piArray[glb_i][0]*fPRate),
								Axis_Y,(long)(glb_nStart_Y+Offset_C_Y+glb_piArray[glb_i][1]*fPRate),MOTION_ABSOLUTE);//两轴直线
							glb_i++;
							glb_bRotateEnable = TRUE;
							glb_bMoveEnable = FALSE;
						} 
					}				

					if(TRUE == glb_bRotateEnable)
					{
						//checkdone
						if(d5480_check_done(Axis_X) == 1 && d5480_check_done(Axis_Y) == 1 && d5480_check_done(Axis_C) == 1)
						{
							if (TRUE == glb_bCutStart)
							{
								int nAngleRe = glb_nAngle2-glb_nAngle1;
								if (nAngleRe>180)
								{
									nAngleRe -= 360;
								}
								else if (nAngleRe<-180)
								{
									nAngleRe += 360;
								}

								if (TRUE == glb_bOpenFlag)	// 开切点
								{
									int nAngle = d5480_get_position(Axis_C)%(360*fPRateC);
									int nAngleTemp = nAngle/fPRateC-glb_nAngle2;
									if (nAngleTemp>180)
									{
										nAngle -= 360*fPRateC;
									} 
									else if (nAngleTemp<-180)
									{
										nAngle += 360*fPRateC;
									}
									d5480_set_position(Axis_C,nAngle);

									d5480_pmove(Axis_C,glb_nAngle2*fPRateC,MOTION_ABSOLUTE);
								}
								else
								{
									d5480_pmove(Axis_C,nAngleRe*fPRateC,MOTION_RELATIVE);
								}
							}
							glb_bMoveEnable = TRUE;
							glb_bRotateEnable = FALSE;
						}
					}
				}
				else // 裁剪完成
				{
					if (TRUE == glb_bCylinderInit)
					{
						glb_bCylinderInit = FALSE;

						//checkdone
						if(d5480_check_done(Axis_X) == 1 && d5480_check_done(Axis_Y) == 1 && d5480_check_done(Axis_C) == 1)
						{
							int nAngle = d5480_get_position(Axis_C)%(360*fPRateC);
							int nAngleTemp = nAngle/fPRateC-glb_nAngle2;
							if (nAngleTemp>180)
							{
								nAngle -= 360*fPRateC;
							} 
							else if (nAngleTemp<-180)
							{
								nAngle += 360*fPRateC;
							}
							d5480_set_position(Axis_C,nAngle);

							//d5480_line2(Axis_X,0,Axis_Y,0,MOTION_ABSOLUTE);//两轴直线
							//d5480_pmove(Axis_C,0*fPRateC,MOTION_ABSOLUTE);
							d5480_line3(g_Axis,0,0,0,MOTION_ABSOLUTE);
							g_motionCardState = MOTION_CARD_STOP;  //停止系统运行			
							//glb_bRun = FALSE;	// MainFrame Timer EmgOP 中复位(确保三轴停止再复位glb_bRun)
							glb_i = 0;	//初始化裁剪位置
							glb_iPre = glb_i;	//初始化裁剪位置
						}
					}
				}
			}						
		}
	}
	
	if ((TRUE==glb_bRun) && (MOTION_CARD_STOP==g_motionCardState))
	{
		//checkdone
		if(d5480_check_done(Axis_X) == 1 && d5480_check_done(Axis_Y) == 1 && d5480_check_done(Axis_C) == 1)
		{
			glb_bRun = FALSE;
		}
	}
}


void CMainFrame::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	Reset();
	Servo();
	Init();
	EmgOP();
	AlarmOP();

	Manual();
	Dial();
	AutoRun();


	CFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(0);
	
	CFrameWnd::OnClose();
}
