/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_SPI_POWER_Launch.h */
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


#ifndef DRV_SPI_POWER_LAUNCH_H
#define DRV_SPI_POWER_LAUNCH_H

/******************************************************************************/
/*                     EXTERNAL FUNCTION DECLARATION                          */
/******************************************************************************/

extern void DRV_OutputPort(e_OUTPUT_NAME _Port, UWORD16 _Value);
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
extern void DRV_SPI_POWER_WaitEndTransmit(void);

#endif