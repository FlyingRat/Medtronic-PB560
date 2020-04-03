/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CMP_ExhalationComputings.h                                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   Data declaration for CMP_ExhalationComputings.c                        */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                           CONSTANT DECLARATION                     	      */
/******************************************************************************/

#ifndef CMP_EXHALATION_COMPUTINGS_H
#define CMP_EXHALATION_COMPUTINGS_H


/******************************************************************************/
/*             EXTERNAL FUNCTION DECLARATION                    	            */
/******************************************************************************/

extern UWORD16 DB_CurrentRead(e_DB_ADJUST_CURRENT Id);

extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);

extern void DB_ControlWrite(e_DB_CONTROL Id, UWORD16 Value);


extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);

extern UWORD16 DB_ComputeRead(e_DB_COMPUTE Id);

extern void DB_ComputeWrite(e_DB_COMPUTE Id,
                               UWORD16 Value);

extern UWORD16 DB_AlarmStatusRead(e_DB_COMPUTE Id);

extern UWORD16 TIM_ReadCounterValue(e_TIM_TABLE_ID 
                                    offset_table);

extern SWORD32 saturation(SWORD32 Value,
                          SWORD32 Min,
                          SWORD32 Max); 
  

#endif
 