/**
 * VSC-HVDC control system.
 * The entry point of the program.
 * Author: XIAN yuneng dianli
 */

#include <string.h>
#include <stdlib.h>
#include "DSP2833x_Device.h"
#include "IQmathLib.h"
#include "main.h"
#include "hal.h"
#include "VARIABLE.h"
#include "I2C_EEPROM.h"
#include "DSP28x_Project.h"

interrupt void MAIN_Ctrl(void); //控制主中断
interrupt void Assist_Func(void); //辅助中断

// 初始化子函数
void Variable_Init();     // 变量初始化子函数 
// 逻辑相关子函数
void Sys_State_Handle();  // 逻辑状态机子函数
void Switch_Open();       // 停机分闸，停机状态时执行的子函数
void Switch_Close();      // 启动合闸，启动状态时执行的子函数
void Reset();             // 故障复位，复位状态时执行的子函数 
// 控制相关子函数
void Sys_CTRL();          // 主控子函数
void RMS_VI();            // 有效值计算
void Protect_VIT();       // 软件保护
void AD_VI();             // AD采样
void PLL();               // 锁相子函数
void CMD_HANDLE();        // cmd handle function 

void scia_echoback_init(void);
void scia_fifo_init(void);
void scia_xmit(Uint16 a);
//void scia_msg(char *msg);
int period;        //CPU_CLK/(2*PWM_CLK)

SYS_REG sys;
Uint32 sysLowTickTimer = 0;		// 10ms 低速计数器
GRAPH g1,g2;
int watch_i = 0;
long LoopCount = 0;
Uint16 ReceivedChar = 0;
Uint16 ReceivedChar1;

RMS rms_Vab = RMS_DEFAULTS; //有效值计RMS Urms_Va = RMS_DEFAULTS;
RMS rms_Vbc = RMS_DEFAULTS;
RMS rms_Vca = RMS_DEFAULTS; 
RMS rms_Ia = RMS_DEFAULTS;
RMS rms_Ib = RMS_DEFAULTS;
RMS rms_Ic = RMS_DEFAULTS; 
RMS rms_Vdclink = RMS_DEFAULTS;
int Ia_Fault_Counter;
int Ib_Fault_Counter; 
int Ic_Fault_Counter;
int test = 0;
int test1 = 0;
int test2 = 0;
int test3 = 0;
int test4 = 0;
int test5 = 0;
int test6 = 0;
int test7 = 0;
int test8 = 0;

void GRAPH_calc(GRAPH *g, int32 v)
{
	g->i %= N_SAMPLE;
	g->buf[g->i++] = v;
}


void main(void)
{
	InitSysCtrl();
	period = (Uint16)(SYSTEM_FREQUENCY*500000/ISR_FREQUENCY);
	InitGpio();
	InitEPwmGpio();
	DINT;
	IER = 0x0000;
	IFR = 0x0000;
	InitPieCtrl();
	InitPieVectTable();
	EALLOW;
	PieVectTable.EPWM1_INT = &MAIN_Ctrl;
	EDIS;
//#ifdef _FLASH
	MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);
	InitFlash();
//#endif
	InitAdc();
	InitSci();
	InitI2C();
	scia_echoback_init();
    scia_fifo_init();
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
	EDIS;
	InitEPWM1();
	InitEPWM2();
	InitEPWM3();
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
	EDIS;
	InitECan();
	InitCpuTimers();   // For this example, only initialize the Cpu Timers
	ConfigCpuTimer(&CpuTimer0, 150.0, 10e3);	// 10ms
	StartCpuTimer0();
	DisableDog();
	InitSystem();
	EnableInterrupts();
	Variable_Init();
	Run();
}

// 应用程序相关初始化
void InitSystem()
{
	memset((void*)&sys, 0, sizeof(sys));
	// 软件版本号初始化
	memset((void*)&g1, 0, sizeof(GRAPH));
	memset((void*)&g2, 0, sizeof(GRAPH));
}
void scia_echoback_init()
{
  	ScicRegs.SCICCR.all =0x0007;   // 1 stop bit,  No loopback
                                   // async mode, idle-line protocol
	ScicRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,
                                   // Disable RX ERR, SLEEP, TXWAKE
	ScicRegs.SCICTL2.all =0x0003;
	ScicRegs.SCICTL2.bit.TXINTENA =1;
	ScicRegs.SCICTL2.bit.RXBKINTENA =1;
	#if (CPU_FRQ_150MHZ)
	      ScicRegs.SCIHBAUD    =0x0000;  // 9600 baud @LSPCLK = 37.5MHz.
	      ScicRegs.SCILBAUD    =0x0027;
	#endif
	#if(CPU_FRQ_100MHZ)
      ScicRegs.SCIHBAUD    =0x0001;  // 9600 baud @LSPCLK = 20MHz.
      ScicRegs.SCILBAUD    =0x0044;
	#endif
	ScicRegs.SCICTL1.all =0x0023;  // Relinquish SCI from Reset

}

