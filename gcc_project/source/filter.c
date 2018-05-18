



/* ==================================================================================
File name:      FILTER.C   (IQ version)                  
                     
Originator:	XJGC RX

Description: 
Header file containing constants, data type definitions, and 
function prototypes for the FIRSTFILTER.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 2013-7-3		Release	Rev 1.0                                                   
-----------------------------------------------------------------------------------*/
/* Don't forget to set a proper GLOBAL_Q in "IQmathLib.h" file */
#include "Filter.h"

void Filter_calc(FILTER *v)
{
	int i;
	//直流母线电压采样频率2kHz,2000/4/50=10,10/2=5;
	for(i=5;i>0;i--)
		v->Udc[i]=v->Udc[i-1];
    v->Udc[0] = v->input;
    v->output = 0.5 * (v->Udc[0] + v->Udc[5]);
}

