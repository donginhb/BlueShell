/*===================================================================================

System Name:    15kW PV Grid Connected Inverter

File Name:    STATE.H

Description:    STATE parameters file for 15kW PV Grid Connected Inverter control
          		
Originator:    Converter Control Group--XAXJ

=====================================================================================
 History:
 ʱ��       �޸�ԭ��                                �޸�����                                  �޸���                                    
------------------------------------------------------------------------------------------------------
 2014-5-7	 Release	Rev 1.0                                                               �ƻ�

==========================================================================================================  */

#ifndef STATE_H
#define STATE_H

/*==========================================================================
1        ״̬��1          Grid_State_1
2        ״̬��2          Grid_State_2
3        ״̬��3          Grid_State_3
4	   Ӳ��������1	      Grid_H_Faults_1
5	   Ӳ��������2	      Grid_H_Faults_2
6	   ���������1	      Grid_S_Faults_1
7	   ���������2	      Grid_S_Faults_2
8      ���������3        Grid_S_Faults_3
9	   ���ع���	          Sever_Faults  
10       ������	          Grid_Alarm
11        ����            DI_State
12        ����            DO_State
===========================================================================*/

//---------------------------------------------------------------------------
//Start Grid_State_1_Bits bit definitions:
struct Grid_State_1_Bits
{                                              
   unsigned int        STOP:1;                  //���������ͣ��
   unsigned int        FAULT:1;                 //���������ͣ��
   unsigned int        START:1;                 //�����������
   unsigned int		   RUN:1;                   //�������������
   unsigned int		   WARN:1;                  //������澯����
   unsigned int		   STANDBY:1;				//���������
   unsigned int        Reserved_1:10;            //����1
 //  unsigned int        LOCAL:1;                 //���ؿ���
 //  unsigned int        REMOTE:1;                //Զ�̿���
 //  unsigned int        Anti_Islanding:1;        //���µ�״̬   1 ʹ��  0 ����
 //  unsigned int        START_CMD:1;             //���ػ�״̬   1 ����  0 �ػ�
 //  unsigned int        Alone_mode: 1;
 //  unsigned int        Parrel_mode: 1;
 //  unsigned int        PV1_put: 1;
 //  unsigned int        PV2_put: 1;
  // unsigned int        PV3_put: 1;
 //  unsigned int        PV4_put: 1;
 //  unsigned int		   Insulation_Detect:1;	        //��Ե���״̬ 1 ʹ��  0 ����
 //  unsigned int		   RCD_Detect:1;	           //©�������״̬ 1 ʹ��  0 ����
};

union Grid_State_1 
{
   unsigned int              all;
   struct Grid_State_1_Bits  bit;
};  
//End Grid_State_1_Bits bit definitions.

//Start Grid_State_2_Bits bit definitions:
struct Grid_State_2_Bits
 { 
   unsigned int		   I_Boost_MODE:1;	        //Boost����ģʽ
   unsigned int		   V_MODE:1;                //NPC���ѹģʽ
   unsigned int		   I_MODE:1;				//NPC�����ģʽ                                             
   //unsigned int        PV1Connect:1;            //PV1����
   unsigned int	       Mppt;                    //mpptģʽ
   unsigned int	       Svg;                    //Svgģʽ
   unsigned int        Islanding_Enable;       //�µ�ʹ��
   unsigned int        Lvrt_Enable;            //�ʹ�ʹ��
   unsigned int        START_CMD:1;             //���ػ�״̬   1 ����  0 �ػ�
   unsigned int        Alone_mode: 1;           //����״̬
   unsigned int        Parrel_mode: 1;          //����״̬
   unsigned int        PV1_put:1;            //boost1����
   unsigned int        PV2_put:1;            //boost2����
   unsigned int        PV3_put:1;            //boost3����
   unsigned int        PV4_put:1;            //boost4����
   unsigned int		   Insulation_Detect:1;	        //��Ե���״̬ 1 ʹ��  0 ����
   unsigned int        RCD_Detect:1;	           //©�������״̬ 1 ʹ��  0 ����
   //unsigned int      PV2Connect:1;            //PV2����
   // unsigned int        PV3Connect:1;            //PV3����
   //unsigned int		   CONTACT:1;	            //���Ӵ����պ�
   //unsigned int		   FAN:1;	                //����Ӵ����պ�
   	
};

