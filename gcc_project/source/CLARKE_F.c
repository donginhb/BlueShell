#include "Solar_F.h"
#include "CLARKE_F.h"

/* 1/sqrt(3) = 0.57735026918963 */
/* sqrt(2)/3 = 0.47140452791031 */
/* 2/3 = 0.66666666666667 */
#pragma CODE_SECTION(clarke_calc,"ramfuncs");
void clarke_calc(CLARKE *v)
{     
   
   v->ds = ((v->as - ((0.5) * v->bs) - ((0.5) * v->cs)) * (0.66666666666667));

   v->qs = ((0.57735026918963) * (v->bs - v->cs)); 
   
   v->os = ((0.33333333333) * (v->as + v->bs + v->cs));     
}

