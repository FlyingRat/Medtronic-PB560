/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505			                                           	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : INTERRUPT_USB_SpiBus.c 														*/
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
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/


#ifndef _TASKING
#include "LH_ST10F276.h"
#else
#include "regf276e.h"
#endif	 
#include "typedef.h"
#include "enum.h"
#include "structure.h"
#include "define.h"
#include "DRV_COM_Data.h"
#include "Flash_Monit_Data.h"
#include "Driver_USB_data.h"
#include "INTERRUPT_USB_SpiBus.h"
						
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
#ifndef _TASKING
 void INTERRUPT_USB_SpiBus_End_Transmit(void)	interrupt (0x41)
#else
interrupt (0x41)
 void INTERRUPT_USB_SpiBus_End_Transmit(void)
#endif

{														  
	/*%C Set the PECC7 register, inhibition this interrupt and reset this flag */
  	XP1IC &= 0xFF3F ;

	/*%C Inhibition of Transmit SPI Interrupt and Reset this Flag */
	XIR1CLR = 0x0808 ;

}	  

#ifndef _TASKING
 void INTERRUPT_USB_SpiBus_End_Receive(void)	interrupt (0x42)
#else
interrupt (0x42)
 void INTERRUPT_USB_SpiBus_End_Receive(void)
#endif
{ 
	/*%C Set the PECC6 register, inhibition this interrupt and reset this flag */
	XP2IC &= 0xFF3F ;

	/*%C Inhibition of Receive SPI Interrupt and Reset this Flag */
	XIR2CLR = 0x1010 ;

	/*%C DeSelect the bridge */
  	DRV_OutputPort(CE_SPI_USB,1) ;

	/*%C In Nand Flash Transfer case */
	switch(UsbFlashTrasnferRunning)
	{
		case USB_NAND_MONIT_TRANSFER_RUNNING :
		{
			DRV_MONIT_New_Data = FALSE;
			break ;
		}
		case USB_NAND_TREND_TRANSFER_RUNNING :
		{
			DRV_TREND_New_Data = FALSE;
			break ;
		}
		default :
		{
			break ;
		}
	}


}

	
	
  