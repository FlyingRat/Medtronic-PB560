/******************************************************************************/
/*																 	          						*/
/* Project Number	: 	RB0505     			     	       	  		          			*/
/*																	          						*/	
/*----------------------------------------------------------------------------*/
/*                                                 			  	              	*/
/* Filename	: DB_EEPROM_BAT_Write.c 			   	           		            */
/*                                                 			  		          	*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 						Functionnal description : 				          				*/
/*%C		This function writes the values in the EEPROM Battery base				*/
/******************************************************************************/
/*%I 	Input Parameter : 			Id			                 	          			*/
/*%I 										Value		                 	          			*/
/*%IO	Input/Output Parameter : 	None          		                      		*/
/*%O 	Output Parameter : 			None				  		              				*/
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		         	              	*/
/******************************************************************************/

#include "typedef.h"
	#define DECLARATION_EEPROM_BAT_BASE
#include "DB_EEPROM_BAT.h"

/******************************************************************************/
/*                     EXTERNAL FUNCTION DECLARATION                         	*/
/******************************************************************************/
void DB_EEPROM_BAT_Write(e_EEPROM_BAT_DATA Id, UBYTE Value)
{
/*%C Writes the parameter value in the EEPROM array if the Id parameter 		*/
/*%C belongs to the EEPROM Battery base 													*/
	if(Id < EEPROM_BAT_EnOfTableData)
	{
		Ram_Write_Bat[Id-DATA_VARIABLE_BAT_AGEING_1] = Value;
	}
}
