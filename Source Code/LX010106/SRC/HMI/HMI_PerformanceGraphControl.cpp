/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_PerformanceGraphControl.cpp 		 	  		 						*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Pen parameters															 					*/
/*		                                                                   	 	*/
/******************************************************************************/


/******************************************************************************/
/*                           HEADER INCLUDE FILE		                        */
/******************************************************************************/

#include "HMI_PerformanceGraphControl.hpp"
				 
/******************************************************************************/
/*                           OTHER INCLUDE FILE		                	   		*/
/******************************************************************************/


#include "HMI_DataBaseAccess.hpp"
extern "C"
{
#include "DB_Compute.h"
}

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
PerformanceGraphControl::PerformanceGraphControl()
{
   Construct();
}
/*----------------------------------------------------------------------------*/
void PerformanceGraphControl::Construct()
{
   RefreshTime = 0;
   CurrentTime = 0;
}
/*----------------------------------------------------------------------------*/
void PerformanceGraphControl::InitRefreshTime(UWORD16 _RefreshTime)
{
   SetRefreshTime(_RefreshTime);
}
/*----------------------------------------------------------------------------*/
void PerformanceGraphControl::SetRefreshTime(UWORD16 _RefreshTime)
{
   RefreshTime = _RefreshTime;
}
/*----------------------------------------------------------------------------*/
UWORD16 PerformanceGraphControl::GetRefreshTime()
{
   return(RefreshTime);
}
/*----------------------------------------------------------------------------*/
void PerformanceGraphControl::SetGraphTarget(Graph* _GraphTarget)
{
   GraphControl::SetGraphTarget(_GraphTarget);
   CurrentTime = _GraphTarget->GetScaleX()->GetMin();
}
/*----------------------------------------------------------------------------*/
void PerformanceGraphControl::ManageGraph()
{
	Graph *GraphTarget = GetGraphTarget();
	CurveData** CurveTable = GraphTarget->GetCurveTable();

	/*%C On affiche 25% de temps en plus de la valeur max */
	UWORD16 MaxTime = GraphTarget->GetScaleX()->GetMax() * 12 / 10;
	/*%C Limitation du WORD16 */
	if(MaxTime > 650) MaxTime = 650;
   /*%C Lecture de la fréquence actuelle */
	UWORD16 Freq;
	DataBaseAccess::ReadValue(&Freq, MEASURE_R_U16, COMPUTE);
	if(Freq != 0)
		CurveTable[0]->SetMaxX(1200/Freq);
	else
		CurveTable[0]->SetMaxX(1200/12);

	if((CurrentTime/100) > MaxTime)
   {
      GraphTarget->Reset();
		CurrentTime = GraphTarget->GetScaleX()->GetMin();
		for(UWORD16 i=0; i<GraphTarget->GetCurveNumber(); i++)
      {
			if(CurveTable[i] != NULL)
         {
				CurveTable[i]->GetPreviousPoint().SetY
                           (CurveTable[i]->GetPreviousPoint().GetY());
				CurveTable[i]->GetPreviousPoint().SetX
                           (GraphTarget->GetScaleX()->GetMin());
			}
		}
	}

	for(UWORD16 i=0; i<GraphTarget->GetCurveNumber(); i++)
   {
		if(CurveTable[i] != NULL)
      {
			CurveTable[i]->GetCurrentPoint().SetX(CurrentTime/100);
		}
	}
   CurrentTime += RefreshTime;
}
/*----------------------------------------------------------------------------*/
void PerformanceGraphControl::Reset()
{
	CurrentTime = 0;
}
