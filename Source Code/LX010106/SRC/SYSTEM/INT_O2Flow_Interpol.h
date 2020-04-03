/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : INT_O2Flow_Interpol.h                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Inspiration Flow  values conversion                            */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef INT_O2FLOW_INTERPOL_H
#define INT_O2FLOW_INTERPOL_H

/************************************************************************/
/*                   	CONSTANT DECLARATION			                     */
/************************************************************************/
#define cP0 1013

/************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION	                     */
/************************************************************************/
extern void DB_ComputeWrite(e_DB_COMPUTE Id, UWORD16 Value);
extern void DB_MeasurementWrite(e_DB_MEASUREMENT Id, UWORD16 Value);
extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);
extern UWORD16 DB_ComputeRead(e_DB_COMPUTE Id);
extern SWORD16 INT_Flow_Conversion_Equation(SWORD16 DigitFlow,
                                            SWORD16 OffsetFlow1,
                                            SWORD16 OffsetFlow2,
                                            UWORD16 CalibFlowPoint1,
                                            UWORD16 CalibFlowPoint2);

extern SWORD32 saturation(SWORD32 Value,
                          SWORD32 Min,
                          SWORD32 Max); 
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);


#endif