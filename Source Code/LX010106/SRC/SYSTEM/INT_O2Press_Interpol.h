/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : INT_O2Press_Interpol.h                                        */
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

#ifndef INT_O2PRESS_INTERPOL_H
#define INT_O2PRESS_INTERPOL_H


/************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION	                     */
/************************************************************************/
/* Sensitivity of the valve pressure sensor       */
#define SENSITIVITY_SENSOR_PRESSURE_O2	8800				

extern void DB_ComputeWrite(e_DB_COMPUTE Id,
                            UWORD16 Value);
extern void DB_MeasurementWrite(e_DB_MEASUREMENT Id,
                                UWORD16 Value);
extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);
#endif