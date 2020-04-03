/******************************************************************************/
/*                                                                            */
/* Project Number :  RB0505                                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename	: DB_IHM_Read_Info_Access.c                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C        Functionnal description :  this function manages the read         */
/*%C        operation in the different bases function of DbType parameter     */
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter : 			Id                                    		  	*/
/*%I                    			DbType	                            		  	*/
/*%IO Input/Output Parameter : 	*Value        			                  		*/
/*%O 	Output Parameter : 			True/False 	                 				  		*/
/******************************************************************************/



/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/

#include "typedef.h"
#include "enum.h"
#include "structure.h"
#include "DB_Control.h"
#include "DB_Rtc.h"
#include "DRV_VarEeprom.h"
#include "DB_IHMAccessParaDatabase.h"
#include "DB_Compute.h"
#include "DB_AlarmStatus.h"
#include "DB_KeyboardEvent.h"
#include "DB_PowerSupply.h"
#include "DB_IHM_Read_Info_Access.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

UWORD16 DB_IHM_Read_Info_Access(UWORD16 *Value,
								UWORD16 Id,
								e_TYPE_OF_DB_TARGET DbType)
{
/* Function result declaration */
   UWORD16 Function_Result = FALSE;
   *Value = 0;

/*%C Base reading choice function of DbType */
	switch (DbType)
	{
		case ALARMS:
		{
            *Value = DB_AlarmInfoRead(Id);
			Function_Result = TRUE;
		}
			break;
		default:
		{
			Function_Result = DB_IHM_Read_Access(Value, Id, DbType);
		}
			break;
	}
	return(Function_Result);
}


