// TI File $Revision: /main/1 $
// Checkin $Date: August 18, 2006   13:46:19 $
//###########################################################################
//
// FILE:   DSP2833x_EPwm.c
//
// TITLE:  DSP2833x ePWM Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP2833x/DSP2823x C/C++ Header Files V1.31 $
// $Release Date: August 4, 2009 $
//###########################################################################

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "parameter.h"

#define EPWM_DB 150

#define ENABLE    1
#define DISENABLE 0

#define EQUAL_ZERO      1 
#define EQUAL_PERIOD    2
#define EQUAL_CMPA_UP   4
#define EQUAL_CMPA_DOWN 5
#define EQUAL_CMPB_UP   6
#define EQUAL_CMPB_DOWN 7

#if (CPU_FRQ_150MHZ)
  #define CPU_CLK   150e6
#endif
#if (CPU_FRQ_100MHZ)
  #define CPU_CLK   100e6
#endif
#define PWM_CLK   10e3                 // If diff freq desired, change freq here.
#define PERIOD    CPU_CLK/(2*PWM_CLK)
//---------------------------------------------------------------------------
// InitEPwm:
//---------------------------------------------------------------------------
// This function initializes the ePWM(s) to a known state.
//
void InitEPwm(void)
{
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
	EDIS;
	EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;
	EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE;
	EPwm3Regs.TBCTL.bit.PHSEN = TB_DISABLE;
	EPwm1Regs.TBPHS.half.TBPHS = 0;
	EPwm2Regs.TBPHS.half.TBPHS = 0;
	EPwm3Regs.TBPHS.half.TBPHS = 0;
	EPwm1Regs.TBCTL.bit.HSPCLKDIV  = TB_DIV1;
	EPwm2Regs.TBCTL.bit.HSPCLKDIV  = TB_DIV1;
	EPwm3Regs.TBCTL.bit.HSPCLKDIV  = TB_DIV1;
	InitEPWM1();
	InitEPWM2();
	InitEPWM3();
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
	EDIS;

}
void InitEPWM1(void)
{
   EPwm1Regs.TBPRD = PERIOD;                        // Set timer period
   EPwm1Regs.TBPHS.half.TBPHS = 0x0000;           // Phase is 0
   EPwm1Regs.TBCTR = 0x0000;                      // Clear counter

   // Setup TBCLK
   EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count updown
   EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
   EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
   EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;

   EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;  	//映射模式  
   EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;	// 时间基准计数器等于零时加载
   EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Setup compare
   EPwm1Regs.CMPA.half.CMPA = 0;

   // Set actions
   EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;//AQ_SET;             // EPWM1A（计数器=CMPA，递增时输出高，递减时输出低）
   EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;//AQ_CLEAR;


   EPwm1Regs.AQCTLB.bit.CAU = AQ_SET;//AQ_CLEAR;          // EPWM1B（计数器=CMPA，递增时输出低，递减时输出高）
   EPwm1Regs.AQCTLB.bit.CAD = AQ_CLEAR;//AQ_SET;

   // Active High Complementary PWMs - Setup Deadband
    EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE; 	//3,延迟输入信号由DBCTL.bit.IN_MODE决定
    EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;//DB_ACTV_LOC;       	//2,主高互补
    EPwm1Regs.DBCTL.bit.IN_MODE = DBA_ALL;         //0,EPWMxA In 是下降沿和上升沿延迟的输入源
    EPwm1Regs.DBRED = EPWM_DB;                
    EPwm1Regs.DBFED = EPWM_DB;                 //6us                

   // Interrupt where we will change the Deadband
   EPwm1Regs.ETCLR.bit.INT = 1;   
   EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     //ET_CTR_PRD;		// 1,Select INT on Zero event
   EPwm1Regs.ETSEL.bit.INTEN = 1;                // Enable INT
   EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;           // 1,Generate INT on 1rd event

   //Start Conversion of ADC
   EPwm1Regs.ETSEL.bit.SOCAEN  = ENABLE;          // Enable SOC on A group
   EPwm1Regs.ETSEL.bit.SOCASEL = EQUAL_PERIOD;   // 时间基准计数器等于周期寄存器值时触发AD采样
   EPwm1Regs.ETPS.bit.SOCAPRD  = 1;               // Generate pulse on 1st event

}
void InitEPWM2(void)
{
   EPwm2Regs.TBPRD = PERIOD;                        // Set timer period
   EPwm2Regs.TBPHS.half.TBPHS = 0x0000;           // Phase is 0
   EPwm2Regs.TBCTR = 0x0000;                      // Clear counter

   // Setup TBCLK
   EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
   EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
   EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;          // Slow just to observe on the scope

   // Setup compare
   EPwm2Regs.CMPA.half.CMPA = 0;

   // Set actions
   EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;//AQ_SET;             // Set PWM2A on Zero
   EPwm2Regs.AQCTLA.bit.CAD = AQ_SET;//AQ_CLEAR;


   EPwm2Regs.AQCTLB.bit.CAU = AQ_SET;//AQ_CLEAR;           // Set PWM2A on Zero
   EPwm2Regs.AQCTLB.bit.CAD = AQ_CLEAR;//AQ_SET;

   // Active Low complementary PWMs - setup the deadband
   EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
   EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;//DB_ACTV_LOC;
   EPwm2Regs.DBCTL.bit.IN_MODE = DBA_ALL;
   EPwm2Regs.DBRED = EPWM_DB;
   EPwm2Regs.DBFED = EPWM_DB;

   // Interrupt where we will modify the deadband
   EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;      // Select INT on Zero event
   EPwm2Regs.ETSEL.bit.INTEN = 0;                 // Enable INT
   EPwm2Regs.ETPS.bit.INTPRD = ET_3RD;            // Generate INT on 3rd event 
}

