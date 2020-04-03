/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_IhmAccessParaDataBase.h    				                  		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	datas for database operations				*/
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameters :  			None          			                  		*/
/*%IO Input/Output Parameters :  None          			                  		*/
/*%O 	Output Parameters :  		None         			                  		*/
/******************************************************************************/
#ifndef IHMACCESSPARADATABASE_H
#define IHMACCESSPARADATABASE_H

#include "DB_Compute.h"
#include "DB_PowerSupply.h"
/* NONE fixed to 0xAAAA */
#define NONE 0xAAAA

/******************************************************************************/
/*                             #DEFINE		                        				*/
/******************************************************************************/
/* USB monitoring transfert */
#define cUSB_MONIT_THRESHOLD_FOR_NEW_STEP 24
#define cUSB_MONIT_NEW_STEP 12

/* Rise time number values                        	                           */
#define cRISE_TIME 4U

/* Delta rise time (in ms)                 	                                 */
#define cDELTA_RISE_TIME  300U

/* Speed communication */
#define cCommunication_Speed	19200u;

/* SIMV min rate                                	                           */
#define cSIMV_BACKUP_R_MIN 8U

/* Constant limits déclaration in VOL, PRES, PSV and VSIMV mode	 */

#define cAlarmRHysteresis						5U
#define cPeepLowPipHysteresis					20U
#define cPeepHighPipHysteresis				100U
#define cPiHighPipHysteresis					20U
#define cLowPipHighPipHysteresis				80U
#define cLowVtiHighVtiHysteresis				20U
#define cVolControlLowVtiHysteresis	   	10U
#define cVolControlHighVtiHysteresis		10U
#define cLowVteHighVteHysteresis				20U
#define cVolControlLowVteHysteresis			10U
#define cVolControlHighVteHysteresis		10U
#define cLowVmHighVmHysteresis				10U
#define cLowVmVolumePerMinuteHysteresis	5U
#define cHighVmVolumePerMinuteHysteresis	5U
#define cPControlPiMaxHysteresis				200U
#define cPSupportPiMaxHysteresis				200U
#define cVolControlSighVtCoefMax				2000U
#define cLowVteTargetVtHysteresis			10U
#define cHighVteTargetVtHysteresis			10U
#define cHighRBackupR 							5U
#define cControlRBackupR 						2U
#define cPeepPi 									50U
#define cPeepMinLeak 				  			40U
#define cDeltaHighLowFio2 				  		10U

// VOL AC and V SIMV flow constraints
#define cPeakFlowMin				3U
#define cPeakFlowMax				100U

/* I/T Max (0.33) * 60 * 1000	 */
#define cITMaxSimvSec		      19800U
/* Ti control limit in SIMV modes when Control R < 8 bpm	 */
#define cITMaxSimvLimit		      2400U
/* Control R limit value for Ti control limitation	 */
#define cSimvControlR		      8U
#define cMaxPressure				   550U
#define cApneaTimeSimv			   12000U

// PSV constants
#define cApneaTimeCoeff			   60000U
#define cApneaTimeCoeff2			   30000U
/*  (1/2 * 60) * 1000	 */
#define cTiMinCoeff				   30000U
#define cDeltaRiseTime				300U
#define cTiMaxmax				      3000U

/* constant declaration for NAND Flash Memory */
#define MICRON			0x2C
#define MT29F2G08AAB	0xDA
#define MT29F2G16AAB	0xCA
#define MT29F4G08BAB	0xDC
#define MT29F4G16BAB	0xCC
#define MT29F8G08FAB	0xDC

#define SAMSUNG			0xEC
#define K9F1G08R0A		0xA1
#define K9F1G08U0A		0xF1


#define ST 				0x20
#define NAND01GR3B		0xA1
#define NAND01GW3B		0xF1
#define NAND01GR4B		0xB1
#define NAND01GW4B		0xC1
#define NAND02GR3B		0xAA
#define NAND02GW3B		0xDA
#define NAND02GR4B		0xBA
#define NAND02GW4B		0xCA
#define NAND04GR3B		0xAC
#define NAND04GW3B		0xDC
#define NAND04GR4B		0xBC
#define NAND04GW4B		0xCC
#define NAND08GR3B		0xA3
#define NAND08GW3B		0xD3
#define NAND08GR4B		0xB3
#define NAND08GW4B		0xC3

#if defined(LEGENDAIR_XL2)
	#define CFG_REVISION_VERSION_NUMBER_0				0x4C58 // LX
	#define CFG_REVISION_VERSION_NUMBER_1				0x3031 // 01
	#define CFG_REVISION_VERSION_NUMBER_2				0x3031 // 01
	#define CFG_REVISION_VERSION_NUMBER_3				0x3036 // 06
#elif defined(SUPPORTAIR_M2)
    #define CFG_REVISION_VERSION_NUMBER_0				0x4C4D // LM
    #define CFG_REVISION_VERSION_NUMBER_1				0x3031 // 01
    #define CFG_REVISION_VERSION_NUMBER_2				0x3030 // 00
    #define CFG_REVISION_VERSION_NUMBER_3				0x3130 // 10
#elif defined(LEGENDAIR_S2)
	#define CFG_REVISION_VERSION_NUMBER_0				0x4C53 // LS
	#define CFG_REVISION_VERSION_NUMBER_1				0x3031 // 01
	#define CFG_REVISION_VERSION_NUMBER_2				0x3031 // 01
	#define CFG_REVISION_VERSION_NUMBER_3				0x3035 // 05
#endif


#ifdef DECLARATION_IHM_ACCESS_PARA_DATABASE


/* Structure array elements giving boundaries, steps, and default parameters:	*/
/*	{min,max,step,défault}																		*/
/* In order to make difference with enum, the "t" prefix is added				  	*/

/* DB_ADJUST_VSIMV */
    #define tADJUST_VOL_CONTROL_VSIMV 								{50,2000,10,500}
    #define tADJUST_PEEP_VSIMV 										{0,200,10,0}
    #define tADJUST_P_SUPPORT_VSIMV 									{50,550,10,150}
    #define tADJUST_RAMP_VSIMV 										{1,1,NONE,1}
    #define tADJUST_CONTROL_R_VSIMV 									{1,40,1,13}
    #define tADJUST_BACKUP_R_VSIMV 									{5,40,1,10}
    #define tADJUST_HIGH_R_VSIMV 										{17,70,1,70}
    #define tHIGH_R_NO_SELECT_VSIMV 									{FALSE,TRUE,1,TRUE}
    #define tADJUST_TI_CONTROL_VSIMV 								{300,2400,100,1500}
    #define tADJUST_INSP_SENS_VSIMV 									{1,6,1,3}
    #define tINSP_SENS_NO_SELECT_VSIMV 								{FALSE,TRUE,1,FALSE}
    #define tADJUST_EXH_SENS_VSIMV 									{5,95,5,75}
    #define tAUTO_EXH_SENS_SELECT_VSIMV								{FALSE,TRUE,1,FALSE}
    #define tADJUST_APNEA_VSIMV 										{1000,60000,1000,12000}
    #define tAUTO_APNEA_SELECT_VSIMV 								{FALSE,TRUE,1,TRUE}
    #define tADJUST_LOW_PIP_VSIMV 									{20,520,10,20}
#define tADJUST_HIGH_PIP_VSIMV 									{120,900,10,400}		
    #define tADJUST_LOW_VTE_VSIMV 									{30,1990,10,300}
    #define tLOW_VTE_NO_SELECT_VSIMV 								{FALSE,TRUE,1,FALSE}	
    #define tADJUST_HIGH_VTE_VSIMV 									{80,3000,10,1000}
    #define tHIGH_VTE_NO_SELECT_VSIMV 								{FALSE,TRUE,1,FALSE}	
    #define tADJUST_RISE_TIME_VSIMV 									{1,4,1,2}		
    #define tADJUST_LOW_VTI_VSIMV 									{30,2000,10,30}
    #define tLOW_VTI_NO_SELECT_VSIMV 								{FALSE,TRUE,1,TRUE}
    #define tADJUST_HIGH_VTI_VSIMV 									{80,3000,10,2000}
    #define tHIGH_VTI_NO_SELECT_VSIMV 								{FALSE,TRUE,1,FALSE}
    #define tADJUST_TI_MIN_VSIMV 										{100,3000,100,700}
    #define tTI_MIN_AUTO_SELECT_VSIMV 								{FALSE,TRUE,1,TRUE}
    #define tADJUST_TI_MAX_VSIMV 										{800,3000,100,3000}
    #define tTI_MAX_AUTO_SELECT_VSIMV 								{FALSE,TRUE,1,TRUE}
    #define tPI_SET_POINT_VSIMV        								{0,550,10,150}
    #define tCONTROL_R_NO_SELECT_VSIMV 								{FALSE,TRUE,1,FALSE}
    #define tPEEP_NO_SELECT_VSIMV 									{FALSE,TRUE,1,TRUE}
    #define tRISE_TIME_VSIMV								         {200,800,200,400}
    #define tADJUST_EXH_SENS_NEGATIVE_VSIMV							{5,95,5,25}
    #define tAUTO_EXH_SENS_NEG_SELECT_VSIMV							{FALSE,TRUE,1,FALSE}
    #define tADJUST_DISCONNECTION_DELAY_VSIMV			         {5000,62000,1000,15000}
    #define tDISCONNECTION_DELAY_AUTO_VSIMV						{FALSE,TRUE,1,FALSE}

/* DB_ADJUST_PSIMV */
    #define tADJUST_P_CONTROL_PSIMV	 								{50,550,10,150}
    #define tADJUST_PEEP_PSIMV 										{0,200,10,0}
    #define tADJUST_P_SUPPORT_PSIMV 									{50,550,10,150}
    #define tADJUST_CONTROL_R_PSIMV 									{1,40,1,13}
    #define tADJUST_BACKUP_R_PSIMV 									{1,40,1,12}
    #define tADJUST_HIGH_R_PSIMV 										{17,70,1,70}
    #define tHIGH_R_NO_SELECT_PSIMV 									{FALSE,TRUE,1,TRUE}
    #define tADJUST_TI_CONTROL_PSIMV 								{300,2400,100,1500}
    #define tADJUST_INSP_SENS_PSIMV 									{1,6,1,3}
    #define tINSP_SENS_NO_SELECT_PSIMV 								{FALSE,TRUE,1,FALSE}
    #define tADJUST_EXH_SENS_PSIMV 									{5,95,5,75}
    #define tAUTO_EXH_SENS_SELECT_PSIMV								{FALSE,TRUE,1,FALSE}
    #define tADJUST_APNEA_PSIMV 										{1000,60000,1000,12000}
    #define tAUTO_APNEA_SELECT_PSIMV 								{FALSE,TRUE,1,TRUE}
    #define tADJUST_LOW_VTE_PSIMV 									{30,1990,10,300}
    #define tLOW_VTE_NO_SELECT_PSIMV 								{FALSE,TRUE,1,FALSE}
    #define tADJUST_HIGH_VTE_PSIMV 									{80,3000,10,1000}
    #define tHIGH_VTE_NO_SELECT_PSIMV 								{FALSE,TRUE,1,FALSE}	
    #define tADJUST_RISE_TIME_PSIMV 									{1,4,1,2}		
    #define tADJUST_LOW_VM_PSIMV 										{5,500,5,40}
    #define tLOW_VM_NO_SELECT_PSIMV 									{FALSE,TRUE,1,FALSE}
    #define tADJUST_HIGH_VM_PSIMV 									{20,990,5,130}
    #define tHIGH_VM_NO_SELECT_PSIMV 								{FALSE,TRUE,1,FALSE}
    #define tADJUST_LOW_VTI_PSIMV 									{30,2000,10,300}
    #define tLOW_VTI_NO_SELECT_PSIMV 								{FALSE,TRUE,1,FALSE}
    #define tADJUST_HIGH_VTI_PSIMV 									{80,3000,10,2000}
    #define tHIGH_VTI_NO_SELECT_PSIMV 								{FALSE,TRUE,1,FALSE}
    #define tADJUST_TI_MIN_PSIMV 										{100,3000,100,700}
    #define tTI_MIN_AUTO_SELECT_PSIMV 								{FALSE,TRUE,1,TRUE}
    #define tADJUST_TI_MAX_PSIMV 										{800,3000,100,3000}
    #define tTI_MAX_AUTO_SELECT_PSIMV 								{FALSE,TRUE,1,TRUE}
    #define tPI_SET_POINT_PSIMV         							{0,550,10,150}
    #define tPEEP_NO_SELECT_PSIMV 									{FALSE,TRUE,1,TRUE}
    #define tRISE_TIME_PSIMV								         {200,800,200,400}
    #define tADJUST_EXH_SENS_NEGATIVE_PSIMV							{5,95,5,25}
    #define tAUTO_EXH_SENS_NEG_SELECT_PSIMV							{FALSE,TRUE,1,FALSE}
    #define tADJUST_DISCONNECTION_DELAY_PSIMV			         {5000,62000,1000,15000}
    #define tDISCONNECTION_DELAY_AUTO_PSIMV						{FALSE,TRUE,1,FALSE}

