/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  :DRV_RS232_Launch.h            					              			*/
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


#ifndef DRV_RS232_LAUNCH_H
#define DRV_RS232_LAUNCH_H

/******************************************************************************/
/*		                EXTERNAL FUNCTION DECLARATION 						  			*/	
/******************************************************************************/

extern void DRV_RS232_ReadBuffer(void);
extern void DRV_RS232_TransmitMonit(void);
extern void TIM_StartDecounter16(e_TIM_TABLE_ID_16,UWORD16);
extern void DB_Control_Write(e_DB_Control Id, UWORD16 Value);
extern UWORD16 DB_Control_Read(e_DB_Control Id);
extern UWORD16 TIM_ReadValue16(e_TIM_TABLE_ID_16);
extern UWORD32 TIM_ReadValue32(e_TIM_TABLE_ID_32);


#endif
