/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : MAIN_Global_Variables_Init.h                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C       It is the initialization  of global variables which are not */
/*%C		be initialized during their declarations.                            */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/
#ifndef MAIN_GLOBAL_VARIABLES_INIT_H
#define MAIN_GLOBAL_VARIABLES_INIT_H

#define BOTTOM_BOOT     	   		0x22AB		// Memoire de type bottom boot ex 29F400BB
const UWORD16 SYS_InitTimerKey[Number_of_key] = {
/* Respect the ordere of the enum "e_SYS_KeyboardInput" */
/* KEY_NO_KEYBOARD */
0,
/* KEY_CODE_MONIT_AND_DOWN */			  
1000,
/* KEY_CODE_MONIT_AND_UP */		  
1000,
/* KEY_CODE_UP_AND_DOWN */		  
3000,
/* Mark */
0,
/* KEY_CODE_UP */		  
1000,
/* KEY_CODE_DOWN */		  
1000,
/* KEY_CODE_VALID */		  
3000,
/* KEY_CODE_MONIT */		  
3000,
/* KEY_CODE_STARTSTOPVENTIL */		  
3000,
/* KEY_CODE_100_O2 */		  
3000, 		  
/* KEY_CODE_NAVIG */		  
3000 		  
};

#endif