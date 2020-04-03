/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_COM_Transmit_Monitoring.c                         		  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                     													  */
/*                                                                            */
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

/*		Temps tache : 2.5 ms (templissage + transmission)						*/		
/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/

#ifndef _TASKING
#include "LH_ST10F276.h"
#include <intrins.h>
#else
#include "regf276e.h"
#endif
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "DB_Compute.h"
#include "DB_Control.h"
#include "DB_Current.h"
#include "DB_AlarmStatus.h"
#include "DB_KeyboardEvent.h"
#include "DB_Config.h"
#include "SEC_AlarmIndication.h"
#include "Timer_Data.h"
#include "DRV_COM_Data.h"
#include "DRV_COM_Transmit_Monitoring.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_COM_Transmit_Monitoring(void)
	{
e_DB_ALARMS Alarm = NO_ALARM;
e_DB_ALARMS_STATE ReadAlarm = ALARM_FALSE;
UWORD16 ValveDetected;
UWORD16 TargetVT;
UWORD16 Compute_CRC = 0;
UWORD16 Compute_U16 = 0 ;
UWORD16 Trigger_Insp_Var;
UWORD16 Backup_R_Var;
UWORD16 Mode_Var;

	ValveDetected = DB_ControlRead(VALVE_DETECTED_U16);
	TargetVT = DB_CurrentRead(TARGET_VT_SELECT_U16);
	Mode_Var = (UBYTE)DB_ControlRead(CURRENT_MODE_U16);		
  	
	if((	TIM_ReadDecounterValue(TIM_COM_RECORDING_MONIT) == 0)
  		&& (DRV_COM_End_of_Transmit == TRUE))
		{
		TIM_StartDecounter(TIM_COM_RECORDING_MONIT
									,TIME_RECORDING_MONIT);		  
		
		/* Transmit Frame Header */
		Array_Direct_Monit [COM_TX_START_FRAME_1] 
											= START_FRAME_COM_VALUE_1;
		Array_Direct_Monit [COM_TX_START_FRAME_2] 
											= START_FRAME_COM_VALUE_2;
		Array_Direct_Monit [COM_TX_START_FRAME_3] 
											= START_FRAME_COM_VALUE_3;
		/* ID Type Frame */
		Compute_U16 = DB_ControlRead(VENTIL_STATE_U16);
		Array_Direct_Monit [COM_TX_ID_FRAME] 
											= (UBYTE)Compute_U16;


		/* Patient Pressure : From -200 to 900 (10-1 mbar) */
		Compute_U16 = DB_ComputeRead(MEASURE_PATIENT_PRESSURE_S16);

		Array_Direct_Monit[COM_TX_DATA_FRAME 
							+ MONIT_MSB_PRESSURE] 
													= (UBYTE)(Compute_U16 >> 8);
		Array_Direct_Monit[COM_TX_DATA_FRAME 
							+ MONIT_LSB_PRESSURE] 
													= (UBYTE)Compute_U16;

		if(ValveDetected == TRUE)
		{
			
			/* Inspired flow : from 0 to 2000 (dl/min) */
			Compute_U16 = DB_ComputeRead(MEASURE_QINSP_S16);
			Array_Direct_Monit[COM_TX_DATA_FRAME 
								+ MONIT_MSB_CORRECTED_FLOW_INSP] 
													= (UBYTE)(Compute_U16 >> 8);
			Array_Direct_Monit[COM_TX_DATA_FRAME 
								+ MONIT_LSB_CORRECTED_FLOW_INSP] 
													= (UBYTE)Compute_U16;

			/* Exhaled flow : from 0 to 2000 (dl/min) */
			Compute_U16 = DB_ComputeRead(MEASURE_QEXH_S16);
			Array_Direct_Monit[COM_TX_DATA_FRAME 
								+ MONIT_MSB_CORRECTED_FLOW_EXHAL] 
													= (UBYTE)(Compute_U16 >> 8);
			Array_Direct_Monit[COM_TX_DATA_FRAME 
								+ MONIT_LSB_CORRECTED_FLOW_EXHAL] 
													= (UBYTE)Compute_U16;

			/* Saturation de la mesure fuite pour ne pas l'afficher */
			Array_Direct_Monit[COM_TX_DATA_FRAME 
								+ MONIT_CORRECTED_VT_LEAK] = 0xFF; 
													
	 	}
		else
		{
			/* Inspired flow : from 0 to 2000 (dl/min) */
	  		Compute_U16	= DB_ComputeRead(MEASURE_QINSP_LEAKCORRECTED_S16);
			Array_Direct_Monit[COM_TX_DATA_FRAME 
								+ MONIT_MSB_CORRECTED_FLOW_INSP] 
													= (UBYTE)(Compute_U16 >> 8);
			Array_Direct_Monit[COM_TX_DATA_FRAME 
								+ MONIT_LSB_CORRECTED_FLOW_INSP] 
													= (UBYTE)Compute_U16;

			/* Exhaled flow : from 0 to 2000 (dl/min) */
			Array_Direct_Monit[COM_TX_DATA_FRAME 
								+ MONIT_MSB_CORRECTED_FLOW_EXHAL] = 0xFF; 
													
			Array_Direct_Monit[COM_TX_DATA_FRAME 
								+ MONIT_LSB_CORRECTED_FLOW_EXHAL] = 0xFF; 
													

			/* Leakage Measure : from 0 to 200 (l/min) */
			Compute_U16 = DB_ComputeRead(COMPUTED_LEAK_U16) / 10; 
			Array_Direct_Monit[COM_TX_DATA_FRAME 
								+ MONIT_CORRECTED_VT_LEAK] 
													= (UBYTE)Compute_U16;
		}

		/* SPO2 Measure : from 0 to 100 (%) */
		/* Cardiac Frequency : from 0 to 255 (p/min) */
		/* 0 if error sensor */
		if(DB_ControlRead(ERROR_SPO2_SENSOR_DETECTED) == TRUE)
		{
			Array_Direct_Monit[COM_TX_DATA_FRAME + MONIT_SPO2] = 0;
			Array_Direct_Monit[COM_TX_DATA_FRAME + MONIT_HR] = 0;
		}
		else
		{
			Compute_U16 = DB_ComputeRead(MEASURE_SPO2_U16); 
			Array_Direct_Monit[COM_TX_DATA_FRAME + MONIT_SPO2] 
						= (UBYTE)Compute_U16;
			Compute_U16 = DB_ComputeRead(MEASURE_HR_U16);
			Array_Direct_Monit[COM_TX_DATA_FRAME + MONIT_HR] 
						= (UBYTE)Compute_U16;
		}

		
		/* Activation/Desactivation alarm state */
		Array_Direct_Monit[COM_TX_DATA_FRAME + MONIT_ALARM_1] = 0;
		Array_Direct_Monit[COM_TX_DATA_FRAME + MONIT_ALARM_2] = 0;
		Array_Direct_Monit[COM_TX_DATA_FRAME + MONIT_ALARM_3] = 0;
		Array_Direct_Monit[COM_TX_DATA_FRAME + MONIT_ALARM_4] = 0;
		Array_Direct_Monit[COM_TX_DATA_FRAME + MONIT_ALARM_5] = 0;
		Array_Direct_Monit[COM_TX_DATA_FRAME + MONIT_ALARM_6] = 0;
		Array_Direct_Monit[COM_TX_DATA_FRAME + MONIT_ALARM_7] = 0;
		Array_Direct_Monit[COM_TX_DATA_FRAME + MONIT_ALARM_8] = 0;
		Array_Direct_Monit[COM_TX_DATA_FRAME + MONIT_ALARM_9] = 0;
		for (Alarm = 1;Alarm < Mark_Displayed_Alarm;Alarm++)
		{
			ReadAlarm = DB_AlarmStatusRead(Alarm);
			/* si CANCELED et alarme sans priorité la zone reste à ZERO */			
			if ((ReadAlarm == ALARM_DISPLAYED) && (Alarm_Level != WP))
			{
				Array_Direct_Monit[COM_TX_DATA_FRAME + MONIT_ALARM_1 + (Alarm/8)] 
						|= 1 << (Alarm%8 );
			}
		}
		
		/* Symbol to be displayed : 
			   0 = No Valve / No target Vt
			   1 = Valve / No target Vt	
			   2 = No Valve / Target Vt
			   3 = Valve / Target Vt	*/
		if (  (TargetVT == FALSE)
			|| (Mode_Var == VOL)
			|| (Mode_Var == VSIMV)
			|| (Mode_Var == CPAP))
		{
			if(ValveDetected == FALSE)
			{
				Array_Direct_Monit[COM_TX_DATA_FRAME + MONIT_SYMBOL] = 0x00;
			}
			else
			{
				Array_Direct_Monit[COM_TX_DATA_FRAME + MONIT_SYMBOL] = 0x01;
			}
		}
		else
		{
			if (ValveDetected == FALSE)
			{
				Array_Direct_Monit[COM_TX_DATA_FRAME + MONIT_SYMBOL] = 0x02;
			}
			else
			{
				Array_Direct_Monit[COM_TX_DATA_FRAME + MONIT_SYMBOL] = 0x03;

			}
		}

  	
		/* Ventilation mode */
		Array_Direct_Monit[COM_TX_DATA_FRAME + MONIT_VENTIL_MODE] = 
								(UBYTE)Mode_Var;		
		Trigger_Insp_Var = DB_CurrentRead(INSP_SENS_NO_SELECT_U16);
		Backup_R_Var = DB_CurrentRead(BACKUP_R_NO_SELECT_U16);
		 
		switch (Array_Direct_Monit[COM_TX_DATA_FRAME + MONIT_VENTIL_MODE])
				{
					case VOL :
					{
						if (Trigger_Insp_Var == FALSE)
						{
							Array_Direct_Monit[COM_TX_DATA_FRAME + MONIT_VENTIL_MODE] = COM_VOL_A;
						}
						else if (Trigger_Insp_Var == TRUE)
						{
							Array_Direct_Monit[COM_TX_DATA_FRAME + MONIT_VENTIL_MODE] = COM_VOL_C; 
						}
						break;
					}
					
					case PRES :
					{
						if (Trigger_Insp_Var == FALSE)
						{
							Array_Direct_Monit[COM_TX_DATA_FRAME + MONIT_VENTIL_MODE] = COM_PRES_A;
						}
						else if (Trigger_Insp_Var == TRUE)
						{
							Array_Direct_Monit[COM_TX_DATA_FRAME + MONIT_VENTIL_MODE] = COM_PRES_C; 
						}
						break;
					}
					
					case PSVT :
					{
						if (Backup_R_Var == FALSE) 
						{
							Array_Direct_Monit[COM_TX_DATA_FRAME + MONIT_VENTIL_MODE] = COM_PSVT;
						}
						else if (Backup_R_Var == TRUE)
						{
							Array_Direct_Monit[COM_TX_DATA_FRAME + MONIT_VENTIL_MODE] = COM_PSV; 
						}
						break;
					 					}
					
					case VSIMV :
					{
						Array_Direct_Monit[COM_TX_DATA_FRAME + MONIT_VENTIL_MODE] = COM_VSIMV;
						break;
					}
				
					case PSIMV :
					{
						Array_Direct_Monit[COM_TX_DATA_FRAME + MONIT_VENTIL_MODE] = COM_PSIMV;
						break;
					}
					
					case CPAP :
					{
						Array_Direct_Monit[COM_TX_DATA_FRAME + MONIT_VENTIL_MODE] = COM_CPAP;
						break;
					}
					
					default :
					{
						break;
					}
				} 

	   

		/*%C CRC16 Compute */ 
		Compute_CRC = CRC16_TableCompute((UWORD16)MONIT_MSB_PRESSURE + COM_TX_DATA_FRAME, 
	 												(UWORD16)End_Of_Table_Direct_Monitoring + COM_TX_DATA_FRAME,   
													Array_Direct_Monit ,
													0);
 	
		Array_Direct_Monit [	COM_TX_MSB_CRC_FRAME 
							+ 	End_Of_Table_Direct_Monitoring 
							- 	1] = (UBYTE)(Compute_CRC >> 8); 

		Array_Direct_Monit [	COM_TX_LSB_CRC_FRAME 
							+ 	End_Of_Table_Direct_Monitoring 
							- 	1] = (UBYTE)(Compute_CRC & 0x00FF);		    

		/*%C Stop Frame Header */
		Array_Direct_Monit[		COM_TX_END_FRAME_1 
							+ 	End_Of_Table_Direct_Monitoring 
							- 	1] = END_FRAME_COM_VALUE_1;

		Array_Direct_Monit[COM_TX_END_FRAME_2 
							+ 	End_Of_Table_Direct_Monitoring 
							- 	1] = END_FRAME_COM_VALUE_2;

		Array_Direct_Monit[COM_TX_END_FRAME_3 
							+ 	End_Of_Table_Direct_Monitoring 
							- 	1] = END_FRAME_COM_VALUE_3;

  	  		
		/*%C Autorisation de l'interruption de transmission RS232 					*/
	  	S0TBIR = 0;
		PECC2 = 0x0500; // incrémentation du pointeur source - transfert d'un word
		PECC2 |= End_Of_Table_Com_TX_Remote + End_Of_Table_Direct_Monitoring - 1; // taille du tableau d'évènement à transférer
		SRCP2 = _sof_(&Array_Direct_Monit); 	// adresse du tableau d'évènement 
		// Pointeur destination  pointe sur le registre de transmission RS232
		DSTP2 = (UWORD16) &S0TBUF;
		//autorisation de transmission
		DRV_COM_End_of_Transmit = FALSE;
		S0TBIE = 1;
		S0TBIR = 1;	   
		}	
}
