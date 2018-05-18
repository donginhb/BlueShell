/*
 * CRC.h
 *
 *  Created on: 2014-8-28
 *      Author: ONLYME
 */

#ifndef CRC_H_
#define CRC_H_

//全局变量声明
#ifdef CRC_GLOBALS
#define CRC_EXT
#else
#define CRC_EXT extern
#endif
//CRC_EXT
CRC_EXT Uint16 CRC_Code;

extern Uint16 CRC16(Uint8 *puchMsgg, Uint16 usDataLen);

#endif /* CRC_H_ */
