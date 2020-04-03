/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_Launch.c                                    		  		  */
/*													 						  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                    System management     								  */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/

#include "typedef.h"
#include "enum.h"
#include "define.h"
#define DECLARATION_GAUGE_DATA
#include "DB_PowerSupply.h"
#include "DB_EEPROM_BAT.h"
#include "DB_Control.h"
#include "SYS_Gauge_Data.h"
#include "SYS_Launch.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void SYS_Launch(void)
{
	
	static UBYTE FirstRun = TRUE;
	static UBYTE FirtsVentil = TRUE;

	UWORD16 Sampling_OK = DB_Control_Read(SAMPLING_OK);
	UWORD16 VentilAuthorization = DB_PowerSupply_Read(VENTIL_AUTHORIZATION);
	UWORD16 BatState = DB_PowerSupply_Read(BAT_STATE_U16);	
	UWORD16 UnknowBatteryFlag = DB_PowerSupply_Read(UNKNOWN_BATTERY_FLAG);
	UWORD16 NewBatFlag = DB_PowerSupply_Read(NEW_BAT_FLAG);
	UWORD16 BatAgeing	= DB_PowerSupply_Read(BAT_AGEING);
	UWORD16 BatImpedance	= DB_PowerSupply_Read(BAT_IMPEDANCE);
	UWORD16 CommunicationFailureFlag = DB_PowerSupply_Read(COMMUNICATION_FAILURE_FLAG);
	UWORD16 ReadDataEepromBatFailure = DB_PowerSupply_Read(READ_DATA_EEPROM_BAT_FAILURE);
	UWORD16 AbnormalIBatFlag = DB_PowerSupply_Read(ABNORMAL_IBAT_FLAG);
	
	UWORD16 DischargeBatCycles = 0 ;

	UWORD16 VariableCapacity1;
	UWORD16 VariableCapacity2;
	UWORD16 VariableNbrCycle1;
	UWORD16 VariableNbrCycle2;
	UWORD16 VarBatImpedance1; 
	UWORD16 VarBatImpedance2;	
	UWORD16 FirstBatteryUse;
	
/*%C If SAMPLING_OK = TRUE, then										      */
	if(Sampling_OK == TRUE)
	{ 
/*%C Leds management 													  	  */
		SYS_Led_Management();

/*%C 	If First Run														  */
		if (FirstRun == TRUE)
		{
/*%C 		Then Locking the flag of first run	: FirstRun = FALSE			  */
			FirstRun = FALSE;
/*%C 		Initialize TYPICAL_BAT_CAPACITY = 2400 for the BatCapacity compute*/ 
			TYPICAL_BAT_CAPACITY = CAPACITY_7S1P;

/*%C 		Initialize variables for the BAT_AGEING compute					  */ 
			DELTA_BAT_VOLTAGE = 0;
			DELTA_CAPACITY = 0;
			CAPACITY_AT_T1 = 0;
			VOLTAGE_AT_T1 = 0;
			SAMPLES_AGEING_NUMBER = 0;

			/*%C Initialize variables for the BAT_FEM compute				  */
			SUM_BAT_FEM = 0;
			SAMPLE_BAT_FEM = 0;
			DB_Control_Write(COMPUTE_CAPACITY_READY_FLAG,FALSE);

/*%C 		Initialize DISCHARGE_BAT_CYCLES = 0 							  */
			DB_PowerSupply_Write(DISCHARGE_BAT_CYCLES,0);
			
/*%C 		Initialize BAT_AGEING to BAT_AGEING_DEFAULT 				 	  */
			DB_PowerSupply_Write(BAT_AGEING, BAT_AGEING_DEFAULT);

/*%C 		Initialize BAT_IMPEDANCE to BAT_IMPEDANCE_DEFAULT				  */
			DB_PowerSupply_Write(BAT_IMPEDANCE, BAT_IMPEDANCE_DEFAULT);
		}
	
/*%C 	Else If NEW_BAT_FLAG = TRUE and READ_DATA_EEPROM_BAT_FAILURE = FALSE, */
		else if ((NewBatFlag == TRUE)
			&& (ReadDataEepromBatFailure == FALSE))
		{
/*%C 		Then Locking the flag of new battery NEW_BAT_FLAG = FALSE		  */
			DB_PowerSupply_Write(NEW_BAT_FLAG,FALSE);
			
			/*%C Set flag for detection of changing battery	and nex compute	  */
			BatteryChangingDetectedFlagToImpedanceCompute = TRUE;
			BatteryChangingDetectedFlagToCycleCompute = TRUE;
			BatteryChangingDetectedFlagToAgeingCompute = TRUE;

/*%C 		Initialize variables for the BAT_CAPACITY compute				  */
			SUM_BAT_FEM = 0;
			SAMPLE_BAT_FEM = 0;
			DB_Control_Write(COMPUTE_CAPACITY_READY_FLAG,FALSE);

/*%C 		Read the Typical BAT_CAPACITY in EEPROM Battery					  */ 
			VariableCapacity1 = DB_EEPROM_BAT_Read(DATA_FIXE_CAPACITE_1);
			VariableCapacity2 = DB_EEPROM_BAT_Read(DATA_FIXE_CAPACITE_2);
			TYPICAL_BAT_CAPACITY = (VariableCapacity1 * 256) + VariableCapacity2;		

/*%C 		Initialize variables for the BAT_AGEING compute					  */ 
			DELTA_BAT_VOLTAGE = 0;
			DELTA_CAPACITY = 0;
			CAPACITY_AT_T1 = 0;
			VOLTAGE_AT_T1 = 0;
			SAMPLES_AGEING_NUMBER = 0;
			
/*%C 		The goal is to improve repeatability of the capacity calculation.*/
/*			Quand la batterie est utilisée pour la première fois, on met un Ageing à 100% */
			BatAgeing = DB_EEPROM_BAT_Read(DATA_VARIABLE_BAT_AGEING_1);
			FirstBatteryUse = DB_EEPROM_BAT_Read(DATA_VARIABLE_FIRST_BATTEY_USE);
			if (FirstBatteryUse != TRUE)
			{
				DB_PowerSupply_Write(BAT_AGEING, 100);
				DB_EEPROM_BAT_Write(DATA_VARIABLE_BAT_AGEING_1,100);
				DB_EEPROM_BAT_Write(DATA_VARIABLE_FIRST_BATTEY_USE,TRUE);

			}
/*%C 		If DATA_VARIABLE_BAT_AGEING_1 > BAT_AGEING_MAX or 				  */
/*%C		DATA_VARIABLE_BAT_AGEING_1 < BAT_AGEING_MIN, then 				  */
			else if(	(BatAgeing > BAT_AGEING_MAX)
					|| (BatAgeing < BAT_AGEING_MIN))
			{
/*%C 			BAT_AGEING set to default value medium aeging				  */
/*%C			BAT_AGEING = BAT_AGEING_DEFAULT								  */
/*%C			DATA_VARIABLE_BAT_AGEING_1 = BAT_AGEING_DEFAULT				  */
				DB_PowerSupply_Write(BAT_AGEING, BAT_AGEING_DEFAULT);
				DB_EEPROM_BAT_Write(DATA_VARIABLE_BAT_AGEING_1,BAT_AGEING_DEFAULT);
			}
			else
			{
/*%C 			Else the value is in the limits, it's stored in data base 	  */
/*%C			BAT_AGEING = DATA_VARIABLE_BAT_AGEING_1					      */
				DB_PowerSupply_Write(BAT_AGEING,BatAgeing);
			}
/*%C		End if 															  */

/*%C 		Initialize DISCHARGE_BAT_CYCLES 								  */
			VariableNbrCycle1 = DB_EEPROM_BAT_Read(DATA_VARIABLE_NBR_CYCLE_1);
			VariableNbrCycle2 = DB_EEPROM_BAT_Read(DATA_VARIABLE_NBR_CYCLE_2);
			DischargeBatCycles = (VariableNbrCycle1*256) + VariableNbrCycle2;
/*%C 		Update data bases 												  */
			DB_PowerSupply_Write(DISCHARGE_BAT_CYCLES,DischargeBatCycles);

/*%C 		Read BAT_IMPEDANCE in EEPROM Battery 							  */
/*%C		BatImpedance = (DATA_VARIABLE_BAT_IMPEDANCE_1* 256) +  	          */
/*%C		DATA_VARIABLE_BAT_IMPEDANCE_2 		  							  */
			VarBatImpedance1 = DB_EEPROM_BAT_Read(DATA_VARIABLE_BAT_IMPEDANCE_1);
			VarBatImpedance2 = DB_EEPROM_BAT_Read(DATA_VARIABLE_BAT_IMPEDANCE_2);
			BatImpedance = (VarBatImpedance1* 256) + VarBatImpedance2 ;
/*%C		if BatImpedance > BAT_IMPEDANCE_MAX or 						      */
/*%C		BatImpedance < BAT_IMPEDANCE_MIN 								  */
			if((BatImpedance > BAT_IMPEDANCE_MAX)
				||(BatImpedance < BAT_IMPEDANCE_MIN))
			{
/*%C 			Then default value for impedence is stored 				      */
/*%C			BAT_IMPEDANCE = BAT_IMPEDANCE_DEFAULT						  */
/*%C			DATA_VARIABLE_BAT_IMPEDANCE_1 = BAT_IMPEDANCE_DEFAULT/256     */
/*%C			DATA_VARIABLE_BAT_IMPEDANCE_2 = BAT_IMPEDANCE_DEFAULT%256     */
				DB_PowerSupply_Write(BAT_IMPEDANCE, BAT_IMPEDANCE_DEFAULT);			
				DB_EEPROM_BAT_Write(DATA_VARIABLE_BAT_IMPEDANCE_1
												,BAT_IMPEDANCE_DEFAULT/256);
				DB_EEPROM_BAT_Write(DATA_VARIABLE_BAT_IMPEDANCE_2
												,BAT_IMPEDANCE_DEFAULT%256);
			}
			else
			{
/*%C 			BAT_IMPEDANCE = BatImpedance								 */
				DB_PowerSupply_Write(BAT_IMPEDANCE,BatImpedance);
			}
/*%C		End if 															 */
		}
		else
		{
			/* No Function 													 */
		}
/*%C	End if 																 */
/*%C 	Compute the capacity of battery in discharge						 */
/*%C 	if BAT_STATE = BAT_DISCHARGE, then								  	 */
		if (BatState == BAT_DISCHARGE)
		{
/*%C 		Calcul de l'impedance de la batterie							 */
			SYS_ImpedanceCompute();
			/* Calcul de la capacité restante (Abaque)						 */
/*%C 		Calcul de l'effondrement de la tension batterie en décharge.*/
			SYS_Voltage_Colapse_Compensation();
/*%C 		Calcul de la capacité restante en %								 */				   								
			SYS_Gas_Gauge_Percent();
/*%C 		Calcul de la jauge en minute				 					 */
/*%C 		Minute gauge compute											 */
			SYS_Gas_Gauge_Minute();
/* 			Calcul du veillissement											 */
/*%C 		Aeging compute													 */
			SYS_Bat_Ageing();
/*%C 		Comptage du nombre de cycle de décharge de la batterie 			 */
/*%C 		Charging & discharging cycles compute							 */				
			SYS_Charge_Discharge_Compute();
		}
/*%C Else */
		else
		{	
/*%C 		Set flag to the next discharge compute							 */
			BatteryChangingDetectedFlagToImpedanceCompute = TRUE;
			BatteryChangingDetectedFlagToCycleCompute = TRUE;
			BatteryChangingDetectedFlagToAgeingCompute = TRUE;

/*%C 		Start a 2 minutes delay to next compute Bat ageing				 */
			TIM_StartDecounter32(SYS_BAT_AGEING_READY_DELAY
												, TIME_BAT_AGEING_DELAY);
/*%C 		Start a 2 minutes delay to next compute Bat cycle				 */
			TIM_StartDecounter32(SYS_BAT_CYCLE_READY_DELAY
												, TIME_BAT_CYCLE_READY_DELAY);
/*%C 		Out of discharge condition, there is no battery voltage colapse. */
			DB_PowerSupply_Write(BATTERY_VOLTAGE_COLAPSE,0);
/*%C 		Calcul de la capacité restante en %	   					 		 */
			SYS_Gas_Gauge_Percent();
		}
/*%C	End if 																 */
	}
	else
	{
		/* No Function */
	}
/*%C End if 																 */

/*%C Detection of a new ventilation											 */
/*%C If VENTIL_AUTHORIZATION = TRUE and BAT_STATE_U16 = BAT_DISCHARGE and	 */
/*%C FirtsVentil = TRUE, then 												 */
	if ((VentilAuthorization == TRUE)
		&& (BatState == BAT_DISCHARGE)
		&& (FirtsVentil == TRUE))
	{
/*%C	FirtsVentil = FALSE													  */
		FirtsVentil = FALSE;
/*%C 	Start a 2 minutes delay												  */
		TIM_StartDecounter32(SYS_GAUGE_MINUTE_READY_DELAY
												, TIME_GAUGE_MINUTE_READY_DELAY);
	}
/*%C Else if VENTIL_AUTHORIZATION = FALSE or BAT_STATE_U16 <> BAT_DISCHARGE   */
	else if	((VentilAuthorization == FALSE)
				|| (BatState != BAT_DISCHARGE))
	{
/*%C	Then FirtsVentil = TRUE												  */
		FirtsVentil = TRUE;
	}
	else
	{
		/* No Function	*/
	}
/*%C End if 																  */
/* Authorisation du l'affichage des caculs de jauge						  	  */
/* Si on est en ventilation sur batterie									  */
/* Si Communication Failure == Flase										  */
/* Si la batterie est reconnue												  */
/*%C If  VENTIL_AUTHORIZATION = TRUE and delay of gauge avaibility is over and*/
/*%C BAT_STATE_U16 = BAT_DISCHARGE and COMMUNICATION_FAILURE_FLAG = FALSE	  */
/*%C and UNKNOWN_BATTERY_FLAG = FALSE and ABNORMAL_IBAT_FLAG = FALSE, then	  */
	if(	(VentilAuthorization == TRUE)
		&& (TIM_ReadValue32(SYS_GAUGE_MINUTE_READY_DELAY) == 0 )
		&& (BatState == BAT_DISCHARGE)
		&& (CommunicationFailureFlag == FALSE)
		&& (UnknowBatteryFlag == FALSE)
		&&	(AbnormalIBatFlag == FALSE))
	{
/*%C	GAUGE_AVALAIBLE_U16 = TRUE											  */
		DB_PowerSupply_Write (GAUGE_AVALAIBLE_U16, TRUE);
	}
/*%C Esle if VENTIL_AUTHORIZATION = FALSE or  								  */
/*%C COMMUNICATION_FAILURE_FLAG = FALSE or UNKNOWN_BATTERY_FLAG = TRUE  or    */
/*%C BAT_STATE_U16 <> BAT_DISCHARGE or ABNORMAL_IBAT_FLAG = TRUE, then	      */
	else if(	(VentilAuthorization == FALSE)
			|| (CommunicationFailureFlag == TRUE)
			|| (UnknowBatteryFlag == TRUE)
			|| (BatState != BAT_DISCHARGE)
			||	(AbnormalIBatFlag == TRUE))
	{
/*%C 	GAUGE_AVALAIBLE_U16 = FALSE 										  */
		DB_PowerSupply_Write (GAUGE_AVALAIBLE_U16, FALSE);
	}
	else
	{
		/* No Function 														  */
	}
/*%C End if 																  */		
}
