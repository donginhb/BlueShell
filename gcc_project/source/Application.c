/*
 * Application.c
 *
 *  Created on: 2016-12-22
 *      Author: OnlyMe
 */
#define APPLICATION_GLOBALS
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "Application.h"
extern long LoopCount1;
Uint16 RXDataLength=0;
void SCI_TX_Character(volatile struct SCI_REGS  *SCIn,Uint8 data)
{
	while(SCIn->SCICTL2.bit.TXRDY!=1);
	SCIn->SCITXBUF=data;
}

void SCI_TX_Frame(volatile struct SCI_REGS  *SCIn,Uint8 *Buffer,Uint16 Length)
{
	Uint16 cnt;
	for(cnt=0;cnt<Length;cnt++)
	{
		SCI_TX_Character(SCIn,Buffer[cnt]);
	}
}

Uint16 SCI_FIFOTX_Data(volatile struct SCI_REGS  *SCIn,Uint8 *Buffer,Uint16 TXLength)
{

	while((TX_RX_Struct.TXBufferIndex<TXLength)&&(SCIn->SCIFFTX.bit.TXFFST<16))  //还有数据要发送
	{
		SCIn->SCITXBUF = Buffer[TX_RX_Struct.TXBufferIndex++];
	}

	//TX_RX_Struct.TXTimeoutCNT=0;

	if(TXLength==TX_RX_Struct.TXBufferIndex)
	{
		if((SCIn->SCIFFTX.bit.TXFFST==0)&&(SCIn->SCICTL2.bit.TXEMPTY == 1))//SCIBTXBUF和移位寄存器TXSHF都空
		{
			TX_RX_Struct.TXStatus = LINE_IDLE;
			TX_RX_Struct.TXBufferIndex=0;
			return TRUE;
		}
	}
	return FALSE;

}

Uint16 SCI_FIFORX_Data(volatile struct SCI_REGS  *SCIn,Uint8 *Buffer,Uint16 BufferLength)
{
    // LoopCount1++;
	if(SCIn->SCIFFRX.bit.RXFFST>0)
	{
		TX_RX_Struct.RXStatus=RX_ONGOING;
		while(SCIn->SCIFFRX.bit.RXFFST>0)
		{
			TX_RX_Struct.RXBuffer[TX_RX_Struct.RXBufferIndex++]=SCIn->SCIRXBUF.bit.RXDT;
			if(TX_RX_Struct.RXBufferIndex>BufferLength)
			{
			   // LoopCount1++;	
				TX_RX_Struct.RXBufferIndex=0;
				return FALSE;
			}
		}
		TX_RX_Struct.RXTimeoutCNT=0;
	}

	if(TX_RX_Struct.RXStatus==LINE_IDLE) TX_RX_Struct.RXTimeoutCNT=0;

	if((TX_RX_Struct.RXStatus==RX_ONGOING) && (TX_RX_Struct.RXTimeoutCNT>2))//TX_RX_Struct.RXTimeoutCNT 根据中断间隔而定，保证有9600波特率1.5ms延时；115200波特率200us延时
	{
		Uint16 cnt=0;

		for(cnt=0;cnt<TX_RX_Struct.RXBufferIndex;cnt++)
			Buffer[cnt]=TX_RX_Struct.RXBuffer[cnt];


		TX_RX_Struct.RXStatus=LINE_IDLE;
		TX_RX_Struct.RXDataLength=TX_RX_Struct.RXBufferIndex;
		TX_RX_Struct.RXBufferIndex=0;
		return TX_RX_Struct.RXDataLength;
	}
	return FALSE;

}

void Init_RX_Struct()
{
	TX_RX_Struct.RXBufferIndex=0;
	TX_RX_Struct.RXDataLength=0;
	TX_RX_Struct.RXStatus=LINE_IDLE;
	TX_RX_Struct.RXTimeoutCNT=0;
	TX_RX_Struct.TXBufferIndex=0;
	TX_RX_Struct.TXDataLength=0;
	TX_RX_Struct.TXStatus=LINE_IDLE;
	TX_RX_Struct.TXTimeoutCNT=0;

	WaveIndex.BeginIndex=10;
	WaveIndex.DataLength=300;
	WaveIndex.TotalIndex=WaveIndex.BeginIndex;
	WaveIndex.TempCNT=0;

	TM_Grid_State1=0;
	TM_Grid_HF=0;
	TM_Grid_SF1=0;
	TM_Grid_SF2=0;
	TM_Grid_ServerF=0;


}
