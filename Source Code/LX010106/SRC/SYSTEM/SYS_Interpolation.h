/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_Interpolation.h                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C        Management of the interpolations after acuirements are done.      */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef SYS_INTERPOLATION_H
#define SYS_INTERPOLATION_H


/******************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION	                          */
/******************************************************************************/
extern void INT_ExhFlow_Interpol(void);
extern void INT_InspFlow_Interpol(void);
extern void INT_PatPress_Interpol(void);
extern void INT_ProxiPress_Interpol(void);
extern void INT_ValvePress_Interpol(void);
extern void INT_Voltages_Interpol(void);
extern void DRV_ADC_ChannelConvert(void);
extern void INT_SpeedBlow_Interpol(void);
extern void INT_BlowerTemperatureInterpol(void);
extern void SYS_CurveFlowCalcul(void);
extern void INT_AbsPress_Interpol(void);
extern void INT_Fio2_Interpol(void);
extern void INT_O2Flow_Interpol(void);
extern void INT_O2Press_Interpol(void);
extern void DB_ControlWrite(e_DB_CONTROL Id
							,UWORD16 Value);
extern void SYS_SupplyDetect(void);

#endif