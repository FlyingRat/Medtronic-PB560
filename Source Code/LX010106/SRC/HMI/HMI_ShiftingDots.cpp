/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_ShiftingDots.cpp		  		                             	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage	d'un chenillard											      */
/*		                                                                        */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_ShiftingDots.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/
#define SPACING 9
/******************************************************************************/
/*                        VARIABLE DECLARATION		              		   		*/
/******************************************************************************/
/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
ShiftingDots::ShiftingDots():DisplayObject()
{
   UWORD16 i;
   Current = 0;
   SetVertical(FALSE);

   for(i=0; i<MAX_SYMBOLS; i++)
   {
      Symbols[i].SetParent(this);
   }
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
/*----------------------------------------------------------------------------*/
void ShiftingDots::SetPreviousSymbol(e_SYMBOL _PreviousSymbol, UWORD16 _Index)
{
   if(_Index < MAX_SYMBOLS)
      PreviousSymbols[_Index] = _PreviousSymbol;
}
/*----------------------------------------------------------------------------*/
e_SYMBOL ShiftingDots::GetPreviousSymbol(UWORD16 _Index)
{
   if(_Index < MAX_SYMBOLS)
      return (PreviousSymbols[_Index]);
   return(PreviousSymbols[0]);
}
/*----------------------------------------------------------------------------*/
void ShiftingDots::ChangeSymbol(UWORD16 _Index)
{
   e_SYMBOL _Symbol;

   if(_Index < MAX_SYMBOLS)
   {
      /* Récupération du symbole précédent */
      _Symbol = Symbols[_Index].GetSymbol();

      /* Mise à jour du symbole */
      Symbols[_Index].SetSymbol(GetPreviousSymbol(_Index));

      /* Sauvegarde du symbole précédent */
      SetPreviousSymbol(_Symbol, _Index);
   }
}
/*----------------------------------------------------------------------------*/
void ShiftingDots::SetVertical(e_BOOL _Vertical)
{
   Vertical = _Vertical;
}
/*----------------------------------------------------------------------------*/
e_BOOL ShiftingDots::IsVertical()
{
   return(Vertical);
}
/******************************************************************************/
/*                           METHODES                					      		*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation																				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		 : icone												               		*/
/*%I		Name : Pointeur sur le tableau de nom						         		*/
/*%I		Line : ligne 												               		*/
/*%I		Col : colonne												            			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void ShiftingDots::Init(   e_SYMBOL _FirstSymbol,
                           e_SYMBOL _SecondSymbol,
                           e_BOOL _Vertical,
                           UWORD16 _Line,
                           UWORD16 _Col)
{
   UWORD16 i;
   
   SetVertical(_Vertical);

   for(i=0; i<MAX_SYMBOLS; i++)
   {
      if(i==0)
      {
         PreviousSymbols[i] = _FirstSymbol;
         Symbols[i].SetSymbol(_SecondSymbol);
      }
      else
      {
         PreviousSymbols[i] = _SecondSymbol;
         Symbols[i].SetSymbol(_FirstSymbol);
      }
      if(IsVertical() == TRUE)
      {
         Symbols[i].SetLine(_Line + i*SPACING);
         Symbols[i].SetCol(_Col);
      }
      else
      {
         Symbols[i].SetLine(_Line);
         Symbols[i].SetCol(_Col + i*SPACING);
      }

   }

   Current = 0;
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage	de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE														               			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void ShiftingDots::Show()
{
   UWORD16 i;

   DisplayObject::Show();

   for(i=0; i<MAX_SYMBOLS; i++)
   {
      Symbols[i].Show();
   }
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement de l'Objet	 																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE														               			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void ShiftingDots::Hide()
{
   UWORD16 i;

   for(i=0; i<MAX_SYMBOLS; i++)
   {
      Symbols[i].Hide();
   }
   DisplayObject::Hide();
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Animation de l'Objet	 																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE														               			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void ShiftingDots::Animate()
{

   ChangeSymbol(Current);

   /* Même traitement pour le symbole suivant */
   Current = (Current+1)%MAX_SYMBOLS;

   ChangeSymbol(Current);
}

