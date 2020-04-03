/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_GraphTitle.cpp	                                 	 		*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage	(text + white background)								      */
/*		                                                                        */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_GraphTitle.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_DisplayObject.hpp"
#include "HMI_DataBaseAccess.hpp"
#include "HMI_InterfaceCppC.hpp"
#include "HMI_Tools.hpp"
#include "HMI_Message.hpp"
#include "DB_Config.h"


#define BACKGROUND_HEIGHT			   22
#define BACKGROUND_WIDTH            104
#define TITLE_HEIGHT                16
#define LEFT_MARGIN_WIDTH			   7
#define RIGHT_MARGIN_WIDTH			   7

extern UWORD16 Language;
extern UWORD16 NbLanguage;


/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
GraphTitle::GraphTitle():DisplayObject()
{
   TFMode.SetParent(this);
	TFMode.Init(TITLE_HEIGHT,0,FONT_4,TRUE,(UBYTE *)"");
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
e_BOOL GraphTitle::IsPressureMode()
{
   UWORD16 Mode;
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */

   DataBaseAccess::ReadValue(&Mode,ADJUST_MODE_U16,CONFIG);
   return (e_BOOL)(Mode==PRES || Mode==PSVT);
}
/*----------------------------------------------------------------------------*/
e_BOOL GraphTitle::IsChangingMode()
{
   	UWORD16 CurrentMode;
   	UWORD16 AdjustMode;
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */

   	DataBaseAccess::ReadValue(&CurrentMode,CURRENT_MODE_U16,CONTROL);
  	DataBaseAccess::ReadValue(&AdjustMode,ADJUST_MODE_U16,CONFIG);
   	return (e_BOOL) (CurrentMode != AdjustMode);
}
/*----------------------------------------------------------------------------*/
void GraphTitle::SetNameMode2Display(e_BOOL _NameMode2Display)
{
   NameMode2Display = _NameMode2Display;
}
/*----------------------------------------------------------------------------*/
e_BOOL GraphTitle::IsNameMode2Display()
{
   return NameMode2Display;
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
/*%I		Icon : icone												               		*/
/*%I		Name : Pointeur sur le tableau de nom						         		*/
/*%I		Line : ligne 												               		*/
/*%I		Col : colonne												            			*/
/*%I		Value1 : Valeur 1											               		*/
/*%I		ValueRefresh : Valeur pour le champ de refresh								*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void GraphTitle::Init(  UWORD16 _Line,
                        UWORD16 _Col,
                        UBYTE** _NameMode1,
                        UBYTE** _NameMode2,
                        UBYTE** _TargetVT)
{
	_TargetVT = _TargetVT;
	DisplayObject::Init(_Line, _Col);
   	NameMode1 = _NameMode1;
   	NameMode2 = _NameMode2;

   	TFMode.SetText(NameMode1[VOL*NbLanguage + GetLanguage()]);
   	TFMode.SetCol(LEFT_MARGIN_WIDTH);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Refresh de l'état du paramètre VT														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void GraphTitle::Refresh()
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Retourne nom du mode 																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	Mode : Numero du mode								               			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		Nom long d'un mode			  														*/
/******************************************************************************/
UBYTE* GraphTitle::GetNameMode(e_MODE_TYPES _Mode)
{
   if(!IsNameMode2Display())
   {
      return GetNameMode1(_Mode);
   }
   else
   {
      return GetNameMode2(_Mode);
   }
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Retourne le nom court d'un mode														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	Mode : Numero du mode								               			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		Nom court d'un mode			  														*/
/******************************************************************************/
UBYTE* GraphTitle::GetNameMode2(e_MODE_TYPES _Mode)
{
   if(NameMode2 != NULL)
   {
      UBYTE **tmp;
      tmp = NameMode2;

      /*%C positionnement de la ligne (ici NB_LANGUAGE = nb de langues) */
      tmp = &tmp[NB_LANGUAGE*(_Mode)];

      /*%C lecture de la colonne */
      return tmp[GetLanguage()];
   }
   else
	{
      return (UBYTE *)"???";
	}
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Retourne le nom court d'un mode														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	Mode : Numero du mode								               			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		Nom court d'un mode			  														*/
/******************************************************************************/
UBYTE* GraphTitle::GetNameMode1(e_MODE_TYPES _Mode)
{
   if(NameMode2 != NULL)
   {
      UBYTE **tmp;
      tmp = NameMode1;

      /*%C positionnement de la ligne (ici NB_LANGUAGE = nb de langues) */
      tmp = &tmp[NB_LANGUAGE*(_Mode)];

      /*%C lecture de la colonne */
      return tmp[GetLanguage()];
   }
   else
	{
      return (UBYTE *)"???";
	}
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage	de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void GraphTitle::Show()
{

	DisplayObject::Show();

	InterfaceCppC::DisBox(  GetLine(),
									GetCol(),
									BACKGROUND_HEIGHT-1,
                           BACKGROUND_WIDTH-1,
                           TRUE,
                           1,
                           GetPage());    

	InterfaceCppC::DisplaySymbol( CADRE_WHITE_BGw,
											GetLine()+BACKGROUND_HEIGHT-4,
                                 GetCol(), 
                                 GetPage());

	InterfaceCppC::DisplaySymbol( CADRE_WHITE_BDw,
											GetLine()+BACKGROUND_HEIGHT-4,
                                 GetCol()+BACKGROUND_WIDTH-1-3, 
                                 GetPage());

	InterfaceCppC::DisplaySymbol(	CADRE_WHITE_HGw,
											GetLine(), 
											GetCol(),
											GetPage());

	InterfaceCppC::DisplaySymbol( CADRE_WHITE_HDw,
											GetLine(),
                                 GetCol()+BACKGROUND_WIDTH-1-3, 
                                 GetPage());

   UWORD16 CurrentMode;
   DataBaseAccess::ReadValue(&CurrentMode,ADJUST_MODE_U16,CONFIG);
   TFMode.SetText((UBYTE*)GetNameMode((e_MODE_TYPES)CurrentMode));

   TFMode.SetCol(	1 +
                  (BACKGROUND_WIDTH -
                  TFMode.GetPixelSize())/2);

	TFMode.Show();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void GraphTitle::Hide()
{
	TFMode.Hide();

	InterfaceCppC::DisBox(  GetLine(),
									GetCol(),
									BACKGROUND_HEIGHT-1,
                           BACKGROUND_WIDTH-1,
                           TRUE,
                           0,
                           GetPage());
	DisplayObject::Hide();                           
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Refresh du titre                                                         */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void GraphTitle::RefreshLanguage()
{
   UWORD16 CurrentMode;
   DataBaseAccess::ReadValue(&CurrentMode,ADJUST_MODE_U16,CONFIG);
   TFMode.SetText((UBYTE*)GetNameMode((e_MODE_TYPES)CurrentMode));
}
