#include "RMS.h"
#include "math.h"
#pragma CODE_SECTION(RMS_calc,"ramfuncs");
void RMS_calc(RMS *v)
{		                    
//	v->F_sample = 120;   //在RMS.h中初始化时赋初值RMS_DEFAULTS                            
    v->rms++;                                       
   if(v->rms <= v->F_sample)                        
   {                                               
        v->Ia_A2 = v->in * v->in;                            
        v->Ia_A1 = v->Ia_A1 + v->Ia_A2; 
   } 
   else
   {
		v->Ia_B1 = v->Ia_A1/v->F_sample;
		v->out = sqrt(v->Ia_B1);
		v->Ia_A1 = 0;
		v->rms = 0;
   }
}
