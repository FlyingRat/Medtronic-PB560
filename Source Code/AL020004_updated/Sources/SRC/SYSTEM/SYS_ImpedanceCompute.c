/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_ImpedanceCompute.c                          		  		  	*/
/*													 						  							*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C             Compute the impedance of the battery   								*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/
#include "typedef.h"
#include "define.h"
#include "enum.h"
#include "DB_PowerSupply.h"
#include "DB_EEPROM_BAT.h"
#include "DB_Measurement.h"
#include "SYS_Gauge_Data.h"
#include"SYS_ImpedanceCompute.h"

/******************************************************************************/
/*                                FUNCTION BODY                               */
/******************************************************************************/


void SYS_ImpedanceCompute(void)
{
	static UWORD16 Impedance_Compute_IBat_Max = 0x0000;
	static UWORD16 Impedance_Compute_Vbat_Max = 0x0000;
	static UWORD16 Impedance_Compute_Ibat_Min = 0xFFFF;
	static UWORD16 Impedance_Compute_Vbat_Min = 0xFFFF;

	SWORD16 MeasureIBat = DB_Measurement_Read(I_BAT);	
	UWORD16 MeasureVBat = DB_Measurement_Read(MEASURE_VBAT);
	UWORD16 BatImpedance = DB_PowerSupply_Read(BAT_IMPEDANCE);
	
	UWORD32 ImpedanceCompute = 0 ;
	UWORD16 EepromImpedanceCompute = 0 ;

	/*%C To compute the impedance, the current must be positive						*/
	if( MeasureIBat < 0 )
	{
		MeasureIBat = -MeasureIBat;
	}

	/*%C New battery is detected																*/
	if(BatteryChangingDetectedFlagToImpedanceCompute == TRUE)
	{
		/*%C Locking the flag of new battery												*/
		BatteryChangingDetectedFlagToImpedanceCompute = FALSE;
		/*%C Launch the current and voltage sampling										*/ 
		TIM_StartDecounter16(SYS_IMPEDANCE_MEASURE_DELAY
										,TIME_IMPEDANCE_MEASURE_DELAY);
		/*%C RAZ variable																			*/
		Impedance_Compute_IBat_Max = 0x0000;
		Impedance_Compute_Vbat_Max = 0x0000;
		Impedance_Compute_Ibat_Min = 0xFFFF;
		Impedance_Compute_Vbat_Min = 0xFFFF;
	}
	/*%C Compute impedance when current and voltage sampling are finished		*/
	if ((TIM_ReadValue16(SYS_IMPEDANCE_MEASURE_DELAY)== 0)
		&&(TIM_ReadValue16(SYS_IMPEDANCE_PHASE_VBATMAX_DELAY)== 0)
		&&(TIM_ReadValue16(SYS_IMPEDANCE_PHASE_VBATMIN_DELAY)== 0))
	{	
		TIM_StartDecounter16(SYS_IMPEDANCE_MEASURE_DELAY
									,TIME_IMPEDANCE_MEASURE_DELAY);
		/*%C Impedance compute			 														*/
		ImpedanceCompute =(Impedance_Compute_Vbat_Max 
									- Impedance_Compute_Vbat_Min);
		ImpedanceCompute = ImpedanceCompute *100000 ;
		ImpedanceCompute = ImpedanceCompute 
								/ (Impedance_Compute_IBat_Max 
								- Impedance_Compute_Ibat_Min);
		
		/*%C If Impedance is no correct 														*/
			if (ImpedanceCompute > BAT_IMPEDANCE_MAX)
		{
			ImpedanceCompute = BAT_IMPEDANCE_MAX ;
		}
		else if(ImpedanceCompute < BAT_IMPEDANCE_MIN)
		{
			ImpedanceCompute = BAT_IMPEDANCE_MIN ;			
		}
		else
		{
			/*No Function */
		}
		/*%C Filter this  value 															*/
		ImpedanceCompute = ImpedanceCompute + BatImpedance * 3;
		ImpedanceCompute = ImpedanceCompute / 4;
		EepromImpedanceCompute = (UWORD16)ImpedanceCompute;
		/*%C Update Datas EEPROM 															*/
		DB_EEPROM_BAT_Write(DATA_VARIABLE_BAT_IMPEDANCE_1
											,EepromImpedanceCompute/256);
		DB_EEPROM_BAT_Write(DATA_VARIABLE_BAT_IMPEDANCE_2
											,EepromImpedanceCompute%256);
		/*%C Update data bases 																*/
		DB_PowerSupply_Write(BAT_IMPEDANCE,(UWORD16)ImpedanceCompute);	

		Impedance_Compute_IBat_Max = 0x0000;
		Impedance_Compute_Vbat_Max = 0x0000;
		Impedance_Compute_Ibat_Min = 0xFFFF;
		Impedance_Compute_Vbat_Min = 0xFFFF;
	}
	/*%C Current and voltage sampling during TIME_IMPEDANCE_MEASURE_DELAY		*/
	else
	{
		/*%C Store the I_Bat current min 													*/
		if(MeasureIBat < Impedance_Compute_Ibat_Min)
		{
		 	Impedance_Compute_Ibat_Min = MeasureIBat;
		 	Impedance_Compute_Vbat_Max  = 0x0000;
		 	TIM_StartDecounter16(SYS_IMPEDANCE_PHASE_VBATMIN_DELAY
									,TIME_IMPEDANCE_PHASE_DELAY);								
		}
		if ((TIM_ReadValue16(SYS_IMPEDANCE_PHASE_VBATMIN_DELAY)!= 0)
		   &&(MeasureVBat > Impedance_Compute_Vbat_Max))
		{
			Impedance_Compute_Vbat_Max  = MeasureVBat;	
		}
		/*%C Store the I_Bat current max													*/
		if(MeasureIBat > Impedance_Compute_IBat_Max)
		{
			Impedance_Compute_IBat_Max = MeasureIBat;
		 	TIM_StartDecounter16(SYS_IMPEDANCE_PHASE_VBATMAX_DELAY
									,TIME_IMPEDANCE_PHASE_DELAY);
			Impedance_Compute_Vbat_Min  = 0xFFFF;				
		}
		if ((TIM_ReadValue16(SYS_IMPEDANCE_PHASE_VBATMAX_DELAY)!= 0)
		   &&(MeasureVBat < Impedance_Compute_Vbat_Min))
		{
			Impedance_Compute_Vbat_Min  = MeasureVBat;	
		}
	}
}






	
