/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LoupeAlarm.cpp 				   	      	 	  					*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage de la loupe pour la fenetre alarme		 					*/
/*		                                                                   	 	*/
/******************************************************************************/


/******************************************************************************/
/*                           HEADER INCLUDE FILE		                        */
/******************************************************************************/

#include "HMI_LoupeAlarm.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                     	   */
/******************************************************************************/

#include "HMI_Tools.hpp"
#include "HMI_FrameAlarme.hpp"

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
LoupeAlarm::LoupeAlarm():Loupe()
{
   SetLineValue(68);
	Message.SetParent				(this);

   Message.SetWhithBox			(WHITH_ALARMEBOX);

	Message.InitGraphicBox		(103,
										207,
										35,
										WHITH_ALARMEBOX,
                              FALSE,
                              FALSE,
										TRUE);

	Message.SetLineLine1			(16);

	Message.SetLineLine2			(29);

	Message.SetLineLine3			(42);

	MonitorBox.Init(32,COL_ALARMEBOX,117,WHITH_ALARMEBOX,TRUE,TRUE,TRUE);
}

/******************************************************************************/
/*                           METHODES        		        					      */
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Permet de centrer la valeur en fct du type											*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		Type : type de la valeur															*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LoupeAlarm::Format(DataType _Type)
{
	UWORD16 length = 0;

	switch(_Type)
   {
		case eValue  :
        	length = Tools::GetNumberPixelSize( GetValue(),
                                             GetFValueI()->GetFont(),
                                             GetFValueI()->GetFloat());

         SetColValue((111-length)/2);
         break;

        case eString :
        	   length = Tools::GetStringPixelSize( GetFValueS()->GetText(),
                                                GetFValueS()->GetFont());
            SetColValue(1+(WHITH_ALARMEBOX-length)/2);
            break;

        case eValueSign :
        	   GetFValueI()->SetCol(24);
            GetFValueS()->SetCol(8);
            break;
         default : break;            
	}
}
