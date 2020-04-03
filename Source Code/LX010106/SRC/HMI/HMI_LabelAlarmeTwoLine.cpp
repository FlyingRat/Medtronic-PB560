/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelAlarmeTwoLine.cpp	                            	 		*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet d'affichage	d'une alarme sur deux lignes							      */
/*		                                                                        */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_LabelAlarmeTwoLine.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_InterfaceCppC.hpp"
#include "HMI_Tools.hpp"
#include "HMI_IhmType.hpp"
#include "HMI_FrameVentilation.hpp"
#include "HMI_FrameAlarme.hpp"

extern "C"
{
#include "DB_AlarmStatus.h"
}
/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
LabelAlarmeTwoLine::LabelAlarmeTwoLine():LabelAlarme()
{
   FLine2.SetParent(this);
   FLine2.Init(18,0,FONT_1,FALSE,(UBYTE *)"");
	WBox = WHITH_ALARMEBOX;
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void LabelAlarmeTwoLine::SetAlarmId(UWORD16 _AlarmId)
{
   AlarmId = _AlarmId;
   SetText(GetName());
}
/*----------------------------------------------------------------------------*/
void LabelAlarmeTwoLine::RemoveAlarmId(UWORD16 AlarmId)
{
   AlarmList.RemoveFromList(AlarmId);
}
/*----------------------------------------------------------------------------*/
void LabelAlarmeTwoLine::RemoveAllAlarms(void)
{
   AlarmList.EmptyList();
}
/*----------------------------------------------------------------------------*/
void LabelAlarmeTwoLine::SetWhithBox(UWORD16 _WBox)
{
   WBox = _WBox;
}

/******************************************************************************/
/*                           METHODES                	      						*/
/******************************************************************************/
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Initialisation de l'Objet 																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	Icon : icone											               			*/
/*%I	  	Name : nom à afficher                                                */
/*%I     Line : ligne d'affichage                                             */
/*%I     Col : Colonne d'affichage                                            */
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelAlarmeTwoLine::Init(  e_SYMBOL Icon, UBYTE **Name, UWORD16 Line, UWORD16 Col)
{
   LabelAlarme::Init(Icon, Name, Line, Col);
   AlarmList.Init(Mark_Displayed_Alarm - 1 - Mark_Begin_Alarm);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage	de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE														               			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelAlarmeTwoLine::Show()
{
	LabelAlarme::Show();
	FLine2.Show();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement	de l'Objet																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE														               			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelAlarmeTwoLine::Hide()
{
  /*%C Effacement des lignes */
	FLine2.Hide();
	LabelAlarme::Hide();    
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Inversion vidéo																				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE														               			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelAlarmeTwoLine::SetInvertVideo(e_BOOL _Actif)
{
	LabelAlarme::SetInvertVideo(_Actif);
   FLine2.SetReverseVideo(_Actif);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage d'une alarme																	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE														               			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
void LabelAlarmeTwoLine::SetText(UBYTE* Text)
{

   /*%C Déclaration du Texte tampon */
   UBYTE* TextTemp;
   UBYTE* FirstLine;
   UBYTE* SecondLine;   

   /*%C Variables locales */
   UWORD16 SizeBox = 0 ;
   UWORD16 BoxFont = 0;
   UWORD16 i = 0 , j = 0 , k = 0, x1 = 0,  x2 = 0;

   /*%C Receuil de la longueur de la fenetre + 1 afin d'intégrer */
   /* le cadre Blanc */
	SizeBox = WBox - 6;

	/*%C Receuil de la police de la police */
	BoxFont = FLine2.GetFont();

   if(E_NO == AlarmList.InList(GetAlarmId()))
   {
      /*%C Initialisation du tableau de ligne */
      for (i=0; i<cMAX_LINE; i++)
      {
         for (j=0; j<cMAX_CHARACTER; j++)
         {
            TextLine[i][j] = 0;
         }
      }

	   /*%C Appel de la fonction de traitement de message */
      TextTemp = Tools::BuildMessage(Text , SizeBox , BoxFont);

      /*%C Mise en forme des différentes lignes */
      for(i = 0 ; i < 100 ; i ++)
      {
         if(TextTemp[i] == '\0')
         {
	   		break;
         }
         if(TextTemp[i] == '|')
         {
            j = j + 1;
            i = i + 1;
            k = 0;
	   	}
         /*%C Protection pour le dépasement */
         x1 = j;
      	x1 = x1 % cMAX_LINE;
         /*%C Protection pour le dépasement */
         x2 = k;
	      x2 = x2 % cMAX_CHARACTER;
         TextLine[x1][x2] = TextTemp [i];
         k ++;
   	}

      if(!AlarmList.IsListFull())
      {
         /*%C Liste NON pleine, on insère le message dans la file */
         AlarmList.AddToList(GetAlarmId(),0, TextLine[0]);
         AlarmList.AddToList(GetAlarmId(),1, TextLine[1]);
      }
      FirstLine = TextLine[0];
      SecondLine = TextLine[1];
   }
   else
   {

      /*% Récupération des messages de chaque ligne */
      AlarmList.GetTextLineFromId(GetAlarmId(), 0, &FirstLine);
      AlarmList.GetTextLineFromId(GetAlarmId(), 1, &SecondLine);
   }

	/*%C  affectation des Line 1 & 2 à getlabel() et Fline2 */
   GetFLabel()->SetText(FirstLine);
	FLine2.SetText(SecondLine);

   /*%C Centrer les line1 & 2 sur la box */
   GetFLabel()->SetCol(	(SizeBox -
								Tools::GetStringPixelSize(FirstLine, BoxFont))
								/ 2);

   FLine2.SetCol(	(SizeBox -
						Tools::GetStringPixelSize(SecondLine, BoxFont))
                  / 2);

   /* Affichage d'une ligne blanche et une ligne sur le cadre Alarme */
   /* ou Ventil afin d'éviter son effacement */
   if(WBox == WHITH_ALARMEBOX)
   {
		  InterfaceCppC::DisplayLine( 154,
                                    COL_ALARMEBOX + WHITH_ALARMEBOX,
												56,
                                    0,
												1,
												this->GetPage());
		  InterfaceCppC::DisplayLine( 154,
												COL_ALARMEBOX + WHITH_ALARMEBOX + 1,
												56,
                                    0,
												0,
												this->GetPage());
   }
   else if (WBox == WHITH_VENTILBOX)
   {
		  InterfaceCppC::DisplayLine( 188,
                                    COL_VENTILBOX + WHITH_VENTILBOX,
                                    33,
                                    0,
												1,
                                    this->GetPage());
        InterfaceCppC::DisplayLine( 188,
                                    COL_VENTILBOX + WHITH_VENTILBOX + 1,
                                    33,
                                    0,
												0,
												this->GetPage());
   }

}



