/*=====================================================================================
 File name:        integral.c  (float version)                  
                    
 Originator:	XIAN yuneng dianli
 
 Description:  The module of integral calculation                  

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 2007-01-16	Release	Rev 1.0
-------------------------------------------------------------------------------------*/
#include "integral.h"
#pragma CODE_SECTION(integral_calc,"ramfuncs");
void integral_calc(INTEGRAL *v)
{	
    v->integral_up = v->integral_ref + v->integral_fdb;
    v->integral_up = v->integral_up /(float)(v->integral_frequency); //1/v->integral_frequency 
    v->integral_out = v->integral_out + v->integral_up * 6.2831852;
	if( v->integral_out > 6.2831852) 
	{
		v->integral_out = v->integral_out - 6.2831852;                                 // 2*pi
	}

	if(v->integral_out < -6.2831852)
	{
       v->integral_out = 0;
    }	
 }
