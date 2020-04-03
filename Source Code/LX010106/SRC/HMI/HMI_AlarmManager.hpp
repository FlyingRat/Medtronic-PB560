/******************************************************************************/
/*                                                                            */
/* Project N  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_AlarmManager.hpp	  	                                    	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  */
/*%C Classe declaration for HMI_AlarmManager.cpp	                          */
/*%C                                                                          */
/******************************************************************************/

#ifndef AlarmManagerH
#define AlarmManagerH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_LabelSymbol.hpp"

extern "C"
{
#include "typedef.h"
}

/* Alarm Manager double message alarms */
typedef enum {  AMANAGER_DOUBLE_ACTIVE = 0,
                AMANAGER_DOUBLE_INACTIVE } eAMANAGER_DOUBLE;
/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class AlarmManager
{

private:
   
   /* Parametres */

   /*%C RefreshActif [ 0: ??? ] */
   UWORD16 RefreshActif;
   eAMANAGER_DOUBLE DoubleAlarm;

	/* Methodes */

protected:

   /* Parametres */

   /* Methodes */

public:

   /* Parametres */

   /* Methodes */

   AlarmManager();
   e_BOOL IsAlarmValid(AlarmEvent* _alarm);         
   e_BOOL IsDoubleAlarmActive();
   void CallRefresh();
   void Refresh();

};

#endif
