/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_Graph.cpp	                                 					*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Construction des graphique														      */
/*		                                                                        */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_Graph.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/


#include "HMI_InterfaceCppC.hpp"
#include "HMI_Tools.hpp"
#include "HMI_DatabaseAccess.hpp"
#include "HMI_Label.hpp"
extern "C"
{
#include "DB_Config.h"
}

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

#define LEFT_SPACE		30
#define RIGHT_SPACE		5
//#define RIGHT_SPACE		15
#define BOTTOM_SPACE	   14
#define TOP_SPACE		   0

TKind Graph::Kind = eLINE;

//extern UWORD16 Language;

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/

Graph::Graph()
{
   Construct();
}
/*----------------------------------------------------------------------------*/
void Graph::Construct()
{
	Init(0,0,0,0,0,0,0,0,0,0,0,0,FONT_2,NULL,NULL,NULL);

   CurveTable[0] = NULL;
   TUnit1 = NULL;
   TUnit2 = NULL;
   TOutOfLimit = NULL;
   OutOfLimit = FALSE;
}
/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void Graph::Init(	UWORD16 Line, 
						UWORD16 Col,
						UWORD16 Height, 
						UWORD16 Width,
                	SWORD16 MinX,
                	SWORD16 MaxX,
                	UWORD16 ZeroPosX,
                	UWORD16 MajorTickSpacingX,
                	SWORD16 MinY,
                	SWORD16 MaxY,
                	UWORD16 ZeroPosY,
                	UWORD16 MajorTickSpacingY,
                	UWORD16 Font, 
                	UBYTE **Unit1, 
                	UBYTE **Unit2, 
                	UBYTE **OutOfLimit)
{

	e_BOOL _IsVisibleLabelX;
	e_BOOL _IsVisibleLabelY;
      
	UWORD16 WidthX = Width - LEFT_SPACE - RIGHT_SPACE;
	UWORD16 WidthY = Height - BOTTOM_SPACE - TOP_SPACE;

	SetKind(eLINE);
	SetGControl(NULL);
	SetCurveNumber(0);

	GraphicBox::Init(	Line,
							Col,
							Height,
							Width,
							FALSE,
							FALSE,
							TRUE);

	ScaleX.SetParent(this);

	ScaleX.Init(Line-BOTTOM_SPACE,
					Col+LEFT_SPACE,
					MinX,
					MaxX,
					MajorTickSpacingX,
					WidthX,
					ZeroPosX,
					eHOR,
					Font);

	ScaleY.SetParent(this);

	ScaleY.Init(Line-BOTTOM_SPACE,
					Col+LEFT_SPACE,
					MinY,
					MaxY,
					MajorTickSpacingY,
					WidthY,
					ZeroPosY,
					eVERT,
					Font);

	LabelX.SetParent(this);
   _IsVisibleLabelX = LabelX.IsVisible();
   LabelX.SetVisible(FALSE);
   SetTUnit1(Unit1);
   LabelX.SetVisible(_IsVisibleLabelX);

   LabelX.Init(-4,
   				Width - Tools::GetStringPixelSize(GetTUnit1(),Font),
   				Font,
   				FALSE,
   				GetTUnit1());

	LabelY.SetParent(this);
   _IsVisibleLabelY = LabelY.IsVisible();
   LabelY.SetVisible(FALSE);
   SetTUnit2(Unit2);
   LabelY.SetVisible(_IsVisibleLabelY);

   LabelY.Init(7-Height,
   				41,
   				Font,
   				FALSE,
   				GetTUnit2());

	LabelOOL.SetParent(this);
   SetTOutOfLimit(OutOfLimit);
   LabelOOL.Init(	-50, 
   					(LEFT_SPACE + 
   					(Width - 
   					Tools::GetStringPixelSize(GetTOutOfLimit(),Font)))/2, 
   					Font, 
   					FALSE,
   					GetTOutOfLimit());

}
/*----------------------------------------------------------------------------*/
Scale* Graph::GetScaleX()
{
	return &this->ScaleX;
}
/*----------------------------------------------------------------------------*/
TextField* Graph::GetLabelX()
{
   return &this->LabelX;
}   
/*----------------------------------------------------------------------------*/
Scale* Graph::GetScaleY()
{
	return &this->ScaleY;
}
/*----------------------------------------------------------------------------*/
void Graph::SetTUnit1(UBYTE** Name)
{
	TUnit1 = Name;
	LabelX.SetText(GetTUnit1());
}
/*----------------------------------------------------------------------------*/
void Graph::SetTUnit2(UBYTE** Name)
{
	TUnit2 = Name;
	LabelY.SetText(GetTUnit2());
}
/*----------------------------------------------------------------------------*/
void Graph::SetTOutOfLimit(UBYTE** Name)
{
   TOutOfLimit = Name;
	LabelOOL.SetText(GetTOutOfLimit());
}
/*----------------------------------------------------------------------------*/
UBYTE* Graph::GetTUnit1()
{
	if(this->TUnit1 != NULL)
   {
		return (TUnit1[GetLanguage()]);
	}
	else
	{
		return (UBYTE *)"";
	}
}
/*----------------------------------------------------------------------------*/
UBYTE** Graph::GetTUnit1Ptr()
{
   return(TUnit1);
}
/*----------------------------------------------------------------------------*/
UBYTE** Graph::GetTUnit2Ptr()
{
   return(TUnit2);
}
/*----------------------------------------------------------------------------*/
UBYTE** Graph::GetTOutOfLimitPtr()
{
   return(TOutOfLimit);
}
/*----------------------------------------------------------------------------*/
UBYTE* Graph::GetTUnit2()
{
	if(TUnit2 != NULL)
	{
		return (TUnit2[GetLanguage()]);
	}
	else 
	{			        
      return (UBYTE *)"";
	}
}
/*----------------------------------------------------------------------------*/
UBYTE* Graph::GetTOutOfLimit()
{
	if(TOutOfLimit != NULL)
	{
		return (TOutOfLimit[GetLanguage()]);
	}
	else 
	{
		return (UBYTE *)"";
	}
}
/*----------------------------------------------------------------------------*/
CurveData** Graph::GetCurveTable()
{
	return CurveTable;
}
/*----------------------------------------------------------------------------*/
void Graph::SetCurveNumber(UWORD16 _CurveNumber)
{
	CurveNumber = _CurveNumber;
}
/*----------------------------------------------------------------------------*/
UWORD16 Graph::GetCurveNumber()
{
	return CurveNumber;
}
/*----------------------------------------------------------------------------*/
void Graph::SetKind(TKind _Kind)
{
   Graph::Kind = _Kind;
}
/*----------------------------------------------------------------------------*/
TKind Graph::GetKind()
{
	return Graph::Kind;
}
/*----------------------------------------------------------------------------*/
void Graph::SetGControl(GraphControl *_GControl)
{
	GControl = _GControl;
   if(GControl != NULL)
   {
   	GControl->SetGraphTarget(this);
	}
}
/*----------------------------------------------------------------------------*/
GraphControl * Graph::GetGControl()
{
	return(GControl);
}
/*----------------------------------------------------------------------------*/
e_BOOL Graph::HaveGControl()
{
	return (e_BOOL)(GControl != NULL);
}