// Transmit a character from the SCI
void scia_xmit(Uint16 a)
{
    
    //while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}
    SciaRegs.SCITXBUF=a;

}

void scia_msg(char * msg)
{
    int i;
    i = 0;
    while(msg[i] != '\0')
    {
        scia_xmit(msg[i]);
        i++;
    }
}

// Initalize the SCI FIFO
void scia_fifo_init()
{
    ScicRegs.SCIFFTX.all=0xE040;
    ScicRegs.SCIFFRX.all=0x204f;
    ScicRegs.SCIFFCT.all=0x0;


}

void Run(void)
{
	for(;;)
	{
		LoopCount++;

		HMI_Comm_Server();

	  if(CpuTimer0Regs.TCR.bit.TIF)
		{
			// 10ms tick
			CpuTimer0Regs.TCR.bit.TIF = 1;
			sysLowTickTimer++;
			//AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;
			KickDog();
			sys.DI.all = GetDI();
			SetDO(sys.DO.all);
		}
	 
     CMD_HANDLE();

	 Sys_State_Handle();
//*系统状态置位*****************************************//
	 TM_Grid_State1 = SYS_Info.grid_state.all;
	 TM_Grid_HF = SYS_Info.grid_faults.all;
	 TM_Grid_SF1 = SYS_Info.grid_s_fault1.all;
	 TM_Grid_SF2 = SYS_Info.grid_s_fault2.all;

       if(LoopCount>10550)
         LoopCount = 0;
		 
	}

}
interrupt void MAIN_Ctrl(void)
{

    LoopCount ++;

	ModbusFram.TimeoutCNT++;
	TX_RX_Struct.RXTimeoutCNT++;
	WaveIndex.TempCNT++;
	
	//CMD_HANDLE();

	AD_VI();                                   					

	Protect_VIT();

	PLL();

	RMS_VI();

	if((SYS_Info.grid_state.bit.RUN == 1)&&(Sys_Run == 1))
	{
		Sys_CTRL();                                              
	}

	if(SYS_Info.grid_state.bit.RUN == 0)
	{
		Udc_ref_init = Vdc_Sample;
		test1++;
		//test2++;
		if(test1>1000)
            {
               test1 = 0;
			   test2 = 0;
			}
	}
	//================delay counter==============//
	if(Delay_Second > 0)
	{
		Delay_Second_i ++;
		if(Delay_Second_i>=(Delay_Second*10000))
		{
			Delay_Second_i = 0;
			Delay_Second = 0;
			Delay_End = 1;
		}
	}
	//==============the end=====================//

//stage

	// Clear INT flag for this timer                                     
    EPwm1Regs.ETCLR.bit.INT = 1;     	                                                                                                     
    // Acknowledge this interrupt to receive more interrupts from group 3 
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;  
}

