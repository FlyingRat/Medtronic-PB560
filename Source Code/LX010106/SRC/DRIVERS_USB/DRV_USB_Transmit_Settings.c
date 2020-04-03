/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_USB_Transmit_Settings.c 												*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                     																		*/
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/



/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/
#ifndef _BORLAND
   #ifndef _TASKING
      #include "LH_ST10F276.h"
      #include <intrins.h>
   #else
      #include "regf276e.h"
   #endif
#endif

#ifdef _BORLAND
   /* Attention, conserver cette inclusion _après_ l'inclucion du io_declare.h
      car redéfinition des valeurs de JUMPER pour chaque produit */
      #include "io_declare.h"
      #include "HMI_Product.hpp"
#else
   #include "io_declare.h"
#endif


#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "DB_RTC.h"
#include "DB_Control.h"
#include "DB_Current.h"
#include "DB_Config.h"
#include "DRV_VarEeprom.h"
#include "DB_IhmAccessParaDataBase.h "
#include "DB_Usb.h"
#include "Driver_USB_Data.h"
#include "DRV_USB_Transmit_Settings.h"
#include "db_event.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_USB_Transmit_Settings(UWORD16 UsbTransferOn)
{

	UWORD16 Compute_CRC = 0 ;
	UWORD16 Compteur = 0 ;
	UWORD16 ComputeValue = 0 ;
	UWORD16 ParamCompatibility = 0 ;
	UWORD16 TMP_LSB = 0 ;									
	UWORD16 TMP_MSB = 0 ;
		
	UWORD16 VentilMode 		= (UBYTE)DB_ControlRead(CURRENT_MODE_U16);
	UWORD16 InspSensNoSelect 	= DB_CurrentRead(INSP_SENS_NO_SELECT_U16) ;
	UWORD16 BackupRNoSelect 	= DB_CurrentRead(BACKUP_R_NO_SELECT_U16) ;

/******************************************************************************/
/*%C Write settings on the key																*/
/******************************************************************************/
 	if (UsbTransferOn == FALSE)
	{

/******************************************************************************/
/*%C Enum parameters */
/******************************************************************************/

		/*%C Extract the ventilator Identifiant to verify compatibility */
		if(	(JUMPER_JP7 == JUMPER_OFF)
			&&	(JUMPER_JP8 == JUMPER_OFF))
		{
			/*%C This is a Legend@ir XL2 */
			ParamCompatibility = XL2_IDENTIFIANT ;
			/*%C Transmit parameters */
			DataSettings[USB_SETTINGS_DATA + SETTINGS_COMPATIBILITY] 
								= (UBYTE)ParamCompatibility ;

		}
		else if	(	(JUMPER_JP7 == JUMPER_ON) 
					&&	(JUMPER_JP8 == JUMPER_OFF))
		{
			/*%C This is a Smart@ir S2 */
			ParamCompatibility = S2_IDENTIFIANT ;
			/*%C Transmit parameters */
			DataSettings[USB_SETTINGS_DATA + SETTINGS_COMPATIBILITY] 
								= (UBYTE)ParamCompatibility ;
		}
		else if	(	(JUMPER_JP7 == JUMPER_OFF) 
					&&	(JUMPER_JP8 == JUMPER_ON))
		{
			/*%C This is a Support@ir M2 */
			ParamCompatibility = M2_IDENTIFIANT ;
			/*%C Transmit parameters */
			DataSettings[USB_SETTINGS_DATA + SETTINGS_COMPATIBILITY] 
								= (UBYTE)ParamCompatibility ;
		}
		else
		{
			/*%C This is a invalid device */
			ParamCompatibility = ERROR_IDENTIFIANT ;
			/*%C Transmit parameters */
			DataSettings[USB_SETTINGS_DATA + SETTINGS_COMPATIBILITY] 
								= (UBYTE)ParamCompatibility ;
		}
      
		DB_ConfigWrite(PARAM_COMPATIBILITY, ParamCompatibility);
		 

		switch (VentilMode)
		{
			case VOL :
			{
				if (InspSensNoSelect == FALSE)
				{
					DataSettings[USB_SETTINGS_DATA + SETTINGS_MODE]
										= COM_VOL_A ;
				}
				else if (InspSensNoSelect == TRUE)
				{
					DataSettings[USB_SETTINGS_DATA + SETTINGS_MODE]
										= COM_VOL_C; 
				}
				else
				{
					/*%C No Function */
				}
				break;
			}
					
			case PRES :
			{
				if (InspSensNoSelect == FALSE)
				{
					DataSettings[USB_SETTINGS_DATA + SETTINGS_MODE]
										= COM_PRES_A;
				}
				else if (InspSensNoSelect == TRUE)
				{
					DataSettings[USB_SETTINGS_DATA + SETTINGS_MODE]
										= COM_PRES_C; 
				}
				else
				{
					/*%C No Function */
				}
				break;
			}
					
			case PSVT :
			{
				if (BackupRNoSelect == FALSE) 
				{
					DataSettings[USB_SETTINGS_DATA + SETTINGS_MODE]
										= COM_PSVT;
				}
				else if(BackupRNoSelect == TRUE) 
				{
					DataSettings[USB_SETTINGS_DATA + SETTINGS_MODE]
										= COM_PSV; 
				}
				else
				{
					/*%C No Function */
				}
				break;
			}
					
			case VSIMV :
			{
					DataSettings[USB_SETTINGS_DATA + SETTINGS_MODE]
										= COM_VSIMV;
				break;
			}

			case PSIMV :
			{
					DataSettings[USB_SETTINGS_DATA + SETTINGS_MODE]
										= COM_PSIMV;
				break;
			}

			case CPAP :
			{
					DataSettings[USB_SETTINGS_DATA + SETTINGS_MODE]
										= COM_CPAP;
				break;
			}
			
			default :
			{
				break;
			}
		} 

		/*%C SETTINGS_CYCLING_MODE */
		DataSettings[USB_SETTINGS_DATA + SETTINGS_CYCLING_MODE_LSB]
				= (UBYTE)DB_ConfigRead(ADJUST_CYCLING_MODE_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_CYCLING_MODE_MSB]
				= (UBYTE)(DB_ConfigRead(ADJUST_CYCLING_MODE_U16)>>8) ;

		/*%C SETTINGS_PRESSURE_UNIT */		
		DataSettings[USB_SETTINGS_DATA + SETTINGS_PRESSURE_UNIT_LSB]
				= (UBYTE)DB_ConfigRead(PRESSURE_UNIT_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_PRESSURE_UNIT_MSB]
				= (UBYTE)(DB_ConfigRead(PRESSURE_UNIT_U16)>>8) ;

/******************************************************************************/
		/*%C SETTINGS_SPO2_MINI */
		/*%C Always at Def Value) */		
		DataSettings[USB_SETTINGS_DATA + SETTINGS_LOW_SPO2_LSB] 
				= (UBYTE) cDB_TEST_CONFIG_DB[ADJUST_LOW_SPO2].defvalue ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_LOW_SPO2_MSB] 
				= (UBYTE) (cDB_TEST_CONFIG_DB[ADJUST_LOW_SPO2].defvalue>>8) ;

		/*%C LOW_SPO2_NO_SELECT_FLAG */
		DataSettings[USB_SETTINGS_DATA + SETTINGS_SPO2_LOW_SELECT_LSB] 
				= (UBYTE)DB_ConfigRead(SPO2_LOW_SELECT) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_SPO2_LOW_SELECT_MSB] 
				= (UBYTE)(DB_ConfigRead(SPO2_LOW_SELECT)>>8) ;

		/*%C SETTINGS_SPO2_MAXI */
		/*%C Always at Def Value) */
		DataSettings[USB_SETTINGS_DATA + SETTINGS_HIGH_SPO2_LSB] 
				= (UBYTE) cDB_TEST_CONFIG_DB[ADJUST_HIGH_SPO2].defvalue ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_HIGH_SPO2_MSB] 
				= (UBYTE) (cDB_TEST_CONFIG_DB[ADJUST_HIGH_SPO2].defvalue>>8) ;

		/*%C HIGH_SPO2_NO_SELECT_FLAG */
		DataSettings[USB_SETTINGS_DATA + SETTINGS_SPO2_HIGH_SELECT_LSB] 
				= (UBYTE)DB_ConfigRead(SPO2_HIGH_SELECT) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_SPO2_HIGH_SELECT_MSB] 
				= (UBYTE)(DB_ConfigRead(SPO2_HIGH_SELECT)>>8) ;

