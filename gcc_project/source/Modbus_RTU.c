/*
 * Modbus_RTU.c
 *
 *  Created on: 2014-8-25
 *      Author: ONLYME
 */
#define MODBUS_RTU_GLOBALS
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
//#include "Modbus_RTU.h"
//#include "VARIABLE.h"
#include "hal.h"
//#include "VARIABLE.h"
long LoopCount1;
Uint16 ModbusRTU_RX()
{
	if(RS485_Status==RS485_RX)
	{
	   SCIB_RX_EN();
	   ModbusFram.RxLen=SCI_FIFORX_Data(&ScicRegs,ModbusFram.RxBuf,256);
	   
	 }
	if(ModbusFram.RxLen!=0)
	{
		SCIB_TX_EN();//TX_EN;
		RS485_Status=RS485_TX;
		return TRUE;
	}
	return FALSE;
}

//test git modified

Uint16 ModbusRTU_TX()
{
	if(RS485_Status==RS485_TX)
	{

		if(SCI_FIFOTX_Data(&ScicRegs,ModbusFram.TxBuf,ModbusFram.TxLen)==TRUE)
		{
			RS485_Status=RS485_RX;
			SCIB_RX_EN();//RX_EN;
			return TRUE;
		}


	}
	return FALSE;
}

void ModbusFrame_Analyse()
{

		if(ModbusFram.ID==ModbusFram.RxBuf[0])
		{
			if(ModbusFram.RxBuf[1]>FUNC_RANG)
			{
				ModbusFram.ErrorCode=FUNC_ERROR;
				Assemble_ErrorFrame();
				return;
			}

			ModbusFram.FunCode=ModbusFram.RxBuf[1];
			ModbusFram.Addr=((ModbusFram.RxBuf[2]<<8)+ModbusFram.RxBuf[3]);
			ModbusFram.Num=((ModbusFram.RxBuf[4]<<8)+ModbusFram.RxBuf[5]);

			switch(ModbusFram.FunCode)
			{
				case READ_COILS:
						if(0<ModbusFram.Num<=Coil_NUM_MAX)
						{
							if((ModbusFram.Num & 0x0007)!=0)
							{
								ModbusFram.BYTENum=(ModbusFram.Num>>3)+1;
							}
							else
							{
								ModbusFram.BYTENum=(ModbusFram.Num>>3);
							}

							if((ModbusFram.Addr<CoilADDR_RANG) &&((ModbusFram.Addr+ModbusFram.Num)<CoilADDR_RANG))
							{
								ModbusFram.CRCCode=(ModbusFram.RxBuf[ModbusFram.RxLen-2]<<8)+ModbusFram.RxBuf[ModbusFram.RxLen-1];
								CRC_Code=CRC16(ModbusFram.RxBuf,ModbusFram.RxLen-2);
								if(CRC_Code==ModbusFram.CRCCode)
								{
									if(Function_Process()==TRUE)
									{break;}
									else
									{
										ModbusFram.ErrorCode=PROCESS_ERROR;
										Assemble_ErrorFrame();
										return;
									}
								}
								else
								{
									ModbusFram.ErrorCode=CRC_ERROR;
									Assemble_ErrorFrame();
									return;
								}
							}
							else
							{
								ModbusFram.ErrorCode=ADDR_ERROR;
								Assemble_ErrorFrame();
								return;
							}
						}
						else
						{
							ModbusFram.ErrorCode=RANG_ERROR;
							Assemble_ErrorFrame();
							return;
						}

				case READ_DISBITS:
						if(0<ModbusFram.Num<=DisBit_NUM_MAX)
						{
							if((ModbusFram.Num & 0x0007)!=0)
							{
								ModbusFram.BYTENum=(ModbusFram.Num>>3)+1;
							}
							else
							{
								ModbusFram.BYTENum=(ModbusFram.Num>>3);

							}

							if((ModbusFram.Addr<DisBitsADDR_RANG) &&((ModbusFram.Addr+ModbusFram.Num)<DisBitsADDR_RANG))
							{
								ModbusFram.CRCCode=(ModbusFram.RxBuf[ModbusFram.RxLen-2]<<8)+ModbusFram.RxBuf[ModbusFram.RxLen-1];
								CRC_Code=CRC16(ModbusFram.RxBuf,ModbusFram.RxLen-2);
								if(CRC_Code==ModbusFram.CRCCode)
								{
									if(Function_Process()==TRUE)
									{break;}
									else
									{
										ModbusFram.ErrorCode=PROCESS_ERROR;
										Assemble_ErrorFrame();
										return;
									}
								}
								else
								{
									ModbusFram.ErrorCode=CRC_ERROR;
									Assemble_ErrorFrame();
									return;
								}
							}
							else
							{
								ModbusFram.ErrorCode=ADDR_ERROR;
								Assemble_ErrorFrame();
								return;
							}
						}
						else
						{
							ModbusFram.ErrorCode=RANG_ERROR;
							Assemble_ErrorFrame();
							return;
						}



				case READ_STOREREGS:
						if(0<ModbusFram.Num<=StoreReg_NUM_MAX)
						{
							if((ModbusFram.Addr<StoreRegADDR_RANG) &&((ModbusFram.Addr+ModbusFram.Num)<StoreRegADDR_RANG))
							{
								ModbusFram.CRCCode=(ModbusFram.RxBuf[ModbusFram.RxLen-2]<<8)+ModbusFram.RxBuf[ModbusFram.RxLen-1];
								CRC_Code=CRC16(ModbusFram.RxBuf,ModbusFram.RxLen-2);
								if(CRC_Code==ModbusFram.CRCCode)
								{
									if(Function_Process()==TRUE)
									{break;}
									else
									{
										ModbusFram.ErrorCode=PROCESS_ERROR;
										Assemble_ErrorFrame();
										return;
									}
								}
								else
								{
									ModbusFram.ErrorCode=CRC_ERROR;
									Assemble_ErrorFrame();
									return;
								}
							}
							else
							{
								ModbusFram.ErrorCode=ADDR_ERROR;
								Assemble_ErrorFrame();
								return;
							}
						}
						else
						{
							ModbusFram.ErrorCode=RANG_ERROR;
							Assemble_ErrorFrame();
							return;
						}



				case READ_INPUTREGS:
						if(0<ModbusFram.Num<=InputReg_NUM_MAX)
						{
							if((ModbusFram.Addr<InputRegADDR_RANG) &&((ModbusFram.Addr+ModbusFram.Num)<InputRegADDR_RANG))
							{
								ModbusFram.CRCCode=(ModbusFram.RxBuf[ModbusFram.RxLen-2]<<8)+ModbusFram.RxBuf[ModbusFram.RxLen-1];
								CRC_Code=CRC16(ModbusFram.RxBuf,ModbusFram.RxLen-2);
								if(CRC_Code==ModbusFram.CRCCode)
								{
									if(Function_Process()==TRUE)
									{break;}
									else
									{
										ModbusFram.ErrorCode=PROCESS_ERROR;
										Assemble_ErrorFrame();
										return;
									}
								}
								else
								{
									ModbusFram.ErrorCode=CRC_ERROR;
									Assemble_ErrorFrame();
									return;
								}
							}
							else
							{
								ModbusFram.ErrorCode=ADDR_ERROR;
								Assemble_ErrorFrame();
								return;
							}
						}
						else
						{
							ModbusFram.ErrorCode=RANG_ERROR;
							Assemble_ErrorFrame();
							return;
						}



				case WRITE_ONECOIL:
						if((ModbusFram.Num==0x0000) || (ModbusFram.Num==0xFF00))
						{
							if(ModbusFram.Addr<CoilADDR_RANG)
							{
								ModbusFram.CRCCode=(ModbusFram.RxBuf[ModbusFram.RxLen-2]<<8)+ModbusFram.RxBuf[ModbusFram.RxLen-1];
								CRC_Code=CRC16(ModbusFram.RxBuf,ModbusFram.RxLen-2);
								if(CRC_Code==ModbusFram.CRCCode)
								{
									if(Function_Process()==TRUE)
									{break;}
									else
									{
										ModbusFram.ErrorCode=PROCESS_ERROR;
										Assemble_ErrorFrame();
										return;
									}
								}
								else
								{
									ModbusFram.ErrorCode=CRC_ERROR;
									Assemble_ErrorFrame();
									return;
								}
							}
							else
							{
								ModbusFram.ErrorCode=ADDR_ERROR;
								Assemble_ErrorFrame();
								return;
							}
						}
						else
						{
							ModbusFram.ErrorCode=RANG_ERROR;
							Assemble_ErrorFrame();
							return;
						}




				case WRITE_ONEREG:
						if(ModbusFram.Num<DATA_RANG)
						{
							if(ModbusFram.Addr<StoreRegADDR_RANG)
							{
								ModbusFram.CRCCode=(ModbusFram.RxBuf[ModbusFram.RxLen-2]<<8)+ModbusFram.RxBuf[ModbusFram.RxLen-1];
								CRC_Code=CRC16(ModbusFram.RxBuf,ModbusFram.RxLen-2);
								if(CRC_Code==ModbusFram.CRCCode)
								{
									if(Function_Process()==TRUE)
									{break;}
									else
									{
										ModbusFram.ErrorCode=PROCESS_ERROR;
										Assemble_ErrorFrame();
										return;
									}
								}
								else
								{
									ModbusFram.ErrorCode=CRC_ERROR;
									Assemble_ErrorFrame();
									return;
								}
							}
							else
							{
								ModbusFram.ErrorCode=ADDR_ERROR;
								Assemble_ErrorFrame();
								return;
							}
						}
						else
						{
							ModbusFram.ErrorCode=RANG_ERROR;
							Assemble_ErrorFrame();
							return;
						}
				case WRITE_COILS:
						if(0<ModbusFram.Num<=WriteCoil_MAX)
						{
							if((ModbusFram.Num & 0x0007)!=0)
							{
								ModbusFram.BYTENum=(ModbusFram.Num>>3)+1;
							}
							else
							{
								ModbusFram.BYTENum=(ModbusFram.Num>>3);
								//ModbusFram.WORDNum=((ModbusFram.BYTENum+1)>>1);
							}

							if(ModbusFram.BYTENum!=ModbusFram.RxBuf[6])
							{
								ModbusFram.ErrorCode=RANG_ERROR;
								Assemble_ErrorFrame();
								return;
							}

							if((ModbusFram.Addr<CoilADDR_RANG) &&((ModbusFram.Addr+ModbusFram.WORDNum)<CoilADDR_RANG))
							{
								ModbusFram.CRCCode=(ModbusFram.RxBuf[ModbusFram.RxLen-2]<<8)+ModbusFram.RxBuf[ModbusFram.RxLen-1];
								CRC_Code=CRC16(ModbusFram.RxBuf,ModbusFram.RxLen-2);
								if(CRC_Code==ModbusFram.CRCCode)
								{
									if(Function_Process()==TRUE)
									{break;}
									else
									{
										ModbusFram.ErrorCode=PROCESS_ERROR;
										Assemble_ErrorFrame();
										return;
									}
								}
								else
								{
									ModbusFram.ErrorCode=CRC_ERROR;
									Assemble_ErrorFrame();
									return;
								}
							}
							else
							{
								ModbusFram.ErrorCode=ADDR_ERROR;
								Assemble_ErrorFrame();
								return;
							}
						}
						else
						{
							ModbusFram.ErrorCode=RANG_ERROR;
							Assemble_ErrorFrame();
							return;
						}
				case WRITE_REGS:
						if((0<ModbusFram.Num<=WriteReg_NUM_MAX) && (ModbusFram.RxBuf[6]==(ModbusFram.Num<<1)))
						{
							if((ModbusFram.Addr<StoreRegADDR_RANG) &&((ModbusFram.Addr+ModbusFram.Num)<StoreRegADDR_RANG))
							{
								ModbusFram.CRCCode=(ModbusFram.RxBuf[ModbusFram.RxLen-2]<<8)+ModbusFram.RxBuf[ModbusFram.RxLen-1];
								CRC_Code=CRC16(ModbusFram.RxBuf,ModbusFram.RxLen-2);
								if(CRC_Code==ModbusFram.CRCCode)
								{
									if(Function_Process()==TRUE)
									{break;}
									else
									{
										ModbusFram.ErrorCode=PROCESS_ERROR;
										Assemble_ErrorFrame();
										return;
									}
								}
								else
								{
									ModbusFram.ErrorCode=CRC_ERROR;
									Assemble_ErrorFrame();
									return;
								}
							}
							else
							{
								ModbusFram.ErrorCode=ADDR_ERROR;
								Assemble_ErrorFrame();
								return;
							}
						}
						else
						{
							ModbusFram.ErrorCode=RANG_ERROR;
							Assemble_ErrorFrame();
							return;
						}

				default:{
							if(ModbusFram.RxLen==5)
							{
								Error_Process();
								break;
							}
							else
							{
								ModbusFram.ErrorCode=NOT_DEFINED;
								Assemble_ErrorFrame();
								break;
							}
						}
			}
		}

}


