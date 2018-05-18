/*===================================================================================

File Name:       VARIABLE.H

Description:    Variable file for  VSC-HVDC control
          		
Originator:    XIAN yuneng dianli

==========================================================================================================  */

#ifndef VARIABLE_H
#define VARIABLE_H
/*==========================================================================
1        ×´Ì¬×Ö           Grid_State    
2	     ¹ÊÕÏ×Ö 	      Grid_Faults
3	     ±¨¾¯×Ö	          Grid_Alarm
===========================================================================*/

//---------------------------------------------------------------------------

//===============================================================//
#include "Solar_F.h"

CLARKE clarke1 = CLARKE_DEFAULTS;     //ÈıÏà²¢ÍøµçÁ÷CLARKE±ä»»
CLARKE clarke2 = CLARKE_DEFAULTS;     //ÈıÏà½»Á÷µçÑ¹CLARKE±ä»»
iCLARKE_F iclarke1;                   // ÈıÏà²¢ÍøµçÁ÷ÕıĞòCLARKE·´±ä»»
park_PN park1 = park_PN_DEFAULTS;     // 1#ÇÅµçÁ÷Ë«Ğı×ª±ä»»
park_PN park_pll = park_PN_DEFAULTS;  // ËøÏà»·Ë«Ğı×ª±ä»»
IPARK ipark1 = IPARK_DEFAULTS;        // ÈıÏà²¢ÍøµçÁ÷ÕıĞòPARK·´±ä»»
RAMPGEN rg1 = RAMPGEN_DEFAULTS;
SVGENDQ svgen_dq1 = SVGENDQ_DEFAULTS; // SVPWMµ÷ÖÆ·½Ê½
INTEGRAL integral1 = INTEGRAL_DEFAULTS;

CNTL_PI_F pi1_id;                     // dÖáµçÁ÷ÄÚ»·µ÷½ÚÆ÷
CNTL_PI_F pi1_iq;                     // qÖáµçÁ÷ÄÚ»·µ÷½ÚÆ÷
CNTL_PI_F pi1_Vdc;                    // µçÑ¹Íâ»·µ÷½ÚÆ÷
CNTL_PI_F pi1_pll;                    // ËøÏà»·µ÷½ÚÆ÷ 

//Sys_State_Type sys_state;

//=====Ä£ÄâÁ¿²ÉÑù======//
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


//=====Í¨Ñ¶ÊäÈëÒ£¿Ø¼°Ò£µ÷Á¿=====//
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

//=====Í¨Ñ¶Êä³öÒ£²â¼°Ò£ĞÅÁ¿=====//
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

//=========³ÌĞòÖĞ¼ä±äÁ¿=========//
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

// ACµçÁ÷»·dÖáPI 
float pi1_id_Kp = 0.15;//0.4489              
float pi1_id_Ki = 0.0164;//0.00308
// ACµçÁ÷»·qÖáPI
float pi1_iq_Kp = 0.15;//0.4489
float pi1_iq_Ki = 0.0164;//0.00308
// µçÑ¹»·PI
float pi1_Vdc_Kp = 0.5;//0.5
float pi1_Vdc_Ki= 0.0033;//0.003

float Delay_Second;

long Delay_Second_i;

int Delay_End;

//==============================//

struct Grid_State_Bits
{                                              
   unsigned int        STOP:1;                  //Õı³£Í£»ú
   unsigned int        FAULT:1;                 //¹ÊÕÏ
   unsigned int        START:1;                 //Æô¶¯ÖĞ
   unsigned int		   RUN:1;                   //ÔËĞĞ
   unsigned int        VOLTS_MODE:1;            //ºãÑ¹Ä£Ê½
   unsigned int        CURRENT_MODE:1;          //ºãÁ÷Ä£Ê½
   unsigned int        SVG_MODE:1;            //SVGÄ£Ê½
   unsigned int        LOCAL_CTR:1;            //Ô¶³Ì¿ØÖÆ
   unsigned int        REMOTE_CTR:1;           //±¾µØ¿ØÖÆ
   unsigned int        Q_SVG:1;            //ºãÎŞ¹¦¹¦ÂÊ
   unsigned int        Pn_SVG:1;            //ºã¹¦ÂÊÒòÊı
   unsigned int        Auto_SVG:1;           //×Ô¶¯ÎŞ¹¦²¹³¥
   unsigned int		   Reserved_1:4;		    //±¸ÓÃ
};

union Grid_State 
{
   unsigned int              all;
   struct Grid_State_Bits  bit;
};  

