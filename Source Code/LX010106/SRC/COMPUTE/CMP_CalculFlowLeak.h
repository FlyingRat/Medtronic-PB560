/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CMP_CalculFlowLeak.h                                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   Data declaration for CMP_CalculFlowLeak.c                              */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

#ifndef CMP_CALCUL_FLOW_LEAK_H
#define CMP_CALCUL_FLOW_LEAK_H


/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/


/*Integral max value (*10) for the valve                                      */
#define cVEN_COMMAND_QLEAK_MAX  	26700UL 	

/*Integral min value (*10) for the valve                                      */
#define  cVEN_COMMAND_QLEAK_MIN  5000UL 	

#define  cVEN_COMMAND_VALVE_MIN  1000UL 	
 
/******************************************************************************/
/*             EXTERNAL FUNCTION DECLARATION                    	            */
/******************************************************************************/

extern SWORD32 VEN_RiseCompute(SWORD32 x,
                              SWORD32 x1,
                              SWORD32 y1,
                              SWORD32 x2,
                              SWORD32 y2);


extern UWORD16 DB_AlarmStatusRead(e_DB_ALARMS Id);

extern UWORD16 DB_ComputeRead(e_DB_COMPUTE Id);

extern void DB_ComputeWrite(e_DB_COMPUTE Id, 
							UWORD16 Value);

extern UWORD16 DB_CurrentRead(e_DB_ADJUST_CURRENT Id);

extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);

extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);

extern SWORD32 saturation(SWORD32 Value,
                          SWORD32 Min,
                          SWORD32 Max); 

extern UWORD16 TIM_ReadCounterValue(e_TIM_TABLE_ID 
                                    offset_table);

#endif
 