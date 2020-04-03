/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_DIS_grBackLight.c 										  				*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                 	BackLight Level Intensity setting							*/
/******************************************************************************/
/*%I Input Parameter :  BackLight Level Intensity	                          	*/
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE       */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/

#include "typedef.h"
#include "enum.h"
#include "Driver_Display_Data.h"
#include "DRV_DIS_grBackLight.h"						 
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_DIS_grBackLight ( UWORD16 _Level )
{

	DRV_DIS_grWriteDisplay(grESC);
	DRV_DIS_grWriteDisplay('k');

	switch (_Level)
	{
		case SWITCH_OFF:
		{
			DRV_DIS_grWriteDisplay(BACKLIGHT_OFF);
	
		}
		break;

		case WEAK:	
		{
			DRV_DIS_grWriteDisplay(BACKLIGHT_WEAK);
		}			
		break;

		case SWITCH_ON:	
		{
			DRV_DIS_grWriteDisplay(BACKLIGHT_ON);
		}			
		break;

		default:
		{
			DRV_DIS_grWriteDisplay(BACKLIGHT_OFF);
		}			
		break; 	
	}
}