/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_Key_Sound_Bip.c  	 		  			                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C This function manages the "bip" command	for the menu navigation	:			*/
/*%C - short bip when validation menu entry (200ms)									*/
/*%C - long bip when validation menu exit	 (500ms)										*/
/*%C - time out bip when validation menu time out is reached (1000ms)			*/
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
#ifndef _TASKING
#include "LH_ST10F276.h"
#include <intrins.h>
#else
#include "regf276e.h"
#endif	
#include "io_declare.h"
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "Timer_Data.h"
#include "DB_Config.h"
#include "DB_Control.h"
#include "DRV_Key_Sound_Bip.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_Key_Sound_Bip(void)
{

/* First stop bip flag								                                 */
	static UWORD16 First_Stop_Bip = FALSE;
/* Silence flag between first and second stop bip                             */
	static UWORD16 Silence = FALSE;

/* Validation bip recovery from base			                                 */
	e_VALIDATION_BIP Validation_Bip = DB_ControlRead(VALIDATION_BIP_U16);
/* Validation bip recovery from base			                                 */
	e_VALIDATION_BIP_TYPE Adjust_Key_Tone = DB_ConfigRead(ADJUST_KEY_TONE_U16);
/* Buzzer test card recovery from base                                   		*/
	UWORD16 Test_Buz_Card = DB_ControlRead(TEST_BUZ_CARD_U16);
/* Buzzer test security recovery from base                                		*/
	UWORD16 Test_Buz_Sec = DB_ControlRead(TEST_BUZ_SEC_U16);
/* Test volume recovery from base                                		*/
	UWORD16 Test_Volume = DB_ControlRead(TEST_VOLUME_U16);
/* Test volume recovery from base                                		*/
	UWORD16 Alarm_Detected = DB_ControlRead(ALARM_DETECTED_U16);
/* Buzzer test declaration						                                		*/
	UWORD16 Bip_Launch = FALSE;
/* Start burst declaration						                                		*/
	static UWORD16 Start_Burst = FALSE;

/*%C Buzzer test request:					 					  				            */
/*%C a short bip is made when testing buzzer card or security buzzer          */
	if ( (Test_Buz_Card == TRUE)
	  || (Test_Buz_Sec == TRUE) )
	{
		Validation_Bip = BIP_SHORT;
		Bip_Launch = TRUE;	
	}

/*%C Sound level burst command if test volume is requested			            */
	if	(Test_Volume == TRUE)
	{
/*%C 	Burst is launched once and is still active during test volume request   */
		if (Start_Burst == FALSE)
		{
			DRV_Buz_Sound(FAST_SOUND,
	                    BUZ_CARD);
/*%C     Bip running flag activated	to  		 							         	*/
	      DB_ControlWrite(BIP_RUNNING_U16,
		                   TRUE);
			Start_Burst = TRUE;
		}      			
	}
	else
	{
/*%C  Start burst reset 					  				            					*/
		Start_Burst = FALSE;	
/*%C 	Bip choice function of bip request 					  				            */
		switch (Validation_Bip)
		{
/*%C  	Validation bip for menu entry									               */
			case BIP_SHORT:
			{
/*%C  		The short bip timer is launched 						               */
				TIM_StartDecounter(SET_VALIDATION_BIP,
										 TIME_BIP_SHORT);
/*%C     	Bip running flag activated	  	 							         	*/
	         DB_ControlWrite(BIP_RUNNING_U16,
		                      TRUE);
/*%C  		Security buzzer test		 			 					               */
				if (Test_Buz_Sec == TRUE)
				{
					SEC_BUZ = 1;
/*%C  			Buzzer security desactivation	*/
					DB_ControlWrite(TEST_BUZ_SEC_U16,
									 	 FALSE);
				}
/*%C  		Buzzer card test					 					               	*/
				else if (Test_Buz_Card == TRUE)
				{
	            TIM_StartDecounter(SET_VALIDATION_BIP,
										 TIME_BIP_VERY_LONG);
				DRV_Buz_Sound(CONTINU_SOUND,
	                          BUZ_CARD);			

/*%C  			Buzzer card desactivation	*/
					DB_ControlWrite(TEST_BUZ_CARD_U16,
									 	 FALSE);
				}
/*%C  		else, validation bip is commanded  				               	*/
				else
				{
	            DRV_Buz_Sound(START_BIP_SOUND,
	                          BUZ_ALL);			
				}
/*%C  		Validation bip is set to its initial state in the control base		*/
				DB_ControlWrite(VALIDATION_BIP_U16,
									 NO_BIP);
				break;
			}
/*%C  	Validation bip for menu entry									               */
			case BIP_SHORT_VALID:
			{
/*%C  		Bip launch	  													               */
				if ( (Adjust_Key_Tone == BIP_AND_CLOC)	
              || (Adjust_Key_Tone == BIP) )
				{
/*%C  			The short bip timer is launched 						               */
					TIM_StartDecounter(SET_VALIDATION_BIP,
											 TIME_BIP_SHORT_VALID);
/*%C     		Bip running flag activated	  	 							         	*/
	         	DB_ControlWrite(BIP_RUNNING_U16,
		                         TRUE);
/*%C  			Security buzzer test		 			 					               */
					if (Test_Buz_Sec == TRUE)
					{
						SEC_BUZ = 1;
/*%C  				Buzzer security desactivation	*/
						DB_ControlWrite(TEST_BUZ_SEC_U16,
									 		 FALSE);
					}
/*%C  			Buzzer card test					 					               	*/
					else if (Test_Buz_Card == TRUE)
					{
	            	DRV_Buz_Sound(START_BIP_SOUND,
	                          	  BUZ_CARD);			
/*%C  				Buzzer card desactivation	*/
						DB_ControlWrite(TEST_BUZ_CARD_U16,
									 		 FALSE);
					}
/*%C  			else, validation bip is commanded  				               	*/
					else
					{
	            	DRV_Buz_Sound(START_BIP_SOUND,
	                          	  BUZ_ALL);			
					}
				}
/*%C  		Validation bip is set to its initial state in the control base		*/
				DB_ControlWrite(VALIDATION_BIP_U16,
									 NO_BIP);
				break;
			}
/*%C  	Long validation bip 												               */
			case BIP_LONG:
			{
/*%C  		The start bip timer is launched	  						               */
				TIM_StartDecounter(VEN_VENTILATION_BIP,
										 TIME_BIP_LONG);
/*%C     	Bip running flag activated		 							         		*/
	         DB_ControlWrite(BIP_RUNNING_U16,
		                      TRUE);
/*%C  		The buzzer is activated	  								               	*/
				DRV_Buz_Sound(BIP_LONG_SOUND,
	                       BUZ_ALL);			
/*%C  		Validation bip is set to its initial state in the control base		*/
				DB_ControlWrite(VALIDATION_BIP_U16,
									 NO_BIP);		
				break;
			}
/*%C  	Very Long validation bip 										               */
			case BIP_VERY_LONG:
			{
/*%C  		The start bip timer is launched	  						               */
				TIM_StartDecounter(SET_HISTO_BIP,
										 TIME_BIP_VERY_LONG);
/*%C     	Bip running flag activated		 							         		*/
	         DB_ControlWrite(BIP_RUNNING_U16,
		                      TRUE);
/*%C  		The buzzer is activated	  								               	*/
				DRV_Buz_Sound(BIP_VERY_LONG_SOUND,
	                       BUZ_ALL);			
/*%C  		Validation bip is set to its initial state in the control base		*/
				DB_ControlWrite(VALIDATION_BIP_U16,
									 NO_BIP);		
				break;
			}
/*%C  	Validation bip for ventilation start  						               */
			case BIP_START_VENTIL:
			{
/*%C  		The start bip timer is launched	  						               */
				TIM_StartDecounter(VEN_VENTILATION_BIP,
										 TIME_BIP_START_VENTIL);
/*%C     	Bip running flag activated	 	 							         		*/
	         DB_ControlWrite(BIP_RUNNING_U16,
		                      TRUE);
/*%C  		The buzzer is activated									               	*/
				DRV_Buz_Sound(START_BIP_SOUND,
	                       BUZ_ALL);			
/*%C  		Validation bip is set to its initial state in the control base		*/
				DB_ControlWrite(VALIDATION_BIP_U16,
									 NO_BIP);		
				break;
			}
/*%C  	Validation bip for ventilation stop							               */
			case BIP_STOP_VENTIL:
			{
/*%C  		The start bip timer is launched	 						               */
				TIM_StartDecounter(VEN_VENTILATION_BIP,
										 TIME_BIP_STOP_VENTIL);
/*%C     	Bip running flag activated	 	 							         		*/
	         DB_ControlWrite(BIP_RUNNING_U16,
		                      TRUE);
/*%C  		The buzzer is activated									               	*/
				DRV_Buz_Sound(STOP_BIP_SOUND,
	                       BUZ_ALL);			
/*%C  		Validation bip is set to its initial state in the control base		*/
				DB_ControlWrite(VALIDATION_BIP_U16,
									 NO_BIP);		
				break;
			}
/*%C  	Usb Connection Key												               */
			case BIP_USB_CONNECT:
			{
/*%C  		The start bip timer is launched	 						               */
				TIM_StartDecounter(USB_CONNECT_DISCONNECT_KEY,
										 TIME_USB_CONNECT_DISCONNECT_KEY);
/*%C     	Bip running flag activated	 	 							         		*/
	         DB_ControlWrite(BIP_RUNNING_U16,
		                      TRUE);
/*%C  		The buzzer is activated									               	*/
				DRV_Buz_Sound(STOP_BIP_SOUND,
	                       BUZ_ALL);			
/*%C  		Validation bip is set to its initial state in the control base		*/
				DB_ControlWrite(VALIDATION_BIP_U16,
									 NO_BIP);		
				break;
			}
/*%C  	Usb Connection Key												               */
			case BIP_USB_DISCONNECT:
			{
/*%C  		The start bip timer is launched	 						               */
				TIM_StartDecounter(USB_CONNECT_DISCONNECT_KEY,
										 TIME_USB_CONNECT_DISCONNECT_KEY);
/*%C     	Bip running flag activated	 	 							         		*/
	         DB_ControlWrite(BIP_RUNNING_U16,
		                      TRUE);
/*%C  		The buzzer is activated									               	*/
				DRV_Buz_Sound(STOP_BIP_SOUND,
	                       BUZ_ALL);			
/*%C  		Validation bip is set to its initial state in the control base		*/
				DB_ControlWrite(VALIDATION_BIP_U16,
									 NO_BIP);		
				break;
			}
/*%C  	If the validation bip timer is reached, the buzzer is stopped        */
			default:
			{
				if ( 	(TIM_ReadDecounterValue(SET_VALIDATION_BIP) == 0)
				  && 	(TIM_ReadDecounterValue(VEN_VENTILATION_BIP) == 0)
				  && 	(TIM_ReadDecounterValue(SET_HISTO_BIP) == 0)
				  && 	(TIM_ReadDecounterValue(USB_CONNECT_DISCONNECT_KEY) == 0))
				{
/*%C     		Bip running flag cancelled	  						         			*/
	         	DB_ControlWrite(BIP_RUNNING_U16,
		                      	FALSE);
					if ( (Alarm_Detected == FALSE)
					  && (TIM_ReadDecounterValue(SEC_HIGH_PRIORITY_BURST) == 0)
				      && (TIM_ReadDecounterValue(SEC_MEDIUM_PRIORITY_BURST) == 0)
				      && (TIM_ReadDecounterValue(SEC_LOW_PRIORITY_BURST) == 0) )
					{
/*%C     			Stop buzzer if no alarm detected	 			         			*/
						DRV_Buz_Sound(NO_SOUND,
	                       		  BUZ_ALL);
/*%C     			Stop security buzzer					 			         			*/
						SEC_BUZ = 0;
					}	                       		  			
				}
				break;
			}
		}
	}
}
