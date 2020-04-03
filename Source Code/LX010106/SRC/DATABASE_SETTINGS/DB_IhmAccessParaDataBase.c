/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_IhmAccessParaDataBase.c    				                  		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function schedules the different	*/
/*%C         operations in DataBase: read, write, increase, decrease values,	*/
/*%C         affectation to min, max and step values									*/
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter :				Id                                    		  	*/
/*%I                    			DbType                                		  	*/
/*%I                    			DataOperation                         		  	*/
/*%IO Input/Output Parameter : 	*Value  	        			                  	*/
/*%O 	Output Parameter : 			True/False 	                 				  		*/
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/

#include "typedef.h"
#include "enum.h"
#include "structure.h"
#include "DB_Current.h"
#include "DB_Control.h"
#include "DB_Rtc.h"
#include "DB_Config.h"
#include "DB_IhmAccessParaDataBase.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/


UWORD16 DB_IhmAccessParaDataBase(UWORD16 *Value,
											UWORD16 Id,
											e_TYPE_OF_DB_TARGET DbType,
											e_DATA_OPERATION DataOperation)
{
/* Function result declaration */
   UWORD16 Function_Result = FALSE;

/*%C Data operation choice: read, write, increase, decrease */
/*%C and config settings assignment to min, max and step values */

	switch (DataOperation)
	{
/*%C  Read settings operation function call*/
		case READ:
		{
			Function_Result = DB_IHM_Read_Access(Value,
			                                     Id,
			                                     DbType);
			break;
		}
/*%C  Read settings info operation function call*/ 
        case READ_INFO: 
        { 
            Function_Result = DB_IHM_Read_Info_Access(  Value, 
                                                        Id, 
                                                        DbType); 
            break; 
        } 

/*%C  Write settings operation function call*/
		case WRITE:
		{
			Function_Result = DB_IHM_Write_Access(Value,
			                                      Id,
			                                      DbType);
			break;
		}

/*%C  Write settings info operation function call*/ 
        case WRITE_INFO: 
        { 
            Function_Result = DB_IHM_Write_Info_Access( Value, 
                                                        Id, 
                                                        DbType); 
            break;
        }

/*%C  Increase settings operation function call*/
		case INCREASE:
		{
			Function_Result = DB_IHM_Increase_Access(Value,
			                                         Id,
			                                         DbType);
			break;
		}

/*%C  Decrease settings operation function call*/
		case DECREASE:
		{
			Function_Result = DB_IHM_Decrease_Access(Value,
			                                         Id,
			                                         DbType);
			break;
		}

/*%C  Config base settings assignment to their min value for*/
/*%C  sound level, brightness and curve values  */
/*%C  (Max pressure, max flow, max VT, max time)*/
		case MIN:
		{
			if(DbType == CONFIG)
			{
				if ( (Id == ADJUST_BRIGHTNESS_U16) 
				  || (Id == SOUND_LEVEL_SELECT_U16) 
				  || (Id == CURVE_MAX_PRESSURE_U16)
				  || (Id == CURVE_MAX_FLOW_U16)
				  || (Id == CURVE_MAX_VT_U16)
				  || (Id == CURVE_MAX_TIME_U16)
#if defined(SUPPORTAIR_M2) || defined(LEGENDAIR_XL2) || defined(LEGENDAIR_S2)
				  || (Id == ADJUST_FIO2)
#endif
				   )
				{
					*Value = cDB_TEST_CONFIG_DB[Id].mini;
					Function_Result = TRUE;
				}
				else
				{
					Function_Result = FALSE;
				}
			}
         else
         {
            Function_Result = FALSE;
         }

			break;
		} 


/*%C  Config base settings assignment to their max value for*/
/*%C  sound level, brightness and curve values  */
/*%C  (Curve max pressure, max flow, max VT, max time)*/
		case MAX:
		{
			if(DbType == CONFIG)
			{
				if ( (Id == ADJUST_BRIGHTNESS_U16) 
				  || (Id == SOUND_LEVEL_SELECT_U16) 
				  || (Id == CURVE_MAX_PRESSURE_U16)
				  || (Id == CURVE_MAX_FLOW_U16)
				  || (Id == CURVE_MAX_VT_U16)
				  || (Id == CURVE_MAX_TIME_U16) )
				{
					*Value = cDB_TEST_CONFIG_DB[Id].maxi;
					Function_Result = TRUE;
				}
			}
			break;
		} 


/*%C  Step value recovery for 						*/
/*%C  sound level, brightness and curve values  */
/*%C  (Max pressure, max flow, max VT, max time)*/
		case STEP:
		{
			if(DbType == CONFIG)
			{
				if ( (Id == ADJUST_BRIGHTNESS_U16) 
				  || (Id == SOUND_LEVEL_SELECT_U16) 
				  || (Id == CURVE_MAX_PRESSURE_U16)
				  || (Id == CURVE_MAX_FLOW_U16)
				  || (Id == CURVE_MAX_VT_U16)
				  || (Id == CURVE_MAX_TIME_U16) )
				{
					*Value = cDB_TEST_CONFIG_DB[Id].step;
					Function_Result = TRUE;
				}
			}
			break;
		} 

		default:
		{
			Function_Result = FALSE;
			break;
		}

	}
	return(Function_Result);
}
