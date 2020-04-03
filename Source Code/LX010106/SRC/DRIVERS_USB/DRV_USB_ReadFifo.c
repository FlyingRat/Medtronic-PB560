/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505																		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_USB_ReadFifo.c 																*/
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
#include "Structure.h"
#include "Timer_Data.h"
#include "DB_Usb.h"
#include "Driver_USB_Data.h"
#include "DRV_USB_ReadFifo.h"

/******************************************************************************/
/*                             #DEFINE		                        				*/
/******************************************************************************/


/******************************************************************************/
/*                   			FUNCTION BODY                    					*/
/******************************************************************************/

void DRV_USB_ReadFifo(void)
{
	UWORD16 UsbErrorCodeReadyIhm = DB_UsbRead(USB_ERROR_CODE_READY_IHM_U16);
	
	/*Teste si le message precédent à été affiché et qu'il y a un message à afficher*/		
	if	(	(UsbErrorCodeReadyIhm == FLAG_ERROR_CODE_NOT_READY)
		&& 	(TIM_ReadDecounterValue(USB_WAIT_READ_FIFO) == 0)
		&& 	(UsbPtrReadFifoErrorCodeToIHM != UsbPtrWriteFifoErrorCodeToIHM))
	
	{
		/*Positionne le code d'erreur*/
		DB_UsbWrite(USB_ERROR_CODE_IHM_U16 , FifoErrorCodeToIHM[UsbPtrReadFifoErrorCodeToIHM]);	
#ifdef CONFIG_USB
		DB_UsbWrite(USB_ERROR_CODE_READY_IHM_U16 , FLAG_ERROR_CODE_READY);
#endif
		TIM_StartDecounter(USB_WAIT_READ_FIFO,TIME_USB_WAIT_READ_FIFO);
		/*Incrémente le pointeur de pile*/
		UsbPtrReadFifoErrorCodeToIHM ++ ;
		UsbPtrReadFifoErrorCodeToIHM = (UBYTE)(UsbPtrReadFifoErrorCodeToIHM % FIFO_ERROR_CODE_TO_IHM_SIZE);
	}
	else
	{
		/*%C No function */
	}
}