/******************************************************************************/
/*                           METHODES                					      		*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Gestion du graphique																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void Graph::AddCurve(CurveData *CData)
{
	int i = 0;

	while((CurveTable[i] != NULL) && 
			(CurveTable[i] != CData) && 
			(i<MAX_CURVE))
	{
		i++;
	}
	if((i!=MAX_CURVE) && 
		(CurveTable[i] != CData))
	{
		CurveTable[i] = CData;
		SetCurveNumber(GetCurveNumber()+1);
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Gestion du graphique																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void Graph::RemoveCurve(CurveData *CData)
{
	int i = 0;

	while((	CurveTable[i] != CData) && 
				(i<MAX_CURVE))
	{
		i++;
	}
	if(i!=MAX_CURVE)
	{
		CurveTable[i] = NULL;
		SetCurveNumber(this->GetCurveNumber()-1);
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Gestion du graphique																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
e_BOOL Graph::Contains(VPoint& Point)
{
	e_BOOL B1,B2,B3,B4;

	B1 = (e_BOOL) (Point.GetX()>=ScaleX.GetMin());
	B2 = (e_BOOL) (Point.GetX()<=(ScaleX.GetMax()*(SWORD32)12 / (SWORD32)10));
	B3 = (e_BOOL) (Point.GetY()>=ScaleY.GetMin());
	B4 = (e_BOOL) (Point.GetY()<=ScaleY.GetMax());

	return (e_BOOL)(B1 && B2 && B3 && B4);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Gestion du graphique																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void Graph::DataPoint(CurveData* CData)
{
	enum ePointZone { AllPointOut, 
							PreviousPointOut, 
							CurrentPointOut, 
							AllPointIn };

	ePointZone PointZone;
   VPoint* PointOut=0;
   VPoint* PointIn=0;
	Pixel CurrentPixel;
	Pixel MiddlePixel;
	Pixel PreviousPixel;
   UWORD16 Style;
   SWORD32 	a=0,
   			b=0,
   			x=0,
   			y=0;

	if(!CData->GetPen()->IsDotted() || 
		CData->GetPen()->IsDottedState())
	{

		VPoint CurrentPoint = CData->GetCurrentPoint();
		VPoint MiddlePoint = CData->GetCurrentPoint();
		VPoint PreviousPoint = CData->GetPreviousPoint();

		/*%C Dessine la courbe si le nouveau point a bougé */
      if(CurrentPoint != PreviousPoint)
      {
      	/*%C Cherche le nombre de points qui sont en dehors du cadre */
         if(Contains(CurrentPoint) && 
         	Contains(PreviousPoint))
			{
         	PointZone = AllPointIn;
			}
         else if(Contains(CurrentPoint))
			{
         	PointZone = CurrentPointOut;
            PointOut = &PreviousPoint;
				PointIn = &CurrentPoint;
			}
         else if(Contains(PreviousPoint))
			{
				PointZone = PreviousPointOut;
            PointOut = &CurrentPoint;
				PointIn = &PreviousPoint;
			}
         else
			{
         	PointZone = AllPointOut;
			}

         /*%C Calcule les nouveaux points si au moins un point est en dehors */
         /*%C du cadre*/
			switch(PointZone)
		 	{
				/*%C Un point est dehors */
	        	case CurrentPointOut: 
				case PreviousPointOut:
				/*%C Calcule les coefficients de la courbe ax + b */
				/*%C entre les 2 points */
					if(PointOut->GetX() != PointIn->GetX())  
					{
						/*%C Protection contre la division par zéro */
					   a = 	(SWORD32)100 * 
					    		(PointOut->GetY()-PointIn->GetY()) / 
					    		(PointOut->GetX()-PointIn->GetX());
					}
					else
					{
						a = 0;
					}
				   
				   b = 	(SWORD32)100 * 
				   		PointIn->GetY() - 
				   		a * 
				   		PointIn->GetX();

					/*%C Affichage en trait */
					if(Kind == eLINE)
					{
						/*%C Modifie les coordonnées du point hors cadre */
						/*%C afin qu'il se retrouve à la limite */
						if(PointOut->GetY() > ScaleY.GetMax())
						{
							/*%C Calcule X à partir Y Max */
							y = ScaleY.GetMax();
	   	        	   if(a!=0)
							{
								x = ((SWORD32)100 * y - b) / a;
							}
							else
							{
								x = PointIn->GetX();
							}

							/*%C Si X est hors cadre, on calcule Y à partir de X */
							/*%C Min ou X Max */
							if( x < ScaleX.GetMin() ) 
							{
								x = ScaleX.GetMin();
		                  y = (a * x + b)/(SWORD32)100;
							} 
							else if( x > 	(ScaleX.GetMax()*
												(SWORD32)12/
												(SWORD32)10) ) 
							{
								x = 	ScaleX.GetMax()*
										(SWORD32)12/
										(SWORD32)10;

								y = 	(a * x + b)/
										(SWORD32)100;
							}
						}
						else if(PointOut->GetY() < ScaleY.GetMin())
						{
							/*%C Calcule X à partir Y Max */
                     y = ScaleY.GetMin();
	   	        	   if(a!=0)
							{
								x = ((SWORD32)100 * y - b) / a;
							}
							else
							{
                       	x = PointIn->GetX();
							}
							/*%C Si X est hors cadre */
							/*%C on calcule Y à partir de X Min ou X Max */

							if( x < ScaleX.GetMin() ) 
							{
								x = ScaleX.GetMin();
		               	y = (a * x + b)/(SWORD32)100;
							} 
							else if( x > 	ScaleX.GetMax()*
												(SWORD32)12/
												(SWORD32)10 ) 
							{
								x = 	ScaleX.GetMax()*
										(SWORD32)12/
										(SWORD32)10;

		                  y = 	(a * x + b)/
		                  		(SWORD32)100;
							}
						}
						/*%C X hors cadre on calcule Y à partir de X Min */
                  else if(PointOut->GetX() < ScaleX.GetMin())
						{
							x = ScaleX.GetMin();
	                  y = 	(a * x + b)/
	                  		(SWORD32)100;
						}
    					/*%C X hors cadre on calcule Y à partir de X Max */
                  else if(PointOut->GetX() > (ScaleX.GetMax()*
                  									(SWORD32)12/
                  									(SWORD32)10))
						{
							x = 	ScaleX.GetMax()*
									(SWORD32)12/
									(SWORD32)10;

							y = 	(a * x + b)/
									(SWORD32)100;
						}

						/*%C Enregistre les nouvelles coordonnées	*/
						PointOut->SetX(x);
   	        	   PointOut->SetY(y);
					}
					/*%C Affichage en histogramme */
					else
					{
						if(PointOut->GetY() >= ScaleY.GetMax())
						{
		    	       	MiddlePoint.SetY( ScaleY.GetMax() );
		    	        	PointOut->SetY( ScaleY.GetMax() );
                  }
        	         else if(PointOut->GetY() <= ScaleY.GetMin())
                  {
		    	        	MiddlePoint.SetY( ScaleY.GetMin() );
	    		        	PointOut->SetY( ScaleY.GetMin() );
                  }
						else
						{
                  	MiddlePoint.SetY( PointOut->GetY() );
						}
						if(a!=0)
						{
    	        	   	MiddlePoint.SetX(((SWORD32)100 * 
    	        	   							PointOut->GetY() - b) / a);
						}
						else
						{
							MiddlePoint.SetX(PointOut->GetX());
						}

					}
               break;
    	        
				case AllPointOut:
              	/*%C Ces calculs seront utilisés pas le mode histogramme */
              	if(CurrentPoint.GetY() >= ScaleY.GetMax())
				  	{
		    	     	PreviousPoint.SetY( ScaleY.GetMax() );
		    	     	MiddlePoint.SetY( ScaleY.GetMax() );
		    	     	CurrentPoint.SetY( ScaleY.GetMax() );
				  	}
        	     	else if(CurrentPoint.GetY() <= ScaleY.GetMin())
				  	{
		    	     	PreviousPoint.SetY( ScaleY.GetMin() );
		    	     	MiddlePoint.SetY( ScaleY.GetMin() );
	    		     	CurrentPoint.SetY( ScaleY.GetMin() );
               }

              	if(CurrentPoint.GetX() > 	(ScaleX.GetMax()*
              										(SWORD32)12/
              										(SWORD32)10))
				  	{
		    	     	PreviousPoint.SetX(	ScaleX.GetMax()*
		    	     								(SWORD32)12/
		    	     								(SWORD32)10 );

		    	     	MiddlePoint.SetX( ScaleX.GetMax()*
		    	     							(SWORD32)12/
		    	     							(SWORD32)10 );

		    	     	CurrentPoint.SetX(ScaleX.GetMax()*
		    	     							(SWORD32)12/
		    	     							(SWORD32)10 );
					}
        	      else if(CurrentPoint.GetX() <= ScaleX.GetMin())
               {
		    	     	PreviousPoint.SetX( ScaleX.GetMin() );
		    	     	MiddlePoint.SetX( ScaleX.GetMin() );
	    		     	CurrentPoint.SetX( ScaleX.GetMin() );
               }
               break;
               default : break;               
    		}

			/*%C Lecture du Style (Boucle / Pression-Débit) dans la DataBase */
         DataBaseAccess::ReadValue(&Style, CURVE_DISPLAY_TYPE_MODE_U16,CONFIG);

			/*%C Lecture des points */
			CurrentPixel = CurrentPoint.ToPixel(CData->GetScaleX(),
															CData->GetScaleY());

			PreviousPixel = PreviousPoint.ToPixel(	CData->GetScaleX(),
																CData->GetScaleY());

			/*%C Dessine la courbe */
			if((GetCurveNumber()>1) || 
				(Kind == eLINE))
			{
				UWORD16 StartLine = PreviousPixel.GetY();
				for(UWORD16 i = 0;i<CData->GetPen()->GetLineThickness();i++)
				{
					/*%C On ne dessine le segment que si il y a au moins un point */
					/*%C dans la zone d'affichage */

					if(PointZone != AllPointOut)
					{
						InterfaceCppC::DisplayLine(StartLine,
                      		    				   PreviousPixel.GetX(),
							    				   		CurrentPixel.GetY() - 
							    				   		PreviousPixel.GetY(),
								    			   		CurrentPixel.GetX() - 
								    			   		PreviousPixel.GetX(),
									    		   		1,
												    	   GetPage());
					}
			      StartLine--;
				}
			}
			else
			{
				MiddlePixel = MiddlePoint.ToPixel(	CData->GetScaleX(),
																CData->GetScaleY());

				/*%C Protection contre la division par zéro */
				if(PreviousPixel.GetX() != MiddlePixel.GetX())
				{
					a = 	(SWORD32)100 * 
							((SWORD32)MiddlePixel.GetY()-
							(SWORD32)PreviousPixel.GetY()) / 
							((SWORD32)MiddlePixel.GetX()-
							(SWORD32)PreviousPixel.GetX());
				}
				else
				{
					a = 0;
				}
				b = 	(SWORD32)100 * 
						(SWORD32)MiddlePixel.GetY() - 
						a * 
						(SWORD32)MiddlePixel.GetX();

				for(x=PreviousPixel.GetX();x<=(SWORD32)CurrentPixel.GetX();x++)
				{
					switch(PointZone) 
					{
	            	case CurrentPointOut :
    	        		case PreviousPointOut:
                   	if(x>=(SWORD32)MiddlePixel.GetX())
							{
                       	y = MiddlePixel.GetY();
                        break;
                     }
						default :
		              	y = (a * x + b)/(SWORD32)100;
                     break;
					}
					InterfaceCppC::DisplayLine(y,
														x,
														(SWORD16)ScaleX.GetLine() - 
														y - 
														ScaleY.GetZeroPos(),
                                          0,
                                          1,
                                          GetPage());
				}

			}
	   	/*%C Si on n'est en courbe BOUCLE */
       	if(Style == 0 && 
       		!OutOfLimit && 
       		ScaleX.GetMax() > 30)
			{
			/*%C Barre d'effacement du début de la courbe */
			InterfaceCppC::EraseZone(	GetScaleY()->GetLine()-
												GetScaleY()->GetWidth()+9,
                                   	CurrentPixel.GetX() + 1,
                                   	GetScaleY()->GetWidth()-10,
                                   	12,
                                  	0,
                                   	GetPage());
          }
       }
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Gestion du graphique																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void Graph::Raz()
{
	/* On enlève 5 pixels pour éviter d'effacer les flèches */
   InterfaceCppC::EraseZone(	GetScaleY()->GetLine()-
   									GetScaleY()->GetWidth()+9,
									  	GetScaleY()->GetCol()+1,
							 			GetScaleY()->GetWidth()-10,
							 			GetScaleX()->GetWidth()-6,
							 			0,
							 			GetPage());

	Reset();

}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Gestion du graphique																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void Graph::Reset()
{
	UWORD16 i, Style;

	/*%C Lecture du Style (Boucle / Pression-Débit) dans la DataBase */
	DataBaseAccess::ReadValue(&Style, CURVE_DISPLAY_TYPE_MODE_U16,CONFIG);

   /*%C Si on est en courbe WOB et si l'échelle X est < 4s, */
   /*%C on rafraichit totalement le graph */
   if (Style == 1 || this->ScaleX.GetMax() <= 30)
   {
   	// On enlève 5 pixels pour éviter d'effacer les flèches
   	InterfaceCppC::EraseZone(	GetScaleY()->GetLine()-
   										GetScaleY()->GetWidth()+9,
											GetScaleY()->GetCol()+1,
							 				GetScaleY()->GetWidth()-10,
							 				GetScaleX()->GetWidth()-6,
							 				0,
							 				GetPage());
	}

	/*%C Init de la valeur des courbes */
	for(i=0; i<MAX_CURVE; i++)
	{
		if(CurveTable[i] != NULL)
		{
			CurveTable[i]->ResetValue();
		}
	}

	ManageAutoScale();
	ShowYZeroLine();
   ShowMaxLine();

   /*%C Reset du GraphControl */
	if(this->HaveGControl())
	{
  		GControl->Reset();
  	}

 	/*%C Si on n'est pas en courbe BOUCLE on efface que le début de la courbe */
   if (Style == 0 && this->ScaleX.GetMax() > 30)
   {
   	/*%C Barre d'effacement du début de la courbe */
  	 	InterfaceCppC::EraseZone(	GetScaleY()->GetLine()-
  	 										GetScaleY()->GetWidth()+9,
                             		GetScaleY()->GetCol()+1,
                             		GetScaleY()->GetWidth()-10,
                            	 	6,
                             		0,
                             		GetPage());
    }

	/*%C Init de la memo Min Max des courbes */
	for(i=0; i<MAX_CURVE; i++)
	{
		if(CurveTable[i] != NULL)
		{
			CurveTable[i]->ResetMinMax();
		}
		/*%C Si on est hors limites - affichage "Hors Limites" */
		if((CurveTable[i]->GetOutOfLimitDis() == TRUE) && this->CurveTable[i]->IsCurveStart())
      {
			/*%C On enlève 5 pixels pour éviter d'effacer les flèches */
    		InterfaceCppC::EraseZone(	GetScaleY()->GetLine()-
    											GetScaleY()->GetWidth()+9,
									 			GetScaleY()->GetCol()+1,
									 			GetScaleY()->GetWidth()-10,
									 			GetScaleX()->GetWidth()-6,
							 		 			0,
							 		 			GetPage());

            this->CurveTable[i]->SetCurveStart(FALSE);
			LabelOOL.Show();
         OutOfLimit = TRUE;
		}
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Gestion du graphique																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void Graph::ManageAutoScale()
{
	/*%C Gestion des Scales */
	if(GetScaleX()->IsAutoScale())
	{
		if(GetScaleX()->ManageAutoScale(	GetCurveTable(),
													GetCurveNumber()))
		{
			GetScaleX()->Hide();
         GetLabelX()->Show();
			GetScaleX()->Show();
		}
	}
	if(GetScaleY()->IsAutoScale())
	{
		if(GetScaleY()->ManageAutoScale(	GetCurveTable(),
													GetCurveNumber()))
		{
			GetScaleY()->Hide();
			GetScaleY()->Show();
		}
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Gestion du graphique																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void Graph::FreezeGraph(e_BOOL _Freeze)
{
	Freezed = _Freeze;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Gestion du graphique																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void Graph::Refresh()
{
	int i;

	if(IsVisible() && !Freezed)
   {
		for(i=0; i<MAX_CURVE; i++)
		{
			if(CurveTable[i] != NULL)
			{
				CurveTable[i]->Refresh();
			}
			/*%C Si on est hors limites - affichage "Hors Limites" */
			if(this->CurveTable[i]->GetOutOfLimitDis() == FALSE)
         {
         	LabelOOL.Hide();
            OutOfLimit = FALSE;
			}
		}

		if(HaveGControl()) 
		{
			GControl->ManageGraph();
		}

		for(i=0; i<MAX_CURVE; i++)
		{
			if(CurveTable[i] != NULL)
			{
				DataPoint(CurveTable[i]);
			}
		}
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Gestion du graphique																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void Graph::ShowYZeroLine()
{
	/*%C Traitement des axes avec valeurs negatives */
	if(GetScaleY()->GetZeroPos() != 0)
	{
		InterfaceCppC::DisplayHorDottetLine(GetScaleY()->GetLine()-
														GetScaleY()->GetZeroPos(),
        												GetScaleY()->GetCol()+4,
								 		 				GetScaleX()->GetWidth()-7,
                                          5,
                                         	3,
                                          1,
								 		 				GetPage());
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Gestion du graphique																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void Graph::ShowMaxLine()
{
	UWORD16 MaxLine = GetScaleY()->ValToPoint(CurveTable[0]->GetMaxY());;
	UWORD16 ZeroLine = GetScaleY()->GetLine() - GetScaleY()->GetZeroPos();;

	if(this->CurveTable[0] != NULL)
	{
		if( MaxLine != ZeroLine &&
        					CurveTable[0]->GetMaxY() >= GetScaleY()->GetMin() &&
        					CurveTable[0]->GetMaxY() <= GetScaleY()->GetMax())
		{
    		InterfaceCppC::DisplayHorDottetLine(MaxLine,
    	   												GetScaleY()->GetCol()+2,
								 		 					GetScaleX()->GetWidth()-7,
            	                            	1,
                	                       		2,
                                            	1,
								 		 					GetPage() );
		}
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Gestion du graphique																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void Graph::Show()
{
	UWORD16 Value;

	DisplayObject::Show();

	DataBaseAccess::ReadValue(&Value, CURVE_DRAW_MODE_U16, CONFIG);
	Graph::Kind = (TKind)Value;

	GControl->Reset();

	/*%C Init de la valeur des courbes */
	for(int i=0; i<MAX_CURVE; i++)
	{
		if(CurveTable[i] != NULL)
		{
			CurveTable[i]->ResetValue();
	   }
	}
	RefreshEnable(TRUE);
	LabelX.Show();
	LabelY.Show();
   ScaleX.Show();
	ScaleY.Show();
	ShowYZeroLine();
   ShowMaxLine();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Gestion du graphique																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void Graph::Hide()
{
	RefreshEnable(FALSE);
	ScaleX.Hide();
	ScaleY.Hide();
	LabelX.Hide();
	LabelY.Hide();
	DisplayObject::Hide();    
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Gestion du graphique																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void Graph::RefreshLanguage()
{
	LabelX.SetTextOnly(GetTUnit1());
   LabelY.SetTextOnly(GetTUnit2());
   LabelOOL.SetTextOnly(GetTOutOfLimit());
}


