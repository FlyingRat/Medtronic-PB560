/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_COM_Receive_ID.c                                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C       		  Write in the version base the serial number						*/
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
#include "DRV_COM_Data.h"
#include "DRV_COM_Receive_ID.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void DRV_COM_Receive_ID(void)
{
	UWORD16 Compute_U16 = 0 ;

		
	Compute_U16 = (UWORD16)DRV_COM_Receive_ID_Buffer[0];
	Compute_U16 = (Compute_U16 << 8) | ((UWORD16)DRV_COM_Receive_ID_Buffer[1] & 0x00FF);
	DB_VersionWrite(SERIAL_NUMBER_1, Compute_U16);

	Compute_U16 = (UWORD16)DRV_COM_Receive_ID_Buffer[2];
	Compute_U16 = (Compute_U16 << 8) | ((UWORD16)DRV_COM_Receive_ID_Buffer[3] & 0x00FF);
	DB_VersionWrite(SERIAL_NUMBER_2, Compute_U16);

	Compute_U16 = (UWORD16)DRV_COM_Receive_ID_Buffer[4];
	Compute_U16 = (Compute_U16 << 8) | ((UWORD16)DRV_COM_Receive_ID_Buffer[5] & 0x00FF);
	DB_VersionWrite(SERIAL_NUMBER_3, Compute_U16);

	Compute_U16 = (UWORD16)DRV_COM_Receive_ID_Buffer[6];
	Compute_U16 = (Compute_U16 << 8) | ((UWORD16)DRV_COM_Receive_ID_Buffer[7] & 0x00FF);
	DB_VersionWrite(SERIAL_NUMBER_4, Compute_U16);

	Compute_U16 = (UWORD16)DRV_COM_Receive_ID_Buffer[8];
	Compute_U16 = (Compute_U16 << 8) | ((UWORD16)DRV_COM_Receive_ID_Buffer[9] & 0x00FF);
	DB_VersionWrite(SERIAL_NUMBER_5, Compute_U16);

	Compute_U16 = (UWORD16)DRV_COM_Receive_ID_Buffer[10];
	Compute_U16 = (Compute_U16 << 8) | ((UWORD16)DRV_COM_Receive_ID_Buffer[11] & 0x00FF);
	DB_VersionWrite(SERIAL_NUMBER_6, Compute_U16);


	Communication_State = COM_TRANSMIT_STOP;

}
