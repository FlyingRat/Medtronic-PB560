/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelStringTwoItems.cpp  	    	           	 	  				*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage (icon + text + String) avec 2 valeurs possibles			*/
/*		                                                                   	 	*/
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_LabelStringTwoItems.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/



/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
LabelStringTwoItems::LabelStringTwoItems():LabelValueString()
{
   Item1Name = NULL;
   Item2Name = NULL;   
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void LabelStringTwoItems::SetItem1Name(UBYTE** _Item1Name)
{
   Item1Name = _Item1Name;
   SetValue1(GetValue1Name());
}
/*----------------------------------------------------------------------------*/
UBYTE* LabelStringTwoItems::GetItem1Name()
{
   if(Item1Name != NULL)
   {
      return (Item1Name[GetLanguage()]);
   }
   else
	{
      return (UBYTE *)"???";
	}
}
/*----------------------------------------------------------------------------*/
void LabelStringTwoItems::SetItem2Name(UBYTE** _Item2Name)
{
   Item2Name = _Item2Name;
   SetValue1(GetValue1Name());
}
/*----------------------------------------------------------------------------*/
UBYTE* LabelStringTwoItems::GetItem2Name()
{
   if(Item2Name != NULL)
   {
      return (Item2Name[GetLanguage()]);
   }
   else
	{
      return (UBYTE *)"???";
	}
}
/*----------------------------------------------------------------------------*/
UBYTE* LabelStringTwoItems::GetValue1Name()
{
   UWORD16 Value = GetIntValue1();

   switch(Value)
   {
      case 0  : return GetItem1Name();
      case 1  : return GetItem2Name();
      default : return (UBYTE *)"???";
   }
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
e_BOOL LabelStringTwoItems::IncreaseValueOk(UWORD16* _Val)
{
   /*%C Increment authorization */
   if(GetIdParam() != NO_ID)
   {
      return LabelValueString::IncreaseValueOk(_Val);
   }
   else
   {
      if(*_Val == 0)
      {
         (*_Val) +=1;
			return TRUE;
      }
      else
      {
         (*_Val) -=1;
			return TRUE;
      }
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
e_BOOL LabelStringTwoItems::DecreaseValueOk(UWORD16* _Val)
{
	/*%C Decrement authorization */
   if(GetIdParam() != NO_ID)
   {
      return LabelValueString::DecreaseValueOk(_Val);
   }
   else
   {
      if(*_Val == 0)
      {
         (*_Val) +=1;
         return TRUE;
      }
      else
      {
         (*_Val) -=1;
         return TRUE;
      }
   }
}

