/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : PUST_ref_voltages.c                                                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/

/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                     Voltage Check routine                                */
/******************************************************************************/


#ifndef _TASKING
#include "LH_ST10F276.h"
#include <intrins.h>
#else
#include "regf276e.h"
#endif	 
#include "io_declare.h"
#include "typedef.h"
#include "enum.h"
 
#include "PUST_ref_voltages.h"

/* locate boot code to specific section */
#include "locate_boot_code.h"


/******************************************************************************/
/*%C                       Functionnal description :                          */
//*%C Checks reference voltages												  */
/*%C                                                                          */
/*%I  Input Parameter :                                                       */
/*%I		NONE									                          */
/*%IO Input/Output :                                                          */
/*%IO		NONE                                                              */
/*%O  Output Parameter :                                                      */
/*%O 		Error code		                                                  */
/******************************************************************************/
e_REF_VOLTAGE_CODE RefVoltagesCheck(void)
{
    e_REF_VOLTAGE_CODE rc = REF_VOLTAGE_ERR_OK;

	/*%C  Check CPU reference voltage */
	if ((ALIM_FAILURE_5VREF == 0) || (ALIM_FAILURE_10VREF == 0))
	{
		rc = REF_VOLTAGE_ERR_KO;
	}
	
    return (rc);
}