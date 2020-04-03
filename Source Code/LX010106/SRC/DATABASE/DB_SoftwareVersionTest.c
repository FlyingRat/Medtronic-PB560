/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_SoftwareVersionTest.c     				                  		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function tests the software    	*/
/*%C        version   																			*/
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter : 			None		        			                  	*/
/*%IO Input/Output Parameter : 	None 	        			                  		*/
/*%O 	Output Parameter : 			None      	                 				  		*/
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/
#ifndef _BORLAND
   #ifndef _TASKING
      #include "LH_ST10F276.h"
      #include <intrins.h>
   #else
      #include "regf276e.h"
   #endif
#endif
#include "typedef.h"
#include "io_declare.h"
#include "enum.h"
#include "Structure.h"
#include "Define.h"
#include "DB_Control.h"
#include "DB_current.h"
#include "DB_config.h"
#include "DB_Event.h"
#include "DB_Rtc.h"
#include "DB_IhmAccessParaDataBase.h"
#include "DB_SoftwareVersionTest.h"
#include "DRV_VarEeprom.h"
#include "MAIN_Data.h"
#ifndef _BORLAND
	#include "Pust.h"
#endif	


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DB_SoftwareVersionTest(void)
{

/* Id Declaration  */
	UWORD16 Id=0;

#ifndef _BORLAND
/* EraseState Declaration  */
	e_BadEraseState EraseState = ERASE_OK;

	DB_StartInitRequest = FALSE;

/*%C Software version test */
/*%C --------------------- */


/*%C Hardware Test Version	XL2													            */
#if defined(LEGENDAIR_XL2)
	if ((JUMPER_JP7 == 1)  && (JUMPER_JP8 == 1))
#elif defined(SUPPORTAIR_M2)
	if ((JUMPER_JP7 == 1)  && (JUMPER_JP8 == 0))
#elif defined(LEGENDAIR_S2)
	if ((JUMPER_JP7 == 0)  && (JUMPER_JP8 == 1))
#endif
	{
/*%C if the version is different between ROM and EEPROM, change of            */
/*%C version and EEPROM parameter initialization                              */
		EEP_FIFO_PushOneData(&EEP_DB_Version_Number[VERSION_NUMBER_0],
		                     READ_EEP); 
	
/*%C First start Test                             */
		if (EEP_DB_Version_Number[VERSION_NUMBER_0] !=
		                     (UWORD16)cDB_TEST_VERSION_DB[VERSION_NUMBER_0].defvalue)
	   {
#if defined(LEGENDAIR_XL2)
/*%C  if US, M2 or S2 Version                                                */
			if (	(EEP_DB_Version_Number[VERSION_NUMBER_0] == LU)	||
					(EEP_DB_Version_Number[VERSION_NUMBER_0] == LM) ||
					(EEP_DB_Version_Number[VERSION_NUMBER_0] == LS)
				)
#elif defined(SUPPORTAIR_M2)
/*%C  if XL2, US or S2 Version                                                */
			if (	(EEP_DB_Version_Number[VERSION_NUMBER_0] == LX)	||
					(EEP_DB_Version_Number[VERSION_NUMBER_0] == LU) ||
					(EEP_DB_Version_Number[VERSION_NUMBER_0] == LS)
				)
#elif defined(LEGENDAIR_S2)
/*%C  if XL2, M2 or US Version                                                */
			if (	(EEP_DB_Version_Number[VERSION_NUMBER_0] == LX)	||
					(EEP_DB_Version_Number[VERSION_NUMBER_0] == LM) ||
					(EEP_DB_Version_Number[VERSION_NUMBER_0] == LU)
				)
#endif
			{
/*%C  Bad Version Detected                                               */
				BadVersion = TRUE;
			}
			else
			{
/*%C  First Start detected                                               */
				NewVersionDetected = TRUE;
				DB_FirstStart = TRUE;
			}
	 	}
	}
	else
	{
/*%C  Bad Version Detected                                               */
		BadVersion = TRUE;
	}

/*%C Test: version compatibility after first start                            */
/*%C Start test on the first number version (Id = 0 treated just before)      */

   if (BadVersion == FALSE)
   {
	   for (Id=1;Id<VERSION_NUMBER_3 + 1;Id++)
	   {
		   EEP_FIFO_PushOneData(&EEP_DB_Version_Number[Id], READ_EEP);

/*%C Version change test                                                      */
		   if	(EEP_DB_Version_Number[Id] != 
		                        (UWORD16)cDB_TEST_VERSION_DB[Id].defvalue)
   	   	   {
			   NewVersionDetected = TRUE;

/*********************************************************************************************/
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!    THIS ONLY FOR  LU010005	 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/* In LU010005 version, we need to reload all the database (calibration points will be erased) */
/* so, DB_FirstStart falg is set to TRUE .*/
			   if((cDB_TEST_VERSION_DB[VERSION_NUMBER_0].defvalue == 0x4C55) /* LU */
			   &&(cDB_TEST_VERSION_DB[VERSION_NUMBER_1].defvalue == 0x3031)	 /* 01 */
			   &&(cDB_TEST_VERSION_DB[VERSION_NUMBER_2].defvalue == 0x3030)	 /* 00 */
			   &&(cDB_TEST_VERSION_DB[VERSION_NUMBER_3].defvalue == 0x3035)) /* 05 */
			   {
			   		DB_FirstStart = TRUE;	
			   }
/*********************************************************************************************/
		   }	
	   } 

/* if there is a problem with the Eeprom CRC,and if it is not a new version software*/
/* we must call the "PUST_Check" function, which blocks the software running.*/
		if((NewVersionDetected == FALSE)
		&& (MAIN_CrcEepromTrouble == TRUE))
		{
#ifndef _TASKING
		   	PUST_Checks(TRUE,PUST_EEPROM_CHECK_REQ);
#endif
		}
   }




#endif
#ifndef _BORLAND

/*%C Last erase state read                                                    */
	EEP_FIFO_PushOneData(&EEP_DB_Config[BAD_ERASE_U16], READ_EEP);
	EraseState = EEP_DB_Config[BAD_ERASE_U16]; 

/*%C If new version detected,                                                 */
/*%C EEPROM parameter initialization with the default values :                */
/*%C -if the new version is correct :                                         */
/*%C -if the last erase is not good :                                         */
	if ( (NewVersionDetected == TRUE) 
	  && (BadVersion == FALSE) 
	  || (EraseState == BAD_TOTAL_ERASE) )
	{
#endif

/*%C  Flash initialization and erase running indication                       */
/*%C  The end of treatment indication is saved by:                            */
/*%C  - the trap if the treatment is interrupted                              */
/*%C  - the flash driver at the end of init                                   */

#ifndef _BORLAND
      do
 		{
	 		DB_WriteDataInEepAndRam(&EEP_DB_Config[BAD_ERASE_U16],
	 		                        BAD_TOTAL_ERASE);
 			EEP_FIFO_PushOneData(&EEP_DB_Config[BAD_ERASE_U16],
 			                     READ_EEP);
  		}	
		while (EEP_DB_Config[BAD_ERASE_U16] != BAD_TOTAL_ERASE);
#endif
/*%C  Database parameters writing (RAM and EEPROM)                            */

/*%C  Settings writing                                                        */
		for (Id=0;Id<end_of_adjust_table;Id++)
		{
/*%C     VOL settings writing                                                 */
			do
			{
				DB_WriteDataInEepAndRam(&EEP_DB_VOL_Adjust[Id],
				                        cDB_VOL_TEST_ADJUST_DB[Id].defvalue); 

				EEP_FIFO_PushOneData(&EEP_DB_VOL_Adjust[Id],
				                     READ_EEP);

			}	
			while (EEP_DB_VOL_Adjust[Id] != cDB_VOL_TEST_ADJUST_DB[Id].defvalue);

/*%C     PSV settings writing                                                 */
			do
			{
				DB_WriteDataInEepAndRam(&EEP_DB_PSV_Adjust[Id],
				                        cDB_PSV_TEST_ADJUST_DB[Id].defvalue);

				EEP_FIFO_PushOneData(&EEP_DB_PSV_Adjust[Id],
				                     READ_EEP);
			}	
			while (EEP_DB_PSV_Adjust[Id] != cDB_PSV_TEST_ADJUST_DB[Id].defvalue);
			
/*%C     CPAP settings writing                                                */
			do
			{
				DB_WriteDataInEepAndRam(&EEP_DB_CPAP_Adjust[Id],
				                        cDB_CPAP_TEST_ADJUST_DB[Id].defvalue);

				EEP_FIFO_PushOneData(&EEP_DB_CPAP_Adjust[Id],
				                     READ_EEP);
			}	
			while (EEP_DB_CPAP_Adjust[Id] != cDB_CPAP_TEST_ADJUST_DB[Id].defvalue);
			
/*%C     VSIMV settings writing                                               */
			do
			{			
				DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[Id],
				                        cDB_VSIMV_TEST_ADJUST_DB[Id].defvalue);

				EEP_FIFO_PushOneData(&EEP_DB_VSIMV_Adjust[Id],
				                     READ_EEP);
			}	
			while (EEP_DB_VSIMV_Adjust[Id] != 
			                                cDB_VSIMV_TEST_ADJUST_DB[Id].defvalue);

/*%C     PRES settings writing                                                */
			do
			{
				DB_WriteDataInEepAndRam(&EEP_DB_PRES_Adjust[Id],
				                        cDB_PRES_TEST_ADJUST_DB[Id].defvalue);

				EEP_FIFO_PushOneData(&EEP_DB_PRES_Adjust[Id],
				                     READ_EEP);
			}	
			while (EEP_DB_PRES_Adjust[Id] != cDB_PRES_TEST_ADJUST_DB[Id].defvalue);

/*%C     PSIMV settings writing                                               */
			do
			{
				DB_WriteDataInEepAndRam(&EEP_DB_PSIMV_Adjust[Id],
										cDB_PSIMV_TEST_ADJUST_DB[Id].defvalue);

				EEP_FIFO_PushOneData(&EEP_DB_PSIMV_Adjust[Id],
									 READ_EEP);
			}
			while (EEP_DB_PSIMV_Adjust[Id] !=
										  cDB_PSIMV_TEST_ADJUST_DB[Id].defvalue);
    }

/*%C  Version number writing                                                  */
      for (Id=0;Id<end_of_db_version_table;Id++)
      {
		if ( (DB_FirstStart == TRUE) 
		||(Id < SERIAL_NUMBER_1)) 
		{
		
			do
			{
				DB_WriteDataInEepAndRam(&EEP_DB_Version_Number[Id],
				                        cDB_TEST_VERSION_DB[Id].defvalue);
				
				EEP_FIFO_PushOneData(&EEP_DB_Version_Number[Id],
				                     READ_EEP);
			}
			while (EEP_DB_Version_Number[Id] != cDB_TEST_VERSION_DB[Id].defvalue);
		}
	  }

/*%C Trend database writing */
		for (Id = 0; Id < end_of_db_trend_table; Id++)
		{
	      do
   		{
				DB_WriteDataInEepAndRam(&EEP_DB_TREND[Id],
   				                     cDB_TEST_TREND_DB[Id].defvalue);

   			EEP_FIFO_PushOneData(&EEP_DB_TREND[Id],
   				                  READ_EEP);
   		}
   		while (EEP_DB_TREND[Id] != cDB_TEST_TREND_DB[Id].defvalue);
		 }

/*%C  Config settings writing                                                 */
      for (Id=0;Id<end_of_db_config_table;Id++)
      {
#ifndef _BORLAND
/*%C     Parameter RAZ (except offset and counter)                            */
			if ( (DB_FirstStart == TRUE)
 			   ||( (Id < OFFSET_INSP_FLOW_1_U16)
 			 	  || ( (Id > OFFSET_VALVE_PRESS_2_U16)
 				 	  &&(Id < SAVED_MACHINE_COUNTER_HOUR_U16) )
 				  || (Id > SAVED_MACHINE_COUNTER_MIN_U16)
 				  && (Id != BAD_ERASE_U16) ) )
         	{
#endif
		         do
		   		{
					DB_WriteDataInEepAndRam(&EEP_DB_Config[Id],
		   				                     cDB_TEST_CONFIG_DB[Id].defvalue);
		
		   			EEP_FIFO_PushOneData(&EEP_DB_Config[Id],
		   				                  READ_EEP);
		   		}
		   		while (EEP_DB_Config[Id] != cDB_TEST_CONFIG_DB[Id].defvalue);

#ifndef _BORLAND
            }
#endif
		}

#ifndef _BORLAND
/*%C  Write inhibition and RTC start                                          */
		DRV_RTC_control(0x0070);
/*%C  Flash erase                                                             */
		DRV_EVENT_Erase_Flash();
/*%C  End of erase waiting                                                    */
	  	while (BUSY_MEM2 != 1);

	}
#endif


}
