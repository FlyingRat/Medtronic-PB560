/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : INT_ValvePress_Interpol.h                                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Valve pressure values conversion                               */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


#ifndef INT_VALVE_PRESS_INTERPOL_H
#define INT_VALVE_PRESS_INTERPOL_H


/******************************************************************************/
/*                    CONSTANT DECLARATION                                    */
/******************************************************************************/
  
/* Sensitivity of the valve pressure sensor       */
#define SENSITIVITY_SENSOR_PRESSURE_VALVE	1343	/* 10^-4 cmH2O*/					


/******************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION	                           */
/******************************************************************************/
extern void DB_ComputeWrite(e_DB_COMPUTE Id,
                            UWORD16 Value);
extern void DB_MeasurementWrite(e_DB_MEASUREMENT Id,
                                UWORD16 Value);
extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);
#endif
  