void Assemble_ErrorFrame()
{
	ModbusFram.TimeoutCNT=0;

	ModbusFram.FunCode=ModbusFram.RxBuf[1]+0x80;
	ModbusFram.TxBuf[0]=ModbusFram.ID;
	ModbusFram.TxBuf[1]=ModbusFram.FunCode;
	ModbusFram.TxBuf[2]=ModbusFram.ErrorCode;
	ModbusFram.CRCCode=CRC16(ModbusFram.TxBuf,3);
	ModbusFram.TxBuf[3]=ModbusFram.CRCCode>>8;
	ModbusFram.TxBuf[4]=ModbusFram.CRCCode&0xFF;
	ModbusFram.TxLen=5;
	ModbusFram.Status=IDLE_WAIT;
	ModbusFram.Pointer=0;

}



//********************************************************************************************
//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Æ£ï¿½InitComm
//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ü£ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½á¹¹ï¿½ï¿½ï¿½Ä¸ï¿½Î»
//Ëµï¿½ï¿½ï¿½ï¿½
//********************************************************************************************
void InitComm()
{
	for(ModbusFram.CNT=0;ModbusFram.CNT<256;ModbusFram.CNT++)
	{
		ModbusFram.TxBuf[ModbusFram.CNT]=0;
		ModbusFram.RxBuf[ModbusFram.CNT]=0;
	}
	ModbusFram.TxLen=0;
	ModbusFram.RxLen=0;
	ModbusFram.Pointer=0;
	ModbusFram.RetryCNT=0;
	ModbusFram.TimeoutCNT=0;
	ModbusFram.ID=01;
	ModbusFram.FunCode=0;
	ModbusFram.ErrorCode=0;
	ModbusFram.CRCCode=0;
	ModbusFram.Addr=0;
	ModbusFram.Num=0;
	ModbusFram.BYTENum=0;
	ModbusFram.WORDNum=0;
	ModbusFram.Data=0;
	ModbusFram.Status=IDLE_WAIT;
	ModbusFram.CNT=0;

	RS485_Status=RS485_RX;

}

