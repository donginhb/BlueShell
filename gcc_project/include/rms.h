#ifndef RMS_H_
#define RMS_F_H_

//*********** Structure Definition ********//
typedef struct{
	float  in;  		//Input
    float  out;		//Output
	float  Ia_A1;
	float  Ia_A2;
	float  Ia_B1;
	float  Ia_B2;
	int    rms;
	int    F_sample;
	void   (*calc)();	    /* Pointer to calculation function */ 
}RMS;

typedef RMS *RMS_handle;

#define RMS_DEFAULTS { 0,0,0,0,0,0,0,600,\
                       (void (*)(long))RMS_calc}
#define RMS_DEFAULTS_40 { 0,0,0,0,0,0,0,40,\
                        (void (*)(long))RMS_calc}
//*********** Function Declarations *******//
//void RMS_F_init(RMS_F *v);
//void RMS_F_FUNC(RMS_F *v);

void RMS_calc(RMS_handle);

# endif
