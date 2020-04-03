/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CMP_InspRiseComputings.h                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   Data declaration for CMP_InspRiseComputings.c                          */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

#ifndef CMP_INSP_RISE_COMPUTINGS_H
#define CMP_INSP_RISE_COMPUTINGS_H


/******************************************************************************/
/*             EXTERNAL FUNCTION DECLARATION                    	            */
/******************************************************************************/

extern UWORD16 DB_CurrentRead(e_DB_ADJUST_CURRENT Id);

extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);

extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);

extern UWORD16 TIM_ReadCounterValue(e_TIM_TABLE_ID offset_table);

extern void DB_ComputeWrite(e_DB_COMPUTE Id,
                            UWORD16 Value);

extern UWORD16 CMP_TargetVt(void);

extern SWORD32 VEN_RiseCompute(SWORD32 x,
                              SWORD32 x1,
                              SWORD32 y1,
                              SWORD32 x2,
                              SWORD32 y2);

extern UWORD16 DB_ComputeRead(e_DB_COMPUTE Id);

#endif
 