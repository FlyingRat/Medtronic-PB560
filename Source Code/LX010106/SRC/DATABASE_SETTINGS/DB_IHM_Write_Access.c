/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_IHM_Write_Access.c			    			                  		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function manages the writing		*/
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
#include "DRV_VarEeprom.h"
#include "DB_Event.h" 
#include "DB_AlarmStatus.h"
#include "DB_IHM_Write_Access.h"
#include "DB_IhmAccessParaDataBase.h"
#include "DB_KeyboardEvent.h"
#include "DB_PowerSupply.h"
#include "DB_Usb.h"
#include "DB_Compute.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

UWORD16 DB_IHM_Write_Access(UWORD16 *Value,
									 UWORD16 Id,
									 e_TYPE_OF_DB_TARGET DbType)
{
/* Function result declaration */
   UWORD16 Function_Result = FALSE;
   UWORD16 Limit_Flag_Number = Start_Limit_Setting;
   static UWORD16 First_Time_Rtc = TRUE;

/* Current mode recovery*/
   e_MODE_TYPES ActualMode = VOL;
   ActualMode = EEP_DB_Config[ADJUST_MODE_U16];

   switch (DbType)
   {
/*%C	Adjust base writing */
		case ADJUST:
		{
   		switch (ActualMode)
   		{
#ifdef CONFIG_VOL_MODE
/*%C			Adjust base write function call for the VOL mode*/
      		case VOL:
				{
					Function_Result = DB_IHM_Write_Adjust_Vol_Mode(Value,
																				  Id);

					break;
      		}
#endif
/*%C			Adjust base write for function call for the PRES mode*/
				case PRES:
				{
					Function_Result = DB_IHM_Write_Adjust_Pres_Mode(Value,
																				   Id);
					break;
      		}

/*%C			Adjust base write for function call for the PSV mode*/
				case PSVT:
				{
					Function_Result = DB_IHM_Write_Adjust_Psv_Mode(Value,
																				  Id);
					break;
      		}

/*%C			Adjust base write for function call for the CPAP mode*/
				case CPAP:
				{
					Function_Result = DB_IHM_Write_Adjust_Cpap_Mode(Value,
																				  Id);
					break;
      		}
#ifdef CONFIG_SIMV_MODE
/*%C			Adjust base write function call for the VSIMV mode*/
				case VSIMV:
				{
					Function_Result = DB_IHM_Write_Adjust_Vsimv_Mode(Value,
																				    Id);
 					break;
			   }
/*%C			Adjust base write function call for the VSIMV mode*/
				case PSIMV:
				{
					Function_Result = DB_IHM_Write_Adjust_Psimv_Mode(Value,
																					Id);
					break;
			   }
#endif
				default:
				{
					Function_Result = FALSE;
					break;
				}
			}
/*%C	   Setting event management */
		   if (EventNumber[Id] != NO_EVENT)
		   {
			  DB_EventMngt(EventNumber[Id]);
				Function_Result = TRUE;
		   }

		   break;
		}
/*%C	Config base writing */
		case CONFIG:
		{
/*%C	   Curves representation choice, when the WOB is activated,*/
/*%C	   the histogram representation is forbidden.              */
		   if ( (Id == CURVE_DISPLAY_TYPE_MODE_U16)
			 && (*Value == TRUE) )
			{
/*      	   Write value in config base              */
			DB_WriteDataInEepAndRam(&EEP_DB_Config[CURVE_DRAW_MODE_U16],0);

			DB_WriteDataInEepAndRam(&EEP_DB_Config[Id], *Value);
			}
		   else if (Id == ADJUST_FIO2)
			{
/*      	   Write value function call              */
				Function_Result = DB_IHM_Write_Config_Adjust_Fio2(Value);
/*%C	   	FiO2 Setting event management */
				DB_EventMngt(EVENT_MODIF_FIO2);
			}
		   else if (Id == PRESSURE_SUPPORT_RELATIVE_U16)
			{
/*      	   Write value in config base              */
				DB_WriteDataInEepAndRam(&EEP_DB_Config[Id]
										,*Value);
				DB_WriteDataInEepAndRam(&EEP_DB_Config[PRESSURE_SUPPORT_CHANGED_U16]
										,TRUE);
										
			}
/*%C	   Others writing in the config base*/
			else
		 {
				DB_WriteDataInEepAndRam(&EEP_DB_Config[Id],
												*Value);

/*%C 			Event recorded if previous mode is different from active mode		*/
				if ( (Id == ADJUST_MODE_U16)
				  && (*Value != MemoMode ) )
				{
					DB_EventMngt(EVENT_MODIF_MODE);
					MemoMode = *Value;
				}
				else if (Id == ADJUST_LOW_FIO2)
				{
					DB_EventMngt(EVENT_MODIF_FIO2_MINI);
				}
				else if (Id == ADJUST_HIGH_FIO2)
				{
					DB_EventMngt(EVENT_MODIF_FIO2_MAXI);
				}
				else if (Id == ADJUST_LOW_SPO2)
				{
					DB_EventMngt(EVENT_MODIF_SPO2_MINI);
				}
				else if (Id == ADJUST_HIGH_SPO2)
				{
					DB_EventMngt(EVENT_MODIF_SPO2_MAXI);
				}
		}
			if (Id == SOUND_LEVEL_SELECT_U16)
			{
				DB_ConfigWrite(PREVIOUS_SOUND_LEVEL_SELECT_U16,
									EEP_DB_Config[SOUND_LEVEL_SELECT_U16]);
			}
		 Function_Result = TRUE;
			break;
		}

/*%C	Control base writing*/
		case CONTROL:
		{
			DB_Control[Id] = *Value;
/*%C	   If there is a mode change, an event is sent */
			if ( (Id == CURRENT_MODE_U16)
			  && (*Value != (UWORD16) MemoMode) )
			{
				DB_EventMngt(EVENT_MODIF_MODE);
/*	         Mode memorization */
				MemoMode = *Value;
			}
			Function_Result = TRUE;
			break;
		}

/*%C	Alarm base writing*/
		case ALARMS:
		{
            DB_AlarmStatusWrite(Id, *Value);
			Function_Result = TRUE;
			break;
		}

/*%C	RTC base writing*/
		case RTC:
		{
			DB_Rtc[Id] = *Value;
/*%C	   February and leap year management  */
         if (DB_Rtc[ADJUST_RTC_MONTH_U16] == FEBRUARY)
         {
            if (DB_Rtc[ADJUST_RTC_DAY_U16] >= 29)
            {
               if (DB_Rtc[ADJUST_RTC_YEAR_U16] % 4 == 0)
               {
                  DB_Rtc[ADJUST_RTC_DAY_U16] = 29;
                  DB_Rtc[DB_RTC_DAY_U16] = 29;
               }
               else
               {
                  DB_Rtc[ADJUST_RTC_DAY_U16] = 28;
                  DB_Rtc[DB_RTC_DAY_U16] = 28;
               }
            }
         }
/*%C	   30 days month management  */
         else if ( (DB_Rtc[ADJUST_RTC_DAY_U16] > 30)
                && ( (DB_Rtc[ADJUST_RTC_MONTH_U16] == APRIL)
                  || (DB_Rtc[ADJUST_RTC_MONTH_U16] == JUNE)
                  || (DB_Rtc[ADJUST_RTC_MONTH_U16] == SEPTEMBER)
                  || (DB_Rtc[ADJUST_RTC_MONTH_U16] == NOVEMBER) ) )
         {
            DB_Rtc[ADJUST_RTC_DAY_U16] = 30;
            DB_Rtc[DB_RTC_DAY_U16] = 30;
         }

/*%C 		Validation short beep (do not take account of the first writing)		*/
			if ( (Id == ADJUST_RTC_YEAR_U16)
			  || (Id == ADJUST_RTC_SECOND_U16) )
			{
				if (First_Time_Rtc == FALSE)
				{
/*%C 				Validation short beep 														*/
					DB_ControlWrite(VALIDATION_BIP_U16,
						 		 	 	BIP_SHORT_VALID);
					First_Time_Rtc = TRUE;
				}
				else
				{
					First_Time_Rtc = FALSE;
				}
			}
			Function_Result = TRUE;
			break;
		} 

/*%C	KEYBOARD base writing*/
		case KEYBOARD:
		{
			DB_KeyboardEvent[Id] = *Value;
			Function_Result = TRUE;
			break;
		} 

/*%C  Power Supply base writing*/
		case POWER_SUPPLY:
		{
			DB_powerSupply[Id] = *Value;
			Function_Result = TRUE;
			break;
		}

/*%C  USB base writing*/
		case USB:
		{
			DB_Usb[Id] = *Value;
			Function_Result = TRUE;
			break;
		}

/*%C  COMPUTE base writing*/
		case COMPUTE:
		{
			DB_Compute[Id] = *Value;
			Function_Result = TRUE;
			break;
		}

      /*%C  VERSION base writing*/
		case VERSION:
		{
         	DB_WriteDataInEepAndRam(&EEP_DB_Version_Number[Id], *Value);
			Function_Result = TRUE;
			break;
		}

      /*%C  TREND base writing*/
		case TREND:
		{
         	DB_WriteDataInEepAndRam(&EEP_DB_TREND[Id], *Value);
			Function_Result = TRUE;
			break;
		}

		default:
		{
			Function_Result = FALSE;
			break;
		}
	} 
/*%C IHM Limit flag desactivation (time out case)*/
   for (Limit_Flag_Number = Start_Limit_Setting +1; Limit_Flag_Number <End_Limit_Setting; Limit_Flag_Number++)
   {
      DB_ControlWrite(Limit_Flag_Number, FALSE);
   }
	return(Function_Result);
}


