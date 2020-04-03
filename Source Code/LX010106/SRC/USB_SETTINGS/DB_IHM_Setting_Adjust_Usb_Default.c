/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Usb_Default.c            	       		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function controls the limits		*/
/*%C        of Default setting             	     							         */
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

/******************************************************************************/
/*                                FUNCTION BODY		                          	*/
/******************************************************************************/

UWORD16 DB_IHM_Setting_Adjust_Usb_Default(UWORD16 *Value, UWORD16 Id)
{

/* Function result declaration */
   UWORD16 Function_Result = FALSE;
   UWORD16 OverFlowlimit;

/*%C Limit tests */
/*%C Down Limit test */
   if (*Value < cDB_TEST_USB_DB[Id].mini)
	{
      *Value = cDB_TEST_USB_DB[Id].maxi;
		Function_Result = FALSE;
	}
/*%C Up Limit test */
   else if (*Value > cDB_TEST_USB_DB[Id].maxi)
   {
      /*%C Overflow */
      OverFlowlimit = cDB_TEST_USB_DB[Id].mini - cDB_TEST_USB_DB[Id].step;
      if(*Value == OverFlowlimit)
      {
        *Value = cDB_TEST_USB_DB[Id].maxi;
      }
      else
      {
         *Value = cDB_TEST_USB_DB[Id].mini;
      }
      Function_Result = FALSE;
   }
   else
   {
/*%C  Setting authorized */
      Function_Result = FALSE;
   }

	return(Function_Result);
}
