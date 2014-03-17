// MotionControl.h: interface for the CMotionControl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOTIONCONTROL_H__973BE140_BBD1_49F8_86E8_2F6244C945A2__INCLUDED_)
#define AFX_MOTIONCONTROL_H__973BE140_BBD1_49F8_86E8_2F6244C945A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMotionControl  
{
public:
	CMotionControl();
	virtual ~CMotionControl();

};

#endif // !defined(AFX_MOTIONCONTROL_H__973BE140_BBD1_49F8_86E8_2F6244C945A2__INCLUDED_)


//////////////////////////////////////////////////////////////////////////

typedef enum tagOutMode {
	OutMode_OutDir_IL = 0,	// out 上升沿(increase)， direction 低电平(low)
	OutMode_OutDir_DL = 1,	// out 下降沿(decrease)， direction 低电平(low)
	OutMode_OutDir_IH = 2,	// out 上升沿(increase)， direction 高电平(high)
	OutMode_OutDir_DH = 3,	// out 下升沿(decrease)， direction 高电平(high)
	OutMode_CWCCW_I	  = 4,	// 上升沿
	OutMode_CWCCW_D	  = 5	// 下降沿
} OutMode;

typedef enum tagIptMode {
	IptMode_4X		= 0,	// 4X A/B
	IptMode_2X		= 1,	// 2X A/B
	IptMode_1X		= 2,	// 1X A/B
	IptMode_CWCCW	= 3		// CW/CCW
} IptMode;

//////////////////////////////////////////////////////////////////////////
// 速度模式运动函数														//
// DWORD d3000_start_sv_move(short axis, long StrVel, long MaxVel,		//
// double Tacc, double Tsacc)											//
// d3000_start_tv_move													//
// d3000_get_speed														//
// d3000_change_speed													//
// d3000_decel_stop														//
// d3000_emg_stop														//
// 以S 形轮廓加速一个轴至常速然后该轴一直以常速度运动					//
// 直到改变速度命令停或限位停运动的方向由速度参数MaxVel 的符号决定		//
// strVel: start velocity, unit: pulse per-second(pps)					//
// MaxVel: maxium velocity(pps); 正值正方向运动，负值负方向运动			//
// newVel: new velocity(pps), 只能写入正值，方向由原来方向确定			//
// Tacc: acceleration time; Tsacc: s section acceleration time			//
// 正确返回ERR_NoError 错误返回ERR_Error								//
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// 单轴位置模式函数														//
// DWORD d3000_start_t_move(short axis, long Dist, long StrVel, long	//
// MaxVel, double Tacc, double Tdec)									//
// d3000_start_t_move 以梯形速度轮廓运动指定距离						//	
// d3000_start_ta_move 以梯形速度轮廓运动到指定位置						//
// d3000_start_s_move 以S 形速度轮廓运动指定距离						//
// d3000_start_sa_move 以S 形速度轮廓运动到指定位置						//
// 以S 形轮廓加速一个轴至常速然后该轴一直以常速度运动					//
// 直到改变速度命令停或限位停运动的方向由速度参数MaxVel 的符号决定		//
// strVel: start velocity, unit: pulse per-second(pps)					//
// MaxVel: maxium velocity(pps); 正值正方向运动，负值负方向运动			//
// newVel: new velocity(pps), 只能写入正值，方向由原来方向确定			//
// Tacc: acceleration time; Tsacc: s section acceleration time			//
// unit: second. 必须满足:  Tacc > Tsacc								//
// Tdec: deceleration time; Tsacc: s section acceleration time			//
// 正确返回ERR_NoError 错误返回ERR_Error								//
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// 原点返回函数															//
// DWORD d3000_set_home(short axis, short home_mode, short org_logic)	//
// DWORD d3000_set_index(short axis, short index_mode, short ez_logic)	//
// d3000_set_home 设置遇原点信号是否停止以及原点信号有效电平			//
// d3000_set_index 设置遇EZ 信号是否停止以及EZ 信号有效电平				//
// d3000_home_move 驱使指定轴执行回原点运动								//
// d3000_index_move 驱动指定轴执行找EZ 信号运动							//
// home_mode: 遇原点信号是否停止，0-不停止，1-停止						//
// index_mode: 遇EZ信号是否停止，0-不停止，1-停止						//
// org_logic: 原点信号有效电平，0-低电平有效，1-高电平有效				//
// ez_logic: EZ信号有效电平，0-低电平有效，1-高电平有效					//
// strVel: start velocity, unit: pulse per-second(pps)					//
// MaxVel: maxium velocity(pps); 正值正方向运动，负值负方向运动			//
// Tacc: acceleration time; unit: second. 必须满足:  Tacc > 0			//
// 正确返回ERR_NoError 错误返回ERR_Error								//
//////////////////////////////////////////////////////////////////////////
typedef enum tagHomeMode {
	HomeMode_NoStop = 0,	// 遇原点信号是否停止，0-不停止，1-停止
	HomeMode_Stop	= 1		// 遇原点信号是否停止，0-不停止，1-停止
} HomeMode;

