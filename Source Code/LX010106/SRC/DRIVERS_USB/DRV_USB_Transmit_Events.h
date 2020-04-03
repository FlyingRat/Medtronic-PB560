/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_USB_Transmit_Events.h  									  			*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                  																			*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                            		*/
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE       															*/
/******************************************************************************/


#ifndef DRV_USB_TRANSMIT_EVENTS_H
#define DRV_USB_TRANSMIT_EVENTS_H

/******************************************************************************/
/*                     EXTERNAL FUNCTION DECLARATION                          */
/******************************************************************************/


extern UBYTE DRV_EVENT_Read_Event(	UWORD16 num_event
												,e_EVENT_PARAMETERS id_event
												,UWORD16 xhuge *Ptr_retrieval);

extern UWORD16 CRC16_TableCompute(	UWORD16 StartIndex,
										UWORD16 StopIndex,
										UBYTE* TransmitArray,
										UWORD16 Compute_CRC);




#endif