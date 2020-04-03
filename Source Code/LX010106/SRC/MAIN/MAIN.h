/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : MAIN.h                                                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C          It is the entry point, the "main", of the software :            */
/*%C          It initializes the processor target (registers and variables)   */
/*%C          and launch the scheduler.                                       */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef MAIN_H
#define MAIN_H

extern void MAIN_Target_Init(void);
extern void	MAIN_Global_Variables_Init(void);
extern void	MAIN_Interfaces_Init(void);
extern void MAIN_Leds_Backlight_Buzzers_StartControl(void);
extern void DRV_RS232_Init(void);
extern void MAIN_Tasks_Init(void);
extern void TIM_Temporize(UWORD32 useconde);
extern void MAIN_Airox_Symbol_Display(void);

extern void SCHED_Setup_Main(void);
extern void SCHED_Ventilation_Main(void);
extern void MAIN_Version_Error_Mngt(void);

extern void VENTILATION_HMI_Start(void);
extern void SETUP_HMI_Start(void);
extern void CIRCUIT_CHECK_HMI_Start(void);
extern void DB_EventMngt (UWORD16 Value);
extern void EEP_FIFO_PushOneData(	UWORD16 xhuge *ptr_DataRam,
												e_EEP_ACCESS_STATE access_type);

extern void DB_ControlWrite(e_DB_CONTROL Id, UWORD16 Value);
extern void DRV_NAND_ReadID(void);

extern void MAIN_NAND_Flash_Bad_Block_Detection(void);
extern void MAIN_NAND_Flash_Bad_Block_Read(void);

extern UWORD16 KEY_Touch_Detection(e_SYS_KeyboardInput Touch);

#endif
