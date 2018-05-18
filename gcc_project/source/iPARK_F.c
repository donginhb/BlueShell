/*=====================================================================================
 File name:     iPARK_F.c  (float version)                  
                    
 Originator:	XIAN yuneng dianli
 
 Description:  The module of IPARK calculation                  

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 2007-01-16	Release	Rev 1.0
-------------------------------------------------------------------------------------*/
#include "Solar_F.h"
#include "math.h"
#include "iPARK_F.h"

#pragma CODE_SECTION(ipark_calc,"ramfuncs");
void ipark_calc(IPARK *v)
{	
   
   float cos_ang,sin_ang;

     sin_ang = sin (v->ang);
     cos_ang = cos (v->ang);
         
     v->ds = (v->de * sin_ang) + (v->qe * cos_ang);
     v->qs = (v->qe * sin_ang) - (v->de * cos_ang); 
     v->os = v->oe;
     
}

