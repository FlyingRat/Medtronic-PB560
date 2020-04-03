/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505         		                       	  	    */
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 		  	*/
/* Filename	: DRV_SPIPowerSupplyUpdate.h    				                */
/*                                                           					*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function computes the rise time   */
/*%C value, fonction of rise level setting and respecting the condition :		*/
/*%C Ti < Rise time + 300 ms                                             		*/
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter : 			None		        			                  	*/
/*%IO Input/Output Parameter : 	None 	        			                  		*/
/*%O 	Output Parameter : 			None	                       				  		*/
/******************************************************************************/

#ifndef DRV_SPI_POWER_SUPPLY_UPDATE_H
#define DRV_SPI_POWER_SUPPLY_UPDATE_H


/******************************************************************************/
/*                  EXTERNAL FUNCTION DECLARATION                    	      */
/******************************************************************************/

extern void DB_PowerSupplyWrite(e_DB_POWERSUPPLY Id, UWORD16 Value);
extern void DB_ControlWrite(e_DB_CONTROL Id, UWORD16 Value);
extern UWORD16 TIM_ReadDecounterValue(e_TIM_TABLE_ID offset_table);
extern void TIM_StartDecounter(e_TIM_TABLE_ID offset_table, UWORD16 value);
extern void DB_ControlWrite(e_DB_CONTROL Id, UWORD16 Value);
extern e_BOOL SEC_ForceUnknownBattery(void);

#endif













											   