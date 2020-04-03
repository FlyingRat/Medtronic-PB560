/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_KeyboardEventWrite.c 														*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/* 			Description fonctionnelle:		 	                        	      */
/*                                                                      	   */
/* Ecriture dans la base "KeyboardEvent"                                      */
/*          	                                                               */
/*                                                            				      */
/******************************************************************************/
/*%I 	Input Parameter : 			Id   		        			                  	*/
/*%I 	Input Parameter : 			Value		        			                  	*/
/*%IO Input/Output Parameter : 	None 	        			                  		*/
/*%O 	Output Parameter : 			None      	                 				  		*/
/******************************************************************************/

/******************************************************************************/
/*                              INCLUDE FILES		                           */
/******************************************************************************/

#include "typedef.h"
#include "enum.h"
	#define DECLARATION_EVENT_BASE
#include "DB_KeyboardEvent.h"
#include "DB_Control.h"
#include "DB_Config.h"
#include "KEY_Event.h"

/******************************************************************************/
/*                       FUNCTION BODY               	                        */
/******************************************************************************/

void DB_KeyboardEventWrite(e_DB_KEYBOARD_EVENT_ID Id,
                           UWORD16 Value)
{
/*%C Writes the parameter value in the keyboard event array if the Id         */
/*%C parameter belongs to the keyboard event base                             */
   if (Id < end_of_db_Keyboard_Event_table)
   {
      DB_KeyboardEvent[Id] = Value;
   }
}