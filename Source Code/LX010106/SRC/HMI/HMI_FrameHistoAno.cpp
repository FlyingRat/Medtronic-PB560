/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_FrameHistoAno.cpp      	  		                  			*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Fenetre Historique des Anomalies												      */
/*		                                                                        */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_FrameHistoAno.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/

#include "HMI_Message.hpp"
#include "HMI_InterfaceCppC.hpp"
#include "HMI_Config.hpp"

extern "C"
{
#include "DB_Event.h"
#include "define.h"
}

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
FrameHistoAno::FrameHistoAno():VFrame()
{
#ifdef HMI_CONFIG_TIME_24H_FORMAT
   SetTimeFormat(ANO_24H_FORMAT);
#elif defined HMI_CONFIG_TIME_12H_FORMAT
   SetTimeFormat(ANO_12H_FORMAT);
#else
   SetTimeFormat(ANO_12H_FORMAT);
#endif

#ifdef HMI_CONFIG_DATE_US_FORMAT
   SetDateFormat(ANO_US_FORMAT);
#elif defined HMI_CONFIG_DATE_EUR_FORMAT
   SetDateFormat(ANO_EUR_FORMAT);
#else
   SetDateFormat(ANO_EUR_FORMAT);
#endif

}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void FrameHistoAno::SetDateFormat(e_ANO_DATE_FORMAT _format)
{
   AlarmDateFormat = _format;
}
/*----------------------------------------------------------------------------*/
e_ANO_DATE_FORMAT FrameHistoAno::GetDateFormat(void)
{
   return(AlarmDateFormat);
}
/*----------------------------------------------------------------------------*/
void FrameHistoAno::SetTimeFormat(e_ANO_TIME_FORMAT _format)
{
   AlarmTimeFormat = _format;
}
/*----------------------------------------------------------------------------*/
e_ANO_TIME_FORMAT FrameHistoAno::GetTimeFormat(void)
{
   return(AlarmTimeFormat);
}
/******************************************************************************/
/*                           METHODES                					 		     	*/
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

