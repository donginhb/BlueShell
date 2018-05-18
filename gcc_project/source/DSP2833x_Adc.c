// TI File $Revision: /main/5 $
// Checkin $Date: October 23, 2007   13:34:09 $
//###########################################################################
//
// FILE:	DSP2833x_Adc.c
//
// TITLE:	DSP2833x ADC Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP2833x/DSP2823x C/C++ Header Files V1.31 $
// $Release Date: August 4, 2009 $
//###########################################################################

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#define ADC_usDELAY  5000L
// ADC start parameters
#if (CPU_FRQ_150MHZ)     // Default - 150 MHz SYSCLKOUT
  #define ADC_MODCLK 0x3 // HSPCLK = SYSCLKOUT/2*ADC_MODCLK2 = 150/(2*3)   = 25.0 MHz
#endif
#if (CPU_FRQ_100MHZ)
  #define ADC_MODCLK 0x2 // HSPCLK = SYSCLKOUT/2*ADC_MODCLK2 = 100/(2*2)   = 25.0 MHz
#endif
#define ADC_SHCLK  0xf   // S/H width in ADC module periods                        = 16 ADC clocks
#define AVG        1000  // Average sample limit
#define ZOFFSET    0x00  // Average Zero offset
#define BUF_SIZE   160    // Sample buffer size

//---------------------------------------------------------------------------
// InitAdc:
//---------------------------------------------------------------------------
// This function initializes ADC to a known state.
//
void InitAdc(void)
{
	extern void DSP28x_usDelay(Uint32 Count);

	// *IMPORTANT*
	// The ADC_cal function, which  copies the ADC calibration values from TI reserved
	// OTP into the ADCREFSEL and ADCOFFTRIM registers, occurs automatically in the
	// Boot ROM. If the boot ROM code is bypassed during the debug process, the
	// following function MUST be called for the ADC to function according
	// to specification. The clocks to the ADC MUST be enabled before calling this
	// function.
	// See the device data manual and/or the ADC Reference
	// Manual for more information.

	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;
	ADC_cal();
	EDIS;

	// To powerup the ADC the ADCENCLK bit should be set first to enable
	// clocks, followed by powering up the bandgap, reference circuitry, and ADC core.
	// Before the first conversion is performed a 5ms delay must be observed
	// after power up to give all analog circuits time to power up and settle

	// Please note that for the delay function below to operate correctly the
	// CPU_RATE define statement in the DSP2833x_Examples.h file must
	// contain the correct CPU clock period in nanoseconds.

	AdcRegs.ADCTRL3.all = 0x00E0;  // Power up bandgap/reference/ADC circuits
	DELAY_US(ADC_usDELAY);         // Delay before converting ADC channels

	// Specific ADC setup for this example:
	AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;       // 0 Non-Cascaded Mode; 1 Cascaded Mode
	AdcRegs.ADCTRL1.bit.SEQ_OVRD = 0;		// Allow wrap-around
	AdcRegs.ADCTRL1.bit.CONT_RUN = 0;		// 0 start/stop mode, 1 continue run mode
	AdcRegs.ADCTRL1.bit.CPS = 0;			// HSPCLK 经过ACQ_PS分频以后的分频系数，0不分频，1二分频
	AdcRegs.ADCTRL1.bit.ACQ_PS = 7;			// S/H width in ADC module periods  = 8 ADC clocks
	AdcRegs.ADCTRL1.bit.SUSMOD = 0;			// 忽略仿真挂起
	AdcRegs.ADCTRL1.bit.RESET = 0;			// 写入1复位整个ADC

//	AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;		// 排序器复位到CONV00
//	AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 0;
	AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;  	// Enable SEQ1 interrupt (every EOS)
	AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1;	// Enable SOCA from ePWM to start SEQ1
//	AdcRegs.ADCTRL2.bit.RST_SEQ2 = 0;		// 排序器复位到CONV08

	AdcRegs.ADCTRL3.bit.ADCBGRFDN = 3;
	AdcRegs.ADCTRL3.bit.ADCPWDN = 1;
	AdcRegs.ADCTRL3.bit.ADCCLKPS = 5;		// ADCCLK = 75/(2*5) = 7.5 MHz @ HSCLK = 75MHz AdcRegs.ADCTRL1.bit.CPS=0
	AdcRegs.ADCTRL3.bit.SMODE_SEL = 0;		// 0 顺序采样, 1 同步采样

	AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 15;   // Set up ADC to perform 4 conversions for every SOC
	AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0;
	AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x1;
	AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 0x2;
	AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 0x3;
	AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 0x4;
	AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 0x5;
	AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 0x6;
	AdcRegs.ADCCHSELSEQ2.bit.CONV07 = 0x7;
	AdcRegs.ADCCHSELSEQ3.bit.CONV08 = 0x8;
	AdcRegs.ADCCHSELSEQ3.bit.CONV09 = 0x9;
	AdcRegs.ADCCHSELSEQ3.bit.CONV10 = 0xA;
	AdcRegs.ADCCHSELSEQ3.bit.CONV11 = 0xB;
	AdcRegs.ADCCHSELSEQ4.bit.CONV12 = 0xC;
	AdcRegs.ADCCHSELSEQ4.bit.CONV13 = 0xD;
	AdcRegs.ADCCHSELSEQ4.bit.CONV14 = 0xE;
	AdcRegs.ADCCHSELSEQ4.bit.CONV15 = 0xF;

	DSP28x_usDelay(20L);

	PieCtrlRegs.PIEIER1.bit.INTx6 = 1;

	IER |= M_INT1; 							// Enable CPU Interrupt 1
}

//===========================================================================
// End of file.
//===========================================================================