void InitEPWM3(void)
{
   EPwm3Regs.TBPRD = PERIOD;                       // Set timer period
   EPwm3Regs.TBPHS.half.TBPHS = 0x0000;            // Phase is 0
   EPwm3Regs.TBCTR = 0x0000;                       // Clear counter


   // Setup TBCLK
   EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   EPwm3Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
   EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
   EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;          // Slow so we can observe on the scope

   // Setup compare
   EPwm3Regs.CMPA.half.CMPA = 0;

   // Set actions
   EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR;//AQ_SET;  	//AQ_CLEAR;	//            // Set PWM3A on Zero
   EPwm3Regs.AQCTLA.bit.CAD = AQ_SET;//AQ_CLEAR;		//AQ_SET;//

   EPwm3Regs.AQCTLB.bit.CAU = AQ_SET;//AQ_CLEAR;            // Set PWM3A on Zero
   EPwm3Regs.AQCTLB.bit.CAD = AQ_CLEAR;//AQ_SET;

   // Active high complementary PWMs - Setup the deadband
   EPwm3Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
   EPwm3Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;//DB_ACTV_LOC;
   EPwm3Regs.DBCTL.bit.IN_MODE = DBA_ALL;
   EPwm3Regs.DBRED = EPWM_DB;
   EPwm3Regs.DBFED = EPWM_DB;

   // Interrupt where we will change the deadband
   EPwm3Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;       // Select INT on Zero event
   EPwm3Regs.ETSEL.bit.INTEN = 0;                  // Disnable INT
   EPwm3Regs.ETPS.bit.INTPRD = ET_3RD;             // Generate INT on 3rd event	
}

//---------------------------------------------------------------------------
// Example: InitEPwmGpio:
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as ePWM pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//

void InitEPwmGpio(void)
{
	// GPIO48 GPIO49 is ePWM enable.
	EALLOW;
	GpioCtrlRegs.GPBMUX2.bit.GPIO48 = 0;
	GpioCtrlRegs.GPBDIR.bit.GPIO48  = 1;
	GpioCtrlRegs.GPBPUD.bit.GPIO48  = 0;
	GpioDataRegs.GPBSET.bit.GPIO48  = 1;

	GpioCtrlRegs.GPBMUX2.bit.GPIO49 = 0;
	GpioCtrlRegs.GPBDIR.bit.GPIO49  = 1;
	GpioCtrlRegs.GPBPUD.bit.GPIO49  = 0;
	GpioDataRegs.GPBSET.bit.GPIO49  = 1;
	EDIS;

	InitEPwm1Gpio();
	InitEPwm2Gpio();
	InitEPwm3Gpio();
#if DSP28_EPWM4
	InitEPwm4Gpio();
#endif // endif DSP28_EPWM4
#if DSP28_EPWM5
	InitEPwm5Gpio();
#endif // endif DSP28_EPWM5
#if DSP28_EPWM6
	InitEPwm6Gpio();
#endif // endif DSP28_EPWM6
}

void InitEPwm1Gpio(void)
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;    // Enable pull-up on GPIO0 (EPWM1A)
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;    // Enable pull-up on GPIO1 (EPWM1B)

