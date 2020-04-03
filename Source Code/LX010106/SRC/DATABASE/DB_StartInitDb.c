/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_StartInitDb.c 			   				                  		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function makes the init process	*/
/*%C         version prg, chek ram and init variables									*/
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameters :  			None          			                  		*/
/*%IO Input/Output Parameters :  None          			                  		*/
/*%O 	Output Parameters :  		None         			                  		*/
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/

#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "DB_Config.h"
#include "DB_event.h"
#include "DB_Control.h"
#include "DB_Current.h"
	#define DECLARATION_ALARM_STATUS_BASE
#include "DB_AlarmStatus.h"
#include "DB_Rtc.h"
#include "DB_Usb.h"
#include "DB_StartInitDb.h"
	#define DECLARATION_IHM_ACCESS_PARA_DATABASE
#include "DB_IhmAccessParaDataBase.h"
	#define DECLARATION_SECURITY_DATAS
#include "Security_Datas.h"
#include "DRV_VarEeprom.h"
#include "Ventilation_Compute_data.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void DB_StartInitDb(void)
{
 	UBYTE Id;

/*%C Version test function call                     									*/
   DB_SoftwareVersionTest();

/*%C Load and check Eeprom into Ram function call			    						*/
   DB_LoadAndCheckEepromIntoRam();

/*%C Tables initialization function call            									*/
   DB_InitializeTables();

#ifndef _BORLAND
/*%C Active mode memorization initialization                     			      */
	MemoMode = EEP_DB_Config[ADJUST_MODE_U16];

/*%C Adjust base to current base copy function call              			      */
	DB_CopyMngt();

/*%C Good erase and complete initialization indication in order to know if    */
/*%C an init is needed to the next device start                			      */
   do
	{
		DB_WriteDataInEepAndRam(&EEP_DB_Config[BAD_ERASE_U16],
		                        ERASE_OK);
		EEP_FIFO_PushOneData(&EEP_DB_Config[BAD_ERASE_U16],
		                     READ_EEP);
	}
	while (EEP_DB_Config[BAD_ERASE_U16] != ERASE_OK);

	/*%C Initialisation of DB_Trend's compute variables*/
	for(Id = DB_TREND_VENTIL_HOUR ; Id < DB_TREND_IHM_VENTIL_HOUR ; Id++)
	{
		CMP_VentilReport_Array[Id] = DB_TrendRead(Id);
	}

	
/*%C End of base initialization                                               */
   DB_StartInitRequest = TRUE;
#endif

}
