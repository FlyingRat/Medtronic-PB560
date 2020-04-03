/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_CheckPageAndRetransmitAddress.h                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C  Data declaration for DRV_CheckPageAndRetransmitAddress.c	               */
/*                                                                            */
/******************************************************************************/
/*%I  Input Parameter :   NONE                                                */
/*%IO Input/Output :      NONE                                                */
/*%O  Output Parameter :  NONE                                                */
/******************************************************************************/

#ifndef DRV_CHECK_PAGE_AND_RETRANSMIT_ADDRESS_H
#define DRV_CHECK_PAGE_AND_RETRANSMIT_ADDRESS_H

/************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION	                     */
/************************************************************************/
extern void DRV_EEP_WaitEndTransmit(void);
extern void DRV_EEP_tempo_CE(void);
extern void DRV_OutputPort(e_OUTPUT_NAME _Port, UWORD16 _Value);
 
#endif

