/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_COM_Treament_Buffer.c                         		*/
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
#include "LH_ST10F276.h"
#else
#include "regf276e.h"
#endif	 
#include "typedef.h"
#include "enum.h"
#include "define.h"
#include "Structure.h"
#include "DB_Control.h"
#include "Flash_Monit_Data.h"
#include "Timer_Data.h"
#include "DRV_COM_Data.h"
#include "DRV_COM_Treatment_Buffer.h"
#include "Driver_USB_Data.h"





/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_COM_Treatment_Buffer(void)
{
	UBYTE Compteur = 0;
	
   	switch (DRV_COM_Buffer_Of_Receipt[(DRV_COM_Ptr_Read_Buffer_Rx + COM_RX_COMMAND) % COM_RX_BufferSize])							
		{	
			case CMD_START_TRANSMIT_EVENT_FRAME:
		
	  			DRV_TREND_Read_Request = ENDED;
	  			DRV_MONIT_Read_Request = ENDED;
				num_event = 1;
	  			DRV_COM_End_of_Transmit = TRUE;
			   	Communication_State = COM_TRANSMIT_RETRIEVAL;
		  		adr_flash_retrieval = (UWORD16 xhuge *)DRV_EVENT_TransPtrMemory();
				break;
			
			case CMD_STOP_TRANSMIT_EVENT_FRAME:
			
	  			DRV_TREND_Read_Request = ENDED;
	  			DRV_MONIT_Read_Request = ENDED;
 				Communication_State = COM_TRANSMIT_STOP;
				break;
			
			case CMD_START_TRANSMIT_MONITORING_FRAME:
			
	  			DRV_TREND_Read_Request = ENDED;
	  			DRV_MONIT_Read_Request = ENDED;
				DRV_COM_End_of_Transmit = TRUE;
				Communication_State = COM_TRANSMIT_MONITORING;
				TIM_StartDecounter(TIM_COM_RECORDING_MONIT,TIME_RECORDING_MONIT);
				break;
			
			case CMD_STOP_TRANSMIT_MONITORING_FRAME:
		
	  			DRV_TREND_Read_Request = ENDED;
	  			DRV_MONIT_Read_Request = ENDED;
 				Communication_State = COM_TRANSMIT_STOP;
				break;
			
			case CMD_START_TRANSMIT_TENDANCE_FRAME:
				if(UsbFlashTrasnferRunning == USB_NAND_TRANSFER_IDLE)
				{
		  			DRV_MONIT_Read_Request = ENDED;
					if ( DRV_TREND_Read_Request == ENDED)
					{
						DRV_TREND_Read_Request = REQUEST;
						DRV_COM_End_of_Transmit = TRUE;
					   	Communication_State = COM_TRANSMIT_TENDANCE;
						DRV_NAND_End_Of_Read = FALSE;
					}
				}
				break;
		
			case CMD_STOP_TRANSMIT_TENDANCE_FRAME:
	  			DRV_MONIT_Read_Request = ENDED;
				if(Communication_State != COM_TRANSMIT_STOP)
				{
					Communication_State = COM_TRANSMIT_STOP;
					DRV_TREND_Read_Request = ENDED;
					UsbFlashTrasnferRunning = USB_NAND_TRANSFER_IDLE;
				}
				break;
			
			case CMD_START_TRANSMIT_DETAILLED_MONITORING_FRAME:
				if(UsbFlashTrasnferRunning == USB_NAND_TRANSFER_IDLE)
				{
		  			DRV_TREND_Read_Request = ENDED;
					if ( DRV_MONIT_Read_Request == ENDED)
					{
						DRV_COM_End_of_Transmit = TRUE;
				 		Communication_State = COM_TRANSMIT_DETAILLED_MONITORING;
				 		DRV_MONIT_Read_Request = REQUEST;
						DRV_NAND_End_Of_Read = FALSE;
					}
				}
				break;

			case CMD_START_TRANSMIT_DETAILLED_MONITORING_ON_KEY:
				DRV_COM_End_of_Transmit = TRUE;
				Communication_State = COM_TRANSMIT_MONITORING_TO_KEY;
				break;	
						
			case CMD_STOP_TRANSMIT_DETAILLED_MONITORING_FRAME:
	  			DRV_TREND_Read_Request = ENDED;
				if(Communication_State != COM_TRANSMIT_STOP)
				{
					Communication_State = COM_TRANSMIT_STOP;
					DRV_MONIT_Read_Request = ENDED;
					UsbFlashTrasnferRunning = USB_NAND_TRANSFER_IDLE;
				}
				break;
			
			case CMD_TRANSMIT_SERIAL_NUMBER:
	  			DRV_TREND_Read_Request = ENDED;
	  			DRV_MONIT_Read_Request = ENDED;
				DRV_COM_End_of_Transmit = TRUE;
				Communication_State = COM_TRANSMIT_IDENTIFICATION_DEVICE;
				break;
		
			case CMD_RECEIVE_SERIAL_NUMBER:
	  			DRV_TREND_Read_Request = ENDED;
	  			DRV_MONIT_Read_Request = ENDED;
		  		for (Compteur = 0; Compteur < COM_ID_BUFFER_SIZE ; Compteur ++)
				{
					DRV_COM_Receive_ID_Buffer[Compteur % COM_ID_BUFFER_SIZE] 
						= DRV_COM_Buffer_Of_Receipt[(DRV_COM_Ptr_Read_Buffer_Rx + COM_RX_COMMAND + Compteur + 1) % COM_RX_BufferSize];
				}	
				Communication_State = COM_RECEIVE_IDENTIFICATION_DEVICE;
				break;
		
			case CMD_TRANSMIT_MACHINE_COUNTER:
	  			DRV_TREND_Read_Request = ENDED;
	  			DRV_MONIT_Read_Request = ENDED;
				DRV_COM_End_of_Transmit = TRUE;
				Communication_State = COM_TRANSMIT_MACHINE_COUNTER;
				break;
			
			case CMD_RECEIVE_MACHINE_COUNTER:
	  			DRV_TREND_Read_Request = ENDED;
	  			DRV_MONIT_Read_Request = ENDED;
				DRV_COM_Machine_Counter_Value_MSB
					= DRV_COM_Buffer_Of_Receipt[(DRV_COM_Ptr_Read_Buffer_Rx+ COM_RX_COMMAND + 1) % COM_RX_BufferSize];
				DRV_COM_Machine_Counter_Value_LSB 
					= DRV_COM_Buffer_Of_Receipt[(DRV_COM_Ptr_Read_Buffer_Rx+ COM_RX_COMMAND + 2) % COM_RX_BufferSize];
				Communication_State = COM_RECEIVE_MACHINE_COUNTER;
				break;

			case CMD_TRANSMIT_DATABASE:
	  			DRV_TREND_Read_Request = ENDED;
	  			DRV_MONIT_Read_Request = ENDED;
				for(Compteur = 0; Compteur < 2 * DRV_COM_NbParamDb ; Compteur++)
				{				
					DRV_COM_Database_Parameter[Compteur] 
						= DRV_COM_Buffer_Of_Receipt[(DRV_COM_Ptr_Read_Buffer_Rx + COM_RX_COMMAND + 2 + Compteur) % COM_RX_BufferSize];
				}
				DRV_COM_End_of_Transmit = TRUE;
				DRV_COM_Transmit_Database_Full_Speed = FALSE;
				Communication_State = COM_TRANSMIT_DATABASE;
				break;
		
			case CMD_TRANSMIT_DATABASE_FULL_SPEED:
	  			DRV_TREND_Read_Request = ENDED;
	  			DRV_MONIT_Read_Request = ENDED;			
	  			for(Compteur = 0; Compteur < 2 * DRV_COM_NbParamDb ; Compteur++)
				{				
					DRV_COM_Database_Parameter[Compteur] 
						= DRV_COM_Buffer_Of_Receipt[(DRV_COM_Ptr_Read_Buffer_Rx + COM_RX_COMMAND + 2 + Compteur) % COM_RX_BufferSize];
				}
				DRV_COM_End_of_Transmit = TRUE;
				DRV_COM_Transmit_Database_Full_Speed = TRUE;
				Communication_State = COM_TRANSMIT_DATABASE;
				break;
		
			case CMD_RECEIVE_DATABASE:
	  			DRV_TREND_Read_Request = ENDED;
	  			DRV_MONIT_Read_Request = ENDED;
				DRV_COM_Database_Id	= DRV_COM_Buffer_Of_Receipt[(DRV_COM_Ptr_Read_Buffer_Rx	+ COM_RX_COMMAND + 1)% COM_RX_BufferSize]; 
				DRV_COM_Database_Data
					= DRV_COM_Buffer_Of_Receipt[(DRV_COM_Ptr_Read_Buffer_Rx + COM_RX_COMMAND + 2) % COM_RX_BufferSize];
				DRV_COM_Database_Value_MSB 
					= DRV_COM_Buffer_Of_Receipt[(DRV_COM_Ptr_Read_Buffer_Rx	+ COM_RX_COMMAND + 3) % COM_RX_BufferSize];
				DRV_COM_Database_Value_LSB 
					= DRV_COM_Buffer_Of_Receipt[(DRV_COM_Ptr_Read_Buffer_Rx	+ COM_RX_COMMAND + 4) % COM_RX_BufferSize];					 
				DRV_COM_Database_Value_CRC
					= DRV_COM_Buffer_Of_Receipt[(DRV_COM_Ptr_Read_Buffer_Rx	+ COM_RX_COMMAND + 5) % COM_RX_BufferSize]; 
			   	DRV_COM_End_of_Transmit = TRUE;
				Communication_State = COM_RECEIVE_DATABASE;
				break;
		
	 		case CMD_COM_READY:
	  			DRV_TREND_Read_Request = ENDED;
	  			DRV_MONIT_Read_Request = ENDED;
				 Communication_State = COM_READY;
			 	 break;
		
			case CMD_READ_EEPROM:	
	  			DRV_TREND_Read_Request = ENDED;
	  			DRV_MONIT_Read_Request = ENDED;
				S0TBIE = 0;
				DRV_COM_End_of_Transmit = TRUE;
				EepromDataRead = (UBYTE xhuge *) &EepromData;
				Communication_State = COM_READ_EEPROM;
				break;
		
			case CMD_START_TRANSMIT_SETTINGS_FRAME:	
	  			DRV_TREND_Read_Request = ENDED;
	  			DRV_MONIT_Read_Request = ENDED;
				S0TBIE = 0;
				DRV_COM_End_of_Transmit = TRUE;
				Communication_State = COM_TRANSMIT_SETTINGS;
				break;
		
			case CMD_STOP_TRANSMIT_SETTINGS_FRAME:	
	  			DRV_TREND_Read_Request = ENDED;
	  			DRV_MONIT_Read_Request = ENDED;
				Communication_State = COM_TRANSMIT_STOP;
				break;
		
			default:
			
				break;
			
		 }

}