/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_SupplyDetect.c                                           	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C  Detect Supply used																	 	*/
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                           INCLUDE FILES		                              */
/******************************************************************************/
#ifndef _TASKING
	#include "LH_ST10F276.h"
	#include <intrins.h>
#else	    
 		#include "regf276e.h"
#endif 	
#include "io_declare.h"
#include "DB_Control.h"
#include "DB_PowerSupply.h"
#include "SYS_SupplyDetect.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void SYS_SupplyDetect(void)
{
	UWORD16 PowerType	= DB_PowerSupplyRead(POWER_TYPE_U16);

/*%C Ac supply state record */
 	DB_ControlWrite(AC_SELECTED_U16,AC_SELECT);

/*%C Supply Status Read */
	DB_ControlWrite(SUPPLY_AC_DC_BAT_U16, PowerType); 
}