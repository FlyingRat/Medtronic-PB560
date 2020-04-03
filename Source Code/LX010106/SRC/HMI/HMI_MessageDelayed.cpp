/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
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
/*%C Objet gérant l'affichage temporisé grâce à un timer			 					*/
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
/*%I		_TimerPtr   : Pointeur sur l'objet VTimer qui gère les timers 			*/
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

   /* Vérification de l'initialisation */
   if(   (GetMessDiagPtr()) &&
         (GetTimerPtr()) )
         SetConfigured(TRUE);         
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
///*%C                                                                          */
/*%C Handler qui doit être appelé par le controller sur expiration du timer   */
/*%C identifié par son Id                                                     */      
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		_DisplayFlag : indique si l'affichage doit etre effectué ou pas      */
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
      /* Tant que le curseur de lecture n'a pas rattrapé le curseur d'écriture,
         on traite les messages*/
      if(WriteIndex != ReadIndex)
      {
         TimerPtr->StopTimer(TimerId);      
         DisplayMessageFromQueue(_DisplayFlag);
	      TimerPtr->StartTimer(MessageFifo[ReadIndex].Delay, TimerId, FALSE);         
      }
      else
      {
         /* Plus de messages à afficher dans la fifo ! */
         TimerPtr->StopTimer(TimerId);
      }            
   }
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Ajoute un message dans la fifo d'affchage qui sera traitée par le Handler*/
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

  	 	   	/* C'est le premier élément, on affiche le message et on lance le timer */
		   	if(empty)
		   	{
            	DisplayMessageFromQueue(_DisplayFlag);
			   	TimerPtr->StartTimer(   MessageFifo[ReadIndex].Delay,
			 	       					TimerId,
			 				         	FALSE);
		   	}

		   	/* Mise à jour de l'index d'écriture */
         	WriteIndex = (WriteIndex+1)%MAX_FIFO;
      	}
      	else
         	/* le curseur d'écriture a rattrapé le curseur de lecture, on ne peut
         	donc plus insérer de message dans la fifo ! */
         	rc = 2;
   		}
   		else
      		/* l'objet n'est pas bien configuré ou message est NULL, on n'autorise pas l'ajout d'élément*/
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
