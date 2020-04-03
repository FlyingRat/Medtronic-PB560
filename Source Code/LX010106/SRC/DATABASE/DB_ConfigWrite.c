/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_ConfigWrite.c 			   				                  		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function writes the values in the	*/
/*%C         config base																		*/
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter : 			Id		  	        			                  	*/
/*%I 						  				Value                                 		  	*/
/*%IO Input/Output Parameter : 	None 	        			                  		*/
/*%O 	Output Parameter : 			None  	                   				  		*/
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "structure.h"
#include "DB_Control.h"
#include "DB_Rtc.h"
#include "DRV_VarEeprom.h"
#include "DB_Config.h"
#include "DB_IhmAccessParaDataBase.h"
/******************************************************************************/
/*                     EXTERNAL FUNCTION DECLARATION                         	*/
/******************************************************************************/
UWORD16 DB_ConfigWrite(e_DB_CONFIG Id,
							  UWORD16 Value)
{
UWORD16 TempValue;
UWORD16 Result = FALSE;

/*%C Check the Id included in the config table		                        	*/
	if(Id < end_of_db_config_table)
	{
/*%C Min and max test										                        	*/
		if ( (Value < cDB_TEST_CONFIG_DB[Id].mini)
	  	  || (Value > cDB_TEST_CONFIG_DB[Id].maxi) )
		{
/*%C 		Value out of range => Id takes its default value  							*/
			TempValue = cDB_TEST_CONFIG_DB[Id].defvalue;
/*%C 		The function returns FALSE								  							*/
			Result = FALSE;
		}
		else
		{
/*%C 		The value is in range									  							*/
			TempValue = Value;
/*%C 		The function returns TRUE							  								*/
			Result = TRUE;

/*%C 		Offset test in order to have the curent point to calibrate lower than the	*/
/*%C 		previous calibrated point (for the flow calibration)	*/
			if (((Id > OFFSET_INSP_FLOW_1_U16) && (Id <= OFFSET_INSP_FLOW_8_U16))
			  ||((Id > OFFSET_EXH_FLOW_1_U16) && (Id <= OFFSET_EXH_FLOW_8_U16)))
			{
				if (TempValue < EEP_DB_Config[Id-1])
				{
/*%C 				TempValue reaffectation						  								*/
					TempValue = EEP_DB_Config[Id-1];
				}
			}
/*%C		Valve Offset check																				*/			
			else if ((Id > OFFSET_FAS_VALVE_3_U16) && (Id <= OFFSET_FAS_VALVE_9_U16))
			{
/*%C			Valve Offset protection - previous value + 15								*/			
				if (TempValue > EEP_DB_Config[Id-1] - 15)
				{
/*%C 				Value out of range => Id takes previous value + 15 					*/
					TempValue = EEP_DB_Config[Id-1] - 15;
/*%C 				The function returns FALSE							  								*/
					Result = FALSE;
				}
			}
		}
/*%C 			Value writing in eeprom and ram						  								*/
		DB_WriteDataInEepAndRam(&EEP_DB_Config[Id],
										TempValue);
	}


return(Result);
}
