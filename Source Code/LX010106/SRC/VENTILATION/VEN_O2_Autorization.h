/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : VEN_O2_Autorization.h  									  					*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                  */
/******************************************************************************/
/*%I Input Parameter :  NONE                                            */
/*%IO Input/Output :    NONE	                                              */
/*%O Output Parameter : NONE       */
/******************************************************************************/


#ifndef VEN_O2_AUTORIZATION_H 
#define VEN_O2_AUTORIZATION_H

/******************************************************************************/
/*                     EXTERNAL FUNCTION DECLARATION                          */
/******************************************************************************/


extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);

extern void DB_ControlWrite(e_DB_CONTROL Id,UWORD16 Value);

extern void DB_AlarmStatusWrite(e_DB_ALARMS Id, e_DB_ALARMS_STATE Value);
extern UWORD16 DB_AlarmStatusRead(e_DB_ALARMS Id);

extern void TIM_StartDecounter(e_TIM_TABLE_ID offset_table,
                               UWORD16 value);	
extern UWORD16 TIM_ReadDecounterValue(e_TIM_TABLE_ID offset_table);


#endif