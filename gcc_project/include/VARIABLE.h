/*===================================================================================

File Name:       VARIABLE.H

Description:    Variable file for  VSC-HVDC control
          		
Originator:    XIAN yuneng dianli

==========================================================================================================  */

#ifndef VARIABLE_H
#define VARIABLE_H
/*==========================================================================
1        ״̬��           Grid_State    
2	     ������ 	      Grid_Faults
3	     ������	          Grid_Alarm
===========================================================================*/

//---------------------------------------------------------------------------

//===============================================================//
#include "Solar_F.h"

CLARKE clarke1 = CLARKE_DEFAULTS;     //���ಢ������CLARKE�任
CLARKE clarke2 = CLARKE_DEFAULTS;     //���ཻ����ѹCLARKE�任
iCLARKE_F iclarke1;                   // ���ಢ����������CLARKE���任
park_PN park1 = park_PN_DEFAULTS;     // 1#�ŵ���˫��ת�任
park_PN park_pll = park_PN_DEFAULTS;  // ���໷˫��ת�任
IPARK ipark1 = IPARK_DEFAULTS;        // ���ಢ����������PARK���任
RAMPGEN rg1 = RAMPGEN_DEFAULTS;
SVGENDQ svgen_dq1 = SVGENDQ_DEFAULTS; // SVPWM���Ʒ�ʽ
INTEGRAL integral1 = INTEGRAL_DEFAULTS;

CNTL_PI_F pi1_id;                     // d������ڻ�������
CNTL_PI_F pi1_iq;                     // q������ڻ�������
CNTL_PI_F pi1_Vdc;                    // ��ѹ�⻷������
CNTL_PI_F pi1_pll;                    // ���໷������ 

//Sys_State_Type sys_state;

//=====ģ��������======//
float Ia_Sample;
float Ib_Sample;
float Ic_Sample; 
float Vab_Sample;
float Vbc_Sample;
float Vca_Sample; 
float Vdc_Sample;
float Vdc_Sample_mid;
float Vdc_Sample_init;
int Vdc_Sample_counter;

float Grid_Va_Instant;
float Grid_Vb_Instant;
float Grid_Vc_Instant;
float Grid_Act_Power;
float Grid_React_Power;
int Avg_PQ_i = 0;
float Avg_P_Temp;
float Avg_Q_Temp;


//=====ͨѶ����ң�ؼ�ң����=====//
unsigned int LEVEL;
unsigned int Run_Mode;
float Grid_m;
float Id_ref;
float Iq_ref;
float Udc_ref;
unsigned int Start_CMD = 0;
//unsigned int RemoteOrLocal = 0;
unsigned int Stop_CMD;
unsigned int Reset_CMD; 
//==============================//

//=====ͨѶ���ң�⼰ң����=====//
unsigned int Grid_Ia;
unsigned int Grid_Ib;
unsigned int Grid_Ic;
unsigned int Grid_Vab;
unsigned int Grid_Vbc;
unsigned int Grid_Vca;
unsigned int Udc;
unsigned int Grid_Freq = 0;
int Grid_Pac;
int Grid_Qac;
int Frq_i = 0;
float Frq_Avg_Tmp = 0;
float Frq_Avg = 0;


//==============================//

//=========�����м����=========//
float Id_ref_init;
float Iq_ref_init;
float Id_ref_step;
float Iq_ref_step;
float Udc_ref_init;
float Udc_ref_step;
float theta;
float theta_line;
float theta_park;

unsigned int Sys_Run;
unsigned int Reset_onetime_flag = 0;

//==============================// 

//==============================//

// AC������d��PI 
float pi1_id_Kp = 0.15;//0.4489              
float pi1_id_Ki = 0.0164;//0.00308
// AC������q��PI
float pi1_iq_Kp = 0.15;//0.4489
float pi1_iq_Ki = 0.0164;//0.00308
// ��ѹ��PI
float pi1_Vdc_Kp = 0.5;//0.5
float pi1_Vdc_Ki= 0.0033;//0.003

float Delay_Second;

long Delay_Second_i;

int Delay_End;

//==============================//

struct Grid_State_Bits
{                                              
   unsigned int        STOP:1;                  //����ͣ��
   unsigned int        FAULT:1;                 //����
   unsigned int        START:1;                 //������
   unsigned int		   RUN:1;                   //����
   unsigned int        VOLTS_MODE:1;            //��ѹģʽ
   unsigned int        CURRENT_MODE:1;          //����ģʽ
   unsigned int        SVG_MODE:1;            //SVGģʽ
   unsigned int        LOCAL_CTR:1;            //Զ�̿���
   unsigned int        REMOTE_CTR:1;           //���ؿ���
   unsigned int        Q_SVG:1;            //���޹�����
   unsigned int        Pn_SVG:1;            //�㹦������
   unsigned int        Auto_SVG:1;           //�Զ��޹�����
   unsigned int		   Reserved_1:4;		    //����
};

