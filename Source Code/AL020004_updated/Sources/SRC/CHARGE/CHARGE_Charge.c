/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CHARGE_Charge.c                                                */
/*													 						  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                    Management of battery charge			  			  */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/

#include "p18f6622.h"
#include "IO_Declare.h"
#include "define.h"
#include "enum.h"
#include "typedef.h"
#include "DB_PowerSupply.h"
#include "DB_Config.h"
#include "DB_Control.h"
#include "DB_Measurement.h"
#include "CHARGE_Data.h"
#include "CHARGE_Charge.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void CHARGE_Charge(void)
{

	UWORD16 VentilAuthorization
						= DB_PowerSupply_Read(VENTIL_AUTHORIZATION);
	UWORD16 MaintenanceMode
						= DB_PowerSupply_Read(MAINTENANCE_MODE);
	UWORD16 CommunicationFailureFlag
						= DB_PowerSupply_Read(COMMUNICATION_FAILURE_FLAG);
	UWORD16 AbnormalIBatFlag
						= DB_PowerSupply_Read(ABNORMAL_IBAT_FLAG);
	UWORD16 AmbientTempTooHigh
						= DB_PowerSupply_Read(AMBIENT_TEMP_TOO_HIGH);
	UWORD16 NoCommunicationCpu
						= DB_PowerSupply_Read(NO_COMMUNICATION_CPU);
	SWORD16 Ibat_Average 
						= DB_Measurement_Read(IBAT_AVERAGE);
	UWORD16 CpuOn 	= DB_Control_Read(CPU_ON);

	UBYTE Pwm_Icharge = 0;	
	UWORD16 IChargeSetPoint = 0;


	
/*%C To compute the charge cumul the current must be positive			  	  */
/*%C If IBAT_AVERAGE < 0 then IBAT_AVERAGE = - IBAT_AVERAGE				  	  */
	if( Ibat_Average < 0 )
	{
		Ibat_Average = -Ibat_Average;
	}
/*%C End if 																  */	
/*%C If VENTIL_AUTHORIZATION = TRUE or MAINTENANCE_MODE = TRUE 				  */
/*%C Or COMMUNICATION_FAILURE_FLAG = TRUE or 						    	  */
/*%C (NO_COMMUNICATION_CPU = TRUE and  CPU_ON = TRUE) or 					  */
/*%C ABNORMAL_IBAT_FLAG = TRUE or  AMBIENT_TEMP_TOO_HIGH = TRUE, then		  */

	if((VentilAuthorization == TRUE) 
		|| (MaintenanceMode == TRUE)		
		||	(CommunicationFailureFlag == TRUE)	
		|| ((NoCommunicationCpu == TRUE) 
		&& (CpuOn == TRUE))
		||	(AbnormalIBatFlag == TRUE)					
		||	(AmbientTempTooHigh == TRUE))
	{
/*%C I Charge setpoint : 500 mA 											  */
		Pwm_Icharge = ICHARGE_SETPOINT_MIN ;
		IChargeSetPoint = 5000;
	}

/*%C Else if COMMUNICATION_FAILURE_FLAG = FALSE and 						  */
/*%C VENTIL_AUTHORIZATION = FALSE and MAINTENANCE_MODE = FALSE 		  		  */
/*%C or (NO_COMMUNICATION_CPU = FALSE and CPU_ON = FALSE), then		  		  */
	else if ((CommunicationFailureFlag == FALSE)		
				&&	((VentilAuthorization == FALSE)
				&& (MaintenanceMode == FALSE))
				|| ((NoCommunicationCpu == TRUE) 
				&& (CpuOn == FALSE)))
	{
/*%C Pwm_Icharge = ICHARGE_SETPOINT_MAX, I Charge setpoint = 1500 mA 		  */
		Pwm_Icharge = ICHARGE_SETPOINT_MAX ;
		IChargeSetPoint = 15000;
	}
/*%C End if 																  */
/* Commuter le chargeur et appliquer le PWM 								  */
/*%C Charge On commutation 													  */
/*%C With selected setpoint (ICHARGE_SETPOINT = IChargeSetPoint)			  */
	PWM_ICHARGE = Pwm_Icharge;
	DB_Config_Write(ICHARGE_SETPOINT, IChargeSetPoint);
	SHUNT_DIODE_CHARGEUR = TRUE;
	COMMUT_CHARGEUR = TRUE;
	COMMUT_IFC = FALSE;

/*%C If the current measure is avalaible (delay between to acquisition is reached)*/
 	if (TIM_ReadValue16(SYS_COULOMB_COMPUTE_DELAY) == 0)
	{
/*%C 	Then Run timer to acquire measure 									  */
 		TIM_StartDecounter16(SYS_COULOMB_COMPUTE_DELAY
										, TIME_COULOMB_COMPUTE_DELAY);
/*%C Add measure 								 							  */
		CumulChargeCurrent = CumulChargeCurrent
								+ (((UWORD32)Ibat_Average * 100) / 60);
	}
/*%C End if 																  */	
}
