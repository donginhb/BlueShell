// TI File $Revision: /main/1 $
// Checkin $Date: August 18, 2006   13:46:25 $
//###########################################################################
//
// FILE:	DSP2833x_Gpio.c
//
// TITLE:	DSP2833x General Purpose I/O Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP2833x/DSP2823x C/C++ Header Files V1.31 $
// $Release Date: August 4, 2009 $
//###########################################################################

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

//---------------------------------------------------------------------------
// InitGpio:
//---------------------------------------------------------------------------
// This function initializes the Gpio to a known (default) state.
//
// For more details on configuring GPIO's as peripheral functions,
// refer to the individual peripheral examples and/or GPIO setup example.
void InitGpio(void)
{
   EALLOW;

   // Each GPIO pin can be:
   // a) a GPIO input/output
   // b) peripheral function 1
   // c) peripheral function 2
   // d) peripheral function 3
   // By default, all are GPIO Inputs
   GpioCtrlRegs.GPAMUX1.all = 0x0000;     // GPIO functionality GPIO0-GPIO15
   GpioCtrlRegs.GPAMUX2.all = 0x0000;     // GPIO functionality GPIO16-GPIO31
   GpioCtrlRegs.GPBMUX1.all = 0x0000;     // GPIO functionality GPIO32-GPIO39
   GpioCtrlRegs.GPBMUX2.all = 0x0000;     // GPIO functionality GPIO48-GPIO63
   GpioCtrlRegs.GPCMUX1.all = 0x0000;     // GPIO functionality GPIO64-GPIO79
   GpioCtrlRegs.GPCMUX2.all = 0x0000;     // GPIO functionality GPIO80-GPIO95

   GpioCtrlRegs.GPADIR.all = 0x0000;      // GPIO0-GPIO31 are inputs
   GpioCtrlRegs.GPBDIR.all = 0x0000;      // GPIO32-GPIO63 are inputs
   GpioCtrlRegs.GPCDIR.all = 0x0000;      // GPI064-GPIO95 are inputs

   // Each input can have different qualification
   // a) input synchronized to SYSCLKOUT
   // b) input qualified by a sampling window
   // c) input sent asynchronously (valid for peripheral inputs only)
   GpioCtrlRegs.GPAQSEL1.all = 0x0000;    // GPIO0-GPIO15 Synch to SYSCLKOUT
   GpioCtrlRegs.GPAQSEL2.all = 0x0000;    // GPIO16-GPIO31 Synch to SYSCLKOUT
   GpioCtrlRegs.GPBQSEL1.all = 0x0000;    // GPIO32-GPIO39 Synch to SYSCLKOUT
   GpioCtrlRegs.GPBQSEL2.all = 0x0000;    // GPIO48-GPIO63 Synch to SYSCLKOUT

   // Pull-ups can be enabled or disabled.
   GpioCtrlRegs.GPAPUD.all = 0x0000;      // Pullup's enabled GPIO0-GPIO31
   GpioCtrlRegs.GPBPUD.all = 0x0000;      // Pullup's enabled GPIO32-GPIO63
   GpioCtrlRegs.GPCPUD.all = 0x0000;      // Pullup's enabled GPIO64-GPIO79

   //GpioCtrlRegs.GPAPUD.all = 0xFFFF;    // Pullup's disabled GPIO0-GPIO31
   //GpioCtrlRegs.GPBPUD.all = 0xFFFF;    // Pullup's disabled GPIO32-GPIO34
   //GpioCtrlRegs.GPCPUD.all = 0xFFFF     // Pullup's disabled GPIO64-GPIO79

	// 8 Digital output
	GpioCtrlRegs.GPCMUX1.bit.GPIO79 = 0;	// DO8
	GpioCtrlRegs.GPCMUX1.bit.GPIO78 = 0;	// DO7
	GpioCtrlRegs.GPCMUX1.bit.GPIO77 = 0;	// DO1
	GpioCtrlRegs.GPCMUX1.bit.GPIO76 = 0;	// DO2
	GpioCtrlRegs.GPCMUX1.bit.GPIO75 = 0;	// DO3
	GpioCtrlRegs.GPCMUX1.bit.GPIO74 = 0;	// DO4
	GpioCtrlRegs.GPCMUX1.bit.GPIO73 = 0;	// DO5
	GpioCtrlRegs.GPCMUX1.bit.GPIO72 = 0;	// DO6

	// 先设置输出寄存器，再设置为输出，防止上电后状态不确定
	GpioDataRegs.GPCDAT.bit.GPIO79 = 1;		// DO8
	GpioDataRegs.GPCDAT.bit.GPIO78 = 1;		// DO7
	GpioDataRegs.GPCDAT.bit.GPIO77 = 1;		// DO1
	GpioDataRegs.GPCDAT.bit.GPIO76 = 1;		// DO2
	GpioDataRegs.GPCDAT.bit.GPIO75 = 1;		// DO3
	GpioDataRegs.GPCDAT.bit.GPIO74 = 1;		// DO4
	GpioDataRegs.GPCDAT.bit.GPIO73 = 1;		// DO5
	GpioDataRegs.GPCDAT.bit.GPIO72 = 1;		// DO6

	GpioCtrlRegs.GPCDIR.bit.GPIO79 = 1;		// DO8
	GpioCtrlRegs.GPCDIR.bit.GPIO78 = 1;		// DO7
	GpioCtrlRegs.GPCDIR.bit.GPIO77 = 1;		// DO1
	GpioCtrlRegs.GPCDIR.bit.GPIO76 = 1;		// DO2
	GpioCtrlRegs.GPCDIR.bit.GPIO75 = 1;		// DO3
	GpioCtrlRegs.GPCDIR.bit.GPIO74 = 1;		// DO4
	GpioCtrlRegs.GPCDIR.bit.GPIO73 = 1;		// DO5
	GpioCtrlRegs.GPCDIR.bit.GPIO72 = 1;		// DO6

	GpioCtrlRegs.GPCPUD.bit.GPIO79 = 0;		// DO8
	GpioCtrlRegs.GPCPUD.bit.GPIO78 = 0;		// DO7
	GpioCtrlRegs.GPCPUD.bit.GPIO77 = 0;		// DO1
	GpioCtrlRegs.GPCPUD.bit.GPIO76 = 0;		// DO2
	GpioCtrlRegs.GPCPUD.bit.GPIO75 = 0;		// DO3
	GpioCtrlRegs.GPCPUD.bit.GPIO74 = 0;		// DO4
	GpioCtrlRegs.GPCPUD.bit.GPIO73 = 0;		// DO5
	GpioCtrlRegs.GPCPUD.bit.GPIO72 = 0;		// DO6

	// 8 Digital input
	GpioCtrlRegs.GPCMUX1.bit.GPIO71 = 0;	// DI1
	GpioCtrlRegs.GPCMUX1.bit.GPIO70 = 0;	// DI2
	GpioCtrlRegs.GPCMUX1.bit.GPIO69 = 0;	// DI3
	GpioCtrlRegs.GPCMUX1.bit.GPIO68 = 0;	// DI4
	GpioCtrlRegs.GPCMUX1.bit.GPIO67 = 0;	// DI5
	GpioCtrlRegs.GPCMUX1.bit.GPIO66 = 0;	// DI6
	GpioCtrlRegs.GPCMUX1.bit.GPIO65 = 0;	// DI7
	GpioCtrlRegs.GPCMUX1.bit.GPIO64 = 0;	// DI8

	GpioCtrlRegs.GPCDIR.bit.GPIO71 = 0;		// DI1
	GpioCtrlRegs.GPCDIR.bit.GPIO70 = 0;		// DI2
	GpioCtrlRegs.GPCDIR.bit.GPIO69 = 0;		// DI3
	GpioCtrlRegs.GPCDIR.bit.GPIO68 = 0;		// DI4
	GpioCtrlRegs.GPCDIR.bit.GPIO67 = 0;		// DI5
	GpioCtrlRegs.GPCDIR.bit.GPIO66 = 0;		// DI6
	GpioCtrlRegs.GPCDIR.bit.GPIO65 = 0;		// DI7
	GpioCtrlRegs.GPCDIR.bit.GPIO64 = 0;		// DI8

	GpioCtrlRegs.GPCPUD.bit.GPIO71 = 0;		// DI1
	GpioCtrlRegs.GPCPUD.bit.GPIO70 = 0;		// DI2
	GpioCtrlRegs.GPCPUD.bit.GPIO69 = 0;		// DI3
	GpioCtrlRegs.GPCPUD.bit.GPIO68 = 0;		// DI4
	GpioCtrlRegs.GPCPUD.bit.GPIO67 = 0;		// DI5
	GpioCtrlRegs.GPCPUD.bit.GPIO66 = 0;		// DI6
	GpioCtrlRegs.GPCPUD.bit.GPIO65 = 0;		// DI7
	GpioCtrlRegs.GPCPUD.bit.GPIO64 = 0;		// DI8

	GpioCtrlRegs.GPBMUX2.bit.GPIO48 = 0;	// PWM_EN1
	GpioCtrlRegs.GPBDIR.bit.GPIO48 = 1;
	GpioDataRegs.GPBDAT.bit.GPIO48 = 1;

	GpioCtrlRegs.GPBMUX2.bit.GPIO49 = 0;	// PWM_EN2
	GpioCtrlRegs.GPBDIR.bit.GPIO49 = 1;
	GpioDataRegs.GPBDAT.bit.GPIO49 = 1;

	GpioCtrlRegs.GPBMUX2.bit.GPIO50 = 0;	// SDA
	GpioCtrlRegs.GPBDIR.bit.GPIO50 = 1;
	GpioDataRegs.GPBDAT.bit.GPIO50 = 1;

	GpioCtrlRegs.GPBMUX2.bit.GPIO51 = 0;	// SCL
	GpioCtrlRegs.GPBDIR.bit.GPIO51 = 1;
	GpioDataRegs.GPBDAT.bit.GPIO51 = 1;

	GpioCtrlRegs.GPCMUX2.bit.GPIO84 = 0;	// BENCH
	GpioCtrlRegs.GPCDIR.bit.GPIO84 = 1;
	GpioDataRegs.GPCDAT.bit.GPIO84 = 1;

	GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 0;	// LED2
	GpioCtrlRegs.GPBDIR.bit.GPIO39 = 1;
	GpioDataRegs.GPBDAT.bit.GPIO39 = 1;

	GpioCtrlRegs.GPAPUD.bit.GPIO25 = 0;		// Enable pull-up on GPIO25 (CAP2)
	GpioCtrlRegs.GPAQSEL2.bit.GPIO25 = 0;	// Synch to SYSCLKOUT GPIO25 (CAP2)
	GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 1;	// Configure GPIO25 as CAP2

	EDIS;
}

//===========================================================================
// End of file.
//===========================================================================