/* DB_ADJUST_PRES */
    #define tADJUST_P_CONTROL_PRES	 								{20,550,10,150}
    #define tADJUST_PEEP_PRES	 										{0,200,10,0}
    #define tADJUST_CONTROL_R_PRES 									{1,60,1,13}
    #define tADJUST_HIGH_R_PRES 										{10,70,1,70}
    #define tHIGH_R_NO_SELECT_PRES 									{FALSE,TRUE,1,TRUE}
    #define tADJUST_TI_CONTROL_PRES	 								{300,6000,100,1500}
    #define tADJUST_INSP_SENS_PRES 									{0,6,1,3}
    #define tINSP_SENS_NO_SELECT_PRES 								{FALSE,TRUE,1,FALSE}
    #define tAUTO_INSP_SENS_SELECT_PRES								{FALSE,TRUE,1,TRUE}
    #define tADJUST_LOW_VTE_PRES	 									{30,1990,10,300}
    #define tLOW_VTE_NO_SELECT_PRES	 								{FALSE,TRUE,1,FALSE}	
    #define tADJUST_HIGH_VTE_PRES 									{80,3000,10,1000}
    #define tHIGH_VTE_NO_SELECT_PRES 								{FALSE,TRUE,1,FALSE}
    #define tADJUST_RISE_TIME_PRES 									{1,4,1,2}		
    #define tADJUST_LOW_VTI_PRES	 									{30,2000,10,300}
    #define tLOW_VTI_NO_SELECT_PRES	 								{FALSE,TRUE,1,FALSE}
    #define tADJUST_HIGH_VTI_PRES 									{80,3000,10,2000}
    #define tHIGH_VTI_NO_SELECT_PRES 								{FALSE,TRUE,1,FALSE}
    #define tPI_SET_POINT_PRES        								{0,550,10,150}
    #define tPEEP_NO_SELECT_PRES 										{FALSE,TRUE,1,TRUE}
    #define tRISE_TIME_PRES   								         {200,800,200,400}
    #define tADJUST_HIGH_LEAK_PRES									{5,150,5,150}			
    #define tHIGH_LEAK_SELECT_PRES									{FALSE,TRUE,1,FALSE}	
    #define tADJUST_TARGET_VT_PRES									{50,2000,10,100}
    #define tTARGET_VT_SELECT_PRES								{FALSE,TRUE,1,FALSE}
    #define tADJUST_MAX_PRESSURE_PRES								{80,550,10,180}
    #define tADJUST_DISCONNECTION_DELAY_PRES			         {5000,62000,1000,15000}
    #define tDISCONNECTION_DELAY_AUTO_PRES							{FALSE,TRUE,1,FALSE}


/* DB_ADJUST_VOL */
    #define tADJUST_VOL_CONTROL_VOL	 								{50,2000,10,500}
    #define tADJUST_PEEP_VOL	 										{0,200,10,0}
    #define tADJUST_RAMP_VOL	 										{0,2,1,0}
    #define tADJUST_CONTROL_R_VOL 									{1,60,1,13}
    #define tADJUST_HIGH_R_VOL 										{10,70,1,70}
    #define tHIGH_R_NO_SELECT_VOL 									{FALSE,TRUE,1,TRUE}
    #define tADJUST_TI_CONTROL_VOL	 								{300,6000,100,1500}
    #define tADJUST_INSP_SENS_VOL 									{0,6,1,3}
    #define tINSP_SENS_NO_SELECT_VOL 								{FALSE,TRUE,1,FALSE}
    #define tADJUST_LOW_PIP_VOL	 									{20,820,10,20}
    #define tADJUST_HIGH_PIP_VOL	 								{120,900,10,400}		
    #define tADJUST_LOW_VTE_VOL	 									{30,1990,10,300}
    #define tLOW_VTE_NO_SELECT_VOL	 								{FALSE,TRUE,1,FALSE}	
    #define tADJUST_HIGH_VTE_VOL	 									{80,3000,10,1000}
    #define tHIGH_VTE_NO_SELECT_VOL 	   							{FALSE,TRUE,1,FALSE}
    #define tPEEP_NO_SELECT_VOL    									{FALSE,TRUE,1,TRUE}
    #define tADJUST_SIGH_SELECT_VOL									{FALSE,TRUE,1,FALSE}
    #define tADJUST_SIGH_CPT_VOL 										{50,250,50,50}
    #define tADJUST_SIGH_VT_COEF_VOL									{10,20,1,10}
    #define tADJUST_DISCONNECTION_DELAY_VOL			         {5000,62000,1000,15000}
    #define tDISCONNECTION_DELAY_AUTO_VOL							{FALSE,TRUE,1,FALSE}

/* DB_ADJUST_PSV */
    #define tADJUST_PEEP_PSV	 										{0,200,10,0}
    #define tADJUST_P_SUPPORT_PSV 									{20,550,10,150}
    #define tADJUST_BACKUP_R_PSV	 									{4,40,1,13}
    #define tADJUST_HIGH_R_PSV 										{10,70,1,70}
    #define tHIGH_R_NO_SELECT_PSV 									{FALSE,TRUE,1,TRUE}
    #define tADJUST_INSP_SENS_PSV 									{1,6,1,3}
    #define tINSP_SENS_NO_SELECT_PSV 								{FALSE,TRUE,1,FALSE}
    #define tADJUST_EXH_SENS_PSV	 									{5,95,5,75}
    #define tAUTO_EXH_SENS_SELECT_PSV								{FALSE,TRUE,1,TRUE}
    #define tADJUST_APNEA_PSV	 										{1000,60000,1000,4600}
    #define tAUTO_APNEA_SELECT_PSV	 								{FALSE,TRUE,1,TRUE}
    #define tADJUST_LOW_VTE_PSV	 									{30,1990,10,300}		
    #define tLOW_VTE_NO_SELECT_PSV	 								{FALSE,TRUE,1,FALSE}
    #define tADJUST_HIGH_VTE_PSV 										{80,3000,10,1000}
    #define tHIGH_VTE_NO_SELECT_PSV 									{FALSE,TRUE,1,FALSE}	
    #define tADJUST_RISE_TIME_PSV 									{1,4,1,2}		
    #define tADJUST_LOW_VTI_PSV	 									{30,2000,10,300}
    #define tLOW_VTI_NO_SELECT_PSV	 								{FALSE,TRUE,1,FALSE}
    #define tADJUST_HIGH_VTI_PSV	 									{80,3000,10,2000}
    #define tHIGH_VTI_NO_SELECT_PSV	 								{FALSE,TRUE,1,FALSE}
    #define tADJUST_TI_MIN_PSV 										{100,2800,100,700}
    #define tTI_MIN_AUTO_SELECT_PSV	 								{FALSE,TRUE,1,TRUE}
    #define tADJUST_TI_MAX_PSV 										{800,3000,100,3000}
    #define tTI_MAX_AUTO_SELECT_PSV	 								{FALSE,TRUE,1,TRUE}
    #define tPI_SET_POINT_PSV         								{0,550,10,150}
    #define tBACKUP_R_NO_SELECT_PSV         						{FALSE,FALSE,0,FALSE}
    #define tP_SUPPORT_NO_SELECT_PSV          					{FALSE,TRUE,1,FALSE}
    #define tPEEP_NO_SELECT_PSV 										{FALSE,TRUE,1,TRUE}
    #define tRISE_TIME_PSV   								         {200,800,200,400}
    #define tADJUST_HIGH_LEAK_PSV										{5,150,5,150}			
    #define tHIGH_LEAK_SELECT_PSV										{FALSE,TRUE,1,FALSE}	
    #define tADJUST_TARGET_VT_PSV										{50,2000,10,100}
    #define tTARGET_VT_SELECT_PSV									{FALSE,TRUE,1,FALSE}
    #define tADJUST_MAX_PRESSURE_PSV									{80,550,10,180}
    #define tADJUST_EXH_SENS_NEGATIVE_PSV							{5,95,5,25}
    #define tAUTO_EXH_SENS_NEG_SELECT_PSV							{FALSE,TRUE,1,TRUE}
    #define tADJUST_DISCONNECTION_DELAY_PSV			         {5000,62000,1000,15000}
    #define tDISCONNECTION_DELAY_AUTO_PSV							{FALSE,TRUE,1,FALSE}

/* DB_ADJUST_CPAP */
    #define tADJUST_PEEP_CPAP	 										{40,200,10,100}
    #define tADJUST_APNEA_CPAP	 										{1000,60000,1000,30000}
    #define tAUTO_APNEA_SELECT_CPAP	 								{FALSE,TRUE,1,TRUE}
    #define tADJUST_LOW_VTI_CPAP	 									{30,2000,10,300}
    #define tLOW_VTI_NO_SELECT_CPAP	 								{FALSE,TRUE,1,FALSE}
    #define tADJUST_HIGH_VTI_CPAP	 									{80,3000,10,2000}
    #define tPI_SET_POINT_CPAP         								{0,200,10,150}
    #define tHIGH_VTI_NO_SELECT_CPAP	 								{FALSE,TRUE,1,FALSE}
    #define tADJUST_HIGH_LEAK_CPAP									{5,150,5,150}			
    #define tHIGH_LEAK_SELECT_CPAP									{FALSE,TRUE,1,FALSE}	
    #define tADJUST_HIGH_R_CPAP 										{10,70,1,70}
    #define tHIGH_R_NO_SELECT_CPAP 									{FALSE,TRUE,1,TRUE}
    #define tADJUST_DISCONNECTION_DELAY_CPAP			         {5000,62000,1000,15000}
    #define tDISCONNECTION_DELAY_AUTO_CPAP							{FALSE,TRUE,1,FALSE}
    #define tADJUST_TI_MIN_CPAP 										{100,2800,100,700}
    #define tTI_MIN_AUTO_SELECT_CPAP	 								{FALSE,TRUE,1,TRUE}
    #define tADJUST_TI_MAX_CPAP 										{800,3000,100,3000}
    #define tTI_MAX_AUTO_SELECT_CPAP	 								{FALSE,TRUE,1,TRUE}
    #define tRISE_TIME_CPAP   								         {200,800,200,400}
    #define tADJUST_INSP_SENS_CPAP 									{0,6,1,3}
    #define tINSP_SENS_NO_SELECT_CPAP 								{FALSE,TRUE,1,FALSE}
    #define tADJUST_EXH_SENS_CPAP	 									{5,95,5,25}
    #define tAUTO_EXH_SENS_SELECT_CPAP								{FALSE,TRUE,1,TRUE}

