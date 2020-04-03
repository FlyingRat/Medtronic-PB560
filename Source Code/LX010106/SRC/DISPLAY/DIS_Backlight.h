/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DIS_BackLight.h 														*/
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

#ifndef DIS_BACKLIGHT_H
#define DIS_BACKLIGHT_H

extern void DIS_FifoWrite(UWORD16 DisplayFunction,
								  UWORD16 Param1,
								  UWORD16 Param2,
								  UWORD16 Param3,
								  UWORD16 Param4,
								  UWORD16 Param5,
								  UWORD16 Param6,
								  UWORD16 Param7,
								  UWORD16 Param8,
								  UWORD16 Param9,
								  UWORD16 Param10,
								  UWORD16 Param11,
								  UWORD16 Param12);
#endif