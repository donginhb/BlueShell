/**
 * EEPROM emulation with C2000 on-chip FLASH.
 * Author: Dong Xiao <echo@xaatx.com> 2015.4.9
 * user apps should not use FLASHB
 * [0x3F4000, 0x3F6000) for 2812  -> F281x_EEPROM.lib
 * [0x330000, 0x338000) for 28335 -> F2833x_EEPROM.lib
 *
 * main()
 * ...
 * InitFlash();
 * EEPROM_Init();
 * EEPROM_Load();
 * EALLOW;
 * Flash_CPUScaleFactor = SCALE_FACTOR;
 * Flash_CallbackPtr = NULL;
 * EDIS;
 * ...
 */

#ifndef _F28X_EEPROM_H_
#define _F28X_EEPROM_H_

#define MIRROR_DATLEN	255

// eeprom buffer, 255 words
extern Uint16 eeprom_mirror[MIRROR_DATLEN];

// init eeprom
// user should call this function in main(), after call InitFlash()
extern Uint16 EEPROM_Init(void);

// load eeprom contents from flash
extern Uint16 EEPROM_Load(void);

// flush eeprom contents to flash. caution: this routine will disable global interrupt
// if you want to call this routine, you should add Flash281x_API_Library to your project
extern Uint16 EEPROM_Save(void);

// Get Library version info
extern Uint16 EEPROM_Version(void);

// eeprom data access, you can also access eeprom_mirror directly.
extern Uint16 EEPROM_WriteUint16(Uint16 addr, Uint16  dat);
extern Uint16 EEPROM_ReadUint16 (Uint16 addr, Uint16 *dat);
extern Uint16 EEPROM_WriteUint32(Uint16 addr, Uint32  dat);
extern Uint16 EEPROM_ReadUint32 (Uint16 addr, Uint32 *dat);


#endif

