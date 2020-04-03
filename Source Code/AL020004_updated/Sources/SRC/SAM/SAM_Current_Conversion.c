/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SAM_Current_Conversion.c										  			*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                   Conversion des mesures de courant		   			  		*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


/******************************************************************************/
/*                                INCLUDE FILES								  			*/
/******************************************************************************/

#include "typedef.h"
#include "enum.h"
#include "DB_Config.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
SWORD16 SAM_Current_Conversion(UWORD16 CanValue ,
							   e_SAM_Current CurrentMesureType)
{
	/*%C */
	SWORD32 Compute = 0;

	switch(CurrentMesureType)
	{
		case Sampling_I_Battery :
		{
			/*%C Mesure Ibat (V) = Vréf * R55/R107 +/- Ibat(A)*R45*R55/1000		*/
			/*%C R45=0.015 ; R55=40.2K ; R107=66.5K ; Vréf = 3.00V 					*/
			/*%C Mesure Ibat (V) = 1.813533 +/- 0.603 Ibat(A)							*/
			/*%C Ibat(A) = (Mesure Ibat (V) - 1.813533)/0.603 							*/
			/*%C Mesure Ibat = CanValue * Vréf/1023										*/
			/*%C Ibat(A) = (CanValue*Vréf/1023 - 1.813533)/0.603						*/
			/*%C Ibat(A) = (CanValue * 2.93255E-3 - 1.813533)/0.603					*/
			/*%C Ibat(mA) = (CanValue * 2.93255 - 1813533) / 0.603					*/
			/*%C Ibat(10emme de mA) = (CanValue * 29325 - 18135330) / 603			*/
			/*%C 			==> CAN (pour Ibat = 0) = 618 									*/
			Compute = (SWORD32)CanValue;	
			Compute = Compute * 29325;
			Compute = Compute - 18135330;
			Compute /= 603;
			break;
		}
	
		default:
		{
			break;
		}
	}
	return (SWORD16)Compute;
}
