/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_COM_Launch.c                                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C          																						*/
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
#include "DRV_COM_Data.h"
#include "DRV_COM_Launch.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void DRV_COM_Launch(void)
{
   	DRV_COM_Read_Buffer();

	switch (Communication_State)
	{
		/*%C Transmission de Monitoring 									  */
		case  COM_TRANSMIT_MONITORING:
	  	  	DRV_COM_Transmit_Monitoring(); 
			break;

		/*%C Transmission de recueil 									  */
		case  COM_TRANSMIT_RETRIEVAL:
		  	DRV_COM_Transmit_Retrieval();
			break;

		/*%C Transmission de tendance 									  */
		case COM_TRANSMIT_TENDANCE:
			DRV_COM_Transmit_Trend();
			break;

		/*%C Transmission de monitoring détaillé 	   					  */
		case COM_TRANSMIT_DETAILLED_MONITORING:
			DRV_COM_Transmit_Detailled();
			break;

		/*%C Transmission de ID appareil									  */
		case COM_TRANSMIT_IDENTIFICATION_DEVICE:
			DRV_COM_Transmit_ID();
			break;

		/*%C Reception de ID appareil									  */
		case COM_RECEIVE_IDENTIFICATION_DEVICE:
			DRV_COM_Receive_ID();
			break;

		/*%C Transmission de compteur machine							  */
		case COM_TRANSMIT_MACHINE_COUNTER:
			DRV_COM_Transmit_Machine_Counter();
			break;

		/*%C Reception de compteur machine							  */
		case COM_RECEIVE_MACHINE_COUNTER:
			DRV_COM_Receive_Machine_Counter();
			break;

		/*%C Transmission de DATABASE									  */
		case COM_TRANSMIT_DATABASE:
			DRV_COM_Transmit_Database();
			break;

		/*%C Reception DATABASE */		
		case COM_RECEIVE_DATABASE :
			DRV_COM_Receive_Database();
			break;

		/*%C Transmission COM_Ready */
		case COM_READY :
			DRV_COM_Ready();
			break;

		/*%C Transmission EEPROM */
		case COM_READ_EEPROM :
			DRV_COM_Read_Eeprom();
			break;

		/*%C Transmission des reglages */
		case COM_TRANSMIT_SETTINGS :
			DRV_COM_Transmit_Settings();
			break;

 		/*%C Transmission des monitorings vers la clé */
		case COM_TRANSMIT_MONITORING_TO_KEY :
			DRV_COM_Transmit_Monitoring_To_Key();
			break;

		/*%C Stop Transmission 											  */
		case  COM_TRANSMIT_STOP:  
			break;

		default:
			break;
			
	}
}