/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_COM_Transmit_Database.h  									  */
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


#ifndef DRV_COM_TRANSMIT_DATABASE_H 
#define DRV_COM_TRANSMIT_DATABASE_H

/******************************************************************************/
/*                     EXTERNAL FUNCTION DECLARATION                          */
/******************************************************************************/
	/* Keil  */
#ifndef _TASKING
UBYTE sdata Array_Read_Database[End_Of_Table_Com_TX_Remote - 2 + COM_NB_MAX_PARAMETER_DATABASE]; 
	/* Tasking  */
#else
UBYTE near Array_Read_Database[End_Of_Table_Com_TX_Remote - 2 + COM_NB_MAX_PARAMETER_DATABASE]; 
#endif


extern UWORD16 DB_IhmAccessParaDataBase(UWORD16 *Value,
										UWORD16 Id,
										e_TYPE_OF_DB_TARGET DbType,
										e_DATA_OPERATION DataOperation);
extern UWORD16 CRC16_TableCompute(	UWORD16 StartIndex,
										UWORD16 StopIndex,
										UBYTE* TransmitArray,
										UWORD16 Compute_CRC);
#endif