#pragma CODE_SECTION(Sys_CTRL,"ramfuncs");
void Sys_CTRL(void)
{
	clarke1.as = Ia_Sample;
	clarke1.bs = Ib_Sample;
	clarke1.cs = Ic_Sample;
	clarke1.calc(&clarke1);
	if((LEVEL ==1)||(LEVEL == 2))
	{
		if(LEVEL == 1)
		{ 
			rg1.Freq = 1.0;
			RG_MACRO(rg1);
			ipark1.de = Grid_m;                                
			ipark1.qe = 0;
			ipark1.oe = 0.0;
		}
		else if(LEVEL == 2)
		{
			rg1.Freq = 1.0;
			RG_MACRO(rg1);
			park1.ds = clarke1.ds/32;
			park1.qs = clarke1.qs/32;
			park1.os = clarke1.os/32;
			park1.ang = rg1.Out*Twice_PI;//-0.11304;
			park1.calc(&park1);

			SLOPER(Id_ref_init,Id_ref,Id_ref_step);
			SLOPER(Iq_ref_init,Iq_ref,Iq_ref_step);

			pi1_id.Ref = Id_ref_init/32;    
			pi1_iq.Ref = Iq_ref_init/32;	

			pi1_id.Fbk = park1.de;
			CNTL_PI_F_MACRO(pi1_id);
	
			pi1_iq.Fbk = park1.qe;
			CNTL_PI_F_MACRO(pi1_iq);

			ipark1.de = pi1_id.Out;                                
			ipark1.qe = pi1_iq.Out;
			ipark1.oe = 0;
		}
		ipark1.ang = rg1.Out*Twice_PI;// +3.1415926;//-0.11304;

		ipark1.calc(&ipark1);                    
	}
	else if(LEVEL == 3)
	{
		park1.ds = clarke1.ds/32;
		park1.qs = clarke1.qs/32;
		park1.os = clarke1.os/32;
		park1.ang = theta_park;
		park1.calc(&park1);

		if(Run_Mode == 0)
		{
			SLOPER(Id_ref_init,Id_ref,Id_ref_step);	
			pi1_id.Ref = Id_ref_init/32;    			
		}
		else if(Run_Mode == 1)
		{			
			//SLOPER(Udc_ref_init,Udc_ref,Udc_ref_step);

			if(Udc_ref_init<Udc_ref)
              Udc_ref_init = Udc_ref_init + Udc_ref_step;
			if(Udc_ref_init>Udc_ref)
              Udc_ref_init = Udc_ref_init - Udc_ref_step;
			if(Udc_ref_init == Udc_ref)
              Udc_ref_init = Udc_ref;
             test++;
			 if(test>1000)
              test = 0;
			pi1_Vdc.Ref   = Udc_ref_init/1000;
			pi1_Vdc.Fbk = Vdc_Sample/1000;
			CNTL_PI_F_MACRO(pi1_Vdc);
			pi1_id.Ref = - pi1_Vdc.Out; 

		}
		//pi1_iq.Ref = 0;	
		pi1_id.Fbk = park1.de;
		CNTL_PI_F_MACRO(pi1_id);

		SLOPER(Iq_ref_init,Iq_ref,Iq_ref_step);
		pi1_iq.Ref = Iq_ref_init/32;
	
		pi1_iq.Fbk = park1.qe;
		CNTL_PI_F_MACRO(pi1_iq);

		ipark1.de = pi1_id.Out;                                
		ipark1.qe = pi1_iq.Out;
		ipark1.oe = 0;

		ipark1.ang = theta_park;
		ipark1.calc(&ipark1);
	}
    
    PWM1_ON();

	svgen_dq1.Ualfa = ipark1.ds;
    svgen_dq1.Ubeta = ipark1.qs;

	svgen_dq1.k = (0.5);	
    svgen_dq1.calc(&svgen_dq1);	

	EPwm1Regs.CMPA.half.CMPA = (Uint16)(svgen_dq1.Ta*period);
	EPwm2Regs.CMPA.half.CMPA = (Uint16)(svgen_dq1.Tb*period);
	EPwm3Regs.CMPA.half.CMPA = (Uint16)(svgen_dq1.Tc*period);
	EPwm4Regs.CMPA.half.CMPA = (Uint16)(svgen_dq1.Ta*period);
	EPwm5Regs.CMPA.half.CMPA = (Uint16)(svgen_dq1.Tb*period);
	EPwm6Regs.CMPA.half.CMPA = (Uint16)(svgen_dq1.Tc*period);
	 
}

