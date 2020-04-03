/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DIS_FifoWrite.c */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                  */
/******************************************************************************/
/*%I Input Parameter :  NONE                                            */
/*%IO Input/Output :    NONE	                                              */
/*%O Output Parameter : NONE       */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/

#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "Display_Data.h"
#include "Main_Data.h"
			 
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DIS_FifoWrite(UWORD16 DisplayFunction,UWORD16 Param1,UWORD16 Param2,UWORD16 Param3,UWORD16 Param4,
														 UWORD16 Param5,UWORD16 Param6,UWORD16 Param7,UWORD16 Param8,
														 UWORD16 Param9,UWORD16 Param10,UWORD16 Param11,UWORD16 Param12)
{
	//Si débordement de FIFO comptabilisation de débordement
	if((DIS_FifoIdxWrite + 1) % FIFO_DISPLAY_SIZE == DIS_FifoIdxRead)
		{
		DIS_FifoOverflow++;
		}
	//Si Fifo libre stockage des données d'affichage dans la FIFO
	else
		{	
		DIS_FifoDisplay[DIS_FifoIdxWrite].DisplayFunction = DisplayFunction;
		DIS_FifoDisplay[DIS_FifoIdxWrite].Param1 = Param1;
		DIS_FifoDisplay[DIS_FifoIdxWrite].Param2 = Param2;
		DIS_FifoDisplay[DIS_FifoIdxWrite].Param3 = Param3;
		DIS_FifoDisplay[DIS_FifoIdxWrite].Param4 = Param4;
		DIS_FifoDisplay[DIS_FifoIdxWrite].Param5 = Param5;
		DIS_FifoDisplay[DIS_FifoIdxWrite].Param6 = Param6;
		DIS_FifoDisplay[DIS_FifoIdxWrite].Param7 = Param7;
		DIS_FifoDisplay[DIS_FifoIdxWrite].Param8 = Param8;
		DIS_FifoDisplay[DIS_FifoIdxWrite].Param9 = Param9;
		DIS_FifoDisplay[DIS_FifoIdxWrite].Param10 = Param10;
		DIS_FifoDisplay[DIS_FifoIdxWrite].Param11 = Param11;
		DIS_FifoDisplay[DIS_FifoIdxWrite].Param12 = Param12;
		DIS_FifoIdxWrite++;
		if (DIS_FifoIdxWrite >= FIFO_DISPLAY_SIZE) DIS_FifoIdxWrite = 0; 
		}
}