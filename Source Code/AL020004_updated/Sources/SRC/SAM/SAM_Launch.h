/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SAM_Launch.h            					              				*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C        			  										      		  					*/
/*%C          																  						*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/
#ifdef DECLARATION_SAM_LAUNCH

	#ifndef SAM_LAUNCH_H
	#define SAM_LAUNCH_H

		static UWORD16 VACDC_Can_Samples[NB_SAMPLES_VACDC];
		static UWORD16 VDC_Can_Samples[NB_SAMPLES];
		static UWORD16 VBAT_Can_Samples[NB_SAMPLES];
		static UWORD16 IBAT_Can_Samples[NB_SAMPLES];
		static UWORD16 VCHARGE_Can_Samples[NB_SAMPLES];

		extern SWORD16 SAM_Temperature_Conversion(UWORD16 CanValue, 
												  e_SAM_Temperature TemperatureMesureType);
		
		extern UWORD16 SAM_Voltage_Conversion(UWORD16 CanValue, 
									          e_SAM_Voltage VoltageMeasureType);
		
		extern SWORD16 SAM_Current_Conversion(UWORD16 CanValue ,
									          e_SAM_Current CurrentMesureType);
		
		extern void DB_Measurement_Write(e_DB_Measurement Id, UWORD16 Value);
		extern UWORD16 DB_Measurement_Read(e_DB_Measurement Id);
		extern void TIM_StartDecounter16(e_TIM_TABLE_ID_16,UWORD16);
		extern void TIM_StartDecounter32(e_TIM_TABLE_ID_32 offset_table,UWORD32 value);
		extern void DB_Config_Write(e_DB_Config Id, UWORD16 Value);
		extern UWORD16 TIM_ReadValue16(e_TIM_TABLE_ID_16);
		extern void DB_Control_Write(e_DB_Control Id, UWORD16 Value);
		extern UWORD16 DB_Control_Read(e_DB_Control Id);
		extern UWORD16 DB_PowerSupply_Read(e_DB_POWERSUPPLY Id);
		extern void DB_PowerSupply_Write(e_DB_POWERSUPPLY Id, UWORD16 Value);

	

	#endif
#else

	#ifndef SAM_LAUNCH_H
	#define SAM_LAUNCH_H

		extern static UWORD16 VACDC_Can_Samples[];
		extern static UWORD16 VDC_Can_Samples[];
		extern static UWORD16 VBAT_Can_Samples[];
		extern static UWORD16 IBAT_Can_Samples[];
		extern static UWORD16 VCHARGE_Can_Samples[];

		extern SWORD16 SAM_Temperature_Conversion(UWORD16 CanValue, 
												  e_SAM_Temperature TemperatureMesureType);
		
		extern UWORD16 SAM_Voltage_Conversion(UWORD16 CanValue, 
									          e_SAM_Voltage VoltageMeasureType);
		
		extern SWORD16 SAM_Current_Conversion(UWORD16 CanValue ,
									          e_SAM_Current CurrentMesureType);
		
		extern void DB_Measurement_Write(e_DB_Measurement Id, UWORD16 Value);
		extern UWORD16 DB_Measurement_Read(e_DB_Measurement Id);
		extern void TIM_StartDecounter16(e_TIM_TABLE_ID_16,UWORD16);
		extern void TIM_StartDecounter32(e_TIM_TABLE_ID_32 offset_table,UWORD32 value);
		extern void DB_Config_Write(e_DB_Config Id, UWORD16 Value);
		extern UWORD16 TIM_ReadValue16(e_TIM_TABLE_ID_16);
		extern void DB_Control_Write(e_DB_Control Id, UWORD16 Value);
		extern UWORD16 DB_Control_Read(e_DB_Control Id);
		extern UWORD16 DB_PowerSupply_Read(e_DB_POWERSUPPLY Id);
		extern void DB_PowerSupply_Write(e_DB_POWERSUPPLY Id, UWORD16 Value);


	#endif
#endif


