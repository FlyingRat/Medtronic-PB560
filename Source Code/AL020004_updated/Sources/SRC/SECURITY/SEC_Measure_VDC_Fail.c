/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_Measure_VDC_Fail.c                                    	  */
/*													 						  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C               Detection of DC supply default		    		      	  */
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
#include "DB_PowerSupply.h"
#include "DB_Measurement.h"
#include "DB_Control.h"
#include "SEC_VDCFailAlarms.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void SEC_Measure_VDC_Fail(void)
{
	UWORD16 SupplyState = DB_Control_Read(SUPPLY_STATE);
	UWORD16 MeasureVDC = DB_Measurement_Read(MEASURE_VDC);
	

/*%C If SUPPLY_STATE <> DC_SUPPLY and MEASURE_VDC > HIGH_VDC_LEVEL			  */
	if ( (MeasureVDC > HIGH_VDC_LEVEL)
  	  && (SupplyState != DC_SUPPLY))	
	{
/*%C 	Then FAILURE_MES_VDC_FLAG = TRUE 									  */
		DB_PowerSupply_Write(FAILURE_MES_VDC_FLAG,TRUE);
	}
/*%C Else if MEASURE_VDC <=  HIGH_VDC_LEVEL 								  */
	else if (MeasureVDC <= HIGH_VDC_LEVEL)
	{
/*%C 	Then FAILURE_MES_VDC_FLAG = FALSE 									  */
 		DB_PowerSupply_Write(FAILURE_MES_VDC_FLAG,FALSE);
	}
/*%C End if 																  */
}
