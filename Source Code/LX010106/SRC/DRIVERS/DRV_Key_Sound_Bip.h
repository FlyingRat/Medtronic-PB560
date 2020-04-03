/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_Key_Sound_Bip.h                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Data declaration for  DRV_Key_Sound_Bip.c                                */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE                                                  */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef DRV_KEY_SOUND_H
#define DRV_KEY_SOUND_H

/******************************************************************************/
/*           EXTERNAL FUNCTION DECLARATION        	                        	*/
/******************************************************************************/
/* Access to the config read function */
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);

/* Access to the config write function */
extern void DB_ControlWrite(e_DB_CONTROL Id, UWORD16 Value);

/* Access to the decounter start function */
extern void TIM_StartDecounter(e_TIM_TABLE_ID offset_table,
                               UWORD16 value);

/* Access to the decounter read function */
extern UWORD16 TIM_ReadDecounterValue(e_TIM_TABLE_ID offset_table);

extern void DRV_Key_Sound_Cloc(void);

extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);

extern void DRV_Buz_Sound(e_TYPE_SOUND sound,
                   		  e_NUMBER_BUZ NumBuzzer);

#endif

