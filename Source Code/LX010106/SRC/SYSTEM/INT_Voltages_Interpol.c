/******************************************************************************/
/*                                                                            */
/* Project N  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : INT_Voltages_Interpol.c                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Voltage values conversion                                      */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/

#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "Timer_Data.h"
#include "DB_Compute.h"
#include "DB_Control.h"
#include "Driver_Datas.h"
#include "INT_Voltages_Interpol.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void INT_Voltages_Interpol(void)
{
	UWORD16 MeasureBatteryBuzzer = 0 ;
	UWORD32 MeasureTestBuzzerVoltage = 0 ;
   	UWORD16 ControlBuzzer = DB_ControlRead(CONTROL_BUZZER_U16);
	SWORD32 CalibratedValue = 0;

	/*----------------------------------------------------------------------------*/
	/*%C Measure of buzzer voltage & storage in the base Compute with a filter		*/
	/*%C MeasureBuzzerVoltage   = ConverterResolution * 5.000 / 1023 (V)			*/
	/*%C MeasureBuzzerVoltage   = ConverterResolution * 5000 / 1023 (10-3V)			*/
	MeasureTestBuzzerVoltage = (5000 * (SWORD32)AD_Digit.TestBuzzer) / 1023 ; ;
	/*%C Buzzer test Measure storage in mV (0 to 5000 mV)*/
	DB_ComputeWrite(MEASURE_TEST_BUZZER_VOLTAGE_U16,(UWORD16)MeasureTestBuzzerVoltage); 
	if 	(TIM_ReadDecounterValue(INT_MEASURE_BUZZER) == 0)
	{
		/*%C If the buzzer command is on, we measure the buzzer voltage */
		if ( ControlBuzzer ==  TRUE)
		{
			/*%C Buzzer voltage compute */
			/*%C V_buzzer = V_buzzer_test - (BATTERY_VOLTAGE_DIVIDER * V_battery) / 10 */
			MeasureBatteryBuzzer = DB_ComputeRead(MEASURE_BATTERY_BUZZER_VOLTAGE_U16);		
			MeasureBatteryBuzzer = MeasureBatteryBuzzer / BATTERY_VOLTAGE_DIVIDER;
			MeasureBatteryBuzzer = MeasureBatteryBuzzer * 10 ;
			/*%C Buzzer voltage storage in mV (0 to 5000 mV)*/
			DB_ComputeWrite(MEASURE_BUZZER_VOLTAGE_U16,(((UWORD16)MeasureTestBuzzerVoltage) - MeasureBatteryBuzzer)); 
		}
		/*%C If the buzzer command is off, we measure the battery buzzer voltage */
		else
		{
			/*%C Battery voltage storage in mV (0 to 10000 mV)*/
			MeasureTestBuzzerVoltage = (MeasureTestBuzzerVoltage / 10) * BATTERY_VOLTAGE_DIVIDER;
			DB_ComputeWrite(MEASURE_BATTERY_BUZZER_VOLTAGE_U16,(UWORD16)(MeasureTestBuzzerVoltage));
		}
	}
/*----------------------------------------------------------------------------*/
/*%C Measure of Vbat voltage & storage in the base Compute							*/
/*%C MeasureVbat   = (R74+R75)/R75 * 5Vref-M /ConverterResolution * VbatDigit	*/
/*%C                   = (56+10.5)/10.5 * 5.000/1023 * VBatDigit					*/
/*%C                   = 0.030955 * VBatDigit (V)										*/
/*%C                   = 30.955 * VBatDigit (mV)	  									*/
	CalibratedValue = (30955 * (SWORD32)AD_Digit.MesVBat) / 100000;			
	DB_ComputeWrite(MEASURE_BATTERY_VOLTAGE_U16,(UWORD16)CalibratedValue);

/*----------------------------------------------------------------------------*/
/*%C Measure of Ivalve current & storage in the base Compute							*/
/*%C MeasureIvalve (A)  = (IvalveDigit * 5Vref /ConverterResolution) / R52 */
/*%C                    = (IvalveDigit * 5 /1024) / 10					*/
/*%C                    = (IvalveDigit * 5 /1024) / 10					*/
/*%C MeasureIvalve (mA) = (IvalveDigit * 5 * 1000 /1024) / 10	 */
	CalibratedValue = (500 * (SWORD32)AD_Digit.MesIValve) / 1024;
	DB_ComputeWrite(MEASURE_VALVE_CURRENT_U16,(UWORD16)CalibratedValue);			

/*----------------------------------------------------------------------------*/
/*%C Measure of watchdog voltage & storage in the base Compute						*/
/*%C MeasurePFI    = (R17/R18+R17/R19+1)* 5Vref-M /ConverterResolution  		*/
/*%C                 * PFIDigit - 5*R17/R7                			  				*/
/*%C               = (15/1.5 + 15/75 + 1)* 5/1023*PFIDigit - 5*15/75 		*/
/*%C               = 11.2 * 5 /1023 * PFIDigit-1 (V)									*/
/*%C               = 0.054740*PFIDigit - 1(V)										*/
/*%C               = 54.74 * PFIDigit - 1000 (mV)	   								*/
	CalibratedValue = (54740 * (SWORD32)AD_Digit.Pfi) / 100000 ;

/*%C If the calibrated value is upper than 10(AD_Digit.Pfi > 10), then */
/*%C Calibrated value take "calibrated value - 10"  */
	if (CalibratedValue >= 10)
	{
	    CalibratedValue = CalibratedValue - 10;
	}
	DB_ComputeWrite(MEASURE_PFI_VOLTAGE_U16, (UWORD16)CalibratedValue);


/*----------------------------------------------------------------------------*/
/*%C Measure of 24V voltage & storage in the base Compute							*/
/*%C MeasureSupply24v = (R12+R9)/R9 * 5Vref-M /ConverterResolution * 24VDigit */
/*%C                  = (7.5+1.5)/1.5 * 5.000/1023 * 24vDigit 				*/
/*%C                  = 29.32 * 24vDigit2+ 400		  */
	CalibratedValue = (2932 * (SWORD32)AD_Digit.Volt24) / 10000;
	CalibratedValue = CalibratedValue;
	DB_ComputeWrite(MEASURE_SUPPLY_24V_U16, (UWORD16)CalibratedValue); 
}
