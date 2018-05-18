#include "hal.h"
#include "IQmathLib.h"
#include "DSP2833x_I2c_defines.h"
#include "DSP2833x_I2c.h"
#include "f2833xbmsk.h"
#include "I2C_EEPROM.h"

Uint16 GetADResult(int16 dataType, int16 *result)
{
	if(!result)
	{
		return 0xFFFF;
	}

	result[0]  = AdcMirror.ADCRESULT0;
	result[1]  = AdcMirror.ADCRESULT1;
	result[2]  = AdcMirror.ADCRESULT2;
	result[3]  = AdcMirror.ADCRESULT3;
	result[4]  = AdcMirror.ADCRESULT4;
	result[5]  = AdcMirror.ADCRESULT5;
	result[6]  = AdcMirror.ADCRESULT6;
	result[7]  = AdcMirror.ADCRESULT7;
	result[8]  = AdcMirror.ADCRESULT8;
	result[9]  = AdcMirror.ADCRESULT9;
	result[10] = AdcMirror.ADCRESULT10;
	result[11] = AdcMirror.ADCRESULT11;
	result[12] = AdcMirror.ADCRESULT12;
	result[13] = AdcMirror.ADCRESULT13;
	result[14] = AdcMirror.ADCRESULT14;
	result[15] = AdcMirror.ADCRESULT15;

	return 0;
}

BOOL I2C_EepromTest(Uint16 nBytes)
{
	Uint16 i=0;
	Uint32 input=0, output=0;

	// 4 bytes align
	nBytes &= 0xFFFC;

	// fill eeprom
	for(i=0; i<(nBytes>>2); i++)
	{
		input = i;
		if(I2C_SUCCESS != I2C_WriteUint32(i<<2, &input))
		{
			return FALSE;
		}
		DELAY_MS(8);
	}

	// read and verify eeprom
	for(i=0; i<(nBytes>>2); i++)
	{
		if(I2C_SUCCESS != I2C_ReadUint32(i<<2, &output))
		{
			return FALSE;
		}
		DELAY_MS(1);

		if(output != i)
		{
			return FALSE;
		}
	}

	return TRUE;
}

Uint16 GetDI()
{
	Uint16 DI = 0x0000;

	DI =
		 (GpioDataRegs.GPCDAT.bit.GPIO64<<7)	// DI8
		|(GpioDataRegs.GPCDAT.bit.GPIO65<<6)	// DI7
		|(GpioDataRegs.GPCDAT.bit.GPIO66<<5)	// DI6
		|(GpioDataRegs.GPCDAT.bit.GPIO67<<4)	// DI5
		|(GpioDataRegs.GPCDAT.bit.GPIO68<<3)	// DI4
		|(GpioDataRegs.GPCDAT.bit.GPIO69<<2)	// DI3
		|(GpioDataRegs.GPCDAT.bit.GPIO70<<1)	// DI2
		|(GpioDataRegs.GPCDAT.bit.GPIO71<<0);	// DI1

	return DI | 0xFF00;
}

void SetDO(Uint16 code)
{
	static Uint16 lastDO = 0;

	if(lastDO == code)
	{
		return ;
	}

	lastDO = code;

	// DO1
	if((code>>0)&1)
	{
		GpioDataRegs.GPCSET.bit.GPIO77 = 1;
	}
	else
	{
		GpioDataRegs.GPCCLEAR.bit.GPIO77 = 1;
	}

	// DO2
	if((code>>1)&1)
	{
		GpioDataRegs.GPCSET.bit.GPIO76 = 1;
	}
	else
	{
		GpioDataRegs.GPCCLEAR.bit.GPIO76 = 1;
	}

	// DO3
	if((code>>2)&1)
	{
		GpioDataRegs.GPCSET.bit.GPIO75 = 1;
	}
	else
	{
		GpioDataRegs.GPCCLEAR.bit.GPIO75 = 1;
	}

	// DO4
	if((code>>3)&1)
	{
		GpioDataRegs.GPCSET.bit.GPIO74 = 1;
	}
	else
	{
		GpioDataRegs.GPCCLEAR.bit.GPIO74 = 1;
	}

	// DO5
	if((code>>4)&1)
	{
		GpioDataRegs.GPCSET.bit.GPIO73 = 1;
	}
	else
	{
		GpioDataRegs.GPCCLEAR.bit.GPIO73 = 1;
	}

	// DO6
	if((code>>5)&1)
	{
		GpioDataRegs.GPCSET.bit.GPIO72 = 1;
	}
	else
	{
		GpioDataRegs.GPCCLEAR.bit.GPIO72 = 1;
	}

	// DO7
	if((code>>6)&1)
	{
		GpioDataRegs.GPCSET.bit.GPIO78 = 1;
	}
	else
	{
		GpioDataRegs.GPCCLEAR.bit.GPIO78 = 1;
	}

	// DO8
	if((code>>7)&1)
	{
		GpioDataRegs.GPCSET.bit.GPIO79 = 1;
	}
	else
	{
		GpioDataRegs.GPCCLEAR.bit.GPIO79 = 1;
	}
}


// 在内部SRAM中执行，参数为1000时延时约为70us

#pragma CODE_SECTION(Delay,"ramfuncs");
void Delay(volatile Uint32 n)
{
	while(--n);
}

#pragma CODE_SECTION(DELAY_MS,"ramfuncs");
void DELAY_MS(Uint16 n)
{
	while(n--)
	{
		KickDog();
		DELAY_US(500);
		KickDog();
		DELAY_US(500);
	}
}


