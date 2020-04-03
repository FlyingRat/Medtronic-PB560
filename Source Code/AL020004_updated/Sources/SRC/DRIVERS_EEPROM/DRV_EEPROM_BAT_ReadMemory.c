/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_EEPROM_BAT_ReadMemory.c                                    */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           	Read the 64 bytes of the EEPROM Battery 							*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/

#include "p18f6622.h"
#include "typedef.h"
#include "enum.h"
#include "DB_PowerSupply.h"
#include "DRV_EEPROM_BAT_Data.h"
#include "DB_EEPROM_BAT.h"
#include "DRV_EEPROM_BAT_Read.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void DRV_EEPROM_BAT_ReadMemory(void)
{
	/*%C Test the step of the read access memory	and quit the fonction.			*/	
	/*%C The next step of reading will be at the next step of the scheduler 	*/
	switch(STEP)
	{
		/*%C Send a reset pulse (EUSART 1) to the EEPROM Battery						*/ 
		case RESET:
			Flag_Answer_EEPROM_BAT = FALSE;
			/*%C Send a Reset Pulse Command (0xC1) to TX									*/
			TXREG1 = 0xC1;
			/*%C Next step of reading															*/
			STEP=WAIT_ANSWER_RESET;
			break;
		
		/*%C Read the answer of the Reset Pulse											*/
		case WAIT_ANSWER_RESET:
			/*%C Check condition to continue or stop the reading of the EEPROM:	*/
			/*%C When the answer is CD or ED, we continue to read				 		*/
			if ( (Flag_Answer_EEPROM_BAT == TRUE) 
			  && ((Answer_EEPROM_BAT & 0xDF)==0xCD) )
			{
				/*%C Send a Data Mode Command (0xE1) to TX								*/
				TXREG1 = 0xE1;
				/*%C Next step of reading															*/
				STEP=DATA_MODE;
			}
			/*%C If the answer isn't CD or ED, we stop the reading					*/
			else
			{
				STEP=RESET;
			}
			break;
		
		case	DATA_MODE:
			Flag_Answer_EEPROM_BAT=FALSE;
			/*%C Send a Skip ROM Command (0xCC) to TX										*/
			TXREG1 = 0xCC;
			/*%C Next step of reading															*/
			STEP = WAIT_ANSWER_SKIP_COMMAND;
			break;
		
		/*%C Read the answer of the Skip Rom Command										*/
		case WAIT_ANSWER_SKIP_COMMAND:
			/*%C Check condition to continue or stop the reading of the EEPROM:	*/
			/*%C When the answer is CC, we continue to read				 				*/
			if(Flag_Answer_EEPROM_BAT==TRUE && Answer_EEPROM_BAT==0xCC)
			{
				/*%C Send a Read EEPROM Command (0xF0) to TX								*/
				TXREG1 = 0xF0;
				/*%C Next step of reading														*/
				STEP=WRITE_ADRESS_LSB;
			}
			/*%C If the answer isn't CC, we stop the reading							*/
			else
			{
				STEP=RESET;
			}
			break;

		/*%C Send the LSB of the adress to the EEPROM Battery							*/ 
		case WRITE_ADRESS_LSB:
			/*%C LSB of adress = 0x00															*/
			TXREG1 = 0x00;
			/*%C Next step of reading															*/
			STEP=WRITE_ADRESS_MSB;
			break;

		/*%C Send the MSB of the adress to the EEPROM Battery							*/ 
		case WRITE_ADRESS_MSB:
			/*%C MSB of adress = 0x00															*/
			TXREG1 = 0x00;
			/*%C Next step of reading															*/
			STEP=START_READ_DATA;
			break;
			
		/*%C Read the fisrt byte of the memory												*/
		case START_READ_DATA:
			/*%C Send a Read Data Command (0xFF) to TX									*/
			TXREG1 = 0xFF;
			/*%C Next step of reading															*/
			STEP=READ_DATA;
			/*%C Initialize the pointer of the reading and writing storage array*/
			Ptr_Ram_MR = Ram_Read_Bat;	
			Ptr_Ram_MW = Ram_Write_Bat;
			break;

		/*%C Store the reading byte and read the next byte of the memory			*/
		case READ_DATA:
			/*%C Store the reading byte														*/
			*Ptr_Ram_MR = Answer_EEPROM_BAT;
			/*%C Test if it's a first Read of the memory									*/
			if ( (Ptr_Ram_MR >= Ram_Read_Bat + DATA_VARIABLE_BAT_AGEING_1)
			  && (FirstRead == TRUE) )
			{
				/*%C Init of the writing storage array										*/ 
				*Ptr_Ram_MW = Answer_EEPROM_BAT;
				Ptr_Ram_MW++;
			}
			/*%C Increment the pointer	of reading											*/
			Ptr_Ram_MR++;
			/*%C Send a Read Data Command (0xFF) to read the next byte				*/
			TXREG1 = 0xFF;
			/*%C Test if we read all data of the memory									*/
			if (Ptr_Ram_MR >= Ram_Read_Bat + EEPROM_BAT_EnOfTableData)
			{
				/*%C Send a Command Mode (0xE3) to TX										*/
				TXREG1 = 0xE3;
				/*%C Flag of Reading EEPROM Failure = False 								*/
				/*%C on the Power_Suply Data Base											*/
				DB_PowerSupply_Write(READ_DATA_EEPROM_BAT_FAILURE, FALSE);
				/*%C Next step of reading														*/
				STEP = RESET;
				/*%C After a reading, we can write the data to the EEPROM			*/
				State = WRITE;
				/*%C Flag=False after a first read memory									*/
				FirstRead = FALSE;
			}
			break;
		default :
			break ;
	}
}
