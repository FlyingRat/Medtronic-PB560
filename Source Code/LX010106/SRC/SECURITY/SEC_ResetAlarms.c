/******************************************************************************/
/*                                                                            */
/* Project N  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_ResetAlarms.c                                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C  This function resets alarms and actualizes the associated               */
/*%C  priority flags                                                          */
/******************************************************************************/
/*%I  Input Parameter :   NONE                                                */
/*%IO Input/Output :      NONE                                                */
/*%O  Output Parameter :  NONE                                                */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "DB_AlarmStatus.h"
#include "DB_Current.h"
#include "DB_Control.h"
#include "Security_Datas.h"
#include "SEC_ResetAlarms.h"
#include "Ventilation_Datas.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void SEC_ResetAlarms(void)
{
#ifndef _BORLAND
UBYTE j = 0;
#endif

/*%C High Pressure alarm reset */
	DB_AlarmStatusWrite(ALARM_CHECK_VALVE_PRESSURE_U16,
	                    ALARM_FALSE);

/*%C High Pressure alarm reset */
	DB_AlarmStatusWrite(ALARM_HIGH_PRESSURE_U16,
	                    ALARM_FALSE);
/*%C High Pressure flag reset */
	DB_ControlWrite(HIGH_PRESSURE_LED_REMINDER_U16,
	                FALSE);

/*%C Disconnection alarm reset */
	DB_AlarmStatusWrite(ALARM_DISCONNECTION_U16,
	                    ALARM_FALSE);

/*%C High Rate alarm reset */
	DB_AlarmStatusWrite(ALARM_HIGH_RATE_U16,
	                    ALARM_FALSE);

/*%C High Vti alarm reset */
	DB_AlarmStatusWrite(ALARM_HIGH_VTI_U16,
	                    ALARM_FALSE);

/*%C Low Vti alarm reset */
	DB_AlarmStatusWrite(ALARM_LOW_VTI_U16,
	                    ALARM_FALSE);

/*%C High Vte alarm reset */
	DB_AlarmStatusWrite(ALARM_HIGH_VTE_U16,
	                    ALARM_FALSE);

/*%C Low Vte alarm reset */
	DB_AlarmStatusWrite(ALARM_LOW_VTE_U16,
	                    ALARM_FALSE);

/*%C Valve alarm reset */
	DB_AlarmStatusWrite(ALARM_VALVE_LEAKAGE_U16,
	                    ALARM_FALSE);

/*%C Apnea alarm reset */
	DB_AlarmStatusWrite(ALARM_APNEA_U16,
	                    ALARM_FALSE);

/*%C Check Pressure alarm reset */
	DB_AlarmStatusWrite(ALARM_CHECK_PRESSURE_U16,
	                    ALARM_FALSE);

/*%C Check valve alarm reset */
	DB_AlarmStatusWrite(ALARM_CHECK_VALVE_U16,
	                    ALARM_FALSE);

/*%C Check volume alarm reset */
	DB_AlarmStatusWrite(ALARM_CHECK_VOLUME_U16,
							  ALARM_FALSE);

/*%C No proximal alarm reset */
	DB_AlarmStatusWrite(ALARM_NO_PROXIMAL_U16,
	                    ALARM_FALSE);

/*%C Check proximal alarm reset */
	DB_AlarmStatusWrite(ALARM_CHECK_PROXIMAL_U16,
	                    ALARM_FALSE);

/*%C Proximal disconnection alarm reset */
	DB_AlarmStatusWrite(ALARM_PROXI_DISCONNECTION_U16,
	                    ALARM_FALSE);

/*%C Occlusion alarm reset */
	DB_AlarmStatusWrite(ALARM_OCCLUSION_U16,
	                    ALARM_FALSE);

/*%C Turbine overheat alarm reset */
/*	DB_AlarmStatusWrite(ALARM_TURBINE_OVERHEAT_U16,
	                    ALARM_FALSE); */

/*%C Clock alarm reset at each ventilation start or mode change */
   DB_AlarmStatusWrite(TECH_ALARM_CLOCK_DEFAULT_U16,
                       ALARM_FALSE);

/*%C Breath time cycled reset */
   DB_AlarmStatusWrite(ALARM_BREATH_TIME_CYCLED_U16,
                       ALARM_FALSE);
 
/*%C Insp flow failure reset */
   DB_AlarmStatusWrite(ALARM_INSP_FLOW_FAILURE_U16,
                       ALARM_FALSE);

/*%C Leak Occlusion reset */
   DB_AlarmStatusWrite(ALARM_LEAK_OCCLUSION_U16,
                       ALARM_FALSE);

/*%C Controlled Cycles reset */
   DB_AlarmStatusWrite(ALARM_CONTROLLED_CYCLES_U16,
                       ALARM_FALSE);

/*%C Check Fio2 reset */
	DB_AlarmStatusWrite(ALARM_CHECK_FIO2_U16,
	                    ALARM_FALSE);

/*%C No Fio2 sensor reset */
	DB_AlarmStatusWrite(ALARM_NO_FIO2_SENSOR_U16,
	                    ALARM_FALSE);
/*%C Low Fio2 reset */
	DB_AlarmStatusWrite(ALARM_LOW_FIO2_U16,
	                    ALARM_FALSE);

/*%C High Fio2 reset */
	DB_AlarmStatusWrite(ALARM_HIGH_FIO2_U16,
	                    ALARM_FALSE);

/*%C Leakage reset */
	DB_AlarmStatusWrite(ALARM_LEAKAGE_U16,
						ALARM_FALSE);

/*%C No fio2 sensor reset             */
	DB_AlarmStatusWrite(ALARM_NO_FIO2_SENSOR_U16, 
						ALARM_FALSE);

/*%C FIO2 calibration needed */
	DB_AlarmStatusWrite(ALARM_NEEDED_FIO2_CALIB_U16,
					  ALARM_FALSE);

/*%C  Apnea flag for SIMV contolled cycles */
	DB_AlarmStatusWrite(ALARM_APNEA_FLAG_U16,
					  ALARM_FALSE);


/*%C Priority flags update */
   SEC_High_Priority_1   &=  0x2E18;
   SEC_High_Priority_2   &=  0xE0E3;
   SEC_High_Priority_3   &=  0x0000;
   SEC_Medium_Priority_1 &=  0xFFB8;
   SEC_Medium_Priority_2 &=  0xFF70;
   SEC_Medium_Priority_3 &=  0xF60F;
   
#ifndef _BORLAND 
/*%C Reset of VEN_SIMV_PS_End array	*/
	for (j = 0; j < 6; j++)
	{
		VEN_SIMV_PS_End[j].EndType = PS_FLOW_END;
	}
	j=0;
#endif	
}