/******************************************************************************/
		
/******************************************************************************/
/*%C Settings parameters */
/******************************************************************************/

		/*%C SETTINGS_VOL_CONTROL */
		DataSettings[USB_SETTINGS_DATA + SETTINGS_VOL_CONTROL_LSB]
				= (UBYTE)DB_CurrentRead(ADJUST_VOL_CONTROL_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_VOL_CONTROL_MSB]
				= (UBYTE)(DB_CurrentRead(ADJUST_VOL_CONTROL_U16) >> 8) ;

		/*%C SETTINGS_P_CONTROL */
		DataSettings[USB_SETTINGS_DATA + SETTINGS_P_CONTROL_LSB]
				= (UBYTE)DB_CurrentRead(ADJUST_P_CONTROL_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_P_CONTROL_MSB]
				= (UBYTE)(DB_CurrentRead(ADJUST_P_CONTROL_U16) >> 8) ;

		/*%C SETTINGS_P_SUPPORT */
		DataSettings[USB_SETTINGS_DATA + SETTINGS_P_SUPPORT_LSB]
				= (UBYTE)DB_CurrentRead(ADJUST_P_SUPPORT_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_P_SUPPORT_MSB]
				= (UBYTE)(DB_CurrentRead(ADJUST_P_SUPPORT_U16) >> 8) ;

		/*%C SETTINGS_PEEP */
	   	DataSettings[USB_SETTINGS_DATA + SETTINGS_PEEP_LSB]
				= (UBYTE)DB_CurrentRead(ADJUST_PEEP_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_PEEP_MSB]
				= (UBYTE)(DB_CurrentRead(ADJUST_PEEP_U16) >> 8) ;

		/*%C PEEP_NO_SELECT_FLAG */
	   	DataSettings[USB_SETTINGS_DATA + SETTINGS_PEEP_NO_SELECT_LSB]
				= (UBYTE)DB_CurrentRead(PEEP_NO_SELECT_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_PEEP_NO_SELECT_MSB]
				= (UBYTE)(DB_CurrentRead(PEEP_NO_SELECT_U16) >> 8) ;

		/*%C SETTINGS_RISE_TIME */
	   	DataSettings[USB_SETTINGS_DATA + SETTINGS_RISE_TIME_LSB]
				= (UBYTE)DB_CurrentRead(ADJUST_RISE_TIME_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_RISE_TIME_MSB]
				= (UBYTE)(DB_CurrentRead(ADJUST_RISE_TIME_U16) >> 8) ;

		/*%C SETTINGS_RAMP */
	   	DataSettings[USB_SETTINGS_DATA + SETTINGS_RAMP_LSB]
				= (UBYTE)DB_CurrentRead(ADJUST_RAMP_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_RAMP_MSB]
				= (UBYTE)(DB_CurrentRead(ADJUST_RAMP_U16) >> 8) ;
					
		/*%C SETTINGS_I_T */				
	   	DataSettings[USB_SETTINGS_DATA + SETTINGS_I_T_LSB]
				= 0xAA;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_I_T_MSB]
				= 0xAA;
		
		/*%C SETTINGS_IE_NUMERATOR */
	   	DataSettings[USB_SETTINGS_DATA + SETTINGS_IE_NUMERATOR_LSB]
				= 0xAA;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_IE_NUMERATOR_MSB]
				= 0xAA;

		/*%C SETTINGS_IE_DENOMINATOR */
	   	DataSettings[USB_SETTINGS_DATA + SETTINGS_IE_DENOMINATOR_LSB]
				= 0xAA;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_IE_DENOMINATOR_MSB]
				= 0xAA;

		/*%C SETTINGS_CONTROL_R */
	  	DataSettings[USB_SETTINGS_DATA + SETTINGS_CONTROL_R_LSB]
				= (UBYTE)DB_CurrentRead(ADJUST_CONTROL_R_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_CONTROL_R_MSB]
				= (UBYTE)(DB_CurrentRead(ADJUST_CONTROL_R_U16) >> 8) ;

		/*%C SETTINGS_BACKUP_R */
	  	DataSettings[USB_SETTINGS_DATA + SETTINGS_BACKUP_R_LSB]
				= (UBYTE)DB_CurrentRead(ADJUST_BACKUP_R_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_BACKUP_R_MSB]
				= (UBYTE)(DB_CurrentRead(ADJUST_BACKUP_R_U16) >> 8) ;

		/*%C BACKUP_R_NO_SELECT_FLAG */
	  	DataSettings[USB_SETTINGS_DATA + SETTINGS_BACKUP_R_NO_SELECT_LSB]
				= (UBYTE)DB_CurrentRead(BACKUP_R_NO_SELECT_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_BACKUP_R_NO_SELECT_MSB]
				= (UBYTE)(DB_CurrentRead(BACKUP_R_NO_SELECT_U16) >> 8) ;

		/*%C SETTINGS_APNEA */
	 	DataSettings[USB_SETTINGS_DATA + SETTINGS_APNEA_LSB]
				= (UBYTE)DB_CurrentRead(ADJUST_APNEA_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_APNEA_MSB]
				= (UBYTE)(DB_CurrentRead(ADJUST_APNEA_U16) >> 8) ;

		/*%C APNEA_AUTO_SELECT_FLAG */
	 	DataSettings[USB_SETTINGS_DATA + SETTINGS_AUTO_APNEA_SELECT_LSB]
				= (UBYTE)DB_CurrentRead(AUTO_APNEA_SELECT_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_AUTO_APNEA_SELECT_MSB]
				= (UBYTE)(DB_CurrentRead(AUTO_APNEA_SELECT_U16) >> 8) ;

		/*%C SETTINGS_INSP_SENS */
	 	DataSettings[USB_SETTINGS_DATA + SETTINGS_INSP_SENS_LSB]
				= (UBYTE)DB_CurrentRead(ADJUST_INSP_SENS_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_INSP_SENS_MSB]
				= (UBYTE)(DB_CurrentRead(ADJUST_INSP_SENS_U16) >> 8) ;
		
		/*%C INSP_SENS_NO_SELECT_FLAG */
		DataSettings[USB_SETTINGS_DATA + SETTINGS_INSP_SENS_NO_SELECT_LSB]
				= (UBYTE)DB_CurrentRead(INSP_SENS_NO_SELECT_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_INSP_SENS_NO_SELECT_MSB]
				= (UBYTE)(DB_CurrentRead(INSP_SENS_NO_SELECT_U16) >> 8) ;

		/*%C SETTINGS_EXH_SENS */
		DataSettings[USB_SETTINGS_DATA + SETTINGS_EXH_SENS_LSB]
				= (UBYTE)DB_CurrentRead(ADJUST_EXH_SENS_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_EXH_SENS_MSB]
				= (UBYTE)(DB_CurrentRead(ADJUST_EXH_SENS_U16) >> 8) ;
						
		/*%C EXH_AUTO_SELECT_FLAG */
		DataSettings[USB_SETTINGS_DATA + SETTINGS_AUTO_EXH_SENS_SELECT_LSB]
				= (UBYTE)DB_CurrentRead(AUTO_EXH_SENS_SELECT_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_AUTO_EXH_SENS_SELECT_MSB]
				= (UBYTE)(DB_CurrentRead(AUTO_EXH_SENS_SELECT_U16) >> 8) ;

		/*%C SETTINGS_TARGET_VT */
		DataSettings[USB_SETTINGS_DATA + SETTINGS_TARGET_VT_LSB]
				= (UBYTE)DB_CurrentRead(ADJUST_TARGET_VT_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_TARGET_VT_MSB]
				= (UBYTE)(DB_CurrentRead(ADJUST_TARGET_VT_U16) >> 8) ;
		
		/*%C TARGET_VT_SELECT_FLAG */
		DataSettings[USB_SETTINGS_DATA + SETTINGS_TARGET_VT_SELECT_LSB]
				= (UBYTE)DB_CurrentRead(TARGET_VT_SELECT_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_TARGET_VT_SELECT_MSB]
				= (UBYTE)(DB_CurrentRead(TARGET_VT_SELECT_U16) >> 8) ;

		/*%C SETTINGS_MAX_PRESSURE */
		DataSettings[USB_SETTINGS_DATA + SETTINGS_MAX_PRESSURE_LSB]
				= (UBYTE)DB_CurrentRead(ADJUST_MAX_PRESSURE_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_MAX_PRESSURE_MSB]
				= (UBYTE)(DB_CurrentRead(ADJUST_MAX_PRESSURE_U16) >> 8) ;

		/*%C SETTINGS_LOW_VTI */
		DataSettings[USB_SETTINGS_DATA + SETTINGS_LOW_VTI_LSB]
				= (UBYTE)DB_CurrentRead(ADJUST_LOW_VTI_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_LOW_VTI_MSB]
				= (UBYTE)(DB_CurrentRead(ADJUST_LOW_VTI_U16) >> 8) ;

		/*%C LOW_VTI_NO_SELECT_FLAG */	
		DataSettings[USB_SETTINGS_DATA + SETTINGS_LOW_VTI_NO_SELECT_LSB]
				= (UBYTE)DB_CurrentRead(LOW_VTI_NO_SELECT_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_LOW_VTI_NO_SELECT_MSB]
				= (UBYTE)(DB_CurrentRead(LOW_VTI_NO_SELECT_U16) >> 8) ;
					
		/*%C SETTINGS_HIGH_VTI */
		DataSettings[USB_SETTINGS_DATA + SETTINGS_HIGH_VTI_LSB]
				= (UBYTE)DB_CurrentRead(ADJUST_HIGH_VTI_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_HIGH_VTI_MSB]
				= (UBYTE)(DB_CurrentRead(ADJUST_HIGH_VTI_U16) >> 8) ;

		/*%C HIGH_VTI_NO_SELECT_FLAG */	
		DataSettings[USB_SETTINGS_DATA + SETTINGS_HIGH_VTI_NO_SELECT_LSB]
				= (UBYTE)DB_CurrentRead(HIGH_VTI_NO_SELECT_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_HIGH_VTI_NO_SELECT_MSB]
				= (UBYTE)(DB_CurrentRead(HIGH_VTI_NO_SELECT_U16) >> 8) ;
					
		 /*%C SETTINGS_LOW_VTE */
		DataSettings[USB_SETTINGS_DATA + SETTINGS_LOW_VTE_LSB]
				= (UBYTE)DB_CurrentRead(ADJUST_LOW_VTE_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_LOW_VTE_MSB]
				= (UBYTE)(DB_CurrentRead(ADJUST_LOW_VTE_U16) >> 8) ;

		/*%C LOW_VTE_NO_SELECT_FLAG */	
		DataSettings[USB_SETTINGS_DATA + SETTINGS_LOW_VTE_NO_SELECT_LSB]
				= (UBYTE)DB_CurrentRead(LOW_VTE_NO_SELECT_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_LOW_VTE_NO_SELECT_MSB]
				= (UBYTE)(DB_CurrentRead(LOW_VTE_NO_SELECT_U16) >> 8) ;
							
		/*%C SETTINGS_HIGH_VTE */
		DataSettings[USB_SETTINGS_DATA + SETTINGS_HIGH_VTE_LSB]
				= (UBYTE)DB_CurrentRead(ADJUST_HIGH_VTE_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_HIGH_VTE_MSB]
				= (UBYTE)(DB_CurrentRead(ADJUST_HIGH_VTE_U16) >> 8) ;

		/*%C HIGH_VTE_NO_SELECT_FLAG */	
		DataSettings[USB_SETTINGS_DATA + SETTINGS_HIGH_VTE_NO_SELECT_LSB]
				= (UBYTE)DB_CurrentRead(HIGH_VTE_NO_SELECT_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_HIGH_VTE_NO_SELECT_MSB]
				= (UBYTE)(DB_CurrentRead(HIGH_VTE_NO_SELECT_U16) >> 8) ;
			
		/*%C SETTINGS_HIGH_PIP */
		DataSettings[USB_SETTINGS_DATA + SETTINGS_HIGH_PIP_LSB]
				= (UBYTE)DB_CurrentRead(ADJUST_HIGH_PIP_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_HIGH_PIP_MSB]
				= (UBYTE)(DB_CurrentRead(ADJUST_HIGH_PIP_U16) >> 8) ;
	
		/*%C SETTINGS_LOW_PIP */		
		DataSettings[USB_SETTINGS_DATA + SETTINGS_LOW_PIP_LSB]
				= (UBYTE)DB_CurrentRead(ADJUST_LOW_PIP_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_LOW_PIP_MSB]
				= (UBYTE)(DB_CurrentRead(ADJUST_LOW_PIP_U16) >> 8) ;

		/*%C SETTINGS_HIGH_R */
		DataSettings[USB_SETTINGS_DATA + SETTINGS_HIGH_R_LSB]
				= (UBYTE)DB_CurrentRead(ADJUST_HIGH_R_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_HIGH_R_MSB]
				= (UBYTE)(DB_CurrentRead(ADJUST_HIGH_R_U16) >> 8) ;

		/*%C HIGH_R_NO_SELECT_FLAG */
		DataSettings[USB_SETTINGS_DATA + SETTINGS_HIGH_R_NO_SELECT_LSB]
				= (UBYTE)DB_CurrentRead(HIGH_R_NO_SELECT_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_HIGH_R_NO_SELECT_MSB]
				= (UBYTE)(DB_CurrentRead(HIGH_R_NO_SELECT_U16) >> 8) ;

		/*%C SETTINGS_HIGH_LEAK */
		DataSettings[USB_SETTINGS_DATA + SETTINGS_HIGH_LEAK_LSB]
				= (UBYTE)DB_CurrentRead(ADJUST_HIGH_LEAK_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_HIGH_LEAK_MSB]
				= (UBYTE)(DB_CurrentRead(ADJUST_HIGH_LEAK_U16) >> 8) ;
	
		/*%C HIGH_LEAK_NO_SELECT_FLAG */
		DataSettings[USB_SETTINGS_DATA + SETTINGS_HIGH_LEAK_SELECT_LSB]
				= (UBYTE)DB_CurrentRead(HIGH_LEAK_SELECT_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_HIGH_LEAK_SELECT_MSB]
				= (UBYTE)(DB_CurrentRead(HIGH_LEAK_SELECT_U16) >> 8) ;

		/*%C SETTINGS_TI_MIN */
		DataSettings[USB_SETTINGS_DATA + SETTINGS_TI_MIN_LSB]
				= (UBYTE)DB_CurrentRead(ADJUST_TI_MIN_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_TI_MIN_MSB]
				= (UBYTE)(DB_CurrentRead(ADJUST_TI_MIN_U16) >> 8) ;

		/*%C TI_MIN_AUTO_SELECT_FLAG */
   		DataSettings[USB_SETTINGS_DATA + SETTINGS_TI_MIN_AUTO_SELECT_LSB]
				= (UBYTE)DB_CurrentRead(TI_MIN_AUTO_SELECT_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_TI_MIN_AUTO_SELECT_MSB]
				= (UBYTE)(DB_CurrentRead(TI_MIN_AUTO_SELECT_U16) >> 8) ;

		/*%C SETTINGS_TI_MAX */
   		DataSettings[USB_SETTINGS_DATA + SETTINGS_TI_MAX_LSB]
				= (UBYTE)DB_CurrentRead(ADJUST_TI_MAX_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_TI_MAX_MSB]
				= (UBYTE)(DB_CurrentRead(ADJUST_TI_MAX_U16) >> 8) ;

		/*%C TI_MAX_AUTO_SELECT_FLAG */
		DataSettings[USB_SETTINGS_DATA + SETTINGS_TI_MAX_AUTO_SELECT_LSB]
				= (UBYTE)DB_CurrentRead(TI_MAX_AUTO_SELECT_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_TI_MAX_AUTO_SELECT_MSB]
				= (UBYTE)(DB_CurrentRead(TI_MAX_AUTO_SELECT_U16) >> 8) ;

		/*%C SETTINGS_DISCONNECTION_DELAY */
		DataSettings[USB_SETTINGS_DATA + SETTINGS_DISCONNECTION_DELAY_LSB]
				= (UBYTE)DB_CurrentRead(ADJUST_DISCONNECTION_DELAY_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_DISCONNECTION_DELAY_MSB]
				= (UBYTE)(DB_CurrentRead(ADJUST_DISCONNECTION_DELAY_U16) >> 8) ;
			
		/*%C DICONNECTION_DELAY_AUTO_FLAG */
		DataSettings[USB_SETTINGS_DATA + SETTINGS_DISCONNECTION_DELAY_AUTO_LSB]
				= (UBYTE)DB_CurrentRead(DISCONNECTION_DELAY_AUTO_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_DISCONNECTION_DELAY_AUTO_MSB]
				= (UBYTE)(DB_CurrentRead(DISCONNECTION_DELAY_AUTO_U16) >> 8) ;
						
		/*%C SIGH_SELECT_FLAG */
		DataSettings[USB_SETTINGS_DATA + SETTINGS_SIGH_SELECT_LSB]
				= (UBYTE)DB_CurrentRead(ADJUST_SIGH_SELECT_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_SIGH_SELECT_MSB]
				= (UBYTE)(DB_CurrentRead(ADJUST_SIGH_SELECT_U16) >> 8) ;

		/*%C SIGH_VT_COEF */
		DataSettings[USB_SETTINGS_DATA + SETTINGS_SIGH_VT_COEF_LSB]
				= (UBYTE)DB_CurrentRead(ADJUST_SIGH_VT_COEF_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_SIGH_VT_COEF_MSB]
				= (UBYTE)(DB_CurrentRead(ADJUST_SIGH_VT_COEF_U16) >> 8) ;

		/*%C SIGH_CPT */
		DataSettings[USB_SETTINGS_DATA + SETTINGS_SIGH_CPT_LSB]
				= (UBYTE)DB_CurrentRead(ADJUST_SIGH_CPT_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_SIGH_CPT_MSB]
				= (UBYTE)(DB_CurrentRead(ADJUST_SIGH_CPT_U16) >> 8) ;
	 
		/*%C APNEA_ALARM_ACTIVATION */
		DataSettings[USB_SETTINGS_DATA + SETTINGS_APNEA_ALARM_ACTIVATION_LSB]
				= (UBYTE)DB_ConfigRead(APNEA_ALARM_ACTIVATION) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_APNEA_ALARM_ACTIVATION_MSB]
				= (UBYTE)(DB_ConfigRead(APNEA_ALARM_ACTIVATION) >> 8) ;

 		/*%C ADJUST_PEDIATRIC_CIRCUIT */
		DataSettings[USB_SETTINGS_DATA + SETTINGS_PEDIATRIC_CIRCUIT_LSB]
				= (UBYTE)DB_ConfigRead(ADJUST_PEDIATRIC_CIRCUIT_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_PEDIATRIC_CIRCUIT_MSB]
				= (UBYTE)(DB_ConfigRead(ADJUST_PEDIATRIC_CIRCUIT_U16) >> 8) ;

 		/*%C PRESSURE_SUPPORT_RELATIVE */
		DataSettings[USB_SETTINGS_DATA + SETTINGS_PRESSURE_SUPPORT_RELATIVE_LSB]
				= (UBYTE)DB_ConfigRead(PRESSURE_SUPPORT_RELATIVE_U16) ;
		DataSettings[USB_SETTINGS_DATA + SETTINGS_PRESSURE_SUPPORT_RELATIVE_MSB]
				= (UBYTE)(DB_ConfigRead(PRESSURE_SUPPORT_RELATIVE_U16) >> 8) ;

		/*%C CRC16 Compute */
		UsbComputeCRC =  CRC16_TableCompute
						(
						(UWORD16)SETTINGS_COMPATIBILITY,
						(UWORD16)(USB_SETTINGS_DATA + End_Of_Table_Settings),
						DataSettings, 
						UsbComputeCRC
						);

		/*%C Soustract 1 because Settings_Data */
		DataSettings [End_Of_Table_Settings + USB_SETTINGS_MSB_CRC_FRAME - 1]
				= (UBYTE)(UsbComputeCRC >> 8);
		DataSettings [End_Of_Table_Settings + USB_SETTINGS_LSB_CRC_FRAME - 1]
				= (UBYTE)(UsbComputeCRC & 0x00FF);
	}

