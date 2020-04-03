/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_RS232_TransmitMonit.c													*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C          Sent monitoring information by the serial port                  */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/
#include "p18f6622.h"
#include "IO_Declare.h"
#include "typedef.h"
#include "DB_Measurement.h"
#include "DB_EEPROM_BAT.h"
#include "DB_PowerSupply.h"
#include "DRV_RS232_TransmitMonit.h"
#include "enum.h"
#include "DRV_RS232_Data.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void DRV_RS232_TransmitMonit(void)
{

	UBYTE ComputeCRC;
	UBYTE Idx = 0;

	if (EndOfTransmit == TRUE)
	{
		EndOfTransmit  = FALSE;
		ArrayTxDataId = MSB_START_FRAME;

		/*%C Trame monitorage 																	*/
		ComputeCRC = 0;
		ComputeCRC ^= ArrayTxData[MSB_START_FRAME];
		ComputeCRC ^= ArrayTxData[LSB_START_FRAME];
		
		/*%C Measure Temp_BATTERY 																*/
		ArrayTxData[DATA0] =  (UBYTE) (DB_Measurement[BATTERY_TEMP] / 256);
		ComputeCRC ^= ArrayTxData[DATA0];
		ArrayTxData[DATA1] =  (UBYTE) (DB_Measurement[BATTERY_TEMP]);
		ComputeCRC ^= ArrayTxData[DATA1];		
		
		/*%C Identifiant batterie																*/
		ArrayTxData[DATA2] =  (UBYTE) Ram_Read_Bat[DATA_FIXE_IDENTIFIANT_6];
		ComputeCRC ^= ArrayTxData[DATA2];
		ArrayTxData[DATA3] =  (UBYTE) Ram_Read_Bat[DATA_FIXE_IDENTIFIANT_7];
		ComputeCRC ^= ArrayTxData[DATA3];
		
		/*%C Measure 3V3 																			*/
		ArrayTxData[DATA4] =  (UBYTE) (DB_Measurement[MEASURE_3V3] / 256);
		ComputeCRC ^= ArrayTxData[DATA4];
		ArrayTxData[DATA5] =  (UBYTE) (DB_Measurement[MEASURE_3V3]);
		ComputeCRC ^= ArrayTxData[DATA5];
		
		/*%C Measure 5V 																			*/
		ArrayTxData[DATA6] =  (UBYTE) (DB_Measurement[MEASURE_5V] / 256);
		ComputeCRC ^= ArrayTxData[DATA6];
		ArrayTxData[DATA7] =  (UBYTE) DB_Measurement[MEASURE_5V];
		ComputeCRC ^= ArrayTxData[DATA7];
		
		/*%C Measure VACDC																		*/
		ArrayTxData[DATA8] =  (UBYTE) (DB_Measurement[MEASURE_VACDC] / 256);
		ComputeCRC ^= ArrayTxData[DATA8];
		ArrayTxData[DATA9] =  (UBYTE) DB_Measurement[MEASURE_VACDC];
		ComputeCRC ^= ArrayTxData[DATA9];
		
		/*%C Measure I_BAT																		*/
		ArrayTxData[DATA10] = (UBYTE) (DB_Measurement[I_BAT] / 256);
		ComputeCRC ^= ArrayTxData[DATA10];
		ArrayTxData[DATA11] = (UBYTE) DB_Measurement[I_BAT];
		ComputeCRC ^= ArrayTxData[DATA11];
		
		/*%C Measure V_CHARGE																	*/
		ArrayTxData[DATA12] = (UBYTE) (DB_Measurement[VCHARGE_MEASURE_FILTERED] / 256);
		ComputeCRC ^= ArrayTxData[DATA12];
		ArrayTxData[DATA13] = (UBYTE) DB_Measurement[VCHARGE_MEASURE_FILTERED];
		ComputeCRC ^= ArrayTxData[DATA13];
		
		/*%C Measure TEMP_AMB																	*/
		ArrayTxData[DATA14] = (UBYTE) (DB_Measurement[TEMP_AMB] / 256);
		ComputeCRC ^= ArrayTxData[DATA14];
		ArrayTxData[DATA15] = (UBYTE) DB_Measurement[TEMP_AMB];
		ComputeCRC ^= ArrayTxData[DATA15];
		
		/*%C Measure VDC																			*/
		ArrayTxData[DATA16] = (UBYTE) (DB_Measurement[MEASURE_VDC] / 256);
		ComputeCRC ^= ArrayTxData[DATA16];
		ArrayTxData[DATA17] = (UBYTE) DB_Measurement[MEASURE_VDC];
		ComputeCRC ^= ArrayTxData[DATA17];
		
		/*%C Measure 24VUTIL																		*/
		ArrayTxData[DATA18] = (UBYTE) (DB_Measurement[MEASURE_24VUTIL] / 256);
		ComputeCRC ^= ArrayTxData[DATA18];
		ArrayTxData[DATA19] = (UBYTE) DB_Measurement[MEASURE_24VUTIL];
		ComputeCRC ^= ArrayTxData[DATA19];
		
		/*%C Measure V_BAT																		*/
		ArrayTxData[DATA20] = (UBYTE) (DB_Measurement[MEASURE_VBAT] / 256);
		ComputeCRC ^= ArrayTxData[DATA20];
		ArrayTxData[DATA21] = (UBYTE) DB_Measurement[MEASURE_VBAT];
		ComputeCRC ^= ArrayTxData[DATA21];
		
		/*%C Actionneur_1 frame																	*/
		ArrayTxData[DATA22] = (UBYTE) (COMMUT_IFC) + 
									         (LED_ETAT_BAT << 1) + 
												(PRESENCE_DC << 2 ) +
												(PRESENCE_AC << 3) +
												(COMMUT_AC << 4) +
												(SHUNT_DIODE_AC << 5) +
												(COMMUT_DC << 6) +
												(SHUNT_DIODE_DC << 7);
		ComputeCRC ^= ArrayTxData[DATA22];
		
		/*%C Actionneur_2 frame																	*/	
		ArrayTxData[DATA23] = (UBYTE) (SHUNT_DIODE_CHARGEUR) + 
												(SHUNT_DIODE_BAT << 1) +
												(COMMUT_BAT << 2) +
												(COMMUT_CHARGEUR << 3) +
												(INTERRUPT_VDC << 4) + 
												(INTERRUPT_VACDC << 5);
		ComputeCRC ^= ArrayTxData[DATA23];
		
		/*%C DATA FREE_1																			*/
		ArrayTxData[DATA24] = (UBYTE) 0x55;
		ComputeCRC ^= ArrayTxData[DATA24];
		ArrayTxData[DATA25] = (UBYTE) 0xAA;
		ComputeCRC ^= ArrayTxData[DATA25];
	
		/*%C DATA FREE_2																			*/
		ArrayTxData[DATA26] = (UBYTE) 0x55;
		ComputeCRC ^= ArrayTxData[DATA26];
		ArrayTxData[DATA27] = (UBYTE) 0xAA;
		ComputeCRC ^= ArrayTxData[DATA27];
	
		/*%C DATA FREE_3																			*/
		ArrayTxData[DATA28] = (UBYTE) 0x55;
		ComputeCRC ^= ArrayTxData[DATA28];
		ArrayTxData[DATA29] = (UBYTE) 0xAA;
		ComputeCRC ^= ArrayTxData[DATA29];
	
		/*%C Measure FAN_SPEED																	*/
		ArrayTxData[DATA30] = (UBYTE) (DB_Measurement[MEASURE_FAN_SPEED] /256);
		ComputeCRC ^= ArrayTxData[DATA30];
		ArrayTxData[DATA31] = (UBYTE) DB_Measurement[MEASURE_FAN_SPEED];
		ComputeCRC ^= ArrayTxData[DATA31];
	
		/*%C Measure I_Bat Average 															*/
		ArrayTxData[DATA32] = (UBYTE) (DB_Measurement[IBAT_AVERAGE] / 256);
		ComputeCRC ^= ArrayTxData[DATA32];
		ArrayTxData[DATA33] = (UBYTE) DB_Measurement[IBAT_AVERAGE];
		ComputeCRC ^= ArrayTxData[DATA33];
	
		/*%C Measure BAT_IMPEDANCE																*/
		ArrayTxData[DATA34] = (UBYTE) (DB_powerSupply[BAT_IMPEDANCE] / 256);
		ComputeCRC ^= ArrayTxData[DATA34];
		ArrayTxData[DATA35] = (UBYTE) DB_powerSupply[BAT_IMPEDANCE];
		ComputeCRC ^= ArrayTxData[DATA35];
		
		/*%C Measure DISCHARGE_BAT_CYCLES													*/
		ArrayTxData[DATA36] = (UBYTE) (DB_powerSupply[DISCHARGE_BAT_CYCLES] / 256);
		ComputeCRC ^= ArrayTxData[DATA36];
		ArrayTxData[DATA37] = (UBYTE) DB_powerSupply[DISCHARGE_BAT_CYCLES];
		ComputeCRC ^= ArrayTxData[DATA37];
		
		/*%C Measure BAT_AGEING																	*/
		ArrayTxData[DATA38] = (UBYTE) DB_powerSupply[BAT_AGEING];
		ComputeCRC ^= ArrayTxData[DATA38];
		
		/*%C Measure GAUGE_MINUTE_U16															*/
		ArrayTxData[DATA39] = (UBYTE) (DB_powerSupply[GAUGE_MINUTE_U16] / 256);
		ComputeCRC ^= ArrayTxData[DATA39];
		ArrayTxData[DATA40] = (UBYTE) DB_powerSupply[GAUGE_MINUTE_U16];
		ComputeCRC ^= ArrayTxData[DATA40];
		
		/*%C Measure PER_CENT_BAT_U16															*/
		ArrayTxData[DATA41] = (UBYTE) DB_powerSupply[PER_CENT_BAT_U16];
		ComputeCRC ^= ArrayTxData[DATA41];
		
		/*%C Calcul FEM 																			*/
		ArrayTxData[DATA42] = (UBYTE) (DB_powerSupply[FEM_COMPUTE] / 256);
		ComputeCRC ^= ArrayTxData[DATA42];
		ArrayTxData[DATA43] = (UBYTE) DB_powerSupply[FEM_COMPUTE];
		ComputeCRC ^= ArrayTxData[DATA43];
		
		/*%C Calcul Capacité théorique														*/
		ArrayTxData[DATA44] = (UBYTE) (DB_powerSupply[BAT_CAPACITY_THEORICAL_FOR_GAUGE] / 256);
		ComputeCRC ^= ArrayTxData[DATA44];
		ArrayTxData[DATA45] = (UBYTE) DB_powerSupply[BAT_CAPACITY_THEORICAL_FOR_GAUGE];
		ComputeCRC ^= ArrayTxData[DATA45];
		
		/*%C Calcul Capacité compensée														*/
		ArrayTxData[DATA46] = (UBYTE) (DB_powerSupply[BAT_CAPACITY_COMPENSATED] / 256);
		ComputeCRC ^= ArrayTxData[DATA46];
		ArrayTxData[DATA47] = (UBYTE) DB_powerSupply[BAT_CAPACITY_COMPENSATED];
		ComputeCRC ^= ArrayTxData[DATA47];
		
		/*%C Calcul Veillissement calculé													*/
		ArrayTxData[DATA48] = (UBYTE) (DB_powerSupply[BAT_AGEING_COMPUTED] / 256);
		ComputeCRC ^= ArrayTxData[DATA48];
		ArrayTxData[DATA49] = (UBYTE) DB_powerSupply[BAT_AGEING_COMPUTED];
		ComputeCRC ^= ArrayTxData[DATA49];
		
		ArrayTxData[CRC] = ComputeCRC;
		
		/*%C Autorisation de l'interruption de transmission RS232 					*/
		PIE3bits.TX2IE = 1;
	}
}