typedef enum tagEzMode {
	EzMode_NoStop	= 0,		// 遇EZ信号是否停止，0-不停止，1-停止
	EzMode_Stop		= 1			// 遇EZ信号是否停止，0-不停止，1-停止
}EzMode;

typedef enum tagIndexMode {
	IndexMode_EZNoStop	= 0,	// 遇EZ信号是否停止，0-不停止，1－停止
	IndexMode_EZStop	= 1		// 遇EZ信号是否停止，0-不停止，1－停止
} IndexMode;

// 有效电平： 0-低电平有效，1-高电平有效
typedef enum tagPwLevel {
		Level_Low	= 0,
		Level_High	= 1
}PwLevel;

//////////////////////////////////////////////////////////////////////////
// 手轮/JOG运动函数														//
// DWORD d3000_set_hwheel(short axis, short mode, long pulse, long MaxVel)
// DWORD d3000_set_jog(short axis, short mode, long MaxVel)				//
// d3000_set_hwheel 指定轴按照手轮输入运动								//
// d3000_set_jog 指定轴进行JOG 运动										//
// mode 在d3000_set_hwheel 函数中表示手轮运动模式						//
//		在d3000_set_jog 函数中表示JOG 运动模式							//
//	0 禁止外部脉冲驱动													//
//	1 设axis 为n PAn/Jn+和PBn/Jn-输入控制第n 轴输出						//
//	2 第0 轴的PA0/J0+和PB0/J0-输入输出由INPUT8 和INPUT7					//
//		选择00:0 轴01:1 轴10:2 轴11:3 轴								//
//	3 第1 轴的PA0/J0+和PB0/J0-输入输出由INPUT8 和INPUT7					//
//		选择00:0 轴01:1 轴10:2 轴11:3 轴								//
//	4 0 轴的PA0/J0+和PB0/J0-控制axis 轴输出								//
//	5 1 轴的PA1/J1+和PB1/J1-控制axis 轴输出								//
//	6 2 轴的PA2/J2+和PB2/J2-控制axis 轴输出								//
//	7 3 轴的PA2/J2+和PB2/J2-控制axis 轴输出								//
// pulse: 手轮运动中输出脉冲数,只能设置为正值							//
// MaxVel: 输出脉冲速度只能设置为正值									//
// 正确返回ERR_NoError 错误返回ERR_Error								//
//////////////////////////////////////////////////////////////////////////

typedef enum tagManualMode {
	ManualMode_NoExternalPulse		= 0,	// 禁止外部脉冲驱动
	ManualMode_AxisSel_PJN			= 1,	// 各轴(轴号n)的 PAn/Jn+和PBn/Jn-输入控制第n 轴输出
	ManualMode_OptSel0_IPT78		= 2,	// 第0 轴的PA0/J0+和PB0/J0-输入,输出由INPUT8 和INPUT7选择	
	ManualMode_OptSel1_IPT78		= 3,	// 第1 轴的PA0/J0+和PB0/J0-输入输出由INPUT8 和INPUT7选择
	ManualMode_OptSel_PJ0			= 4,	// 0 轴的PA0/J0+和PB0/J0-控制axis 轴输出
	ManualMode_OptSel_PJ1			= 5,	// 1 轴的PA1/J1+和PB1/J1-控制axis 轴输出
	ManualMode_OptSel_PJ2			= 6,	// 2 轴的PA2/J2+和PB2/J2-控制axis 轴输出
	ManualMode_OptSel_PJ3			= 7		// 3 轴的PA3/J3+和PB3/J3-控制axis 轴输出
} ManualMode;

//////////////////////////////////////////////////////////////////////////
// 运动状态监测
// DWORD d3000_check_done(short axis)
// d3000_check_done 这个函数返回运动控制卡的运动状态

