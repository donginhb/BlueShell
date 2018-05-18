/*
 * Modbus_RTU.h
 *
 *  Created on: 2014-8-26
 *      Author: ONLYME
 */

#ifndef MODBUS_RTU_H_
#define MODBUS_RTU_H_

//全锟街憋拷锟斤拷锟斤拷锟斤拷
#ifdef MODBUS_RTU_GLOBALS
#define MODBUS_RTU_EXT
#else
#define MODBUS_RTU_EXT extern
#endif


MODBUS_RTU_EXT Uint16  RS485_Status;

#define  RS485_RX    0
#define  RS485_TX    1

//------------MODULE-Status---------------
#define IDLE_WAIT         0x00
#define RECE_START        0x01
#define RECE_END          0x02
#define OACK_RDY          0x03
#define EACK_RDY          0x04
#define SEND_START        0x05
#define SEND_END          0x06


#define READ_COILS        0x01
#define READ_DISBITS      0x02
#define READ_STOREREGS    0x03
#define READ_INPUTREGS    0x04

#define WRITE_ONECOIL     0x05
#define WRITE_ONEREG      0x06
#define WRITE_COILS       0x0F
#define WRITE_REGS        0x10

#define StorageMap_Addr   999 //TA TM离散量  放置变量起始地址
#define InputMap_Addr     2989 //TS TM数组 放置变量起始地址，状态字放在数组之前
#define Coil_Addr         5000 //TC 放置变量起始地址
#define DisCoil_Addr      0 //暂未定义起始地址，默认为0


#define FUNC_RANG         127
#define ADDR_RANG         50
#define CoilADDR_RANG     0x0FFFF
#define DisBitsADDR_RANG  0x0FFFF
#define StoreRegADDR_RANG 0x0FFFF
#define InputRegADDR_RANG 0x0FFFF
#define InputReg_NUM_MAX  0x07D
#define StoreReg_NUM_MAX  0x07D
#define Coil_NUM_MAX      0x07D0
#define DisBit_NUM_MAX    0x07D0
#define DATA_RANG         0x0FFFF
#define WriteCoil_MAX     0x07B0
#define WriteReg_NUM_MAX  0x07B

#define FUNC_ERROR        0x01
#define RANG_ERROR        0x03
#define ADDR_ERROR        0x02
#define PROCESS_ERROR     0x04
#define CRC_ERROR         0x05
#define NOT_DEFINED       0x10

#define INDEX(x)          x


//以下为本程序中自定义全局变量的索引地址


#define Grid_m_INDEX  		0
#define Id_Set_INDEX  		2
#define Udc_ref_INDEX  		4
#define Id_Kp_INDEX  		6
#define Id_Ki_INDEX  		8
#define Iq_Kp_INDEX  		10
#define Iq_Ki_INDEX  		12
#define Udc_Kp_INDEX  		14
#define Udc_Ki_INDEX  		16
#define PF_Set_INDEX  		18
#define Q_Set_INDEX  		20
#define Q_Discharge_INDEX   22
#define TAM_Float_Reserved1 24
//保留地址，可用来增加变量
#define TAM_Float_Reservedn 38
/*....................*/

#define Gird_Ia_RMS_INDEX  	40
#define Gird_Ib_RMS_INDEX  	42
#define Gird_Ic_RMS_INDEX  	44
#define Gird_Freq_INDEX  	46
#define PF_INDEX  			48
#define Temp_INDEX  		50
#define DCI_RMS_INDEX  		52
#define TM_Float_Reserved1  54
//保留地址，可用来增加变量
#define TM_Float_Reservedn  98
/*....................*/

#define Second_INDEX  		100
#define Minute_INDEX  		101
#define Hour_INDEX  		102
#define Day_INDEX  		    103
#define Month_INDEX  		104
#define Year_INDEX  		105
#define StationNum_INDEX  	106
#define LEVEL_INDEX  		107
#define RunMode_INDEX  		108
#define WaveType_INDEX  	109
#define TAM_int16_Reserved1 110
//保留地址，可用来增加变量
#define TAM_int16_Reservedn 120
/*....................*/

#define Chcode_DSP_INDEX  	121
#define Grid_Pac_INDEX  	122
#define Grid_Qac_INDEX  	123
#define DCVU_RMS_INDEX  	124
#define DCVD_RMS_INDEX  	125
#define Grid_Vab_RMS_INDEX  126
#define Grid_Vbc_RMS_INDEX  127
#define Grid_Vca_RMS_INDEX  128
#define TM_int16_Reserved1  129
//保留地址，可用来增加变量
#define TM_int16_Reservedn  199
/*....................*/


#define Start_Stop_INDEX    0
#define Reset_INDEX    		1
#define Local_Remote_INDEX  2
#define Reborn_INDEX    	3
#define SVG_EN_INDEX    	4


#define Grid_State1_INDEX   0
#define Grid_HF_INDEX 		1
#define Grid_SF1_INDEX		2
#define Grid_SF2_INDEX   	3
#define Grid_ServerF_INDEX  4
#define Grid_COMM_INDEX   	5
#define TS_Reserved1        6
//保留地址，可用来增加变量
#define TS_Reservedn        9
/*....................*/
#define DCV_WaveBegin       10 //--309
#define ACV_WaveBegin       10 //--309
#define ACI_WaveBegin       10 //--309

//////////////////


