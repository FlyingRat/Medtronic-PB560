/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : VEN_LeakActuators.c             											*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                 		Actuators management                					*/
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter :  NONE                                   					*/
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE 																	*/
/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/
#ifndef _TASKING         
#include "LH_ST10F276.h" 
#include <intrins.h>     
#else                    
#include "regf276e.h"    
#endif                   	
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "Timer_Data.h"
#include "io_declare.h"
#include "define.h"
#include "Ventilation_Constants.h"
#include "DB_Control.h"
#include "DB_Config.h"
#include "DB_Compute.h"
#include "DB_Current.h"
#include "DB_AlarmStatus.h"
#include "Ventilation_Datas.h"
#include "VEN_Actuators.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void VEN_LeakActuators(void)
{

/*%C Previous regulation phase */
static e_VEN_Controller_Phase PreviousControllerPhase = 0;

SWORD16 MeasurePatientPressure 
						=(SWORD16)DB_ComputeRead(MEASURE_PATIENT_PRESSURE_S16);
/*%C Reading Te counters in data base */
UWORD16 VenTeCount = TIM_ReadCounterValue(VEN_TE_COUNT);
/*%C reading the Adjusted mode */
UWORD16 AdjustPeep = DB_CurrentRead(ADJUST_PEEP_U16);
/*%C Current mode recovery from base */
e_MODE_TYPES CurrentMode = DB_ControlRead(CURRENT_MODE_U16);
/* Computed Pi set point recovery from base                */
UWORD16 ComputedPiSetPoint = DB_ComputeRead(COMPUTED_PI_SET_POINT_U16);

SWORD32 Kp_Insp = 0;
SWORD32 Ki_Insp = 0;
static UWORD16 TimeForRiseKpEndBrake = 0;

#ifdef CONFIG_REGUL_O2
/*%C O2 correction variable */
SWORD32 ConsQO2CorrectionInspi = 125 ;
SWORD32 ConsQO2CorrectionExhal = 75 ;
SWORD32 ConsQO2 = 0 ;
#endif

/*%C Valve closing in order to avoid the valve pluging during a leak mode  */
	VALVE_CMD = cVALVE_CMD_OFF;

/*%C Blower command in CPAP mode  */
	if (CurrentMode == CPAP)
	{
		if ( (MeasurePatientPressure > AdjustPeep + 20) 
        || (MeasurePatientPressure < AdjustPeep - 20) )
		{
		   ACT_BlowerCmd(cVEN_KP_PPC_HIGH,
		   				  cVEN_KI_PPC,
		   				  AdjustPeep,
		   				  CONTROL_PRESSURE);
		}
      else
      {				  
      	ACT_BlowerCmd(cVEN_KP_PPC_LOW,
      					  cVEN_KI_PPC,
      					  AdjustPeep,
      					  CONTROL_PRESSURE);
		}

#ifdef CONFIG_REGUL_O2
/*%C	O2 regulation function call */
     	if (VEN_AuthorizationRegulO2 == TRUE)	
     		{
/*%C		O2 consigne calcul */
		  	ConsQO2 = CMP_O2Consigne();
/*%C		O2 consigne correction */
        	ConsQO2 = (ConsQO2 * ConsQO2CorrectionExhal) /100;

/*%C		Regulation launch */
       	ACT_O2ValveCmd(cVEN_KPV_VALVE_O2_INSP, cVEN_KIV_VALVE_O2_INSP, ConsQO2); 
     		}
/*%C	Else close the O2 valve */
     	else
	   	VANNE_O2_CMD = cVALVEO2_CMD_OFF;
#endif
	}
/*%C Blower command for other modes  */
	else
	{
		switch(VEN_Controller_Phase)
		{
	   ////////////////////////////////
	   //   EXHALATION FALL - FUITE  //
	   ////////////////////////////////
	   case VEN_EXH_FALL : 

/*%C 		Brake authorized only during 700ms with patient pressure > Peep +20  */
		   if (VEN_Controller_Phase != PreviousControllerPhase)
			{
		   	VEN_IntegralBlower = cVEN_INTEGRAL_EXH_FACTOR * AdjustPeep;
				if (VEN_IntegralBlower < 1800)
				{
				   VEN_IntegralBlower = 1800;
				}
			}

/*%C 		Brake authorized only during 700ms with patient pressure > Peep +20  */
			if ( (MeasurePatientPressure > AdjustPeep + 20)
			  && (VenTeCount <= cTIME_END_BRAKE) )
			{
				BLOWER_CMD = cBLOWER_CMD_OFF;
		  		ACT_BrakePower(cPOWER);
				TimeForRiseKpEndBrake = VenTeCount; 
			}
			else
			{
/*%C 			Brake desactivation  */
		  		ACT_BrakePower(0);
		      Kp_Insp = VEN_RiseCompute((SWORD32)VenTeCount,
		                               TimeForRiseKpEndBrake,
		                               cVEN_KPB_LEAK_EXH_PLATEAU_START,
		                               cVEN_LEAK_EXH_PLATEAU_RAMP_KP_TIME,
		                               cVEN_KPB_LEAK_EXH_PLATEAU_END);

/*%C 			Pressure control function call  */
				ACT_BlowerCmd(Kp_Insp,
								 cVEN_KIB_LEAK_EXH_PLATEAU,
								 AdjustPeep,
								 CONTROL_PRESSURE);
			}

#ifdef CONFIG_REGUL_O2
/*%C		O2 regulation function call */
	     	if (VEN_AuthorizationRegulO2 == TRUE)	
	     		{
/*%C			O2 consigne calcul */
			  	ConsQO2 = CMP_O2Consigne();
/*%C			O2 consigne correction */
	        	ConsQO2 = (ConsQO2 * ConsQO2CorrectionExhal) /100;
	
/*%C			Regulation launch */
	       	ACT_O2ValveCmd(cVEN_KPV_VALVE_O2_INSP, cVEN_KIV_VALVE_O2_INSP, ConsQO2); 
	     		}
/*%C		Else close the O2 valve */
	     	else
		   	VANNE_O2_CMD = cVALVEO2_CMD_OFF;
#endif
			break;
				
	   ///////////////////////////////////
	   //   EXPIRATION PLATEAU - FUITE  //
	   ///////////////////////////////////
		case VEN_EXH_PLAT :

/*%C 		Brake authorized only during 700ms with patient pressure > Peep +20  */
			if ( (MeasurePatientPressure > AdjustPeep + 20)
			  && (VenTeCount <= cTIME_END_BRAKE) )
			{
				BLOWER_CMD = cBLOWER_CMD_OFF;
		  		ACT_BrakePower(cPOWER);
				TimeForRiseKpEndBrake = VenTeCount; 
			}
			else
			{
/*%C 			Brake desactivation  */
		  		ACT_BrakePower(0);
		      Kp_Insp = VEN_RiseCompute((SWORD32)VenTeCount,
		                               TimeForRiseKpEndBrake,
		                               cVEN_KPB_LEAK_EXH_PLATEAU_START,
		                               cVEN_LEAK_EXH_PLATEAU_RAMP_KP_TIME,
		                               cVEN_KPB_LEAK_EXH_PLATEAU_END);

/*%C 			Pressure control function call  */
				ACT_BlowerCmd(Kp_Insp,
								 cVEN_KIB_LEAK_EXH_PLATEAU,
								 AdjustPeep,
								 CONTROL_PRESSURE);
			}

#ifdef CONFIG_REGUL_O2
/*%C		O2 regulation function call */
	     	if (VEN_AuthorizationRegulO2 == TRUE)	
	     		{
/*%C			O2 consigne calcul */
			  	ConsQO2 = CMP_O2Consigne();
/*%C			O2 consigne correction */
	        	ConsQO2 = (ConsQO2 * ConsQO2CorrectionExhal) /100;
	
/*%C			Regulation launch */
	       	ACT_O2ValveCmd(cVEN_KPV_VALVE_O2_INSP, cVEN_KIV_VALVE_O2_INSP, ConsQO2); 
	     		}
/*%C		Else close the O2 valve */
	     	else
		   	VANNE_O2_CMD = cVALVEO2_CMD_OFF;
#endif
			break;

	   /////////////////////////////////
	   //   INSPIRATION RISE - FUITE  //
	   /////////////////////////////////
		case VEN_INSP_RISE : 

/*%C 		Ki computing function of Pi - Pe delta  */
	      Ki_Insp = VEN_RiseCompute((SWORD32)(ComputedPiSetPoint - AdjustPeep),
	                               cVEN_DELTA_KI_MIN_LEAK_INSP,
	                               cVEN_KIB_MAX_LEAK_INSP,
	                               cVEN_DELTA_KI_MAX_LEAK_INSP,
	                               cVEN_KIB_MIN_LEAK_INSP);

/*%C 		Kp computing function of Pi - Pe delta  */
	      Kp_Insp = VEN_RiseCompute((SWORD32)(ComputedPiSetPoint - AdjustPeep),
	                               cVEN_DELTA_KP_MIN_LEAK_INSP,
	                               cVEN_KPB_MIN_LEAK_INSP,
	                               cVEN_DELTA_KP_MAX_LEAK_INSP,
	                               cVEN_KPB_MAX_LEAK_INSP);

/*%C 		Control parameter modification during the rise phase in order to  */
/*%C 		avoid overpass				 */
	      Kp_Insp = Kp_Insp + (Kp_Insp * VEN_PerCentRisePI) / 100;
	      Ki_Insp = Ki_Insp + (Ki_Insp * VEN_PerCentRisePI) / 100;

/*%C 		Control pressure function call				 */
			ACT_BlowerCmd(Kp_Insp,
							  Ki_Insp,
							  VEN_Rise_Pi_Set_Point,
							  CONTROL_PRESSURE);
															
#ifdef CONFIG_REGUL_O2
/*%C		O2 regulation function call */
	     	if (VEN_AuthorizationRegulO2 == TRUE)	
	     		{
/*%C			O2 consigne calcul */
			  	ConsQO2 = CMP_O2Consigne();
/*%C			O2 consigne correction */
	        	ConsQO2 = (ConsQO2 * ConsQO2CorrectionInspi) /100;
	
/*%C			Regulation launch */
	       	ACT_O2ValveCmd(cVEN_KPV_VALVE_O2_INSP, cVEN_KIV_VALVE_O2_INSP, ConsQO2); 
	     		}
/*%C		Else close the O2 valve */
	     	else
		   	VANNE_O2_CMD = cVALVEO2_CMD_OFF;
#endif
			break;

	   /////////////////////////////////////
	   //   INSPIRATION PLATEAU - FUITE   //
	   /////////////////////////////////////
	   case VEN_INSP_PLAT : 

/*%C 		Ki computing function of Pi - Pe delta  */
	      Ki_Insp = VEN_RiseCompute((SWORD32)(ComputedPiSetPoint - AdjustPeep),
	                               cVEN_DELTA_KI_MIN_LEAK_INSP,
	                               cVEN_KIB_MAX_LEAK_INSP,
	                               cVEN_DELTA_KI_MAX_LEAK_INSP,
	                               cVEN_KIB_MIN_LEAK_INSP);

/*%C 		Kp computing function of Pi - Pe delta  */
	      Kp_Insp = VEN_RiseCompute((SWORD32)(ComputedPiSetPoint - AdjustPeep),
	                               cVEN_DELTA_KP_MIN_LEAK_INSP,
	                               cVEN_KPB_MIN_LEAK_INSP,
	                               cVEN_DELTA_KP_MAX_LEAK_INSP,
	                               cVEN_KPB_MAX_LEAK_INSP);

/*%C 		Control pressure function call				 */
			ACT_BlowerCmd(Kp_Insp,
							  Ki_Insp,
							  ComputedPiSetPoint,
							  CONTROL_PRESSURE);

#ifdef CONFIG_REGUL_O2
/*%C		O2 regulation function call */
	     	if (VEN_AuthorizationRegulO2 == TRUE)	
	     		{
/*%C			O2 consigne calcul */
			  	ConsQO2 = CMP_O2Consigne();
/*%C			O2 consigne correction */
	        	ConsQO2 = (ConsQO2 * ConsQO2CorrectionInspi) /100;
	
/*%C			Regulation launch */
	       	ACT_O2ValveCmd(cVEN_KPV_VALVE_O2_INSP, cVEN_KIV_VALVE_O2_INSP, ConsQO2); 
	     		}
/*%C		Else close the O2 valve */
	     	else
		   	VANNE_O2_CMD = cVALVEO2_CMD_OFF;
#endif
			break;
		}
	}
/*%C Controller phase memorization				 */
	PreviousControllerPhase = VEN_Controller_Phase;
}