/******************************************************************************/
/*%C Read settings on the key	*/
/******************************************************************************/
	else if (UsbTransferOn == TRUE)
	{

		PtrAdresseSettingTable = EEP_DB_Config ;

		/*%C SETTINGS_COMPATIBILITY */
		/*%C Settings compatibility is extract before read the frame */
																							
		/*%C SETTINGS_MODE */
		VentilMode = PEC_Reception[	USB_SETTINGS_DATA 
											+ 	SETTINGS_MODE 
											+	End_of_e_usb_frame_serialNumberAndDate
											+	5];

		switch(VentilMode)
		{
			
			case COM_VOL_A : 
			case COM_VOL_C : 
			{
				VentilMode = VOL ;
				break ;
			}
			
			
			case COM_PRES_A : 
			case COM_PRES_C : 
			{
				VentilMode = PRES ;
				break ;
			}
			
			
			case COM_PSVT : 
			case COM_PSV : 
			{
				VentilMode = PSVT ;
				break ;
			}
			
			
			case COM_VSIMV : 
			{
				VentilMode = VSIMV ;				
				break ;
			}
			case COM_PSIMV : 
			{
				VentilMode = PSIMV ;				
				break ;
			}

			case COM_CPAP : 
			{
				VentilMode = CPAP ;
				break ;
			}
			default :
			{
				VentilMode = 0;	
				break ;
			}
		}

		/*%C Write New Mode in DataBase */
		DB_UsbWrite(USB_NEW_MODE , VentilMode);

		/*%C SETTINGS_CYCLING */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_CYCLING_MODE_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_CYCLING_MODE_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_CYCLING_MODE_U16) , TMP_MSB) ;

		/*%C SETTINGS_P_UNIT_CONV */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_PRESSURE_UNIT_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_PRESSURE_UNIT_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + PRESSURE_UNIT_U16) , TMP_MSB) ;

