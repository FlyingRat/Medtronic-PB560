/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_Scale.cpp 											 						*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Echelle des courbes	 													 			  	*/
/*		                                                                   	 	*/
/******************************************************************************/


/******************************************************************************/
/*                           HEADER INCLUDE FILE		                        */
/******************************************************************************/

#include "HMI_Scale.hpp"
				 
/******************************************************************************/
/*                           OTHER INCLUDE FILE		                	   		*/
/******************************************************************************/

#include "HMI_InterfaceCppC.hpp"
#include "HMI_Tools.hpp"
#include "HMI_DataBaseAccess.hpp"

extern "C"
{
#include "DB_Config.h"
}

/******************************************************************************/
/*                           CONSTANT DECLARATION		                			*/
/******************************************************************************/
  
#define LEFT_MARGIN			3
#define BOTTOM_MARGIN		10

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
Scale::Scale()
{
   Init(0,0,0,0,0,0,0,eHOR,FONT_2);
	Heigth = 3;
	AutoScale = FALSE;
	TickVisible = TRUE;
	DoubleTick = FALSE;
	NumberVisible = TRUE;
	Pas = 10;
	Symetric = FALSE;
	NumberSide = eBOTTOM;
	FirstRefresh = TRUE;
}
/*----------------------------------------------------------------------------*/
void Scale::Init( UWORD16 _Line,
                  UWORD16 _Col,
                  SWORD16 _Min,
                  SWORD16 _Max,
                  UWORD16 _MajorTickSpacing,
                  UWORD16 _Width,
                  UWORD16 _ZeroPos,
                  TOrientation _Orientation,
                  UWORD16 _Font)
{
	FieldObject::Init(_Line,_Col,_Font,FALSE);
	Min = (SWORD32)_Min;
	Max = (SWORD32)_Max;
	Width = (SWORD32)_Width;
   Orientation = _Orientation;
	ZeroPos = _ZeroPos;
	SetMajorTickSpacing((SWORD32)_MajorTickSpacing);
}
/*----------------------------------------------------------------------------*/
void Scale::InitDbAccess(UWORD16 _IdMax, e_TYPE_OF_DB_TARGET _DbMax)
{
	DBMax.SetIdParam(_IdMax);
   DBMax.SetDbTarget(_DbMax);
}
/*----------------------------------------------------------------------------*/
UWORD16 Scale::GetIdMax()
{
   return(DBMax.GetIdParam());
}
/*----------------------------------------------------------------------------*/
e_TYPE_OF_DB_TARGET Scale::GetDbMax()
{
   return(DBMax.GetDbTarget());
}
/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
UWORD16 Scale::GetZeroPos()
{
	return ZeroPos;
}
/*----------------------------------------------------------------------------*/
e_BOOL Scale::IsAutoScale()
{
	UWORD16 Value;
	DataBaseAccess::ReadValue(&Value, DBMax.GetIdParam(), DBMax.GetDbTarget());

	return (e_BOOL) ((Value == 0) || (AutoScale));
}

/*----------------------------------------------------------------------------*/
void Scale::SetSymetric(e_BOOL _Symetric)
{
   Symetric = _Symetric;
}
/*----------------------------------------------------------------------------*/
e_BOOL Scale::GetSymetric()
{
   return(Symetric);
}
/*----------------------------------------------------------------------------*/
SWORD32 Scale::GetMin()
{
	return Min;
}
/*----------------------------------------------------------------------------*/
SWORD32 Scale::GetMax()
{
	return Max;
}
/*----------------------------------------------------------------------------*/
SWORD32 Scale::GetWidth()
{
	return Width;
}
/*----------------------------------------------------------------------------*/
void Scale::SetMajorTickSpacing(SWORD32 _MajorTickSpacing)
{
	if(_MajorTickSpacing == 0) 
	{
		_MajorTickSpacing =1;
	}
   MajorTickSpacing = _MajorTickSpacing;

	/*%C calcul de la position du premier Tick */
	SWORD16 PosTmp = GetZeroPos();
	do
   {
		FirstX = PosTmp;
		PosTmp -= (SWORD16)GetMajorTickSpacing();
	}
   while(PosTmp>=0);
}
/*----------------------------------------------------------------------------*/
SWORD32 Scale::GetMajorTickSpacing()
{
	return MajorTickSpacing;
}

