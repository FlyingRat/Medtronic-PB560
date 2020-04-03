/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_COM_Transmit_Monitoring.h  									  */
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


#ifndef DRV_COM_TRANSMIT_MONITORING_H
#define DRV_COM_TRANSMIT_MONITORING_H

/******************************************************************************/
/*                     EXTERNAL FUNCTION DECLARATION                          */
/******************************************************************************/
/*%C Transmit direct monitoring data storage */
	/* Keil  */
#ifndef _TASKING
UBYTE sdata Array_Direct_Monit[End_Of_Table_Direct_Monitoring + End_Of_Table_Com_TX_Remote - 1];
	/* Tasking  */
#else
UBYTE near Array_Direct_Monit[End_Of_Table_Direct_Monitoring + End_Of_Table_Com_TX_Remote - 1];
#endif




extern UWORD16 DB_ComputeRead(e_DB_COMPUTE Id);
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
extern UWORD16 DB_CurrentRead(e_DB_ADJUST_CURRENT Id);

extern UWORD16 DB_AlarmStatusRead(e_DB_ALARMS Id);
extern UWORD16 DRV_COM_Compute_CRC(void);
extern void TIM_StartDecounter(e_TIM_TABLE_ID offset_table,
                               UWORD16 Value);
extern UWORD16 TIM_ReadDecounterValue(e_TIM_TABLE_ID offset_table);
extern UWORD16 CRC16_TableCompute(	UWORD16 StartIndex,
										UWORD16 StopIndex,
										UBYTE* TransmitArray,
										UWORD16 Compute_CRC);
#endif
