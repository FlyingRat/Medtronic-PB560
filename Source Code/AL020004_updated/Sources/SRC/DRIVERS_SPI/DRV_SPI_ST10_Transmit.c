/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_SPI_ST10_Transmit.c										  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C          Send information to the CPU board by the SPI                    */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              */
/*%O Output Parameter : NONE                                                  */
/*  Temps d'execution < 500uS												  */
/******************************************************************************/


/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/

#include "p18f6622.h"
#include "IO_Declare.h"
#include "typedef.h"
#include "define.h"
#include "DB_PowerSupply.h"
#include "DB_EEPROM_BAT.h"
#include "DRV_SPI_ST10_Transmit.h"
#include "enum.h"
#include "DRV_SPI_ST10_Data.h"



/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void DRV_SPI_ST10_Transmit(void)
{

		UBYTE ComputeCRC;
		UBYTE Idx = 0;
		
		/*%C Data to be sent to the CPU board 									*/
		/*%C V Bat, Temp Bat, bat data, Bat state, Power type, Bat gauge minute */
		/*%C Gauge availlable, Gauge per cent, No bat flag, Bat open flag, 		*/
		/*%C Charge fail flag, Bat unchargeable flag, Charge time too long flag */
		/*%C Abnormal I bat flag, Abnormal I conso flag, End of charge failure  */
		/*%C Volt out of bounds flag, Unknown batttery flag, Ambient temperature*/
		/*%C End of battery flag,First date day,First date month,First date Year*/
		/*%C Charge temp fail flag, Failure 5 V Flag, Failure 3 V flag, 		*/
		/*%C Failure measure VACDC flag, Failure measure VDC flag,				*/
		/*%C Temperature sensor fail flag, Failure 24V flag,					*/
		/*%C Ambient temp too high, Ambient temp too low,Cooling fan fail flag	*/ 
		
		/*%C CRC Compute														*/
		ComputeCRC = 0;
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_MSB_START_FRAME];
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_LSB_START_FRAME];
		
		/*%C VBat */		
		SpiArrayTransmitData[SPI_ST10_MSB_V_BAT_U16] = (UBYTE)(DB_powerSupply[V_BAT_U16]/256);
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_MSB_V_BAT_U16];
		SpiArrayTransmitData[SPI_ST10_LSB_V_BAT_U16] = (UBYTE)(DB_powerSupply[V_BAT_U16]);
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_LSB_V_BAT_U16];

		/*%C Temp Bat */
		SpiArrayTransmitData[SPI_ST10_MSB_TEMP_BAT_S16] = (UBYTE)(DB_powerSupply[TEMP_BAT_S16]/256);
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_MSB_TEMP_BAT_S16];
		SpiArrayTransmitData[SPI_ST10_LSB_TEMP_BAT_S16] = (UBYTE)(DB_powerSupply[TEMP_BAT_S16]);
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_LSB_TEMP_BAT_S16];

		/*%C Bat Cycles */
		SpiArrayTransmitData[SPI_ST10_MSB_BAT_CYCLES_U16] = (UBYTE)(Ram_Read_Bat[DATA_VARIABLE_NBR_CYCLE_1]);	
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_MSB_BAT_CYCLES_U16];
		SpiArrayTransmitData[SPI_ST10_LSB_BAT_CYCLES_U16] = (UBYTE)(Ram_Read_Bat[DATA_VARIABLE_NBR_CYCLE_2]);
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_LSB_BAT_CYCLES_U16];

		/*%C Bat Ageing */
		SpiArrayTransmitData[SPI_ST10_LSB_BAT_AGEING_U16] = (UBYTE)(Ram_Read_Bat[DATA_VARIABLE_BAT_AGEING_1]);	
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_LSB_BAT_AGEING_U16];

		/*%C Bat State */
		SpiArrayTransmitData[SPI_ST10_LSB_BAT_STATE_U16] = (UBYTE)(DB_powerSupply[BAT_STATE_U16]);	
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_LSB_BAT_STATE_U16];
	
		/*%C Power Type */
		SpiArrayTransmitData[SPI_ST10_LSB_POWER_TYPE_U16] = (UBYTE)(DB_powerSupply[POWER_TYPE_U16]);	
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_LSB_POWER_TYPE_U16];
		
		/*%C Gauge Minute */
		SpiArrayTransmitData[SPI_ST10_MSB_GAUGE_MINUTE_U16] = (UBYTE)(DB_powerSupply[GAUGE_MINUTE_U16]/256);	
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_MSB_GAUGE_MINUTE_U16];
		SpiArrayTransmitData[SPI_ST10_LSB_GAUGE_MINUTE_U16] = (UBYTE)(DB_powerSupply[GAUGE_MINUTE_U16]);
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_LSB_GAUGE_MINUTE_U16];

		/*%C Gauge Avalaible */
		SpiArrayTransmitData[SPI_ST10_LSB_GAUGE_AVALAIBLE_U16] = (UBYTE)(DB_powerSupply[GAUGE_AVALAIBLE_U16]);			
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_LSB_GAUGE_AVALAIBLE_U16];
		
		/*%C Gauge Percent */
		SpiArrayTransmitData[SPI_ST10_LSB_PER_CENT_BAT_U16] = (UBYTE)(DB_powerSupply[PER_CENT_BAT_U16]);			
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_LSB_PER_CENT_BAT_U16];

		/*%C Presence Bat */
		SpiArrayTransmitData[SPI_ST10_LSB_NO_PRESENCE_BAT_U16] = (UBYTE)(DB_powerSupply[NO_BAT_FLAG]);			
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_LSB_NO_PRESENCE_BAT_U16];
			
		/*%C Bat Ok */
		SpiArrayTransmitData[SPI_ST10_LSB_BAT_KO_U16] 
					= (UBYTE)(DB_powerSupply[BAT_OPENED_FLAG]
									| DB_powerSupply[BAT_UNCHARGEABLE_FLAG]
									| DB_powerSupply[CHARGE_TIME_TOO_LONG_FLAG]);			
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_LSB_BAT_KO_U16];
		
		/*%C Charge Ok */
		SpiArrayTransmitData[SPI_ST10_LSB_CHARGE_KO_U16] 
					= (UBYTE)(DB_powerSupply[CHARGE_FAIL_FLAG]
									| DB_powerSupply[VOLT_OUT_OF_BOUNDS_FLAG]
									| DB_powerSupply[ABNORMAL_IBAT_FLAG]
									| DB_powerSupply[INIT_CHARGEUR_FAIL]);
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_LSB_CHARGE_KO_U16];

		/*%C Unknow Battery */
		SpiArrayTransmitData[SPI_ST10_LSB_UNKNOWN_BATTERY_U16] = (UBYTE)(DB_powerSupply[UNKNOWN_BATTERY_FLAG]);			
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_LSB_UNKNOWN_BATTERY_U16];
		
		/*%C Ambient Temp */
		SpiArrayTransmitData[SPI_ST10_MSB_AMBIENT_TEMP_S16] = (UBYTE)(DB_powerSupply[AMBIENT_TEMP_S16]/256);	
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_MSB_AMBIENT_TEMP_S16];
		SpiArrayTransmitData[SPI_ST10_LSB_AMBIENT_TEMP_S16] = (UBYTE)(DB_powerSupply[AMBIENT_TEMP_S16]);
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_LSB_AMBIENT_TEMP_S16];

		/*%C Battery End */
		SpiArrayTransmitData[SPI_ST10_LSB_BATTERY_END_U16] = (UBYTE)(DB_powerSupply[END_OF_BATTERY_FLAG]);			
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_LSB_BATTERY_END_U16];
		
		/*%C Battery Low */
		SpiArrayTransmitData[SPI_ST10_LSB_BATTERY_LOW_U16] = (UBYTE)(DB_powerSupply[LOW_BATTERY_FLAG]);			
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_LSB_BATTERY_LOW_U16];

		/*%C Bat Temp Overflow */
		SpiArrayTransmitData[SPI_ST10_LSB_BAT_TEMP_OVERFLOW] 
					= (UBYTE)(DB_powerSupply[CHARGE_TEMP_FAIL_FLAG]
									| DB_powerSupply[DISCHARGE_TEMP_FAIL_FLAG]);
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_LSB_BAT_TEMP_OVERFLOW];

		/*%C Supply measure */
		SpiArrayTransmitData[SPI_ST10_LSB_SUPPLY_MEASURE_FAILURE] 
					= (UBYTE)(DB_powerSupply[FAILURE_5V_FLAG]
									| DB_powerSupply[FAILURE_3V_FLAG]
									| DB_powerSupply[FAILURE_MES_VDC_FLAG]
									| DB_powerSupply[FAILURE_MES_VACDC_FLAG]
									| DB_powerSupply[TEMP_SENSOR_FAILURE_FLAG]);
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_LSB_SUPPLY_MEASURE_FAILURE];									
									
		/*%C Failure 24V */
		SpiArrayTransmitData[SPI_ST10_LSB_FAILURE_24V_FLAG] = (UBYTE)(DB_powerSupply[FAILURE_24V_FLAG]);			
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_LSB_FAILURE_24V_FLAG];
		
		/*%C Ambiant Temp OutOfBounds */
		SpiArrayTransmitData[SPI_ST10_LSB_AMBIENT_TEMP_OUTOFBOUNDS] = (UBYTE)(DB_powerSupply[AMBIENT_TEMP_TOO_HIGH]);			
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_LSB_AMBIENT_TEMP_OUTOFBOUNDS];

		/*%C Cooling Fan Failure */
		SpiArrayTransmitData[SPI_ST10_LSB_COOLING_FAN_FAILURE_FLAG] = (UBYTE)(DB_powerSupply[COOLING_FAN_FAILURE_FLAG]);			
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_LSB_COOLING_FAN_FAILURE_FLAG];

		/*%C Identifiant version */
		SpiArrayTransmitData[SPI_ST10_FIRST_VERSION_IDENTIFIANT] = FIRST_IDENTIFIANT_VERSION ;
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_FIRST_VERSION_IDENTIFIANT];
		SpiArrayTransmitData[SPI_ST10_SECOND_VERSION_IDENTIFIANT] = SECOND_IDENTIFIANT_VERSION ;
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_SECOND_VERSION_IDENTIFIANT];
		SpiArrayTransmitData[SPI_ST10_THIRD_VERSION_IDENTIFIANT] = THIRD_IDENTIFIANT_VERSION ;
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_THIRD_VERSION_IDENTIFIANT];
		
		/*%C Battery informations	*/
		SpiArrayTransmitData[SPI_ST10_LSB_BAT_SUPPLIER_U16] = (UBYTE)(DB_powerSupply[BAT_SUPPLIER]);			
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_LSB_BAT_SUPPLIER_U16];
		SpiArrayTransmitData[SPI_ST10_LSB_BAT_FIRST_DATE_YEAR_U16] = (UBYTE)(Ram_Read_Bat[DATA_FIXE_DATE_1]);			
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_LSB_BAT_FIRST_DATE_YEAR_U16];
		SpiArrayTransmitData[SPI_ST10_LSB_BAT_FIRST_DATE_MONTH_U16] = (UBYTE)(Ram_Read_Bat[DATA_FIXE_DATE_2]);
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_LSB_BAT_FIRST_DATE_MONTH_U16];
		SpiArrayTransmitData[SPI_ST10_LSB_BAT_FIRST_DATE_DAY_U16] = (UBYTE)(Ram_Read_Bat[DATA_FIXE_DATE_3]);
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_LSB_BAT_FIRST_DATE_DAY_U16];
		SpiArrayTransmitData[SPI_ST10_LSB_BAT_FIRST_DATE_HOUR_U16] = (UBYTE)(Ram_Read_Bat[DATA_FIXE_DATE_4]);		
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_LSB_BAT_FIRST_DATE_HOUR_U16];
		SpiArrayTransmitData[SPI_ST10_LSB_BAT_FIRST_DATE_MINUTE_U16] = (UBYTE)(Ram_Read_Bat[DATA_FIXE_DATE_5]);
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_LSB_BAT_FIRST_DATE_MINUTE_U16];
		SpiArrayTransmitData[SPI_ST10_LSB_BAT_FIRST_DATE_SECOND_U16] = (UBYTE)(Ram_Read_Bat[DATA_FIXE_DATE_6]);
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_LSB_BAT_FIRST_DATE_SECOND_U16];

		SpiArrayTransmitData[SPI_ST10_LSB_BAT_TYPICAL_CAPACITY_U16] = (UBYTE)((Ram_Read_Bat[DATA_FIXE_CAPACITE_1]*256 + Ram_Read_Bat[DATA_FIXE_CAPACITE_2])/100);
		ComputeCRC ^= SpiArrayTransmitData[SPI_ST10_LSB_BAT_TYPICAL_CAPACITY_U16];

		/*%C CRC Update																			*/
		SpiArrayTransmitData[SPI_ST10_CRC] = ComputeCRC;
}
