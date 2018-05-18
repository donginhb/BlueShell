


/* =================================================================================
File name:        SPEED_PR.H  (IQ version)                 
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
    Header file containing the data types, constants for the period based
    speed measurement function. Also contains the prototypes for the 
    functions implemented in SPEED_PR.C
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 05-15-2002		Release	Rev 1.0                                                   
------------------------------------------------------------------------------*/
#ifndef CNTL_PR_F_H_
#define CNTL_PR_F_H_

typedef struct {
	   float a1;
	   float a2;
	   float b0;
	   float b1;
	   float b2;
	   float  Ref;   	/* Input: Reference input  */
	   float  Fbk;   	/* Input: Feedback input  */
	   float  Out;
	   float qpr_out_old1;
	   float qpr_out_old2;
	   float qpr_in;
	   float qpr_in_old1;
	   float qpr_in_old2;    	 /* Pointer to the calulation function                   */
       }CNTL_PR_F;     /* Data type created      */

//number of teeth in sprocket:30,f_cpu:60MHz,Pre_sca:128
/*-----------------------------------------------------------------------------
Default initalizer for the SPEED_MEAS_CAP object. //3233// 6211// 2988
-----------------------------------------------------------------------------*/                     
/*#define QPR_DEFAULTS   {            _IQ(-1.996), \
                                    _IQ(0.9996), \
                                    _IQ(0.3241), \  
                                    _IQ(-0.6209),\ 
                                    _IQ(0.298), \  
									0, \
									0, \
									0, \
									0, \
                                    0, \
									0, \
									0, \
                                    0, \
									(void (*)(long))QPR_calc }
*/
                             

/*------------------------------------------------------------------------------
Prototypes for the functions in quasi_pr.C
------------------------------------------------------------------------------*/
void CNTL_PR_F_init(CNTL_PR_F *k);
void CNTL_PR_F_FUNC(CNTL_PR_F *v); 
# endif
