/**
 * EEPROM read & write with C2000 I2C.
 * Author: Dong Xiao <echo@xaatx.com> 2014.3.3
 * --add ISL1208 RTC support: Dong Xiao <echo@xaatx.com> 2014.3.29
 */


#ifndef _I2C_EEPROM_H_
#define _I2C_EEPROM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "DSP2833x_Device.h"
#include "DSP2833x_I2c.h"
#include "DSP2833x_I2c_defines.h"

/*-----------------------------------------------------------------------------
   Module CLK = 10M, SCL = 80k
   1. Specify the device.
      Define the device to be used as "1" (no quotes).
      Define all other devices as "0" (no quotes).
      150M device such as F28335...
      100M device such as F2808...
      60M  device such as F28035...
-----------------------------------------------------------------------------*/
#define I2C_150M_DEVICE   1
#define I2C_100M_DEVICE   0
#define I2C_60M_DEVICE    0

// for 24LC32 and above eeprom, define this macro.
// for 24LC16 and below eeprom, comment this line out.
//#define I2C_EEPROM_24LC32	1

extern void I2C_Init(void);
extern Uint16 I2C_WriteUint32(Uint16 addr, const Uint32 *dat);
extern Uint16 I2C_ReadUint32(Uint16 addr, Uint32 *dat);

struct rtc_time {
	Uint16 tm_sec;
	Uint16 tm_min;
	Uint16 tm_hour;
	Uint16 tm_mday;
	Uint16 tm_mon;
	Uint16 tm_year;
	Uint16 tm_wday;
	Uint16 tm_yday;
	Uint16 tm_isdst;
};
extern Uint16 ISL1208_WriteTime(const struct rtc_time *tm);
extern Uint16 ISL1208_ReadTime( struct rtc_time *tm);
extern Uint16 EncodeRtcTime(const struct rtc_time *tm, Uint32 *t);
extern Uint16 DecodeRtcTime(struct rtc_time *tm, Uint32 t);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

