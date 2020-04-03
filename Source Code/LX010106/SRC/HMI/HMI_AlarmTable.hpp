/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_AlarmTable.hpp		                                      	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																									*/
/*%C Classe declaration for HMI_AlarmTable.cpp		                          	*/
/*%C                                                                          */
/******************************************************************************/

#ifndef AlarmTableH
#define AlarmTableH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_DisplayObject.hpp"
extern "C"
{
#include "typedef.h"
}

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

#ifdef _BORLAND
   #define cMAX_ALARM 100
#else
   #define cMAX_ALARM 30
#endif

#define cNO_ALARM  9999

class AlarmTable
{
private:

   /* Parametres */

	AlarmEvent TableAlarm[cMAX_ALARM];

   /*%C CurrentIndex [ 0: cMAX_ALARM ] */
   UWORD16 CurrentIndex;

   /*%C NbAlarm, [ 0: cMAX_ALARM ] */
   UWORD16 NbAlarm;

   /*%C MaxAction; [ 12 : 24 ] */
   UWORD16 MaxAction;

   AlarmEvent LastAlarm;   

   /* Methodes */

	void SetAlarmEntry(AlarmEvent* _alarm, UWORD16 _index, e_BOOL _logtolast);

protected:

   /* Parametres */

   /* Methodes */

public:

   /* Parametres */

   /* Methodes */

   AlarmTable();

   UWORD16 GetCurrentIndex();
   void SetCurrentIndex(UWORD16 CurrentIndex);

   UWORD16 GetNbAlarm();
   void SetNbAlarm(UWORD16 Nb);

   UWORD16 GetMaxAction();
   void SetMaxAction(UWORD16 MaxAction);

   UWORD16 FindAlarm(UWORD16 Id);
   AlarmEvent* GetAlarmFromId(UWORD16 _Id);
   UWORD16 FindFreeIndex();
   UWORD16 FindFirstOfTwoFreeIndex();
   UWORD16 FindNextAlarm(UWORD16 CurrentIndex);
   UWORD16 FindAlarmWithLast(void);
   UWORD16 FindMaxAction();

   AlarmEvent* GetLastAlarm();
   void SetLastAlarm(AlarmEvent* _last);

   void AddElement(AlarmEvent* Alarm, e_BOOL _LogToLast);
   void AddElement2(AlarmEvent* Alarm, e_BOOL _LogToLast);
   void RemoveElement(AlarmEvent* Alarm, e_BOOL _LogToLast);
   void RemoveAll(void);
   void Refresh();

};

#endif
