/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505							*/
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_Buz.h                                      			*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   API du driver de Buzzer						     */
/*%C 									      */
/*	                                                                       */
/******************************************************************************/

#include "typedef.h"
#include "enum.h"

#ifndef DRV_BUZ_H
#define DRV_BUZ_H

extern void DRV_Buz_Sound(e_TYPE_SOUND sound, e_NUMBER_BUZ NumBuzzer);

extern void DRV_Buz_Test(e_NUMBER_BUZ NbBuzzer, e_TYPE_TEST_BUZ Mode);

extern void DRV_Backlight(e_BOOL Actif);

#endif


