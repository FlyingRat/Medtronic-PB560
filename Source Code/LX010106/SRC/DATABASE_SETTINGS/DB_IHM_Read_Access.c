/******************************************************************************/
/*                                                                            */
/* Project Number :  RB0505                                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename	: DB_IHM_Read_Access.c                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C        Functionnal description :  this function manages the read         */
/*%C        operation in the different bases function of DbType parameter     */
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter : 			Id                                    		  	*/
/*%I                    			DbType	                            		  	*/
/*%IO Input/Output Parameter : 	*Value        			                  		*/
/*%O 	Output Parameter : 			True/False 	                 				  		*/
/******************************************************************************/



/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/

#define DECLARATION_REVISION_BASE

#include "typedef.h"
#include "enum.h"
#include "structure.h"
#include "DB_Control.h"
#include "DB_Rtc.h"
#include "DB_Usb.h"
#include "DRV_VarEeprom.h"
#include "DB_IHMAccessParaDatabase.h"
#include "DB_Compute.h"
#include "DB_Revision.h"
#include "DB_AlarmStatus.h"
#include "DB_PowerSupply.h"
#include "DB_IHM_Read_Access.h"
#include "DB_KeyboardEvent.h"
#include "DB_IHM_Read_Access.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

UWORD16 DB_IHM_Read_Access(UWORD16 *Value,
                           UWORD16 Id,
                           e_TYPE_OF_DB_TARGET DbType)
{
/* Function result declaration */
   UWORD16 Function_Result = FALSE;

/* Current mode recovery*/
   e_MODE_TYPES ActualMode = VOL;
   ActualMode = EEP_DB_Config[ADJUST_MODE_U16];

/*%C Base reading choice function of DbType */
	switch (DbType)
	{
/*%C  Parameter reading in the adjust base */
		case ADJUST:
		{					

/*%C 		Parameter reading in the PRES mode */
			if (ActualMode == PRES)
 			{
				*Value = EEP_DB_PRES_Adjust[Id];
				Function_Result = TRUE;
			}
#ifdef CONFIG_VOL_MODE
/*%C 		Parameter reading in the VOL mode */
			else if (ActualMode == VOL)
			{ 
				*Value = EEP_DB_VOL_Adjust[Id];
				Function_Result = TRUE;
			}
#endif
#ifdef CONFIG_SIMV_MODE
/*%C 		Parameter reading in the VSIMV mode */
			else if (ActualMode == VSIMV)
			{ 
				*Value = EEP_DB_VSIMV_Adjust[Id];
				Function_Result = TRUE;
			}
/*%C 		Parameter reading in the VSIMV mode */
			else if (ActualMode == PSIMV)
			{
				*Value = EEP_DB_PSIMV_Adjust[Id];
				Function_Result = TRUE;
			}
#endif
/*%C 		Parameter reading in the PSVT mode */
			else if (ActualMode == PSVT)
			{ 
				*Value = EEP_DB_PSV_Adjust[Id];
				Function_Result = TRUE;
			}
/*%C 		Parameter reading in the CPAP mode */
			else if (ActualMode == CPAP)
			{ 
				*Value = EEP_DB_CPAP_Adjust[Id];
				Function_Result = TRUE;
		  }
			else
			{ 
				Function_Result = FALSE;
			}
			break;
		}
/*%C 	Parameter reading in the version base */
		case VERSION:
		{
			*Value = EEP_DB_Version_Number[Id];
			Function_Result = TRUE;
			break;	
		}
/*%C 	Parameter reading in the Config base */
/*%C 	If an error is detected in this base, the Id takes the default value */
		case CONFIG:
		{
 			if (DB_EepConfigDbError[Id] == TRUE)
			{
				*Value = cDB_TEST_CONFIG_DB[Id].defvalue;
			}
			else
			{
				*Value = EEP_DB_Config[Id];
			}
			Function_Result = TRUE;
			break;
		}
/*%C 	Parameter reading in the Trend base */
/*%C 	If an error is detected in this base, the Id takes the default value */
		case TREND:
		{
			if (DB_EepTrendDbError[Id] == TRUE)
			{
				*Value = cDB_TEST_TREND_DB[Id].defvalue;
			}
			else
			{
				*Value = EEP_DB_TREND[Id];
			}
			Function_Result = TRUE;
			break;
		}
/*%C 	Parameter reading in the Control base */
		case CONTROL:
		{
			*Value = DB_ControlRead(Id);
			Function_Result = TRUE;
			break;	
		} 

/*%C 	Parameter reading in the Compute base */
		case COMPUTE:
		{
			*Value = DB_ComputeRead(Id);
			Function_Result = TRUE;
			break;	
		} 

/*%C Parameter reading in the Alarm base */
		case ALARMS:
		{
			*Value = DB_AlarmStatusRead(Id); 
			Function_Result = TRUE;
			break;	
		} // case ALARMS:

/*%C Parameter reading in the RTC base */
		case RTC:
		{
			*Value = DB_Rtc[Id];
			Function_Result = TRUE;
			break;	
		} 
	
/*%C Parameter reading in the KEYBOARD base */
		case KEYBOARD:
		{
			*Value = DB_KeyboardEvent[Id];
			Function_Result = TRUE;
			break;
		}

/*%C Parameter reading in the KEYBOARD base */
		case CURRENT:
		{
			*Value = DB_Current[Id];
			Function_Result = TRUE;
			break;
		}

/*%C Parameter reading in the Power Supply base */
		case POWER_SUPPLY:
		{
			*Value = DB_PowerSupplyRead(Id);
			Function_Result = TRUE;
			break;
		}

/*%C Parameter reading in the Usb base */
		case USB:
		{
			*Value = DB_UsbRead(Id);
			Function_Result = TRUE;
			break;
		}

/*%C Parameter reading in the Revision base */
		case REVISION:
		{
			*Value = DB_RevisionRead(Id);
			Function_Result = TRUE;
			break;
		}

		default:
		{
			Function_Result = FALSE;
			break;
		}
	}
	return(Function_Result);
}


