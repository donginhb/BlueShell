/*===================================================================================

System Name:    15kW PV Grid Connected Inverter

File Name:    STATE.H

Description:    STATE parameters file for 15kW PV Grid Connected Inverter control
          		
Originator:    Converter Control Group--XAXJ

=====================================================================================
 History:
 时间       修改原因                                修改内容                                  修改人                                    
------------------------------------------------------------------------------------------------------
 2014-5-7	 Release	Rev 1.0                                                               黄辉

==========================================================================================================  */

#ifndef STATE_H
#define STATE_H

/*==========================================================================
1        状态字1          Grid_State_1
2        状态字2          Grid_State_2
3        状态字3          Grid_State_3
4	   硬件故障字1	      Grid_H_Faults_1
5	   硬件故障字2	      Grid_H_Faults_2
6	   软件故障字1	      Grid_S_Faults_1
7	   软件故障字2	      Grid_S_Faults_2
8      软件故障字3        Grid_S_Faults_3
9	   严重故障	          Sever_Faults  
10       报警字	          Grid_Alarm
11        开入            DI_State
12        开出            DO_State
===========================================================================*/

//---------------------------------------------------------------------------
//Start Grid_State_1_Bits bit definitions:
struct Grid_State_1_Bits
{                                              
   unsigned int        STOP:1;                  //逆变器正常停机
   unsigned int        FAULT:1;                 //逆变器故障停机
   unsigned int        START:1;                 //逆变器启动中
   unsigned int		   RUN:1;                   //逆变器正常运行
   unsigned int		   WARN:1;                  //逆变器告警运行
   unsigned int		   STANDBY:1;				//逆变器待机
   unsigned int        Reserved_1:10;            //备用1
 //  unsigned int        LOCAL:1;                 //本地控制
 //  unsigned int        REMOTE:1;                //远程控制
 //  unsigned int        Anti_Islanding:1;        //防孤岛状态   1 使能  0 禁能
 //  unsigned int        START_CMD:1;             //开关机状态   1 开机  0 关机
 //  unsigned int        Alone_mode: 1;
 //  unsigned int        Parrel_mode: 1;
 //  unsigned int        PV1_put: 1;
 //  unsigned int        PV2_put: 1;
  // unsigned int        PV3_put: 1;
 //  unsigned int        PV4_put: 1;
 //  unsigned int		   Insulation_Detect:1;	        //绝缘检测状态 1 使能  0 禁能
 //  unsigned int		   RCD_Detect:1;	           //漏电流检测状态 1 使能  0 禁能
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
   unsigned int		   I_Boost_MODE:1;	        //Boost恒流模式
   unsigned int		   V_MODE:1;                //NPC恒电压模式
   unsigned int		   I_MODE:1;				//NPC恒电流模式                                             
   //unsigned int        PV1Connect:1;            //PV1接入
   unsigned int	       Mppt;                    //mppt模式
   unsigned int	       Svg;                    //Svg模式
   unsigned int        Islanding_Enable;       //孤岛使能
   unsigned int        Lvrt_Enable;            //低穿使能
   unsigned int        START_CMD:1;             //开关机状态   1 开机  0 关机
   unsigned int        Alone_mode: 1;           //独立状态
   unsigned int        Parrel_mode: 1;          //并联状态
   unsigned int        PV1_put:1;            //boost1接入
   unsigned int        PV2_put:1;            //boost2接入
   unsigned int        PV3_put:1;            //boost3接入
   unsigned int        PV4_put:1;            //boost4接入
   unsigned int		   Insulation_Detect:1;	        //绝缘检测状态 1 使能  0 禁能
   unsigned int        RCD_Detect:1;	           //漏电流检测状态 1 使能  0 禁能
   //unsigned int      PV2Connect:1;            //PV2接入
   // unsigned int        PV3Connect:1;            //PV3接入
   //unsigned int		   CONTACT:1;	            //主接触器闭合
   //unsigned int		   FAN:1;	                //风机接触器闭合
   	
};