union Grid_State_2
{
   unsigned int              all;
   struct Grid_State_2_Bits  bit;
};  
struct Grid_State_3_Bits
 {                                              
   unsigned int        REMOTE:1;                //Զ�̿���
   unsigned int        LOCAL:1;                 //���ؿ���
   unsigned int        Dispatch_Q:1;            //�޹����ʵ���
   unsigned int		   PF_Set:1;                //������������
   unsigned int		   P_Set_PCT:1;				//�й����ʰٷֱȵ���
   unsigned int		   P_Set_R:1;	            //�й�����ֵ����
   unsigned int		   Reserved_1:10;	        //����1   	  	
};

union Grid_State_3
{
   unsigned int              all;
   struct Grid_State_3_Bits  bit;
};  
//End Grid_State_2_Bits bit definitions.

//Start Grid_H_Faults_1_Bits bit definitions:
struct Grid_H_Faults_1_Bits
 {                                              
   unsigned int        Ia:1;                   //a���������
   unsigned int        Ib:1;                   //b���������
   unsigned int        Ic:1;                   //c���������
   unsigned int		   Uab:1;                  //Uab��ѹ
   unsigned int		   Ubc:1;				   //Ubc��ѹ
   unsigned int		   Uca:1;	               //Uca��ѹ
//   unsigned int        Upv1:1;                 //������й�ѹ1
//   unsigned int        Upv2:1;                 //������й�ѹ2
//   unsigned int        Upv3:1;                 //������й�ѹ3
   unsigned int        Idc1:1;                 //boost�������1
   unsigned int        Idc2:1;                 //ֱ���������2
   unsigned int        Idc3:1;                 //ֱ���������3
   unsigned int        Idc4:1;                 //ֱ���������4
   unsigned int        Udclink:1;              //ֱ��ĸ�ߵ�ѹ��ѹ
   unsigned int        Udcdown:1;              //ֱ����ĸ�ߵ�ѹ��ѹ
   unsigned int		   Reserved_1:4;	      //����1   
  // unsigned int        TBoost:1;               //boostɢ��������
  // unsigned int        TNPC:1; 	  	           //NPCɢ��������
};

union Grid_H_Faults_1
{
   unsigned int                 all;
   struct Grid_H_Faults_1_Bits  bit;
};  
//End Grid_H_Faults_1_Bits bit definitions.

//Start Grid_H_Faults_2_Bits bit definitions:
struct Grid_H_Faults_2_Bits
 {                                              
   unsigned int        NPCADriv:1;            //A����������
   unsigned int        NPCBDriv:1;            //B����������
   unsigned int        NPCCDriv:1;            //C����������
   unsigned int		   Boost1Driv:1;          //Boost1��������
 //  unsigned int		   Boost2Driv:1;	      //Boost2��������
 //  unsigned int		   Boost3Driv:1;	      //Boost3��������
   unsigned int		   I_Two:1;                //���ι�������
   unsigned int		   Lvrt_Handshake:1;       //LVRT���ֹ���,�����������ʧ��
   unsigned int		   Reserved_1:10;	      //����1   	  	
};

union Grid_H_Faults_2
{
   unsigned int                 all;
   struct Grid_H_Faults_2_Bits  bit;
};  
//End Grid_H_Faults_2_Bits bit definitions.

//Start Grid_S_Faults_1_Bits bit definitions:
struct Grid_S_Faults_1_Bits
 {                                              
   unsigned int        Ia:1;                  //a�����
   unsigned int        Ib:1;                  //b�����
   unsigned int        Ic:1;                  //c�����
   unsigned int		   Idc1:1;                //ֱ���������1
   unsigned int        Idc2:1;                //ֱ���������2
   unsigned int        Idc3:1;                //ֱ���������3
   unsigned int        Idc4:1;                //ֱ���������3
   unsigned int        Udclink:1;             //ֱ��ĸ�ߵ�ѹ��ѹ
   unsigned int        Udcdown:1;             //ֱ����ĸ�ߵ�ѹ��ѹ
   unsigned int        Upv1:1;                //boost1�����ѹ
   unsigned int        Upv2:1;                //boost2�����ѹ
   unsigned int        Upv3:1;                //boost3�����ѹ
   unsigned int        Upv4:1;                //boost4�����ѹ
   unsigned int        TBoost:1;              //Boostɢ��������
   unsigned int        TNPC:1;                //NPCɢ��������
   unsigned int        Unp:1;	              //�е��λ��ƽ��
	  	
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
   unsigned int		   ISLAND:1;				//�µ�����
   unsigned int		   INSULATE_RESISTANCE:1;   //��Ե������
   unsigned int        RESIDUAL_CURRENT:1;      //©��������
   unsigned int		   UNBALANCE_CURRENT:1;	    //������ƽ��
   unsigned int		   LVRT_Fault:1;	        //�ʹ����� 
   unsigned int		   Reserved_1:3;	        //����1    	  	  	
};

