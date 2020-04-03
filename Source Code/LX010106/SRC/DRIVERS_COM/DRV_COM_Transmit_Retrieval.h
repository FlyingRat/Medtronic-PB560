/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_COM_Transmit_Retrieval.h  									  */
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


#ifndef DRV_COM_TRANSMIT_RETRIEVAL_H
#define DRV_COM_TRANSMIT_RETRIEVAL_H

/******************************************************************************/
/*                     EXTERNAL FUNCTION DECLARATION                          */
/******************************************************************************/


/* Keil  */
#ifndef _TASKING
UBYTE sdata Array_Event[EVENT_Last_Event_Parameter + End_Of_Table_Com_TX_Remote - 1];
/* Tasking  */
#else
UBYTE near Array_Event[EVENT_Last_Event_Parameter + End_Of_Table_Com_TX_Remote - 1];
#endif



extern UBYTE DRV_EVENT_Read_Event(UWORD16 num_event
											,e_EVENT_PARAMETERS id_event
											,UWORD16 xhuge *Ptr_retrieval);
extern UWORD16 CRC16_TableCompute(	UWORD16 StartIndex,
										UWORD16 StopIndex,
										UBYTE* TransmitArray,
										UWORD16 Compute_CRC);

#endif
