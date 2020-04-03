/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_FrameHistoAlarme.cpp        		                  			*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Fenetre Historique des Alarmes													      */
/*		                                                                        */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_FrameHistoAlarme.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_Message.hpp"
#include "HMI_IhmType.hpp"
#include "HMI_InterfaceCppC.hpp"
#include "HMI_Label.hpp"
#include "HMI_Tools.hpp"

extern "C"
{
#include "define.h"
}

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
FrameHistoAlarme::FrameHistoAlarme():VFrame()
{

#ifdef HMI_CONFIG_TIME_24H_FORMAT
   SetTimeFormat(ALARM_24H_FORMAT);
#elif defined HMI_CONFIG_TIME_12H_FORMAT
   SetTimeFormat(ALARM_12H_FORMAT);
#else
   SetTimeFormat(ALARM_12H_FORMAT);
#endif

#ifdef HMI_CONFIG_DATE_US_FORMAT
   SetDateFormat(ALARM_US_FORMAT);
#elif defined HMI_CONFIG_DATE_EUR_FORMAT
   SetDateFormat(ALARM_EUR_FORMAT);
#else
   SetDateFormat(ALARM_EUR_FORMAT);
#endif
}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void FrameHistoAlarme::SetDateFormat(e_ALARM_DATE_FORMAT _format)
{
   AlarmDateFormat = _format;
}
/*----------------------------------------------------------------------------*/
e_ALARM_DATE_FORMAT FrameHistoAlarme::GetDateFormat(void)
{
   return(AlarmDateFormat);
}
/*----------------------------------------------------------------------------*/
void FrameHistoAlarme::SetTimeFormat(e_ALARM_TIME_FORMAT _format)
{
   AlarmTimeFormat = _format;
}
/*----------------------------------------------------------------------------*/
e_ALARM_TIME_FORMAT FrameHistoAlarme::GetTimeFormat(void)
{
   return(AlarmTimeFormat);
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
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameHistoAlarme::init()
{
   LHistoAlarm.SetParent		(this);

   LHistoAlarm.Init				(NO,
   									(UBYTE**)cMSG_TitleMemoAlarms,
   									18,
   									0);

   LHistoAlarm.SetFontLabel(FONT_4);

   LHistoAlarm.SetCentered(TRUE);

}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Affichage	de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameHistoAlarme::Show()
{
   VFrame::Show();
   LHistoAlarm.Show();
   SeekEnd();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Operation de changement de la langue de l'Objet							  		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameHistoAlarme::RefreshLanguage()
{
   LHistoAlarm.RefreshLanguage();
   LHistoAlarm.SetCentered(LHistoAlarm.GetCentered());
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Effacement de l'Objet															  		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameHistoAlarme::Hide()
{
   LHistoAlarm.Hide();
   VFrame::Hide();   
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Refresh des param de la fenetre  ->Lecture des Alarmes					  		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
e_BOOL FrameHistoAlarme::SeekEnd()
{
   static UWORD16 NbAlarmes = 0;
   static UWORD16 NbEventRead = 0;

   UWORD16 Offset = 42;
   UWORD16 Hours = 0;
   UWORD16 DayCol, MonthCol, YearCol;
   
   e_BOOL FlagHour = FALSE;
   
   UBYTE *NameMonth,*NameAlarme;
   
   static FlashEvent ArrayAlarme[NB_ALARME_DISPLAY];
   
   UBYTE evenement_read, i;

	/*%C Initialisation des variables */
	i = 0;

	/*%C Scrutation de la Flash */
	do
	{
      /*%C Lecture de la nature de l'évènement */
	   evenement_read = InterfaceCppC::FlashReadEvent(	NbEventRead+1,
	   																EVENT_NB_ID,
	   																NULL);

	   /*%C Filtre d'évènement */
	   if (	(evenement_read >= Start_Alarm) && 
	   		(evenement_read < End_Event_Alarm))
      {
  	      ArrayAlarme[NbAlarmes].evenement = evenement_read;

         ArrayAlarme[NbAlarmes].year  =   InterfaceCppC::FlashReadEvent
                                          (NbEventRead+1,EVENT_YEA_ID,NULL);
	      
	      ArrayAlarme[NbAlarmes].month =   InterfaceCppC::FlashReadEvent
                                          (NbEventRead+1,EVENT_MON_ID,NULL);
         
         ArrayAlarme[NbAlarmes].day   =   InterfaceCppC::FlashReadEvent
                                          (NbEventRead+1,EVENT_DAY_ID,NULL);
   	   
   	   ArrayAlarme[NbAlarmes].hour  =   InterfaceCppC::FlashReadEvent
                                          (NbEventRead+1,EVENT_HOU_ID,NULL);
	      
	      ArrayAlarme[NbAlarmes].min   =   InterfaceCppC::FlashReadEvent
                                          (NbEventRead+1,EVENT_MIN_ID,NULL);
         
         NbAlarmes++;
		}

   	/*%C Pas plus de 100 lecture sinon nouveau tour de scheduler */
	   i++;
   	
   	/*%C Scrutation de l'évènement précédent */
	    NbEventRead++;
   }
   while (  (NbAlarmes != NB_ALARME_DISPLAY) &&
	         (evenement_read != 0x00FF)  &&
	         (NbEventRead != ((EVENT_FLASH_END_ADDRESS - 
	         EVENT_FLASH_START_ADDRESS) / EVENT_Last_Event_Parameter) - 1) &&
            (i < 100));

   if (  (NbAlarmes == NB_ALARME_DISPLAY) ||
         (evenement_read == 0x00FF)  ||
		   (NbEventRead == ((EVENT_FLASH_END_ADDRESS - 
		   EVENT_FLASH_START_ADDRESS) / EVENT_Last_Event_Parameter) - 1))
   {
      /*%C Affiche le résultat */
      if (NbAlarmes == 0)
      {
         InterfaceCppC::DisplayString((UBYTE*)cMSG_EmptyList
         					[GetLanguage()],
         					FONT_4,
         					FALSE,
         					110,
         					(DISPLAY_WINDOW_WIDTH - Tools::GetStringPixelSize((UBYTE*)cMSG_EmptyList[GetLanguage()], FONT_4))/2,
         					1,
         					GetPage());
      }
      else
      {
         for(UWORD16 i=0;i<NbAlarmes;i++)
			{
				UBYTE **tmp;
			      
				tmp = (UBYTE**)cMSG_HistAlarm;
			      
				/*%C positmnt de la ligne (ici NB_LANGUAGE = nb de langues) */
				tmp = &tmp[Label::GetNbLanguage()*
										(ArrayAlarme[i].evenement-Start_Alarm-1)];

				/*%C lecture de la colonne */
				NameAlarme = tmp[GetLanguage()];

				InterfaceCppC::DisplayString( NameAlarme,
                                          FONT_1,
                                          FALSE,
														i*20+Offset,
														5,
                                          1,
                                          GetPage());


            InterfaceCppC::DisplayString( (UBYTE *)"-",
                                          FONT_1,
                                          FALSE,
                                          i*20+Offset,
                                          197,
                                          1,
                                          GetPage());

            /*%C Affichage du mois */
            if((ArrayAlarme[i].month>=1) && (ArrayAlarme[i].month<=12))
            {
               UBYTE **tmp;
               tmp = (UBYTE**)cMSG_Month;

               /*%C positmnt de la ligne (ici NB_LANGUAGE = nb de langues) */
               tmp = &tmp[Label::GetNbLanguage()*(ArrayAlarme[i].month)];
               
               /*%C lecture de la colonne */
               NameMonth = tmp[GetLanguage()];
            }
            else
            {
               NameMonth = (UBYTE *)"???";
            }

            if(GetDateFormat() == ALARM_US_FORMAT)
            {
               DayCol = 229;
               MonthCol = 202;
               YearCol = 245;
            }
            else
            {
               DayCol = 202;
               MonthCol = 218;
               YearCol = 245;
            }

            InterfaceCppC::DisplayString( NameMonth,
                                          FONT_1,
                                          FALSE,
                                          i*20+Offset,
                                          MonthCol,
                                          1,
                                          GetPage());
            InterfaceCppC::DisplayNumber( ArrayAlarme[i].day,
                                          FALSE,
                                          FALSE,
                                          i*20+Offset,
                                          DayCol,
                                          FONT_1,
                                          2,
                                          TRUE,
                                          1,
                                          GetPage());
            InterfaceCppC::DisplayNumber( ArrayAlarme[i].year,
                                          FALSE,
                                          FALSE,
                                          i*20+Offset,
                                          YearCol,
                                          FONT_1,
                                          2,
                                          TRUE,
                                          1,
                                          GetPage());
            InterfaceCppC::DisplayString( (UBYTE *)"-",
                                          FONT_1,
                                          FALSE,
                                          i*20+Offset,
                                          261,
                                          1,
                                          GetPage());
            Hours = ArrayAlarme[i].hour;
            if(GetTimeFormat() == ALARM_12H_FORMAT)
            {
                /* AM or PM */
                if(Hours >= 12)
                    FlagHour = TRUE;
                else
                    FlagHour = FALSE;
                /* 0-12 range */
                if(Hours > 12)
                {
                  Hours = Hours - 12;
                }
                else if(Hours == 0)
                {
                  Hours = Hours + 12;
                }
            }
            InterfaceCppC::DisplayNumber( Hours,
                                          FALSE,
                                          FALSE,
                                          i*20+Offset,
                                          266,
                                          FONT_1,
                                          2,
                                          TRUE,
                                          1,
                                          GetPage());
            InterfaceCppC::DisplayString( (UBYTE *)":",
                                          FONT_1,
                                          FALSE,
                                          i*20+Offset,
                                          281,
                                          1,
                                          GetPage());
            InterfaceCppC::DisplayNumber( ArrayAlarme[i].min,
                                          FALSE,
                                          FALSE,
                                          i*20+Offset,
                                          285,
                                          FONT_1,
                                          2,
                                          TRUE,
                                          1,
                                          GetPage());
            if(GetTimeFormat() == ALARM_12H_FORMAT)
            {
               if(FlagHour == FALSE)
               {
                  InterfaceCppC::DisplayString( (UBYTE *)"am",
                                                FONT_1,
                                                FALSE,
                                                i*20+Offset,
                                                300,
                                                1,
                                                GetPage());
               }
               else
               {
                  InterfaceCppC::DisplayString( (UBYTE *)"pm",
                                                FONT_1,
                                                FALSE,
                                                i*20+Offset,
                                                300,
                                                1,
                                                GetPage());
               }
            }
         }
      }
      NbAlarmes = 0;
      NbEventRead = 0;
      return TRUE;
   }
   else
   {
      return FALSE;
	}
}


