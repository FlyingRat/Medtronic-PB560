/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_InterfaceCppC.cpp                                 	 		*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Communication c/c++																      */
/*		                                                                        */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_InterfaceCppC.hpp"
#include "Driver_Display_Data.h"
#include "HMI_IhmType.hpp"
#include "HMI_DataBaseAccess.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/
#ifndef _BORLAND
#endif
extern "C"
{
#include "typedef.h"
#include "enum.h"
#include "define.h"
#include "DB_Rtc.h"
#include "DRV_Leds.h"
#include "DRV_Buz.h"

}

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/

/******************************************************************************/
/*                           ACCESSEURS				                				*/
/******************************************************************************/

/******************************************************************************/
/*                           METHODES   D'AFFICHAGE     								*/
/******************************************************************************/


void InterfaceCppC::DisplayPixel(UWORD16 Line,
                                 UWORD16 Column,
                                 UWORD16 PrintOn,
                                 UWORD16 Page)
{
	DIS_FifoWrite					(DRV_PIXEL,
				                  (UBYTE)Line,
            				      Column,
				                  GetDriverPrintOn(PrintOn),
            				      GetDriverPage(Page),
				                  0,
				                  0,
				                  0,
				                  0,
				                  0,
				                  0,
				                  0,
				                  0);
}
/*----------------------------------------------------------------------------*/
void InterfaceCppC::DisplayCross(UWORD16 Line,
								 UWORD16 Column,
								 UWORD16 Line1Size,
								 UWORD16 Line2Size,
								 UWORD16 PrintOn,
								 UWORD16 Page)
{
	UWORD16 line, col, i;

	line = Line;
	col = Column;

	/* 1ère croix */
	for (i = 0; i < Line1Size; i++) {

		InterfaceCppC::DisplayPixel(line - i,
								col + i,
								1,
								Page);
	}
	for (i = 0; i < Line2Size; i++) {

		InterfaceCppC::DisplayPixel(line - Line2Size + 1 + i,
								col + i,
								1,
								Page);
	}

	line --;
	
	/* 2ème croix */
	for (i = 0; i < Line1Size; i++) {

		InterfaceCppC::DisplayPixel(line - i,
								col + i,
								1,
								Page);
	}
	for (i = 0; i < Line2Size; i++) {

		InterfaceCppC::DisplayPixel(line - Line2Size + 1 + i,
								col + i,
								1,
								Page);
	}

}
/*----------------------------------------------------------------------------*/
void InterfaceCppC::DisplaySymbol(  UWORD16 Symbol,
									UWORD16 Line,
									UWORD16 Column,
									UWORD16 Page)
{
	DIS_FifoWrite					(DRV_SYMBOL,Symbol,
				                  (UBYTE)Line,
            				      Column,
				                  GetDriverPage(Page),
            				      0,
            				      0,
            				      0,
            				      0,
            				      0,
            				      0,
            				      0,
            				      0);
}
/*----------------------------------------------------------------------------*/
void InterfaceCppC::DisplayString(  UBYTE *ptr_char,
                                    UWORD16 Font,
                                    e_BOOL ReverseVideo,
                                    UWORD16 Line,
                                    UWORD16 Column,
                                    UWORD16 PrintOn,
                                    UWORD16 Page)
{
	UWORD32 AddressConvert;

	AddressConvert = (UWORD32) ptr_char;

	DIS_FifoWrite					(DRV_STRING,
				                  (UWORD16)(AddressConvert >> 16),
            				      (UWORD16)AddressConvert,
				                  GetDriverFont(Font,ReverseVideo),
			 	                 	Line,
			 	                 	(UWORD16)Column,
					               GetDriverPrintOn(PrintOn),
               				   GetDriverPage(Page),
				                  0,
				                  0,
				                  0,
				                  0,
				                  0);
}
/*----------------------------------------------------------------------------*/
void InterfaceCppC::DisplayNumber(  SWORD32 Value,
                                    UWORD16 Nature,
                                    e_BOOL ReverseVideo,
                                    UWORD16 Line,
                                    UWORD16 Column,
                                    UWORD16 Font,
                                    UWORD16 Nb_Digit,
                                    e_BOOL Zero,
                                    UWORD16 PrintOn,
                                    UWORD16 Page)
{
	DIS_FifoWrite					(DRV_NUMBER,
				                  (UWORD16)(Value >> 16),
				                  (UWORD16)Value,
				                  GetDriverNature(Nature),
				                  Line,
				                  (UWORD16)Column,
				                  GetDriverFont(Font,ReverseVideo),
            				      Nb_Digit,
            				      Zero,
				                  GetDriverPrintOn(PrintOn),
            				      GetDriverPage(Page),
            				      0,
            				      0);
}
/*----------------------------------------------------------------------------*/
void InterfaceCppC::EraseZone(UWORD16 Line,
                              UWORD16 Column,
                              UWORD16 Heigth,
                              UWORD16 Width,
                              UWORD16 PrintOn,
                              UWORD16 Page)
{
	DIS_FifoWrite					(DRV_ERASE_ZONE,
				                  Line,
				                  (UWORD16)(Column),
				                  (Line+Heigth),
				                  (Column+Width),
				                  GetDriverPrintOn(PrintOn),
				                  GetDriverPage(Page),
            					   0,
            					   0,
            					   0,
            					   0,
            					   0,
            					   0);
}
/*----------------------------------------------------------------------------*/
void InterfaceCppC::DisBox(UWORD16 Line,
                           UWORD16 Column,
                           UWORD16 Heigth,
                           UWORD16 Width,
                           e_BOOL FloodBlack,
                  			UWORD16 PrintOn,
                           UWORD16 Page)
{
	DIS_FifoWrite					(DRV_BOX,GetDriverColor(FloodBlack),
				                  Line,
				                  (UWORD16)(Column),
				                  (Line+Heigth),
            				      (Column+Width),
								      GetDriverPrintOn(PrintOn),
				                  GetDriverPage(Page),
            					   0,
            					   0,
            					   0,
            					   0,
            					   0);
}
/*----------------------------------------------------------------------------*/
void InterfaceCppC::DisplayLine( SWORD16 Line,
                                 SWORD16 Column,
                                 SWORD16 Heigth,
                                 SWORD16 Width,
                                 UWORD16 PrintOn,
                                 UWORD16 Page)
{
	DIS_FifoWrite					(DRV_LINE,Line,
				                  (UWORD16)(Column),
				                  (Line+Heigth),
				                  (Column+Width),
				                  GetDriverPrintOn(PrintOn),
				                  GetDriverPage(Page),
            					   0,
            					   0,
            					   0,
            					   0,
            					   0,
            					   0);
}
/*----------------------------------------------------------------------------*/
void InterfaceCppC::DisplayHorDottetLine( UWORD16 Line,
                                          UWORD16 Column,
                                          SWORD16 Length,
                                          UWORD16 IndentLength,
                                          UWORD16 BlankLength,
                                          UWORD16 PrintOn,
                                          UWORD16 Page)
{
	for(int i=0; i<Length; i += (IndentLength+BlankLength))
	{
    	if( (i+IndentLength) > Length)
		{
         InterfaceCppC::DisplayLine(Line, 
         									Column+i, 
         									0, 
         									Length-i-1, 
         									PrintOn, 
         									Page);
		}
      else
		{
         InterfaceCppC::DisplayLine(Line, 
         									Column+i, 
         									0, 
         									IndentLength-1, 
         									PrintOn, 
         									Page);
		}
	}
}
/*----------------------------------------------------------------------------*/
void InterfaceCppC::DisplayBrithness(UWORD16 Value)
{
	DIS_FifoWrite(DRV_BRITHNESSAJUST,Value,0,0,0,0,0,0,0,0,0,0,0);
}
/*----------------------------------------------------------------------------*/
void InterfaceCppC::DisplayPage(UWORD16 NumPage)
{
	DIS_FifoWrite(DRV_DISPLAY_PAGE,NumPage, 4,0,0,0,0,0,0,0,0,0,0);
}
/*----------------------------------------------------------------------------*/
void InterfaceCppC::ErazePage(UWORD16 NumPage)
{
	DIS_FifoWrite(DRV_ERASE_PAGE,NumPage,0,0,0,0,0,0,0,0,0,0,0);
}
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/*                           METHODES                					     			*/
/******************************************************************************/
e_BOOL InterfaceCppC::DB_Request(UWORD16 *Value,
                                 UWORD16 Id,
                                 e_TYPE_OF_DB_TARGET DbType,
                                 e_DATA_OPERATION DataOp)
{
	return (e_BOOL)DB_IhmAccessParaDataBase(Value,Id,DbType,DataOp);
}
/*----------------------------------------------------------------------------*/
UWORD16 InterfaceCppC::GetDriverFont(  UWORD16 PrgFont,
                                       e_BOOL ReverseVideo)
{
	UWORD16 FT;
	switch(PrgFont)
   {
		case FONT_1    :  FT = ARIAL9;
                        break;
		case FONT_2    :  FT = ARIAL8;
                        break;
		case FONT_4    :  FT = ARIALBLACK11;
                        break;
		case FONT_5    :  FT = ARIALBOLD29;
                        break;
		default		   :  FT = ARIAL9;
                        break;
	}
	if(ReverseVideo)
   {
		FT |= INV;
	}
	return FT;
}
/*----------------------------------------------------------------------------*/
UWORD16 InterfaceCppC::GetDriverPrintOn(UWORD16 PrgPrintOn)
{
	switch(PrgPrintOn)
   {
		case 0	: return OFF;
		case 1	: return ON;
		default	: return OFF;
	}
}
/*----------------------------------------------------------------------------*/
UWORD16 InterfaceCppC::GetDriverNature(UWORD16 PrgNature)
{
	switch(PrgNature)
   {
		case 0	: return INTEGER;
		case 1	: return DECIMAL;
		default	: return INTEGER;
	}
}
/*----------------------------------------------------------------------------*/
UWORD16 InterfaceCppC::GetDriverPage(UWORD16 PrgPage)
{
	switch(PrgPage)
   {
		case VIDEO_PAGE1	: return PAGE1;
		case VIDEO_PAGE2	: return PAGE2;
		case VIRTUAL_PAGE	: return PAGE3;
		default				: return PAGE1;
   }
}
/*----------------------------------------------------------------------------*/
UWORD16 InterfaceCppC::GetDriverColor(UWORD16 PrgColor)
{
	switch(PrgColor)
   {
		case 1	: return BLACK;
		default	: return WHITE;
	}
}
/*----------------------------------------------------------------------------*/
UWORD16 InterfaceCppC::FlashReadEvent( UWORD16 NumEvent,
                                       e_EVENT_PARAMETERS IdEvent,
                                       UWORD16 *PtrRetrieval)
{
	return (UWORD16)DRV_EVENT_Read_Event(NumEvent,IdEvent,PtrRetrieval);
}
/*----------------------------------------------------------------------------*/
void InterfaceCppC::FlashWriteEvent( UWORD16 NumEvent )
{
	DB_EventMngt (NumEvent);
}
/*----------------------------------------------------------------------------*/
void InterfaceCppC::ActiveLed(e_TYPE_OF_LED Led, e_BOOL On)
{
	switch(Led)
   {
		case LED_VENTIL	:
         DRV_Led_Ventil(On);
      break;
      default:
      break;
	}
}
/*----------------------------------------------------------------------------*/
void InterfaceCppC::ActiveLed(e_TYPE_OF_LED Led, e_TYPE_BLINK Blink)
{
	switch(Led){
		case LED_ALARM_RED		:
         DRV_Led_Red(Blink);
      break;
		case LED_ALARM_ORANGE	:
         DRV_Led_Orange(Blink);
      break;
		case LED_WHITE			:
         DRV_Led_White(Blink);
      break;
#ifdef _BORLAND
      case LED_AC :
         DRV_Led_Ac(Blink);
      break;
      case LED_DC :
         DRV_Led_Dc(Blink);
      break;
      case LED_BAT :
         DRV_Led_Bat(Blink);
      break;
#endif

	}
}
/*----------------------------------------------------------------------------*/
void InterfaceCppC::ActiveBuzzer(e_TYPE_SOUND sound, e_NUMBER_BUZ NumBuzzer)
{
   DRV_Buz_Sound(sound, NumBuzzer);
}
/*----------------------------------------------------------------------------*/
e_BOOL InterfaceCppC::IsOneAlarmActive()
{
    return DB_AlarmIsOneActive();
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Fonction permettant d'attendre la fin d'éffacement de la Flash			  	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void InterfaceCppC::MaintEraseFlashMngt(void)
{
#ifndef _BORLAND
	
	UWORD16 _Id;
	UWORD16 _Value;

   /*%C RTC à lire */
   t_RTC_TIME_DATE RtcValue;

   if (DRV_EVENT_TransStateFlash() == DRV_EVENT_FREE)
	{
   	/*%C RAZ du cumul Compteur horaire Patient */
	   DB_ControlWrite(CURRENT_PATIENT_COUNTER_MIN_U16,0);
      DB_ControlWrite(CURRENT_PATIENT_COUNTER_HOUR_U16,0);

      /*%C Lecture de l'heure et de la date courante */
   	RtcValue.Minute = DB_RTCRead(DB_RTC_MINUTE_U16);
   	RtcValue.Hour = DB_RTCRead(DB_RTC_HOUR_U16);
   	RtcValue.Day = DB_RTCRead(DB_RTC_DAY_U16);
   	RtcValue.Month = DB_RTCRead(DB_RTC_MONTH_U16);
	   RtcValue.Year = DB_RTCRead(DB_RTC_YEAR_U16);

   	/*%C Ecriture de l'heure et de la date courante dans la date */
   	/*%C de Raz Compteur Patient */
   	DB_ConfigWrite(RAZ_COUNTER_PAT_MIN_U16,RtcValue.Minute);
	   DB_ConfigWrite(RAZ_COUNTER_PAT_HOUR_U16,RtcValue.Hour);
   	DB_ConfigWrite(RAZ_COUNTER_PAT_DATE_U16,RtcValue.Day);
	   DB_ConfigWrite(RAZ_COUNTER_PAT_MONTH_U16,RtcValue.Month);
   	DB_ConfigWrite(RAZ_COUNTER_PAT_YEAR_U16,RtcValue.Year);

	   /*%C RAZ des pointeurs d'évènement + Secteur + Sauvegarde e2prom */
   	DRV_EVENT_RazPointerSector();
		
		
		_Value = 0;
		/*%C Re-Initialize the TrendEvent and the DB_Trend */
		for(_Id = DB_TREND_VENTIL_HOUR ; _Id < end_of_db_trend_table ; _Id ++)
		{
			DataBaseAccess::WriteValue(&_Value,_Id,TREND);
		}
	}

#endif

}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Fonction d'éffacement de la Flash	monitorage détaillé		  	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void InterfaceCppC::EraseNANDFlashMngt(void)
{
#ifndef _BORLAND

	DRV_NAND_Erase_Flash();

#endif

}
