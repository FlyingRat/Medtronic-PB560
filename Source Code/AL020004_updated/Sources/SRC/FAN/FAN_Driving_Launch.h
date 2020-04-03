/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  :FAN_Driving_Launch.h            					              	  	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C        			  										      		  					*/
/*%C          																  						*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef FAN_DRIVING_LAUNCH_H
#define FAN_DRIVING_LAUNCH_H

/******************************************************************************/
/*		                EXTERNAL FUNCTION DECLARATION 						  			*/
/******************************************************************************/

extern UWORD16 DB_PowerSupply_Read(e_DB_POWERSUPPLY Id);
extern UWORD16 DB_Measurement_Read(e_DB_Measurement Id);
extern UBYTE FAN_Loop_Controller(UWORD16 Setpoint, UWORD16 Measure);
extern UWORD16 DB_Control_Read(e_DB_Control Id);
extern void DB_Control_Write(e_DB_Control Id, UWORD16 Value);
extern void FAN_Sampling(void);

#endif
