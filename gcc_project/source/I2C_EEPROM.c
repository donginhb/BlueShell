/**
 * EEPROM read & write with C2000 I2C.
 * --add ISL1208 RTC support: Dong Xiao <echo@xaatx.com> 2014.3.29
 */

#include "I2C_EEPROM.h"

#define I2C_DEV_EEPROM	0x50
#define I2C_DEV_ISL1208	0x6F

/* Register map */
/* rtc section */
#define ISL1208_REG_SC  0x00
#define ISL1208_REG_MN  0x01
#define ISL1208_REG_HR  0x02
#define ISL1208_REG_HR_MIL     (1<<7)	/* 24h/12h mode */
#define ISL1208_REG_HR_PM      (1<<5)	/* PM/AM bit in 12h mode */
#define ISL1208_REG_DT  0x03
#define ISL1208_REG_MO  0x04
#define ISL1208_REG_YR  0x05
#define ISL1208_REG_DW  0x06
#define ISL1208_RTC_SECTION_LEN 7

/* control/status section */
#define ISL1208_REG_SR  0x07
#define ISL1208_REG_SR_ARST    (1<<7)	/* auto reset */
#define ISL1208_REG_SR_XTOSCB  (1<<6)	/* crystal oscillator */
#define ISL1208_REG_SR_WRTC    (1<<4)	/* write rtc */
#define ISL1208_REG_SR_ALM     (1<<2)	/* alarm */
#define ISL1208_REG_SR_BAT     (1<<1)	/* battery */
#define ISL1208_REG_SR_RTCF    (1<<0)	/* rtc fail */
#define ISL1208_REG_INT 0x08
#define ISL1208_REG_INT_ALME   (1<<6)   /* alarm enable */
#define ISL1208_REG_INT_IM     (1<<7)   /* interrupt/alarm mode */
#define ISL1208_REG_09  0x09	/* reserved */
#define ISL1208_REG_ATR 0x0a
#define ISL1208_REG_DTR 0x0b

/* alarm section */
#define ISL1208_REG_SCA 0x0c
#define ISL1208_REG_MNA 0x0d
#define ISL1208_REG_HRA 0x0e
#define ISL1208_REG_DTA 0x0f
#define ISL1208_REG_MOA 0x10
#define ISL1208_REG_DWA 0x11
#define ISL1208_ALARM_SECTION_LEN 6

/* user section */
#define ISL1208_REG_USR1 0x12
#define ISL1208_REG_USR2 0x13
#define ISL1208_USR_SECTION_LEN 2

#define ISL1208_REG_MAX_LEN 0x14

/* Macros to convert 2-digit BCD into binary and vice versa */
#define	BIN2BCD(b)	(((b)%10) | (((b)/10)<<4))
#define	BCD2BIN(b)	(((b)&0xf) + ((b)>>4)*10)

static Uint16 ISL1208_WriteReg(Uint16 addr, const Uint16 *buf, Uint16 len);
static Uint16 ISL1208_ReadReg(Uint16 addr, Uint16 *buf, Uint16 len);

void I2C_Init(void)
{
	// Initialize I2C
	I2caRegs.I2CMDR.bit.IRS = 0;	// Take I2C into reset
	I2caRegs.I2CPSC.bit.IPSC = 14;	// Module clk = 10M,Prescaler - need 7-12 Mhz on module clk = SYSCLKOUT/(IPSC+1)
#if I2C_150M_DEVICE
	I2caRegs.I2CPSC.bit.IPSC = 14;	// Module clk = 10M
#endif
#if I2C_100M_DEVICE
	I2caRegs.I2CPSC.bit.IPSC = 9;	// Module clk = 10M
#endif
#if I2C_60M_DEVICE
	I2caRegs.I2CPSC.bit.IPSC = 5;	// Module clk = 10M
#endif
	I2caRegs.I2CCLKL = 45;			// ICCL,NOTE: must be non zero
	I2caRegs.I2CCLKH = 70;			// ICCH,NOTE: must be non zero
	//                                   150MHz
	//  master clock frequency = --------------------------- = 80kHz
	//	                         (IPSC+1)[(ICCL+5)+(ICCH+5)]
	I2caRegs.I2CSAR = I2C_DEV_EEPROM;		// 00h.7Fh,the 7-bit slave address that the I2C module transmits when it is in the master-transmitter mode.ode
	I2caRegs.I2CIER.all = 0x00;		// Disable SCD & ARDY interrupts
	I2caRegs.I2CMDR.bit.IRS = 1;	// Take I2C out of reset
									// Stop I2C when suspended
	I2caRegs.I2CFFTX.all = 0x6000;	// Enable FIFO mode and TXFIFO
	I2caRegs.I2CFFRX.all = 0x2040;	// Enable RXFIFO, clear RXFFINT,

	I2caRegs.I2CCNT = 0x0000;
	I2caRegs.I2CSTR.all = 0xFFFF;
}


