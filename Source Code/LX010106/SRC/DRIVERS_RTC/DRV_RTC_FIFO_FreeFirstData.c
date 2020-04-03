/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_RTC_FIFO_FreeFirstData.c                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                     */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
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
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "define.h"
#include "DRV_RTC_FIFO_FreeFirstData.h"
#include "RTC_Driver_Data.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

BIT DRV_RTC_FIFO_FreeFirstData(void)
{
	if (RTC_FIFO_NbDataInFifo <= 0)
		{	
		return(FALSE);
		} 
	else
		{
		RTC_FIFO_NbDataInFifo--;
		}
	RTC_FIFO_AccessDriver[RTC_FIFO_IdxPull].ptr_data = NULL;	
	RTC_FIFO_AccessDriver[RTC_FIFO_IdxPull].regist 	 = RTC_SECOND;	
	RTC_FIFO_AccessDriver[RTC_FIFO_IdxPull].state    = FREE_RTC;
/*%C Computing of the new index for writing in buffer "fifo"	 */
	if (RTC_FIFO_IdxPull < (SIZE_OF_FIFO_RTC_ACCESS-1))
		{
		RTC_FIFO_IdxPull++;		
		}
	else 
		{
		RTC_FIFO_IdxPull=0;		
		}
	return (TRUE);
}
