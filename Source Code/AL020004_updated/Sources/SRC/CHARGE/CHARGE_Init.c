/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CHARGE_Init.c                                                	*/
/*													 						  							*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                     																		*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/

#include "p18f6622.h"
#include "IO_Declare.h"
#include "typedef.h"
#include "define.h"
#include "enum.h"
#include "DB_Control.h"
#include "DB_PowerSupply.h"
#include "DB_Measurement.h"
#include "CHARGE_Init.h"
#include "CHARGE_Data.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void CHARGE_Init(void)
{
	
	UWORD16 Measure_Vcharge = 0;

	static UBYTE PointNb = 0;
	static UWORD16 PWM_Sum = 0;

	UWORD16 Vbat_Measure_Filtered = DB_Measurement_Read(VBAT_MEASURE_FILTERED);
	/*%C RaZ Cumul de la capacité de la batterie en charge */ 
	CumulChargeCurrent = 0 ;
	/*%C Start timer  */
	TIM_StartDecounter16(SYS_COULOMB_COMPUTE_DELAY
											, TIME_COULOMB_COMPUTE_DELAY);
	/*%C Start the maximum delay to initialize charging */
	/* Init_Chargeur ne doit pas dépasser CHARGE_INIT_PERIOD_TIME_OUT */
	/*%C When there's not yet charge authorization	*/
	if (Init_Chargeur_Autorisation == FALSE)
	{
		/*%C begening of count down for charge initialization */
 		TIM_StartDecounter16(CHARGE_INIT_PERIOD,CHARGE_INIT_PERIOD_TIME_OUT); 
		/*%C Lock Max delay launching */
		Init_Chargeur_Autorisation = TRUE;
		/*%C Reset chargeur configure value */
		PointNb = 0 ;
		PWM_Sum = 0 ;
	}
	else
	{
		/*%C No Function */
	}
	/*%C While the delay is  not over */
	if(TIM_ReadValue16(CHARGE_INIT_PERIOD)!= 0)
	{
		/*%C  Init_Charging allowed, commutation of charging stage */
		SHUNT_DIODE_CHARGEUR = FALSE;
		COMMUT_CHARGEUR = FALSE;
		COMMUT_IFC = TRUE;
		/*%C 	Maximum charge current setpoint */
		PWM_ICHARGE = 0x00;
		
		/*%C  VCharge measure up dating */
		Measure_Vcharge = DB_Measurement_Read(MEASURE_VCHARGE);
		
		/*  PWM_VCharge regulation ( delta setpoint measure) */
		PWM_VCHARGE = CHARGE_Loop_Controller(VBAT_CHARGE_SETPOINT, Measure_Vcharge);
		/*%C test to ensure to be on good level between 29.26V and 29.54 V */
		if((Measure_Vcharge > VCHARGE_LOW_LEVEL) &&
			(Measure_Vcharge < VCHARGE_HIGH_LEVEL))
		{
			/*%C  Loop for calculate average of PWM when measure is on good level */
			/*%C this way filtrates non stable measurement */
			if(PointNb < 99)
			{
				/*%C Summing of PWM for average */
				PWM_Sum = PWM_Sum + Previous_PWM_Charge;
				/*%C icreasing of average index */
				PointNb = PointNb + 1;
			}
			/*%C When there's 100 consecutives good measures */
			else if(PointNb == 99)
			{
				/*%C Computing average of setpoints  for PWM and commutation */
				PWM_Sum = PWM_Sum / 100;
				PWM_VCHARGE = PWM_Sum ;
				COMMUT_IFC = FALSE;
				/*%C Checking if the VBat measured is lower than 28.5 V */
				/*%C Delivering Authorization for charging */
				DB_Control_Write(CHARGE_AUTHORIZATION, TRUE);
				/*%C Update  Charge phase in power supply base */
				DB_PowerSupply_Write(INIT_CHARGEUR_FAIL,FALSE);
				/*%C Update  Charge phase in Control base */	
				DB_Control_Write(INIT_BAT_STATE,FALSE); 
				/*%C Reset of index */
				PointNb = 0;
			}
			/*%C When there's more than 99 computed values of PWM ( & good measure) */
			else
			{
				/*%C Erazing counter for PWM average */
				PointNb = 0;
			}
		}
		else
		{
			/* No Function */	
		}
		/*%C memorizing previous state of PWM V charge	*/
		Previous_PWM_Charge = PWM_VCHARGE ;	
	}
	/*%C When Time out is over */	
	else
	{
		/* Time_Out pour Init_Chargeur */

		/* commutation OFF Chargeur &  VCharge reglage*/
		SHUNT_DIODE_CHARGEUR = FALSE;
		COMMUT_CHARGEUR = FALSE;
		COMMUT_IFC = FALSE;
		/*%C Up dating Flags inBase Control & PowerSupply */
		DB_PowerSupply_Write(INIT_CHARGEUR_FAIL,TRUE);	
		DB_Control_Write(CHARGE_AUTHORIZATION, FALSE);
		DB_Control_Write(INIT_BAT_STATE,FALSE); 
		/*%C Erazing counter for PWM average */
		PointNb = 0;	
	}
}
