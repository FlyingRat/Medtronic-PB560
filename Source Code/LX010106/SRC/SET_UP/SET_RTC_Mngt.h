/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SET_RTC_Mngt.h												  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C             			RTC management                  				  */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef SET_RTC_MNGT_H
#define SET_RTC_MNGT_H

/************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION	                     */
/************************************************************************/
extern void DB_RTCWrite(e_DB_RTC Id,
                        UWORD16 Value);
extern UWORD16 DB_RTCRead(e_DB_RTC Id);
extern void DRV_RTC_WriteTimeAndDate(t_RTC_TIME_DATE);
extern t_RTC_TIME_DATE DRV_RTC_ReadTimeAndDate(void);
extern void DB_EventMngt (UWORD16 Value);



#endif