/*DB_CONTROL*/
    #define tVENTIL_AUTHORIZATION						{NONE,NONE,NONE,FALSE}
    #define tCURRENT_MODE								{NONE,NONE,NONE,PRES}
    #define tCHANGE_MODE									{NONE,NONE,NONE,FALSE}
    #define tVENTIL_STATE								{NONE,NONE,NONE,VEN_VENTIL_DISABLE}
    #define tSIMV_CYCLES									{NONE,NONE,NONE,CAV_Cycle}
    #define tCALIB_PATIENT_PRESS_REQ					{NONE,NONE,NONE,NO_CALIB}
    #define tCALIB_FLOW_INSP_REQ						{NONE,NONE,NONE,NO_CALIB}
    #define tCALIB_FLOW_EXH_REQ						{NONE,NONE,NONE,NO_CALIB}
    #define tCALIB_VALVE_PRESS_REQ					{NONE,NONE,NONE,NO_CALIB}
    #define tCALIB_FAS_VALVE_REQ_U16				{NONE,NONE,NONE,NO_CALIB}
    #define tINHIBIT_BUZZER_REQ						{NONE,NONE,NONE,FALSE}
    #define tINHIBITION_AUTHORIZATION				{NONE,NONE,NONE,FALSE}
    #define tALARM_CANCEL_REQ							{NONE,NONE,NONE,FALSE}
    #define tBUZZER_CDE									{NONE,NONE,NONE,FALSE}
    #define tCALIB_ADJUST_CMD							{0,50000,10,0}
    #define tMAINT_CONTROL_SET_POINT					{NONE,NONE,NONE,0}
    #define tMAINT_CONTROL_TYPE						{NONE,NONE,NONE,NO_CONTROL}
    #define tSUPPLY_AC_DC_BAT							{NONE,NONE,NONE,AC}
    #define tDISPLAY_BATTERY							{NONE,NONE,NONE,FALSE}
    #define tCURRENT_PATIENT_COUNTER_HOUR			{NONE,NONE,NONE,0}
    #define tCURRENT_PATIENT_COUNTER_MIN			{NONE,NONE,NONE,0}
    #define tCURRENT_MACHINE_COUNTER_HOUR			{NONE,NONE,NONE,0}
    #define tCURRENT_MACHINE_COUNTER_MIN			{NONE,NONE,NONE,0}
    #define tCONTROL_BUZZER								{NONE,NONE,NONE,FALSE}
    #define tVALVE_DETECTED								{NONE,NONE,NONE,FALSE}
    #define tAC_SELECTED									{NONE,NONE,NONE,FALSE}
    #define tDC_SELECTED									{NONE,NONE,NONE,FALSE}
    #define tREMOTE_STATE								{NONE,NONE,NONE,FALSE}
    #define tPROXI_DETECTED								{NONE,NONE,NONE,FALSE}
    #define tALARM_DETECTED								{NONE,NONE,NONE,FALSE}
    #define tNEW_ALARM_HP_DETECTED					{NONE,NONE,NONE,FALSE}
    #define tStart_Limit_Setting                	{NONE,NONE,NONE,FALSE} // Marqueur
    #define tLIMIT_LOW_PIP							   {NONE,NONE,NONE,FALSE}
    #define tLIMIT_HIGH_PIP						      {NONE,NONE,NONE,FALSE}
    #define tLIMIT_LOW_VM							   {NONE,NONE,NONE,FALSE}
    #define tLIMIT_HIGH_VM							   {NONE,NONE,NONE,FALSE}
    #define tLIMIT_PEEP								   {NONE,NONE,NONE,FALSE}
    #define tLIMIT_VOL_CONTROL					      {NONE,NONE,NONE,FALSE}
    #define tLIMIT_TI_CONTROL						   {NONE,NONE,NONE,FALSE}
    #define tLIMIT_CONTROL_R						   {NONE,NONE,NONE,FALSE}
    #define tLIMIT_P_CONTROL						   {NONE,NONE,NONE,FALSE}
    #define tLIMIT_PI_U16							   {NONE,NONE,NONE,FALSE}
    #define tLIMIT_LOW_VTI   						   {NONE,NONE,NONE,FALSE}
    #define tLIMIT_HIGH_VTI   						   {NONE,NONE,NONE,FALSE}
    #define tLIMIT_LOW_VTE   						   {NONE,NONE,NONE,FALSE}
    #define tLIMIT_HIGH_VTE   						   {NONE,NONE,NONE,FALSE}
    #define tLIMIT_P_SUPPORT  						   {NONE,NONE,NONE,FALSE}
    #define tLIMIT_TI_MIN   						   {NONE,NONE,NONE,FALSE}
    #define tLIMIT_TI_MAX   						   {NONE,NONE,NONE,FALSE}
    #define tLIMIT_SPO2_MINI  						   {NONE,NONE,NONE,FALSE}
    #define tLIMIT_SPO2_MAXI  						   {NONE,NONE,NONE,FALSE}
    #define tLIMIT_TARGET_VT  						   {NONE,NONE,NONE,FALSE}
    #define tLIMIT_APNEA  						   	{NONE,NONE,NONE,FALSE}
    #define tLIMIT_HIGH_FIO2  						   	{NONE,NONE,NONE,FALSE}
    #define tLIMIT_LOW_FIO2  						   	{NONE,NONE,NONE,FALSE}
    #define tLIMIT_SPO2  						   	{NONE,NONE,NONE,FALSE}
    #define tLIMIT_BACKUP_R					   		{NONE,NONE,NONE,FALSE}
    #define tLIMIT_INSP_SENS					   	{NONE,NONE,NONE,FALSE}
    #define tLIMIT_SIGH					   			{NONE,NONE,NONE,FALSE}
    #define tLIMIT_PMAX					   			{NONE,NONE,NONE,FALSE}
    #define tEnd_Limit_Setting                   {NONE,NONE,NONE,FALSE} // Marqueur
    #define tUNCANCELL_CMD                       {NONE,NONE,NONE,FALSE}
    #define tFAILURE_BUS                         {NONE,NONE,NONE,FALSE}
    #define tKEYBOARD_ANOMALIE                   {NONE,NONE,NONE,FALSE}
    #define tVALIDATION_BIP	                   	{0,3,1,0}
    #define tBIP_RUNNING		                  	{NONE,NONE,NONE,FALSE}
    #define tMAINTENANCE_MODE		               {NONE,NONE,NONE,FALSE}
    #define tCALIBRATION_MODE		               {NONE,NONE,NONE,FALSE}
    #define tTEST_BUZ_CARD								{NONE,NONE,NONE,FALSE}
    #define tTEST_BUZ_SEC								{NONE,NONE,NONE,FALSE}
    #define tTEST_VOLUME									{NONE,NONE,NONE,FALSE}
    #define tCANCEL_ALARM_ASKED						{NONE,NONE,NONE,FALSE}
    #define tKEY_EVENT									{NONE,NONE,NONE,FALSE}
    #define tBACKLIGHT_OFF								{NONE,NONE,NONE,FALSE}
    #define tHIGH_PRESSURE_LED_REMINDER				{NONE,NONE,NONE,FALSE}
    #define tRECORD_SETTINGS_USB_U16					{FALSE,TRUE,1,TRUE}
    #define tAPPLY_SETTINGS_USB_U16					{FALSE,TRUE,1,TRUE}
    #define tERASE_KEY_USB_U16							{FALSE,TRUE,1,TRUE}
    #define tRECORD_TIME_TENDANCE_U16				{1,48,1,1}
    #define tERROR_SPO2_SENSOR_DETECTED				{NONE,NONE,NONE,FALSE}
    #define tDETECTED_FIO2_SENSOR						{NONE,NONE,NONE,FALSE}
    #define tCALIBRATED_FIO2_SENSOR					{NONE,NONE,NONE,FALSE}
    #define tCALIB_ADJUST_VANNE_FIO2_CMD			{0,2670,10,10}
    #define tCALIB_FIO2_REQ								{NONE,NONE,NONE,FALSE}
    #define tCALIB_FLOW_O2_REQ				 			{NONE,NONE,NONE,FALSE}
    #define tMEMO_CMD_VANNE_FIO2_TO_CALIB			{NONE,NONE,NONE,FALSE}
    #define tCALIB_PRESS_O2_REQ						{NONE,NONE,NONE,FALSE}
    #define tFLOW_SAT_FLAG								{NONE,NONE,NONE,FALSE}
    #define tHIGH_PRESSURE_DETECTED					{NONE,NONE,NONE,FALSE}
    #define tHIGH_PRESSURE_EXHALATION_DETECTED	{NONE,NONE,NONE,FALSE}
    #define tHIGH_PRESSURE_DETECT_WINDOW            {NONE,NONE,NONE,FALSE}
    #define tHIGH_PRESSURE_DETECTED_PRESSURE_MODE				{NONE,NONE,NONE,FALSE}
    #define tHIGH_PRESSURE_EXHALATION_DETECTED_PRESSURE_MODE {NONE,NONE,NONE,FALSE}
    #define tFIO2_100_ACTIVE							{NONE,NONE,NONE,FALSE}
    #define tLOAD_USB_SETTINGS							{NONE,NONE,NONE,FALSE}
    #define tCOM_READY									{NONE,NONE,NONE,FALSE}
    #define tSTART_MONITORING							{NONE,NONE,NONE,FALSE}
    #define tSIMV_PSV_CYCLE_U16						{NONE,NONE,NONE,FALSE}
    #define tBLOC_EXPI_DETECTED						{NONE,NONE,NONE,FALSE}
    #define tADJUSTMENT_IN_PROGRESS_U16				{NONE,NONE,NONE,FALSE}
    #define tVALVE_DETECT_IN_PROGRESS_U16			{NONE,NONE,NONE,FALSE}
    #define tEXHAL_FLOW_USE_U16						{NONE,NONE,NONE,FALSE}
    #define tFLAT_INT_U16                           {NONE,NONE,NONE,FALSE}  
    #define tFLAT_PROXI_U16                         {NONE,NONE,NONE,FALSE}  
    #define tVALVE_O2_CMD_U16					{NONE,NONE,NONE,FALSE}
    #define tCPAP_TRIG_I							{NONE,NONE,NONE,FALSE}
    #define tCPAP_TRIG_E							{NONE,NONE,NONE,FALSE}
    #define tCONTROLER_TYPE_U16                     {NONE,NONE,NONE,FALSE}
    #define tVTI_DISPLAY_DELAY_U16                  {FALSE,TRUE,1,FALSE}
    #define tVOLUNTARY_STOP_U16						{NONE,NONE,NONE,FALSE}
#define tSOUND_TYPE_SELECT_U16					{ORIGINAL,COMPLIANT,1,COMPLIANT}
    #define tSIMV_CONTROLLED_INSP_U16						{NONE,NONE,NONE,FALSE}
    #define tEND_OF_OPERATION_U16						{NONE,NONE,NONE,FALSE}


/*DB_CONFIG*/
    #define tADJUST_LANGUAGE 							{0,18,1,3}
    #define tADJUST_MODE		 							{0,5,1,1}
    #define tADJUST_KEYLOCK								{FALSE,TRUE,1,FALSE}
    #define tVENTIL_REQ									{FALSE,TRUE,1,FALSE}
/******************************************************************/
/* LES VALEURS D'OFFSETS SONT DIFFERENTES ENTRE CAPTEUR QI et QE :*/
/* MECANIQUE DIFFERENTES													 	*/  
/*******************************************************************/
    #define tOFFSET_INSP_FLOW_1						{160,250, NONE,215}				
    #define tOFFSET_INSP_FLOW_2						{175,280, NONE,229}				
    #define tOFFSET_INSP_FLOW_3						{215,315, NONE,268}				
    #define tOFFSET_INSP_FLOW_4						{200,500, NONE,315}				
    #define tOFFSET_INSP_FLOW_5						{370,550, NONE,459}				
    #define tOFFSET_INSP_FLOW_6						{465,700, NONE,581}				
    #define tOFFSET_INSP_FLOW_7						{560,850, NONE,706}				
    #define tOFFSET_INSP_FLOW_8						{650,1022,NONE,880}			

    #define tOFFSET_EXH_FLOW_1							{160,250, NONE,210}				
    #define tOFFSET_EXH_FLOW_2							{185,265, NONE,227}				
    #define tOFFSET_EXH_FLOW_3							{215,315, NONE,275}			
    #define tOFFSET_EXH_FLOW_4							{200,600, NONE,325}			
    #define tOFFSET_EXH_FLOW_5							{410,620, NONE,513}			
    #define tOFFSET_EXH_FLOW_6							{520,780, NONE,657}				
    #define tOFFSET_EXH_FLOW_7							{600,1010,NONE,818}				
    #define tOFFSET_EXH_FLOW_8							{700,1022,NONE,970}				
    #define tOFFSET_O2_FLOW_1							{185,230,NONE,207}				
    #define tOFFSET_O2_FLOW_2							{325,400,NONE,360}				
    #define tOFFSET_O2_FLOW_3							{401,800,NONE,630}			
    #define tOFFSET_O2_FLOW_4							{750,950,NONE,830}			
    #define tOFFSET_O2_FLOW_5							{800,1022,NONE,960}				
    #define tOFFSET_O2_FLOW_6							{0,1022,NONE,512}	// Inutilisé 	
    #define tOFFSET_O2_FLOW_7							{0,1022,NONE,512}	// Inutilisé 	

    #define tOFFSET_PATIENT_PRESS1					{165,200,NONE,176}
    #define tOFFSET_PATIENT_PRESS2					{425,520,NONE,468}				
    #define tOFFSET_PATIENT_PROX_PRESS1				{165,200,NONE,176}
    #define tOFFSET_PATIENT_PROX_PRESS2				{425,520,NONE,468}				
    #define tOFFSET_PRESS_O2							{50,150,NONE,104}				
    #define tI_VALVE_REF_U16							{3500,5500,NONE,4500}
    #define tOFFSET_FAS_VALVE_1_U16					{3900,4100,NONE,4000}
    #define tOFFSET_FAS_VALVE_2_U16					{0,50,NONE,0}
    #define tOFFSET_FAS_VALVE_3_U16					{1010,1650,NONE,1332}
    #define tOFFSET_FAS_VALVE_4_U16					{950,1510,NONE,1233}
    #define tOFFSET_FAS_VALVE_5_U16					{890,1430,NONE,1158}
    #define tOFFSET_FAS_VALVE_6_U16					{830,1350,NONE,1095}
    #define tOFFSET_FAS_VALVE_7_U16					{780,1300,NONE,1037}
    #define tOFFSET_FAS_VALVE_8_U16					{710,1240,NONE,977}
    #define tOFFSET_FAS_VALVE_9_U16					{630,1180,NONE,908}
    #define tOFFSET_VALVE_PRESS						{165,200,NONE,176}
    #define tOFFSET_VALVE_PRESS2					{425,520,NONE,468}				
    #define tOFFSET_FIO2							{125,225,NONE,172}
    #define tADJUST_BRIGHTNESS							{25,38,1,32}						
    #define tADJUST_BACKLIGHT							{FALSE,TRUE,1,FALSE}
    #define tRETRIEVAL_EVENT_ADRESS_LSB				{0x0,0xFFFF,NONE,0x0}
    #define tRETRIEVAL_EVENT_ADRESS_MSB				{0x0,0x7,NONE,0x0}
    #define tSPEED_COM									{9600,38400,9600,38400}
    #define tSAVED_PATIENT_COUNTER_HOUR				{0,65535,1,0}
    #define tSAVED_PATIENT_COUNTER_MIN				{0,59,1,0}
    #define tSAVED_MACHINE_COUNTER_HOUR				{0,65535,1,0}
    #define tSAVED_MACHINE_COUNTER_MIN				{0,59,1,0}
    #define tRAZ_COUNTER_PAT_DATE						{1,31,1,1}
    #define tRAZ_COUNTER_PAT_MONTH					{1,12,1,1}
    #define tRAZ_COUNTER_PAT_YEAR						{3,99,1,3}
    #define tRAZ_COUNTER_PAT_HOUR						{0,65535,1,0}
    #define tRAZ_COUNTER_PAT_MIN						{0,59,1,0}
    #define tBAD_ERASE									{ERASE_OK,BAD_TOTAL_ERASE,1,ERASE_OK}
    #define tSOUND_LEVEL_SELECT						{20,100,2,60}
    #define tPREVIOUS_SOUND_LEVEL_SELECT			{20,100,2,60}
    #define tCURVE_DISPLAY_TYPE_MODE        		{FALSE,TRUE,1,FALSE}
    #define tCURVE_MAX_PRESSURE					   {0,100,5,0}
    #define tCURVE_MAX_FLOW								{0,200,5,0}
    #define tCURVE_MAX_VT								{0,3000,100,0}
    #define tCURVE_MAX_TIME								{0,60,1,0}
    #define tCURVE_DRAW_MODE     						{FALSE,TRUE,1,FALSE}
    #define tADJUST_CYCLING_MODE						{0,1,1,1}
    #define tADJUST_KEY_TONE							{0,3,1,2}

    #ifdef SUPPORTAIR_M2
        #define tWAVEFORME_DISPLAY							{FALSE,TRUE,1,TRUE}
    #elif	defined (LEGENDAIR_XL2) || defined (LEGENDAIR_S2)
        #define tWAVEFORME_DISPLAY							{FALSE,TRUE,1,FALSE}
    #endif

    #define tADJUST_BAROMETRIC_CORRECTOR			{FALSE,TRUE,1,TRUE}
    #define tADJUST_FIO2									{21,100,5,21}
    #define tADJUST_FIO2_SELECT						{FALSE,TRUE,1,TRUE}
    #define tADJUST_LOW_FIO2_XL2						{18,90,1,18}
    #define tADJUST_LOW_FIO2_M2						{1,90,1,6}
    #define tADJUST_LOW_FIO2_SELECT				  	{FALSE,TRUE,1,FALSE}
    #define tADJUST_HIGH_FIO2_XL2						{30,100,1,100}
    #define tADJUST_HIGH_FIO2_M2						{30,115,1,36}
    #define tADJUST_HIGH_FIO2_SELECT				  	{FALSE,TRUE,1,FALSE}
    #define tADJUST_LOW_SPO2							{80,98,1,95}
    #define tADJUST_HIGH_SPO2							{90,100,1,98}
    #define tSPO2_LOW_SELECT							{FALSE,TRUE,1,FALSE}
    #define tSPO2_HIGH_SELECT							{FALSE,TRUE,1,FALSE}
    #define tPRESSURE_UNIT								{0,2,1,0}
    #define tTRIGGER_E_POSITIVE						{0,1,1,0}
    #define tVOLUNTARY_STOP_ALARM_ACTIVATION		{FALSE,TRUE,1,TRUE}
    #define tAPNEA_ALARM_ACTIVATION					{FALSE,TRUE,1,TRUE}
