/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CYC_Insp_Controller_Phase.h */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C          Generation of the type of control Phase and the type of */ 
/*            control.                                     */
/******************************************************************************/
/*%I Input Parameter :  NONE                                            */
/*%IO Input/Output :    NONE	                                              */
/*%O Output Parameter : NONE       */
/******************************************************************************/


#ifndef CYC_INSP_CONTROLLER_PHASE_H
#define CYC_INSP_CONTROLLER_PHASE_H

/******************************************************************************/
/*               				CONSTANT DECLARATION                              */
/******************************************************************************/
#define cVEN_SLOPE_LIMIT 200U
#define cDELTA_PI 99U
#define cRISE_TIME_PERCENT 33U
#define cRISE_TIME_LIMIT 150U
#define cDELTA_QINSP 90U
/******************************************************************************/
/*               	 EXTERNAL FUNCTION DECLARATION                              */
/******************************************************************************/
extern UWORD16 TIM_ReadCounterValue(e_TIM_TABLE_ID offset_table);
extern UWORD16 DB_CurrentRead(e_DB_ADJUST_CURRENT Id);
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
extern UWORD16 DB_ComputeRead(e_DB_COMPUTE Id);
extern void DB_ComputeWrite(e_DB_COMPUTE Id,
                            UWORD16 Value);

#endif

