/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_RS232_ReadBuffer.h           					              	*/
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


#ifndef DRV_RS232_READBUFFER_H
#define DRV_RS232_READBUFFER_H

/******************************************************************************/
/*		                EXTERNAL FUNCTION DECLARATION 						  			*/	
/******************************************************************************/

extern void TIM_StartDecounter32(e_TIM_TABLE_ID_32 offset_table,UWORD32 value);
extern void SAM_PWM_Conversion( UBYTE PWMValue,e_SAM_PWM PWMControlType);
extern void DB_Control_Write(e_DB_Control Id, UWORD16 Value);
extern UWORD16 DB_Control_Read(e_DB_Control Id);
extern UWORD16 DB_PowerSupply_Read(e_DB_POWERSUPPLY Id);

#endif
