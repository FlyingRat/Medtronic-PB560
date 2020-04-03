/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_MessageList.cpp     	      			 	  						*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Classe gérant une liste de messages                                      */
/*		                                                                   	 	*/
/******************************************************************************/


/******************************************************************************/
/*                           HEADER INCLUDE FILE		                        */
/******************************************************************************/
#ifdef _BORLAND
   #include <vcl.h>
#endif

#include "HMI_MessageList.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                	   		*/
/******************************************************************************/

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
MessageList::MessageList()
{
   
}
/******************************************************************************/
/*                           ACCESSEURS				                    			*/
/******************************************************************************/
#ifdef HMI_MESSAGE_LIST_CFG_FAST
   #define FAST_IS_INLIST(X) ((e_BOOL) (InListTable[(X/8)%MESSAGE_LIST_IN_LIST_TABLE_SIZE] &  (0x01 << (X%8))))
   #define FAST_SET_INLIST(X) (InListTable[(X/8)%MESSAGE_LIST_IN_LIST_TABLE_SIZE] |= (0x01 << (X%8)))
   #define FAST_UNSET_INLIST(X) (InListTable[(X/8)%MESSAGE_LIST_IN_LIST_TABLE_SIZE] &= ~(0x01 << (X%8)))
#else
e_BOOL MessageList::FAST_IS_INLIST(UWORD16 X)
{
   e_BOOL rc = (e_BOOL) (InListTable[(X/8)%MESSAGE_LIST_IN_LIST_TABLE_SIZE] &  (0x01 << (X%8)));
   return (rc);
}
void MessageList::FAST_SET_INLIST(UWORD16 X)
{
   InListTable[(X/8)%MESSAGE_LIST_IN_LIST_TABLE_SIZE] |= (0x01 << (X%8));
}
void MessageList::FAST_UNSET_INLIST(UWORD16 X)
{
   InListTable[(X/8)%MESSAGE_LIST_IN_LIST_TABLE_SIZE] &= ~(0x01 << (X%8));
}

