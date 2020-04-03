/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_COM_Data.h                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                    Global variables of "DRV_COM"                    */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*                                                                            */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/*%C State Communication frame */
#define CMD_START_TRANSMIT_EVENT_FRAME  							0x10
#define CMD_STOP_TRANSMIT_EVENT_FRAME  								0x11
#define CMD_START_TRANSMIT_MONITORING_FRAME 					 	0x20
#define CMD_STOP_TRANSMIT_MONITORING_FRAME     						0x21
#define CMD_START_TRANSMIT_TENDANCE_FRAME  							0x30
#define CMD_STOP_TRANSMIT_TENDANCE_FRAME   							0x31
#define CMD_START_TRANSMIT_DETAILLED_MONITORING_FRAME  				0x40
#define CMD_STOP_TRANSMIT_DETAILLED_MONITORING_FRAME  				0x41
#define CMD_START_TRANSMIT_DETAILLED_MONITORING_ON_KEY				0x42
#define CMD_RECEIVE_SERIAL_NUMBER									0x50
#define CMD_RECEIVE_MACHINE_COUNTER									0x51
#define CMD_START_TRANSMIT_SETTINGS_FRAME  							0x60
#define CMD_STOP_TRANSMIT_SETTINGS_FRAME  							0x61
#define CMD_COM_READY												0x97
#define CMD_TRANSMIT_MACHINE_COUNTER								0x98
#define CMD_TRANSMIT_SERIAL_NUMBER									0x99	
#define CMD_TRANSMIT_DATABASE										0xBA 
#define CMD_TRANSMIT_DATABASE_FULL_SPEED							0xBF 
#define CMD_RECEIVE_DATABASE										0xBC
#define CMD_READ_EEPROM												0xEE

/*%C Header Commmunication frame */
#define START_FRAME_COM_VALUE_1										0x02
#define START_FRAME_COM_VALUE_2										0x05
#define START_FRAME_COM_VALUE_3										0x07
#define END_FRAME_COM_VALUE_1   							 		0x07
#define END_FRAME_COM_VALUE_2   							 		0x05
#define END_FRAME_COM_VALUE_3   							 		0x02


/*%C Communication ID Data List */
#define ID_SERIAL_NUMBER	   		 						 		0x01
#define ID_EVENT_DATA	   			 			 					0x02		
#define ID_SETTINGS_DATA	 						 				0x03
#define ID_TREND_DATA	   			 			 					0x04
#define ID_DETAILED_MONITORING_DATA	   						 		0x05
#define ID_COM_MONITORING_TO_KEY									0x06
#define ID_END_OF_TRANSMISSION	   	 					 			0x07
#define ID_MACHINE_HOUR			   	 					 			0x08
#define ID_COM_READY												0x09
#define ID_READ_DATABASE											0xBB

/*%C Monitoring to key transfer return codes */
#define COM_MONIT_TO_KEY_TRANSFER_START_OK				 			0x00
#define COM_MONIT_TO_KEY_TRANSFER_ERROR_NO_KEY					 	0x01
#define COM_MONIT_TO_KEY_TRANSFER_ERROR_TOO_MANY_KEYS				0x02
#define COM_MONIT_TO_KEY_TRANSFER_ERROR_USB_BUSY				 	0x03
#define COM_MONIT_TO_KEY_TRANSFER_NOT_IN_USB_MENU					0x04


#define COM_EEPROM_BUFFER_SIZE										2048
#define COM_ID_BUFFER_SIZE											12
#define COM_NB_MAX_RECEIVED_DATA									48
#define COM_NB_MAX_PARAMETER_DATABASE								20



/******************************************************************************/
/*%C COM Frame enum */
/******************************************************************************/

typedef enum
{
  	/*%C enum state transmission receive */
	COM_RX_B1_START_FRAME = 0, //1ier octet d'entête de trame
	COM_RX_B2_START_FRAME, 	   //2ième octet d'entête de trame	
	COM_RX_B3_START_FRAME, 	   //3ièmer octet d'entête de trame		
	COM_RX_COMMAND, 		   //indentifiant de commande de trame
	COM_RX_NB_ARG,			   // nombre d'arguments (données dans la trame 				
	COM_RX_BufferSize = 96	   //Taille du buffer de reception liaison série			
}e_COM_RX_REMOTE;

typedef enum
{
	COM_TX_START_FRAME_1 = 0,
	COM_TX_START_FRAME_2,
	COM_TX_START_FRAME_3,
	COM_TX_ID_FRAME,
	COM_TX_DATA_FRAME,
	COM_TX_MSB_CRC_FRAME,
	COM_TX_LSB_CRC_FRAME,
	COM_TX_END_FRAME_1,
	COM_TX_END_FRAME_2,
	COM_TX_END_FRAME_3,
	End_Of_Table_Com_TX_Remote
}e_COM_TX_REMOTE;


typedef enum
{
	COM_TRANSMIT_MONITORING = 0, 		// en transmission de monitoring
	COM_TRANSMIT_RETRIEVAL,  			// en transmission de recueil
	COM_TRANSMIT_TENDANCE,
	COM_TRANSMIT_DETAILLED_MONITORING,
	COM_TRANSMIT_MONITORING_TO_KEY,
	COM_TRANSMIT_IDENTIFICATION_DEVICE,
	COM_RECEIVE_IDENTIFICATION_DEVICE,	
	COM_TRANSMIT_MACHINE_COUNTER,
	COM_RECEIVE_MACHINE_COUNTER,
	COM_TRANSMIT_DATABASE,
	COM_RECEIVE_DATABASE,
	COM_READY,
	COM_READ_EEPROM,
	COM_TRANSMIT_SETTINGS,
	COM_TRANSMIT_STOP	      			 // arrêt de la transmission
}e_COM_STATE;
   
