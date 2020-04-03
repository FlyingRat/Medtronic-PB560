/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_Monit_Buffer_Write.c                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/



/******************************************************************************/
/*                               INCLUDE FILES                                */
/******************************************************************************/
#include "typedef.h"
#include "io_declare.h"
#include "enum.h"
#include "define.h"
#include "DB_Rtc.h"
#include "DB_Current.h"
#include "DB_Compute.h"
#include "DB_Control.h"
#include "DB_Config.h"
#include "SYS_Monit_Buffer_Write.h"
#include "Structure.h"
#include "Flash_Monit_Data.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void SYS_Monit_Buffer_Write(void)
{
static UBYTE First_Start = TRUE;
static UWORD32 Counter = 0;
static UWORD16 Monit_Idx_Frame = 0;
static UWORD16 Trend_Idx_Frame = 0;
static e_VentilState MemoVentilState = VEN_VENTIL_DISABLE;
static UBYTE Stop_Write_Date_Counter = 0;
e_VentilState VentilState = DB_ControlRead(VENTIL_STATE_U16);
UWORD16 ValveDetected = DB_ControlRead(VALVE_DETECTED_U16) ;
e_MODE_TYPES CurrentMode = PRES;
UWORD16	Trigger_Insp_Var = FALSE;
UWORD16 Backup_R_Var = FALSE;
e_MODE_COM Trend_Ventilation_Mode = COM_VOL_A;
UBYTE Previous_Idx_Write_Frame = 0;

/*%C the records start only if the ventilation is on */
if(VentilState != VEN_VENTIL_DISABLE)
{
Stop_Write_Date_Counter = 0;
/******************************************************************************/
/*%C					DETAILLED MONITORING STORAGE                          */

if (First_Start == TRUE)
{
	for(Monit_Idx_Frame = 0 
	   ;Monit_Idx_Frame < End_Of_Table_Detailled_Monitoring 
	   ;Monit_Idx_Frame++)
	{
		DRV_NAND_Monit_Buffer[0]
							 [Monit_Idx_Frame]
							 = 0xFF;
	}
	for(Monit_Idx_Frame = End_Of_Table_Detailled_Monitoring 
	   ;Monit_Idx_Frame < (2*End_Of_Table_Detailled_Monitoring) 
	   ;Monit_Idx_Frame++)
	{
		DRV_NAND_Monit_Buffer[0]
 							 [Monit_Idx_Frame]
							 = 0x00;
	}
	for(Monit_Idx_Frame = (2*End_Of_Table_Detailled_Monitoring) 
	   ;Monit_Idx_Frame < (3*End_Of_Table_Detailled_Monitoring) 
	   ;Monit_Idx_Frame++)
	{
		DRV_NAND_Monit_Buffer[0]
							 [Monit_Idx_Frame]
							 = 0x00;
	}

	DRV_NAND_Monit_Buffer[0]
						 [Monit_Idx_Frame]
						= 0x00;
	Monit_Idx_Frame = Monit_Idx_Frame + 1;
	DRV_NAND_Monit_Buffer[0]
						 [Monit_Idx_Frame]
						= 0x00;
	Monit_Idx_Frame = Monit_Idx_Frame + 1;
	DRV_NAND_Monit_Buffer[0]
						 [Monit_Idx_Frame]
						= (UBYTE)DB_RTCRead(DB_RTC_SECOND_U16);
	Monit_Idx_Frame = Monit_Idx_Frame + 1;
	DRV_NAND_Monit_Buffer[0]
						 [Monit_Idx_Frame]
						= (UBYTE)DB_RTCRead(DB_RTC_MINUTE_U16);
	Monit_Idx_Frame = Monit_Idx_Frame + 1;
	DRV_NAND_Monit_Buffer[0]
						 [Monit_Idx_Frame]
						= (UBYTE)DB_RTCRead(DB_RTC_HOUR_U16);
	Monit_Idx_Frame = Monit_Idx_Frame + 1;
	DRV_NAND_Monit_Buffer[0]
						 [Monit_Idx_Frame]
						= (UBYTE)DB_RTCRead(DB_RTC_YEAR_U16);
	Monit_Idx_Frame = Monit_Idx_Frame + 1;
	DRV_NAND_Monit_Buffer[0]
						 [Monit_Idx_Frame]
						= (UBYTE)DB_RTCRead(DB_RTC_MONTH_U16);
	Monit_Idx_Frame = Monit_Idx_Frame + 1;
	DRV_NAND_Monit_Buffer[0]
						 [Monit_Idx_Frame]
						= (UBYTE)DB_RTCRead(DB_RTC_DAY_U16);
	Monit_Idx_Frame = Monit_Idx_Frame + 1;
	DRV_NAND_Monit_Buffer[0]
						 [Monit_Idx_Frame]
						= (UBYTE)HORODATAGE;
   Monit_Idx_Frame = Monit_Idx_Frame + 1;

/******************************************************************************/
/*                      	TRENDS                                         */

	for(Trend_Idx_Frame = 0 
	   ;Trend_Idx_Frame < End_Of_Table_Trends 
	   ;Trend_Idx_Frame++)
	{
		DRV_NAND_Trend_Buffer[0]
		  					 [Trend_Idx_Frame]
							= 0xFF;
	}
	for(Trend_Idx_Frame = End_Of_Table_Trends 
	   ;Trend_Idx_Frame < (2*End_Of_Table_Trends) 
	   ;Trend_Idx_Frame++)
	{
		DRV_NAND_Trend_Buffer[0]
		 					 [Trend_Idx_Frame]
							= 0x00;
	}
	for(Trend_Idx_Frame = (2*End_Of_Table_Trends) 
	   ;Trend_Idx_Frame < (3*End_Of_Table_Trends) 
	   ;Trend_Idx_Frame++)
	{
		DRV_NAND_Trend_Buffer[0]
							 [Trend_Idx_Frame]
							= 0x00;
	}



	First_Start = FALSE;

}

else 
{	 
/*****************************************************************************/
/*                                 MONITORING 								 */					
if ((DRV_MONIT_Idx_Write_Frame + 1) % MONIT_BUFFER_SIZE !=
													DRV_MONIT_Idx_Read_Frame)
{									 

/*%C All the 15 minutes, we put a dating frame , or when the ventilation was off,*/
/*%C just before .*/
	if((Counter == FIFTEEN_MINUTES)
	||(MemoVentilState == VEN_VENTIL_DISABLE))
	{
/*%C The counter is reset */
		Counter = 0;
	

		DRV_NAND_Monit_Buffer[DRV_MONIT_Idx_Write_Frame]
		 					 [Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]  
					= (UBYTE)0x55;

		Monit_Idx_Frame = Monit_Idx_Frame + 1;
		if(Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_MONIT_Idx_Write_Frame = DRV_MONIT_Idx_Write_Frame + 1;
		  	if (DRV_MONIT_Idx_Write_Frame >= MONIT_BUFFER_SIZE)
			{
			  	DRV_MONIT_Idx_Write_Frame = 0;
				Monit_Idx_Frame = 0;
			}

		}
		DRV_NAND_Monit_Buffer[DRV_MONIT_Idx_Write_Frame]
							 [Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
					= (UBYTE)0x55;

		Monit_Idx_Frame = Monit_Idx_Frame + 1;
		if(Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_MONIT_Idx_Write_Frame = DRV_MONIT_Idx_Write_Frame + 1;
		  	if (DRV_MONIT_Idx_Write_Frame >= MONIT_BUFFER_SIZE)
			{
			  	DRV_MONIT_Idx_Write_Frame = 0;
				Monit_Idx_Frame = 0;
			}

		}
		DRV_NAND_Monit_Buffer[DRV_MONIT_Idx_Write_Frame]
   							 [Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
   					= (UBYTE)DB_RTCRead(DB_RTC_SECOND_U16);

		Monit_Idx_Frame = Monit_Idx_Frame + 1;
		if(Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_MONIT_Idx_Write_Frame = DRV_MONIT_Idx_Write_Frame + 1;
		  	if (DRV_MONIT_Idx_Write_Frame >= MONIT_BUFFER_SIZE)
			{
			  	DRV_MONIT_Idx_Write_Frame = 0;
				Monit_Idx_Frame = 0;
			}

		}
		DRV_NAND_Monit_Buffer[DRV_MONIT_Idx_Write_Frame]
							 [Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
					= (UBYTE)DB_RTCRead(DB_RTC_MINUTE_U16);

		Monit_Idx_Frame = Monit_Idx_Frame + 1;
		if(Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_MONIT_Idx_Write_Frame = DRV_MONIT_Idx_Write_Frame + 1;
		  	if (DRV_MONIT_Idx_Write_Frame >= MONIT_BUFFER_SIZE)
			{
			  	DRV_MONIT_Idx_Write_Frame = 0;
				Monit_Idx_Frame = 0;
			}

		}
		DRV_NAND_Monit_Buffer[DRV_MONIT_Idx_Write_Frame]
							 [Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
					= (UBYTE)DB_RTCRead(DB_RTC_HOUR_U16);

		Monit_Idx_Frame = Monit_Idx_Frame + 1;
		if(Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_MONIT_Idx_Write_Frame = DRV_MONIT_Idx_Write_Frame + 1;
		  	if (DRV_MONIT_Idx_Write_Frame >= MONIT_BUFFER_SIZE)
			{
			  	DRV_MONIT_Idx_Write_Frame = 0;
				Monit_Idx_Frame = 0;
			}

		}
		DRV_NAND_Monit_Buffer[DRV_MONIT_Idx_Write_Frame]
							 [Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
			= (UBYTE)DB_RTCRead(DB_RTC_YEAR_U16);

		Monit_Idx_Frame = Monit_Idx_Frame + 1;
		if(Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_MONIT_Idx_Write_Frame = DRV_MONIT_Idx_Write_Frame + 1;
		  	if (DRV_MONIT_Idx_Write_Frame >= MONIT_BUFFER_SIZE)
			{
			  	DRV_MONIT_Idx_Write_Frame = 0;
				Monit_Idx_Frame = 0;
			}

		}
		DRV_NAND_Monit_Buffer[DRV_MONIT_Idx_Write_Frame]
							 [Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
		= (UBYTE)DB_RTCRead(DB_RTC_MONTH_U16);

		Monit_Idx_Frame = Monit_Idx_Frame + 1;
		if(Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_MONIT_Idx_Write_Frame = DRV_MONIT_Idx_Write_Frame + 1;
		  	if (DRV_MONIT_Idx_Write_Frame >= MONIT_BUFFER_SIZE)
			{
			  	DRV_MONIT_Idx_Write_Frame = 0;
				Monit_Idx_Frame = 0;
			}

		}
		DRV_NAND_Monit_Buffer[DRV_MONIT_Idx_Write_Frame]
							 [Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
						= (UBYTE)DB_RTCRead(DB_RTC_DAY_U16);

		Monit_Idx_Frame = Monit_Idx_Frame + 1;
		if(Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_MONIT_Idx_Write_Frame = DRV_MONIT_Idx_Write_Frame + 1;
		  	if (DRV_MONIT_Idx_Write_Frame >= MONIT_BUFFER_SIZE)
			{
			  	DRV_MONIT_Idx_Write_Frame = 0;
				Monit_Idx_Frame = 0;
			}

		}
		DRV_NAND_Monit_Buffer[DRV_MONIT_Idx_Write_Frame]
   							 [Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
   							 = (UBYTE)HORODATAGE;

		Monit_Idx_Frame = Monit_Idx_Frame + 1;
		if(Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
		 	DRV_MONIT_Idx_Write_Frame = DRV_MONIT_Idx_Write_Frame + 1;
		  	if (DRV_MONIT_Idx_Write_Frame >= MONIT_BUFFER_SIZE)
			{
			  	DRV_MONIT_Idx_Write_Frame = 0;
				Monit_Idx_Frame = 0;
			}
		}

  	}
			   /* All the 40 ms */
 	if((Counter % 4) == 0)
	{	 

		if(ValveDetected == TRUE)
		{
			DRV_NAND_Monit_Buffer[DRV_MONIT_Idx_Write_Frame]
			 					 [Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]  
						= 0x00FF;
	
			Monit_Idx_Frame = Monit_Idx_Frame + 1;
			if(Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
			{
			 	DRV_MONIT_Idx_Write_Frame = DRV_MONIT_Idx_Write_Frame + 1;
			  	if (DRV_MONIT_Idx_Write_Frame >= MONIT_BUFFER_SIZE)
				{
				  	DRV_MONIT_Idx_Write_Frame = 0;
					Monit_Idx_Frame = 0;
				}
	
			}
			DRV_NAND_Monit_Buffer[DRV_MONIT_Idx_Write_Frame]
								 [Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
						= (UBYTE)(DB_ComputeRead(MEASURE_QEXH_S16)& 0x00FF);
	
			Monit_Idx_Frame = Monit_Idx_Frame + 1;
			if(Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
			{
			 	DRV_MONIT_Idx_Write_Frame = DRV_MONIT_Idx_Write_Frame + 1;
			  	if (DRV_MONIT_Idx_Write_Frame >= MONIT_BUFFER_SIZE)
				{
				  	DRV_MONIT_Idx_Write_Frame = 0;
					Monit_Idx_Frame = 0;
				}
	
			}
			DRV_NAND_Monit_Buffer[DRV_MONIT_Idx_Write_Frame]
	   							 [Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
	   					= (UBYTE)((DB_ComputeRead(MEASURE_QEXH_S16)>> 8)& 0x00FF);
	
			Monit_Idx_Frame = Monit_Idx_Frame + 1;
			if(Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
			{
			 	DRV_MONIT_Idx_Write_Frame = DRV_MONIT_Idx_Write_Frame + 1;
			  	if (DRV_MONIT_Idx_Write_Frame >= MONIT_BUFFER_SIZE)
				{
				  	DRV_MONIT_Idx_Write_Frame = 0;
					Monit_Idx_Frame = 0;
				}
	
			}
			DRV_NAND_Monit_Buffer[DRV_MONIT_Idx_Write_Frame]
								 [Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
						= (UBYTE)(DB_ComputeRead(MEASURE_QINSP_S16)& 0x00FF);
	
			Monit_Idx_Frame = Monit_Idx_Frame + 1;
			if(Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
			{
			 	DRV_MONIT_Idx_Write_Frame = DRV_MONIT_Idx_Write_Frame + 1;
			  	if (DRV_MONIT_Idx_Write_Frame >= MONIT_BUFFER_SIZE)
				{
				  	DRV_MONIT_Idx_Write_Frame = 0;
					Monit_Idx_Frame = 0;
				}
	
			}
			DRV_NAND_Monit_Buffer[DRV_MONIT_Idx_Write_Frame]
								 [Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
						= (UBYTE)((DB_ComputeRead(MEASURE_QINSP_S16)>> 8)& 0x00FF);
	
			Monit_Idx_Frame = Monit_Idx_Frame + 1;
			if(Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
			{
			 	DRV_MONIT_Idx_Write_Frame = DRV_MONIT_Idx_Write_Frame + 1;
			  	if (DRV_MONIT_Idx_Write_Frame >= MONIT_BUFFER_SIZE)
				{
				  	DRV_MONIT_Idx_Write_Frame = 0;
					Monit_Idx_Frame = 0;
				}
	
			}
	   }
	   else
	   {
			DRV_NAND_Monit_Buffer[DRV_MONIT_Idx_Write_Frame]
			 					 [Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]  
						= (UBYTE)((DB_ComputeRead(COMPUTED_LEAK_U16) / 10) & 0x00FF);
	
			Monit_Idx_Frame = Monit_Idx_Frame + 1;
			if(Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
			{
			 	DRV_MONIT_Idx_Write_Frame = DRV_MONIT_Idx_Write_Frame + 1;
			  	if (DRV_MONIT_Idx_Write_Frame >= MONIT_BUFFER_SIZE)
				{
				  	DRV_MONIT_Idx_Write_Frame = 0;
					Monit_Idx_Frame = 0;
				}
	
			}
			DRV_NAND_Monit_Buffer[DRV_MONIT_Idx_Write_Frame]
								 [Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
						= 0xFF;
	
			Monit_Idx_Frame = Monit_Idx_Frame + 1;
			if(Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
			{
			 	DRV_MONIT_Idx_Write_Frame = DRV_MONIT_Idx_Write_Frame + 1;
			  	if (DRV_MONIT_Idx_Write_Frame >= MONIT_BUFFER_SIZE)
				{
				  	DRV_MONIT_Idx_Write_Frame = 0;
					Monit_Idx_Frame = 0;
				}
	
			}
			DRV_NAND_Monit_Buffer[DRV_MONIT_Idx_Write_Frame]
	   							 [Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
	   					= 0xFF;
	
			Monit_Idx_Frame = Monit_Idx_Frame + 1;
			if(Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
			{
			 	DRV_MONIT_Idx_Write_Frame = DRV_MONIT_Idx_Write_Frame + 1;
			  	if (DRV_MONIT_Idx_Write_Frame >= MONIT_BUFFER_SIZE)
				{
				  	DRV_MONIT_Idx_Write_Frame = 0;
					Monit_Idx_Frame = 0;
				}
	
			}
			DRV_NAND_Monit_Buffer[DRV_MONIT_Idx_Write_Frame]
								 [Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
						= (UBYTE)(DB_ComputeRead(MEASURE_QINSP_LEAKCORRECTED_S16)& 0x00FF);
	
			Monit_Idx_Frame = Monit_Idx_Frame + 1;
			if(Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
			{
			 	DRV_MONIT_Idx_Write_Frame = DRV_MONIT_Idx_Write_Frame + 1;
			  	if (DRV_MONIT_Idx_Write_Frame >= MONIT_BUFFER_SIZE)
				{
				  	DRV_MONIT_Idx_Write_Frame = 0;
					Monit_Idx_Frame = 0;
				}
	
			}
			DRV_NAND_Monit_Buffer[DRV_MONIT_Idx_Write_Frame]
								 [Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
						= (UBYTE)((DB_ComputeRead(MEASURE_QINSP_LEAKCORRECTED_S16)>> 8)& 0x00FF);
	
			Monit_Idx_Frame = Monit_Idx_Frame + 1;
			if(Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
			{
			 	DRV_MONIT_Idx_Write_Frame = DRV_MONIT_Idx_Write_Frame + 1;
			  	if (DRV_MONIT_Idx_Write_Frame >= MONIT_BUFFER_SIZE)
				{
				  	DRV_MONIT_Idx_Write_Frame = 0;
					Monit_Idx_Frame = 0;
				}
	
			}
		}

		DRV_NAND_Monit_Buffer[DRV_MONIT_Idx_Write_Frame]
							 [Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
			= (UBYTE)(DB_ComputeRead(MEASURE_PATIENT_PRESSURE_S16)& 0x00FF);

		Monit_Idx_Frame = Monit_Idx_Frame + 1;
		if(Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_MONIT_Idx_Write_Frame = DRV_MONIT_Idx_Write_Frame + 1;
		  	if (DRV_MONIT_Idx_Write_Frame >= MONIT_BUFFER_SIZE)
			{
			  	DRV_MONIT_Idx_Write_Frame = 0;
				Monit_Idx_Frame = 0;
			}

		}
		DRV_NAND_Monit_Buffer[DRV_MONIT_Idx_Write_Frame]
							 [Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
		= (UBYTE)((DB_ComputeRead(MEASURE_PATIENT_PRESSURE_S16)>> 8)& 0x00FF);

		Monit_Idx_Frame = Monit_Idx_Frame + 1;
		if(Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_MONIT_Idx_Write_Frame = DRV_MONIT_Idx_Write_Frame + 1;
		  	if (DRV_MONIT_Idx_Write_Frame >= MONIT_BUFFER_SIZE)
			{
			  	DRV_MONIT_Idx_Write_Frame = 0;
				Monit_Idx_Frame = 0;
			}

		}
		DRV_NAND_Monit_Buffer[DRV_MONIT_Idx_Write_Frame]
							 [Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
						= (UBYTE)VentilState;

		Monit_Idx_Frame = Monit_Idx_Frame + 1;
		if(Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_MONIT_Idx_Write_Frame = DRV_MONIT_Idx_Write_Frame + 1;
		  	if (DRV_MONIT_Idx_Write_Frame >= MONIT_BUFFER_SIZE)
			{
			  	DRV_MONIT_Idx_Write_Frame = 0;
				Monit_Idx_Frame = 0;
			}

		}
		DRV_NAND_Monit_Buffer[DRV_MONIT_Idx_Write_Frame]
   							 [Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
   							 = (UBYTE)MONITORAGE;

		Monit_Idx_Frame = Monit_Idx_Frame + 1;
		if(Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
		 	DRV_MONIT_Idx_Write_Frame = DRV_MONIT_Idx_Write_Frame + 1;
		  	if (DRV_MONIT_Idx_Write_Frame >= MONIT_BUFFER_SIZE)
			{
			  	DRV_MONIT_Idx_Write_Frame = 0;
				Monit_Idx_Frame = 0;
			}
		}
	}
}
/******************************************************************************/
/*                         				TRENDS 				                  */

if ((DRV_TREND_Idx_Write_Frame + 1) % MONIT_BUFFER_SIZE !=
													DRV_TREND_Idx_Read_Frame)
{
	if((Counter % 6000) == 0)
	{
		DRV_NAND_Trend_Buffer[DRV_TREND_Idx_Write_Frame]
							 [Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
							 = (UBYTE)DB_ComputeRead(MEASURE_SPO2_U16);//SPO2

		Trend_Idx_Frame = Trend_Idx_Frame + 1;
		if(Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_TREND_Idx_Write_Frame = DRV_TREND_Idx_Write_Frame + 1;
		  	if (DRV_TREND_Idx_Write_Frame >= TREND_BUFFER_SIZE)
			{
			  	DRV_TREND_Idx_Write_Frame = 0;
				Trend_Idx_Frame = 0;
			}
 		}

		DRV_NAND_Trend_Buffer[DRV_TREND_Idx_Write_Frame]
							 [Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
							 = (UBYTE)DB_ComputeRead(MEASURE_HR_U16);//FC;

		Trend_Idx_Frame = Trend_Idx_Frame + 1;
		if(Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_TREND_Idx_Write_Frame = DRV_TREND_Idx_Write_Frame + 1;
		  	if (DRV_TREND_Idx_Write_Frame >= TREND_BUFFER_SIZE)
			{
			  	DRV_TREND_Idx_Write_Frame = 0;
				Trend_Idx_Frame = 0;
			}
 		}

		DRV_NAND_Trend_Buffer[DRV_TREND_Idx_Write_Frame]
							 [Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
			= (UBYTE)(DB_ComputeRead(COMPUTED_VTE_U16)& 0x00FF);

		Trend_Idx_Frame = Trend_Idx_Frame + 1;
		if(Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_TREND_Idx_Write_Frame = DRV_TREND_Idx_Write_Frame + 1;
		  	if (DRV_TREND_Idx_Write_Frame >= TREND_BUFFER_SIZE)
			{
			  	DRV_TREND_Idx_Write_Frame = 0;
				Trend_Idx_Frame = 0;
			}
 		}

		DRV_NAND_Trend_Buffer[DRV_TREND_Idx_Write_Frame]
							 [Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
			= (UBYTE)((DB_ComputeRead(COMPUTED_VTE_U16)>> 8) & 0x00FF);

		Trend_Idx_Frame = Trend_Idx_Frame + 1;
		if(Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_TREND_Idx_Write_Frame = DRV_TREND_Idx_Write_Frame + 1;
		  	if (DRV_TREND_Idx_Write_Frame >= TREND_BUFFER_SIZE)
			{
			  	DRV_TREND_Idx_Write_Frame = 0;
				Trend_Idx_Frame = 0;
			}
 		}

		DRV_NAND_Trend_Buffer[DRV_TREND_Idx_Write_Frame]
							 [Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
			= (UBYTE)(DB_ComputeRead(COMPUTED_VTI_U16)& 0x00FF);

		Trend_Idx_Frame = Trend_Idx_Frame + 1;
		if(Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_TREND_Idx_Write_Frame = DRV_TREND_Idx_Write_Frame + 1;
		  	if (DRV_TREND_Idx_Write_Frame >= TREND_BUFFER_SIZE)
			{
			  	DRV_TREND_Idx_Write_Frame = 0;
				Trend_Idx_Frame = 0;
			}
 		}

		DRV_NAND_Trend_Buffer[DRV_TREND_Idx_Write_Frame]
							 [Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
			= (UBYTE)((DB_ComputeRead(COMPUTED_VTI_U16)>> 8) & 0x00FF);

		Trend_Idx_Frame = Trend_Idx_Frame + 1;
		if(Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_TREND_Idx_Write_Frame = DRV_TREND_Idx_Write_Frame + 1;
		  	if (DRV_TREND_Idx_Write_Frame >= TREND_BUFFER_SIZE)
			{
			  	DRV_TREND_Idx_Write_Frame = 0;
				Trend_Idx_Frame = 0;
			}
 		}

		DRV_NAND_Trend_Buffer[DRV_TREND_Idx_Write_Frame]
							 [Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
			= (UBYTE)DB_ComputeRead(MEASURE_R_U16);

		Trend_Idx_Frame = Trend_Idx_Frame + 1;
		if(Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_TREND_Idx_Write_Frame = DRV_TREND_Idx_Write_Frame + 1;
		  	if (DRV_TREND_Idx_Write_Frame >= TREND_BUFFER_SIZE)
			{
			  	DRV_TREND_Idx_Write_Frame = 0;
				Trend_Idx_Frame = 0;
			}
 		}

		DRV_NAND_Trend_Buffer[DRV_TREND_Idx_Write_Frame]
							 [Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
			= (UBYTE)DB_ComputeRead(MEASURE_IE_DENOMINATOR_U16);

		Trend_Idx_Frame = Trend_Idx_Frame + 1;
		if(Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_TREND_Idx_Write_Frame = DRV_TREND_Idx_Write_Frame + 1;
		  	if (DRV_TREND_Idx_Write_Frame >= TREND_BUFFER_SIZE)
			{
			  	DRV_TREND_Idx_Write_Frame = 0;
				Trend_Idx_Frame = 0;
			}
 		}

		DRV_NAND_Trend_Buffer[DRV_TREND_Idx_Write_Frame]
							 [Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
			= (UBYTE)DB_ComputeRead(MEASURE_IE_NUMERATOR_U16);

		Trend_Idx_Frame = Trend_Idx_Frame + 1;
		if(Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_TREND_Idx_Write_Frame = DRV_TREND_Idx_Write_Frame + 1;
		  	if (DRV_TREND_Idx_Write_Frame >= TREND_BUFFER_SIZE)
			{
			  	DRV_TREND_Idx_Write_Frame = 0;
				Trend_Idx_Frame = 0;
			}
 		}
		
		DRV_NAND_Trend_Buffer[DRV_TREND_Idx_Write_Frame]
							 [Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
			= (UBYTE)(DB_ComputeRead(COMPUTED_VMI_U16)& 0x00FF);

		Trend_Idx_Frame = Trend_Idx_Frame + 1;
		if(Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_TREND_Idx_Write_Frame = DRV_TREND_Idx_Write_Frame + 1;
		  	if (DRV_TREND_Idx_Write_Frame >= TREND_BUFFER_SIZE)
			{
			  	DRV_TREND_Idx_Write_Frame = 0;
				Trend_Idx_Frame = 0;
			}
 		}
		
		DRV_NAND_Trend_Buffer[DRV_TREND_Idx_Write_Frame]
							 [Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
			= (UBYTE)((DB_ComputeRead(COMPUTED_VMI_U16)>> 8) & 0x00FF);

		Trend_Idx_Frame = Trend_Idx_Frame + 1;
		if(Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_TREND_Idx_Write_Frame = DRV_TREND_Idx_Write_Frame + 1;
		  	if (DRV_TREND_Idx_Write_Frame >= TREND_BUFFER_SIZE)
			{
			  	DRV_TREND_Idx_Write_Frame = 0;
				Trend_Idx_Frame = 0;
			}
 		}

		DRV_NAND_Trend_Buffer[DRV_TREND_Idx_Write_Frame]
							 [Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
			= (UBYTE)(DB_ComputeRead(COMPUTED_LEAK_U16)& 0x00FF);

		Trend_Idx_Frame = Trend_Idx_Frame + 1;
		if(Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_TREND_Idx_Write_Frame = DRV_TREND_Idx_Write_Frame + 1;
		  	if (DRV_TREND_Idx_Write_Frame >= TREND_BUFFER_SIZE)
			{
			  	DRV_TREND_Idx_Write_Frame = 0;
				Trend_Idx_Frame = 0;
			}
 		}

		DRV_NAND_Trend_Buffer[DRV_TREND_Idx_Write_Frame]
							 [Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
			= (UBYTE)((DB_ComputeRead(COMPUTED_LEAK_U16)>>8)& 0x00FF);

		Trend_Idx_Frame = Trend_Idx_Frame + 1;
		if(Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_TREND_Idx_Write_Frame = DRV_TREND_Idx_Write_Frame + 1;
		  	if (DRV_TREND_Idx_Write_Frame >= TREND_BUFFER_SIZE)
			{
			  	DRV_TREND_Idx_Write_Frame = 0;
				Trend_Idx_Frame = 0;
			}
 		}

		DRV_NAND_Trend_Buffer[DRV_TREND_Idx_Write_Frame]
							 [Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
			= (UBYTE)(DB_ComputeRead(COMPUTED_PEEP_U16)& 0x00FF);

		Trend_Idx_Frame = Trend_Idx_Frame + 1;
		if(Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_TREND_Idx_Write_Frame = DRV_TREND_Idx_Write_Frame + 1;
		  	if (DRV_TREND_Idx_Write_Frame >= TREND_BUFFER_SIZE)
			{
			  	DRV_TREND_Idx_Write_Frame = 0;
				Trend_Idx_Frame = 0;
			}
 		}

		DRV_NAND_Trend_Buffer[DRV_TREND_Idx_Write_Frame]
							 [Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
			= (UBYTE)((DB_ComputeRead(COMPUTED_PEEP_U16)>>8)& 0x00FF);

		Trend_Idx_Frame = Trend_Idx_Frame + 1;
		if(Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_TREND_Idx_Write_Frame = DRV_TREND_Idx_Write_Frame + 1;
		  	if (DRV_TREND_Idx_Write_Frame >= TREND_BUFFER_SIZE)
			{
			  	DRV_TREND_Idx_Write_Frame = 0;
				Trend_Idx_Frame = 0;
			}
 		}

		DRV_NAND_Trend_Buffer[DRV_TREND_Idx_Write_Frame]
							 [Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
			= (UBYTE)(DB_ComputeRead(COMPUTED_PIP_U16)& 0x00FF);

		Trend_Idx_Frame = Trend_Idx_Frame + 1;
		if(Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_TREND_Idx_Write_Frame = DRV_TREND_Idx_Write_Frame + 1;
		  	if (DRV_TREND_Idx_Write_Frame >= TREND_BUFFER_SIZE)
			{
			  	DRV_TREND_Idx_Write_Frame = 0;
				Trend_Idx_Frame = 0;
			}
 		}

		DRV_NAND_Trend_Buffer[DRV_TREND_Idx_Write_Frame]
							 [Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
			= (UBYTE)((DB_ComputeRead(COMPUTED_PIP_U16)>>8)& 0x00FF);

		Trend_Idx_Frame = Trend_Idx_Frame + 1;
		if(Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_TREND_Idx_Write_Frame = DRV_TREND_Idx_Write_Frame + 1;
		  	if (DRV_TREND_Idx_Write_Frame >= TREND_BUFFER_SIZE)
			{
			  	DRV_TREND_Idx_Write_Frame = 0;
				Trend_Idx_Frame = 0;
			}
 		}

	   DRV_NAND_Trend_Buffer[DRV_TREND_Idx_Write_Frame]
							 [Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
			= (UBYTE)VentilState;

		Trend_Idx_Frame = Trend_Idx_Frame + 1;
		if(Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_TREND_Idx_Write_Frame = DRV_TREND_Idx_Write_Frame + 1;
		  	if (DRV_TREND_Idx_Write_Frame >= TREND_BUFFER_SIZE)
			{
			  	DRV_TREND_Idx_Write_Frame = 0;
				Trend_Idx_Frame = 0;
			}
 		}

		CurrentMode = DB_ControlRead(CURRENT_MODE_U16);
		Trigger_Insp_Var = DB_CurrentRead(INSP_SENS_NO_SELECT_U16);
		Backup_R_Var = DB_CurrentRead(BACKUP_R_NO_SELECT_U16);
		switch (CurrentMode)
		{
			case VOL :
			{
				if (Trigger_Insp_Var == FALSE)
				{
					Trend_Ventilation_Mode = COM_VOL_A ;
				}
				else if (Trigger_Insp_Var == TRUE)
				{
					Trend_Ventilation_Mode = COM_VOL_C; 
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
					Trend_Ventilation_Mode = COM_PRES_A;
				}
				else if (Trigger_Insp_Var == TRUE)
				{
					Trend_Ventilation_Mode = COM_PRES_C; 
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
					Trend_Ventilation_Mode = COM_PSVT;
				}
				else if(Backup_R_Var == TRUE) 
				{
					Trend_Ventilation_Mode = COM_PSV; 
				}
				else
				{
					/*%C No Function */
				}
				break;
			}
					
			case VSIMV :
			{
					Trend_Ventilation_Mode = COM_VSIMV;
				break;
			}

			case PSIMV :
			{
					Trend_Ventilation_Mode = COM_PSIMV;
				break;
			}
			
			case CPAP :
			{
					Trend_Ventilation_Mode = COM_CPAP;
				break;
			}
			
			default :
			{
				break;
			}
		}
	
	   DRV_NAND_Trend_Buffer[DRV_TREND_Idx_Write_Frame]
							[Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
				= (UBYTE)Trend_Ventilation_Mode;

		Trend_Idx_Frame = Trend_Idx_Frame + 1;
		if(Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_TREND_Idx_Write_Frame = DRV_TREND_Idx_Write_Frame + 1;
		  	if (DRV_TREND_Idx_Write_Frame >= TREND_BUFFER_SIZE)
			{
			  	DRV_TREND_Idx_Write_Frame = 0;
				Trend_Idx_Frame = 0;
			}
 		}

	   DRV_NAND_Trend_Buffer[DRV_TREND_Idx_Write_Frame]
							[Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
				= (UBYTE)DB_RTCRead(DB_RTC_SECOND_U16);

		Trend_Idx_Frame = Trend_Idx_Frame + 1;
		if(Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_TREND_Idx_Write_Frame = DRV_TREND_Idx_Write_Frame + 1;
		  	if (DRV_TREND_Idx_Write_Frame >= TREND_BUFFER_SIZE)
			{
			  	DRV_TREND_Idx_Write_Frame = 0;
				Trend_Idx_Frame = 0;
			}
 		}

	   DRV_NAND_Trend_Buffer[DRV_TREND_Idx_Write_Frame]
							[Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
				= (UBYTE)DB_RTCRead(DB_RTC_MINUTE_U16);

		Trend_Idx_Frame = Trend_Idx_Frame + 1;
		if(Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_TREND_Idx_Write_Frame = DRV_TREND_Idx_Write_Frame + 1;
		  	if (DRV_TREND_Idx_Write_Frame >= TREND_BUFFER_SIZE)
			{
			  	DRV_TREND_Idx_Write_Frame = 0;
				Trend_Idx_Frame = 0;
			}
 		}

	   DRV_NAND_Trend_Buffer[DRV_TREND_Idx_Write_Frame]
							[Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
				= (UBYTE)DB_RTCRead(DB_RTC_HOUR_U16);

		Trend_Idx_Frame = Trend_Idx_Frame + 1;
		if(Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_TREND_Idx_Write_Frame = DRV_TREND_Idx_Write_Frame + 1;
		  	if (DRV_TREND_Idx_Write_Frame >= TREND_BUFFER_SIZE)
			{
			  	DRV_TREND_Idx_Write_Frame = 0;
				Trend_Idx_Frame = 0;
			}
 		}

	   DRV_NAND_Trend_Buffer[DRV_TREND_Idx_Write_Frame]
							[Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
				= (UBYTE)DB_RTCRead(DB_RTC_YEAR_U16);

		Trend_Idx_Frame = Trend_Idx_Frame + 1;
		if(Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_TREND_Idx_Write_Frame = DRV_TREND_Idx_Write_Frame + 1;
		  	if (DRV_TREND_Idx_Write_Frame >= TREND_BUFFER_SIZE)
			{
			  	DRV_TREND_Idx_Write_Frame = 0;
				Trend_Idx_Frame = 0;
			}
 		}

	   DRV_NAND_Trend_Buffer[DRV_TREND_Idx_Write_Frame]
							[Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
				= (UBYTE)DB_RTCRead(DB_RTC_MONTH_U16);

		Trend_Idx_Frame = Trend_Idx_Frame + 1;
		if(Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_TREND_Idx_Write_Frame = DRV_TREND_Idx_Write_Frame + 1;
		  	if (DRV_TREND_Idx_Write_Frame >= TREND_BUFFER_SIZE)
			{
			  	DRV_TREND_Idx_Write_Frame = 0;
				Trend_Idx_Frame = 0;
			}
 		}

	   DRV_NAND_Trend_Buffer[DRV_TREND_Idx_Write_Frame]
							[Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
				= (UBYTE)DB_RTCRead(DB_RTC_DAY_U16);

		Trend_Idx_Frame = Trend_Idx_Frame + 1;
		if(Trend_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_TREND_Idx_Write_Frame = DRV_TREND_Idx_Write_Frame + 1;
		  	if (DRV_TREND_Idx_Write_Frame >= TREND_BUFFER_SIZE)
			{
			  	DRV_TREND_Idx_Write_Frame = 0;
				Trend_Idx_Frame = 0;
			}
 		}
	} 


}
/*****************************************************************************/
		
}
Counter = Counter + 1;
}
/*%C When the ventilation becomes disable, we write into the Flash the date */
/*%C into the space remaining in the current raw of the array,and into the */
/*%C next row (so we write more than 512 octets of date).*/  
else if((VentilState == VEN_VENTIL_DISABLE)
      &&(Stop_Write_Date_Counter < 1)
	  &&(First_Start == FALSE))
{
	if ((DRV_MONIT_Idx_Write_Frame + 1) % MONIT_BUFFER_SIZE !=
													DRV_MONIT_Idx_Read_Frame)	
	{
		DRV_NAND_Monit_Buffer[DRV_MONIT_Idx_Write_Frame]
		 					 [Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]  
					= (UBYTE)0x55;

		Monit_Idx_Frame = Monit_Idx_Frame + 1;
		if(Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_MONIT_Idx_Write_Frame = DRV_MONIT_Idx_Write_Frame + 1;
		  	if (DRV_MONIT_Idx_Write_Frame >= MONIT_BUFFER_SIZE)
			{
			  	DRV_MONIT_Idx_Write_Frame = 0;
				Monit_Idx_Frame = 0;
				Stop_Write_Date_Counter = Stop_Write_Date_Counter + 1;
			}

		}
		DRV_NAND_Monit_Buffer[DRV_MONIT_Idx_Write_Frame]
							 [Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
					= (UBYTE)0x55;

		Monit_Idx_Frame = Monit_Idx_Frame + 1;
		if(Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_MONIT_Idx_Write_Frame = DRV_MONIT_Idx_Write_Frame + 1;
		  	if (DRV_MONIT_Idx_Write_Frame >= MONIT_BUFFER_SIZE)
			{
			  	DRV_MONIT_Idx_Write_Frame = 0;
				Monit_Idx_Frame = 0;
				Stop_Write_Date_Counter = Stop_Write_Date_Counter + 1;
			}

		}
		DRV_NAND_Monit_Buffer[DRV_MONIT_Idx_Write_Frame]
   							 [Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
   					= (UBYTE)DB_RTCRead(DB_RTC_SECOND_U16);

		Monit_Idx_Frame = Monit_Idx_Frame + 1;
		if(Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_MONIT_Idx_Write_Frame = DRV_MONIT_Idx_Write_Frame + 1;
		  	if (DRV_MONIT_Idx_Write_Frame >= MONIT_BUFFER_SIZE)
			{
			  	DRV_MONIT_Idx_Write_Frame = 0;
				Monit_Idx_Frame = 0;
				Stop_Write_Date_Counter = Stop_Write_Date_Counter + 1;
			}

		}
		DRV_NAND_Monit_Buffer[DRV_MONIT_Idx_Write_Frame]
							 [Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
					= (UBYTE)DB_RTCRead(DB_RTC_MINUTE_U16);

		Monit_Idx_Frame = Monit_Idx_Frame + 1;
		if(Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_MONIT_Idx_Write_Frame = DRV_MONIT_Idx_Write_Frame + 1;
		  	if (DRV_MONIT_Idx_Write_Frame >= MONIT_BUFFER_SIZE)
			{
			  	DRV_MONIT_Idx_Write_Frame = 0;
				Monit_Idx_Frame = 0;
				Stop_Write_Date_Counter = Stop_Write_Date_Counter + 1;
			}

		}
		DRV_NAND_Monit_Buffer[DRV_MONIT_Idx_Write_Frame]
							 [Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
					= (UBYTE)DB_RTCRead(DB_RTC_HOUR_U16);

		Monit_Idx_Frame = Monit_Idx_Frame + 1;
		if(Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_MONIT_Idx_Write_Frame = DRV_MONIT_Idx_Write_Frame + 1;
		  	if (DRV_MONIT_Idx_Write_Frame >= MONIT_BUFFER_SIZE)
			{
			  	DRV_MONIT_Idx_Write_Frame = 0;
				Monit_Idx_Frame = 0;
				Stop_Write_Date_Counter = Stop_Write_Date_Counter + 1;
			}

		}
		DRV_NAND_Monit_Buffer[DRV_MONIT_Idx_Write_Frame]
							 [Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
			= (UBYTE)DB_RTCRead(DB_RTC_YEAR_U16);

		Monit_Idx_Frame = Monit_Idx_Frame + 1;
		if(Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_MONIT_Idx_Write_Frame = DRV_MONIT_Idx_Write_Frame + 1;
		  	if (DRV_MONIT_Idx_Write_Frame >= MONIT_BUFFER_SIZE)
			{
			  	DRV_MONIT_Idx_Write_Frame = 0;
				Monit_Idx_Frame = 0;
				Stop_Write_Date_Counter = Stop_Write_Date_Counter + 1;
			}

		}
		DRV_NAND_Monit_Buffer[DRV_MONIT_Idx_Write_Frame]
							 [Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
		= (UBYTE)DB_RTCRead(DB_RTC_MONTH_U16);

		Monit_Idx_Frame = Monit_Idx_Frame + 1;
		if(Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_MONIT_Idx_Write_Frame = DRV_MONIT_Idx_Write_Frame + 1;
		  	if (DRV_MONIT_Idx_Write_Frame >= MONIT_BUFFER_SIZE)
			{
			  	DRV_MONIT_Idx_Write_Frame = 0;
				Monit_Idx_Frame = 0;
				Stop_Write_Date_Counter = Stop_Write_Date_Counter + 1;
			}

		}
		DRV_NAND_Monit_Buffer[DRV_MONIT_Idx_Write_Frame]
							 [Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
						= (UBYTE)DB_RTCRead(DB_RTC_DAY_U16);

		Monit_Idx_Frame = Monit_Idx_Frame + 1;
		if(Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
	 	DRV_MONIT_Idx_Write_Frame = DRV_MONIT_Idx_Write_Frame + 1;
		  	if (DRV_MONIT_Idx_Write_Frame >= MONIT_BUFFER_SIZE)
			{
			  	DRV_MONIT_Idx_Write_Frame = 0;
				Monit_Idx_Frame = 0;
				Stop_Write_Date_Counter = Stop_Write_Date_Counter + 1;
			}

		}
		DRV_NAND_Monit_Buffer[DRV_MONIT_Idx_Write_Frame]
   							 [Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE]
   							 = (UBYTE)HORODATAGE;

		Monit_Idx_Frame = Monit_Idx_Frame + 1;
		if(Monit_Idx_Frame%NAND_PAGE_CLUSTER_SIZE == 0)
		{
		 	DRV_MONIT_Idx_Write_Frame = DRV_MONIT_Idx_Write_Frame + 1;

		  	if (DRV_MONIT_Idx_Write_Frame >= MONIT_BUFFER_SIZE)
			{
			  	DRV_MONIT_Idx_Write_Frame = 0;
				Monit_Idx_Frame = 0;
				Stop_Write_Date_Counter = Stop_Write_Date_Counter + 1;
				
			}
		}
  }
}




MemoVentilState = VentilState;
}
