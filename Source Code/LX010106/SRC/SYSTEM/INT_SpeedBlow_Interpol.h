/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : INT_SpeedBlow_Interpol.h                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Blower Speed value conversion                                  */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef INT_SPEED_BLOWER_DRIVER_H
#define INT_SPEED_BLOWER_DRIVER_H


/******************************************************************************/
/*                   EXTERNAL FUNCTION  DEFINITIONS                           */
/******************************************************************************/

extern void DRV_SPEED_LaunchingSpeedBlowerMeasure(void);
extern void DB_ComputeWrite(e_DB_COMPUTE Id,
                            UWORD16 Value);
extern void TIM_StartDecounter(e_TIM_TABLE_ID offset_table,
                               UWORD16 value);

extern UWORD16 TIM_ReadCounterValue(e_TIM_TABLE_ID 
                                    offset_table);
 
#endif