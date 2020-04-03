/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_ParameterSpy.cpp 	   	      			 	  		 			*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Spy de parametre														 					*/
/*		                                                                   	 	*/
/******************************************************************************/


/******************************************************************************/
/*                           HEADER INCLUDE FILE		                        */
/******************************************************************************/

#include "HMI_ParameterSpy.hpp"
				 
/******************************************************************************/
/*                           OTHER INCLUDE FILE		                	   		*/
/******************************************************************************/

#include "HMI_Controller.hpp"
#include "HMI_DataBaseAccess.hpp"

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
ParameterSpy::ParameterSpy()
{
   RemoveAll();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Ajoute un element dans le tableau													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		Id     : Id de l'element										            	*/
/*%I		Bd	 : Target BD de l'element								            		*/
/*%I		Value	 : valeur a detecter									            		*/
/*%I		Event	 : evenement a generer en cas de detection de la valeur 		 	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void ParameterSpy::AddElement(UWORD16 _Id,
                              e_TYPE_OF_DB_TARGET _Bd,
                              UWORD16 _Value,
                              EventId _Event)
{
	/*%C Look for free parameters */
   if(FindParam(_Id,_Bd,_Value) == NO_PARAM)
   {
      UWORD16 Free = FindFreeIndex();

      if(Free != NO_PARAM)
      {
			/* Set parameters in table */
         TableId[Free] = _Id;
         TableValue[Free] = _Value;
         TableBd[Free] = _Bd;
         TableEvent[Free] = _Event;
      }
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Retourne l'indice d'un element														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		Id     : Id de l'element										            	*/
/*%I		Bd	 : Target BD de l'element								            		*/
/*%I		Value	 : valeur a detecter									            		*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
UWORD16 ParameterSpy::FindParam( UWORD16 _Id,
                                 e_TYPE_OF_DB_TARGET _Bd,
                                 UWORD16 _Value)
{
   UWORD16 Find = NO_PARAM;

	/* Look for a parameter in table */
   for(UWORD16 i = 0; i<MAX_SPY; i++)
   {
      if((TableId[i] == _Id) &&
         (TableBd[i] == _Bd) &&
         (TableValue[i] == _Value))
      {
         /* Assign the parameter found */
         Find = i;
      }
   }
   return Find;
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Retourne l'indice d'un emplacement libre											*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		Indice de l'emplacement libre, NO_PARAM sinon		            		*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
UWORD16 ParameterSpy::FindFreeIndex()
{
   UWORD16 i = 0;
  
   /*%C Seek free parameter in the table  */
   while((TableId[i] != NO_PARAM) && (i<MAX_SPY))
   {
      i++;
   }
	/*%C Return the free parameter or no param */
   if(i != MAX_SPY)
   {
      return i;
   }
   else
   {
      return NO_PARAM;
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Effacement d'un element																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		Id : Id DB													               		*/
/*%I		Bd : Target BD												               		*/
/*%I		Value : Valeur a surveiller		            								*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void ParameterSpy::RemoveElement(UWORD16 _Id,
                                 e_TYPE_OF_DB_TARGET _Bd,
                                 UWORD16 _Value)
{
   UWORD16 indexAlarm = FindParam(_Id,_Bd,_Value);

   /*%C Erase parameter */
   if(indexAlarm != NO_PARAM)
   {
      TableId[indexAlarm] = NO_PARAM;
      TableEventOk[indexAlarm] = FALSE;
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Effacement de tous les elements														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE															               		*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void ParameterSpy::RemoveAll(void)
{
	/*%C Erase all parameters */
   for(UWORD16 i=0; i<MAX_SPY; i++)
   {
      TableId[i] = NO_PARAM;
      TableEventOk[i] = FALSE;
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Lancement d'un spy																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE															               		*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void ParameterSpy::Refresh()
{
   UWORD16 Value;

   for(UWORD16 i = 0; i<MAX_SPY; i++)
   {
      if(TableId[i] != NO_PARAM)
      {
         DataBaseAccess::ReadValue(&Value,TableId[i],TableBd[i]);
         if(Value == TableValue[i])
         {
            if(!TableEventOk[i])
            {
               Controller::GetInstance()->ManageSpyEvent(TableEvent[i]);
               TableEventOk[i] = TRUE;
            }
         }
         else
         {
            TableEventOk[i] = FALSE;
         }
      }
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Reset de la table de detection des elements										*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE															               		*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void ParameterSpy::Reset()
{
   for(UWORD16 i = 0; i<MAX_SPY; i++)
   {
      TableEventOk[i] = FALSE;
   }
}