/******************************************************************************/
		/*%C SETTINGS_LOW_SPO2 */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_LOW_SPO2_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_LOW_SPO2_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_LOW_SPO2) , TMP_MSB) ;

		/*%C SETTINGS_SPO2_LOW_SELECT_FLAG */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_SPO2_LOW_SELECT_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_SPO2_LOW_SELECT_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + SPO2_LOW_SELECT) , TMP_MSB) ;

		/*%C SETTINGS_HIGH_SPO2 */
	   	TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_HIGH_SPO2_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_HIGH_SPO2_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_HIGH_SPO2) , TMP_MSB) ;

		/*%C SETTINGS_SPO2_HIGH_SELECT_FLAG */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_SPO2_HIGH_SELECT_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_SPO2_HIGH_SELECT_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + SPO2_HIGH_SELECT) , TMP_MSB) ;

		/*%C APNEA_ALARM_ACTIVATION */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_APNEA_ALARM_ACTIVATION_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_APNEA_ALARM_ACTIVATION_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + APNEA_ALARM_ACTIVATION) , TMP_MSB) ;

 		/*%C ADJUST_PEDIATRIC_CIRCUIT */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_PEDIATRIC_CIRCUIT_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_PEDIATRIC_CIRCUIT_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_PEDIATRIC_CIRCUIT_U16) , TMP_MSB) ;

 		/*%C PRESSURE_SUPPORT_RELATIVE */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_PRESSURE_SUPPORT_RELATIVE_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_PRESSURE_SUPPORT_RELATIVE_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + PRESSURE_SUPPORT_RELATIVE_U16) , TMP_MSB) ;


