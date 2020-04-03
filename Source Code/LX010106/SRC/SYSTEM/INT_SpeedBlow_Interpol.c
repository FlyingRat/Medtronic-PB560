/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : INT_SpeedBlow_Interpol.c                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Blower Speed value conversion                                  */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "DB_Compute.h"
#include "Timer_Data.h"
#include "Driver_Datas.h"
#include "INT_SpeedBlow_Interpol.h"



/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void INT_SpeedBlow_Interpol(void)
{
/*%C Variables for computing of filtering window (gliding) */
	static UWORD16 SampleNb = 0;
	static UWORD16 SpeedSample[10] = {0,0,0,0,0,0,0,0,0,0};
	UWORD16 i = 0;
	UWORD32 SpeedCumul = 0;
	UWORD16 Measure_speed_blower = 0;
	UWORD16 Filter_speed_blower = 0;
	

	/*%C Flag for speed blower available		*/
  	UWORD16 MeasuredValueOK = FALSE;
	UWORD16 Timer_Counter_Value = TIM_ReadCounterValue(SYS_TIME_OUT_SPEED);

	
/*%C When acquisition delay is over	   */
	if (Timer_Counter_Value == 0)
   {
/*%C  The speed blower measure is initialized	 */
      Measure_speed_blower = 0;
/*%C  Authorization for interpolation operation		 */
      MeasuredValueOK = TRUE;
	}
/*%C Else, if a speed acquirement is available, then 			 */
	else if (AvailableSpeedBlowerDigit == TRUE)
	{
/*%C  - Load the duration of one rotation of the blower :   */
/*%C	SpeedBlowerDigit is given by the interrupt CCO 
/*%C  - Convert the duration above into a rotation speed (rate/minute) :	   */
/*%C  (60s /((Nbr de clock CPU/prédiviseur) x durée d'une impulsion(800nS)) */
	   Measure_speed_blower = (UWORD16)(600000000UL / (SpeedBlowerDigit * 2UL));
/*%C  - End of sampling, flag for interpolation	   */
	   MeasuredValueOK = TRUE;
	}

/*%C If acquisition and sampling are ended, then	*/
	if (MeasuredValueOK == TRUE)
	{
/*%C  - Writing in Data base of calibrated speed blower	  */
	   DB_ComputeWrite(MEASURE_SPEED_BLOWER_U16,
	                   Measure_speed_blower);

/*%C  - Speed blower filtering :			   */
		SpeedSample[SampleNb] = Measure_speed_blower;
		SampleNb = SampleNb + 1;
      SampleNb = SampleNb % 10;
/*%C  Speed blower Average between 10 values			*/
      for(i=0;i<10;i++)
		{
		   SpeedCumul = SpeedCumul + SpeedSample[i];   
		}
		SpeedCumul = SpeedCumul / 10;
		Filter_speed_blower = (UWORD16)SpeedCumul;

/*%C  Storage of Filtered speed blower in the Computed Data base	 */
	   DB_ComputeWrite(FILTER_SPEED_BLOWER_S16,
	                   Filter_speed_blower);

/*%C  Load blower speed time out: */
/*%C  TIM_StartDecounter(SYS_TIME_OUT_SPEED,TIME_OUT_SPEED)   */
	   TIM_StartDecounter(SYS_TIME_OUT_SPEED,
	                      TIME_OUT_SPEED);

/*%C 	Begening of a new speed blower acquisition	 :  */
/*%C 	the function "DRV_SPEED_LaunchingSpeedBlowerMeasure" is launched */
	   DRV_SPEED_LaunchingSpeedBlowerMeasure();
	}
}
