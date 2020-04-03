/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : Main_Carte_Alim.c            					                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C        			  										      					      */
/*%C          																					   */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/

#include "typedef.h"
#include "enum.h"
#include "Main_Carte_Alim.h"
#include "LOG.h"



/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void main(void)
{

	/*%C Init_CPU 																					*/
	INIT_CPU();

	/*%C Initialisation matérielle de la RS232											*/
	INIT_RS232_Driver();

	/*%C LOG initialisation) */
	LOG_INIT();

	LOG_DEBUG(CFG_LOG_MOD_PUST, "Device start...\r\n");

	#ifdef TEST_FLASH
		/*%C Contrôle de la FLASH																*/
		PUST_Checks((UBYTE)FALSE);
	#endif

	/*%C Init_DataBase																			*/
	INIT_DataBase();

	/*%C Initialisation du Sampling 															*/
	INIT_Sample();

	/*%C Initialisation des timers															*/
	INIT_Timer();
	
	/*%C Initialisation matérielle de la RS232											*/
	INIT_RS232_Driver();

	/*%C Place this Init before INIT_Interrupt_T0 										*/
	/*%C Init Leds 																				*/
	INIT_Leds();
	
	/*%C Initialisation du timer T0 du séquenceur										*/
	INIT_Interrupt_T0();

	/*%C Initialisation du convertisseur UART/1-Wire: DS2480B						*/
	INIT_EEPROM_BAT_Driver();

	/*%C Initialisation du timer T0 du séquenceur										*/
	INIT_SPI_ST10_Driver();

	/*%C Run_Scheduler 																			*/
	SCHED_Launch();
}
