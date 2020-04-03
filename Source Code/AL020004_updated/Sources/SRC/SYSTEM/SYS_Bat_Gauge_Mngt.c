
/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_Bat_Gauge_Mngt.c                            		  		  */
/*													 						  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                    Gauge management     								  */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/

#include "typedef.h"
#include "define.h"
#include "enum.h"
#include "Gauge_Datas.h"
#include "DB_PowerSupply.h"
#include "DB_Control.h"
/******************************************************************************/
/*                                FUNCTION BODY                               */
/******************************************************************************/
void  SYS_Bat_Gauge_Mngt(void)
{
	UWORD32 ComputeU32;

	//	SYS_Total_Capacity_Bat
	ComputeU32 = SYS_Remaining_Impendance_Tension_Based_Capacity_Bat1;
	ComputeU32 = ComputeU32 * 100 / SYS_Total_Capacity_Bat1;
	//Limitation du pourcentage en charge 100% ne doit pas être atteind avant la fin de charge
	if ((DB_ControlRead(STATE) == CHARGE_BAT1_STATE) && (ComputeU32 > 99))
	{
		ComputeU32 = 99;
	}
	//limitation à 100% maximum
	if (ComputeU32 > 100)
	{
		ComputeU32  = 100;
	}
	DB_powerSupplyWrite(JAUGE_U16,(UWORD16)ComputeU32);

}