/* NAND flash memory type   */
    #define tFLASH_MEM_MANUFACTURER					{0,255,1,MICRON}
    #define tFLASH_MEM_DEVICE						{0,255,1,MT29F2G08AAB}
    #define tFLASH_MEMORY_FIVE_ADDRESS_CYCLES		{FALSE,TRUE,1,FALSE}
    #define tFLASH_MONIT_WRITE_BLOCK						{0,65535,1,1}
    #define tFLASH_MONIT_WRITE_PAGE						{0,65535,1,0}
    #define tFLASH_MONIT_WRITE_COLUMN						{0,65535,1,0}
    #define tFLASH_TREND_WRITE_BLOCK						{0,65535,1,342}
    #define tFLASH_TREND_WRITE_PAGE						{0,65535,1,0}
    #define tFLASH_TREND_WRITE_COLUMN						{0,65535,1,0}
    #define tFLASH_FIRST_PARTITION_FULL				{FALSE,TRUE,1,FALSE}
    #define tFLASH_SECOND_PARTITION_FULL			{FALSE,TRUE,1,FALSE}
    #define tPARAM_COMPATIBILITY                 {0,4,1,0}
    #define tIHM_LOCKED_FRAME_ID				 {4, 6, 2, 4} /* FRAME_VENTILATION == 4, FRAME_ALARM == 6, see IHM_IhmType.hpp */
    #define tPEDIACTRIC_CIRCUIT                     {0, 1, 1, 0}
    #define tPRESSURE_SUPPORT_RELATIVE		{0, 1, 1, 0}  /* 0 = Absolut ,1 = Relative */
    #define tPRESSURE_SUPPORT_CHANGED_U16  {FALSE,TRUE,1,FALSE}
    #define tPREVIOUS_MODE						{NONE,NONE,NONE,FALSE}

/*DB_RTC*/
    #define tADJUST_RTC_REQ								{0,2,1,0}
    #define tADJUST_RTC_SECOND 							{0,59,1,0}
    #define tADJUST_RTC_MINUTE 							{0,59,1,0}
    #define tADJUST_RTC_HOUR 							{0,23,1,0}
    #define tADJUST_RTC_DAY 							{1,31,1,1}
    #define tADJUST_RTC_MONTH 							{1,12,1,1}
    #define tADJUST_RTC_YEAR 							{4,99,1,6}

/*DB_USB*/
    #define tADJUST_USB_ERASE_KEY						{FALSE,TRUE,1,FALSE}
    #define tADJUST_USB_TRANSFER_APPLY 				   	{FALSE,TRUE,1,FALSE}
    #define tADJUST_USB_CONTINUOUS_RECORDING  	   		{FALSE,TRUE,1,FALSE}
    #define tADJUST_USB_MONITOR_TRANSFER			   	{0,48,4,0}
    #define tADJUST_USB_MONITOR_TRANSFER_SELECT     	{FALSE,TRUE,1,FALSE}
    #define tADJUST_USB_TREND_TRANSFER			      	{0,12,3,0}
    #define tADJUST_USB_TREND_TRANSFER_SELECT       	{FALSE,TRUE,1,FALSE}
    #define tADJUST_USB_EVENTS_TRANSFER			      	{FALSE,TRUE,1,FALSE}

/*DB_VERSION*/
    #define tVERSION_NUMBER_0							{NONE,NONE,NONE,CFG_REVISION_VERSION_NUMBER_0} 
    #define tVERSION_NUMBER_1							{NONE,NONE,NONE,CFG_REVISION_VERSION_NUMBER_1} 
    #define tVERSION_NUMBER_2							{NONE,NONE,NONE,CFG_REVISION_VERSION_NUMBER_2} 
    #define tVERSION_NUMBER_3							{NONE,NONE,NONE,CFG_REVISION_VERSION_NUMBER_3}

    #define tSERIAL_NUMBER_1							{NONE,NONE,NONE,0x0000} // 00
    #define tSERIAL_NUMBER_2							{NONE,NONE,NONE,0x0000} // 00
    #define tSERIAL_NUMBER_3							{NONE,NONE,NONE,0x0000} // 00
    #define tSERIAL_NUMBER_4							{NONE,NONE,NONE,0x0000} // 00
    #define tSERIAL_NUMBER_5							{NONE,NONE,NONE,0x0000} // 00
    #define tSERIAL_NUMBER_6							{NONE,NONE,NONE,0x0000} // 00


/*DB_TREND*/
    #define tDB_TREND_VENTIL_HOUR						{0,23,NONE,0x0000}
    #define tDB_TREND_VENTIL_MIN						{0,59,NONE,0x0000}
    #define tDB_TREND_AVG_VTI							{0,65530,NONE,0x0000}
    #define tDB_TREND_SIG_VTI							{0,NONE,NONE,0x0000}	   
    #define tDB_TREND_AVG_VTE							{0,65530,NONE,0x0000}
    #define tDB_TREND_SIG_VTE							{0,NONE,NONE,0x0000}
    #define tDB_TREND_AVG_VM							{0,9990,NONE,0x0000}
    #define tDB_TREND_SIG_VM							{0,NONE,NONE,0x0000}
    #define tDB_TREND_AVG_FR							{0,990,NONE,0x0000}
    #define tDB_TREND_SIG_FR							{0,NONE,NONE,0x0000}
    #define tDB_TREND_LEAK_MODE							{0,NONE,NONE,0x0000}
    #define tDB_TREND_AVG_LEAK							{0,15000,NONE,0x0000}
    #define tDB_TREND_SIG_LEAK							{0,NONE,NONE,0x0000}
    #define tDB_TREND_AVG_PI							{0,9900,NONE,0x0000}
    #define tDB_TREND_SIG_PI							{0,NONE,NONE,0x0000}
    #define tDB_TREND_IA								{0,999,NONE,0x0000}
    #define tDB_TREND_APNEA								{0,999,NONE,0x0000}
    #define tDB_TREND_PERCENT_CONTROLLED				{0,100,NONE,0x0000}
    #define tDB_TREND_PERCENT_TRIGGERED					{0,100,NONE,0x0000}
    #define tDB_TREND_SAVE_RTC_DAY						{1,31,NONE,0x0000}
    #define tDB_TREND_SAVE_RTC_MONTH					{1,12,NONE,0x0000}
    #define tDB_TREND_SAVE_RTC_YEAR						{4,99,NONE,0x0000}
    #define tDB_TREND_SAVE_PC_HOUR						{0,24,NONE,0x0000}
    #define tDB_TREND_SAVE_PC_MIN						{0,59,NONE,0x0000}
    #define tDB_TREND_NB_APNEA							{0,65535,NONE,0x0000}
    #define tDB_TREND_APNEA_TIME						{0,65535,NONE,0x0000}
    #define tDB_TREND_NB_CYCLE_COUNTER_MSB					{0,NONE,NONE,0x0000}
    #define tDB_TREND_NB_CYCLE_COUNTER_LSB					{0,65535,NONE,0x0000}
    #define tDB_TREND_NB_CYCLE_TRIGERRED_MSB			{0,NONE,NONE,0x0000}
    #define tDB_TREND_NB_CYCLE_TRIGERRED_LSB			{0,65535,NONE,0x0000}
    #define tDB_TREND_NB_CYCLE_CONTROLLED_MSB			{0,NONE,NONE,0x0000}
    #define tDB_TREND_NB_CYCLE_CONTROLLED_LSB			{0,65535,NONE,0x0000}
    #define tDB_TREND_VENTIL_REPORT_UPD					{0,NONE,NONE,0x0000}
    #define tDB_TREND_IHM_VENTIL_HOUR 					{0,23,NONE,0x0000}
    #define tDB_TREND_IHM_VENTIL_MIN					{0,59,NONE,0x0000}
    #define tDB_TREND_IHM_AVG_VTI						{0,65530,NONE,0x0000}
    #define tDB_TREND_IHM_SIG_VTI						{0,NONE,NONE,0x0000}
    #define tDB_TREND_IHM_AVG_VTE						{0,65530,NONE,0x0000}
    #define tDB_TREND_IHM_SIG_VTE						{0,NONE,NONE,0x0000}
    #define tDB_TREND_IHM_AVG_VM						{0,9990,NONE,0x0000}
    #define tDB_TREND_IHM_SIG_VM						{0,NONE,NONE,0x0000}
    #define tDB_TREND_IHM_AVG_FR						{0,990,NONE,0x0000}
    #define tDB_TREND_IHM_SIG_FR						{0,NONE,NONE,0x0000}
    #define tDB_TREND_IHM_LEAK_MODE						{0,NONE,NONE,0x0000}
    #define tDB_TREND_IHM_AVG_LEAK						{0,15000,NONE,0x0000}
    #define tDB_TREND_IHM_SIG_LEAK						{0,NONE,NONE,0x0000}
    #define tDB_TREND_IHM_AVG_PI						{0,9900,NONE,0x0000}
    #define tDB_TREND_IHM_SIG_PI						{0,NONE,NONE,0x0000}
    #define tDB_TREND_IHM_IA							{0,999,NONE,0x0000}
    #define tDB_TREND_IHM_APNEA							{0,999,NONE,0x0000}
    #define tDB_TREND_IHM_PERCENT_CONTROLLED			{0,100,NONE,0x0000}
    #define tDB_TREND_IHM_PERCENT_TRIGGERED				{0,100,NONE,0x0000}
    #define tDB_TREND_IHM_SAVE_RTC_DAY					{0,31,NONE,0x0000}
    #define tDB_TREND_IHM_SAVE_RTC_MONTH				{0,12,NONE,0x0000}
    #define tDB_TREND_IHM_SAVE_RTC_YEAR					{0,2099,NONE,0x0000}

