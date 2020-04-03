/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_InitializeTables.c 	   				                  		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function makes the init off all  	*/
/*%C        temporary tables.                        									*/
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameters :  			None          			                  		*/
/*%IO Input/Output Parameters :  None          			                  		*/
/*%O 	Output Parameters :  		None         			                  		*/
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/

#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "DB_Compute.h"
#include "DB_Control.h"
#include "DB_Config.h"
#include "DB_PowerSupply.h"
	#define DECLARATION_MEASUREMENT_BASE
#include "DB_Measurement.h"
#include "DB_Rtc.h"
#include "DB_Current.h"
#include "DB_InitializeTables.h"
#include "DB_AlarmStatus.h"
#include "DB_IhmAccessParaDataBase.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void DB_InitializeTables(void)
{
/* Id Declaration  */
	UWORD16 Id=0;

/*%C Compute base initialization.                    									*/
	for (Id=0;Id<end_of_db_compute_table;Id++)
	{
		DB_Compute[Id] = cDB_Saturate_COMPUTE[Id].cDB_TEST_DB.defvalue;
	}

/*%C Control base initialization.                    									*/
	for (Id=0;Id<end_of_db_control_table;Id++)
	{
		DB_Control[Id] = cDB_TEST_CONTROL_DB[Id].defvalue;
	}

/*%C Patient and machine counter initialization.            						*/
	DB_Control[CURRENT_PATIENT_COUNTER_HOUR_U16] =
	                            DB_ConfigRead(SAVED_PATIENT_COUNTER_HOUR_U16);

	DB_Control[CURRENT_PATIENT_COUNTER_MIN_U16] =
	                            DB_ConfigRead(SAVED_PATIENT_COUNTER_MIN_U16);

	DB_Control[CURRENT_MACHINE_COUNTER_HOUR_U16] =
	                            DB_ConfigRead(SAVED_MACHINE_COUNTER_HOUR_U16);

	DB_Control[CURRENT_MACHINE_COUNTER_MIN_U16] =
	                            DB_ConfigRead(SAVED_MACHINE_COUNTER_MIN_U16);

/*%C Measurement base initialization.                									*/
	for (Id=0;Id<end_of_db_measurement_table;Id++)
	{
		DB_Measurement[Id] = 0;
	}

/*%C RTC base initialization.                      									*/
	for (Id=0;Id<end_of_db_rtc_table;Id++)
	{
		DB_Rtc[Id] = 0;
	}

/*%C Current base initialization.                    									*/
	for (Id=0;Id<end_of_adjust_table;Id++)
	{
		DB_Current[Id] = 0;
	}

/*%C Priority alarm level initialization            									*/
	for (Id=0;Id<end_of_alarms_table;Id++)
	{
		DB_AlarmStatus[Id] = 0;
	}

/*%C Power Supply base initialization.               									*/
/*%C Spi Power is launched before the scheduler */

}
