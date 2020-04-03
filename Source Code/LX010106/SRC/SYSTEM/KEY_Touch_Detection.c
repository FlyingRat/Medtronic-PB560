/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : KEY_Touch_Detection.c                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Key press detection                                            */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : Touch                                                  */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : Result                                                */
/******************************************************************************/

/******************************************************************************/
/*                              INCLUDE FILES		                           */
/******************************************************************************/
#ifndef _TASKING
#include "LH_ST10F276.h"
#include <intrins.h>
#else
#include "regf276e.h"
#endif	
#include "typedef.h"
#include "enum.h"
#include "io_declare.h"
#include "System_Datas.h"

#define DECLARATION_KEY_TOUCH_DETECTION
#include "KEY_Touch_Detection.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/


UWORD16 KEY_Touch_Detection(e_SYS_KeyboardInput Touch)
{
	UWORD16 Result = 0;
 	UWORD16 Key_Port = 0;
/*%C RAZ of the COMx outputs :*/
/*%C The result of a "AND" mask between "KEY_PORT" and	*/
/*%C "SYS_KeyboardMatrice[Touch - Mark_Begin_Simple_Touch].Colum" is stored*/
/*%C into "KEY_PORT" */
   Key_Port = KEY_PORT;											   
   KEY_PORT = Key_Port 
	         & SYS_KeyboardMatrice[Touch - Mark_Begin_Simple_Touch - 1].Colum;
	
/* Small delay, to let the signal get its true value*/
	_nop_();
	_nop_();

/*%C Reading of the input depending on the key requested on parameter :  */
/*%C if the result of a "AND" mask between "KEY_PORT" and	*/
/*%C "SYS_KeyboardMatrice[Touch - Mark_Begin_Simple_Touch].Line" is equal */
/*%C to "0x0000",then "Result" get a "TRUE" value */
/*%C flag get a "TRUE" value,else it get a "FALSE" value.*/
	Key_Port = KEY_PORT;
	Key_Port = Key_Port 
	         & SYS_KeyboardMatrice[Touch - Mark_Begin_Simple_Touch - 1].Line;
	if (Key_Port == 0x0000)
	{
	   Result = TRUE;
	}
	else
	{ 
	   Result = FALSE;
	}
/*%C RAZ of the outputs : */
/*%C The result of a "OR" mask between "KEY_PORT" and  "RAZ_COM" is stored */
/*%C into "KEY_PORT" */
  	KEY_PORT = KEY_PORT | (UWORD16)RAZ_COM;

/* Small delay, to let the signal get its true value*/
	_nop_();
	_nop_();

   return (Result);
}

