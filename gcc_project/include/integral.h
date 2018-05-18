



/* =================================================================================
File name:       PID.H  (IQ version)                    
                    
Originator:	Wind Power Group---XJTU

Description: 
Header file containing constants, data type definitions, and 
function prototypes for the PID.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 2007-01-16		Release	Rev 1.0                                                   
------------------------------------------------------------------------------*/

typedef struct {  int  integral_frequency;
                  float  integral_ref;   	/* Input: Reference input  */
				  float  integral_fdb;   	/* Input: Feedback input  */
				  float  integral_up;
				  float  integral_out;
		 	 	  void  (*calc)();	  	/* Pointer to calculation function */ 
				 } INTEGRAL;	            

typedef INTEGRAL *INTEGRAL_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the PID object.
-----------------------------------------------------------------------------*/                     
#define INTEGRAL_DEFAULTS { 0, \
                            0, \
                            0, \
                            0, \
                            0, \
             			  (void (*)(long))integral_calc }

/*------------------------------------------------------------------------------
Prototypes for the functions in PID.C
------------------------------------------------------------------------------*/
void integral_calc(INTEGRAL_handle);
