// TI File $Revision: /main/2 $
// Checkin $Date: March 1, 2007   16:06:07 $
//###########################################################################
//
// FILE:	DSP2833x_Sci.c
//
// TITLE:	DSP2833x SCI Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP2833x/DSP2823x C/C++ Header Files V1.31 $
// $Release Date: August 4, 2009 $
//###########################################################################

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "hal.h"
//#include "Modbus_RTU.h"
//Uint16 ReceivedChar = 0;
//---------------------------------------------------------------------------
// InitSci:
//---------------------------------------------------------------------------
// This function initializes the SCI(s) to a known state.
//
void InitSci(void)
{
	EALLOW;

	// SCIA 固定使用GPIO28 GPIO29
	//GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;    // Enable pull-up for GPIO28 (SCIRXDA)
	//GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;	   // Enable pull-up for GPIO29 (SCITXDA)
	//GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;  // Asynch input GPIO28 (SCIRXDA)
	//GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;   // Configure GPIO28 for SCIRXDA operation
	//GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;   // Configure GPIO29 for SCITXDA operation

/*	GpioCtrlRegs.GPBPUD.bit.GPIO35 = 0;    // Enable pull-up for GPIO28 (SCIRXDA)
	GpioCtrlRegs.GPBPUD.bit.GPIO36 = 0;	   // Enable pull-up for GPIO29 (SCITXDA)

/* Set qualification for selected pins to asynch only */
// Inputs are synchronized to SYSCLKOUT by default.  
// This will select asynch (no qualification) for the selected pins.

//	GpioCtrlRegs.GPBQSEL1.bit.GPIO36 = 3;  // Asynch input GPIO28 (SCIRXDA)

/* Configure SCI-A pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be SCI functional pins.

/*	GpioCtrlRegs.GPBMUX1.bit.GPIO35 = 1;   // Configure GPIO28 for SCIRXDA operation
	GpioCtrlRegs.GPBMUX1.bit.GPIO36 = 1;   // Configure GPIO29 for SCITXDA operation

	GpioCtrlRegs.GPBPUD.bit.GPIO34  = 1; \
	GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0; \
	GpioCtrlRegs.GPBDIR.bit.GPIO34  = 1; \
	GpioDataRegs.GPBCLEAR.bit.GPIO34  = 1;*/	

	// SCIB 管脚可以多组选择
/*	GpioCtrlRegs.GPAPUD.bit.GPIO22 = 0;    // Enable pull-up for GPIO62 (SCIRXDC)
	GpioCtrlRegs.GPAPUD.bit.GPIO23 = 0;	   // Enable pull-up for GPIO63 (SCITXDC)
	GpioCtrlRegs.GPAQSEL2.bit.GPIO23 = 3;  // Asynch input GPIO62 (SCIRXDC)
	GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 3;   // Configure GPIO62 for SCIRXDC operation
	GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 3;   // Configure GPIO63 for SCITXDC operation
*/
	// SCIC 固定使用GPIO62 GPIO63
	GpioCtrlRegs.GPBPUD.bit.GPIO62 = 0;    // Enable pull-up for GPIO62 (SCIRXDC)
	GpioCtrlRegs.GPBPUD.bit.GPIO63 = 0;	   // Enable pull-up for GPIO63 (SCITXDC)
	GpioCtrlRegs.GPBQSEL2.bit.GPIO62 = 3;  // Asynch input GPIO62 (SCIRXDC)
	GpioCtrlRegs.GPBMUX2.bit.GPIO62 = 1;   // Configure GPIO62 for SCIRXDC operation
	GpioCtrlRegs.GPBMUX2.bit.GPIO63 = 1;   // Configure GPIO63 for SCITXDC operation
    //GpioCtrlRegs.GPBDIR.bit.GPIO63 = 1;

	// RS485方向控制，包括SCIB管脚选择
	RS485_CTL_INIT();
	//////////////////////////////////////////////

    // Initialize SCI-B:
		/* loopback   8 bit data */
		//ScibRegs.SCICCR.all = 0x07;	// 1 bit stop, disable parity, idle mode, 8 bits data
/*		ScibRegs.SCICCR.bit.STOPBITS     =SCI_STOPBITS_ONE;
		ScibRegs.SCICCR.bit.SCICHAR      =SCI_CHARLENGTH_8;
		ScibRegs.SCICCR.bit.PARITYENA    =SCI_PARITY_DIS;
		ScibRegs.SCICCR.bit.PARITY       =SCI_PARITY_ODD;
		ScibRegs.SCICCR.bit.LOOPBKENA    =SCI_LOOPBACK_DIS;
		ScibRegs.SCICCR.bit.ADDRIDLE_MODE=SCI_MODE_IDLE;


		ScibRegs.SCIHBAUD = 0x00;//0x01E7 9600
		ScibRegs.SCILBAUD = 0x27;

//		ScibRegs.SCICTL1.all 			 = 0x0003; 		// 使能 TX, RX, internal SCICLK,
		ScibRegs.SCICTL1.bit.RXENA       =SCI_RX_EN;
		ScibRegs.SCICTL1.bit.TXENA       =SCI_TX_EN;
		ScibRegs.SCICTL1.bit.SLEEP       =SCI_SLEEP_MODE_DIS;

		ScibRegs.SCICTL1.bit.RXERRINTENA =SCI_RXERR_INT_DIS;


//		ScibRegs.SCIFFTX.all			 = 0xC000;       //1100增强模式使能，复位发送接收通道
		ScibRegs.SCIFFTX.bit.SCIRST      =SCI_RESET_DIS;
		ScibRegs.SCIFFTX.bit.SCIFFENA    =SCI_FIFO_EN;
		ScibRegs.SCIFFTX.bit.TXFIFOXRESET=SCI_TXFIFO_RESET_DIS;
		ScibRegs.SCIFFTX.bit.TXFFINTCLR  =SCI_TXFIFO_INTF_CLR;
		ScibRegs.SCIFFTX.bit.TXFFIENA    =SCI_TXFIFO_INT_DIS;
		ScibRegs.SCIFFTX.bit.TXFFIL      =SCI_TXFIFO_INTLEVEL_0;


//		ScibRegs.SCIFFRX.all			 = 0x4000;       //0100清除FIFO溢出故障
		ScibRegs.SCIFFRX.bit.RXFFOVRCLR  =SCI_RXFIFO_OVERFLOW_CLR;
		ScibRegs.SCIFFRX.bit.RXFIFORESET =SCI_RXFIFO_RESET_DIS;
		ScibRegs.SCIFFRX.bit.RXFFINTCLR  =SCI_RXFIFO_INTF_CLR;
		ScibRegs.SCIFFRX.bit.RXFFIENA    =SCI_RXFIFO_INT_DIS;
		ScibRegs.SCIFFRX.bit.RXFFIL      =SCI_RXFIFO_INTLEVEL_16;

		ScibRegs.SCIPRI.bit.FREE=1;

//		ScibRegs.SCICTL1.all 			= 0x0023;     	//SCI软件复位
//		ScibRegs.SCIFFTX.bit.SCIRST      =SCI_RESET_EN;
//		ScibRegs.SCIFFTX.bit.SCIRST      =SCI_RESET_DIS;


		ScibRegs.SCIFFTX.bit.TXFIFOXRESET=1;            //FIFO发送复位
		ScibRegs.SCIFFRX.bit.RXFIFORESET=1;	            //FIFO接收复位

		ScibRegs.SCICTL1.bit.SWRESET     =SCI_SW_RESET_DIS;*/

		InitComm();
		Init_RX_Struct();


	//////////////////////////////////////////////

	EDIS;

	PieCtrlRegs.PIEIER9.bit.INTx1 = 1;	// 使能SCIA接收中断 INT9.1
	PieCtrlRegs.PIEIER9.bit.INTx3 = 1;	// 使能SCIB接收中断 INT9.3
	PieCtrlRegs.PIEIER8.bit.INTx5 = 1;	// 使能SCIC接收中断 INT8.5

	IER |= M_INT9;
	IER |= M_INT8;
}