void CMD_HANDLE(void)
{
	if((Start_CMD == 1)&&(RemoteOrLocal==1)&&(SYS_Info.grid_faults.all == 0)&&(SYS_Info.grid_s_fault1.all == 0)&&(SYS_Info.grid_s_fault2.all == 0))
	{
		Sys_Run = 1;
	//	Start_CMD = 0x55;
	}
	if(((Start_CMD == 0)&&(RemoteOrLocal==0))||(SYS_Info.grid_faults.all != 0)||(SYS_Info.grid_s_fault1.all != 0)||(SYS_Info.grid_s_fault2.all != 0))
	{
		test2++;
		Sys_Run = 0;
		PWM1_OFF();
	//	Stop_CMD = 0x55;
	}
	if((Reset_CMD == 1)&&(Start_CMD == 0)&&(RemoteOrLocal==0))//停机状态下复位命令
	{
		 Reset_onetime_flag = 1;
		 Reset_CMD = 0;
		//Reset_CMD = 0x55;
	}
	if((LEVEL != 1)&&(LEVEL != 2)&&(LEVEL != 3))
		LEVEL = 3;
	if((Run_Mode != 0)&&(Run_Mode != 1))
		Run_Mode = 1;
	if(Id_ref>=Id_Max)
		Id_ref = Id_Max;
	else if(Id_ref<=Id_Min)
		Id_ref = Id_Min;
	if(Iq_ref>=Iq_Max)
		Iq_ref = Iq_Max;
	else if(Iq_ref<=Iq_Min)
		Iq_ref = Iq_Min;
	if(Udc_ref>=Udc_Max)
		Udc_ref = Udc_Max;
	else if(Udc_ref<=Udc_Min)
		Udc_ref = Udc_Min;
	if(Grid_m>=100)
		Grid_m = 100;
	else if(Grid_m<0)
		Grid_m = 0;
}

#pragma CODE_SECTION(PLL,"ramfuncs"); 
void PLL()
{

	clarke2.as = Vab_Sample/565;
	clarke2.bs = Vbc_Sample/565;
	clarke2.cs = Vca_Sample/565;
	clarke2.calc(&clarke2);

	park_pll.ds = clarke2.ds;
	park_pll.qs = clarke2.qs;
	park_pll.os = clarke2.os;
	park_pll.ang = theta_line;
	park_pll.calc(&park_pll);

	pi1_pll.Ref = 0;
	pi1_pll.Fbk = -park_pll.qe;
	CNTL_PI_F_MACRO(pi1_pll);

	integral1.integral_frequency = ISR_FREQUENCY;
	integral1.integral_ref = pi1_pll.Out;
	integral1.integral_fdb = 50;
	integral1.calc(&integral1);

	theta_line = integral1.integral_out; 

	theta = theta_line - 0.5236+0.0504;   
	theta_park = theta;

	if(theta<0)
	{
		theta= theta + Twice_PI;
	}  	
	if(theta_park > Twice_PI)
	{
		theta_park = theta_park - Twice_PI;
	}
	
} 

#pragma CODE_SECTION(AD_VI,"ramfuncs"); 
void AD_VI()
{
	Vab_Sample = ((float)((AdcRegs.ADCRESULT0>>4)+18))*0.58608059-1200.0;
	Vbc_Sample = ((float)((AdcRegs.ADCRESULT1>>4)+17))*0.58608059-1200.0;
	Vca_Sample = ((float)((AdcRegs.ADCRESULT2>>4)+21))*0.58608059-1200.0;
	Ia_Sample = ((float)((AdcRegs.ADCRESULT3>>4)+21))*0.01831502/0.5-37.5/0.5;
	Ib_Sample = ((float)((AdcRegs.ADCRESULT4>>4)+25))*0.01831502/0.5-37.5/0.5;
	Ic_Sample = ((float)((AdcRegs.ADCRESULT5>>4)+16))*0.01831502/0.5-37.5/0.5;
	Vdc_Sample_init = ((float)(AdcRegs.ADCRESULT9>>4))*0.29304029;
	Vdc_Sample_counter++;
	if(Vdc_Sample_counter>10)
	{
		Vdc_Sample_counter = 0;
		Vdc_Sample = Vdc_Sample_mid;
		Vdc_Sample_mid = 0;
	}
	else
		Vdc_Sample_mid += Vdc_Sample_init*0.1;
} 

