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

int period = 7500;        //CPU_CLK/(2*PWM_CLK)

SYS_REG sys;
Uint32 sysLowTickTimer = 0;		// 10ms 低速计数器
GRAPH g1,g2;
int watch_i = 0;
long LoopCount = 0;
Uint16 ReceivedChar = 0;
Uint16 ReceivedChar1;
void GRAPH_calc(GRAPH *g, int32 v)
{
	g->i %= N_SAMPLE;
	g->buf[g->i++] = v;
}


void main(void)
{
	InitSysCtrl();
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
#ifdef _FLASH
	MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);
	InitFlash();
#endif
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
    // Note: Clocks were turned on to the SCIA peripheral
    // in the InitSysCtrl() function
 	//ScicRegs.SCICCR.all =0x0007;   // 1 stop bit,  No loopback
                                   // async mode, idle-line protocol
	//ScicRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,
                                   // Disable RX ERR, SLEEP, TXWAKE
	//ScicRegs.SCICTL2.all =0x0003;
	//ScicRegs.SCICTL2.bit.TXINTENA =1;
	//ScicRegs.SCICTL2.bit.RXBKINTENA =1;
	//#if (CPU_FRQ_150MHZ)
	     // ScicRegs.SCIHBAUD    =0x0001;  // 9600 baud @LSPCLK = 37.5MHz.
	     // ScicRegs.SCILBAUD    =0x00E7;
	//#endif
	//#if(CPU_FRQ_100MHZ)
      //ScicRegs.SCIHBAUD    =0x0001;  // 9600 baud @LSPCLK = 20MHz.
     // ScicRegs.SCILBAUD    =0x0044;
	//#endif
	//ScicRegs.SCICTL1.all =0x0023;  // Relinquish SCI from Reset
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
    //ScicRegs.SCIFFTX.all=0xE040;
    //ScicRegs.SCIFFRX.all=0x204f;
    //ScicRegs.SCIFFCT.all=0x0;
    ScicRegs.SCIFFTX.all=0xE040;
    ScicRegs.SCIFFRX.all=0x204f;
    ScicRegs.SCIFFCT.all=0x0;


}

