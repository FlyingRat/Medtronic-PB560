/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_FrameTendance.cpp                          						*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Fenetre Menu Tendance																      */
/*		                                                                        */
/******************************************************************************/

/******************************************************************************/
/*                           HEADER INCLUDE FILE		                  		*/
/******************************************************************************/

#include "HMI_FrameTendance.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                  			*/
/******************************************************************************/
#include "HMI_DatabaseAccess.hpp"
#include "HMI_Message.hpp"
#include "HMI_Config.hpp"
extern "C"
{
#include "enum.h"
}

#ifdef HMI_CONFIG_SPO2
   #ifdef HMI_CONFIG_TREND_SIGMA
	  #define TREND_TABLE_FIRST_LINE      38
	  #define TREND_TABLE_FIRST_COL       1
   #ifdef HMI_CONFIG_TREND_VTE
	  #define TREND_TABLE_LINE_NB         12
   #else
	  #define TREND_TABLE_LINE_NB         11
   #endif
      #define TREND_TABLE_COL_NB          2
	  #define TREND_TABLE_HEIGHT          200
      #define TREND_TABLE_WIDTH           300
      #define TREND_TABLE_ODD_COL_WIDTH   150
	  #define TREND_TABLE_EVEN_COL_WIDTH  150
   #else
      #define TREND_TABLE_FIRST_LINE      38
	  #define TREND_TABLE_FIRST_COL       1
   #ifdef HMI_CONFIG_TREND_VTE
	  #define TREND_TABLE_LINE_NB         12
   #else
	  #define TREND_TABLE_LINE_NB         11
   #endif
      #define TREND_TABLE_COL_NB          2
      #define TREND_TABLE_HEIGHT          200
      #define TREND_TABLE_WIDTH           300
      #define TREND_TABLE_ODD_COL_WIDTH   150
      #define TREND_TABLE_EVEN_COL_WIDTH  150
   #endif //HMI_CONFIG_TREND_SIGMA
#else
   #ifdef HMI_CONFIG_TREND_SIGMA
      #define TREND_TABLE_FIRST_LINE      35
      #define TREND_TABLE_FIRST_COL       30
   #ifdef HMI_CONFIG_TREND_VTE
	  #define TREND_TABLE_LINE_NB         8
   #else
	  #define TREND_TABLE_LINE_NB         7
   #endif
      #define TREND_TABLE_COL_NB          2
      #define TREND_TABLE_HEIGHT          168
      #define TREND_TABLE_WIDTH           260
      #define TREND_TABLE_ODD_COL_WIDTH   130
	  #define TREND_TABLE_EVEN_COL_WIDTH  130
   #else
      #define TREND_TABLE_FIRST_LINE      35
      #define TREND_TABLE_FIRST_COL       30
   #ifdef HMI_CONFIG_TREND_VTE
	  #define TREND_TABLE_LINE_NB         8
   #else
	  #define TREND_TABLE_LINE_NB         7
   #endif
	  #define TREND_TABLE_COL_NB          2
      #define TREND_TABLE_HEIGHT          168
      #define TREND_TABLE_WIDTH           260
      #define TREND_TABLE_ODD_COL_WIDTH   130
      #define TREND_TABLE_EVEN_COL_WIDTH  130
   #endif //HMI_CONFIG_TREND_SIGMA
