/**
 * ���������ʹ�õĳ���
 */

#ifndef _PARAMETER_H_
#define _PARAMETER_H_

#define SYSTEM_FREQ 150E6				// ϵͳʱ��Ƶ�� 150MHz
#define BASE_FREQ 	50UL				// ����Ƶ�� 50Hz
#define N_SAMPLE 	200UL				// ÿ����Ƶ���ڵĲ�������
#define N_PLL_BUF 	(2*N_SAMPLE)		// ��ǻ�������С
#define ISR_FREQUENCY 10000
#define SYSTEM_FREQUENCY 150

#define SAMPLE_FREQ		(N_SAMPLE*BASE_FREQ)	// AD����Ƶ�ʣ�Ҳ�ǳ�����ȵ���С��λ

#define LIMIT_DCOV_DEF	160.0			// Ĭ��ֱ����ѹ��ֵ��V
#define LIMIT_ACOC_DEF	10.0			// Ĭ�Ͻ���������ֵ��A

#define Twice_PI  6.28318530717959      // 2pi
#define Once_PI 3.1415926

#define Id_Max 10.0
#define Id_Min -10.0
#define Iq_Max 10.0
#define Iq_Min -10.0
#define Udc_Max 730
#define Udc_Min 30

#define SLOPER(VAR,TARGET1,STEP) \
if((VAR)<(TARGET1))\
(VAR)+=(STEP);\
else if((VAR)>(TARGET1))\
(VAR)-=(STEP)
#endif