// Addr is counted by BYTEs, so two LSB of addr should be zero.
// Write cycle of EEPROM is 5ms+, after this routine return,
// wait for 5ms before access the content of EEPROM
Uint16 I2C_WriteUint32(Uint16 addr, const Uint32 *dat)
{
	volatile Uint16 cnt = 0;

	if(!dat)
	{
		return I2C_ERROR;
	}

	// Wait until the STP bit is cleared from any previous master communication.
	// Clearing of this bit by the module is delayed after the SCD bit is set.
	// If this bit is not checked prior to initiating a new message, the I2C
	// could get confused.

	cnt = 0;
	while (1 == I2caRegs.I2CMDR.bit.STP)
	{
		if (cnt++ > 9000)	// 6000
		{
			return I2C_STP_NOT_READY_ERROR;
		}
	}

	// Setup slave address
#if I2C_EEPROM_24LC32
	I2caRegs.I2CSAR = I2C_DEV_EEPROM;
#else
	I2caRegs.I2CSAR = (Uint16)(((addr>>8) & 0x0007) | I2C_DEV_EEPROM);
#endif

	// Check if bus busy
	if (1 == I2caRegs.I2CSTR.bit.BB)
	{
		return I2C_BUS_BUSY_ERROR;
	}


#if I2C_EEPROM_24LC32
	// Setup number of bytes to send: 16 bits addr + 32 bits data
	I2caRegs.I2CCNT = 2 + 4;
	I2caRegs.I2CDXR = (addr>>8*1) & 0xFF;	// high byte
	I2caRegs.I2CDXR = (addr>>8*0) & 0xFF;	// Low byte little endian
#else
	// Setup number of bytes to send: 8 bits addr + 32 bits data, MSB of addr is I2CSAR
	I2caRegs.I2CCNT = 1 + 4;
	I2caRegs.I2CDXR = addr & 0xFF;
#endif

	// Setup data to send
	I2caRegs.I2CDXR = (*dat>>8*0) & 0xFF;
	I2caRegs.I2CDXR = (*dat>>8*1) & 0xFF;
	I2caRegs.I2CDXR = (*dat>>8*2) & 0xFF;
	I2caRegs.I2CDXR = (*dat>>8*3) & 0xFF;

	// Send start as master transmitter
	I2caRegs.I2CMDR.all = 0x6E20;

	return I2C_SUCCESS;
}

Uint16 I2C_ReadUint32(Uint16 addr, Uint32 *dat)
{
	volatile Uint16 cnt = 0;

	if(!dat)
	{
		return I2C_ERROR;
	}

	cnt = 0;
	while (1 == I2caRegs.I2CMDR.bit.STP)
	{
		if(cnt++ > 9000)	// 6000
		{
			return I2C_STP_NOT_READY_ERROR;
		}
	}

	// Setup slave address
#if I2C_EEPROM_24LC32
	I2caRegs.I2CSAR = I2C_DEV_EEPROM;
#else
	I2caRegs.I2CSAR = (Uint16)(((addr>>8) & 0x0007) | I2C_DEV_EEPROM);
#endif

	// Check if bus busy
	if (1 == I2caRegs.I2CSTR.bit.BB)
	{
		return I2C_BUS_BUSY_ERROR;
	}

#if I2C_EEPROM_24LC32
	// Setup number of bytes to send: 16 bits addr + 32 bits data
	I2caRegs.I2CCNT = 2;
	I2caRegs.I2CDXR = (addr>>8*1) & 0xFF;	// high byte
	I2caRegs.I2CDXR = (addr>>8*0) & 0xFF;	// Low byte little endian
#else
	// Setup number of bytes to send: 8 bits addr + 32 bits data, MSB of addr is I2CSAR
	I2caRegs.I2CCNT = 1;
	I2caRegs.I2CDXR = addr & 0xFF;
#endif

	I2caRegs.I2CMDR.all = 0x6620;			// Send data to setup EEPROM address
	I2caRegs.I2CSTR.bit.SCD = 1;			// clear stop condition

	cnt = 0;
	while (1 != I2caRegs.I2CSTR.bit.ARDY)
	{
		if(cnt++ > 6000)	// 4000			// on GZ test, is 173, about 0.95ms
		{
			return I2C_ERROR;
		}
	}

	// Setup number of bytes to receive: 32 bits data
	I2caRegs.I2CCNT = 4;
	I2caRegs.I2CMDR.all = 0x6C20;			//

	cnt = 0;
	while (1 != I2caRegs.I2CSTR.bit.SCD)	// wait for Stop condition
	{
		if(cnt++ > 9000)	// 6000
		{
			return I2C_ERROR;
		}
	}

	*dat  = ((Uint32)I2caRegs.I2CDRR)<<(8*0);	// little endian
	*dat |= ((Uint32)I2caRegs.I2CDRR)<<(8*1);
	*dat |= ((Uint32)I2caRegs.I2CDRR)<<(8*2);
	*dat |= ((Uint32)I2caRegs.I2CDRR)<<(8*3);

	return I2C_SUCCESS;
}


