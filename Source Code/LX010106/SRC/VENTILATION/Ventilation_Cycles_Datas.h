/******************************************************************************/
/*                                                                            */
/* Project N  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : Ventilation_Cycles_datas.h                                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Description fonctionnelle:		 	                        	      */
/*                                                                      	   */
/*%C Data declaration for ventilation cycles functions                        */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/
#ifndef VENTILATION_CYCLES_DATAS_H
#define VENTILATION_CYCLES_DATAS_H


/******************************************************************************/
/*                              	DEFINE							              */
/******************************************************************************/

#define cINIT_SIMV_DELAY 2000
#define cNB_TRIGGER_APNEA_OFF 3

/******************************************************************************/
/*                              STRUCTURE DECLARATION              */
/******************************************************************************/
typedef struct
	{
	e_ActiveModeState VolPres;
	e_ActiveModeState Psvt;
	e_ActiveModeState Psv;
	e_ActiveModeState Vsimv;
	e_ActiveModeState Psimv;
	e_ActiveModeState Cpap;
	} t_CYC_ActiveModeState;

typedef struct
	{
	UWORD16 TiMax;
	UWORD16 TiMin;
	}t_CYC_TiLimit;


#ifdef DECLARATION_CYCLES_DATAS

/******************************************************************************/
/*                           VARIABLE DECLARATION                    	      */
/******************************************************************************/

   
t_CYC_ActiveModeState CYC_ActiveModeState;
t_CYC_ActiveModeState CYC_NextModeState;
UWORD16 CYC_TiExpired = FALSE;
UWORD16 CYC_TeExpired = FALSE;
UWORD16 CYC_FirstInspirationActive = FALSE;

SWORD16 CYC_Qmax = 0;

e_VEN_Controller_Phase CYC_PreviousControllerPhase = VEN_EXH_PLAT;
UWORD16 RazSightCpt = TRUE;

#else


/******************************************************************************/
/*                       EXTERNAL VARIABLE DECLARATION                    	  */
/******************************************************************************/

extern t_CYC_ActiveModeState CYC_ActiveModeState;
extern t_CYC_ActiveModeState CYC_NextModeState;

extern UWORD16 CYC_TiExpired;
extern UWORD16 CYC_TeExpired;
extern UWORD16 CYC_FirstInspirationActive;

extern SWORD16 CYC_Qmax;

extern e_VEN_Controller_Phase CYC_PreviousControllerPhase;
extern UWORD16 RazSightCpt; 
 
#endif
#endif




