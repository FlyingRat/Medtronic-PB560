/******************************************************************************/
/*																 	          						*/
/* Project Number	: 	RB0505     			     	       	  		         		 	*/
/*																	          						*/
/*----------------------------------------------------------------------------*/
/*                                                 			  	              	*/
/* Filename	: DB_PowerSupply_Write.c 		   	           		             	*/
/*                                                 			  		          	*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 						Functionnal description : 				          				*/
/*%C			  This function writes the values in the					 	 			*/
/*%C         			Power supply base							          				*/
/*                                                     				  		  		*/
/******************************************************************************/
/*%I 	Input Parameter : 			Id			                 	          			*/
/*%I 								Value		                 	          					*/
/*%IO	Input/Output Parameter : 	None          		                      		*/
/*%O 	Output Parameter : 			None				  		              				*/
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		         	              	*/
/******************************************************************************/

#include "typedef.h"
	#define DECLARATION_POWERSUPPLY_BASE
#include "DB_PowerSupply.h"

/******************************************************************************/
/*                     EXTERNAL FUNCTION DECLARATION                         	*/
/******************************************************************************/
void DB_PowerSupply_Write(e_DB_POWERSUPPLY Id, UWORD16 Value)
{
/*%C Writes the parameter value in the Measurement array if the Id parameter 	*/
/*%C belongs to the PowerSupply base 														*/
	if(Id < end_of_db_Powersupply_table)
	{
		DB_powerSupply[Id] = Value;
	}
}
