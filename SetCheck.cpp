// SetCheck.cpp : implementation file
//

#include "stdafx.h"
#include "YuanDao.h"
#include "SetCheck.h"
#include "DMC5480.h"
#include "MotionControl.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern FILE *sysInfoFile;
extern CString			glb_strSysIniPath;			// 系统文件路径

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



/////////////////////////////////////////////////////////////////////////////
// CSetCheck dialog


CSetCheck::CSetCheck(CWnd* pParent /*=NULL*/)
	: CDialog(CSetCheck::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetCheck)
	m_nSharpen_Time = 1;
	m_nSTime_Interval = 180;
	m_nHSpeed = 40;
	m_nLSpeed = 20;
	m_nIdleSpeed = 60;
	m_nAccSpeed = 200;
	m_nSwitchAngle = 27;
	m_nSwitchLength = 200;
	m_nCutDelay = 5;
	m_nDial = 1;
	m_bDemo = FALSE;
	m_bPump = FALSE;
	//}}AFX_DATA_INIT

	m_bHeadRotation = FALSE;
	m_bMCylinder = FALSE;
	m_bACylinder = FALSE;
	m_bKnifeCylinder = FALSE;
	m_bCutterRun = FALSE;
	m_bSharpen = FALSE;
	m_bEmergencyLamp = FALSE;
	m_bOriginLamp = FALSE;
	m_bStartLamp = FALSE;

	m_bPCylinder = FALSE;
	m_bPMotor = FALSE;
}


