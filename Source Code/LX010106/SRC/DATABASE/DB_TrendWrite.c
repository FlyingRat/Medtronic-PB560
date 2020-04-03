/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_TrendWrite.c 			   				                  		*/
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
#include "DRV_VarEeprom.h"
#include "DB_IhmAccessParaDataBase.h"
#include "DB_TrendWrite.h"
/******************************************************************************/
/*                     EXTERNAL FUNCTION DECLARATION                         	*/
/******************************************************************************/
UWORD16 DB_TrendWrite(e_DB_Trend Id,
							  UWORD16 Value)
{
UWORD16 TempValue;
UWORD16 Result = FALSE;

/*%C Check the Id included in the config table		                        	*/
	if(Id < end_of_db_trend_table)
	{
		if ( Value < cDB_TEST_TREND_DB[Id].mini) 
			{
			TempValue = 	cDB_TEST_TREND_DB[Id].mini;
			Result = FALSE;
			}
	  	else if (Value > cDB_TEST_TREND_DB[Id].maxi) 
			{
			TempValue = cDB_TEST_TREND_DB[Id].maxi;
			Result = FALSE;
			}
		else
			{
			TempValue = Value;
			Result = TRUE;
			}
		
/*%C 	Value writing in eeprom and ram						  								*/
		DB_WriteDataInEepAndRam(&EEP_DB_TREND[Id],
										TempValue);
	}

return(Result);
}