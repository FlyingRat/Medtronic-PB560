/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : PUST.c                                                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C          Power Up Self Test routines	  								  */
/******************************************************************************/
	 
/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
#ifndef _TASKING
#include "LH_ST10F276.h"
#include <intrins.h>
#else
#include "regf276e.h"
#endif	 
#include "io_declare.h"
#include "typedef.h"
#include "enum.h"
#include "PUST.h"
#include "PUST_crc8.h"
#include "PUST_ramtestlib.h"
#include "PUST_ref_voltages.h"
#include "Driver_Display_Data.h"
#include "DIS_FifoRead.h"
#include "DRV_VarEeprom.h"

/* locate boot code to specific section */
#include "locate_boot_code.h"

/* Uncomment the following line to display a detailed error code message
   If commented, "VERSION SOFTWARE ERROR" is displayed whatever the error code value */
/* #define _PUST_DETAILED_ERROR_MESSAGE */

/* static routines */
static e_PUST_ERROR_CODE PUST_Check_Flash(T_FLASH_MEM_RANGE* PtMem);
static e_PUST_ERROR_CODE PUST_Check_Ram(void);
static e_PUST_ERROR_CODE ConvertRamErrorCode(e_RAM_ERROR_CODE _RamErrCode);
static e_PUST_ERROR_CODE PUST_Check_RefVoltages(void);

static void PUST_DisplayOnError(e_PUST_ERROR_CODE code);
static void PUST_InfiniteLoop(void);
static void PUST_Sound(void);
static void PUST_LaunchTimer(void);
static e_BOOL PUST_HasTimerExpired(void);

#define MAX_CHARS 50

const UBYTE near  
PustProblemDisplayedCodes[PUST_ERR_MAX][MAX_CHARS] = {  "",	  /* PUST_ERR_OK */
                                                  		"9",  /* PUST_ERR_DATA_BUS (Ram error) */
											      		"9",  /* PUST_ERR_ADDRESS_BUS (Ram error) */
											      		"9",  /* PUST_ERR_DEVICE (Ram error) */
											      		"10", /* PUST_ERR_CRC (Flash error) */
												  		"",   /* PUST_ERR_FORCED_FAIL */
												  		"11", /* PUST_ERR_EEPROM (Eeprom error) */
												  		"12", /* PUST_ERR_REF_VOLTAGE (ref. voltages error)*/
                                                        "13", /* PUST_ERR_SOFT_VERSION (error version)*/
												  		"" 	  /* PUST_ERR_UNKNOWN */
												   };

T_FLASH_MEM_RANGE FlashMapping[FLASH_MEM_RANGE_MAX+1] = {{TRUE,  0x0,     0x7FFF},
                                                        {TRUE,  0x18000, MEM_END_CODE_AND_CONST},
                                                        {FALSE, 0      , 0} }; /* --> end of struct table identifier */


static UBYTE FlashCalculatedCrc = 0;
static UBYTE FlashRomedCrc = 0;


