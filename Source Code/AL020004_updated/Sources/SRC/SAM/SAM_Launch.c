/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SAM_Launch.c													  				*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                   AD conversion module :                      				*/
/*%C     One channel of the AD converter is loaded in one step of Scheduler. 	*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


/******************************************************************************/
/*                                INCLUDE FILES								  			*/
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "define.h"
#include "DB_Measurement.h"
#include "DB_PowerSupply.h"
#include "DB_Control.h"
#include "DB_Config.h"
#include "CAN_Channel_Acquisition.h"
#define DECLARATION_SAM_LAUNCH
#include "SAM_Launch.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void SAM_Launch (void)
{
	
	static e_BOOL FirstRun = TRUE;
	static UWORD16 SampleFiltrage = 0;
	static UWORD16 SampleFiltrageVACDC = 0;
	static UWORD16 SampleAverage = 0;
	static UWORD32 AverageCurrentCompute = 0;

	UWORD16 VentilAuthorization = DB_PowerSupply_Read(VENTIL_AUTHORIZATION);
	UWORD16 Discharge_Bat_State =  DB_Control_Read(DISCHARGE_BAT_STATE);
	UWORD16 ChargeBatState = DB_Control_Read(CHARGE_BAT_STATE);

	UWORD16 Compute16 = 0;
	SWORD16 ComputeS16 = 0;

	UWORD16 Compute16_VACDC = 0;
	UWORD32 Cumul32VACDC	= 0;
	UWORD16 Compute16_VDC = 0;	
	UWORD16 Compute16_VBAT = 0;
	UWORD16 Compute16_VCHARGE = 0;
	UWORD16 Compute16_IBAT = 0;

	UBYTE Loop = 0;
	UWORD16 Sam_Sampling_Ready_Delay = 0;

/*%C At the first start an initialization delay is needed to wait for sampling 																					*/
	if (FirstRun == TRUE)
	{
		TIM_StartDecounter16(SAM_SAMPLING_READY_DELAY,TIME_SAMPLING_READY_DELAY);
		FirstRun = FALSE;
	}
	else
	{
		Sam_Sampling_Ready_Delay = TIM_ReadValue16(SAM_SAMPLING_READY_DELAY);
		if (Sam_Sampling_Ready_Delay == 0)
		{
			DB_Control_Write(SAMPLING_OK,TRUE);			
			
		}
		else
		{
			DB_Control_Write(SAMPLING_OK,FALSE);
		}
	}

/*%C AD Traitement 																				*/

/******************************************************************************/
	/*%C Traitement de la voie 0 température  batterie	*/
	Compute16 = CAN_Previous_Acquisition[Can_Acquisition_TempBat];
	Compute16 = Compute16 * 3;
	Compute16 = Compute16 + CAN_Acquisition[Can_Acquisition_TempBat];
	Compute16 = Compute16 / 4;
	CAN_Previous_Acquisition[Can_Acquisition_TempBat] 
					= CAN_Acquisition[Can_Acquisition_TempBat];
	ComputeS16 = SAM_Temperature_Conversion(Compute16, Sampling_T_Battery);
	DB_Measurement_Write(BATTERY_TEMP, ComputeS16);
	DB_PowerSupply_Write(TEMP_BAT_S16, ComputeS16);
/******************************************************************************/


/******************************************************************************/
	/*%C Traitement de la voie 2 Mesure 3V3	 											*/
	Compute16 = CAN_Previous_Acquisition[Can_Acquisition_3V3];
	Compute16 = Compute16 * 3;
	Compute16 = Compute16 + CAN_Acquisition[Can_Acquisition_3V3];
	Compute16 = Compute16 / 4;
	CAN_Previous_Acquisition[Can_Acquisition_3V3] 
					= CAN_Acquisition[Can_Acquisition_3V3];
	ComputeS16 = SAM_Voltage_Conversion(Compute16, Sampling_3V3);
	DB_Measurement_Write(MEASURE_3V3, ComputeS16);
/******************************************************************************/

	
/******************************************************************************/
	/*%C Traitement de la voie 4 Mesure VACDC	 											*/
	Compute16 = CAN_Acquisition[Can_Acquisition_VACDC];
	/*%C Tableau pour filtrage */
	VACDC_Can_Samples[SampleFiltrageVACDC] = Compute16;
	ComputeS16 = SAM_Voltage_Conversion(Compute16, Sampling_VACDC);
	DB_Measurement_Write(MEASURE_VACDC, ComputeS16);
/******************************************************************************/
	

/******************************************************************************/	
	/*%C Traitement de la voie 5 I_BAT 														*/
	Compute16 = CAN_Previous_Acquisition[Can_Acquisition_IBat];
	Compute16 = Compute16 * 3;
	Compute16 = Compute16 + CAN_Acquisition[Can_Acquisition_IBat];
	Compute16 = Compute16 / 4;
	/* Tableau pour filtrage */
	if(SampleFiltrage < NB_SAMPLES)
	{
		IBAT_Can_Samples[SampleFiltrage] = CAN_Acquisition[Can_Acquisition_IBat];
	}
	/*%C else, nothing is done */
	CAN_Previous_Acquisition[Can_Acquisition_IBat]
					= CAN_Acquisition[Can_Acquisition_IBat];
	ComputeS16 = SAM_Current_Conversion(Compute16, Sampling_I_Battery);
	DB_Measurement_Write(I_BAT, ComputeS16);
/******************************************************************************/


/******************************************************************************/	
	/*%C Traitement de la voie 6 Mesure VCharge	 										*/ 
	Compute16 = CAN_Previous_Acquisition[Can_Acquisition_VCharge];
	Compute16 = Compute16 * 3;
	Compute16 = Compute16 + CAN_Acquisition[Can_Acquisition_VCharge];
	Compute16 = Compute16 / 4;
	/*%C Tableau pour filtrage */
	if (SampleFiltrage < NB_SAMPLES)
	{
		VCHARGE_Can_Samples[SampleFiltrage] = CAN_Acquisition[Can_Acquisition_VCharge];
	}
	/*%C else, nothing is done */
	CAN_Previous_Acquisition[Can_Acquisition_VCharge] 
					= CAN_Acquisition[Can_Acquisition_VCharge];
	ComputeS16 = SAM_Voltage_Conversion(Compute16, Sampling_VCharge);
	DB_Measurement_Write(MEASURE_VCHARGE, ComputeS16);
/******************************************************************************/


/******************************************************************************/	
	/*%C Traitement de la voie 7 Mesure TEMP AMB	 										*/
	Compute16 = CAN_Previous_Acquisition[Can_Acquisition_TempAmb];
	Compute16 = Compute16 * 3;
	Compute16 = Compute16 + CAN_Acquisition[Can_Acquisition_TempAmb];
	Compute16 = Compute16 / 4;
	CAN_Previous_Acquisition[Can_Acquisition_TempAmb] 
					= CAN_Acquisition[Can_Acquisition_TempAmb];
	ComputeS16 = SAM_Temperature_Conversion(Compute16, Sampling_T_Ambiant);
	DB_Measurement_Write(TEMP_AMB, ComputeS16);
	DB_PowerSupply_Write(AMBIENT_TEMP_S16 , ComputeS16);
/******************************************************************************/


/******************************************************************************/	
	/*%C Traitement de la voie 8 Mesure VDC	 											*/
	Compute16 = CAN_Previous_Acquisition[Can_Acquisition_VDC];
	Compute16 = Compute16 * 3;
	Compute16 = Compute16 + CAN_Acquisition[Can_Acquisition_VDC];
	Compute16 = Compute16 / 4;
	/*%C Tableau pour filtrage */
	if (SampleFiltrage < NB_SAMPLES)
	{
		VDC_Can_Samples[SampleFiltrage] = CAN_Acquisition[Can_Acquisition_VDC];
	}
	/*%C else, nothing is done */

	CAN_Previous_Acquisition[Can_Acquisition_VDC] 
					= CAN_Acquisition[Can_Acquisition_VDC];	
	ComputeS16 = SAM_Voltage_Conversion(Compute16, Sampling_VDC);
	DB_Measurement_Write(MEASURE_VDC, ComputeS16);
/******************************************************************************/


/******************************************************************************/
	/*%C Traitement de la voie 9 Mesure 24VUTIL	 										*/
	Compute16 = CAN_Previous_Acquisition[Can_Acquisition_24VUtil];
	Compute16 = Compute16 * 3;
	Compute16 = Compute16 + CAN_Acquisition[Can_Acquisition_24VUtil];
	Compute16 = Compute16 / 4;
	CAN_Previous_Acquisition[Can_Acquisition_24VUtil] 
					= CAN_Acquisition[Can_Acquisition_24VUtil];
	ComputeS16 = SAM_Voltage_Conversion(Compute16, Sampling_24V);
	DB_Measurement_Write(MEASURE_24VUTIL, ComputeS16);
/******************************************************************************/


/******************************************************************************/	
	/*%C Traitement de la voie 10 Mesure 5V	 											*/
	Compute16 = CAN_Previous_Acquisition[Can_Acquisition_5V];
	Compute16 = Compute16 * 3;
	Compute16 = Compute16 + CAN_Acquisition[Can_Acquisition_5V];
	Compute16 = Compute16 / 4;
	CAN_Previous_Acquisition[Can_Acquisition_5V] 
					= CAN_Acquisition[Can_Acquisition_5V];
	ComputeS16 = SAM_Voltage_Conversion(Compute16, Sampling_5V);
	DB_Measurement_Write(MEASURE_5V, ComputeS16);
/******************************************************************************/


/******************************************************************************/	
	/*%C Traitement de la voie 11 Mesure VBAT	 											*/
	Compute16 = CAN_Previous_Acquisition[Can_Acquisition_VBat];
	Compute16 = Compute16 * 3;
	Compute16 = Compute16 + CAN_Acquisition[Can_Acquisition_VBat];
	Compute16 = Compute16 / 4;
	/*%C Tableau pour filtrage */
	if (SampleFiltrage < NB_SAMPLES)
	{
		VBAT_Can_Samples[SampleFiltrage] = CAN_Acquisition[Can_Acquisition_VBat];
	}
	/*%C else, nothing is done */
	CAN_Previous_Acquisition[Can_Acquisition_VBat] 
					= CAN_Acquisition[Can_Acquisition_VBat];
	ComputeS16 = SAM_Voltage_Conversion(Compute16, Sampling_VBAT);
	DB_Measurement_Write(MEASURE_VBAT, ComputeS16);
/******************************************************************************/
		

/******************************************************************************/
	/*%C Increment filtrage value 															*/
	SampleFiltrage = SampleFiltrage + 1;
	SampleFiltrageVACDC = SampleFiltrageVACDC + 1;
	SampleFiltrageVACDC = SampleFiltrageVACDC % NB_SAMPLES_VACDC;
	
/******************************************************************************/


/******************************************************************************/

	/*Filtrage par une fenetre glissante de 80 valeurs*/
	Cumul32VACDC = 0;
	for (Loop = 0 ; Loop < NB_SAMPLES_VACDC ; Loop++)
	{
		Cumul32VACDC = Cumul32VACDC + (UWORD32)VACDC_Can_Samples[Loop];	
	}
	/*%C Filtrage VACDC 																		*/
	Cumul32VACDC = Cumul32VACDC / NB_SAMPLES_VACDC;
	Cumul32VACDC = SAM_Voltage_Conversion(Cumul32VACDC, Sampling_VACDC);
	DB_Measurement_Write(VACDC_MEASURE_FILTERED,(UWORD16)Cumul32VACDC);	


	if (SampleFiltrage >= NB_SAMPLES)
	{
	
		/*%C Filtrage des mesures tensions 													*/
		for (Loop = 0;Loop < NB_SAMPLES;Loop++)
		{
			Compute16_VDC = Compute16_VDC + VDC_Can_Samples[Loop];
			Compute16_VBAT = Compute16_VBAT + VBAT_Can_Samples[Loop];
			Compute16_VCHARGE = Compute16_VCHARGE + VCHARGE_Can_Samples[Loop];
			Compute16_IBAT = Compute16_IBAT + IBAT_Can_Samples[Loop];
		}

		/*%C Filtrage VDC 																		*/
		Compute16_VDC = Compute16_VDC / NB_SAMPLES;	
		ComputeS16 = SAM_Voltage_Conversion(Compute16_VDC, Sampling_VDC);
		DB_Measurement_Write(VDC_MEASURE_FILTERED,ComputeS16);	

		/*%C Filtrage VBAT 																		*/
		Compute16_VBAT = Compute16_VBAT / NB_SAMPLES;	
		ComputeS16 = SAM_Voltage_Conversion(Compute16_VBAT, Sampling_VBAT);
		DB_Measurement_Write(VBAT_MEASURE_FILTERED,ComputeS16);	
		DB_PowerSupply_Write(V_BAT_U16,ComputeS16);	

		/*%C Filtrage VCHARGE																	*/
		Compute16_VCHARGE = Compute16_VCHARGE / NB_SAMPLES;	
		ComputeS16 = SAM_Voltage_Conversion(Compute16_VCHARGE, Sampling_VCharge);
		DB_Measurement_Write(VCHARGE_MEASURE_FILTERED,ComputeS16);
		
		/*%C Filtrage IBAT 																		*/
		Compute16_IBAT = Compute16_IBAT / NB_SAMPLES;	
		ComputeS16 = SAM_Current_Conversion(Compute16_IBAT, Sampling_I_Battery);			
		DB_Measurement_Write(IBAT_MEASURE_FILTERED,ComputeS16);	

		SampleFiltrage = 0;
	}	
/******************************************************************************/


/******************************************************************************/
	/*%C Average I_BAT 																			*/
	if (	(Discharge_Bat_State == TRUE)
		|| (ChargeBatState == TRUE))
	{
		/*%C Increment average value 															*/
		SampleAverage = SampleAverage + 1;
		/*%C Compute average current 															*/
		AverageCurrentCompute = CAN_Previous_Acquisition[Can_Acquisition_IBat]
											+ AverageCurrentCompute;					
		if (SampleAverage >= 6000)
		{
			AverageCurrentCompute = AverageCurrentCompute / 6000;
			Compute16= (UWORD16)AverageCurrentCompute;
			ComputeS16 = SAM_Current_Conversion(Compute16,Sampling_I_Battery);
			DB_Measurement_Write(IBAT_AVERAGE, ComputeS16);					
			AverageCurrentCompute = 0;
			SampleAverage = 0;
			
			/*%C If battery an Average Ibat value is computed, the coulomb compute is allowed*/	
			DB_Measurement_Write(COULOMB_COMPUTE_DISCHARGE_READY_FLAG,TRUE);
			DB_Measurement_Write(COULOMB_COMPUTE_CHARGE_READY_FLAG,TRUE);
		}
		/*%C else, nothing is done                 										*/										
	}	
	else
	/*%C If battery is in IDLE status, the coulomb compute is not allowed*/
	{
			DB_Measurement_Write(COULOMB_COMPUTE_DISCHARGE_READY_FLAG,FALSE);
			DB_Measurement_Write(COULOMB_COMPUTE_CHARGE_READY_FLAG,FALSE);
	}																
}