#endif
/******************************************************************************/
/*                           METHODES                					      		*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation de l'objet                  										*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		_MaxId : Le range d'Ids que peut gérer la message list  va de 0 à    */
/*%I              _MaxId	                                                   */
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void MessageList::Init(UWORD16 _MaxId)
{
   UWORD16 i;
   for(i=0; i<MESSAGE_LIST_SIZE; i++)
   {
      ClearEntry(i);
   }
   if(_MaxId > MESSAGE_LIST_NB_ITEMS)
   {
      /* Problème ! liste trop petite ! */
      #ifdef _BORLAND
         ShowMessage("Problème dans HMI_MessageList.cpp, Init(...) : Liste trop petite ! ");
      #endif
   }
   else
   {
      for(i=0; i<MESSAGE_LIST_IN_LIST_TABLE_SIZE; i++)
      {
         InListTable[i] = 0;
      }         
   }
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Ajout d'un message dans la listeà un index de ligne particulier  			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		_Id : Paramètre libre d'utilisation	permettant d'identifier de       */
/*%I		      manière unique le message (clé)  										*/
/*%I		_Line : Numéro de ligne du message                                   */
/*%I		_Message : Message à ajouter                                         */
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		Code d'erreur (cf. HMI_MessageList.hpp pour la liste)                */
/******************************************************************************/
SWORD16  MessageList::AddToList(  UWORD16 _Id, UWORD16 _Line, UBYTE* _Message)
{
   SWORD16 rc = E_NO;
   UWORD16 index;

   if(E_OK == InList(_Id))
      rc = GetIndexFromId(_Id, &index);
   else
      rc = FindFreeIndex(&index);
      
   if(rc == E_OK)
   {
      if(_Line < cMAX_LINE)
      {
         FAST_SET_INLIST(_Id);
         Messages[index].Id = _Id;
         Tools::StrCpy(Messages[index].Text[_Line], _Message);
         Messages[index].Used = TRUE;
      }
      else
         rc = E_NO;
   }
   return(rc);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Récupération d'une ligne à partir d'un _Id (clé unique) et d'un numéro de*/
/*%C ligne _Line                                                              */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		_Id : Paramètre libre d'utilisation	permettant d'identifier de       */
/*%I		      manière unique le message													*/
/*%I     _Line : numéro de ligne                                              */
/*%IO Input/Output : 																			*/
/*%IO		_text : texte de la ligne     												  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		Code d'erreur (cf. HMI_MessageList.hpp pour la liste)                */
/******************************************************************************/
SWORD16  MessageList::GetTextLineFromId(UWORD16 _Id, UWORD16 _Line, UBYTE** _Text)
{
   SWORD16 rc = E_NO;
   UWORD16 index;

   rc = GetIndexFromId(_Id, &index);
   if(rc == E_OK)
   {
      if(_Line < cMAX_LINE)
         *_Text = Messages[index].Text[_Line];
      else
         rc = E_OUT_OF_BOUNDS;         
   }
   return(rc);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Suppression d'un message dans la liste à partir de son Id (clé unique)   */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		_Id : Paramètre libre d'utilisation	permettant d'identifier de       */
/*%I		      manière unique le message													*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		Code d'erreur (cf. HMI_MessageList.hpp pour la liste)                */
/******************************************************************************/
SWORD16  MessageList::RemoveFromList(UWORD16 _Id)
{
   SWORD16 rc = E_NO;
   UWORD16 index;

   if(FAST_IS_INLIST(_Id))
   {
      FAST_UNSET_INLIST(_Id);
      rc = GetIndexFromId(_Id, &index);
      if(rc == E_OK)
      {
         ClearEntry(index);
      }
   }
   return(rc);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Suppression de la totalilté du contenu de la liste                       */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																					  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		Code d'erreur (cf. HMI_MessageList.hpp pour la liste)                */
/******************************************************************************/
SWORD16  MessageList::EmptyList(void)
{
   SWORD16 rc = E_OK;
   UWORD16 i;

   for(i=0; i<MESSAGE_LIST_SIZE; i++)
   {
      ClearEntry(i);
   }
   
   for(i=0; i<MESSAGE_LIST_IN_LIST_TABLE_SIZE; i++)
   {
         InListTable[i] = 0;
   }

   return(rc);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Clear du contenu d'une entrée dans l'index de la message list            */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		_Index : Index dans la message list                                  */
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE                                                                 */
/******************************************************************************/
void MessageList::ClearEntry(UWORD16 _Index)
{

   if(_Index < MESSAGE_LIST_SIZE)
   {
      Messages[_Index].Used = FALSE;
      Messages[_Index].Id = 0;
   }
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Permet de savoir si un message est présent dans la liste                 */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		_Id : Paramètre libre d'utilisation	permettant d'identifier de       */
/*%I		      manière unique le message (clé)  										*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		Code d'erreur (cf. HMI_MessageList.hpp pour la liste)                */
/******************************************************************************/
SWORD16  MessageList::InList( UWORD16 _Id)
{
   SWORD16 rc;
/*   UWORD16 i; */

   if(FAST_IS_INLIST(_Id))
      rc = E_OK;
   else
      rc = E_NO;

   return(rc);      
/* méthode plus rapide ci-dessus

   for(i=0; i<MESSAGE_LIST_SIZE; i++)
   {
      if((Messages[i].Used == TRUE) && (Messages[i].Id == _Id))
      {
         rc = E_OK;
         break;
      }
   }
   return(rc);
*/
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Trouve le premier index libre dans la liste                              */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE                                                                 */
/*%IO Input/Output : 																			*/
/*%IO		_Index : premier index libre trouvé											  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		Code d'erreur (cf. HMI_MessageList.hpp pour la liste)                */
/******************************************************************************/
SWORD16  MessageList::FindFreeIndex(UWORD16* _Index)
{
   SWORD16 rc = E_NO;
   UWORD16 i;

   for(i=0; i<MESSAGE_LIST_SIZE; i++)
   {
      if(Messages[i].Used == FALSE)
      {
         rc = E_OK;
         *_Index = i;
         break;
      }
   }
   return(rc);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Récupère l'index du message dans la liste à partir de l'Id (clé unique)  */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		_Id : Paramètre libre d'utilisation	permettant d'identifier de       */
/*%I		      manière unique le message (clé)  										*/
/*%IO Input/Output : 																			*/
/*%IO		_Index : index dans la liste de messages										*/
/*%O Output Parameter : 																	 	*/
/*%O 		Code d'erreur (cf. HMI_MessageList.hpp pour la liste)                */
/******************************************************************************/
SWORD16  MessageList::GetIndexFromId(UWORD16 _Id, UWORD16* _Index)
{
   SWORD16 rc = E_NO;
   UWORD16 i;

   for(i=0; i<MESSAGE_LIST_SIZE; i++)
   {
      if((Messages[i].Used == TRUE) && (Messages[i].Id == _Id))
      {
         rc = E_OK;
         *_Index = i;
         break;
      }
   }
   return(rc);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Récupère l'index du message dans la liste à partir de l'Id (clé unique)  */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE                                                                 */
/*%IO Input/Output : 																			*/
/*%IO		NONE                                                                 */
/*%O Output Parameter : 																	 	*/
/*%O 		TRUE si liste pleine; FALSE sinon                                    */
/******************************************************************************/
e_BOOL MessageList::IsListFull(void)
{
   UWORD16 _Index;
   SWORD16 rc;
   rc = FindFreeIndex(&_Index);
   _Index = _Index; /* To avoid warning */
   return((e_BOOL)(rc != E_OK));
}

