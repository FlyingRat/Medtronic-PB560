/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : Ventilation_Constants.h                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   Constant declaration for ventilation function                          */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/



#ifndef VENTILATION_CONSTANTS_H
#define VENTILATION_CONSTANTS_H

/******************************************************************************/
/*                           CONSTANT DECLARATION                      	      */
/******************************************************************************/

#define  cVEN_SLOPE_1  200u					// Periode en ms associé à la pente 1
#define  cVEN_SLOPE_2  400u 					// Periode en ms associé à la pente 2
#define  cVEN_SLOPE_3  600u					// Periode en ms associé à la pente 3
#define  cVEN_SLOPE_4  800u					// Periode en ms associé à la pente 4

#define  cDELTA_PI  99u
#define  cDELTA_QINSP  90u
#define  cDELTA_PE 10u

#define  cTRANSITION_TIMEOUT 50u
#define  cINSP_RISE_TIMEOUT 500u
#define  cEXH_FALL_TIMEOUT 2000u
// step du Vt cible
#define  cMIN_STEP 5u
#define  cMAX_STEP 20u

// step de la boucle fermée de débit
#define  cOFFSETQINSP 40u
#define  cDELTA_MINI 100u
#define  cDELTA_MAXI 100u
#define  cQ_STEP_MIN 95u
#define  cQ_STEP_MAX 105u

/* Blower Speed to reach during test*/
#define cSPEED_BLOWER_TEST  13000U

#define  cT_RISE_MIN 150UL
#define  cT_RISE_MAX 350UL	

#define  cVEN_3S 3000u		 // Constante 3 sec pour calcul valeur max de l'apnée;
#define  cVEN_TRIGGER_DELAY 700u // Retard de 700ms pour détection du trigger;

#define  cBLOWER_CMD_OFF 	4097        // 2 point > valeur maxi de PWM pour assurer une commande à zéro
#define  cVALVE_CMD_ON		0U				// Commande valve ON (valve ouverte)
#define  cVALVE_CMD_OFF		2672u			// Commande valve OFF (valve fermée)
#define  cVALVEO2_CMD_OFF 	2670U			// Commande valve O2 OFF (valve fermée)
#define  cPOWER_MAX			100U			// Puissance de freinage max
#define  cPOWER				45U				// Puissance de freinage en IDLE				
#define  BRAKE_PERIOD 		65369U	   	// T0REL = 65535 - (periode PWM / 400ns) 
   															// Pour PWM a 15Khz T0REL = 65535 - 66,6us/400ns = 65369
#define  NB_TIMER0_VALUE 	166u				// 65535 - BRAKE_PERIOD correspond au nb d'échantillons 
																// qu'on peut donner au Timer
#define  cVALVE_BOOST		3
#define  cVALVE_BOOST_MAX	25
#define  cBOOST_TIMER	    2500

#define  cVEN_INTEGRAL_MAX 	30000L			// Valeur Max de l'intégrale *10 pour la turbine
#define  cVEN_INTEGRAL_MIN 	0L				// Valeur Min de l'intégrale pour la turbine
#define  cVEN_INTEGRAL_VALVE_MAX 26720UL 	// Valeur Max de l'intégrale *10 pour la valve
#define  cVEN_INTEGRAL_VALVE_MIN 0UL 		// Valeur Max de l'intégrale *10 pour la valve
#define  cVEN_INTEGRAL_EXH_FACTOR 20u
#define  cVEN_INTEGRAL_EXH_FALL_FACTOR 443u
#define  cVEN_INTEGRAL_EXH_PLAT_FACTOR 400u
#define  cVEN_INTEGRAL_EXH_FALL_STATIC 1500u
#define  cVEN_INTEGRAL_EXH_PLAT_STATIC 0u

#define  VT_COEF_PEDIA_DBRANCH  	6UL	// Vt compensation : Pediatric / Double Branch
#define  VT_COEF_ADULT_DBRANCH	12		// Vt compensation : Adult / Double Branch
#define  VT_COEF_PEDIA_SBRANCH	3UL	// Vt compensation : Pediatric / Simple Branch
#define  VT_COEF_ADULT_SBRANCH  	6UL	// Vt compensation : Adult / Simple Branch

/*----------------------------------------------------------------*/
/* 				PARAMETRES DE REGULATION EN INSPI FLOW VALVE			*/
/*----------------------------------------------------------------*/

// KI regul Turbine Constante intégrale phase plateau en inspi	
#define  cVEN_KIB_FLOW_INSP 1000UL
#define  cVEN_KPB_FLOW_INSP_MIN 50000UL		
#define  cVEN_KPB_FLOW_INSP_MAX 8000UL		
#define  cVEN_CMP_KPB_FLOW_TI_MAX 0UL
#define  cVEN_CMP_KPB_FLOW_TI_MIN 3000UL
#define  cVEN_KPB_FLOW_SIN  10000UL

#define  cVEN_PER_CENT_RISE_FLOW_DEF 0L         

