/******************************************************************************/
/*                                                                            */
/* Project N  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : VEN_Compute.c                                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   It schedules the computed operation during ventilation phases          */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "DB_Control.h"
#include "DB_Compute.h"
#include "DB_RTC.h"
#include "DB_Config.h"
#include "Ventilation_Datas.h"
#include "VEN_Compute.h"

#define DECLARATION_VENTILATION_COMPUTE_DATA_H
#include "Ventilation_Compute_Data.h"

#include "io_declare.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void VEN_Compute(void)
{

	UBYTE RTC_Year = (UBYTE)DB_RTCRead(DB_RTC_YEAR_U16);
	UBYTE RTC_Month = (UBYTE)DB_RTCRead(DB_RTC_MONTH_U16);
	UBYTE RTC_Day = (UBYTE)DB_RTCRead(DB_RTC_DAY_U16);
	UBYTE RTC_Hour = (UBYTE)DB_RTCRead(DB_RTC_HOUR_U16);
	UBYTE RTC_Minute = (UBYTE)DB_RTCRead(DB_RTC_MINUTE_U16);

	UWORD16	PC_Hour;
	UWORD16 PC_Min;

	e_VentilState VentilState;
	e_MODE_TYPES Current_Mode = DB_ControlRead(CURRENT_MODE_U16);

	UBYTE VentilAuth = (UBYTE)DB_ControlRead(VENTIL_AUTHORIZATION_U16);
	UBYTE Ventil_Report_Upd = (UBYTE)DB_TrendRead(DB_TREND_VENTIL_REPORT_UPD);
	UBYTE Id;
	UBYTE Index;

	UWORD16 Value;

	UWORD32 Tampon = 0 ; 

	UWORD16 Measure_FIO2 = DB_ComputeRead(MEASURE_FIO2);
    SWORD16 Measure_Patient_Pressure = 0;

	static UBYTE PreviousVentilAuth = FALSE;
	static UBYTE Write_Trend_In_EEPROM = FALSE;
	static UBYTE Exhal_First_Pass = FALSE;

    /*%C If ventilation is ON */
	if (VentilAuth == TRUE)
	{
		/************************************/
		/*       EXHALATION COMPUTE          */
		/*************************************/

		/*%C  Compute sequence during exhalation    */
		   if ( (VEN_Controller_Phase == VEN_EXH_FALL)
			  || (VEN_Controller_Phase == VEN_EXH_PLAT) )
			{

            if ( Exhal_First_Pass == TRUE)
			{
					Exhal_First_Pass = FALSE;
					/*%C Compute Avg and Deviation to ventilation report*/
					CMP_VentilationReport();
			}

		/*%C  During the first exhalation cycle, the inspiratory rise pressure and    */
		/*%C  rinse flow closed loop are made                                         */
		      if ( (CMP_PreviousControllerPhase == VEN_INSP_RISE)
			  	  || (CMP_PreviousControllerPhase == VEN_INSP_PLAT) )
				{
		/*%C     Inspiratory rise pressure closed loop compute */
		         CMP_CalculAutoAdaptInsp();
		/*%C     Rinse flow closed loop compute */
		         CMP_CalculFlowLeak();
				}

		/*%C  Exhalation plateau computed values  */
		      if (VEN_Controller_Phase == VEN_EXH_PLAT)
		      {
			  	CMP_ExhPlatComputings();
			  }

		/*%C  Exhalation computed values  */
		      CMP_ExhalationComputings();
			}

		/*************************************/
		/*      INSPIRATION COMPUTE          */
		/*************************************/

		   else
		   {
            if ( Exhal_First_Pass == FALSE)
				{
					Exhal_First_Pass = TRUE;
					VentilState = DB_ControlRead(VENTIL_STATE_U16);
					if (VentilState == VEN_INSPIRATION_CONTROLED)
					{
						/*%C Increase and Store number cylce controlled */
						Tampon = ((UWORD32)(CMP_VentilReport_Array[DB_TREND_NB_CYCLE_CONTROLLED_MSB]) << 16) 
								| (UWORD32)(CMP_VentilReport_Array[DB_TREND_NB_CYCLE_CONTROLLED_LSB]);
						Tampon = Tampon + 1 ;	
						CMP_VentilReport_Array[DB_TREND_NB_CYCLE_CONTROLLED_MSB] = (UWORD16)(Tampon >> 16); 
						CMP_VentilReport_Array[DB_TREND_NB_CYCLE_CONTROLLED_LSB] = (UWORD16)(Tampon)  ;
					}
					else
					{
						/*%C Increase and Store number cylce trigerred */
						Tampon = ((UWORD32)(CMP_VentilReport_Array[DB_TREND_NB_CYCLE_TRIGERRED_MSB]) << 16) 
								| (UWORD32)(CMP_VentilReport_Array[DB_TREND_NB_CYCLE_TRIGERRED_LSB]);
						Tampon = Tampon + 1 ;	
						CMP_VentilReport_Array[DB_TREND_NB_CYCLE_TRIGERRED_MSB] = (UWORD16)(Tampon >> 16); 
						CMP_VentilReport_Array[DB_TREND_NB_CYCLE_TRIGERRED_LSB] = (UWORD16)(Tampon)  ;

					}

					/*%C Save in the EEPROM every hour*/
					if (RTC_Minute == 1)
					{
						if (Write_Trend_In_EEPROM == FALSE )
						{
                        for (Id = DB_TREND_VENTIL_HOUR ; Id < DB_TREND_IHM_VENTIL_HOUR ; Id ++)
							{
								DB_TrendWrite(Id,CMP_VentilReport_Array[Id]);
							}
							Write_Trend_In_EEPROM = TRUE;
						}
                    else
						{
						/*%C no function */
						}
					}
					else
					{
						Write_Trend_In_EEPROM = FALSE;
					}
				}

		/*%C  Time measure computing (after the first respiration cycle)              */
		/*%C  It's measuring rate, Ti, Te and Ti/Te ratio                             */
		      if (VEN_FirstCycle == TRUE)
				{
		/*%C     The measure is made once, after the end of exhalation                */
		         if ( (CMP_PreviousControllerPhase == VEN_INSP_RISE)
		           || (CMP_PreviousControllerPhase == VEN_INSP_PLAT) )
					{
				      CMP_TimeComputing();
					}
				}

		/*%C  Compute sequence during inspiration    */
				CMP_InspirationComputings();

		/*%C  Compute sequence during inspiration rise    */
		      if (VEN_Controller_Phase == VEN_INSP_RISE)
		      {
				   CMP_InspRiseComputings();
			   }
		/*%C  Compute sequence during inspiration plateau    */
		      if (VEN_Controller_Phase == VEN_INSP_PLAT)
		      {
				   CMP_InspPlatComputings();
			   }
			}
		/*****************************************************/
		/*      INSPIRATION  AND EXHALATION COMPUTE          */
		/*****************************************************/
#ifdef CONFIG_SIMV_MODE		
		/*%C Pi set point computing for PSIMV mode               */
			if (Current_Mode == PSIMV)
			{
				CMP_PiSetPointPsimvMode();
			}
#endif
		/*%C Average pressure compute on one cycle               */
			CMP_AveragePressureComputing();

		/*%C Previous controller phase update               */
		   CMP_PreviousControllerPhase = VEN_Controller_Phase;

		/*%C Leak computings               */
			CMP_LeakComputing();

	}
	/*%c if the ventilation is off */
	else
	{
        /*%C  	VTI and VTE computings init writing in compute base                              */
		DB_ComputeWrite(COMPUTED_VTE_U16, 0);
		DB_ComputeWrite(COMPUTED_VTE_INSP_U16, 0);
		DB_ComputeWrite(COMPUTED_VTI_U16, 0);
		DB_ComputeWrite(COMPUTED_VTI_EXH_S16, 0);
		VEN_LeakFactorCptValues = 0;
		DB_ComputeWrite(COMPUTED_FIO2,Measure_FIO2/10);

        // update LPF_PATIENT_PRESSURE_S16 when ventilation is off
        Measure_Patient_Pressure =  (SWORD16)DB_ComputeRead(MEASURE_PATIENT_PRESSURE_S16);
        DB_ComputeWrite(LPF_PATIENT_PRESSURE_S16,Measure_Patient_Pressure);

	/*%C Initialization of CMP_SetPoint_Mutex to restart the ventilation */
	/*%C with the first adjusted Pi*/ 
		CMP_SetPoint_Mutex = FALSE;
	}

    /*%C Save the ventilation report variables in the trend's base */
    /*%C when the ventilation is turned off */
	if ((PreviousVentilAuth == TRUE) && (VentilAuth == FALSE))
	{
        for (Id = DB_TREND_VENTIL_HOUR ; Id < DB_TREND_IHM_VENTIL_HOUR ; Id ++)
		{
			DB_TrendWrite(Id,CMP_VentilReport_Array[Id]);
		}
		PreviousVentilAuth = FALSE;
	}
	else if ((PreviousVentilAuth == FALSE )&& (VentilAuth == TRUE))
	{
		PreviousVentilAuth = TRUE;
	}
	else
	{
		/*%C no function */
	}


	if (	(RTC_Day 	!= (UBYTE)(CMP_VentilReport_Array[DB_TREND_SAVE_RTC_DAY]))
		||	(RTC_Month 	!= (UBYTE)(CMP_VentilReport_Array[DB_TREND_SAVE_RTC_MONTH]))
		||	(RTC_Year 	!= (UBYTE)(CMP_VentilReport_Array[DB_TREND_SAVE_RTC_YEAR])))
	{
		if (RTC_Hour >= 8)
		{
	 	 	if (Ventil_Report_Upd == FALSE)
			{
				/*%C Copy the part of trend base computed value in the part */
				/*%C display value */
                for (Id = DB_TREND_VENTIL_HOUR ; Id < DB_TREND_SAVE_PC_HOUR ; Id++)
				{
					Value = CMP_VentilReport_Array[Id];
					Index = Id + DB_TREND_IHM_VENTIL_HOUR;
					DB_TrendWrite(Index, Value);
				}

				/*%C Re-Initialize the TrendEvent and the DB_Trend */
                for (Id = DB_TREND_VENTIL_HOUR ; Id < DB_TREND_IHM_VENTIL_HOUR ; Id ++)
				{
				 	CMP_VentilReport_Array[Id] = 0;
					DB_TrendWrite(Id,0);
				}

				/*%C Save the date in the trend base */
				CMP_VentilReport_Array[DB_TREND_SAVE_RTC_DAY] = RTC_Day;
				CMP_VentilReport_Array[DB_TREND_SAVE_RTC_MONTH] = RTC_Month;
				CMP_VentilReport_Array[DB_TREND_SAVE_RTC_YEAR] = RTC_Year;
				DB_TrendWrite(DB_TREND_SAVE_RTC_DAY,RTC_Day);
				DB_TrendWrite(DB_TREND_SAVE_RTC_MONTH,RTC_Month);
				DB_TrendWrite(DB_TREND_SAVE_RTC_YEAR,RTC_Year);

				/*%C Save the patient counter in the base */
				PC_Hour = DB_ControlRead(CURRENT_PATIENT_COUNTER_HOUR_U16);
				PC_Min = DB_ControlRead(CURRENT_PATIENT_COUNTER_MIN_U16 );
				CMP_VentilReport_Array[DB_TREND_SAVE_PC_HOUR] = PC_Hour;
				CMP_VentilReport_Array[DB_TREND_SAVE_PC_MIN] = PC_Min;
				DB_TrendWrite(DB_TREND_SAVE_PC_HOUR,PC_Hour); 
			    DB_TrendWrite(DB_TREND_SAVE_PC_MIN,PC_Min);

				/*%C Save the trend's flag update */
				Ventil_Report_Upd = TRUE;
				DB_TrendWrite(DB_TREND_VENTIL_REPORT_UPD,Ventil_Report_Upd);
			}
			else
			{
				/*%C No function */
			}
		}
		else
		{
			/*%C No function */
		}

    }
	else
	{
		if (Ventil_Report_Upd == TRUE)
		{
			Ventil_Report_Upd = FALSE;
			DB_TrendWrite(DB_TREND_VENTIL_REPORT_UPD,Ventil_Report_Upd);
		}
		else
		{
			/*%C No function */
		}
	}
}
