 
//###########################################################################
//
// FILE:   DSP2833x_Examples.h
//
// TITLE:  DSP2833x Device Definitions.
//
 

#ifndef DSP2833x_PROJECT_H
#define DSP2833x_PROJECT_H

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File


#ifdef __cplusplus
extern "C" {
#endif


//SYSTEM RUN SET ControlS 
#define	  SYSRUN_SET   GpioDataRegs.GPASET.bit.GPIO23
#define	  SYSRUN_CLEAR  GpioDataRegs.GPACLEAR.bit.GPIO23
void delay (Uint16 t);
void configtestledON(void);
void configtestledOFF(void);
void Delay_func(void);
void InitXintf(void);
void   I2CA_Init(void);
Uint16 I2CA_WriteData(struct I2CMSG *msg);
Uint16 I2CA_ReadData(struct I2CMSG *msg);
void   WriteData(struct I2CMSG *msg,struct CALENDAR  *MsgBuffer,Uint16 MemoryAdd,Uint16 NumOfBytes);
interrupt void i2c_int1a_isr(void);
void I2CTASKX1(void);
void I2CTASKX2(void);
#define ADC_cal_func_ptr (void (*)(void))0x380080
#define I2C_SLAVE_ADDR       0x68
#define I2C_NUMBYTES          1
#define I2C_RNUMBYTES         7
#define I2C_RTC_ADDR  0x00
#define ADC_BUF_LEN			50				// ADC buffer length 

#define  YEAR  0x2012
#define  YEARL  0x12
#define	 MONTH  0x03
#define  DAY    0x08
#define  WEEK   0x01
#define	 HOUR   0x15
#define	 MINUTE  0x10
#define  SECOND  0x00
#define  RTC_COUNT  0x10
#define	SC		0x0000

// Global variables
// Two bytes will be used for the outgoing address,

struct I2CMSG I2cMsgOut1={I2C_MSGSTAT_SEND_WITHSTOP,
                          I2C_SLAVE_ADDR,
                          I2C_NUMBYTES,
                          I2C_RTC_ADDR,
                          };


struct I2CMSG I2cMsgIn1={ I2C_MSGSTAT_SEND_NOSTOP,
                          I2C_SLAVE_ADDR,
                          I2C_RNUMBYTES,
                          I2C_RTC_ADDR,
                          };

struct I2CMSG *CurrentMsgPtr;	

 
//CPU CLK Define 
#define CPU_FREQ 	 150E6
#define LSPCLK_FREQ  CPU_FREQ/4
#define SCI_FREQ 	 100E3
#define SCI_PRD 	 (LSPCLK_FREQ/(SCI_FREQ*8))-1

//interrupt void sciaTxFifoIsr(void);
//interrupt void sciaRxFifoIsr(void);
//interrupt void scibTxFifoIsr(void);
//interrupt void scibRxFifoIsr(void);
//void scia_fifo_init(void);
//void scib_fifo_init(void);
// Global variables
//Uint16 sdataA[8];    // Send data for SCI-A
Uint16 sdataB[8];    // Send data for SCI-B
Uint16 rdataA[8];    // Received data for SCI-A
Uint16 rdataB[8];    // Received data for SCI-A
Uint16 rdata_pointA; // Used for checking the received data
Uint16 rdata_pointB;
Uint16 AdcBuf[ADC_BUF_LEN];			// ADC data buffer allocation
Uint16 PassCount;
Uint16 FailCount;
#ifdef __cplusplus
}
#endif /* extern "C" */
#endif // DSP2833x_PROJECT_H
