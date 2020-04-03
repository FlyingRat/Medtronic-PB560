/******************************************************************************/
/*																 	          						*/
/* Project Number	: 	RB0505     			     	       	  		          			*/
/*																	          						*/
/*----------------------------------------------------------------------------*/
/*                                                 			  	              	*/
/* Filename	: DRV_EEPROM_BAT_DifferenceZoneReadWrite.c 			   	         */
/*                                                 			  		          	*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 							Functionnal description : 				          			*/
/*%C	Compare the 2 array memories (Ram_Read_Bat and Ram_Write_Bat)				*/
/******************************************************************************/
/*%I 	Input Parameter : 			None			              	          			*/
/*%IO Input/Output Parameter : 	None 	          		                      	*/
/*%O 	Output Parameter : 			TRUE or FALSE	  		              				*/
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		         	              	*/
/******************************************************************************/

#include "typedef.h"
#include "enum.h"
#include "DB_EEPROM_BAT.h"

/******************************************************************************/
/*                                FUNCTION BODY                               */
/******************************************************************************/
UWORD16 DRV_EEPROM_BAT_DifferenceZoneReadWrite(void)
{
	UBYTE LoopReadEEPROM = 0;
	UWORD16 return_value = FALSE;
	
	/*%C	Compare 2 arrays memory																*/
	do
	{
		if(Ram_Read_Bat[LoopReadEEPROM + DATA_VARIABLE_BAT_AGEING_1]
						 != Ram_Write_Bat[LoopReadEEPROM])
		{
			/*%C Both array are different														*/
			return_value = TRUE;
		}
		else
		{
			/*No Function */
		}
		LoopReadEEPROM = LoopReadEEPROM + 1 ;
	}
	while(	(LoopReadEEPROM < (EEPROM_BAT_EnOfTableData - DATA_VARIABLE_BAT_AGEING_1))
				&& (return_value == FALSE)	);
	return (return_value);	
}
