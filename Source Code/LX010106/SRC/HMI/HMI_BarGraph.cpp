/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_BarGraph.cpp           	                         			*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Champ Bargraph																		      */
/*		                                                                        */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_BarGraph.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_DataBaseAccess.hpp"
#include "HMI_InterfaceCppC.hpp"
#include "Driver_Display_Data.h"

/******************************************************************************/
/*                             #DEFINE		                        				*/
/******************************************************************************/

/*%C Origine : Coint inférieur gauche */

#define STARTLINE_VERT 			33
#define STARTCOLUMN_VERT 		162
#define HEIGTH_VERT		   	192
#define WIDTH_VERT				10
#define LIMIT_BAR_VERT 			190

/*%C Origine : Coint supérieur gauche, chiffres non-inclus */

#define STARTLINE_HOR			194
#define STARTCOLUMN_HOR			2
#define HEIGTH_HOR		   	14
#define WIDTH_HOR					315
#define LIMIT_BAR_HOR			306

#define LONG_GRAD		   		4
#define SMALL_GRAD				2
#define MAX_BARGRAPH_MBAR		90
#define STEP_GRADUATION			10


/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
BarGraph::BarGraph():DisplayObject()
{

}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void BarGraph::SetNameUnit(UBYTE** _NameUnit)
{
   UWORD16 _PixelSize;
   
   NameUnit = _NameUnit;
   TFUnit.SetTextOnly(GetNameUnit());

   if(GetPosition() == VERT)
   {
      /*%C On réajuste la colonne pour le centrage */
      _PixelSize = TFUnit.GetPixelSize();
      if((_PixelSize) && (GetCol() >= (_PixelSize/2)))
         TFUnit.SetCol(GetCol() - (_PixelSize/2));
   }
   TFUnit.SetVisible(TRUE);
   TFUnit.Show();
//   RefreshUnitDisplay();   
}
/*----------------------------------------------------------------------------*/
UBYTE* BarGraph::GetNameUnit()
{
	if(NameUnit != NULL)
   {
		return (NameUnit[GetLanguage()]);
	}
	else
	{
      return (UBYTE *)"???";
	}
}
/*----------------------------------------------------------------------------*/
void BarGraph::SetValue(UWORD16 _Value)
{
	if(this->GetValue() != _Value)
   {
		Value = _Value;
		Show();
   }
}
/*----------------------------------------------------------------------------*/
UWORD16 BarGraph::GetValue()
{
   return Value;
}
/*----------------------------------------------------------------------------*/
void BarGraph::SetPep(UWORD16 _Pep)
{
   Pep = _Pep;
}
/*----------------------------------------------------------------------------*/
UWORD16 BarGraph::GetPep()
{
   return Pep;
}
/*----------------------------------------------------------------------------*/
void BarGraph::SetPmax(UWORD16 _Pmax)
{
   Pmax = _Pmax;
}
/*----------------------------------------------------------------------------*/
UWORD16 BarGraph::GetPmax()
{
   return Pmax;
}
/*----------------------------------------------------------------------------*/
void BarGraph::SetPosition(UWORD16 _Position)
{
   Position = _Position;
}
/*----------------------------------------------------------------------------*/
UWORD16 BarGraph::GetPosition()
{
   return Position;
}

