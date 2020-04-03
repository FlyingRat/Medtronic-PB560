/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : Average.c					                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           Average computing					                                 */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : *Data                                                  */
/*%I Input Parameter : Size                                                  */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : DataCumul / Size                                      */
/******************************************************************************/

/************************************************************************/
/*                           INCLUDE FILES		                        */
/************************************************************************/
#ifndef _TASKING
#include <intrins.h>
#endif
#include "typedef.h"


/******************************************************************************/
/*                        FUNCTION DECLARATION	    		                     */
/******************************************************************************/
UWORD16 average(UWORD16 *Data,
					 UWORD16 Size) 
{
UWORD16 i;
UWORD32 DataCumul = 0;
UWORD32 Reste = 0;

/*%C Average Compute of a sum of values */
/*%CThe @ of value and the size are sent to the function */	
   for(i=0; i<Size; i++)
      {
      DataCumul = DataCumul + (UWORD32)Data[i];
	  }
/*%C Average calculation */
	DataCumul = (DataCumul*10L) / (UWORD32)Size;
/*%C Average rounded to +1 */
	Reste = DataCumul % 10;
	if( Reste >= 5) 
	{
		DataCumul = DataCumul + 10;
	}
/*%CThe average is returned to the calling function */
	return ((UWORD16)DataCumul/10);
}