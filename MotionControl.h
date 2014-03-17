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
	OutMode_OutDir_IL = 0,	// out ������(increase)�� direction �͵�ƽ(low)
	OutMode_OutDir_DL = 1,	// out �½���(decrease)�� direction �͵�ƽ(low)
	OutMode_OutDir_IH = 2,	// out ������(increase)�� direction �ߵ�ƽ(high)
	OutMode_OutDir_DH = 3,	// out ������(decrease)�� direction �ߵ�ƽ(high)
	OutMode_CWCCW_I	  = 4,	// ������
	OutMode_CWCCW_D	  = 5	// �½���
} OutMode;

typedef enum tagIptMode {
	IptMode_4X		= 0,	// 4X A/B
	IptMode_2X		= 1,	// 2X A/B
	IptMode_1X		= 2,	// 1X A/B
	IptMode_CWCCW	= 3		// CW/CCW
} IptMode;

//////////////////////////////////////////////////////////////////////////
// �ٶ�ģʽ�˶�����														//
// DWORD d3000_start_sv_move(short axis, long StrVel, long MaxVel,		//
// double Tacc, double Tsacc)											//
// d3000_start_tv_move													//
// d3000_get_speed														//
// d3000_change_speed													//
// d3000_decel_stop														//
// d3000_emg_stop														//
// ��S ����������һ����������Ȼ�����һֱ�Գ��ٶ��˶�					//
// ֱ���ı��ٶ�����ͣ����λͣ�˶��ķ������ٶȲ���MaxVel �ķ��ž���		//
// strVel: start velocity, unit: pulse per-second(pps)					//
// MaxVel: maxium velocity(pps); ��ֵ�������˶�����ֵ�������˶�			//
// newVel: new velocity(pps), ֻ��д����ֵ��������ԭ������ȷ��			//
// Tacc: acceleration time; Tsacc: s section acceleration time			//
// ��ȷ����ERR_NoError ���󷵻�ERR_Error								//
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// ����λ��ģʽ����														//
// DWORD d3000_start_t_move(short axis, long Dist, long StrVel, long	//
// MaxVel, double Tacc, double Tdec)									//
// d3000_start_t_move �������ٶ������˶�ָ������						//	
// d3000_start_ta_move �������ٶ������˶���ָ��λ��						//
// d3000_start_s_move ��S ���ٶ������˶�ָ������						//
// d3000_start_sa_move ��S ���ٶ������˶���ָ��λ��						//
// ��S ����������һ����������Ȼ�����һֱ�Գ��ٶ��˶�					//
// ֱ���ı��ٶ�����ͣ����λͣ�˶��ķ������ٶȲ���MaxVel �ķ��ž���		//
// strVel: start velocity, unit: pulse per-second(pps)					//
// MaxVel: maxium velocity(pps); ��ֵ�������˶�����ֵ�������˶�			//
// newVel: new velocity(pps), ֻ��д����ֵ��������ԭ������ȷ��			//
// Tacc: acceleration time; Tsacc: s section acceleration time			//
// unit: second. ��������:  Tacc > Tsacc								//
// Tdec: deceleration time; Tsacc: s section acceleration time			//
// ��ȷ����ERR_NoError ���󷵻�ERR_Error								//
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// ԭ�㷵�غ���															//
// DWORD d3000_set_home(short axis, short home_mode, short org_logic)	//
// DWORD d3000_set_index(short axis, short index_mode, short ez_logic)	//
// d3000_set_home ������ԭ���ź��Ƿ�ֹͣ�Լ�ԭ���ź���Ч��ƽ			//
// d3000_set_index ������EZ �ź��Ƿ�ֹͣ�Լ�EZ �ź���Ч��ƽ				//
// d3000_home_move ��ʹָ����ִ�л�ԭ���˶�								//
// d3000_index_move ����ָ����ִ����EZ �ź��˶�							//
// home_mode: ��ԭ���ź��Ƿ�ֹͣ��0-��ֹͣ��1-ֹͣ						//
// index_mode: ��EZ�ź��Ƿ�ֹͣ��0-��ֹͣ��1-ֹͣ						//
// org_logic: ԭ���ź���Ч��ƽ��0-�͵�ƽ��Ч��1-�ߵ�ƽ��Ч				//
// ez_logic: EZ�ź���Ч��ƽ��0-�͵�ƽ��Ч��1-�ߵ�ƽ��Ч					//
// strVel: start velocity, unit: pulse per-second(pps)					//
// MaxVel: maxium velocity(pps); ��ֵ�������˶�����ֵ�������˶�			//
// Tacc: acceleration time; unit: second. ��������:  Tacc > 0			//
// ��ȷ����ERR_NoError ���󷵻�ERR_Error								//
//////////////////////////////////////////////////////////////////////////
typedef enum tagHomeMode {
	HomeMode_NoStop = 0,	// ��ԭ���ź��Ƿ�ֹͣ��0-��ֹͣ��1-ֹͣ
	HomeMode_Stop	= 1		// ��ԭ���ź��Ƿ�ֹͣ��0-��ֹͣ��1-ֹͣ
} HomeMode;

