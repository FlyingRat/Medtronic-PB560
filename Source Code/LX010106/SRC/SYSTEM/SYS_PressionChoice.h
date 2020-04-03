/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_PressionChoice.h                                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C  Choice between internal pressure sensor and proximal pressure sensor	*/
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


#ifndef SYS_PRESSIONCHOICE_H
#define SYS_PRESSIONCHOICE_H

/******************************************************************************/
/*                    CONSTANT DECLARATION                     	            */
/******************************************************************************/

#define  cPRESSURE_CHOICE_LEVEL1 4
#define cPRESSURE_PROX_LEAK_CHOICE_LEVEL 20	

/******************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION	                          */
/******************************************************************************/
extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);
extern UWORD16 DB_ComputeRead(e_DB_COMPUTE Id);
extern void DB_ComputeWrite(e_DB_COMPUTE Id,
                            UWORD16 Value);
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
extern void DB_ControlWrite(e_DB_CONTROL Id,
                            UWORD16 Value);
extern void TIM_StartDecounter(e_TIM_TABLE_ID offset_table,
                               UWORD16 value);	
extern UWORD16 TIM_ReadDecounterValue(e_TIM_TABLE_ID offset_table);

extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);
extern UWORD16 DB_CurrentRead(e_DB_ADJUST_CURRENT Id);

#endif
