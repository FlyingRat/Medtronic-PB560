/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_COM_Transmit_Machine_Counter.c                                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C          			Send Machine counter via UART																			*/
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
#include "DRV_COM_Data.h"
#include "DRV_COM_Transmit_Machine_Counter.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void DRV_COM_Transmit_Machine_Counter(void)
{
 	UWORD16 Compute_CRC = 0;
	UWORD16 Compute_U16 = 0 ;

	
	   /*%C Feed the frame with the 3 start bytes							*/
		Array_Machine_Counter [COM_TX_START_FRAME_1] = START_FRAME_COM_VALUE_1;
		Array_Machine_Counter [COM_TX_START_FRAME_2] = START_FRAME_COM_VALUE_2;
		Array_Machine_Counter [COM_TX_START_FRAME_3] = START_FRAME_COM_VALUE_3;
	  	
	  	/*%C The Event retrieval frame ID */
	  	Array_Machine_Counter [COM_TX_ID_FRAME] = ID_MACHINE_HOUR;
	  
	  	/*%C Feed the frame with data bytes									*/
	Compute_U16 = (UWORD16) DB_ControlRead(CURRENT_MACHINE_COUNTER_HOUR_U16);
	  	Array_Machine_Counter [COM_MACHINE_COUNTER_MSB + COM_TX_DATA_FRAME] 
	  														= (UBYTE)(Compute_U16 >>8);
	Array_Machine_Counter [COM_MACHINE_COUNTER_LSB + COM_TX_DATA_FRAME] 
														= (UBYTE)(Compute_U16 & 0x00FF);


		/*%C CRC16 Compute */
		Compute_CRC = CRC16_TableCompute((UWORD16)COM_MACHINE_COUNTER_MSB + COM_TX_DATA_FRAME, 
 												(UWORD16)End_Of_Table_Com_Machine_Counter + COM_TX_DATA_FRAME,   
												Array_Machine_Counter,
												0);

	/*%CFeed the frame with 2 CRC bytes */
	Array_Machine_Counter [	COM_TX_MSB_CRC_FRAME 
					 +	End_Of_Table_Com_Machine_Counter - 1] 
				   	 = 	(UBYTE)(Compute_CRC >>8);
	Array_Machine_Counter [	COM_TX_LSB_CRC_FRAME 
					 +	End_Of_Table_Com_Machine_Counter - 1] 
					 =	(UBYTE)(Compute_CRC);

	/*%C Feed the frame with the 3 stop frame bytes					   	*/
	Array_Machine_Counter [ COM_TX_END_FRAME_1	
					+ End_Of_Table_Com_Machine_Counter - 1]
					= END_FRAME_COM_VALUE_1; 
	Array_Machine_Counter [	COM_TX_END_FRAME_2 
					+ End_Of_Table_Com_Machine_Counter - 1]
					= END_FRAME_COM_VALUE_2; 
	Array_Machine_Counter [	COM_TX_END_FRAME_3 
					+ End_Of_Table_Com_Machine_Counter - 1]	
					= END_FRAME_COM_VALUE_3;
	
  	S0TBIR = 0;
	/* Origin index increasing - sending a byte */
	PECC2 = 0x0500; 
	/* Size of array to transmit	    										*/
	PECC2 |= End_Of_Table_Com_Machine_Counter + End_Of_Table_Com_TX_Remote - 1 ; 
	/*%C Origin index on events array										*/
	SRCP2 = _sof_(&Array_Machine_Counter); 	
	/*%C Index transformation in adress  0 segment					*/
	/*%C Destination index on  RS232 transmit register	  				*/
	DSTP2 = (UWORD16) &S0TBUF; 
	/*%C Sending datas allowed													*/
	DRV_COM_End_of_Transmit = FALSE;
	S0TBIE = 1;
	S0TBIR = 1;
	Communication_State = COM_TRANSMIT_STOP;
}
