/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : MAIN_Leds_Backlight_Buzzers_StartControl.h                   	*/
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
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef MAIN_LEDS_BLIGHT_BUZ_STARTCONTROL_H
#define MAIN_LEDS_BLIGHT_BUZ_STARTCONTROL_H
						 
/******************************************************************************/
/*                            External Function Declaration                   */
/******************************************************************************/


extern void TIM_Temporize(UWORD32 useconde);
extern void DRV_DIS_HostRequest ( bit etat );
extern void DRV_DIS_grWriteDisplay ( UBYTE dat );
extern void DRV_DIS_grBackLight ( UWORD16 _Level );
extern void DRV_OutputPort(e_OUTPUT_NAME _Port, UWORD16 _Value);
extern void DRV_Buz_Test(e_NUMBER_BUZ NumBuzzer, e_TYPE_TEST_BUZ Mode);
extern void DRV_ADC_ChannelConvert(void);
#endif