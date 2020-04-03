/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_LeakDisconnection.h                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C            									                                    */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef SEC_LEAKDISCONNECTION_H
#define SEC_LEAKDISCONNECTION_H

/************************************************************************/
/*                    CONSTANT DECLARATION                     	      */
/************************************************************************/
#define cFIVE_SEC 5000
#define cQMAXLEAKDISCONNECTION_600 600
#define cQMAXLEAKDISCONNECTION_1300 1300
#define cQMINVTIDISCONNECTION 20
#define cMININSPDELAY 240U
	

/************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION	                     */
/************************************************************************/
extern UWORD16	DB_ComputeRead(e_DB_COMPUTE Id);
extern UWORD16 DB_AlarmStatusRead(e_DB_ALARMS Id);
extern UWORD16 DB_CurrentRead(e_DB_ADJUST_CURRENT Id);

extern void DB_AlarmStatusWrite(e_DB_ALARMS Id, 
								e_DB_ALARMS_STATE Value);
extern void DB_EventMngt (UWORD16 Value);
extern void TIM_StartDecounter(e_TIM_TABLE_ID offset_table,
                               UWORD16 value);
extern UWORD16 TIM_ReadDecounterValue(e_TIM_TABLE_ID offset_table);
extern UWORD16 TIM_ReadCounterValue(e_TIM_TABLE_ID offset_table);
#endif