union Grid_S_Faults_2
{
   unsigned int                 all;
   struct Grid_S_Faults_2_Bits  bit;
};  
struct Grid_S_Faults_3_Bits
 {                                              
   unsigned int        Connect:1;              //������ѹ��Ƶ
   unsigned int		   Reserved_1:15;	        //����1    	  	  	
};

union Grid_S_Faults_3
{
   unsigned int                 all;
   struct Grid_S_Faults_3_Bits  bit;
};  
//End Grid_S_Faults_2_Bits bit definitions.

//Start Grid_Alarm_Bits bit definitions:
struct Grid_Alarm_Bits
 {                                              
   unsigned int        LOAD:1;                  //����
   unsigned int        U_unbalance;             //��ѹ��ƽ��
   unsigned int        STRING1:1;               //�鴮1�쳣
   unsigned int		   STRING2:1;               //�鴮2�쳣
   unsigned int		   STRING3:1;				//�鴮3�쳣
   unsigned int		   STRING4:1;	            //�鴮4�쳣
   unsigned int        STRING5:1;               //�鴮5�쳣
   unsigned int        STRING6:1;               //�鴮6�쳣
   unsigned int        STRING7:1;               //�鴮7�쳣
   unsigned int		   STRING8:1;               //�鴮8�쳣
   unsigned int		   STRING9:1;				//�鴮9�쳣
   unsigned int		   STRING10:1;	            //�鴮10�쳣
   unsigned int        STRING11:1;               //�鴮11�쳣
   unsigned int        STRING12:1;               //�鴮12�쳣
   unsigned int		   Reserved_1:2;	        //����1   	  	
};

union Grid_Alarm
{
   unsigned int            all;
   struct Grid_Alarm_Bits  bit;
};  
//End Grid_Alarm_Bits bit definitions.

//Start Sever_Faults_Bits bit definitions:
struct Sever_Faults_Bits
{                                              
   unsigned int        PHASE:1;                 //�������
//   unsigned int        PV_Array_Reverse:1;
   unsigned int		   Reserved_1:15;	        //����1   	  	
};

union Sever_Faults
{
   unsigned int              all;
   struct Sever_Faults_Bits  bit;
};  
//End Sever_Faults_Bits bit definitions.

//Start DI_State_Bits bit definitions:
struct DI_State_Bits
 {                                              
   unsigned int		   Reserved_1:16;	        //����1 	  	
};

union DI_State
{
   unsigned int            all;
   struct DI_State_Bits    bit;
};  
//End DI_State_Bits bit definitions.

//Start DO_State_Bits bit definitions:
struct DO_State_Bits
 { 
   unsigned int        Pwm:1;                     //pwm�������                                             
   unsigned int        CONTACT1:1;             //�����Ӵ���1
   unsigned int        CONTACT2:1;             //�����Ӵ���2
   unsigned int        FAN1:1;                  //����Ӵ���1
   unsigned int        FAN2:1;           //����Ӵ���2
   unsigned int		   FAN3:1;	       //����Ӵ���3
   unsigned int		   FAN4:1;	       //����Ӵ���4
   unsigned int        DC_Relay1:1;      //ֱ���̵���1
   unsigned int        DC_Relay2:1;      //ֱ���̵���2
   unsigned int        DC_Relay3:1;      //ֱ���̵���3
   unsigned int        DC_Relay4:1;      //ֱ���̵���4
   unsigned int		   INSULATE:1;             //��Ե���
   unsigned int		   Reserved_1:4;	       //����
   	  	
};

union DO_State
{
   unsigned int            all;
   struct DO_State_Bits    bit;
};  
//End DO_State_Bits bit definitions.

//---------------------------------------------------------------------------

// INV15_States Head File:
//

struct INV15_States 
{
   union Grid_State_1       grid_state_1;
   union Grid_State_2       grid_state_2; 
   union Grid_State_3       grid_state_3; 
   union Grid_H_Faults_1    grid_H_faults_1;        
   union Grid_H_Faults_2    grid_H_faults_2;       
   union Grid_S_Faults_1    grid_S_faults_1;       
   union Grid_S_Faults_2    grid_S_faults_2; 
   union Grid_S_Faults_3    grid_S_faults_3;            
   union Grid_Alarm         grid_alarm;              
   union Sever_Faults       sever_faults;       
   union DI_State           DI_state;        
   union DO_State           DO_state;       
};

volatile struct INV15_States SYS_Info; //Info: Information

#endif 
//===========================================================================
// No more.
//===========================================================================
