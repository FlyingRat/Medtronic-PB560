/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_EEPROM_BAT_InitNewBattery.c                       	      */
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
#include "DB_EEPROM_BAT.h"
#include "DB_PowerSupply.h"
#include "DRV_EEPROM_BAT_Data.h"
#include "DRV_EEPROM_BAT_InitNewBattery.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void DRV_EEPROM_BAT_INIT_NEW_BATTERY(void)
{
	/*%C To identify the battery 																*/
	static UBYTE ID_INDEX=0;
	static UBYTE ID_AIROXSAFT[]="AIROXSAF";
	static UBYTE ID_AIROXACCUTRONICS[]="AIROXACC";
	UWORD16 LoopInit =0;

	/*%C Test the step of the init access memory	and quit the fonction.			*/	
	/*%C The next step of init will be at the next step of the scheduler		 	*/
	switch(STEP)
	{
		case RESET:
				/*%C Init the two array memory												*/
				for (	LoopInit = 0 ; 
						LoopInit < EEPROM_BAT_EnOfTableData ; 
						LoopInit++)
				{
					Ram_Read_Bat[LoopInit] = 0x00;
					if ( LoopInit >=  DATA_VARIABLE_BAT_AGEING_1)				
					{					
						Ram_Write_Bat[LoopInit - DATA_VARIABLE_BAT_AGEING_1] = 0x00;
					}
				} 
				/*%C It's a new battery	*/				
				DB_PowerSupply_Write(BAT_SUPPLIER, UNKNOWN_SUPPLIER);

				Flag_Answer_EEPROM_BAT = FALSE;
				/*%C Search the ID of the battery				  							*/
				TXREG1 = 0xE3; 			/*Command Mode										*/
				TXREG1 = 0xC5;
				STEP = WAIT_ANSWER_RESET_DS2480B;
				break;

		case 	WAIT_ANSWER_RESET_DS2480B:
			/*%C Test the answer	of the previuos request									*/
			if ( (Flag_Answer_EEPROM_BAT == TRUE)
			  && (Answer_EEPROM_BAT == 0xCD) )
			{
				Flag_Answer_EEPROM_BAT = FALSE;
				/*%C Search the ID of the battery				  							*/
				TXREG1 = 0xC1;				/* Send a Reset Pulse Command to TX			*/
				STEP = WAIT_INIT_ID_MEMORY_1;
			}
			/*%C No answer of the DS2480B or bad answer									*/
			else
			{
				/*%C Restart the init															*/
				STEP = RESET;
			}
			break;

	case 	WAIT_INIT_ID_MEMORY_1:
			/*%C Test the answer																	*/
			if ( (Flag_Answer_EEPROM_BAT == TRUE)
			  && ((Answer_EEPROM_BAT & 0xDF) == 0xCD) )
			{
				Flag_Answer_EEPROM_BAT = FALSE;
				/*%C Search the ID of the battery				  							*/
				TXREG1 = 0xE1;				/* Data Mode										*/
				TXREG1 = 0xCC;				/* Send a Skip ROM Command						*/
				STEP = WAIT_INIT_ID_MEMORY_2;
			}
			else
			{
				/*%C Restart the init															*/
				STEP = RESET;
			}
			break;

		case 	WAIT_INIT_ID_MEMORY_2:
			/*%C Test the answer																	*/
			if ( (Flag_Answer_EEPROM_BAT == TRUE)
			  && (Answer_EEPROM_BAT == 0xCC) )
			{
				Flag_Answer_EEPROM_BAT = FALSE;
				/*%C Search the ID of the battery				  							*/
				TXREG1 = 0xF0;				/* Command to read EEPROM						*/
				STEP = WAIT_INIT_ID_MEMORY_3;
			}
			else
			{
				/*%C Restart the init															*/
				STEP = RESET;
			}
			break;

		case 	WAIT_INIT_ID_MEMORY_3:
			/*%C Test the answer																	*/
			if (Flag_Answer_EEPROM_BAT == TRUE)
			{
				Flag_Answer_EEPROM_BAT = FALSE;
				/*%C Search the ID of the battery				  							*/
				TXREG1 = 0x00;				/* LSB of adress=0x00							*/
				STEP = WAIT_INIT_ID_MEMORY_4;
			}
			else
			{
				/*%C Restart the init															*/
				STEP = RESET;
			}
			break;

		case 	WAIT_INIT_ID_MEMORY_4:
			/*%C Test the answer																	*/
			if (Flag_Answer_EEPROM_BAT == TRUE)
			{
				Flag_Answer_EEPROM_BAT = FALSE;
				/*%C Search the ID of the battery				  							*/
				TXREG1 = 0x00;				/* MSB of adress=0x00							*/
				/*%C Initialize the pointer of the reading and writing storage array*/
				Ptr_Ram_MR = Ram_Read_Bat;	
				Ptr_Ram_MW = Ram_Write_Bat;
				ID_INDEX = 0;
				STEP = WAIT_INIT_ID_MEMORY_5;
			}
			else
			{
				/*%C Restart the init															*/
				STEP = RESET;
			}
			break;
	
		case 	WAIT_INIT_ID_MEMORY_5:
			/*%C Test the answer																	*/
			if (Flag_Answer_EEPROM_BAT == TRUE)
			{
				Flag_Answer_EEPROM_BAT = FALSE;
				/*%C get the first byte ID of the battery				  					*/
				TXREG1 = 0xFF;				/* Read a byte and adress++					*/
				STEP = WAIT_INIT_ID_MEMORY_6;
			}
			else
			{
				/*%C Restart the init															*/
				STEP = RESET;
			}
			break;
	
		case 	WAIT_INIT_ID_MEMORY_6:
			/*%C Test the answer	and the ID byte											*/
			if ( (Flag_Answer_EEPROM_BAT == TRUE) 
			  && (Answer_EEPROM_BAT == ID_AIROXSAFT[ID_INDEX]) )
			{
				Flag_Answer_EEPROM_BAT = FALSE;
				/*%C Check if the test of the ID is finish								*/
				if (ID_INDEX >= 7)
				{
					/*%C To finish the communication with the battery					*/
					TXREG1 = 0xE3;				/* Command Mode								*/
					ID_INDEX = 0;
					DB_PowerSupply_Write(COMMUNICATION_EEPROM_FAILURE,FALSE);
					/*%C Battery SAFT																*/
					DB_PowerSupply_Write(BAT_SUPPLIER, SAFT_SUPPLIER);
					/*%C After a init, we can read the data to the EEPROM				*/
					/*%C Initialize the pointer 												*/
					/*%C of the reading and writing storage array						*/
					Ptr_Ram_MR = Ram_Read_Bat;	
					Ptr_Ram_MW = Ram_Write_Bat;
					/*%C Flag=True because the next step is a frist reading			*/
					FirstRead = TRUE;
					STEP = RESET;
					State = READ;				
				}
				else
				{
					/*%C Test the next byte ID of the battery								*/
					ID_INDEX++;
					TXREG1 = 0xFF;				/* Read a byte and adress++				*/
					STEP = WAIT_INIT_ID_MEMORY_6;
				}
			}
			else if ( (Flag_Answer_EEPROM_BAT == TRUE) 
			  && (Answer_EEPROM_BAT == ID_AIROXACCUTRONICS[ID_INDEX]) )
			{
				Flag_Answer_EEPROM_BAT = FALSE;
				/*%C Check if the test of the ID is finish								*/
				if (ID_INDEX >= 7)
				{
					/*%C To finish the communication with the battery					*/
					TXREG1 = 0xE3;				/* Command Mode								*/
					ID_INDEX = 0;
					DB_PowerSupply_Write(COMMUNICATION_EEPROM_FAILURE,FALSE);
					/*%C Battery MOLTEC															*/
					DB_PowerSupply_Write(BAT_SUPPLIER, ACCUTRONICS_SUPPLIER);
					/*%C After a init, we can read the data to the EEPROM				*/
					/*%C Initialize the pointer 												*/
					/*%C of the reading and writing storage array						*/
					Ptr_Ram_MR = Ram_Read_Bat;	
					Ptr_Ram_MW = Ram_Write_Bat;
					/*%C Flag=True because the next step is a frist reading			*/
					FirstRead = TRUE;
					STEP = RESET;
					State = READ;				
				}
				else
				{
					/*%C Test the next byte ID of the battery								*/
					ID_INDEX++;
					TXREG1 = 0xFF;				/* Read a byte and adress++				*/
					STEP = WAIT_INIT_ID_MEMORY_6;
				}
			}
			else
			{
				/*%C Restart the init															*/
				STEP = RESET;
			}
			break;

		default :
			break ;
	}
}
