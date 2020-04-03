/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : FAN_Acquisition                                   		  			*/
/*													 						  							*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                    Cooling fan acquisition								  			*/
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
#include "typedef.h"
#include "DB_Measurement.h"
#include "FAN_Data.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void FAN_Acquisition(void)
{	
	UWORD16 Speed_Digit_Compute = 0;	
	static UBYTE NbInterrupt = 0;
	static UBYTE Overflow_TimerFan = FALSE;
	
	/*%C First pulse																			*/
	if (NbInterrupt == 0 )
	{
		/*%C Raz interrupt flag,  															*/
		PIR1bits.CCP1IF = 0;
		/*%C Capture the ventilateur period												*/
		Speed_Digit_Fan_Array[NbInterrupt % SPEED_DIGIT_FAN_ARRAY_SIZE] =  CCPR1 ;
		/*%C Increment table index															*/
		NbInterrupt = NbInterrupt + 1 ;
	}
	/*%C Second to fifth  pulse 			 												*/
	else 
	{
		Speed_Digit_Fan_Array[NbInterrupt % SPEED_DIGIT_FAN_ARRAY_SIZE] =  CCPR1 ;
		/*%C Calculation the period between two pulses in without overflow timer case */
		if (Speed_Digit_Fan_Array[NbInterrupt] < Speed_Digit_Fan_Array[NbInterrupt+1])
		{
			/*%C Value[1] - Value[0] 														*/
			Speed_Digit_Compute = Speed_Digit_Fan_Array[NbInterrupt] 
										- Speed_Digit_Fan_Array[NbInterrupt-1] ;
		}
		/*%C Calculation the period between to pulses in overflow timer case 		*/
		// Si le timer déborde il faut ajouter le temps écoulé depuis la dernière capture
		// jusqu'a la fin du timer et ajouter la valeur courante du timer
		else
		{
			Speed_Digit_Compute =(0xFFFF	- Speed_Digit_Fan_Array[NbInterrupt-1]) 
									+ Speed_Digit_Fan_Array[NbInterrupt] ;
			Overflow_TimerFan = TRUE;
		}
		/*%C Fifth pulse 	and pulse valid  one turn moteur									*/
		// Sur la cinquième capture le moteur du ventilateur a effectué un tour complet
		//
		if ((NbInterrupt == 4) && (Speed_Digit_Compute > 500))
		{
			/*%C Inibition interrupt capture 													*/
			PIE1bits.CCP1IE = 0;
			/*%C Calculation the period for one turn motor without overflow timer   */
			if( 	Overflow_TimerFan == TRUE)
			{
				Speed_Fan =(0xFFFF - Speed_Digit_Fan_Array[0]) +  Speed_Digit_Fan_Array[4];
			}
			/*%C Calculation the period for one turn motor with overflow timer   	*/
			else
			{
				Speed_Fan = Speed_Digit_Fan_Array[4]- Speed_Digit_Fan_Array[0];
			}
			Overflow_TimerFan = FALSE;
			NbInterrupt = 0;
			/*%C Reset interrupt flag, 															*/
			PIR1bits.CCP1IF = 0;
		}
		/*%C Second pulse to fourth pulse  	and valid pulse								*/
		// Si le temps mesuré entre deux impusions est inférieur à 210us 
		// c'est que la capture est une capture parasite sur front montant ou sur
		// front descendant il faut attendre la prochaine capture.
		else if (Speed_Digit_Compute > 500)
		{ 
			/*%C Count motor's pulse														   	*/
			NbInterrupt = NbInterrupt + 1 ;
			/*%C Reset interrupt flag, 															*/
			PIR1bits.CCP1IF = 0;
		}
		else 
		{
			/*%C Reset interrupt flag, 															*/
			PIR1bits.CCP1IF = 0;
		}
	}
}
