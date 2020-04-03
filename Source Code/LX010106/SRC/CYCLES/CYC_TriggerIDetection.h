/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CYC_TriggerIDetection.h                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                Detection of the Inspiration trigger                		*/ 
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter :  NONE                                            		*/
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : UWORD16  TriggerIDetected      								*/
/******************************************************************************/


 
#ifndef CYC_TRIGGERIDETECTION_H
#define CYC_TRIGGERIDETECTION_H

/******************************************************************************/
/*                       CONSTANT DECLARATION                      	  			*/
/******************************************************************************/
#define cTIME_TRIG_I_MIN 1100U
#define cTIME_TRIG_I_MAX 2000U
#define cTIME_TRIG_I_MIN_PED 700U
#define cTIME_TRIG_I_MAX_PED 1100U
#define cCPAP_TRIGGERI_VALUE 5U
#define cDELTA_PEEP 2U

/******************************************************************************/
/*                      EXTERNAL FUNCTION DECLARATION	                      	*/
/******************************************************************************/
extern UWORD16 TIM_ReadCounterValue(e_TIM_TABLE_ID);
extern UWORD16 DB_ComputeRead(e_DB_COMPUTE Id);
extern UWORD16 DB_CurrentRead(e_DB_ADJUST_CURRENT Id);
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
extern SWORD32 VEN_RiseCompute(SWORD32 x,
										SWORD32 x1,
										SWORD32 y1,
										SWORD32 x2,
										SWORD32 y2);
extern UWORD16 TIM_ReadDecounterValue(e_TIM_TABLE_ID offset_table);
#endif