typedef enum tagEzMode {
	EzMode_NoStop	= 0,		// ��EZ�ź��Ƿ�ֹͣ��0-��ֹͣ��1-ֹͣ
	EzMode_Stop		= 1			// ��EZ�ź��Ƿ�ֹͣ��0-��ֹͣ��1-ֹͣ
}EzMode;

typedef enum tagIndexMode {
	IndexMode_EZNoStop	= 0,	// ��EZ�ź��Ƿ�ֹͣ��0-��ֹͣ��1��ֹͣ
	IndexMode_EZStop	= 1		// ��EZ�ź��Ƿ�ֹͣ��0-��ֹͣ��1��ֹͣ
} IndexMode;

// ��Ч��ƽ�� 0-�͵�ƽ��Ч��1-�ߵ�ƽ��Ч
typedef enum tagPwLevel {
		Level_Low	= 0,
		Level_High	= 1
}PwLevel;

//////////////////////////////////////////////////////////////////////////
// ����/JOG�˶�����														//
// DWORD d3000_set_hwheel(short axis, short mode, long pulse, long MaxVel)
// DWORD d3000_set_jog(short axis, short mode, long MaxVel)				//
// d3000_set_hwheel ָ���ᰴ�����������˶�								//
// d3000_set_jog ָ�������JOG �˶�										//
// mode ��d3000_set_hwheel �����б�ʾ�����˶�ģʽ						//
//		��d3000_set_jog �����б�ʾJOG �˶�ģʽ							//
//	0 ��ֹ�ⲿ��������													//
//	1 ��axis Ϊn PAn/Jn+��PBn/Jn-������Ƶ�n �����						//
//	2 ��0 ���PA0/J0+��PB0/J0-���������INPUT8 ��INPUT7					//
//		ѡ��00:0 ��01:1 ��10:2 ��11:3 ��								//
//	3 ��1 ���PA0/J0+��PB0/J0-���������INPUT8 ��INPUT7					//
//		ѡ��00:0 ��01:1 ��10:2 ��11:3 ��								//
//	4 0 ���PA0/J0+��PB0/J0-����axis �����								//
//	5 1 ���PA1/J1+��PB1/J1-����axis �����								//
//	6 2 ���PA2/J2+��PB2/J2-����axis �����								//
//	7 3 ���PA2/J2+��PB2/J2-����axis �����								//
// pulse: �����˶������������,ֻ������Ϊ��ֵ							//
// MaxVel: ��������ٶ�ֻ������Ϊ��ֵ									//
// ��ȷ����ERR_NoError ���󷵻�ERR_Error								//
//////////////////////////////////////////////////////////////////////////