/******************************************************************************/
/*%C                       Functionnal description :                          */
//*%C Checks the CRC of the flash (const + code)                              */
/*%C                                                                          */
/*%I  Input Parameter :                                                       */
/*%I		NONE                                                              */
/*%IO Input/Output :                                                          */
/*%IO		NONE                                                              */
/*%O  Output Parameter :                                                      */
/*%O 		NONE                                                              */
/******************************************************************************/
static e_PUST_ERROR_CODE PUST_Check_Flash(T_FLASH_MEM_RANGE* PtMem)
{
	UBYTE CalculatedCrc;
	CalculatedCrc = PUST_CalcCrc8(PtMem);

	FlashCalculatedCrc = CalculatedCrc;
	FlashRomedCrc = *(UBYTE xhuge *)MEM_CRC_ADDRESS;

	if(CalculatedCrc == *(UBYTE xhuge *)MEM_CRC_ADDRESS)
	{
		CalculatedCrc = PUST_ERR_OK;
	}
	else
	{
		CalculatedCrc = PUST_ERR_CRC;
	}
	return (CalculatedCrc);
}
/******************************************************************************/
/*%C                       Functionnal description :                          */
//*%C Convert Test ram error code to PUST error code                          */
/*%C                                                                          */
/*%I  Input Parameter :                                                       */
/*%I		NONE                                                              */
/*%IO Input/Output :                                                          */
/*%IO		NONE                                                              */
/*%O  Output Parameter :                                                      */
/*%O 		NONE                                                              */
/******************************************************************************/
e_PUST_ERROR_CODE ConvertRamErrorCode(e_RAM_ERROR_CODE _RamErrCode)
{
	e_PUST_ERROR_CODE rc;

 	switch(_RamErrCode)
	{
		default:
		case RAM_ERR_ADDRESS_BUS_KO:
			rc = PUST_ERR_ADDRESS_BUS;
		break;

		case RAM_ERR_DATABUS_BUS_KO:
			rc = PUST_ERR_DATA_BUS;
		break;

		case RAM_ERR_OK:
			rc = PUST_ERR_OK;
		break;
	 }

	 return (rc);
}
/******************************************************************************/
/*%C                       Functionnal description :                          */
//*%C Checks error_code location                                              */
/*%C                                                                          */
/*%I  Input Parameter :                                                       */
/*%I		NONE                                                              */
/*%IO Input/Output :                                                          */
/*%IO		NONE                                                              */
/*%O  Output Parameter :                                                      */
/*%O 		NONE                                                              */
/******************************************************************************/
e_PUST_ERROR_CODE PUST_Check_Ram_ErrorCode_Location(void)
{
	/* This routine is called from startup file before c_init so don't use
	   initialized global data ! */

	T_RAM_MEM_RANGE FirstTestRamMapping;
	e_PUST_ERROR_CODE rc = PUST_ERR_OK;

	/* Range 0 : init */
	FirstTestRamMapping.ToBeCalc = TRUE; 
	FirstTestRamMapping.MinAddress = 0x000F0000;
	FirstTestRamMapping.MaxAddress = 0x000F00FF;
	
	/* Range 0 : test */
	if(rc == PUST_ERR_OK)
	{
		rc = ConvertRamErrorCode(RamTest(&FirstTestRamMapping));
	}
			
	return(rc);							
}
/******************************************************************************/
/*%C                       Functionnal description :                          */
//*%C Checks the first part of RAM                                            */
/*%C                                                                          */
/*%I  Input Parameter :                                                       */
/*%I		NONE                                                              */
/*%IO Input/Output :                                                          */
/*%IO		NONE                                                              */
/*%O  Output Parameter :                                                      */
/*%O 		NONE                                                              */
/******************************************************************************/
e_PUST_ERROR_CODE PUST_Check_Ram_First_Part(void)
{
	/* This routine is called from startup file before c_init so don't use
	   initialized global data ! */

	T_RAM_MEM_RANGE FirstTestRamMapping;
	e_PUST_ERROR_CODE rc = PUST_ERR_OK;

	/* Range 0 : init */
	FirstTestRamMapping.ToBeCalc = TRUE; 
	//FirstTestRamMapping.ToBeCalc = FALSE;
	FirstTestRamMapping.MinAddress = 0x0000F800;
	FirstTestRamMapping.MaxAddress = 0x0000FDFF;
	
	/* Range 0 : test */
	if(rc == PUST_ERR_OK)
	{
		rc = ConvertRamErrorCode(RamTest(&FirstTestRamMapping));
	}
	
	/* Range 1 : init */
	FirstTestRamMapping.ToBeCalc = TRUE; 	
	FirstTestRamMapping.MinAddress = 0x00200000;
	FirstTestRamMapping.MaxAddress = 0x0027FFEF;
		/* note : we don't test from 0x0027FFF0 to 0x0027FFFF since the last 0xF bytes 
		does not pass ram test. This is not a problem as there is no data here because
		linker file does not allow to put something there. */
	
	/* Range 1 : test */
	if(rc == PUST_ERR_OK)
	{
		rc = ConvertRamErrorCode(RamTest(&FirstTestRamMapping));
	}

	/* Range 2 : init */
	FirstTestRamMapping.ToBeCalc = TRUE; 	
	FirstTestRamMapping.MinAddress = 0x0000E000;
	FirstTestRamMapping.MaxAddress = 0x0000E7EF;
		/* note : we don't test from 0x0000E7F0 to 0x0000E7FF since the last 0xF bytes 
		does not pass ram test. This is not a problem as there is no data here because
		linker file does not allow to put something there. */
	
	/* Range 2 : test */
	if(rc == PUST_ERR_OK)
	{
		rc = ConvertRamErrorCode(RamTest(&FirstTestRamMapping));
	}

	/* Range 3 : init */
	FirstTestRamMapping.ToBeCalc = TRUE; 
	FirstTestRamMapping.MinAddress = 0x000F3000;
	FirstTestRamMapping.MaxAddress = 0x000FFFFF;
	
	/* Range 3 : test */
	if(rc == PUST_ERR_OK)
	{
		rc = ConvertRamErrorCode(RamTest(&FirstTestRamMapping));	
	}

	/* update error code */
	_error_code = rc;

	return(rc);							
}
/******************************************************************************/
/*%C                       Functionnal description :                          */
//*%C Checks the second part of RAM                                           */
/*%C                                                                          */
/*%I  Input Parameter :                                                       */
/*%I		NONE                                                              */
/*%IO Input/Output :                                                          */
/*%IO		NONE                                                              */
/*%O  Output Parameter :                                                      */
/*%O 		NONE                                                              */
/******************************************************************************/
e_PUST_ERROR_CODE PUST_Check_Ram_Second_Part(void)
{
	/* This routine is called from startup file before c_init so don't use
	initialized global data ! */

	T_RAM_MEM_RANGE FirstTestRamMapping;
	e_PUST_ERROR_CODE rc = PUST_ERR_OK;

	/* Range 0 : init */
	FirstTestRamMapping.ToBeCalc = TRUE; 
	FirstTestRamMapping.MinAddress = 0x0000F600;
	FirstTestRamMapping.MaxAddress = 0x0000F9FF;
	
	/* Range 0 : test */
	if(rc == PUST_ERR_OK)
	{
		rc = ConvertRamErrorCode(RamTest(&FirstTestRamMapping));
	}

	/* Range 1 : init */
	FirstTestRamMapping.ToBeCalc = TRUE; 	
	FirstTestRamMapping.MinAddress = 0x000F0010;
	FirstTestRamMapping.MaxAddress = 0x000F2FFF;
	
	/* Range 1 : test */
	if(rc == PUST_ERR_OK)
	{
		rc = ConvertRamErrorCode(RamTest(&FirstTestRamMapping));
	}

	/* update error code */
	_error_code = rc;

	return(rc);
}
/******************************************************************************/
/*%C                       Functionnal description :                          */
//*%C Checks the RAM                                                          */
/*%C                                                                          */
/*%I  Input Parameter :                                                       */
/*%I		NONE                                                              */
/*%IO Input/Output :                                                          */
/*%IO		NONE                                                              */
/*%O  Output Parameter :                                                      */
/*%O 		NONE                                                              */
/******************************************************************************/
static e_PUST_ERROR_CODE PUST_Check_Ram(void)
{
	/* ram test has been done by startup code (memtest), we just have to get 
	the updated error_code */	
	return(_error_code);
}
/******************************************************************************/
/*%C                       Functionnal description :                          */
//*%C Convert Test ram error code to PUST error code                          */
/*%C                                                                          */
/*%I  Input Parameter :                                                       */
/*%I		NONE                                                              */
/*%IO Input/Output :                                                          */
/*%IO		NONE                                                              */
/*%O  Output Parameter :                                                      */
/*%O 		NONE                                                              */
/******************************************************************************/
static e_PUST_ERROR_CODE GetErrorCodeFromRequest(e_PUST_REQUEST _CheckRequest)
{
	e_PUST_ERROR_CODE rc = PUST_ERR_OK;

 	switch(_CheckRequest)
	{
		case PUST_RAM_CHECK_REQ:
			rc = PUST_ERR_DATA_BUS;
		break;

		case PUST_FLASH_CHECK_REQ:
			rc = PUST_ERR_CRC;
		break;

		case PUST_EEPROM_CHECK_REQ:
			rc = PUST_ERR_EEPROM;
		break;

		case PUST_REF_VOLTAGE_CHECK_REQ:
			rc = PUST_ERR_REF_VOLTAGE;
		break;

        case PUST_SOFT_VERSION_CHECK_REQ:
			rc = PUST_ERR_SOFT_VERSION;
		break;
        
		default:		
			rc = PUST_ERR_UNKNOWN;
		break;
	 }

	 return (rc);
}
/******************************************************************************/
/*%C                       Functionnal description :                          */
//*%C Checks Reference Voltages                                               */
/*%C                                                                          */
/*%I  Input Parameter :                                                       */
/*%I		NONE                                                              */
/*%IO Input/Output :                                                          */
/*%IO		NONE                                                              */
/*%O  Output Parameter :                                                      */
/*%O 		NONE                                                              */
/******************************************************************************/
static e_PUST_ERROR_CODE PUST_Check_RefVoltages(void)
{
	e_REF_VOLTAGE_CODE rc = RefVoltagesCheck();
	
	if(rc == REF_VOLTAGE_ERR_OK)
	{
		rc = PUST_ERR_OK;
	}
	else
	{
		rc = PUST_ERR_REF_VOLTAGE;
	}
	return (rc);
}
/******************************************************************************/
/*%C                       Functionnal description :                          */
//*%C Displays a message on the screen according to the passed error code     */
/*%C                                                                          */
/*%I  Input Parameter :                                                       */
/*%I		code : error code                                                 */
/*%IO Input/Output :                                                          */
/*%IO		NONE                                                              */
/*%O  Output Parameter :                                                      */
/*%O 		NONE                                                              */
/******************************************************************************/
static void PUST_DisplayOnError(e_PUST_ERROR_CODE code)
{
	DRV_DIS_HostRequest(1);

	T2IR = 0;			T2IC = 0;
	T2 = 5000;   	
	T2CON  = 0x00C0;   
	while (MASTERBUSY && (T2IR == 0));
	T2CON = 0x0000;     

	DIS_ErasePage(PAGE3);
	DIS_ErasePage(PAGE2);
	DIS_ErasePage(PAGE1);

	DIS_DisplayPage ( PAGE3, PAGEON );						


	DIS_String( (UBYTE*) "DEVICE FAULT", 
				/* Font */ ARIALBLACK11,
				/* line */ 120,
				/* column */ 70,
				/* printon */ ON,
				(UBYTE)PAGE3);
	
	DIS_String( (UBYTE*) &PustProblemDisplayedCodes[code][0], 
				/* Font */ ARIALBLACK11,
				/* line */ 120,
				/* column */ 200,
				/* printon */ ON,
				(UBYTE)PAGE3);

	DIS_String( (UBYTE*) "RESTART/SRVC", 
				/* Font */ ARIALBLACK11,
				/* line */ 140,
				/* column */ 70,
				/* printon */ ON,
				(UBYTE)PAGE3);

#ifdef _PUST_DETAILED_ERROR_MESSAGE

   if(code == PUST_ERR_CRC)
   {
		DIS_String( "Calculated CRC:", 
					/* Font */ ARIAL9,
					/* line */ 170,
					/* column */ 70,
					/* printon */ ON,
					(UBYTE)PAGE3);

		DIS_Number( 	(SWORD32) (FlashCalculatedCrc & 0x000000FF),
						/* float */(UBYTE) FALSE,
						/* line */ 170,
						/* column */ 170,
						/* Font */ ARIAL9,
						/* nbdigit */ 4,
						/* zero */ 0,
						/* printon */ ON,
						(UBYTE)PAGE3);	

		DIS_String( "Romed CRC:", 
					/* Font */ ARIAL9,
					/* line */ 190,
					/* column */ 70,
					/* printon */ ON,
					(UBYTE)PAGE3);

		DIS_Number( 	(SWORD32) (FlashRomedCrc & 0x000000FF),
						/* float */(UBYTE) FALSE,
						/* line */ 190,
						/* column */ 170,
						/* Font */ ARIAL9,
						/* nbdigit */ 4,
						/* zero */ 0,
						/* printon */ ON,
						(UBYTE)PAGE3);
	
	} /* if(code == PUST_ERR_CRC */

#endif // _PUST_DETAILED_ERROR_MESSAGE

	DRV_DIS_HostRequest (0) ;

}
/******************************************************************************/
/*%C                       Functionnal description :                          */
/*%C Launches a hardware timer whose expiration will be tested using the      */
/*%C PUST_HasTimerExpired routine										      */
/*%C                                                                          */
/*%I  Input Parameter :                                                       */
/*%I		NONE                                                              */
/*%IO Input/Output :                                                          */
/*%IO		NONE                                                              */
/*%O  Output Parameter :                                                      */
/*%O 		NONE                                                              */
/******************************************************************************/
static void PUST_LaunchTimer(void)
{				
		T2IR  = 0;
		T2IC  = 0;
		T2    = 50000;	/* 50000 * 200ns = 10ms */
		T2CON = 0x00C0;		
}
/******************************************************************************/
/*%C                       Functionnal description :                          */
/*%C Launches a hardware timer whose expiration will be tested using the      */
/*%C PUST_HasTimerExpired routine										      */
/*%C                                                                          */
/*%I  Input Parameter :                                                       */
/*%I		NONE                                                              */
/*%IO Input/Output :                                                          */
/*%IO		NONE                                                              */
/*%O  Output Parameter :                                                      */
/*%O 		Boolean : TRUE if has expired                                     */
/******************************************************************************/
static e_BOOL PUST_HasTimerExpired(void)
{
	static counter = 0;
	e_BOOL rc = FALSE;
	
	if(T2IR == 1)
	{
		/* 10 ms timer has fired */
	    counter++;
		if(counter == 50) 		
		{
			counter = 0;
			rc = TRUE;	  /* Expires after 50 * 10 = 500 ms */
		}
		PUST_LaunchTimer();
	}	

	return(rc);
}
/******************************************************************************/
/*%C                       Functionnal description :                          */
/*%C Enters an infinite loop refreshing hardware and software wdogs	and 	  */
/*%C flashing LEDs                                                            */
/*%C                                                                          */
/*%I  Input Parameter :                                                       */
/*%I		code : error code                                                 */
/*%IO Input/Output :                                                          */
/*%IO		NONE                                                              */
/*%O  Output Parameter :                                                      */
/*%O 		NONE                                                              */
/******************************************************************************/
static void PUST_InfiniteLoop(void)
{
	UWORD16 cnt = 0;
	UWORD32 leds_cnt = 0;

	LED_ALARME_ORANGE =  TRUE;
	LED_ALARME_ROUGE =  TRUE;

   	PUST_LaunchTimer();

	while(1)
	{
		cnt++;
		leds_cnt++;

		/* refreshing watchdogs */
		if(cnt == 0)
		{
			WDOG = !WDOG;
			_srvwdt_();
		}

		if(PUST_HasTimerExpired())
		{
			/* When timer fires, toggle LEDs. Note that timer is autorelaunched */
			LED_ALARME_ORANGE = !LED_ALARME_ORANGE;
			LED_ALARME_ROUGE = !LED_ALARME_ROUGE;
		}
	}
}
/******************************************************************************/
/*%C                       Functionnal description :                          */
/*%C Sounds !	                                                              */
/*%C                                                                          */
/*%I  Input Parameter :                                                       */
/*%I		code : error code                                                 */
/*%IO Input/Output :                                                          */
/*%IO		NONE                                                              */
/*%O  Output Parameter :                                                      */
/*%O 		NONE                                                              */
/******************************************************************************/
static void PUST_Sound(void)
{	
	ARRET_INVOLONTAIRE = TRUE;
	SEC_BUZ = TRUE;
	LED_ALARME_ROUGE = TRUE;
	RAPPEL_ALARM = TRUE;
}
/******************************************************************************/
/*%C                       Functionnal description :                          */
//*%C Power Up Self Tests routine. Does no return if a problem occurs         */
/*%C                                                                          */
/*%I  Input Parameter :                                                       */
/*%I		UBYTE _ForceFail : if TRUE, enters infinite loop                 */
/*%IO Input/Output :                                                          */
/*%IO		NONE                                                              */
/*%O  Output Parameter :                                                      */
/*%O 		NONE                                                              */
/******************************************************************************/
void PUST_Checks(UBYTE _ForceFail, e_PUST_REQUEST _CheckRequest)
{ 
	e_PUST_ERROR_CODE rc = PUST_ERR_OK;
	
	if(_ForceFail == FALSE)
	{
		switch(_CheckRequest)
		{
			/* Check Ram */
			case PUST_RAM_CHECK_REQ:					
				rc = PUST_Check_Ram();	
			break;

			/* Check Flash CRC */
			case PUST_FLASH_CHECK_REQ:				
				rc = PUST_Check_Flash(FlashMapping);
			break;

			/* Check Reference Voltages */
			case PUST_REF_VOLTAGE_CHECK_REQ:
				rc = PUST_Check_RefVoltages();
			break;

			case PUST_EEPROM_CHECK_REQ:
				rc = PUST_ERR_EEPROM; 
			break;

			default :
				rc = PUST_ERR_UNKNOWN;		
			break;
		}
	}
	else
	{		
		rc = GetErrorCodeFromRequest(_CheckRequest);
	}

    /* update error code which is used by SEC_NMI_Trap and*/
    PUST_ERROR = rc;

   	if ( (rc != PUST_ERR_OK) 
	|| (_ForceFail == TRUE) )
	{
		/* On error, first sound ! */
		PUST_Sound();

		/* Then display error message if possible (if code present in flash !) */
		PUST_DisplayOnError(rc);		

		/* Once display has been updated, enter infinite loop */
		PUST_InfiniteLoop();
	}
	/* we can exit since no error was detected or no "force fail" request was received */
}