/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_DisplayObject.cpp                                   			*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage																	      */
/*		                                                                        */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_DisplayObject.hpp"

#define DISP_VISIBLE 0x01
#define DISP_FORCED_VISIBLE 0x02
/******************************************************************************/
/*                           OTHER INCLUDE FILE		                	   	   */
/******************************************************************************/

UWORD16 DisplayObject::Language = 0;
e_BOOL DisplayObject::EndOfInit = FALSE;
char DisplayObject::StringValue1[DISP_OBJ_MAX_CHAR];
char DisplayObject::StringValue2[DISP_OBJ_MAX_CHAR];

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR      						   */
/******************************************************************************/
DisplayObject::DisplayObject()
{
   Line = 0;
   Col = 0;
   Page = 1;

   SetVisible(FALSE);   
   SetForcedVisible(TRUE);   
   
   RefreshEnable(TRUE);
   
   Parent = NULL;
   
   SetEndOfInit(FALSE);
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
UWORD16 DisplayObject::GetLine()
{
   return Line;
}
/*----------------------------------------------------------------------------*/
void DisplayObject::SetLine(UWORD16 _Line)
{
	if	(IsVisible() && 
		(_Line != Line))
   {
		Hide();
      Line = _Line;
		Show();
   }
	else
   {
      Line = _Line;
	}
}
/*----------------------------------------------------------------------------*/
UWORD16 DisplayObject::GetCol()
{
   return Col;
}
/*----------------------------------------------------------------------------*/
void DisplayObject::SetCol(UWORD16 _Col)
{
	if(IsVisible() && (_Col != Col))
   {
		Hide();
      Col = _Col;
		Show();
	}
	else
   {
      Col = _Col;
	}
}
/*----------------------------------------------------------------------------*/
void DisplayObject::SetParent(DisplayObject *_Parent)
{
   Parent = _Parent;
	SetPage(_Parent->GetPage());
}
/*----------------------------------------------------------------------------*/
DisplayObject* DisplayObject::GetParent()
{
   return Parent;
}
/*----------------------------------------------------------------------------*/
e_BOOL DisplayObject::HaveParent()
{
   return (e_BOOL)(GetParent() != NULL);
}
/*----------------------------------------------------------------------------*/
UWORD16 DisplayObject::GetPage()
{
	DisplayObject* Obj;
	Obj = this;

	while(Obj->HaveParent())
   {
      Obj = Obj->GetParent();
   }
   return Obj->Page;
}
/*----------------------------------------------------------------------------*/
void DisplayObject::SetPage(UWORD16 _Page)
{
   Page = _Page;
}
/*----------------------------------------------------------------------------*/
e_BOOL DisplayObject::IsVisible()
{
   return (e_BOOL)((Visible & DISP_FORCED_VISIBLE) && (Visible & DISP_VISIBLE));
}
/*----------------------------------------------------------------------------*/
void DisplayObject::SetVisible(e_BOOL _V)
{
	if(_V)
		Visible |= DISP_VISIBLE;
	else
		Visible &= ~DISP_VISIBLE;
}
/*----------------------------------------------------------------------------*/
void DisplayObject::SetForcedVisible(e_BOOL _V)
{
	if(_V)
		Visible |= DISP_FORCED_VISIBLE;
	else
		Visible &= ~DISP_FORCED_VISIBLE;
}
/*----------------------------------------------------------------------------*/
e_BOOL DisplayObject::IsRefreshObject()
{
   	return (e_BOOL)(RefreshE == TRUE);
}
/*----------------------------------------------------------------------------*/
void DisplayObject::SetLanguage(UWORD16 Lang)
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
   	Language = Lang;
}
/*----------------------------------------------------------------------------*/
UWORD16 DisplayObject::GetLanguage()
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
   	return(Language);
}
/*----------------------------------------------------------------------------*/
void DisplayObject::SetEndOfInit(e_BOOL _EndOfInit)
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
   	EndOfInit = _EndOfInit;
}
/*----------------------------------------------------------------------------*/
e_BOOL DisplayObject::GetEndOfInit()
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
   	return(EndOfInit);
}
/*----------------------------------------------------------------------------*/
UBYTE* DisplayObject::GetName()
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
   	return((UBYTE *)"");
}
/*----------------------------------------------------------------------------*/
UBYTE* DisplayObject::GetStringValue1()
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
   	return((UBYTE *)"");
}
/*----------------------------------------------------------------------------*/
UBYTE* DisplayObject::GetStringValue2()
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
	return((UBYTE *)"");
}
/*----------------------------------------------------------------------------*/
UBYTE* DisplayObject::GetUnit1()
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
	return((UBYTE *)"");
}
/*----------------------------------------------------------------------------*/
UBYTE* DisplayObject::GetUnit2()
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
   	return((UBYTE *)"");
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
/*%I 		Line : Ligne objet 																	*/
/*%I		Col : Colonne objet																	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void DisplayObject::Init(UWORD16 _Line, UWORD16 _Col)
{
   SetLine(_Line);
   SetCol(_Col);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Arret du monitorage pour l'Objet														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void DisplayObject::StopMonitoringMode()
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Freeze du monitorage pour l'Objet														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void DisplayObject::FreezeMonitoringMode()
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Reprise du monitorage pour l'Objet													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void DisplayObject::StartMonitoringMode()
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Freeze du monitorage pour l'Objet														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		_DisplayFlag : impacte l'affichage ou non 									*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void DisplayObject::FreezeMonitoringModeImpactDisplay(e_BOOL _DisplayFlag)
{
	_DisplayFlag = _DisplayFlag; /* to avoid compilation warning (parameter not used) */
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Reprise du monitorage pour l'Objet													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		_DisplayFlag : impacte l'affichage ou non 									*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void DisplayObject::StartMonitoringModeImpactDisplay(e_BOOL _DisplayFlag)
{
	_DisplayFlag = _DisplayFlag; /* to avoid compilation warning (parameter not used) */
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Arret du monitorage pour l'Objet				   									*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		_DisplayFlag : impacte l'affichage ou non 									*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void DisplayObject::StopMonitoringModeImpactDisplay(e_BOOL _DisplayFlag)
{
	_DisplayFlag = _DisplayFlag; /* to avoid compilation warning (parameter not used) */
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Determine si l'objet peut etre rafraichi											*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		RefreshE : TRUE si rafraichi														*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void DisplayObject::RefreshEnable(e_BOOL _RefreshE)
{
   /*%C Turn over the state of refresh */
   RefreshE =  _RefreshE;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Refresh de l'affichage																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void DisplayObject::Refresh()
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage	de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void DisplayObject::Show()
{
   /*%C Show this object */
   SetVisible(TRUE);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void DisplayObject::Hide()
{
	/*%C Hide this object */
   SetVisible(FALSE);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Blink de l'Objet																			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void DisplayObject::Blink(e_BOOL _Actif)
{
	/* Pour éviter les warnings */
	_Actif = _Actif;
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Operation de changement de la langue de l'Objet		 							*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void DisplayObject::RefreshLanguage()
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Renvoi la valeur complète d'un objet                                     */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		Valeur  							  														*/
/******************************************************************************/
UWORD16 DisplayObject::GetFullValue()
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
   	return(0);
}