Uint16 ISL1208_WriteReg(Uint16 addr, const Uint16 *buf, Uint16 len)
{
	volatile Uint16 cnt = 0;

	if(!buf || (addr+len) > ISL1208_REG_MAX_LEN)
	{
		return I2C_ERROR;
	}

	// Wait until the STP bit is cleared from any previous master communication.
	// Clearing of this bit by the module is delayed after the SCD bit is set.
	// If this bit is not checked prior to initiating a new message, the I2C
	// could get confused.

	cnt = 0;
	while (1 == I2caRegs.I2CMDR.bit.STP)
	{
		if (cnt++ > 9000)	// 6000
		{
			return I2C_STP_NOT_READY_ERROR;
		}
	}

	// Setup slave address
	I2caRegs.I2CSAR = I2C_DEV_ISL1208;

	// Check if bus busy
	if (1 == I2caRegs.I2CSTR.bit.BB)
	{
		return I2C_BUS_BUSY_ERROR;
	}

	// Setup number of bytes to send
	I2caRegs.I2CCNT = 1 + len;
	I2caRegs.I2CDXR = addr & 0xFF;
	// Setup data to send
	for(cnt=0; cnt<len; cnt++)
	{
		I2caRegs.I2CDXR = buf[cnt] & 0xFF;
	}

	// Send start as master transmitter
	I2caRegs.I2CMDR.all = 0x6E20;

	return I2C_SUCCESS;
}


Uint16 ISL1208_ReadReg(Uint16 addr, Uint16 *buf, Uint16 len)
{
	volatile Uint16 cnt = 0;

	if(!buf || (addr+len) > ISL1208_REG_MAX_LEN)
	{
		return I2C_ERROR;
	}

	cnt = 0;
	while (1 == I2caRegs.I2CMDR.bit.STP)
	{
		if(cnt++ > 9000)	// 6000
		{
			return I2C_STP_NOT_READY_ERROR;
		}
	}

	// Setup slave address
	I2caRegs.I2CSAR = I2C_DEV_ISL1208;

	// Check if bus busy
	if (1 == I2caRegs.I2CSTR.bit.BB)
	{
		return I2C_BUS_BUSY_ERROR;
	}

	// Setup number of bytes to send: 8 bits addr
	I2caRegs.I2CCNT = 1;
	I2caRegs.I2CDXR = addr & 0xFF;

	I2caRegs.I2CMDR.all = 0x6620;			// Send data to setup RTC address
	I2caRegs.I2CSTR.bit.SCD = 1;			// clear stop condition

	cnt = 0;
	while (1 != I2caRegs.I2CSTR.bit.ARDY)
	{
		if(cnt++ > 6000)	// 4000			// on GZ test, is 173, about 0.95ms
		{
			return I2C_ERROR;
		}
	}

	// Setup number of bytes to receive
	I2caRegs.I2CCNT = len;
	I2caRegs.I2CMDR.all = 0x6C20;			//

	cnt = 0;
	while (1 != I2caRegs.I2CSTR.bit.SCD)	// wait for Stop condition
	{
		if(cnt++ > 9000)	// 6000
		{
			return I2C_ERROR;
		}
	}

	for(cnt=0; cnt<len; cnt++)
	{
		buf[cnt] = I2caRegs.I2CDRR & 0xFF;
	}

	return I2C_SUCCESS;
}


