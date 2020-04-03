/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_Gas_Gauge_Minute.c                         		  		  		*/
/*													 						  							*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                    % Gauge management     								  			*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/

#include "typedef.h"
#include "define.h"
#include "DB_PowerSupply.h"
#include "DB_Measurement.h"
#include"SYS_Gauge_Data.h"
#include "SYS_Gas_Gauge_Minute.h"
/******************************************************************************/
/*                                FUNCTION BODY                               */
/******************************************************************************/
void SYS_Gas_Gauge_Minute(void)
{
	SWORD16 Ibat_Average = DB_Measurement_Read(IBAT_AVERAGE);
	UWORD16 BatCapacityCompensated = DB_PowerSupply_Read(BAT_CAPACITY_COMPENSATED);

	UWORD32 Compute = 0;
	UWORD16 Remain = 0;

	/*%C To compute the gauge minute, the current must be positive					*/
	if( Ibat_Average < 0 )
	{
		Ibat_Average = -Ibat_Average;
	}
	
	/*%C Convert Bat Capacity	10éme de mA / min											*/		
	Compute = (UWORD32) BatCapacityCompensated * 600 ;
	/*%C Remaining time computing
	/*%C Addition of a 0.94 corrective factor to compy with accuracy requirement */
	Compute = Compute * 94;
	Compute = Compute / 100;
	Compute = Compute / (UWORD32) Ibat_Average;
	
	/*%C Protect calcul, maxi value is 1440 minutes	(24 hours)						*/
	if (Compute > 1440) 
	{
		Compute = 1440;
	}
	/* Correction de la jauge en minute afin d'avoir une jauge pécimiste */
	/* Correctif apporté apres la production des  P4 */
	if(Compute >= SECURITY_OFFESET_GAUGE_MINUTE)
	{
		Compute = Compute - SECURITY_OFFESET_GAUGE_MINUTE;
	}
	else
	{
		Compute = 0;	
	}
	/*%C Update the computed gauge minute in Data base 								*/
	DB_PowerSupply_Write(GAUGE_MINUTE_U16,(UWORD16)Compute);
}
