/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_LoadAndCheckEepromIntoRam.c				                  		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function loads and check all     	*/
/*%C        eeprom into ram								                           */
/*                                                            				  		*/
/*%C If a problem occurs in one of the different modes (VOL, PRES, PSV, PSIMV */
/*%C and VSIMV), an error is indicated and the default value is given to the  */
/*%C setting.               								                           */
/*%C The treatment is identical for the config base, if the problem concerns  */
/*%C ADJUST_LANGUAGE, ADJUST_BACKLIGHT or SPEED_COM a flag is set.         */
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter : 			None		        			                  	*/
/*%IO Input/Output Parameter : 	None 	        			                  		*/
/*%O 	Output Parameter : 			None      	                 				  		*/
/******************************************************************************/


/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "structure.h"
#include "DB_Control.h"
#include "DB_Current.h"
#include "DB_Rtc.h"
#include "DB_Config.h"
#include "DB_IhmAccessParaDataBase.h"
#include "DB_LoadAndCheckEepromIntoRam.h"
#include "DRV_VarEeprom.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void DB_LoadAndCheckEepromIntoRam(void)
{

#ifndef _BORLAND

/* Id Declaration  */
	UWORD16 Id=0;

/********************************************************************************/
/* When the pressure support convention is changed (Absolut or relative), */
/* the pressure support/control has to be changed .*/

	EEP_FIFO_PushOneData(&EEP_DB_Config[PRESSURE_SUPPORT_CHANGED_U16],
	   						   READ_EEP);
	
	
	if(EEP_DB_Config[PRESSURE_SUPPORT_CHANGED_U16] == TRUE)
	{
	    EEP_FIFO_PushOneData(&EEP_DB_Config[PRESSURE_SUPPORT_RELATIVE_U16],
	   						   READ_EEP);

		EEP_FIFO_PushOneData(&EEP_DB_PRES_Adjust[ADJUST_P_CONTROL_U16],
		                     READ_EEP);
		EEP_FIFO_PushOneData(&EEP_DB_PRES_Adjust[ADJUST_MAX_PRESSURE_U16],
		                     READ_EEP);
		EEP_FIFO_PushOneData(&EEP_DB_PRES_Adjust[ADJUST_PEEP_U16],
		                     READ_EEP);

		EEP_FIFO_PushOneData(&EEP_DB_PSV_Adjust[ADJUST_P_SUPPORT_U16],
		                     READ_EEP);
		EEP_FIFO_PushOneData(&EEP_DB_PSV_Adjust[ADJUST_MAX_PRESSURE_U16],
		                     READ_EEP);
		EEP_FIFO_PushOneData(&EEP_DB_PSV_Adjust[ADJUST_PEEP_U16],
		                     READ_EEP);

		EEP_FIFO_PushOneData(&EEP_DB_VSIMV_Adjust[ADJUST_P_SUPPORT_U16],
		                     READ_EEP);
		EEP_FIFO_PushOneData(&EEP_DB_VSIMV_Adjust[ADJUST_PEEP_U16],
		                     READ_EEP);

 		EEP_FIFO_PushOneData(&EEP_DB_PSIMV_Adjust[ADJUST_P_CONTROL_U16],
		                     READ_EEP);
		EEP_FIFO_PushOneData(&EEP_DB_PSIMV_Adjust[ADJUST_P_SUPPORT_U16],
		                     READ_EEP);
		EEP_FIFO_PushOneData(&EEP_DB_PSIMV_Adjust[ADJUST_PEEP_U16],
		                     READ_EEP);

		if(EEP_DB_Config[PRESSURE_SUPPORT_RELATIVE_U16]== FALSE)
		{
			DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[ADJUST_P_CONTROL_U16]
									,EEP_DB_PRES_Adjust[ADJUST_P_CONTROL_U16]
										 + EEP_DB_PRES_Adjust[ADJUST_PEEP_U16]);

			DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[ADJUST_MAX_PRESSURE_U16]
									,EEP_DB_PRES_Adjust[ADJUST_MAX_PRESSURE_U16]
										 + EEP_DB_PRES_Adjust[ADJUST_PEEP_U16]);
										 
										 		  
			DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[ADJUST_P_SUPPORT_U16]
									,EEP_DB_PSV_Adjust[ADJUST_P_SUPPORT_U16]
										 + EEP_DB_PSV_Adjust[ADJUST_PEEP_U16]);

			DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[ADJUST_MAX_PRESSURE_U16]
									,EEP_DB_PSV_Adjust[ADJUST_MAX_PRESSURE_U16]
										 + EEP_DB_PSV_Adjust[ADJUST_PEEP_U16]);

			DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[ADJUST_P_SUPPORT_U16]
									,EEP_DB_VSIMV_Adjust[ADJUST_P_SUPPORT_U16]
										 + EEP_DB_VSIMV_Adjust[ADJUST_PEEP_U16]);

			DB_WriteDataInEepAndRam(&EEP_DB_PSIMV_Adjust[ADJUST_P_CONTROL_U16]
									,EEP_DB_PSIMV_Adjust[ADJUST_P_CONTROL_U16]
										 + EEP_DB_PSIMV_Adjust[ADJUST_PEEP_U16]);

			DB_WriteDataInEepAndRam(&EEP_DB_PSIMV_Adjust[ADJUST_P_SUPPORT_U16]
									,EEP_DB_PSIMV_Adjust[ADJUST_P_SUPPORT_U16]
										 + EEP_DB_PSIMV_Adjust[ADJUST_PEEP_U16]);
		}
		else
		{
			
			DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[ADJUST_P_CONTROL_U16]
									,EEP_DB_PRES_Adjust[ADJUST_P_CONTROL_U16]
										 - EEP_DB_PRES_Adjust[ADJUST_PEEP_U16]);

			DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[ADJUST_MAX_PRESSURE_U16]
									,EEP_DB_PRES_Adjust[ADJUST_MAX_PRESSURE_U16]
										 - EEP_DB_PRES_Adjust[ADJUST_PEEP_U16]);

			DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[ADJUST_P_SUPPORT_U16]
									,EEP_DB_PSV_Adjust[ADJUST_P_SUPPORT_U16]
										 - EEP_DB_PSV_Adjust[ADJUST_PEEP_U16]);

			DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[ADJUST_MAX_PRESSURE_U16]
									,EEP_DB_PSV_Adjust[ADJUST_MAX_PRESSURE_U16]
										 - EEP_DB_PSV_Adjust[ADJUST_PEEP_U16]);
										 
			DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[ADJUST_P_SUPPORT_U16]
									,EEP_DB_VSIMV_Adjust[ADJUST_P_SUPPORT_U16]
										 - EEP_DB_VSIMV_Adjust[ADJUST_PEEP_U16]);

			DB_WriteDataInEepAndRam(&EEP_DB_PSIMV_Adjust[ADJUST_P_CONTROL_U16]
									,EEP_DB_PSIMV_Adjust[ADJUST_P_CONTROL_U16]
										 - EEP_DB_PSIMV_Adjust[ADJUST_PEEP_U16]);

			DB_WriteDataInEepAndRam(&EEP_DB_PSIMV_Adjust[ADJUST_P_SUPPORT_U16]
									,EEP_DB_PSIMV_Adjust[ADJUST_P_SUPPORT_U16]
										 - EEP_DB_PSIMV_Adjust[ADJUST_PEEP_U16]);
		}
		DB_WriteDataInEepAndRam(&EEP_DB_Config[PRESSURE_SUPPORT_CHANGED_U16]
								,FALSE);
	 }


