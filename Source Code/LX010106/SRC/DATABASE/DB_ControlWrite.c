/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_ControlWrite.c 			   				                  		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function writes the values in the	*/
/*%C         control base																		*/
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter : 			Id			        			                  	*/
/*%I 						  				Value                                 		  	*/
/*%IO Input/Output Parameter : 	None 	        			                  		*/
/*%O 	Output Parameter : 			None	                      				  		*/
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "DB_Control.h"
#include "DB_Rtc.h"
#include "DB_Current.h"
#include "DB_Config.h"
#include "DB_IhmAccessParaDataBase.h"
/******************************************************************************/
/*                    EXTERNAL FUNCTION DECLARATION                          	*/
/******************************************************************************/
void DB_ControlWrite(e_DB_CONTROL Id,
							UWORD16 Value)
{
/*%C If Id is an element of the control base, the value is written				*/
	if(Id < end_of_db_control_table)
	{
		DB_Control[Id] = Value;
	}
}
