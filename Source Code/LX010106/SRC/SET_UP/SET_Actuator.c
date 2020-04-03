/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SET_Actuator.c                											*/
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
#include "io_declare.h"
#include "define.h"
#include "Ventilation_Constants.h"
#include "DB_Control.h"
#include "DB_Config.h"
#include "DB_Compute.h"
#include "DB_Current.h"
#include "System_Datas.h"
#include "Ventilation_Datas.h"
#include "SET_Actuator.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void SET_Actuator(void)
{

	UWORD16 RegulType = 0;
	UWORD16  Consigne = 0;
   SWORD16 PatientPressure = 
   							(SWORD16)DB_ComputeRead(MEASURE_PATIENT_PRESSURE_S16);
   SWORD16 SpeedBlower = (SWORD16)DB_ComputeRead(MEASURE_SPEED_BLOWER_U16);
	UWORD16 PatientPressRequest = 0; 
	UWORD16 InspFlowRequest = 0;
	UWORD16 ExhFlowRequest = 0;
	UWORD16 ValvePressRequest = 0;
    UWORD16 O2ValveCmd = 0; 
	UWORD16 O2FlowRequest = 0; 

	e_CalibrationCommand CalibFasValveReq = DB_ControlRead(CALIB_FAS_VALVE_REQ_U16);

	static UWORD16 MemPatPressReq = 0;
	static UWORD16 MemInspFlowReq = 0;
	static UWORD16 MemExhFlowReq = 0;
	static UWORD16 MemValvPressReq = 0;
	static UWORD16 MemO2FlowReq = 0;
	static UWORD16 MemCalibFasValveReq = 0;

   //////////////////////////
   //   MAINTENANCE MODE   //
   //////////////////////////

/*%C  Reading of the Control Type to be used */
	   RegulType = DB_ControlRead(SETUP_CONTROL_TYPE_U16);
/*%C  Reading of the Control Setup to be used */
	   Consigne = DB_ControlRead(SETUP_CONTROL_SET_POINT_U16);
/*%C  Reading sensors to be calibrated */
	   PatientPressRequest = DB_ControlRead(CALIB_PATIENT_PRESS_REQ_U16);
	   InspFlowRequest = DB_ControlRead(CALIB_FLOW_INSP_REQ_U16);
       ExhFlowRequest =  DB_ControlRead(CALIB_FLOW_EXH_REQ_U16);
	   ValvePressRequest = DB_ControlRead(CALIB_VALVE_PRESS_REQ_U16);
	   O2FlowRequest = DB_ControlRead(CALIB_FLOW_O2_REQ_U16);
/*%C  Reading O2 Valve Command */ 
 	   O2ValveCmd = DB_ControlRead(VALVE_O2_CMD_U16); 

/*%C  Updating of Patient pressure previous state of calibration request */
/*%C  If the request is different	from previous state */
/*%C  And different from a test of limits request */
/*%C  and differnt from the result of test limits, OK or Not OK */
   	if((PatientPressRequest != MemPatPressReq)
   	&& (PatientPressRequest != TEST_LIMITES_REQUEST)
   	&& (PatientPressRequest != TEST_LIMITES_OK )
   	&& (PatientPressRequest != TEST_LIMITES_FALSE))
		{
			MemPatPressReq = PatientPressRequest;
		}
/*%C  Updating of Insp. Flow previous state of caliration request */
/*%C  If the request is different	from previous state */
/*%C  And different from a test of limits request */
/*%C  and differnt from the result of test limits, OK or Not OK */
    	if((InspFlowRequest != MemInspFlowReq)
    	&& (InspFlowRequest != TEST_LIMITES_REQUEST)
   	&& (InspFlowRequest != TEST_LIMITES_OK)
   	&& (InspFlowRequest != TEST_LIMITES_FALSE))
		{
			MemInspFlowReq = InspFlowRequest;
		}
/*%C  Updating of Exhalation Flow previous state of caliration request */
/*%C  If the request is different	from previous state */
/*%C  And different from a test of limits request */
/*%C  and differnt from the result of test limits, OK or Not OK */
    	if((ExhFlowRequest != MemExhFlowReq)
    	&& (ExhFlowRequest != TEST_LIMITES_REQUEST)
   	&& (ExhFlowRequest != TEST_LIMITES_OK)
   	&& (ExhFlowRequest != TEST_LIMITES_FALSE))
		{
			MemExhFlowReq = ExhFlowRequest;
		}
/*%C  Updating of Fas Valve previous state of caliration request */
/*%C  If the request is different	from previous state */
/*%C  And different from a test of limits request */
/*%C  and differnt from the result of test limits, OK or Not OK */
    	if((CalibFasValveReq != MemCalibFasValveReq)
    	&& (CalibFasValveReq != TEST_LIMITES_REQUEST)
   	&& (CalibFasValveReq != TEST_LIMITES_OK)
   	&& (CalibFasValveReq != TEST_LIMITES_FALSE))
		{
			MemCalibFasValveReq = CalibFasValveReq;
		}
/*%C  Updating of Valve pressure previous state of caliration request */
/*%C  If the request is different	from previous state */
/*%C  And different from a test of limits request */
/*%C  and differnt from the result of test limits, OK or Not OK */
	  	if((ValvePressRequest != MemValvPressReq)
	  	&& (ValvePressRequest != TEST_LIMITES_REQUEST)
   	&& (ValvePressRequest != TEST_LIMITES_OK)
   	&& (ValvePressRequest != TEST_LIMITES_FALSE))
		{
			MemValvPressReq = ValvePressRequest;
		}

/*%C  Updating of O2 Flow previous state of caliration request */
/*%C  If the request is different	from previous state */
/*%C  And different from a test of limits request */
/*%C  and differnt from the result of test limits, OK or Not OK */
	  	if((O2FlowRequest != MemO2FlowReq)
	  	&& (O2FlowRequest != TEST_LIMITES_REQUEST)
   	&& (O2FlowRequest != TEST_LIMITES_OK)
   	&& (O2FlowRequest != TEST_LIMITES_FALSE))
		{
			MemO2FlowReq = O2FlowRequest;
		}

/*%C  For all sensors, during Calibration or Auto calibration of 1st segment */ 
   	if(((MemPatPressReq == SEGMENT_1)
   	|| (MemPatPressReq == AUTOCALIB_SEG_1)) 
   	|| ((MemInspFlowReq == SEGMENT_1)
   	|| (MemInspFlowReq == AUTOCALIB_SEG_1))
      || ((MemExhFlowReq == SEGMENT_1)
      || (MemExhFlowReq == AUTOCALIB_SEG_1))
    	|| ((MemValvPressReq == SEGMENT_1)
    	|| (MemValvPressReq == AUTOCALIB_SEG_1))
    	|| ((MemO2FlowReq == SEGMENT_1)
    	|| (MemO2FlowReq == AUTOCALIB_SEG_1))
		|| (SYS_CalibProcessing == FALSE))
		{
			VANNE_O2_CMD = cVALVEO2_CMD_OFF;
/*%C 		Brake: medium reduce speed if over 3000 rpm */
/*%C 		Maximum reduce speed under 3000 rpm */
			if( ( RegulType != CONTROL_SPEED)
			||  ((RegulType == CONTROL_SPEED) && (Consigne == 0)))
			{	
				BLOWER_CMD = cBLOWER_CMD_OFF;
				if( SpeedBlower > 3000 )
	         {
	         	ACT_BrakePower(cPOWER);
				}
	         else
	         {
	          	ACT_BrakePower(cPOWER_MAX);
				}
			}

			if(SYS_CalibProcessing == FALSE)
			{
				DB_ControlWrite(CALIBRATION_MODE_U16, FALSE);
			}
			else
			{
				DB_ControlWrite(CALIBRATION_MODE_U16, TRUE);
			}
		}
/*%C  For Segments over the first */
	   else
		{
/*%C 		No brake activation */
			ACT_BrakePower(0);
			DB_ControlWrite(CALIBRATION_MODE_U16, FALSE);
		}

/*%C  Send parameters coresponding to Control pressure */
		if(RegulType == CONTROL_PRESSURE_MAINT)
		{             
			ACT_BlowerCmd(cVEN_KPB_MAINT_PRESS,
 						  	  cVEN_KIB_MAINT_PRESS,
 						  	  Consigne,
 						  	  CONTROL_PRESSURE_MAINT);
		}
/*%C  Send parameters coresponding to Control flow */
		else if(RegulType == CONTROL_FLOW)
		{             
			ACT_BlowerCmd(cVEN_KPB_MAINT_FLOW,
   	   				  cVEN_KIB_MAINT_FLOW,
   	   				  Consigne,
   	   				  CONTROL_FLOW);
		}
/*%C  Send parameters coresponding to Control exhalation flow */
		else if(RegulType == CONTROL_FLOW_EXH)
		{
 			ACT_BlowerCmd(cVEN_KPB_MAINT_FLOW,
   	   				  cVEN_KIB_MAINT_FLOW,
   	   				  Consigne,
   	   				  CONTROL_FLOW_EXH);
		}
/*%C  Send parameters corresponding to Speed Control */
		else if(RegulType == CONTROL_SPEED)
		{             
			ACT_BlowerCmd(cVEN_KPB_MAINT_SPEED,
 							  cVEN_KIB_MAINT_SPEED,
   	   				  Consigne,
   	   				  CONTROL_SPEED);
		}
/*%C  Send parameters corresponding to Flow O2 Control */
		else if(  (RegulType == CONTROL_FLOW_O2) 
				 && (MemO2FlowReq != SEGMENT_1)
    			 && (MemO2FlowReq != AUTOCALIB_SEG_1))
		{             
			ACT_O2ValveCmd(cVEN_KPVO2_MAINT_FLOW_O2,
						   cVEN_KIVO2_MAINT_FLOW_O2,
						   (SWORD32)Consigne);
		}
/*%C  Send parameters corresponding to Flow O2 Control */
		else if(RegulType == CONTROL_FLOW_O2_MANUEL)
		{             
			VANNE_O2_CMD = cVALVEO2_CMD_OFF - (UWORD16)Consigne;
		}
		else if(RegulType == CONTROL_PRESSURE_O2)
		{             
			VANNE_O2_CMD = cVALVEO2_CMD_ON;
		}
/*%C  Close the valve ( Baloon open )	*/
		if ( (CalibFasValveReq == NO_CALIB)
		  && (PatientPressRequest == NO_CALIB) )
		{
   			VALVE_CMD = cVALVE_CMD_OFF;
		}
		else if ( (CalibFasValveReq == NO_CALIB)
		  && (PatientPressRequest >= NO_CALIB) )
		{
			VALVE_CMD = cVALVE_CMD_ON;
		}
//    VALVE_CMD = DB_ComputeRead(DEB_SETUP_CMD_VALVE);


/*%C O2 Valve Open during the max speed blower test */ 
    if (O2ValveCmd == TRUE) 
    { 
 		CD_VANNE_FIO2 = 1;  
	} 
/*%C O2 Valve Close after the max speed blower test */ 
	else 
	{ 
	    CD_VANNE_FIO2 = 0;  
	} 
}
