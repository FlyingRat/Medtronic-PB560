/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_EEPROM_BAT_WriteMemoty.c                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C            Write the 32 bytes of the EEPROM Battery  							*/
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
#include "define.h"
#include "DB_PowerSupply.h"
#include "DRV_EEPROM_BAT_Data.h"
#include "DB_EEPROM_BAT.h"
#include "DRV_EEPROM_BAT_Write.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void DRV_EEPROM_BAT_WriteMemory(void)
{
	static UBYTE Adress_LSB = 0x20;
	static UBYTE BLOCK = 0;
	static e_BOOL Flag_Scratchpad_Full = FALSE;
	static UWORD16 CRC_EEPROM_BAT = 0;

	/*%C Test the step of the write access memory	and quit the fonction.		*/	
	/*%C The next step of writing will be at the next step of the scheduler 	*/
	switch(STEP)
	{
		/*%C Send a reset pulse (EUSART 1) to the EEPROM Battery						*/ 
		case RESET:
			Flag_Answer_EEPROM_BAT=FALSE;
			/*%C Send a Reset Pulse Command (0xC1) to TX									*/
			TXREG1 = 0xC1;
			/*%C Next step of writing															*/
			STEP = WAIT_ANSWER_RESET;
			break;

		/*%C Read the answer of the Reset Pulse											*/
		case WAIT_ANSWER_RESET:
			/*%C Check condition to continue or stop the writing of the EEPROM:	*/
			/*%C When the answer is CD or ED, we continue to write			 		*/
			if ( (Flag_Answer_EEPROM_BAT == TRUE)
			  && ((Answer_EEPROM_BAT & 0xDF)==0xCD) )
			{
				/*%C Send a Data Mode Command (0xE1) to TX								*/
				TXREG1 = 0xE1;
				/*%C Next step of writing														*/
				STEP = DATA_MODE;
			}
			else
			{
				/*%C If the answer isn't CD or ED, we stop the writing				*/
				STEP = STEP_END;
			}
			break;
		
		case	DATA_MODE:
			Flag_Answer_EEPROM_BAT=FALSE;
			/*%C Send a Skip ROM Command (0xCC) to TX										*/
			TXREG1 = 0xCC;
			/*%C Next step of writing															*/
			STEP = WAIT_ANSWER_SKIP_COMMAND;
			break;
		
		/*%C Read the answer of the Skip Rom Command										*/
		case WAIT_ANSWER_SKIP_COMMAND:
			/*%C Check condition to continue or stop the writing of the EEPROM:	*/
			/*%C When the answer is CC, we continue to write				 			*/
			if ( (Flag_Answer_EEPROM_BAT == TRUE)
			  && (Answer_EEPROM_BAT == 0xCC) )
			{
				/*%C Send a Write Scratchpad EEPROM Command (0x0F) to TX				*/
				TXREG1 = 0x0F;
				/*%C Initialise the CRC value													*/
				CRC_EEPROM_BAT = 0;
				/*%C Compute the CRC																*/
				CRC_EEPROM_BAT = CRC16_Table[(UBYTE)CRC_EEPROM_BAT ^ 0x0F] ^ (UBYTE)(CRC_EEPROM_BAT>>8);
				/*%C Next step of writing														*/
				STEP = WRITE_ADRESS_LSB;
			}
			else
			{
				/*%C If the answer isn't CD or ED, we stop the writing				*/	
				STEP=STEP_END;
			}
			break;

		/*%C Send the LSB of the adress to the scratchpad								*/ 
		case WRITE_ADRESS_LSB:
			/*%C LSB of adress = 0x20 or 0x28 or 0x30 or 0x38							*/
			TXREG1 = Adress_LSB;		
			/*%C Compute the CRC																	*/
			CRC_EEPROM_BAT=CRC16_Table[(UBYTE)CRC_EEPROM_BAT ^ Adress_LSB] ^ (UBYTE)(CRC_EEPROM_BAT>>8);
			/*%C Next step of writing															*/		
			STEP = WRITE_ADRESS_MSB;
			break;

		/*%C Send the MSB of the adress to the scratchpad								*/ 
		case WRITE_ADRESS_MSB:
			/*%C MSB of adress = 0x00															*/
			TXREG1 = 0x00;
			/*%C Compute the CRC																	*/
			CRC_EEPROM_BAT=CRC16_Table[(UBYTE)CRC_EEPROM_BAT ^ 0x00] ^ (UBYTE)(CRC_EEPROM_BAT>>8);
			/*%C Next step of writing															*/		
			STEP = WRITE_BLOCK;
			break;
		
		/*%C Write 8 byte on the scratchpad													*/	
		case WRITE_BLOCK:
			/*%C If the scratchpad isn't full, send a data to the scratchpad		*/
			if (Flag_Scratchpad_Full==FALSE)
			{
				/*%C Send a byte to the scratchpad											*/
				TXREG1 = *Ptr_Ram_MW;
				/*%C Compute the CRC																*/
				CRC_EEPROM_BAT=CRC16_Table[(UBYTE)CRC_EEPROM_BAT ^ (*Ptr_Ram_MW)] ^ (UBYTE)(CRC_EEPROM_BAT>>8);
				/*%C Increment the pointer	of writng										*/
				Ptr_Ram_MW++;
				/*%C Check if the 8 bytes were sent 										*/
				if (((Ptr_Ram_MW-Ram_Write_Bat)%8)==0)
				{
					Flag_Scratchpad_Full=TRUE;
					/*%C Next step of writing													*/		
					STEP_COPY=CHECK_CRC_LSB;
				}
			}
			/*%C The scratchpad is full. Copy the scratchpad on the memory			*/
			else
			{
				switch(STEP_COPY)
				{
					/*%C Check if the LSB of the CRC is OK									*/
					case CHECK_CRC_LSB:
						Flag_Answer_EEPROM_BAT=FALSE;
						/*%C We finish to compute the CRC									*/
						CRC_EEPROM_BAT=~CRC_EEPROM_BAT;
						/*%C Send a Read Command to read the LSB of the CRC			*/
						TXREG1 = 0xFF;
						/*%C Next step of writing												*/		
						STEP_COPY=WAIT_ANSWER_CRC_LSB;
						break;
					
					/*%C Read the answer of the Read CRC Command							*/
					case WAIT_ANSWER_CRC_LSB:
						/*%C if the two values (computed value and read value) 		*/
						/*%C	are the same, we continue to write in the memory		*/
						if ( (Flag_Answer_EEPROM_BAT == TRUE)
						  && (Answer_EEPROM_BAT == (UBYTE)CRC_EEPROM_BAT) )
						{
							/*%C Next step of writing											*/		
							STEP_COPY=CHECK_CRC_MSB;
						}
						/*%C else, the two values are different 							*/
						/*%C  we stop writing in the memory								*/
						else
						{
							STEP=STEP_END;
						}
						break;

					/*%C Check if the MSB of the CRC is OK									*/
					case CHECK_CRC_MSB:
						Flag_Answer_EEPROM_BAT=FALSE;
						/*%C Send a Read Command to read the MSB of the CRC			*/
						TXREG1 = 0xFF;
						/*%C Next step of writing												*/		
						STEP_COPY=WAIT_ANSWER_CRC_MSB;
						break;

					/*%C Read the answer of the Read CRC Command							*/
					case WAIT_ANSWER_CRC_MSB:
						/*%C if the two values (computed value and read value) 		*/
						/*%C	are the same, we continue to write in the memory		*/
						if ( (Flag_Answer_EEPROM_BAT == TRUE)
						  && (Answer_EEPROM_BAT == (UBYTE)(CRC_EEPROM_BAT>>8)) )
						{
							/*%C Next step of writing											*/		
							STEP_COPY=COMMAND_MODE_COPY;
						}
						/*%C if the two values are different 								*/
						/*%C  we stop to write in the memory								*/
						else
						{
							STEP=STEP_END;
						}
						break;

					case COMMAND_MODE_COPY:
						/*%C Send a Command Mode (0xE3) to TX								*/
						TXREG1 = 0xE3;
						/*%C Next step of writing												*/		
						STEP_COPY=RESET_COPY;
						break;

					/*%C Send a reset pulse to copy the scratchpad on the memory	*/ 
					case RESET_COPY:
						Flag_Answer_EEPROM_BAT=FALSE;
						/*%C Send a Reset Pulse Command (0xC1) to TX						*/
						TXREG1 = 0xC1;				
						/*%C Next step of writing												*/		
						STEP_COPY=WAIT_ANSWER_RESET_COPY;
						break;
					
					/*%C Read the answer of the Reset Pulse								*/
					case WAIT_ANSWER_RESET_COPY:
						/*%C Check condition to continue or stop the writing of the EEPROM:	*/
						/*%C When the answer is CD or ED, we continue to write			 		*/
						if ( (Flag_Answer_EEPROM_BAT == TRUE)
						  && ((Answer_EEPROM_BAT & 0xDF) == 0xCD) )
						{
							/*%C Send a Data Mode Command (0xE1) to TX					*/
							TXREG1 = 0xE1;
							/*%C Next step of writing											*/	
							STEP_COPY=DATA_MODE_COPY;
						}
						/*%C If the answer isn't CD or ED, we stop the writing	*/
						else
						{
							STEP=STEP_END;
						}
						break;
			
					case	DATA_MODE_COPY:
						Flag_Answer_EEPROM_BAT=FALSE;
						/*%C Send a Skip ROM Command (0xCC) to TX							*/
						TXREG1 = 0xCC;
						/*%C Next step of writing												*/	
						STEP_COPY=WAIT_ANSWER_SKIP_COPY;
						break;

					/*%C Read the answer of the Skip Rom Command							*/
					case WAIT_ANSWER_SKIP_COPY:
						/*%C Check condition to continue or stop the writing of the EEPROM:	*/
						/*%C When the answer is CC, we continue to write		 		*/
						if ( (Flag_Answer_EEPROM_BAT == TRUE)
						  && (Answer_EEPROM_BAT == 0xCC) )
						{
							/*%C Send a Copy Scratchpad Command (0x55) to TX			*/
							TXREG1 = 0x55;
							/*%C Next step of writing											*/	
							STEP_COPY=WRITE_ADRESS_LSB_COPY;
						}
						/*%C If the answer isn't CC, we stop the writing				*/
						else
						{
							STEP=STEP_END;
						}
						break;
					
					/*%C Send the LSB of the adress 											*/ 
					case WRITE_ADRESS_LSB_COPY:
						/*%C LSB of adress = 0x20 or 0x28 or 0x30 or 0x38				*/
						TXREG1 = Adress_LSB;
						/*%C Next step of writing												*/
						STEP_COPY=WRITE_ADRESS_MSB_COPY;
						break;

					/*%C Send the MSB of the adress 											*/ 
					case WRITE_ADRESS_MSB_COPY:
						/*%C MSB of adress =  0x00												*/
						TXREG1 = 0x00;
						/*%C Next step of writing												*/
						STEP_COPY=AUTHORISATION_COPY;
						break;

					/*%C Send the authorisation byte											*/
					case AUTHORISATION_COPY:
						/*%C Send a authorisation byte (0x07) to TX						*/
						TXREG1 = 0x07;
						/*%C Wait 20ms to copy the scratchpad on the memory			*/
						TIM_StartDecounter16(TIME_EEPROM_COPY_SCRATCHPAD,TIME_EEPROM_COPY_SCRATCHPAD_TIME_OUT);
						/*%C Next step of writing												*/
						STEP_COPY=WAIT_WRITE_COPY;
						break;
					
					case WAIT_WRITE_COPY:
						/*%C Check the end of the timer (20ms)								*/
						if (TIM_ReadValue16(TIME_EEPROM_COPY_SCRATCHPAD)== 0)
						{
							Flag_Answer_EEPROM_BAT=FALSE;
							/*%C Send a Read Command to read the Flag Status			*/
							TXREG1 = 0xFF;
							/*%C Next step of writing											*/
							STEP_COPY=WAIT_ANSWER_STATUS_COPY;
						}
						break;

					/*%C Read the answer of the Status Flag Command						*/
					case WAIT_ANSWER_STATUS_COPY:
						/*%C Check condition to continue or stop the writing 			*/
						/*%C When the answer is AA, we continue to write		 		*/
						if ( (Flag_Answer_EEPROM_BAT == TRUE)
						  && (Answer_EEPROM_BAT == 0xAA) )
						{
							/*%C Send a Command Mode (0xE3) to TX							*/
							TXREG1 = 0xE3;
							BLOCK++;		
							/*%C Test if we are copied the 32 bytes on page n°2		*/
							if (BLOCK>3)
							{
								/*%C We are finished to write the memory					*/
								/*%C we initialize different variables of the fonction*/ 
								State=READ;
								STEP=RESET;
								Ptr_Ram_MW = Ram_Write_Bat;
								Adress_LSB=0x20;
								Flag_Scratchpad_Full=FALSE;
								BLOCK=0;
								/*%C Flag of Writing EEPROM Failure = False				*/
								/*%C on the Power_Suply Data Base							*/
								DB_PowerSupply_Write(WRITE_DATA_EEPROM_BAT_FAILURE, FALSE);
								/*%C Start a Timer (15 minutes)								*/
								TIM_StartDecounter32(TIME_ACCESS_EEPROM_WRITE,TIME_ACCESS_EEPROM_WRITE_TIME_OUT);
							}
							else
							{		
								/*%C We copy the 8 following octects						*/
								STEP=RESET;
								/*%C Increment the adresse of the next 8 butes			*/
								Adress_LSB=Adress_LSB+8;
								Flag_Scratchpad_Full=FALSE;
							}
						}
						/*%C If the answer isn't AA, we stop the writing				*/
						else
						{
							STEP=STEP_END;
						}
						break;
					default :
						break ;
				}
			}
			break;
		/*%C There is a problem on the writing												*/
		case STEP_END:
			/*%C Flag of Writing EEPROM Failure = True 									*/
			/*%C on the Power_Suply Data Base												*/	
			DB_PowerSupply_Write(WRITE_DATA_EEPROM_BAT_FAILURE, TRUE);
			/*%C we initialize different variables of the fonction					*/ 
			State=READ;
			STEP=RESET;
			Ptr_Ram_MW = Ram_Write_Bat;
			Adress_LSB=0x20;
			Flag_Scratchpad_Full=FALSE;
			BLOCK=0;
			break;
		default :
			break ;		
	}
}