//*******************************************************************************************
//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Æ£ï¿½HMI_Comm_Server
//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ü£ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½î¡¢ï¿½ï¿½ï¿½ï¿½ï¿½Â·ï¿½ï¿½Í·ï¿½ï¿½ï¿½
//Ëµï¿½ï¿½ï¿½ï¿½
//*******************************************************************************************
void HMI_Comm_Server()
{
	if(ModbusRTU_RX()==TRUE)
	{

//		LoopCount1++;
		Assemble_StorageMap_Regs();
		Assemble_Coil_Regs();
		ModbusFrame_Analyse();
		ModbusRTU_TX();

		Unpack_StorageMap_Regs();
		Unpack_Coil_Regs();
	}

	if(WaveIndex.TempCNT>=10)
	{
		Assemble_InputMap_Regs();
		WaveIndex.TempCNT=0;
	}
}



void Error_Process()
{
	if(ModbusFram.TimeoutCNT>12500)
	ModbusFram.Status=IDLE_WAIT;
}


Uint16 Function_Process()
{
	ModbusFram.TimeoutCNT=0;

	switch(ModbusFram.FunCode)
	{
		case READ_COILS:
				{
					ModbusRTU_ReadCoils_0x01_ReadDisBits_0x02(Coil_Addr,Coil_Reg,&ModbusFram);
					break;
				}
		case READ_DISBITS://ÔÝÊ±µ±×÷Coil_RegÊ¹ÓÃ
				{
					ModbusRTU_ReadCoils_0x01_ReadDisBits_0x02(Coil_Addr,Coil_Reg,&ModbusFram);
					break;
				}
		case READ_STOREREGS:
				{
					ModbusRTU_ReadStoreRegs_0x03_InputRegs_0x04(StorageMap_Addr, StorageMap_Reg,&ModbusFram);
					break;
				}
		case READ_INPUTREGS:
				{
					ModbusRTU_ReadStoreRegs_0x03_InputRegs_0x04(InputMap_Addr, InputMap_Reg,&ModbusFram);
					break;
				}
		case WRITE_ONECOIL:
				{

					ModbusRTU_WriteOneCoil_0x05(Coil_Addr,Coil_Reg,&ModbusFram);
					break;
				}
		case WRITE_ONEREG:
				{

					ModbusRTU_WriteOneReg_0x06(StorageMap_Addr, StorageMap_Reg,&ModbusFram);
					break;
				}
		case WRITE_COILS:
				{

					ModbusRTU_WriteCoils_0x0F(Coil_Addr,Coil_Reg,&ModbusFram);
					break;
				}
		case WRITE_REGS:
				{

					ModbusRTU_WriteRegs_0x10(StorageMap_Addr, StorageMap_Reg,&ModbusFram);
					break;
				}
		default:
			break;
	}
	return TRUE;
}


