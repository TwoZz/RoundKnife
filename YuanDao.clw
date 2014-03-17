; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAlarm
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "YuanDao.h"
LastPage=0

ClassCount=8
Class1=CYuanDaoApp
Class2=CYuanDaoDoc
Class3=CYuanDaoView
Class4=CMainFrame

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDD_RUN
Class5=CAboutDlg
Resource3=IDR_MAINFRAME
Class6=CSetCheck
Class7=CRun
Resource4=IDD_SET_CHECK
Class8=CAlarm
Resource5=IDD_ALARM

[CLS:CYuanDaoApp]
Type=0
HeaderFile=YuanDao.h
ImplementationFile=YuanDao.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CYuanDaoApp

[CLS:CYuanDaoDoc]
Type=0
HeaderFile=YuanDaoDoc.h
ImplementationFile=YuanDaoDoc.cpp
Filter=N

[CLS:CYuanDaoView]
Type=0
HeaderFile=YuanDaoView.h
ImplementationFile=YuanDaoView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CYuanDaoView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=YuanDao.cpp
ImplementationFile=YuanDao.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_SET_CHECK
Command17=ID_RUN
Command18=ID_APP_ABOUT
CommandCount=18

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[DLG:IDD_SET_CHECK]
Type=1
Class=CSetCheck
ControlCount=57
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,static,1342308352
Control5=IDC_SHARPEN_TIME,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_S_TIME_INTER,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_H_SPEED,edit,1350631552
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_L_SPEEN,edit,1350631552
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_I_SPEED,edit,1350631552
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_ACC,edit,1350631552
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_SWITCH_ANGLE,edit,1350631552
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_SWITCH_LENGTH,edit,1350631552
Control27=IDC_STATIC,static,1342308352
Control28=IDC_STATIC,static,1342308352
Control29=IDC_CUT_DELAY,edit,1350631552
Control30=IDC_STATIC,static,1342308352
Control31=IDC_STATIC,button,1342177287
Control32=IDC_STATIC,static,1342308352
Control33=IDC_HEAD_ROTATION,button,1342242816
Control34=IDC_STATIC,static,1342308352
Control35=IDC_M_CYLINDER,button,1342242816
Control36=IDC_STATIC,static,1342308352
Control37=IDC_A_CYLINDER,button,1342242816
Control38=IDC_STATIC,static,1342308352
Control39=IDC_KNIFE_CYLINDER,button,1342242816
Control40=IDC_STATIC,static,1342308352
Control41=IDC_CUTTER_RUN,button,1342242816
Control42=IDC_STATIC,static,1342308352
Control43=IDC_SHARPEN,button,1342242816
Control44=IDC_STATIC,static,1342308352
Control45=IDC_EMERGENCY_LAMP,button,1342242816
Control46=IDC_STATIC,static,1342308352
Control47=IDC_ORIGIN_LAMP,button,1342242816
Control48=IDC_STATIC,static,1342308352
Control49=IDC_START_LAMP,button,1342242816
Control50=IDC_STATIC,button,1342177287
Control51=IDC_DIAL,edit,1350631552
Control52=IDC_DIAL_CONFIRM,button,1342242816
Control53=IDC_PUMP,button,1342242851
Control54=IDC_DEMO,button,1342242851
Control55=IDC_DIAL_SPIN,msctls_updown32,1342177314
Control56=IDC_STATIC,static,1208090624
Control57=IDC_BORE_CYLINDER,button,1208025088

[DLG:IDD_RUN]
Type=1
Class=CRun
ControlCount=18
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_ORIGIN,button,1342242816
Control4=IDC_OPEN_CUT_FILE,button,1342242816
Control5=IDC_CUT_FILE_NAME,edit,1350631552
Control6=IDC_AUTO_RUN,button,1342242816
Control7=IDC_ORIGIN_STATUS,static,1342308352
Control8=IDC_EMERGENCYSTOP,button,1342242816
Control9=IDC_STATIC,button,1342177287
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_POSITIONX,edit,1350631552
Control14=IDC_POSITIONC,edit,1350631552
Control15=IDC_POSITIONY,edit,1350631552
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352

[CLS:CSetCheck]
Type=0
HeaderFile=SetCheck.h
ImplementationFile=SetCheck.cpp
BaseClass=CDialog
Filter=D
LastObject=CSetCheck
VirtualFilter=dWC

[CLS:CRun]
Type=0
HeaderFile=Run.h
ImplementationFile=Run.cpp
BaseClass=CDialog
Filter=D
LastObject=CRun
VirtualFilter=dWC

[DLG:IDD_ALARM]
Type=1
Class=CAlarm
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_ALARM_V,static,1342308352

[CLS:CAlarm]
Type=0
HeaderFile=Alarm.h
ImplementationFile=Alarm.cpp
BaseClass=CDialog
Filter=D
LastObject=CAlarm
VirtualFilter=dWC

