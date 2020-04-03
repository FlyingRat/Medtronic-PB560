/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_KeyboardEvent.h */
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C Functionnal description : 	datas declaration for Keyboard EVent base   */
/*                                                                            */
/******************************************************************************/
/*%I 	Input Parameter : 			None			      	                       	*/
/*%IO Input/Output Parameter : 	None 	        			                  		*/
/*%O 	Output Parameter : 			None				            				  		*/
/******************************************************************************/
#ifndef KEYBOARD_EVENT_H
#define KEYBOARD_EVENT_H

#include "typedef.h"

/******************************************************************************/
/*                     ENUM DECLARATION				                         	*/
/******************************************************************************/
typedef enum
{
	KEYBOARD_UP_EVENT_U16 = 0,
	KEYBOARD_DOWN_EVENT_U16,
	KEYBOARD_VALID_EVENT_U16,
	KEYBOARD_INHIB_EVENT_U16,  
	KEYBOARD_INHIB_IT_GEN_EVENT_ARRAY_U16,		
	KEYBOARD_IT_GEN_EVENT_U16,
	KEYBOARD_IT_OFF_EVENT_U16,
	KEYBOARD_START_VENTIL_DOWN_EVENT_U16,
	KEYBOARD_START_VENTIL_UP_EVENT_U16,
	KEYBOARD_STOP_VENTIL_EVENT_U16,
	KEYBOARD_CONFIRM_STOP_VENTIL_EVENT_U16,
	KEYBOARD_LOCK_EVENT_U16,
	KEYBOARD_LONG_VALID_EVENT_U16,
	KEYBOARD_LONG_DOWN_EVENT_U16,
	KEYBOARD_LONG_UP_EVENT_U16,
	KEYBOARD_BRIGHTNESS_UP_EVENT_U16,
	KEYBOARD_BRIGHTNESS_DOWN_EVENT_U16,
	KEYBOARD_LONG_INHIB_EVENT_U16,
	KEYBOARD_DOUBLE_PULSE_INHIB_EVENT_U16,
	KEYBOARD_NAVIG_EVENT_U16,
	KEYBOARD_LONG_NAVIG_EVENT_U16,
   KEYBOARD_100_FIO2,
   KEYBOARD_LONG_100_FIO2,
    KEYBOARD_NAVIG_IT_GEN_EVENT_U16,	 
	end_of_db_Keyboard_Event_table
} e_DB_KEYBOARD_EVENT_ID;

#ifdef DECLARATION_EVENT_BASE
/******************************************************************************/
/*                     ARRAY DECLARATION			                         	*/
/******************************************************************************/
/* Base Keyboard event array */
UWORD16 DB_KeyboardEvent[end_of_db_Keyboard_Event_table];
#else
/******************************************************************************/
/*                     EXTERNAL ARRAY DECLARATION                            */
/******************************************************************************/
/* Base Keyboard event array */
extern UWORD16 DB_KeyboardEvent[end_of_db_Keyboard_Event_table];
#endif

#endif