void ModbusRTU_ReadCoils_0x01_ReadDisBits_0x02(Uint16 BeginAddress,union Byte_Bits *StoreRegs,struct MODBUS_MODULE *ModbusFrame)
{
	union Byte_Bits  TempByteBits;
	Uint8 TempChar[8]={0,0,0,0,0,0,0,0},Index=0,CoilBitIndex;
	Uint16 ByteIndex;

	ModbusFrame->TxBuf[0]=ModbusFrame->ID;
	ModbusFrame->TxBuf[1]=ModbusFrame->FunCode;
	ModbusFrame->TxBuf[2]=ModbusFrame->BYTENum;
	ModbusFrame->Pointer=3;

	ByteIndex=(ModbusFrame->Addr-BeginAddress)>>3;
	CoilBitIndex=ModbusFrame->Addr & 0x07;
	while(ModbusFrame->Num--)
	{
		switch(CoilBitIndex++)
		{
			case 0:
					TempChar[Index++]=StoreRegs[ByteIndex].bit.Bit0;
					break;

			case 1:
					TempChar[Index++]=StoreRegs[ByteIndex].bit.Bit1;
					break;

			case 2:
					TempChar[Index++]=StoreRegs[ByteIndex].bit.Bit2;
					break;

			case 3:
					TempChar[Index++]=StoreRegs[ByteIndex].bit.Bit3;
					break;

			case 4:
					TempChar[Index++]=StoreRegs[ByteIndex].bit.Bit4;
					break;

			case 5:
					TempChar[Index++]=StoreRegs[ByteIndex].bit.Bit5;
					break;

			case 6:
					TempChar[Index++]=StoreRegs[ByteIndex].bit.Bit6;
					break;

			case 7:
					TempChar[Index++]=StoreRegs[ByteIndex++].bit.Bit7;
					CoilBitIndex=0;
					break;
			default :
					break;
		}
		if((Index==8) ||(ModbusFrame->Num==0))
		{

			TempByteBits.all=0;
			if(TempChar[0]!=0)TempByteBits.bit.Bit0 = 1;
			if(TempChar[1]!=0)TempByteBits.bit.Bit1 = 1;
			if(TempChar[2]!=0)TempByteBits.bit.Bit2 = 1;
			if(TempChar[3]!=0)TempByteBits.bit.Bit3 = 1;
			if(TempChar[4]!=0)TempByteBits.bit.Bit4 = 1;
			if(TempChar[5]!=0)TempByteBits.bit.Bit5 = 1;
			if(TempChar[6]!=0)TempByteBits.bit.Bit6 = 1;
			if(TempChar[7]!=0)TempByteBits.bit.Bit7 = 1;
			ModbusFrame->TxBuf[ModbusFrame->Pointer++]=TempByteBits.all;

			for(Index=0;Index<8;Index++)
				TempChar[Index]=0;
			Index=0;//return to zero
		}

	}
	ModbusFrame->CRCCode=CRC16(ModbusFrame->TxBuf,ModbusFrame->Pointer);
	ModbusFrame->TxBuf[ModbusFrame->Pointer++]=ModbusFrame->CRCCode>>8;
	ModbusFrame->TxBuf[ModbusFrame->Pointer++]=ModbusFrame->CRCCode&0xFF;
	ModbusFrame->TxLen=ModbusFrame->Pointer;
	ModbusFrame->Status=OACK_RDY;
}


void ModbusRTU_ReadStoreRegs_0x03_InputRegs_0x04(Uint16 BeginAddress, union Reg_WORLD *StoreRegs,struct MODBUS_MODULE *ModbusFrame)
{
	Uint16 WordIndex;
	ModbusFrame->TxBuf[0]=ModbusFrame->ID;
	ModbusFrame->TxBuf[1]=ModbusFrame->FunCode;
	ModbusFrame->TxBuf[2]=ModbusFrame->Num<<1;
	ModbusFrame->Pointer=3;

	WordIndex=ModbusFrame->Addr-BeginAddress;
	for(ModbusFrame->CNT=0;ModbusFrame->CNT<ModbusFrame->Num;ModbusFrame->CNT++)
	{
		ModbusFrame->TxBuf[ModbusFrame->Pointer++]=StoreRegs[WordIndex].bit.HIGH;
		ModbusFrame->TxBuf[ModbusFrame->Pointer++]=StoreRegs[WordIndex].bit.LOW;
		WordIndex++;
	}
	ModbusFrame->CRCCode=CRC16(ModbusFrame->TxBuf,ModbusFrame->Pointer);
	ModbusFrame->TxBuf[ModbusFrame->Pointer++]=ModbusFrame->CRCCode>>8;
	ModbusFrame->TxBuf[ModbusFrame->Pointer++]=ModbusFrame->CRCCode&0xFF;
	ModbusFrame->TxLen=ModbusFrame->Pointer;
	ModbusFrame->Status=OACK_RDY;
}

void ModbusRTU_WriteOneCoil_0x05(Uint16 BeginAddress,union Byte_Bits *StoreRegs,struct MODBUS_MODULE *ModbusFrame)
{
	Uint8 cnt=0,CoilBitIndex,ByteIndex;
	ByteIndex=(ModbusFrame->Addr-BeginAddress)>>3;
	CoilBitIndex=ModbusFrame->Addr & 0x07;
	switch(CoilBitIndex)
	{
		case 0:
				StoreRegs[ByteIndex].bit.Bit0=ModbusFrame->RxBuf[4];//0xFF or 0x00
				break;

		case 1:
				StoreRegs[ByteIndex].bit.Bit1=ModbusFrame->RxBuf[4];
				break;

		case 2:
				StoreRegs[ByteIndex].bit.Bit2=ModbusFrame->RxBuf[4];
				break;

		case 3:
				StoreRegs[ByteIndex].bit.Bit3=ModbusFram.RxBuf[4];
				break;

		case 4:
				StoreRegs[ByteIndex].bit.Bit4=ModbusFrame->RxBuf[4];
				break;

		case 5:
				StoreRegs[ByteIndex].bit.Bit5=ModbusFrame->RxBuf[4];
				break;

		case 6:
				StoreRegs[ByteIndex].bit.Bit6=ModbusFrame->RxBuf[4];
				break;

		case 7:
				StoreRegs[ByteIndex].bit.Bit7=ModbusFrame->RxBuf[4];
				break;
		default :
				break;
	}

	for(cnt=0;cnt<ModbusFrame->RxLen;cnt++)
		ModbusFrame->TxBuf[cnt]=ModbusFrame->RxBuf[cnt];
	ModbusFrame->TxLen=ModbusFrame->RxLen;
	ModbusFrame->Status=OACK_RDY;
}

void ModbusRTU_WriteOneReg_0x06(Uint16 BeginAddress, union Reg_WORLD *StoreRegs,struct MODBUS_MODULE *ModbusFrame)
{
	Uint16 WordIndex;
	WordIndex=ModbusFrame->Addr-BeginAddress;
	StoreRegs[WordIndex].bit.HIGH=ModbusFrame->RxBuf[4];
	StoreRegs[WordIndex].bit.LOW=ModbusFrame->RxBuf[5];
	for(WordIndex=0;WordIndex < ModbusFrame->RxLen;WordIndex++)
	{
		ModbusFrame->TxBuf[WordIndex]=ModbusFrame->RxBuf[WordIndex];
	}
	ModbusFrame->TxLen=ModbusFrame->RxLen;
	ModbusFrame->Status=OACK_RDY;
}

