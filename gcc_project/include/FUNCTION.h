#ifndef FUNCTION_H
#define FUNCTION_H

// ��ʼ���Ӻ���
void Sys_Init();          // ϵͳ��ʼ���Ӻ���
void Variable_Init();     // ������ʼ���Ӻ���
void Version_No();        // ����汾�ż����Ӻ���
void InitEPwmTimer(void); // EPWM��������ʼ���Ӻ���
void configtestled(void);
void Zero_JZ();
// �߼�����Ӻ���
void Sys_State_Handle();  // �߼�״̬���Ӻ���
void Switch_Open();       // ͣ����բ��ͣ��״̬ʱִ�е��Ӻ���
void Switch_Close();      // ������բ������״̬ʱִ�е��Ӻ���
void Reset();             // ���ϸ�λ����λ״̬ʱִ�е��Ӻ���
void Test_Level();        // �����Ӻ���

// ��������Ӻ���
void Sys_CTRL();          // �����Ӻ���
void MPPT_CMD();          // MPPT�Ӻ���
void RMS_VI();            // ��Чֵ����
void Protect_VIT();       // �������
void AD_VI();             // AD����
void RMS_VI1();
void PLL();               // �����Ӻ���
void LVRT();
// ������ͳ������Ӻ���
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

// ���������Ӻ���
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

		

