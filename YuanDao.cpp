// YuanDao.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "YuanDao.h"

#include "MainFrm.h"
#include "YuanDaoDoc.h"
#include "YuanDaoView.h"
#include "MotionControl.h"
#include "DMC5480.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CYuanDaoApp

BEGIN_MESSAGE_MAP(CYuanDaoApp, CWinApp)
	//{{AFX_MSG_MAP(CYuanDaoApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CYuanDaoApp construction

CYuanDaoApp::CYuanDaoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CYuanDaoApp object

CYuanDaoApp theApp;


/////////////////////////////////////////
FILE *sysInfoFile;

//////////////////////////////////////////////////////////////////////////
CString	glb_strSysIniPath;	// 系统文件路径(包括文件名)


int glb_nSharpen_Time = 1;
int glb_nSTime_Interval = 60;
int glb_nHSpeed = 40;
int glb_nLSpeed = 20;
int glb_nIdleSpeed = 60;
int glb_nAccSpeed = 200;
int glb_nSwitchAngle = 27;
int glb_nSwitchLength = 200;
int glb_nCutDelay = 5;
int glb_nDial = 1;
BOOL glb_bDemo = FALSE;
BOOL glb_bPump = FALSE;
BOOL glb_bServOn = FALSE;

BOOL glb_bAlarm = FALSE;
BOOL glb_bAlarm_SX = FALSE;
BOOL glb_bAlarm_SY = FALSE;
BOOL glb_bAlarm_SC = FALSE;


BOOL glb_bInit = FALSE;
BOOL glb_bInitFinish = FALSE;


BOOL glb_bRunPre = FALSE;
BOOL glb_bRun = FALSE;
BOOL glb_bRunFinish = FALSE;
BOOL glb_bPause = FALSE;


int **glb_piArray;	// 裁切数据点
int glb_nCount = 0;	// 数据总行数
int glb_i = 0;		// 当前行
int glb_iPre = 0;	// 上一行

CString glb_pathName;
CString glb_strWndTitle;

int g_motionCardState = MOTION_CARD_STOP;    //运动轴的状态
WORD g_Axis[3]={3,0,2};  //保存参数类型
int g_nNumber[3];  //保存参数值的大小


BOOL glb_bContinue = FALSE;	// 连续插补

BOOL glb_bCutStart = FALSE;	// 图开始标志
BOOL glb_bOpenFlag = FALSE;	// 开口标志
BOOL glb_bArcFlag = FALSE;	// 圆弧标志

int glb_nReDistance[3];	// 相对距离
int glb_nAngle1;		// 角度1
int glb_nAngle2;		// 角度2
int glb_nAngle1_Pre;		// 角度1-前值
int glb_nAngle2_Pre;		// 角度2-前值
int glb_nDistance;		// 点距
int glb_nAngleRun;		// 执行的角度

int glb_ReAngle;	// 角度差

BOOL glb_bMoveEnable = FALSE;	//旋转后
BOOL glb_bRotateEnable = FALSE;	//移动后

BOOL glb_bEmgStatus = FALSE;	// 急停状态

BOOL glb_bCylinderInit = FALSE;	// 气缸初始化
BOOL glb_bHeadToUp = FALSE;	// 机头准备上升

int glb_nPosMax_X;	//单位0.1或0.025	数据单位
int glb_nPosMax_Y;
int glb_nStart_X;	//单位0.01mm		伺服单位
int glb_nStart_Y;

BOOL glb_bDataErr = FALSE;


/////////////////////////////////////////////////////////////////////////////
// CYuanDaoApp initialization

BOOL CYuanDaoApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CYuanDaoDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CYuanDaoView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	//////////////////////////////////////////////////////////////////////////
	// 创建系统文件
	char path[MAX_PATH] = "";	
	GetModuleFileName(NULL, path, MAX_PATH);//得到exe文件的全路径
	
	glb_strSysIniPath = path;
	
	//	CString strInfo;
	//	strInfo = glb_strSysIniPath;
	
	//	strInfo = strInfo.Left(strInfo.ReverseFind('\\'));
	//	strInfo += "\\sysInfo.ini";
	glb_strSysIniPath = glb_strSysIniPath.Left(glb_strSysIniPath.ReverseFind('\\'));
	glb_strSysIniPath += "\\sysInfo.ini";

