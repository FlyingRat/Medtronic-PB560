/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : MAIN_activate_tasks.h                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C          ****************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef MAIN_ACTIVATE_TASKS_H
#define MAIN_ACTIVATE_TASKS_H

#define NB_1MS_BY_SCHEDULER_STEP 5

extern void DRV_EEP_Launch(void);
extern void DRV_RTC_Launch(void);
extern void DRV_SPI_POWER_Launch(void);
#endif
