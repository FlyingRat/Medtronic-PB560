/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_COM_Launch.h  									  */
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


#ifndef DRV_COM_LAUNCH_H
#define DRV_COM_LAUNCH_H

/******************************************************************************/
/*                     EXTERNAL FUNCTION DECLARATION                          */
/******************************************************************************/
extern void DRV_COM_Read_Buffer(void);
extern UWORD16 DB_UsbRead(e_DB_USB Id);
extern void DRV_COM_Transmit_Retrieval(void);
extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);
extern void DRV_COM_Transmit_Monitoring(void);
extern void DRV_COM_Transmit_Trend(void);
extern void DRV_COM_Transmit_Detailled(void);
extern void DRV_COM_Transmit_ID(void);
extern void DRV_COM_Transmit_Machine_Counter(void);
extern void DRV_COM_Transmit_Database(void);
extern void DRV_COM_Receive_ID(void);
extern void DRV_COM_Receive_Database(void);
extern void DRV_COM_Receive_Machine_Counter(void);
extern void DRV_COM_Ready(void);
extern void DRV_COM_Read_Eeprom(void);
extern void DRV_COM_Transmit_Settings(void);
extern void DRV_COM_Transmit_Monitoring_To_Key(void);

#endif
