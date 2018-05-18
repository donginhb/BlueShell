#ifndef SOLAR_F_H
#define SOLAR_F_H

#ifndef F28_DATA_TYPES
#define F28_DATA_TYPES
#ifndef DSP28_DATA_TYPES
#define DSP28_DATA_TYPES
//////////////////////////////////////////
typedef char               int8;
typedef unsigned char      Uint8;
//////////////////////////////////////////
typedef int             	int16;
typedef long            	int32;
typedef long long			int64;
typedef unsigned long long	Uint64;
typedef float           	float32;
typedef long double     	float64;
typedef unsigned long   Uint32;
typedef unsigned int    Uint16; 
#endif
#endif


#ifndef _TI_STD_TYPES
#define _TI_STD_TYPES
typedef int             Int;
typedef unsigned        Uns;
typedef char            Char;
typedef char            *String;
typedef void            *Ptr;
typedef unsigned short	Bool;

#endif

#include "math.h"
#include "CLARKE_F.h"
#include "iCLARKE_F.h"
#include "iPARK_F.h"
#include "PARK_F.h" 
#include "CNTL_PI_F.h"
#include "rampgen.h"
#include "svgen_dq.h"
#include "integral.h"


#endif
