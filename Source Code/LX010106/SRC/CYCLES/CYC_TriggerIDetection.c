/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CYC_TriggerIDetection.c                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                Detection of the Inspiration trigger                 		*/
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter :  NONE                                            		*/
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : UWORD16  TriggerIDetected      								*/
/******************************************************************************/



/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "structure.h"
#include "DB_Compute.h"
#include "DB_Current.h"
#include "DB_Control.h"
#include "Timer_Data.h"
#include "Ventilation_Cycles_Datas.h"
#include "CYC_TriggerIDetection.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/


UWORD16 CYC_TriggerIDetection(void)
{
	UWORD16 VenTeCounter = TIM_ReadCounterValue(VEN_TE_COUNT);
   SWORD16 MeasureQinsp = (SWORD16)DB_ComputeRead(MEASURE_QINSP_S16);
	SWORD16 CurrentQinsp = 0;
	UWORD16 AdjustInspSens = DB_CurrentRead(ADJUST_INSP_SENS_U16);
	UWORD16 AdjustPeep = DB_CurrentRead(ADJUST_PEEP_U16);
   	UWORD16 Vti = DB_ComputeRead(COMPUTED_VTI_U16);
   SWORD16 TriggerIValue = 0; 
	SWORD32 TriggTime = 0;
  	SWORD16 Qinsp_filter = 0;
  	SWORD16 DeltaFlow_filter = 0;
	UWORD16 TriggerIDetected = FALSE;
    SWORD16 MaxAdjustTriggerI = 4;
   static SWORD16 PreviousFlow2_filter = 0;
   static SWORD16 PreviousFlow1_filter = 0;
	static UWORD16 DeltaCompute = 0;

    /*%C Qinsp filter correspond to the equation below : */
    /*%SC Qinsp_filter = (MeausreQinsp + 2 *PreviousFlow1_Filter)/3 */
    /*%C But PreviousFlow1_Filter = PreviousFlow2_Filter	*/
    /*%C So, */
    /*%C Qinsp_filter = (MeasureQinsp + PreviousFlow1_filter + */
    /*%C PreviousFlow2_filter) / 3 */
	Qinsp_filter = (MeasureQinsp + PreviousFlow1_filter + PreviousFlow2_filter) / 3;


	CurrentQinsp =	MeasureQinsp;
    /*%C Compute of the exempted period depending on CYC_Qmax*/

    // trigger lockout interval based on inspired-volume
    if (Vti >= 250)
	{
		TriggTime = VEN_RiseCompute(Vti, 250, cTIME_TRIG_I_MIN, 1900, cTIME_TRIG_I_MAX);
	}
	else
	{
		TriggTime = VEN_RiseCompute(Vti, 50, cTIME_TRIG_I_MIN_PED, 250, cTIME_TRIG_I_MAX_PED);
	}

    switch (AdjustInspSens)
	{
    case TRIGGER_LEVEL_0P:
        TriggTime = 300;
        TriggerIValue = 6;
        MaxAdjustTriggerI = 2;
        break;
    case TRIGGER_LEVEL_1P:
        TriggTime = 500;
        TriggerIValue = 8;
        break;
    case TRIGGER_LEVEL_2:
        TriggerIValue = (AdjustPeep <= 140) ? 11 : 13;
        break;
    case TRIGGER_LEVEL_3:
        TriggerIValue = (AdjustPeep <= 140) ? 13 : 15;
        break;
    case TRIGGER_LEVEL_4:
        TriggerIValue = (AdjustPeep <= 140) ? 14 : 16;
        break;
    case TRIGGER_LEVEL_5:
        TriggerIValue = (AdjustPeep <= 140) ? 16 : 18;
        break;
    default:
        TriggerIValue = 11;
        break;
	}

    /*%C the following compute is done one call out of two */
    /*%C because the callof the function is twice faster than the use*/
	DeltaCompute = DeltaCompute + 1;
    if (DeltaCompute == 2)
	{
        /*%C  RAZ the DeltaCompute */ 
		DeltaCompute = 0; 
        /*%C  Flow delta compute :*/
        /*%C 	DeltaFlow_filter = Qinsp_filter - PreviousFlow2_filter */
		DeltaFlow_filter = Qinsp_filter - PreviousFlow2_filter;

        /*%C  management of flow values stack */
        /*%C  Memorizing the Qinsp value for the next use (PreviousFlow1)*/
		PreviousFlow1_filter = Qinsp_filter;
        /*%C  Memorizing the PreviousFlow value for the next use (PreviousFlow2)*/
		PreviousFlow2_filter = PreviousFlow1_filter;


        /*%C		Flow delta trigger :*/ 
        /*%C if the DeltaFlow_Filter is equal 														*/
        /*%C to or upper than (Trigger value - CounterTe/750), and DeltaFlow_Filter */
        /*%C is equal to or upper than (Trigger value - 4), and  counterTe is  equal */
        /*%C to or upper than trigger time, then*/
        if (  (DeltaFlow_filter >= (TriggerIValue - (SWORD16)(VenTeCounter / 750u))) 
              && (DeltaFlow_filter >= (TriggerIValue - MaxAdjustTriggerI))
              && (VenTeCounter >= TriggTime) )
			{
            /*%C Inspiration Trigger is detected,*/
					TriggerIDetected = TRUE;
        }
        /*%C 		else, */
			else
			{
            /*%C Inspiration trigger is not detected */
		      TriggerIDetected = FALSE;
			}
 	}
    /*%C else,Inspiration trigger is not detected */
	else
	{
		TriggerIDetected = FALSE;
	}

    /*%C If no isnp sens is adjusted,then no trigger is detected. */
    if (AdjustInspSens == TRIGGER_LEVEL_OFF)
	{
		TriggerIDetected = FALSE;
	}

    /*%C the value of trigger state is returned */
	return(TriggerIDetected);
}
