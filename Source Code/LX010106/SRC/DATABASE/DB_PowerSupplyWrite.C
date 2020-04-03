/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_PowerSupplyWrite.c	   				               	   		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function writes the values in the	*/
/*%C         measurement base																	*/
/*                                                            				  		*/
/******************************************************************************/
/*%I Input Parameter : 				Id		  	        			                  	*/
/*%I 						  				Value	  	        			                  	*/
/*%IO Input/Output Parameter : 	None 	        			                  		*/
/*%O Output Parameter : 			None	                       				  		*/
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "DRV_VarEeprom.h"
#define DECLARATION_POWERSUPPLY_BASE
#include "DB_IhmAccessParaDataBase.h"
#include "DB_PowerSupply.h"
/******************************************************************************/
/*                    EXTERNAL FUNCTION DECLARATION                          	*/
/******************************************************************************/
void DB_PowerSupplyWrite(e_DB_POWERSUPPLY Id,
								 UWORD16 Value)
{
	if(Id < end_of_db_powersupply_table)
		{
		if (cDB_Saturate_POWERSUPPLY[Id].issigned == 1	)
			{
			if ((SWORD16)Value > (SWORD16)cDB_Saturate_POWERSUPPLY[Id].cDB_TEST_DB.maxi) Value = cDB_Saturate_POWERSUPPLY[Id].cDB_TEST_DB.maxi;
			else if ((SWORD16)Value < (SWORD16)cDB_Saturate_POWERSUPPLY[Id].cDB_TEST_DB.mini) Value = cDB_Saturate_POWERSUPPLY[Id].cDB_TEST_DB.mini; 
			}
		else	  	
			{
			if (Value > cDB_Saturate_POWERSUPPLY[Id].cDB_TEST_DB.maxi) Value = cDB_Saturate_POWERSUPPLY[Id].cDB_TEST_DB.maxi;
			else if (Value < cDB_Saturate_POWERSUPPLY[Id].cDB_TEST_DB.mini) Value = cDB_Saturate_POWERSUPPLY[Id].cDB_TEST_DB.mini; 
			}
		DB_powerSupply[Id] = Value;
		}
}