// 	sysInfoFile = fopen(glb_strSysIniPath, "a");
// 	if( sysInfoFile == NULL )
// 	{
// 		AfxMessageBox( "The file fscanf.out was not opened\n", MB_ICONWARNING );
// 	}	
// 	fclose(sysInfoFile);

	//////////////////////////////////////////////////////////////////////////
	//读文件
	CString strFileData;
	long	nfLen = 0;
	long	nIndicator = 0;
	char	tokenBeg[] = "PARA_BEGIN";
	char	tokenEnd[] = "PARA_END";
	
	//int		nResult = 0;
	char*	data = NULL;
	
	long    firstIndicator=0;
	long    nextIndicator=0;
	CString readBackString[11];
	
	
	sysInfoFile = fopen(glb_strSysIniPath, "r");
	if (sysInfoFile)
	{
		nfLen = GetFileInfo(sysInfoFile);
		data = new char[nfLen];
		fread(data, sizeof(char), nfLen-1, sysInfoFile);
		data[nfLen-1] = '\0';
		
		strFileData = data;
		
		nIndicator = strFileData.Find(tokenBeg, nIndicator);
		if (nIndicator == -1)
		{
			AfxMessageBox("Read system information failure!");
		}
		else
		{
			nextIndicator=strFileData.Find('\n',nIndicator+1);
			for (int i=0;i<11;i++)
			{
				firstIndicator=nextIndicator;
				nextIndicator=strFileData.Find('\n',firstIndicator+1);
				readBackString[i]=
					strFileData.Mid(firstIndicator+1,nextIndicator-firstIndicator);					
			}
			
			glb_nSharpen_Time = atoi(readBackString[0]);
			glb_nSTime_Interval = atoi(readBackString[1]);
			glb_nHSpeed = atoi(readBackString[2]);		
			glb_nLSpeed = atoi(readBackString[3]);
			glb_nIdleSpeed = atoi(readBackString[4]);
			glb_nAccSpeed = atoi(readBackString[5]);		
			glb_nSwitchAngle = atoi(readBackString[6]);
			glb_nSwitchLength = atoi(readBackString[7]);
			glb_nCutDelay = atoi(readBackString[8]);
			
			glb_bPump = (BOOL)(atoi(readBackString[9]));
			glb_bDemo = (BOOL)((atoi(readBackString[10])));
		}
	}
	else
	{
		AfxMessageBox("Read system information failure!");
	}
	
	delete []data;
	data = NULL;
	
	fclose(sysInfoFile);


	if( d5480_board_init() <= 0 )//控制卡的初始化操作
		AfxMessageBox("初始化DMC5480卡失败！");

	//glb_nCount = 0;

	//Sleep(100);
	//d5480_set_pulse_outmode (Axis_X,5);
	//d5480_set_pulse_outmode (Axis_Y,5);
	//d5480_set_pulse_outmode (Axis_C,5);
	//////////////////////////////////////////////////////////////////////////


	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CYuanDaoApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CYuanDaoApp message handlers


int CYuanDaoApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	if (glb_nCount > 0)	//先释放
	{
		for (int i=0; i<glb_nCount; i++)
		{
			delete[] glb_piArray[i];
		}
		delete[] glb_piArray;
	}

	d5480_write_outbit(0,OutPort_Cutter,!FALSE);
	d5480_write_outbit(0,Cylinder_Knife,!TRUE);
	d5480_write_outbit(0,Cylinder_M,!FALSE);
	d5480_write_outbit(0,Cylinder_A,!FALSE);
	d5480_write_outbit(0,Cylinder_Sharpen,!FALSE);


	d5480_board_close();	//非常之重要，释放其占用的系统资源

	return CWinApp::ExitInstance();
}
