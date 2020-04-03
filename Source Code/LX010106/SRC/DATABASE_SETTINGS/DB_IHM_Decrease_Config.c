/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_IHM_Decrease_Config.c   		 			                  		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function manages the decrement		*/
/*%C        operation in the config base													*/
/*                                                            				  		*/
/******************************************************************************/
/*%I Input Parameter :				Id                                    		  	*/
/*%IO Input/Output Parameter : 	*Value  	        			                  	*/
/*%O Output Parameter : 			True/False 	                 				  		*/
/******************************************************************************/

			 
/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/

#include "typedef.h"
#include "enum.h"
#include "structure.h"
#include "DB_Config.h"
#include "DB_Current.h"
#include "DB_Control.h"
#include "DB_Rtc.h"
#include "DB_Event.h"
#include "DB_IhmAccessParaDatabase.h"
#include "DRV_VarEeprom.h"
#include "DB_IHM_Decrease_Config.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

UWORD16 DB_IHM_Decrease_Config(UWORD16 *Value,
										 UWORD16 Id)
{
UWORD16 Function_Result = FALSE;

/*%C Rolling menu for communication speed setting                             */
/*%C Possible values: 38400 -> 19200 -> 9600 --> 38400...                     */
	if (Id == SPEED_COM_U16)
	{
		if (DB_EepConfigDbError[Id] == TRUE)
		{
			*Value = cDB_TEST_CONFIG_DB[Id].defvalue;
		}
		else
		{
			if (*Value == cDB_TEST_CONFIG_DB[Id].mini)
			{
				*Value = cDB_TEST_CONFIG_DB[Id].maxi;
			}
			else if (*Value == cDB_TEST_CONFIG_DB[Id].maxi)
			{
				*Value = 19200;
			}
			else
			{
				*Value = cDB_TEST_CONFIG_DB[Id].mini;
			}
		}
		Function_Result = TRUE;
	}

/*%C Curves config: representation						                           */
	else if (Id == CURVE_DRAW_MODE_U16)
	{
		if (DB_EepConfigDbError[Id] == TRUE)
		{
			*Value = cDB_TEST_CONFIG_DB[Id].defvalue;
		}
		else
		{
			if (EEP_DB_Config[CURVE_DISPLAY_TYPE_MODE_U16] == FALSE)
			{
				if (*Value >= (cDB_TEST_CONFIG_DB[Id].mini +
									cDB_TEST_CONFIG_DB[Id].step))
				{
					*Value = *Value - cDB_TEST_CONFIG_DB[Id].step;
				}
				else
				{
					*Value = cDB_TEST_CONFIG_DB[Id].maxi;
				}
			}
		}
		Function_Result = TRUE;
	}

/*%C Mode type test											                           */
	else if (Id == ADJUST_MODE_U16)
	{
		if (DB_EepConfigDbError[Id] == TRUE)
		{
			*Value = cDB_TEST_CONFIG_DB[Id].defvalue;
			Function_Result = TRUE;
		}
		else
		{
			*Value = *Value - 1;
#if defined(LEGENDAIR_S2)
  			Function_Result = DB_IHM_Setting_Config_Adjust_Mode_S2(Value,
																			 FALSE);
#else 
  			Function_Result = DB_IHM_Setting_Config_Adjust_Mode(Value,
																				 FALSE);
#endif
		}
	}

/*%C Adjust Fio2 management								                           */
	else if (Id == ADJUST_FIO2)
	{
		if (DB_EepConfigDbError[Id] == TRUE)
		{
			*Value = cDB_TEST_CONFIG_DB[Id].defvalue;
			Function_Result = TRUE;
		}
		else
		{
			*Value = *Value - cDB_TEST_CONFIG_DB[Id].step;
			Function_Result = DB_IHM_Setting_Config_Adjust_Fio2(Value,
																Id);
			if (Function_Result == TRUE)
			{
				*Value = *Value + cDB_TEST_CONFIG_DB[Id].step;
			}
		}
	}

/*%C Adjust Low Fio2 management 							                           */
	else if (Id == ADJUST_LOW_FIO2)
	{
		if (DB_EepConfigDbError[Id] == TRUE)
		{
			*Value = cDB_TEST_CONFIG_DB[Id].defvalue;
			Function_Result = TRUE;
		}
		else
		{
			*Value = *Value - cDB_TEST_CONFIG_DB[Id].step;
			Function_Result = DB_IHM_Setting_Config_Adjust_Low_Fio2(Value,
																	Id);
			if (Function_Result == TRUE)
			{
				*Value = *Value +	cDB_TEST_CONFIG_DB[Id].step;
			}
		}
	}

/*%C Adjust High Fio2 management							                           */
	else if (Id == ADJUST_HIGH_FIO2)
	{
		if (DB_EepConfigDbError[Id] == TRUE)
		{
			*Value = cDB_TEST_CONFIG_DB[Id].defvalue;
			Function_Result = TRUE;
		}
		else
		{
			*Value = *Value - cDB_TEST_CONFIG_DB[Id].step;
			Function_Result = DB_IHM_Setting_Config_Adjust_High_Fio2(Value,
																	 Id);
			if (Function_Result == TRUE)
			{
				*Value = *Value +	cDB_TEST_CONFIG_DB[Id].step;
			}
		}
	}

/*%C Adjust Low Spo2 management 							                           */
	else if (Id == ADJUST_LOW_SPO2)
	{
		if (DB_EepConfigDbError[Id] == TRUE)
		{
			*Value = cDB_TEST_CONFIG_DB[Id].defvalue;
			Function_Result = TRUE;
		}
		else
		{
			*Value = *Value - cDB_TEST_CONFIG_DB[Id].step;
			Function_Result = DB_IHM_Setting_Config_Adjust_Low_Spo2(Value,
																	Id);
			if (Function_Result == TRUE)
			{
				*Value = *Value +	cDB_TEST_CONFIG_DB[Id].step;
			}
		}
	}

/*%C Adjust High Spo2 management 						                           */
	else if (Id == ADJUST_HIGH_SPO2)
	{
		if (DB_EepConfigDbError[Id] == TRUE)
		{
			*Value = cDB_TEST_CONFIG_DB[Id].defvalue;
			Function_Result = TRUE;
		}
		else
		{
			*Value = *Value - cDB_TEST_CONFIG_DB[Id].step;
			Function_Result = DB_IHM_Setting_Config_Adjust_High_Spo2(Value,
																	 Id);
			if (Function_Result == TRUE)
			{
				*Value = *Value +	cDB_TEST_CONFIG_DB[Id].step;
			}
		}
	}

	else if (*Value >= (cDB_TEST_CONFIG_DB[Id].mini +
							  cDB_TEST_CONFIG_DB[Id].step))
	{
/*%C For all others parameters without dependancies					            */
	  *Value = *Value - cDB_TEST_CONFIG_DB[Id].step;
	  Function_Result = TRUE;
	}
	else
	{
/*%C Rolling menu for language: if language is equal to the first value, the  */
/*%C decrease is made until the last value								            */
		if (Id == ADJUST_LANGUAGE_U16)
		{
			if (DB_EepConfigDbError[Id] == TRUE)
			{
				*Value = cDB_TEST_CONFIG_DB[Id].defvalue;
			}
			else
			{
				*Value = cDB_TEST_CONFIG_DB[Id].maxi;
			}
		  	Function_Result = TRUE;
		}

/*%C  Rolling menu for screen stand by (Min -> Max)									*/
		else if (Id == ADJUST_BACKLIGHT_U16)
		{
			if (DB_EepConfigDbError[Id] == TRUE)
			{
				*Value = cDB_TEST_CONFIG_DB[Id].defvalue;
			}
			else
			{
				*Value = cDB_TEST_CONFIG_DB[Id].maxi;
			}
			Function_Result = TRUE;
		}
/*%C  Rolling menu for Key Tone (Min -> Max)												*/
		else if (Id == ADJUST_KEY_TONE_U16)
		{
			if (DB_EepConfigDbError[Id] == TRUE)
			{
				*Value = cDB_TEST_CONFIG_DB[Id].defvalue;
			}
			else
			{
				*Value = cDB_TEST_CONFIG_DB[Id].maxi;
			}
			Function_Result = TRUE;
		}

/*%C  Rolling menu for cycling mode (Min -> Max)	  									*/
		else if (Id == ADJUST_CYCLING_MODE_U16)
		{
			if (DB_EepConfigDbError[Id] == TRUE)
			{
				*Value = cDB_TEST_CONFIG_DB[Id].defvalue;
			}
			else
			{
				*Value = cDB_TEST_CONFIG_DB[Id].maxi;
			}
			Function_Result = TRUE;
		}

/*%C  Rolling menu for curve configuration (Min -> Max)	  							*/
		else if (Id == CURVE_DISPLAY_TYPE_MODE_U16)
		{
			if (DB_EepConfigDbError[Id] == TRUE)
			{
				*Value = cDB_TEST_CONFIG_DB[Id].defvalue;
			}
			else
			{
				*Value = cDB_TEST_CONFIG_DB[Id].maxi;
			}
			Function_Result = TRUE;
		}

/*%C  Rolling menu for Waveform display (Min -> Max)	  							*/
		else if (Id == ADJUST_WAVEFORM_DISPLAY_U16)
		{
			if (DB_EepConfigDbError[Id] == TRUE)
			{
				*Value = cDB_TEST_CONFIG_DB[Id].defvalue;
			}
			else
			{
				*Value = cDB_TEST_CONFIG_DB[Id].maxi;
			}
			Function_Result = TRUE;
		}

/*%C  Rolling menu for Pediatric circuit (off -> on)	  							*/
		else if (Id == ADJUST_PEDIATRIC_CIRCUIT_U16)
		{
			if (DB_EepConfigDbError[Id] == TRUE)
			{
				*Value = cDB_TEST_CONFIG_DB[Id].defvalue;
			}
			else
			{
				*Value = cDB_TEST_CONFIG_DB[Id].maxi;
			}
			Function_Result = TRUE;
		}

/*%C  Rolling menu for Barometric Corrector (Min -> Max)	  							*/
		else if (Id == ADJUST_BAROMETRIC_CORRECTOR_U16)
		{
			if (DB_EepConfigDbError[Id] == TRUE)
			{
				*Value = cDB_TEST_CONFIG_DB[Id].defvalue;
			}
			else
			{
				*Value = cDB_TEST_CONFIG_DB[Id].maxi;
			}
			Function_Result = TRUE;
		}

/*%C  Rolling menu for APNEA ALARM ACTIVATION				  							*/
		else if (Id == APNEA_ALARM_ACTIVATION)
		{
			if (DB_EepConfigDbError[Id] == TRUE)
			{
				*Value = cDB_TEST_CONFIG_DB[Id].defvalue;
			}
			else
			{
				*Value = cDB_TEST_CONFIG_DB[Id].maxi;
			}
			Function_Result = TRUE;
		}

/*%C Curves config: representation						                           */
		else if (Id == PRESSURE_UNIT_U16)
		{
			if (DB_EepConfigDbError[Id] == TRUE)
			{
				*Value = cDB_TEST_CONFIG_DB[Id].defvalue;
			}
			else
			{
				*Value = cDB_TEST_CONFIG_DB[Id].maxi;
			}
			Function_Result = TRUE;
		}

/*%C  Rolling menu PRESSURE SUPPORT RELATIVE    			   */
		else if (Id == PRESSURE_SUPPORT_RELATIVE_U16)
		{
			if (DB_EepConfigDbError[Id] == TRUE)
			{
				*Value = cDB_TEST_CONFIG_DB[Id].defvalue;
			}
			else
			{
				*Value = cDB_TEST_CONFIG_DB[Id].maxi;
			}
			Function_Result = TRUE;
		}

/*%C  Rolling menu for Barometric Corrector (Min -> Max)	  							*/
		else if (Id == ADJUST_BAROMETRIC_CORRECTOR_U16)
		{
			if (DB_EepConfigDbError[Id] == TRUE)
			{
				*Value = cDB_TEST_CONFIG_DB[Id].defvalue;
			}
			else
			{
				*Value = cDB_TEST_CONFIG_DB[Id].maxi;
			}
			Function_Result = TRUE;
		}

/*%C  Rolling menu for TRIGG E POSITIVE						  							*/
		else if (Id == TRIGG_E_POSITIVE)
		{
			if (DB_EepConfigDbError[Id] == TRUE)
			{
				*Value = cDB_TEST_CONFIG_DB[Id].defvalue;
			}
			else
			{
				*Value = cDB_TEST_CONFIG_DB[Id].maxi;
			}
			Function_Result = TRUE;
		}
/*%C  Rolling menu for VOLUNTARY_STOP_ALARM_ACTIVATION			  							*/
		else if (Id == VOLUNTARY_STOP_ALARM_ACTIVATION)
		{
			if (DB_EepConfigDbError[Id] == TRUE)
			{
				*Value = cDB_TEST_CONFIG_DB[Id].defvalue;
			}
			else
			{
				*Value = cDB_TEST_CONFIG_DB[Id].maxi;
			}
			Function_Result = TRUE;
		}

		else if (Id == SOUND_TYPE_SELECT_U16)
		{
			if (DB_EepConfigDbError[Id] == TRUE)
			{
				*Value = cDB_TEST_CONFIG_DB[Id].defvalue;
			}
			else
			{
				*Value = cDB_TEST_CONFIG_DB[Id].maxi;
			}
			Function_Result = TRUE;
		}
/*%C  For all others parameters, value is fixed to its min							*/
		else
		{
			if (DB_EepConfigDbError[Id] == TRUE)
			{
				*Value = cDB_TEST_CONFIG_DB[Id].defvalue;
			}
			else
			{
				*Value = cDB_TEST_CONFIG_DB[Id].mini;
			}
			Function_Result = TRUE;
		}
	}
	return (Function_Result);
}  