/*----------------------------------------------------------------*/
/* 				PARAMETRES DE REGULATION EN INSPI PRESSURE VALVE	*/
/*----------------------------------------------------------------*/
#define  cVEN_KPB_MIN_INSP 90000UL			
#define  cVEN_KPB_MAX_INSP 120000UL			
#define  cVEN_DELTA_KP_MIN_INSP 100UL  			
#define  cVEN_DELTA_KP_MAX_INSP 200UL 			

#define  cVEN_KIB_MIN_INSP 1200UL			
#define  cVEN_KIB_MAX_INSP 500UL			
#define  cVEN_DELTA_KI_MIN_INSP 50UL  			
#define  cVEN_DELTA_KI_MAX_INSP 400UL 		

// Constante paramètres de régul par défaut lors du Rise pour éviter les dépassements : -30%
#define  cVEN_PER_CENT_RISE_PRESS_DEF  -30L         
	
/*----------------------------------------------------------------*/
/* 				PARAMETRES DE REGULATION EN EXPI	VALVE					*/
/*----------------------------------------------------------------*/
#define  KI_B  2000L 
#define  KP_B_MIN_PEP_0_8_MIN 200000UL   
#define  KP_B_MIN_PEP_0_8_MAX 40000UL    
#define  KP_B_MAX_PEP_1_3_MIN 600000UL        
#define  KP_B_MAX_PEP_1_3_MAX 400000UL      
#define  KP_B_MAX_PEP_4_8_MIN 400000UL     
#define  KP_B_MAX_PEP_4_8_MAX 200000UL     


#define  cPOWER_BRAKE_PEP_REGUL_HIGH_SB 40UL		
#define  cPOWER_BRAKE_PEP_REGUL_DEFAULT 30UL		

/*----------------------------------------------------------------*/
/* 				PARAMETRES DE REGULATION EN INSPI / EXPI MODE CPAP	*/
/*----------------------------------------------------------------*/
/*%C CPA constants */
#define  cVEN_KP_PPC_HIGH 50000UL 
#define  cVEN_KP_PPC_LOW 30000UL	 
#define  cVEN_KI_PPC 300UL	 

/*----------------------------------------------------------------*/
/* 				PARAMETRES DE REGULATION EN INSPI FUITE				*/
/*----------------------------------------------------------------*/
#define  cVEN_KPB_MIN_LEAK_INSP 150000UL			
#define  cVEN_KPB_MAX_LEAK_INSP 700000UL			
#define  cVEN_DELTA_KP_MIN_LEAK_INSP 130UL  			
#define  cVEN_DELTA_KP_MAX_LEAK_INSP 300UL 			

#define  cVEN_KIB_MIN_LEAK_INSP 500UL			
#define  cVEN_KIB_MAX_LEAK_INSP 1500UL			
#define  cVEN_DELTA_KI_MIN_LEAK_INSP 20UL  			
#define  cVEN_DELTA_KI_MAX_LEAK_INSP 150UL 			

/*----------------------------------------------------------------*/
/* 				PARAMETRES DE REGULATION EN EXPI FUITE					*/
/*----------------------------------------------------------------*/
#define  cVEN_LEAK_EXH_PLATEAU_RAMP_KP_TIME 500UL			
#define  cVEN_KPB_LEAK_EXH_PLATEAU_START 700000UL		
#define  cVEN_KPB_LEAK_EXH_PLATEAU_END 250000UL		

// KI regul Turbine Constante intégrale phase plateau en expi	
#define  cVEN_KIB_LEAK_EXH_PLATEAU 500UL	

// Temps pendant lequel la regul Pe sera forte
#define  cTIME_END_BRAKE 2000u  			

 

/*----------------------------------------------------------------------*/
/* 		PARAMETRES DE REGULATION DE LA TURBINE EN INIT 						*/
/*----------------------------------------------------------------------*/

/*%C Integral for initialization */
#define  cVEN_KPB_INIT 2000L
/*%C Proportional for initialization */
#define  cVEN_KIB_INIT 50L


/*----------------------------------------------------------------------*/
/* 		PARAMETRES DE REGULATION O2												*/
/*----------------------------------------------------------------------*/
#define 	cVEN_KPV_VALVE_O2_INSP 		10000			
#define 	cVEN_KIV_VALVE_O2_INSP 		1000
#define 	cVEN_INTEGRAL_VALVEO2_MAX	26700 	
#define 	cVEN_INTEGRAL_VALVEO2_MIN 	0 		
#define 	cADJUST_FIO2 					21
	
/* integral constant for setup mode	 */
#define cVEN_KPVO2_MAINT_FLOW_O2 2000
/* proportional constant for setup mode	 */
#define cVEN_KIVO2_MAINT_FLOW_O2 200

/* O2 valve command (open)	 */
#define cVALVEO2_CMD_ON 0	

/* FAS valve parameters corrections */
#define cREF_VALVE_COMMAND_COEFF			252
#define cTEMP_CORRECTION_FACTOR_OFFSET		280

#endif