/********************************************************************************/
/*%C Read and check EEP Integrity in Adjust base                              */
	for (Id=0;Id<end_of_adjust_table;Id++)
	{
/*%C Read and check EEP Integrity in VOL base                                 */
      EEP_FIFO_PushOneData(&EEP_DB_VOL_Adjust[Id],
		                     READ_EEP);
																			
/*%C  if the value is in range, result is false                               */
		if ( (EEP_DB_VOL_Adjust[Id] >= cDB_VOL_TEST_ADJUST_DB[Id].mini)
		  && (EEP_DB_VOL_Adjust[Id] <= cDB_VOL_TEST_ADJUST_DB[Id].maxi) )
		{
			DB_EepVolAdjustDbError[Id]= FALSE;
		}
/*%C  else, if the value is out of range, result is true                      */
		else
		{
			DB_EepVolAdjustDbError[Id]= TRUE;
/*%C  	The bad parameter flag is set to true    		                        */
			BadParameter = TRUE;

/*%C  	Default value is written 				    		                        */
			DB_WriteDataInEepAndRam(&EEP_DB_VOL_Adjust[Id],
			                        cDB_VOL_TEST_ADJUST_DB[Id].defvalue);

		}

/*%C Read and check EEP Integrity in PSV base                                 */
		EEP_FIFO_PushOneData(&EEP_DB_PSV_Adjust[Id],
		                     READ_EEP);

/*%C  if the value is in range, result is false                               */
		if ( (EEP_DB_PSV_Adjust[Id] >= cDB_PSV_TEST_ADJUST_DB[Id].mini)
		  && (EEP_DB_PSV_Adjust[Id] <= cDB_PSV_TEST_ADJUST_DB[Id].maxi) )
		{
			DB_EepPsvAdjustDbError[Id]= FALSE;
		}
/*%C  else, if the value is out of range, result is true                      */
		else
		{
			DB_EepPsvAdjustDbError[Id]= TRUE;
/*%C  	The bad parameter flag is set to true    		                        */
			BadParameter = TRUE;

/*%C  	Default value is written 				    		                        */
			DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[Id],
			                        cDB_PSV_TEST_ADJUST_DB[Id].defvalue);
		}