typedef enum tagManualMode {
	ManualMode_NoExternalPulse		= 0,	// ��ֹ�ⲿ��������
	ManualMode_AxisSel_PJN			= 1,	// ����(���n)�� PAn/Jn+��PBn/Jn-������Ƶ�n �����
	ManualMode_OptSel0_IPT78		= 2,	// ��0 ���PA0/J0+��PB0/J0-����,�����INPUT8 ��INPUT7ѡ��	
	ManualMode_OptSel1_IPT78		= 3,	// ��1 ���PA0/J0+��PB0/J0-���������INPUT8 ��INPUT7ѡ��
	ManualMode_OptSel_PJ0			= 4,	// 0 ���PA0/J0+��PB0/J0-����axis �����
	ManualMode_OptSel_PJ1			= 5,	// 1 ���PA1/J1+��PB1/J1-����axis �����
	ManualMode_OptSel_PJ2			= 6,	// 2 ���PA2/J2+��PB2/J2-����axis �����
	ManualMode_OptSel_PJ3			= 7		// 3 ���PA3/J3+��PB3/J3-����axis �����
} ManualMode;

//////////////////////////////////////////////////////////////////////////
// �˶�״̬���
// DWORD d3000_check_done(short axis)
// d3000_check_done ������������˶����ƿ����˶�״̬

typedef enum tagMotionCheck {
	MotionCheck_NoCard		= 0, // �޿�	
	MotionCheck_Moving		= 1, // �˶���
	MotionCheck_PulseOver	= 2, // ����������������
	MotionCheck_CmdStop		= 3, // ָ��ֹͣ
	MotionCheck_LimitStop	= 4, // ��λֹͣ
	MotionCheck_OrgStop		= 5, // ��ԭ���˶�ֹͣ
	MotionCheck_EzStop		= 6, // �ҵ�EZ�ź�ֹͣ
	MotionCheck_AlmValid	= 7, // Alarm�ź���Чֹͣ
	MotionCheck_EmgStop		= 8  // �ⲿEMG�ź�ֹͣ
} MotionCheck;

//////////////////////////////////////////////////////////////////////////
// ר��I/O�ӿں���														//
// d3000_set_alm ����ALARM �ź��Ƿ�ʹ�ܼ���Ч��ƽ���ALARM �ź�����
// ���б�����Ϊʹ�ܵ�ALARM �ź���Чʱ����������ֹͣ
// d3000_set_el �趨EL �źŵ���Ч��ƽ����Ӧģʽ
// d3000_set_inpINP �ź��Ƿ�ʹ���Լ���Ч��ƽ
// d3000_get_axis_status ��ȡָ���������ר���ź�״̬
// DWORD d3000_set_alm(short axis, short alm_mode, short alm_logic)
// DWORD d3000_set_el(short axis, shortel_select, short el_mode, 
//	short el_logic)
// DWORD d3000_set_inp(short axis, short inp_mode, short inp_logic)
// DWORD d3000_get_axis_status(short axis)
// alm_mode �Ƿ�ʹ��ALARM �ź�0 ��ʹ��1 ʹ��
// alm_logic ALARM �źŵ���Ч��ƽ0 �͵�ƽ��Ч1 �ߵ�ƽ��Ч
// el_select ������λѡ��: 0 ����λ1 ����λ
// el_mode ������λԪ����ʱ��Ӧģʽ0 ����ֹͣ 1 ����ֹͣ
// el_logic EL �źŵ���Ч��ƽ0 �͵�ƽ��Ч1 �ߵ�ƽ��Ч
// inp_mode �Ƿ�ʹ��INP �ź�0 ��ʹ��1 ʹ��
// inp_logic 1INP �źŵ���Ч��ƽ0 �͵�ƽ��Ч 1�ߵ�ƽ��Ч

typedef enum tagAlmMode {
	AlmMode_Disable = 0,
	AlmMode_Enable	= 1
} AlmMode;

typedef enum tagELSlect {
	ELSlect_LimitPlus		= 0,	// ������λѡ��: 0 ����λ1 ����λ
	ELSlect_LimitMinus		= 1		// ������λѡ��: 0 ����λ1 ����λ
} ELSelect;

typedef enum tagELMode {
	ELMode_Stop		= 0,	// ������λԪ����ʱ��Ӧģʽ0 ����ֹͣ 1 ����ֹͣ
	ELMode_DecStop	= 1		// ������λԪ����ʱ��Ӧģʽ0 ����ֹͣ 1 ����ֹͣ
} ELMode;

