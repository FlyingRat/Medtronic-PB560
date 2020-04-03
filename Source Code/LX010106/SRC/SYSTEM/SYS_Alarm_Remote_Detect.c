/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_Alarm_Remote_Detect.c                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Detection of the alarm Remote      	    				   */
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
#include "SYS_Alarm_Remote_Detect.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void SYS_Alarm_Remote_Detect(void)
{
/*----------------------------------------------------------------------------*/
/* Detection of an alarm remote :                                             */
/*%C If the interface input "ALARM_REMOTE_STATE" get a "FALSE" state 			*/
/*%C corresponding to 0 V, then write "TRUE" into "REMOTE_STATE_U16" 			*/
/*%C of "control data base"             													*/
	if (ALARM_REMOTE_STATE == FALSE)
	{
		DB_ControlWrite(REMOTE_STATE_U16,
		                TRUE);
   	}
/*%C else, write "FALSE" into "REMOTE_STATE_U16" of "control data base"      */
	else
	{
		DB_ControlWrite(REMOTE_STATE_U16,   
		                FALSE);
	}

}