typedef enum
{
	ID_DEVICE_1 = 0,
	ID_DEVICE_2,
	ID_DEVICE_3,
	ID_DEVICE_4,
	ID_DEVICE_5,
	ID_DEVICE_6,
	ID_DEVICE_7,
	ID_DEVICE_8,
	ID_DEVICE_9,
	ID_DEVICE_10,
	ID_DEVICE_11,
	ID_DEVICE_12,
	End_Of_Table_Com_ID_Device
}e_COM_ID_DEVICE;

typedef enum
{
	COM_MACHINE_COUNTER_MSB = 0,	
	COM_MACHINE_COUNTER_LSB,
	End_Of_Table_Com_Machine_Counter
}e_COM_MACHINE_HOUR;

typedef enum
{
	COM_TX_DATABASE_MSB = 0,	
	COM_TX_DATABASE_LSB,
	End_Of_Table_TX_DATABASE	
}e_COM_TX_DATABASE;

typedef enum
{
	COM_TX_SETTINGS_MODE = 0,
	COM_TX_SETTINGS_FIO2,
	COM_TX_SETTINGS_VT_MSB,
	COM_TX_SETTINGS_VT_LSB,
	COM_TX_SETTINGS_PI,
	COM_TX_SETTINGS_PE,
	COM_TX_SETTINGS_PISLOPE,
	COM_TX_SETTINGS_RAMP,
	COM_TX_SETTINGS_IT,
	COM_TX_SETTINGS_IE_NUM,
	COM_TX_SETTINGS_IE_DEN,
	COM_TX_SETTINGS_FREQ,
	COM_TX_SETTINGS_FVACI,
	COM_TX_SETTINGS_APNEA,
	COM_TX_SETTINGS_ITRIGGER,
	COM_TX_SETTINGS_ETRIGGER,
	COM_TX_SETTINGS_VTTARGET_MSB,
	COM_TX_SETTINGS_VTTARGET_LSB,
	COM_TX_SETTINGS_PIMAXI,
	End_Of_Table_TX_Settings
}e_COM_TX_SETTINGS;




#ifdef DECLARATION_COM_DATA
	#ifndef DRV_COM_DATA_H
	#define DRV_COM_DATA_H


/*%C RS232	state	 */
e_COM_STATE Communication_State;
/*%C Frame reception buffer																	*/
UBYTE DRV_COM_Buffer_Of_Receipt[COM_RX_BufferSize];
UBYTE DRV_COM_Ptr_Read_Buffer_Rx;
UBYTE DRV_COM_Ptr_Write_Buffer_Rx;
UBYTE DRV_COM_Receive_ID_Buffer[COM_ID_BUFFER_SIZE];
UBYTE DRV_COM_Transmit_Database_Full_Speed;

/*%C  Reading of Memory flash Writing index */
UWORD16 xhuge *adr_flash_retrieval; 

/*%C Reading array datas stored in eeprom  */
UWORD16 EepromData[COM_EEPROM_BUFFER_SIZE]; 
volatile UBYTE xhuge *EepromDataRead;

/*%C Transmition frame end issue from PECC2 */
volatile UWORD16 DRV_COM_End_of_Transmit = TRUE;

/*%C  readig index of events stored in flash memory*/
volatile UWORD16 num_event;	

UBYTE DRV_COM_Database_Id;
UBYTE DRV_COM_Database_Data;
UBYTE DRV_COM_Database_Value_MSB;
UBYTE DRV_COM_Database_Value_LSB;
UBYTE DRV_COM_Database_Value_CRC;
UBYTE DRV_COM_Machine_Counter_Value_MSB;
UBYTE DRV_COM_Machine_Counter_Value_LSB;
UBYTE DRV_COM_NbParamDb;
UBYTE DRV_COM_Param;
UBYTE DRV_COM_Database_Parameter[COM_NB_MAX_PARAMETER_DATABASE];
	#endif
#else
	#ifndef DRV_COM_DATA_H
	#define DRV_COM_DATA_H

/*%C RS232	state	 */
extern e_COM_STATE Communication_State;
/*%C Frame reception buffer																	*/
extern UBYTE DRV_COM_Buffer_Of_Receipt[];
extern UBYTE DRV_COM_Ptr_Read_Buffer_Rx; 
extern UBYTE DRV_COM_Ptr_Write_Buffer_Rx;
extern UBYTE DRV_COM_Receive_ID_Buffer[];
extern UBYTE DRV_COM_Transmit_Database_Full_Speed;

/*%C  Reading of Memory flash Writing index */
extern UWORD16 xhuge *adr_flash_retrieval; 


extern UWORD16 EepromData[]; /*%C Reading array datas stored in eeprom  */
extern volatile UBYTE xhuge *EepromDataRead;


/*%C Transmition frame end issue from PECC2 */
extern volatile UWORD16 DRV_COM_End_of_Transmit;

/*%C  readig index of events stored in flash memory*/
extern volatile UWORD16 num_event;

extern UBYTE DRV_COM_Database_Id;
extern UBYTE DRV_COM_Database_Data;
extern UBYTE DRV_COM_Database_Value_MSB;
extern UBYTE DRV_COM_Database_Value_LSB;
extern UBYTE DRV_COM_Database_Value_CRC;
extern UBYTE DRV_COM_Machine_Counter_Value_MSB;
extern UBYTE DRV_COM_Machine_Counter_Value_LSB;
extern UBYTE DRV_COM_NbParamDb;
extern UBYTE DRV_COM_Param;
extern UBYTE DRV_COM_Database_Parameter[];

	#endif
#endif
