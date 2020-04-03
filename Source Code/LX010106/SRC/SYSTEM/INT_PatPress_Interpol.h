/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : INT_PatPress_Interpol.h                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Internal pressure values conversion                            */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef INT_PATPRESS_INTERPOL_H
#define INT_PATPRESS_INTERPOL_H


/************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION	                     */
/************************************************************************/
extern void DB_ComputeWrite(e_DB_COMPUTE Id,
                            UWORD16 Value);
extern void DB_MeasurementWrite(e_DB_MEASUREMENT Id, 
                                UWORD16 Value);
extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);
#endif