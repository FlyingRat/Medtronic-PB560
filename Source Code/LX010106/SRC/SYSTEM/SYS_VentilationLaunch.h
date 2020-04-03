/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_VentilationLaunch.h                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C      			Data declaration for SYS_VentilationLaunch.c            		*/
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


#ifndef SYS_VENTILATION_LAUNCH_H
#define SYS_VENTILATION_LAUNCH_H
/******************************************************************************/
/*                       EXTERNAL FUNCTION DECLARATION                        */
/******************************************************************************/


extern void SYS_Alarm_Remote_Detect(void);
extern void SYS_PressionChoice(void);
extern void SYS_Keyboard(void);
extern void SYS_Backlight_Mngt(void);
extern void SYS_RTC_Update(void);
extern void SYS_Counters(void);
extern void SYS_CalibrationManagement(void);
extern void DRV_Key_Sound_Bip(void);
extern void SYS_SPO2Interpol(void);
extern void SYS_Monit_Buffer_Write(void);
extern void SYS_Trend_Buffer_Write(void);
extern void SYS_Fio2Detection(void);


#endif