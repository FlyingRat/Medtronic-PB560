/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_NmiTrap.h                                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C  Data declaration for SEC_NmiTrap.c				                           */
/*                                                                            */
/******************************************************************************/
/*%I  Input Parameter :   NONE                                                */
/*%IO Input/Output :      NONE                                                */
/*%O  Output Parameter :  NONE                                                */
/******************************************************************************/

#ifndef SEC_NMI_TRAP_H
#define SEC_NMI_TRAP_H

/************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION	                     */
/************************************************************************/
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);
extern void DRV_EEP_WaitEndTransmit(void);
extern void DRV_EEP_tempo_CE(void);
extern void	CheckPageAndRetransmitAddress(UWORD16 Address);
extern void DRV_ResetOnReturnSupply(void);
extern e_DRV_EVENT_STATE DRV_EVENT_TransStateFlash(void);
extern UWORD16 xhuge * DRV_EVENT_TransPtrMemory(void);
extern UWORD16 DRV_EVENT_TransfIdent(void);
extern UBYTE DRV_EVENT_Program_Flash(UWORD16 data_prog,UWORD16 xhuge *adr_prog);
extern UWORD16 xhuge * DRV_EVENT_TransAdressErase(void);
extern void	DRV_CheckPageAndRetransmitAddress(UWORD16 Address);
extern void DRV_DIS_HostRequest ( bit etat );
extern void DRV_DIS_grBackLight ( UWORD16 _Level );
extern void DRV_OutputPort(e_OUTPUT_NAME _Port, UWORD16 _Value);
extern void DRV_NAND_CommandInput(UBYTE Flash_Command);
extern UWORD16 CRC16_TableCompute(	UWORD16 StartIndex,
										UWORD16 StopIndex,
										UBYTE* TransmitArray,
										UWORD16 Compute_CRC);

#endif

