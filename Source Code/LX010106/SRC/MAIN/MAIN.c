/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : MAIN.c                                                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C          It is the entry point, the "main", of the software :            */
/*%C          It initializes the processor target (registers and variables)   */
/*%C          and launch the scheduler.                                       */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/
#define DECLARATION_MAIN_DATA

#ifndef _BORLAND
 #ifndef _TASKING
  #pragma PECDEF (0,1,2,3,4,5,6,7)
 #endif
#endif

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
#include "Structure.h"
#include "SCHED_Ventilation_Scheduler_Config.h"	
#include "Main_Data.h"
#include "DB_Event.h"
#include "DB_Config.h"
#include "DB_Control.h"
#include "DRV_VarEeprom.h"
#include "MAIN.h"
#include "PUST.h"


/* locate boot code to specific section */
#include "locate_boot_code.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void main(void)
{ 

    /* Instruction pour activer XPERCON dans l'émulateur - XPEREMU = Valeur de XPERCON */
	XPEREMU = 0x05AC;	

    /******************************************************************************/
    /*                         Target init														*/
    /*%C The function of target initialization is launched :                      */
    /*%C  - allowing the use of the emulator          										*/
    /*%C  - Watchdog setup            															*/
    /*%C  - service the watchdog 																	*/
    /*%C  - Input/Output port setup     														*/
 	MAIN_Target_Init();		

#ifdef MEM_TEST
	/* Memory test are performed only if MEM_TEST macro is defined from command line */

	/* Check RAM (already checked by startup code, only processes the error code */
	PUST_Checks((UBYTE)FALSE, PUST_RAM_CHECK_REQ);

	/* Check FLASH*/
	PUST_Checks((UBYTE)FALSE, PUST_FLASH_CHECK_REQ);	
#endif

#ifndef _TASKING
	/* Check reference voltages */
	PUST_Checks((UBYTE)FALSE, PUST_REF_VOLTAGE_CHECK_REQ);
#endif	

    /*%C Initialization phase start:            												*/
    /*%C This variable allows to inhib the watchdog during the initialization.   	*/
    /*%C If not made, a target reset can occur depending on the duration of the	*/
    /*%C initialization phase.                               							*/
	MAIN_End_of_init = FALSE;

    /******************************************************************************/
    /*%C Call of the function which initializes some global variables		*/
  	MAIN_Global_Variables_Init();

    /******************************************************************************/

    /*%C This is the Bit number 11 of PSW (Program Status Word) register.         */
    /*%C It allows all the interupts. */ 
  	IEN = 1;

    /*%C This variable is use in the peripheral initialization function : 			*/
    /*%C Indeed, the initialization of these interfaces has got 2 phases :			*/
    /*%C the first must be done before the "version error management" (init of the*/
    /* EEEPROM), and the second is done after	*/
 	MAIN_Interfaces_Second_Init = FALSE;

    /*%C Call of the  interfaces initialisation function */
 	MAIN_Interfaces_Init();

    /******************************************************************************/
    /*%C NAND flash memory recognition */
	DRV_NAND_ReadID();
    /*%C NAND flash memory bad blocks detection  */         
 	MAIN_NAND_Flash_Bad_Block_Detection();
    /*%C The bad block map is loaded into an array */
 	MAIN_NAND_Flash_Bad_Block_Read();	

    /******************************************************************************/
    /*%C Leds, Backlight, and Buzzers must be tested, so the function below */
    /*%C is called */   
  	MAIN_Leds_Backlight_Buzzers_StartControl();


    /******************************************************************************/
    /*%C The function below checks the software version anomaly writed into EEPROM*/
    /*%C If an version error alarm is detected, then the software warns with */
    /*%C a message, and goes into a "standby mode" (infinite loop).       */
 	MAIN_Version_Error_Mngt();


    /******************************************************************************/
    /*%C "AIROX" logo display function call						                 		*/
 	MAIN_Airox_Symbol_Display();

    /******************************************************************************/

    /*%C Delay of 1s to let the RTC reload                                       	*/
  	TIM_Temporize(1000000);

    /******************************************************************************/
    /*% the second phase of interfaces initialization is launched             		*/
	MAIN_Interfaces_Second_Init = TRUE;
 	MAIN_Interfaces_Init();

    /*%C Tasks initialization function call						                     */
 	MAIN_Tasks_Init();

    /*%C End of the initialization, the watchdog can be allowed  						*/
	MAIN_End_of_init = TRUE;



    /******************************************************************************/
    /*%C                       SCHEDULER CHOICE												*/
    /******************************************************************************/

    /*%C If the inhibition key is press with no unvolontary stop   */
    /*%C then go to the "SETUP" application .*/
    /*%C So a specific "setup" HMI function, and a specific "setup" Scheduler */
    /*%C are launched.	*/
    /*%C An event is sent too at maintenance start.	*/

	if  ( (INHIB_DETECTED == FALSE)
     && (EEP_DB_Config[VENTIL_REQ_U16] == FALSE) 
         && (EEP_DB_Config[ADJUST_KEYLOCK_U16] == FALSE) )
   {
		DB_EventMngt(EVENT_MAINTENANCE_MENU_ACCESS);
  	 	SETUP_HMI_Start();
		DB_ControlWrite(MAINTENANCE_MODE_U16, TRUE);
        while (1)
		{
		   	SCHED_Setup_Main();
		}
  	}
    // if the NAVIG (page) key is pressed
    else if ( (KEY_Touch_Detection(KEY_CODE_NAVIG) == TRUE)
              && (EEP_DB_Config[VENTIL_REQ_U16] == FALSE) )
   {
        DB_EventMngt(EVENT_CIRCUIT_CHECK_MENU_ACCESS);
        CIRCUIT_CHECK_HMI_Start();
        DB_ControlWrite(CIRCUIT_CHECK_MODE_U16, TRUE);
        while (1)
        {
            SCHED_Setup_Main();
        }
    }
    else
    /*%C Else, a specific "ventilation" HMI function, and a specific "ventilation"*/
    /*%C Scheduler are launched.	*/
    {

		VENTILATION_HMI_Start();
        while (1)
		{

			SCHED_Ventilation_Main();
		}
	}
}
