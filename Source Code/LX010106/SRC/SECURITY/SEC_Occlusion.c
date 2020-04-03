/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_Occlusion.c                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                  Management of the occlusion alarm                       */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : Alarm_Error                                           */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES                               */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "Timer_Data.h"
#include "DB_Event.h"
#include "DB_Compute.h"
#include "DB_Control.h"
#include "DB_AlarmStatus.h"
#include "SEC_Occlusion.h"
#include "Security_Datas.h"
#include "Ventilation_Datas.h"
#include "Ventilation_Compute_Data.h"

/* locate security code to specific section */
#include "locate_security_code.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/* Function is called from leak configuration and non-leak configurations     */
/* and is used to control the occlusion check circuit* alarm.  If a leak is   */
/* present during leak configurations we know an occlusion is not possible.   */
/* This helps in the reduction of nusiance alarms during this configuration.  */
/* If further reduction during non-leak configurations use                    */
/* (ELeakCoeff > cDETECTION_LEAK_CRITERIA) criteria that is found in          */
/* SYS_PressionChoice.c                                                       */
/*                                                                            */
/******************************************************************************/
e_ALARM_ERROR SEC_Occlusion(void)
{
/*%C AlarmOcclusion recovery from base                                       */
	e_DB_ALARMS_STATE AlarmOcclusion = DB_AlarmStatusRead(ALARM_OCCLUSION_U16);
/*%C ComputedVti recovery from base                                          */
	SWORD16 ComputedVti = (SWORD16)DB_ComputeRead(COMPUTED_VTI_U16);
/*%C ComputedPip recovery from base                                          */
	UWORD16 ComputedPip = DB_ComputeRead(COMPUTED_PIP_U16);
/*%C ComputedPiSetPoint recovery from base                                   */
	UWORD16 ComputedPiSetPoint = DB_ComputeRead(COMPUTED_PI_SET_POINT_U16);
/*%C VentilState recovery from base                                          */
	UWORD16 VentilState = DB_ControlRead(VENTIL_STATE_U16);
/*%C Leak from base                                                          */
	UWORD16 QLeak = DB_ComputeRead(COMPUTED_LEAK_HMI_U16);
	UWORD16 ValveDetected = DB_ControlRead(VALVE_DETECTED_U16);
/*%C Initialisation of static and local variables                            */
	static e_VentilState MemoVentilState = VEN_VENTIL_DISABLE;
	static UWORD16 CycleCount = 0;
	UWORD16 ComputedPipMin = 0;
	UWORD16 ComputedPipMax = 0;
	e_ALARM_ERROR Alarm_Error = NO_ERR_AL;

// "The obstruction TECHNICAL ALARM CONDITION shall be HIGH PRIORITY.
//  The maximum ALARM CONDITION DELAY shall be no more than two    
//  breath cycles or 5 s, whichever is greater."                    
	const UWORD16 MAX_OCCLUSION_TIMER_DELAY = 5000;  // 5 secs
	const UWORD16 MAX_NUM_BREATHS_FOR_OCCLUSION_DETECTION = 2;

/*%C ComputedPipMin = 80% COMPUTED_PI_SET_POINT_U16                           */
	ComputedPipMin = (ComputedPiSetPoint * 8) / 10;
/*%C ComputedPipMax = 120% COMPUTED_PI_SET_POINT_U16                          */
	ComputedPipMax = (ComputedPiSetPoint * 12) / 10;

/*%C Check ALARM_OCCLUSION_U16 state                                          */
	switch (AlarmOcclusion)
	{
/******************************************************************************/
/*%C                                  "FALSE" State                           */
/******************************************************************************/
	case ALARM_FALSE :
		// If there is a leak we know we can not possibly have an occlusion
		// this is especially helpful in the reduction of nuisance alarms
		// when the mask shifts and leaks are transitory
		// Also, if patient effort is detected then the occlusion alarm
		// shall not be activated for this current breath.
/*%C    If COMPUTED_VTI_U16 < cVTI_MIN and COMPUTED_PIP_U16 > ComputedPipMin  */
/*%C    and COMPUTED_PIP_U16 < ComputedPipMax, and QLeak == 0 and */
/*%C    VEN_DetectedNegativeFlow == FALSE and                     */
/*%C    valveDetected == FALSE then                               */
		if ((ComputedVti <  cVTI_MIN)
			&& (ComputedPip > ComputedPipMin)
			&& (ComputedPip < ComputedPipMax)
			&& (VEN_DetectedNegativeFlow == FALSE)
		   )
		{
			if ((TRUE == ValveDetected) ||
				((FALSE == ValveDetected) && (QLeak == 0)))
			{
/*%C        ALARM_OCCLUSION_U16 = ALARM_DETECTED                              */
				DB_AlarmStatusWrite(ALARM_OCCLUSION_U16, ALARM_DETECTED);
/*%C        Init of cycles counter CycleCount                                 */
				CycleCount = 0; 
				/*%C 		Occlusion Alarm Timer is started    										  */
				TIM_StartDecounter(SEC_OCCLUSION_TIMER,
								   MAX_OCCLUSION_TIMER_DELAY);
			}
		}
/*%C    End if                                                                */
/*%C    Alarm_Error = NO_ERR_AL                                               */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C                                  "DETECTED" State                        */
/******************************************************************************/
	case ALARM_DETECTED :
/*%C    If COMPUTED_VTI_U16 > cVTI_MIN or COMPUTED_PIP_U16 < ComputedPipMin   */
/*%C    or COMPUTED_PIP_U16 > ComputedPipMax, or QLeak > 0 and */
/*%C    valveDetected == FALSE or if COMPUTED_VTI_U16 < cVTI_MIN              */
/*%C    and VEN_DetectedNegativeFlow == TRUE then                             */
		if ((ComputedVti >= cVTI_MIN)
			|| (ComputedPip <= ComputedPipMin)
			|| (ComputedPip >= ComputedPipMax)
			|| ((FALSE == ValveDetected) && (QLeak > 0))
			|| (VEN_DetectedNegativeFlow == TRUE)			   
		   )
		{
/*%C        Init of cycles counter CycleCount                                 */
			CycleCount = 0;
/*%C        ALARM_OCCLUSION_U16 = ALARM_FALSE                                 */
			DB_AlarmStatusWrite(ALARM_OCCLUSION_U16, ALARM_FALSE);
		    Alarm_Error = NO_ERR_AL;
			break;
		}
/*%C    End if                                                                */
/*%C    If ( VENTIL_STATE_U16 = VEN_INSPIRATION_CONTROLED or                  */
/*%C    VENTIL_STATE_U16 = VEN_INSPIRATION_TRIGGERED) and                     */
/*%C    MemoVentilState == VEN_EXHALATION, then                               */
		if (((VentilState == VEN_INSPIRATION_CONTROLED)
			 || (VentilState == VEN_INSPIRATION_TRIGGERED))
			&& (MemoVentilState == VEN_EXHALATION))
		{
/*%C        The cycle counter CycleCount is increased                         */
			CycleCount = CycleCount + 1;
		}
/*%C    End if                                                                */

/*%C    According to ISO 80601-2-72_2015                                      */
/*%C    201.12.4.107 * Obstruction ALARM CONDITION                            */
/*%C        "The obstruction TECHNICAL ALARM CONDITION shall be HIGH PRIORITY.*/
/*%C         The maximum ALARM CONDITION DELAY shall be no more than two      */
/*%C         breath cycles or 5 s, whichever is greater."                     */
		if (TIM_ReadDecounterValue(SEC_OCCLUSION_TIMER) == 0)
		{
			if (CycleCount >= MAX_NUM_BREATHS_FOR_OCCLUSION_DETECTION)
			{
				/*%C        ALARM_OCCLUSION_U16 = ALARM_TRUE                                  */
				DB_AlarmStatusWrite(ALARM_OCCLUSION_U16, ALARM_TRUE);
				/*%C        Associated event is stored                                        */
				DB_EventMngt(EVENT_AL_OCCLUSION);
				/*%C        Updating priority register                                        */
				SEC_High_Priority_1 = SEC_High_Priority_1 | 0x1000;
			}
		}
/*%C    End if                                                                */
/*%C    Alarm_Error = NO_ERR_AL                                               */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C                                  "TRUE" State                            */
/******************************************************************************/
	case ALARM_TRUE :
/*%C    The following state ,"ALARM_DISPLAYED", is written by HMI module.     */
/*%C    So there is no action to do.                                          */
/*%C    Alarm_Error = NO_ERR_AL                                               */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C                                  "DISPLAYED" State                       */
/******************************************************************************/
	case ALARM_DISPLAYED    :
/*%C    If COMPUTED_VTI_U16 > cVTI_MIN or COMPUTED_PIP_U16 < ComputedPipMin   */
/*%C    or COMPUTED_PIP_U16 > ComputedPipMax, or QLeak > 0 and */
/*%C    valveDetected == FALSE or if COMPUTED_VTI_U16 < cVTI_MIN              */
/*%C    and VEN_DetectedNegativeFlow == TRUE then                             */
		if ((ComputedVti >= cVTI_MIN)
			|| (ComputedPip <= ComputedPipMin)
			|| (ComputedPip >= ComputedPipMax)
			|| ((FALSE == ValveDetected) && (QLeak > 0))
			|| (VEN_DetectedNegativeFlow == TRUE)
		   )
		{
/*%C        Init of cycles counter CycleCount                                 */
			CycleCount = 0;
/*%C        ALARM_OCCLUSION_U16 = ALARM_FALSE                                 */
			DB_AlarmStatusWrite(ALARM_OCCLUSION_U16, ALARM_FALSE);
/*%C        Associated event is stored                                        */
			DB_EventMngt(EVENT_AL_END_OCCLUSION);
/*%C        Updating priority register                                        */
			SEC_High_Priority_1 = SEC_High_Priority_1 & 0xEFFF;
		}
/*%C    End if                                                                */
/*%C    Alarm_Error = NO_ERR_AL                                               */
		Alarm_Error = NO_ERR_AL;
		break;
/******************************************************************************/
/*%C                                  "CANCELED" State                        */
/******************************************************************************/
	case ALARM_CANCELED :
/*%C    Alarm_Error = ERR_AL_OCCLUSION                                        */
		Alarm_Error = ERR_AL_OCCLUSION;
		break;
/******************************************************************************/
/*%C                                  DEFAULT                                 */
/******************************************************************************/
	default:
/*%C    Alarm_Error = ERR_AL_OCCLUSION                                        */
		Alarm_Error = ERR_AL_OCCLUSION;
		break;
	}
/*%C End of check alarm state                                                 */
/*%C Updating the memory of the ventil state MemoVentilState                  */
	MemoVentilState = VentilState;
	return (Alarm_Error);
}

