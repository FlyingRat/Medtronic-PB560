/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Usb_Trend_Transfer.c    	       		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of Trend Transfer setting             	     							   */
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter :				Id                                    		  	*/
/*%IO Input/Output Parameter : 	*Value  	        			                  	*/
/*%O 	Output Parameter : 			True/False 	                 				  		*/
/******************************************************************************/


/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "structure.h"
#include "DB_Usb.h"
#include "DB_Current.h"
#include "DB_Config.h"
#include "DB_IhmAccessParaDataBase.h"

extern void DB_UsbWrite(e_DB_USB Id, UWORD16 Value);
extern UWORD16 DB_UsbRead(e_DB_USB Id);
/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Setting_Adjust_Usb_Trend_Transfer(UWORD16 *Value,
																   UWORD16 Id)
{

/* Function result declaration */
   UWORD16 Function_Result = FALSE;

/*%C Limit tests */
/*%C Down Limit test */
   if( (*Value <= cDB_TEST_USB_DB[Id].mini) ||
       (*Value > cDB_TEST_USB_DB[Id].maxi + cDB_TEST_USB_DB[Id].step) )
	{
/*%C  Value limited to its min */
      *Value = cDB_TEST_USB_DB[Id].mini;
/*%C  Flag writing by DB_UsbWrite function call 	*/
		DB_UsbWrite(USB_TREND_TRANSFER_SELECT_U16, (UWORD16) FALSE);
 		Function_Result = FALSE;
	}
/*%C Up Limit test */
   else if (*Value >= cDB_TEST_USB_DB[Id].maxi)
   {
/*%C  Value limited to its max */
      *Value = cDB_TEST_USB_DB[Id].maxi;
      Function_Result = FALSE;
   }
/*%C If "select flag cancelled"  => "select flag" activated */
	else if ((e_BOOL) DB_UsbRead(USB_TREND_TRANSFER_SELECT_U16) == FALSE)
	{
/*%C  Flag writing by DB_UsbWrite function call 	*/
		DB_UsbWrite(USB_TREND_TRANSFER_SELECT_U16, (UWORD16) TRUE);
		Function_Result = FALSE;
	}
   else
   {
/*%C  Setting authorized */
      Function_Result = FALSE;
   }

	return(Function_Result);
}