//×¢Òâ£¬Î»µØÖ·±ØÐë´Ó8µÄÕûÊý±¶¿ªÊ¼£¬²»È»»áµ¼ÖÂ´íÎ»
void ModbusRTU_WriteCoils_0x0F(Uint16 BeginAddress,union Byte_Bits *StoreRegs,struct MODBUS_MODULE *ModbusFrame)
{
	union Byte_Bits  TempByteBits;
	Uint8 TempChar[8],Index=8,CoilBitIndex;
	Uint16 ByteIndex;

	ModbusFrame->Pointer=7;//ÏÂ±êµÚÆß¸ö¿ªÊ¼ÎªÐ´Èë±äÁ¿µÄÊý¾Ý
	ByteIndex=(ModbusFrame->Addr-BeginAddress)>>3;
	CoilBitIndex=ModbusFrame->Addr & 0x07;
	while(ModbusFrame->Num--)
	{
		if(Index==8)
		{
			Index=0;
			TempByteBits.all=ModbusFrame->RxBuf[ModbusFrame->Pointer++];
			if(TempByteBits.bit.Bit0 == 1)TempChar[0]=0x0FF;
									 else TempChar[0]=0x000;
			if(TempByteBits.bit.Bit1 == 1)TempChar[1]=0x0FF;
									 else TempChar[1]=0x000;
			if(TempByteBits.bit.Bit2 == 1)TempChar[2]=0x0FF;
									 else TempChar[2]=0x000;
			if(TempByteBits.bit.Bit3 == 1)TempChar[3]=0x0FF;
									 else TempChar[3]=0x000;
			if(TempByteBits.bit.Bit4 == 1)TempChar[4]=0x0FF;
									 else TempChar[4]=0x000;
			if(TempByteBits.bit.Bit5 == 1)TempChar[5]=0x0FF;
									 else TempChar[5]=0x000;
			if(TempByteBits.bit.Bit6 == 1)TempChar[6]=0x0FF;
									 else TempChar[6]=0x000;
			if(TempByteBits.bit.Bit7 == 1)TempChar[7]=0x0FF;
									 else TempChar[7]=0x000;
		}

		switch(CoilBitIndex++)
		{
			case 0:
					StoreRegs[ByteIndex].bit.Bit0=TempChar[Index++];
					break;

			case 1:
					StoreRegs[ByteIndex].bit.Bit1=TempChar[Index++];
					break;

			case 2:
					StoreRegs[ByteIndex].bit.Bit2=TempChar[Index++];
					break;

			case 3:
					StoreRegs[ByteIndex].bit.Bit3=TempChar[Index++];
					break;

			case 4:
					StoreRegs[ByteIndex].bit.Bit4=TempChar[Index++];
					break;

			case 5:
					StoreRegs[ByteIndex].bit.Bit5=TempChar[Index++];
					break;

			case 6:
					StoreRegs[ByteIndex].bit.Bit6=TempChar[Index++];
					break;

			case 7:
					StoreRegs[ByteIndex++].bit.Bit7=TempChar[Index++];
					CoilBitIndex=0;
					break;
			default :
					break;
		}


	}
	for(Index=0;Index<6;Index++)
		ModbusFrame->TxBuf[Index]=ModbusFrame->RxBuf[Index];
	ModbusFrame->CRCCode=CRC16(ModbusFrame->RxBuf,6);
	ModbusFrame->TxBuf[6]=ModbusFrame->CRCCode>>8;
	ModbusFrame->TxBuf[7]=ModbusFrame->CRCCode&0xFF;
	ModbusFrame->TxLen=8;
	ModbusFrame->Status=OACK_RDY;

}

void ModbusRTU_WriteRegs_0x10(Uint16 BeginAddress, union Reg_WORLD *StoreRegs,struct MODBUS_MODULE *ModbusFrame)
{
	Uint16 WordIndex;
	ModbusFrame->Pointer=7;
	WordIndex=ModbusFrame->Addr-BeginAddress;
	while(ModbusFrame->Num--)
	{
		StoreRegs[WordIndex].bit.HIGH=ModbusFrame->RxBuf[ModbusFrame->Pointer++];
		StoreRegs[WordIndex].bit.LOW=ModbusFrame->RxBuf[ModbusFrame->Pointer++];
		WordIndex++;
	}
	for(ModbusFrame->Pointer=0;ModbusFrame->Pointer<6;ModbusFrame->Pointer++)
	{
		ModbusFrame->TxBuf[ModbusFrame->Pointer]=ModbusFrame->RxBuf[ModbusFrame->Pointer];
	}
	ModbusFrame->CRCCode=CRC16(ModbusFrame->TxBuf,ModbusFrame->Pointer);
	ModbusFrame->TxBuf[ModbusFrame->Pointer++]=ModbusFrame->CRCCode>>8;
	ModbusFrame->TxBuf[ModbusFrame->Pointer++]=ModbusFrame->CRCCode&0xFF;
	ModbusFrame->TxLen=ModbusFrame->Pointer;
	ModbusFrame->Status=OACK_RDY;

}

