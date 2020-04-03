/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_USB_Transmit_Monitoring.c                         			*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                     																		*/
/*%C																									*/
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/



/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/

#include "enum.h" 
#include "define.h" 
#include "typedef.h" 
#include "Structure.h" 
#include "Ventilation_Datas.h" 
#include "Ventilation_Compute_data.h" 
#include "DB_Control.h" 
#include "Timer_Data.h" 
#include "DB_Usb.h" 
#include "Driver_USB_Data.h" 
#include "DRV_USB_WriteInContinuousRecordBuffer.h"

extern void DB_UsbWrite(e_DB_USB Id, UWORD16 Value);
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_USB_WriteInContinuousRecordBuffer(void)
{
	UWORD16 idx = 0 ;
	e_VentilState UsbVentilState = DB_ControlRead(VENTIL_STATE_U16); 

	/*%C Recording Trends when ventilation */
	if 	((VEN_Controller_Phase == VEN_INSP_RISE)
		&& (VEN_Controller_Phase != CMP_PreviousControllerPhase)
		&& (UsbVentilState != VEN_VENTIL_DISABLE) )
	{
		/*%C Read Trends Datas */
		DRV_USB_Transmit_Trend();
		/*%C Write to the buffer */
		for (idx = 0 ; idx < (USB_End_Of_Continuous_Frame + End_Of_Table_Trends - 1) ; idx ++)  
		{
			DRV_USB_Continuous_Record_Buffer[DRV_USB_Idx_Write]=DataTrends[idx];
			DRV_USB_Idx_Write ++ ;
			DRV_USB_Idx_Write = (UWORD16)(DRV_USB_Idx_Write % DRV_USB_CONTINUOUS_RECORD_BUFFER_SIZE);
		}
	}
	
	/*%C Recording Monitoring when ventilation */
	else if (TIM_ReadDecounterValue(TIM_USB_RECORDING_MONIT) == 0)	
	{

		if ( ( (TIM_ReadMinuteDecounterValue(TimerUsbRecordingDetailledHorodatage) == 0)
		    && (UsbVentilState != VEN_VENTIL_DISABLE) )
		  || ( (UsbMemoVentilState == VEN_VENTIL_DISABLE)
			&& (UsbVentilState != VEN_VENTIL_DISABLE) )
		  || ( (UsbMemoVentilState != VEN_VENTIL_DISABLE)
		    && (UsbVentilState == VEN_VENTIL_DISABLE) ) )
		{

			/*%C Timer launch for next recording (15 minutes) */
            TIM_StartMinuteDecounter(TimerUsbRecordingDetailledHorodatage,
                               TIME_USB_RECORDING_DETAILLED_HORODATAGE,
                               FALSE);

			/*%C Read Monitoring Datas (Horodatage)*/
			DRV_USB_Transmit_Monitoring(DETAILLED_HORODATAGE_TYPE);

			/*%C Write to the buffer */
			for (idx = 0;idx<(USB_End_Of_Continuous_Frame + End_Of_Table_Detailled_Monitoring - 1);idx++)  
			{
				DRV_USB_Continuous_Record_Buffer[DRV_USB_Idx_Write]=DataMonitoring[idx];
				DRV_USB_Idx_Write ++ ;
				DRV_USB_Idx_Write = (UWORD16)(DRV_USB_Idx_Write % DRV_USB_CONTINUOUS_RECORD_BUFFER_SIZE);
			}
		}
		else if (UsbVentilState != VEN_VENTIL_DISABLE)
		{
 			/*%C Read Monitoring Datas */
			DRV_USB_Transmit_Monitoring(DETAILLED_MONITORING_TYPE);

			/*%C Write to the buffer */
			for (idx = 0;idx<(USB_End_Of_Continuous_Frame + End_Of_Table_Detailled_Monitoring - 1);idx++)  
			{
				DRV_USB_Continuous_Record_Buffer[DRV_USB_Idx_Write]=DataMonitoring[idx];
				DRV_USB_Idx_Write ++ ;
				DRV_USB_Idx_Write = (UWORD16)(DRV_USB_Idx_Write % DRV_USB_CONTINUOUS_RECORD_BUFFER_SIZE);
			}
		}

		/*%C Restart Decounter */
		TIM_StartDecounter(TIM_USB_RECORDING_MONIT
									,TIME_RECORDING_MONIT);

		/*%C Record the ventil state*/
		UsbMemoVentilState = UsbVentilState;

	}

	/*%C Recording Events */
	else if(PtrUsbNumEventsRead != PtrUsbNumEventsWrite)
	{
		DRV_USB_Transmit_Events(FALSE);
		/*%C Write to the buffer */
		for (idx = 0;idx<(USB_End_Of_Continuous_Frame + EVENT_Last_Event_Parameter - 1);idx++)  
		{
			DRV_USB_Continuous_Record_Buffer[DRV_USB_Idx_Write]=DataEvents[idx];
			DRV_USB_Idx_Write ++ ;
			DRV_USB_Idx_Write = (UWORD16)(DRV_USB_Idx_Write % DRV_USB_CONTINUOUS_RECORD_BUFFER_SIZE);
		}

	}
	/*%C No Records */
	else
	{
		/*%C no function */
	}



}