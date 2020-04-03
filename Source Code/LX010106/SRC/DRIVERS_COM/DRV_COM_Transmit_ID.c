/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_COM_Transmit_ID.c                                             */
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
#include "LH_ST10F276.h"
#include <intrins.h>
#else
#include "regf276e.h"
#endif
#include "typedef.h"
#include "enum.h"
#include "DB_Control.h"
#include "DRV_COM_Data.h"
#include "CRC16_Table.h"
#include "DRV_COM_Transmit_ID.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void DRV_COM_Transmit_ID(void)
{
 	UWORD16 Compute_CRC = 0;
	UWORD16 Compute_U16 = 0; 
	
  	   	/*%C Feed the frame with the 3 start bytes							*/
  		Array_ID [COM_TX_START_FRAME_1]	= START_FRAME_COM_VALUE_1;
  		Array_ID [COM_TX_START_FRAME_2]	= START_FRAME_COM_VALUE_2;
 		Array_ID [COM_TX_START_FRAME_3] = START_FRAME_COM_VALUE_3;
 	  	
 	  	/*%C The Event retrieval frame ID */
 	  	Compute_U16 = DB_ControlRead(VENTIL_STATE_U16);
 	 
 	  	Array_ID [COM_TX_ID_FRAME] = ID_SERIAL_NUMBER;

 	  	/*%C Feed the frame with data bytes									*/
		Compute_U16 = (UWORD16) DB_VersionRead(SERIAL_NUMBER_1);
 	  	Array_ID [ID_DEVICE_1 + COM_TX_DATA_FRAME] = (UBYTE)(Compute_U16 >>8);
		Array_ID [ID_DEVICE_2 + COM_TX_DATA_FRAME] = (UBYTE)(Compute_U16);
		Compute_U16 = (UWORD16) DB_VersionRead(SERIAL_NUMBER_2); 
		Array_ID [ID_DEVICE_3 + COM_TX_DATA_FRAME] = (UBYTE)(Compute_U16 >>8);
		Array_ID [ID_DEVICE_4 + COM_TX_DATA_FRAME] = (UBYTE)(Compute_U16);
		Compute_U16 = (UWORD16) DB_VersionRead(SERIAL_NUMBER_3);
		Array_ID [ID_DEVICE_5 + COM_TX_DATA_FRAME] = (UBYTE)(Compute_U16 >>8);
		Array_ID [ID_DEVICE_6 + COM_TX_DATA_FRAME] = (UBYTE)(Compute_U16);
		Compute_U16 = (UWORD16) DB_VersionRead(SERIAL_NUMBER_4);
		Array_ID [ID_DEVICE_7 + COM_TX_DATA_FRAME] = (UBYTE)(Compute_U16 >>8);
		Array_ID [ID_DEVICE_8 + COM_TX_DATA_FRAME] = (UBYTE)(Compute_U16);
		Compute_U16 = (UWORD16) DB_VersionRead(SERIAL_NUMBER_5);
		Array_ID [ID_DEVICE_9 + COM_TX_DATA_FRAME]  = (UBYTE)(Compute_U16 >>8);
		Array_ID [ID_DEVICE_10 + COM_TX_DATA_FRAME] = (UBYTE)(Compute_U16);
		Compute_U16 = (UWORD16) DB_VersionRead(SERIAL_NUMBER_6);
		Array_ID [ID_DEVICE_11 + COM_TX_DATA_FRAME] = (UBYTE)(Compute_U16 >>8);
		Array_ID [ID_DEVICE_12 + COM_TX_DATA_FRAME] = (UBYTE)(Compute_U16);			
		

  		/*%C CRC16 Compute */
  	  	Compute_CRC = CRC16_TableCompute(	
  	  							(UWORD16)(ID_DEVICE_1 + COM_TX_DATA_FRAME), 
  		 						(UWORD16)(End_Of_Table_Com_ID_Device + COM_TX_DATA_FRAME),   
								 Array_ID,
								 0 );


		/*%CFeed the frame with 2 CRC bytes */
		Array_ID [	COM_TX_MSB_CRC_FRAME 
						 +	End_Of_Table_Com_ID_Device - 1] 
					   	 = 	(UBYTE)(Compute_CRC >> 8);
		Array_ID [	COM_TX_LSB_CRC_FRAME 
						 +	End_Of_Table_Com_ID_Device - 1] 
						 =	(UBYTE)(Compute_CRC &0x00FF );

		/*%C Feed the frame with the 3 stop frame bytes			    	*/
		Array_ID [COM_TX_END_FRAME_1 + End_Of_Table_Com_ID_Device - 1] = END_FRAME_COM_VALUE_1; 
		Array_ID [COM_TX_END_FRAME_2 + End_Of_Table_Com_ID_Device - 1] = END_FRAME_COM_VALUE_2; 
		Array_ID [COM_TX_END_FRAME_3 + End_Of_Table_Com_ID_Device - 1] = END_FRAME_COM_VALUE_3;
		
	  	S0TBIR = 0;
		/* Origin index increasing - sending a byte						 */
		PECC2 = 0x0500; 
 	   	/* Size of array to transmit	   								 */
 	   	PECC2 |= End_Of_Table_Com_ID_Device + End_Of_Table_Com_TX_Remote - 1 ; 
		/*%C Origin index on array												*/
 	  	SRCP2 = _sof_(&Array_ID); 	
 	   	/*%C Index transformation in adress  0 segment					*/
		/*%C Destination index on  RS232 transmit register	  			*/
 	   	DSTP2 = (UWORD16) &S0TBUF; 
		/*%C Sending datas allowed												*/
		S0TBIE = 1;
		S0TBIR = 1;
		/*%C End of transmition  				    							*/
	 	Communication_State = COM_TRANSMIT_STOP;

}