void Assemble_StorageMap_Regs()
{
	FloatAndUint32.FloatType=Grid_m;//
	StorageMap_Reg[Grid_m_INDEX].all	 =FloatAndUint32.Uint32Type.words.LowWord.all;  //#define Id_Set_INDEX  		50float Id_ref;
	StorageMap_Reg[Grid_m_INDEX+1].all	 =FloatAndUint32.Uint32Type.words.HighWord.all;

	FloatAndUint32.FloatType=Id_ref;//
	StorageMap_Reg[Id_Set_INDEX].all	 =FloatAndUint32.Uint32Type.words.LowWord.all;  //#define Id_Set_INDEX  		50float Id_ref;
	StorageMap_Reg[Id_Set_INDEX+1].all	 =FloatAndUint32.Uint32Type.words.HighWord.all;

	FloatAndUint32.FloatType=Udc_ref;//
	StorageMap_Reg[Udc_ref_INDEX].all	 =FloatAndUint32.Uint32Type.words.LowWord.all;  //#define Id_Set_INDEX  		50float Id_ref;
	StorageMap_Reg[Udc_ref_INDEX+1].all	 =FloatAndUint32.Uint32Type.words.HighWord.all;

	FloatAndUint32.FloatType=pi1_id_Kp;//
	StorageMap_Reg[Id_Kp_INDEX].all	 	 =FloatAndUint32.Uint32Type.words.LowWord.all;  //#define Id_Set_INDEX  		50float Id_ref;
	StorageMap_Reg[Id_Kp_INDEX+1].all	 =FloatAndUint32.Uint32Type.words.HighWord.all;

	FloatAndUint32.FloatType=pi1_id_Ki;//
	StorageMap_Reg[Id_Ki_INDEX].all		 =FloatAndUint32.Uint32Type.words.LowWord.all;  //#define Id_Set_INDEX  		50float Id_ref;
	StorageMap_Reg[Id_Ki_INDEX+1].all	 =FloatAndUint32.Uint32Type.words.HighWord.all;

	FloatAndUint32.FloatType=pi1_iq_Kp;//
	StorageMap_Reg[Iq_Kp_INDEX].all		 =FloatAndUint32.Uint32Type.words.LowWord.all;  //#define Id_Set_INDEX  		50float Id_ref;
	StorageMap_Reg[Iq_Kp_INDEX+1].all	 =FloatAndUint32.Uint32Type.words.HighWord.all;

	FloatAndUint32.FloatType=pi1_iq_Ki;//
	StorageMap_Reg[Iq_Ki_INDEX].all		 =FloatAndUint32.Uint32Type.words.LowWord.all;  //#define Id_Set_INDEX  		50float Id_ref;
	StorageMap_Reg[Iq_Ki_INDEX+1].all	 =FloatAndUint32.Uint32Type.words.HighWord.all;

	FloatAndUint32.FloatType=pi1_Vdc_Kp;//
	StorageMap_Reg[Udc_Kp_INDEX].all	 =FloatAndUint32.Uint32Type.words.LowWord.all;  //#define Id_Set_INDEX  		50float Id_ref;
	StorageMap_Reg[Udc_Kp_INDEX+1].all	 =FloatAndUint32.Uint32Type.words.HighWord.all;

	FloatAndUint32.FloatType=pi1_Vdc_Ki;//
	StorageMap_Reg[Udc_Ki_INDEX].all	 =FloatAndUint32.Uint32Type.words.LowWord.all;  //#define Id_Set_INDEX  		50float Id_ref;
	StorageMap_Reg[Udc_Ki_INDEX+1].all	 =FloatAndUint32.Uint32Type.words.HighWord.all;

	FloatAndUint32.FloatType=0;
	StorageMap_Reg[PF_Set_INDEX].all	 =FloatAndUint32.Uint32Type.words.LowWord.all;  //#define Id_Set_INDEX  		50float Id_ref;
	StorageMap_Reg[PF_Set_INDEX+1].all	 =FloatAndUint32.Uint32Type.words.HighWord.all;

	FloatAndUint32.FloatType=0;
	StorageMap_Reg[Q_Set_INDEX].all		 =FloatAndUint32.Uint32Type.words.LowWord.all;  //#define Id_Set_INDEX  		50float Id_ref;
	StorageMap_Reg[Q_Set_INDEX+1].all	 =FloatAndUint32.Uint32Type.words.HighWord.all;

	FloatAndUint32.FloatType=0;
	StorageMap_Reg[Q_Discharge_INDEX].all	     =FloatAndUint32.Uint32Type.words.LowWord.all;  //#define Id_Set_INDEX  		50float Id_ref;
	StorageMap_Reg[Q_Discharge_INDEX+1].all	     =FloatAndUint32.Uint32Type.words.HighWord.all;

	FloatAndUint32.FloatType=0;
	StorageMap_Reg[TAM_Float_Reserved1].all		 =FloatAndUint32.Uint32Type.words.LowWord.all;  //#define Id_Set_INDEX  		50float Id_ref;
	StorageMap_Reg[TAM_Float_Reserved1+1].all	 =FloatAndUint32.Uint32Type.words.HighWord.all;


	FloatAndUint32.FloatType=Grid_Ia;//
	StorageMap_Reg[Gird_Ia_RMS_INDEX].all	 =FloatAndUint32.Uint32Type.words.LowWord.all;  //#define Id_Set_INDEX  		50float Id_ref;
	StorageMap_Reg[Gird_Ia_RMS_INDEX+1].all	 =FloatAndUint32.Uint32Type.words.HighWord.all;

	FloatAndUint32.FloatType=Grid_Ib;//
	StorageMap_Reg[Gird_Ib_RMS_INDEX].all	 =FloatAndUint32.Uint32Type.words.LowWord.all;  //#define Id_Set_INDEX  		50float Id_ref;
	StorageMap_Reg[Gird_Ib_RMS_INDEX+1].all	 =FloatAndUint32.Uint32Type.words.HighWord.all;

	FloatAndUint32.FloatType=Grid_Ic;//
	StorageMap_Reg[Gird_Ic_RMS_INDEX].all	 =FloatAndUint32.Uint32Type.words.LowWord.all;  //#define Id_Set_INDEX  		50float Id_ref;
	StorageMap_Reg[Gird_Ic_RMS_INDEX+1].all	 =FloatAndUint32.Uint32Type.words.HighWord.all;

	FloatAndUint32.FloatType=Grid_Freq;//
	StorageMap_Reg[Gird_Freq_INDEX].all		 =FloatAndUint32.Uint32Type.words.LowWord.all;  //#define Id_Set_INDEX  		50float Id_ref;
	StorageMap_Reg[Gird_Freq_INDEX+1].all	 =FloatAndUint32.Uint32Type.words.HighWord.all;

	FloatAndUint32.FloatType=0;
	StorageMap_Reg[PF_INDEX].all	 		 =FloatAndUint32.Uint32Type.words.LowWord.all;  //#define Id_Set_INDEX  		50float Id_ref;
	StorageMap_Reg[PF_INDEX+1].all			 =FloatAndUint32.Uint32Type.words.HighWord.all;

	FloatAndUint32.FloatType=0;
	StorageMap_Reg[Temp_INDEX].all		 	 =FloatAndUint32.Uint32Type.words.LowWord.all;  //#define Id_Set_INDEX  		50float Id_ref;
	StorageMap_Reg[Temp_INDEX+1].all	 	 =FloatAndUint32.Uint32Type.words.HighWord.all;

	FloatAndUint32.FloatType=0;
	StorageMap_Reg[DCI_RMS_INDEX].all		 =FloatAndUint32.Uint32Type.words.LowWord.all;  //#define Id_Set_INDEX  		50float Id_ref;
	StorageMap_Reg[DCI_RMS_INDEX+1].all		 =FloatAndUint32.Uint32Type.words.HighWord.all;

	FloatAndUint32.FloatType=0;
	StorageMap_Reg[TM_Float_Reserved1].all	 =FloatAndUint32.Uint32Type.words.LowWord.all;  //#define Id_Set_INDEX  		50float Id_ref;
	StorageMap_Reg[TM_Float_Reserved1+1].all =FloatAndUint32.Uint32Type.words.HighWord.all;



	//	TAM_Second,TAM_Minute,TAM_Hour,TAM_Day,TAM_Month,TAM_Year,TAM_StationNum;
	StorageMap_Reg[Second_INDEX].all		 =TAM_Second;//#define Q_Set_INDEX  						0
	StorageMap_Reg[Minute_INDEX].all		 =TAM_Minute;//#define Q_Discharge_INDEX     			1
	StorageMap_Reg[Hour_INDEX].all		     =TAM_Hour;//#define LEVEL_INDEX  					2	unsigned int LEVEL;
	StorageMap_Reg[Day_INDEX].all	 		 =TAM_Day;//#define RunMode_INDEX  			3	unsigned int Run_Mode;
	StorageMap_Reg[Month_INDEX].all	 		 =TAM_Month;//#define Grid_m_INDEX  			4	float Grid_m;
	StorageMap_Reg[Year_INDEX].all	 		 =TAM_Year;//#define Udc_ref_INDEX  		5	float Udc_ref;
	StorageMap_Reg[StationNum_INDEX].all	 =TAM_StationNum;//#define Id_Kp_INDEX  		6   float pi1_id_Kp = 0.4489;
	StorageMap_Reg[LEVEL_INDEX].all		 	 =LEVEL;//#define Id_Ki_INDEX  		7   float pi1_id_Ki = 0.00308;
	StorageMap_Reg[RunMode_INDEX].all		 =Run_Mode;//#define Iq_Kp_INDEX  		8   float pi1_iq_Kp = 0.4489;
	StorageMap_Reg[WaveType_INDEX].all	     =WaveTpye;//#define Iq_Ki_INDEX  		9	float pi1_iq_Ki = 0.00308;


	StorageMap_Reg[Chcode_DSP_INDEX].all	 =1234;//#define Udc_Kp_INDEX  		10	float pi1_Vdc_Kp = 0.5;
	StorageMap_Reg[Grid_Pac_INDEX].all	 	 =Grid_Pac;//#define Udc_Ki_INDEX  		11	float pi1_Vdc_Ki= 0.003;
	StorageMap_Reg[Grid_Qac_INDEX].all	 	 =Grid_Qac;//#define Grid_Pac_INDEX  			12  int Grid_Pac;
	StorageMap_Reg[DCVU_RMS_INDEX].all	 	 =Vdc_Sample;//#define Grid_Qac_INDEX  			13	int Grid_Qac;
	StorageMap_Reg[DCVD_RMS_INDEX].all	 	 =Grid_Freq;//#define DC_V_Up_INDEX  					14	float Vdc_Sample;
	StorageMap_Reg[Grid_Vab_RMS_INDEX].all	 =Grid_Vab;//#define DC_V_Down_INDEX  					15
	StorageMap_Reg[Grid_Vbc_RMS_INDEX].all	 =Grid_Vbc;//#define Grid_Va_INDEX  			16	float Vab_Sample; unsigned int Grid_Vab;
	StorageMap_Reg[Grid_Vca_RMS_INDEX].all	 =Grid_Vca;//#define Grid_Vb_INDEX  			17	float Vbc_Sample; unsigned int Grid_Vbc;
	StorageMap_Reg[TM_int16_Reserved1].all	 =0;//#define Grid_Vc_INDEX  			18	float Vca_Sample; unsigned int Grid_Vca;



}

