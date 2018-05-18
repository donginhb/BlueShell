/*=====================================================================================
 File name:        MPPT.C  (IQ version)                  
                    

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 05-15-2008	Release	Rev 1.0
-------------------------------------------------------------------------------------*/

#include "Solar_F.h"
//#include "parameter.h"
/* Don't forget to set a proper GLOBAL_Q in "IQmathLib.h" file */

//extern int Vdc_ref;
extern float MPPT_Step;
void MPPT_PNO_F_FUNC(MPPT *v)
{
/* dP-P&O */  
 
if(v->pv_i < 10)                // 到开路电压以上往回寻找MPP
  v->deltu = -MPPT_Step;
else
{
  if(v->pv_p > v->pv_p1)                   
  {
	 if(v->pv_v > v->pv_v1)              // 若P(k)>P(k-1)且V(k)>V(k-1)，功率变化方向和
	    v->deltu = MPPT_Step;
	 else                                // 若P(k)>P(k-1)且V(k)<V(k-1)，功率变化方向和
		v->deltu = -MPPT_Step;
  }
  if(v->pv_p < v->pv_p1)
  {
     if(v->pv_v > v->pv_v1)            // 若P(k)<P(k-1)且V(k)>V(k-1)，功率变化方向和
		  //Vdc_ref -= MPPT_Step;          // 扰动方向不一致,应减小电压
		v->deltu = -MPPT_Step;
     else                                   // 若P(k)<P(k-1)且V(k)<V(k-1)，功率变化方向和
		v->deltu = MPPT_Step;   
  } 
}
   v->pv_p1 = v->pv_p;                    // 令P(k-1)=P(k)
   v->pv_v1 = v->pv_v;                    // 令V(k-1)=V(k) 
   v->pv_i1 = v->pv_i;
}


