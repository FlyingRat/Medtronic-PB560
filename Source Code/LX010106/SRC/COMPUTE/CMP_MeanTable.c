/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CMP_MeanTable.c     	 		                           		  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   This function computes mean value of a sample in a table    			  */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "Ventilation_Datas.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

SWORD32 CMP_MeanTable(SWORD16 Stop, UWORD16 Sample, SWORD32 Table[], UWORD16 TableLenght)
{
	UWORD16 j = 0;	
	SWORD32 Mean = 0;
	SWORD16 Start = 0;

	// Détermination de l'indice de pointeur de départ pour éffectuer la moyenne 
	Start = Stop - Sample;
	Start = Start + 1;
		if (Start < 0)
		{
			Start = TableLenght + Start;
		}

	// Calcule de la somme entre l'indice de début et l'indice de fin.
	if (Start <= Stop)
	{
		for (j = (UWORD16)Start; j <= Stop; j ++)
		{
			Mean += (SWORD32)Table[j];
		}
	}
	else
	{ 
		for (j=0; j<= Stop;j++)
		{
			Mean += (SWORD32)Table[j];
		}
		for (j = (UWORD16)Start; j < TableLenght; j ++)
		{
			Mean += (SWORD32)Table[j];
		}
	}
	// Calcule de la moyenne.
	Mean = Mean / (SWORD32)Sample;
	return (Mean);
}

