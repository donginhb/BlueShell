/*
 * Application.h
 *
 *  Created on: 2016-12-22
 *      Author: OnlyMe
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_
//全局变量声明
#ifdef APPLICATION_GLOBALS
#define APPLICATION_EXT
#else
#define APPLICATION_EXT extern
#endif
//APPLICATION_EXT

#define  LINE_IDLE   0
#define  RX_ONGOING  1
#define  TX_ONGOING  2





#define InitDIR()                                          \
                     EALLOW;                               \
                     GpioCtrlRegs.GPBPUD.bit.GPIO61 = 0;   \
                     GpioCtrlRegs.GPBDIR.bit.GPIO61 = 1;   \
                     GpioDataRegs.GPBCLEAR.bit.GPIO61 = 1; \
                     EDIS;

//#define RX_EN       GpioDataRegs.GPBCLEAR.bit.GPIO61 = 1
//#define TX_EN       GpioDataRegs.GPBSET.bit.GPIO61 = 1


typedef struct
{
	char   RXBuffer[256];
	char   TXBuffer[256];
	Uint16 RXDataLength;
	Uint16 TXDataLength;
	Uint16 RXStatus;
	Uint16 TXStatus;
	Uint16 RXTimeoutCNT;
	Uint16 TXTimeoutCNT;
	Uint16 RXBufferIndex;
	Uint16 TXBufferIndex;

} SCI_TX_RX_STRUCT;

APPLICATION_EXT SCI_TX_RX_STRUCT  TX_RX_Struct;

void SCI_TX_Character(volatile struct SCI_REGS  *SCIn,Uint8 data);
void SCI_TX_Frame(volatile struct SCI_REGS  *SCIn,Uint8 *Buffer,Uint16 Length);
Uint16 SCI_FIFORX_Data(volatile struct SCI_REGS  *SCIn,Uint8 *Buffer,Uint16 BufferLength);
Uint16 SCI_FIFOTX_Data(volatile struct SCI_REGS  *SCIn,Uint8 *Buffer,Uint16 TXLength);
void Init_RX_Struct();

#endif /* APPLICATION_H_ */
