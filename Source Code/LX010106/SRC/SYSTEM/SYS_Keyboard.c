/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_Keyboard.c                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                       KEYBOARD management : 		            	   		*/
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                              INCLUDE FILES	                              */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "DB_Control.h"
#include "DB_KeyboardEvent.h"
#include "Timer_Data.h"
#include "System_Datas.h"
#include "DB_Config.h"
#include "SYS_Keyboard.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void SYS_Keyboard(void)
{
   UWORD16 i = 0;
   UWORD16 Key_Detected = 0;
   UWORD16 Monit_Key_Detected = 0;
   UWORD16 Up_Key_Detected = 0;
   UWORD16 Down_Key_Detected = 0;
   UWORD16 Start_Stop_Key_Detected = 0;
/*	UWORD16 Timer_OverFlow;	 utilisé dans l'anomalie clavier qui est maintenant*/
/*                          gérée dans "SECURITY"                FM         */
   e_BOOL End_Of_Scan = FALSE;
	e_SYS_KeyboardInput KeyboardInput = KEY_NO_KEYBOARD;
   static e_SYS_KeyboardInput KeyboardInputMemory = KEY_NO_KEYBOARD;
   UWORD16 Timer_OverFlow = 0;
   static e_SYS_KeyboardInput KeyboardAnomalieMemory = KEY_NO_KEYBOARD;

/* Validation bip recovery from base			                                 */
	e_VALIDATION_BIP_TYPE Adjust_Key_Tone = DB_ConfigRead(ADJUST_KEY_TONE_U16);

  
/*%C Reading of Ventil key	*/
	Start_Stop_Key_Detected = KEY_Touch_Detection(KEY_CODE_STARTSTOPVENTIL);
	Monit_Key_Detected = KEY_Touch_Detection(KEY_CODE_MONIT);
	Down_Key_Detected = KEY_Touch_Detection(KEY_CODE_DOWN);
	Up_Key_Detected = KEY_Touch_Detection(KEY_CODE_UP);	


/******************************************************************************/
/*%C                     DETECTION OF DOUBLE KEYPRESS                         */

/*%C The Key for starting or stoping the ventilation must be tested first, */
/*%C because priority action .*/
	if (Start_Stop_Key_Detected == TRUE)
	{ 	
	   KeyboardInput = KEY_CODE_STARTSTOPVENTIL;  
	}

/*%C Test to reduce the contrast :*/
/*%C "Monitoring" and "Down" keys has to be pressed */
/*%C Detection of double keypress  Monitoring and Down*/
	else if ((Monit_Key_Detected == TRUE)
	      && (Down_Key_Detected == TRUE))
	{			
	   KeyboardInput = KEY_CODE_MONIT_AND_DOWN; 
	}

/*%C Test to increase the contrast :*/
/*%C "Monitoring" and "Up" keys has to be pressed */
/*%C Detection of double keypress  Monitoring and Up*/	   
	else if ((Monit_Key_Detected == TRUE)
	      && (Up_Key_Detected == TRUE)) 			
	{
	   KeyboardInput = KEY_CODE_MONIT_AND_UP; 
	}

/*%C Test of the Key lock or Key Unlock */
/*%C "Up" and "Down" keys has to be pressed */
/*%C Detection of double keypress  Up and Down*/  
	else if ((Up_Key_Detected == TRUE)
	      && (Down_Key_Detected == TRUE)) 			
	{
	   KeyboardInput = KEY_CODE_UP_AND_DOWN; 
	}


/******************************************************************************/
/*%C                     DETECTION OF SIMPLE KEYPRESS                         */
	else
	{
/*%C A scan of all the keys, must be done, until one of them is pressed */
/*%C Simple Key Iint */
		i = Mark_Begin_Simple_Touch + 1;
        do
		{
/*%C 		if the index is lower than the end of "Keys" table, then a detection */
/*%C 		of key depending on this index is launched*/
		   if (i < Number_of_key )
		   {
		      Key_Detected = KEY_Touch_Detection(i);
/*%C  		If a key is pressed, the index is memorized and the scan can be */
/*%C 			stopped writing "TRUE" into the flag "End_Of_Scan".*/
		      if(Key_Detected == TRUE)
			  	{ 
		         KeyboardInput = i;
		         End_Of_Scan = TRUE ;
		      }
/*%C 			The index must increase to continue the scan.*/
		      i = i + 1;
		   }
/*%C 		If the index is equal or upper than the end of "keys" table, then no */
/*%C 		keys has been pressed, and the scan is stopped. */         
		   else
		   {
		      KeyboardInput = KEY_NO_KEYBOARD;
		      End_Of_Scan = TRUE;
		   }
		  }
		while(End_Of_Scan != TRUE);
	}


/******************************************************************************/
/*%C                           PULSE AUTHORISATION                            */

/*%C A new pulse is authorized, when , at least, one of the two keys */
/*%C ("monit" and "down") is unactivated.*/
	if ( (Monit_Key_Detected == FALSE)
	  || (Down_Key_Detected == FALSE) )				
	{
		SYS_Num_Keyboard[KEY_CODE_MONIT_AND_DOWN].autorization = TRUE; 
	}
/*%C A new pulse is authorized, when , at least, one of the two keys */
/*%C ("monit" and "Up") is unactivated.*/
	if ( (Monit_Key_Detected == FALSE)
	  || (Up_Key_Detected == FALSE) )
	{		
		SYS_Num_Keyboard[KEY_CODE_MONIT_AND_UP].autorization = TRUE;
	}
/*%C A new pulse is authorized, when , at least, one of the two keys */
/*%C ("Up" and "Down") is unactivated.*/
	if ( (Up_Key_Detected == FALSE)
	  || (Down_Key_Detected == FALSE) )
	{  				
	   SYS_Num_Keyboard[KEY_CODE_UP_AND_DOWN].autorization = TRUE; 
	}
/*%C In case of simple key press, a new pulse is authorized when */
/*%C the detection of each key is "FALSE".*/
	for(i=Mark_Begin_Simple_Touch + 1; i<Number_of_key; i++)
	{
	   Key_Detected = KEY_Touch_Detection(i);
	   if (Key_Detected == FALSE)
	   {
	      SYS_Num_Keyboard[i].autorization = TRUE;
	   }
	}

/******************************************************************************/
/*                        KEY PRESS HYSTERESIS                                */

/*%C When there is one ore more activated key */
	if (KeyboardInput != KEY_NO_KEYBOARD)  
	{
/*%C 	Increasing detection counter */
      SYS_Num_Keyboard[KeyboardInput].debounceDetected = 
            SYS_Num_Keyboard[KeyboardInput].debounceDetected + 1;
/*%C 	Test if the pulse is  longer enougth */
	   if (SYS_Num_Keyboard[KeyboardInput].debounceDetected
	       >= CHANGE_MS_TO_STEPS(cSYS_DebounceValidated))	 
	   {
/*%C  	Test if the key is authorized and it pulse not yet True */
	      if ( (SYS_Num_Keyboard[KeyboardInput].autorization == TRUE)
	        && (SYS_Num_Keyboard[KeyboardInput].pulse == FALSE) )
	      {
				if ( (Adjust_Key_Tone == CLOC)	
			  	  || (Adjust_Key_Tone == BIP_AND_CLOC) )
				{
/*%C     		Key press sound  */ 
	         	DRV_Key_Sound_Cloc();
				}
/*%C			The pulse field for the key is turned to true and the associated*/
/*%C    		pulse time is reset */
				SYS_Num_Keyboard[KeyboardInput].pulse = TRUE;
				SYS_Num_Keyboard[KeyboardInput].PulseTime = 0;
			}
/*%C  The level field of the key is turned to true and its debouncedetected */
/*%C  field is loaded with the max delay */
		SYS_Num_Keyboard[KeyboardInput].level = TRUE;	 	
		SYS_Num_Keyboard[KeyboardInput].debounceDetected =
		CHANGE_MS_TO_STEPS(cSYS_DebounceValidated);
/*%C  The DebounceCanceled field of the key is reset */
		SYS_Num_Keyboard[KeyboardInput].debounceCanceled = 0;
	   }
	}

/******************************************************************************/
/*%C                        UNACTIVATION KEY STATE                            */

/*%C For all the Keys */
	for (i = 0;i < Number_of_key;i++)
	{
/*%C 	Unactivation  for all the Keys Level	*/
/*%C 	If the key level is true */
	   if (SYS_Num_Keyboard[i].level == TRUE)
	   {
/*%C  	Increasing the debounceCanceld field */
         SYS_Num_Keyboard[i].debounceCanceled = 
			SYS_Num_Keyboard[i].debounceCanceled + 1;
/*%C   	if the debounceCanceld field is = or > than the max delay */
	      if (SYS_Num_Keyboard[i].debounceCanceled >= 
	          CHANGE_MS_TO_STEPS(cSYS_DebounceDesactivated))
	      {
/*%C  		The level field of the key is turned to false & its */
/*%C  		debounceDetected is reset */
	      	SYS_Num_Keyboard[i].level = FALSE;
	      	SYS_Num_Keyboard[i].debounceDetected = 0;
	      }
	   }
/*%C  Unactivation Key Pulse if the pulse field is true	 */
	   if (SYS_Num_Keyboard[i].pulse == TRUE)
	   {
/*%C  	Increasing the pulse time of the key */
         SYS_Num_Keyboard[i].PulseTime = SYS_Num_Keyboard[i].PulseTime + 1;
/*%C  	If the pulse time field of the key is = or > than the max delay */
	      if (SYS_Num_Keyboard[i].PulseTime >= 
	          CHANGE_MS_TO_STEPS(cSYS_PulseTime))
	      {
/*%C  		Pulse field of the key is turned to False	Authorization field */
/*%C  		of the key is turned to False */
	         SYS_Num_Keyboard[i].pulse = FALSE;
	         SYS_Num_Keyboard[i].autorization = FALSE;
	      }
	   }
	}
/*----------------------------------------------------------------------------*/
/* cette fonction est gérée dans SECURITY                                     */
/******************************************************************************/
/*                           KEYBOARD ANOMALY								  */

/*%C if no key is activated or on detection of a new key	 */
	if ((KeyboardInput == KEY_NO_KEYBOARD)			 
	 || ((KeyboardInput != KeyboardInputMemory)
	 && (KeyboardAnomalieMemory == KEY_NO_KEYBOARD)))	  
	{		 
	   KeyboardAnomalieMemory = KEY_NO_KEYBOARD;
/*%C  Reload the anomaly delay  */
	   TIM_StartDecounter(KEY_ANO_KEYB,
	                      TIME_ANO_KEYB);		 
	} 
/*%C Writting in Base control the anomaly when the delay is over  */
	if (TIM_ReadDecounterValue(KEY_ANO_KEYB) == 0)
	{				
	   KeyboardAnomalieMemory = KeyboardInput;
		DB_ControlWrite(KEYBOARD_ANOMALIE_U16,
	                   TRUE); 
	}
	else
	{
	   DB_ControlWrite(KEYBOARD_ANOMALIE_U16,
	                   FALSE); 
	} 
/*%C Updating the memory of the previous keys activated  */
	KeyboardInputMemory = KeyboardInput;  
/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                    CALL OF "KEY_Event" Function                          */

	KEY_Event();
}

