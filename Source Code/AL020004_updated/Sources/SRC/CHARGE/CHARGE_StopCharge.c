/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CHARGE_StopCharge.c                                            */
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
#include "enum.h"
#include "DB_Control.h"
#include "DB_PowerSupply.h"
#include "CHARGE_Data.h"
#include "CHARGE_StopCharge.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void CHARGE_StopCharge(void)
{
	/*%C StopCharge Commutation  */
	SHUNT_DIODE_CHARGEUR = FALSE;
	COMMUT_CHARGEUR = FALSE;
	COMMUT_IFC = FALSE;
	/*%C Updating Charge flags in data base Power supply & Control */
	Init_Chargeur_Autorisation = FALSE ;
	DB_Control_Write(CHARGE_AUTHORIZATION, FALSE);

}
