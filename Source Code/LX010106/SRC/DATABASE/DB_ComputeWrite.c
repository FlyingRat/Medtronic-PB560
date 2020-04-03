/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_ComputeWrite.c 			   				                  		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function writes the values in the	*/
/*%C         compute base																		*/
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter : 			Id			        			                  	*/
/*%I 						  				Value		      	        			           	*/
/*%IO Input/Output Parameter : 	None 	        			                  		*/
/*%O 	Output Parameter : 			None			                          			*/
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "structure.h"
#include "DRV_VarEeprom.h"
#define DECLARATION_COMPUTE_BASE
#include "DB_IhmAccessParaDataBase.h"
#include "DB_Compute.h"
/******************************************************************************/
/*                     EXTERNAL FUNCTION DECLARATION                         	*/
/******************************************************************************/
void DB_ComputeWrite(e_DB_COMPUTE Id, UWORD16 Value)
{
/*%C Writes the parameter value in the compute array if the Id parameter     */
/*%C belongs to the compute base   */                      	                    
	if(Id < end_of_db_compute_table)
		{
		if (cDB_Saturate_COMPUTE[Id].issigned == 1	)
			{
			if ((SWORD16)Value > (SWORD16)cDB_Saturate_COMPUTE[Id].cDB_TEST_DB.maxi) Value = cDB_Saturate_COMPUTE[Id].cDB_TEST_DB.maxi;
			else if ((SWORD16)Value < (SWORD16)cDB_Saturate_COMPUTE[Id].cDB_TEST_DB.mini) Value = cDB_Saturate_COMPUTE[Id].cDB_TEST_DB.mini; 
			}
		else	  	
			{
			if (Value > cDB_Saturate_COMPUTE[Id].cDB_TEST_DB.maxi) Value = cDB_Saturate_COMPUTE[Id].cDB_TEST_DB.maxi;
			else if (Value < cDB_Saturate_COMPUTE[Id].cDB_TEST_DB.mini) Value = cDB_Saturate_COMPUTE[Id].cDB_TEST_DB.mini; 
			}
		DB_Compute[Id] = (UWORD16)Value;	
		}
}
