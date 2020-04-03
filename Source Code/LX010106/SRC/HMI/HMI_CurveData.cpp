/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_CurveData.cpp                                     			*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Calcul des paramètres de courbes        											*/
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_CurveData.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                	   		*/
/******************************************************************************/

#include "HMI_DataBaseAccess.hpp"
#include <math.h>

extern "C"
{
#include "DB_Config.h"
#include "DB_Compute.h"
}

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
CurveData::CurveData()
{
   Construct();
}
/*----------------------------------------------------------------------------*/
void CurveData::Construct()
{
   Init(NULL,NULL);
   OutOfLimitDis = FALSE;
}
/*----------------------------------------------------------------------------*/
CurveData::CurveData(Scale *_Ex,Scale *_Ey)
{
	Init(_Ex,_Ey);
}
/*----------------------------------------------------------------------------*/
 void CurveData::Init(Scale *_Ex,Scale *_Ey)
{
	Ex = _Ex;
	Ey = _Ey;
	InitDbAccess(NO_ID,COMPUTE,NO_ID,COMPUTE);
	ResetValue();
	ResetMinMax();
}
/*----------------------------------------------------------------------------*/
void CurveData::InitDbAccess( UWORD16 _IdParamX, 
										e_TYPE_OF_DB_TARGET _DbTargetX,
                              UWORD16 _IdParamY, 
                              e_TYPE_OF_DB_TARGET _DbTargetY)
{
	DBx.SetIdParam(_IdParamX);
	DBx.SetDbTarget(_DbTargetX);
	DBy.SetIdParam(_IdParamY);
	DBy.SetDbTarget(_DbTargetY);
}
/*----------------------------------------------------------------------------*/
void CurveData::InitDbAccess(	UWORD16 _IdParamY, 
										e_TYPE_OF_DB_TARGET _DbTargetY)
{
	DBy.SetIdParam(_IdParamY);
	DBy.SetDbTarget(_DbTargetY);
	DBx.SetIdParam(NO_ID);
	DBx.SetDbTarget(COMPUTE);
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void CurveData::SetScale(Scale *_Ex,Scale *_Ey)
{
	Ex = _Ex;
	Ey = _Ey;
	ResetMinMax();
	PreviousPoint.Init(0,0);
	CurrentPoint.Init(0,0);
}
/*----------------------------------------------------------------------------*/
void CurveData::SetCurveStart(e_BOOL _start)
{
	CurveStart = _start;
}
/*----------------------------------------------------------------------------*/
e_BOOL CurveData::IsCurveStart(void)
{
    return CurveStart;
}
/*----------------------------------------------------------------------------*/
Pen* CurveData::GetPen()
{
	return  &this->LocalPen;
}
/*----------------------------------------------------------------------------*/
SWORD16 CurveData::GetMaxX()
{
   return MaxX;
}
/*----------------------------------------------------------------------------*/
void CurveData::SetMaxX(SWORD16 _MaxX)
{
   MaxX = _MaxX;
}
/*----------------------------------------------------------------------------*/
SWORD16 CurveData::GetMaxY()
{
   return MaxY;
}
/*----------------------------------------------------------------------------*/
SWORD16 CurveData::GetMinX()
{
   return MinX;
}
/*----------------------------------------------------------------------------*/
SWORD16 CurveData::GetMinY()
{
   return MinY;
}
/*----------------------------------------------------------------------------*/
VPoint& CurveData::GetPreviousPoint()
{
   return PreviousPoint;
}
/*----------------------------------------------------------------------------*/
VPoint& CurveData::GetCurrentPoint()
{
   return CurrentPoint;
}
/*----------------------------------------------------------------------------*/
Scale* CurveData::GetScaleX()
{
   return Ex;
}
/*----------------------------------------------------------------------------*/
Scale* CurveData::GetScaleY()
{
   return Ey;
}
/*----------------------------------------------------------------------------*/
e_BOOL CurveData::GetOutOfLimitDis()
{
   return OutOfLimitDis;
}
/*----------------------------------------------------------------------------*/
UWORD16 CurveData::GetIdParamY()
{
   return(DBy.GetIdParam());
}
/*----------------------------------------------------------------------------*/
e_TYPE_OF_DB_TARGET CurveData::GetDbTargetY()
{
   return(DBy.GetDbTarget());
}
/******************************************************************************/
/*                           METHODES                					      	   */
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affectation des paramètres																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		X : abscisses																			*/
/*%I		Y : ordonnées																			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void CurveData::StoreNewPoint(SWORD16 _X,SWORD16 _Y)
{
	if(_X>MaxX)
	{
		MaxX = _X;
	}
	else if(_X<MinX) 
	{
		MinX = _X;
	}

	if(_Y>MaxY) 
	{
		MaxY = _Y;
	}
	else if(_Y<MinY) 
	{
		MinY = _Y;
	}

   PreviousPoint = CurrentPoint;
	CurrentPoint.Init(_X,_Y);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Reset paramètres																			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void CurveData::ResetMinMax()
{
	/*%C Reset parameters */
	MaxX = 0;
	MaxY = 0;
	MinX = 0;
	MinY = 0;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Reset valeurs																				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void CurveData::ResetValue()
{
	PreviousPoint.Init(0,0);
	CurrentPoint.Init(0,0);
	JustReset = TRUE;
	SetCurveStart(TRUE);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Refresh																						*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I 		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/

void CurveData::Refresh()
{
	SWORD16 	SValueX,
				SValueY, 
				ComputedPep;

 	UWORD16 Style;

   /*%C Lecture du Style (Boucle / Pression-Débit) dans la DataBase */
   DataBaseAccess::ReadValue(&Style, CURVE_DISPLAY_TYPE_MODE_U16,CONFIG);
   
   /*%C Lecture de la valeur de la Pep pour initialiser les courbes Wob */
   DataBaseAccess::ReadValue((UWORD16*)&ComputedPep, COMPUTED_PEEP_U16,COMPUTE);

	SValueX = 0;
	SValueY = 0;
   
   if(DBx.GetIdParam() != NO_ID)
	{
		DataBaseAccess::ReadValue(	(UWORD16*)&SValueX, 
											DBx.GetIdParam(), 
											DBx.GetDbTarget());
   }

   DataBaseAccess::ReadValue(	(UWORD16*)&SValueY,
										DBy.GetIdParam(),
	   								DBy.GetDbTarget());

   StoreNewPoint(	SValueX,
						SValueY);

   /*%C Si on est pas hors limites - Effacement "Hors Limites" */
   if(SValueY <= GetScaleY()->GetMax())
   {
	  OutOfLimitDis = FALSE;
   }
   else
	   OutOfLimitDis = TRUE;
	   
   /*%C RAZ de la valeur d'init si on n'est pas en Wob */
	if(JustReset)
   {
		/*%C Exclusion */
		JustReset = FALSE;
		/*%C  Si on n'est pas en courbe Wob */
		if(Style == 0)
	  {
			/*%C dans le cas d'un reset la valeur precedante n'est pas valide */
			StoreNewPoint(SValueX,SValueY);
		 //Si on est hors limites - affichage "Hors Limites"
/*		  if(MinY < GetScaleY()->GetMax())
		 {
			OutOfLimitDis = TRUE;
         }*/
      }
		else
      {
			/*%C On refresh le graph Press/Vt */
			/*%C On démarre le prochain cycle de la valeur de la Pep */
			if(DBy.GetIdParam() == FILTER_PATIENT_PRESSURE_S16)
			{
				CurrentPoint.Init(0,ComputedPep*10);
			}
			else
			{
				CurrentPoint.Init(0,0);
			}
			PreviousPoint = CurrentPoint;
		}
	}
	if(GetPen()->IsDotted())GetPen()->SwapDottedState();
}

