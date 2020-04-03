/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CMP_LeakFactors.h                                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   Data declaration for CMP_LeakFactors.c   		              */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

#ifndef CMP_LEAKFACTORS_H
#define CMP_LEAKFACTORS_H


/******************************************************************************/
/*             EXTERNAL FUNCTION DECLARATION                    	      */
/******************************************************************************/
#define cPLATEAU_CHECK_SAMPLESIZE 	5
#define cMEANINGFUL_LEAK_STABILITY 	30
#define c4MM_LEAK_COEFF 			29

extern void DB_ComputeWrite(e_DB_COMPUTE Id,
                            UWORD16 Value);
extern void DB_ControlWrite(e_DB_CONTROL Id,
                            UWORD16 Value);

extern UWORD16 DB_ComputeRead(e_DB_COMPUTE Id);
extern UWORD16 DB_CurrentRead(e_DB_ADJUST_CURRENT Id);
extern UWORD16 TIM_ReadCounterValue(e_TIM_TABLE_ID offset_table);
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
extern SWORD32 VEN_RiseCompute(SWORD32 x,
                              SWORD32 x1,
                              SWORD32 y1,
                              SWORD32 x2,
                              SWORD32 y2);

extern SWORD32 CMP_MeanTable(SWORD16 Stop, UWORD16 Size, SWORD32 table[],UWORD16 TableLenght);

#endif
 