union Grid_State 
{
   unsigned int              all;
   struct Grid_State_Bits  bit;
};  

struct Grid_Faults_Bits
 {                                              
   unsigned int        Ia_OVER:1;                 //a�����
   unsigned int        Ib_OVER:1;                 //b�����
   unsigned int        Ic_OVER:1;                 //c�����
   unsigned int		   Idc_OVER:1;                //ֱ������
   unsigned int		   Uab_OVER:1;                //Uab��ѹ
   unsigned int        Ubc_OVER:1;                //Ubc��ѹ
   unsigned int        Uca_OVER:1;                //Uca��ѹ
   unsigned int        Udc_Up_OVER:1;             //ֱ����ĸ�߹�ѹ
   unsigned int        Udc_Down_OVER:1;           //ֱ����ĸ�߹�ѹ
   unsigned int        A_Driv:1;                 //A����������
   unsigned int        B_Driv:1;                //B����������
   unsigned int        C_Driv:1;               //C����������
   unsigned int        CONTACT_Fault:1;          //�Ӵ����쳣
   unsigned int		   Reserved_1:3;	          //����1   	  	
};

union Grid_Faults
{
   unsigned int                 all;
   struct Grid_Faults_Bits  bit;
};  
//Start Grid_S_Faults_1_Bits bit definitions:
struct Grid_S_Faults_1_Bits
 {                                              
   unsigned int        Ia:1;                  //a�����
   unsigned int        Ib:1;                  //b�����
   unsigned int        Ic:1;                  //c�����
   unsigned int		   Idc1:1;                //ֱ���������
   unsigned int        solft_Fault:1;         //����ʧ��
   unsigned int        UNBALANCE_CURRENT:1;    //������ƽ��
   unsigned int        COM_Fault:1;            //ͨѶ����
   unsigned int        Heat_Fault:1;            //ɢ��������
   unsigned int        Local_Emrgence:1;        //���ؼ�ͣ
   unsigned int		   Reserved_1:7;	        //����1    	  	  	
};

union Grid_S_Faults_1
{
   unsigned int                 all;
   struct Grid_S_Faults_1_Bits  bit;
};  
//End Grid_S_Faults_1_Bits bit definitions.

//Start Grid_S_Faults_2_Bits bit definitions:
struct Grid_S_Faults_2_Bits
 {                                              
   unsigned int        OVER_FRQ:1;              //������ѹ��Ƶ
   unsigned int        UNDER_FRQ:1;             //������ѹǷƵ
   unsigned int        OVER_Uab:1;              //uab��ѹ
   unsigned int		   OVER_Ubc:1;              //Ubc��ѹ
   unsigned int		   OVER_Uca:1;				//Uca��ѹ
   unsigned int		   UNDER_Uab:1;	            //UabǷѹ
   unsigned int        UNDER_Ubc:1;             //UbcǷѹ
   unsigned int		   UNDER_Uca:1;             //UcaǷѹ
   unsigned int		   UNBALANCE_Volt:1;		//������ѹ��ƽ��
   unsigned int		   UNBALANCE_Udc:1;         //ֱ��ĸ�߲�ƽ��
   unsigned int		   UNDER_Udc:1;	            //UdcǷѹ
   unsigned int        OVER_Udc_UP:1;            //ֱ����ĸ�߹�ѹ
   unsigned int		   OVER_Udc_DOWN:1;	    //ֱ����ĸ�߹�ѹ
   unsigned int		   OVER_POWVER:1;	    //����
   unsigned int		   Udc_Reverse:1;	        //ֱ���ӷ� 
   unsigned int		   PHASE:1;	        //�����������
};

union Grid_S_Faults_2
{
   unsigned int                 all;
   struct Grid_S_Faults_2_Bits  bit;
};  

struct Grid_Alarm_Bits
 {                                              
   unsigned int        LOAD:1;                  //���������
   unsigned int		   Reserved_1:15;	        //����1   	  	
};

union Grid_Alarm
{
   unsigned int            all;
   struct Grid_Alarm_Bits  bit;
};  

struct INV15_States 
{
   union Grid_State       grid_state;
   union Grid_Faults      grid_faults;                   
   union Grid_Alarm       grid_alarm; 
   union Grid_S_Faults_1  grid_s_fault1; 
   union Grid_S_Faults_2  grid_s_fault2; 
};

volatile struct INV15_States SYS_Info; //Info: Information

typedef enum _Sys_State
{
	State_Stopping = 10,                // ͣ������״̬
	State_Stopped,                      // ����ͣ����?
	State_Starting,                     // �������״̬
	State_Reset,                        // ��λ״̬
	State_SoloStage_Running,            // ��״̬
	State_DualStage_Running,            // ˫������״̬
	State_Error,                        // ����ͣ��״̬
	State_Standby,                      // ����״̬
    State_Running                       //��������״̬
}Sys_State_Type;   

Sys_State_Type sys_state;

//=====================//

#endif 
//===========================================================================
// No more.
//===========================================================================
