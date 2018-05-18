#include "Solar_F.h"

//*********** Structure Init Function ****//
void MPPT_PNO_F_init(MPPT_PNO_F *v)
{
	v->Ipv=0;
	v->Vpv=0;
	v->DeltaPmin=(0.0);
	v->MaxVolt=(0.8);
	v->MinVolt=0;
	v->Stepsize=(0.002);
	v->VmppOut=0;
	v->DeltaP=0;
	v->PanelPower=0;
	v->PanelPower_Prev=0;
	v->mppt_enable=1;
	v->mppt_first=1;
}

//*********** Function Definition ********//
void MPPT_PNO_F_FUNC(MPPT_PNO_F *v)
{
	if (v->mppt_enable==1)
		{
			if (v->mppt_first == 1)
			{
				v->VmppOut= v->Vpv - v->Stepsize;
				v->mppt_first=0;
				v->PanelPower_Prev=(v->Vpv*v->Ipv); //v->PanelPower;
			}
			else
			{
				v->PanelPower=(v->Vpv*v->Ipv);
				v->DeltaP=v->PanelPower-v->PanelPower_Prev;
				if (v->DeltaP > v->DeltaPmin)
				{
					v->VmppOut=v->Vpv - v->Stepsize;
				}
				else
				{
					if (v->DeltaP < -v->DeltaPmin)
					{
						v->VmppOut=v->Vpv + v->Stepsize;
					}
				}
				v->PanelPower_Prev = v->PanelPower;
			}
			if(v->VmppOut < v->MinVolt) v->VmppOut = v->MinVolt;
			if(v->VmppOut > v->MaxVolt) v->VmppOut = v->MaxVolt;
		}
}
