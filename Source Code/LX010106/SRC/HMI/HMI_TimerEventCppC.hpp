/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_TimerEventCppC.hpp 	 					 		 			  	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_TimerEventCppC.cpp 	 						     	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef _IHMTIMER_H
#define _IHMTIMER_H

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_IhmType.hpp"

extern "C"
{
#include "io_declare.h"
#include "enum.h"
}

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

extern UWORD16 IHM_GetCrossRefTimerId(EventId);

extern EventId IHM_GetEventIdOfTimer(UWORD16 TimerId);

//extern void IHM_Start(void);

extern "C" UWORD16 TIM_TestMinuteDecounterActivateOk(e_TIM_MINUTE_TABLE_ID offset_table);

extern "C" UWORD16 TIM_TestMinuteOverflowOk(e_TIM_MINUTE_TABLE_ID offset_table);

#endif
