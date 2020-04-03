/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SET_TechnicalAlarms.c  														*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C It schedules the technical alarms					     								*/
/******************************************************************************/
/*%I Input Parameter :  NONE                     										*/
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE																	*/
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/
#include "io_declare.h"
#include "typedef.h"
#include "enum.h"
#include "SET_TechnicalAlarms.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void SET_TechnicalAlarms(void)
{

/*%C Inspirated flow offset default alarm call	                           	*/
	SET_InspFlowOffsetDefault();

/*%C Internal pressure offset default alarm call	                          	*/
	SET_InternalPressureOffsetDefault();

/*%C Proximal pressure offset default alarm call	                          	*/
	SET_ProximalPressureOffsetDefault();

/*%C Valve pressure offset default alarm call	                          		*/
	SET_ValvePressureOffsetDefault();

/*%C Turbine overheat alarm call	                           	*/
	SEC_TurbineOverheat();

#ifdef CONFIG_VTE
/*%C Exhalated flow offset default alarm call	                           	*/
	SEC_ExhFlowOffsetDefault();
#endif

/*%C Flash Pointer ALARM 																		*/
	SEC_LooseFlashPointer();

#ifdef CONFIG_ALARM_O2
/*%C O2 flow offset default alarm call	                           	*/
	SET_O2FlowOffsetDefault();

/*%C O2 pressure offset default alarm call	                           	*/
	SET_O2PressureOffsetDefault();
#endif

}

