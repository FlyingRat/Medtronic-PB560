/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_USB_Transmit_Trend.c                         					*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                     																		*/
/*                                                                            */
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

#include "typedef.h"
#include "enum.h"
#include "DB_RTC.h"
#include "DB_Control.h"
#include "DB_Compute.h"
#include "DB_Current.h"
#include "CRC16_Table.h"
#include "Driver_USB_Data.h"
#include "DRV_USB_Transmit_Trend.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_USB_Transmit_Trend(void)
{


/******************************************************************************/
/*%C Variables */	
/******************************************************************************/
	
	UWORD16 Compteur = 0 ;
	UWORD16 Compute_CRC = 0 ;

   	UWORD16 VentilMode 		= (UBYTE)DB_ControlRead(CURRENT_MODE_U16);
	UWORD16 Trigger_Insp_Var 	= DB_CurrentRead(INSP_SENS_NO_SELECT_U16) ;
	UWORD16 Backup_R_Var 	= DB_CurrentRead(BACKUP_R_NO_SELECT_U16) ;

/******************************************************************************/
/*%C Read data to prepare the frame */
/******************************************************************************/

	/*%C Trends Identifiant */
  	DataTrends [USB_ID_FRAME] = USB_TREND_IDENTIFIANT;
	
	/*%C Write Dante and time Tendances */
	DataTrends [USB_DATA + TREND_DAY] 
							= (UBYTE)DB_RTCRead(DB_RTC_DAY_U16) ;	
	DataTrends [USB_DATA + TREND_MONTH]
							= (UBYTE)DB_RTCRead(DB_RTC_MONTH_U16) ;
	DataTrends [USB_DATA + TREND_YEAR]
							= (UBYTE)DB_RTCRead(DB_RTC_YEAR_U16) ;
	DataTrends [USB_DATA + TREND_HOUR]
							= (UBYTE)DB_RTCRead(DB_RTC_HOUR_U16) ;
	DataTrends [USB_DATA + TREND_MINUTE]
							= (UBYTE)DB_RTCRead(DB_RTC_MINUTE_U16) ;
	DataTrends [USB_DATA + TREND_SECOND]
							= (UBYTE)DB_RTCRead(DB_RTC_SECOND_U16) ;

	/*%C Write Paramteters */
  	switch (VentilMode)
	{
		case VOL :
		{
			if (Trigger_Insp_Var == FALSE)
			{
				DataTrends[USB_DATA + TREND_VENTIL_MODE] = COM_VOL_A ;
			}
			else if (Trigger_Insp_Var == TRUE)
			{
				DataTrends[USB_DATA + TREND_VENTIL_MODE] = COM_VOL_C; 
			}
			else
			{
				/*%C No Function */
			}
			break;
		}
				
		case PRES :
		{
			if (Trigger_Insp_Var == FALSE)
			{
				DataTrends[USB_DATA + TREND_VENTIL_MODE] = COM_PRES_A;
			}
			else if (Trigger_Insp_Var == TRUE)
			{
				DataTrends[USB_DATA + TREND_VENTIL_MODE] = COM_PRES_C; 
			}
			else
			{
				/*%C No Function */
			}
			break;
		}
			
		case PSVT :
		{
			if (Backup_R_Var == FALSE) 
			{
				DataTrends[USB_DATA + TREND_VENTIL_MODE] = COM_PSVT;
			}
			else if(Backup_R_Var == TRUE) 
			{
				DataTrends[USB_DATA + TREND_VENTIL_MODE] = COM_PSV; 
			}
			else
			{
				/*%C No Function */
			}
			break;
		}
					
		case VSIMV :
		{
				DataTrends[USB_DATA + TREND_VENTIL_MODE] = COM_VSIMV;
			break;
		}

		case PSIMV :
		{
				DataTrends[USB_DATA + TREND_VENTIL_MODE] = COM_PSIMV;
			break;
		}
		
		case CPAP :
		{
				DataTrends[USB_DATA + TREND_VENTIL_MODE] = COM_CPAP;
			break;
		}
		
		default :
		{
			/*%C No Function */
			break;
		}
	} 

	DataTrends [USB_DATA + TREND_VENTIL_TYPE]
							= (UBYTE)DB_ControlRead(VENTIL_STATE_U16) ;


	DataTrends [USB_DATA + TREND_MSB_P_MAX]
							= (UBYTE)(DB_ComputeRead(COMPUTED_PIP_U16) >> 8) ;
	DataTrends [USB_DATA + TREND_LSB_P_MAX]
							= (UBYTE)DB_ComputeRead(COMPUTED_PIP_U16) ;

	DataTrends [USB_DATA + TREND_MSB_AV_PEP]
							= (UBYTE)(DB_ComputeRead(COMPUTED_PEEP_U16) >> 8) ;
	DataTrends [USB_DATA + TREND_LSB_AV_PEP]
							= (UBYTE)DB_ComputeRead(COMPUTED_PEEP_U16) ;

	DataTrends [USB_DATA + TREND_MSB_LEAKAGE]
							= (UBYTE)(DB_ComputeRead(COMPUTED_LEAK_U16) >> 8) ;
	DataTrends [USB_DATA + TREND_LSB_LEAKAGE]
							= (UBYTE)DB_ComputeRead(COMPUTED_LEAK_U16) ;

	DataTrends [USB_DATA + TREND_MSB_AV_VOLUME]
							= (UBYTE)(DB_ComputeRead(COMPUTED_VMI_U16) >> 8) ;
	DataTrends [USB_DATA + TREND_LSB_AV_VOLUME]
							= (UBYTE)DB_ComputeRead(COMPUTED_VMI_U16) ;

	DataTrends [USB_DATA + TREND_IE_RATIO_NUMERATOR]
							= (UBYTE)DB_ComputeRead(MEASURE_IE_NUMERATOR_U16) ;
	DataTrends [USB_DATA + TREND_IE_RATIO_DENOMINATOR]
							= (UBYTE)DB_ComputeRead(MEASURE_IE_DENOMINATOR_U16) ;

	DataTrends [USB_DATA + TREND_FREQUENCY]
		  					= (UBYTE)DB_ComputeRead(MEASURE_R_U16) ;

	DataTrends [USB_DATA + TREND_MSB_INSPIRATED_VOLUME]
		  					= (UBYTE)(DB_ComputeRead(COMPUTED_VTI_U16) >> 8) ;
	DataTrends [USB_DATA + TREND_LSB_INSPIRATED_VOLUME]
		  					= (UBYTE)DB_ComputeRead(COMPUTED_VTI_U16) ;

	DataTrends [USB_DATA + TREND_MSB_EXHALED_VOLUME]
		  					= (UBYTE)(DB_ComputeRead(COMPUTED_VTE_U16) >> 8) ;
	DataTrends [USB_DATA + TREND_LSB_EXHALED_VOLUME]
		  					= (UBYTE)DB_ComputeRead(COMPUTED_VTE_U16) ;

	DataTrends [USB_DATA + TREND_HEART_RATE]
		  					= (UBYTE)DB_ComputeRead(COMPUTED_PULSE_U16) ;

	DataTrends [USB_DATA + TREND_SPO2]
		  					= (UBYTE)DB_ComputeRead(MEASURE_SPO2_U16) ;

}