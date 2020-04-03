/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SET_TechnicalAlarms.h  														*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C Data declaration for SET_TechnicalAlarms.c		     								*/
/******************************************************************************/
/*%I Input Parameter :  NONE                     										*/
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE																	*/
/******************************************************************************/

#ifndef SET_TECHNICAL_ALARMS_H	
#define SET_TECHNICAL_ALARMS_H

/************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION	                     */
/************************************************************************/
extern void SET_InspFlowOffsetDefault(void);
extern void SET_InternalPressureOffsetDefault(void);
extern void SET_ProximalPressureOffsetDefault(void);
extern void SET_ValvePressureOffsetDefault(void);
extern void SEC_ExhFlowOffsetDefault(void);
extern void	SEC_LooseFlashPointer(void);
extern e_ALARM_ERROR SEC_TurbineOverheat(void);

#ifdef CONFIG_ALARM_O2
extern void SET_O2FlowOffsetDefault(void);
extern void SET_O2PressureOffsetDefault(void);
#endif

#endif
