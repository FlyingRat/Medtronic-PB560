/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_COM_Transmit_Monitoring_To_Key.c                                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C          																						*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/

#ifndef _TASKING
#include <intrins.h>
#include "LH_ST10F276.h"
#else
#include "regf276e.h"
#endif	 
#include "typedef.h"
#include "DB_Control.h"
#include "DB_Compute.h"
#include "DB_Usb.h"
#include "enum.h"
#include "DRV_COM_Data.h"
#include "CRC16_Table.h"
#include "DRV_COM_Transmit_Monitoring_To_Key.h"
#include "Driver_USB_Data.h"

void DRV_COM_Transmit_Monitoring_To_Key(void)
{
	UWORD16 UsbMsnbOneDetected = DB_UsbRead(USB_MSNB_ONE_DETECTED_U16);
	UWORD16 UsbMsnbTwoDetected = DB_UsbRead(USB_MSNB_TWO_DETECTED_U16);

	UWORD16 Compute_CRC = 0;
	UWORD16 Compute_U16 = 0; 
	UBYTE Param =0;
	
  	   /*%C Feed the frame with the 3 start bytes							*/
  		Array_Monitoring_To_Key [COM_TX_START_FRAME_1] = START_FRAME_COM_VALUE_1;
  		Array_Monitoring_To_Key [COM_TX_START_FRAME_2] = START_FRAME_COM_VALUE_2;
 		Array_Monitoring_To_Key [COM_TX_START_FRAME_3] = START_FRAME_COM_VALUE_3;
 	  	
 	 	/* Frame Identification byte	*/
 	  	Array_Monitoring_To_Key [COM_TX_ID_FRAME] = ID_COM_MONITORING_TO_KEY;


		if ( ( (UsbMsnbOneDetected == TRUE)
		   	&& (UsbMsnbTwoDetected == FALSE)	)
		  || ( (UsbMsnbOneDetected == FALSE)
		   	&& (UsbMsnbTwoDetected == TRUE) ) )
		{
			if (USB_CommandInProgress == FALSE)
			{
				if (!HMI_USBSendCmd(USB_MONITOR_TRANSFER_U16,DRV_COM_Param))
				{
					Array_Monitoring_To_Key [COM_TX_DATA_FRAME] = COM_MONIT_TO_KEY_TRANSFER_START_OK;
				}
				else
				{
					Array_Monitoring_To_Key [COM_TX_DATA_FRAME] = COM_MONIT_TO_KEY_TRANSFER_NOT_IN_USB_MENU;
				}
  			}
			else
			{
				Array_Monitoring_To_Key [COM_TX_DATA_FRAME] = COM_MONIT_TO_KEY_TRANSFER_ERROR_USB_BUSY;
			}
		}
		else if ( (UsbMsnbOneDetected == FALSE)
		   	   && (UsbMsnbTwoDetected == FALSE) )
		{
			Array_Monitoring_To_Key [COM_TX_DATA_FRAME] = COM_MONIT_TO_KEY_TRANSFER_ERROR_NO_KEY;
		}
		else
		{
			Array_Monitoring_To_Key [COM_TX_DATA_FRAME] = COM_MONIT_TO_KEY_TRANSFER_ERROR_TOO_MANY_KEYS;
		}

  		/*%C CRC16 Compute */
  	  	Compute_CRC = CRC16_TableCompute(	
  	  							(UWORD16)(COM_TX_DATA_FRAME), 
  		 						(UWORD16)(COM_TX_DATA_FRAME + 1),   
								Array_Monitoring_To_Key,
								0);
  		 	  		 									  
 	  	
		/*%CFeed the frame with 2 CRC bytes */
		Array_Monitoring_To_Key [COM_TX_MSB_CRC_FRAME] = (UBYTE)(Compute_CRC >> 8);
		Array_Monitoring_To_Key [COM_TX_LSB_CRC_FRAME] = (UBYTE)(Compute_CRC &0x00FF );

		/*%C Feed the frame with the 3 stop frame bytes					   	*/
		Array_Monitoring_To_Key [COM_TX_END_FRAME_1] = END_FRAME_COM_VALUE_1; 
		Array_Monitoring_To_Key [COM_TX_END_FRAME_2] = END_FRAME_COM_VALUE_2; 
		Array_Monitoring_To_Key [COM_TX_END_FRAME_3] = END_FRAME_COM_VALUE_3;
		
	  	S0TBIR = 0;
		/* Origin index increasing - sending a byte */
		PECC2 = 0x0500; 
	   	/* Size of array to transmit	    */
	   	PECC2 |= End_Of_Table_Com_TX_Remote; 
		/*%C Origin index on events array							*/
 	  	SRCP2 = _sof_(&Array_Monitoring_To_Key); 	
		/*%C Index transformation in adress  0 segment				*/
		/*%C Destination index on  RS232 transmit register	  		*/
 	  	DSTP2 = (UWORD16) &S0TBUF; 
		/*%C Sending datas allowed									*/
		S0TBIE = 1;
		S0TBIR = 1;
		/*%C End of transmission  				    */
	 	Communication_State = COM_TRANSMIT_STOP;

}
