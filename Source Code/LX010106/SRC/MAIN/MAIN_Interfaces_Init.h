/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : MAIN_Interfaces_Init.c                                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C       It launches the interfaces initialisations.                        */
/*%C       It is done in to phases, and it is important to respect the        */
/*%C			call order.													  */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              */
/*%O Output Parameter : NONE                                                  */
/*					 
/******************************************************************************/
#ifndef MAIN_INTERFACES_INIT_H
#define MAIN_INTERFACES_INIT_H




extern void DRV_LedInit(void);
extern void DRV_RTC_Init(void);
extern void DRV_EEP_Init(void);
extern UWORD16 DRV_EEP_ReadWord(UWORD16);
extern void InitInterruptT6 (void);
extern void DB_StartInitDb(void);
extern void DRV_BuzInit(void);
extern void DRV_RS232_Init(void);
extern void DRV_ADC_ConvertInit (void);
extern void DRV_EEP_tempo_CE(void);
extern void DRV_EEP_WaitEndTransmit(void);
extern void DRV_OutputPort(e_OUTPUT_NAME _Port, UWORD16 _Value);


extern void DRV_SPIPowerSupplyUpdate(void); 
extern void TIM_Temporize(UWORD32 useconde);
extern void It_watchdog(void);

extern UWORD16 CRC16_TableCompute(	UWORD16 StartIndex,
									UWORD16 StopIndex,
									UBYTE* TransmitArray, 
									UWORD16 Compute_CRC);

#endif