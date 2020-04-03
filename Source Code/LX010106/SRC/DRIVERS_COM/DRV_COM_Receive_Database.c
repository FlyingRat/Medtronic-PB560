/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_COM_Receive_Database.c                                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C          			 Write data from PC to Database									*/
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
#include "DRV_COM_Receive_Database.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void DRV_COM_Receive_Database(void)
{
	UWORD16 Compute_U16 = 0 ;
	UWORD16 Compute_CRC = 0;


	Compute_CRC = START_FRAME_COM_VALUE_1 
					^ START_FRAME_COM_VALUE_2 
					^ START_FRAME_COM_VALUE_3
				  	^ CMD_RECEIVE_DATABASE
					^ DRV_COM_Database_Id
					^ DRV_COM_Database_Data 
				  	^ DRV_COM_Database_Value_MSB
				  	^ DRV_COM_Database_Value_LSB;

	if (DRV_COM_Database_Value_CRC == Compute_CRC)
	{
		Compute_U16 = (DRV_COM_Database_Value_MSB << 8) 
						| (DRV_COM_Database_Value_LSB & 0x00FF);
		
		DB_IhmAccessParaDataBase(	&Compute_U16,
									 		DRV_COM_Database_Data, 
									 		DRV_COM_Database_Id, 
									 		WRITE);
 	}

	Communication_State = COM_TRANSMIT_STOP;
}