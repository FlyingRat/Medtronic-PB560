/******************************************************************************/
/*																 	          						*/
/* Project Number	: 	RB0505     			     	       	  		          			*/
/*																	          						*/
/*----------------------------------------------------------------------------*/
/*                                                 			  	              	*/
/* Filename	: DB_Control_Write.c 			   	           		              	*/
/*                                                 			  		          	*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 						Functionnal description : 				          				*/
/*%C			  This function writes the values in the				      			*/
/*%C         				  control base							          				*/
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
	#define DECLARATION_CONTROL_BASE
#include "DB_Control.h"

/******************************************************************************/
/*                     EXTERNAL FUNCTION DECLARATION                         	*/
/******************************************************************************/
void DB_Control_Write(e_DB_Control Id, UWORD16 Value)
{
/*%C Writes the parameter value in the Measurement array if the Id parameter 	*/
/*%C belongs to the compute base 															*/
	if(Id < end_of_db_control_table)
	{
		DB_Control[Id] = Value;
	}
}
