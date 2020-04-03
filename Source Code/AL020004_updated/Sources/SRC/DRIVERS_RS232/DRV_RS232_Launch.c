/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_RS232_launch.c                                             */
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

#include "p18f6622.h"
#include "typedef.h"
#include "enum.h"
#include "define.h"
#include "IO_Declare.h"
#include "DB_Control.h"
#include "DRV_RS232_Data.h"
#include "DRV_RS232_Launch.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void DRV_RS232_Launch(void)
{
	UBYTE Rs232Reg;	
	
	/*%C RECEIVE STATUS AND CONTROL REGISTER		  */
	/*%C bit 7 SPEN: Serial Port Enable bit : enabled = 1 							*/
	/*%C bit 6 RX9: 9-bit Receive Enable bit : 8 bits recpetion	= 0				*/
	/*%C bit 5 SREN: Single Receive Enable bit :0										*/
	/*%C bit 4 CREN: Continuous Receive Enable bit : enabled = 1					*/
	/*%C bit 3 ADDEN: Address Detect Enable bit : disabled = 0						*/
	/*%C bit 2 FERR: Framing Error bit : No error = 0									*/
	/*%C bit 1 OERR: Overrun Error bit : No error = 0									*/
	/*%C bit 0 RX9D: 9th bit of Received Data												*/
	/*%C RCSTA = 0b1001 0000																	*/
	/*%C Initialize COM on Overrun Error													*/
	if ((RCSTA2 & 0x02) > 0)
	{
		/*%C Disable Serial Port																*/
		RCSTA2 = 0x00;
		Rs232Reg	 = RCREG2;
		/*%C Enable Serial Port																	*/
		RCSTA2 = 0x90;
	}	
	/*%C Read buffer of reception 															*/
	DRV_RS232_ReadBuffer();
		
	/*%C Stop communication on time out of reception (DRV_RS232_TIME_OUT) 		*/
	if (TIM_ReadValue32(DRV_RS232_TIME_OUT) == 0)
	{
		/*%C Update the RS_232 state 															*/
		Rs232_State = DRV_RS232_TRANSMIT_STOP;
	}

	/*%C Stop the control on time out of control (DRV_RS232_CONTROL_TIME_OUT) 	*/
	if (TIM_ReadValue32(DRV_RS232_CONTROL_TIME_OUT) == 0)
	{
		/*%C Update the MAINTENANCE_CONTROL database flag								*/
		DB_Control_Write(MAINTENANCE_CONTROL,FALSE);
	}
	else
	{
		/*%C Update the MAINTENANCE_CONTROL database flag								*/
		DB_Control_Write(MAINTENANCE_CONTROL,TRUE);
	}

	/*%C Call the RS232 fonction 																*/
	switch (Rs232_State)
	{
		/*%C Call the transmition monitoring												*/
		case  DRV_RS232_TRANSMIT_MONITORING:
		{ 
			/*%C Transmit enabled 																*/
			TXSTA2 = 0x26;

			/*%C Start decounter transmit period 											*/
			if (TIM_ReadValue16(DRV_RS232_TRANSMIT_PERIOD) == 0)
			{
				/*%C Every DRV_RS232_TRANSMIT_PERIOD, transmit monitoring and		*/
				/*%C restart decounter 															*/
				DRV_RS232_TransmitMonit(); 
				TIM_StartDecounter16(DRV_RS232_TRANSMIT_PERIOD,
											RS232_MONITORING_PERIOD);
			}
			break;
		}
		/*%C Call the stop transmition 														*/
		case  DRV_RS232_TRANSMIT_STOP:  
		{
			/*%C Transmit disable and End of tranmit is right							*/
			TXSTA2 = 0x06;
			/*%C Update the end of transmit */
			EndOfTransmit = TRUE;
			break;
		}

		default:
		{
			break;
		}
	}	
}
