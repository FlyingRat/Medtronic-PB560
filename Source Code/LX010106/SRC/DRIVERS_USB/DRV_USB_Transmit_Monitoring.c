/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_USB_Transmit_Monitoring.c                         			*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                     																		*/
/*%C																									*/
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/


/******************************************************************************/
/* -	Pression patient : de -200 à + 900  en 10-1 mbar sur deux octets : 		*/
/*		1°octet = pression / 256 et 2° octet = pression %256. Le signal de 		*/
/* 	pression est renvoyé dans un format spécifique 									*/
/*		permettant de simplifier la transmission des valeurs négatives. Un 		*/
/* 	offset de + 600 est proposé par défaut. 											*/
/*		La prise en compte des décimales est nécessaire afin d'éviter une 		*/
/* 	apparence de courbe en " escalier ".												*/

/* -	Débit inspiré : de 0 à 2000 en dl/min sur deux octets :						*/
/* 	1°octet = débit / 256 et 2° octet = débit %256.									*/

/* -	Débit expiré : de 0 à 2000 en dl/min sur deux octets :						*/
/*    1°octet = débit / 256 et 2° octet = débit %256.									*/

/* -	Caractères d'alarme : sur 4 octets utilisables pour transmettre les 		*/
/* 	états  d'activation ou désactivation des alarmes 								*/
/*		(voir § Options de monitorage).														*/