void Sys_State_Handle(void)
{
	switch(sys_state)
	{
		case State_Reset:
		{
			Reset();
			sys_state = State_Stopping;
			SYS_Info.grid_state.bit.STOP = 1;
            SYS_Info.grid_state.bit.FAULT = 0;
            SYS_Info.grid_state.bit.RUN = 0;
            SYS_Info.grid_state.bit.START = 0;
			test3++;
			break;
		}
		case State_Stopping:  
		{
			Switch_Open();
            //sys_state = State_Stopped;
			if(SYS_Info.grid_faults.all==0x0000)
			{
				 sys_state = State_Stopped;
				 SYS_Info.grid_state.bit.STOP = 1;
                 SYS_Info.grid_state.bit.FAULT = 0;
                 SYS_Info.grid_state.bit.RUN = 0;
                 SYS_Info.grid_state.bit.START = 0;
				 test4++;
			}
			else
			{
				sys_state = State_Error;
				SYS_Info.grid_state.bit.STOP = 0;
                SYS_Info.grid_state.bit.FAULT = 1;
                SYS_Info.grid_state.bit.RUN = 0;
				test5++;
                SYS_Info.grid_state.bit.START = 0;
            }
	 
			break;
		}
		case State_Stopped:
		{
			//SYS_Info.grid_state.all &= 0x03F0;
		//	sys_state = State_Error;
	        pi1_id.Kp = pi1_id_Kp;
	        pi1_id.Ki = pi1_id_Ki;
	        pi1_id.Umax = 0.98;
	        pi1_id.Umin = -0.98;

       	   pi1_iq.Kp = pi1_iq_Kp;
	       pi1_iq.Ki = pi1_iq_Ki;
	       pi1_iq.Umax = 0.98;
	       pi1_iq.Umin = -0.98;

	       pi1_Vdc.Kp = pi1_Vdc_Kp*10;
	       pi1_Vdc.Ki = pi1_Vdc_Ki;
	       pi1_Vdc.Umax = 1;
	       pi1_Vdc.Umin = -1;


			if(SYS_Info.grid_faults.all != 0)
			{
				sys_state = State_Error;
				SYS_Info.grid_state.bit.STOP = 0;
                SYS_Info.grid_state.bit.FAULT = 1;
                SYS_Info.grid_state.bit.RUN = 0;
				test6++;
                SYS_Info.grid_state.bit.START = 0;

				break;
			}
			if(Sys_Run == 1)
				sys_state = State_Starting;

			if(Reset_onetime_flag == 1)
				sys_state = State_Reset;

			break;

		}
		case State_Error:
		{
			//SYS_Info.grid_state.all &= 0x03F0;
				SYS_Info.grid_state.bit.STOP = 0;
                SYS_Info.grid_state.bit.FAULT = 1;
                SYS_Info.grid_state.bit.RUN = 0;
				test7++;
                SYS_Info.grid_state.bit.START = 0;

			if(Reset_onetime_flag == 1)
				sys_state = State_Reset;
			break;
		}
		case State_Starting:
		{
			//SYS_Info.grid_state.all &= 0x03F0;
			SYS_Info.grid_state.bit.STOP = 0;
            SYS_Info.grid_state.bit.FAULT = 0;
            SYS_Info.grid_state.bit.RUN = 0;
			test8++;
            SYS_Info.grid_state.bit.START = 1;

			Switch_Close();
			if(SYS_Info.grid_faults.all == 0x0000)
			{
				sys_state = State_Running;
				break;
			}
			if(SYS_Info.grid_faults.all != 0x0000)
			{
				sys_state = State_Stopping;
				break;
			}
			break;
		}
		case State_Running:
		{
			//SYS_Info.grid_state.all &= 0x03F0;
			SYS_Info.grid_state.bit.RUN = 1;
			SYS_Info.grid_state.bit.STOP = 0;
            SYS_Info.grid_state.bit.FAULT = 0;
            SYS_Info.grid_state.bit.RUN = 1;
            SYS_Info.grid_state.bit.START = 0;

			if((SYS_Info.grid_faults.all != 0) || (Sys_Run == 0))
			{
				sys_state = State_Stopping;
				break;
			}

		}
	}

}

