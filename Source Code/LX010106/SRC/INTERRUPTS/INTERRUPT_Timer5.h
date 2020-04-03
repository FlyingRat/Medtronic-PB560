/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : INTERRUPT_Timer5.h */
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


#ifndef INTERRUPT_TIMER5_H
#define INTERRUPT_TIMER5_H

/******************************************************************************/
/*                     EXTERNAL FUNCTION DECLARATION                          */
/******************************************************************************/
extern void DRV_PwmBuzzer(e_BOOL Active);
extern void DRV_PwmBuzzerInt(e_BOOL Active, UWORD16 DesiredLevel);

/* Access to the decounter function */
extern void TIM_StartDecounter(e_TIM_TABLE_ID offset_table,
                               UWORD16 value);
extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);
#endif