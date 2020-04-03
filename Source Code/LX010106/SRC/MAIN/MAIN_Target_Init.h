/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : MAIN_Target_Init.h                                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C The function of target initialization is launched :                      */
/*%C  - allowing the use of the emulator          */
/*%C  - Watchdog setup            */
/*%C  - service the watchdog */
/*%C  - Input/Output port setup     */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef MAIN_TARGET_INIT_H
#define MAIN_TARGET_INIT_H

extern void DRV_OutputPort(e_OUTPUT_NAME _Port, UWORD16 _Value);

#endif