struct Grid_Faults_Bits
 {                                              
   unsigned int        Ia_OVER:1;                 //aÏà¹ıÁ÷
   unsigned int        Ib_OVER:1;                 //bÏà¹ıÁ÷
   unsigned int        Ic_OVER:1;                 //cÏà¹ıÁ÷
   unsigned int		   Idc_OVER:1;                //Ö±Á÷¹ıÁ÷
   unsigned int		   Uab_OVER:1;                //Uab¹ıÑ¹
   unsigned int        Ubc_OVER:1;                //Ubc¹ıÑ¹
   unsigned int        Uca_OVER:1;                //Uca¹ıÑ¹
   unsigned int        Udc_Up_OVER:1;             //Ö±Á÷ÉÏÄ¸Ïß¹ıÑ¹
   unsigned int        Udc_Down_OVER:1;           //Ö±Á÷ÏÂÄ¸Ïß¹ıÑ¹
   unsigned int        A_Driv:1;                 //AÇÅÇı¶¯¹ÊÕÏ
   unsigned int        B_Driv:1;                //BÇÅÇı¶¯¹ÊÕÏ
   unsigned int        C_Driv:1;               //CÇÅÇı¶¯¹ÊÕÏ
   unsigned int        CONTACT_Fault:1;          //½Ó´¥Æ÷Òì³£
   unsigned int		   Reserved_1:3;	          //±¸ÓÃ1   	  	
};

union Grid_Faults
{
   unsigned int                 all;
   struct Grid_Faults_Bits  bit;
};  
//Start Grid_S_Faults_1_Bits bit definitions:
struct Grid_S_Faults_1_Bits
 {                                              
   unsigned int        Ia:1;                  //aÏà¹ıÁ÷
   unsigned int        Ib:1;                  //bÏà¹ıÁ÷
   unsigned int        Ic:1;                  //cÏà¹ıÁ÷
   unsigned int		   Idc1:1;                //Ö±Á÷ÊäÈë¹ıÁ÷
   unsigned int        solft_Fault:1;         //ÈíÆôÊ§°Ü
   unsigned int        UNBALANCE_CURRENT:1;    //µçÁ÷²»Æ½ºâ
   unsigned int        COM_Fault:1;            //Í¨Ñ¶¹ÊÕÏ
   unsigned int        Heat_Fault:1;            //É¢ÈÈÆ÷¹ÊÕÏ
   unsigned int        Local_Emrgence:1;        //±¾µØ¼±Í£
   unsigned int		   Reserved_1:7;	        //±¸ÓÃ1    	  	  	
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
   unsigned int        OVER_FRQ:1;              //µçÍøµçÑ¹¹ıÆµ
   unsigned int        UNDER_FRQ:1;             //µçÍøµçÑ¹Ç·Æµ
   unsigned int        OVER_Uab:1;              //uab¹ıÑ¹
   unsigned int		   OVER_Ubc:1;              //Ubc¹ıÑ¹
   unsigned int		   OVER_Uca:1;				//Uca¹ıÑ¹
   unsigned int		   UNDER_Uab:1;	            //UabÇ·Ñ¹
   unsigned int        UNDER_Ubc:1;             //UbcÇ·Ñ¹
   unsigned int		   UNDER_Uca:1;             //UcaÇ·Ñ¹
   unsigned int		   UNBALANCE_Volt:1;		//½»Á÷µçÑ¹²»Æ½ºâ
   unsigned int		   UNBALANCE_Udc:1;         //Ö±Á÷Ä¸Ïß²»Æ½ºâ
   unsigned int		   UNDER_Udc:1;	            //UdcÇ·Ñ¹
   unsigned int        OVER_Udc_UP:1;            //Ö±Á÷ÉÏÄ¸Ïß¹ıÑ¹
   unsigned int		   OVER_Udc_DOWN:1;	    //Ö±Á÷ÏÂÄ¸Ïß¹ıÑ¹
   unsigned int		   OVER_POWVER:1;	    //¹ıÔØ
   unsigned int		   Udc_Reverse:1;	        //Ö±Á÷½Ó·´ 
   unsigned int		   PHASE:1;	        //µçÍøÏàĞò´íÎó
};

union Grid_S_Faults_2
{
   unsigned int                 all;
   struct Grid_S_Faults_2_Bits  bit;
};  

struct Grid_Alarm_Bits
 {                                              
   unsigned int        LOAD:1;                  //Äæ±äÆ÷¹ıÔØ
   unsigned int		   Reserved_1:15;	        //±¸ÓÃ1   	  	
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
	State_Stopping = 10,                // Í£»ú¶¯×÷×´Ì¬
	State_Stopped,                      // Õı³£Í£»ú´Ì?
	State_Starting,                     // Æô¶¯¯×÷×´Ì¬
	State_Reset,                        // ¸´Î»×´Ì¬
	State_SoloStage_Running,            // ĞĞ×´Ì¬
	State_DualStage_Running,            // Ë«¼¶ÔËĞĞ×´Ì¬
	State_Error,                        // ¹ÊÕÏÍ£»ú×´Ì¬
	State_Standby,                      // ´ı»ú×´Ì¬
    State_Running                       //Õı³£ÔËĞĞ×´Ì¬
}Sys_State_Type;   

Sys_State_Type sys_state;

//=====================//

#endif 
//===========================================================================
// No more.
//===========================================================================
