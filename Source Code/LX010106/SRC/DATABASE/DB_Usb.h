/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_Usb.h	 		   				                  		         */
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C Functionnal description : datas for Usb Base							         */
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter :				None                                  		  	*/
/*%IO Input/Output Parameter : 	None  	        			                  	*/
/*%O 	Output Parameter : 			None		 	                 				  		*/
/******************************************************************************/
#ifndef USB_H
#define USB_H

#include "typedef.h"


/******************************************************************************/
/*                     ENUM DECLARATION				                           */
/******************************************************************************/

/* Base Usb	  */
typedef enum {
	USB_ERASE_KEY_U16 = 0,
   	USB_TRANSFER_APPLY_U16,
	USB_CONTINUOUS_RECORDING_U16,
	USB_MONITOR_TRANSFER_U16,
	USB_MONITOR_TRANSFER_SELECT_U16,
	USB_TREND_TRANSFER_U16,
	USB_TREND_TRANSFER_SELECT_U16,
	USB_EVENTS_TRANSFER_U16,   	
   	USB_KEY1_DETECTED_AFTER_POWER_ON_U16,
   	USB_KEY2_DETECTED_AFTER_POWER_ON_U16,
   	USB_ERROR_CODE_READY_U16,
   	USB_ERROR_CODE_U16,
	USB_ERROR_CODE_READY_IHM_U16,
   	USB_ERROR_CODE_IHM_U16,
   	USB_PROGRESS_HOURS_U16,
   	USB_PROGRESS_MINUTES_U16,
   	USB_COMMAND_SENT_U16,
   	USB_STOP_COMMAND_SENT_U16,    
   	USB_MSNB_ONE_DETECTED_U16,
   	USB_MSNB_TWO_DETECTED_U16,
	USB_NEW_KEY_CONNECTED_U16,
	USB_MSB_FREE_SPACE_KEY_ONE,
	USB_LSB_FREE_SPACE_KEY_ONE,
	USB_MSB_FREE_SPACE_KEY_TWO,
	USB_LSB_FREE_SPACE_KEY_TWO,
   	USB_NEW_MODE_DETECTED,
   	USB_NEW_MODE,
   	end_of_db_usb_table
} e_DB_USB;


/* Code d'erreur */
#define E_USB_OK                 		   0
#define E_USB_FILE_OPEN_FAILED   		   1
#define E_USB_FILE_CLOSE_FAILED  		   2
#define E_USB_FILE_WRITE_FAILED  		   3
#define E_USB_FILE_READ_FAILED   		   4
#define E_USB_ENTIRE_ERASE_FAILED         5
#define E_USB_SETTING_FILE_NOT_FOUND      6
#define E_USB_SETTING_FILE_CORRUPTED      7
#define E_USB_NO_FREE_SPACE               8
#define E_USB_TOO_MANY_KEY_CONNECTED      9
#define E_USB_ONE_KEY_CONNECTED   		   10
#define E_USB_CREATE_FAILED               11
#define E_USB_FILE_SYSTEM_FAILED          12
#define E_USB_EXPLORE_FAILED              13
#define E_USB_COMMAND_STOPPED             14
#define E_USB_NOERROR_SETTINGS_OVERWRITE  15
#define E_USB_NOERROR_COMPATIBLE_M2XL2S2  16
#define E_USB_NOERROR_COMPATIBLE_M2XL2    17
#define E_USB_NOERROR_COMPATIBLE_XL2      18
#define E_USB_NOERROR_COMPATIBLE_S2       19
#define E_USB_INCOMPATIBLE_SETTINGS       20
#define E_USB_READY_ACCESS						21
#define E_USB_DISCONNECTION_KEY_DURING_OPERATION 	22
#define E_USB_NOT_ENOUGH_KEY_SPACE			23
#define E_USB_KEY_DISCONNECTED					24
/* A voir pour chgt d'heure et de date */

/* Code d'erreur prêt ? */
#define FLAG_ERROR_CODE_READY       1
#define FLAG_ERROR_CODE_NOT_READY   0

#ifdef DECLARATION_USB_BASE
/******************************************************************************/
/*                     CONSTANT DECLARATION			                           */
/******************************************************************************/
/* Base Control array */
UWORD16 DB_Usb[end_of_db_usb_table];
#else
/******************************************************************************/
/*                     CONSTANT DECLARATION			                           */
/******************************************************************************/
/* Base Control array */
extern UWORD16 DB_Usb[end_of_db_usb_table];
#endif

#endif
