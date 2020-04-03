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
#include "p18f6622.h"
#include "typedef.h"
#include "define.h" 
#include "enum.h"
#include "IO_Declare.h"
#include "PUST.h"
#include "PUST_crc8.h"
#include "LOG.h"

extern void read_AA_error(void);

/* Static routines */
static e_MEM_ERROR_CODE PUST_Check_Flash(T_FLASH_MEM_RANGE* PtMem);
static void PUST_InfiniteLoopFlashLeds(void);

/* Globals */
static T_FLASH_MEM_RANGE FlashMapping[FLASH_MEM_RANGE_MAX+1] = {
                                                                 {TRUE, 0x0,  MEM_END_CODE_AND_CONST},
																 {TRUE, 0x300000,  0x30000D},
                                                                 {FALSE, 0      , 0} 
                                                               }; /* --> end of struct table identifier */


static ram UBYTE FlashCalculatedCrc = 0;
static ram UBYTE FlashRomedCrc = 0;


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
static e_MEM_ERROR_CODE PUST_Check_Flash(T_FLASH_MEM_RANGE* PtMem)
{
	UBYTE CalculatedCrc;

	CalculatedCrc = PUST_CalcCrc8(PtMem);
	FlashCalculatedCrc = CalculatedCrc;
	
	FlashRomedCrc = *(far rom UBYTE *) MEM_CRC_ADDRESS;
	
	return ((CalculatedCrc == FlashRomedCrc)? MEM_ERR_OK:MEM_ERR_CRC);
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
void PUST_Checks(UBYTE _ForceFail)
{ 
	e_MEM_ERROR_CODE rcChkFlash = MEM_ERR_OK;
		
	if(_ForceFail == FALSE)
	{
		/* Check FLASH CRC */
		rcChkFlash = PUST_Check_Flash(FlashMapping);
	}
	else
	{
		rcChkFlash = MEM_ERR_FORCED_FAIL;
	}

   	if ( (rcChkFlash != MEM_ERR_OK) || 
		 (_ForceFail == TRUE) )
	{
		/* On error, infinite loop + flash leds ! */
		PUST_InfiniteLoopFlashLeds();
	}
	/* we can start since all memory locations seem correct */

	LOG_DEBUG(CFG_LOG_MOD_PUST, "Calculated crc = %02X", FlashCalculatedCrc);
	LOG_DEBUG(CFG_LOG_MOD_PUST, "Romed crc = %02X", FlashRomedCrc);
    LOG_DEBUG(CFG_LOG_MOD_PUST, "CRC is correct !!!");
}
/******************************************************************************/
/*%C                       Functionnal description :                          */
/*%C Enters an infinite loop refreshing hardware and software wdogs and       */
/*%C flashing leds 		                                                      */
/*%C                                                                          */
/*%I  Input Parameter :                                                       */
/*%I		code : error code                                                 */
/*%IO Input/Output :                                                          */
/*%IO		NONE                                                              */
/*%O  Output Parameter :                                                      */
/*%O 		NONE                                                              */
/******************************************************************************/
static void PUST_InfiniteLoopFlashLeds(void)
{
	/* On appelle la boucle infinie de clignottement des LEDs */
	read_AA_error();
}
