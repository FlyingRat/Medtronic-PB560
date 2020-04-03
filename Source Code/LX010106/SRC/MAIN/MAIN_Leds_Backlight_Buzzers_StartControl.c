/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : MAIN_Leds_Backlight_Buzzers_StartControl.c                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C    This function allows to switch on the backlight, and Leds and Buzzers */
/*%C	during 200ms.                                     								*/
/*%C  The most powerful Buzzer can be inhbited, pressing the "inhib" Key 		*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              	*/
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
#include "io_declare.h"
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "Driver_Datas.h"
#include "MAIN_Leds_Backlight_Buzzers_StartControl.h"	
					 
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void MAIN_Leds_Backlight_Buzzers_StartControl(void)
{

	UWORD32 BuzzerVoltage  = 0 ;
	UWORD32 BatteryBuzzerVoltage = 0 ;

/*%C Sound alarm activation if the inhibition key is not pushed in order to   */
/*%C avoid a buzzer stop just after its power on (noise present: "clac")   */
	if (INHIB_DETECTED == 1)
	{
		ARRET_INVOLONTAIRE = 1;
	}
/*%C Security buzzer activation   */
	SEC_BUZ = 1;

/*% Activate and test the remote control */
	RAPPEL_ALARM = 1;
	TIM_Temporize(50000);
	if (ALARM_REMOTE_STATE == 0)
 	{
 		ALARM_CheckRemoteFlag = TRUE;
 	}
/*% Unactivate and test the remote control */
	RAPPEL_ALARM = 0;
	TIM_Temporize(50000);
	if (ALARM_REMOTE_STATE == 1)
 	{
 		ALARM_CheckRemoteFlag = TRUE;
 	}

/*%C Display request ON  */
	DRV_DIS_HostRequest ( 1 ) ;

/*%C Backligt command ON*/
  	DRV_DIS_grBackLight(SWITCH_ON); 

/*%C Display request OFF  */
	DRV_DIS_HostRequest ( 0 ) ;

/*%C Led activation for init test */
  	LED_ALARME_ROUGE  = 1;
  	LED_ALARME_ORANGE = 1;
	DRV_OutputPort(OUT_LED_VENTIL, 1); 						

#ifdef CONFIG_REGUL_O2
	DRV_OutputPort(OUT_LED_O2, 1); 						
#endif
	
/*%C 100 ms temporization for CAN acquisition */
	TIM_Temporize(100000);
	DRV_ADC_ChannelConvert();
/*%C 100ms temporization */
 	TIM_Temporize(10000);

/*%C Led desactivation for init test */
  	LED_ALARME_ROUGE  = 0;
  	LED_ALARME_ORANGE = 0;
	DRV_OutputPort(OUT_LED_VENTIL, 0); 						
#ifdef CONFIG_REGUL_O2
	DRV_OutputPort(OUT_LED_O2, 0); 						
#endif

	/*%C Measure of buzzer voltage for unvolontary stop ventil test */														
	BuzzerVoltage = (UWORD32) (5000 * (SWORD32)AD_Digit.TestBuzzer) / 1023;

/*%C Sound alarm unactivation if the inhibition key is not pushed   */
	if (INHIB_DETECTED == 1)
	{
		ARRET_INVOLONTAIRE = 0;
	}
/*%C Security buzzer unactivation   */
	SEC_BUZ = 0;

	/*%C 100 ms temporization for CAN acquisition */
	TIM_Temporize(100000);
	DRV_ADC_ChannelConvert();
	/*%C 100ms temporization */
 	TIM_Temporize(100000);
	/*%C Measure of battery buzzer voltage for unvolontary stop ventil  test*/														
	BatteryBuzzerVoltage = (UWORD32) (5000 * (SWORD32)AD_Digit.TestBuzzer) / 1023;
	/*% the test cares from battery level in case of unvoluntary stop, this */
	/*% shall not autorize an intempestive alarm  */
	if  (((BuzzerVoltage - BatteryBuzzerVoltage) < BUZZER_LOW_VOLTAGE_THRESHOLD_POWER_ON)
		&& (INHIB_DETECTED == 1)
		&& (((BatteryBuzzerVoltage/10)*BATTERY_VOLTAGE_DIVIDER) > BATTERY_BUZZER_LOW_VOLTAGE_THRESHOLD))
	{
		ALARM_CheckBuzzerFlag = TRUE;
	}


/*%C Buzzer board test */												
	DRV_Buz_Test(BUZ_CARD,BUZ);
 
/*%C 100 ms temporization for CAN acquisition */
	TIM_Temporize(100000);
	DRV_ADC_ChannelConvert();
/*%C 100ms temporization */
 	TIM_Temporize(100000);
	
	/*%C Measure of buzzer voltage for alarm test */	
	BuzzerVoltage = (UWORD32) (5000 * (SWORD32)AD_Digit.TestBuzzer) / 1023;
	if  (((BuzzerVoltage - BatteryBuzzerVoltage) < BUZZER_LOW_VOLTAGE_THRESHOLD_POWER_ON)
	     )
	{
		ALARM_CheckBuzzerFlag = TRUE;
	}
 	DRV_Buz_Test(BUZ_CARD,NO_BUZ);

}
