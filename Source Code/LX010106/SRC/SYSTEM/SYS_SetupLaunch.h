/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_SetupLaunch.h      		                         	         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Management of all the detections, of the backlight,            */
/*%C           of the counters, bip mngt, etc.                                */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


#ifndef SYS_SETUP_LAUNCH_H
#define SYS_SETUP_LAUNCH_H
/******************************************************************************/
/*                       EXTERNAL FUNCTION DECLARATION                        */
/******************************************************************************/


extern void SYS_Keyboard(void);
extern void SYS_Backlight_Mngt(void);
extern void DRV_Key_Sound_Bip(void);
extern void SET_ResetCounters(void);
extern void SYS_Fio2Detection(void);
#endif