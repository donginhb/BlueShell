#ifndef IPARK_F_H_
#define IPARK_F_H_

//*********** Structure Definition ********//
typedef struct {  float  ds;  	/* Output: stationary d-axis stator variable */
				  float  qs;		/* Output: stationary q-axis stator variable */
				  float  os;
				  float  ang;		/* Input: rotating angle (pu) */
				  float  de;		/* Input: rotating d-axis stator variable */
				  float  qe;		/* Input: rotating q-axis stator variable */
		 	 	  float  oe;
		 	 	  void  (*calc)();	/* Pointer to calculation function */ 
				 } IPARK;	            

typedef IPARK *IPARK_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the IPARK object.
-----------------------------------------------------------------------------*/                     
#define IPARK_DEFAULTS {  0, \
                          0, \
                          0, \
                          0, \
                          0, \
                          0, \
                          0, \
              			  (void (*)(long))ipark_calc }

/*------------------------------------------------------------------------------
Prototypes for the functions in IPARK.C
------------------------------------------------------------------------------*/
void ipark_calc(IPARK_handle);


#endif /* iPARK_F_H_ */
