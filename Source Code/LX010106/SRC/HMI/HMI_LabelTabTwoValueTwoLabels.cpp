/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelTabTwoValueTwoLabels.cpp           	 	  					*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage	(icon + text + text + value + Value) 						*/
/*		                                                                   	 	*/
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_LabelTabTwoValueTwoLabels.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_Tools.hpp"
#include "HMI_DataBaseAccess.hpp"

extern "C"
{
#include "stdfile.h"
}

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
LabelTabTwoValueTwoLabels::LabelTabTwoValueTwoLabels():LabelTabTwoValue()
{
   ColOffset = 0;
   LineOffset = 0;   
}
/******************************************************************************/
/*                           ACCESSEURS				                				*/
/******************************************************************************/
void LabelTabTwoValueTwoLabels::SetLabel2ColOffset(UWORD16 _ColOffset)
{
   UWORD16 _PreviousCol;
   UWORD16 _NewCol;
   _PreviousCol = FLabel2.GetCol();

   if(_PreviousCol >= ColOffset)
      _NewCol = _PreviousCol - ColOffset;
   else
      _NewCol = 0;

   _NewCol += _ColOffset;
   ColOffset = _ColOffset;
   FLabel2.SetCol(_NewCol);
}
/*----------------------------------------------------------------------------*/
void LabelTabTwoValueTwoLabels::SetLabel2LineOffset(UWORD16 _LineOffset)
{
   UWORD16 _PreviousLine;
   UWORD16 _NewLine;
   _PreviousLine = FLabel2.GetLine();

   if(_PreviousLine >= LineOffset)
      _NewLine = _PreviousLine - LineOffset;
   else
      _NewLine = 0;

   _NewLine += _LineOffset;
   LineOffset = _LineOffset;
   FLabel2.SetLine(_NewLine);
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelTabTwoValueTwoLabels::GetLabel2ColOffset(void)
{
   return(ColOffset);
}
/*----------------------------------------------------------------------------*/
UWORD16 LabelTabTwoValueTwoLabels::GetLabel2LineOffset(void)
{
   return(LineOffset);
}
/*----------------------------------------------------------------------------*/
void LabelTabTwoValueTwoLabels::SetLine(UWORD16 Line)
{
   UWORD16 _Label2LineOffset = GetLabel2LineOffset();
   SetLabel2LineOffset(0);
   LabelTabTwoValue::SetLine(Line);
   FLabel2.SetLine(Line);
   SetLabel2LineOffset(_Label2LineOffset);
}
/*----------------------------------------------------------------------------*/
void LabelTabTwoValueTwoLabels::SetCol(UWORD16 Col)
{
   UWORD16 _Label2ColOffset = GetLabel2ColOffset();
   SetLabel2ColOffset(0);
   LabelTabTwoValue::SetCol(Col);
   FLabel2.SetCol(Col);
   SetLabel2ColOffset(_Label2ColOffset);
}
/*----------------------------------------------------------------------------*/
void LabelTabTwoValueTwoLabels::SetNameLabel2(UBYTE** _Name)
{
   FLabel2.SetName(_Name);
}
/*----------------------------------------------------------------------------*/
UBYTE* LabelTabTwoValueTwoLabels::GetNameLabel2()
{
   return(FLabel2.GetName());
}
/******************************************************************************/
/*                           METHODES                									*/
/******************************************************************************/
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation																				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		Icon   : icone												               		*/
/*%I		Name   : Pointeur sur le tableau de nom						         	*/
/*%I		Name2   : Pointeur sur le tableau de nom pour le 2ième label         	*/
/*%I		Line   : ligne 												               	*/
/*%I		Col    : colonne												         			*/
/*%I		Value1  : Valeur 1											     		         */
/*%I		ValueRefresh : Valeur pour le champ de refresh			  		        	*/
/*%I		Value2  : Valeur 2																	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabTwoValueTwoLabels::Init(	e_SYMBOL _Icon,
										         UBYTE **_Name,
										         UBYTE **_Name2,
         										UWORD16 _Line,
			         							UWORD16 _Col,
                                  		UWORD16 _Value1,
                                	   	UWORD16 _ValueRefresh,
                                  		UWORD16 _Value2)
{
	LabelTabTwoValue::Init(_Icon, _Name, _Line, _Col, _Value1, _ValueRefresh, _Value2);
   FLabel2.SetParent(GetParent());
   FLabel2.Init(NO,_Name2,_Line,_Col);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage	de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																		  		    	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabTwoValueTwoLabels::Show()
{
   LabelTabTwoValue::Show();
   FLabel2.Show();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																		  		    	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelTabTwoValueTwoLabels::Hide()
{
   FLabel2.Hide();
   LabelTabTwoValue::Hide();      
}