void CSetCheck::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetCheck)
	DDX_Control(pDX, IDC_START_LAMP, m_btnStartLamp);
	DDX_Control(pDX, IDC_ORIGIN_LAMP, m_btnOriginLamp);
	DDX_Control(pDX, IDC_EMERGENCY_LAMP, m_btnEmergencyLamp);
	DDX_Control(pDX, IDC_SHARPEN, m_btnSharpen);
	DDX_Control(pDX, IDC_CUTTER_RUN, m_btnCutterRun);
	DDX_Control(pDX, IDC_KNIFE_CYLINDER, m_btnKnifeCylinder);
	DDX_Control(pDX, IDC_A_CYLINDER, m_btnACylinder);
	DDX_Control(pDX, IDC_M_CYLINDER, m_btnMCylinder);
	DDX_Control(pDX, IDC_HEAD_ROTATION, m_btnHeadRotation);
	DDX_Control(pDX, IDC_DIAL_SPIN, m_DialSpin);
	DDX_Text(pDX, IDC_SHARPEN_TIME, m_nSharpen_Time);
	DDV_MinMaxInt(pDX, m_nSharpen_Time, 0, 20);
	DDX_Text(pDX, IDC_S_TIME_INTER, m_nSTime_Interval);
	DDV_MinMaxInt(pDX, m_nSTime_Interval, 0, 1000);
	DDX_Text(pDX, IDC_H_SPEED, m_nHSpeed);
	DDV_MinMaxInt(pDX, m_nHSpeed, 0, 200);
	DDX_Text(pDX, IDC_L_SPEEN, m_nLSpeed);
	DDV_MinMaxInt(pDX, m_nLSpeed, 0, 200);
	DDX_Text(pDX, IDC_I_SPEED, m_nIdleSpeed);
	DDV_MinMaxInt(pDX, m_nIdleSpeed, 0, 200);
	DDX_Text(pDX, IDC_ACC, m_nAccSpeed);
	DDV_MinMaxInt(pDX, m_nAccSpeed, 0, 10000);
	DDX_Text(pDX, IDC_SWITCH_ANGLE, m_nSwitchAngle);
	DDV_MinMaxInt(pDX, m_nSwitchAngle, 0, 90);
	DDX_Text(pDX, IDC_SWITCH_LENGTH, m_nSwitchLength);
	DDV_MinMaxInt(pDX, m_nSwitchLength, 0, 1000);
	DDX_Text(pDX, IDC_CUT_DELAY, m_nCutDelay);
	DDV_MinMaxInt(pDX, m_nCutDelay, 0, 100);
	DDX_Text(pDX, IDC_DIAL, m_nDial);
	DDV_MinMaxInt(pDX, m_nDial, 0, 9);
	DDX_Check(pDX, IDC_DEMO, m_bDemo);
	DDX_Check(pDX, IDC_PUMP, m_bPump);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetCheck, CDialog)
	//{{AFX_MSG_MAP(CSetCheck)
	ON_BN_CLICKED(IDC_M_CYLINDER, OnMCylinder)
	ON_BN_CLICKED(IDC_SHARPEN, OnSharpen)
	ON_BN_CLICKED(IDC_HEAD_ROTATION, OnHeadRotation)
	ON_BN_CLICKED(IDC_A_CYLINDER, OnACylinder)
	ON_BN_CLICKED(IDC_KNIFE_CYLINDER, OnKnifeCylinder)
	ON_BN_CLICKED(IDC_CUTTER_RUN, OnCutterRun)
	ON_BN_CLICKED(IDC_EMERGENCY_LAMP, OnEmergencyLamp)
	ON_BN_CLICKED(IDC_ORIGIN_LAMP, OnOriginLamp)
	ON_BN_CLICKED(IDC_START_LAMP, OnStartLamp)
	ON_BN_CLICKED(IDC_DIAL_CONFIRM, OnDialConfirm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetCheck message handlers

BOOL CSetCheck::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_DialSpin.SetBuddy(GetDlgItem(IDC_DIAL));
	m_DialSpin.SetRange(0,9);


	m_nSharpen_Time = glb_nSharpen_Time;
	m_nSTime_Interval = glb_nSTime_Interval;
	m_nHSpeed = glb_nHSpeed;
	m_nLSpeed = glb_nLSpeed;
	m_nIdleSpeed = glb_nIdleSpeed;
	m_nAccSpeed = glb_nAccSpeed;
	m_nSwitchAngle = glb_nSwitchAngle;
	m_nSwitchLength = glb_nSwitchLength;
	m_nCutDelay = glb_nCutDelay;
	m_nDial = glb_nDial;
	m_bPump = glb_bPump;
	m_bDemo = glb_bDemo;

	UpdateData(FALSE);



// 	if( d5480_board_init() <= 0 )//控制卡的初始化操作
// 		MessageBox("初始化DMC5480卡失败！","出错");
	


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetCheck::OnHeadRotation() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_nAxis = Axis_C;
	//m_bLogic = 1;
	
	m_nSpeed = (long)(36*fRateC); //C轴速度
	m_nAcc = (long)(m_nAccSpeed*fRateC);
	m_nDec = (long)(m_nAccSpeed*fRateC);

	if (m_bHeadRotation)
	{
		m_btnHeadRotation.SetWindowText("Off");
		m_bHeadRotation = FALSE;

		d5480_imd_stop(m_nAxis);
		//d5480_decel_stop(m_nAxis,m_nDec);		
		//d5480_emg_stop();	//全部急停

	}
	else
	{
		m_btnHeadRotation.SetWindowText("On");
		m_bHeadRotation = TRUE;

		if ((d5480_check_done( m_nAxis ))&0x02 == 1) //已经在运动中
			return; 

		//设定脉冲模式及逻辑方向
		//d5480_set_pulse_outmode( m_nAxis, 5);

		//设定T形截面的特性
		d5480_set_profile(m_nAxis,0,m_nSpeed,m_nAcc,m_nDec);
		d5480_set_s_profile(m_nAxis,1.0);//设定S形截面的特性
		int	dir = 1;//0:负方向	1：正方向
		d5480_vmove( m_nAxis, dir,m_nSpeed);	
	}

}

void CSetCheck::OnMCylinder() 
{
	// TODO: Add your control notification handler code here
	if (m_bMCylinder)
	{
		m_btnMCylinder.SetWindowText("Off");
		m_bMCylinder = FALSE;
		d5480_write_outbit(0,Cylinder_M,!m_bMCylinder);
	}
	else
	{
		m_btnMCylinder.SetWindowText("ON");
		m_bMCylinder = TRUE;
		d5480_write_outbit(0,Cylinder_M,!m_bMCylinder);
	}
}

void CSetCheck::OnACylinder() 
{
	// TODO: Add your control notification handler code here
	if (m_bACylinder)
	{
		m_btnACylinder.SetWindowText("Off");
		m_bACylinder = FALSE;
		d5480_write_outbit(0,Cylinder_A,!m_bACylinder);
	} 
	else
	{
		m_btnACylinder.SetWindowText("ON");
		m_bACylinder = TRUE;
		d5480_write_outbit(0,Cylinder_A,!m_bACylinder);
	}
	
}

