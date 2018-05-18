/**********************************************************************
* File: Gpio.c
* Devices: TMS320F2833x
* Author: David M. Alter, Texas Instruments Inc.
* History:
*   12/18/07 - original (D. Alter)
**********************************************************************/
#include "DSP2833x_Device.h"			// Peripheral address definitions
#include "DSP2833x_Examples.h"				// Main include file


/**********************************************************************
* Function: InitGpio()
*
* Description: Initializes the shared GPIO pins on the F2833x.
**********************************************************************/
void InitGpio(void)
{
	asm(" EALLOW");								// Enable EALLOW protected register access

//--- Group A pins
    GpioCtrlRegs.GPACTRL.all  = 0x00000000;		// QUALPRD =1xSCLKOUT for  group A GPIO0-31
	GpioCtrlRegs.GPAQSEL1.all = 0x00000000;		// No qualification for all group A GPIO 0-15
	GpioCtrlRegs.GPAQSEL2.all = 0x00000000;		// No qualification for  group A GPIO 16-31
	GpioCtrlRegs.GPADIR.all   = 0xF0858FFF;		// group A GPIO 0-1 15 16 18 23 28 29 30 31 AS OUTPUT OTHER AS INPUT
	GpioCtrlRegs.GPAPUD.all   = 0x000F0000;     //Pullups enabled GPIO31-20,GPIO0-15 disabled GPIO16-19

 
	GpioCtrlRegs.GPAMUX1.bit.GPIO0  = 1;		// 0=GPIO   1=EPWM1A     2=rsvd       3=rsvd
	GpioCtrlRegs.GPAMUX1.bit.GPIO1  = 1;		// 0=GPIO   1=EPWM1B     2=ECAP6      3=rsvd
	GpioCtrlRegs.GPAMUX1.bit.GPIO2  = 1;		// 0=GPIO   1=EPWM2A     2=rsvd       3=rsvd
	GpioCtrlRegs.GPAMUX1.bit.GPIO3  = 1;		// 0=GPIO   1=EPWM2B     2=ECAP5      3=rsvd
	GpioCtrlRegs.GPAMUX1.bit.GPIO4  = 1;		// 0=GPIO   1=EPWM3A     2=rsvd       3=rsvd
	GpioCtrlRegs.GPAMUX1.bit.GPIO5  = 1;		// 0=GPIO   1=EPWM3B     2=MFSRA      3=ECAP1
	GpioCtrlRegs.GPAMUX1.bit.GPIO6  = 1;		// 0=GPIO   1=EPWM4A     2=EPWMSYNCI  3=EPWMSYNCO
	GpioCtrlRegs.GPAMUX1.bit.GPIO7  = 1;		// 0=GPIO   1=EPWM4B     2=MCLKRA     3=ECAP2
	GpioCtrlRegs.GPAMUX1.bit.GPIO8  = 1;		// 0=GPIO   1=EPWM5A     2=CANTXB     3=ADCSOCAO
	GpioCtrlRegs.GPAMUX1.bit.GPIO9  = 1;		// 0=DGPIO  1=EPWM5B     2=SCITXDB    3=ECAP3
	GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 1;		// 0=GPIO   1=EPWM6A     2=CANRXB     3=ADCSOCBO
	GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 1;		// 0=GPIO   1=EPWM6B     2=SCIRXDB    3=ECAP4
	GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 1;		// 0=GPIO   1=TZ1        2=CANTXB     3=SPISIMOB
	GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 1;		// 0=GPIO   1=TZ2        2=CANRXB     3=SPISOMIB
	GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 1;		// 0=GPIO   1=TZ3/XHOLD  2=SCITXDB    3=SPICLKB
	GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 1;	   	// 0=GPIO   1=TZ4/XHOLDA 2=SCIRXDB    3=SPISTEB

	GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 2;		// 0=GPIO   1=SPISIMOA   2=CANTXB     3=TZ5
	GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 2;		// 0=GPIO   1=SPISOMIA   2=CANRXB     3=TZ6
	GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 2;		// 0=GPIO   1=SPICLKA    2=SCITXDB    3=CANRXA
	GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 2;		// 0=GPIO   1=SPISTEA    2=SCIRXDB    3=CANTXA
	GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 0;		// 0=GPIO  NMI 1=EQEP1A     2=MDXA       3=CANTXB
	GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 0;		// 0=GPIO  INT1 1=EQEP1B     2=MDRA       3=CANRXB
	GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 0;		// 0=GPIO  INT2 1=EQEP1S     2=MCLKXA     3=SCITXDB
	GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 0;		// 0=GPIO  SYSRUN 1=EQEP1I     2=MFSXA      3=SCIRXDB
	GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 1;		// 0=GPIO   1=ECAP1      2=EQEP2A     3=MDXB
	GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 1;		// 0=GPIO   1=ECAP2      2=EQEP2B     3=MDRB
	GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 1;		// 0=GPIO   1=ECAP3      2=EQEP2I     3=MCLKXB
	GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 1;		// 0=GPIO   1=ECAP4      2=EQEP2S     3=MFSXB  
	GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 2;		// 0=GPIO  BANK1 1=SCIRXDA    2=XZCS6      3=XZCS6
	GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 2;		// 0=GPIO  A19 1=SCITXDA    2=XA19       3=XA19
	GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 2;		// 0=GPIO  A18 1=CANRXA     2=XA18       3=XA18
	GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 2;		// 0=GPIO  A17 1=CANTXA     2=XA17       3=XA17
   
//--- Group B pins
    GpioCtrlRegs.GPBCTRL.all  = 0x00000000;		// QUALPRD = 1XSYSCLKOUT for  group B GPIO48-63
	GpioCtrlRegs.GPBQSEL1.all = 0x00000000;		// No qualification for all group B GPIO 32-47
	GpioCtrlRegs.GPBQSEL2.all = 0x00000000;		// No qualification for all group B GPIO 48-63
 
	GpioCtrlRegs.GPBDIR.all   = 0x8340FFF8;		//  group B GPIO 32-34,48-53,55,58-62 are AS inputs ,OTHER AS OUTPUTS
	GpioCtrlRegs.GPBPUD.all   = 0xC0000003;		//  group B GPIO 32 33 62 63 pullups Disenabled,OTHER Pullups Enabled

	GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 1;		// 0=GPIO  1=SDAA      2=EPWMSYNCI  3=ADCSOCAO
	GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 1;		// 0=GPIO  1=SCLA      2=EPWMSYNCO  3=ADCSOCBO
	GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 2;		// 0=GPIO  1=ECAP1     2=XREADY     3=XREADY
	GpioCtrlRegs.GPBMUX1.bit.GPIO35 = 2;		// 0=GPIO  1=SCITXDA   2=XR/W       3=XR/W
	GpioCtrlRegs.GPBMUX1.bit.GPIO36 = 2;		// 0=GPIO  1=SCIRXDA   2=XZCS0      3=XZCS0
	GpioCtrlRegs.GPBMUX1.bit.GPIO37 = 2;		// 0=GPIO  1=ECAP2     2=XZCS7      3=XZCS7
	GpioCtrlRegs.GPBMUX1.bit.GPIO38 = 2;		// 0=GPIO  1=rsvd      2=XWE0       3=XWE0
	GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 2;		// 0=GPIO  1=rsvd      2=XA16       3=XA16
	GpioCtrlRegs.GPBMUX1.bit.GPIO40 = 2;		// 0=GPIO  1=rsvd      2=XA0/XWE1   3=XA0/XWE1
	GpioCtrlRegs.GPBMUX1.bit.GPIO41 = 2;		// 0=GPIO  1=rsvd      2=XA1        3=XA1
	GpioCtrlRegs.GPBMUX1.bit.GPIO42 = 2;		// 0=GPIO  1=rsvd      2=XA2        3=XA2
	GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 2;		// 0=GPIO  1=rsvd      2=XA3        3=XA3
	GpioCtrlRegs.GPBMUX1.bit.GPIO44 = 2;		// 0=GPIO  1=rsvd      2=XA4        3=XA4
	GpioCtrlRegs.GPBMUX1.bit.GPIO45 = 2;		// 0=GPIO  1=rsvd      2=XA5        3=XA5
	GpioCtrlRegs.GPBMUX1.bit.GPIO46 = 2;		// 0=GPIO  1=rsvd      2=XA6        3=XA6
	GpioCtrlRegs.GPBMUX1.bit.GPIO47 = 2;		// 0=GPIO  1=rsvd      2=XA7        3=XA7

	GpioCtrlRegs.GPBMUX2.bit.GPIO48 = 1;		// 0=GPIO  1=ECAP5     2=XD31       3=XD31
	GpioCtrlRegs.GPBMUX2.bit.GPIO49 = 1;		// 0=GPIO  1=ECAP6     2=XD30       3=XD30
	GpioCtrlRegs.GPBMUX2.bit.GPIO50 = 1;		// 0=GPIO  1=EQEP1A    2=XD29       3=XD29
	GpioCtrlRegs.GPBMUX2.bit.GPIO51 = 1;		// 0=GPIO  1=EQEP1B    2=XD28       3=XD28
	GpioCtrlRegs.GPBMUX2.bit.GPIO52 = 1;		// 0=GPIO  1=EQEP1S    2=XD27       3=XD27
	GpioCtrlRegs.GPBMUX2.bit.GPIO53 = 1;		// 0=GPIO  1=EQEP1I    2=XD26       3=XD26
	GpioCtrlRegs.GPBMUX2.bit.GPIO54 = 1;		// 0=GPIO  1=SPISIMOA  2=XD25       3=XD25
	GpioCtrlRegs.GPBMUX2.bit.GPIO55 = 1;		// 0=GPIO  1=SPISOMIA  2=XD24       3=XD24
	GpioCtrlRegs.GPBMUX2.bit.GPIO56 = 1;		// 0=GPIO  1=SPICLKA   2=XD23       3=XD23
	GpioCtrlRegs.GPBMUX2.bit.GPIO57 = 1;		// 0=GPIO  1=SPISTEA   2=XD22       3=XD22
	GpioCtrlRegs.GPBMUX2.bit.GPIO58 = 0;		// 0=GPIO  1=MCLKRA    2=XD21       3=XD21
	GpioCtrlRegs.GPBMUX2.bit.GPIO59 = 0;		// 0=GPIO  1=MFSRA     2=XD20       3=XD20
	GpioCtrlRegs.GPBMUX2.bit.GPIO60 = 0;		// 0=GPIO  1=MCLKRB    2=XD19       3=XD19
	GpioCtrlRegs.GPBMUX2.bit.GPIO61 = 0;		// 0=GPIO  1=MFSRB     2=XD18       3=XD18
	GpioCtrlRegs.GPBMUX2.bit.GPIO62 = 1;		// 0=GPIO  1=SCIRXDC   2=XD17       3=XD17
	GpioCtrlRegs.GPBMUX2.bit.GPIO63 = 1;		// 0=GPIO  1=SCITXDC   2=XD16       3=XD16
   

//--- Group C pins
	GpioCtrlRegs.GPCDIR.all = 0xFFFFFFFF;		// All group C GPIO are Outputs
	GpioCtrlRegs.GPCPUD.all = 0x00000000;		// All group C pullups enabled

	GpioCtrlRegs.GPCMUX1.bit.GPIO64 = 2;		// 0=GPIO  1=GPIO      2=XD15       3=XD15
	GpioCtrlRegs.GPCMUX1.bit.GPIO65 = 2;		// 0=GPIO  1=GPIO      2=XD14       3=XD14
	GpioCtrlRegs.GPCMUX1.bit.GPIO66 = 2;		// 0=GPIO  1=GPIO      2=XD13       3=XD13
	GpioCtrlRegs.GPCMUX1.bit.GPIO67 = 2;		// 0=GPIO  1=GPIO      2=XD12       3=XD12
	GpioCtrlRegs.GPCMUX1.bit.GPIO68 = 2;		// 0=GPIO  1=GPIO      2=XD11       3=XD11
	GpioCtrlRegs.GPCMUX1.bit.GPIO69 = 2;		// 0=GPIO  1=GPIO      2=XD10       3=XD10
	GpioCtrlRegs.GPCMUX1.bit.GPIO70 = 2;		// 0=GPIO  1=GPIO      2=XD9        3=XD9
	GpioCtrlRegs.GPCMUX1.bit.GPIO71 = 2;		// 0=GPIO  1=GPIO      2=XD8        3=XD8
	GpioCtrlRegs.GPCMUX1.bit.GPIO72 = 2;		// 0=GPIO  1=GPIO      2=XD7        3=XD7
	GpioCtrlRegs.GPCMUX1.bit.GPIO73 = 2;		// 0=GPIO  1=GPIO      2=XD6        3=XD6
	GpioCtrlRegs.GPCMUX1.bit.GPIO74 = 2;		// 0=GPIO  1=GPIO      2=XD5        3=XD5
	GpioCtrlRegs.GPCMUX1.bit.GPIO75 = 2;		// 0=GPIO  1=GPIO      2=XD4        3=XD4
	GpioCtrlRegs.GPCMUX1.bit.GPIO76 = 2;		// 0=GPIO  1=GPIO      2=XD3        3=XD3
	GpioCtrlRegs.GPCMUX1.bit.GPIO77 = 2;		// 0=GPIO  1=GPIO      2=XD2        3=XD2
	GpioCtrlRegs.GPCMUX1.bit.GPIO78 = 2;		// 0=GPIO  1=GPIO      2=XD1        3=XD1
	GpioCtrlRegs.GPCMUX1.bit.GPIO79 = 2;		// 0=GPIO  1=GPIO      2=XD0        3=XD0

	GpioCtrlRegs.GPCMUX2.bit.GPIO80 = 2;		// 0=GPIO  1=GPIO      2=XA8        3=XA8
	GpioCtrlRegs.GPCMUX2.bit.GPIO81 = 2;		// 0=GPIO  1=GPIO      2=XA9        3=XA9
	GpioCtrlRegs.GPCMUX2.bit.GPIO82 = 2;		// 0=GPIO  1=GPIO      2=XA10       3=XA10
	GpioCtrlRegs.GPCMUX2.bit.GPIO83 = 2;		// 0=GPIO  1=GPIO      2=XA11       3=XA11
	GpioCtrlRegs.GPCMUX2.bit.GPIO84 = 2;		// 0=GPIO  1=GPIO      2=XA12       3=XA12
	GpioCtrlRegs.GPCMUX2.bit.GPIO85 = 2;		// 0=GPIO  1=GPIO      2=XA13       3=XA13
	GpioCtrlRegs.GPCMUX2.bit.GPIO86 = 2;		// 0=GPIO  1=GPIO      2=XA14       3=XA14
	GpioCtrlRegs.GPCMUX2.bit.GPIO87 = 2;		// 0=GPIO  1=GPIO      2=XA15       3=XA15

//--- External interrupt selection
	GpioIntRegs.GPIOXINT1SEL.all = 0x0015;		// GPIO21is XINT1 source
	GpioIntRegs.GPIOXINT2SEL.all = 0x0016;		// GPIO22 is XINT2 source
	GpioIntRegs.GPIOXINT3SEL.all = 0x0030;		// GPIO48 is XINT3 source
	GpioIntRegs.GPIOXINT4SEL.all = 0x0031;		// GPIO49 is XINT4 source
	GpioIntRegs.GPIOXINT5SEL.all = 0x0032;		// GPIO50 is XINT5 source
	GpioIntRegs.GPIOXINT6SEL.all = 0x0000;		// GPIO32 is XINT6 source
	GpioIntRegs.GPIOXINT7SEL.all = 0x0000;		// GPIO32 is XINT7 source
	GpioIntRegs.GPIOXNMISEL.all = 0x00014;		// GPIO20 is XNMI source

	XIntruptRegs.XINT1CR.all = 0x0000;			// XINT1 disabled
	XIntruptRegs.XINT2CR.all = 0x0000;			// XINT2 disabled
	XIntruptRegs.XINT3CR.all = 0x0000;			// XINT3 disabled
	XIntruptRegs.XINT4CR.all = 0x0000;			// XINT4 disabled
	XIntruptRegs.XINT5CR.all = 0x0000;			// XINT5 disabled
	XIntruptRegs.XINT6CR.all = 0x0000;			// XINT6 disabled
	XIntruptRegs.XINT7CR.all = 0x0000;			// XINT7 disabled
	XIntruptRegs.XNMICR.all = 0x0000;			// XNMI disabled

//--- Low-power mode selection
	GpioIntRegs.GPIOLPMSEL.all = 0x00000000;	// No pin selected for HALT and STANBY wakeup (reset default)

//--- Selected pin configurations
//	GpioCtrlRegs.GPBDIR.bit.GPIO32 = 1;			// GPIO32 is an output (connected to LED on eZdspF28335)

//--- Finish up
	asm(" EDIS");								// Disable EALLOW protected register access

} // end InitGpio()


//--- end of file -----------------------------------------------------
