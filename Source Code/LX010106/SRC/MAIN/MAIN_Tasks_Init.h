/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : MAIN_Tasks_Init.h                                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C        It is the initializations of the main tasks :                     */
/*%C				- System																  */
/*%C				- Security															  */
/*%C				- Ventilation														  */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef MAIN_TASKS_INIT_H
#define MAIN_TASKS_INIT_H

extern void DRV_EVENT_Init(void);
extern void	DRV_NAND_Flash_Init(void);
extern void MAIN_System_Init(void);
extern void MAIN_Ventilation_Init (void);
extern void MAIN_Security_Init(void);
#endif