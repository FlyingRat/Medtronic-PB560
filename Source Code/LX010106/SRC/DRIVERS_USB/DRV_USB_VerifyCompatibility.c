/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505 				                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_USB_VerifyCompatibility.c												*/
/*																										*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C         																						*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/

#include "typedef.h"
#include "enum.h"
#include "DB_Config.h"
#include "DB_Usb.h"
#include "Driver_USB_Data.h"
#include "CRC16_Table.h"
#include "DRV_USB_VerifyCompatibility.h"
			
											
/******************************************************************************/
/*                   			FUNCTION BODY                    					*/
/******************************************************************************/
UWORD16 DRV_USB_VerifyCompatibility(void)
{

/******************************************************************************/
/*%C Local variables 																			*/
/******************************************************************************/
	
	UWORD16 ParamCompatibility = DB_ConfigRead(PARAM_COMPATIBILITY);

	UWORD16 SettingsCompatible = 0 ;


	/*%C The settings are compatible */
	if((PEC_Reception[	SETTINGS_COMPATIBILITY
							+ 	5 
							+ 	End_of_e_usb_frame_serialNumberAndDate
							])
	  == (UBYTE)ParamCompatibility)
	{
		/*%C This is the same ventilateur */
		SettingsCompatible = TRUE ;
	}
	else if(
				((PEC_Reception[	
						SETTINGS_COMPATIBILITY
					+ 	5 
					+ 	End_of_e_usb_frame_serialNumberAndDate])
	  				== M2_IDENTIFIANT)
		&&		(ParamCompatibility 
					== XL2_IDENTIFIANT))
	{
		/*%C Supportair M2 is compatible with Legendair XL2 */
		SettingsCompatible = TRUE ;
	}
	else if(
				((PEC_Reception[SETTINGS_COMPATIBILITY + End_of_e_usb_frame_serialNumberAndDate + 5]) == M2_IDENTIFIANT)
		&&		(ParamCompatibility == S2_IDENTIFIANT)
		&&		((PEC_Reception[SETTINGS_MODE + End_of_e_usb_frame_serialNumberAndDate + 5]) != COM_VOL_A)
		&&		((PEC_Reception[SETTINGS_MODE + End_of_e_usb_frame_serialNumberAndDate + 5]) != COM_VOL_C)
		&&		((PEC_Reception[SETTINGS_MODE + End_of_e_usb_frame_serialNumberAndDate + 5]) != COM_VSIMV)
		&&		((PEC_Reception[SETTINGS_MODE + End_of_e_usb_frame_serialNumberAndDate + 5]) != COM_PSIMV))
	{
		/*%C Supportair M2 is compatible with Legendair S2 */
		/*%C If mode is different than VOL */
		SettingsCompatible = TRUE ;
	}
	/*%C Settings are not compatible */
	else
	{
		SettingsCompatible = FALSE ;
	}
   return(SettingsCompatible);
}
