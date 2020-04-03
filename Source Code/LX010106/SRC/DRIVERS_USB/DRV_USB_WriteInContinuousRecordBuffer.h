/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505 				                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_USB_WriteInContinuousRecordBuffer.h 											*/
/*																										*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C         																						*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef DRV_USB_WRITEINCONTINUOUSRECORDBUFFER_H
#define DRV_USB_WRITEINCONTINUOUSRECORDBUFFER_H


/******************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION	                    			*/
/******************************************************************************/
	extern UWORD16 DB_ControlRead(e_DB_CONTROL Id); 
 
    /*%C Usb Read Continuous Frames */ 
    extern void DRV_USB_Transmit_Monitoring(UWORD16 DetailledDataType); 
	extern void DRV_USB_Transmit_Trend(void); 
    extern void DRV_USB_Transmit_Events(UBYTE EntireEventsMemoryTransfer); 
   
    /*%C Usb Timer Function */ 
    extern void TIM_StartDecounter(e_TIM_TABLE_ID,UWORD16); 
    extern UWORD16 TIM_ReadDecounterValue(e_TIM_TABLE_ID offset_table);  
    extern void TIM_StartMinuteDecounter(e_TIM_MINUTE_TABLE_ID offset_table,UWORD32 value,e_BOOL autoreload); 
    extern UWORD32 TIM_ReadMinuteDecounterValue(e_TIM_MINUTE_TABLE_ID offset_table); 


 #endif