//---------------------------------------------------------------------------
// Example: InitSciGpio:
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as SCI pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//
// Caution:
// Only one GPIO pin should be enabled for SCITXDA/B operation.
// Only one GPIO pin shoudl be enabled for SCIRXDA/B operation.
// Comment out other unwanted lines.

void InitSciGpio()
{
	InitSciaGpio();
	InitScibGpio();
	InitScicGpio();
}

// 3.3V TTL串口
void InitSciaGpio()
{
	EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled disabled by the user.
// This will enable the pullups for the specified pins.

	GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;    // Enable pull-up for GPIO28 (SCIRXDA)
	GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;	   // Enable pull-up for GPIO29 (SCITXDA)

/* Set qualification for selected pins to asynch only */
// Inputs are synchronized to SYSCLKOUT by default.
// This will select asynch (no qualification) for the selected pins.

	GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;  // Asynch input GPIO28 (SCIRXDA)

/* Configure SCI-A pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be SCI functional pins.

	GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;   // Configure GPIO28 for SCIRXDA operation
	GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;   // Configure GPIO29 for SCITXDA operation

	EDIS;
}

#if DSP28_SCIB
void InitScibGpio()
{
	EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

//  GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;     // Enable pull-up for GPIO9  (SCITXDB)
//  GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0;    // Enable pull-up for GPIO14 (SCITXDB)
//	GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;	   // Enable pull-up for GPIO18 (SCITXDB)
    GpioCtrlRegs.GPAPUD.bit.GPIO22 = 0;    // Enable pull-up for GPIO22 (SCITXDB)


//  GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;    // Enable pull-up for GPIO11 (SCIRXDB)
//  GpioCtrlRegs.GPAPUD.bit.GPIO15 = 0;    // Enable pull-up for GPIO15 (SCIRXDB)
//  GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;	   // Enable pull-up for GPIO19 (SCIRXDB)
    GpioCtrlRegs.GPAPUD.bit.GPIO23 = 0;    // Enable pull-up for GPIO23 (SCIRXDB)

/* Set qualification for selected pins to asynch only */
// This will select asynch (no qualification) for the selected pins.
// Comment out other unwanted lines.

//  GpioCtrlRegs.GPAQSEL1.bit.GPIO11 = 3;  // Asynch input GPIO11 (SCIRXDB)
//  GpioCtrlRegs.GPAQSEL1.bit.GPIO15 = 3;  // Asynch input GPIO15 (SCIRXDB)
//	GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3;  // Asynch input GPIO19 (SCIRXDB)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO23 = 3;  // Asynch input GPIO23 (SCIRXDB)

/* Configure SCI-B pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be SCI functional pins.
// Comment out other unwanted lines.

//  GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 2;    // Configure GPIO9 for SCITXDB operation
//  GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 2;   // Configure GPIO14 for SCITXDB operation
//	GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 2;   // Configure GPIO18 for SCITXDB operation
    GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 3;   // Configure GPIO22 for SCITXDB operation

//  GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 2;   // Configure GPIO11 for SCIRXDB operation
//  GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 2;   // Configure GPIO15 for SCIRXDB operation
//  GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 2;   // Configure GPIO19 for SCIRXDB operation
    GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 3;   // Configure GPIO23 for SCIRXDB operation

	// RS485方向控制 GPIO24
	GpioCtrlRegs.GPAPUD.bit.GPIO24  = 1;			// 关闭上拉
	GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 0;			// 设置为GPIO功能
	GpioCtrlRegs.GPADIR.bit.GPIO24  = 1;			// 设置为输出
	GpioDataRegs.GPACLEAR.bit.GPIO24  = 1;			// SCIA初始化为接收状态

    EDIS;
}
#endif // if DSP28_SCIB

#if DSP28_SCIC
void InitScicGpio()
{
	EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled disabled by the user.
// This will enable the pullups for the specified pins.

	GpioCtrlRegs.GPBPUD.bit.GPIO62 = 0;    // Enable pull-up for GPIO62 (SCIRXDC)
	GpioCtrlRegs.GPBPUD.bit.GPIO63 = 0;	   // Enable pull-up for GPIO63 (SCITXDC)

/* Set qualification for selected pins to asynch only */
// Inputs are synchronized to SYSCLKOUT by default.
// This will select asynch (no qualification) for the selected pins.

	GpioCtrlRegs.GPBQSEL2.bit.GPIO62 = 3;  // Asynch input GPIO62 (SCIRXDC)

/* Configure SCI-C pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be SCI functional pins.

	GpioCtrlRegs.GPBMUX2.bit.GPIO62 = 1;   // Configure GPIO62 for SCIRXDC operation
	GpioCtrlRegs.GPBMUX2.bit.GPIO63 = 1;   // Configure GPIO63 for SCITXDC operation

	// RS485方向控制
	GpioCtrlRegs.GPBPUD.bit.GPIO61  = 1;			// 关闭上拉
	GpioCtrlRegs.GPBMUX2.bit.GPIO61 = 0;			// 设置为GPIO功能
	GpioCtrlRegs.GPBDIR.bit.GPIO61  = 1;			// 设置为输出
	GpioDataRegs.GPBCLEAR.bit.GPIO61  = 1;			// SCIC初始化为接收状态

    EDIS;
}
#endif // if DSP28_SCIC


//===========================================================================
// End of file.
//===========================================================================
