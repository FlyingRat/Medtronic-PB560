/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_RS232_Read_Buffer.c                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                      													  					*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/

#include "p18f6622.h"
#include "enum.h"
#include "IO_Declare.h"
#include "typedef.h"
#include "DB_Control.h"
#include "DB_PowerSupply.h"
#include "DRV_RS232_Data.h"
#include "DRV_RS232_ReadBuffer.h"
#include "define.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void DRV_RS232_ReadBuffer(void)
{
	
	UWORD16 ComputeCRC = 0;
	UBYTE Idx = 0;
	UBYTE i = 0;
	UWORD16 BufferOfReceiptId = 0;
	UWORD16 NoCommunicationCpu = DB_PowerSupply_Read(NO_COMMUNICATION_CPU);
	static UWORD16 MaintenanceControl = FALSE ;
	
	/*%C Search a complete frame 																*/


	/*%C If there are no data in the frame, quit the fonction 					*/
	if (PtrReadBufferRx == PtrWriteBufferRx) 
	{
		return;
	}
	

	/*%C While the data in the buffer is different to MSB_START_FRAME_VALUE	*/
	while ( 	(BufferOfReceipt[PtrReadBufferRx ]	!= MSB_START_FRAME_VALUE)
		  	&& (PtrReadBufferRx 							!= PtrWriteBufferRx))
	{
		/*%C Increment the pointer of the buffer of receipt 						*/
		PtrReadBufferRx = ((PtrReadBufferRx + 1) % RX_BufferSize);
	}
	
	/*%C Check if the frame is complete													*/
	if ( (RX_BufferSize - PtrReadBufferRx + PtrWriteBufferRx) % RX_BufferSize >= RX_EndOfFrame)
	{
		/*%C Check for rhe CRC value														*/
		ComputeCRC = 0;
	
		for (Idx = PtrReadBufferRx ; Idx != (PtrReadBufferRx + RX_CRC)%RX_BufferSize ; Idx = (Idx + 1) %RX_BufferSize)
		{
			/*%C Calcul of CRC (XOR)														*/
			ComputeCRC ^= (UBYTE)BufferOfReceipt[Idx];
		}
	
		/*%C Compare the CRC computing to the frame CRC byte 						*/
		if ( 	(BufferOfReceipt[(PtrReadBufferRx + RX_CRC) 					% RX_BufferSize]	== ComputeCRC) 
		  	&& (BufferOfReceipt[(PtrReadBufferRx + RX_END_FRAME) 			% RX_BufferSize]	== END_FRAME_VALUE) 
			&&	(BufferOfReceipt[(PtrReadBufferRx + RX_START_FRAME_MSB) 	% RX_BufferSize] 	== MSB_START_FRAME_VALUE)
	 			&& (BufferOfReceipt[(PtrReadBufferRx + RX_START_FRAME_LSB) 	% RX_BufferSize]	== LSB_START_FRAME_VALUE))
		{
			/*%C If CRC is ok, then the frame is ok 									*/
			/*%C Update each byte															*/	
			BufferOfReceiptId = (PtrReadBufferRx + RX_COMMAND)%RX_BufferSize;
				switch(BufferOfReceipt[BufferOfReceiptId])							
			{	
	
				/*%C Check the CMD_START_MONIT value 									*/
				case CMD_START_MONIT:
				{
					/*%C Start a decounter to verify the activity 					*/
					/*%C on reception 														*/
					TIM_StartDecounter32(DRV_RS232_TIME_OUT,
												RS232_TIME_OUT_WAIT);
					/*%C Update RS_232 state 												*/
					Rs232_State = DRV_RS232_TRANSMIT_MONITORING;
					break;
				}
	
				/*%C Check the CMD_STOP_COM value 										*/
				case CMD_STOP_COM:
				{
					/*%C Update RS_232 state 												*/
					Rs232_State = DRV_RS232_TRANSMIT_STOP;
					break;
				}
	
				/*%C Check the CMD_CONTROL value 										*/
				case CMD_CONTROL:
				{
					/*%C Start a decounter to verify the activity 					*/
					/*%C on control reception 												*/
					TIM_StartDecounter32(DRV_RS232_CONTROL_TIME_OUT,
												RS232_CONTROL_TIME_OUT_WAIT);
					/*%C Allowed the control if 											*/
					/*%C CommunicationFailureFlag = FALSE								*/
					if (NoCommunicationCpu == TRUE)
					{
						/*%C Allowed MAINTENANCE_CONTROL 								*/
						DB_Control_Write(MAINTENANCE_CONTROL,TRUE);
						TIM_StartDecounter32(DRV_RS232_TIME_OUT,
														RS232_TIME_OUT_WAIT);
						/*%C Update RS_232 state 											*/
						Rs232_State = DRV_RS232_TRANSMIT_MONITORING;
					}
					else
					{
						/*%C Prohibit MAINTENANCE_CONTROL								*/
						DB_Control_Write(MAINTENANCE_CONTROL,FALSE);
					}
				
					/* Update the MAINTENANCE_CONTROL flag 							*/
					MaintenanceControl = DB_Control_Read(MAINTENANCE_CONTROL);
					break;
				}
				
	
	
	/*C% All the next command are allowed if the MAINTENANCE_CONTROL flag is true */
	
	
				/*%C Check the CMD_COMMUT_CH value 										*/
				case CMD_COMMUT_CH:
				{
					if(MaintenanceControl == TRUE)
					{
						/*%C Update the COMMUT_CHARGEUR value 							*/
						COMMUT_CHARGEUR = BufferOfReceipt[
													(PtrReadBufferRx + RX_PARAM1)
													%RX_BufferSize];
					}
					/*%C else, no change */
					break;
				}	
			
				/*%C Check the CMD_SHUNT_DIODE_CH value 								*/
				case CMD_SHUNT_DIODE_CH:
				{
					if(MaintenanceControl == TRUE)
					{
						/*%C Update the SHUNT_DIODE_CHARGEUR value 					*/
						SHUNT_DIODE_CHARGEUR = BufferOfReceipt[
														(PtrReadBufferRx + RX_PARAM1)
														%RX_BufferSize];
					}
					/*%C else, no change */
					break;
				}	
			
				/*%C Check the CMD_COMMUT_BAT value 									*/
				case CMD_COMMUT_BAT:
				{
					if(MaintenanceControl == TRUE)
					{
						/*%C Update the COMMUT_BAT value 								*/
						COMMUT_BAT = BufferOfReceipt[
											(PtrReadBufferRx + RX_PARAM1)
											%RX_BufferSize];
					}
					/*%C else, no change */
					break;
				}	
			
				/*%C Check the CMD_SHUNT_DIODE_BAT value 								*/
				case CMD_SHUNT_DIODE_BAT:
				{
					if (MaintenanceControl == TRUE)
					{
						/*%C Update the SHUNT_DIODE_BAT value 							*/
						SHUNT_DIODE_BAT = BufferOfReceipt[
													(PtrReadBufferRx + RX_PARAM1)
													%RX_BufferSize];
					}
					/*%C else, no change */
					break;
				}	
			
				/*%C Check the CMD_COMMUT_DC value 										*/
				case CMD_COMMUT_DC:
				{
					if(MaintenanceControl == TRUE)
					{
						/*%C Update the COMMUT_DC value 									*/
						COMMUT_DC = BufferOfReceipt[
											(PtrReadBufferRx + RX_PARAM1)
											%RX_BufferSize];
					}
					/*%C else, no change */
					break;
				}		
	
				/*%C Check the CMD_SHUNT_DIODE_DC value 								*/
				case CMD_SHUNT_DIODE_DC:
				{
					if(MaintenanceControl == TRUE)
					{
						/*%C Update the SHUNT_DIODE_DC value 							*/
						SHUNT_DIODE_DC = BufferOfReceipt[
												(PtrReadBufferRx + RX_PARAM1)
												%RX_BufferSize];
					}
					/*%C else, no change */
					break;
				}		
	
				/*%C Check the CMD_COMMUT_AC value 										*/
				case CMD_COMMUT_AC:
				{
					if(MaintenanceControl == TRUE)
					{
						/*%C Update the COMMUT_AC value 									*/
						COMMUT_AC = BufferOfReceipt[
											(PtrReadBufferRx + RX_PARAM1)
											%RX_BufferSize];
					}
					/*%C else, no change */
					break;
				}		
	
				/*%C Check the CMD_SHUNT_DIODE_AC value 								*/
				case CMD_SHUNT_DIODE_AC:
				{
					if (MaintenanceControl == TRUE)
					{
						/*%C Update the SHUNT_DIODE_AC value 							*/
						SHUNT_DIODE_AC = BufferOfReceipt[
												(PtrReadBufferRx + RX_PARAM1)
												%RX_BufferSize];
					}
					/*%C else, no change */
					break;
				}		
	
				/*%C Check the CMD_LED_PRESENCE_AC value 								*/
				case CMD_LED_PRESENCE_AC:
				{
					if(MaintenanceControl == TRUE)
					{
						/*%C Update the PRESENCE_AC value 								*/
						PRESENCE_AC = BufferOfReceipt[
											(PtrReadBufferRx + RX_PARAM1)
											%RX_BufferSize];
					}
					/*%C else, no change */
					break;
				}		
				
				/*%C Check the CMD_LED_ETAT_BAT value 									*/
				case CMD_LED_ETAT_BAT:
				{
					if(MaintenanceControl == TRUE)
					{
						/*%C Update the LED_ETAT_BAT value 								*/
						LED_ETAT_BAT = BufferOfReceipt[
												(PtrReadBufferRx + RX_PARAM1)
												%RX_BufferSize];
					}
					/*%C else, no change */
					break;
				}		
	
				/*%C Check the CMD_VENTIL value 											*/
				case CMD_VENTIL:
				{
					if(MaintenanceControl == TRUE)
					{
						/*%C Update the PWM_V_Ventil value 								*/
						PWM_CMD_VENTIL = 	(BufferOfReceipt[
													(PtrReadBufferRx 
													+ RX_PARAM1 )%RX_BufferSize]);
					}
					/*%C else, no change */
					break;
				}		
	
				/*%C Check the CMD_COMMUT_IFC value 									*/
				case CMD_COMMUT_IFC:
				{
					if(MaintenanceControl == TRUE)
					{
						/*%C Update the COMMUT_IFC value 								*/
						COMMUT_IFC = BufferOfReceipt[
												(PtrReadBufferRx + RX_PARAM1)
												%RX_BufferSize];
					}
					/*%C else, no change */
					break;
				}	
	
				/*%C Check the CMD_REGLAGE_VCHARGE value 								*/
				case CMD_REGLAGE_VCHARGE:
				{
					if(MaintenanceControl == TRUE)
					{
						/*%C Update the PWM_V_Charge value 								*/
						SAM_PWM_Conversion(BufferOfReceipt[
													(PtrReadBufferRx + RX_PARAM1)
													%RX_BufferSize]
													, PWM_V_Charge);
					}
					/*%C else, no change */
					break;
				}	
	
				/*%C Check the CMD_REGLAGE_ICHARGE value 								*/
				case CMD_REGLAGE_ICHARGE:
				{
					if(MaintenanceControl == TRUE)
					{
						/*%C Update the PWM_I_Charge value 								*/
						SAM_PWM_Conversion(BufferOfReceipt[
													(PtrReadBufferRx + RX_PARAM1)
													%RX_BufferSize]
													, PWM_I_Charge);
					}
					/*%C else, no change */
					break;
				}	
	
	
				/*%C Check the CMD_RESET_CPU value 										*/
				case CMD_RESET_CPU:
				{
	
					if ((BufferOfReceipt[(PtrReadBufferRx + RX_PARAM1)
							%RX_BufferSize] == 0x55)
						&& (BufferOfReceipt[(PtrReadBufferRx + RX_PARAM2)
							%RX_BufferSize] == 0xAA))
					{
						/*%C Reset 																*/
						_asm
						RESET
						_endasm
					}
				/*%C else, no change */
				break;	
				}
									
				/*%C In case default 														*/	
				default :	
				{
					break;
				}
			}
	
			/*%C Increment the pointer to read the next frame						*/
			PtrReadBufferRx = (PtrReadBufferRx + RX_EndOfFrame ) % RX_BufferSize;
		}	
		else
		{
			/*%C Increment the pointer 														*/
			PtrReadBufferRx = (PtrReadBufferRx + 1) % RX_BufferSize;
		}
	}
}

