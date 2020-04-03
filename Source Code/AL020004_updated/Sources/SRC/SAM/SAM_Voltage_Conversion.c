/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SAM_Voltage_Conversion.c													*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                   Gestion des conversions de tensions		   				*/
/******************************************************************************/
/*%I Input Parameter :  CanValue                                              */
/*%I							VoltageMeasureType												*/
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : Compute																*/
/******************************************************************************/


/******************************************************************************/
/*                                INCLUDE FILES											*/
/******************************************************************************/
#include "typedef.h"
#include "enum.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
UWORD16 SAM_Voltage_Conversion(UWORD16 CanValue, 
							   e_SAM_Voltage VoltageMeasureType)
{
	UWORD32 Compute = 0;
	
	/*%C Voltage choice conversion   				*/
	switch (VoltageMeasureType)
	{
		/*%C VACDC conversion   				*/
		case Sampling_VACDC :
		{
			/*%C VACDC = (R19+R22)/R22  * Vref/1023*CanValue  */
			/*%C R19=110K ; R22=10K ; Vref = 3.00V */
			/*%C VACDC = 0.0351906 * CanValue */
			Compute  = 3603 * (UWORD32) CanValue;
			Compute = Compute>>10;
			
			break;
 		}

		/*%C VDC conversion   				*/
		case Sampling_VDC :
		{
			/*%C VDC = (R33+R35)/R35  * Vref/1023*CanValue  */
			/*%C R33=110K ; R35=10K ; Vref = 3.00V */
			/*%C VDC = 0.0351906 * CanValue */
			Compute  = 3603 * (UWORD32) CanValue;
			Compute = Compute>>10;

			break;
 		}

		/*%C VBAT conversion   				*/
		case Sampling_VBAT :
		{
			/*%C VBAT = (R44+R47)/R47  * Vref/1023*CanValue  */
			/*%C R44=100K ; R47=10K ; Vref = 3.00V */
			/*%C VBAT = 0.0322580 * CanValue */
			Compute  = 3303 * (UWORD32) CanValue;
			Compute = Compute>>10;

			break;
 		}

		/*%C 5V conversion   				*/
		case Sampling_5V :
		{
			/*%C MES_5V = (R72+R70)/R72 * Vref/1023*CanValue  */
			/*%C R70=10K ; R72=10K ; Vref = 3.00V */
			/*%C MES_5V = 0.00586510 * CanValue */
			Compute  =  600 * (UWORD32) CanValue;
			Compute = Compute>>10;
	
			break;
 		}

		/*%C 3V3 conversion   				*/
		case Sampling_3V3 :
		{
			/*%C MES_3V3 = (R56+R57)/R57 * Vref/1023*CanValue  */
			/*%C R56=10K ; R57=10K ; Vref = 3.00V */
			/*%C MES_3V3 = 0.00586510 * CanValue */
			Compute  = 600 * (UWORD32) CanValue;
			Compute = Compute>>10;

			break;
 		}

		/*%C 24V conversion   				*/
		case Sampling_24V :
		{
			/*%C MES_24VUTIL = (R64+R66)/R66 * Vref/1023*CanValue  */
			/*%C R66=10K ; R64=100K ; Vref = 3.00V */
			/*%C MES_24VUTIL = 0.0322580 * CanValue */
			Compute  = 3303 * (UWORD32) CanValue;
			Compute = Compute>>10;

			break;
		}

		/*%C VCharge conversion   				*/
		case Sampling_VCharge :
		{
			/*%C MES_VCharge = (R81+R90)/R90 * Vref/1023*CanValue  */
			/*%C R90=10K ; R81=100K ; Vref = 3.00V */
			/*%C MES_VCharge = 0.0322580 * CanValue */
			Compute  = 3303 * (UWORD32) CanValue;
			Compute = Compute>>10;

			break;
 		}

		default:
		{
			break;
		}
	}
	return Compute;
}


