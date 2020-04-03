/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_COM_Transmit_TaskMeasure.c  											*/
/*																										*/
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
#include "Structure.h"
#include "SCHED_Ventilation_Main.h"
#include "Main_Data.h"
#include "DB_Control.h"
#include "DRV_COM_Data.h"
#include "DRV_COM_Transmit_TaskMeasure.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void DRV_COM_Transmit_TaskMeasure(void)
{

	UWORD16 Loop = 0 ;
	UWORD16 LoopArray = 0 ;
	UWORD16 Compute_CRC = 0;
	UWORD16 Compute_U16 = 0;



	/*%C At the end of previous event sending, sending the next event */
   if (DRV_COM_End_of_Transmit == TRUE)
  	{
  	   /*%C Feed the frame with the 3 start bytes */
  		Array_TaskMeasure [COM_TX_START_FRAME_1]
  							= START_FRAME_COM_VALUE_1;
  		Array_TaskMeasure [COM_TX_START_FRAME_2]
  							= START_FRAME_COM_VALUE_2;
 		Array_TaskMeasure [COM_TX_START_FRAME_3]
 							= START_FRAME_COM_VALUE_3;
 	  	 
		/*%C Write the ID frame identifiant */ 	  	 	 
 	  	Array_TaskMeasure [COM_TX_ID_FRAME] = ID_VENTIL_TASK_MEASURE;

		/*%C Write Min, Max and Current time in frame */
		for(	Loop = 0 ; 
				Loop < MAXIMUM_VENTILATION_NUMBER_OF_TASKS ;
				Loop ++)
		{

			/*%C Msb of Ventilation Time Task Min */
			Array_TaskMeasure	[	COM_TX_DATA_FRAME 
									+ 	LoopArray]
					= (UBYTE)(Ventilation_TimesOfTask[Loop].mini >> 8) ;

			/*%C Compute CRC */
			Compute_U16 = 	Compute_U16
									^ 	Array_TaskMeasure	
									[	COM_TX_DATA_FRAME 
									+	LoopArray] ;



			/*%C Msb of Ventilation Time Task Current */
			Array_TaskMeasure	[	COM_TX_DATA_FRAME 
									+ 	LoopArray
									+ 	(2 * MAXIMUM_VENTILATION_NUMBER_OF_TASKS)]
					= (UBYTE)(Ventilation_TimesOfTask[Loop].current	>> 8) ;

			/*%C Compute CRC */
			Compute_U16 = 	Compute_U16
									^ 	Array_TaskMeasure	
									[	COM_TX_DATA_FRAME 
									+	LoopArray
									+	(2 * MAXIMUM_VENTILATION_NUMBER_OF_TASKS)] ;


			/*%C Msb of Ventilation Time Task Max */
			Array_TaskMeasure	[	COM_TX_DATA_FRAME
									+ 	LoopArray
									+ 	(4 * MAXIMUM_VENTILATION_NUMBER_OF_TASKS)]
					= (UBYTE)(Ventilation_TimesOfTask[Loop].maxi	>> 8) ;

			/*%C Compute CRC */
			Compute_U16 = 	Compute_U16
									^ 	Array_TaskMeasure	
									[	COM_TX_DATA_FRAME 
									+	LoopArray
									+	(4 * MAXIMUM_VENTILATION_NUMBER_OF_TASKS)] ;


			LoopArray = LoopArray + 1 ;


			/*%C Lsb of Ventilation Time Task Min */
			Array_TaskMeasure	[	COM_TX_DATA_FRAME 
									+ 	LoopArray]
					= (UBYTE)(Ventilation_TimesOfTask[Loop].mini) ;

			/*%C Compute CRC */
			Compute_U16 = 	Compute_U16
									^ 	Array_TaskMeasure 
									[	COM_TX_DATA_FRAME 
									+	LoopArray] ;


			/*%C Lsb of Ventilation Time Task Current */
			Array_TaskMeasure	[	COM_TX_DATA_FRAME 
									+ 	LoopArray
									+	(2 * MAXIMUM_VENTILATION_NUMBER_OF_TASKS)]
					= (UBYTE)(Ventilation_TimesOfTask[Loop].current) ;

			/*%C Compute CRC */
			Compute_U16 = 	Compute_U16
									^ 	Array_TaskMeasure 
									[	COM_TX_DATA_FRAME 
									+	LoopArray
									+	(2 * MAXIMUM_VENTILATION_NUMBER_OF_TASKS)] ;


			/*%C Lsb of Ventilation Time Task Max */
			Array_TaskMeasure	[	COM_TX_DATA_FRAME 
									+ 	LoopArray
									+	(4 * MAXIMUM_VENTILATION_NUMBER_OF_TASKS)]
					= (UBYTE)(Ventilation_TimesOfTask[Loop].maxi) ;

			/*%C Compute CRC */
			Compute_U16 = 	Compute_U16
									^ 	Array_TaskMeasure 
									[	COM_TX_DATA_FRAME 
									+	LoopArray
									+	(4 * MAXIMUM_VENTILATION_NUMBER_OF_TASKS)] ;



			LoopArray = LoopArray + 1 ;
		}

	   /*%C CRC Compute */
  	
		Compute_CRC = START_FRAME_COM_VALUE_1 
						^ START_FRAME_COM_VALUE_2 
						^ START_FRAME_COM_VALUE_3
						^ ID_VENTIL_TASK_MEASURE 
						^ Compute_U16 ;


		/*%CFeed the frame with 2 CRC bytes */
		Array_TaskMeasure 	[	COM_TX_MSB_CRC_FRAME 
									+	(MAXIMUM_VENTILATION_NUMBER_OF_TASKS * 3 * 2 ) 
 									- 	1]
					   			=	(UBYTE)(Compute_CRC & 0x00FF);


		/*%C Feed the frame with the 3 stop frame bytes */
		Array_TaskMeasure [	COM_TX_END_FRAME_1
								+ 	(MAXIMUM_VENTILATION_NUMBER_OF_TASKS * 3 * 2 ) - 2]
								= 	END_FRAME_COM_VALUE_1; 
		Array_TaskMeasure [	COM_TX_END_FRAME_2 
								+ 	(MAXIMUM_VENTILATION_NUMBER_OF_TASKS * 3 * 2 ) - 2]
								= 	END_FRAME_COM_VALUE_2; 
		Array_TaskMeasure [	COM_TX_END_FRAME_3 
								+ 	(MAXIMUM_VENTILATION_NUMBER_OF_TASKS * 3 * 2 ) - 2]	
								= 	END_FRAME_COM_VALUE_3;
		
	  	S0TBIR = 0;

		/*%C Origin index increasing - sending a byte */
		PECC2 = 0x0500;
 	   
 	   /* Size of events array to transmit	    */
 	   PECC2 |= 		(MAXIMUM_VENTILATION_NUMBER_OF_TASKS * 3 * 2 )
 	   				+ 	End_Of_Table_Com_TX_Remote 
 	   				- 	2 ; 
		
		/*%C Origin index on events array */
 	   SRCP2 = _sof_(&Array_TaskMeasure); 	/*%C Events array adress */
		
		/*%C Index transformation in adress  0 segment */
		/*%C Destination index on  RS232 transmit register */
 	   DSTP2 = (UWORD16) &S0TBUF; 
		
		/*%C Sending datas allowed */
		S0TBIE = 1;
		S0TBIR = 1;
		/*%C End of transmition */
	 	
	 	Communication_State = COM_TRANSMIT_STOP;

	}
}
