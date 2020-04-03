/******************************************************************************/
/*                                                                            */
/* Project N�  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_MessageDelayed.cpp     	      			 	  						*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet g�rant l'affichage temporis� gr�ce � un timer			 					*/
/*		                                                                   	 	*/
/******************************************************************************/


/******************************************************************************/
/*                           HEADER INCLUDE FILE		                        */
/******************************************************************************/

#include "HMI_MessageDelayed.hpp"
				 
/******************************************************************************/
/*                           OTHER INCLUDE FILE		                	   		*/
/******************************************************************************/
#include "HMI_InterfaceCppC.hpp"
/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
MessageDelayed::MessageDelayed()
{
   SetMessDiagPtr(NULL);
   SetTimerPtr(NULL);
   SetTimerLoad(0);
   SetTimerId(0);
   ResetFifo();   
   SetConfigured(FALSE);   
}

/******************************************************************************/
/*                           ACCESSEURS				                    			*/
/******************************************************************************/
void MessageDelayed::SetMessDiagPtr(MessageDialog* _MessDiagPtr)
{
   MessDiagPtr = _MessDiagPtr;
}
/*----------------------------------------------------------------------------*/
MessageDialog* MessageDelayed::GetMessDiagPtr()
{
   return(MessDiagPtr);
}
/*----------------------------------------------------------------------------*/
void MessageDelayed::SetTimerPtr(VTimer* _TimerPtr)
{
   TimerPtr = _TimerPtr;
}
/*----------------------------------------------------------------------------*/
VTimer* MessageDelayed::GetTimerPtr()
{
   return(TimerPtr);
}
/*----------------------------------------------------------------------------*/
void MessageDelayed::SetTimerLoad(UWORD32 _TimerLoad)
{
   TimerLoad = _TimerLoad;
}
/*----------------------------------------------------------------------------*/
UWORD32 MessageDelayed::GetTimerLoad()
{
   return(TimerLoad);
}
/*----------------------------------------------------------------------------*/
void MessageDelayed::SetTimerId(UWORD16 _TimerId)
{
   TimerId = _TimerId;
}
/*----------------------------------------------------------------------------*/
UWORD16 MessageDelayed::GetTimerId()
{
   return(TimerId);
}
/*----------------------------------------------------------------------------*/
void MessageDelayed::SetConfigured(e_BOOL _Configured)
{
   Configured = _Configured;
}
/*----------------------------------------------------------------------------*/
e_BOOL MessageDelayed::GetConfigured()
{
   return(Configured);
}
/*----------------------------------------------------------------------------*/
void MessageDelayed::ResetFifo()
{
   ReadIndex = 0;
   WriteIndex = 0;
}
/******************************************************************************/
/*                           METHODES                					      		*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation de l'objet                  										*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		_TimerPtr   : Pointeur sur l'objet VTimer qui g�re les timers 			*/
/*%I		_MessaDiagPtr : Pointeur vers l'objet MessageDialog d'affichage		*/
/*%I		_TimerLoad : Load du timer                                           */
/*%I		_TimedId : L'Id du timer                                       		*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MessageDelayed::Init( VTimer* _TimerPtr,
                           MessageDialog* _MessaDiagPtr,
                           UWORD16 _TimedId)
{
   /* Initialisation de l'objet */
   SetMessDiagPtr(_MessaDiagPtr);
   SetTimerPtr(_TimerPtr);
   SetTimerId(_TimedId);
   ResetFifo();

   /* V�rification de l'initialisation */
   if(   (GetMessDiagPtr()) &&
         (GetTimerPtr()) )
         SetConfigured(TRUE);         
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
///*%C                                                                          */
/*%C Handler qui doit �tre appel� par le controller sur expiration du timer   */
/*%C identifi� par son Id                                                     */      
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		_DisplayFlag : indique si l'affichage doit etre effectu� ou pas      */
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MessageDelayed::TimerHandler(e_BOOL _DisplayFlag)
{
   
   if(GetConfigured())
   {
	   ReadIndex = (ReadIndex+1)%MAX_FIFO;
      /* Tant que le curseur de lecture n'a pas rattrap� le curseur d'�criture,
         on traite les messages*/
      if(WriteIndex != ReadIndex)
      {
         TimerPtr->StopTimer(TimerId);      
         DisplayMessageFromQueue(_DisplayFlag);
	      TimerPtr->StartTimer(MessageFifo[ReadIndex].Delay, TimerId, FALSE);         
      }
      else
      {
         /* Plus de messages � afficher dans la fifo ! */
         TimerPtr->StopTimer(TimerId);
      }            
   }
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Ajoute un message dans la fifo d'affchage qui sera trait�e par le Handler*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE                                                                 */
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
UWORD16 MessageDelayed::AddMessageToQueue(	UBYTE* _Message, 
											UWORD32 _Delay,	
											e_BOOL _DisplayFlag)
{
   UWORD16 rc = 0;
   e_BOOL empty;

   if(GetConfigured())
   {
	  if (_Message != NULL)
	  {
      	if (ReadIndex == WriteIndex)
		 	empty = TRUE;
	  	else
			empty = FALSE;

      	if((WriteIndex+1)%MAX_FIFO != ReadIndex)
      	{
         	MessageFifo[WriteIndex].Body = _Message;
		   	MessageFifo[WriteIndex].Delay = _Delay;

  	 	   	/* C'est le premier �l�ment, on affiche le message et on lance le timer */
		   	if(empty)
		   	{
            	DisplayMessageFromQueue(_DisplayFlag);
			   	TimerPtr->StartTimer(   MessageFifo[ReadIndex].Delay,
			 	       					TimerId,
			 				         	FALSE);
		   	}

		   	/* Mise � jour de l'index d'�criture */
         	WriteIndex = (WriteIndex+1)%MAX_FIFO;
      	}
      	else
         	/* le curseur d'�criture a rattrap� le curseur de lecture, on ne peut
         	donc plus ins�rer de message dans la fifo ! */
         	rc = 2;
   		}
   		else
      		/* l'objet n'est pas bien configur� ou message est NULL, on n'autorise pas l'ajout d'�l�ment*/
      		rc = 1;
	}

   return(rc);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affiche le message courant de la fifo                                    */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		_DisplayFlag : flag d'affichage                                      */
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MessageDelayed::DisplayMessageFromQueue(e_BOOL _DisplayFlag)
{
	e_BOOL _IsVisible = MessDiagPtr->IsVisible();

    MessDiagPtr->SetVisible(_DisplayFlag);

    if(_DisplayFlag)
    {
#if 0
      /* Ne fonctionne par sur cible, on efface donc brutalement avec le EraseZone */
    	MessDiagPtr->Hide();
#else
      InterfaceCppC::EraseZone(  MessDiagPtr->GetLine() + 2,
   									   MessDiagPtr->GetCol()+ 2,
                                 MessDiagPtr->GetLineLine2(),
                                 MessDiagPtr->GetWidth() - 4,
                                 1,
                                 MessDiagPtr->GetPage());

#endif
    }

    MessDiagPtr->SetMessage(MessageFifo[ReadIndex].Body, NO);

    if(_DisplayFlag)
    	MessDiagPtr->Refresh();
            
	MessDiagPtr->SetVisible(_IsVisible);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Renvoie le nombre des messages dans la queue de messages                 */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE                                                                 */
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
UWORD16 MessageDelayed::GetNbOfMessagesInQueue()
{
   UWORD16 _number = 0;
   
   if(WriteIndex >= ReadIndex)
      _number = WriteIndex - ReadIndex;
   else
      _number = MAX_FIFO - (ReadIndex - WriteIndex);

   return(_number);
}
