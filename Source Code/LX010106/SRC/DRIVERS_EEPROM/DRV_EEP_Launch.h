/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_EEP_Launch.h																*/
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
#define BEGIN_RAM_ADRESS_OF_EEP_DATA 0xFF000


#ifndef DRV_EEP_LAUNCH_H
#define DRV_EEP_LAUNCH_H

extern void DRV_EEP_WaitEndWrite(void);
extern BIT EEP_FIFO_FreeFirstData(void);
extern UBYTE EEP_FIFO_ReadNbDataStored(void);
extern t_EEP_ACCESS_CONTROL EEP_FIFO_PullFirstData(void);
extern UWORD16 DRV_EEP_ReadWord(UWORD16);
extern void DRV_EEP_StartWriteWord(UWORD16 donnee, UWORD16 adresse);

#endif