union Grid_State_2
{
   unsigned int              all;
   struct Grid_State_2_Bits  bit;
};  
struct Grid_State_3_Bits
 {                                              
   unsigned int        REMOTE:1;                //远程控制
   unsigned int        LOCAL:1;                 //本地控制
   unsigned int        Dispatch_Q:1;            //无功功率调度
   unsigned int		   PF_Set:1;                //功率因数调度
   unsigned int		   P_Set_PCT:1;				//有功功率百分比调度
   unsigned int		   P_Set_R:1;	            //有功功率值调度
   unsigned int		   Reserved_1:10;	        //备用1   	  	
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
   unsigned int        Ia:1;                   //a相电流过流
   unsigned int        Ib:1;                   //b相电流过流
   unsigned int        Ic:1;                   //c相电流过流
   unsigned int		   Uab:1;                  //Uab过压
   unsigned int		   Ubc:1;				   //Ubc过压
   unsigned int		   Uca:1;	               //Uca过压
//   unsigned int        Upv1:1;                 //光伏阵列过压1
//   unsigned int        Upv2:1;                 //光伏阵列过压2
//   unsigned int        Upv3:1;                 //光伏阵列过压3
   unsigned int        Idc1:1;                 //boost输入过流1
   unsigned int        Idc2:1;                 //直流输入过流2
   unsigned int        Idc3:1;                 //直流输入过流3
   unsigned int        Idc4:1;                 //直流输入过流4
   unsigned int        Udclink:1;              //直流母线电压过压
   unsigned int        Udcdown:1;              //直流下母线电压过压
   unsigned int		   Reserved_1:4;	      //备用1   
  // unsigned int        TBoost:1;               //boost散热器过温
  // unsigned int        TNPC:1; 	  	           //NPC散热器过温
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
   unsigned int        NPCADriv:1;            //A桥驱动故障
   unsigned int        NPCBDriv:1;            //B桥驱动故障
   unsigned int        NPCCDriv:1;            //C桥驱动故障
   unsigned int		   Boost1Driv:1;          //Boost1驱动故障
 //  unsigned int		   Boost2Driv:1;	      //Boost2驱动故障
 //  unsigned int		   Boost3Driv:1;	      //Boost3驱动故障
   unsigned int		   I_Two:1;                //二次过流故障
   unsigned int		   Lvrt_Handshake:1;       //LVRT握手故障,过流脉冲解锁失败
   unsigned int		   Reserved_1:10;	      //备用1   	  	
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
   unsigned int        Ia:1;                  //a相过流
   unsigned int        Ib:1;                  //b相过流
   unsigned int        Ic:1;                  //c相过流
   unsigned int		   Idc1:1;                //直流输入过流1
   unsigned int        Idc2:1;                //直流输入过流2
   unsigned int        Idc3:1;                //直流输入过流3
   unsigned int        Idc4:1;                //直流输入过流3
   unsigned int        Udclink:1;             //直流母线电压过压
   unsigned int        Udcdown:1;             //直流下母线电压过压
   unsigned int        Upv1:1;                //boost1输入过压
   unsigned int        Upv2:1;                //boost2输入过压
   unsigned int        Upv3:1;                //boost3输入过压
   unsigned int        Upv4:1;                //boost4输入过压
   unsigned int        TBoost:1;              //Boost散热器过温
   unsigned int        TNPC:1;                //NPC散热器过温
   unsigned int        Unp:1;	              //中点电位不平衡
	  	
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
   unsigned int        OVER_FRQ:1;              //电网电压过频
   unsigned int        UNDER_FRQ:1;             //电网电压欠频
   unsigned int        OVER_Uab:1;              //uab过压
   unsigned int		   OVER_Ubc:1;              //Ubc过压
   unsigned int		   OVER_Uca:1;				//Uca过压
   unsigned int		   UNDER_Uab:1;	            //Uab欠压
   unsigned int        UNDER_Ubc:1;             //Ubc欠压
   unsigned int		   UNDER_Uca:1;             //Uca欠压
   unsigned int		   ISLAND:1;				//孤岛保护
   unsigned int		   INSULATE_RESISTANCE:1;   //绝缘监测故障
   unsigned int        RESIDUAL_CURRENT:1;      //漏电流故障
   unsigned int		   UNBALANCE_CURRENT:1;	    //电流不平衡
   unsigned int		   LVRT_Fault:1;	        //低穿故障 
   unsigned int		   Reserved_1:3;	        //备用1    	  	  	
};

union Grid_S_Faults_2
{
   unsigned int                 all;
   struct Grid_S_Faults_2_Bits  bit;
};  
struct Grid_S_Faults_3_Bits
 {                                              
   unsigned int        Connect:1;              //电网电压过频
   unsigned int		   Reserved_1:15;	        //备用1    	  	  	
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
   unsigned int        LOAD:1;                  //过载
   unsigned int        U_unbalance;             //电压不平衡
   unsigned int        STRING1:1;               //组串1异常
   unsigned int		   STRING2:1;               //组串2异常
   unsigned int		   STRING3:1;				//组串3异常
   unsigned int		   STRING4:1;	            //组串4异常
   unsigned int        STRING5:1;               //组串5异常
   unsigned int        STRING6:1;               //组串6异常
   unsigned int        STRING7:1;               //组串7异常
   unsigned int		   STRING8:1;               //组串8异常
   unsigned int		   STRING9:1;				//组串9异常
   unsigned int		   STRING10:1;	            //组串10异常
   unsigned int        STRING11:1;               //组串11异常
   unsigned int        STRING12:1;               //组串12异常
   unsigned int		   Reserved_1:2;	        //备用1   	  	
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
   unsigned int        PHASE:1;                 //相序错误
//   unsigned int        PV_Array_Reverse:1;
   unsigned int		   Reserved_1:15;	        //备用1   	  	
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
   unsigned int		   Reserved_1:16;	        //备用1 	  	
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
   unsigned int        Pwm:1;                     //pwm脉冲封锁                                             
   unsigned int        CONTACT1:1;             //交流接触器1
   unsigned int        CONTACT2:1;             //交流接触器2
   unsigned int        FAN1:1;                  //风机接触器1
   unsigned int        FAN2:1;           //风机接触器2
   unsigned int		   FAN3:1;	       //风机接触器3
   unsigned int		   FAN4:1;	       //风机接触器4
   unsigned int        DC_Relay1:1;      //直流继电器1
   unsigned int        DC_Relay2:1;      //直流继电器2
   unsigned int        DC_Relay3:1;      //直流继电器3
   unsigned int        DC_Relay4:1;      //直流继电器4
   unsigned int		   INSULATE:1;             //绝缘监测
   unsigned int		   Reserved_1:4;	       //备用
   	  	
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