/*%C Read and check EEP Integrity in PRES base                                */
		EEP_FIFO_PushOneData(&EEP_DB_PRES_Adjust[Id],
		                     READ_EEP);

/*%C  if the value is in range, result is false                               */
		if ( (EEP_DB_PRES_Adjust[Id] >= cDB_PRES_TEST_ADJUST_DB[Id].mini)
		  && (EEP_DB_PRES_Adjust[Id] <= cDB_PRES_TEST_ADJUST_DB[Id].maxi) )
		{
			DB_EepPresAdjustDbError[Id]= FALSE;
		}
/*%C  else, if the value is out of range, result is true                      */
		else
		{
			DB_EepPresAdjustDbError[Id]= TRUE;
/*%C  	The bad parameter flag is set to true    		                        */
			BadParameter = TRUE;

/*%C  	Default value is written 				    		                        */
			DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[Id],
			                        cDB_PRES_TEST_ADJUST_DB[Id].defvalue);
		}
		
/*%C Read and check EEP Integrity in VSIMV base                               */
		EEP_FIFO_PushOneData(&EEP_DB_VSIMV_Adjust[Id],
		                     READ_EEP);

/*%C  if the value is in range, result is false                               */
		if ( (EEP_DB_VSIMV_Adjust[Id] >= cDB_VSIMV_TEST_ADJUST_DB[Id].mini)
		  && (EEP_DB_VSIMV_Adjust[Id] <= cDB_VSIMV_TEST_ADJUST_DB[Id].maxi) )
		{
			DB_EepVsimvAdjustDbError[Id]= FALSE;
		}
/*%C  else, if the value is out of range, result is true                      */
		else
		{
			DB_EepVsimvAdjustDbError[Id]= TRUE;
/*%C  	The bad parameter flag is set to true    		                        */
			BadParameter = TRUE;

/*%C  	Default value is written 				    		                        */
			DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[Id],
			                        cDB_VSIMV_TEST_ADJUST_DB[Id].defvalue);	 
		}

/*%C Read and check EEP Integrity in PSIMV base                               */
		EEP_FIFO_PushOneData(&EEP_DB_PSIMV_Adjust[Id],
		                     READ_EEP);

/*%C  if the value is in range, result is false                               */
		if ( (EEP_DB_PSIMV_Adjust[Id] >= cDB_PSIMV_TEST_ADJUST_DB[Id].mini)
		  && (EEP_DB_PSIMV_Adjust[Id] <= cDB_PSIMV_TEST_ADJUST_DB[Id].maxi) )
		{
			DB_EepPsimvAdjustDbError[Id]= FALSE;
		}
/*%C  else, if the value is out of range, result is true                      */
		else
		{
			DB_EepPsimvAdjustDbError[Id]= TRUE;
/*%C  	The bad parameter flag is set to true    		                        */
			BadParameter = TRUE;

/*%C  	Default value is written 				    		                        */
			DB_WriteDataInEepAndRam(&EEP_DB_PSIMV_Adjust[Id],
			                        cDB_PSIMV_TEST_ADJUST_DB[Id].defvalue);
		}

/*%C Read and check EEP Integrity in CPAP base                               */
		EEP_FIFO_PushOneData(&EEP_DB_CPAP_Adjust[Id],
		                     READ_EEP);

/*%C  if the value is in range, result is false                               */
		if ( (EEP_DB_CPAP_Adjust[Id] >= cDB_CPAP_TEST_ADJUST_DB[Id].mini)
		  && (EEP_DB_CPAP_Adjust[Id] <= cDB_CPAP_TEST_ADJUST_DB[Id].maxi) )
		{
			DB_EepCpapAdjustDbError[Id]= FALSE;
		}
/*%C  else, if the value is out of range, result is true                      */
		else
		{
			DB_EepCpapAdjustDbError[Id]= TRUE;
/*%C  	The bad parameter flag is set to true    		                        */
			BadParameter = TRUE;
/*%C  	Default value is written 				    		                        */
			DB_WriteDataInEepAndRam(&EEP_DB_CPAP_Adjust[Id],
			                        cDB_CPAP_TEST_ADJUST_DB[Id].defvalue);
		}

   }

