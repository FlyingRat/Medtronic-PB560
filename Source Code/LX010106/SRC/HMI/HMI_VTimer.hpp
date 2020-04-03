/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_VTimer.hpp                           	 	  						*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Classe declaration for HMI_VTimer.cpp	                       				*/
/*		                                                                   	 	*/
/******************************************************************************/

#ifndef VTimerH
#define VTimerH

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_IhmType.hpp"
extern "C"
{
#include "typedef.h"
#include "enum.h"
}

/******************************************************************************/
/*                           CLASSE DECLARATION                    	      	*/
/******************************************************************************/

class VTimer
{
private:

   /* Parametres */

   /* Méthodes */

protected:

   /* Parametres */

   /* Méthodes */

public:

   /* Parametres */

   /* Méthodes */

   /* VTimer::*/
   VTimer();

   void StartTimer(	UWORD32 Delay, 
   					UWORD16 Event, 
   					e_BOOL AutoReload);

   void StopTimer(UWORD16 Event);

	void RemoveAll(void);

};

extern "C" void TIM_StartMinuteDecounter(e_TIM_MINUTE_TABLE_ID offset_table,
									                   UWORD32 value,
									                   e_BOOL autoreload);

extern "C" void TIM_StopMinuteDecounter(e_TIM_MINUTE_TABLE_ID offset_table);

#endif
