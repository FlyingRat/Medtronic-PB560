/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SWITCH_Launch.c                                                */
/*													 						  							*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                     																		*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/

#include "typedef.h"
#include "enum.h"
#include "define.h"
#include "DB_Control.h"
#include "DB_PowerSupply.h"
#include "SWITCH_Launch.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

   
/******************************************************************************/
/* Description          : Periodic Interrupt handler (every 5ms)        	  	*/
/* Parametres en entree : aucun                                         	  	*/
/* Parametres en sortie : aucun                                         	  	*/
/* Contrainte                                                           	 	*/
/*        Pré-conditions  : Néant                                       	  	*/
/*        Post-condition  : Néant                                       	  	*/
/*        Exceptions      : Néant                                     		  	*/
/******************************************************************************/

void SWITCH_Launch(void)
{
	UWORD16 Sampling_OK = DB_Control_Read(SAMPLING_OK);
	UWORD16 MaintenanceControl = DB_Control_Read(MAINTENANCE_CONTROL);
	static UWORD16 PreviousMaintenanceControl = FALSE ;

/*%C	if the sampling is correct,															*/
	if (Sampling_OK == TRUE)
	{ 
		/*%C Then if MaintenanceControl = FALSE*/ 
		if(MaintenanceControl == FALSE)
		{
			/*%C then the supply detection and state control function are detected	*/
			SWITCH_Supply_Detection();
			SWITCH_State_Control();
		}
			/*%C Else */
		else
		{
			/*%C If PreviousMaintenanceControl = FALSE*/
			if(PreviousMaintenanceControl == FALSE)
			{
				/*%C Then OU à DIODE */
				DRV_Switch(AC_DC_BAT);
				DB_PowerSupply_Write(POWER_TYPE_U16,AC_DC_BAT);
				DB_Control_Write(SUPPLY_STATE,AC_DC_BAT);
			}
			/*%C Maintenance Control mode 													*/
		}
	}
	PreviousMaintenanceControl = MaintenanceControl;
}
