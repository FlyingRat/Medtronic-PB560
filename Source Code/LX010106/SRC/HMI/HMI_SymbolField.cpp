/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_SymbolField.cpp                        	 	  					*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C   Objet d'affichage d'un symbole	  	   					  						*/
/*		                                                                   	 	*/
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/
#include "HMI_SymbolField.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/
#include "HMI_InterfaceCppC.hpp"

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
SymbolField::SymbolField():FieldObject()
{
	Symbol = NO;
   BarredSymbol = TRUE;
}
/*----------------------------------------------------------------------------*/
SymbolField::SymbolField(DisplayObject *_Parent)
{
	SymbolField();
	SetParent(_Parent);
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void SymbolField::SetSymbol(e_SYMBOL _Symbol)
{
	/*%C Clear the previous symbol */
	Clear();
	/*%C affectation (quand WHITE_SQUARE selectionné, impossible */
	/*%C de revenir en arrière) */
	if(Symbol != WHITE_SQUARE && Symbol != KEY_WHITE)
		Symbol = _Symbol;
	/*%C Si l'actuel symbol est WHITE_SQUARE et le nouveau KEY_WHITE */
	else if(Symbol == WHITE_SQUARE || Symbol == KEY_WHITE)
		Symbol = _Symbol;

	/*%C affichage */
	if(IsVisible())
   {
		Show();
	}
}
/*----------------------------------------------------------------------------*/
e_SYMBOL SymbolField::GetSymbol()
{
	return Symbol;
}
/*----------------------------------------------------------------------------*/
void SymbolField::SetBarredSymbol(e_BOOL _Barred)
{
   BarredSymbol = _Barred;
	if(IsVisible())
   {
      Hide();
    	Show();
   }
}
/*----------------------------------------------------------------------------*/
e_BOOL SymbolField::GetBarredSymbol()
{
	return BarredSymbol;
}

/******************************************************************************/
/*                           METHODES                					      		*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation des accés de DataBase													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		IdParamHours : ID de la lecture de l'heure dans la DB						*/
/*%I		DbTarget : Nom de la DB				            								*/
/*%I		IdParamMin : ID de la lecture des minutes dans la DB						*/
/*%I		IdParamSec : ID de la lecture des secpndes dans DB							*/
/*%I		IdParamRegHours : ID du réglage de l'heure dans la DB		      		*/
/*%I		IdParamRegMin : ID du réglage des minutes dans la DB 		      		*/
/*%I		IdParamRegSec : ID du réglage des secondes dans la DB		      		*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void SymbolField::Init( UWORD16 _Line,
                        UWORD16 _Col,
                        UWORD16 _Font,
                        e_BOOL _ReverseVideo,
                        e_SYMBOL _Symbol)
{
	FieldObject::Init(_Line, _Col, _Font, _ReverseVideo);
	SetSymbol(_Symbol);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Blink de l'Objet																			*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	   NONE																		      		*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void SymbolField::Blink(e_BOOL _Actif)
{
	if(_Actif)
   {
		Hide();
	}
	else
   {
		Show();
	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Affichage de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	   NONE																		      		*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void SymbolField::Show()
{
	if(!HaveParent() || GetParent()->IsVisible())
   {
		if(GetSymbol() != NO)
      {
			FieldObject::Show();

			UWORD16 ColTmp, LineTmp;
			LineTmp = GetLine();
			ColTmp = GetCol();

			if(HaveParent())
         {
				LineTmp = LineTmp + GetParent()->GetLine();
            ColTmp  = ColTmp + GetParent()->GetCol();
			}


			switch(GetSymbol())
			{
				case BLACK_SQUARES :

				case FREE_SQUARE :

            case WHITE_SQUARE :

				case LOS :

				case BLACK_LOS :

				case LESS_OR_MORE :

				case TRIGGER :

				case TRIGGERINV :
					LineTmp-=6;
               break;

				case LOCKS :
               LineTmp-=3;
               break;

				case WHITE_LOCK :
               LineTmp-=6;
               break;

            case PAUSE :
             	LineTmp-=9;
               break;

				case BAT :

            case BAT_INV :

				case RAMPE1 :

				case RAMPE2 :

 				case RAMPE3 :

				case RISETIME1 :

				case RISETIME2 :

				case RISETIME3 :

				case RISETIME4 :

            case VALVE_BLACK :

				case VALVE_WHITE :
             	LineTmp-=12;
               break;

				case KEY :

				case KEY_WHITE :
					LineTmp-=13;
               break;

				case BELL_BLACK :
			   case ALARM_TRIANGLE_BLACK_DOT :
			   case ALARM_TRIANGLE_BLACK :
					LineTmp-=17;
               break;

				case EQUAL :
					LineTmp-=6;
					break;

				case HEART_INVERSE_VIDEO :
				case HEART :
					LineTmp-=12;
					break;

				default:
					break;
			}

         if(GetSymbol() == WHITE_SQUARE)
         {
			   InterfaceCppC::EraseZone(LineTmp,ColTmp,6,6,0,GetPage());
			   InterfaceCppC::EraseZone(LineTmp+1,ColTmp+1,4,4,1,GetPage());
			   InterfaceCppC::EraseZone(LineTmp+2,ColTmp+2,2,2,0,GetPage());
         }
         else if(GetSymbol() == WHITE_LOCK)
         {
           	InterfaceCppC::DisplayLine(LineTmp+3,ColTmp,0,6, 0, GetPage());
         }
         else
			InterfaceCppC::DisplaySymbol(	Symbol,
											      LineTmp,
                                       ColTmp,
											      GetPage());
         if(Symbol == VALVE_BLACK && BarredSymbol)
         {
           	InterfaceCppC::DisplayLine(LineTmp-1,
                                       ColTmp-3,
                                       14+1,
                                       10+5,
                                       1,
                                       GetPage());

            InterfaceCppC::DisplayLine(LineTmp-1,
                                       ColTmp+10+2,
                                       14+1,
                                       -10-5,
                                       1,
                                       GetPage());

           	InterfaceCppC::DisplayLine(LineTmp,
                                       ColTmp-3,
                                       14-1,
                                       10+5,
                                       1,
                                       GetPage());

           	InterfaceCppC::DisplayLine(LineTmp,
                                       ColTmp+10+2,
                                       14-1,
                                       -10-5,
                                       1,
                                       GetPage());
         }
         if(Symbol == VALVE_WHITE && BarredSymbol)
         {
          	InterfaceCppC::DisplayLine(LineTmp-1,
                                       ColTmp-3,
                                       14+1,
                                       10+5,
                                       0,
                                       GetPage());

				InterfaceCppC::DisplayLine(LineTmp-1,
                                       ColTmp+10+2,
                                       14+1,
                                       -10-5,
                                       0,
                                       GetPage());

           	InterfaceCppC::DisplayLine(LineTmp,
                                       ColTmp-3,
                                       14-1,
                                       10+5,
                                       0,
                                       GetPage());

           	InterfaceCppC::DisplayLine(LineTmp,
                                       ColTmp+10+2,
                                       14-1,
                                       -10-5, 0, GetPage());
         }
      }
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Effacement de l'Objet																  	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	   NONE																		      		*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void SymbolField::Hide()
{
    if(!HaveParent() || GetParent()->IsVisible())
    {
        if(IsVisible())
	    {
		    if(GetSymbol() != NO)
		    {
			    /*%C Clear before hide !! */
                Clear();
	            FieldObject::Hide();
    		}
	    }
    }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Efface la valeur courante															  	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	   NONE																		      		*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void SymbolField::Clear()
{
    if(!HaveParent() || GetParent()->IsVisible())
    {
	    if(IsVisible())
        {
	    	if(GetSymbol() != NO)
		    {
    			UWORD16 ColTmp, LineTmp;
	    		LineTmp = GetLine();
		    	ColTmp = GetCol();

    			if(HaveParent())
	    		{
		    		LineTmp = LineTmp+ GetParent()->GetLine();
			    	ColTmp  = ColTmp + GetParent()->GetCol();
    			}

	    		switch(GetSymbol())
		    	{
			    	case BLACK_SQUARES :

    				case FREE_SQUARE :
		
    				case LOS :
		
	    			case BLACK_LOS :
		
	    			case LESS_OR_MORE :
		
	    			case TRIGGER :
		    			InterfaceCppC::EraseZone(		LineTmp-6,
															ColTmp,
															7,
															8,
															0,
															GetPage());
                    break;
		
    				case LOCKS :
				    	InterfaceCppC::EraseZone(		LineTmp-3,
															ColTmp,
															7,
															8,
															0,
															GetPage());
                    break;
		
		    		case WHITE_SQUARE :
		
		    		case WHITE_LOCK :
					    InterfaceCppC::EraseZone(		LineTmp-6,
															ColTmp,
															7,
															8,
															1,
															GetPage());
                    break;
		
				    case PAUSE :
				    	InterfaceCppC::EraseZone(		LineTmp-9,
															ColTmp,
															11,
															11,
															0,
															GetPage());
                    break;
		
				    case BAT :
					    InterfaceCppC::EraseZone(		LineTmp-12,
															ColTmp,
															14,
															16,
															0,
															GetPage());
                    break;
      
                    case BAT_INV :
					    InterfaceCppC::EraseZone(		LineTmp-12,
															ColTmp,
															14,
															16,
															1,
															GetPage());
                    break;
		
				    case RAMPE1 :
		
				    case RAMPE2 :

				    case RAMPE3 :
		
				    case RISETIME1 :
		
				    case RISETIME2 :
		
				    case RISETIME3 :
		
				    case RISETIME4 :
					    InterfaceCppC::EraseZone(		LineTmp-12,
															ColTmp,
															12,
															40,
															0,
															GetPage());
                    break;
		
				    case KEY :

                    case KEY_WHITE :
					    if ((GetPage() == VIDEO_PAGE1) || (GetPage() == VIDEO_PAGE2))
					    {
    					    InterfaceCppC::EraseZone(	LineTmp-13,
    														ColTmp,
    														13,
    														8,
    														0,
    														GetPage());
					    }
                        else
					    {
    					    InterfaceCppC::EraseZone(	LineTmp-13,
    														ColTmp,
    														13,
    														8,
    														1,
    														GetPage());
					    }
                    break;

				    case TRIGGERINV :
					    InterfaceCppC::DisBox(			LineTmp-6,
															ColTmp,
															6, 
															6, 
															TRUE, 
															1, 
															GetPage());
                    break;

				    case VENTIL :
					    InterfaceCppC::DisBox(			LineTmp,
															ColTmp,
															40, 
															40, 
															TRUE, 
															1, 
															GetPage());
                    break;
                    case VALVE_BLACK :
					    InterfaceCppC::EraseZone(		LineTmp-13,
															ColTmp-3,
															14+2,
															10+6,
															0,
															GetPage());
                    break;

				    case VALVE_WHITE :
					    InterfaceCppC::EraseZone(		LineTmp-13,
															ColTmp-3,
															14+2,
															10+6,
															1,
															GetPage());
                    break;

				    case BELL_BLACK :
                    case ALARM_TRIANGLE_BLACK_DOT :
				    case ALARM_TRIANGLE_BLACK :
			            InterfaceCppC::EraseZone(	LineTmp-17,
                                                ColTmp,
                                                17,
                                                17,
                                                0,
                                                GetPage());
                    break;

                    case EQUAL :
					    InterfaceCppC::EraseZone(	LineTmp-6,
														ColTmp,
														6,
														7,
														0,
														GetPage());
                    break;

				    case HEART_INVERSE_VIDEO :
					    InterfaceCppC::EraseZone(	LineTmp-12,
												ColTmp,
												12-1, /* -1 dû au décalage du driver d'affichage */
												14-1,
												1,
												GetPage());
				    break;

				    case HEART :
					    InterfaceCppC::EraseZone(	LineTmp-12,
												ColTmp,
												12-1, /* -1 dû au décalage du driver d'affichage */
												14-1,
												0,
												GetPage());
               		    /*%C Une fois la zone effacée, réafficher la même zone avec l'inverse video correcte */
               		    InterfaceCppC::DisBox(LineTmp-12,
                                          ColTmp,
                                          12-1,
                                          14-1,
                                          GetReverseVideo(),
                  			               0,
                                          GetPage());
					    break;

				    default:
					    break;

                }
			}
		}
	}
}





