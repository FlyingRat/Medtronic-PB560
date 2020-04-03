/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_COM_Transmit_Machine_Counter.h  									  */
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


#ifndef DRV_COM_TRANSMIT_MACHINE_COUNTER_H
#define DRV_COM_TRANSMIT_MACHINE_COUNTER_H

/******************************************************************************/
/*                     EXTERNAL FUNCTION DECLARATION                          */
/******************************************************************************/


#ifndef _TASKING
UBYTE sdata Array_Machine_Counter[End_Of_Table_Com_Machine_Counter + End_Of_Table_Com_TX_Remote - 1]; 
/* Tasking  */
#else
UBYTE near Array_Machine_Counter[End_Of_Table_Com_Machine_Counter + End_Of_Table_Com_TX_Remote - 1]; 
#endif


UWORD16 DB_ControlRead(e_DB_CONTROL Id);
extern UWORD16 CRC16_TableCompute(	UWORD16 StartIndex,
										UWORD16 StopIndex,
										UBYTE* TransmitArray,
										UWORD16 Compute_CRC);
#endif