void CSetCheck::OnKnifeCylinder() 
{
	// TODO: Add your control notification handler code here
	if (m_bKnifeCylinder)
	{
		m_btnKnifeCylinder.SetWindowText("Off");
		m_bKnifeCylinder = FALSE;
		d5480_write_outbit(0,Cylinder_Knife,!m_bKnifeCylinder);
	} 
	else
	{
		m_btnKnifeCylinder.SetWindowText("ON");
		m_bKnifeCylinder = TRUE;
		d5480_write_outbit(0,Cylinder_Knife,!m_bKnifeCylinder);
	}
}

void CSetCheck::OnCutterRun() 
{
	// TODO: Add your control notification handler code here
	if (m_bCutterRun)
	{
		m_btnCutterRun.SetWindowText("Off");
		m_bCutterRun = FALSE;
		d5480_write_outbit(0,OutPort_Cutter,!m_bCutterRun);
	} 
	else
	{
		m_btnCutterRun.SetWindowText("ON");
		m_bCutterRun = TRUE;
		d5480_write_outbit(0,OutPort_Cutter,!m_bCutterRun);
	}
	
}

void CSetCheck::OnSharpen() 
{
	// TODO: Add your control notification handler code here
	if (m_bSharpen)
	{
		m_btnSharpen.SetWindowText("Off");
		m_bSharpen = FALSE;
		d5480_write_outbit(0,Cylinder_Knife,0);
		d5480_write_outbit(0,OutPort_Cutter,!m_bSharpen);
		d5480_write_outbit(0,Cylinder_Sharpen,!m_bSharpen);
	} 
	else
	{
		m_btnSharpen.SetWindowText("ON");
		m_bSharpen = TRUE;
		d5480_write_outbit(0,Cylinder_Knife,0);
		d5480_write_outbit(0,OutPort_Cutter,!m_bSharpen);
		d5480_write_outbit(0,Cylinder_Sharpen,!m_bSharpen);
	}
	
}

void CSetCheck::OnEmergencyLamp() 
{
	// TODO: Add your control notification handler code here
	if (m_bEmergencyLamp)
	{
		m_btnEmergencyLamp.SetWindowText("Off");
		m_bEmergencyLamp = FALSE;
		d5480_write_outbit(0,OutPort_EMGLamp,!m_bEmergencyLamp);
	} 
	else
	{
		m_btnEmergencyLamp.SetWindowText("ON");
		m_bEmergencyLamp = TRUE;
		d5480_write_outbit(0,OutPort_EMGLamp,!m_bEmergencyLamp);
	}
	
}

void CSetCheck::OnOriginLamp() 
{
	// TODO: Add your control notification handler code here
	if (m_bOriginLamp)
	{
		m_btnOriginLamp.SetWindowText("Off");
		m_bOriginLamp = FALSE;
		d5480_write_outbit(0,OutPort_OriginLamp,!m_bOriginLamp);
	} 
	else
	{
		m_btnOriginLamp.SetWindowText("ON");
		m_bOriginLamp = TRUE;
		d5480_write_outbit(0,OutPort_OriginLamp,!m_bOriginLamp);
	}
	
}

void CSetCheck::OnStartLamp() 
{
	// TODO: Add your control notification handler code here
	if (m_bStartLamp)
	{
		m_btnStartLamp.SetWindowText("Off");
		m_bStartLamp = FALSE;
		d5480_write_outbit(0,OutPort_StartLamp,!m_bStartLamp);
	} 
	else
	{
		m_btnStartLamp.SetWindowText("ON");
		m_bStartLamp = TRUE;
		d5480_write_outbit(0,OutPort_StartLamp,!m_bStartLamp);
	}
	
}

