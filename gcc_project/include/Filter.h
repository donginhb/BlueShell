

/* ==================================================================================
File name:       FILTER.H   (IQ version)                  
                     
Originator:	XJRX

Description: 
Header file containing constants, data type definitions, and 
function prototypes for the FILTER.
用来滤除子模块直流母线电压中的100Hz分量
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 2013-7-3		Release	Rev 1.0                                                   
-----------------------------------------------------------------------------------*/
#ifndef __FILTER_H__
#define __FILTER_H__

typedef struct {  float  input;       /* Input:  */
				  float  output;		/* Output: */              
		 	 	  void  (*calc)();	  	/* Pointer to calculation function */ 
	              float  Udc[11];
				 } FILTER;	            

typedef FILTER *FILTER_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the FIRSTFILTER object.
目前直流母线电压采样的频率为10k/6;
因此10k/6*0.005s=8.3333，取8个点进行滤波
-----------------------------------------------------------------------------*/                     
#define FILTER_DEFAULTS {    0,    /*  input  */        \
						          0,    /*  output  */       \
              			          (void (*)(long))Filter_calc }

/*------------------------------------------------------------------------------
Prototypes for the functions in FILTER.C
------------------------------------------------------------------------------*/
void Filter_calc(FILTER_handle);


#endif

