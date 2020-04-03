/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : RTC_FIFO_PushOneData.c                         */
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

#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "define.h"
#include "Main_Data.h"
#include "RTC_Driver_Data.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

UWORD16 DRV_RTC_FIFO_PushOneData(UWORD16  * access_ptr_data,
									  e_DRV_RTC_REGISTER access_register,
									  e_DRV_RTC_ACCESS_STATE access_type)
{
	// buffer non  saturé
	if (RTC_FIFO_NbDataInFifo < SIZE_OF_FIFO_RTC_ACCESS)	
		{	
			RTC_FIFO_NbDataInFifo++;
		}
	// buffer  saturé		
	else
		{
			return (FALSE);
		}
	// stockage dans le buffer "fifo" de l'adresse de la donnée à lire ou à écrire
	RTC_FIFO_AccessDriver[RTC_FIFO_IdxPush].ptr_data = access_ptr_data;
	// stockage dans le buffer "fifo" du type d'accés lecture,écriture,libération,erreur
	RTC_FIFO_AccessDriver[RTC_FIFO_IdxPush].state    = access_type;
	// stockage du registre de la RTC a accéder
	RTC_FIFO_AccessDriver[RTC_FIFO_IdxPush].regist   = access_register;
	
	//calcul du nouvel index d'écriture du buffer "fifo"
	if (RTC_FIFO_IdxPush < (SIZE_OF_FIFO_RTC_ACCESS-1))
		{
			RTC_FIFO_IdxPush++;	
		}
	else 
		{
		RTC_FIFO_IdxPush=0;
		}
	return (TRUE);
}