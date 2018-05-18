//
// Ӳ�������
// ��ģ���Ӳ���������з�װ��Ϊ�ϲ�����ṩͳһ�Ľӿڣ������㷨��ʵ��Ӳ�������
// ��ģ����Ҫ��Ӳ�������Ա��ɣ���������Ա���ø�ģ���еĺ��������Ҫ�Ĳ���
//

#ifndef _HAL_H_
#define _HAL_H_

#include "DSP2833x_Device.h"
#include "parameter.h"
#include "IQmathLib.h"
#include "I2C_EEPROM.h"

#include "iCLARKE_F.h"
#include "iPARK_F.h"
#include "CLARKE_F.h"
#include "PARK_F.h"
#include "svgen_dq.h"
#include "CNTL_PI_F.h"
#include "rampgen.h"
#include "RMS.h"
// 28335Ӳ�����ע������
// TMS320F28335 PIN169 GPIO84/XA12ͨ�����ߴ���10k�����GND��SCIA����TTL����RS232ʹ�ã�
// �������߿������� SCIA������DSP���������bootloader

// �趨����汾��V2.x��V1.x��Ҫ�仯�����޸���I2C�ӿڵ�λ��
#define _PCS_CTL_V1_	0		// PCS_CTL_V1.x
#define _PCS_CTL_V2_	1		// PCS_CTL_V2.x


//------------------------------------------------------------------------------

// PCB�ϵ�ָʾ�� LED2
#define LED_ON()			GpioDataRegs.GPBCLEAR.bit.GPIO39 = 1;
#define LED_OFF()			GpioDataRegs.GPBSET.bit.GPIO39 = 1;
#define LED_TOG()			GpioDataRegs.GPBTOGGLE.bit.GPIO39 = 1;

// RS485���ƣ�H: ����ʹ�ܣ�L: ����ʹ��
// SCIA RXD=GPIO28 TXD=GPIO29���ӿڹ̶���TTL�޷���ʹ��
// SCIB RXD=GPIO23 TXD=GPIO22, ��������CTL=GPIO24
// SCIC RXD=GPIO62 TXD=GPIO63���ӿڹ̶���CTL=GPIO61
#define SCIA_TX_EN()
#define SCIA_RX_EN()
#define SCIB_TX_EN()		GpioDataRegs.GPBSET.bit.GPIO61 = 1;//GpioDataRegs.GPASET.bit.GPIO24 = 1; DELAY_MS(1);
#define SCIB_RX_EN()		GpioDataRegs.GPBCLEAR.bit.GPIO61 = 1;;//DELAY_MS(2); GpioDataRegs.GPACLEAR.bit.GPIO24 = 1;
#define SCIC_TX_EN()		GpioDataRegs.GPBSET.bit.GPIO61 = 1; DELAY_MS(1);
#define SCIC_RX_EN()		DELAY_MS(2); GpioDataRegs.GPBCLEAR.bit.GPIO61 = 1;
#define RS485_CTL_INIT() 	GpioCtrlRegs.GPAPUD.bit.GPIO22 = 0; \
							GpioCtrlRegs.GPAPUD.bit.GPIO23 = 0; \
							GpioCtrlRegs.GPAQSEL2.bit.GPIO23 = 3; \
							GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 3; \
							GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 3; \
							GpioCtrlRegs.GPAPUD.bit.GPIO24  = 1; \
							GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 0; \
							GpioCtrlRegs.GPADIR.bit.GPIO24  = 1; \
							GpioDataRegs.GPACLEAR.bit.GPIO24 = 1; \
							GpioCtrlRegs.GPBPUD.bit.GPIO61  = 1; \
							GpioCtrlRegs.GPBMUX2.bit.GPIO61 = 0; \
							GpioCtrlRegs.GPBDIR.bit.GPIO61  = 1; \
							GpioDataRegs.GPBCLEAR.bit.GPIO61  = 1;
// GPIO
#define BENCH_ON()			(GpioDataRegs.GPCSET.bit.GPIO84=1)
#define BENCH_OFF()		(GpioDataRegs.GPCCLEAR.bit.GPIO84=1)
#define BEHCH_TOG()		(GpioDataRegs.GPCTOGGLE.bit.GPIO84=1)

// PWMӲ������
#define PWM1_ON()			(GpioDataRegs.GPBDAT.bit.GPIO48 = 0)//(GpioDataRegs.GPBCLEAR.bit.GPIO48 = 1)
#define PWM1_OFF()			(GpioDataRegs.GPBDAT.bit.GPIO48 = 1)//(GpioDataRegs.GPBSET.bit.GPIO48 = 1)

#define PWM2_ON()			(GpioDataRegs.GPBDAT.bit.GPIO49 = 0)//(GpioDataRegs.GPBCLEAR.bit.GPIO49 = 1)
#define PWM2_OFF()			(GpioDataRegs.GPBDAT.bit.GPIO49 = 1)//(GpioDataRegs.GPBSET.bit.GPIO49 = 1)

#define PWM_ON()			(GpioDataRegs.GPBCLEAR.all |= 0x00030000)
#define PWM_OFF()			(GpioDataRegs.GPBSET.all |= 0x00030000)

