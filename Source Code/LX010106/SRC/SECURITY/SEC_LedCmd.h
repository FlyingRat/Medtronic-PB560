/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_LedCmd.h                                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C  Data declaration for SEC_LedCmd.c                                       */
/*                                                                            */
/******************************************************************************/
/*%I  Input Parameter :   NONE                                                */
/*%IO Input/Output :      NONE                                                */
/*%O  Output Parameter :  NONE                                                */
/******************************************************************************/

#ifndef SEC_LED_CMD_H
#define SEC_LED_CMD_H

/******************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION                            */
/******************************************************************************/


/* Access to the orange and red leds driver */

extern void DRV_Led_Red(e_TYPE_BLINK Blink);

extern void DRV_Led_Orange(e_TYPE_BLINK Blink);

/* Access to the reading decounter function */
extern UWORD16 TIM_ReadDecounterValue(e_TIM_TABLE_ID offset_table);

extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);

#endif