/*%C Read and check EEP Integrity in Config base                              */
	for (Id=0;Id<end_of_db_config_table;Id++)
	{
	   EEP_FIFO_PushOneData(&EEP_DB_Config[Id],
	   						   READ_EEP);
/*%C  if adjust mode is a possible value, the result is false                 */
  	   if ( (Id == ADJUST_MODE_U16) 
  	     && ( (EEP_DB_Config[Id] >= cDB_TEST_CONFIG_DB[Id].mini)
  	       && (EEP_DB_Config[Id] <= cMODE_HIGH_LIMIT_VALUE) ) )
		{
			DB_EepConfigDbError[Id]= FALSE;
		}
/*%C  else, if the values are in range, the result is false                   */
		else if ( (EEP_DB_Config[Id] >= cDB_TEST_CONFIG_DB[Id].mini)
		       && (EEP_DB_Config[Id] <= cDB_TEST_CONFIG_DB[Id].maxi) )
		{
			DB_EepConfigDbError[Id]= FALSE;
			/*%C Load the last value saved to the current value*/ 
 		    if (Id == PREVIOUS_SOUND_LEVEL_SELECT_U16) 
 		    {  
 				EEP_DB_Config[SOUND_LEVEL_SELECT_U16] = EEP_DB_Config[Id]; 
			} 
		}
		else
		{
/*%C  	an error is detected, the result is true, the default value is 		*/
/*%C		written															                  */
			DB_EepConfigDbError[Id]= TRUE;
			DB_WriteDataInEepAndRam(&EEP_DB_Config[Id],
			                        cDB_TEST_CONFIG_DB[Id].defvalue);
/*%C  	if loss of langage, stand by or transmission speed                   */
/*%C  	loose parameter indication                                           */
			if ( (Id == ADJUST_LANGUAGE_U16)
			  || (Id == ADJUST_MODE_U16)
			  || (Id == ADJUST_BRIGHTNESS_U16)
			  || (Id == ADJUST_BACKLIGHT_U16)
			  || (Id == SPEED_COM_U16)
			  || (Id == SOUND_LEVEL_SELECT_U16)
			  || (Id == PREVIOUS_SOUND_LEVEL_SELECT_U16)
			  || (Id == ADJUST_CYCLING_MODE_U16)
			  || (Id == ADJUST_KEY_TONE_U16)
			  || (Id == ADJUST_WAVEFORM_DISPLAY_U16)
			  || (Id == ADJUST_BAROMETRIC_CORRECTOR_U16)
			  || (Id == ADJUST_FIO2)
			  || (Id == ADJUST_FIO2_SELECT) 
			  || (Id == ADJUST_LOW_FIO2)
			  || (Id == ADJUST_HIGH_FIO2)
			  || (Id == ADJUST_LOW_SPO2)
			  || (Id == ADJUST_HIGH_SPO2)
			  || (Id == SPO2_LOW_SELECT)
			  || (Id == SPO2_HIGH_SELECT)
			  || (Id == FIO2_LOW_SELECT)
			  || (Id == FIO2_HIGH_SELECT)
			  || (Id == PRESSURE_UNIT_U16)
			  || (Id == SOUND_TYPE_SELECT_U16)
			  || (Id == TRIGG_E_POSITIVE)
			  || (Id == APNEA_ALARM_ACTIVATION) )
			{
				LoosePara = TRUE;
	         BadParameter = FALSE;
 
			}
		}
   }

/*%C Read and check EEP Integrity in Version base (Only Serial Number)                             */
	for (Id=SERIAL_NUMBER_1;Id<end_of_db_version_table;Id++)
	{
	   EEP_FIFO_PushOneData(&EEP_DB_Version_Number[Id],
	   						   READ_EEP);



	}
 
 /*%C Read and check EEP Integrity in Trend base                              */
	for (Id=DB_TREND_VENTIL_HOUR;Id<end_of_db_trend_table;Id++)
	{
	   EEP_FIFO_PushOneData(&EEP_DB_TREND[Id],
	   						   READ_EEP);

/*%C  if the values are in range, the result is false                   */
		if ( (EEP_DB_TREND[Id] >= cDB_TEST_TREND_DB[Id].mini)
		       && (EEP_DB_TREND[Id] <= cDB_TEST_TREND_DB[Id].maxi) )
		{
			DB_EepTrendDbError[Id]= FALSE;
		}
		else
		{
/*%C  	an error is detected, the result is true, the default value is 		*/
/*%C		written															                  */
			DB_EepTrendDbError[Id]= TRUE;
			DB_WriteDataInEepAndRam(&EEP_DB_TREND[Id],
			                        cDB_TEST_TREND_DB[Id].defvalue);
		}
	}

#endif
}
