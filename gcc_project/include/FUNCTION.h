#ifndef FUNCTION_H
#define FUNCTION_H

// 初始化子函数
void Sys_Init();          // 系统初始化子函数
void Variable_Init();     // 变量初始化子函数
void Version_No();        // 软件版本号计算子函数
void InitEPwmTimer(void); // EPWM计数器初始化子函数
void configtestled(void);
void Zero_JZ();
// 逻辑相关子函数
void Sys_State_Handle();  // 逻辑状态机子函数
void Switch_Open();       // 停机分闸，停机状态时执行的子函数
void Switch_Close();      // 启动合闸，启动状态时执行的子函数
void Reset();             // 故障复位，复位状态时执行的子函数
void Test_Level();        // 调试子函数

// 控制相关子函数
void Sys_CTRL();          // 主控子函数
void MPPT_CMD();          // MPPT子函数
void RMS_VI();            // 有效值计算
void Protect_VIT();       // 软件保护
void AD_VI();             // AD采样
void RMS_VI1();
void PLL();               // 锁相子函数
void LVRT();
// 发电量统计相关子函数
void Clock();
void Energy_Production();
unsigned char Day_up();
unsigned char Isleapyear();  
void Grid_Synchro();
void Oscillograph_VI();
//void PLL();
//void Run_to_Waiting();
//void Start_Stop_DSP();
//void CMD_VI();

//void CMD_Gain_Caculation();

//void Check_Clock();

void Current_ZeroJZ();
void Insulation_Monitor();

// 辅助功能子函数
void RSTFPGA();
void RSTIGBT();
void DA_Out(); 

unsigned int ReadExADD(unsigned int TempADD);
unsigned int SetExCode(unsigned int TempADD,unsigned int TempCode);
unsigned int CRC16(unsigned char *CheckData,unsigned int Length);

void DI_L_Shake_Filter(unsigned int TempADD);
void DI_H_Shake_Filter(unsigned int TempADD);

void Delay(float CycleNum1);
void Delay_MS(int CycleNum1);
void Delay_func();
//void EMERGENCY_Stop();
//void RAM_LOG_W();
//void RAM_LOG_R();
void ExRAM_Com_W();
void ExRAM_Com_R();
//void E2PROM_W();
//void E2PROM_R();
//void TLB_Reset();
void SetDAValue(unsigned char ChannalNo,float DAOUTFValue);

#endif  // end of FUNCTION_H definition

		

