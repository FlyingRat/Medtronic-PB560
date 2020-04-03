/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_Monit_Buffer_Write.c                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


#ifndef SYS_MONIT_BUFFER_WRITE_H
#define SYS_MONIT_BUFFER_WRITE_H


/******************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION	                          */
/******************************************************************************/




/* Access to the control read value */
extern UWORD16 DB_RTCRead(e_DB_RTC Id);
extern UWORD16 DB_ComputeRead(e_DB_COMPUTE Id);
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
extern UWORD16 DB_CurrentRead(e_DB_ADJUST_CURRENT Id);

#endif