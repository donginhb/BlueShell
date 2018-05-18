/* =================================================================================
File name:  SVGEN_DQ.H  (float version)                    
                    
Originator:	XIAN yuneng dianli

Description: 
Header file containing constants, data type definitions, and 
function prototypes for the SVGEN_DQ.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 2007-01-16		Release	Rev 1.0                                                   
------------------------------------------------------------------------------*/

#ifndef SVGEN_F_H
#define SVGEN_F_H


typedef struct 	{ float  Ualfa; 			/* Input: reference alfa-axis phase voltage   */
				  float  Ubeta;			/* Input: reference beta-axis phase voltage   */
				  float  k;
				  float  Ta;				/* Output: reference phase-a switching function  */			
				  float  Tb;				/* Output: reference phase-b switching function   */
				  float  Tc;				/* Output: reference phase-c switching function   */
				  void   (*calc)();	    /* Pointer to calculation function */ 
				} SVGENDQ;
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																				
typedef SVGENDQ *SVGENDQ_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the SVGENDQ object.
-----------------------------------------------------------------------------*/                     
#define SVGENDQ_DEFAULTS { 0,0,0.5,0,0,0,\
                       (void (*)(long))svgendq_calc }

/*------------------------------------------------------------------------------
Prototypes for the functions in SVGEN_DQ.C
------------------------------------------------------------------------------*/
void svgendq_calc(SVGENDQ_handle);



#endif
