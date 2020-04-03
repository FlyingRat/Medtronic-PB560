/******************************************************************************/
/*																										*/
/* Project Number	: 	RA0104     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_Measurement_Write.c 			   				                  */
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 							Functionnal description : 										*/
/*%C				  This function writes the values in the								*/
/*%C         					 compute base													*/
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
#include "DB_Measurement.h"

/******************************************************************************/
/*                     EXTERNAL FUNCTION DECLARATION                         	*/
/******************************************************************************/
void DB_Measurement_Write(e_DB_Measurement Id, UWORD16 Value)
{
/*%C Writes the parameter value in the Measurement array if the Id parameter */
/*%C belongs to the compute base */
	if(Id < end_of_db_measurement_table)
	{
		DB_Measurement[Id] = Value;
	}
}