void CSetCheck::OnDialConfirm() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	switch (m_nDial)
	{
	case 0:
		
		break;
	case 1:
		m_nAxis = Axis_C;
		//m_bLogic = 0;
		
		m_nSpeed = (long)(36*fRateC); //Z轴速度
		m_nAcc = (long)(m_nAccSpeed*fRateC);
		m_nDec = (long)(m_nAccSpeed*fRateC);
		
		if (m_bHeadRotation)
		{
			m_bHeadRotation = FALSE;
			
			d5480_imd_stop(m_nAxis);
			//d5480_decel_stop(m_nAxis,m_nDec);		
			//d5480_emg_stop();	//全部急停
			
		}
		else
		{
			m_bHeadRotation = TRUE;
			
			if ((d5480_check_done( m_nAxis ))&0x02 == 1) //已经在运动中
				return; 
			
			//设定脉冲模式及逻辑方向（此处脉冲模式固定为P+D方向：脉冲+方向）	
			//d5480_set_pulse_outmode( m_nAxis, 5);
			
			//设定T形截面的特性
			d5480_set_profile(m_nAxis,0,m_nSpeed,m_nAcc,m_nDec);
			d5480_set_s_profile(m_nAxis,1.0);//设定S形截面的特性
			int	dir = 1;//0:负方向	1：正方向
			d5480_vmove( m_nAxis, dir,m_nSpeed);	
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
			Sleep(1000);
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

void CSetCheck::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();

	glb_nSharpen_Time = m_nSharpen_Time;
	glb_nSTime_Interval = m_nSTime_Interval;
	glb_nHSpeed = m_nHSpeed;
	glb_nLSpeed = m_nLSpeed;
	glb_nIdleSpeed = m_nIdleSpeed;
	glb_nAccSpeed = m_nAccSpeed;
	glb_nSwitchAngle = m_nSwitchAngle;
	glb_nSwitchLength = m_nSwitchLength;
	glb_nCutDelay = m_nCutDelay;
	glb_nDial = m_nDial;
	glb_bPump = m_bPump;
	glb_bDemo = m_bDemo;


	//设定T形截面的特性
	//d5480_set_profile(Axis_X,0,glb_nHSpeed,glb_nAccSpeed,glb_nAccSpeed);
	//d5480_set_s_profile(Axis_X,1.0);//设定S形截面的特性


	// 写文件
	CString strFileData;
	long	nfLen = 0;
	//long	nIndicator = 0;
	char	tokenBeg[] = "PARA_BEGIN";
	char	tokenEnd[] = "PARA_END";
	
	//int		nResult = 0;
	char*	data = NULL;
	
	
	sysInfoFile = fopen(glb_strSysIniPath, "r");
	
	rewind(sysInfoFile);
	
	nfLen = GetFileInfo(sysInfoFile);
	data = new char[nfLen];
	fread(data, sizeof(char), nfLen-1, sysInfoFile);
	data[nfLen-1] = '\0';
	
	strFileData = data;
	// AfxMessageBox(strFileData);	
	fclose(sysInfoFile);
	
	
	sysInfoFile = fopen(glb_strSysIniPath, "w");
// 	nIndicator = strFileData.Find(tokenBeg, nIndicator);
// 	if (nIndicator == -1)
// 	{
// 		AfxMessageBox("Read system information failure!");
// 		return;
// 	}

	if (sysInfoFile)
	{		
		fprintf( sysInfoFile, "%s\n", tokenBeg);

		fprintf(sysInfoFile, "%ld\n", glb_nSharpen_Time);
		fprintf(sysInfoFile, "%ld\n", glb_nSTime_Interval);
		fprintf(sysInfoFile, "%ld\n", glb_nHSpeed);		
		fprintf(sysInfoFile, "%ld\n", glb_nLSpeed);
		fprintf(sysInfoFile, "%ld\n", glb_nIdleSpeed);
		fprintf(sysInfoFile, "%ld\n", glb_nAccSpeed);
		fprintf(sysInfoFile, "%ld\n", glb_nSwitchAngle);
		fprintf(sysInfoFile, "%ld\n", glb_nSwitchLength);
		fprintf(sysInfoFile, "%ld\n", glb_nCutDelay);		
		fprintf(sysInfoFile, "%ld\n", glb_bPump);		
		fprintf(sysInfoFile, "%ld\n", glb_bDemo);

		fprintf( sysInfoFile, "%s\n", tokenEnd);
	}
	
	delete []data;
	data = NULL;
	
	fclose(sysInfoFile);
	


	CDialog::OnOK();
}
