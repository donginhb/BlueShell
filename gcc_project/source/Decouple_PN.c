#include "Solar_F.h"

void Decouple_PN_calc(DECOUPLE *v)
{  
   float cos_ang,sin_ang,double_angle;   
   
   double_angle = 2*v->angle;

   if(double_angle>=6.28)
	  double_angle = double_angle - 6.28;

   sin_ang = sin(double_angle);
   cos_ang = cos(double_angle);
/*
   v->de_p_out = v->de_p_in - _IQmpy(v->de_n_out,cos_ang) - _IQmpy(v->qe_n_out,sin_ang);
   v->qe_p_out = v->qe_p_in + _IQmpy(v->de_n_out,sin_ang) - _IQmpy(v->qe_n_out,cos_ang);
   
   v->de_n_out = v->de_n_in - _IQmpy(v->de_p_out,cos_ang) + _IQmpy(v->qe_p_out,sin_ang);
   v->qe_n_out = v->qe_n_in - _IQmpy(v->de_p_out,sin_ang) - _IQmpy(v->qe_p_out,cos_ang);

*/

   v->de_p_out = v->de_p_in - v->de_n_out_Filter*cos_ang - v->qe_n_out_Filter*sin_ang;
   v->qe_p_out = v->qe_p_in + v->de_n_out_Filter*sin_ang - v->qe_n_out_Filter*cos_ang;
   
   v->de_n_out = v->de_n_in - v->de_p_out_Filter*cos_ang + v->qe_p_out_Filter*sin_ang;
   v->qe_n_out = v->qe_n_in - v->de_p_out_Filter*sin_ang - v->qe_p_out_Filter*cos_ang;

   v->de_p_out_Filter = v->de_p_out_Filter_old*v->k1 + v->de_p_out_old*v->k2 + v->de_p_out*v->k2;
   v->de_p_out_old = v->de_p_out;
   v->de_p_out_Filter_old = v->de_p_out_Filter;

   v->qe_p_out_Filter = v->qe_p_out_Filter_old*v->k1 + v->qe_p_out_old*v->k2 + v->qe_p_out*v->k2;
   v->qe_p_out_old = v->qe_p_out;
   v->qe_p_out_Filter_old = v->qe_p_out_Filter;

   v->de_n_out_Filter = v->de_n_out_Filter_old*v->k1 + v->de_n_out_old*v->k2 + v->de_n_out*v->k2;
   v->de_n_out_old = v->de_n_out;
   v->de_n_out_Filter_old = v->de_n_out_Filter;
   
   v->qe_n_out_Filter = v->qe_n_out_Filter_old*v->k1 + v->qe_n_out_old*v->k2 + v->qe_n_out*v->k2;
   v->qe_n_out_old = v->qe_n_out;
   v->qe_n_out_Filter_old = v->qe_n_out_Filter;
}