typedef enum tagMotionCheck {
	MotionCheck_NoCard		= 0, // 无卡	
	MotionCheck_Moving		= 1, // 运动中
	MotionCheck_PulseOver	= 2, // 命令脉冲数输出完毕
	MotionCheck_CmdStop		= 3, // 指令停止
	MotionCheck_LimitStop	= 4, // 限位停止
	MotionCheck_OrgStop		= 5, // 回原点运动停止
	MotionCheck_EzStop		= 6, // 找到EZ信号停止
	MotionCheck_AlmValid	= 7, // Alarm信号有效停止
	MotionCheck_EmgStop		= 8  // 外部EMG信号停止
} MotionCheck;

//////////////////////////////////////////////////////////////////////////
// 专用I/O接口函数														//
// d3000_set_alm 设置ALARM 信号是否使能及有效电平如果ALARM 信号在驱
// 动中被设置为使能当ALARM 信号有效时驱动将立即停止
// d3000_set_el 设定EL 信号的有效电平和响应模式
// d3000_set_inpINP 信号是否使能以及有效电平
// d3000_get_axis_status 读取指定轴的所有专用信号状态
// DWORD d3000_set_alm(short axis, short alm_mode, short alm_logic)
// DWORD d3000_set_el(short axis, shortel_select, short el_mode, 
//	short el_logic)
// DWORD d3000_set_inp(short axis, short inp_mode, short inp_logic)
// DWORD d3000_get_axis_status(short axis)
// alm_mode 是否使能ALARM 信号0 不使能1 使能
// alm_logic ALARM 信号的有效电平0 低电平有效1 高电平有效
// el_select 设置限位选择: 0 正限位1 负限位
// el_mode 设置限位元触发时响应模式0 立即停止 1 减速停止
// el_logic EL 信号的有效电平0 低电平有效1 高电平有效
// inp_mode 是否使能INP 信号0 不使能1 使能
// inp_logic 1INP 信号的有效电平0 低电平有效 1高电平有效

typedef enum tagAlmMode {
	AlmMode_Disable = 0,
	AlmMode_Enable	= 1
} AlmMode;

typedef enum tagELSlect {
	ELSlect_LimitPlus		= 0,	// 设置限位选择: 0 正限位1 负限位
	ELSlect_LimitMinus		= 1		// 设置限位选择: 0 正限位1 负限位
} ELSelect;

typedef enum tagELMode {
	ELMode_Stop		= 0,	// 设置限位元触发时响应模式0 立即停止 1 减速停止
	ELMode_DecStop	= 1		// 设置限位元触发时响应模式0 立即停止 1 减速停止
} ELMode;

typedef enum tagInpMode {
	InpMode_Disable = 0,	// 是否使能INP 信号0 不使能1 使能
	InpMode_Enable	= 1		// 是否使能INP 信号0 不使能1 使能
} InpMode;

typedef enum tagAxisStatus {
	AxisStatus_SLMT_Plus		= 0,	//正向软件限位状态
	AxisStatus_SLMT_Minus		= 1,	//负向软件限位状态
	AxisStatus_EL_Plus			= 2,	//正向限位状态
	AxisStatus_EL_Minus			= 3,	//负向限位状态
	AxisStatus_AlmStatus		= 4,	//ALARM信号状态
	AxisStatus_EmgStop			= 5,	//紧急停状态
	AxisStatus_EzLevel			= 6,	//EZ输入电平
	AxisStatus_Reserve1			= 7,	//保留
	AxisStatus_Reserve2			= 8,	//保留
	AxisStatus_OrgLevel			= 9,	//ORG信号输入电平
	AxisStatus_HwJogLevel_PAJ	= 10,	//PA/Jn+ 手轮和JOG输入电平 Hand wheel
	AxisStatus_HwJogLevel_PBJ	= 11,	//nPB/J- 手轮和JOG输入电平
	AxisStatus_InpLevel			= 12,	//INP INP输入电平
	AxisStatus_AlmLevel			= 13	//ALM_LEVEL ALARM信号电平

} AxisStatus;



//////////////////////////////////////////////////////////////////////////