void Assemble_InputMap_Regs()
{
	//TM_Grid_State1,TM_Grid_HF,TM_Grid_SF1,TM_Grid_SF2,TM_Grid_ServerF;
	InputMap_Reg[Grid_State1_INDEX].all	 = TM_Grid_State1;//#define Grid_State1_INDEX     0
	InputMap_Reg[Grid_HF_INDEX].all		 = TM_Grid_HF;//#define Grid_HF_INDEX 		1
	InputMap_Reg[Grid_SF1_INDEX].all	 = TM_Grid_SF1;	//	2
	InputMap_Reg[Grid_SF2_INDEX].all	 = TM_Grid_SF2; // 		3
	InputMap_Reg[Grid_ServerF_INDEX].all = TM_Grid_ServerF;//#define Grid_ServerF_INDEX    4
	InputMap_Reg[Grid_COMM_INDEX].all	 =1;//#define Grid_COMM_INDEX   	5

	if(WaveTpye==2)
	{
		InputMap_Reg[WaveIndex.TotalIndex++].sall=Vdc_Sample;
		InputMap_Reg[WaveIndex.TotalIndex++].sall=Vdc_Sample;
		InputMap_Reg[WaveIndex.TotalIndex++].sall=Vdc_Sample;
		if(WaveIndex.TotalIndex>=310)WaveIndex.TotalIndex=DCV_WaveBegin;
	}
	else if(WaveTpye==0)
	{
		InputMap_Reg[WaveIndex.TotalIndex++].sall=Vab_Sample;
		InputMap_Reg[WaveIndex.TotalIndex++].sall=Vbc_Sample;
		InputMap_Reg[WaveIndex.TotalIndex++].sall=Vca_Sample;
		if(WaveIndex.TotalIndex>=310)WaveIndex.TotalIndex=ACV_WaveBegin;
	}
	else//WaveTpye==1
	{
		InputMap_Reg[WaveIndex.TotalIndex++].sall=Ia_Sample;
		InputMap_Reg[WaveIndex.TotalIndex++].sall=Ib_Sample;
		InputMap_Reg[WaveIndex.TotalIndex++].sall=Ic_Sample;
		if(WaveIndex.TotalIndex>=310)WaveIndex.TotalIndex=ACI_WaveBegin;
	}

}

void Assemble_Coil_Regs()
{
	Coil_Reg[0].bit.Bit0=Start_CMD; 			 //#define Start_Stop_INDEX     0 unsigned int Sys_Run;
	Coil_Reg[0].bit.Bit1=Reset_CMD; //#define Reset_INDEX    		1 unsigned int Reset_onetime_flag;
	Coil_Reg[0].bit.Bit2=RemoteOrLocal; 	 //#define Local_Remote_INDEX   2
	Coil_Reg[0].bit.Bit3=0; 				 //#define Reborn_INDEX    	    3
	Coil_Reg[0].bit.Bit4=0; 				 //#define SVG_EN_INDEX    	    4
	Coil_Reg[0].bit.Bit5=0; 				 //
	Coil_Reg[0].bit.Bit6=0; 				 //
	Coil_Reg[0].bit.Bit7=0; 				 //

}

