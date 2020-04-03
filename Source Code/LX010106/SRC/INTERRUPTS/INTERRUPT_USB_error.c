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
	#include <intrins.h>
#else	    
 		#include "regf276e.h"
#endif 	
#include "io_declare.h"
#include "typedef.h"
#include "enum.h"
#include "INTERRUPT_USB_Error.h"
		
/*****************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
#ifndef _TASKING
 void INTERRUPT_USB_Error(void)	interrupt (0x43)
#else
interrupt (0x43)
 void INTERRUPT_USB_Error(void)
#endif
{
	/*Gestion d'erreurs clé USB */
	/*A finir*/
	/*%C Reset Flaf IR*/
	XIR3CLR = 0x0008 ;
	/*%C Reset SPI Error Flag*/
	XSSCCONCLR = 0x0F00  ;
	/*%C DeSelect the bridge */
   DRV_OutputPort(CE_SPI_USB,1) ;   
}	  



	
	
  
