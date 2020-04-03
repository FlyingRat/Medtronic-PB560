/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : VEN_Actuators.c                											*/
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
void VEN_Actuators(void)
{

/*%C Previous regulation phase */
static e_VEN_Controller_Phase PreviousControllerPhase = 0;
/*%C Reading the start request in data base */
UWORD16 VentilReq = DB_ConfigRead(VENTIL_REQ_U16);
/*%C Reading if ventilation is allowed in data base */
UWORD16 VentilAuthorization = DB_ControlRead(VENTIL_AUTHORIZATION_U16);
/*%C Reading patient pressure in data base */
SWORD16 MeasurePatientPressure 
						=(SWORD16)DB_ComputeRead(MEASURE_PATIENT_PRESSURE_S16);
/*%C Reading speed blower in data base */
SWORD16 MeasureSpeedBlower = (SWORD16)DB_ComputeRead(MEASURE_SPEED_BLOWER_U16);
/*%C Reading Te counters in data base */
UWORD16 VenTeCount = TIM_ReadCounterValue(VEN_TE_COUNT);
/*%C reading the Adjusted mode */
UWORD16 CurrentMode = DB_ControlRead(CURRENT_MODE_U16);
/*%C Reading  Adjust Pi and Adjust Pe in Data base  */
UWORD16 AdjustPeep = DB_CurrentRead(ADJUST_PEEP_U16);
UWORD16 ComputedPiSetPoint = DB_ComputeRead(COMPUTED_PI_SET_POINT_U16);
UWORD16 AdjustTiControl = DB_CurrentRead(ADJUST_TI_CONTROL_U16);
/* Exhal Flow Use state recovery from base 									  */
UWORD16 ExhalFlowUse = DB_ControlRead(EXHAL_FLOW_USE_U16);
/*%C Reading High pressure in exhalation flag in Data base  */
UWORD16 High_Pressure_Exhalation_Detected =
				 DB_ControlRead(HIGH_PRESSURE_EXHALATION_DETECTED_U16);
/* Pediatric Circuit state recovery from base */
UWORD16 AdjustPediatricCircuit = DB_ConfigRead(ADJUST_PEDIATRIC_CIRCUIT_U16);
/*%C Reading measure Q insp in data base */
SWORD16 MeasureQinsp = (SWORD16)DB_ComputeRead(MEASURE_QINSP_S16);
/* Pediatric Circuit state recovery from base */
   UWORD16 PediatricCircuit = DB_ConfigRead(ADJUST_PEDIATRIC_CIRCUIT_U16);
/*%C Valve detection flag recovery */
UWORD16 ValveDetected = DB_ControlRead(VALVE_DETECTED_U16);
UWORD16 AdjustRamp = DB_CurrentRead(ADJUST_RAMP_U16);
UWORD16 Alarm_Turbine_Overheat = DB_AlarmStatusRead(ALARM_TURBINE_OVERHEAT_U16);
UWORD16 CalibFio2Req = DB_ControlRead(CALIB_FIO2_REQ_U16);

SWORD32 Kp_Insp = 0;
SWORD32 Ki_Insp = 0;
SWORD32 Kp_Exal = 0;
SWORD32 Ki_Exal = 0;
SWORD32 Min = 0;
SWORD32 Max = 0;

/*%C initialization of Kp for volume modes*/
UWORD16 ValveCmd = 0;
static UWORD16 ValveBoost = 0;
e_CalibrationCommand CalibFlowExhReq = DB_ControlRead(CALIB_FLOW_EXH_REQ_U16);

/*%C Reading of the Control Setup to be used */
UWORD16 SetupControlSetPoint = DB_ControlRead(SETUP_CONTROL_SET_POINT_U16);

/*%C First cycle flag */
static BIT FirstExhalationActive = TRUE;

static UWORD16 MutexBlower = FALSE;

static UWORD16 PreviousCurrentMode = PRES;

#ifdef CONFIG_REGUL_O2
/*%C O2 correction variable */
SWORD32 ConsQO2CorrectionInspi = 125 ;
SWORD32 ConsQO2CorrectionExhal = 75 ;
SWORD32 ConsQO2 = 0 ;
#endif


   ///////////////////
   //     IDLE      //
   ///////////////////
/*%C if VentilReq is FALSE or VEN_UnvolontaryStop is TRUE, when no calibration then 					*/
	if ( (CalibFlowExhReq == NO_CALIB)
	&& ( (VentilReq == FALSE) 
	|| (VEN_UnvolontaryStop == TRUE) ) )
	{

		VEN_MutexVanneO2 = FALSE;
/*%C  Initialization of integral values for control									*/
		VEN_IntegralBlower = 0;
		VEN_IntegralValve = 0;
		VEN_VentilationStart = FALSE;

/*%C  Valve closing 																				*/
		VALVE_CMD = cVALVE_CMD_OFF;	 

/*%C  Stop speed blower																			*/
		BLOWER_CMD = cBLOWER_CMD_OFF;
	
		
#ifdef CONFIG_REGUL_O2
/*%C  O2 Valve closed */
		VANNE_O2_CMD = cVALVEO2_CMD_OFF;
		//Initialisation de l'etat de calibration automatique FIO2
	  	DB_AlarmStatusWrite(ALARM_CALIB_FIO2_U16, ALARM_FALSE);
		DB_ControlWrite(CALIB_FIO2_REQ_U16, NO_CALIB);

		VEN_AuthorizationRegulO2 = FALSE;
		VEN_LaunchCalibO2 = FALSE;
#endif

/*%C  If an unvolontary stop has been detected, the start bip is inhibited	 	*/
   		if (VEN_UnvolontaryStop == TRUE)
/*%C  Start bip inhibition after an unvolontary stop 	*/
		{
			VEN_StartBip = FALSE;
		}
/*%C  Unvolontary stop reset 																	*/
		VEN_UnvolontaryStop = FALSE;  


/*%C  Medium breaking over 3000 rpm 														*/
/*%C  Maximum breaking under 3000 rpm 														*/
      	if( MeasureSpeedBlower > 3000 )
		{
			ACT_BrakePower(cPOWER);
     	}
      	else
      	{
   	 		ACT_BrakePower(cPOWER_MAX);
      	}

/*%C  Init timer for speed blower test 													*/
  		TIM_StartDecounter(SEC_SPEED_BLOW_TIM,
  		                   TIME_SPEED_BLOW);
	}
	///////////////////
   //     INIT      //
   ///////////////////
/*%C if VentilReq is TRUE and VentilAuthorization is FALSE, then 					*/
	if ( (VentilReq == TRUE) 
	&& (VentilAuthorization == FALSE) )
	{

	/*%C The detection of the valve hasn't been done yet.*/
		DB_ControlWrite(VALVE_DETECT_IN_PROGRESS_U16,TRUE);

		if (VEN_VentilationStart == FALSE)
		{
/*%C  		Init timer for valve detection 														*/
	  		TIM_StartDecounter(VEN_VALVE_TIM,
	  	                   TIME_VALVE);
			VEN_VentilationStart = TRUE;
		}
/*%C  Call break management with adjust = No brake										*/
		ACT_BrakePower(0);
/*%C  Opening valve 																				*/
		VALVE_CMD = cVALVE_CMD_ON;
/*%C  Call regulation function for speed blower test 									*/
		ACT_BlowerCmd(cVEN_KPB_INIT,
	   				  cVEN_KIB_INIT,	   				  
	   				  cSPEED_BLOWER_TEST,
	   				  CONTROL_SPEED);
/*%C  Call the function for detecting the valve 										*/
		ACT_ValveDetected();

/*%C Active the first cycle flag */
		FirstExhalationActive = TRUE;

		VEN_PerCentRisePI = cVEN_PER_CENT_RISE_PRESS_DEF;
		VEN_PerCentRiseQI = cVEN_PER_CENT_RISE_FLOW_DEF;

		VEN_PressureUpStep = cMIN_STEP;
		VEN_PressureDownStep = cMIN_STEP;
	}

   //////////////////////////
   //  VENTILATION ON      //
   //////////////////////////
/*%C if VentilReq is TRUE and  VentilAuthorization is TRUE, then 					*/
	else if (VentilReq == TRUE 
	&& VentilAuthorization == TRUE)
	{
#ifdef CONFIG_REGUL_O2
/*%C   switch on the phase of the controller :*/ 
		VEN_O2_Autorization();
#endif
		if (ValveDetected == TRUE)
		{
/*%C 		switch on the phase of the controller : 										*/
			switch (VEN_Controller_Phase)
			{
			   /////////////////////////////////
			   //   EXHALATION FALL - VALVE   //
			   /////////////////////////////////
/*%C 			if VEN_Controller_Phase is  VEN_EXH_FALL, 								*/
			case VEN_EXH_FALL :
	          
/*%C 				At the first time, speed blower integral initialization			*/
	            if (VEN_Controller_Phase != PreviousControllerPhase)
				{
					if ( (ExhalFlowUse == FALSE)
					  && (AdjustPediatricCircuit == FALSE)
	  				  && (AdjustPeep > 90) )
					{
					    VEN_IntegralBlower = (SWORD32)cVEN_INTEGRAL_EXH_FALL_FACTOR * (SWORD32)AdjustPeep;
						VEN_IntegralBlower = VEN_IntegralBlower / 10;
						VEN_IntegralBlower = VEN_IntegralBlower + cVEN_INTEGRAL_EXH_FALL_STATIC;
					}
					else
					{
					    VEN_IntegralBlower = cVEN_INTEGRAL_EXH_FACTOR * AdjustPeep;
						if (VEN_IntegralBlower < 1800)
						{
						   VEN_IntegralBlower = 1800;
						}
					}
				}
	

/*%C				If an high pressure is detected:											*/
/*%C				- the valve is open 															*/
/*%C				- the blower is closed 														*/
				if (High_Pressure_Exhalation_Detected == TRUE)
				{
					VALVE_CMD = cVALVE_CMD_OFF;
				}   
					
/*%C 				if the Te counter is lower than VEN_TempRiseOpenValve, then		*/
	            else if (VenTeCount <= VEN_TempRiseOpenValve)
				{
/*%C 				valve opening following a ramp  	 									*/
				 	ValveCmd = (UWORD16)VEN_RiseCompute((SWORD32)VenTeCount,
														  0,
														  cVALVE_CMD_OFF,
														  VEN_TempRiseOpenValve,
														  VEN_CommandFlow/10); 
					ACT_ValveCmd(ValveCmd);
					ValveBoost = 0;
				}
	            else 
				{
/*%C 					Using closed loop on cycle 											*/
					ValveCmd = (UWORD16)(VEN_CommandFlow/10);
					ACT_ValveCmd((UWORD16)(ValveCmd));
				}
	
				// Commande Turbine désactivée
				BLOWER_CMD = cBLOWER_CMD_OFF;
				
				/*%C  Breaking adjust depends on Pe value and on the patient circuit type */
				if (CurrentMode != CPAP) 
				{
					if ((ExhalFlowUse == FALSE)	&& (AdjustPeep > 50))
					{
						ACT_BrakePower((UWORD16)cPOWER_BRAKE_PEP_REGUL_HIGH_SB);
					}
					else
					{
						ACT_BrakePower((UWORD16)cPOWER_BRAKE_PEP_REGUL_DEFAULT);
					}
				}
				MutexBlower = FALSE;
	 					 
#ifdef CONFIG_REGUL_O2
/*%C				O2 regulation function call */
	        	if (VEN_AuthorizationRegulO2 == TRUE)	
	        		{
/*%C					O2 consigne calcul */
				  	ConsQO2 = CMP_O2Consigne();
/*%C					O2 consigne correction */
	           	ConsQO2 = (ConsQO2 * ConsQO2CorrectionExhal) /100;

/*%C					Regulation launch */
		       	ACT_O2ValveCmd(cVEN_KPV_VALVE_O2_INSP, cVEN_KIV_VALVE_O2_INSP, ConsQO2); 
	        		}
/*%C				Else close the O2 valve */	    
	        	else
			   	VANNE_O2_CMD = cVALVEO2_CMD_OFF;
#endif

				break;		   
					  	
				///////////////////////////////////
			   //   EXPIRATION PLATEAU - VALVE  //
				///////////////////////////////////
/*%C 			if VEN_Controller_Phase is  VEN_EXH_PLAT, 								*/
			case VEN_EXH_PLAT :

				if ( (MeasurePatientPressure > AdjustPeep)
				&& (MutexBlower == FALSE)
				&& (ExhalFlowUse == FALSE)
				&& (AdjustPediatricCircuit == FALSE)
				&& (AdjustPeep > 90) )
				{
				    VEN_IntegralBlower = (SWORD32)cVEN_INTEGRAL_EXH_PLAT_FACTOR * (SWORD32)AdjustPeep;
					VEN_IntegralBlower = VEN_IntegralBlower / 10;
					VEN_IntegralBlower = VEN_IntegralBlower + cVEN_INTEGRAL_EXH_PLAT_STATIC;
					MutexBlower = TRUE;
				}
					
/*%C				Setting Off the brake 														*/
	            ACT_BrakePower(0);

	
/*%C Close the Balloon if first cycle */
				if (FirstExhalationActive == TRUE)
				{
				/*%C Open the Valve - Close the Balloon */
					VALVE_CMD = cVALVE_CMD_ON;
				}
				/*%C				If an high pressure is detected:											*/
				/*%C				- the valve is open 															*/
				else if (High_Pressure_Exhalation_Detected == TRUE)
				{
					VALVE_CMD = cVALVE_CMD_OFF;
				}			
				else if (VenTeCount <= VEN_TempRiseOpenValve)
				{
				/*%C 					valve opening following a ramp 	 									*/
			 		ValveCmd = (UWORD16)VEN_RiseCompute((SWORD32)VenTeCount,
														  0,
														  cVALVE_CMD_OFF,
														  VEN_TempRiseOpenValve,
														  VEN_CommandFlow/10);
					ACT_ValveCmd(ValveCmd);
					ValveBoost = 0;
				}
				else if ( (TIM_ReadDecounterValue(ACT_BOOST_FREQ) == 0 )
				  	   && (VenTeCount > cBOOST_TIMER)
				  	   && ((SWORD32)MeasureQinsp < (SWORD32)(VEN_TargetFlow))
					   && (ExhalFlowUse == FALSE)
					   && (AdjustPediatricCircuit == FALSE)
					   && (AdjustPeep > 90) )
				{
					ValveBoost =  ValveBoost + cVALVE_BOOST;
					if (ValveBoost > cVALVE_BOOST_MAX)
					{
						ValveBoost = cVALVE_BOOST_MAX;
					}
					ValveCmd = (UWORD16)(VEN_CommandFlow/10) + ValveBoost; 
					ACT_ValveCmd(ValveCmd);
					TIM_StartDecounter(ACT_BOOST_FREQ,
			 								TIME_BOOST_FREQ);
				}
				else
				{
				/*%C 					Using closed loop on cycle 	  										*/
					ValveCmd = (UWORD16)(VEN_CommandFlow/10) + ValveBoost; 
					ACT_ValveCmd(ValveCmd);
				}
					
/*%C 				Call of the speed blower regulation function 						*/
				Min = VEN_RiseCompute((SWORD32)AdjustPeep,
											 0,
											 KP_B_MIN_PEP_0_8_MIN,
											 80,
											 KP_B_MIN_PEP_0_8_MAX);
/*%C 				If computed Adjust Pe is lower or equals 30 							*/
/*%C 				Call of the rise compute function with adaptated parameters		*/
				if (AdjustPeep <= 30)
				{
					Max = VEN_RiseCompute((SWORD32)AdjustPeep,
												 10,
												 KP_B_MAX_PEP_1_3_MIN,
												 30,
												 KP_B_MAX_PEP_1_3_MAX);
				}
/*%C 				If computed Adjust Pe is over 30 	 									*/
/*%C 				Call of the rise compute function with adaptated parameters		*/
				else
				{
					Max = VEN_RiseCompute((SWORD32)AdjustPeep,
												 40,
												 KP_B_MAX_PEP_4_8_MIN,
												 80,
												 KP_B_MAX_PEP_4_8_MAX);
				}
/*%C 				Call of the speed blower regulation function 						*/

            	Kp_Exal = VEN_RiseCompute((SWORD32)VenTeCount,
            								  0,
            								  Max,
            								  3000,
            								  Min);

				if ( (ExhalFlowUse == FALSE)
					&& (AdjustPediatricCircuit == FALSE)
	  				&& (AdjustPeep > 90) )
			  	{
					Ki_Exal = 800;
				}
				else
				{
					Ki_Exal = KI_B;
				}	
/*%C				If an high pressure is detected:											*/
/*%C				- the blower is closed 														*/
				if (High_Pressure_Exhalation_Detected == TRUE)
				{
					BLOWER_CMD = cBLOWER_CMD_OFF;
				}			
/*%C 				Pe = 0.6 mbar to obtain a rinse flow with Pep = 0 					*/
				else if(AdjustPeep == 0)
				{
					ACT_BlowerCmd(Kp_Exal,
					              Ki_Exal,
					              AdjustPeep + 6,
					              CONTROL_PRESSURE);
				}
/*%C 				else Pe is obtain with adjusted Pe 										*/
				else
				{
					ACT_BlowerCmd(Kp_Exal,
					              Ki_Exal,
					              AdjustPeep,
					              CONTROL_PRESSURE);
				}

#ifdef CONFIG_REGUL_O2
/*%C				O2 regulation function call */
	        	if (VEN_AuthorizationRegulO2 == TRUE)	
	        	{
/*%C					O2 consigne calcul */
				  	ConsQO2 = CMP_O2Consigne();
/*%C					O2 consigne correction */
	           		ConsQO2 = (ConsQO2 * ConsQO2CorrectionExhal) /100;

/*%C					Regulation launch */
		       		ACT_O2ValveCmd(cVEN_KPV_VALVE_O2_INSP, cVEN_KIV_VALVE_O2_INSP, ConsQO2); 
	        	}
/*%C				Else close the O2 valve */
	        	else
				{
			   		VANNE_O2_CMD = cVALVEO2_CMD_OFF;
				}
#endif
				break;

			   //////////////////////////////////
			   //   INSPIRATION RISE - VALVE   //
			   //////////////////////////////////
/*%C 			if VEN_Controller_Phase is  VEN_INSP_RISE, 								*/
			case VEN_INSP_RISE : 
	
/*%C Cancelled the first cycle flag */
				if (FirstExhalationActive == TRUE)
				{
					FirstExhalationActive = FALSE;
				}

/*%C 				Checking if it's a Pressure regulation Type 							*/
	            if (VEN_ControllerType == CONTROL_PRESSURE)    
	            {
/*%C 					Ki computing, depending on delta pressure (Pi - Pe)	 		*/
	              	Ki_Insp = VEN_RiseCompute((SWORD32)ComputedPiSetPoint - 
	              									  (SWORD32)AdjustPeep,
	                                         cVEN_DELTA_KI_MIN_INSP,
	                                         cVEN_KIB_MIN_INSP,
	                                         cVEN_DELTA_KI_MAX_INSP,
	                                         cVEN_KIB_MAX_INSP);
	
/*%C 					Kp computing, depending on delta pressure (Pi - Pe)	 		*/
					Kp_Insp = VEN_RiseCompute((SWORD32)ComputedPiSetPoint -
	               								  (SWORD32)AdjustPeep,
	                                         cVEN_DELTA_KP_MIN_INSP,
	                                         cVEN_KPB_MIN_INSP,
	                                         cVEN_DELTA_KP_MAX_INSP,
	                                         cVEN_KPB_MAX_INSP);
	
/*%C 					Control parameters modification in order to avoid overflow 	*/
/*%C					of more:  -30%																*/
	               Kp_Insp = Kp_Insp + (Kp_Insp * VEN_PerCentRisePI)/100;
	               Ki_Insp = Ki_Insp + (Ki_Insp * VEN_PerCentRisePI)/100;
	
/*%C 					Pressure mode control function call									*/
	               ACT_BlowerCmd(Kp_Insp,
	               				  Ki_Insp,
	               				  VEN_Rise_Pi_Set_Point,
	               				  CONTROL_PRESSURE);		  	            
	            }
	
/*%C 				Flow mode control function call											*/
	            else
	            {
/*%C 					Kp computing for Sinus ramp										*/
					if (AdjustRamp == RAMP_SINUS)
					{
						Kp_Insp = cVEN_KPB_FLOW_SIN;
						Ki_Insp = cVEN_KIB_FLOW_INSP;
					}
/*%C 					Kp computing for rectangle and decelerate ramp 					*/
					else
					{
						Kp_Insp = VEN_RiseCompute((SWORD32)AdjustTiControl,
		                                     cVEN_CMP_KPB_FLOW_TI_MAX,
		                                     cVEN_KPB_FLOW_INSP_MIN,
		                                     cVEN_CMP_KPB_FLOW_TI_MIN,
		                                     cVEN_KPB_FLOW_INSP_MAX);
						Ki_Insp = cVEN_KIB_FLOW_INSP;
/*%C 						Modification of régulation parameters to prohibe overflow of more : -30% */
		       			Kp_Insp = Kp_Insp + (Kp_Insp * VEN_PerCentRiseQI)/100;
		       			Ki_Insp = Ki_Insp + (Ki_Insp * VEN_PerCentRiseQI)/100;
					}
						
	
	
/*%C 					Flow mode control function call										*/
					ACT_BlowerCmd(Kp_Insp,
	               				  Ki_Insp,
	               				  VEN_Qi_Set_Point,
	               				  CONTROL_FLOW);
	            }
/*%C 				Valve opening																	*/
	            VALVE_CMD = cVALVE_CMD_ON;
	
/*%C				Braking off																		*/
	            ACT_BrakePower(0);
	
#ifdef CONFIG_REGUL_O2
/*%C				O2 regulation function call */
	        	if (VEN_AuthorizationRegulO2 == TRUE)	
	        	{
/*%C					O2 consigne calcul */
				  	ConsQO2 = CMP_O2Consigne();
/*%C					O2 consigne correction */
	           		ConsQO2 = (ConsQO2 * ConsQO2CorrectionInspi) /100;

/*%C					Regulation launch */
		       		ACT_O2ValveCmd(cVEN_KPV_VALVE_O2_INSP, cVEN_KIV_VALVE_O2_INSP, ConsQO2); 
	        	}
/*%C				Else close the O2 valve */
	        	else
				{
			   		VANNE_O2_CMD = cVALVEO2_CMD_OFF;
				}
#endif
				break;
	
			   /////////////////////////////////////
			   //   INSPIRATION PLATEAU - VALVE   //
			   /////////////////////////////////////
/*%C 			if VEN_Controller_Phase is  VEN_INSP_PLAT, 								*/
			case VEN_INSP_PLAT : 
	
/*%C				check if the control mode is Pressure 									*/
	            if (VEN_ControllerType == CONTROL_PRESSURE)
	            {
/*%C 					Ki Computing depending on pressure delta (Pi - Pe)				*/
	               Ki_Insp = VEN_RiseCompute((SWORD32)ComputedPiSetPoint -
	               								  (SWORD32)AdjustPeep,
	                                			  cVEN_DELTA_KI_MIN_INSP,
	                                			  cVEN_KIB_MIN_INSP,
			                                   cVEN_DELTA_KI_MAX_INSP,
			                                   cVEN_KIB_MAX_INSP);
	
/*%C 					Kp Computing depending on pressure delta (Pi - Pe)				*/
	               Kp_Insp = VEN_RiseCompute((SWORD32)ComputedPiSetPoint -
	               								  (SWORD32)AdjustPeep,
	                                         cVEN_DELTA_KP_MIN_INSP,
	                                         cVEN_KPB_MIN_INSP,
	                                         cVEN_DELTA_KP_MAX_INSP,
	                                         cVEN_KPB_MAX_INSP);


/*%C					Pressure control function call*/
	               ACT_BlowerCmd(Kp_Insp,
	                             Ki_Insp,
	                             ComputedPiSetPoint,
	                             CONTROL_PRESSURE);		 
	            }
	
	
/*%C 				If control mode is not Pressure => control mode = Flow */ 
	            else
	            {
/*%C 					Kp computing for Sinus ramp										*/
					if (AdjustRamp == RAMP_SINUS)
					{
						Kp_Insp = cVEN_KPB_FLOW_SIN;
					}
/*%C 					Kp computing for rectangle and decelerate ramp 					*/
					else
					{
						Kp_Insp = VEN_RiseCompute((SWORD32)AdjustTiControl,
		                                     cVEN_CMP_KPB_FLOW_TI_MAX,
		                                     cVEN_KPB_FLOW_INSP_MIN,
		                                     cVEN_CMP_KPB_FLOW_TI_MIN,
		                                     cVEN_KPB_FLOW_INSP_MAX);
					}
/*%C					Calling Flow regulation function */
	               ACT_BlowerCmd(Kp_Insp,
	                             cVEN_KIB_FLOW_INSP,
	                             VEN_Qi_Set_Point,
	                             CONTROL_FLOW);
	            }

/*%C 				Valve Opening*/
	            VALVE_CMD = cVALVE_CMD_ON;
/*%C				Braking off*/
	            ACT_BrakePower(0);

#ifdef CONFIG_REGUL_O2
/*%C				O2 regulation function call */
	        	if (VEN_AuthorizationRegulO2 == TRUE)	
	        	{
/*%C					O2 consigne calcul */
				  	ConsQO2 = CMP_O2Consigne();
/*%C					O2 consigne correction */
	           		ConsQO2 = (ConsQO2 * ConsQO2CorrectionInspi) /100;

/*%C					Regulation launch */
		       		ACT_O2ValveCmd(cVEN_KPV_VALVE_O2_INSP, cVEN_KIV_VALVE_O2_INSP, ConsQO2); 
	        	}
/*%C				Else close the O2 valve */
	        	else
				{
			   		VANNE_O2_CMD = cVALVEO2_CMD_OFF;
				}
#endif
				break;
			}
		}
		else
		{
			VEN_LeakActuators();
		}
	}
/*%C Calibrationn control */
	else if (CalibFlowExhReq > NO_CALIB)
	{
		if (CalibFlowExhReq == SEGMENT_1)
		{
/*%C 		Brake: medium speed decrease if over 3000 rpm */
/*%C 		Maximum speed decrease under 3000 rpm */
			BLOWER_CMD = cBLOWER_CMD_OFF;
			if( MeasureSpeedBlower > 3000 )
			{
				ACT_BrakePower(cPOWER);
			}
			else
			{
				ACT_BrakePower(cPOWER_MAX);
			}
		}
/*%C  For Segments over the first */
	   	else
		{
/*%C 		No brake activation */
			ACT_BrakePower(0);
		}

/*%C 	Blower command function call */
		ACT_BlowerCmd(cVEN_KPB_MAINT_FLOW,
   	   			   cVEN_KIB_MAINT_FLOW,
   	   				SetupControlSetPoint,
   	   			   CONTROL_FLOW);
	}
/*%C Up dating the previous ventilation phase */
	PreviousControllerPhase = VEN_Controller_Phase;

/******************************************************************************/
/*%C The O2 Valve	Output is closed when the device dont run or 					*/
/*%C there's disconnection or an turbine overheat										*/
if(VEN_MutexVanneO2 == FALSE)
{
	if ((VentilAuthorization == FALSE)
		|| (Alarm_Turbine_Overheat >= ALARM_TRUE)
		|| (CalibFio2Req == TRUE))
	{
		CD_VANNE_FIO2 = 0; 
	}
/*%C The O2 valve is opened when device runs without overheat & disconnection	*/
 	else
	{
		CD_VANNE_FIO2 = 1; 
	}
}
/******************************************************************************/

	PreviousCurrentMode = CurrentMode;
}