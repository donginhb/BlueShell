/*=====================================================================================
File name:       svpwm_npc.c  (float version)                    
                    
Originator:	 Converter Control Group--XAXJ

Description: 

 Description:  Space-vector PWM generation for npc                    

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 2007-01-16	Release	Rev 1.0
-------------------------------------------------------------------------------------*/
#include "svpwm_npc.h"
extern float C_Multiply_fs;

//#pragma CODE_SECTION(svpwmnpc_calc,"ramfuncs");
void svpwmnpc_calc(SVPWMNPC *v)

{	

	float Va,Vb,Vc;
	extern float Ia_Sample,Ib_Sample,Ic_Sample;
	float Vmax_SP,Vmin_SP,Voff;
	float Vmax_SV,Vmin_SV;
	float delta_Vd_a,delta_Vd_b,delta_Vd_c,Vd_low,Vd_up;
	int mid_phase,max_phase,min_phase;
	extern unsigned int LEVEL;
//	extern float DETA_V;
//	extern float SV_Ta1;
	extern float DETA_UP;
//	extern float Ta1_test;
//	extern float Ta2_test;															
/* Inverse clarke transformation */
    Va = v->Ualfa + v->Uzero;
    Vb = -0.5*v->Ualfa + 0.8660254*v->Ubeta + v->Uzero;  /* 0.8660254 = sqrt(3)/2 */
    Vc = -0.5*v->Ualfa - 0.8660254*v->Ubeta + v->Uzero;  /* 0.8660254 = sqrt(3)/2 */

/*  Voff calculate */
	MAX(Vmax_SP, Va, Vb, Vc);
	MIN(Vmin_SP, Va, Vb, Vc);	
	
	Voff = -0.5 * (Vmax_SP + Vmin_SP);

/* SPWM TO SVPWM */	
	Va = Va + Voff;      //加Voffset1,使正弦调制波变为马鞍形调制波
	Vb = Vb + Voff;
	Vc = Vc + Voff;
	if((LEVEL==3)||(LEVEL ==4))
	{
		if(Ia_Sample >= 0)
			Va += 0.048;
		else if(Ia_Sample < 0)
			Va -= 0.048;
		if(Ib_Sample >= 0)
			Vb += 0.048;
		else if(Ib_Sample < 0)
			Vb -= 0.048;
		if(Ic_Sample >= 0)
			Vc += 0.048;
		else if(Ic_Sample < 0)
			Vc -= 0.048;
	}
	//零序环流抑制算法

	MAX(Vmax_SV, Va, Vb, Vc);
	MIN(Vmin_SV, Va, Vb, Vc);

//	Ta1_test=Vmax_SV;

/*	v->U0 =(-0.1)*(v->Ia + v->Ib + v->Ic);

	SATURATE(v->U0, -1.0-Vmin_SV, 1.0-Vmax_SV); //动态限幅

	SATURATE(v->U0, -0.1, 0.1);//0.08
	
	Va = Va + v->U0;
	Vb = Vb + v->U0;
	Vc = Vc + v->U0;

	MAX(Vmax_SV, Va, Vb, Vc);
 	MIN(Vmin_SV, Va, Vb, Vc);
*/
//  delta_Vd culculate       中点电位平衡控制量delta_Vd计算
	if (Vmax_SV == Va)
		max_phase = 1;
	else if	(Vmax_SV == Vb)
		max_phase = 2;
	else
		max_phase = 3;

	if (Vmin_SV == Va)
		min_phase = 1;
	else if	(Vmin_SV == Vb)
		min_phase = 2;
	else
		min_phase = 3;

	mid_phase = 6 - max_phase - min_phase;

	switch(mid_phase)
	{

		case 1:	// 调节Va
		{
			
			if (fabs(v->Ia) <= 0.04)//0.04            限值5%
			{
				if (v->Ia >= 0)
				   v->Ia = 0.04;//0.04;
				else
				   v->Ia = -0.04;//-0.04;
			}
//			SV_Ta1 = (0.005 * v->Unp)/v->Ia;
//			delta_Vd_a = (0.617 * v->Unp)/ v->Ia + 0.5*(Vmax_SV - fabs(Va)); //0.617 = 0.2 * Udc / Iabc
			
			delta_Vd_a = (0.025 * v->Unp)/ v->Ia + 0.5*(Vmax_SV - fabs(Va)); //0.617 = 0.2 * Udc / Iabc
			Vd_up = 0.5 * (0.98-fabs(Va));
			Vd_low = 0;

//			DETA_UP = Vd_up;

		    SATURATE(delta_Vd_a, Vd_low, Vd_up);
			//SATURATE(delta_Vd_a, Vd_low, _IQ(0.2));

			delta_Vd_b = 0;
			delta_Vd_c = 0;

			break;
		}
		case 2:	// 调节Vb
		{
			if (fabs(v->Ib) <= 0.04)//0.04
			{
				if (v->Ib >= 0)
				   v->Ib = 0.04;//0.04;
				else
				   v->Ib = -0.04;//-0.04;
			}
			
//			delta_Vd_b = (0.617 * v->Unp)/v->Ib + 0.5 * (Vmax_SV - fabs(Vb));
			delta_Vd_b = (0.025 * v->Unp)/v->Ib + 0.5 * (Vmax_SV - fabs(Vb));			
			Vd_up = 0.5 * (0.98 - fabs(Vb));
			Vd_low = 0;
		    SATURATE(delta_Vd_b, Vd_low, Vd_up);
			//SATURATE(delta_Vd_b, Vd_low, _IQ(0.2));

			delta_Vd_a = 0;
			delta_Vd_c = 0;

			break;
		}
		case 3:	// 调节Vc
		{
			if (fabs(v->Ic) <= 0.04)//0.04
			{
				if (v->Ic >= 0)
				   v->Ic = 0.04;//0.04;
				else
				   v->Ic = -0.04;//-0.04;
			}
			
//			delta_Vd_c = (0.617 * v->Unp)/v->Ic + 0.5 * (Vmax_SV - fabs(Vc));
			delta_Vd_c = (0.025 * v->Unp)/v->Ic + 0.5 * (Vmax_SV - fabs(Vc));
			Vd_up = 0.5*(0.98 - fabs(Vc));
			Vd_low = 0;
		    SATURATE(delta_Vd_c, Vd_low, Vd_up);
			//SATURATE(delta_Vd_c, Vd_low, _IQ(0.2));

			delta_Vd_a = 0;
			delta_Vd_b = 0;

			break;
		}
		case 0:	// 无效
		{
			delta_Vd_a = 0;
			delta_Vd_b = 0;
			delta_Vd_c = 0;
			break;
		}
	}


//			delta_Vd_a = 0;
//			delta_Vd_b = 0;
//			delta_Vd_c = 0;
  //			DETA_V = delta_Vd_a;
			
	if (Va >= 0)
	{
  //		Ta2_test=Va;
		v->Ta1 = Va + delta_Vd_a;
		v->Ta2 = -delta_Vd_a;
	}
	else
	{	
		v->Ta1 = delta_Vd_a;
		v->Ta2 = Va - delta_Vd_a;
	}

	if (Vb >= 0)
	{
		v->Tb1 = Vb + delta_Vd_b;
		v->Tb2 = -delta_Vd_b;
	}
	else
	{
		v->Tb1 = delta_Vd_b;
		v->Tb2 = Vb - delta_Vd_b;
	}

	if (Vc >= 0)
	{
		v->Tc1 = Vc + delta_Vd_c;
		v->Tc2 = -delta_Vd_c;
	}
	else
	{
		v->Tc1 = delta_Vd_c;
		v->Tc2 = Vc - delta_Vd_c;
	}
 

    SATURATE(v->Ta1, 0, 0.98);
    SATURATE(v->Tb1, 0, 0.98);
    SATURATE(v->Tc1, 0, 0.98);
    SATURATE(v->Ta2, -0.98, 0);
    SATURATE(v->Tb2, -0.98, 0);
    SATURATE(v->Tc2, -0.98, 0);

}
