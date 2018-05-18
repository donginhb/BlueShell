/*=====================================================================================
 File name:     PARK_F.c  (float version)                  
                    
 Originator:	XIAN yuneng dianli
 
 Description:  The module of PARK calculation                  

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 2007-01-16	Release	Rev 1.0
-------------------------------------------------------------------------------------*/

#include "Solar_F.h"

//*********** Structure Init Function ****//
#pragma CODE_SECTION(park_PN_calc,"ramfuncs");
void park_PN_calc(park_PN *v)
{  
   float cos_ang,sin_ang;
   sin_ang = sin(v->ang);
   cos_ang = cos(v->ang);
   v->de = (v->ds * sin_ang) - (v->qs * cos_ang);
   v->qe = (v->ds * cos_ang) + (v->qs * sin_ang);
   v->os = v->os;                                                            
}
