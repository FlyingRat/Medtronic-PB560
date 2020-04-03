/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : MAIN_Version_Error_Mngt.c                                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C       If it is a bad version, then the ventilation is not allowed, 		*/
/*%C		  and a message is displayed continously.         							*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/
/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/
#ifndef _TASKING
#include "LH_ST10F276.h"
#include <intrins.h>
#else
#include "regf276e.h"
#endif
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "define.h"

#include "io_declare.h"
#include "Driver_Display_Data.h"
#include "DB_Config.h"
#include "DB_Control.h"
#include "DB_Rtc.h"
#include "DB_Current.h"
#include "DB_AlarmStatus.h"
#include "DB_Event.h"
#include "Security_Datas.h"
#include "DB_AlarmStatus.h"
#include "MAIN_Version_Error_Mngt.h"
#include "DB_IhmAccessParaDatabase.h"
#include "DRV_VarEeprom.h"
#include "PUST.h"
			 
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void MAIN_Version_Error_Mngt(void)
{
/*%C If a bad version is detected, an alarm flag is set         			      */
   if ( (BadVersion == TRUE)
     && (EEP_DB_Config[VENTIL_REQ_U16] == FALSE) ) 
   {
/*%C 	Ventilation stop if reboot         			      */
      DB_ConfigWrite(VENTIL_REQ_U16,FALSE);

#ifndef _TASKING
/*%C 	Enter infinite loop         			      */
      PUST_Checks(TRUE, PUST_SOFT_VERSION_CHECK_REQ);
#endif	
	}
}