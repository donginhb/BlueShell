#ifndef PARKPN_F_H
#define PARKPN_F_H

//*********** Structure Definition ********//
typedef struct{
	float32 alpha;
	float32 beta;
	float32 zero;
	float32 sin;
	float32 cos;
	float32 d_p;
	float32 q_p;
	float32 z_p;
	float32 d_n;
	float32 q_n;
	float32 z_n;
}PARKPN_F;

//*********** Function Declarations *******//
void PARKPN_F_init(PARKPN_F *v);
void PARKPN_F_FUNC(PARKPN_F *v);

//*********** Macro Definition ***********//
#define PARKPN_F_MACRO(v) 				\
	v.d_p= v.alpha*v.sin - v.beta*v.cos;	\
	v.q_p= v.alpha*v.cos + v.beta*v.sin;	\
	v.z_p= v.zero;                            \
	v.d_n= -v.alpha*v.sin - v.beta*v.cos;	\
	v.q_n= v.alpha*v.cos - v.beta*v.sin;	\
	v.z_n= v.zero;

#endif /* PARKPN_F_H_ */
