/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_IHM_Decrease_Access.c   		 			                  		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function manages the increment		*/
/*%C        operation in the different bases function of DbType parameter		*/
/*                                                            				  		*/
/******************************************************************************/
/*%I Input Parameter :				Id                                    		  	*/
/*%I                    			DbType                                		  	*/
/*%I                    			DataOperation                         		  	*/
/*%IO Input/Output Parameter : 	*Value  	        			                  	*/
/*%O Output Parameter : 			True/False 	                 				  		*/
/******************************************************************************/


			 
/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/

#include "typedef.h"
#include "enum.h"
#include "structure.h"
#include "DB_Control.h"
#include "DB_Rtc.h"
#include "DB_Usb.h"
#include "DRV_VarEeprom.h"
#include "DB_IhmAccessParaDataBase.h"
#include "DB_Current.h"
#include "DB_IHM_Setting_Adjust_Usb.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

UWORD16 DB_IHM_Decrease_Access(UWORD16 *Value,
									  	 UWORD16 Id,
									  	 e_TYPE_OF_DB_TARGET DbType)
{

/*%C Function result declaration */
   UWORD16 Function_Result = FALSE;

/* Adjust mode declaration */
   UWORD16 Adjust_Mode = VOL;

/* Adjust mode recovery */
   Adjust_Mode = EEP_DB_Config[ADJUST_MODE_U16];
    

/*%C Database choice  to increase */
	switch (DbType)
	{
/*%C  Adjust base decrease */
		case ADJUST:
		{

			switch (Adjust_Mode)
			{
#ifdef CONFIG_VOL_MODE
				case VOL:
				{
/*%C				Value recovery and decrease operation for the VOL base*/
               *Value = *Value -	cDB_VOL_TEST_ADJUST_DB[Id].step;

/*%C				Parameter setting function call in the VOL mode*/
			   	Function_Result = DB_IHM_Setting_Adjust_Vol_Mode(Value,
																					 Id);
/*%C				Value recovery and decrease operation for the VOL base*/
               if(Function_Result == TRUE)
               {
                  *Value = *Value +	cDB_VOL_TEST_ADJUST_DB[Id].step;
               }
					break;
		    	}
#endif
				case PRES:
				{
/*%C				Value recovery and decrease operation for the PRES base*/
               *Value = *Value - cDB_PRES_TEST_ADJUST_DB[Id].step;

/*%C				Parameter setting function call in the PRES mode*/
			   	Function_Result = DB_IHM_Setting_Adjust_Pres_Mode(Value,
																					  Id);
/*%C				Value recovery and decrease operation for the PRES base*/
               if(Function_Result == TRUE)
               {
                  *Value = *Value +	cDB_PRES_TEST_ADJUST_DB[Id].step;
               }
					break;
		    	}

				case PSVT:
				{
/*%C				Value recovery and decrease operation for the PSV base*/
               *Value = *Value - cDB_PSV_TEST_ADJUST_DB[Id].step;

/*%C				Parameter setting function call in the PSV mode*/
			   	Function_Result = DB_IHM_Setting_Adjust_Psv_Mode(Value,
																					 Id);
/*%C				Value recovery and decrease operation for the PSV base*/
               if(Function_Result == TRUE)
               {
                  *Value = *Value +	cDB_PSV_TEST_ADJUST_DB[Id].step;
               }
					break;
		    	}
            case CPAP:
				{
/*%C				Value recovery and decrease operation for the CPAP base*/
               *Value = *Value - cDB_CPAP_TEST_ADJUST_DB[Id].step;

/*%C				Parameter setting function call in the PSV mode*/
			   	Function_Result = DB_IHM_Setting_Adjust_Cpap_Mode(Value,
																					 Id);
/*%C				Value recovery and decrease operation for the CPAP base*/
               if(Function_Result == TRUE)
               {
                  *Value = *Value +	cDB_CPAP_TEST_ADJUST_DB[Id].step;
               }
					break;
		    	}
#ifdef CONFIG_SIMV_MODE
				case VSIMV:
				{
/*%C				Value recovery and decrease operation for the VSIMV base*/
               *Value = *Value - cDB_VSIMV_TEST_ADJUST_DB[Id].step;

/*%C				Parameter setting function call in the VSIMV mode*/
			   	Function_Result = DB_IHM_Setting_Adjust_Vsimv_Mode(Value,
																						Id);
/*%C				Value recovery and decrease operation for the VSIMV base*/
               if(Function_Result == TRUE)
               {
                  *Value = *Value +	cDB_VSIMV_TEST_ADJUST_DB[Id].step;
               }
					break;
				}
/*%C				Value recovery and decrease operation for the PSIMV base*/
				case PSIMV:
				{
/*%C				Value recovery and decrease operation for the PSIMV base*/
			   *Value = *Value - cDB_PSIMV_TEST_ADJUST_DB[Id].step;

/*%C				Parameter setting function call in the PSIMV mode*/
				Function_Result = DB_IHM_Setting_Adjust_Psimv_Mode(Value,
																						Id);
/*%C				Value recovery and decrease operation for the PSIMV base*/
			   if(Function_Result == TRUE)
			   {
				  *Value = *Value +	cDB_PSIMV_TEST_ADJUST_DB[Id].step;
			   }
					break;
				}
#endif
				default:
				{
			   	Function_Result = FALSE;
					break;
		    	}
			}
		break;
		}
/*%C  Config base decrease */
		case CONFIG:
		{
			Function_Result = DB_IHM_Decrease_Config(Value,
																  Id);
			break;
		}  

/*%C  RTC base decrease */
		case RTC:
		{
         if (Id == ADJUST_RTC_DAY_U16)
         {
            *Value = *Value - cDB_TEST_RTC_DB[Id].step;
/*%C 		   Day setting function call */
			   Function_Result = DB_IHM_Setting_Rtc_Day(Value);
         }
/*%C 		Month and year settings (rolling values) */
         else
         {
            if (*Value >= (cDB_TEST_RTC_DB[Id].mini +
			                  cDB_TEST_RTC_DB[Id].step))
            {
               *Value = *Value - cDB_TEST_RTC_DB[Id].step;
            }
            else
            {
               *Value = cDB_TEST_RTC_DB[Id].maxi;
            }
			   Function_Result = TRUE;
         }
			break;
		}
/*%C  USB base decrease */
		case USB:
		{
/* for USB monitoring transfert, the step is 4 until 24 and after it is 12*/
		if(Id == USB_MONITOR_TRANSFER_U16)
		{
			if(*Value <= cUSB_MONIT_THRESHOLD_FOR_NEW_STEP)
			{
/*%C     Value recovery and decrease operation for the USB base*/
         *Value = *Value - cDB_TEST_USB_DB[Id].step;
			}
			else
			{
/*%C     Value recovery and decrease operation for the USB base*/
	         *Value = *Value - cUSB_MONIT_NEW_STEP;
			}
		}
		else
		{
/*%C     Value recovery and decrease operation for the USB base*/
         *Value = *Value - cDB_TEST_USB_DB[Id].step;
		}

/*%C     Parameter setting function call */
         Function_Result = DB_IHM_Setting_Adjust_Usb(Value,	Id);

/*%C     Value recovery and decrease operation for the USB base*/
         if(Function_Result == TRUE)
         {
            *Value = *Value +	cDB_TEST_USB_DB[Id].step;
         }
         break;
		}
/*%C  CONTROL base decrease */
		case CONTROL:
		{
/*%C  Rolling menu for screen stand by (Max -> Min)									*/
			if (Id == RECORD_SETTINGS_USB_U16 ||
				 Id == APPLY_SETTINGS_USB_U16 ||
				 Id == ERASE_KEY_USB_U16)
			{
/*%C     	If value > min + step => value is decreased of one step 					*/
				if (*Value >= (cDB_TEST_CONTROL_DB[Id].mini +
								cDB_TEST_CONTROL_DB[Id].step) )
				{
					*Value = *Value - cDB_TEST_CONTROL_DB[Id].step;
					Function_Result = TRUE;
				}
/*%C     	else, value is set to its max													 	*/
				else
				{
					*Value = cDB_TEST_CONTROL_DB[Id].maxi;
					Function_Result = TRUE;
				}
			}
			else
			{
/*%C     	If value > min + step => value is decreased of one step 					*/
				if (*Value >= (cDB_TEST_CONTROL_DB[Id].mini +
								cDB_TEST_CONTROL_DB[Id].step) )
				{
					*Value = *Value - cDB_TEST_CONTROL_DB[Id].step;
					Function_Result = TRUE;
				}
/*%C     	else, value is set to its min													 	*/
				else
				{
					*Value = cDB_TEST_CONTROL_DB[Id].mini;
					Function_Result = FALSE;
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
