/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_PwmBuzzer.c               							            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C This function manages the buzzer command, computing a PWM value function */
/*%C of an adjusted sound level.																*/
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
#include <intrins.h>
#else
#include "regf276e.h"
#endif
#include "typedef.h"
#include "enum.h"
#include "structure.h"
#include "io_declare.h"
#include "Timer_Data.h" 
#include "DB_Config.h"
#include "DB_AlarmStatus.h"
#include "DB_Control.h"
#include "DRV_PwmBuzzer.h"
#include "Driver_Datas.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/



void DRV_PwmBuzzer(e_BOOL Active)
{
	UWORD32 PW3Load = 0;
	UWORD16 SoundLevel = 0;
    /* Control buzzer recovery from base                                           */ 
    UWORD16 ControlBuzzer = DB_ControlRead(CONTROL_BUZZER_U16); 
	

/*%C If the PWM command is TRUE, the PWM value is computed	                  */
	if (Active == TRUE)
	{
/*%C In setup mode, maximum sound level				*/
		if (DB_ControlRead(MAINTENANCE_MODE_U16)==TRUE)
		{
			SoundLevel = 100;	//100%
		}
/*%C In ventilation mode, sound level recovery from config base				*/
		else
		{
			SoundLevel = DB_ConfigRead(SOUND_LEVEL_SELECT_U16);
			SEC_BUZ=1; 	//turn on CPU buzzer
		}
/*%C  PWM computing function of sound level:                                                      */ 
 		PW3Load = (PP3 * (100 - SoundLevel)) / 100 ;  // 100
/*%C  PW3 loaded with computed value														*/
		PW3 = (UWORD16)PW3Load;
/*%C  PW3 activated																				*/
		PWMCON1 |= 0x0008;
/*%C  Démarrage du timer T7											                  */
		T7R = 1;
/*%C  Security buzzer activated if alarm check buzzer detected						*/
		if (DB_AlarmStatusRead(ALARM_CHECK_BUZZER_U16) >= ALARM_TRUE)
		{
			SEC_BUZ = 1;
		}
	}
/*%C else the PW3 and the security buzzer are desactivated	                  */
	else
	{
        /*%C  PWM computing function of sound level:                                                      */ 
 		PW3Load = (PP3 * (100 - 0)) / 100 ;  // 100
		PW3 = (UWORD16)PW3Load;

/*%C  PW3 desactivated													                  */
		PWMCON1 &= 0xFFF7;    	
/*%C  Arrêt du timer T7													                  */
		T7R = 0;
		T7 = 0;
/*%C  Security buzzer desactivated													      */
		SEC_BUZ = 0;
	}
/*%C Anomaly buzzer information														      */
	DB_ControlWrite(CONTROL_BUZZER_U16 , Active);

/*%C Test to launch the timer only one time */ 
    if (ControlBuzzer != Active) 
	{ 
 		/*%C  authorise la mesure 50 ms apres le lancement de la commande */             
		TIM_StartDecounter(INT_MEASURE_BUZZER , TIME_INT_MEASURE_BUZZER); 
 	} 
}

// DesiredLevel in precentage, 100 precent is full sound
void DRV_PwmBuzzerInt(e_BOOL Active, UWORD16 DesiredLevel)
{
	UWORD32 PW3Load = 0;
	UWORD16 SoundLevel = 0;
	UWORD16 SndLevel = 0;
    /* Control buzzer recovery from base                                           */ 
    UWORD16 ControlBuzzer = DB_ControlRead(CONTROL_BUZZER_U16); 
	
    // sanity check for input
    if (DesiredLevel > 100) 
    {
        DesiredLevel = 100;
    }

/*%C If the PWM command is TRUE, the PWM value is computed	                  */
	if (Active == TRUE)
	{
/*%C In setup mode, maximum sound level				*/
		if (DB_ControlRead(MAINTENANCE_MODE_U16)==TRUE)
		{
			SoundLevel = 100;	//100%
		}
/*%C In ventilation mode, sound level recovery from config base				*/
		else
		{
			SoundLevel = DB_ConfigRead(SOUND_LEVEL_SELECT_U16);
			SEC_BUZ=1; 	//turn on CPU buzzer
		}

        SndLevel = (SoundLevel * DesiredLevel) / 100;

/*%C  PWM computing function of sound level:                                                      */ 
 		PW3Load = (PP3 * (100 - SndLevel)) / 100 ;  // 100
/*%C  PW3 loaded with computed value														*/
		PW3 = (UWORD16)PW3Load;
/*%C  PW3 activated																				*/
		PWMCON1 |= 0x0008;
/*%C  Démarrage du timer T7											                  */
		T7R = 1;
/*%C  Security buzzer activated if alarm check buzzer detected						*/
		if (DB_AlarmStatusRead(ALARM_CHECK_BUZZER_U16) >= ALARM_TRUE)
		{
			SEC_BUZ = 1;
		}
	}
/*%C else the PW3 and the security buzzer are desactivated	                  */
	else
	{
        /*%C  PWM computing function of sound level:                                                      */ 
 		PW3Load = (PP3 * (100 - 0)) / 100 ;  // 100
		PW3 = (UWORD16)PW3Load;

/*%C  PW3 desactivated													                  */
		PWMCON1 &= 0xFFF7;    	
/*%C  Arrêt du timer T7													                  */
		T7R = 0;
		T7 = 0;
/*%C  Security buzzer desactivated													      */
		SEC_BUZ = 0;
	}
/*%C Anomaly buzzer information														      */
	DB_ControlWrite(CONTROL_BUZZER_U16 , Active);

/*%C Test to launch the timer only one time */ 
    if (ControlBuzzer != Active) 
	{ 
 		/*%C  authorise la mesure 50 ms apres le lancement de la commande */             
		TIM_StartDecounter(INT_MEASURE_BUZZER , TIME_INT_MEASURE_BUZZER); 
 	} 
}
