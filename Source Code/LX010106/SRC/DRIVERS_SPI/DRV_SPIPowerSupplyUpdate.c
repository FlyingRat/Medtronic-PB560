/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DRV_SPIPowerSupplyUpdate.c 					                  		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function update the values in the	*/
/*%C         Power Supply base from the values sent by the power board			*/
/*%C         Duration Max = 150 us (04/09/06)											*/
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter : 			Id			      	     	                  	*/
/*%IO Input/Output Parameter : 	None 	        			                  		*/
/*%O 	Output Parameter : 			None			                 				  		*/
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#ifndef _TASKING
#include "LH_ST10F276.h"
#else
#include "regf276e.h"
#endif	 
#include "io_declare.h"

#include "DB_PowerSupply.h"
#include "DB_Control.h"
#include "Structure.h"
#include "Timer_Data.h"
#include "DRV_SPIPowerSupplyUpdate.h"
#include "DRV_SPI_POWER_Data.h"


/******************************************************************************/
/*                     EXTERNAL FUNCTION DECLARATION                         	*/
/******************************************************************************/
void DRV_SPIPowerSupplyUpdate(void)
{
	static UWORD16 FirstRun = TRUE ;

	UBYTE	Idx;
	UBYTE	ComputeCRC;
	UWORD16	TmpMSB;
	UBYTE	TmpLSB;
	SWORD16 Temp = 0;

	if(FirstRun == TRUE)
	{
   		/*%C Lock the frist Run Flag															*/
		FirstRun = FALSE ;
		/*%C Start Timer to wait the display gauge (15 s)	*/
		TIM_StartDecounter(SPI_WAIT_DISPLAY_BATTERY_GAUGE,TIME_WAIT_DISPLAY_BATTERY_GAUGE);
	}

	/*%C if there is no data received*/
	if (SpiPtrReadBufferRx == SpiPtrWriteBufferRx) 
	{
		/*%C No Function */
	}
	/*%C else, reception treatment of the SPI bus*/
	else
	{
		/*%C Find the start frame				*/
		while ((SpiBufferOfReceipt[SpiPtrReadBufferRx ]!= SPI_POWER_START_FRAME_MSB_VALUE) && 
				(SpiPtrReadBufferRx != SpiPtrWriteBufferRx ))
		{
			SpiPtrReadBufferRx =(UBYTE) ((SpiPtrReadBufferRx + 1) % SPI_POWER_RECEIVE_BufferSize);
		}
 		/*%C if frame complète	*/
		if (((SPI_POWER_RECEIVE_BufferSize - SpiPtrReadBufferRx + SpiPtrWriteBufferRx)
			 % SPI_POWER_RECEIVE_BufferSize) >= SPI_POWER_RECEIVE_EndOfTable)
		{

			/*%C Compute CRC 										*/
			ComputeCRC = 0;
			for (Idx = SpiPtrReadBufferRx; 
				  Idx != (SpiPtrReadBufferRx + SPI_POWER_RECEIVE_CRC) % SPI_POWER_RECEIVE_BufferSize; 
				  Idx =(UBYTE)((Idx + 1) % SPI_POWER_RECEIVE_BufferSize))
			{
				ComputeCRC ^= (UBYTE)SpiBufferOfReceipt[Idx];
			}

				
			/*%C Header and end frame verification, CRC	 verification*/
			if 	(	(SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_CRC) 			%SPI_POWER_RECEIVE_BufferSize] == ComputeCRC)
				&& 	(SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_LSB_START_FRAME)%SPI_POWER_RECEIVE_BufferSize] == SPI_POWER_START_FRAME_LSB_VALUE)
				&& 	(SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_END_FRAME)		%SPI_POWER_RECEIVE_BufferSize] == SPI_POWER_END_FRAME_VALUE)
				)
			{
				/*%C Update PowerSupplyFrame flag */			
				PowerSupplyFrame = TRUE ;
					
				/* V_BAT_U16 */
				TmpMSB = SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_MSB_V_BAT_U16) % SPI_POWER_RECEIVE_BufferSize];
				TmpLSB = SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_LSB_V_BAT_U16) % SPI_POWER_RECEIVE_BufferSize];
				DB_PowerSupplyWrite(V_BAT_U16, ((TmpMSB << 8 ) | TmpLSB) );

				/* TEMP_BAT_S16 */
				TmpMSB = SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_MSB_TEMP_BAT_S16) % SPI_POWER_RECEIVE_BufferSize];
				TmpLSB = SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_LSB_TEMP_BAT_S16) % SPI_POWER_RECEIVE_BufferSize];
				Temp =(SWORD16) ((TmpMSB << 8 ) | TmpLSB);
				Temp = Temp/10;
				DB_PowerSupplyWrite(TEMP_BAT_S16, Temp );

				/* BAT_CYCLES_U16 */
				TmpMSB = SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_MSB_BAT_CYCLES_U16) % SPI_POWER_RECEIVE_BufferSize];
				TmpLSB = SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_LSB_BAT_CYCLES_U16) % SPI_POWER_RECEIVE_BufferSize];
				DB_PowerSupplyWrite(BAT_CYCLES_U16, ((TmpMSB << 8 ) | TmpLSB) );
				
				/* BAT_STATE_U16 */
				TmpLSB = SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_LSB_BAT_STATE_U16) % SPI_POWER_RECEIVE_BufferSize];
				DB_PowerSupplyWrite(BAT_STATE_U16, TmpLSB);

				/* POWER_TYPE_U16 */
				TmpLSB = SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_LSB_POWER_TYPE_U16) % SPI_POWER_RECEIVE_BufferSize];
				DB_PowerSupplyWrite(POWER_TYPE_U16, TmpLSB);

				if ((TmpLSB == BATTERY)
					&& (TIM_ReadDecounterValue(SPI_WAIT_DISPLAY_BATTERY_GAUGE) == 0))
				{
					DB_ControlWrite(DISPLAY_BATTERY_U16, TRUE);
				}								  
				else
				{
					DB_ControlWrite(DISPLAY_BATTERY_U16, FALSE);
				}

				/* JAUGE_MINUTE_U16 */
				TmpMSB = SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_MSB_JAUGE_MINUTE_U16) % SPI_POWER_RECEIVE_BufferSize];
				TmpLSB = SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_LSB_JAUGE_MINUTE_U16) % SPI_POWER_RECEIVE_BufferSize];
				TmpMSB =  ((TmpMSB << 8 ) | TmpLSB);
				/* Store the jauge in minute	*/
				DB_PowerSupplyWrite(JAUGE_MINUTE_U16,TmpMSB);

				/* Compute the display jauge, modulo 10 minutes */
				TmpLSB = (UBYTE) (TmpMSB % 10);
				if(TmpLSB < 5)  
				{
					/* Computed value less remaining value of modulo */
					TmpMSB = TmpMSB - TmpLSB;
				}
				else
				{
					/* computed value less difference from remaining value and 10 */
					 TmpMSB = TmpMSB - (TmpLSB - 10);
				}
				/* Store the display jauge */
				DB_PowerSupplyWrite(JAUGE_MINUTE_DISPLAY_U16, TmpMSB % 60);
				DB_PowerSupplyWrite(JAUGE_HOUR_DISPLAY_U16, TmpMSB / 60);

				/* JAUGE_AVALAIBLE_U16 */
				TmpLSB = SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_LSB_JAUGE_AVALAIBLE_U16) % SPI_POWER_RECEIVE_BufferSize];
				DB_PowerSupplyWrite(JAUGE_AVALAIBLE_U16, TmpLSB);

				/* PER_CENT_BAT_U16 */
				TmpLSB = SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_LSB_PER_CENT_BAT_U16) % SPI_POWER_RECEIVE_BufferSize];
				DB_PowerSupplyWrite(PER_CENT_BAT_U16, TmpLSB);

				/* NO_PRESENCE_BAT_U16 */
				TmpLSB = SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_LSB_NO_PRESENCE_BAT_U16) % SPI_POWER_RECEIVE_BufferSize];
				DB_PowerSupplyWrite(NO_PRESENCE_BAT_U16, TmpLSB);

				/* BAT_KO_U16 */
				TmpLSB = SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_LSB_BAT_KO_U16) % SPI_POWER_RECEIVE_BufferSize];
				DB_PowerSupplyWrite(BAT_KO_U16, TmpLSB);

				/* CHARGE_KO_U16 */
				TmpLSB = SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_LSB_CHARGE_KO_U16) % SPI_POWER_RECEIVE_BufferSize];
				DB_PowerSupplyWrite(CHARGE_KO_U16, TmpLSB);

				/* UNKNOWN_BATTERY_U16 */
				if (SEC_ForceUnknownBattery() == TRUE)
				{
					DB_PowerSupplyWrite(UNKNOWN_BATTERY_U16, TRUE);
				}
				else {
					TmpLSB = SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_LSB_UNKNOWN_BATTERY_U16) % SPI_POWER_RECEIVE_BufferSize];
					DB_PowerSupplyWrite(UNKNOWN_BATTERY_U16, TmpLSB);
				}

				/* AMBIENT_TEMP_S16 */
				TmpMSB = SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_MSB_AMBIENT_TEMP_S16) % SPI_POWER_RECEIVE_BufferSize];
				TmpLSB = SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_LSB_AMBIENT_TEMP_S16) % SPI_POWER_RECEIVE_BufferSize];
				Temp =(SWORD16) ((TmpMSB << 8 ) | TmpLSB);
				Temp = Temp/10;
				DB_PowerSupplyWrite(AMBIENT_TEMP_S16, Temp);

				/* BATTERY_END_U16 */
				TmpLSB = SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_LSB_BATTERY_END_U16) % SPI_POWER_RECEIVE_BufferSize];
				DB_PowerSupplyWrite(BATTERY_END_U16, TmpLSB);

				/* BATTERY_LOW_U16 */
				TmpLSB = SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_LSB_BATTERY_LOW_U16) % SPI_POWER_RECEIVE_BufferSize];
				DB_PowerSupplyWrite(BATTERY_LOW_U16, TmpLSB);

				/* FIRST_DATE_DAY_U16 */
				TmpLSB = SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_LSB_FIRST_DATE_DAY_U16) % SPI_POWER_RECEIVE_BufferSize];
				DB_PowerSupplyWrite(FIRST_DATE_DAY_U16, TmpLSB);

				/* FIRST_DATE_MONTH_U16 */
				TmpLSB = SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_LSB_FIRST_DATE_MONTH_U16) % SPI_POWER_RECEIVE_BufferSize];
				DB_PowerSupplyWrite(FIRST_DATE_MONTH_U16, TmpLSB);

				/* FIRST_DATE_YEAR_U16 */
				TmpLSB = SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_LSB_FIRST_DATE_YEAR_U16) % SPI_POWER_RECEIVE_BufferSize];
				DB_PowerSupplyWrite(FIRST_DATE_YEAR_U16, TmpLSB);

				/* BAT_TEMP_OUTOFBOUNDS_U16 */
				TmpLSB = SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_LSB_BAT_TEMP_OVERFLOW) % SPI_POWER_RECEIVE_BufferSize];
				DB_PowerSupplyWrite(BAT_TEMP_OUTOFBOUNDS_U16, TmpLSB);

				/* SUPPLY_MEASURE_FAILURE_U16 */
				TmpLSB = SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_LSB_SUPPLY_MEASURE_FAILURE) % SPI_POWER_RECEIVE_BufferSize];
				DB_PowerSupplyWrite(SUPPLY_MEASURE_FAILURE_U16, TmpLSB);

				/* FAILURE_24V_FLAG_U16 */
				TmpLSB = SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_LSB_FAILURE_24V_FLAG) % SPI_POWER_RECEIVE_BufferSize];
				DB_PowerSupplyWrite(FAILURE_24V_FLAG_U16, TmpLSB);

				/* AMBIENT_TEMP_OUTOFBOUNDS_U16 */
				TmpLSB = SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_LSB_AMBIENT_TEMP_OUTOFBOUNDS) % SPI_POWER_RECEIVE_BufferSize];
				DB_PowerSupplyWrite(AMBIENT_TEMP_OUTOFBOUNDS_U16, TmpLSB);

				/* COOLING_FAN_FAILURE_FLAG_U16 */
				TmpLSB = SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_LSB_COOLING_FAN_FAILURE_FLAG) % SPI_POWER_RECEIVE_BufferSize];
				DB_PowerSupplyWrite(COOLING_FAN_FAILURE_FLAG_U16, TmpLSB);

				/* POWER_SUPPLY_VERSION_NUMBER_0 */
				TmpLSB = SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_LSB_FIRST_VERSION_IDENTIFIANT) % SPI_POWER_RECEIVE_BufferSize];
				DB_PowerSupplyWrite(POWER_SUPPLY_VERSION_NUMBER_0, TmpLSB);

				/* POWER_SUPPLY_VERSION_NUMBER_1 */
				TmpLSB = SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_LSB_SECOND_VERSION_IDENTIFIANT) % SPI_POWER_RECEIVE_BufferSize];
				DB_PowerSupplyWrite(POWER_SUPPLY_VERSION_NUMBER_1, TmpLSB);

				/* POWER_SUPPLY_VERSION_NUMBER_2 */
				TmpLSB = SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_LSB_THIRD_VERSION_IDENTIFIANT) % SPI_POWER_RECEIVE_BufferSize];
				DB_PowerSupplyWrite(POWER_SUPPLY_VERSION_NUMBER_2, TmpLSB);

				/* FIRST_DATE_HOUR_U16 */
				TmpLSB = SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_LSB_BAT_FIRST_DATE_HOUR_U16) % SPI_POWER_RECEIVE_BufferSize];
				DB_PowerSupplyWrite(FIRST_DATE_HOUR_U16, TmpLSB);

				/* FIRST_DATE_MINUTE_U16 */
				TmpLSB = SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_LSB_BAT_FIRST_DATE_MINUTE_U16) % SPI_POWER_RECEIVE_BufferSize];
				DB_PowerSupplyWrite(FIRST_DATE_MINUTE_U16, TmpLSB);

				/* FIRST_DATE_SECOND_U16 */
				TmpLSB = SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_LSB_BAT_FIRST_DATE_SECOND_U16) % SPI_POWER_RECEIVE_BufferSize];
				DB_PowerSupplyWrite(FIRST_DATE_SECOND_U16, TmpLSB);

				/* AGEING_U16 */
				/* Value between 50 and 110% */
				TmpLSB = SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_LSB_BAT_AGEING_U16) % SPI_POWER_RECEIVE_BufferSize];
				DB_PowerSupplyWrite(AGING_U16, TmpLSB);

				/* CAPACITY_THEORICAL_U16 */
				TmpMSB = SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_LSB_BAT_TYPICAL_CAPACITY_U16) % SPI_POWER_RECEIVE_BufferSize];
				DB_PowerSupplyWrite(CAPACITY_THEORICAL_U16, 100*TmpMSB);

				 /* CAPACITY_U16 */
				TmpMSB = SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_LSB_BAT_TYPICAL_CAPACITY_U16) % SPI_POWER_RECEIVE_BufferSize];
				DB_PowerSupplyWrite(CAPACITY_U16, TmpMSB * TmpLSB);

				/* SUPPLIER_U16 */
				TmpLSB = SpiBufferOfReceipt[(SpiPtrReadBufferRx + SPI_POWER_RECEIVE_LSB_BAT_SUPPLIER_U16) % SPI_POWER_RECEIVE_BufferSize];
				DB_PowerSupplyWrite(SUPPLIER_U16, TmpLSB);

				//incrementation du pointeur de lecture pour lire la trame suivante
				SpiPtrReadBufferRx =(UBYTE) ((SpiPtrReadBufferRx + SPI_POWER_RECEIVE_EndOfTable)%SPI_POWER_RECEIVE_BufferSize);
		    
				TIM_StartDecounter(SPI_FRAME_TIME,TIME_FRAMES_SPI_RECEIVE);
			}
			else
			{
				SpiPtrReadBufferRx =(UBYTE)( (SpiPtrReadBufferRx +1)%SPI_POWER_RECEIVE_BufferSize) ;
			}
		}
	}
   	/*%C overtaking of the time between two frames*/
	if (TIM_ReadDecounterValue(SPI_FRAME_TIME) == 0)
	{
		/*%C Bus state writing in the control base */
		DB_ControlWrite(SUPPLY_BUS_FAILURE_U16,TRUE);

		/*%C Forcing DISPLAY_BATTERY_U16 flag to TRUE to make the GUI display the Battery symbol */
		DB_ControlWrite(DISPLAY_BATTERY_U16,TRUE);
	}
	else
	{
		/*%C Bus state writing in the control base */
		DB_ControlWrite(SUPPLY_BUS_FAILURE_U16,FALSE);
	}
}
