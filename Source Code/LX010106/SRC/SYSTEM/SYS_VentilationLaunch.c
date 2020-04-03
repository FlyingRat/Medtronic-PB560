/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_VentilationLaunch.c                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Management of all the detections, of the backlight,            */
/*%C           of the counters, of the RTC,etc                                */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                           INCLUDE FILES                                    */
/******************************************************************************/

#include "typedef.h"
#include "SYS_VentilationLaunch.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void SYS_VentilationLaunch(void)
{
	static UWORD16 MeasureSpo2Flag = 0;
	 
/*%C The function below are launched on this order :      	               */
/*%C   -	SYS_Alarm_Remote_Detect()*/
/*%C   - SYS_PressionChoice()*/
/*%C   - SYS_Keyboard() */
/*%C   - SYS_Backlight_Mngt() */
/*%C   -	SYS_RTC_Update()*/
/*%C   -	SYS_Counters_Mngt()*/
/*%C   -	SYS_CalibrationManagement()*/
/*%C   -	SYS_Monit_Buffer_Write()*/
/*%C   -	DRV_Key_Sound_Bip()*/
/*%C   -	SYS_Fio2Detection()*/
/*%C   -	SYS_SPO2Interpol() every 500ms*/

	SYS_Alarm_Remote_Detect();
	SYS_PressionChoice();
	SYS_Keyboard();
	SYS_Backlight_Mngt();
 	SYS_RTC_Update();
	SYS_Counters();
	SYS_CalibrationManagement();
	SYS_Monit_Buffer_Write();
	DRV_Key_Sound_Bip();
	SYS_Fio2Detection();
/*%C	SPO2 read every 500 ms */
	MeasureSpo2Flag++;
	if (MeasureSpo2Flag == 100)
	{
		SYS_SPO2Interpol();
		MeasureSpo2Flag = 0;
	}	  

}