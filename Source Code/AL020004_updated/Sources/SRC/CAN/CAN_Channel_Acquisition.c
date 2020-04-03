/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CAN_Channel_Acquisition											  			*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                   AD conversion module :                      				*/
/*%C     One channel of the AD converter is loaded in one step of Scheduler. 	*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


/******************************************************************************/
/*                                INCLUDE FILES								  			*/
/******************************************************************************/

#include "p18f6622.h"
#include "typedef.h"
#include "define.h"
	#define DECLARATION_CAN_CHANNEL_ACQUISITION
#include "CAN_Channel_Acquisition.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void CAN_Channel_Acquisition(void)
{

	UBYTE Channel = 0;
	UWORD16 CanValue = 0;

/*%C Check if input acquisition is ended */
	if (ADCON0bits.GO == 0)
	{
		/*%C Lecture du résultat de la conversion analogique */
		CanValue = ADRES;
		Channel = ADCON0 >> 2;
		Channel = Channel & 0x0F;
			
		switch(Channel)
		{
			/*%C Traitement battery temperature Input	*/
			case 0 :	
			{
				CAN_Acquisition[Can_Acquisition_TempBat] = CanValue;
				/*%C Affectation de la voie suivante à convertir (1) */
				/*%C adrress for the next way to convert */
				ADCON0 = MEASURE_3V3_CHANNEL; 
				break;
			}
	
			/* Traitement 1 input No Measure */
			case 1 :
			{
				/*%C No Anolag line input */
				break;
			}
		
			/*%C Traitement 2 Input Measure 3V3	 */
			case 2 :
			{
				CAN_Acquisition[Can_Acquisition_3V3]  = CanValue;
				/*%C Affectation de la voie suivante à convertir (4) */
				/*%C adrress for the next way to convert */
				ADCON0 = MEASURE_VACDC_CHANNEL ; 			
				break;
			}

			/* Traitement 3 input No Measure */
			case 3 :
			{
				/*%C No Anolag line input */
				break;
			}
	
			/*%C Traitement 4 input  Measure VACDC	 */
			case 4 :
			{
				CAN_Acquisition[Can_Acquisition_VACDC] = CanValue;
				/*%C Affectation de la voie suivante à convertir (5)*/
				/*%C adrress for the next way to convert */
				ADCON0 = I_BAT_CHANNEL ;
				break;
			}
	
			/*%C Traitement 5 Input Measure IBAT	 */
			case 5 :
			{
				CAN_Acquisition[Can_Acquisition_IBat] = CanValue;	
				/*%C Affectation de la voie suivante à convertir (6)*/
				/*%C adrress for the next way to convert */
				ADCON0 = MEASURE_VCHARGE_CHANNEL ;
				break;
			}
	
			/*%C Traitement 6 input Measure VCharge */ 
			case	6 :
			{
				CAN_Acquisition[Can_Acquisition_VCharge] = CanValue;	
				/*%C Affectation de la voie suivante à convertir (7)*/
				/*%C adrress for the next way to convert */
				ADCON0 = TEMP_AMB_CHANNEL ;
				break;
			}
				
			/*%C Traitement 7 input Measure TEMP AMB	 */
			case 7 : 
			{
				CAN_Acquisition[Can_Acquisition_TempAmb] = CanValue;	
				/*%C Affectation de la voie suivante à convertir (8)*/
				/*%C adrress for the next way to convert */
				ADCON0 = MEASURE_VDC_CHANNEL ;
				break;
		   }
	
			/*%C Traitement 8 input Measure VDC	 */
			case 8 :
			{
				CAN_Acquisition[Can_Acquisition_VDC] = CanValue;	
				/*%C Affectation de la voie suivante à convertir (9)*/
				/*%C adrress for the next way to convert */
				ADCON0 = MEASURE_24VUTIL_CHANNEL ;
				break;
			}
		
			/*%C Traitement 9 input Measure 24VUTIL	 */
			case 9 :
			{
				CAN_Acquisition[Can_Acquisition_24VUtil] = CanValue;	
				/*%C Affectation de la voie suivante à convertir (10)*/
				/*%C adrress for the next way to convert */
				ADCON0 = MEASURE_5V_CHANNEL ;
				break;
			}
	
			/*%C Traitement 10 input Measure 5V	 */
			case 10 :
			{
				CAN_Acquisition[Can_Acquisition_5V] = CanValue;	
				/*%C Affectation de la voie suivante à convertir (11)*/
				/*%C adrress for the next way to convert */
				ADCON0 = MEASURE_VBAT_CHANNEL ;
				break;
			}
	
			/*%C Traitement 11 input Measure VBAT	 */
			case 11 :
			{
				CAN_Acquisition[Can_Acquisition_VBat] = CanValue;
				/*%C Affectation de la voie suivante à convertir (0)*/
				/*%C adrress for the next way to convert */
				ADCON0 = BATTERY_TEMP_CHANNEL ;
				break;
			}
			default:
			{
				break;
			}
		}
	/*%C Allows next input convert */
	ADCON0bits.GO = 1;
	}
}