/*DB_COMPUTE*/
    #define	sMEASURE_VALVE_PRESSURE_S16 {-32768,32767,NONE,0x0000,1}
    #define	sFILTER_VALVE_PRESSURE_S16 {-999,999,NONE,0x0000,1}
    #define	sMEASURE_INTERNAL_PRESSURE_S16 {-32768,32767,NONE,0x0000,1}
    #define	sFILTER_INTERNAL_PRESSURE_S16 {-999,999,NONE,0x0000,1}
    #define	sMEASURE_PATIENT_PRESSURE_PROXI_S16 {-32768,32767,NONE,0x0000,1}
    #define	sFILTER_PATIENT_PRESSURE_PROXI_S16 {-999,999,NONE,0x0000,1}
    #define	sMEASURE_PATIENT_PRESSURE_S16 {-32768,32767,NONE,0x0000,1}
    #define	sFILTER_PATIENT_PRESSURE_S16 {-32768,32767,NONE,0x0000,1}
    #define	sMEASURE_QINSP_S16 {-32768,32767,NONE,0x0000,1}
    #define	sFILTER_QI_S16 {-9999,9999,NONE,0x0000,1}
    #define	sFILTER_QI_LOW_S16 {-32768,32767,NONE,0x0000,1}
    #define	sMEASURE_QEXH_S16 {-32768,32767,NONE,0x0000,1}
    #define	sFILTER_QE_S16 {-9999,9999,NONE,0x0000,1}
    #define	sCOMPUTED_VTE_U16 {0,3000,NONE,0x0000,0}
    #define	sCOMPUTED_VTE_INSP_U16 {0,65535,NONE,0x0000,0}
    #define	sCOMPUTED_PIP_U16 {0,990,NONE,0x0000,0}
    #define	sCOMPUTED_PEEP_U16 {0,990,NONE,0x0000,0}
    #define sCOMPUTED_FIO2 {0,999,NONE,0x0000,0}
    #define sMEASURE_FIO2 {0,9999,NONE,0x0000,0}
    #define	sMEASURE_IE_NUMERATOR_U16 {0,99,NONE,0x0000,0}	  
    #define	sMEASURE_IE_DENOMINATOR_U16 {0,1990,NONE,0x0000,0}
    #define	sMEASURE_TI_U16 {0,99,NONE,0x0000,0}
    #define	sMEASURE_TI_HMI_U16 {0,65535,NONE,0x0000,0}
    #define	sMEASURE_TE_U16 {0,599,NONE,0x0000,0}
    #define	sMEASURE_R_U16 {0,99,NONE,0x0000,0}
    #define	sMEASURE_SPEED_BLOWER_U16 {0,65535,NONE,0x0000,0}
    #define	sFILTER_SPEED_BLOWER_S16 {-32768,32767,NONE,0x0000,1}
    #define	sCOMPUTED_BATTERY_LEVEL_U16 {0,65535,NONE,0x0000,0}
    #define	sMEASURE_SUPPLY_5V_U16 {0,65535,NONE,0x0000,0}
    #define	sMEASURE_SUPPLY_24V_U16 {0,999,NONE,0x0000,0}
    #define	sMEASURE_TEST_BUZZER_VOLTAGE_U16 {0,65535,NONE,0x0000,0} 
    #define	sMEASURE_BUZZER_VOLTAGE_U16 {0,10000,NONE,0x0000,0} 
    #define sMEASURE_BATTERY_BUZZER_VOLTAGE_U16 {0,65535,NONE,0x0000,0} 
    #define	sMEASURE_PFI_VOLTAGE_U16 {0,999,NONE,0x0000,0}
    #define	sCOMPUTED_PI_SET_POINT_U16 {0,65535,NONE,0x0000,0}
    #define	sCOMPUTED_VTI_EXH_S16 {-32768,32767,NONE,0x0000,1}
    #define	sMEASURE_SPO2_U16 {0,65535,NONE,0x0000,0}
    #define	sMEASURE_HR_U16 {0,65535,NONE,0x0000,0}
    #define	sCOMPUTED_LEAK_U16 {0,1500,NONE,0x0000,0}
    #define sCOMPUTED_LEAK_HMI_U16 {0,150,NONE,0x0000,0}
    #define	sCURVE_CORRECTED_VT_WOB_U16 {0,65535,NONE,0x0000,0}
    #define	sCURVE_CORRECTED_FLOW_S16 {-32768,32767,NONE,0x0000,1}
    #define	sCOMPUTED_TEMP_S16 {-32768,32767,NONE,0x0000,1}	 /* Battery temperature */
    #define	sCOMPUTED_VTI_U16 {0,3000,NONE,0x0000,0}
    #define	sCOMPUTED_USED_44_U16 {0,65535,NONE,0x0000,0}
    #define	sCOMPUTED_USED_45_U16 {0,65535,NONE,0x0000,0}
    #define	sMEASURE_BATTERY_VOLTAGE_U16 {0,65535,NONE,0x0000,0}
    #define	sCOMPUTED_VMI_U16 {0,999,NONE,0x0000,0}
    #define	sCOMPUTED_VME_U16 {0,999,NONE,0x0000,0}
    #define	sAVERAGE_PRESSURE_U16 {0,65535,NONE,0x0000,0}
    #define sMEASURE_ABSOLUTE_PRESSURE_U16 {0,65535,NONE,0x0000,0}
    #define sMEASURE_BLOWER_TEMPERATURE_S16 {-999,999,NONE,0x0000,1}
    #define	sCOMPUTED_RISE_TIME_U16 {0,65535,NONE,0x0000,0}
    #define	sMEASURE_IT_U16 {0,100,NONE,0x0000,0}
    #define	sMEASURE_BATTERY_CAPACITY_U16 {0,65535,NONE,0x0000,0}
    #define	sCOMPUTED_PULSE_U16 {0,65535,NONE,0x0000,0}
    #define	sCOMPUTE_CORRECTED_Q {-32768,32767,NONE,0x0000,1}
    #define sCOMPUTED_TI_CONTROL_U16 {0,65535,NONE,0x0000,0}
    #define sFILTER_QO2_S16 {-32768,32767,NONE,0x0000,1}
    #define sFILTER_PRESSURE_O2_S16 {-32768,32767,NONE,0x0000,1}
    #define sMEASURE_PRESSURE_O2_S16 {-32768,32767,NONE,0x0000,1} 
    #define sMEASURE_QO2_S16 {-32768,32767,NONE,0x0000,1}
    #define sCOMPUTED_IE_NUMERATOR_U16 {0,65535,NONE,0x0000,0}               
    #define sCOMPUTED_IE_DENOMINATOR_U16 {0,65535,NONE,0x0000,0}
    #define	sCOMPUTE_QEE_S16 {-32768,32767,NONE,0x0000,1}
    #define sCOMPUTED_I_T_U16 {0,65535,NONE,0x0000,0}
    #define sMEAS_ABS_PRESS_MMHG_U16 {0,9999,NONE,0x0000,0}
    #define sCOMPUTED_RATE_U16 {0,65535,NONE,0x0000,0}
    #define sBLOWER_COMMAND_U16 {0,65535,NONE,0x0000,0} 
    #define	sMEASURE_ZERO_VALUE_U16 {0,65535,NONE,0x0000,0}
    #define	sCOMPUTED_P_VALVE_MAX_U16 {0,65535,NONE,0x0000,0}
    #define	sCUMUL_PRESS_INSP_S16 {-32768,32767,NONE,0x0000,1}
    #define	sESTIMATED_PROXIMAL_PRESSURE_S16 {-32768,32767,NONE,0x0000,1}
    #define	sMEASURE_QINSP_LEAKCORRECTED_S16 {-32768,32767,NONE,0x0000,1}
    #define	sMEASURE_VALVE_CURRENT_U16 {0,65535,NONE,0x0000,0}
    #define	sMEAN_INSP_VALVE_CURRENT_U16 {350,550,NONE,450,0}
    #define	sVALVE_COMMAND_INIT_U16 {7800,13500,NONE,10660,0}
    #define	sVALVE_COMMAND_MIN_U16 {6300,12400,NONE,9420,0}
    #define	sVALVE_COMMAND_MAX_U16 {10150,16500,NONE,13320,0}
    #define	sVALVE_COMMAND_COEFF_U16 {350,1640,NONE,991,0}
    #define	sVALVE_COMMAND_U16 {0,65535,NONE,0x0000,0}
    #define	sLPF_PATIENT_PRESSURE_S16 {-999,999,NONE,0x0000,1}
    #define	sCOMPUTED_LPF_PIP_U16 {0,990,NONE,0x0000,0}
    #define sLEAK_TEST_QI_S16 {-32768,32767,NONE,0x0000,1}
    #define sLEAK_TEST_RESULT_U16 {0,65535,NONE,0x0000,0}
/*DB_POWER_SUPPLY*/
    #define sV_BAT_U16 {0,9990,NONE,0x0000,0}
    #define sTEMP_BAT_S16 {-999,999,NONE,0x0000,1}
    #define sBAT_CYCLES_U16 {0,65535,NONE,0x0000,0}	/* Identifier; Nb cycles */
    #define sBAT_STATE_U16 {0,65535,NONE,0x0000,0}	   /* Default...*/
    #define sPOWER_TYPE_U16 {0,65535,NONE,0x0000,0}
    #define sJAUGE_MINUTE_U16 {0,65535,NONE,0x0000,0}
    #define sJAUGE_HOUR_DISPLAY_U16 {0,24,NONE,0x0000,0}
    #define sJAUGE_MINUTE_DISPLAY_U16 {0,59,NONE,0x0000,0}
    #define sJAUGE_AVALAIBLE_U16 {0,65535,NONE,0x0000,0}
    #define sPER_CENT_BAT_U16 {0,100,NONE,0x0000,0}
    #define sNO_PRESENCE_BAT_U16 {0,65535,NONE,0x0000,0}
    #define sBAT_KO_U16 {0,65535,NONE,0x0000,0}
    #define sCHARGE_KO_U16 {0,65535,NONE,0x0000,0}
    #define sUNKNOWN_BATTERY_U16 {0,65535,NONE,0x0000,0}
    #define sAMBIENT_TEMP_S16 {-999,999,NONE,0x0000,1}
    #define sBATTERY_END_U16 {0,65535,NONE,0x0000,0}
    #define sBATTERY_LOW_U16 {0,65535,NONE,0x0000,0}
    #define sFIRST_DATE_DAY_U16 {1,31,NONE,0x0000,0}
    #define sFIRST_DATE_MONTH_U16 {1,12,NONE,0x0000,0}
    #define sFIRST_DATE_YEAR_U16 {4,99,NONE,0x0000,0}
    #define sCOOLING_FAN_FAILURE_FLAG_U16 {0,65535,NONE,0x0000,0}
    #define sAMBIENT_TEMP_OUTOFBOUNDS_U16 {0,65535,NONE,0x0000,0}
    #define sFAILURE_24V_FLAG_U16 {0,65535,NONE,0x0000,0}
    #define sBAT_TEMP_OUTOFBOUNDS_U16 {0,65535,NONE,0x0000,0}
    #define sSUPPLY_MEASURE_FAILURE_U16 {0,65535,NONE,0x0000,0}
    #define sPOWER_SUPPLY_VERSION_NUMBER_0 {0,65535,NONE,0x0000,0}
    #define sPOWER_SUPPLY_VERSION_NUMBER_1 {0,65535,NONE,0x0000,0}
    #define sPOWER_SUPPLY_VERSION_NUMBER_2 {0,65535,NONE,0x0000,0}
    #define sSUPPLIER_U16 {0,65535,NONE,0x0000,0}
    #define sCAPACITY_U16 {0,9999,NONE,0x0000,0}
    #define sCAPACITY_THEORICAL_U16 {0,9999,NONE,0x0000,0}
    #define sFIRST_DATE_HOUR_U16 {0,65535,NONE,0x0000,0}
    #define sFIRST_DATE_MINUTE_U16 {0,65535,NONE,0x0000,0}
    #define sFIRST_DATE_SECOND_U16 {0,65535,NONE,0x0000,0}
    #define sAGING_U16 {0,65535,NONE,0x0000,0}


/******************************************************************************/
/*                       CONSTANT DECLARATION     	              					*/
/******************************************************************************/
/* Adjust parameters declaration for the different bases */

/* VSIMV CONSTANTS */
const t_TEST_EEPROM_DB cDB_VSIMV_TEST_ADJUST_DB[end_of_adjust_table]=
{
    tADJUST_VOL_CONTROL_VSIMV,
    {NONE,NONE,NONE,NONE},
        tADJUST_PEEP_VSIMV,
        tADJUST_P_SUPPORT_VSIMV,
        tADJUST_RAMP_VSIMV,
        tADJUST_CONTROL_R_VSIMV,
        tADJUST_BACKUP_R_VSIMV,
        tADJUST_HIGH_R_VSIMV,
        tHIGH_R_NO_SELECT_VSIMV,
        tADJUST_TI_CONTROL_VSIMV,
        tADJUST_INSP_SENS_VSIMV,
        tINSP_SENS_NO_SELECT_VSIMV,
        tADJUST_EXH_SENS_VSIMV,
        tAUTO_EXH_SENS_SELECT_VSIMV,
        tADJUST_APNEA_VSIMV,
        tAUTO_APNEA_SELECT_VSIMV,
        tADJUST_LOW_PIP_VSIMV,
        tADJUST_HIGH_PIP_VSIMV,
        tADJUST_LOW_VTE_VSIMV,
        tLOW_VTE_NO_SELECT_VSIMV,
        tADJUST_HIGH_VTE_VSIMV,
        tHIGH_VTE_NO_SELECT_VSIMV,
        tADJUST_RISE_TIME_VSIMV,
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
        tADJUST_LOW_VTI_VSIMV,
        tLOW_VTI_NO_SELECT_VSIMV,
        tADJUST_HIGH_VTI_VSIMV,
        tHIGH_VTI_NO_SELECT_VSIMV,
        tADJUST_TI_MIN_VSIMV,
        tTI_MIN_AUTO_SELECT_VSIMV,
        tADJUST_TI_MAX_VSIMV,
        tTI_MAX_AUTO_SELECT_VSIMV,
        tPI_SET_POINT_VSIMV,
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
        tCONTROL_R_NO_SELECT_VSIMV,
        tPEEP_NO_SELECT_VSIMV,
        tRISE_TIME_VSIMV,
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
        tADJUST_EXH_SENS_NEGATIVE_VSIMV,
        tAUTO_EXH_SENS_NEG_SELECT_VSIMV,
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
        tADJUST_DISCONNECTION_DELAY_VSIMV,
        tDISCONNECTION_DELAY_AUTO_VSIMV
};

