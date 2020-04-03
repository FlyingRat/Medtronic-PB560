
/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_IHM_Setting_Rtc_Day.c   		 			                  		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function manages the day settings	*/
/*                                                            				  		*/
/******************************************************************************/
/*%I Input Parameter :				Id                                    		  	*/
/*%IO Input/Output Parameter : 	*Value  	        			                  	*/
/*%O Output Parameter : 			True/False 	                 				  		*/
/******************************************************************************/

			 
/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/

#include "typedef.h"
#include "enum.h"
#include "structure.h"
#include "DB_Rtc.h"
#include "DB_Current.h"
#include "DB_Config.h"
#include "DB_Event.h"
#include "DB_IhmAccessParaDatabase.h"
#include "DRV_VarEeprom.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

UWORD16 DB_IHM_Setting_Rtc_Day(UWORD16 *Value)
{
UWORD16 Max_Day_Number = 31;

/*%C Max day number setting                             */
/*%C Max day number for February                              */
   if (DB_Rtc[ADJUST_RTC_MONTH_U16] == FEBRUARY)
   {
/*%C  Leap year                              */
      if (DB_Rtc[ADJUST_RTC_YEAR_U16] % 4 == 0)
      {
         Max_Day_Number = 29;
      }
      else
      {
         Max_Day_Number = 28;
      }
   }
/*%C  30 day months                               */
   else if ( (DB_Rtc[ADJUST_RTC_MONTH_U16] == APRIL)
          || (DB_Rtc[ADJUST_RTC_MONTH_U16] == JUNE)
          || (DB_Rtc[ADJUST_RTC_MONTH_U16] == SEPTEMBER)
          || (DB_Rtc[ADJUST_RTC_MONTH_U16] == NOVEMBER) )
	{
      Max_Day_Number = 30;
	}
/*%C 31 day months                               */
	else
	{
      Max_Day_Number = 31;
	}

/*%C Day setting                               */
/*%C Value < 1 => Value set to the max         */
   if ( (*Value < cDB_TEST_RTC_DB[ADJUST_RTC_DAY_U16].mini)
     || (*Value > cDB_TEST_RTC_DB[ADJUST_RTC_DAY_U16].maxi +
                  cDB_TEST_RTC_DB[ADJUST_RTC_DAY_U16].step) )
   {
      *Value = Max_Day_Number;
   }
/*%C Value > max day number => Value set to the min         */
   else if (*Value > Max_Day_Number)
   {
      *Value = 1;
   }

	return (TRUE);
}  


 