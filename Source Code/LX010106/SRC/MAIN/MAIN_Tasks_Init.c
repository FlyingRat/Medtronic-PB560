/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : MAIN_Tasks_Init.c                                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C        It is the initializations of the main tasks :                     */
/*%C				- System																  			*/
/*%C				- Security															  			*/
/*%C				- Ventilation														  			*/
/*                                           											*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/
#include "MAIN_Tasks_Init.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void MAIN_Tasks_Init(void)
{


/*%C DRV_NAND_Flash_Init function call */
	DRV_NAND_Flash_Init();
/*%C System	Init function call															   */
  	MAIN_System_Init();
/*%C Ventilation Init function call														   */
	MAIN_Ventilation_Init();
/*%C Security Init function call														  		*/
	MAIN_Security_Init();
/*%C DRV_EVENT	Init function call															   */
  	DRV_EVENT_Init();
}