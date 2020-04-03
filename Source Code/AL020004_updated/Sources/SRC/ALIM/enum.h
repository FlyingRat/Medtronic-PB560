/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : enum.h                                                         */
/*													 						  							*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


#ifndef ENUM_H
#define ENUM_H

typedef enum 
{ 
	FALSE=0,
	TRUE 
} e_BOOL;

/******************  use for "counters" *************************************/
typedef enum
{

	DRV_RS232_TRANSMIT_PERIOD = 0,
	TIME_EEPROM_COPY_SCRATCHPAD,
	TIME_EEPROM_INIT,
	SAM_SAMPLING_READY_DELAY,
	TIM_NO_FRAME,
	TIM_SPI_WRONG_FRAME,
	CHARGE_INIT_PERIOD,
	CHARGE_CUT_OFF_DELAY,
	TIM_CHARGE_RUNNING,
	TIM_NO_BAT,
	TIM_MEASURES_OUT_OF_BOUNDS,
	TIM_5V_FAIL,
	TIM_24V_FAIL,
	TIM_VACDC_FAIL,
	TIM_BAT_OPENED,
	TIM_VDC_FAIL,
	TIM_COOLING_FAN_FAIL,
	TIM_ABNORMAL_IBAT,
	TIM_UNKNOW_BATTERY,
	TIM_NO_COMMUT,
	SYS_COULOMB_COMPUTE_DELAY,
	SYS_IMPEDANCE_MEASURE_DELAY,  		
	SYS_BLINK_BAT_LED,					// Période clignotement ON led batterie en charge
	SYS_TOTAL_CAPACITY_READY_DELAY,		
	SEC_CHARGE_FAIL,						/* Temporisation du défaut de charge */	
	SEC_END_OF_START,
	FAN_SPEED_MEASURE_OVERFLOW,
	SYS_IMPEDANCE_PHASE_VBATMAX_DELAY,
	SYS_IMPEDANCE_PHASE_VBATMIN_DELAY,
	end_of_table_cnt_decnt_16
} e_TIM_TABLE_ID_16; 

typedef enum
{	
	DRV_RS232_TIME_OUT = 0,
	DRV_RS232_CONTROL_TIME_OUT,
	TIME_ACCESS_EEPROM_WRITE,
	SYS_GAUGE_MINUTE_READY_DELAY,
	SYS_BATTERY_VOLTAGE_OBSERVATION_PERIOD,
	SYS_BAT_AGEING_READY_DELAY,
	SYS_BAT_CYCLE_READY_DELAY,
	end_of_table_cnt_decnt_32
} e_TIM_TABLE_ID_32; 

typedef enum
{
  COUNT = 0,
  DECOUNT
} e_TYPE_USE_TIMER;

/******************  use for "RS232" *************************************/
typedef enum
{

	/*%C enum state transmission monitorage */
	DRV_RS232_TRANSMIT_MONITORING = 0,
	DRV_RS232_TRANSMIT_STOP,	 
	DRV_RS232_TRANSMIT_CONTROL 

}e_DRV_RS232_STATE;


typedef enum
{

	/*%C enum frame transmission monitorage */
	MSB_START_FRAME = 0,
	LSB_START_FRAME,
	DATA0,
	DATA1,		
	DATA2,
	DATA3,
	DATA4,
	DATA5,
	DATA6,
	DATA7,
	DATA8,
	DATA9,
	DATA10,
	DATA11,
	DATA12,
	DATA13,
	DATA14,
	DATA15,
	DATA16,
	DATA17,
	DATA18,
	DATA19,
	DATA20,
	DATA21,
	DATA22,
	DATA23,
	DATA24,
	DATA25,
	DATA26,
	DATA27,
	DATA28,
	DATA29,
	DATA30,
	DATA31,
	DATA32,
	DATA33,
	DATA34,
	DATA35,
	DATA36,
	DATA37,
	DATA38,
	DATA39,
	DATA40,
	DATA41,
	DATA42,
	DATA43,
	DATA44,
	DATA45,
	DATA46,
	DATA47,
	DATA48,
	DATA49,
	CRC,
	END_FRAME,
	EndOfTableTx

}e_data_monit;

typedef enum
{

	/*%C enum state transmission recive */
	RX_START_FRAME_MSB = 0, 		
	RX_START_FRAME_LSB =1, 				
	RX_COMMAND =2, 						
	RX_PARAM1 =3,							
	RX_PARAM2 =4,							
	RX_CRC =5, 								
	RX_END_FRAME =6,						
	RX_EndOfFrame =7,					
	RX_BufferSize = 21

}e_data_RX_Remote;

/******************  use for "sampling" *************************************/

typedef enum
{
	/*%C enum type mesure tension */
	Sampling_VACDC = 0,
	Sampling_VDC,
	Sampling_VBAT,
	Sampling_5V, 
	Sampling_3V3,
	Sampling_24V,
	Sampling_VCharge

}e_SAM_Voltage;

typedef enum
{
	/*%C enum type mesure current */
	Sampling_I_Battery = 0

}e_SAM_Current;

typedef enum
{
	/*%C enum type mesure température */
	Sampling_T_Ambiant = 0,
	Sampling_T_Battery

}e_SAM_Temperature;


typedef enum
{
	/*%C enum type mesure PWM Controleur */
	PWM_V_Charge = 0,
	PWM_I_Charge,
	PWM_V_Ventil

}e_SAM_PWM;

