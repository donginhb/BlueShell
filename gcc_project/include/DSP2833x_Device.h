// TI File $Revision: /main/5 $
// Checkin $Date: January 22, 2008   16:55:35 $
//###########################################################################
//
// FILE:   DSP2833x_Device.h
//
// TITLE:  DSP2833x Device Definitions.
//
//###########################################################################
// $TI Release: DSP2833x/DSP2823x C/C++ Header Files V1.31 $
// $Release Date: August 4, 2009 $
//###########################################################################

#ifndef DSP2833x_DEVICE_H
#define DSP2833x_DEVICE_H


#ifdef __cplusplus
extern "C" {
#endif


#define   TARGET   1
//---------------------------------------------------------------------------
// User To Select Target Device:

#define   DSP28_28335   TARGET    // Selects '28335/'28235
#define   DSP28_28334   0         // Selects '28334/'28234
#define   DSP28_28332   0         // Selects '28332/'28232


//---------------------------------------------------------------------------
// Common CPU Definitions:
//

extern cregister volatile unsigned int IFR;
extern cregister volatile unsigned int IER;

#define  EINT   asm(" clrc INTM")
#define  DINT   asm(" setc INTM")
#define  ERTM   asm(" clrc DBGM")
#define  DRTM   asm(" setc DBGM")
#define  EALLOW asm(" EALLOW")
#define  EDIS   asm(" EDIS")
#define  ESTOP0 asm(" ESTOP0")

#define M_INT1  0x0001
#define M_INT2  0x0002
#define M_INT3  0x0004
#define M_INT4  0x0008
#define M_INT5  0x0010
#define M_INT6  0x0020
#define M_INT7  0x0040
#define M_INT8  0x0080
#define M_INT9  0x0100
#define M_INT10 0x0200
#define M_INT11 0x0400
#define M_INT12 0x0800
#define M_INT13 0x1000
#define M_INT14 0x2000
#define M_DLOG  0x4000
#define M_RTOS  0x8000

#define BIT0    0x0001
#define BIT1    0x0002
#define BIT2    0x0004
#define BIT3    0x0008
#define BIT4    0x0010
#define BIT5    0x0020
#define BIT6    0x0040
#define BIT7    0x0080
#define BIT8    0x0100
#define BIT9    0x0200
#define BIT10   0x0400
#define BIT11   0x0800
#define BIT12   0x1000
#define BIT13   0x2000
#define BIT14   0x4000
#define BIT15   0x8000



//---------------------------------------------------------------------------
// For Portability, User Is Recommended To Use Following Data Type Size
// Definitions For 16-bit and 32-Bit Signed/Unsigned Integers:
//

#ifndef DSP28_DATA_TYPES
#define DSP28_DATA_TYPES

//////////////////////////////////////////
typedef char               int8;
typedef unsigned char      Uint8;
//////////////////////////////////////////
typedef int                int16;
typedef long               int32;
typedef long long          int64;
typedef unsigned int       Uint16;
typedef unsigned long      Uint32;
typedef unsigned long long Uint64;
typedef float              float32;
typedef long double        float64;

//#include "stdint.h"

typedef union  {
	int16 i16;
	struct {
		int16 lByte:8;
		int16 hByte:8;
	}	bit;
}	int16Bit;

typedef union  {
	int32 i32;
	struct {
		int16Bit lWord;
		int16Bit hWord;
	}	bit;
	float32 f32;
}	int32Bit;

typedef union  {
	Uint16 ui16;
	struct {
		Uint16 lByte:8;
		Uint16 hByte:8;
	}	bit;
}	Uint16Bit;

typedef union  {
	Uint32 ui32;
	struct {
		Uint16Bit lWord;
		Uint16Bit hWord;
	}	bit;
	float32 f32;
}	Uint32Bit;

#endif


#ifndef M_PI
#define M_PI 3.14159265358979
#endif

#ifndef M_SQRT2
#define M_SQRT2  1.41421356237310
#endif

#ifndef M_SQRT3
#define M_SQRT3  1.73205080756888
#endif

#ifndef BOOL
#define BOOL	int
#endif
#ifndef TRUE
#define TRUE	(~0)
#endif
#ifndef FALSE
#define FALSE	(0)
#endif

#ifndef NULL
#ifdef __cplusplus
#define NULL (0L)
#else
#define NULL ((void*)0)
#endif
#endif

#define ARRAYSIZE(a)	(sizeof(a)/sizeof(a[0]))
#define MAX(a,b)		(a>b?a:b)
#define MIN(a,b)		(a<b?a:b)
#define LOBYTE(w)		(w&0xFF)
#define HIBYTE(w)		((w>>8)&0xFF)
#define LOWORD(dw)		(dw&0xFFFF)
#define HIWORD(dw)		((dw>>16)&0xFFFF)
#define BITNx1(n)		((1UL<<(n))-1UL)
#define FABS(x)			((x>0)?(x):(-x))
// 高7位年，中4位月，低5位日，16位字表示到2127年12月31日
#define MAKEDATE(y,m,d)	(((y&0x7F)<<9)|((m&0xF)<<5)|(d&0x1F))

// 使用FLOAT_MATH时，实际的 _iq宏为float32,相关转换宏不起作用
// 将整形的IQn转换为浮点 将浮点转换为整形的IQn
#define _QNtoF32(q, n)	((float32)(q)*(1.0/(1L<<(n))))
#define _F32toQN(q, n)	((int32)((q)*(1L<<(n))))

//---------------------------------------------------------------------------
// Include All Peripheral Header Files:
//

#include "DSP2833x_Adc.h"                // ADC Registers
#include "DSP2833x_DevEmu.h"             // Device Emulation Registers
#include "DSP2833x_CpuTimers.h"          // 32-bit CPU Timers
#include "DSP2833x_ECan.h"               // Enhanced eCAN Registers
#include "DSP2833x_ECap.h"               // Enhanced Capture
#include "DSP2833x_DMA.h"                // DMA Registers
#include "DSP2833x_EPwm.h"               // Enhanced PWM
#include "DSP2833x_EQep.h"               // Enhanced QEP
#include "DSP2833x_Gpio.h"               // General Purpose I/O Registers
#include "DSP2833x_I2c.h"                // I2C Registers
#include "DSP2833x_McBSP.h"              // McBSP
#include "DSP2833x_PieCtrl.h"            // PIE Control Registers
#include "DSP2833x_PieVect.h"            // PIE Vector Table
#include "DSP2833x_Spi.h"                // SPI Registers
#include "DSP2833x_Sci.h"                // SCI Registers
#include "DSP2833x_SysCtrl.h"            // System Control/Power Modes
#include "DSP2833x_XIntrupt.h"           // External Interrupts
#include "DSP2833x_Xintf.h"              // XINTF External Interface

///////////////////////////////////////////////////////
#include "svgen_dq.h"
#include "hal.h"
#include "CRC.h"
#include "Modbus_RTU.h"
#include "Application.h"
#include "RDefine.h"

///////////////////////////////////////////////////////

#if DSP28_28335
#define DSP28_EPWM1  1
#define DSP28_EPWM2  1
#define DSP28_EPWM3  1
#define DSP28_EPWM4  1
#define DSP28_EPWM5  1
#define DSP28_EPWM6  1
#define DSP28_ECAP1  1
#define DSP28_ECAP2  1
#define DSP28_ECAP3  1
#define DSP28_ECAP4  1
#define DSP28_ECAP5  1
#define DSP28_ECAP6  1
#define DSP28_EQEP1  1
#define DSP28_EQEP2  1
#define DSP28_ECANA  1
#define DSP28_ECANB  0		// we do not use ecanb
#define DSP28_MCBSPA 1
#define DSP28_MCBSPB 1
#define DSP28_SPIA   1
#define DSP28_SCIA   1
#define DSP28_SCIB   1
#define DSP28_SCIC   1
#define DSP28_I2CA   1
#endif  // end DSP28_28335

#if DSP28_28334
#define DSP28_EPWM1  1
#define DSP28_EPWM2  1
#define DSP28_EPWM3  1
#define DSP28_EPWM4  1
#define DSP28_EPWM5  1
#define DSP28_EPWM6  1
#define DSP28_ECAP1  1
#define DSP28_ECAP2  1
#define DSP28_ECAP3  1
#define DSP28_ECAP4  1
#define DSP28_ECAP5  0
#define DSP28_ECAP6  0
#define DSP28_EQEP1  1
#define DSP28_EQEP2  1
#define DSP28_ECANA  1
#define DSP28_ECANB  1
#define DSP28_MCBSPA 1
#define DSP28_MCBSPB 1
#define DSP28_SPIA   1
#define DSP28_SCIA   1
#define DSP28_SCIB   1
#define DSP28_SCIC   1
#define DSP28_I2CA   1
#endif  // end DSP28_28334

#if DSP28_28332
#define DSP28_EPWM1  1
#define DSP28_EPWM2  1
#define DSP28_EPWM3  1
#define DSP28_EPWM4  1
#define DSP28_EPWM5  1
#define DSP28_EPWM6  1
#define DSP28_ECAP1  1
#define DSP28_ECAP2  1
#define DSP28_ECAP3  1
#define DSP28_ECAP4  1
#define DSP28_ECAP5  0
#define DSP28_ECAP6  0
#define DSP28_EQEP1  1
#define DSP28_EQEP2  1
#define DSP28_ECANA  1
#define DSP28_ECANB  1
#define DSP28_MCBSPA 1
#define DSP28_MCBSPB 0
#define DSP28_SPIA   1
#define DSP28_SCIA   1
#define DSP28_SCIB   1
#define DSP28_SCIC   0
#define DSP28_I2CA   1
#endif  // end DSP28_28332

// added by Echo
/*-----------------------------------------------------------------------------
      Specify the PLL control register (PLLCR) and divide select (DIVSEL) value.
-----------------------------------------------------------------------------*/
//#define DSP28_DIVSEL   0   // Enable /4 for SYSCLKOUT
//#define DSP28_DIVSEL   1 // Enable /4 for SYSCKOUT
#define DSP28_DIVSEL     2 // Enable /2 for SYSCLKOUT
//#define DSP28_DIVSEL     3 // Enable /1 for SYSCLKOUT

#define DSP28_PLLCR   10
//#define DSP28_PLLCR    9
//#define DSP28_PLLCR    8
//#define DSP28_PLLCR    7
//#define DSP28_PLLCR    6
//#define DSP28_PLLCR    5
//#define DSP28_PLLCR    4
//#define DSP28_PLLCR    3
//#define DSP28_PLLCR    2
//#define DSP28_PLLCR    1
//#define DSP28_PLLCR    0  // PLL is bypassed in this mode
//----------------------------------------------------------------------------


/*-----------------------------------------------------------------------------
      Specify the clock rate of the CPU (SYSCLKOUT) in nS.

      Take into account the input clock frequency and the PLL multiplier
      selected in step 1.

      Use one of the values provided, or define your own.
      The trailing L is required tells the compiler to treat
      the number as a 64-bit value.

      Only one statement should be uncommented.

      Example 1:150 MHz devices:
                CLKIN is a 30MHz crystal.

                In step 1 the user specified PLLCR = 0xA for a
                150Mhz CPU clock (SYSCLKOUT = 150MHz).

                In this case, the CPU_RATE will be 6.667L
                Uncomment the line:  #define CPU_RATE  6.667L

      Example 2:  100 MHz devices:
                  CLKIN is a 20MHz crystal.

	              In step 1 the user specified PLLCR = 0xA for a
	              100Mhz CPU clock (SYSCLKOUT = 100MHz).

	              In this case, the CPU_RATE will be 10.000L
                  Uncomment the line:  #define CPU_RATE  10.000L
-----------------------------------------------------------------------------*/
#define CPU_RATE    6.667L   // for a 150MHz CPU clock speed (SYSCLKOUT)
//#define CPU_RATE    7.143L   // for a 140MHz CPU clock speed (SYSCLKOUT)
//#define CPU_RATE    8.333L   // for a 120MHz CPU clock speed (SYSCLKOUT)
//#define CPU_RATE   10.000L   // for a 100MHz CPU clock speed (SYSCLKOUT)
//#define CPU_RATE   13.330L   // for a 75MHz CPU clock speed (SYSCLKOUT)
//#define CPU_RATE   20.000L   // for a 50MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   33.333L   // for a 30MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   41.667L   // for a 24MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   50.000L   // for a 20MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   66.667L   // for a 15MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE  100.000L   // for a 10MHz CPU clock speed  (SYSCLKOUT)

//----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
      Target device (in DSP2833x_Device.h) determines CPU frequency
      (for examples) - either 150 MHz (for 28335 and 28334) or 100 MHz
      (for 28332). User does not have to change anything here.
-----------------------------------------------------------------------------*/
#if DSP28_28332                   // DSP28_28332 device only
  #define CPU_FRQ_100MHZ    1     // 100 Mhz CPU Freq (20 MHz input freq)
  #define CPU_FRQ_150MHZ    0
#else
  #define CPU_FRQ_100MHZ    0     // DSP28_28335||DSP28_28334
  #define CPU_FRQ_150MHZ    1     // 150 MHz CPU Freq (30 MHz input freq) by DEFAULT
#endif


//---------------------------------------------------------------------------
// Include Example Header Files:
//

#include "DSP2833x_GlobalPrototypes.h"         // Prototypes for global functions within the
                                              // .c files.

#include "DSP2833x_ePwm_defines.h"             // Macros used for PWM examples.
#include "DSP2833x_Dma_defines.h"              // Macros used for DMA examples.
#include "DSP2833x_I2C_defines.h"              // Macros used for I2C examples.

#define PARTNO_28335  0xEF
#define PARTNO_28334  0xEE
#define PARTNO_28332  0xED
#define PARTNO_28235  0xE8
#define PARTNO_28234  0xE7
#define PARTNO_28232  0xE6


// Include files not used with DSP/BIOS
#ifndef DSP28_BIOS
#include "DSP2833x_DefaultISR.h"
#endif


// DO NOT MODIFY THIS LINE.
#define DELAY_US(A)  DSP28x_usDelay(((((long double) A * 1000.0L) / (long double)CPU_RATE) - 9.0L) / 5.0L)

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of DSP2833x_DEVICE_H definition


//===========================================================================
// End of file.
//===========================================================================
