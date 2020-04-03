/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : INIT_DataBase.c																*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                		  Database initialization   									*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES											*/
/******************************************************************************/

#include "p18f6622.h"
#include "typedef.h"
#include "define.h"
#include "DB_Config.h"
#include "DB_Control.h"
#include "DB_Measurement.h"
#include "DB_PowerSupply.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void INIT_DataBase(void)
{
	UBYTE Id = 0;

	for(Id = 0 ; Id < end_of_db_config_table ; Id++)
	{
		DB_Config[Id]= NULL;
	}
	for(Id = 0 ; Id < end_of_db_control_table ; Id++)
	{
		DB_Control[Id]= NULL;
	}
	for(Id = 0 ; Id < end_of_db_measurement_table ; Id++)
	{
		DB_Measurement[Id]= NULL;
	}
	for(Id = 0 ; Id < end_of_db_Powersupply_table ; Id++)
	{
		DB_powerSupply[Id]= NULL;
	}
	/*%C Run WatchDog */
	ClrWdt();
}