typedef enum
{

	/*%C enum frame transmission to cpu board */
	SPI_ST10_MSB_START_FRAME = 0,
	SPI_ST10_LSB_START_FRAME,
	SPI_ST10_MSB_V_BAT_U16,
	SPI_ST10_LSB_V_BAT_U16,		
	SPI_ST10_MSB_TEMP_BAT_S16,
	SPI_ST10_LSB_TEMP_BAT_S16,
	SPI_ST10_MSB_BAT_CYCLES_U16,
	SPI_ST10_LSB_BAT_CYCLES_U16,
	SPI_ST10_LSB_BAT_STATE_U16,
	SPI_ST10_LSB_POWER_TYPE_U16,
	SPI_ST10_MSB_GAUGE_MINUTE_U16,
	SPI_ST10_LSB_GAUGE_MINUTE_U16,
	SPI_ST10_LSB_GAUGE_AVALAIBLE_U16,
	SPI_ST10_LSB_PER_CENT_BAT_U16,
	SPI_ST10_LSB_NO_PRESENCE_BAT_U16,
	SPI_ST10_LSB_BAT_KO_U16,
	SPI_ST10_LSB_CHARGE_KO_U16,
	SPI_ST10_LSB_UNKNOWN_BATTERY_U16,
	SPI_ST10_MSB_AMBIENT_TEMP_S16,
	SPI_ST10_LSB_AMBIENT_TEMP_S16,
	SPI_ST10_LSB_BATTERY_END_U16,
	SPI_ST10_LSB_BATTERY_LOW_U16,
	SPI_ST10_LSB_BAT_FIRST_DATE_DAY_U16,
	SPI_ST10_LSB_BAT_FIRST_DATE_MONTH_U16,
	SPI_ST10_LSB_BAT_FIRST_DATE_YEAR_U16,
	SPI_ST10_LSB_BAT_TEMP_OVERFLOW,
	SPI_ST10_LSB_SUPPLY_MEASURE_FAILURE,
	SPI_ST10_LSB_FAILURE_24V_FLAG,
	SPI_ST10_LSB_AMBIENT_TEMP_OUTOFBOUNDS,
	SPI_ST10_LSB_COOLING_FAN_FAILURE_FLAG,
	SPI_ST10_FIRST_VERSION_IDENTIFIANT,
	SPI_ST10_SECOND_VERSION_IDENTIFIANT,
	SPI_ST10_THIRD_VERSION_IDENTIFIANT,
	SPI_ST10_LSB_BAT_FIRST_DATE_HOUR_U16,
	SPI_ST10_LSB_BAT_FIRST_DATE_MINUTE_U16,
	SPI_ST10_LSB_BAT_FIRST_DATE_SECOND_U16,
	SPI_ST10_LSB_BAT_AGEING_U16,
	SPI_ST10_LSB_BAT_SUPPLIER_U16,
	SPI_ST10_LSB_BAT_TYPICAL_CAPACITY_U16,
	SPI_ST10_CRC,
	SPI_ST10_END_FRAME,
	SPI_ST10_EndOfTableTransmit

}e_data_spi_st10_transmit;


typedef enum
{

	/*%C enum state SPI transmission receive */
	SPI_ST10_RECEIVE_START_FRAME_MSB = 0,
	SPI_ST10_RECEIVE_START_FRAME_LSB =1,
	SPI_ST10_RECEIVE_VENTIL_AUTHORIZATION =2,
	SPI_ST10_RECEIVE_MAINTENANCE_FLAG =3,
	SPI_ST10_RECEIVE_CALIBRATION_FLAG =4,
	SPI_ST10_RECEIVE_CRC =5,
	SPI_ST10_RECEIVE_END_FRAME =6,
	SPI_ST10_RECEIVE_EndOfFrame =7,
	SPI_ST10_RECEIVE_BufferSize = 14

}e_data_spi_st10_receive;

typedef enum
{
	DRV_SPI_ST10_NO_ERROR = 0,
	DRV_SPI_ST10_NO_FRAME,
	DRV_SPI_ST10_BAD_FRAME
}e_DRV_SPI_ST10_ERROR;



#endif

/******************  use for EEPROM battery *************************************/
typedef enum
{
	/*%C enum state of step to read, write and init the scratchpad (EEPROM BAT)	*/
	RESET = 0,
	WAIT_ANSWER_RESET_DS2480B,
	WAIT_INIT_ID_MEMORY_1,
	WAIT_INIT_ID_MEMORY_2,
	WAIT_INIT_ID_MEMORY_3,
	WAIT_INIT_ID_MEMORY_4,
	WAIT_INIT_ID_MEMORY_5,
	WAIT_INIT_ID_MEMORY_6,
	WAIT_ANSWER_RESET,
	DATA_MODE,
	WAIT_ANSWER_SKIP_COMMAND,
	WRITE_ADRESS_LSB,
	WRITE_ADRESS_MSB,
	START_READ_DATA,
	READ_DATA,
	WRITE_BLOCK,
	STEP_END
}e_DRV_EEPROM_BAT_STEP_STATE;
typedef enum
{
	/*%C enum state of step_copy to copy the scratchpad in the EEPROM BAT array	*/
	CHECK_CRC_LSB = 0,
	WAIT_ANSWER_CRC_LSB,
	CHECK_CRC_MSB,
	WAIT_ANSWER_CRC_MSB,
	COMMAND_MODE_COPY,
	RESET_COPY,
	WAIT_ANSWER_RESET_COPY,
	DATA_MODE_COPY,
	WAIT_ANSWER_SKIP_COPY,
	WRITE_ADRESS_LSB_COPY,
	WRITE_ADRESS_MSB_COPY,
	AUTHORISATION_COPY,
	WAIT_WRITE_COPY,
	WAIT_ANSWER_STATUS_COPY
}e_DRV_EEPROM_BAT_STEP_COPY_STATE;

typedef enum
{
	INIT = 0,
	READ,
	WRITE
} e_EEPROM_BAT_STATE;