//以下是外部全局变量的申明

	extern	unsigned int LEVEL;
	extern	unsigned int Run_Mode;
	extern	float Grid_m;
	extern	float Udc_ref;
	extern  float pi1_id_Kp;
	extern   float pi1_id_Ki;
	extern   float pi1_iq_Kp;
	extern	float pi1_iq_Ki;
	extern	float pi1_Vdc_Kp;
	extern	float pi1_Vdc_Ki;

	extern  int Grid_Pac;
	extern	int Grid_Qac;
	extern	float Vdc_Sample;

	extern unsigned int Grid_Vab;
	extern unsigned int Grid_Vbc;
	extern unsigned int Grid_Vca;

	extern float Id_ref;


	extern unsigned int Grid_Ia;
	extern unsigned int Grid_Ib;
	extern unsigned int Grid_Ic;
	extern unsigned int Grid_Freq;
	extern float Ia_Sample;
	extern float Ib_Sample;
	extern float Ic_Sample;
	extern float Vab_Sample;
	extern float Vbc_Sample;
	extern float Vca_Sample;

	extern unsigned int Sys_Run;
	extern unsigned int Start_CMD;
	extern unsigned int Reset_CMD;
	extern unsigned int Reset_onetime_flag;
	extern SVGENDQ svgen_dq1;

//////////////////

union Byte_Bits
{
	Uint8   all;
	struct bits
	{
		Uint8 Bit0:1;
		Uint8 Bit1:1;
		Uint8 Bit2:1;
		Uint8 Bit3:1;
		Uint8 Bit4:1;
		Uint8 Bit5:1;
		Uint8 Bit6:1;
		Uint8 Bit7:1;
	}bit;
};



struct Reg_Byte
{
	Uint16  LOW:8;
	Uint16  HIGH:8;
};

union Reg_WORLD
{
	Uint16  					all;
	int16                       sall;
	struct      Reg_Byte        bit;
};

union Float_With_Uint32
{
	float  FloatType;
	union  _Uint32
	{
		Uint32 all;
		struct _Uint16
		{
			union Reg_WORLD LowWord;
			union Reg_WORLD HighWord;
		}words;
	} Uint32Type;
};

struct MODBUS_MODULE
{
	Uint8	TxBuf[256];
	Uint8	RxBuf[256];
	Uint16	TxLen;
	Uint16	RxLen;
	Uint16	Pointer;
	Uint16	RetryCNT;
	Uint16	TimeoutCNT;
	Uint16	ID;
	Uint16	FunCode;
	Uint16	ErrorCode;
	Uint16	CRCCode;
	Uint32	Addr;
	Uint16	Num;
	Uint16	BYTENum;
	Uint16	WORDNum;
	Uint16	Data;
	Uint16	Status;
	Uint16  CNT;
};

struct Wave_Index
{
	Uint16 TotalIndex;
	Uint16 BeginIndex;
	Uint16 DataLength;
	Uint8  TempCNT;
};

MODBUS_RTU_EXT  struct MODBUS_MODULE ModbusFram;
MODBUS_RTU_EXT  union Reg_WORLD StorageMap_Reg[200]; //全局变量，未初始化时默认为0，下同；局部变量，未初始化时值未知，故需要赋初值。
MODBUS_RTU_EXT  union Reg_WORLD InputMap_Reg[311];
MODBUS_RTU_EXT  union Byte_Bits Coil_Reg[2];
MODBUS_RTU_EXT  union Byte_Bits DisCoil_Reg[2];
MODBUS_RTU_EXT  union Float_With_Uint32 FloatAndUint32;
MODBUS_RTU_EXT  struct Wave_Index WaveIndex;

MODBUS_RTU_EXT  Uint8 WaveTpye;
MODBUS_RTU_EXT  Uint8 RemoteOrLocal;
MODBUS_RTU_EXT  Uint16 TAM_Second,TAM_Minute,TAM_Hour,TAM_Day,TAM_Month,TAM_Year,TAM_StationNum;
MODBUS_RTU_EXT  Uint16 TM_Grid_State1,TM_Grid_HF,TM_Grid_SF1,TM_Grid_SF2,TM_Grid_ServerF;


Uint16 ModbusRTU_RX();
Uint16 ModbusRTU_TX();

extern void ModbusFrame_Analyse();

extern void InitComm();
extern void HMI_Comm_Server();
extern void Assemble_ErrorFrame();
extern void Error_Process();
extern Uint16 Function_Process();
void ModbusRTU_ReadCoils_0x01_ReadDisBits_0x02(Uint16 BeginAddress,union Byte_Bits *StoreRegs,struct MODBUS_MODULE *ModbusFrame);
//void ModbusRTU_ReadDisBits_0x02(Uint16 BeginAddress,union Byte_Bits *StoreRegs,struct MODBUS_MODULE *ModbusFrame);
void ModbusRTU_ReadStoreRegs_0x03_InputRegs_0x04(Uint16 BeginAddress, union Reg_WORLD *StoreRegs,struct MODBUS_MODULE *ModbusFrame);
void ModbusRTU_WriteOneCoil_0x05(Uint16 BeginAddress,union Byte_Bits *StoreRegs,struct MODBUS_MODULE *ModbusFrame);
void ModbusRTU_WriteOneReg_0x06(Uint16 BeginAddress, union Reg_WORLD *StoreRegs,struct MODBUS_MODULE *ModbusFrame);
void ModbusRTU_WriteCoils_0x0F(Uint16 BeginAddress,union Byte_Bits *StoreRegs,struct MODBUS_MODULE *ModbusFrame);
void ModbusRTU_WriteRegs_0x10(Uint16 BeginAddress, union Reg_WORLD *StoreRegs,struct MODBUS_MODULE *ModbusFrame);

void Assemble_StorageMap_Regs();
void Assemble_InputMap_Regs();
void Assemble_Coil_Regs();
void Unpack_StorageMap_Regs();
void Unpack_Coil_Regs();


#endif /* MODBUS_RTU_H_ */
