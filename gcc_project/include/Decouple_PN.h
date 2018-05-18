#ifndef __Decouple_PN_H__
#define __Decouple_PN_H__

typedef struct {
	   float32 de_p_in;/*new version for doubly transfer edit by hq20110210*/
	   float32 de_n_in;
     float32 qe_p_in;   
     float32 qe_n_in; 
     float32 angle;
	   float32 k1;
	   float32 k2;
	   //_iq k3;
	   float32 de_p_out_old;
     float32 de_n_out_old;
	   float32 qe_p_out_old;
	   float32 qe_n_out_old;
     float32 de_p_out_Filter_old;
	   float32 de_n_out_Filter_old;
	   float32 qe_p_out_Filter_old;
	   float32 qe_n_out_Filter_old;
     float32 de_p_out_Filter;
     float32 de_n_out_Filter;
	   float32 qe_p_out_Filter;
	   float32 qe_n_out_Filter;
	   float32 de_p_out;
     float32 de_n_out;
	   float32 qe_p_out;
	   float32 qe_n_out;
     void (*calc)();     	 /* Pointer to the calulation function                   */
       } DECOUPLE;     /* Data type created      */
       
typedef DECOUPLE *DECOUPLE_handle;

#define TWICE_PI  6.283185307
//CCS联合仿真按照双线性变换开关频率为8k计算公式如下k2=T/(T+Ts)=0.02674,k1=(Ts-T)/(T+Ts)=0.946519]  
#define DECOUPLE_DEFAULTS   { 0, \
                  0, \
                  0, \
                  0, \
                  0, \
                  0.946519, \
                  0.02674, \
									0, \
									0, \
									0, \
                  0, \
									0, \
                  0, \
                  0, \
                  0, \
                  0, \
                  0, \
									0, \
									0, \
									0, \
                  0, \
									0, \
                  0, \
									(void (*)(long))Decouple_PN_calc }

void Decouple_PN_calc(DECOUPLE_handle); 

#endif

