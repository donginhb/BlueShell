/*=====================================================================================
 File name:        iCLARKE_F.c  (float version)                  
                    
 Originator:	XIAN yuneng dianli
 
 Description:  The module of iCLARKE calculation                  

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 2007-01-16	Release	Rev 1.0
-------------------------------------------------------------------------------------*/
#include "hal.h"
#include "Solar_F.h"

//*********** Structure Init Function ****//
void iCLARKE_F_init(iCLARKE_F *v)
{
	v->a=0;
	v->b=0;
	v->c=0;
	v->alpha=0;
	v->beta=0;
}

//*********** Function Definition ********//
void iCLARKE_F_FUNC(iCLARKE_F *v)
{
	v->a = v->alpha + v->zero;
	v->b = -0.5*v->alpha + 0.8660254*v->beta + v->zero;
	v->c = -0.5*v->alpha - 0.8660254*v->beta + v->zero;
}

