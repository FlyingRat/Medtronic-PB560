/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_Compute.h					   				                  		*/
/*                                                            				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C Functionnal description : 	datas declaration for compute base				*/
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter : 			None			      	                       	*/
/*%IO Input/Output Parameter : 	None 	        			                  		*/
/*%O 	Output Parameter : 			None				            				  		*/
/******************************************************************************/
#ifndef COMPUTE_H
#define COMPUTE_H
/******************************************************************************/
/*                     ENUM DECLARATION				                           */
/******************************************************************************/
/* Compute base */
//
// These enumerations cannot be changed without affecting PB VTS. 
// DO NOT delete an enumerator, replace it with COMPUTED_USED_XX_U16
// instead. This allows PB VST to maintain backwards compatibility with
// older vent software.
//
typedef enum
{
	MEASURE_VALVE_PRESSURE_S16=0,
	FILTER_VALVE_PRESSURE_S16,
	MEASURE_INTERNAL_PRESSURE_S16,
	FILTER_INTERNAL_PRESSURE_S16,
	MEASURE_PATIENT_PRESSURE_PROXI_S16,
	FILTER_PATIENT_PRESSURE_PROXI_S16,
	MEASURE_PATIENT_PRESSURE_S16,
	FILTER_PATIENT_PRESSURE_S16,
	MEASURE_QINSP_S16,
	FILTER_QI_S16,
	FILTER_QI_LOW_S16,
	MEASURE_QEXH_S16,
	FILTER_QE_S16,
	COMPUTED_VTE_U16,
	COMPUTED_VTE_INSP_U16,
	COMPUTED_PIP_U16,
	COMPUTED_PEEP_U16,
  	COMPUTED_FIO2,
  	MEASURE_FIO2,
	MEASURE_IE_NUMERATOR_U16,	  
	MEASURE_IE_DENOMINATOR_U16,
	MEASURE_TI_U16,
	MEASURE_TI_HMI_U16,
	MEASURE_TE_U16,
	MEASURE_R_U16,
	MEASURE_SPEED_BLOWER_U16,
	FILTER_SPEED_BLOWER_S16,
	COMPUTED_BATTERY_LEVEL_U16,  /* Charge level in % */
	MEASURE_SUPPLY_5V_U16,
	MEASURE_SUPPLY_24V_U16,
	MEASURE_TEST_BUZZER_VOLTAGE_U16, 
 	MEASURE_BUZZER_VOLTAGE_U16, 
 	MEASURE_BATTERY_BUZZER_VOLTAGE_U16,
	MEASURE_PFI_VOLTAGE_U16,
	COMPUTED_PI_SET_POINT_U16,
	COMPUTED_VTI_EXH_S16,
	MEASURE_SPO2_U16,
	MEASURE_HR_U16,
	COMPUTED_LEAK_U16,
	COMPUTED_LEAK_HMI_U16,
	CURVE_CORRECTED_VT_WOB_U16,
	CURVE_CORRECTED_FLOW_S16,
	COMPUTED_TEMP_S16,	 /* Battery temperature */
	COMPUTED_VTI_U16,
	COMPUTED_USED_44_U16,
	COMPUTED_USED_45_U16,
	MEASURE_BATTERY_VOLTAGE_U16,
	COMPUTED_VMI_U16,
	COMPUTED_VME_U16,
	AVERAGE_PRESSURE_U16,
   	MEASURE_ABSOLUTE_PRESSURE_U16,
   	MEASURE_BLOWER_TEMPERATURE_S16,
	COMPUTED_RISE_TIME_U16,
	MEASURE_IT_U16,
	MEASURE_BATTERY_CAPACITY_U16,
	COMPUTED_PULSE_U16,
	COMPUTE_CORRECTED_Q,
   COMPUTED_TI_CONTROL_U16,
  	FILTER_QO2_S16,
   FILTER_PRESSURE_O2_S16,
   MEASURE_PRESSURE_O2_S16,
   MEASURE_QO2_S16,
   COMPUTED_IE_NUMERATOR_U16,               
   COMPUTED_IE_DENOMINATOR_U16,
	COMPUTE_QEE_S16,
   COMPUTED_I_T_U16,
   MEAS_ABS_PRESS_MMHG_U16,
   COMPUTED_RATE_U16,
   BLOWER_COMMAND_U16, 
	MEASURE_ZERO_VALUE_U16,
	COMPUTED_P_VALVE_MAX_U16,
	CUMUL_PRESS_INSP_S16,
	ESTIMATED_PROXIMAL_PRESSURE_S16,
	MEASURE_QINSP_LEAKCORRECTED_S16,
	MEASURE_VALVE_CURRENT_U16,
	MEAN_INSP_VALVE_CURRENT_U16,
	VALVE_COMMAND_INIT_U16,
	VALVE_COMMAND_MIN_U16,
	VALVE_COMMAND_MAX_U16,
	VALVE_COMMAND_COEFF_U16,
	VALVE_COMMAND_U16,
	LPF_PATIENT_PRESSURE_S16,
    COMPUTED_LPF_PIP_U16,
    LEAK_TEST_QI_S16,
    LEAK_TEST_RESULT_U16,
	end_of_db_compute_table
} e_DB_COMPUTE;

#ifdef DECLARATION_COMPUTE_BASE
/******************************************************************************/
/*                     CONSTANT DECLARATION			                           */
/******************************************************************************/
/* Base Compute Array*/
UWORD16 DB_Compute[end_of_db_compute_table];

#else
/******************************************************************************/
/*                     CONSTANT DECLARATION			                         	*/
/******************************************************************************/
/* Base Compute Array*/
extern UWORD16 DB_Compute[end_of_db_compute_table];
#endif

#endif
