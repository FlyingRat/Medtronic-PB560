/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_AlarmStatusRead.c	 	   				                  		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/

/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "DB_AlarmStatus.h"
#include "Security_Datas.h"
/******************************************************************************/
/*                     EXTERNAL FUNCTION DECLARATION                         	*/
/******************************************************************************/
e_BOOL DB_AlarmIsActive(e_DB_ALARM_LEVEL_PRIORITY prio)
{
    e_BOOL active = FALSE;

    switch (prio) {

        case HP :
        /* High */
        active = (SEC_High_Priority_1 || SEC_High_Priority_2 || SEC_High_Priority_3)?TRUE:FALSE;
        break;

        case MPR :
        /* Medium */
        active = (SEC_Medium_Priority_1 || SEC_Medium_Priority_2 || SEC_Medium_Priority_3)?TRUE:FALSE;
        break;

        case LP :
        /* Low */
        active = (SEC_Low_Priority)?TRUE:FALSE;
        break;

        default:
        break;
    }
    return active;
}

e_BOOL DB_AlarmIsOneActive(void)
{
    return (DB_AlarmIsActive(HP) || DB_AlarmIsActive(MPR) || DB_AlarmIsActive(LP));
}
