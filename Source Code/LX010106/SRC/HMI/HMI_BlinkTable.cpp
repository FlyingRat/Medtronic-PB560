/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_BlinkTable.cpp                                     			*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Gestion du blink						        											*/
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_BlinkTable.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                	   		*/
/******************************************************************************/


/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
BlinkTable::BlinkTable()
{
   BlinkState = FALSE;
   RemoveAll();
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/

/******************************************************************************/
/*                           METHODES                					      	   */
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Ajout d'un element																			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		Object : Element a ajouter															*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void BlinkTable::AddElement(DisplayObject *Object)
{
   int i = 0;

	/*%C Addition of an element */	
   while((Table[i] != NULL) && 
   		(Table[i] != Object) && 
   		(i<cMAX_BLINK))
   {
      i++;
   }
   if((i!=cMAX_BLINK) && (Table[i] != Object))
   {
      Table[i] = Object;
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement d'un element																  	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		Object : Element a effacer															*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void BlinkTable::RemoveElement(DisplayObject *Object)
{
   int i = 0;

	/*%C  Obliteration of an element */
   while((Table[i] != Object) && 
   		(i<cMAX_BLINK))
   {
      i++;
   }
   if(i!=cMAX_BLINK)
   {
      Table[i]->Blink(FALSE);
      Table[i] = NULL;
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement de tous les elements													  	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void BlinkTable::RemoveAll(void)
{
	 /*%C  Obliteration of all the elements */
   for(int i=0; i<cMAX_BLINK; i++)
   {
      Table[i] = NULL;
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Traitement du blink																	  	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void BlinkTable::Blink()
{
   BlinkState = (e_BOOL)!BlinkState;

   /*%C Treatment of the blink */
   for(int i = 0; i<cMAX_BLINK; i++)
   {
      if(Table[i] != NULL)
      {
         Table[i]->Blink(BlinkState);
      }
   }
}
