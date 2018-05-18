#ifndef PARK_F_H
#define PARK_F_H

//*********** Structure Definition ********//

typedef struct {
	   float ds;/*new version for doubly transfer edit by hq20110210*/
	   float qs;
       float os;   
       float ang; 
       float de;
	   float qe;
       float oe;
       void (*calc)();     	 /* Pointer to the calulation function                   */
       } park_PN;     /* Data type created      */

/* 
Note that 
         speed_scaler = 60*f/rmp_max 
where f = CLK_freq/(128*N), N = number of teeth in sprocket
and 128 is pre-determined prescaler of timer 2 (used by capture)
*/
//number of teeth in sprocket:30,f_cpu:60MHz,Pre_sca:128
typedef park_PN *park_PN_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the SPEED_MEAS_CAP object.
-----------------------------------------------------------------------------*/                     
/* speed_scaler = 260 based on f(clk) 25 MHz, f(samping)=16.67, 25 kHz*/
/* rmp_max = 1800 rpm */

#define TWICE_PI  float(6.283185307)
#define park_PN_DEFAULTS   { 0, \
                                    0, \
                                    0, \
                                    0, \
                                    0, \
                                    0, \
                                    0, \
									(void (*)(long))park_PN_calc }
                                  

/*------------------------------------------------------------------------------
Prototypes for the functions in SPEED_PR.C
------------------------------------------------------------------------------*/
void park_PN_calc(park_PN_handle); 



#endif /* PARK_F_H_ */