/* Configure ePWM-1 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM1 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;   // Configure GPIO0 as EPWM1A
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;   // Configure GPIO1 as EPWM1B

    EDIS;
}

void InitEPwm2Gpio(void)
{
	EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;    // Enable pull-up on GPIO2 (EPWM2A)
    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;    // Enable pull-up on GPIO3 (EPWM3B)

/* Configure ePWM-2 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM2 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;   // Configure GPIO2 as EPWM2A
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;   // Configure GPIO3 as EPWM2B

    EDIS;
}

void InitEPwm3Gpio(void)
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;    // Enable pull-up on GPIO4 (EPWM3A)
    GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;    // Enable pull-up on GPIO5 (EPWM3B)

/* Configure ePWM-3 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM3 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;   // Configure GPIO4 as EPWM3A
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;   // Configure GPIO5 as EPWM3B

    EDIS;
}


#if DSP28_EPWM4
void InitEPwm4Gpio(void)
{
	EALLOW;
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

	GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;    // Enable pull-up on GPIO6 (EPWM4A)
	GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;    // Enable pull-up on GPIO7 (EPWM4B)

/* Configure ePWM-4 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM4 functional pins.
// Comment out other unwanted lines.

	GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;   // Configure GPIO6 as EPWM4A
	GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1;   // Configure GPIO7 as EPWM4B

	EDIS;
}
#endif // endif DSP28_EPWM4


#if DSP28_EPWM5
void InitEPwm5Gpio(void)
{
   EALLOW;
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO8 = 0;    // Enable pull-up on GPIO8 (EPWM5A)
    GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;    // Enable pull-up on GPIO9 (EPWM5B)

/* Configure ePWM-5 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM5 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 1;   // Configure GPIO8 as EPWM5A
    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 1;   // Configure GPIO9 as EPWM5B

    EDIS;
}
#endif // endif DSP28_EPWM5


#if DSP28_EPWM6
void InitEPwm6Gpio(void)
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO10 = 0;    // Enable pull-up on GPIO10 (EPWM6A)
    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;    // Enable pull-up on GPIO11 (EPWM6B)

/* Configure ePWM-6 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM6 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 1;   // Configure GPIO10 as EPWM6A
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 1;   // Configure GPIO11 as EPWM6B

    EDIS;
}
#endif // endif DSP28_EPWM6

//---------------------------------------------------------------------------
// Example: InitEPwmSyncGpio:
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as ePWM Synch pins
//

void InitEPwmSyncGpio(void)
{

   EALLOW;

/* Configure EPWMSYNCI  */

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;    // Enable pull-up on GPIO6 (EPWMSYNCI)
// GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;   // Enable pull-up on GPIO32 (EPWMSYNCI)

/* Set qualification for selected pins to asynch only */
// This will select synch to SYSCLKOUT for the selected pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAQSEL1.bit.GPIO6 = 0;   // Synch to SYSCLKOUT GPIO6 (EPWMSYNCI)
// GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 0;  // Synch to SYSCLKOUT GPIO32 (EPWMSYNCI)

/* Configure EPwmSync pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPwmSync functional pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 2;    // Enable pull-up on GPIO6 (EPWMSYNCI)
// GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 2;   // Enable pull-up on GPIO32 (EPWMSYNCI)



/* Configure EPWMSYNC0  */

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

// GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;    // Enable pull-up on GPIO6 (EPWMSYNC0)
   GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;   // Enable pull-up on GPIO33 (EPWMSYNC0)

// GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 3;    // Enable pull-up on GPIO6 (EPWMSYNC0)
   GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 2;   // Enable pull-up on GPIO33 (EPWMSYNC0)

}



//---------------------------------------------------------------------------
// Example: InitTzGpio:
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as Trip Zone (TZ) pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//

void InitTzGpio(void)
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.
	GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;    // Enable pull-up on GPIO12 (TZ1)
	GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;    // Enable pull-up on GPIO13 (TZ2)
	GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0;    // Enable pull-up on GPIO14 (TZ3)
	GpioCtrlRegs.GPAPUD.bit.GPIO15 = 0;    // Enable pull-up on GPIO15 (TZ4)

	GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;    // Enable pull-up on GPIO16 (TZ5)
//	GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;    // Enable pull-up on GPIO28 (TZ5)

//	GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;    // Enable pull-up on GPIO17 (TZ6)
//	GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;    // Enable pull-up on GPIO29 (TZ6)

/* Set qualification for selected pins to asynch only */
// Inputs are synchronized to SYSCLKOUT by default.
// This will select asynch (no qualification) for the selected pins.
// Comment out other unwanted lines.

	GpioCtrlRegs.GPAQSEL1.bit.GPIO12 = 3;  // Asynch input GPIO12 (TZ1)
	GpioCtrlRegs.GPAQSEL1.bit.GPIO13 = 3;  // Asynch input GPIO13 (TZ2)
	GpioCtrlRegs.GPAQSEL1.bit.GPIO14 = 3;  // Asynch input GPIO14 (TZ3)
	GpioCtrlRegs.GPAQSEL1.bit.GPIO15 = 3;  // Asynch input GPIO15 (TZ4)

	GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3;  // Asynch input GPIO16 (TZ5)
//	GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;  // Asynch input GPIO28 (TZ5)

//	GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3;  // Asynch input GPIO17 (TZ6)
//	GpioCtrlRegs.GPAQSEL2.bit.GPIO29 = 3;  // Asynch input GPIO29 (TZ6)


/* Configure TZ pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be TZ functional pins.
// Comment out other unwanted lines.
	GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 1;  // Configure GPIO12 as TZ1
	GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 1;  // Configure GPIO13 as TZ2
	GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 1;  // Configure GPIO14 as TZ3
	GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 1;  // Configure GPIO15 as TZ4

	GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 3;  // Configure GPIO16 as TZ5
//	GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 3;  // Configure GPIO28 as TZ5

//	GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 3;  // Configure GPIO17 as TZ6
//	GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 3;  // Configure GPIO29 as TZ6

	EDIS;
}


void EPWM_TZINT_HOOK(void)
{
	ESTOP0;
	for(;;);
}

//===========================================================================
// End of file.
//===========================================================================
