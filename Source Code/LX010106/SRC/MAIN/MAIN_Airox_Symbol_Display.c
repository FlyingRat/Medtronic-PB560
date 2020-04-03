/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : MAIN_Airox_Symbol_Diplay.c                                   	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C       It displays the "AIROX" symbol                     						*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                           */
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
#include "Driver_Display_Data.h"
#include "MAIN_Airox_Symbol_Display.h"					 
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void MAIN_Airox_Symbol_Display(void)
{
	UWORD16 _Col, _Col2, _Col3;
	UWORD16 _Logo, _Logo2, _Logo3;
	UWORD16 _Line;
	 	
/*%C Display request*/
	DRV_DIS_HostRequest(1) ;

/*%C Timer launch for 1ms step scheduler	*/
/*%C Timer2 underflow flag reset				*/
	T2IR = 0;			T2IC = 0;
/*%C Timer2 delay = 1ms (5000 * 200ns)		*/
	T2 = 5000;   	
/*%C Count down, prescaler 200nS FCPU/8, start timer		*/
	T2CON  = 0x00C0;   
	while (MASTERBUSY && (T2IR == 0));
/*%C Stop Timer 2		*/
	T2CON = 0x0000;     
/*%C Page 1,2 and 3 erase */
	DIS_ErasePage(PAGE3);
	DIS_ErasePage(PAGE2);
	DIS_ErasePage(PAGE1);
/*%C Page 3 display */
	DIS_DisplayPage ( PAGE3, PAGEON );

/*%C Airox symbol display */
_Col = 30;
_Col2 = 218;
_Col3 = 242;
_Logo = LOGO_LEGENDAIR;
_Logo2 = TRADEMARK;

#if defined(LEGENDAIR_XL2)
	_Logo3 = LOGO_XL2;
#elif defined(LEGENDAIR_S2)
	_Logo3 = LOGO_S2;
#elif defined(SUPPORTAIR_M2)
	_Logo3 = LOGO_M2;
#endif

/* ... second part */
	_Line = 110;

	DIS_Symbol((UBYTE)_Logo, (UBYTE)_Line, _Col, (UBYTE)PAGE3);
	DIS_Symbol((UBYTE)_Logo2, (UBYTE)_Line, _Col2, (UBYTE)PAGE3);
	DIS_Symbol((UBYTE)_Logo3, (UBYTE)_Line, _Col3, (UBYTE)PAGE3);

/*%C Display request*/
	DRV_DIS_HostRequest (0) ;
/*%C 1,5 sec temporization for RTC loading*/
	TIM_Temporize(1500000);
}
