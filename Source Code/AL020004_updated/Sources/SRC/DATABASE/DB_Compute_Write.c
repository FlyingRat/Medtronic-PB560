/******************************************************************************/
/*																 	          						*/
/* Project Number	: 	RB0505     			     	       	  		          			*/
/*																	          						*/
/*----------------------------------------------------------------------------*/
/*                                                 			  	              	*/
/* Filename	: DB_Compute_Write.c 			   	           		              	*/
/*                                                 			  		          	*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 						Functionnal description : 				          				*/
/*%C			  This function writes the values in the				      			*/
/*%C         				  compute base							          				*/
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
	#define DECLARATION_COMPUTE_BASE
#include "DB_Compute.h"

/******************************************************************************/
/*                     EXTERNAL FUNCTION DECLARATION                         	*/
/******************************************************************************/
void DB_Compute_Write(e_DB_Compute Id, UWORD16 Value)
{
/*%C Writes the parameter value in the Measurement array if the Id parameter */
/*%C belongs to the compute base */
	if(Id < end_of_db_compute_table)
	{
		DB_Compute[Id] = Value;
	}
}

