/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505																		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_USB_WriteFifo.c 																*/
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



/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/

#ifndef _TASKING
	#include "LH_ST10F276.h"
	#include <intrins.h>
#else	    
 		#include "regf276e.h"
#endif 	
#include "io_declare.h"
#include "enum.h"
#include "define.h"
#include "typedef.h"
#include "DB_Usb.h"
#include "Driver_USB_Data.h"
#include "DRV_USB_WriteFifo.h"

/******************************************************************************/
/*                             #DEFINE		                        				*/
/******************************************************************************/


/******************************************************************************/
/*                   			FUNCTION BODY                    					*/
/******************************************************************************/

void DRV_USB_WriteFifo(void)
{

	UWORD16 UsbErrorCodeReady = DB_UsbRead(USB_ERROR_CODE_READY_U16);
	
	if(UsbErrorCodeReady == FLAG_ERROR_CODE_READY)
	{
		/*Positionne le code d'erreur dans la pile*/
		FifoErrorCodeToIHM[UsbPtrWriteFifoErrorCodeToIHM] = (UBYTE)DB_UsbRead(USB_ERROR_CODE_U16);
		/*Incrémente le pointeur de pile*/
		UsbPtrWriteFifoErrorCodeToIHM ++ ;
		UsbPtrWriteFifoErrorCodeToIHM = (UBYTE)(UsbPtrWriteFifoErrorCodeToIHM % FIFO_ERROR_CODE_TO_IHM_SIZE);
		/*Permet de détecter le prochain code d'erreur*/
		DB_UsbWrite(USB_ERROR_CODE_READY_U16, FLAG_ERROR_CODE_NOT_READY);
	}
	else
	{
		/*%C No function */
	}	

}
