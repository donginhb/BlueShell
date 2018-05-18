#include "Solar_F.h"

//*********** Structure Init Function ****//
void PARKPN_F_init(PARKPN_F *v)
{
	v->alpha=0;
	v->beta=0;
	v->zero=0;
	v->d_p=0;
	v->q_p=0;
	v->z_p=0;
	v->d_n=0;
	v->q_n=0;
	v->z_n=0;
}

//*********** Function Definition ********//
void PARKPN_F_FUNC(PARKPN_F *v)
{
	v->d_p= v->alpha*v->sin - v->beta*v->cos;
	v->q_p= v->alpha*v->cos + v->beta*v->sin;
	v->z_p= v->zero;
	
	v->d_n= -v->alpha*v->sin - v->beta*v->cos;
	v->q_n= v->alpha*v->cos - v->beta*v->sin;
	v->z_n= v->zero;
}
