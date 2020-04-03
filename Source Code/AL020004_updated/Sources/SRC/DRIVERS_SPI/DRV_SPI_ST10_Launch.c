/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_SPI_ST10_launch.c                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C          			max duration = 530 us (12/09/2006)					  			*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "define.h"
#include "DB_PowerSupply.h"
#include "DRV_SPI_ST10_Data.h"
#include "DRV_SPI_ST10_Launch.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void DRV_SPI_ST10_Launch(void)
{
	/*%C If no frame is detected the "no communication" flag is set to TRUE	*/
	if (TIM_ReadValue16(TIM_NO_FRAME) == 0)
	{		
		DB_PowerSupply_Write(NO_COMMUNICATION_CPU, TRUE);	
	}
	/*%C else, the "no communication" flag is set to FALSE	*/
	else
	{
		DB_PowerSupply_Write(NO_COMMUNICATION_CPU, FALSE);
	}

	/*%C SPI buffer read function call	*/
	DRV_SPI_ST10_ReadBuffer();
	
}