#endif //HMI_CONFIG_SPO2

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
FrameTendance::FrameTendance():VFrame()
{

}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/

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
void FrameTendance::init()
{
   UWORD16 _line, _col, _colLabel, _colValue, _colUnit;
   UWORD16 _CellLineIndex, _CellColIndex;
   _col = 0;

   LTendance.SetParent				(this);

	LTendance.Init						(NO,
										   (UBYTE**)cMSG_ReportTitle,
										   12,
										   0);

	LTendance.SetFontLabel			(FONT_4);

   LTendance.SetCentered         (TRUE);


	GTable.SetParent					(this);

   GTable.Init(   TREND_TABLE_FIRST_LINE,
				  TREND_TABLE_FIRST_COL,
				  TREND_TABLE_LINE_NB,
                  TREND_TABLE_COL_NB,
                  TREND_TABLE_HEIGHT,
                  TREND_TABLE_WIDTH,
                  TREND_TABLE_ODD_COL_WIDTH,
                  TREND_TABLE_EVEN_COL_WIDTH);

   /* Ventilation Moyenne */
   _line = 30;

	LOVVentMoy.SetParent				(this);

   LOVVentMoy.InitDbAccess			(DB_TREND_IHM_VENTIL_HOUR,
										   TREND,
                                 DB_TREND_IHM_VENTIL_MIN,
										   TREND);

	LOVVentMoy.Init  					(NO,
										   (UBYTE**)cMSG_VentTimeReport,
										   _line,
										   8,
										   9999,
										   (UBYTE**)cMSG_HourUnit,
  										   9999,
										   (UBYTE**)cMSG_MinuteUnit);

   LOVVentMoy.SetColAdjust       (TRUE);

	LOVVentMoy.SetColLabel			(0);

	LOVVentMoy.SetColSep		      (110);

	LOVVentMoy.SetColValue1		   (116);

	LOVVentMoy.SetColValue2		   (162);

	LOVVentMoy.SetMaxDisplayValue(24);

	LOVVentMoy.SetMaxDisplayValue2(59);

   /* Date */

   Date.SetParent						   (this);

	Date.InitDbAccess					   (DB_TREND_IHM_SAVE_RTC_MONTH,
												TREND,
												DB_TREND_IHM_SAVE_RTC_DAY,
												DB_TREND_IHM_SAVE_RTC_YEAR,
												NO_ID,
												NO_ID,
												NO_ID,
												TREND);

	Date.Init								(NO,
												(UBYTE**)cMSG_ReportDay,
												_line,
												185);

	Date.SetColSep						   (28);

	Date.SetColDate						(28);

	Date.SetNameMonth					   ((UBYTE**)cMSG_Month);

   Date.SetFontDate						(FONT_4);


   /* Titre du tableau de report */
   TableTitle.SetParent				(this);

	TableTitle.Init					(NO,
										   (UBYTE**)cMSG_NoneUnit,
										   79,
										   0);
   TableTitle.SetColLabel        (1);


   /* Vti */
   _CellLineIndex = 0;
   _CellColIndex = 0;

   _line = GTable.GetLineOfCell                 (_CellLineIndex,_CellColIndex);
   _colLabel = GTable.GetLeftJustifiedColOfCell (_CellLineIndex,_CellColIndex);
   _colValue = GTable.GetLeftJustifiedColOfCell (_CellLineIndex,_CellColIndex+1);
   _colUnit = _colValue + 11;

	LTVVt.SetParent				(this);

#ifdef HMI_CONFIG_TREND_SIGMA
   LTVVt.InitDbAccess			(DB_TREND_IHM_AVG_VTI,
										TREND,
                              DB_TREND_IHM_SIG_VTI,
										TREND);

	LTVVt.Init  					(NO,
										(UBYTE**)cMSG_VtiReport,
										_line,
										_col,
										9999,
										(UBYTE**)cMSG_MoreOrLess,
                                        9999,
										(UBYTE**)cMSG_VolumeUnit);

   LTVVt.SetColAdjust         (TRUE);
#else
   LTVVt.InitDbAccess			(DB_TREND_IHM_AVG_VTI,
										TREND);
	LTVVt.Init  					(NO,
										(UBYTE**)cMSG_VtiReport,
										_line,
										_col,
										9999,
										(UBYTE**)cMSG_VolumeUnit);
#endif

   LTVVt.SetDivider           (10);

   LTVVt.SetInitNbDigits(TRUE);

	LTVVt.SetSep					((UBYTE *)"");

	LTVVt.SetColLabel			 	(_colLabel);

	LTVVt.SetColValue1			(_colValue);

	LTVVt.SetColUnit1				(_colUnit);


   /* Vte */
#ifdef HMI_CONFIG_TREND_VTE
   _CellLineIndex++;

   _line = GTable.GetLineOfCell                 (_CellLineIndex,_CellColIndex);
   _colLabel = GTable.GetLeftJustifiedColOfCell (_CellLineIndex,_CellColIndex);
   _colValue = GTable.GetLeftJustifiedColOfCell (_CellLineIndex,_CellColIndex + 1);
   _colUnit = _colValue + 11;

	LTVVte.SetParent				(this);

#ifdef HMI_CONFIG_TREND_SIGMA
	LTVVte.InitDbAccess			(DB_TREND_IHM_AVG_VTE,
										TREND,
                              DB_TREND_IHM_SIG_VTE,
										TREND);

	LTVVte.Init  					(NO,
										(UBYTE**)cMSG_VteReport,
										_line,
										_col,
										9999,
										(UBYTE**)cMSG_MoreOrLess,
										9999,
										(UBYTE**)cMSG_VolumeUnit);

   LTVVte.SetColAdjust        (TRUE);
#else
	LTVVte.InitDbAccess			(DB_TREND_IHM_AVG_VTE,
										TREND);

	LTVVte.Init  					(NO,
										(UBYTE**)cMSG_VteReport,
										_line,
										_col,
										9999,
										(UBYTE**)cMSG_VolumeUnit);

#endif

   LTVVte.SetDivider          (10);

   LTVVte.SetInitNbDigits(TRUE);   

	LTVVte.SetSep					((UBYTE *)"");

	LTVVte.SetColLabel		  	(_colLabel);

	LTVVte.SetColValue1			(_colValue);

	LTVVte.SetColUnit1			(_colUnit);
#endif
   /* Pi */
   _CellLineIndex++;

   _line = GTable.GetLineOfCell                 (_CellLineIndex,_CellColIndex);
   _colLabel = GTable.GetLeftJustifiedColOfCell (_CellLineIndex,_CellColIndex) - _col;
   _colValue = GTable.GetLeftJustifiedColOfCell (_CellLineIndex,_CellColIndex + 1) - _col;
   _colUnit = _colValue + 14;

	LTVPi.SetParent			   (this);

#ifdef HMI_CONFIG_TREND_SIGMA
	LTVPi.InitDbAccess			(DB_TREND_IHM_AVG_PI,
										TREND,
                              DB_TREND_IHM_SIG_PI,
										TREND);

	LTVPi.Init  				   (NO,
										(UBYTE**)cMSG_PipReport,
										_line,
										_col,
										9999,
										(UBYTE**)cMSG_MoreOrLess,
										9999,
										(UBYTE**)cMSG_PressureUnit);

   LTVPi.SetColAdjust         (TRUE);

#else
	LTVPi.InitDbAccess			(DB_TREND_IHM_AVG_PI,
										TREND);

	LTVPi.Init  				   (NO,
										(UBYTE**)cMSG_PipReport,
										_line,
										_col,
										9999,
										(UBYTE**)cMSG_PressureUnit);
#endif

   LTVPi.SetDivider           (100);

   LTVPi.SetInitNbDigits(TRUE);

	LTVPi.SetSep					((UBYTE *)"");

	LTVPi.SetColLabel			   (_colLabel);

	LTVPi.SetColValue1			(_colValue);

	LTVPi.SetColUnit1		      (_colUnit);

	LTVPi.SetMaxDisplayValue(9999);

   /* Fr */

   _CellLineIndex++;
   _col = GTable.GetLeftJustifiedColOfCell (_CellLineIndex,_CellColIndex) - 3;

   _line = GTable.GetLineOfCell                 (_CellLineIndex,_CellColIndex);
   _colLabel = GTable.GetLeftJustifiedColOfCell (_CellLineIndex,_CellColIndex) - _col;
   _colValue = GTable.GetLeftJustifiedColOfCell (_CellLineIndex,_CellColIndex + 1) - _col;
   _colUnit = _colValue + 14;

	LTVFr.SetParent			   (this);

#ifdef HMI_CONFIG_TREND_SIGMA
	LTVFr.InitDbAccess		   (DB_TREND_IHM_AVG_FR,
										TREND,
                              DB_TREND_IHM_SIG_FR,
										TREND);

	LTVFr.Init  					(NO,
										(UBYTE**)cMSG_FrReport,
										_line,
										_col,
										9999,
										(UBYTE**)cMSG_MoreOrLess,
										9999,
										(UBYTE**)cMSG_FrequencyUnit);

   LTVFr.SetColAdjust         (TRUE);

#else
	LTVFr.InitDbAccess		   (DB_TREND_IHM_AVG_FR,
										TREND);

	LTVFr.Init  					(NO,
										(UBYTE**)cMSG_FrReport,
										_line,
										_col,
										9999,
										(UBYTE**)cMSG_FrequencyUnit);
#endif
   LTVFr.SetDivider           (10);

   LTVFr.SetInitNbDigits(TRUE);

	LTVFr.SetSep					((UBYTE *)"");

	LTVFr.SetColLabel			   (_colLabel);

	LTVFr.SetColValue1			(_colValue);

	LTVFr.SetColUnit1		      (_colUnit);

	LTVFr.SetMaxDisplayValue(999);

   /* Fuite */
   _CellLineIndex++;

   _line = GTable.GetLineOfCell                 (_CellLineIndex,_CellColIndex);
   _colLabel = GTable.GetLeftJustifiedColOfCell (_CellLineIndex,_CellColIndex) - _col;
   _colValue = GTable.GetLeftJustifiedColOfCell (_CellLineIndex,_CellColIndex + 1) - _col;
   _colUnit = _colValue + 14;

	LTVLeak.SetParent				(this);

#ifdef HMI_CONFIG_TREND_SIGMA
	LTVLeak.InitDbAccess			(DB_TREND_IHM_AVG_LEAK,
										TREND,
                              DB_TREND_IHM_SIG_LEAK,
										TREND);

	LTVLeak.Init  					(NO,
										(UBYTE**)cMSG_LeakReport,
										_line,
										_col,
										9999,
										(UBYTE**)cMSG_MoreOrLess,
										9999,
										(UBYTE**)cMSG_FlowUnit);

   LTVLeak.SetColAdjust       (TRUE);

#else
	LTVLeak.InitDbAccess			(DB_TREND_IHM_AVG_LEAK,
										TREND);

	LTVLeak.Init  					(NO,
										(UBYTE**)cMSG_LeakReport,
										_line,
										_col,
										9999,
										(UBYTE**)cMSG_FlowUnit);
#endif

   LTVLeak.SetDivider         (10);

   LTVLeak.SetInitNbDigits(TRUE);

	LTVLeak.SetSep					((UBYTE *)"");

	LTVLeak.SetColLabel			(_colLabel);

	LTVLeak.SetColValue1			(_colValue);

	LTVLeak.SetColUnit1		   (_colUnit);

#ifdef HMI_CONFIG_TREND_SIGMA
	LTVLeak.SetColValue2			(_colValue);

	LTVLeak.SetColUnit2		   (_colUnit);
#endif	

#if 0
   /* Vm */
   _CellLineIndex++;

   _line = GTable.GetLineOfCell                 (_CellLineIndex,_CellColIndex);
   _colLabel = GTable.GetLeftJustifiedColOfCell (_CellLineIndex,_CellColIndex) - _col;;
   _colValue = GTable.GetLeftJustifiedColOfCell (_CellLineIndex,_CellColIndex + 1) - _col;;
   _colUnit = _colValue + 11;

	LTVVm.SetParent			   (this);

#ifdef HMI_CONFIG_TREND_SIGMA
	LTVVm.InitDbAccess			(DB_TREND_IHM_AVG_VM,
										TREND,
                              DB_TREND_IHM_SIG_VM,
										TREND);

	LTVVm.Init  					(NO,
										(UBYTE**)cMSG_VmReport,
										_line,
										_col,
										9999,
										(UBYTE**)cMSG_MoreOrLess,
										9999,
										(UBYTE**)cMSG_FlowUnit);

   LTVVm.SetColAdjust         (TRUE);
#else
	LTVVm.InitDbAccess			(DB_TREND_IHM_AVG_VM,
										TREND);

	LTVVm.Init  					(NO,
										(UBYTE**)cMSG_VmReport,
										_line,
										_col,
										9999,
										(UBYTE**)cMSG_FlowUnit);
#endif

   LTVVm.SetDivider           (10);

   LTVVm.SetInitNbDigits(TRUE);

	LTVVm.SetSep					((UBYTE *)"");

	LTVVm.SetColLabel			 	(_colLabel);

	LTVVm.SetColValue1			(_colValue);

	LTVVm.SetColUnit1				(_colUnit);

   LTVVm.SetFloatValue1       (TRUE);

   LTVVm.SetFloatValue2       (TRUE);
#endif     

#ifdef HMI_CONFIG_SPO2
   /* SpO2 */
   _CellLineIndex++;

   _line = GTable.GetLineOfCell                 (_CellLineIndex,_CellColIndex);
   _colLabel = GTable.GetLeftJustifiedColOfCell (_CellLineIndex,_CellColIndex) - _col;;
   _colValue = GTable.GetLeftJustifiedColOfCell (_CellLineIndex,_CellColIndex + 1) - _col;;
   _colUnit = _colValue + 11;

	LTVSpo2.SetParent			   (this);
#ifdef HMI_CONFIG_TREND_SIGMA
	/*LTVSpo2.InitDbAccess			(DB_TREND_AVG_SPO2,
                                 TREND,
                                 DB_TREND_SIG_SPO2,
										   TREND);*/

	LTVSpo2.Init  					(NO,
										(UBYTE**)cMSG_Spo2Report,
										_line,
										_col,
										9999,
										(UBYTE**)cMSG_MoreOrLess,
										9999,
										(UBYTE**)cMSG_PerCentUnit);

   LTVSpo2.SetColAdjust         (TRUE);

#else
	/*LTVSpo2.InitDbAccess			(DB_TREND_AVG_SPO2,
										TREND);*/

	LTVSpo2.Init  					(NO,
										(UBYTE**)cMSG_Spo2Report,
										_line,
										_col,
										9999,
										(UBYTE**)cMSG_PerCentUnit);
#endif

   LTVSpo2.SetInitNbDigits(TRUE);

	LTVSpo2.SetSep					((UBYTE *)"");

	LTVSpo2.SetColLabel			(_colLabel);

	LTVSpo2.SetColValue1			(_colValue);

	LTVSpo2.SetColUnit1			(_colUnit);
#endif

   /* IA */
   _CellLineIndex++;
   _col = GTable.GetLeftJustifiedColOfCell (_CellLineIndex,_CellColIndex) - 3;
   _line = GTable.GetLineOfCell                 (_CellLineIndex,_CellColIndex);
   _colLabel = GTable.GetLeftJustifiedColOfCell (_CellLineIndex,_CellColIndex) - _col;
   _colValue = GTable.GetLeftJustifiedColOfCell (_CellLineIndex,_CellColIndex + 1) - _col;;
   _colUnit = _colValue + 11;

	LTVIA.SetParent				(this);

	LTVIA.SetInitNbDigits(TRUE);

	LTVIA.InitDbAccess			(DB_TREND_IHM_IA,
										TREND);

	LTVIA.Init  					(NO,
										(UBYTE**)cMSG_IAReport,
										_line,
										_col,
										9999,
										(UBYTE**)cMSG_eventUnit);


	LTVIA.SetSep					((UBYTE *)"");

	LTVIA.SetColLabel			   (_colLabel);

	LTVIA.SetColValue1			(_colValue);

	LTVIA.SetColUnit1			   (_colUnit);

	LTVIA.SetMaxDisplayValue(999);


#ifdef HMI_CONFIG_SPO2
   /* Fc */
   _CellLineIndex++;

   _line = GTable.GetLineOfCell                 (_CellLineIndex,_CellColIndex);
   _colLabel = GTable.GetLeftJustifiedColOfCell (_CellLineIndex,_CellColIndex) - _col;
   _colValue = GTable.GetLeftJustifiedColOfCell (_CellLineIndex,_CellColIndex + 1) - _col;
   _colUnit = _colValue + 14;

	LTVFc.SetParent			   (this);
   #ifdef HMI_CONFIG_TREND_SIGMA
	/*LTVFc.InitDbAccess			(DB_TREND_AVG_FC,
										TREND,
                              DB_TREND_SIG_FC,
										TREND);*/

	LTVFc.Init  					(HEART,
										NULL,
										_line,
										_col+3,
										9999,
										(UBYTE**)cMSG_MoreOrLess,
										9999,
										(UBYTE**)cMSG_FrequencyUnit);

   LTVFc.SetColAdjust         (TRUE);

   #else
	/*LTVFc.InitDbAccess			(DB_TREND_AVG_FC,
										TREND);*/

	LTVFc.Init  					(HEART,
										NULL,
										_line,
										_col,
										9999,
										(UBYTE**)cMSG_FrequencyUnit);
   #endif

	LTVFc.SetInitNbDigits(TRUE);

	LTVFc.SetSep					((UBYTE *)"");

	LTVFc.SetColLabel		      (_colLabel-3);

	LTVFc.SetColValue1			(_colValue-3);

	LTVFc.SetColUnit1		      (_colUnit-3);

   #ifdef HMI_CONFIG_TREND_SIGMA
   LTVFc.SetColValue2(LTVFc.GetColValue2() - 3);
   LTVFc.SetColUnit2(LTVFc.GetColUnit2() - 3);
   #endif

#endif


   /* Apnée */
   _CellLineIndex++;

   _line = GTable.GetLineOfCell                 (_CellLineIndex,_CellColIndex);
   _colLabel = GTable.GetLeftJustifiedColOfCell (_CellLineIndex,_CellColIndex) - _col;
   _colValue = GTable.GetLeftJustifiedColOfCell (_CellLineIndex,_CellColIndex + 1) - _col;
   _colUnit = _colValue + 14;

	LTVTApnea.SetParent					(this);

	LTVTApnea.InitDbAccess		(DB_TREND_IHM_APNEA,
										TREND);

	LTVTApnea.Init  				(NO,
										(UBYTE**)cMSG_TapneaReport,
										_line,
										_col,
										9999,
										(UBYTE**)cMSG_SecondUnit);

	LTVTApnea.SetInitNbDigits(TRUE);

	LTVTApnea.SetSep				((UBYTE *)"");

	LTVTApnea.SetColLabel		(_colLabel);

	LTVTApnea.SetColValue1		(_colValue);

	LTVTApnea.SetColUnit1		(_colUnit);

	LTVTApnea.SetMaxDisplayValue(999);

#if 0
   /* % Contr */
   _CellLineIndex++;

   _line = GTable.GetLineOfCell                 (_CellLineIndex,_CellColIndex);
   _colLabel = GTable.GetLeftJustifiedColOfCell (_CellLineIndex,_CellColIndex) - _col;
   _colValue = GTable.GetLeftJustifiedColOfCell (_CellLineIndex,_CellColIndex + 1) - _col;
   _colUnit = _colValue + 14;

	LOVContr.SetParent		   (this);

	LOVContr.InitDbAccess		(DB_TREND_IHM_PERCENT_CONTROLLED,
										TREND);


	LOVContr.Init  			   (NO,
										(UBYTE**)cMSG_ContrReport,
										_line,
										_col,
										9999,
										(UBYTE**)cMSG_PerCentUnit);

	LOVContr.SetSep				((UBYTE *)"");

	LOVContr.SetInitNbDigits(TRUE);

	LOVContr.SetColLabel		   (_colLabel);

	LOVContr.SetColValue1		(_colValue);

	LOVContr.SetMaxDisplayValue(100);
	
#endif

   /* % Spont */
   _CellLineIndex++;

   _line = GTable.GetLineOfCell                 (_CellLineIndex,_CellColIndex);
   _colLabel = GTable.GetLeftJustifiedColOfCell (_CellLineIndex,_CellColIndex) - _col;;
   _colValue = GTable.GetLeftJustifiedColOfCell (_CellLineIndex,_CellColIndex + 1) - _col;;
   _colUnit = _colValue + 11;

	LOVSpont.SetParent					(this);

	LOVSpont.InitDbAccess		(DB_TREND_IHM_PERCENT_TRIGGERED,
										TREND);


	LOVSpont.Init  				(NO,
										(UBYTE**)cMSG_SpontReport,
										_line,
										_col,
										9999,
										(UBYTE**)cMSG_PerCentUnit);

	LOVSpont.SetSep				((UBYTE *)"");

	LOVSpont.SetInitNbDigits(TRUE);

	LOVSpont.SetColLabel			(_colLabel);

	LOVSpont.SetColValue1		(_colValue);

	LOVSpont.SetMaxDisplayValue(100);


    _line += 20;
    _col = 8;

    /* Machine Hour and patient counter */

	LOVMachine.SetParent			(this);

	LOVMachine.InitDbAccess		(CURRENT_MACHINE_COUNTER_HOUR_U16,
										CONTROL);

	LOVMachine.Init				(NO,
										(UBYTE**)cMSG_Machine,
										_line,
										_col,
										9999,
				                  (UBYTE**)cMSG_HourUnit);

	LOVMachine.SetColLabel		    (0);

	LOVMachine.SetColSep			(51);

	LOVMachine.SetColValue1		    (59);

	LOVMachine.SetNbDigitValue1(5);

	LOVMachine.SetDisplayZeroValue1(TRUE);


	LTVPatient.SetParent       (this);

   LTVPatient.InitDbAccess    (CURRENT_PATIENT_COUNTER_HOUR_U16,
                              CONTROL,
                              CURRENT_PATIENT_COUNTER_MIN_U16,
                              CONTROL);

   LTVPatient.Init            (NO,
                              (UBYTE**)cMSG_PatWelcome,
                              _line,
                              _col + 130,
                              10,
                              (UBYTE**)cMSG_HourUnit,
                              34,
                              (UBYTE**)cMSG_MinuteUnit);

   LTVPatient.SetColSep       (64);

   LTVPatient.SetColValue1    (73);

   LTVPatient.SetColValue2    (133);

   LTVPatient.SetColUnit2     (153);

   LTVPatient.SetNbDigitValue1(5);

   LTVPatient.SetDisplayZeroValue1(TRUE);

   LTVPatient.SetNbDigitValue2(2);

   LTVPatient.SetDisplayZeroValue2(TRUE);

}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Affichage de l'Objet																	 	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameTendance::Show()
{
   UWORD16 value;

   DataBaseAccess::ReadValue(&value, DB_TREND_IHM_LEAK_MODE, TREND);

	VFrame::Show();
	LTendance.Show();
   LOVVentMoy.Show();
   Date.SetDate(1,1,6);
   Date.Show();
   TableTitle.Show();
	GTable.Show();

	LTVVt.Show();

   if((e_BOOL) value == TRUE)
      LTVLeak.StartMonitoringMode();
   else
	  LTVLeak.StopMonitoringMode();

	LTVLeak.Show();

	LTVFr.Show();

	LTVPi.Show();

#ifndef HMI_CONFIG_TREND_VTE
	LTVVte.StopMonitoringMode();
#else
	LTVVte.Show();
#endif

#ifdef HMI_CONFIG_SPO2
	LTVSpo2.Show();

	LTVFc.Show();
#endif

	LTVIA.Show();

	LTVTApnea.Show();

	LOVSpont.Show();

    LTVPatient.Show();

    LOVMachine.Show();
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Operation de changement de la langue de l'Objet								 	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameTendance::RefreshLanguage()
{
	LTendance.RefreshLanguage();
   LTendance.SetCentered(LTendance.GetCentered());
   LOVVentMoy.RefreshLanguage();
   Date.RefreshLanguage();
   TableTitle.RefreshLanguage();
	LTVLeak.RefreshLanguage();
	LTVFr.RefreshLanguage();
	LTVPi.RefreshLanguage();
#ifdef HMI_CONFIG_TREND_VTE
	LTVVte.RefreshLanguage();
#endif
#ifdef HMI_CONFIG_SPO2
	LTVSpo2.RefreshLanguage();
	LTVFc.RefreshLanguage();
#endif
	LTVIA.RefreshLanguage();
	LTVTApnea.RefreshLanguage();
	LOVSpont.RefreshLanguage();
    LTVPatient.RefreshLanguage();
    LOVMachine.RefreshLanguage();
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Effacement de l'Objet																	 	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I	  	NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE  							  														*/
/******************************************************************************/
void FrameTendance::Hide()
{
	LTendance.Hide();
   LOVVentMoy.Hide();
   Date.Hide();
   TableTitle.Hide();
	GTable.Hide();
	LTVLeak.Hide();
	LTVFr.Hide();
	LTVPi.Hide();
#ifdef HMI_CONFIG_TREND_VTE
	LTVVte.Hide();
#endif
#ifdef HMI_CONFIG_SPO2
	LTVSpo2.Hide();
	LTVFc.Hide();
#endif   
	LTVIA.Hide();
	LTVTApnea.Hide();
	LOVSpont.Hide();
    LTVPatient.Hide();
    LOVMachine.Hide();
    VFrame::Hide();
}
/************************************************************************/
/* Description          : Positionne l'unité de pression                */
/* Parametres en entree : aucun	                                       */
/*		- _PressureUnit : Unité de pression                               */
/* Parametres en sortie : aucun											         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void FrameTendance::SetPressureUnit(UBYTE** _PressureUnit)
{
   e_BOOL _VisibleBackup;

   _VisibleBackup = LTVPi.IsVisible();
   LTVPi.SetVisible(FALSE);
#ifdef HMI_CONFIG_TREND_SIGMA
   LTVPi.SetNameUnit2(_PressureUnit);
#else
   LTVPi.SetNameUnit(_PressureUnit);
#endif
   LTVPi.SetVisible(_VisibleBackup);
}