void Variable_Init(void)
{
	sys.DO.all = 0x003F;
	SetDO(sys.DO.all);
	sys_state = State_Reset;
	SYS_Info.grid_faults.all=0x0000;

	Grid_Ia = 0;
	Grid_Ib = 0;
	Grid_Ic = 0;
	Grid_Pac = 0;
	Grid_Qac = 0;
	LEVEL = 3;
	Run_Mode = 1;
	Grid_m = 0.8;
	Id_ref = 0;
	Iq_ref = 0.0;
	Udc_ref = 70;
	Start_CMD = 0;
	Stop_CMD = 0x0055;
	Reset_CMD = 0;

	Id_ref_init = 0.0;
	Id_ref_step = 0.01;
	Iq_ref_init = 0.0;
	Iq_ref_step = 0.0001;
	Udc_ref_init = 70.0;
	Udc_ref_step = 0.001;

	Sys_Run = 0;
	Reset_onetime_flag = 0;

	CNTL_PI_F_init(&pi1_id);
	CNTL_PI_F_init(&pi1_iq);
	CNTL_PI_F_init(&pi1_Vdc);

	pi1_id.Kp = pi1_id_Kp;
	pi1_id.Ki = pi1_id_Ki;
	pi1_id.Umax = 0.98;
	pi1_id.Umin = -0.98;

	pi1_iq.Kp = pi1_iq_Kp;
	pi1_iq.Ki = pi1_iq_Ki;
	pi1_iq.Umax = 0.98;
	pi1_iq.Umin = -0.98;

	pi1_Vdc.Kp = pi1_Vdc_Kp*10;
	pi1_Vdc.Ki = pi1_Vdc_Ki;
	pi1_Vdc.Umax = 1;
	pi1_Vdc.Umin = -1;

	pi1_pll.Kp = 8;//6;
	pi1_pll.Ki = 0.05;//0.03
	pi1_pll.Umax = 16;
	pi1_pll.Umin = -16;
    pi1_pll.i1 = 0;
    pi1_pll.ui = 0;


	pi1_id.ui = 0;  
	pi1_id.Out = 0;     
	pi1_iq.ui = 0;
	pi1_iq.Out = 0;
	pi1_Vdc.ui = 0;
	pi1_iq.Out = 0;

	theta = 0;
	theta_line = 0;

	integral1.integral_out = 0;
    RemoteOrLocal = 0;
	
	Delay_Second = 0;
	Delay_Second_i = 0;
	Delay_End = 1;

	rg1.StepAngleMax = 50.0/ISR_FREQUENCY;

	Vdc_Sample_counter = 0;
	
	SYS_Info.grid_faults.all = 0x0000;
	SYS_Info.grid_alarm.all = 0x0000;
	SYS_Info.grid_s_fault1.all = 0x0000;
	SYS_Info.grid_s_fault2.all = 0x0000;

	Ia_Fault_Counter = 0;
    Ib_Fault_Counter = 0; 
    Ic_Fault_Counter = 0;


} 

void Switch_Open()
{  
	PWM1_OFF();

	Delay_co(1);

	sys.DO.bit.FanKM = 1;
	SetDO(sys.DO.all);
	//Delay_co(1);
	//SYS_Info.grid_state.bit.FAN_CONTACT = 0;

	sys.DO.bit.ACKM = 1;
	SetDO(sys.DO.all);
//	Delay_co(1);
//	SYS_Info.grid_state.bit.AC_CONTACT = 0;  

	sys.DO.bit.DCKM = 1;
	SetDO(sys.DO.all);
	//Delay_co(1);

	CNTL_PI_F_init(&pi1_id);
	CNTL_PI_F_init(&pi1_iq);
	CNTL_PI_F_init(&pi1_Vdc);

	pi1_id.Kp = pi1_id_Kp;
	pi1_id.Ki = pi1_id_Ki;
	pi1_id.Umax = 0.98;
	pi1_id.Umin = -0.98;

	pi1_iq.Kp = pi1_iq_Kp;
	pi1_iq.Ki = pi1_iq_Ki;
	pi1_iq.Umax = 0.98;
	pi1_iq.Umin = -0.98;

	pi1_Vdc.Kp = pi1_Vdc_Kp;
	pi1_Vdc.Ki = pi1_Vdc_Ki;
	pi1_Vdc.Umax = 1;
	pi1_Vdc.Umin = -1;

	pi1_pll.Kp = 8;//6;
	pi1_pll.Ki = 0.05;//0.03
	pi1_pll.Umax = 16;
	pi1_pll.Umin = -16;

    Id_ref_init = 0.0;
	Id_ref_step = 0.01;
	Iq_ref_init = 0.0;
	Iq_ref_step = 0.01;
	Udc_ref_init = 600.0;
	Udc_ref_step = 0.001;

	pi1_id.ui = 0;  
	pi1_id.Out = 0;     
	pi1_iq.ui = 0;
	pi1_iq.Out = 0;
	pi1_Vdc.ui = 0;
	pi1_iq.Out = 0;
	SYS_Info.grid_state.all = 0x0081;
	Start_CMD = 0;

	Ia_Fault_Counter = 0;
    Ib_Fault_Counter = 0; 
    Ic_Fault_Counter = 0;

}

