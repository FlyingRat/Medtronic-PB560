/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SAM_Temperature_Conversion.c									  			*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                 Conversion de la mesure de temperature		   			  	*/
/******************************************************************************/
/*%I Input Parameter :  CanValue			  								  					*/
/*%I                    TemperatureMesureType                   			  		*/
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : Valeur convertie en °C                                */
/******************************************************************************/


/******************************************************************************/
/*                                INCLUDE FILES								  			*/
/******************************************************************************/
#include "typedef.h"
#include "enum.h"



const UWORD16 TempConvTable_Ambiante[12][2]={{978,-3000},{941,-2000},{883,-1000},
													{798,0},{692,1000},{572,2000},
													{453,3000},{344,4000},{256,5000},
													{187,6000},{136,7000},{99,8000}};


const UWORD16 TempConvTable_Batterry[12][2]={{939,-3000},{891,-2000},{828,-1000},
													{749,0},{657,1000},{560,2000},
													{464,3000},{377,4000},{301,5000},
													{237,6000},{186,7000},{146,8000}};

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
SWORD16 SAM_Temperature_Conversion(	UWORD16 CanValue, 
									e_SAM_Temperature TemperatureMesureType)
{

	SWORD32 Compute1 = 0;
	SWORD32 Compute2 = 0;
	UWORD16 IndexSegment = 0;

	/*%C Ce tableau définit les segments de linéarisation. */
	/*%C 				Champ 0 : valeur du can */
	/*%C 				Champ 1 : température (en 10ième de degré) correspondante */



	/*%C Temperature conversion choice (ambient or battery temperature) */
	switch(TemperatureMesureType)
	{
		/*%C Ambient temperature conversion */
		case Sampling_T_Ambiant :
		{
			/*%C Segment interpolation computing */
			/*%C Value saturation: Can Value limits [99 ; 977)*/
			/*%C  				  => compute limits [8000; -3000] */
			if (CanValue > 977)
			{
				Compute1 = -3000 ;
			}
			else if (CanValue < 99)
			{
				Compute1 = 8000 ;
			}
			else
			{
				while (CanValue < TempConvTable_Ambiante[IndexSegment][0])
				{
					IndexSegment++;
				}

				Compute2 = 100000 / (TempConvTable_Ambiante[IndexSegment-1][0] - TempConvTable_Ambiante[IndexSegment][0]);
				Compute1 =(Compute2 * (TempConvTable_Ambiante[IndexSegment-1][0] - CanValue)) / 100 + TempConvTable_Ambiante[IndexSegment-1][1];
			}
			break;	
		}

		/*%C Battery temperature conversion */
		case Sampling_T_Battery :
		{
	
			/*%C Ce tableau définit les segments de linéarisation. */
			/*%C 				Champ 0 : valeur du can */
			/*%C 				Champ 1 : température (en 10ième de degré) correspondante */

	
			/*%C Calcul par linéarisation par segments */
			if (CanValue > 938)
			{
				Compute1 = -3000 ;
			}
			else if (CanValue < 146)
			{
				Compute1 = 8000 ;
			}
			else
			{
				while (CanValue < TempConvTable_Batterry[IndexSegment][0])
				{
					IndexSegment++;
				}
				Compute2 = 100000 / (TempConvTable_Batterry[IndexSegment-1][0] - TempConvTable_Batterry[IndexSegment][0]);
				Compute1 =(Compute2 * (TempConvTable_Batterry[IndexSegment-1][0] - CanValue)) / 100 + TempConvTable_Batterry[IndexSegment-1][1];
			}	
			break;
		}
		default:
		{
			break;
		}	
	}
	return (SWORD16)Compute1;
}
