/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_CommFail.c              		                     		  	*/
/*													 						  							*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C               Detection of Communication default				     	  			*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                         	*/
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "DRV_SPI_ST10_Data.h"
#include "DB_PowerSupply.h"
#include "DB_Control.h"
#include "SEC_CommFail.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void SEC_CommFail(void)
{

	UWORD16 NoCommunicationCpu = DB_PowerSupply_Read(NO_COMMUNICATION_CPU);
	UWORD16 CpuOn = DB_Control_Read(CPU_ON);

	/*%C If Frame error counter reading  */
	/*%C or ( communication interrupted and */
	/*%C Cpu supplied with 24V ) */
	if 	((DRV_SPI_ST10_Status == DRV_SPI_ST10_BAD_FRAME)
		||	((NoCommunicationCpu == TRUE)
		&&	(CpuOn == TRUE)))
	{
	/*%C The flag COMMUNICATION_FAILURE_FLAG is set */
		DB_PowerSupply_Write(COMMUNICATION_FAILURE_FLAG,TRUE);
	}
	/*%C Else, the flag COMMUNICATION_FAILURE_FLAG is reset */
	else
	{
		DB_PowerSupply_Write(COMMUNICATION_FAILURE_FLAG,FALSE);
	}
}
