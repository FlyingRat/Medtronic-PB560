/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_COM_Receive_Machine_Counter.c                                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C          			Write in the base control the machine counter				*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/

#include "typedef.h"
#include "DB_Control.h"
#include "DRV_COM_Data.h"
#include "DRV_COM_Receive_Machine_Counter.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void DRV_COM_Receive_Machine_Counter(void)
{
	UWORD16 Compute_U16 = 0;


	Compute_U16 =		(DRV_COM_Machine_Counter_Value_MSB << 8)
						|	(DRV_COM_Machine_Counter_Value_LSB & 0x00FF);

	DB_ControlWrite(CURRENT_MACHINE_COUNTER_HOUR_U16,	Compute_U16);

	Communication_State = COM_TRANSMIT_STOP;
		

}
