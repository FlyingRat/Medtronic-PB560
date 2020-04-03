/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : INTERRUPT_COM_Receive.c 													*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                  																			*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                            		*/
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE       															*/
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
#ifndef _TASKING
#include "LH_ST10F276.h"
#else
#include "regf276e.h"
#endif	 
#include "typedef.h"
#include "DRV_COM_Data.h"
					 
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

#ifndef _TASKING
 void INTERRUPT_COM_Receive(void) interrupt (0x2B)
#else
interrupt (0x2B)
 void INTERRUPT_COM_Receive(void)
#endif	 
	{ 
	UWORD16 Received_Data;
   	

  	Received_Data = S0RBUF;

	//masquage de la partie haute du buffer de reception
	Received_Data &= 0x00FF;
   DRV_COM_Buffer_Of_Receipt[DRV_COM_Ptr_Write_Buffer_Rx] = (UBYTE)Received_Data;
	DRV_COM_Ptr_Write_Buffer_Rx = DRV_COM_Ptr_Write_Buffer_Rx + 1;
	DRV_COM_Ptr_Write_Buffer_Rx %= COM_RX_BufferSize;
	 }
  