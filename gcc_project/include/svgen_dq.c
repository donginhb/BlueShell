#include "Solar_F.h"
/* Don't forget to set a proper GLOBAL_Q in "IQmathLib.h" file */
#include "svgen_dq.h"

#pragma CODE_SECTION(svgendq_calc,"ramfuncs");
void svgendq_calc(SVGENDQ *v)
{	

	float Va,Vb,Vc,t1,t2;
	float sector = 0;  /* sector is treated as Q0 - independently with global Q */
																	
/* Inverse clarke transformation */
    Va = v->Ubeta;
    Vb = ((-0.5) * v->Ubeta) + ((0.8660254) * v->Ualfa);  /* 0.8660254 = sqrt(3)/2 */
    Vc = ((-0.5) * v->Ubeta) - ((0.8660254) * v->Ualfa);  /* 0.8660254 = sqrt(3)/2 */

/* 60 degree sector determination */
    if (Va>(0))
       sector = 1; 
    if (Vb>(0))
       sector = sector + 2;
    if (Vc>(0))   
       sector = sector + 4;
       
/* X,Y,Z (Va,Vb,Vc) calculations  */
    Va = v->Ubeta;                                                  /* X = Va */
    Vb = ((0.5) * v->Ubeta) + ((0.8660254) * v->Ualfa);   /* Y = Vb */
    Vc = ((0.5) * v->Ubeta) - ((0.8660254) * v->Ualfa);   /* Z = Vc */
       
    if (sector==1)  /* sector 1: t1=Z and t2=Y (abc ---> Tb,Ta,Tc) */
    {
       t1 = Vc;
       t2 = Vb;
       v->Tb = (v->k * ((1)-t1-t2));      /* tbon = (1-t1-t2)/2 */
       v->Ta = v->Tb+t1;           /* taon = tbon+t1 */
       v->Tc = v->Ta+t2;           /* tcon = taon+t2 */
    }
    else if (sector==2)  /* sector 2: t1=Y and t2=-X (abc ---> Ta,Tc,Tb) */
    {
       t1 = Vb;
       t2 = -Va;
       v->Ta = (v->k * ((1)-t1-t2));      /* taon = (1-t1-t2)/2 */
       v->Tc = v->Ta+t1;           /* tcon = taon+t1 */
       v->Tb = v->Tc+t2;           /* tbon = tcon+t2 */
    }      
    else if (sector==3)  /* sector 3: t1=-Z and t2=X (abc ---> Ta,Tb,Tc) */
    {
       t1 = -Vc;
       t2 = Va;
       v->Ta = (v->k * ((1)-t1-t2));      /* taon = (1-t1-t2)/2 */
       v->Tb = v->Ta+t1;           /* tbon = taon+t1 */
       v->Tc = v->Tb+t2;           /* tcon = tbon+t2 */
    }   
    else if (sector==4)  /* sector 4: t1=-X and t2=Z (abc ---> Tc,Tb,Ta) */
    {
       t1 = -Va;
       t2 = Vc;
       v->Tc = (v->k * ((1)-t1-t2));      /* tcon = (1-t1-t2)/2 */
       v->Tb = v->Tc+t1;           /* tbon = tcon+t1 */
       v->Ta = v->Tb+t2;           /* taon = tbon+t2 */
    }   
    else if (sector==5)  /* sector 5: t1=X and t2=-Y (abc ---> Tb,Tc,Ta) */
    {
       t1 = Va;
       t2 = -Vb;
       v->Tb = (v->k * ((1)-t1-t2));      /* tbon = (1-t1-t2)/2 */
       v->Tc = v->Tb+t1;           /* tcon = tbon+t1 */
       v->Ta = v->Tc+t2;           /* taon = tcon+t2 */
    }   
    else if (sector==6)  /* sector 6: t1=-Y and t2=-Z (abc ---> Tc,Ta,Tb) */
    {
       t1 = -Vb;
       t2 = -Vc;
       v->Tc = (v->k * ((1)-t1-t2));      /* tcon = (1-t1-t2)/2 */
       v->Ta = v->Tc+t1;           /* taon = tcon+t1 */
       v->Tb = v->Ta+t2;           /* tbon = taon+t2 */
    }  
 
     v->Ta =1-v->Ta;
	 v->Tb =1-v->Tb;
	 v->Tc =1-v->Tc;      

}




