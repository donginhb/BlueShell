#ifndef _PCS_H_
#define _PCS_H_

#include "DSP28x_Project.h"
#include "Flash2833x_API_Library.h"
#include "I2C_EEPROM.h"
#include "parameter.h"
#include "IQmathLib.h"

typedef struct
{
	Uint16 sec;
	Uint16 min;
	Uint16 hour;
	Uint16 day;
}	TIME_REG;

struct DI_STATUS_BITS
{
	Uint16 unused1:5;				// bit0
	Uint16 Emerge:1;			//
	Uint16 Stop:1;		//
	Uint16 Start:1;			//
	Uint16 unused2:8;			// Œ¥”√ 
};


struct DO_STATUS_BITS
{
	Uint16 unused1:2;				// bit0
	Uint16 FanKM:1;			//
	Uint16 DCKM:1;		//
	Uint16 ChargeKM:1;			//
	Uint16 ACKM:1;				//
	Uint16 unused2:10;				//
};


typedef union
{
	Uint16 all;
	struct DI_STATUS_BITS bit;
}	DI_REG;

typedef union
{
	Uint16 all;
	struct DO_STATUS_BITS bit;
}	DO_REG;

typedef struct
{
	Uint16 dspBuild;
	Uint16 pwmPrd;
	Uint16 pwmCmp;
	Uint16 eepromCmd;
	Uint16 eepromAddr;
	Uint16 eepromDataH;
	Uint16 eepromDataL;
	Uint16 adBuf[16];
	DI_REG DI;
	DO_REG DO;
	TIME_REG now;
	Uint16 timeCmd;
	struct rtc_time time;
}	SYS_REG;

typedef struct
{
	int32 buf[N_SAMPLE];
	int16 i;
}	GRAPH;

void GRAPH_calc(GRAPH*, int32);


extern SYS_REG sys;

extern void InitSystem(void);
extern void Run(void);

#endif