void Run(void)
{
	for(;;)
	{
		  LoopCount++;
	  /*if(LoopCount<10000)
	  {  
	     GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1;
         //ReceivedChar =11;//"\r\nEnter a character: \0";
         //scia_msg(msg);
		 scia_xmit(11);
	  }

       // Wait for inc character
      if((LoopCount>10000)&&(LoopCount<10050))
       {
          GpioDataRegs.GPBSET.bit.GPIO34 = 1;
          while(SciaRegs.SCIFFRX.bit.RXFFST !=1) { } // wait for XRDY =1 for empty state
          // Get character
          ReceivedChar = SciaRegs.SCIRXBUF.all;
       }
       // Echo character back
	   if((LoopCount>10050)&&(LoopCount<10100))
	   {  
	     GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1;        
	     //msg = "  You sent: \0";
         //scia_msg(msg);
         scia_xmit(ReceivedChar);
	     
	   }
	   if(LoopCount>10100)
         LoopCount = 0;
      // if(LoopCount>100000)
       //  LoopCount = 0;
	/*  if(CpuTimer0Regs.TCR.bit.TIF)
		{
			// 10ms tick
			CpuTimer0Regs.TCR.bit.TIF = 1;
			sysLowTickTimer++;
			//AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;
			KickDog();
			sys.DI.all = GetDI();
			SetDO(sys.DO.all);
		}
		Sys_State_Handle();
	  LoopCount++;*/
	 /* if(LoopCount<10000)
	  {  
	     GpioDataRegs.GPASET.bit.GPIO24 = 1;
         //ReceivedChar =11;//"\r\nEnter a character: \0";
         //scia_msg(msg);
		 scia_xmit(11);
	  }*/
      // Wait for inc character
	/*  GpioDataRegs.GPACLEAR.bit.GPIO24 = 1;
      if((LoopCount>10000)&&(LoopCount<10550))
       {
         // GpioDataRegs.GPACLEARbit.GPIO24 = 1;
          while(ScibRegs.SCIFFRX.bit.RXFFST !=1){ } // wait for XRDY =1 for empty state
          ReceivedChar = ScibRegs.SCIRXBUF.all;
       }*/
       // Echo character back
	   /*if((LoopCount>10050)&&(LoopCount<10100))
	   {  
	             
	    // msg = "  You sent: \0";
         GpioDataRegs.GPASET.bit.GPIO24 = 1;
         //scia_msg(msg);
         scia_xmit(ReceivedChar);
	     
	   }
	   //if(LoopCount>10100)
        // LoopCount = 0;*/
      // if(LoopCount>10550)
       //  LoopCount = 0;*/

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
	 Sys_State_Handle();

	 // LoopCount++;
	 // if(LoopCount<10000)
	 // {  
	    // GpioDataRegs.GPBSET.bit.GPIO61 = 1;
         //ReceivedChar =11;//"\r\nEnter a character: \0";
         //scia_msg(msg);
		// scia_xmit(11);
	 // }
      // Wait for inc character
	//  GpioDataRegs.GPBCLEAR.bit.GPIO61 = 1;
     // if((LoopCount>10000)&&(LoopCount<10550))
      // {
         // GpioDataRegs.GPACLEARbit.GPIO24 = 1;
          //while(ScicRegs.SCIFFRX.bit.RXFFST !=1){ } // wait for XRDY =1 for empty state
         // ReceivedChar1 = ScicRegs.SCIRXBUF.all;
       //   while(ScicRegs.SCIFFRX.bit.RXFFST !=1) { } // wait for XRDY =1 for empty state
          // Get character
        //  ReceivedChar = ScicRegs.SCIRXBUF.all;

       //}
       // Echo character back
	   /*if((LoopCount>10050)&&(LoopCount<10100))
	   {  
	             
	    // msg = "  You sent: \0";
         GpioDataRegs.GPASET.bit.GPIO24 = 1;
         //scia_msg(msg);
         scia_xmit(ReceivedChar);
	     
	   }
	   //if(LoopCount>10100)
        // LoopCount = 0;*/
       if(LoopCount>10550)
         LoopCount = 0;
		 
	  /*if(LoopCount<10000)
	  {  
	     GpioDataRegs.GPBSET.bit.GPIO61 = 1;
         //ReceivedChar =11;//"\r\nEnter a character: \0";
         //scia_msg(msg);
		 scia_xmit(11);
	  }
      // Wait for inc character
      if((LoopCount>10000)&&(LoopCount<10050))
       {
          GpioDataRegs.GPBCLEAR.bit.GPIO61 = 1;
          while(ScicRegs.SCIFFRX.bit.RXFFST !=1) { } // wait for XRDY =1 for empty state
          // Get character
          ReceivedChar = ScicRegs.SCIRXBUF.all;
       }
       // Echo character back
	   if((LoopCount>10050)&&(LoopCount<10100))
	   {  
	             
	    // msg = "  You sent: \0";
         GpioDataRegs.GPBSET.bit.GPIO61 = 1;
         //scia_msg(msg);
         scia_xmit(ReceivedChar);
	     
	   }
	   //if(LoopCount>10100)
        // LoopCount = 0;
       if(LoopCount>100000)
         LoopCount = 0;*/
	}

}
interrupt void MAIN_Ctrl(void)
{

    LoopCount ++;

	ModbusFram.TimeoutCNT++;
	TX_RX_Struct.RXTimeoutCNT++;
	WaveIndex.TempCNT++;
	
	CMD_HANDLE();

	AD_VI();                                   					

	Protect_VIT();

	PLL();

	if(SYS_Info.grid_state.bit.RUN == 1)
	{
		Sys_CTRL();                                              
	}
	else if(SYS_Info.grid_state.bit.RUN == 0)
	{
		Udc_ref_init = Vdc_Sample;
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
			park1.ds = clarke1.ds;
			park1.qs = clarke1.qs;
			park1.os = clarke1.os;
			park1.ang = rg1.Out*Twice_PI;//-0.11304;
			park1.calc(&park1);

			SLOPER(Id_ref_init,Id_ref,Id_ref_step);
			SLOPER(Iq_ref_init,Iq_ref,Iq_ref_step);

			pi1_id.Ref = Id_ref_init;    
			pi1_iq.Ref = Iq_ref_init;	

			pi1_id.Fbk = park1.de;
			CNTL_PI_F_MACRO(pi1_id);
	
			pi1_iq.Fbk = park1.qe;
			CNTL_PI_F_MACRO(pi1_iq);

			ipark1.de = pi1_id.Out;                                
			ipark1.qe = pi1_iq.Out;
			ipark1.oe = 0;
		}
		ipark1.ang = rg1.Out*Twice_PI +3.1415926;//-0.11304;

		ipark1.calc(&ipark1);                    
				

	}
	else if(LEVEL == 3)
	{
		park1.ds = clarke1.ds;
		park1.qs = clarke1.qs;
		park1.os = clarke1.os;
		park1.ang = theta_park;
		park1.calc(&park1);

		if(Run_Mode == 0)
		{
			SLOPER(Id_ref_init,Id_ref,Id_ref_step);	
			pi1_id.Ref = Id_ref_init;    			
		}
		else if(Run_Mode == 1)
		{			
			SLOPER(Udc_ref_init,Udc_ref,Udc_ref_step);
			pi1_Vdc.Ref   = Udc_ref_init;
			pi1_Vdc.Fbk = Vdc_Sample;
			CNTL_PI_F_MACRO(pi1_Vdc);
			pi1_id.Ref = pi1_Vdc.Out; 
		}
		//pi1_iq.Ref = 0;	
		pi1_id.Fbk = park1.de;
		CNTL_PI_F_MACRO(pi1_id);
		SLOPER(Iq_ref_init,Iq_ref,Iq_ref_step);
		pi1_iq.Ref = Iq_ref_init;
	
		pi1_iq.Fbk = park1.qe;
		CNTL_PI_F_MACRO(pi1_iq);

		ipark1.de = pi1_id.Out;                                
		ipark1.qe = pi1_iq.Out;
		ipark1.oe = 0;

		ipark1.ang = theta_park;
		ipark1.calc(&ipark1);
	}

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
	if(Start_CMD == 0xAA)
	{
		Sys_Run = 1;
		Start_CMD = 0x55;
	}
	if(Stop_CMD == 0xAA)
	{
		Sys_Run = 0;
		Stop_CMD = 0x55;
	}
	if(Reset_CMD == 0xAA)
	{
		Reset_onetime_flag = 1;
		Reset_CMD = 0x55;
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

	clarke2.as = Vab_Sample;
	clarke2.bs = Vbc_Sample;
	clarke2.cs = Vca_Sample;
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

	theta = theta_line - 0.5236+0.104;   
	theta_park = theta + Once_PI;

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
			break;
		}
		case State_Stopping:  
		{
			Switch_Open();

			if(SYS_Info.grid_faults.all==0x0000)
				sys_state = State_Stopped;
			else
				sys_state = State_Error;
	 
			break;
		}
		case State_Stopped:
		{
			SYS_Info.grid_state.all &= 0x03F0;
			SYS_Info.grid_state.bit.STOP = 1;

			if(SYS_Info.grid_faults.all != 0)
			{
				sys_state = State_Error;
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
			SYS_Info.grid_state.all &= 0x03F0;
			SYS_Info.grid_state.bit.FAULT = 1;
			if(Reset_onetime_flag == 1)
				sys_state = State_Reset;
			break;
		}
		case State_Starting:
		{
			SYS_Info.grid_state.all &= 0x03F0;
			SYS_Info.grid_state.bit.START = 1;
			Switch_Close();
			if(SYS_Info.grid_faults.all == 0x0000)
			{
				sys_state = State_Running;
				break;
			}
			if(SYS_Info.grid_faults.all != 0)
			{
				sys_state = State_Stopping;
				break;
			}
			break;
		}
		case State_Running:
		{
			SYS_Info.grid_state.all &= 0x03F0;
			SYS_Info.grid_state.bit.RUN = 1;
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
	sys_state = State_Stopping;
	SYS_Info.grid_faults.all=0x0000;

	Grid_Ia = 0;
	Grid_Ib = 0;
	Grid_Ic = 0;
	Grid_Pac = 0;
	Grid_Qac = 0;
	LEVEL = 3;
	Run_Mode = 1;
	Grid_m = 0.8;
	Id_ref = 0.5;
	Iq_ref = 0.0;
	Udc_ref = 70;
	Start_CMD = 0x0055;
	Stop_CMD = 0x0055;
	Reset_CMD = 0x0055;

	Id_ref_init = 0.0;
	Id_ref_step = 0.01;
	Iq_ref_init = 0.0;
	Iq_ref_step = 0.01;
	Udc_ref_init = 70.0;
	Udc_ref_step = 0.01;

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

	pi1_Vdc.Kp = pi1_Vdc_Kp;
	pi1_Vdc.Ki = pi1_Vdc_Ki;
	pi1_Vdc.Umax = 10;
	pi1_Vdc.Umin = -10;

	pi1_pll.Kp = 8;//6;
	pi1_pll.Ki = 0.05;//0.03
	pi1_pll.Umax = 16;
	pi1_pll.Umin = -16;

	pi1_id.ui = 0;  
	pi1_id.Out = 0;     
	pi1_iq.ui = 0;
	pi1_iq.Out = 0;
	pi1_Vdc.ui = 0;
	pi1_iq.Out = 0;

	theta = 0;
	theta_line = 0;

	integral1.integral_out = 0;

	Delay_Second = 0;
	Delay_Second_i = 0;
	Delay_End = 1;

	rg1.StepAngleMax = 50.0/ISR_FREQUENCY;

	Vdc_Sample_counter = 0;

} 

void Switch_Open()
{  
	PWM1_OFF();

	Delay_co(1);

	sys.DO.bit.FanKM = 1;
	SetDO(sys.DO.all);
	Delay_co(1);
	SYS_Info.grid_state.bit.FAN_CONTACT = 0;

	sys.DO.bit.ACKM = 1;
	SetDO(sys.DO.all);
	Delay_co(1);
	SYS_Info.grid_state.bit.AC_CONTACT = 0;  

	sys.DO.bit.DCKM = 1;
	SetDO(sys.DO.all);
	Delay_co(1);

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
	pi1_Vdc.Umax = 10;
	pi1_Vdc.Umin = -10;

	pi1_pll.Kp = 8;//6;
	pi1_pll.Ki = 0.05;//0.03
	pi1_pll.Umax = 16;
	pi1_pll.Umin = -16;

    Id_ref_init = 0.0;
	Id_ref_step = 0.01;
	Iq_ref_init = 0.0;
	Iq_ref_step = 0.01;
	Udc_ref_init = 70.0;
	Udc_ref_step = 0.001;

	pi1_id.ui = 0;  
	pi1_id.Out = 0;     
	pi1_iq.ui = 0;
	pi1_iq.Out = 0;
	pi1_Vdc.ui = 0;
	pi1_iq.Out = 0;
}

void Switch_Close()
{
	sys.DO.bit.DCKM = 0;
	SetDO(sys.DO.all);
	Delay_co(2);

	sys.DO.bit.ChargeKM = 0; 
	SetDO(sys.DO.all);
	Delay_co(2);

	sys.DO.bit.ACKM = 0;
	SetDO(sys.DO.all);
	SYS_Info.grid_state.bit.AC_CONTACT = 1;
	Delay_co(1);

	sys.DO.bit.ChargeKM = 1; 
	SetDO(sys.DO.all);
	Delay_co(1);

	sys.DO.bit.FanKM = 0;
	SetDO(sys.DO.all);
	Delay_co(1);
	SYS_Info.grid_state.bit.FAN_CONTACT = 1;

	PWM1_ON();

	pi1_id.ui = 1; 


} 
void Reset()
{
	sys.DO.all = 0x003F;
	SetDO(sys.DO.all);

	SYS_Info.grid_faults.all = 0x0000;
	SYS_Info.grid_alarm.all = 0x0000;

	Reset_onetime_flag = 0;
	Sys_Run = 0;

	Id_ref_init = 0;
	Id_ref=0;
	Iq_ref=0;
	Iq_ref_init = 0;
	Vdc_Sample_counter = 0;
}
#pragma CODE_SECTION(Protect_VIT,"ramfuncs");
void Protect_VIT()
{
	if(Vdc_Sample_init > LIMIT_DCOV_DEF)
	{
		PWM1_OFF();
		SYS_Info.grid_faults.bit.Udc_OVER = 1;
		
	}
	if(Ia_Sample > LIMIT_ACOC_DEF)
	{
		PWM1_OFF();
		SYS_Info.grid_faults.bit.Ia_OVER = 1;
		
	}
	if(Ib_Sample > LIMIT_ACOC_DEF)
	{
		PWM1_OFF();
		SYS_Info.grid_faults.bit.Ib_OVER = 1;
	
	}
	if(Ic_Sample > LIMIT_ACOC_DEF)
	{
		PWM1_OFF();
		SYS_Info.grid_faults.bit.Ic_OVER = 1;
	}



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

