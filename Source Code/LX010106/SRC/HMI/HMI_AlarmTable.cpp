/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_AlarmTable.cpp                                   			  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C This function computes a correction value for the control command        */
/*		                                                                        */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		              		    */
/******************************************************************************/

#include "HMI_AlarmTable.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_Controller.hpp"
extern "C"
{
#include "DB_AlarmStatus.h"
}

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
AlarmTable::AlarmTable()
{
   	RemoveAll();
	CurrentIndex = cMAX_ALARM;
	NbAlarm = 0;
	MaxAction = 0;
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void AlarmTable::SetMaxAction(UWORD16 _MaxAction)
{
	MaxAction = _MaxAction;
}
/*----------------------------------------------------------------------------*/
UWORD16 AlarmTable::GetMaxAction()
{
	return MaxAction;
}
/*----------------------------------------------------------------------------*/
void AlarmTable::SetCurrentIndex(UWORD16 _CurrentIndex)
{
	CurrentIndex = _CurrentIndex;
}
/*----------------------------------------------------------------------------*/
UWORD16 AlarmTable::GetCurrentIndex()
{
	return CurrentIndex;
}
/*----------------------------------------------------------------------------*/
void AlarmTable::SetNbAlarm(UWORD16 _Nb)
{
	NbAlarm = _Nb;
}
/*----------------------------------------------------------------------------*/
void AlarmTable::SetAlarmEntry(AlarmEvent* _alarm, UWORD16 _index, e_BOOL _logtolast)
{
	TableAlarm[_index].id     = _alarm->id;
	TableAlarm[_index].action = _alarm->action;
	TableAlarm[_index].logtolast = _logtolast;
	TableAlarm[_index].day    = _alarm->day;
	TableAlarm[_index].month  = _alarm->month;
	TableAlarm[_index].year   = _alarm->year;
	TableAlarm[_index].hour   = _alarm->hour;
	TableAlarm[_index].min    = _alarm->min;
    SetCurrentIndex(_index);
}
/*----------------------------------------------------------------------------*/
UWORD16 AlarmTable::GetNbAlarm()
{
	return NbAlarm;
}
/*----------------------------------------------------------------------------*/
AlarmEvent* AlarmTable::GetAlarmFromId(UWORD16 _Id)
{
	UWORD16 _FoundId = FindAlarm(_Id);

   if( _FoundId != (UWORD16)(NO_ALARM))
      return(&TableAlarm[_FoundId]);
   else
      return(NULL);
}
/*----------------------------------------------------------------------------*/
AlarmEvent* AlarmTable::GetLastAlarm()
{
    return (&this->LastAlarm);
}
/*----------------------------------------------------------------------------*/
void AlarmTable::SetLastAlarm(AlarmEvent* _last)
{
    this->LastAlarm.id = _last->id;
    this->LastAlarm.action = _last->action;
	this->LastAlarm.logtolast = _last->logtolast;
    this->LastAlarm.hour = _last->hour;
    this->LastAlarm.min = _last->min;
    this->LastAlarm.day = _last->day;
    this->LastAlarm.month = _last->month;
    this->LastAlarm.year = _last->year;
}
/******************************************************************************/
/*                           METHODES                					      		*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Retourne l'indice de la prochaine alarme du tableau								*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		Current : Indice de l'alarme courante								 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		Index : Indice de la prochaine Alarme  							  			*/
/******************************************************************************/
UWORD16 AlarmTable::FindNextAlarm(UWORD16 _Current)
{
	UWORD16 Index = _Current;

	/*%C Look for the next valid alarm in the space of TableAlarm */
	do
   {
      Index++;
		if(Index >= cMAX_ALARM)
      {
			Index = 0;
		}
	}
   while((TableAlarm[Index].id == NO_ALARM) && (Index != _Current));

	/*%C if no alarm found return NO_ALARM else return the alarm's Index */
	if(TableAlarm[Index].id == NO_ALARM)
   {
		return (UWORD16)(NO_ALARM);
	}
	else
   {
		return Index;
	}
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Retourne l'indice de la prochaine alarme du tableau								*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		Current : Indice de l'alarme courante								 			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		Index : Indice de la prochaine Alarme  							  			*/
/******************************************************************************/
UWORD16 AlarmTable::FindAlarmWithLast(void)
{
	UWORD16 Index = 0;
    UWORD16 i;

    for (i = 0; i < cMAX_ALARM; i++) {

        if ((TableAlarm[i].id != NO_ALARM) &&
            (TableAlarm[i].logtolast == TRUE)) {
                break;
            }
    }

    Index = i;

	/*%C if no alarm found return NO_ALARM else return the alarm's Index */
	if ((TableAlarm[Index].id == NO_ALARM) ||
        (TableAlarm[Index].logtolast == FALSE) ||
        (Index >= cMAX_ALARM )) {
		return (UWORD16)(NO_ALARM);
	}
	else {
		return Index;
	}
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Ajoute une alarme dans le tableau				   									*/
/*%C 																									*/
/*%I Input Parameter : 																			*/
/*%I 		Id : Id de l'alarme										              			*/
/*%I 		Action : Action de l'alarme									           		*/
/*%IO Input/Output : 																			*/
/*%IO 	NONE																					  	*/
/*%O Output Parameter : 																		*/
/*%O 		NONE																				  		*/
/******************************************************************************/

void AlarmTable::AddElement(AlarmEvent* Alarm, e_BOOL _LogToLast)
{
	UWORD16 Free ;

	/*%C Add an alarm in free space index */
	if(FindAlarm(Alarm->id) == NO_ALARM)
	{
		Free = FindFreeIndex();
		if(Free != NO_ALARM)
		{
			/*%C Set the alarm table */
			SetNbAlarm(GetNbAlarm()+1);
			SetAlarmEntry(Alarm, Free, _LogToLast);
			SetMaxAction(FindMaxAction());
            if (_LogToLast) {
                SetLastAlarm(Alarm);
            }
		}
	}
}
/******************************************************************************/
/*%C                       Functionnal description :                      	  */
/*%C                                                                          */
/*%C Ajoute une alarme dans le tableau en vérifiant qu'il y a de la place     */
/*%C pour une autre alarme juste après                                        */
/*%C 																		  */
/*%I Input Parameter : 														  */
/*%I 		Id : Id de l'alarme										          */
/*%I 		Action : Action de l'alarme									      */
/*%IO Input/Output : 														  */
/*%IO 	NONE																  */
/*%O Output Parameter : 													  */
/*%O 		NONE															  */
/******************************************************************************/

void AlarmTable::AddElement2(AlarmEvent* Alarm, e_BOOL _LogToLast)
{
	UWORD16 Free, FreeSecondTry ;

	/*%C Add an alarm in free space index */
	if(FindAlarm(Alarm->id) == NO_ALARM)
	{
		Free = FindFirstOfTwoFreeIndex();
		if(Free != NO_ALARM)
		{
			/*%C Set the alarm table */
			SetNbAlarm(GetNbAlarm()+1);
			SetAlarmEntry(Alarm, Free, _LogToLast);
            if (_LogToLast) {
                SetLastAlarm(Alarm);
            }
			SetMaxAction(FindMaxAction());
		}
		else
		{
			FreeSecondTry = FindFreeIndex();
			if(FreeSecondTry != NO_ALARM)
			{
				/*%C Set the alarm table */
				SetNbAlarm(GetNbAlarm()+1);
				SetAlarmEntry(Alarm, FreeSecondTry, _LogToLast);
                if (_LogToLast) {
                    SetLastAlarm(Alarm);
                }
				SetMaxAction(FindMaxAction());
			}
		}
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C 																									*/
/*%C Retourne l'indice de l'alarme passée en paramettre si elle existe	    	*/
/*%C 																									*/
/*%I Input Parameter : 																			*/
/*%I 		Id : Id de l'alarme										            			*/
/*%IO Input/Output : 																			*/
/*%IO  	NONE																					  	*/
/*%O Output Parameter : 																		*/
/*%O 		Indice de l'alarme, NO_ALARM sinon				  								*/
/******************************************************************************/
UWORD16 AlarmTable::FindAlarm(UWORD16 _Id)
{
   UWORD16 Find = (UWORD16)(NO_ALARM);

	/*%C Return the Alarm indice */
	for(UWORD16 i = 0; i<cMAX_ALARM; i++)
   {
		if(TableAlarm[i].id == _Id)
      {
			Find = i;
		}
	}
	return Find;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C 																									*/
/*%C Retourne l'indice d'un emplacement libre 											*/
/*%C 																									*/
/*%I Input Parameter : 																			*/
/*%I 		NONE	 																					*/
/*%IO Input/Output : 																			*/
/*%IO 	NONE																						*/
/*%O Output Parameter : 																		*/
/*%O 		Indice de l'emplacement libre, NO_ALARM sinon					      	*/
/******************************************************************************/
UWORD16 AlarmTable::FindFreeIndex()
{
	UWORD16 i = 0;

	/*%C Return the first free alarm index else return no free space */
	while((TableAlarm[i].id != NO_ALARM) && (i<cMAX_ALARM))
   {
		i++;
	}
	if(i != cMAX_ALARM)
   {
		return i;
	}
	else
   {
		return (UWORD16)(NO_ALARM);
	}
}
/******************************************************************************/
/*%C                       Functionnal description :                      	  */
/*%C 																		  */
/*%C Retourne l'indice du premier emplacement libre avec deux case contigues  */
/*%C 																		  */
/*%I Input Parameter : 														  */
/*%I 		NONE	 														  */
/*%IO Input/Output : 														  */
/*%IO 	NONE																  */
/*%O Output Parameter : 													  */
/*%O 		Indice de l'emplacement libre, NO_ALARM sinon					  */
/******************************************************************************/
UWORD16 AlarmTable::FindFirstOfTwoFreeIndex()
{
	UWORD16 i = 0;
	e_BOOL _found = FALSE;

	/*%C Return the first free alarm index else return no free space */
	while((i<cMAX_ALARM) && (!_found))
	{
		if ((TableAlarm[i%cMAX_ALARM].id == NO_ALARM) && (TableAlarm[(i+1)%cMAX_ALARM].id == NO_ALARM))
			_found = TRUE;
        else
            i++;
	}
	if ((i != cMAX_ALARM) && (_found))
	{
		return i;
	}
	else
    {
		return (UWORD16)(NO_ALARM);
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C																									*/
/*%C Efface une alarme dans le tableau 			   									*/
/*%C																									*/
/*%I Input Parameter :			 		 	 	                                    */
/*%I 		Id : Id de l'alarme a effacer									       		 	*/
/*%IO Input/Output : 																			*/
/*%IO 	NONE																						*/
/*%O Output Parameter : 																		*/
/*%O 		NONE																			     		*/
/******************************************************************************/
void AlarmTable::RemoveElement(AlarmEvent* Alarm, e_BOOL _LogToLast)
{
	UWORD16 Id = Alarm->id;
	UWORD16 indexAlarm = FindAlarm(Id);
    UWORD16 NextId = (UWORD16) NO_ALARM;

	/*%C Delete a alarm in table else return no alarm */
	if(indexAlarm != NO_ALARM)
   {
		SetNbAlarm(GetNbAlarm()-1);

		/*%C Stockage time and date */
		Alarm->id      = TableAlarm[indexAlarm].id;
		Alarm->action  = TableAlarm[indexAlarm].action;
		Alarm->day     = TableAlarm[indexAlarm].day;
		Alarm->month   = TableAlarm[indexAlarm].month;
		Alarm->year    = TableAlarm[indexAlarm].year;
		Alarm->hour    = TableAlarm[indexAlarm].hour;
		Alarm->min     = TableAlarm[indexAlarm].min;
        Alarm->logtolast = TableAlarm[indexAlarm].logtolast;

		/*%C delete */
		TableAlarm[indexAlarm].id = (UWORD16)(NO_ALARM);
		SetMaxAction(FindMaxAction());
   		TableAlarm[indexAlarm].logtolast = FALSE;

        /*%C Set Last Alarm */
        /* If the removed one is the current last one, then we have to switch */
        if ((_LogToLast == TRUE) && (Alarm->id == LastAlarm.id)) {
            NextId = FindAlarmWithLast();
            if (NextId != (UWORD16) NO_ALARM) {
                SetLastAlarm(&TableAlarm[NextId]);
            }
        }
	}
	else
   {
		Alarm->id = NO_ALARM;
		// NO_ALARM => Action WP
		Alarm->action  = 1;
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C																									*/
/*%C Efface toutes les alarmes dans le tableau											*/
/*%C																									*/
/*%I Input Parameter :			 		 	 	                                    */
/*%I 		NONE																		       		*/
/*%IO Input/Output : 																			*/
/*%IO 	NONE																						*/
/*%O Output Parameter : 																		*/
/*%O 		NONE																			     		*/
/******************************************************************************/
void AlarmTable::RemoveAll(void)
{
	/*%C delete all alarm events*/
	for(int i=0; i<cMAX_ALARM; i++)
   {
		TableAlarm[i].id = (UWORD16)(NO_ALARM);
        TableAlarm[i].logtolast = FALSE;
	}
	SetNbAlarm(0);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C																									*/
/*%C Retourne l'action la plus prioritaire des alarmes actives		 				*/
/*%C																									*/
/*%I Input Parameter :			 		 	 	                                    */
/*%I 		NONE																		       	  	*/
/*%IO Input/Output : 																			*/
/*%IO 	NONE																						*/
/*%O Output Parameter : 																		*/
/*%O 		Action la plus prioritaire											      		*/
/******************************************************************************/
UWORD16 AlarmTable::FindMaxAction()
{
	UWORD16 Max = 0;

	/*%C Search and return the high priority alarm */
	for(int i=0; i<cMAX_ALARM; i++)
   {
		if(TableAlarm[i].id != NO_ALARM)
      {
			if(TableAlarm[i].action > Max)
         {
				Max = TableAlarm[i].action;
			}
		}
	}
	return Max;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C																									*/
/*%C Demande d'affichage d'une alarme										 				*/
/*%C																									*/
/*%I Input Parameter :			 		 	 	                                    */
/*%I 		NONE																		      	 	*/
/*%IO Input/Output : 																			*/
/*%IO 	NONE																						*/
/*%O Output Parameter : 																		*/
/*%O 		NONE											      									*/
/******************************************************************************/
void AlarmTable::Refresh()
{
	/*%C Show alarm current index */ 
	if(NbAlarm != 0)
   {
		UWORD16 Index = FindNextAlarm(CurrentIndex);

		if(Index != NO_ALARM)
      {
			SetCurrentIndex(Index);
			Controller::GetInstance()->ShowAlarm(  TRUE,
																TableAlarm[Index].id,
                                                GetMaxAction());

		}
	}
}



