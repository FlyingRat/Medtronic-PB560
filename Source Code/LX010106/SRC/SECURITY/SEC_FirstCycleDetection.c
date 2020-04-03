/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_FirstCycleDetection.c                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   This function detects the first and the second cycle of respiration    */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "DB_Control.h"
#include "SEC_FirstCycleDetection.h"
#include "Ventilation_Datas.h"

/* locate security code to specific section */  
#include "locate_security_code.h" 

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/


void SEC_FirstCycleDetection(void)
{
/*%C Ventil state recovery 													  */
	UWORD16 VentilState = DB_ControlRead(VENTIL_STATE_U16);

/*%C Ventil authorization 													  */
	UWORD16 VentilAuthorization = DB_ControlRead (VENTIL_AUTHORIZATION_U16);

/*%C Ventil state previous state											  */
	static UWORD16 VentilStateMemo = VEN_EXHALATION;

/*%C Cycle counter 															  */
	static UWORD16 CptCycle = 0;

/*%C If VENTIL_AUTHORIZATION_U16 = FALSE, then								  */
	if (VentilAuthorization == FALSE)
	{
/*%C CptCycle, VEN_FirstCycle, VEN_SecondCycle, VEN_ThirdCycle,				  */
/*%C START_MONITORING_U16 flags are reset to FALSE							  */
		CptCycle    = 0;
		VEN_FirstCycle  = FALSE;
		VEN_SecondCycle = FALSE;
		VEN_ThirdCycle = FALSE;
		DB_ControlWrite(START_MONITORING_U16, FALSE);
      
	} 
/*%C Else if ( VENTIL_STATE_U16 = VEN_INSPIRATION_CONTROLED 	   			  */
/*%C or VENTIL_STATE_U16 = VEN_INSPIRATION_TRIGGERED ) and 					  */
/*%C VentilStateMemo = VEN_EXHALATION and CptCycle < 4 						  */
   else if ( ( (VentilState == VEN_INSPIRATION_CONTROLED) 
            || (VentilState == VEN_INSPIRATION_TRIGGERED) )
		    && (VentilStateMemo == VEN_EXHALATION) 
		    && (CptCycle < 4) )
	{
/*%C  Then Counter cycle CptCycle increases 								  */
		CptCycle = CptCycle + 1;
/*%C  If Counter cycle CptCycle = 2 => first cycle detected 				  */
		if (CptCycle == 2)
		{
/*%C 	Then VEN_FirstCycle = TRUE, START_MONITORING_U16 = TRUE 			  */
			VEN_FirstCycle = TRUE;
			DB_ControlWrite(START_MONITORING_U16, TRUE);
		}
/*%C  Else if Counter cycle = 3 => second cycle detected 					  */
		else if (CptCycle == 3)
		{
/*%C 	Then VEN_SecondCycle = TRUE											  */
			VEN_SecondCycle = TRUE;
		}
/*%C  Else if Counter cycle CptCycle = 4 => third cycle detected 			  */
		else if (CptCycle == 4)
		{
/*%C 	Then VEN_ThirdCycle = TRUE											  */
			VEN_ThirdCycle = TRUE;
		}
/*%C 	End if 																  */
	}
/*%C End if																	  */
/*%C Ventil state memorization */
	VentilStateMemo = VentilState;
}
