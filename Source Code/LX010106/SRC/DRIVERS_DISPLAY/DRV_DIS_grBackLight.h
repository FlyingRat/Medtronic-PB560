/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_DIS_grBackLight.h 														*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                  																			*/
/******************************************************************************/
/*%I Input Parameter :  BackLight Level Intensity                             */
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE       															*/
/******************************************************************************/

#ifndef DRV_DIS_GRBACKLIGHT_H
#define DRV_DIS_GRBACKLIGHT_H

#define BACKLIGHT_OFF		115
#define BACKLIGHT_WEAK		105
#define BACKLIGHT_ON			85

extern void DRV_DIS_grWriteDisplay ( UBYTE dat );
#endif