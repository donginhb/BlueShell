#ifndef Insulation_F_H_
#define Insulation_F_H_

//*********** Structure Definition ********//
/* =================================================================================
File name:       Insulation_F.H  (IQ version)                  
                    

=====================================================================================
 History:
-------------------------------------------------------------------------------------
 05-15-2008		Release	Rev 1.0                                                   
------------------------------------------------------------------------------*/

typedef struct {  float  U1;   	/* Input: Reference input  */
				  float  U2;   	/* Input: Feedback input  */
				  float  U3;			/* Variable: Error    */
				  float  Upv1;			/* Parameter: Proportional gain  */
				  float  Upv2;			/* Variable: Proportional output  */
				  float  R1;
				  float  R2;
				  float  R;
				  float  R_yuzhi;
				 }Insulation;	            


/*-----------------------------------------------------------------------------
Default initalizer for the Insulation object.
-----------------------------------------------------------------------------*/                     
#define Insulation_DEFAULTS { 0, \
                           0, \
                           0, \
                           0, \
						   0, \
						   0, \
                           0, \
						   0, \
						   0.66, \
              			        }
/*------------------------------------------------------------------------------
Prototypes for the functions in Insulation_F.C
------------------------------------------------------------------------------*/
void Insulation_F_FUNC(Insulation *V);

#endif /*Insulation_F_H_*/