/******************************************************************************/

/******************************************************************************/
	
		/*%C SETTINGS_FIO2 */
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_FIO2) , cDB_TEST_CONFIG_DB[ADJUST_FIO2].defvalue) ;

		/*%C SETTINGS_FIO2_SELECT_FLAG */
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_FIO2_SELECT) , cDB_TEST_CONFIG_DB[ADJUST_FIO2_SELECT].defvalue) ;

		/*%C SETTINGS_FIO2_MINI */
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_LOW_FIO2) , cDB_TEST_CONFIG_DB[ADJUST_LOW_FIO2].defvalue) ;

		/*%C SETTINGS_FIO2_LOW_SELECT_FLAG */
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + FIO2_LOW_SELECT) , cDB_TEST_CONFIG_DB[FIO2_LOW_SELECT].defvalue) ;

		/*%C SETTINGS_FIO2_MAXI */
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_HIGH_FIO2) , cDB_TEST_CONFIG_DB[ADJUST_HIGH_FIO2].defvalue) ;

		/*%C SETTINGS_FIO2_HIGH_SELECT_FLAG */
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + FIO2_HIGH_SELECT) , cDB_TEST_CONFIG_DB[FIO2_HIGH_SELECT].defvalue) ;

/******************************************************************************/

/******************************************************************************/
/*%C Test Mode to write in EEP table */
/******************************************************************************/
		switch(VentilMode)
		{
			case VOL :
			{
				PtrAdresseSettingTable = EEP_DB_VOL_Adjust ;
				break ;
			}
			case PRES :
			{
				PtrAdresseSettingTable = EEP_DB_PRES_Adjust ;
				break ;
			}
			case PSVT :
			{
				PtrAdresseSettingTable = EEP_DB_PSV_Adjust ;
				break ;
			}
			case CPAP :
			{
				PtrAdresseSettingTable = EEP_DB_CPAP_Adjust ;
				break ;
			}
			case VSIMV :
			{
				PtrAdresseSettingTable = EEP_DB_VSIMV_Adjust ;
				break ;
			}
			default :
			{
				break ;
			}
		}