/* PSIMV CONSTANTS */
const t_TEST_EEPROM_DB cDB_PSIMV_TEST_ADJUST_DB[end_of_adjust_table]=
{
    {NONE,NONE,NONE,NONE},
        tADJUST_P_CONTROL_PSIMV,
        tADJUST_PEEP_PSIMV,
        tADJUST_P_SUPPORT_PSIMV,
    {NONE,NONE,NONE,NONE},
        tADJUST_CONTROL_R_PSIMV,
        tADJUST_BACKUP_R_PSIMV,
        tADJUST_HIGH_R_PSIMV,
        tHIGH_R_NO_SELECT_PSIMV,
        tADJUST_TI_CONTROL_PSIMV,
        tADJUST_INSP_SENS_PSIMV,
        tINSP_SENS_NO_SELECT_PSIMV,
        tADJUST_EXH_SENS_PSIMV,
        tAUTO_EXH_SENS_SELECT_PSIMV,
        tADJUST_APNEA_PSIMV,
        tAUTO_APNEA_SELECT_PSIMV,
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
        tADJUST_LOW_VTE_PSIMV,                  
        tLOW_VTE_NO_SELECT_PSIMV,                   
        tADJUST_HIGH_VTE_PSIMV,
        tHIGH_VTE_NO_SELECT_PSIMV,
        tADJUST_RISE_TIME_PSIMV,        
        tADJUST_LOW_VM_PSIMV,
        tLOW_VM_NO_SELECT_PSIMV,
        tADJUST_HIGH_VM_PSIMV,
        tHIGH_VM_NO_SELECT_PSIMV,
        tADJUST_LOW_VTI_PSIMV,
        tLOW_VTI_NO_SELECT_PSIMV,
        tADJUST_HIGH_VTI_PSIMV,
        tHIGH_VTI_NO_SELECT_PSIMV,
        tADJUST_TI_MIN_PSIMV,
        tTI_MIN_AUTO_SELECT_PSIMV,
        tADJUST_TI_MAX_PSIMV,
        tTI_MAX_AUTO_SELECT_PSIMV,
        tPI_SET_POINT_PSIMV,
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
        tPEEP_NO_SELECT_PSIMV,
        tRISE_TIME_PSIMV,
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
        tADJUST_EXH_SENS_NEGATIVE_PSIMV,
        tAUTO_EXH_SENS_NEG_SELECT_PSIMV,
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
        tADJUST_DISCONNECTION_DELAY_PSIMV,
        tDISCONNECTION_DELAY_AUTO_PSIMV
};


/* VOL CONSTANTS */
const t_TEST_EEPROM_DB cDB_VOL_TEST_ADJUST_DB[end_of_adjust_table]=
{
    tADJUST_VOL_CONTROL_VOL,
    {NONE,NONE,NONE,NONE},
        tADJUST_PEEP_VOL,
    {NONE,NONE,NONE,NONE},
        tADJUST_RAMP_VOL,
        tADJUST_CONTROL_R_VOL,
    {NONE,NONE,NONE,NONE},
        tADJUST_HIGH_R_VOL,
        tHIGH_R_NO_SELECT_VOL,
        tADJUST_TI_CONTROL_VOL,
        tADJUST_INSP_SENS_VOL,
        tINSP_SENS_NO_SELECT_VOL,
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
        tADJUST_LOW_PIP_VOL,
        tADJUST_HIGH_PIP_VOL,
        tADJUST_LOW_VTE_VOL,
        tLOW_VTE_NO_SELECT_VOL,
        tADJUST_HIGH_VTE_VOL,
        tHIGH_VTE_NO_SELECT_VOL,
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
        tPEEP_NO_SELECT_VOL,
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
        tADJUST_SIGH_SELECT_VOL,
        tADJUST_SIGH_CPT_VOL,
        tADJUST_SIGH_VT_COEF_VOL,
        tADJUST_DISCONNECTION_DELAY_VOL,
        tDISCONNECTION_DELAY_AUTO_VOL
};


/* PSV CONSTANTS */
const t_TEST_EEPROM_DB cDB_PSV_TEST_ADJUST_DB[end_of_adjust_table]=
{
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
        tADJUST_PEEP_PSV,
        tADJUST_P_SUPPORT_PSV,
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
        tADJUST_BACKUP_R_PSV,
        tADJUST_HIGH_R_PSV,
        tHIGH_R_NO_SELECT_PSV,
    {NONE,NONE,NONE,NONE},
        tADJUST_INSP_SENS_PSV,
        tINSP_SENS_NO_SELECT_PSV,
        tADJUST_EXH_SENS_PSV,
        tAUTO_EXH_SENS_SELECT_PSV,
        tADJUST_APNEA_PSV,
        tAUTO_APNEA_SELECT_PSV,
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
        tADJUST_LOW_VTE_PSV,
        tLOW_VTE_NO_SELECT_PSV,
        tADJUST_HIGH_VTE_PSV,
        tHIGH_VTE_NO_SELECT_PSV,
        tADJUST_RISE_TIME_PSV,
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
        tADJUST_LOW_VTI_PSV,
        tLOW_VTI_NO_SELECT_PSV,
        tADJUST_HIGH_VTI_PSV,
        tHIGH_VTI_NO_SELECT_PSV,
        tADJUST_TI_MIN_PSV,
        tTI_MIN_AUTO_SELECT_PSV,
        tADJUST_TI_MAX_PSV,
        tTI_MAX_AUTO_SELECT_PSV,
        tPI_SET_POINT_PSV,
        tBACKUP_R_NO_SELECT_PSV,
        tP_SUPPORT_NO_SELECT_PSV,
    {NONE,NONE,NONE,NONE},
        tPEEP_NO_SELECT_PSV,
        tRISE_TIME_PSV,
        tADJUST_HIGH_LEAK_PSV,
        tHIGH_LEAK_SELECT_PSV,
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
        tADJUST_TARGET_VT_PSV,
        tTARGET_VT_SELECT_PSV,
        tADJUST_MAX_PRESSURE_PSV,
        tADJUST_EXH_SENS_NEGATIVE_PSV,
        tAUTO_EXH_SENS_NEG_SELECT_PSV,
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
        tADJUST_DISCONNECTION_DELAY_PSV,
        tDISCONNECTION_DELAY_AUTO_PSV
};

/* CPAP CONSTANTS */
const t_TEST_EEPROM_DB cDB_CPAP_TEST_ADJUST_DB[end_of_adjust_table]=
{
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
        tADJUST_PEEP_CPAP,
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
        tADJUST_HIGH_R_CPAP,
        tHIGH_R_NO_SELECT_CPAP,
    {NONE,NONE,NONE,NONE},
        tADJUST_INSP_SENS_CPAP, 
        tINSP_SENS_NO_SELECT_CPAP,
        tADJUST_EXH_SENS_CPAP,
        tAUTO_EXH_SENS_SELECT_CPAP,
        tADJUST_APNEA_CPAP,
        tAUTO_APNEA_SELECT_CPAP,
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
        tADJUST_LOW_VTI_CPAP,
        tLOW_VTI_NO_SELECT_CPAP,
        tADJUST_HIGH_VTI_CPAP,
        tHIGH_VTI_NO_SELECT_CPAP,
        tADJUST_TI_MIN_CPAP,
        tTI_MIN_AUTO_SELECT_CPAP,
        tADJUST_TI_MAX_CPAP,
        tTI_MAX_AUTO_SELECT_CPAP,
        tPI_SET_POINT_CPAP,
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
        tRISE_TIME_CPAP,
        tADJUST_HIGH_LEAK_CPAP,
        tHIGH_LEAK_SELECT_CPAP,
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
        tADJUST_DISCONNECTION_DELAY_CPAP,
        tDISCONNECTION_DELAY_AUTO_CPAP
};

/* PRES CONSTANTS */
const t_TEST_EEPROM_DB cDB_PRES_TEST_ADJUST_DB[end_of_adjust_table]=
{
    {NONE,NONE,NONE,NONE},
        tADJUST_P_CONTROL_PRES,
        tADJUST_PEEP_PRES,
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
        tADJUST_CONTROL_R_PRES,
    {NONE,NONE,NONE,NONE},
        tADJUST_HIGH_R_PRES,
        tHIGH_R_NO_SELECT_PRES,
        tADJUST_TI_CONTROL_PRES,
        tADJUST_INSP_SENS_PRES,
        tINSP_SENS_NO_SELECT_PRES,
    {NONE,NONE,NONE,NONE},  
    {NONE,NONE,NONE,NONE},  
    {NONE,NONE,NONE,NONE},  
    {NONE,NONE,NONE,NONE},  
    {NONE,NONE,NONE,NONE},  
    {NONE,NONE,NONE,NONE},  
        tADJUST_LOW_VTE_PRES,   
        tLOW_VTE_NO_SELECT_PRES,    
        tADJUST_HIGH_VTE_PRES,  
        tHIGH_VTE_NO_SELECT_PRES,   
        tADJUST_RISE_TIME_PRES, 
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
        tADJUST_LOW_VTI_PRES,   
        tLOW_VTI_NO_SELECT_PRES,    
        tADJUST_HIGH_VTI_PRES,  
        tHIGH_VTI_NO_SELECT_PRES,   
    {NONE,NONE,NONE,NONE},  
    {NONE,NONE,NONE,NONE},  
    {NONE,NONE,NONE,NONE},  
    {NONE,NONE,NONE,NONE},  
        tPI_SET_POINT_PRES, 
    {NONE,NONE,NONE,NONE},  
    {NONE,NONE,NONE,NONE},  
    {NONE,NONE,NONE,NONE},  
        tPEEP_NO_SELECT_PRES,   
        tRISE_TIME_PRES,    
        tADJUST_HIGH_LEAK_PRES, 
        tHIGH_LEAK_SELECT_PRES, 
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
        tADJUST_TARGET_VT_PRES, 
        tTARGET_VT_SELECT_PRES, 
        tADJUST_MAX_PRESSURE_PRES,  
    {NONE,NONE,NONE,NONE},  
    {NONE,NONE,NONE,NONE},  
    {NONE,NONE,NONE,NONE},  
    {NONE,NONE,NONE,NONE},  
    {NONE,NONE,NONE,NONE},  
        tADJUST_DISCONNECTION_DELAY_PRES,
        tDISCONNECTION_DELAY_AUTO_PRES
};


/* CONTROL CONSTANTS */
//const t_TEST_EEPROM_DB cDB_TEST_CONTROL_DB [end_of_db_control_table]=
t_TEST_EEPROM_DB cDB_TEST_CONTROL_DB [end_of_db_control_table]=
{
    tVENTIL_AUTHORIZATION,
    tCURRENT_MODE,
    tCHANGE_MODE,
    tVENTIL_STATE,
    tSIMV_CYCLES,
    tCALIB_PATIENT_PRESS_REQ,
    tCALIB_FLOW_INSP_REQ,
    tCALIB_FLOW_EXH_REQ,
    tCALIB_VALVE_PRESS_REQ,
    tCALIB_FAS_VALVE_REQ_U16,
    tINHIBIT_BUZZER_REQ,
    tINHIBITION_AUTHORIZATION,
    tALARM_CANCEL_REQ,
    tBUZZER_CDE,
    tCALIB_ADJUST_CMD,
    tMAINT_CONTROL_SET_POINT,
    tMAINT_CONTROL_TYPE,
    tSUPPLY_AC_DC_BAT,
    tDISPLAY_BATTERY,
    tCURRENT_PATIENT_COUNTER_HOUR,
    tCURRENT_PATIENT_COUNTER_MIN,
    tCURRENT_MACHINE_COUNTER_HOUR,
    tCURRENT_MACHINE_COUNTER_MIN,
    tCONTROL_BUZZER,
    tVALVE_DETECTED,
    tAC_SELECTED,
    tDC_SELECTED,
    tREMOTE_STATE,
    tPROXI_DETECTED,
    tALARM_DETECTED,
    tNEW_ALARM_HP_DETECTED,
    tStart_Limit_Setting,
    tLIMIT_LOW_PIP,
    tLIMIT_HIGH_PIP,
    tLIMIT_PEEP,
    tLIMIT_VOL_CONTROL,
    tLIMIT_TI_CONTROL,
    tLIMIT_CONTROL_R,
    tLIMIT_PI_U16,
    tLIMIT_LOW_VTI,
    tLIMIT_HIGH_VTI,
    tLIMIT_LOW_VTE,
    tLIMIT_HIGH_VTE,
    tLIMIT_P_SUPPORT,
    tLIMIT_TI_MIN,
    tLIMIT_TI_MAX,
    tLIMIT_SPO2_MINI,
    tLIMIT_SPO2_MAXI,
    tLIMIT_INSP_SENS,
    tLIMIT_SIGH,
    tLIMIT_TARGET_VT,
    tLIMIT_APNEA,
    tLIMIT_HIGH_FIO2,
    tLIMIT_LOW_FIO2,
    tLIMIT_SPO2,
    tLIMIT_BACKUP_R,
    tLIMIT_PMAX,
    tEnd_Limit_Setting,
    tUNCANCELL_CMD,
    tFAILURE_BUS,
    tKEYBOARD_ANOMALIE,
    tVALIDATION_BIP,
    tBIP_RUNNING,
    tMAINTENANCE_MODE,
    tCALIBRATION_MODE,
    tTEST_BUZ_CARD,
    tTEST_BUZ_SEC,
    tTEST_VOLUME,
    tCANCEL_ALARM_ASKED,
    tKEY_EVENT,
    tBACKLIGHT_OFF,
    tHIGH_PRESSURE_LED_REMINDER,
    tRECORD_SETTINGS_USB_U16,
    tAPPLY_SETTINGS_USB_U16,
    tERASE_KEY_USB_U16,
    tRECORD_TIME_TENDANCE_U16,
    tERROR_SPO2_SENSOR_DETECTED,
    tDETECTED_FIO2_SENSOR,
    tCALIBRATED_FIO2_SENSOR,
    tCALIB_ADJUST_VANNE_FIO2_CMD,
    tCALIB_FIO2_REQ,
    tCALIB_FLOW_O2_REQ,
    tMEMO_CMD_VANNE_FIO2_TO_CALIB,
    tCALIB_PRESS_O2_REQ,
    tFLOW_SAT_FLAG,
    tHIGH_PRESSURE_DETECTED,
    tHIGH_PRESSURE_EXHALATION_DETECTED,
    tHIGH_PRESSURE_DETECT_WINDOW,
    tFIO2_100_ACTIVE,
    tLOAD_USB_SETTINGS,
    tCOM_READY,
    tSTART_MONITORING,
    tSIMV_PSV_CYCLE_U16,
    #if defined(SUPPORTAIR_M2) || defined(LEGENDAIR_XL2)
    tBLOC_EXPI_DETECTED,
    #else
    {NONE,NONE,NONE,NONE},
    #endif	
        tADJUSTMENT_IN_PROGRESS_U16,
        tVALVE_DETECT_IN_PROGRESS_U16,
        tEXHAL_FLOW_USE_U16,  
        tFLAT_INT_U16,  
        tFLAT_PROXI_U16,
        tVALVE_O2_CMD_U16,
        tCPAP_TRIG_I,
        tCPAP_TRIG_E,
        tCONTROLER_TYPE_U16,
        tVTI_DISPLAY_DELAY_U16,
        tVOLUNTARY_STOP_U16,
        tSIMV_CONTROLLED_INSP_U16,
        tEND_OF_OPERATION_U16,
};

