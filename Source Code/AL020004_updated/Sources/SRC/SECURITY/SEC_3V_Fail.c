/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_3V_Fail.c                                               	  */
/*													 						  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C               Detection of 3 V supply default					      	  */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/

#include "typedef.h"
#include "enum.h"
#include "DB_PowerSupply.h"
#include "SEC_3VAlarms.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void SEC_3V_Fail(void)
{
UWORD16 Failure5vFlag = DB_PowerSupply_Read(FAILURE_5V_FLAG);
UWORD16 Failure24vFlag = DB_PowerSupply_Read(FAILURE_24V_FLAG);


/*%C if FAILURE_5V_FLAG = TRUE and FAILURE_24V_FLAG = TRUE, then 			  */
	if ( (Failure5vFlag == TRUE)
	  && (Failure24vFlag == TRUE) )	
	{
/*%C    FAILURE_3V_FLAG = TRUE 												  */
		DB_PowerSupply_Write(FAILURE_3V_FLAG,TRUE);
	}

/*%C Else if FAILURE_5V_FLAG = FALSE or FAILURE_24V_FLAG = FALSE, then 		  */
	else if ( (Failure5vFlag == FALSE)
	       || (Failure24vFlag == FALSE) )
	{
/*%C 	FAILURE_3V_FLAG = FALSE 											  */
 	 	DB_PowerSupply_Write(FAILURE_3V_FLAG,FALSE);
	}
/*%C End if 																  */
}
