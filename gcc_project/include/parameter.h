/**
 * 定义程序中使用的常量
 */

#ifndef _PARAMETER_H_
#define _PARAMETER_H_

#define SYSTEM_FREQ 150E6				// 系统时钟频率 150MHz
#define BASE_FREQ 	50UL				// 基波频率 50Hz
#define N_SAMPLE 	200UL				// 每个工频周期的采样点数
#define N_PLL_BUF 	(2*N_SAMPLE)		// 相角缓冲区大小
#define ISR_FREQUENCY 10000
#define SYSTEM_FREQUENCY 150

#define SAMPLE_FREQ		(N_SAMPLE*BASE_FREQ)	// AD采样频率，也是程序调度的最小单位

#define LIMIT_DCOV_DEF	160.0			// 默认直流过压限值，V
#define LIMIT_ACOC_DEF	10.0			// 默认交流过流限值，A

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