void Switch_Close()
{
	sys.DO.bit.DCKM = 0;
	SetDO(sys.DO.all);
	Delay_co(2);

	sys.DO.bit.ChargeKM = 0; 
	SetDO(sys.DO.all);
	Delay_co(8);
   if(Vdc_Sample>((Grid_Vab+Grid_Vbc+Grid_Vca)*0.333-20))
	{
	   sys.DO.bit.ACKM = 0;
	   SetDO(sys.DO.all);
  //	SYS_Info.grid_state.bit.AC_CONTACT = 1;
	   Delay_co(1);

	   sys.DO.bit.ChargeKM = 1; 
	   SetDO(sys.DO.all);
//	Delay_co(1);

	   sys.DO.bit.FanKM = 0;
	   SetDO(sys.DO.all);
//	Delay_co(1);
	//SYS_Info.grid_state.bit.FAN_CONTACT = 1;
	  if(LEVEL==3)
	  {
	     pi1_id.ui = 0.471333*(Grid_Vab+Grid_Vbc+Grid_Vca)/Vdc_Sample; 
         pi1_id.i1 = 0.471333*(Grid_Vab+Grid_Vbc+Grid_Vca)/Vdc_Sample;

	     if(pi1_id.ui>0.98)
	     {
	       pi1_id.i1 = 0.98;
	       pi1_id.ui = 0.98;
	      }
       }
	}
	else
	 {
	    SYS_Info.grid_s_fault1.bit.solft_Fault = 1;
		SYS_Info.grid_faults.bit.Reserved_1 = 1;
	 }

} 
void Reset()
{
	sys.DO.all = 0x003F;
	SetDO(sys.DO.all);

	SYS_Info.grid_faults.all = 0x0000;
	SYS_Info.grid_alarm.all = 0x0000;
	SYS_Info.grid_s_fault1.all = 0x0000;
	SYS_Info.grid_s_fault2.all = 0x0000;

	Reset_onetime_flag = 0;
	Sys_Run = 0;

	Id_ref_init = 0;
	Id_ref=0;
	Iq_ref=0;
	Iq_ref_init = 0;
	Vdc_Sample_counter = 0;

    Ia_Fault_Counter = 0;
    Ib_Fault_Counter = 0; 
    Ic_Fault_Counter = 0;

}
#pragma CODE_SECTION(Protect_VIT,"ramfuncs");
void Protect_VIT()
{
	if(Vdc_Sample_init > LIMIT_DCOV_DEF)
	{
		   PWM1_OFF();
		   SYS_Info.grid_s_fault2.bit.OVER_Udc_UP = 1;
		   SYS_Info.grid_s_fault2.bit.OVER_Udc_DOWN = 1;
		   SYS_Info.grid_faults.bit.Reserved_1 = 1;
		   //Ia_Fault_Counter = 4;
	}
	if(Ia_Sample > LIMIT_ACOC_DEF)
	{
		Ia_Fault_Counter++;
		if(Ia_Fault_Counter>1)
		{

		  PWM1_OFF();
		  SYS_Info.grid_faults.bit.Ia_OVER = 1;
		  Ia_Fault_Counter = 3;
		}
	}
	else
      Ia_Fault_Counter = 0;

	if(Ib_Sample > LIMIT_ACOC_DEF)
	{
		Ib_Fault_Counter++;
		if(Ib_Fault_Counter>1)
		{

		   PWM1_OFF();
		   SYS_Info.grid_faults.bit.Ib_OVER = 1;
	       Ib_Fault_Counter = 3;
	     }
	}
	else
      Ib_Fault_Counter = 0;

	if(Ic_Sample > LIMIT_ACOC_DEF)
	{
	
	   Ic_Fault_Counter++;
	   if(Ic_Fault_Counter>1)
	   {
	     PWM1_OFF();
		SYS_Info.grid_faults.bit.Ic_OVER = 1;
		Ic_Fault_Counter = 3;
		}
	}
	else
      Ic_Fault_Counter = 0;
}

#pragma CODE_SECTION(Delay,"ramfuncs");	  
void Delay_co(float CycleNum1)                                                
{
	Delay_Second = CycleNum1;
	do
	{
	
	}while(Delay_End ==0);
	Delay_End = 0;	
}

