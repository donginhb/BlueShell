#ifndef CLARKE_F_H
#define CLARKE_F_H
//#include "IQmathLib.h"         /* Include header for IQmath library */

typedef struct {  float  as;  		/* Input: phase-a stator variable  */
				  float  bs;			/* Input: phase-b stator variable  */
				  float  cs;          /* Input:*/
				  float  ds;			/* Output: stationary d-axis stator variable  */
				  float  qs;			/* Output: stationary q-axis stator variable  */
		 	 	  float  os;
		 	 	  void  (*calc)();	/* Pointer to calculation function */ 
				 } CLARKE;	            

typedef CLARKE *CLARKE_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the CLARKE object.
-----------------------------------------------------------------------------*/                     
#define CLARKE_DEFAULTS { 0, \
                          0, \
                          0, \
                          0, \
              			  0, \
                          0, \
              			  (void (*)(long))clarke_calc }

/*------------------------------------------------------------------------------
Prototypes for the functions in CLARKE.C
------------------------------------------------------------------------------*/
void clarke_calc(CLARKE_handle);


#endif /* CLARKE_F_H_ */