/******************************************************************************/
/*%C Settings parameters */
/******************************************************************************/
		  
		/*%C SETTINGS_MSB_VT and SETTINGS_LSB_VT */
	   	TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_VOL_CONTROL_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_VOL_CONTROL_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_VOL_CONTROL_U16) , TMP_MSB) ;

		/*%C SETTINGS_P_CONTROL */
	 	TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_P_CONTROL_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_P_CONTROL_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_P_CONTROL_U16) , TMP_MSB) ;

		/*%C SETTINGS_P_SUPPORT */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_P_SUPPORT_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_P_SUPPORT_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
	
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_P_SUPPORT_U16) , TMP_MSB) ;
		
		/*%C SETTINGS_PEEP */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_PEEP_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_PEEP_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_PEEP_U16) , TMP_MSB) ;

		/*%C SETTINGS_PEEP_NO_SELECT_FLAG */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_PEEP_NO_SELECT_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_PEEP_NO_SELECT_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + PEEP_NO_SELECT_U16) , TMP_MSB) ;

		/*%C SETTINGS_PI_SLOP */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_RISE_TIME_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_RISE_TIME_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_RISE_TIME_U16) , TMP_MSB) ;

		/*%C SETTINGS_RAMP */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_RAMP_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_RAMP_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_RAMP_U16) , TMP_MSB) ;

		/*%C SETTINGS_IT */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_I_T_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_I_T_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		//DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_I_T_U16) , TMP_MSB) ;

		/*%C SETTINGS_IE_NUMERATOR */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_IE_NUMERATOR_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_IE_NUMERATOR_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		//DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_IE_NUMERATOR_U16) , TMP_MSB) ;

		/*%C SETTINGS_IE_DENOMINATOR */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_IE_DENOMINATOR_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_IE_DENOMINATOR_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		//DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_IE_DENOMINATOR_U16) , TMP_MSB) ;

		/*%C SETTINGS_CONTROL_R */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_CONTROL_R_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_CONTROL_R_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_CONTROL_R_U16) , TMP_MSB) ;

		/*%C SETTINGS_BACKUP_R */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_BACKUP_R_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_BACKUP_R_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_BACKUP_R_U16) , TMP_MSB) ;

		/*%C SETTINGS_BACKUP_R_NO_SELECT_FLAG */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_BACKUP_R_NO_SELECT_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_BACKUP_R_NO_SELECT_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + BACKUP_R_NO_SELECT_U16) , TMP_MSB) ;

		/*%C SETTINGS_APNEA */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_APNEA_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_APNEA_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_APNEA_U16) , TMP_MSB) ;

		/*%C SETTINGS_AUTO_APNEA_SELECT_FLAG */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_AUTO_APNEA_SELECT_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_AUTO_APNEA_SELECT_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + AUTO_APNEA_SELECT_U16) , TMP_MSB) ;

		/*%C SETTINGS_I_TRIGGER */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_INSP_SENS_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_INSP_SENS_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_INSP_SENS_U16) , TMP_MSB) ;

		/*%C SETTINGS_INSP_SENS_NO_SELECT_FLAG */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_INSP_SENS_NO_SELECT_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_INSP_SENS_NO_SELECT_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + INSP_SENS_NO_SELECT_U16) , TMP_MSB) ;

		/*%C SETTINGS_E_TRIGGER POSITIVE*/
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_EXH_SENS_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_EXH_SENS_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_EXH_SENS_U16) , TMP_MSB) ;

		/*%C SETTINGS_E_TRIGGER NEGATIVE*/
		if (TMP_MSB != NONE)
		{
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_EXH_SENS_NEGATIVE_U16) , 100 - TMP_MSB) ;
		}
		else
		{
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_EXH_SENS_NEGATIVE_U16) , NONE) ;
		}

		/*%C SETTINGS_AUTO_EXH_SENS_SELECT_FLAG */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_AUTO_EXH_SENS_SELECT_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_AUTO_EXH_SENS_SELECT_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + AUTO_EXH_SENS_SELECT_U16) , TMP_MSB) ;

		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + AUTO_EXH_SENS_NEG_SELECT_U16) , TMP_MSB) ;

		/*%C SETTINGS_VT_TARGET */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_TARGET_VT_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_TARGET_VT_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_TARGET_VT_U16) , TMP_MSB) ;

		/*%C SETTINGS_TARGET_VT_SELECT_FLAG */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_TARGET_VT_SELECT_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_TARGET_VT_SELECT_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + TARGET_VT_SELECT_U16) , TMP_MSB) ;

		/*%C SETTINGS_PI_MAXI */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_MAX_PRESSURE_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_MAX_PRESSURE_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_MAX_PRESSURE_U16) , TMP_MSB) ;

		/*%C SETTINGS_VTI_MINI */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_LOW_VTI_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_LOW_VTI_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_LOW_VTI_U16) , TMP_MSB) ;

		/*%C SETTINGS_LOW_VTI_NO_SELECT_FLAG */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_LOW_VTI_NO_SELECT_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_LOW_VTI_NO_SELECT_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + LOW_VTI_NO_SELECT_U16) , TMP_MSB) ;

		/*%C SETTINGS_VTI_MAXI */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_HIGH_VTI_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_HIGH_VTI_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_HIGH_VTI_U16) , TMP_MSB) ;

		/*%C SETTINGS_HIGH_VTI_NO_SELECT_FLAG */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_HIGH_VTI_NO_SELECT_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_HIGH_VTI_NO_SELECT_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + HIGH_VTI_NO_SELECT_U16) , TMP_MSB) ;

		/*%C SETTINGS_VTE_MINI */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_LOW_VTE_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_LOW_VTE_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_LOW_VTE_U16) , TMP_MSB) ;

		/*%C SETTINGS_LOW_VTE_NO_SELECT_FLAG */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_LOW_VTE_NO_SELECT_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_LOW_VTE_NO_SELECT_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + LOW_VTE_NO_SELECT_U16) , TMP_MSB) ;

		/*%C SETTINGS_VTE_MAXI */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_HIGH_VTE_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_HIGH_VTE_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_HIGH_VTE_U16) , TMP_MSB) ;

		/*%C SETTINGS_HIGH_VTE_NO_SELECT_FLAG */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_HIGH_VTE_NO_SELECT_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_HIGH_VTE_NO_SELECT_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + HIGH_VTE_NO_SELECT_U16) , TMP_MSB) ;

		/*%C SETTINGS_P_HIGH */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_HIGH_PIP_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_HIGH_PIP_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_HIGH_PIP_U16) , TMP_MSB) ;

		/*%C SETTINGS_P_LOW */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_LOW_PIP_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_LOW_PIP_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_LOW_PIP_U16) , TMP_MSB) ;

		/*%C SETTINGS_FR_MAXI */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_HIGH_R_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_HIGH_R_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_HIGH_R_U16) , TMP_MSB) ;

		/*%C SETTINGS_HIGH_R_NO_SELECT_FLAG */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_HIGH_R_NO_SELECT_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_HIGH_R_NO_SELECT_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + HIGH_R_NO_SELECT_U16) , TMP_MSB) ;

		/*%C SETTINGS_LEAK_MAXI */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_HIGH_LEAK_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_HIGH_LEAK_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_HIGH_LEAK_U16) , TMP_MSB) ;

		/*%C SETTINGS_HIGH_LEAK_SELECT_FLAG */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_HIGH_LEAK_SELECT_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_HIGH_LEAK_SELECT_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + HIGH_LEAK_SELECT_U16) , TMP_MSB) ;

		/*%C SETTINGS_TI_MINI */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_TI_MIN_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_TI_MIN_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_TI_MIN_U16) , TMP_MSB) ;

		/*%C SETTINGS_TI_MIN_AUTO_SELECT_FLAG */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_TI_MIN_AUTO_SELECT_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_TI_MIN_AUTO_SELECT_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + TI_MIN_AUTO_SELECT_U16) , TMP_MSB) ;

		/*%C SETTINGS_TI_MAXI */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_TI_MAX_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_TI_MAX_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_TI_MAX_U16) , TMP_MSB) ;

		/*%C SETTINGS_TI_MAX_AUTO_SELECT_FLAG */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_TI_MAX_AUTO_SELECT_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_TI_MAX_AUTO_SELECT_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + TI_MAX_AUTO_SELECT_U16) , TMP_MSB) ;

		/*%C SETTINGS_DEC_TEMPO */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_DISCONNECTION_DELAY_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_DISCONNECTION_DELAY_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_DISCONNECTION_DELAY_U16) , TMP_MSB) ;

		/*%C SETTINGS_DISCONNECTION_DELAY_AUTO_FLAG */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_DISCONNECTION_DELAY_AUTO_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_DISCONNECTION_DELAY_AUTO_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + DISCONNECTION_DELAY_AUTO_U16) , TMP_MSB) ;

		/*%C SETTINGS_SIGH */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_SIGH_SELECT_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_SIGH_SELECT_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_SIGH_SELECT_U16) , TMP_MSB) ;

		/*%C SETTINGS_VT_SIGH */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_SIGH_VT_COEF_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_SIGH_VT_COEF_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_SIGH_VT_COEF_U16) , TMP_MSB) ;

		/*%C SETTINGS_CPT_SIGH */
		TMP_LSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_SIGH_CPT_LSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = (UWORD16)PEC_Reception[USB_SETTINGS_DATA + SETTINGS_SIGH_CPT_MSB + End_of_e_usb_frame_serialNumberAndDate	+ 5];
		TMP_MSB = TMP_MSB * 256 + TMP_LSB ;		
		
		DB_WriteDataInEepAndRam((PtrAdresseSettingTable + ADJUST_SIGH_CPT_U16) , TMP_MSB) ;

		/*%C Write New Mode Detected in DataBase */
		DB_UsbWrite(USB_NEW_MODE_DETECTED , TRUE);

		/*%C Write Event USB settings transfer from key in flash*/
		DB_EventMngt(EVENT_USB_SETTINGS_TRANSFER_FROM_KEY);
	}
	
}