#pragma CODE_SECTION(Delay_func,"ramfuncs");	 
void Delay_func()
{
	if(Delay_Second > 0)
	{
		Delay_Second_i ++;
		if(Delay_Second_i>=(Delay_Second*10000)) 
		{
			Delay_Second_i = 0;
			Delay_Second = 0;
			Delay_End =1;
		}  
	}
	else
	{
		Delay_Second_i = 0;
	} 
}

void RMS_VI()
{

	rms_Vdclink.in = Vdc_Sample_init;
    rms_Vdclink.calc(&rms_Vdclink);
	Vdc_Sample = rms_Vdclink.out;

	rms_Vab.in = Vab_Sample;
    rms_Vab.calc(&rms_Vab);
	Grid_Vab = rms_Vab.out;

	rms_Vbc.in = Vbc_Sample;
    rms_Vbc.calc(&rms_Vbc);
	Grid_Vbc = rms_Vbc.out;

	rms_Vca.in = Vca_Sample;
    rms_Vca.calc(&rms_Vca);
	Grid_Vca = rms_Vca.out;

	Frq_i ++;
	if(Frq_i<81)
	{
 	   Frq_Avg_Tmp = pi1_pll.Out * 0.0125;          
 	   Frq_Avg += Frq_Avg_Tmp;     
 	}
	else
 	{
       Frq_i = 0;
       Grid_Freq= Frq_Avg*100+5000;
       Frq_Avg = 0;
    }
	// 在运行状态下计算电流及功率
	if(sys_state==State_Running)
	{        
		//============计悴⑼缌饔行е?===========//
		rms_Ia.in = Ia_Sample;                                            // A嗟缌?
		rms_Ib.in = Ib_Sample;                                            // B相电流
		rms_Ic.in = Ic_Sample;                                            // C相电流
		//rms_Idc.in= Idc_Sample;

		rms_Ia.calc(&rms_Ia);
		rms_Ib.calc(&rms_Ib);
		rms_Ic.calc(&rms_Ic);

		Grid_Ia = rms_Ia.out;                           // A相饔行е?     
		Grid_Ib = rms_Ib.out;                           // B相电流有效值
		Grid_Ic = rms_Ic.out;                           // C相电饔行е? 

	    Grid_Va_Instant=(0.666666667*Vab_Sample+0.333333333*Vbc_Sample);   // (Va=(2Vab+Vbc)/3   A相电压瞬时值 pu iq15格式
	    Grid_Vc_Instant=(-0.666666667*Vbc_Sample-0.333333333*Vab_Sample);  // (Vc=-(2Vbc+Vab)/3   C相电压瞬时值 pu iq15格式
        Grid_Vb_Instant=(-Grid_Va_Instant-Grid_Vc_Instant);
	      
	    Grid_Act_Power = (((Grid_Va_Instant * Ia_Sample)+(Grid_Vb_Instant * Ib_Sample)+(Grid_Vc_Instant * Ic_Sample)));      // 20130513，增加电压⒌流校正系数，校准功率计算              
	    Grid_React_Power = (((Vab_Sample * Ic_Sample)+(Vbc_Sample * Ia_Sample)+(Vca_Sample * Ib_Sample))); 
                 
        Avg_PQ_i++;

	   if(Avg_PQ_i<81)
	   {
           Avg_P_Temp += Grid_Act_Power*0.0125;                                   // 有功功率平均值计算
		   Avg_Q_Temp += Grid_React_Power*0.0125;                                 // 无功功率平均值计算
	   }
	   else
	   {
           Avg_PQ_i = 0;
           Grid_Pac = Avg_P_Temp;                                                  //根据实时观测乘以校正系数1.02（2015.7.30）
		   // 依据实测无功值对触摸屏显示值进行校正 12278
           Grid_Qac = (Avg_Q_Temp+5000); 
	                
           Avg_P_Temp = 0;
           Avg_Q_Temp = 0;
       }

	}
}


void ADCINT_HOOK(void)
{
	GRAPH_calc(&g1, sys.adBuf[1]);
	GRAPH_calc(&g2, sys.adBuf[2]);
}

void EPWM1_INT_HOOK(void)
{

}

// INT9.1
void SCIRXINTA_Callback(void)
{

}


// INT9.3
void SCIRXINTB_Callback(void)
{

}

// INT9.3
void SCIRXINTC_Callback(void)
{

}

