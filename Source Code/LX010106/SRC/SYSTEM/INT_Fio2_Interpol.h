/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : INT_Fio2_Interpol.h  	                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Fio2 interpol decaration data			                           */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef INT_FIO2_INTERPOL_H
#define INT_FIO2_INTERPOL_H

/************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION	                     */
/************************************************************************/
extern void DB_ComputeWrite(e_DB_COMPUTE Id, UWORD16 Value);
extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);
extern UWORD16 DB_ComputeRead(e_DB_COMPUTE Id);
extern SWORD32 VEN_RiseCompute(SWORD32 x,
                              SWORD32 x1,
                              SWORD32 y1,
                              SWORD32 x2,
                              SWORD32 y2);

extern void DB_ComputeWrite(e_DB_COMPUTE Id, 
							UWORD16 Value);			  
#endif