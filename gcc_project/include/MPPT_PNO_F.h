#ifndef MPPT_PNO_F_H_
#define MPPT_PNO_F_H_

//*********** Structure Definition ********//
/* =================================================================================
File name:       MPPT.H  (IQ version)                  
                    

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 05-15-2008		Release	Rev 1.0                                                   
------------------------------------------------------------------------------*/

typedef struct {  float  pv_v;  		/* 光伏阵列端电压  */
                  float  pv_v1;  		/* 光伏阵列前一时刻端电压  */
				  float  pv_i;			/* 光伏阵列输出电流  */
				  float  pv_i1;			//输出电流平均值，判断高于Voc
				  float  pv_p;			/* 当前时刻光伏阵列输出功率  */
				  float  pv_p1;			/* 前一时刻光伏阵列输出功率  */
				  float  deltu;         /* 电压调整方向  */
				 } MPPT;	            

/*-----------------------------------------------------------------------------
Default initalizer for the MPPT object.
-----------------------------------------------------------------------------*/                     
#define MPPT_DEFAULTS { 0, \
                          0, \
                          0, \
                          0, \
                          0,\
						  0,\
						  0,\
 }

/*------------------------------------------------------------------------------
Prototypes for the functions in MPPT.C
------------------------------------------------------------------------------*/
void MPPT_PNO_F_FUNC(MPPT *v);



/*
typedef struct {
	float32  Ipv;
	float32  Vpv;
	float32  DeltaPmin;
	float32  MaxVolt;
	float32  MinVolt;
	float32  Stepsize;
	float32  VmppOut;
	float32  DeltaP;
	float32  PanelPower;
	float32  PanelPower_Prev;
	int16 mppt_enable;
	int16 mppt_first;
} MPPT_PNO_F;

typedef MPPT_PNO_F *mppt_pno_handle;*/

//*********** Function Declarations *******//
//void MPPT_PNO_F_init(MPPT_PNO_F *v);
//void MPPT_PNO_F_FUNC(MPPT_PNO_F *v);

//*********** Macro Definition ***********//
/*#define MPPT_PNO_F_MACRO(v)												\
if (v.mppt_enable==1)													\
{																		\
	if (v.mppt_first == 1)												\
	{																	\
		v.VmppOut= v.Vpv - (0.02);										\
		v.mppt_first=0;													\
		v.PanelPower_Prev=v.PanelPower;									\
	}																	\
	else																\
	{																	\
		v.PanelPower= (v.Vpv*v.Ipv);									\
		v.DeltaP=v.PanelPower-v.PanelPower_Prev;						\
		if (v.DeltaP > v.DeltaPmin)										\
		{																\
			v.VmppOut=v.Vpv+v.Stepsize;									\
		}																\
		else															\
		{																\
			if (v.DeltaP < -v.DeltaPmin)								\
			{															\
				v.Stepsize=-v.Stepsize;									\
				v.VmppOut=v.Vpv+v.Stepsize;								\
			}															\
		}																\
		v.PanelPower_Prev = v.PanelPower;								\
	}																	\
	if(v.VmppOut< v.MinVolt) v.VmppOut = v.MinVolt;						\
	if(v.VmppOut> v.MaxVolt) v.VmppOut= v.MaxVolt;						\
}	
*/

#endif /*MPPT_PNO_F_H_*/
