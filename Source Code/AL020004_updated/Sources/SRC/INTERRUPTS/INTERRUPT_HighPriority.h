/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : INTERRUPT_HighPriority.h                                       */
/*													 						  							*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C          High priority interrupt management                             	*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef INTERRUPT_HIGHPRIORITY_H
#define INTERRUPT_HIGHPRIORITY_H

extern void MAIN_activate_tasks(void);
extern void CAN_Channel_Acquisition(void);
extern void DRV_RS232_InterruptReceive(void);
extern void DRV_RS232_InterruptTransmit(void);
extern void DRV_SPI_ST10_Interrupt(void);
extern void DRV_EEPROM_BAT_Interrupt(void);
extern void FAN_Acquisition(void);
extern void TIM_StartDecounter16(e_TIM_TABLE_ID_16 offset_table, UWORD16 value);
extern UWORD16 DB_Control_Read(e_DB_Control Id);
extern void DB_Control_Write(e_DB_Control Id, UWORD16 Value);
extern UWORD16 DB_PowerSupply_Read(e_DB_POWERSUPPLY Id);
extern void DB_PowerSupply_Write(e_DB_POWERSUPPLY Id, UWORD16 Value);

#endif
