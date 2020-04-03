/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505 				                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_USB_ReadFifo.h 																*/
/*																										*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C         																						*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef DRV_USB_READFIFO_H
#define DRV_USB_READFIFO_H


/******************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION	                    			*/
/******************************************************************************/

	/*%C Usb Acces to DataBase */
	extern void DB_UsbWrite(e_DB_USB Id, UWORD16 Value);
	extern UWORD16 DB_UsbRead(e_DB_USB Id);
	
	extern void TIM_StartDecounter(e_TIM_TABLE_ID offset_table , UWORD16 value);	
	extern UWORD16 TIM_ReadDecounterValue(e_TIM_TABLE_ID offset_table);


 #endif
