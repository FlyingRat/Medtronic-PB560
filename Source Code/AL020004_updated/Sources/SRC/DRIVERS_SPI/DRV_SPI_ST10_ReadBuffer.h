/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_SPI_ST10_ReadBuffer.h           					            */
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


#ifndef DRV_SPI_ST10_READBUFFER_H
#define DRV_SPI_ST10_READBUFFER_H

/******************************************************************************/
/*		                EXTERNAL FUNCTION DECLARATION 						  			*/
/******************************************************************************/

extern void DB_PowerSupply_Write(e_DB_POWERSUPPLY Id, UWORD16 Value);
extern UWORD16 DB_PowerSupply_Read(e_DB_POWERSUPPLY Id);

extern void TIM_StartDecounter16(e_TIM_TABLE_ID_16,UWORD16);
extern UWORD16 TIM_ReadValue16(e_TIM_TABLE_ID_16);


#endif
