

#include "Solar_F.h"

void Insulation_F_FUNC(Insulation *v)
{	
   float a;
   float b;
   float c;
//   _iq V;
//   _iq R_a;
//   _iq R_b;

/*   	a= _IQdiv((v->Upv1 - v->U2),v->U2);
	b= _IQdiv((v->Upv1 - v->U1),v->U1);
	c= _IQdiv(_IQ(1.0),b);*/
	a= (v->Upv1 - v->U2)/v->U2;
	b= (v->Upv1 - v->U1)/v->U1;
	c= 1.0/b;
//	V= _IQmpy(v->Upv1,v->Upv2);
//	R_a= _IQmpy(V,a);
//	R_b=V-_IQmpy(v->U3,v->Upv2)-_IQmpy(v->U2,v->Upv1);
	v->R1 = a-b;//_IQdiv(_IQmpy(v->Upv1,a),v->U3);
//	v->R2=_IQdiv(_IQmpy(v->Upv2,a),v->U2);
	v->R = c * v->R1;//_IQdiv(a,(_IQ(1.0)-_IQdiv(v->U3,v->Upv1)-_IQdiv(v->U2,v->Upv2)));    
}


