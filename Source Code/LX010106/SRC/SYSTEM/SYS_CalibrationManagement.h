/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_CalibrationManagement.h                                    */
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

#ifndef SYS_CALIBRATIONMANAGEMENT_H	
#define SYS_CALIBRATIONMANAGEMENT_H

/************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION	                     */
/************************************************************************/
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
extern void DB_ControlWrite(e_DB_CONTROL Id, UWORD16 Value);
extern void SYS_ExhFlowCalibration(UWORD16 Request,
											  t_SYS_CalibrationParameters CP);
extern void SYS_Fio2Calibration(UWORD16 RequestType,
											  t_SYS_CalibrationParameters CP,
											   UWORD16 CAN_Digit1);

#endif