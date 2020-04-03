/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_COM_Transmit_Detailled.c                         				*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C               Send to the UART the monotoring data								*/
/*%C								recorded in the Nand Flash   								*/
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
	#include "LH_ST10F276.h"
    #include <intrins.h>
#else
	#include "regf276e.h"
#endif	 
#include "typedef.h"
#include "enum.h"
#include "define.h"
#include "Structure.h"
#include "DRV_COM_Data.h"
#include "Flash_Monit_Data.h"
#include "DRV_COM_Transmit_Detailled.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_COM_Transmit_Detailled(void)
{

UWORD16 Compute_CRC = 0;
UBYTE Compteur;
if(DRV_COM_End_of_Transmit == TRUE)
{
   if(DRV_MONIT_New_Data == TRUE)
	{
		/* Start Frame */
 		Array_Detailled_Monit [COM_TX_START_FRAME_1] = START_FRAME_COM_VALUE_1;
		Array_Detailled_Monit [COM_TX_START_FRAME_2] = START_FRAME_COM_VALUE_2;
		Array_Detailled_Monit [COM_TX_START_FRAME_3] = START_FRAME_COM_VALUE_3;
		/* ID Type Frame */
  		Array_Detailled_Monit [COM_TX_ID_FRAME] = ID_DETAILED_MONITORING_DATA;
		/* Size of Frame */
		Array_Detailled_Monit [COM_TX_DATA_FRAME] = (UBYTE)DRV_MONIT_Received_Data;
		/* Data */ 
		for(Compteur = 0; Compteur < DRV_MONIT_Received_Data ; Compteur ++)
		{
						Array_Detailled_Monit[Compteur + COM_TX_DATA_FRAME + 1] 
						=  DRV_MONIT_UART_Buffer_Var[Compteur];
		}
								   
   	/*%C CRC16 Compute with data and size of frame */ 		  
   	Compute_CRC = CRC16_TableCompute((UWORD16)COM_TX_DATA_FRAME, 
	 												(UWORD16)DRV_MONIT_Received_Data + COM_TX_DATA_FRAME + 1,   
													Array_Detailled_Monit,
													0	);
   	Array_Detailled_Monit [COM_TX_MSB_CRC_FRAME + DRV_MONIT_Received_Data] = (UBYTE)(Compute_CRC >> 8);
		Array_Detailled_Monit [COM_TX_LSB_CRC_FRAME + DRV_MONIT_Received_Data] = (UBYTE)(Compute_CRC & 0x00FF);		   
		
		/*%C Stop Frame */			 
 		Array_Detailled_Monit [COM_TX_END_FRAME_1 + DRV_MONIT_Received_Data] = END_FRAME_COM_VALUE_1;
		Array_Detailled_Monit [COM_TX_END_FRAME_2 + DRV_MONIT_Received_Data] = END_FRAME_COM_VALUE_2;
		Array_Detailled_Monit [COM_TX_END_FRAME_3 + DRV_MONIT_Received_Data] = END_FRAME_COM_VALUE_3;
 		
 	  			
		/*%C Autorisation de l'interruption de transmission RS232  			*/	  
	  	S0TBIR = 0;
		/*%C incrémentation du pointeur source - transfert d'un word 	*/
		PECC2 = 0x0500; 
		/*%C taille du tableau d'évènement à transférer	*/
 		PECC2 |= (UBYTE)(DRV_MONIT_Received_Data + End_Of_Table_Com_TX_Remote);
	   /*%C adresse du tableau d'évènement */
	   SRCP2 = _sof_(&Array_Detailled_Monit); 	 
	    /*%C Pointeur destination  pointe sur le registre de transmission RS232 */
		DSTP2 = (UWORD16) &S0TBUF;
		/*%C autorisation de transmission */
		DRV_COM_End_of_Transmit = FALSE;
		S0TBIE = 1;
		S0TBIR = 1;	
		DRV_MONIT_Received_Data = 0;
		}

	 /* Fin de lecture Nand Flash */
 	 else if (DRV_NAND_End_Of_Read == TRUE )
	{
   	Array_Detailled_Monit [COM_TX_START_FRAME_1] = START_FRAME_COM_VALUE_1;
		Array_Detailled_Monit [COM_TX_START_FRAME_2] = START_FRAME_COM_VALUE_2;
		Array_Detailled_Monit [COM_TX_START_FRAME_3] = START_FRAME_COM_VALUE_3;

		/*%C End of tranmission byte Identification  				*/
   	Array_Detailled_Monit [COM_TX_ID_FRAME] = ID_END_OF_TRANSMISSION;
 		/*%C There's no data to tranmit								*/
 		Array_Detailled_Monit [COM_TX_DATA_FRAME] = 0x00; 	  		
		/*%C No CRC compute with this kind of frame					*/
 	  	Array_Detailled_Monit [COM_TX_MSB_CRC_FRAME] = 0x00; 
		Array_Detailled_Monit [COM_TX_LSB_CRC_FRAME] = 0x00; 		   
		/*%C Stop Frame bytes										*/
		Array_Detailled_Monit [COM_TX_END_FRAME_1] = END_FRAME_COM_VALUE_1;
		Array_Detailled_Monit [COM_TX_END_FRAME_2] = END_FRAME_COM_VALUE_2;
		Array_Detailled_Monit [COM_TX_END_FRAME_3] = END_FRAME_COM_VALUE_3;
   
		S0TBIR = 0;
		/* Origin index increasing - sending a byte */
 		PECC2 = 0x0500; 
		/* Size of detailled array to transmit	    */ 
 		PECC2 |= End_Of_Table_Com_TX_Remote;
		/*%C Origin index on trend array							*/
  	 	SRCP2 = _sof_(&Array_Detailled_Monit); 	
		/*%C Destination index on  RS232 transmit register	  		*/
  	 	DSTP2 = (UWORD16) &S0TBUF; 
  		/*%C Sending datas allowed									*/
  	 	DRV_COM_End_of_Transmit = FALSE;
  		S0TBIE = 1;
		S0TBIR = 1;
 		DRV_NAND_End_Of_Read = FALSE;
		/*%C End of transmition  				    							*/
	 	Communication_State = COM_TRANSMIT_STOP;
 	}
	else
	{
	 /*%C no function */
	}

   	
}
}
