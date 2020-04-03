/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelStringNItems.cpp  	    	           	 	  				*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage (icon + text + String) avec N valeurs possibles			*/
/*		                                                                   	 	*/
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_LabelStringNItems.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/



/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
LabelStringNItems::LabelStringNItems():LabelValueString()
{
   UWORD16 i;
   for(i=0; i<MAX_ITEMS; i++)
      ItemNames[i] = NULL;

}
/*----------------------------------------------------------------------------*/
LabelStringNItems::LabelStringNItems(UWORD16 _Size):LabelValueString()
{
     LabelStringNItems();
     SetSize( _Size);
}
/*----------------------------------------------------------------------------*/
void LabelStringNItems::SetSize(UWORD16 _Size)
{
   if((_Size>0)&&(_Size<MAX_ITEMS))
      Size = _Size;
   else
      Size = 0;
}
/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void LabelStringNItems::SetItem(UWORD16 _Rank, UBYTE** _Item)
{
   if(_Rank < Size)
   {
      ItemNames[_Rank] = _Item;
      CurrentRank = _Rank;
   }
}
/*----------------------------------------------------------------------------*/
UBYTE** LabelStringNItems::GetItem(UWORD16 _Rank)
{
   if((_Rank < Size) && (ItemNames[_Rank] != NULL))
   {
      return (ItemNames[_Rank]);
   }
   else
	{
      return NULL;
	}
}
/*----------------------------------------------------------------------------*/
UBYTE* LabelStringNItems::GetItemName(UWORD16 Rank)
{
   if((Rank < Size) && (ItemNames[Rank] != NULL))
   {
      return (ItemNames[Rank][GetLanguage()]);
   }
   else
	{
      return (UBYTE*) "???";
	}
}
/*----------------------------------------------------------------------------*/
UBYTE* LabelStringNItems::GetValue1Name()
{
   UWORD16 _rank = GetIntValue1();

   if(_rank < Size)
   {
      return GetItemName(_rank);
   }
   else
      return (UBYTE *)"???";
}

/******************************************************************************/
/*                           METHODES                					      		*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Autorisation d'increment																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	Val : valeur a incrementer												        	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		TRUE si increment autorisé	  														*/
/******************************************************************************/
e_BOOL LabelStringNItems::IncreaseValueOk(UWORD16* _Val)
{
   /*%C Increment authorization */
   if(GetIdParam() != NO_ID)
   {
      return LabelValueString::IncreaseValueOk(_Val);
   }
   else
   {
      if(*_Val < Size)
      {
         (*_Val) +=1;
      }
      else
      {
         (*_Val) = 0;
      }
		return TRUE;
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Autorisation de decrement																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	Val : valeur a decrementer												        	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		TRUE si decrement autorisé	  														*/
/******************************************************************************/
e_BOOL LabelStringNItems::DecreaseValueOk(UWORD16* _Val)
{
	/*%C Decrement authorization */
   if(GetIdParam() != NO_ID)
   {
      return LabelValueString::DecreaseValueOk(_Val);
   }
   else
   {
      if(*_Val > 0)
      {
         (*_Val) -=1;
      }
      else
      {
         (*_Val) = Size;
      }
		return TRUE;
   }
}