typedef enum tagInpMode {
	InpMode_Disable = 0,	// �Ƿ�ʹ��INP �ź�0 ��ʹ��1 ʹ��
	InpMode_Enable	= 1		// �Ƿ�ʹ��INP �ź�0 ��ʹ��1 ʹ��
} InpMode;

typedef enum tagAxisStatus {
	AxisStatus_SLMT_Plus		= 0,	//���������λ״̬
	AxisStatus_SLMT_Minus		= 1,	//���������λ״̬
	AxisStatus_EL_Plus			= 2,	//������λ״̬
	AxisStatus_EL_Minus			= 3,	//������λ״̬
	AxisStatus_AlmStatus		= 4,	//ALARM�ź�״̬
	AxisStatus_EmgStop			= 5,	//����ͣ״̬
	AxisStatus_EzLevel			= 6,	//EZ�����ƽ
	AxisStatus_Reserve1			= 7,	//����
	AxisStatus_Reserve2			= 8,	//����
	AxisStatus_OrgLevel			= 9,	//ORG�ź������ƽ
	AxisStatus_HwJogLevel_PAJ	= 10,	//PA/Jn+ ���ֺ�JOG�����ƽ Hand wheel
	AxisStatus_HwJogLevel_PBJ	= 11,	//nPB/J- ���ֺ�JOG�����ƽ
	AxisStatus_InpLevel			= 12,	//INP INP�����ƽ
	AxisStatus_AlmLevel			= 13	//ALM_LEVEL ALARM�źŵ�ƽ

} AxisStatus;



//////////////////////////////////////////////////////////////////////////

// typedef enum tagErrorStatus {
// 	ERR_NOERR = 0,			//�ɹ�
// 	ERR_UNKNOWN	= 1,		//δ֪����
// 	ERR_PARAERR = 2,			//��������
// 	ERR_TIMEOUT	= 3,		//������ʱ
// 	ERR_CONTROLLERBUSY = 4,			//���ƿ�״̬æ
// 	ERR_CONTILINE = 6,		//�����岹����
// 	ERR_SENDERR = 10,			//���ݴ����������PCI��λ�Ƿ��ɶ�
// 	ERR_FIRMWARE_INVALID_PARA = 20,		//���������ز�������
// 	ERR_FIRMWARE_STATE_ERR = 22,			//���������ص�ǰ״̬���������
// 	ERR_FIRMWARE_CARD_NOT_SUPPORT = 24		//��������֧�ֵĹ���
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
		Cylinder_No1			= 0,		// ������	
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


// �ٶȱ���   ���Ƶ�λ0.01mm  ���浥λcm
#define	fRateX		(100*10)			//һ��mm����������	ÿת26.67mm		(10000/26.67=375)
#define	fRateY		(100*10)			//һ��mm����������	ÿת36.67mm		(10000/36.67=272.7)
#define	fRateC		(100)			//һ�Ȱ���������	���ٱ�1:6		(9000/(360/6)=150)

// λ�ñ���		���ݵ�λ0.1mm��0.025��  ���Ƶ�λ0.01mm
#define fPRate		2.5		// 0.025ʱ����Ϊ2.5
//#define fPRate	10		// 0.025ʱ����Ϊ2.5
#define fPRateC		100		// ���ݵ�λ����   ���Ƶ�λ0.01��

#define Offset_C_X		(-5000)	//��λ0.01mm
#define Offset_C_Y		(4700)	
#define Offset_P_X		(-13800)	
#define Offset_P_Y		(10700)	

#define PumpTime		300

enum {
	MOTION_CARD_MOVE = 0,    //����
	MOTION_CARD_PAUSE = 1,   //��ͣ
	MOTION_CARD_STOP = 2,    //ֹͣ
};

enum {
	MOTION_RELATIVE = 0,    //���λ��
	MOTION_ABSOLUTE = 1,   //����λ��
};



//////////////////////////////////////////////////////////////////////////
long GetFileInfo(FILE *pfile);