/* CONFIG CONSTANTS */
const t_TEST_EEPROM_DB cDB_TEST_CONFIG_DB[end_of_db_config_table]=
{
    tADJUST_LANGUAGE,                   
    tADJUST_MODE,                           
    tADJUST_KEYLOCK,
    tVENTIL_REQ,                            
    tOFFSET_INSP_FLOW_1,                        
    tOFFSET_INSP_FLOW_2,                    
    tOFFSET_INSP_FLOW_3,                    
    tOFFSET_INSP_FLOW_4,                    
    tOFFSET_INSP_FLOW_5,                        
    tOFFSET_INSP_FLOW_6,                        
    tOFFSET_INSP_FLOW_7,                
    tOFFSET_INSP_FLOW_8,                        
    tOFFSET_EXH_FLOW_1,                         
    tOFFSET_EXH_FLOW_2,                     
    tOFFSET_EXH_FLOW_3,
    tOFFSET_EXH_FLOW_4,                     
    tOFFSET_EXH_FLOW_5,                     
    tOFFSET_EXH_FLOW_6,                     
    tOFFSET_EXH_FLOW_7,                 
    tOFFSET_EXH_FLOW_8,             
    tOFFSET_O2_FLOW_1,
    tOFFSET_O2_FLOW_2,
    tOFFSET_O2_FLOW_3,
    tOFFSET_O2_FLOW_4,
    tOFFSET_O2_FLOW_5,
    tOFFSET_O2_FLOW_6,
    tOFFSET_O2_FLOW_7,
    tOFFSET_PATIENT_PRESS1,
    tOFFSET_PATIENT_PRESS2,
    tOFFSET_PATIENT_PROX_PRESS1,
    tOFFSET_PATIENT_PROX_PRESS2,
    tOFFSET_PRESS_O2,
    tI_VALVE_REF_U16,
    tOFFSET_FAS_VALVE_1_U16,
    tOFFSET_FAS_VALVE_2_U16,
    tOFFSET_FAS_VALVE_3_U16,
    tOFFSET_FAS_VALVE_4_U16,
    tOFFSET_FAS_VALVE_5_U16,    
    tOFFSET_FAS_VALVE_6_U16,    
    tOFFSET_FAS_VALVE_7_U16,    
    tOFFSET_FAS_VALVE_8_U16,    
    tOFFSET_FAS_VALVE_9_U16,    
    tOFFSET_VALVE_PRESS,
    tOFFSET_VALVE_PRESS2,                                               
    tOFFSET_FIO2,
    tADJUST_BRIGHTNESS,                      
    tADJUST_BACKLIGHT,                       
    tSAVED_PATIENT_COUNTER_HOUR, //N				 
    tSAVED_PATIENT_COUNTER_MIN,              
    tSAVED_MACHINE_COUNTER_HOUR,                 
    tSAVED_MACHINE_COUNTER_MIN,
    tRETRIEVAL_EVENT_ADRESS_MSB,                     
    tRETRIEVAL_EVENT_ADRESS_LSB,
    tFLASH_MONIT_WRITE_BLOCK,
    tFLASH_MONIT_WRITE_PAGE,
    tFLASH_MONIT_WRITE_COLUMN,
    tFLASH_TREND_WRITE_BLOCK,
    tFLASH_TREND_WRITE_PAGE,
    tFLASH_TREND_WRITE_COLUMN,
    tFLASH_FIRST_PARTITION_FULL,
    tFLASH_SECOND_PARTITION_FULL,
    tSPEED_COM, 
    tRAZ_COUNTER_PAT_DATE,                   
    tRAZ_COUNTER_PAT_MONTH,                  
    tRAZ_COUNTER_PAT_YEAR,                   
    tRAZ_COUNTER_PAT_HOUR,
    tRAZ_COUNTER_PAT_MIN,                        
    tBAD_ERASE,
    tSOUND_LEVEL_SELECT,
    tPREVIOUS_SOUND_LEVEL_SELECT,
    tCURVE_DISPLAY_TYPE_MODE,
    tCURVE_MAX_PRESSURE,
    tCURVE_MAX_FLOW,
    tCURVE_MAX_VT,
    tCURVE_MAX_TIME,
    tCURVE_DRAW_MODE,
    tADJUST_CYCLING_MODE,                       
    tADJUST_KEY_TONE,
    tWAVEFORME_DISPLAY,
    tADJUST_BAROMETRIC_CORRECTOR,
    tADJUST_FIO2,
    tADJUST_FIO2_SELECT,
    #if defined(SUPPORTAIR_M2)
    tADJUST_LOW_FIO2_M2,
    tADJUST_HIGH_FIO2_M2,
    #endif
    #if defined (LEGENDAIR_XL2)
    tADJUST_LOW_FIO2_XL2,
    tADJUST_HIGH_FIO2_XL2,
    #endif
    #if defined (LEGENDAIR_S2)
    {NONE,NONE,NONE,NONE},  
    {NONE,NONE,NONE,NONE},
    #endif
        tADJUST_LOW_SPO2,
        tADJUST_HIGH_SPO2,
        tSPO2_LOW_SELECT,
        tSPO2_HIGH_SELECT,
        tADJUST_LOW_FIO2_SELECT,
        tADJUST_HIGH_FIO2_SELECT,
        tPRESSURE_UNIT,        
        tTRIGGER_E_POSITIVE,
        tAPNEA_ALARM_ACTIVATION,
        tFLASH_MEM_MANUFACTURER,
        tFLASH_MEM_DEVICE,
        tFLASH_MEMORY_FIVE_ADDRESS_CYCLES,
        tPARAM_COMPATIBILITY,
        tIHM_LOCKED_FRAME_ID,
        tPEDIACTRIC_CIRCUIT,
        tPREVIOUS_MODE, 
        tPRESSURE_SUPPORT_RELATIVE,
        tPRESSURE_SUPPORT_CHANGED_U16,
     tVOLUNTARY_STOP_ALARM_ACTIVATION,
     tSOUND_TYPE_SELECT_U16
};


/* RTC CONSTANTS */
const t_TEST_EEPROM_DB cDB_TEST_RTC_DB [end_of_db_rtc_table]=
{
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
        tADJUST_RTC_REQ,
        tADJUST_RTC_SECOND,
        tADJUST_RTC_MINUTE,
        tADJUST_RTC_HOUR,
        tADJUST_RTC_DAY,
        tADJUST_RTC_MONTH,
        tADJUST_RTC_YEAR
};

/*USB CONSTANTS*/
const t_TEST_EEPROM_DB cDB_TEST_USB_DB [end_of_db_usb_table]=
{
    tADJUST_USB_ERASE_KEY,
    tADJUST_USB_TRANSFER_APPLY,
    tADJUST_USB_CONTINUOUS_RECORDING,
    tADJUST_USB_MONITOR_TRANSFER,
    tADJUST_USB_MONITOR_TRANSFER_SELECT,
    tADJUST_USB_TREND_TRANSFER,
    tADJUST_USB_TREND_TRANSFER_SELECT,
    tADJUST_USB_EVENTS_TRANSFER,
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE},
    {NONE,NONE,NONE,NONE}
};

/* VERSION CONSTANTS */
const t_TEST_EEPROM_DB cDB_TEST_VERSION_DB[end_of_db_version_table]=
{
    tVERSION_NUMBER_0,                       
    tVERSION_NUMBER_1,                       
    tVERSION_NUMBER_2,
    tVERSION_NUMBER_3,                       
    tSERIAL_NUMBER_1,                        
    tSERIAL_NUMBER_2,                        
    tSERIAL_NUMBER_3,                        
    tSERIAL_NUMBER_4,                        
    tSERIAL_NUMBER_5,                        
    tSERIAL_NUMBER_6                         
};

/* TREND CONSTANTS */
const t_TEST_EEPROM_DB cDB_TEST_TREND_DB[end_of_db_trend_table]=
{
    tDB_TREND_VENTIL_HOUR, 
    tDB_TREND_VENTIL_MIN,
    tDB_TREND_AVG_VTI, 
    tDB_TREND_AVG_VTE, 
    tDB_TREND_AVG_VM,  
    tDB_TREND_AVG_FR,  
    tDB_TREND_LEAK_MODE,
    tDB_TREND_AVG_LEAK,    
    tDB_TREND_AVG_PI,  
    tDB_TREND_IA,      
    tDB_TREND_APNEA,       
    tDB_TREND_PERCENT_CONTROLLED,
    tDB_TREND_PERCENT_TRIGGERED,
    tDB_TREND_SAVE_RTC_DAY,    
    tDB_TREND_SAVE_RTC_MONTH,
    tDB_TREND_SAVE_RTC_YEAR,   
    tDB_TREND_SAVE_PC_HOUR,
    tDB_TREND_SAVE_PC_MIN,
    tDB_TREND_NB_APNEA,
    tDB_TREND_APNEA_TIME,
    tDB_TREND_NB_CYCLE_COUNTER_MSB,
    tDB_TREND_NB_CYCLE_COUNTER_LSB,
    tDB_TREND_NB_CYCLE_TRIGERRED_MSB,
    tDB_TREND_NB_CYCLE_TRIGERRED_LSB,
    tDB_TREND_NB_CYCLE_CONTROLLED_MSB,
    tDB_TREND_NB_CYCLE_CONTROLLED_LSB,
    tDB_TREND_VENTIL_REPORT_UPD,
    tDB_TREND_IHM_VENTIL_HOUR, 
    tDB_TREND_IHM_VENTIL_MIN,
    tDB_TREND_IHM_AVG_VTI, 
    tDB_TREND_IHM_AVG_VTE, 
    tDB_TREND_IHM_AVG_VM,  
    tDB_TREND_IHM_AVG_FR,  
    tDB_TREND_IHM_LEAK_MODE,
    tDB_TREND_IHM_AVG_LEAK,    
    tDB_TREND_IHM_AVG_PI,  
    tDB_TREND_IHM_IA,  
    tDB_TREND_IHM_APNEA,   
    tDB_TREND_IHM_PERCENT_CONTROLLED,
    tDB_TREND_IHM_PERCENT_TRIGGERED,
    tDB_TREND_IHM_SAVE_RTC_DAY,
    tDB_TREND_IHM_SAVE_RTC_MONTH,
    tDB_TREND_IHM_SAVE_RTC_YEAR
};

