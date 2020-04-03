/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_COM_Transmit_Retrieval.c                         		*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                     																		*/
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/

#ifndef _TASKING
#include <intrins.h>
#include "LH_ST10F276.h"
#else
#include "regf276e.h"
#endif	 
#include "typedef.h"
#include "enum.h"
#include "define.h"
#include "DRV_COM_Data.h"
#include "DRV_COM_Transmit_Retrieval.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_COM_Transmit_Retrieval(void)
{
	UWORD16 Compute_CRC = 0;
	UBYTE Compteur;
	
	/*%C At the end of previous event sending, sending the next event 		 */
   if (DRV_COM_End_of_Transmit == TRUE)
   {
  	 
  	   	/*%C Feed the frame with the start header							*/
  	   	Array_Event [COM_TX_START_FRAME_1] = START_FRAME_COM_VALUE_1;
  		Array_Event [COM_TX_START_FRAME_2] = START_FRAME_COM_VALUE_2;
 		Array_Event [COM_TX_START_FRAME_3] = START_FRAME_COM_VALUE_3;

 	  	/*%C The event retrieval frame ID */
 	  	Array_Event [COM_TX_ID_FRAME] = ID_EVENT_DATA;

		/*%C While there's event in the flash	*/
		if (num_event <= (((EVENT_FLASH_END_ADDRESS 
							- EVENT_FLASH_START_ADDRESS) 
							/ EVENT_Last_Event_Parameter ) - 1))
		{
			/* Read the Event ID of the current Event */
			Array_Event[EVENT_NB_ID + COM_TX_DATA_FRAME] 
							= DRV_EVENT_Read_Event(num_event,
													EVENT_NB_ID,
													adr_flash_retrieval);
			/*%C We load the array only if the event_id different of 0xFF */
			if (Array_Event[EVENT_NB_ID + COM_TX_DATA_FRAME] != 0xFF)
			{
	   			for(Compteur = EVENT_NB_ID ;
	   			    Compteur < EVENT_Last_Event_Parameter;
	   			    Compteur++)
			   	{
					Array_Event[Compteur + COM_TX_DATA_FRAME] 
							= DRV_EVENT_Read_Event(num_event,
												   Compteur,
												   adr_flash_retrieval);
				 	}

				/* Compute CRC */
	   	  	Compute_CRC = CRC16_TableCompute((UWORD16)EVENT_NB_ID + COM_TX_DATA_FRAME, 
	 												(UWORD16)EVENT_Last_Event_Parameter + COM_TX_DATA_FRAME,   
													Array_Event ,
													0);
	     			
	   	  	Array_Event [COM_TX_MSB_CRC_FRAME + EVENT_Last_Event_Parameter - 1] 
		  										= (UBYTE)(Compute_CRC >> 8);
		  		
				Array_Event [COM_TX_LSB_CRC_FRAME + EVENT_Last_Event_Parameter - 1] 
		  										= (UBYTE)(Compute_CRC & 0x00FF);
				
				/* End of frame */
				Array_Event [COM_TX_END_FRAME_1	+ EVENT_Last_Event_Parameter - 1] 
		  										= END_FRAME_COM_VALUE_1;
				
				Array_Event [COM_TX_END_FRAME_2 	+ EVENT_Last_Event_Parameter - 1] 
		  				  						= END_FRAME_COM_VALUE_2;
				
				Array_Event [COM_TX_END_FRAME_3 	+ EVENT_Last_Event_Parameter - 1] 
		  				   					= END_FRAME_COM_VALUE_3;
	   			
	   		S0TBIR = 0;
				PECC2 = 0x0500; /* Origin index increasing - sending a byte */
  	 			/*%C Size of events array to transmit */
  	 			PECC2 |= EVENT_Last_Event_Parameter + End_Of_Table_Com_TX_Remote - 1; 
				/*%C Origin index on events array							*/
   	 		SRCP2 = _sof_(&Array_Event); 	/*%C Events array adress    */
				/*%C Index transformation in adress  0 segment				*/
				/*%C Destination index on  RS232 transmit register	  		*/
   	 		DSTP2 = (UWORD16) &S0TBUF; 
				/*%C Sending datas allowed									*/
  	 	  	 	DRV_COM_End_of_Transmit = FALSE;
				S0TBIE = 1;
				S0TBIR = 1;
				
	  	 	}
			else
			{
   			/*%C End of tranmission byte Identification  				*/
	   		Array_Event [COM_TX_ID_FRAME] = ID_END_OF_TRANSMISSION;
	 		   /*%C There's no data to tranmit								*/
	 			Array_Event [COM_TX_DATA_FRAME] = 0x00; 	  		
			   /*%C No CRC compute with this kind of frame					*/
	 	  		Array_Event [COM_TX_MSB_CRC_FRAME] = 0x00; 
			  	Array_Event [COM_TX_LSB_CRC_FRAME] = 0x00; 		   
			   /*%C Stop Frame bytes										*/
			  	Array_Event [COM_TX_END_FRAME_1] = END_FRAME_COM_VALUE_1;
			  	Array_Event [COM_TX_END_FRAME_2] = END_FRAME_COM_VALUE_2;
			  	Array_Event [COM_TX_END_FRAME_3] = END_FRAME_COM_VALUE_3;
	   
			  	S0TBIR = 0;
				/* Origin index increasing - sending a byte */
	 			PECC2 = 0x0500; 
				/* Size of events array to	transmit	    */ 
	 			PECC2 |= End_Of_Table_Com_TX_Remote;
				/*%C Origin index on events array							*/
	  	 		SRCP2 = _sof_(&Array_Event); 	/*%C Events array adress    */
	  			/*%C Index transformation in adress  0 segment				*/
				/*%C Destination index on  RS232 transmit register	  		*/
	  	 		DSTP2 = (UWORD16) &S0TBUF; 
	  			/*%C Sending datas allowed									*/
	  	 	  	DRV_COM_End_of_Transmit = FALSE;
	  			S0TBIE = 1;
				S0TBIR = 1;
		 		num_event++;
				Communication_State = COM_TRANSMIT_STOP;
				
			}
 			/*%C We increase the event number counter 						*/
 			num_event++;
		}
	
		 /*%C End of Retrieval transmission */
		 /*%C when we've transmitted the last event, we can send the end of */
		/*%C with transmission frame										*/
	 	 else if (num_event == ((EVENT_FLASH_END_ADDRESS 
							- EVENT_FLASH_START_ADDRESS) 
							/ EVENT_Last_Event_Parameter ) )
		{
   			/*%C End of tranmission byte Identification  				*/
	   		Array_Event [COM_TX_ID_FRAME] = ID_END_OF_TRANSMISSION;
	 		   /*%C There's no data to tranmit								*/
	 			Array_Event [COM_TX_DATA_FRAME] = 0x00; 	  		
			   /*%C No CRC compute with this kind of frame					*/
	 	  		Array_Event [COM_TX_MSB_CRC_FRAME] = 0x00; 
			  	Array_Event [COM_TX_LSB_CRC_FRAME] = 0x00; 		   
			   /*%C Stop Frame bytes										*/
			  	Array_Event [COM_TX_END_FRAME_1] = END_FRAME_COM_VALUE_1;
			  	Array_Event [COM_TX_END_FRAME_2] = END_FRAME_COM_VALUE_2;
			  	Array_Event [COM_TX_END_FRAME_3] = END_FRAME_COM_VALUE_3;
	   
			  	S0TBIR = 0;
				/* Origin index increasing - sending a byte */
	 			PECC2 = 0x0500; 
				/* Size of events array to	transmit	    */ 
	 			PECC2 |= End_Of_Table_Com_TX_Remote;
				/*%C Origin index on events array							*/
	  	 		SRCP2 = _sof_(&Array_Event); 	/*%C Events array adress    */
	  			/*%C Index transformation in adress  0 segment				*/
				/*%C Destination index on  RS232 transmit register	  		*/
	  	 		DSTP2 = (UWORD16) &S0TBUF; 
	  			/*%C Sending datas allowed									*/
	  	 	  	DRV_COM_End_of_Transmit = FALSE;
	  			S0TBIE = 1;
				S0TBIR = 1;
		 		num_event++;
 		}
 		else
 		{
				Communication_State = COM_TRANSMIT_STOP;
 		}  
  	}
}
	
