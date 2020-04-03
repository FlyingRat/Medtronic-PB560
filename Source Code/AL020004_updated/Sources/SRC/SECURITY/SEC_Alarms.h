/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  :SEC_Alarms.h            					              					*/
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


#ifndef SEC_ALARM_H
#define SEC_ALARM_H

/******************************************************************************/
/*		                EXTERNAL FUNCTION DECLARATION 						  			*/
/******************************************************************************/

	extern void TIM_StartDecounter16(e_TIM_TABLE_ID_16,UWORD16);
	extern void TIM_StartDecounter32(e_TIM_TABLE_ID_32 offset_table,UWORD32 value);
	extern void DB_PowerSupply_Write(e_DB_POWERSUPPLY Id, UWORD16 Value);
	extern UWORD16 TIM_ReadValue16(e_TIM_TABLE_ID_16);
	extern UWORD16 DB_PowerSupply_Read(e_DB_POWERSUPPLY Id);

	extern void SEC_End_Of_Battery(void);
	extern void SEC_low_Battery(void);
	extern void SEC_24V_Fail(void);
	extern void SEC_3V_Fail(void);
	extern void SEC_5V_Fail(void);
	extern void SEC_Measure_VACDC_Fail(void);
	extern void SEC_Measure_VDC_Fail(void);
	extern void SEC_Abnormal_IBat(void);
	extern void SEC_Bat_Opened(void);
	extern void SEC_Battery_Unchargeable(void);
	extern void SEC_Charge_Discharge_Fail(void);
	extern void SEC_Charge_Fail(void);
	extern void SEC_Charge_Time_Too_Long(void);
	extern void SEC_CoolingFan_Fail(void);
	extern void SEC_Measures_Out_Of_Bounds(void);
	extern void SEC_No_Battery(void);
	extern void SEC_Temp_Sensor_Failure(void);
	extern void SEC_Ambient_Temp_Too_High(void);
	extern void SEC_UnknownBattery(void);
	extern void SEC_CommFail(void);

#endif