// EEPROM/FRAM����API
#define EE_WriteUint16(a, d)	I2C_WriteUint16(a, d)
#define EE_ReadUint16(a, d)		I2C_ReadUint16(a, d)
#define EE_WriteUint32(a, d)	I2C_WriteUint32(a, d)
#define EE_ReadUint32(a, d)		I2C_ReadUint32(a, d)

#if _PCS_CTL_V1_
// I2C�ܽŷ��� GPIO32=SDA GPIO33=SCL
#define SWI2C_SCL_HIGH()	{GpioDataRegs.GPBSET.bit.GPIO33=1;EALLOW;GpioCtrlRegs.GPBDIR.bit.GPIO33=0;EDIS;}
#define SWI2C_SCL_LOW()		{EALLOW;GpioCtrlRegs.GPBDIR.bit.GPIO33=1;EDIS;GpioDataRegs.GPBCLEAR.bit.GPIO33=1;}

#define SWI2C_SDA_HIGH()	{GpioDataRegs.GPBSET.bit.GPIO32=1;EALLOW;GpioCtrlRegs.GPBDIR.bit.GPIO32=0;EDIS;}
#define SWI2C_SDA_LOW()		{EALLOW;GpioCtrlRegs.GPBDIR.bit.GPIO32=1;EDIS;GpioDataRegs.GPBCLEAR.bit.GPIO32=1;}
#define SWI2C_SDA_GET()		GpioDataRegs.GPBDAT.bit.GPIO32
#endif
#if _PCS_CTL_V2_
// I2C�ܽŷ��� GPIO50=SDA GPIO51=SCL
#define SWI2C_SCL_HIGH()	{GpioDataRegs.GPBSET.bit.GPIO51=1;EALLOW;GpioCtrlRegs.GPBDIR.bit.GPIO51=0;EDIS;}
#define SWI2C_SCL_LOW()		{EALLOW;GpioCtrlRegs.GPBDIR.bit.GPIO51=1;EDIS;GpioDataRegs.GPBCLEAR.bit.GPIO51=1;}

#define SWI2C_SDA_HIGH()	{GpioDataRegs.GPBSET.bit.GPIO50=1;EALLOW;GpioCtrlRegs.GPBDIR.bit.GPIO50=0;EDIS;}
#define SWI2C_SDA_LOW()		{EALLOW;GpioCtrlRegs.GPBDIR.bit.GPIO50=1;EDIS;GpioDataRegs.GPBCLEAR.bit.GPIO50=1;}
#define SWI2C_SDA_GET()		GpioDataRegs.GPBDAT.bit.GPIO50
#endif

// FLASH�����Ϣ
#define FLASH_START 		0x300000
#define FLASH_END			0x340000
#define FLASH_LEN			0x40000
#define FLASH_XBOOT_START	0x338000
#define FLASH_XBOOT_END		0x33FF80
#define FLASH_XBOOT_LEN		0x7F80
#define FLASH_USER_START 	0x300000
#define FLASH_USER_END		0x338000
#define FLASH_USER_LEN		0x38000

// SRAM�����Ϣ
#define SRAM_START	0x8000
#define SRAM_END	0x10000
#define SRAM_LEN	0x8000

#define USER_APP_ENTRY	0x318000		// FLASHE
#define XBOOT_ENTRY		0x33FFF6		// FLASHA

// �ⲿEEPROM��2kB
#define EEPROM_SIZE 0x800

typedef struct
{
	Uint16 PeriodMax;   // Parameter: PWM Half-Period in CPU clock cycles (Q0)
	Uint16 Deadband;    // Parameter: PWM deadband in CPU clock cycles (Q0)
	_iq MfuncC1;        // Input: EPWM1 A&B Duty cycle ratio (Q24)
	_iq MfuncC2;        // Input: EPWM2 A&B Duty cycle ratio (Q24)
	_iq MfuncC3;        // Input: EPWM3 A&B Duty cycle ratio (Q24)
}	PWMGEN ;

extern void InitPWM(PWMGEN *pwm);
extern void SetPwm(Uint16 prd, Uint16 cmp);
extern void EnablePWM(void);
extern void DisablePWM(void);
extern void UpdatePwmDutyCycle(PWMGEN *pwm);

// ��ȡAD��������������ڴ������
#define AD_RAW				0	// �����ݲ�������
#define AD_UNIPOLAR			1	// �������źţ����Q15��ʽ
#define	AD_BIPOLAR			2	// ˫�����źţ����Q15��ʽ
#define AD_BIPOLAR_TO_Q15	3	// ˫�����źŲ������ת��ΪQ15��ʽ
Uint16 GetADResult(int16 dataType, int16 *result);

Uint16 GetDI();			// ��ȡDI�������16·����AC220VΪ1����AC220VΪ0
void SetDO(Uint16 code);	// ����DO����8·��code�Ͱ�λ��Ч������1�̵������ϣ�����0�̵����Ͽ�

// ͨ����ʱ����
void Delay(volatile Uint32);
void DELAY_MS(Uint16);


void Delay_co(float CycleNum1);
//void Delay_MS(int CycleNum1);
//void Delay_func();  

#endif