/* -	Caractère de fin de trame : sur un octet. Le caractère de fin de trame	*/
/* 	permet d'identifier les ensembles 													*/
/*		successifs de données renvoyées à chaque interruption. Ce caractère est	*/
/* 	aussi utilisé pour identifier 														*/
/*		des phases du cycle de respiration (inspiration, expiration, veille) :	*/
/*  	voir § Identification de Ti & Te.		
/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/

#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "DB_Compute.h"
#include "DB_Control.h"
#include "DB_Current.h"
#include "DB_RTC.h"
#include "CRC16_Table.h"
#include "DB_AlarmStatus.h"
#include "DB_Config.h"
#include "DB_KeyboardEvent.h"
#include "SEC_AlarmIndication.h"
#include "Driver_USB_Data.h"
#include "DRV_USB_Transmit_Monitoring.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_USB_Transmit_Monitoring(UWORD16 DetailledDataType)
{

  	e_DB_ALARMS Alarm = NO_ALARM;
	e_DB_ALARMS_STATE ReadAlarm = ALARM_FALSE;

	UWORD16 Compute_U16 = 0 ; 

	UWORD16 ValveDetected 
					= DB_ControlRead(VALVE_DETECTED_U16) ;
	UWORD16 ErrorSpo2SensorDectected
					= DB_ControlRead(ERROR_SPO2_SENSOR_DETECTED) ;


/******************************************************************************/
/*Start Monitoring every 40 ms */
/******************************************************************************/

	if(DetailledDataType == DETAILLED_MONITORING_TYPE)
	{

		/*%C ID Type Frame */
		DataMonitoring [USB_ID_FRAME]	
					= USB_MONITORING_IDENTIFIANT ;

		DataMonitoring[USB_DATA + DETAILLED_DATA_TYPE] 
					= DETAILLED_MONITORING_TYPE ;

		Compute_U16 = DB_ControlRead(VENTIL_STATE_U16);
		DataMonitoring[USB_DATA + DETAILLED_VENTIL_STATE] 
					= (UBYTE)Compute_U16;
											
														  
		/*%C Patient Pressure : From -200 to 900 (10-1 mbar) */
		Compute_U16 = DB_ComputeRead(MEASURE_PATIENT_PRESSURE_S16);

		DataMonitoring[USB_DATA + DETAILLED_PATIENT_PRESSURE_MSB]
					= (UBYTE) (Compute_U16 >> 8) ;
	 	DataMonitoring[USB_DATA + DETAILLED_PATIENT_PRESSURE_LSB]
	 				= (UBYTE) Compute_U16 ;

		if(ValveDetected == TRUE)
		{
			/*%C Inspired flow : from 0 to 2000 (dl/min) */
			Compute_U16	= DB_ComputeRead(MEASURE_QINSP_S16);

			DataMonitoring[USB_DATA + DETAILLED_INSP_FLOW_MSB]
					= (UBYTE) (Compute_U16 >> 8) ;
			DataMonitoring[USB_DATA + DETAILLED_INSP_FLOW_LSB]
					= (UBYTE) Compute_U16 ;

			/*%C Exhaled flow : from 0 to 2000 (dl/min) */
			Compute_U16	= DB_ComputeRead(MEASURE_QEXH_S16);

			DataMonitoring[USB_DATA + DETAILLED_EXH_FLOW_MSB]
					= (UBYTE) (Compute_U16 >> 8) ;
			DataMonitoring[USB_DATA + DETAILLED_EXH_FLOW_LSB]
					= (UBYTE) Compute_U16 ;

			/*%C Saturation de la mesure fuite pour ne pas l'afficher */
			DataMonitoring[USB_DATA + DETAILLED_LEAK]
					=  0xFF;
	 	}
		else
		{
			/*%C Inspired flow : from 0 to 2000 (dl/min) */
			Compute_U16	= DB_ComputeRead(MEASURE_QINSP_LEAKCORRECTED_S16);

			DataMonitoring[USB_DATA + DETAILLED_INSP_FLOW_MSB]
					= (UBYTE) (Compute_U16 >> 8) ;
			DataMonitoring[USB_DATA + DETAILLED_INSP_FLOW_LSB]
					= (UBYTE) Compute_U16 ;

			/*%C Exhaled flow : from 0 to 2000 (dl/min) */
			DataMonitoring[USB_DATA + DETAILLED_EXH_FLOW_MSB]
					= 0xFF;
			DataMonitoring[USB_DATA + DETAILLED_EXH_FLOW_LSB]
					 = 0xFF;

			/*%C Leakage Measure : from 0 to 200 (l/min) */
			Compute_U16 = DB_ComputeRead(COMPUTED_LEAK_U16) / 10;
			
			DataMonitoring[USB_DATA + DETAILLED_LEAK]
					= (UBYTE)Compute_U16;
		}
	}

	else if(DetailledDataType == DETAILLED_HORODATAGE_TYPE)
	{

		/*%C ID Type Frame */
		DataMonitoring [USB_ID_FRAME]	
					= USB_MONITORING_IDENTIFIANT ;

		DataMonitoring[USB_DATA + DETAILLED_DATA_TYPE] 
					= DETAILLED_HORODATAGE_TYPE ;

		DataMonitoring[USB_DATA + DETAILLED_DAY]
				= (UBYTE)DB_RTCRead(DB_RTC_DAY_U16) ;

		DataMonitoring[USB_DATA + DETAILLED_MONTH]
				= (UBYTE)DB_RTCRead(DB_RTC_MONTH_U16) ;

		DataMonitoring[USB_DATA + DETAILLED_YEAR]
				= (UBYTE)DB_RTCRead(DB_RTC_YEAR_U16) ;

		DataMonitoring[USB_DATA + DETAILLED_HOUR]
				= (UBYTE)DB_RTCRead(DB_RTC_HOUR_U16) ;

		DataMonitoring[USB_DATA + DETAILLED_MINUTE]
				= (UBYTE)DB_RTCRead(DB_RTC_MINUTE_U16) ;

		DataMonitoring[USB_DATA + DETAILLED_SECOND]
				= (UBYTE)DB_RTCRead(DB_RTC_SECOND_U16) ;

		DataMonitoring[USB_DATA + DETAILLED_RESERVED1] = 0x00 ;
		DataMonitoring[USB_DATA + DETAILLED_RESERVED2] = 0x00 ;

	}
}