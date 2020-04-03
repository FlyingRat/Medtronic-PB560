/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505							*/
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_Leds.h                                      			*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   API du driver de leds                                                  */
/*%C 									      */
/*	                                                                       */
/******************************************************************************/

#include "typedef.h"
#include "enum.h"

#ifndef DRV_LED_H
#define DRV_LED_H


extern void DRV_LedInit(void);

extern void DRV_Backlight(e_BOOL Actif);

extern void DRV_Led_Orange(e_TYPE_BLINK Blink);

extern void DRV_Led_Red(e_TYPE_BLINK Blink);

extern void DRV_Led_Ventil(e_BOOL On);

extern void DRV_Led_White(e_TYPE_BLINK Blink);

extern void DRV_Led_Ac(e_TYPE_BLINK Blink);

extern void DRV_Led_Dc(e_TYPE_BLINK Blink);

extern void DRV_Led_Bat(e_TYPE_BLINK Blink);

#endif


