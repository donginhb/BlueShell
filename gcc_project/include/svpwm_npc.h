/* =================================================================================
File name:       svpwm_npc.h  (float version)                    
                    
Originator:	 Converter Control Group--XAXJ

Description: 
Header file containing constants, data type definitions, and 
function prototypes for the svpwm_npc.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 2014-9-28		Release	Rev 1.0                                                   
------------------------------------------------------------------------------*/
#ifndef SVPWM_NPC_H
#define SVPWM_NPC_H
 
typedef struct 	{ float  Ualfa; 			/* Input: reference alfa-axis phase voltage   */
				  float  Ubeta;			/* Input: reference beta-axis phase voltage   */
				  float  Uzero; 
				  float  Unp;
				  float  U0;
				  float  Ia;
				  float  Ib;
				  float  Ic;
				  float  Ta1;				/* Output: reference phase-a switching function  */			
				  float  Tb1;				/* Output: reference phase-b switching function   */
				  float  Tc1;				/* Output: reference phase-c switching function   */
				  float  Ta2;
				  float  Tb2;
				  float  Tc2;
				  float  Tmax;				
				  float  Tmin;
				  void   (*calc)();	    /* Pointer to calculation function */ 
				} SVPWMNPC;
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																				
typedef SVPWMNPC *SVPWMNPC_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the SVPWMNPC object.
-----------------------------------------------------------------------------*/                     
#define SVPWMNPC_DEFAULTS { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.99,-0.99,\
                       (void (*)(long))svpwmnpc_calc }

#define MAX(X,A,B,C) \
(X)=(A);\
if((X)<(B))\
(X)=(B);\
if((X)<(C))\
(X)=(C);

#define MIN(X,A,B,C) \
(X)=(A);\
if((X)>(B))\
(X)=(B);\
if((X)>(C))\
(X)=(C);

#define POSI(X,A) \
if((A)>=0)\
(X)=(A);\
else\
(X)=1.0+(A);

#define SATURATE(X,LOW,UP) if((X)>(UP))(X)=(UP);else if((X)<(LOW))(X)=(LOW)

/*------------------------------------------------------------------------------
Prototypes for the functions in SVPWM_NPC.C
------------------------------------------------------------------------------*/
void svpwmnpc_calc(SVPWMNPC_handle);


#endif /* SVPWM_NPC_H */
