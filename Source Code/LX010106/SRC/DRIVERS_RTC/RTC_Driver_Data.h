/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : RTC_Driver_Data.h                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                    Global variables of "RTC DRIVER"                    */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*                                                                            */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/
#define cDRV_RTC_TIME_OUT_10MS 10

#ifdef DECLARATION_RTC_DRIVER_DATA

	#ifndef RTC_DRIVER_DATA_H
	#define RTC_DRIVER_DATA_H

/************************************************************************/
/*                        VARIABLE DECLARATION		                		*/
/************************************************************************/
UBYTE RTC_FIFO_IdxPush= 0; 	// Pointeur d'écriture dans le buffer RTC
UBYTE RTC_FIFO_IdxPull= 0; 	// Pointeur de lecture dans le buffer
UBYTE RTC_FIFO_NbDataInFifo=0;// Nombre de data dans le buffer  

/*%C Last good RTC value		*/
t_RTC_TIME_DATE RTC_Value;

/*%C Temporary RTC value		*/
t_RTC_TIME_DATE RTC_TempValue;

/*%C Write RTC value					  */
t_RTC_TIME_DATE RTC_WriteValue;

/*%C RTC	acces buffer		  */
t_RTC_ACCESS_CONTROL RTC_FIFO_AccessDriver[SIZE_OF_FIFO_RTC_ACCESS];

/*%C Current data of buffer to treat		*/
t_RTC_ACCESS_CONTROL DRV_RTC_CurrentDataPull;

/*%C RTC driver State						*/
e_DRV_RTC_ERROR DRV_RTC_Status;
	#endif
#else
	#ifndef RTC_DRIVER_DATA_H
	#define RTC_DRIVER_DATA_H


/************************************************************************/
/*                        VARIABLE DECLARATION		                		*/
/************************************************************************/
extern UBYTE RTC_FIFO_IdxPush; 	// Pointeur d'écriture dans le buffer RTC
extern UBYTE RTC_FIFO_IdxPull; 	// Pointeur de lecture dans le buffer
extern UBYTE RTC_FIFO_NbDataInFifo;// Nombre de data dans le buffer  

/*%C Last good RTC value		*/
extern t_RTC_TIME_DATE RTC_Value;

/*%C Temporary RTC value		*/
extern t_RTC_TIME_DATE RTC_TempValue;

/*%C Write RTC value					  */
extern t_RTC_TIME_DATE RTC_WriteValue;

/*%C RTC	acces buffer		  */
extern t_RTC_ACCESS_CONTROL RTC_FIFO_AccessDriver[SIZE_OF_FIFO_RTC_ACCESS];

/*%C Current data of buffer to treat		*/
extern t_RTC_ACCESS_CONTROL DRV_RTC_CurrentDataPull;

/*%C RTC driver State						*/
extern e_DRV_RTC_ERROR DRV_RTC_Status;
	#endif
#endif