/*----------------------------------------------------------------------------*/
void BarGraph::SetDivider(UWORD16 _Divider)
{
   Divider = _Divider;
}
/*----------------------------------------------------------------------------*/
UWORD16 BarGraph::GetDivider()
{
	return Divider;
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
/*%I 		Line : ligne													               	*/
/*%I		Col  : colonne												              			*/
/*%I		Position : sens du bargraph     								         		*/
/*%I		Value    : valeur courante						         						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void BarGraph::Init( UWORD16 _Line,
                     UWORD16 _Col,
                     UWORD16 _Position,
                     UWORD16 _Value,
                     UBYTE** _NameUnit)
{

	DisplayObject::Init(_Line,_Col);
   SetValue(_Value);
	SetPosition(_Position);
	firstShow = 1;

   if(_Position == VERT)
   {
	  _Line += HEIGTH_VERT+6;
      _Col += 0;
      TFUnit.Init( _Line, _Col, FONT_2, FALSE, _NameUnit[GetLanguage()]);
   }
   else if (_Position == HORI)
   {
      _Line +=  HEIGTH_HOR+LONG_GRAD+10;
      _Col += WIDTH_HOR-21;
      TFUnit.Init( _Line, _Col, FONT_2, FALSE, _NameUnit[GetLanguage()]);
   }
   else
      TFUnit.Init( 0, 0, FONT_2, FALSE, _NameUnit[GetLanguage()]);

   SetNameUnit(_NameUnit);
         
   Show();
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Rafraîchi	l'affichage de l'unité de pression du bargraph						*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 	 NONE																					  	   */
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void BarGraph::RefreshUnitDisplay(void)
{
   TFUnit.Hide();
   TFUnit.Show();   
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation des paramettres d'acce a DB											*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		IdParam : Id DB													               */
/*%I		DbTarget : Target DB											            		*/
/*%I		IdParam2 : Id DB de la valeur2								            	*/
/*%I		DbTarget2 : Target DB	de la valeur2						         	  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void BarGraph::InitDbAccess(  UWORD16 _IdParam,
                              e_TYPE_OF_DB_TARGET _DbTarget,
                              UWORD16 _IdPmax,
                              UWORD16 _IdPep)
{
   DisplayObject::InitDbAccess(_IdParam,_DbTarget);
   IdPep = _IdPep;
   IdPmax = _IdPmax;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Refresh de l'affichage																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																	         	  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void BarGraph::Refresh()
{
   if(GetIdParam() != NO_ID)
   {
      UWORD16 Value;

		/*%C Refresh prameters */
      DataBaseAccess::ReadValue(&Value, GetIdParam(), GetDbTarget());
      SetValue(Value);

		DataBaseAccess::ReadValue(&Value, IdPep, GetDbTarget());
		/*%C Gestion du Diviseur */
		Value = Value / Divider;
      Pep = Value;

		DataBaseAccess::ReadValue(&Value, IdPmax, GetDbTarget());
		/*%C Gestion du Diviseur */
		Value = Value / Divider;
      Pmax = Value;
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage	de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																	         	  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void BarGraph::Show()
{
	UWORD16 SpaceGrad, i;

	if(firstShow)
   {
    	switch(GetPosition())
      {
         default :
            break;
         case HORI :
			/*%C Affichage rectangle du bargraph horizontal */
		   /*%C Effacement de la zone d'affichage */
   		InterfaceCppC::EraseZone(  STARTLINE_HOR + LONG_GRAD+1,
                                    STARTCOLUMN_HOR+1,
                                    HEIGTH_HOR-1,
                                    WIDTH_HOR-2, 
                                    0, 
                                    GetPage());
                                    
         RefreshUnitDisplay();

			/*%C Calcul de l'espacement des graduations */
			SpaceGrad = (10*LIMIT_BAR_HOR) / MAX_BARGRAPH_MBAR;

			/*%C Affichage les graduations */
			for(i=0; i<=MAX_BARGRAPH_MBAR; i+=STEP_GRADUATION/2)
			{
				/*%C Affichage des traits de graduation avec les "pairs" */
            /*%C plus grands complétés des valeurs numériques */
				if (i%2 == 0)
					{
   					/*%C ATTENTION - Afficher les numéros en 1er pour ne pas */
                  /*%C effacer les graduations */
						if (i == 0)
							/*%C Décalage pour centrer le "0" sur la 1ère graduation */
  							InterfaceCppC::DisplayNumber( i,
  																	INTEGER, 
  																	FALSE,
                                                   STARTLINE_HOR - LONG_GRAD+1,
                                                   ((i*SpaceGrad)/10) + 
                                                   STARTCOLUMN_HOR+1,
                                                   FONT_2, 
                                                   2, 
                                                   FALSE, 
                                                   1, 
                                                   GetPage());
						else
							/*%C Décalage pour centrer les chiffres sur */
                     /*%C les graduations */
  							InterfaceCppC::DisplayNumber( i,
  																	INTEGER,
  																	FALSE,
                                                   STARTLINE_HOR - LONG_GRAD+1,
                                                   ((i*SpaceGrad)/10) + 
                                                   STARTCOLUMN_HOR-4,
                                                   FONT_2, 
                                                   2, 
                                                   FALSE, 
                                                   1, 
                                                   GetPage());

   					/*%C Affichage des "longues" graduations */
						InterfaceCppC::DisplayLine (  STARTLINE_HOR,
                                                STARTCOLUMN_HOR + 
                                                ((i*SpaceGrad)/10),
                                                LONG_GRAD, 
                                                0,
                                                1,
                                                GetPage());

						}
               else
						/*%C Affichage des "courtes" graduations */
						InterfaceCppC::DisplayLine (  STARTLINE_HOR + LONG_GRAD - 
																SMALL_GRAD,
                                                STARTCOLUMN_HOR + 
                                                ((i*SpaceGrad)/10),
                                                SMALL_GRAD, 
                                                0,
                                                1,
                                                GetPage());

         }
			/*%C Affichage rectangle du bargraph horizontal */
			InterfaceCppC::DisBox(  STARTLINE_HOR + LONG_GRAD,STARTCOLUMN_HOR,
                                 HEIGTH_HOR+1, 
                                 WIDTH_HOR, 
                                 FALSE, 
                                 1, 
                                 GetPage());

			/*%C Affichage Pixel afin d'arrondir les angles */
			InterfaceCppC::DisplayPixel(  STARTLINE_HOR + LONG_GRAD,
                                       STARTCOLUMN_HOR+WIDTH_HOR, 
                                       0, 
                                       GetPage());

			/*%C Affichage Pixel afin d'arrondir les angles */
			InterfaceCppC::DisplayPixel(  STARTLINE_HOR + LONG_GRAD + HEIGTH_HOR+1,
                                       STARTCOLUMN_HOR + WIDTH_HOR, 
                                       0, 
                                       GetPage());

			break;

         case VERT :
         /*%C Effacement de la zone d'affichage */
			InterfaceCppC::EraseZone(  STARTLINE_VERT+1,
                                    STARTCOLUMN_VERT,HEIGTH_VERT-2,
                                    WIDTH_VERT-1,
                                    0,
                                    GetPage());

         RefreshUnitDisplay();

			/*%C Calcul de l'espacement des graduations */
			/*%C Arrondie de SpaceGrad à 20, car on utilise pas la totalité */
         /*%C de la fenêtre bargraph*/
			/*%C avec la taille actuelle on pourrais loger une demi-graduation */
         /*%C de plus ou espacer un peu plus les graduations */
			/*%C mais le calcul des graduations est plus simple avec */
         /*%C un espacement de 10. */
			SpaceGrad = 20;

			/*%C Affichage des valeurs numériques de graduation */
         /*%C = 306 / (2*(90/10)/2) */
			for(i=0; i<=MAX_BARGRAPH_MBAR; i+=5)
			{
				/*%C Affichage des traits de graduation avec les "pairs" plus */
            /*%C grands complétés des valeurs numériques */
				if (i%2 == 0)
				{
					/*%C Alignement des valeurs sur les graduations */
					InterfaceCppC::DisplayNumber( i,
															INTEGER, 
															FALSE,
                                             STARTLINE_VERT + HEIGTH_VERT - 
                                             ((i*SpaceGrad)/10),
                                             STARTCOLUMN_VERT + WIDTH_VERT+8,
                                             FONT_2, 
                                             2, 
                                             FALSE, 
                                             1, 
                                             GetPage());

					/*%C Affichage des "longues" graduations	- SpaceGrad) */
               /*%C LIMIT_BAR_VERT = 2 */
					InterfaceCppC::DisplayLine (  STARTLINE_VERT + HEIGTH_VERT - 
															((i*SpaceGrad)/10),
                                             STARTCOLUMN_VERT + WIDTH_VERT, 
                                             0,
                                             LONG_GRAD,
                                             1,
                                             GetPage());
				}
				else
					/*%C Affichage des "courtes" graduations */
					InterfaceCppC::DisplayLine (  STARTLINE_VERT + HEIGTH_VERT - 
															((i*SpaceGrad)/10),
                                             STARTCOLUMN_VERT + WIDTH_VERT, 
                                             0,
                                             SMALL_GRAD,
                                             1,
                                             GetPage());
			}

   		/*%C Affichage rectangle du bargraph vertical */
			InterfaceCppC::DisBox(  STARTLINE_VERT,
											STARTCOLUMN_VERT-1,
                                 HEIGTH_VERT,
                                 WIDTH_VERT+1, 
                                 FALSE, 
                                 1, 
                                 GetPage());

			/*%C Affichage Pixel afin d'arrondir les angles */
			InterfaceCppC::DisplayPixel(  STARTLINE_VERT,
													STARTCOLUMN_VERT-1, 
													0,
                                       GetPage());

			/*%C Affichage Pixel afin d'arrondir les angles */
			InterfaceCppC::DisplayPixel(  STARTLINE_VERT,
													STARTCOLUMN_VERT + WIDTH_VERT,
                                       0, 
                                       GetPage());
         break;
      }
   firstShow = 0;
	}

	DisplayObject::Show();
	DisplayBargraph(GetValue(),Pmax,Pep,GetPosition(),1, GetPage());
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement de l'Objet 																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																	         	  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void BarGraph::Hide()
{
   /*%C Lecture Pep et Pmax */
	DisplayObject::Hide();

	DisplayBargraph(GetValue(),Pmax,Pep,GetPosition(),0, GetPage());
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage du bargraph 																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																	         	  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void BarGraph::DisplayBargraph(  SWORD16 _value,
                                 SWORD16 _Pmax,
                                 SWORD16 _Pep,
                                 UBYTE _position,
                                 UBYTE _printon, 
                                 UBYTE _page)
{
	_page = _page; 			/* Pour éviter les warnings */
	_printon = _printon;	/* Pour éviter les warnings */

	SWORD16 displayline=0, dec_value=0, dec_memoValue=0;

	static SWORD16 memoValue=0;
	static SWORD16 memoPep=0;
	static SWORD16 memoPmax=0;
	static e_BOOL mutex_deltaVert=FALSE;
	static e_BOOL mutex_deltaHori=FALSE;

	/*%C Saturation de la mesure */
	if (_value < 0)
   {
      _value = 0;
   }

	/*%C Bargraph VERTICAL */
	if (_position == VERT)
   {
		/*%C Réajustement => 180 pixels pour 90 mbars */
		/*%C Réajustement par rapport à la zone d'affichage du bargraph */
      /*%C à l'intérieur du cadre donc -1 */
		_value /= 5;
		_Pmax *= 2;
		_Pep *= 2;

		/*%C Limites du bargraph */
		if (_value >= LIMIT_BAR_VERT) 
		{
			_value = LIMIT_BAR_VERT;
		}
	
		if (_Pmax >= LIMIT_BAR_VERT) 
		{
			_Pmax = LIMIT_BAR_VERT;
		}
	
		if (_Pep >= LIMIT_BAR_VERT) 
		{
			_Pep = LIMIT_BAR_VERT;
		}

		/*%C Affichage cadre du bargraph */
      if (mutex_deltaVert == FALSE)
		{
			/*%C Effacement de la zone d'affichage */
			InterfaceCppC::EraseZone(  STARTLINE_VERT +
												1,
												STARTCOLUMN_VERT,
                                    HEIGTH_VERT -
                                    2,
                                    WIDTH_VERT -
                                    1, 
                                    0, 
                                    GetPage());

			memoValue = 0;
			memoPmax = 0;
			memoPep = 0;
			mutex_deltaHori = FALSE;
			mutex_deltaVert = TRUE;
      }

		/*%C Ecart d'affichage */
		displayline = _value - memoValue;

		/*%C Calcul du décalage */
		if (_value == 0)
      {
         dec_value = 1;
      }
		else
      {
         dec_value = 0;
      }
		if (memoValue == 0)
      {
         dec_memoValue = 1;
      }
		else
      {
         dec_memoValue = 0;
      }

		/*%C Affichage du remplissage du bargraph */
		/*%C Sens = montée de pression */
		if (displayline > 0)
      {
			/*%C Affichage rectangle du bargraph vertical */
			InterfaceCppC::DisBox(  STARTLINE_VERT + 
											HEIGTH_VERT-dec_value -
											_value,
                                 STARTCOLUMN_VERT,
                                 dec_value +
                                 _value -
                                 dec_memoValue -
                                 memoValue,
                                 WIDTH_VERT-1,
                                 TRUE,
                                 1,
                                 GetPage());

      }
		/*%C Sens = descente de pression */
		else if (displayline < 0)
      {
         InterfaceCppC::EraseZone(  STARTLINE_VERT + 	
         									HEIGTH_VERT -
         									dec_memoValue -
         									memoValue,
                                    STARTCOLUMN_VERT,
                                    dec_memoValue +
                                    memoValue -
                                    dec_value -
                                    _value,
                                    WIDTH_VERT-1,
                                    0,
                                    GetPage());

      }
		/*%C Effacement curseur Pmax */
		if (memoPmax > 0)
 	   	{
		   	if (memoPmax < _value)
            {
				   InterfaceCppC::DisplayLine (  STARTLINE_VERT + 
				   										HEIGTH_VERT - 
				   										memoPmax,
                                             STARTCOLUMN_VERT, 
                                             0, 
                                             WIDTH_VERT-1,
                                             1,
                                             GetPage());
            }
			   else
            {
				   InterfaceCppC::DisplayLine (  STARTLINE_VERT + 
				   										HEIGTH_VERT - 
				   										memoPmax,
				   										STARTCOLUMN_VERT,
                                             0, 
                                             WIDTH_VERT-1,
                                             0,
                                             GetPage());
            }
         }

		/*%C Affichage curseur Pmax */
		if (_Pmax > 0)
      {
			if (_Pmax < _value)
         {
				InterfaceCppC::DisplayLine (  STARTLINE_VERT + 
														HEIGTH_VERT - 
														_Pmax,
                                          STARTCOLUMN_VERT,
                                          0,
                                          WIDTH_VERT-1,
                                          0,
                                          GetPage());
         }
			else
         {
				InterfaceCppC::DisplayLine (  STARTLINE_VERT + 
														HEIGTH_VERT - 
														_Pmax,
                                          STARTCOLUMN_VERT,
                                          0,
                                          WIDTH_VERT-1,1,
                                          GetPage());
         }
      }

      /*%C Effacement curseur Pep */
		if (memoPep > 0)
      {
			if (memoPep < _value)
         {
				InterfaceCppC::DisplayLine (  STARTLINE_VERT + 
														HEIGTH_VERT - 
														memoPep,
                                          STARTCOLUMN_VERT,
                                          0,
                                          WIDTH_VERT-1,1,
                                          GetPage());
         }
			else
         {
				InterfaceCppC::DisplayLine (  STARTLINE_VERT + 
														HEIGTH_VERT - 
														memoPep,
                                          STARTCOLUMN_VERT,
                                          0,
                                          WIDTH_VERT-1,0,
                                          GetPage());
         }
      }

		/*%C Affichage curseur Pmax */
		if (_Pep > 0)
      {
			if (_Pep < _value)
         {
				InterfaceCppC::DisplayLine (  STARTLINE_VERT + 
														HEIGTH_VERT - 
														_Pep,
                                          STARTCOLUMN_VERT,
                                          0,
                                          WIDTH_VERT 	
                                          -1,
                                          0,
                                          GetPage());
         }
			else
         {
				InterfaceCppC::DisplayLine (  STARTLINE_VERT + 
														HEIGTH_VERT - 
														_Pep,
                                          STARTCOLUMN_VERT,
                                          0,
                                          WIDTH_VERT-1,
                                          1,
                                          GetPage());
			}
 		}

   }
	/*%C Bargraph HORIZONTAL */
	else
	{
		/*%C Réajustement => 306 pixels pour 90 mbars */
		/*%C Réajustement par rapport à la zone d'affichage du bargraph */
      /*%C à l'intérieur du cadre donc -1 */
		_value = (SWORD16)((_value * 306UL) / 900);
		_Pmax = (SWORD16)((_Pmax * 306UL) / 90);
		_Pep = (SWORD16)((_Pep * 306UL) / 90);

		/*%C Limites du bargraph */
		if (_value >= LIMIT_BAR_HOR) 
		{
			_value = LIMIT_BAR_HOR;
		}

 		if (_Pmax >= LIMIT_BAR_HOR) 
 		{
 			_Pmax = LIMIT_BAR_HOR;
		}

		if (_Pep >= LIMIT_BAR_HOR) 
		{
			_Pep = LIMIT_BAR_HOR;
		}

		/*%C Affichage cadre du bargraph */
		if (mutex_deltaHori == FALSE)
		{
			/*%C Effacement de la zone d'affichage */
			InterfaceCppC::EraseZone(  STARTLINE_HOR + 
												LONG_GRAD +
												1,
                                    STARTCOLUMN_HOR +
                                    1,
                                    HEIGTH_HOR -
                                    1,
                                    WIDTH_HOR -
                                    2,
                                    0,
                                    GetPage());
			memoValue = 0;
			memoPmax = 0;
			memoPep = 0;
			mutex_deltaVert = FALSE;
			mutex_deltaHori = TRUE;
		}

	  	/*%C Ecart d'affichage */
		displayline = _value - memoValue;

		/*%C Calcul du décalage */
		if (_value == 0)
      {
         dec_value = 1;
      }
		else
      {
         dec_value = 0;
      }
		if (memoValue == 0)
      {
         dec_memoValue = 1;
      }
		else
      {
         dec_memoValue = 0;
      }

		/*%C Affichage du remplissage du bargraph */
		/*%C Sens = montée de pression */
		if (displayline > 0)
		{
			InterfaceCppC::DisBox(  STARTLINE_HOR + 
											LONG_GRAD +
											1,
                                 STARTCOLUMN_HOR +
                                 dec_memoValue +
                                 memoValue,
                                 HEIGTH_HOR- 
                                 1,
                                 dec_value +
                                 _value-dec_memoValue -
                                 memoValue,
                                 TRUE, 
                                 1,
                                 GetPage());
      }
		
		/*%C Sens = descente de pression */
		else if (displayline < 0)
      {
			InterfaceCppC::EraseZone(  STARTLINE_HOR + 
												LONG_GRAD +
												1,
                                    STARTCOLUMN_HOR +
                                    dec_value +
                                    _value,
                                    HEIGTH_HOR -
                                    1,
                                    dec_memoValue +
                                    memoValue -
                                    dec_value -
                                    _value, 
                                    0,
                                    GetPage());
      }

		/* Effacement curseur Pmax */
		if (memoPmax > 0)
      {
			if (memoPmax < _value)
         {
				InterfaceCppC::DisplayLine (  STARTLINE_HOR + 
														LONG_GRAD + 
														1,
                                          STARTCOLUMN_HOR + 
                                          memoPmax,
                                          HEIGTH_HOR - 
                                          1, 
                                          0, 
                                          1,
                                          GetPage());
         }
			else
         {
				InterfaceCppC::DisplayLine (  STARTLINE_HOR + 
														LONG_GRAD + 
														1,
                                          STARTCOLUMN_HOR + 
                                          memoPmax,
                                          HEIGTH_HOR - 
                                          1, 
                                          0, 
                                          0,
                                          GetPage());
         }
      }

		/*%C Affichage curseur Pmax */
		if (_Pmax > 0)
      {
         if (_Pmax < _value)
         {
			   InterfaceCppC::DisplayLine (  STARTLINE_HOR + 
			   										LONG_GRAD + 
			   										1,
                                          STARTCOLUMN_HOR + 
                                          _Pmax,
                                          HEIGTH_HOR - 
                                          1, 
                                          0, 
                                          0,
                                          GetPage());
         }
			else
         {
			   InterfaceCppC::DisplayLine (  STARTLINE_HOR + 
			   										LONG_GRAD + 
			   										1,
                                          STARTCOLUMN_HOR + 
                                          _Pmax,
                                          HEIGTH_HOR - 
                                          1, 
                                          0, 
                                          1,
                                          GetPage());
         }
      }

		/*%C Effacement curseur Pep */
		if (memoPep > 0)
      {
		  	if (memoPep < _value)
         {
			   InterfaceCppC::DisplayLine (  STARTLINE_HOR + 
			   										LONG_GRAD + 
			   										1,
                                          STARTCOLUMN_HOR + 
                                          memoPep,
                                          HEIGTH_HOR - 
                                          1, 
                                          0, 
                                          1,
                                          GetPage());
         }
		   else
         {
		      InterfaceCppC::DisplayLine (  STARTLINE_HOR + 
		      										LONG_GRAD + 
		      										1,
                                          STARTCOLUMN_HOR + 
                                          memoPep,
                                          HEIGTH_HOR - 
                                          1, 
                                          0,
                                          0,
                                          GetPage());
         }
      }

		/*%C Affichage curseur Pmax */
		if (_Pep > 0)
		{
		   if (_Pep < _value)
         {
		      InterfaceCppC::DisplayLine (  STARTLINE_HOR + 
		      										LONG_GRAD + 
		      										1,
                                          STARTCOLUMN_HOR + 
                                          _Pep,
                                          HEIGTH_HOR - 
                                          1, 
                                          0, 
                                          0,
                                          GetPage());
         }
		   else
         {
			   InterfaceCppC::DisplayLine (  STARTLINE_HOR + 
			   										LONG_GRAD + 
			   										1,
                                          STARTCOLUMN_HOR + 
                                          _Pep,
                                          HEIGTH_HOR - 
                                          1, 
                                          0, 
                                          1,
                                          GetPage());
         }
      }
   }

	/*%C Mémorisation de la valeur */
	memoValue = _value;
	memoPep = _Pep;
	memoPmax = _Pmax;
}
