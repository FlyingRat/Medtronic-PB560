/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SET_CalibrationManagement.h                                    */
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

#ifndef SET_CALIBRATIONMANAGEMENT_H	
#define SET_CALIBRATIONMANAGEMENT_H

/************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION	                     */
/************************************************************************/
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
extern void DB_ControlWrite(e_DB_CONTROL Id, UWORD16 Value);
extern UWORD16 DB_AlarmStatusRead(e_DB_ALARMS Id);
extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);
extern void SET_CalibrationVerification(UWORD16 RequestType,
													 t_SYS_CalibrationParameters CP);
extern void SET_DefaultCalibration(UWORD16 RequestType,
												 t_SYS_CalibrationParameters CP,
												 UWORD16 CAN_Digit1,
												 UWORD16 CAN_Digit2,
												 UWORD16 CAN_Digit3);
extern void SET_ExhFlowCalibration(UWORD16 RequestType,
											  t_SYS_CalibrationParameters CP);
 extern void SET_FasValveCalibration(UWORD16 RequestType);
#endif