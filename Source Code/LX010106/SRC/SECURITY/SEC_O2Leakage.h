/******************************************************************************/
/*                                                                            */
/* Project N°  :  RA0306                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_O2Leakage.h                                   	  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C            Management of the alarm 02 leakage                */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef SEC_O2LEAKAGE_H
#define SEC_O2LEAKAGE_H


/************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION	                     */
/************************************************************************/

extern UWORD16 DB_ComputeRead(e_DB_COMPUTE Id);
extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
extern UWORD16 DB_AlarmStatusRead(e_DB_ALARMS Id);
extern void DB_EventMngt (UWORD16 Value);
extern void DB_AlarmStatusWrite(e_DB_ALARMS Id
							  , e_DB_ALARMS_STATE Value); 
extern void TIM_StartDecounter(e_TIM_TABLE_ID offset_table,
                               UWORD16 value);	
extern UWORD16 TIM_ReadDecounterValue(e_TIM_TABLE_ID offset_table);
#endif
