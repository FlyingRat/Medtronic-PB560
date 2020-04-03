/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Usb.c     	   	                 		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function manages the different		*/
/*%C        settings for an increase or a decrease operation in USB DataBase 	*/
/*%C        function of Id.									  		                  */
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
#include "DB_Usb.h"
#include "DB_IHM_Setting_Adjust_Usb_Monitor_Transfer.h"
#include "DB_IHM_Setting_Adjust_Usb_Trend_Transfer.h"
#include "DB_IHM_Setting_Adjust_Usb_Default.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

UWORD16 DB_IHM_Setting_Adjust_Usb(UWORD16 *Value, UWORD16 Id)
{
/* Function result declaration */
   UWORD16 Function_Result = FALSE;

/*%C Id choice for the limits check */
	switch (Id)
	{
		case USB_MONITOR_TRANSFER_U16:
		{
/*%C     Monitoring Transfer limits check function call */
			Function_Result = DB_IHM_Setting_Adjust_Usb_Monitor_Transfer(Value, Id);

			break;
		}

		case USB_TREND_TRANSFER_U16:
		{
/*%C     Trend Transfer limits check function call */
			Function_Result = DB_IHM_Setting_Adjust_Usb_Trend_Transfer(Value, Id);
			break;
		}

		default :
		{
/*%C     limits check function call for all other settings */
			Function_Result = DB_IHM_Setting_Adjust_Usb_Default(Value, Id);
			break;
		}
	}
	return (Function_Result);
}
