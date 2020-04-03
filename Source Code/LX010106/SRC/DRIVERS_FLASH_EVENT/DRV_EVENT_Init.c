/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_EVENT_Init.c                                     				*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                     																		*/
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
#include "define.h"
#include "DB_Config.h"
#include "DRV_EVENT_Init.h"
#include "Flash_Event_Data.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_EVENT_Init(void)
{
UWORD16 Adress_Calcul_Msb, Adress_Calcul_Lsb; 

/*%C Computing the adress of end of programation */
	End_Of_Event_Flash = (EVENT_FLASH_END_ADDRESS - EVENT_FLASH_START_ADDRESS) / EVENT_Last_Event_Parameter;
	End_Of_Event_Flash = End_Of_Event_Flash * EVENT_Last_Event_Parameter;

/*%C	Compute of the index adress*/		
	Adress_Calcul_Msb = DB_ConfigRead(RETRIEVAL_EVENT_ADRESS_MSB_U16);
	Adress_Calcul_Lsb = DB_ConfigRead(RETRIEVAL_EVENT_ADRESS_LSB_U16);
	Ptr_Flash = (UWORD16 xhuge *)((UWORD32)(Adress_Calcul_Msb * 65536) + Adress_Calcul_Lsb);

/*%C Blank Flash verification */
	DRV_EVENT_BlankCheck();
}
