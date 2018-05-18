




/*=====================================================================================
 File name:        SPEED_PR.C  (IQ version)                  
                    
 Originator:	Digital Control Systems Group
			Texas Instruments

 Description:  Speed measurement computation based capture                   

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 05-15-2002	Release	Rev 1.0
-------------------------------------------------------------------------------------*/
/* Don't forget to set a proper GLOBAL_Q in "IQmathLib.h" file */
#include "Solar_F.h"
void CNTL_PR_F_init(CNTL_PR_F *k){

    k->a1 = -1.996;
	k->a2 = 0.9996;
	k->b0 = 0.03722;//0.3233;
	k->b1 = -0.06211;//-0.6211
	k->b2 = 0.025;//0.2988;
	k->Ref = 0;
	k->Fbk = 0;
	k->Out = 0;    
	k->qpr_out_old1 = 0;
	k->qpr_out_old2 = 0;
	k->qpr_in = 0;
	k->qpr_in_old1 = 0;
	k->qpr_in_old2 = 0;
}

void CNTL_PR_F_FUNC(CNTL_PR_F *v)
{  
   v->qpr_in = v->Ref - v->Fbk;
   
   v->Out = v->qpr_in * v->b0 + v->qpr_in_old1 * v->b1+ v->qpr_in_old2 * v->b2 - v->qpr_out_old1 * v->a1 - v->qpr_out_old2 * v->a2;
   
   v->qpr_in_old2 = v->qpr_in_old1;
   v->qpr_in_old1 = v->qpr_in;
   
   v->qpr_out_old2 = v->qpr_out_old1;
   v->qpr_out_old1 = v->Out; 
}