void Unpack_StorageMap_Regs()
{

	FloatAndUint32.Uint32Type.words.LowWord.all=StorageMap_Reg[Grid_m_INDEX].all;  //#define Id_Set_INDEX  		50float Id_ref;
	FloatAndUint32.Uint32Type.words.HighWord.all=StorageMap_Reg[Grid_m_INDEX+1].all;
	Grid_m=FloatAndUint32.FloatType;

	FloatAndUint32.Uint32Type.words.LowWord.all=StorageMap_Reg[Id_Set_INDEX].all;  //#define Id_Set_INDEX  		50float Id_ref;
	FloatAndUint32.Uint32Type.words.HighWord.all=StorageMap_Reg[Id_Set_INDEX+1].all;
	Id_ref=FloatAndUint32.FloatType;

	FloatAndUint32.Uint32Type.words.LowWord.all=StorageMap_Reg[Udc_ref_INDEX].all;  //#define Id_Set_INDEX  		50float Id_ref;
	FloatAndUint32.Uint32Type.words.HighWord.all=StorageMap_Reg[Udc_ref_INDEX+1].all;
	Udc_ref=FloatAndUint32.FloatType;

	FloatAndUint32.Uint32Type.words.LowWord.all=StorageMap_Reg[Id_Kp_INDEX].all;  //#define Id_Set_INDEX  		50float Id_ref;
	FloatAndUint32.Uint32Type.words.HighWord.all=StorageMap_Reg[Id_Kp_INDEX+1].all;
	pi1_id_Kp=FloatAndUint32.FloatType;

	FloatAndUint32.Uint32Type.words.LowWord.all=StorageMap_Reg[Id_Ki_INDEX].all;  //#define Id_Set_INDEX  		50float Id_ref;
	FloatAndUint32.Uint32Type.words.HighWord.all=StorageMap_Reg[Id_Ki_INDEX+1].all;
	pi1_id_Ki=FloatAndUint32.FloatType;

	FloatAndUint32.Uint32Type.words.LowWord.all=StorageMap_Reg[Iq_Kp_INDEX].all;  //#define Id_Set_INDEX  		50float Id_ref;
	FloatAndUint32.Uint32Type.words.HighWord.all=StorageMap_Reg[Iq_Kp_INDEX+1].all;
	pi1_iq_Kp=FloatAndUint32.FloatType;

	FloatAndUint32.Uint32Type.words.LowWord.all=StorageMap_Reg[Iq_Ki_INDEX].all;  //#define Id_Set_INDEX  		50float Id_ref;
	FloatAndUint32.Uint32Type.words.HighWord.all=StorageMap_Reg[Iq_Ki_INDEX+1].all;
	pi1_iq_Ki=FloatAndUint32.FloatType;

	FloatAndUint32.Uint32Type.words.LowWord.all=StorageMap_Reg[Udc_Kp_INDEX].all;  //#define Id_Set_INDEX  		50float Id_ref;
	FloatAndUint32.Uint32Type.words.HighWord.all=StorageMap_Reg[Udc_Kp_INDEX+1].all;
	pi1_Vdc_Kp=FloatAndUint32.FloatType;

	FloatAndUint32.Uint32Type.words.LowWord.all=StorageMap_Reg[Udc_Ki_INDEX].all;  //#define Id_Set_INDEX  		50float Id_ref;
	FloatAndUint32.Uint32Type.words.HighWord.all=StorageMap_Reg[Udc_Ki_INDEX+1].all;
	pi1_Vdc_Ki=FloatAndUint32.FloatType;


//	FloatAndUint32.Uint32Type.words.LowWord.all=StorageMap_Reg[PF_Set_INDEX].all;  //#define Id_Set_INDEX  		50float Id_ref;
//	FloatAndUint32.Uint32Type.words.HighWord.all=StorageMap_Reg[PF_Set_INDEX+1].all;
//	0=FloatAndUint32.FloatType;
//
//	FloatAndUint32.Uint32Type.words.LowWord.all=StorageMap_Reg[Q_Set_INDEX].all;  //#define Id_Set_INDEX  		50float Id_ref;
//	FloatAndUint32.Uint32Type.words.HighWord.all=StorageMap_Reg[Q_Set_INDEX+1].all;
//	0=FloatAndUint32.FloatType;
//
//	FloatAndUint32.Uint32Type.words.LowWord.all=StorageMap_Reg[Q_Discharge_INDEX].all;  //#define Id_Set_INDEX  		50float Id_ref;
//	FloatAndUint32.Uint32Type.words.HighWord.all=StorageMap_Reg[Q_Discharge_INDEX+1].all;
//	0=FloatAndUint32.FloatType;

//	TAM_Second,TAM_Minute,TAM_Hour,TAM_Day,TAM_Month,TAM_Year,TAM_StationNum;
	TAM_Second=StorageMap_Reg[Second_INDEX].all;//#define Q_Set_INDEX  						0
	TAM_Minute=StorageMap_Reg[Minute_INDEX].all;//#define Q_Discharge_INDEX     			1
	TAM_Hour=StorageMap_Reg[Hour_INDEX].all;//#define LEVEL_INDEX  					2	unsigned int LEVEL;
	TAM_Day=StorageMap_Reg[Day_INDEX].all;//#define RunMode_INDEX  			3	unsigned int Run_Mode;
	TAM_Month=StorageMap_Reg[Month_INDEX].all;//#define Grid_m_INDEX  			4	float Grid_m;
	TAM_Year=StorageMap_Reg[Year_INDEX].all;//#define Udc_ref_INDEX  		5	float Udc_ref;
	TAM_StationNum=StorageMap_Reg[StationNum_INDEX].all;//#define Id_Kp_INDEX  		6   float pi1_id_Kp = 0.4489;
	LEVEL=StorageMap_Reg[LEVEL_INDEX].all;//#define Id_Ki_INDEX  		7   float pi1_id_Ki = 0.00308;
//	0=StorageMap_Reg[RunMode_INDEX].all;//#define Iq_Kp_INDEX  		8   float pi1_iq_Kp = 0.4489;
	WaveTpye=StorageMap_Reg[WaveType_INDEX].all;
}

void Unpack_Coil_Regs()
{
    Start_CMD =Coil_Reg[0].bit.Bit0; 			 //#define Start_Stop_INDEX     0 unsigned int Sys_Run;
	Reset_CMD =Coil_Reg[0].bit.Bit1; //#define Reset_INDEX    		1 unsigned int Reset_onetime_flag;
	RemoteOrLocal=Coil_Reg[0].bit.Bit2;
	if((Reset_CMD == 1)&&(Start_CMD==0))
	Reset_onetime_flag = 1; 

}
