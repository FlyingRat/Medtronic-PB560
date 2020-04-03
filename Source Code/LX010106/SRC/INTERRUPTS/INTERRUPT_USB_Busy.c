/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                            				*/
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : INTERRUPT_USB_Busy.c 														*/
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
#include "Driver_USB_data.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
#ifndef _TASKING
 void INTERRUPT_USB_Busy(void)	interrupt (0x1A)
#else
interrupt (0x1A)
 void INTERRUPT_USB_Busy(void)
#endif
{
 	UBYTE ComputeReplyHeaderCheck = 0 ;
	UWORD16 ReplyHeaderCheck = 0 ;
	UWORD16 PECCFront = 0 ;
	UWORD16 ReplyFront = 0 ;

/******************************************************************************/
/*%C Disable USB interrupt	(CC10 , SPI , PEC)	*/
/******************************************************************************/

	/*%C Disable the interrupt CC10 (USB_BUSY)	*/
	CC10IE = 0 ;
	/*%C Reset the interrupt request flag (CC010 = USB_BUSY)	*/
	CC10IR = 0 ;

	/*%C PECC7 : Inhibition PECC6 Interrupt and Reset this Flag */
	XP1IE = 0 ;
	XP1IR = 0 ;	

	/*%C Inhibition of Transmit SPI Interrupt and Reset this Flag */
	XIR1CLR = 0x0808 ;

/******************************************************************************/
/*%C Compute the number of byte to finish the send frame  	*/
/******************************************************************************/

	/*%C Compute the reply header check */
	ComputeReplyHeaderCheck = 	((PEC_Reception[1] & 0x0F)
									^ 	((PEC_Reception[1] & 0xF0) >> 4)
									^ 	(PEC_Reception[0] & 0x0F)) ;
	ComputeReplyHeaderCheck = ~ ComputeReplyHeaderCheck ;
	ComputeReplyHeaderCheck &= 0x0F;

	/*%C Extract the reply header check */
	ReplyHeaderCheck = ((PEC_Reception[0] & 0xF0) >> 4);

	/*%C Compare the reply header check with the compute header check */
	if(ReplyHeaderCheck == ComputeReplyHeaderCheck)
	{
		/*%C The reply header is true															*/
		/*%C Extract the reply header nbbyte												*/
		ReplyFront = (PEC_Reception[0] << 8	| PEC_Reception[1]) ;
		ReplyFront = ReplyFront & 0x0FFF ;

		/*%C Limit the compute clock edge													*/
		if (ReplyFront < 0x00FF && ReqNbBytes < 0x00FF )
		{
			/*%C Search the maximun clock edge */
			if(ReplyFront > ReqNbBytes)
			{ 
				PECCFront = ReplyFront ;
			} 
			else 
			{
				PECCFront = ReqNbBytes ; 
			}
		}
		else
		{
			PECCFront = 0x00FE;
		}
		/*%C Minimize the compute clock edge												*/
		if (PECCFront < 0x0005)
		{
			PECCFront = 0x0005;
		}
	}
	else
	{
		/*%C The reply header is false														*/
		/*%C Limit the compute clock edge													*/
		if (ReqNbBytes < 0xFF)
		{ 
			PECCFront = ReqNbBytes ;
		}
		else
		{
			PECCFront = 0x00FE;
		}
		/*%C Minimize the compute clock edge												*/
		if (PECCFront < 0x0005)
		{
			PECCFront = 0x0005;
		}
	}

	/*%C Soustract the header datas 	*/
	PECCFront = PECCFront - 0x02 ;

/******************************************************************************/
/*%C PECC 6 et 7 configuration  	*/
/******************************************************************************/

	/*%C Assign the number of PECC6 clock edge */
	DSTP7	  = _sof_(&PEC_Emission[2]);
	PECC6 = (0x0500 + PECCFront) ;


	/*%C Assign the number of PECC7 clock edge and datas*/
	DSTP7	  = _sof_(&PEC_Reception[2]);
 	PECC7 = (0x0300 + PECCFront);

	
	/*%C Authorization of SPI Transmit interrupt */
	XIR1SET = 0x0800 ;
	XP1IE = 1 ;


/******************************************************************************/
/*%C Start data transmission */
/******************************************************************************/
		XP1IR = 1 ;

}


															  