// typedef enum tagErrorStatus {
// 	ERR_NOERR = 0,			//成功
// 	ERR_UNKNOWN	= 1,		//未知错误
// 	ERR_PARAERR = 2,			//参数错误
// 	ERR_TIMEOUT	= 3,		//操作超时
// 	ERR_CONTROLLERBUSY = 4,			//控制卡状态忙
// 	ERR_CONTILINE = 6,		//连续插补出错
// 	ERR_SENDERR = 10,			//数据传输错误，请检查PCI槽位是否松动
// 	ERR_FIRMWARE_INVALID_PARA = 20,		//控制器返回参数错误
// 	ERR_FIRMWARE_STATE_ERR = 22,			//控制器返回当前状态不允许操作
// 	ERR_FIRMWARE_CARD_NOT_SUPPORT = 24		//控制器不支持的功能
// } ErrStatus;


typedef enum tagInPort {
		InPort_N01				= 0,
		InPort_Start			= 1,
		InPort_YP				= 2,
		InPort_YN				= 3,
		InPort_XP				= 4,
		InPort_XN				= 5,
		InPort_Code1			= 6,
		InPort_Code2			= 7,
		InPort_Code3			= 8,
		InPort_Code4			= 9,
		InPort_CodeConfirm		= 10,
		InPort_Shift			= 11,
		InPort_Reset			= 12,
		InPort_Pump				= 13,
		InPort_AirPressure		= 14,
		InPort_InverterAlarm	= 15,
		InPort_HeadDown			= 16,
		InPort_N02				= 17,
		InPort_NO3				= 18,
		InPort_PowerOn			= 19,
		InPort_HeadUp			= 20
} InPort;


typedef enum tagOutPort {
		Cylinder_No1			= 0,		// 无气缸	
		Cylinder_M				= 1,		// 
		Cylinder_A				= 2,			// 
		Cylinder_Knife			= 3,	// 
		Cylinder_Sharpen		= 4,		// 
		OutPort_Bore			= 5,
		OutPort_No2				= 6,
		OutPort_StartLamp		= 7,
		OutPort_OriginLamp		= 8,
		OutPort_Alarm			= 9,
		OutPort_PowerLamp		= 10,
		OutPort_PumpLamp		= 11,
		OutPort_EMGLamp			= 12,
		OutPort_PumpStart		= 13,
		OutPort_PumpAlarmReset	= 14,
		OutPort_Pump1			= 15,
		OutPort_PCylinder		= 16,
		OutPort_PMotor			= 17,
		OutPort_No3				= 18,
		OutPort_BoreMotor		= 19,
		OutPort_Cutter			=20
		//Cylinder_Cuntter	= 5,			// 
		//OutPort_EmergencyLamp		= 6,		// 
		//OutPort_OriginLamp	= 7,			// 
		//OutPort_StartLamp		= 8			// 
} OutPort;

#define OutPort_ERC_X		32
#define OutPort_ERC_Y		29
//#define OutPort_ERC_Z		30
#define OutPort_ERC_C		31

#define InPort_ALM_X		36
#define InPort_ALM_Y		33
//#define InPort_ALM_Z		34
#define InPort_ALM_C		35


typedef enum tagAxis
{
	Axis_X 	= 3,
	Axis_Y	= 0,
	Axis_Z	= 1,
	Axis_C	= 2
} Axis;


// 速度比例   控制单位0.01mm  界面单位cm
#define	fRateX		(100*10)			//一个mm包括脉冲数	每转26.67mm		(10000/26.67=375)
#define	fRateY		(100*10)			//一个mm包括脉冲数	每转36.67mm		(10000/36.67=272.7)
#define	fRateC		(100)			//一度包括脉冲数	减速比1:6		(9000/(360/6)=150)

// 位置比例		数据单位0.1mm（0.025）  控制单位0.01mm
#define fPRate		2.5		// 0.025时，则为2.5
//#define fPRate	10		// 0.025时，则为2.5
#define fPRateC		100		// 数据单位：度   控制单位0.01度

#define Offset_C_X		(-5000)	//单位0.01mm
#define Offset_C_Y		(4700)	
#define Offset_P_X		(-13800)	
#define Offset_P_Y		(10700)	

#define PumpTime		300

enum {
	MOTION_CARD_MOVE = 0,    //运行
	MOTION_CARD_PAUSE = 1,   //暂停
	MOTION_CARD_STOP = 2,    //停止
};

enum {
	MOTION_RELATIVE = 0,    //相对位置
	MOTION_ABSOLUTE = 1,   //绝对位置
};



//////////////////////////////////////////////////////////////////////////
long GetFileInfo(FILE *pfile);