void FrameHistoAno::init()
{
   LHistoAno.SetParent(this);
   LHistoAno.Init(   NO,
                     (UBYTE**)cMSG_MenuHistoAno,
                     18,
                     0);
   LHistoAno.SetFontLabel(FONT_4);
   LHistoAno.SetCentered(TRUE);
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
void FrameHistoAno::Show()
{
   VFrame::Show();
   LHistoAno.Show();
   SeekEnd();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Operation de changement de la langue de l'Objet									*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameHistoAno::RefreshLanguage()
{
   LHistoAno.RefreshLanguage();
   LHistoAno.SetCentered(LHistoAno.GetCentered());
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement de l'Objet																		*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameHistoAno::Hide()
{
   LHistoAno.Hide();
   VFrame::Hide();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Refresh des param de la fenetre ->Lecture des Alarmes							*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
e_BOOL FrameHistoAno::SeekEnd()
{
   static UWORD16 NbAnomalies = 0;
   static UWORD16 NbEventRead = 0;

   UWORD16 DayCol, MonthCol, YearCol;
   
   UWORD16 Hours = 0;
  
   e_BOOL FlagHour = FALSE;
  
   UWORD16 Msb = 0;
   UWORD16 Lsb = 0;
   UWORD16 Offset = 42;

   UBYTE *NameMonth;

   static FlashEvent ArrayAnomalie[NB_ANOMALI_DISPLAY];

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
	   if (	(evenement_read >= Start_Anomalies) && 
	   		(evenement_read <= End_Anomalie-1))
      {
         ArrayAnomalie[NbAnomalies].evenement = evenement_read;

         ArrayAnomalie[NbAnomalies].year =   InterfaceCppC::FlashReadEvent
                                             (NbEventRead+1,EVENT_YEA_ID,NULL);

	      ArrayAnomalie[NbAnomalies].month =  InterfaceCppC::FlashReadEvent
                                             (NbEventRead+1,EVENT_MON_ID,NULL);

         ArrayAnomalie[NbAnomalies].day =    InterfaceCppC::FlashReadEvent
                                             (NbEventRead+1,EVENT_DAY_ID,NULL);

   	   ArrayAnomalie[NbAnomalies].hour =   InterfaceCppC::FlashReadEvent
                                             (NbEventRead+1,EVENT_HOU_ID,NULL);

	      ArrayAnomalie[NbAnomalies].min =    InterfaceCppC::FlashReadEvent
                                             (NbEventRead+1,EVENT_MIN_ID,NULL);

         Msb = InterfaceCppC::FlashReadEvent	(NbEventRead+1,
                                             EVENT_CPTMACHHOURMSB_ID,NULL);

         Lsb = InterfaceCppC::FlashReadEvent(NbEventRead+1,
                                             EVENT_CPTMACHHOURLSB_ID,NULL);

         ArrayAnomalie[NbAnomalies].cpt   = Msb*256+Lsb;
	      NbAnomalies++;
	   }

      /*%C Pas plus de 100 lecture sinon nouveau tour de scheduler */
      i++;
   	
   	/*%C Scrutation de l'évènement précédent */
   	NbEventRead++;
  	}
   while (  (NbAnomalies != NB_ANOMALI_DISPLAY) &&
	         (evenement_read != 0x00FF)  &&
            (NbEventRead != ((EVENT_FLASH_END_ADDRESS - 
            EVENT_FLASH_START_ADDRESS) / EVENT_Last_Event_Parameter) - 1) &&
            (i < 100));
   
   if (  (NbAnomalies == NB_ANOMALI_DISPLAY) ||
	      (evenement_read == 0x00FF)  ||
	      (NbEventRead == ((EVENT_FLASH_END_ADDRESS - 
	      EVENT_FLASH_START_ADDRESS) / EVENT_Last_Event_Parameter) - 1))
	{
	   /*%C Affiche le résultat */
   	if (NbAnomalies == 0)
      {
	      InterfaceCppC::DisplayString( (UBYTE*)cMSG_EmptyList
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
		   for(UWORD16 i=0;i<NbAnomalies;i++)
         {
            InterfaceCppC::DisplayString( (UBYTE *)"n",
                                          FONT_1,
                                          FALSE,
                                          i*20+Offset,
                                          10,
                                          1,
                                          GetPage());

   	      InterfaceCppC::DisplayNumber( ArrayAnomalie[i].evenement - 
   	      										Start_Anomalies,
                                          FALSE,
                                          FALSE,
                                          i*20+Offset,
                                          18,
                                          FONT_1,
                                          2,
                                          TRUE,
                                          1,
                                          GetPage());

	   	   InterfaceCppC::DisplayString( (UBYTE *)"-",
                                          FONT_1,
                                          FALSE,
                                          i*20+Offset,
                                          44,
                                          1,
                                          GetPage());

			   /*%C Affichage du mois */
		      if((ArrayAnomalie[i].month>=1) && (ArrayAnomalie[i].month<=12))
            {
               UBYTE **tmp;
               tmp = (UBYTE**)cMSG_Month;

		         /*%C positmnt de la ligne (ici NB_LANGUAGE = nb de langues) */
		         tmp = &tmp[Label::GetNbLanguage()*(ArrayAnomalie[i].month)];

		         /*%C lecture de la colonne */
		         NameMonth = tmp[GetLanguage()];
		      }
		      else
            {
		         NameMonth = (UBYTE *)"???";
		      }

            if(GetDateFormat() == ANO_US_FORMAT)
            {
               DayCol = 87;
               MonthCol = 60;
               YearCol = 103;
            }
            else
            {
               DayCol = 60;
               MonthCol = 76;
               YearCol = 103;
            }

            InterfaceCppC::DisplayString( NameMonth,
                                          FONT_1,
                                          FALSE,
                                          i*20+Offset,
                                          MonthCol,
                                          1,
                                          GetPage());
            InterfaceCppC::DisplayNumber( ArrayAnomalie[i].day,
                                          FALSE,
                                          FALSE,
                                          i*20+Offset,
                                          DayCol,
                                          FONT_1,
                                          2,
                                          TRUE,
                                          1,
                                          GetPage());
            InterfaceCppC::DisplayNumber( ArrayAnomalie[i].year,
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
                                          120,
                                          1,
                                          GetPage());
            Hours = ArrayAnomalie[i].hour;
            if(GetTimeFormat() == ANO_12H_FORMAT)
            {
               if(Hours > 12)
               {
                  FlagHour = TRUE;
                  Hours = Hours - 12;
               }
               else if(Hours == 0)
               {
                  FlagHour = TRUE;
                  Hours = Hours + 12;
               }
               else
               {
                  FlagHour = FALSE;
               }
            }               
		      InterfaceCppC::DisplayNumber( Hours,
                                          FALSE,
                                          FALSE,
                                          i*20+Offset,
                                          126,
                                          FONT_1,
                                          2,
                                          TRUE,
                                          1,
                                          GetPage());
		      InterfaceCppC::DisplayString( (UBYTE *)":",
                                          FONT_1,
                                          FALSE,
                                          i*20+Offset,
                                          141,
                                          1,
                                          GetPage());
		      InterfaceCppC::DisplayNumber( ArrayAnomalie[i].min,
                                          FALSE,
                                          FALSE,
                                          i*20+Offset,
                                          145,
                                          FONT_1,
                                          2,
                                          TRUE,
                                          1,
                                          GetPage());
            if(GetTimeFormat() == ANO_12H_FORMAT)
            {
               if(FlagHour == FALSE)
               {
                  InterfaceCppC::DisplayString( (UBYTE *)"am",
                                                FONT_1,
                                                FALSE,
                                                i*20+Offset,
                                                160,
                                                1,
                                                GetPage());
               }
               else
               {
                  InterfaceCppC::DisplayString( (UBYTE *)"pm",
                                                FONT_1,
                                                FALSE,
                                                i*20+Offset,
                                                160,
                                                1,
                                                GetPage());
               }
            }               
		      InterfaceCppC::DisplayString( (UBYTE*)cMSG_Cpt
		      										[GetLanguage()],
                                          FONT_1,
                                          FALSE,
                                          i*20+Offset,
                                          196,
                                          1,
                                          GetPage());

		      InterfaceCppC::DisplayString( (UBYTE *)":",
                                          FONT_1,
                                          FALSE,
                                          i*20+Offset,
                                          256,
                                          1,
                                          GetPage());

		      InterfaceCppC::DisplayNumber( ArrayAnomalie[i].cpt,
                                          FALSE,
                                          FALSE,
                                          i*20+Offset,
                                          264,
                                          FONT_1,
                                          5,
                                          TRUE,
                                          1,
                                          GetPage());

            InterfaceCppC::DisplayString((UBYTE *) "h",
                                          FONT_1,
                                          FALSE,
                                          i*20+Offset,
                                          304,
                                          1,
                                          GetPage());
         }
      }
      NbAnomalies = 0;
      NbEventRead = 0;
      return TRUE;
   }
   else
   {
      return FALSE;
   }
}



