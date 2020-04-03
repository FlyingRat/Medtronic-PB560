/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CMP_O2Consigne.h	   											  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C            									                          				*/
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef CMP_O2CONSIGNE_H
#define CMP_O2CONSIGNE_H


/************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION	                     */
/************************************************************************/

	extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);
	extern UWORD16 DB_ConfigWrite(e_DB_CONFIG Id,UWORD16 Value);
	extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
	extern UWORD16 DB_ComputeRead(e_DB_COMPUTE Id);
	extern UWORD16 DB_CurrentRead(e_DB_ADJUST_CURRENT Id);
	extern SWORD32 VEN_RiseCompute(SWORD32 x,
										SWORD32 x1,
										SWORD32 y1,
										SWORD32 x2,
										SWORD32 y2);

#endif