Uint16 ISL1208_ReadTime(struct rtc_time *tm)
{
	Uint16 buf[7] = {0};
	Uint16 ret = I2C_ERROR, hr;

	if(!tm)
	{
		return I2C_ERROR;
	}

	// read status
	ret = ISL1208_ReadReg(7, buf, 1);
	if(ret != I2C_SUCCESS)
	{
		return ret;
	}

	// read time
	ret = ISL1208_ReadReg(0, buf, 7);
	if(ret != I2C_SUCCESS)
	{
		return ret;
	}

	tm->tm_sec  = BCD2BIN(buf[ISL1208_REG_SC]);
	tm->tm_min  = BCD2BIN(buf[ISL1208_REG_MN]);
	hr = buf[ISL1208_REG_HR];
	tm->tm_hour = BCD2BIN((hr&ISL1208_REG_HR_MIL) ? hr&0x3F : hr&ISL1208_REG_HR_PM ? (hr&0x1F+12) : hr&0x1F);
	tm->tm_mday = BCD2BIN(buf[ISL1208_REG_DT]);
	tm->tm_mon  = BCD2BIN(buf[ISL1208_REG_MO]);
	tm->tm_year = BCD2BIN(buf[ISL1208_REG_YR]);
	tm->tm_wday = BCD2BIN(buf[ISL1208_REG_DW]);

	return I2C_SUCCESS;
}

Uint16 ISL1208_WriteTime(const struct rtc_time *tm)
{
	Uint16 buf[16] = {0};
	Uint16 ret = I2C_ERROR;

	if(!tm)
	{
		return I2C_ERROR;
	}

	// read status
	ret = ISL1208_ReadReg(7, buf, 1);
	if(ret != I2C_SUCCESS)
	{
		return ret;
	}

	buf[0] |= ISL1208_REG_SR_WRTC;
	// write enable
	ret = ISL1208_WriteReg(7, buf, 1);
	if(ret != I2C_SUCCESS)
	{
		return ret;
	}

	buf[ISL1208_REG_SC] = BIN2BCD(tm->tm_sec);
	buf[ISL1208_REG_MN] = BIN2BCD(tm->tm_min);
	buf[ISL1208_REG_HR] = BIN2BCD(tm->tm_hour) | ISL1208_REG_HR_MIL;
	buf[ISL1208_REG_DT] = BIN2BCD(tm->tm_mday);
	buf[ISL1208_REG_MO] = BIN2BCD(tm->tm_mon);
	buf[ISL1208_REG_YR] = BIN2BCD(tm->tm_year);
	buf[ISL1208_REG_DW] = BIN2BCD(tm->tm_wday);

	ret = ISL1208_WriteReg(0, buf, 7);

	// read status
	ret = ISL1208_ReadReg(7, buf, 1);
	if(ret != I2C_SUCCESS)
	{
		return ret;
	}

	buf[0] &= ~ISL1208_REG_SR_WRTC;
	// write disable
	ret = ISL1208_WriteReg(7, buf, 1);
	if(ret != I2C_SUCCESS)
	{
		return ret;
	}

	return I2C_SUCCESS;
}


Uint16 EncodeRtcTime(const struct rtc_time *tm, Uint32 *t)
{
	if(!tm || !t)
	{
		return I2C_ERROR;
	}

	*t  = ((Uint32)tm->tm_sec&0x2F)<<0;		// 6 bits
	*t |= ((Uint32)tm->tm_min&0x2F)<<6;		// 6 bits
	*t |= ((Uint32)tm->tm_hour&0x1F)<<12;	// 5 bits
	*t |= ((Uint32)tm->tm_mday&0x1F)<<17;	// 5 bits
	*t |= ((Uint32)tm->tm_mon&0xF)<<22;		// 4 bits
	*t |= ((Uint32)tm->tm_year&0x1F)<<26;	// 6 bits

	return I2C_SUCCESS;
}

Uint16 DecodeRtcTime(struct rtc_time *tm, Uint32 t)
{
	if(!tm)
	{
		return I2C_ERROR;
	}

	tm->tm_sec  = (t>>0)&0x2F;		// 6 bits
	tm->tm_min  = (t>>6)&0x2F;		// 6 bits
	tm->tm_hour = (t>>12)&0x1F;		// 5 bits
	tm->tm_mday = (t>>17)&0x1F;		// 5 bits
	tm->tm_mon  = (t>>22)&0xF;		// 4 bits
	tm->tm_year = (t>>26)&0x1F;		// 6 bits

	return I2C_SUCCESS;
}


