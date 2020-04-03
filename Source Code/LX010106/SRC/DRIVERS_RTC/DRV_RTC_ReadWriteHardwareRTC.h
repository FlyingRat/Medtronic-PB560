/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_RTC_ReadWriteHardwareRTC.h */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                  */
/******************************************************************************/
/*%I Input Parameter :  NONE                                            */
/*%IO Input/Output :    NONE	                                              */
/*%O Output Parameter : NONE       */
/******************************************************************************/


#ifndef DRV_RTC_READWRITEHARDWARERTC_H
#define DRV_RTC_READWRITEHARDWARERTC_H

/******************************************************************************/
/*                     EXTERNAL FUNCTION DECLARATION                          */
/******************************************************************************/
extern UBYTE DRV_RTC_FIFO_ReadNbDataStored(void);
extern t_RTC_ACCESS_CONTROL DRV_RTC_FIFO_PullFirstData(void);
extern void DRV_RTC_control (UBYTE data_control);
extern void DRV_RTC_WaitEndTransmit(void);
extern BIT DRV_RTC_FIFO_FreeFirstData(void);
extern void DRV_OutputPort(e_OUTPUT_NAME _Port, UWORD16 _Value);

#endif