/******************************************************************************/
/*                           METHODES                					      		*/
/******************************************************************************/
void Scale::ManagePas()
{
	SWORD32 Nbtick;
	SWORD32 CurrentValue;

	/*%C Calcul des valeurs courantes */
	SWORD32 _Max = Max;
  	SWORD32 _Min = Min;
	SWORD32 PositiveLength = Width - ZeroPos;
	SWORD32 NegativeLength = ZeroPos;
	SWORD32 PositiveNbTick = PositiveLength/MajorTickSpacing;
	SWORD32 NegativeNbTick = NegativeLength/MajorTickSpacing;
	SWORD32 PositivePas =   PositiveNbTick?(SWORD16)
                           (Tools::Abs(_Max/PositiveNbTick)):0;
	SWORD32 NegativePas =   NegativeNbTick?(SWORD16)
                           (Tools::Abs(_Min/NegativeNbTick)):0;
	SWORD32 Temp;

	/*%C Determination du Pas */
	if(PositivePas>=NegativePas)
   {
		/*%C le cote positif est limitateur */
		Nbtick = PositiveNbTick;
		CurrentValue = _Max;
	}
	else
   {
		/*%C le cote negatif est limitateur */
		Nbtick = NegativeNbTick;
		CurrentValue = _Min;
	}

   /*%C Enlève un espace */
   if(this->Orientation == eHOR)
   if(PositiveNbTick > 0)
   {
      PositiveNbTick--;
      Nbtick--;
   }
	/*%C Calcul temporaire */
	Temp = ((SWORD32)CurrentValue*10)/(SWORD32)Nbtick;
	/*%C Prend une valeur entière pour CurrentValue/NbTick (arrondi supérieur) */
 	if( ((10*CurrentValue)%Nbtick) != 0 )
	{
    	Pas = Tools::Abs(Temp) + 1;
	}
   else
	{
  	 	Pas = Tools::Abs(Temp);
	}

	/*%C correction des valeurs Min Max */
	Temp = -(Pas*(SWORD32)NegativeNbTick)/10;
	Min = (SWORD16)Temp;
	Temp = (Pas*(SWORD32)PositiveNbTick)/10;
	Max = (SWORD16)Temp;
}
/*----------------------------------------------------------------------------*/
e_BOOL Scale::ManageAutoScale(CurveData **_CurveTable, UWORD16 _NbCurve)
{
	e_BOOL ValueChange = FALSE;
	Scale *Ech;
	SWORD32 _Min,_Max,RealMax=0,NewMax;
   UWORD16 Wob;
   /*%C  Réajustmeent d'unité (*10) */
   UWORD16 Round = DataBaseAccess::GetStep(  DBMax.GetIdParam(),
                                             DBMax.GetDbTarget()) * 10;

   DataBaseAccess::ReadValue(&Wob,CURVE_DISPLAY_TYPE_MODE_U16,CONFIG);

	NewMax = Max;

	/*%C Loop sur les courbes pour rechercher les min et max du der affichage */
	for(UWORD16 i=0; i<_NbCurve; i++)
   {
		if(_CurveTable[i] != NULL)
      {
			/*%C Loop sur les Scales */
			for(UWORD16 j = 0; j<2; j++)
         {
				/*%C Affectation de l'échelle X ou Y */
				if(j==0)
            {
					Ech = _CurveTable[i]->GetScaleX();
					_Min = _CurveTable[i]->GetMinX();
					_Max = _CurveTable[i]->GetMaxX();
				}
				else
            {
					Ech = _CurveTable[i]->GetScaleY();
					_Min = _CurveTable[i]->GetMinY();
					_Max = _CurveTable[i]->GetMaxY();
				}

         /*%C Test sur l'échelle courante */
			if(Ech == this)
         {
            /*%C Enregistre le min et le max de la première courbe */
				if(i==0)
            {
               RealMax = _Max>Tools::Abs(_Min) ? _Max : Tools::Abs(_Min);
            }
            /*%C Teste les min et max des autres courbes */
				else
            {
               if(RealMax<Tools::Abs(_Min))
				      RealMax = Tools::Abs(_Min);
               if(RealMax<_Max)
	   				RealMax = _Max;
               }
            }
         }
      }
      else
         break;
   }


	//Filtre des valeurs
	//-------------------------------------------------------CurrentMax
	//                           |
	//                           |
	//                      Current Value
	//                           |
	//                           |
	//-------------------------------------------------------CurrentMax-10%
	//La valeur courante peut se deplacer entre CurrentMax
	//et CurrentMax-10% sans remise a l'échelle

	//---------------------------------------------------NewMax+10% = CurrentMax
	//
	//
	//-------------------------------------------------------NewMax
	//                      Current Value
	//-------------------------------------------------------CurrentMax-10%
	//dans le cas ou la valeur et hors borne, on ajuste la nouvelle borne
	// a +10% pour stabiliser la mise a l'échelle

	if(Orientation == eHOR)
   {
      /*%C Si on est en WOB */
      if (Wob == TRUE)
      {
	      /*%C On calcule le nouveau max de l'échelle*/
         NewMax = (RealMax*11) / 10;
	      /*%C On arrondi au dessus */
         NewMax = (NewMax + Round) - (NewMax%Round);
      }
      else
      {
         /*%C On arrondi au dessus */
         NewMax = (RealMax + Round) - (RealMax%Round);
         /*%C On incrémente d'un step */
    	   NewMax = (NewMax + Round) - (NewMax%Round);
      }
   }
   else
   {
	   /*%C On calcule le nouveau max de l'échelle */
   	NewMax = (RealMax*11) / 10;
	   /*%C On arrondi au dessus */
    	NewMax = (NewMax + Round) - (NewMax%Round);
   }

   if(NewMax > (SWORD32)(DataBaseAccess::GetMax(DBMax.GetIdParam(),
                                                DBMax.GetDbTarget()) * 10))
   {
      NewMax = DataBaseAccess::GetMax( DBMax.GetIdParam(),
                                       DBMax.GetDbTarget()) * 10;
   }

   if(NewMax < (SWORD32)(DataBaseAccess::GetMin(DBMax.GetIdParam(),
                                                DBMax.GetDbTarget()) * 10))
   {
      NewMax = DataBaseAccess::GetMin( DBMax.GetIdParam(),
                                       DBMax.GetDbTarget()) * 10;
   }

   /*%C Si le nouveau max est à plus ou moins de 10% du max de l'échelle */
	if( (NewMax < (Max*9/10)) || (NewMax > (Max*11/10)) )
   {
    	Max = NewMax;
      ValueChange = TRUE;
   }

   /*%C Gestion de la Symetrie */
	if(Symetric)
		Min = -Max;

	return ValueChange;
}
/*----------------------------------------------------------------------------*/
void Scale::RefreshValue()
{
	UWORD16 Value;
	DataBaseAccess::ReadValue(&Value, DBMax.GetIdParam(), DBMax.GetDbTarget());
	Max = Value * 10;		/*%C x10 corrige l'unité utilisée */
	Min = 0;
}
/*----------------------------------------------------------------------------*/
void Scale::Refresh()
{
	/*%C Link to Graphic Object */
	UWORD16 ColTmp, LineTmp;
	LineTmp = GetLine();
	ColTmp = GetCol();
	SWORD16 PosTick = NumberSide==eBOTTOM?1:-1;

   /*%C MAJ Valeur Min Max DataBase */
	if(!IsAutoScale())
   {
		RefreshValue();
	}

	ManagePas();

	if(Orientation == eHOR)
   {
		/*%C Affichage Tick */
		UWORD16 j=0;
		for(UWORD16 i=ColTmp+FirstX; i<=ColTmp+Width-20; i+=(UWORD16)MajorTickSpacing,j++)
      {
			if(TickVisible)
         {
				InterfaceCppC::DisplayLine(LineTmp,
                                       i,
                                       PosTick*Heigth,
                                       0,
                                       1,
                                       GetPage());
				if(DoubleTick)
            {
					InterfaceCppC::DisplayLine(LineTmp,
                                          i,
                                          -1*PosTick*Heigth,
                                          0,
                                          1,
                                          GetPage());
				}
			}
			/*% Cffichage du nombre un coup sur deux */
			if(NumberVisible && !(j%2))
         {
				/*%C gestion de la position des nombres */
				SWORD32 FValue = Min+(Pas*j)/10;
				e_BOOL ValueIsDecimal = Tools::IsFloat(FValue);
				SWORD32 Value = (SWORD32)(ValueIsDecimal?FValue:FValue/10);

				/*%C Ligne des nombres */
				UWORD16 NumberLine = 0;
				if(NumberSide == eBOTTOM)
            {
					NumberLine = LineTmp + BOTTOM_MARGIN;
				}
				else
            {
					NumberLine = LineTmp - BOTTOM_MARGIN;
				}

				InterfaceCppC::DisplayNumber( Value,
         										   ValueIsDecimal?1:0,
										            FALSE,
										            NumberLine,
										            i+3,
										            GetFont(),
										            0,
										            FALSE,
										            1,
										            GetPage());
         }
		}
      /*%C Affichage de l'axe */
		InterfaceCppC::DisplayLine(LineTmp, ColTmp,0, Width,1,GetPage());
		/*%C Affichage de la flèche */
		InterfaceCppC::DisplaySymbol( FLECHE_GRAPH_DROITE,
                                    LineTmp-2,
                                    ColTmp+Width-4,
                                    GetPage());


	}
	else
   {
   /*%C Vertical */
   /*% Caffichage Tick */
   UWORD16 j=0;
	for(  SWORD16 i=LineTmp-FirstX;
         (i>=(SWORD16)(LineTmp-Width)) && (i>=0); i-=(UWORD16)MajorTickSpacing,
         j++)
   {
	   if(TickVisible)
      {
				InterfaceCppC::DisplayLine(i, 
													ColTmp,
													0,
													-1*PosTick*Heigth,
													1,
													GetPage());
				if(DoubleTick)
            {
					InterfaceCppC::DisplayLine(i,
														ColTmp,
														0,
														PosTick*Heigth,
														1,
														GetPage());
				}
			}
			/*%C affichage du nombre un coup sur deux */
			if(NumberVisible && !(j%2))
         {
				/*%C gestion de la position des nombres */
            /*%C Pas est 10 fois plus précis */
				SWORD32 FValue = Min+(Pas*j)/10;
				e_BOOL IsFloat = Tools::IsFloat(FValue);
				SWORD32 Value = (SWORD32)(IsFloat?FValue:FValue/10);

				SWORD16 OffsetColNumber = 0;
            /*%C Calcul de la taille en pixel */
               	OffsetColNumber = Tools::GetNumberPixelSize((UWORD16)
                                    (Tools::Abs(Value)), GetFont(), IsFloat);
            /*%C Correction negatif */
				if(Value<0)
               OffsetColNumber += Tools::GetStringPixelSize((UBYTE *)"-", GetFont());

            InterfaceCppC::DisplayNumber( Value,
                     							IsFloat?1:0,
						      				   	FALSE,
								      		   	i+5,
      										   	ColTmp - 
      										   	OffsetColNumber - 
      										   	LEFT_MARGIN,
		      								   	GetFont(),
				      						   	0,
						      				   	FALSE,
								      		   	1,
										         	GetPage());
			}
		}
		/*%C affichage de l'axe */
		InterfaceCppC::DisplayLine(LineTmp-GetWidth(), 
											ColTmp,GetWidth(),
											0,
											1,
											GetPage());

		/*%C Affichage de la flèche */
		InterfaceCppC::DisplaySymbol( FLECHE_GRAPH_HAUT,
                                    LineTmp-GetWidth(),
                                    ColTmp - 2,
                                    GetPage());
	}
}
/*----------------------------------------------------------------------------*/
UWORD16 Scale::ValToPoint(SWORD32 _Val)
{
	UWORD16 Point;
	UWORD16 ZeroLength;

	ZeroLength = (SWORD16)(Tools::Abs(Min-_Val));
	if(Orientation == eHOR)
   {
		/*%C calcul de la colonne */
		Point = (UWORD16)(GetCol()+
               FirstX +
               (SWORD32)(((SWORD32)ZeroLength*(SWORD32)MajorTickSpacing*
               (SWORD32)10)/(SWORD32)Pas));
	}
	else
   {
		/*%C calcul de la ligne */
		Point  = (UWORD16)(  GetLine()-
               FirstX-
               (SWORD32)(((SWORD32)ZeroLength*(SWORD32)MajorTickSpacing*
               (UWORD32)10)/(SWORD32)Pas));
	}

	return Point;
}
/*----------------------------------------------------------------------------*/
void Scale::Show()
{
	DisplayObject::Show();

	/*%C Initialisation des valeur sur le 1er Show */
	if((FirstRefresh) && (!IsAutoScale()))
   {
		RefreshValue();
		FirstRefresh = FALSE;
   }
	/*%C refresh de l'affichage */
	Refresh();
}
/*----------------------------------------------------------------------------*/
void Scale::Hide()
{
	if(this->Orientation == eHOR){
		InterfaceCppC::EraseZone(  GetLine(),
							   	      GetCol(),
							   	      12,
      								   Width-7,
                                 0,
                                 GetPage());
	}
	else
   {
		InterfaceCppC::EraseZone(  GetLine()-Width+7,
							   	      GetCol()-30,   
							   	      Width,
								         30,
                                 0,
                                 GetPage());
	}
}