/*COMPUTE CONSTANTS*/
const t_TEST_EEPROM_DB_SATURATE cDB_Saturate_COMPUTE [end_of_db_compute_table]= {
    sMEASURE_VALVE_PRESSURE_S16 ,
    sFILTER_VALVE_PRESSURE_S16 ,
    sMEASURE_INTERNAL_PRESSURE_S16 ,
    sFILTER_INTERNAL_PRESSURE_S16 ,
    sMEASURE_PATIENT_PRESSURE_PROXI_S16 ,
    sFILTER_PATIENT_PRESSURE_PROXI_S16 ,
    sMEASURE_PATIENT_PRESSURE_S16 ,
    sFILTER_PATIENT_PRESSURE_S16 ,
    sMEASURE_QINSP_S16 ,
    sFILTER_QI_S16 ,
    sFILTER_QI_LOW_S16 ,
    sMEASURE_QEXH_S16 ,
    sFILTER_QE_S16 ,
    sCOMPUTED_VTE_U16 ,
    sCOMPUTED_VTE_INSP_U16 ,
    sCOMPUTED_PIP_U16 ,
    sCOMPUTED_PEEP_U16 ,
    sCOMPUTED_FIO2 ,
    sMEASURE_FIO2 ,
    sMEASURE_IE_NUMERATOR_U16 ,   
    sMEASURE_IE_DENOMINATOR_U16 ,
    sMEASURE_TI_U16 ,
    sMEASURE_TI_HMI_U16 ,
    sMEASURE_TE_U16 ,
    sMEASURE_R_U16 ,
    sMEASURE_SPEED_BLOWER_U16 ,
    sFILTER_SPEED_BLOWER_S16 ,
    sCOMPUTED_BATTERY_LEVEL_U16 ,
    sMEASURE_SUPPLY_5V_U16 ,
    sMEASURE_SUPPLY_24V_U16 ,
    sMEASURE_TEST_BUZZER_VOLTAGE_U16 , 
    sMEASURE_BUZZER_VOLTAGE_U16 , 
    sMEASURE_BATTERY_BUZZER_VOLTAGE_U16 , 
    sMEASURE_PFI_VOLTAGE_U16 ,
    sCOMPUTED_PI_SET_POINT_U16 ,
    sCOMPUTED_VTI_EXH_S16 ,
    sMEASURE_SPO2_U16 ,
    sMEASURE_HR_U16 ,
    sCOMPUTED_LEAK_U16 ,
    sCOMPUTED_LEAK_HMI_U16 ,
    sCURVE_CORRECTED_VT_WOB_U16 ,
    sCURVE_CORRECTED_FLOW_S16 ,
    sCOMPUTED_TEMP_S16 ,     /* Battery temperature */
    sCOMPUTED_VTI_U16 ,
    sCOMPUTED_USED_44_U16,
    sCOMPUTED_USED_45_U16,
    sMEASURE_BATTERY_VOLTAGE_U16 ,
    sCOMPUTED_VMI_U16 ,
    sCOMPUTED_VME_U16 ,
    sAVERAGE_PRESSURE_U16 ,
    sMEASURE_ABSOLUTE_PRESSURE_U16 ,
    sMEASURE_BLOWER_TEMPERATURE_S16 ,
    sCOMPUTED_RISE_TIME_U16 ,
    sMEASURE_IT_U16 ,
    sMEASURE_BATTERY_CAPACITY_U16 ,
    sCOMPUTED_PULSE_U16 ,
    sCOMPUTE_CORRECTED_Q ,
    sCOMPUTED_TI_CONTROL_U16 ,
    sFILTER_QO2_S16 ,
    sFILTER_PRESSURE_O2_S16 ,
    sMEASURE_PRESSURE_O2_S16 , 
    sMEASURE_QO2_S16 ,
    sCOMPUTED_IE_NUMERATOR_U16 ,               
    sCOMPUTED_IE_DENOMINATOR_U16 ,
    sCOMPUTE_QEE_S16 ,
    sCOMPUTED_I_T_U16 ,
    sMEAS_ABS_PRESS_MMHG_U16 ,
    sCOMPUTED_RATE_U16 ,
    sBLOWER_COMMAND_U16 , 
    sMEASURE_ZERO_VALUE_U16 ,
    sCOMPUTED_P_VALVE_MAX_U16 ,
    sCUMUL_PRESS_INSP_S16 ,
    sESTIMATED_PROXIMAL_PRESSURE_S16 ,
    sMEASURE_QINSP_LEAKCORRECTED_S16 ,
    sMEASURE_VALVE_CURRENT_U16,
    sMEAN_INSP_VALVE_CURRENT_U16,
    sVALVE_COMMAND_INIT_U16,    
    sVALVE_COMMAND_MIN_U16,
    sVALVE_COMMAND_MAX_U16,
    sVALVE_COMMAND_COEFF_U16,   
    sVALVE_COMMAND_U16 ,
    sLPF_PATIENT_PRESSURE_S16,
    sCOMPUTED_LPF_PIP_U16,
    sLEAK_TEST_QI_S16,
    sLEAK_TEST_RESULT_U16
};

/*POWER_SUPPLY CONSTANTS*/
const t_TEST_EEPROM_DB_SATURATE cDB_Saturate_POWERSUPPLY[end_of_db_powersupply_table]=
{
    sV_BAT_U16,
    sTEMP_BAT_S16,
    sBAT_CYCLES_U16,   /* Identifier; Nb cycles */
    sBAT_STATE_U16,       /* Default...*/
    sPOWER_TYPE_U16,
    sJAUGE_MINUTE_U16,
    sJAUGE_HOUR_DISPLAY_U16,
    sJAUGE_MINUTE_DISPLAY_U16,
    sJAUGE_AVALAIBLE_U16,
    sPER_CENT_BAT_U16,
    sNO_PRESENCE_BAT_U16,
    sBAT_KO_U16,
    sCHARGE_KO_U16,
    sUNKNOWN_BATTERY_U16,
    sAMBIENT_TEMP_S16,
    sBATTERY_END_U16,
    sBATTERY_LOW_U16,
    sFIRST_DATE_DAY_U16,
    sFIRST_DATE_MONTH_U16,
    sFIRST_DATE_YEAR_U16,
    sCOOLING_FAN_FAILURE_FLAG_U16,
    sAMBIENT_TEMP_OUTOFBOUNDS_U16,
    sFAILURE_24V_FLAG_U16,
    sBAT_TEMP_OUTOFBOUNDS_U16,
    sSUPPLY_MEASURE_FAILURE_U16,
    sPOWER_SUPPLY_VERSION_NUMBER_0,
    sPOWER_SUPPLY_VERSION_NUMBER_1,
    sPOWER_SUPPLY_VERSION_NUMBER_2,
    sSUPPLIER_U16,
    sCAPACITY_U16,
    sCAPACITY_THEORICAL_U16,
    sFIRST_DATE_HOUR_U16,
    sFIRST_DATE_MINUTE_U16,
    sFIRST_DATE_SECOND_U16,
    sAGING_U16,
};

/* Ventilation modes high limits at the start */
const UWORD16 cMODE_HIGH_LIMIT_VALUE = nb_of_mode;

/*%C Event number table, corresponding to the adjusted Id  */
const UWORD16 EventNumber[end_of_adjust_table] = {
    EVENT_MODIF_VOL_CONTROL,
    EVENT_MODIF_P_CONTROL,
    EVENT_MODIF_PEEP,
    EVENT_MODIF_P_SUPPORT,
    EVENT_MODIF_RAMP,
    EVENT_MODIF_CONTROL_R,
    EVENT_MODIF_BACKUP_R,
    EVENT_MODIF_HIGH_R,
    NO_EVENT,
    EVENT_MODIF_TI_CONTROL,
    EVENT_MODIF_INSP_SENS,
    NO_EVENT,
    EVENT_MODIF_EXH_SENS,
    NO_EVENT,
    EVENT_MODIF_APNEA_TIME,
    NO_EVENT,
    EVENT_MODIF_LOW_PIP,
    EVENT_MODIF_HIGH_PIP,
    EVENT_MODIF_LOW_VTE,
    NO_EVENT,
    EVENT_MODIF_HIGH_VTE,
    NO_EVENT,
    EVENT_MODIF_RISE_TIME,
    NO_EVENT,
    NO_EVENT,
    NO_EVENT,
    NO_EVENT,
    EVENT_MODIF_LOW_VTI,
    NO_EVENT,
    EVENT_MODIF_HIGH_VTI,
    NO_EVENT,
    EVENT_MODIF_TI_MINI,
    NO_EVENT,
    EVENT_MODIF_TI_MAXI,
    NO_EVENT,
    NO_EVENT,
    NO_EVENT,
    NO_EVENT,
    NO_EVENT,
    NO_EVENT,
    EVENT_MODIF_RISE_TIME,
    EVENT_MODIF_MAX_LEAK,
    NO_EVENT,
	EVENT_MODIF_IE,
	NO_EVENT,
	EVENT_MODIF_IT,
    EVENT_MODIF_VTC,
    NO_EVENT,
    EVENT_MODIF_PIMAX,
    EVENT_MODIF_EXH_SENS,
    NO_EVENT,
    NO_EVENT,
    EVENT_MODIF_SIGHT_COUNT,
    EVENT_MODIF_SIGHT_COEF,
    EVENT_MODIF_DISCONNECTION_DELAY,
    NO_EVENT
};

/******************************************************************************/
/*                		 VARIABLE DECLARATIONS			                       	*/
/******************************************************************************/

/* SIMV BACKUP R declaration */
UWORD16 Simv_Backup_R = 12u;

/* MemoMode declaration */
e_MODE_TYPES MemoMode = VOL; 

/* Declaration for init functions */
UWORD16 DB_FirstStart = FALSE;
UWORD16 BadParameter = FALSE;
UWORD16 NewVersionDetected = FALSE;
UWORD16 BadVersion = FALSE;
UWORD16 LoosePara = FALSE;
UWORD16 DB_StartInitRequest = FALSE;



/* Tables for check eeprom result */
UWORD16 DB_EepConfigDbError[end_of_db_config_table];

/* Tables for check eeprom result */
UWORD16 DB_EepTrendDbError[end_of_db_trend_table];

/* Rise time array values (in ms)                 	                           */
UWORD16 RiseTime[cRISE_TIME] = {200, 400, 600, 800};



#else 
/******************************************************************************/
/*                  	    EXTERNAL  			DECLARATION          					*/
/******************************************************************************/

/******************************************************************************/
/*                  	    EXTERNAL CONSTANT DECLARATION          					*/
/******************************************************************************/
/* VSIMV CONSTANTS */
extern const t_TEST_EEPROM_DB cDB_VSIMV_TEST_ADJUST_DB[];

/* PSIMV CONSTANTS */
extern const t_TEST_EEPROM_DB cDB_PSIMV_TEST_ADJUST_DB[];

/* VOL CONSTANTS */
extern const t_TEST_EEPROM_DB cDB_VOL_TEST_ADJUST_DB[];

/* PSV CONSTANTS */
extern const t_TEST_EEPROM_DB cDB_PSV_TEST_ADJUST_DB[];

/* CPAP CONSTANTS */
extern const t_TEST_EEPROM_DB cDB_CPAP_TEST_ADJUST_DB[];

/* PRES CONSTANTS */
extern const t_TEST_EEPROM_DB cDB_PRES_TEST_ADJUST_DB[];

/* CONTROL CONSTANTS */
//extern const t_TEST_EEPROM_DB cDB_TEST_CONTROL_DB [];
extern t_TEST_EEPROM_DB cDB_TEST_CONTROL_DB [];

/* CONFIG CONSTANTS */
extern const t_TEST_EEPROM_DB cDB_TEST_CONFIG_DB[];

/* RTC CONSTANTS */
extern const t_TEST_EEPROM_DB cDB_TEST_RTC_DB [];

/* USB CONSTANTS */
extern const t_TEST_EEPROM_DB cDB_TEST_USB_DB [];

/* VERSION CONSTANTS */
extern const t_TEST_EEPROM_DB cDB_TEST_VERSION_DB[];

/* TREND CONSTANTS */
extern const t_TEST_EEPROM_DB cDB_TEST_TREND_DB[];

/*COMPUTE CONSTANTS*/
extern t_TEST_EEPROM_DB_SATURATE    cDB_Saturate_COMPUTE [];

/*POWER_SUPPLY CONSTANTS*/
extern  t_TEST_EEPROM_DB_SATURATE cDB_Saturate_POWERSUPPLY[];

/* Ventilation modes high limits at the start */
extern const UWORD16 cMODE_HIGH_LIMIT_VALUE;

/*%C Event number table, corresponding to the adjusted Id  */
extern const UWORD16 EventNumber[end_of_adjust_table];

/******************************************************************************/
/*                    EXTERNAL FUNCTION DECLARATION 				          	  	*/
/******************************************************************************/
extern UWORD16 DB_IhmAccessParaDataBase(UWORD16 *Value,
                                        UWORD16 Id,
                                        e_TYPE_OF_DB_TARGET DbType,
                                        e_DATA_OPERATION DataOperation);

extern UWORD16 DB_IHM_Read_Access(UWORD16 *Value,
                                  UWORD16 Id,
                                  e_TYPE_OF_DB_TARGET DbType);

extern UWORD16 DB_IHM_Read_Info_Access( UWORD16 *Value, 
                                        UWORD16 Id, 
                                        e_TYPE_OF_DB_TARGET DbType);

extern void DB_WriteDataInEepAndRam(UWORD16 xhuge *data_address,
                                    UWORD16 value);

extern UWORD16 DB_IHM_Write_Access(UWORD16 *Value,
                                   UWORD16 Id,
                                   e_TYPE_OF_DB_TARGET DbType);

extern UWORD16 DB_IHM_Write_Info_Access(UWORD16 *Value, 
                                        UWORD16 Id, 
                                        e_TYPE_OF_DB_TARGET DbType); 

extern UWORD16 DB_IHM_Increase_Access(UWORD16 *Value,
                                      UWORD16 Id,
                                      e_TYPE_OF_DB_TARGET DbType);

extern UWORD16 DB_IHM_Decrease_Access(UWORD16 *Value,
                                      UWORD16 Id,
                                      e_TYPE_OF_DB_TARGET DbType);

extern UWORD16 DB_IHM_Setting_Adjust_Vol_Mode(UWORD16 *Value,
                                              UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Pres_Mode(UWORD16 *Value,
                                               UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Psv_Mode(UWORD16 *Value,
                                              UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Cpap_Mode(UWORD16 *Value,
                                               UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Vsimv_Mode(UWORD16 *Value,
                                                UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Psimv_Mode(UWORD16 *Value,
                                                UWORD16 Id);  


extern UWORD16 DB_IHM_Increase_Config(UWORD16 *Value,
                                      UWORD16 Id);

extern UWORD16 DB_IHM_Decrease_Config(UWORD16 *Value,
                                      UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Rtc_Day(UWORD16 *Value);

/* Settings and alarms event management */
extern void DB_EventMngt (UWORD16 Value);


/******************************************************************************/
/*                EXTERNAL VARIABLE DECLARATIONS		                       	*/
/******************************************************************************/

/* MemoMode declaration */
extern e_MODE_TYPES MemoMode; 

/* SIMV BACKUP R declaration */
extern UWORD16 Simv_Backup_R;

/* Declaration for init functions */
extern UWORD16 DB_FirstStart;
extern UWORD16 BadParameter;
extern UWORD16 NewVersionDetected;
extern UWORD16 BadVersion;
extern UWORD16 LoosePara;
extern UWORD16 DB_StartInitRequest;

/* Tables for check eeprom result */
extern UWORD16 DB_EepConfigDbError[];

/* Tables for check eeprom result */
extern UWORD16 DB_EepTrendDbError[];

/* Rise time array values (in ms)                 	                           */
extern UWORD16 RiseTime[];

#endif


#endif

