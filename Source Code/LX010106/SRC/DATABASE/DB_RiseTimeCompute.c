/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_RiseTimeCompute.c 		   				                  		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function computes the rise time   */
/*%C value, fonction of rise level setting and respecting the condition :		*/
/*%C Ti < Rise time + 300 ms                                             		*/
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter : 			None		        			                  	*/
/*%IO Input/Output Parameter : 	None 	        			                  		*/
/*%O 	Output Parameter : 			None	                       				  		*/
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "DB_Control.h"
#include "DB_Event.h"
#include "DB_Rtc.h"
#include "DRV_VarEeprom.h"
#include "DB_Current.h"
#include "DB_RiseTimeCompute.h"
#include "DB_IhmAccessParaDataBase.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void DB_RiseTimeCompute(UWORD16 Current_Mode)
{
/* Rise time declaration (initialized to the min value)  */
   UWORD16 Rise_Time = 200;

/* Ti control declaration  */
   UWORD16 Adjust_Ti_Control = DB_CurrentRead(ADJUST_TI_CONTROL_U16);

   UWORD16 Ti_Min_Auto_Select = EEP_DB_PSV_Adjust[TI_MIN_AUTO_SELECT_U16];

/*%C Rise time choice function of current mode */		   
   switch (Current_Mode)
	{
/*%C  Rise time recovery in PRES mode */		   
      case PRES:
		{
		   Rise_Time = RiseTime[EEP_DB_PRES_Adjust[ADJUST_RISE_TIME_U16] - 1];

/*%C 		Rise time limitation (Ti < Rise time + 300 ms )  */
		   if (Adjust_Ti_Control <= Rise_Time + cDELTA_RISE_TIME)
		   {
/*%C 			Rise time is limited to 600 ms   */
			   Rise_Time = RiseTime[2];   
		   }
		    
		   if (Adjust_Ti_Control <= Rise_Time + cDELTA_RISE_TIME)
		   {
/*%C  			Rise time is limited to 400 ms   */
			   Rise_Time = RiseTime[1];   
		   }
		    
		   if (Adjust_Ti_Control <= Rise_Time + cDELTA_RISE_TIME)
		   {
/*%C  			Rise time is limited to 200 ms   */
			   Rise_Time = RiseTime[0];   
		   }
			break;
		}
/*%C  Rise time recovery in VSIMV mode */		   
      case VSIMV:
		{
		   Rise_Time = RiseTime[EEP_DB_VSIMV_Adjust[ADJUST_RISE_TIME_U16] - 1];

/*%C 		Rise time limitation (Ti < Rise time + 300 ms )  */
		   if (Adjust_Ti_Control <= Rise_Time + cDELTA_RISE_TIME)
		   {
/*%C  			Rise time is limited to 600 ms   */
			   Rise_Time = RiseTime[2];   
		   }
		    
		   if (Adjust_Ti_Control <= Rise_Time + cDELTA_RISE_TIME)
		   {
/*%C  			Rise time is limited to 400 ms   */
			   Rise_Time = RiseTime[1];   
		   }
		    
		   if (Adjust_Ti_Control <= Rise_Time + cDELTA_RISE_TIME)
		   {
/*%C  			Rise time is limited to 200 ms   */
			   Rise_Time = RiseTime[0];   
		   }
			break;
		}
/*%C  Rise time recovery in PSIMV mode */		   
      case PSIMV:
		{
		   Rise_Time = RiseTime[EEP_DB_PSIMV_Adjust[ADJUST_RISE_TIME_U16] - 1];

/*%C 		Rise time limitation (Ti < Rise time + 300 ms )  */
		   if (Adjust_Ti_Control <= Rise_Time + cDELTA_RISE_TIME)
		   {
/*%C  			Rise time is limited to 600 ms   */
			   Rise_Time = RiseTime[2];   
		   }
		    
		   if (Adjust_Ti_Control <= Rise_Time + cDELTA_RISE_TIME)
		   {
/*%C  			Rise time is limited to 400 ms   */
			   Rise_Time = RiseTime[1];   
		   }
		    
		   if (Adjust_Ti_Control <= Rise_Time + cDELTA_RISE_TIME)
		   {
/*%C  			Rise time is limited to 200 ms   */
			   Rise_Time = RiseTime[0];   
		   }
			break;
		}
/*%C  Rise time recovery in PSVT mode */		   
      case PSVT:
		{
		   Rise_Time = RiseTime[EEP_DB_PSV_Adjust[ADJUST_RISE_TIME_U16] - 1];
			/*%C Automatic mode test */
		   if (Ti_Min_Auto_Select == TRUE)
		   {
		/*%C  Ti Min writing (fixed to Adjust Rise Time + 300 ms) */
		      DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[ADJUST_TI_MIN_U16],
											   Rise_Time + cDeltaRiseTime);			
		   }
			break;
		}/*%C  Rise time is not modified */		   
      default:
		{
			break;
		}
   } 

/*%C Rise time writing in current base   */
   DB_CurrentWrite(RISE_TIME_U16,
	                Rise_Time);
} 