/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : MAIN_activate_tasks.c                                       	*/
/*													 						  							*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                   													*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/

#include "typedef.h"
#include "define.h"
#include "enum.h"
#include "Main_Data.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void MAIN_activate_tasks(void)
{
	static UBYTE TestSchedulerStep = 0;
	static UBYTE CounterTop1ms = 0;

	/* Tous les 10ms: Donner un Top Synchro pour 1 pas de Sequenceur				*/
	TestSchedulerStep = (UBYTE)((CounterTop1ms + 1)% NB_INTERRUPTS_BY_SCHEDULER_STEP);
	if (TestSchedulerStep == 0)
	{
 		TopTimer5ms = TRUE;
		CounterTop1ms = 0;
	}
	else 
	{
		CounterTop1ms++;
	}
}
