/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_GraphicBox.cpp	                                 			*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Affichage d'une boite avec angle arrondis									      */
/*		                                                                        */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_GraphicBox.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_InterfaceCppC.hpp"

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
GraphicBox::GraphicBox():DisplayObject()
{
	Height = 0;
   Width = 0;
	FloodBlack = FALSE;
	RoundLow = FALSE;
	RoundHigh = FALSE;
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void GraphicBox::SetFloodBlack(e_BOOL _FloodBlack)
{
	FloodBlack = _FloodBlack;
}
/*----------------------------------------------------------------------------*/
e_BOOL GraphicBox::IsFloodBlack()
{
	return (e_BOOL)(FloodBlack == TRUE);
}
/*----------------------------------------------------------------------------*/
void GraphicBox::SetHeight(UWORD16 _Height)
{
   Height = _Height;
}
/*----------------------------------------------------------------------------*/
UWORD16 GraphicBox::GetHeight()
{
	return Height;
}
/*----------------------------------------------------------------------------*/
void GraphicBox::SetWidth(UWORD16 _Width)
{
   Width = _Width;
}
/*----------------------------------------------------------------------------*/
UWORD16 GraphicBox::GetWidth()
{
	return Width;
}
/*----------------------------------------------------------------------------*/
void GraphicBox::SetRoundLow(e_BOOL _RoundLow)
{
	RoundLow = _RoundLow;
}
/*----------------------------------------------------------------------------*/
e_BOOL GraphicBox::GetRoundLow()
{
	return RoundLow;
}
/*----------------------------------------------------------------------------*/
void GraphicBox::SetRoundHigh(e_BOOL _RoundHigh)
{
	RoundHigh = _RoundHigh;
}
/*----------------------------------------------------------------------------*/
e_BOOL GraphicBox::GetRoundHigh()
{
	return RoundHigh;
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
/*%I		Line : Ligne 											            				*/
/*%I		Col : Colonne											            				*/
/*%I		Height : Hauteur 											            			*/
/*%I		Width : Largeur                                            				*/
/*%I 		RounHigh : Box arrondie en Haut								      			*/
/*%I     RounLow : Box arrondie en Bas								         			*/
/*%I		FloodBlack : en Noir si TRUE 														*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void GraphicBox::Init(  UWORD16 _Line, 
								UWORD16 _Col, 
								UWORD16 _Height,
                        UWORD16 _Width, 
                        e_BOOL _RoundHigh, 
                        e_BOOL _RoundLow,
                        e_BOOL _FloodBlack)
{
	/*%C Initialization */
   DisplayObject::Init(_Line, _Col);
   SetHeight(_Height);
   SetWidth(_Width);
   SetRoundHigh(_RoundHigh);
   SetRoundLow(_RoundLow);
   SetFloodBlack(_FloodBlack);
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
void GraphicBox::Show()
{


	if(IsFloodBlack())
   {

      /*%C Effacement des bords uniquement pour les bords ronds */
     	if(GetRoundHigh() || GetRoundLow())
      {
 		   /*%C Découpe du rectangle en trois pour ne pas effacer les angle */
         /*%C arrondis à chaque refresh */
         /*%C Rectangle principal (millieu) */
		   InterfaceCppC::DisBox(  GetLine(),
										   GetCol()+4,
										   GetHeight(),
										   GetWidth()-8,
                                 IsFloodBlack(),
                                 1,
                                 GetPage());

         /*%C Petit Rectangle de gauche */
		 InterfaceCppC::DisBox(  GetLine()+4,
     									   GetCol(),
     									   GetHeight()-8,
     									   4,
     									   IsFloodBlack(),
                                 1,GetPage());
         /*%C Petit Rectangle de droite */
         InterfaceCppC::DisBox(  GetLine()+4,
      								   GetCol()+GetWidth()-4,
      								   GetHeight()-8,
                                 4,
                                 IsFloodBlack(),
                                 1,
                                 GetPage());
      }
      else
      {

		 /*%C Effacement du rectangle entier */
		   InterfaceCppC::DisBox(  GetLine(),
										   GetCol(),
										   GetHeight(),
										   GetWidth(),
                                 IsFloodBlack(),
                                 1,
                                 GetPage());
      }


   }
   else
   {
      InterfaceCppC::DisBox(  GetLine(),
      								GetCol(),
      								GetHeight(),
      								GetWidth(),
                              IsFloodBlack(),
                              1,
                              GetPage());

   }
   if(GetRoundHigh())
   {
		if (IsFloodBlack())
      {
			/*%C Construction du rectangle blanc */
			InterfaceCppC::DisplaySymbol( CADRE_WHITE_HDw,
													GetLine(),
                                       GetCol()+GetWidth()-3,
                                       GetPage());

			InterfaceCppC::DisplaySymbol( CADRE_WHITE_HGw, 
													GetLine(),
													GetCol(),
                                       GetPage());
      }
      else
      {
			/*%C Construction du rectangle noir */
			InterfaceCppC::DisplaySymbol( CADRE_BLACK_HDw,
													GetLine(),
                                       GetCol()+GetWidth()-3,
                                       GetPage());

			InterfaceCppC::DisplaySymbol( CADRE_BLACK_HGw, 
													GetLine(),
													GetCol(),
                                       GetPage());
      }
   }
   if(GetRoundLow())
   {
	   if (IsFloodBlack())
      {
			/*%C Construction du rectangle blanc */
			InterfaceCppC::DisplaySymbol( CADRE_WHITE_BDw,
													GetLine()+GetHeight()-3,
                                       GetCol()+GetWidth()-3,
                                       GetPage());

			InterfaceCppC::DisplaySymbol( CADRE_WHITE_BGw, 
													GetLine()+GetHeight()-3,
                                       GetCol(),
                                       GetPage());
      }
		else
      {
			/*%C Construction du rectangle noir */
			InterfaceCppC::DisplaySymbol( CADRE_BLACK_BDw,
													GetLine()+GetHeight()-3,
                                       GetCol()+GetWidth()-3,
                                       GetPage());

			InterfaceCppC::DisplaySymbol( CADRE_BLACK_BGw, 
													GetLine()+GetHeight()-3,
                                       GetCol(),
                                       GetPage());
      }
   }

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
void GraphicBox::Hide()
{
   InterfaceCppC::DisBox(  GetLine(),
   								GetCol(),
   								GetHeight(),
   								GetWidth(),
   								TRUE,
   								0,
						   GetPage());
   if(GetRoundHigh())
   {
		/*%C Effacement des fenetres */
      InterfaceCppC::EraseZone(	GetLine(),
      									GetCol()+GetWidth()-3,
      									3,
      									3,
      									0,
      									GetPage());

		InterfaceCppC::EraseZone(	GetLine(),
											GetCol(),
											3,
											3,
											0,
											GetPage());
   }
   if(GetRoundLow())
   {
		/*%C Effacement des fenetres */
      InterfaceCppC::EraseZone(  GetLine()+GetHeight()-4,
      									GetCol()+GetWidth()-3,
                                 4,
                                 3,
                                 0,
                                 GetPage());

		InterfaceCppC::EraseZone(	GetLine()+GetHeight()-4,
											GetCol(),
											3,
											3,
											0,
											GetPage());
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
void GraphicBox::RefreshBoxRound(UWORD16 _BackGround)
{

	if(_BackGround == 0)
	{
		InterfaceCppC::DisBox(  GetLine()+2,
								GetCol()+2,
								GetHeight()-4,
								GetWidth()-4,
								TRUE,
								1,
						   GetPage());

		/*%C Construction du rectangle blanc */
		InterfaceCppC::DisplaySymbol( CADRE_WHITE_ALARM_HDw,
												GetLine(),
									GetCol()+GetWidth()-3,
									GetPage());

		InterfaceCppC::DisplaySymbol( CADRE_WHITE_ALARM_HGw,
												GetLine(),
												GetCol(),
									GetPage());

		/*%C Construction du rectangle blanc */
		InterfaceCppC::DisplaySymbol( CADRE_WHITE_ALARM_BDw,
												GetLine()+GetHeight()-3,
									GetCol()+GetWidth()-3,
									GetPage());

		InterfaceCppC::DisplaySymbol( CADRE_WHITE_ALARM_BGw,
												GetLine()+GetHeight()-3,
									GetCol(),
									GetPage());
	}
	else
	{

		InterfaceCppC::DisBox(  GetLine(),
								GetCol(),
								GetHeight(),
								GetWidth(),
								FALSE,
								1,
						   GetPage());

		/*%C Construction du rectangle noir */
		InterfaceCppC::DisplaySymbol( CADRE_BLACK_HDw,
												GetLine(),
								   GetCol()+GetWidth()-3,
								   GetPage());

		InterfaceCppC::DisplaySymbol( CADRE_BLACK_HGw,
												GetLine(),
												GetCol(),
								   GetPage());

		/*%C Construction du rectangle noir */
		InterfaceCppC::DisplaySymbol( CADRE_BLACK_BDw,
												GetLine()+GetHeight()-3,
								   GetCol()+GetWidth()-3,
								   GetPage());

		InterfaceCppC::DisplaySymbol( CADRE_BLACK_BGw,
												GetLine()+GetHeight()-3,
								   GetCol(),
								   GetPage());
	}
}

