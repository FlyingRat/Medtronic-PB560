/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CMP_TimeComputing.c                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   This function computes the different time values :                     */
/*%C   - Ti                                                                   */
/*%C   - Te                                                                   */
/*%C   - Ti/Te ratio                                                          */
/*%C   - Rate                                                                 */
/*%C   - Ti/ (Ti + Te) ratio                                                  */
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
#include "DB_Compute.h"
#include "Ventilation_Datas.h"
#include "CMP_TimeComputing.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void CMP_TimeComputing(void)
{
    /* Ti measure local declaration                                               */
   UWORD16 Ti = 0;
    /* Te measure local declaration                                               */
   UWORD16 Te = 0;
    /* Ratio numerator  declaration                                               */
   UWORD32 Numerator = 0;
    /* Ratio denominator declaration                                              */
   UWORD32 Denominator = 0;
    /* Te measure local declaration                                               */
   UWORD32 Rate = 0;
    /* Round value declaration                                               		*/
   UWORD32 Round = 0;
    /* Measure I/T declaration                                               		*/
   UWORD32 Measure_IT = 0;
    /********************* TI MEASURE **************************/
    /*%C Ti measure (stored in compute base with a tenth second unit)             */
   Ti = VEN_TiTeValueMesured.TiValCount;
   DB_ComputeWrite(MEASURE_TI_U16,
	                Ti/100);
    /*%C Ti measure (stored in compute base in ms for HMI frame alarm)            */
   DB_ComputeWrite(MEASURE_TI_HMI_U16,
	                Ti);

    /********************* TE MEASURE **************************/
    /*%C Te measure (stored in compute base with a tenth second unit)             */
   Te = VEN_TiTeValueMesured.TeValCount;
   DB_ComputeWrite(MEASURE_TE_U16,
	                Te/100);

    /******************* RATIO MEASURE **************************/
    /*%C Ti/Te ratio                                                              */
    /*%C Gives the numerator and the denominator of the ratio (1 decimal)         */
    /*%C Ti < Te => ratio displayed: 1 / Te/Ti                                    */
   if (Ti < Te)
	{
		Numerator = 10;
      Denominator = ((UWORD32)Te * 10) / (UWORD32)Ti;	      
        /*%C  Denominator saturation - clipped in DB_ComputeWrite below */
	}
    /*%C Gives the numerator and the denominator of the ratio (1 decimal)         */
    /*%C Ti > Te => ratio displayed: Ti/Te / 1                                    */
   else
	{
      Numerator = ((UWORD32)Ti * 10) / (UWORD32)Te;
      Denominator = 10;	      
        /*%C 	Numerator saturation - clipped in DB_ComputeWrite below */
	}
    /*%C I/E numerator storage in compute base                                    */
   DB_ComputeWrite(MEASURE_IE_NUMERATOR_U16,
	                (UWORD16)Numerator);

    /*%C I/E denominator storage in compute base                                  */
   DB_ComputeWrite(MEASURE_IE_DENOMINATOR_U16,
	                (UWORD16)Denominator);

    /******************* RATE MEASURE **************************/
    /*%C Rate measure : Rate = 60 (Ti /Te) with Ti and Te in ms                   */
   Rate = (60L * 1000L) / (Ti + Te);
    /*%C Rounded value to the closer integer                   */
   Round = (10 * 60L * 1000L) / (Ti + Te) - 10 * Rate;
    /*%C If round > 5, rate is rounded to its superior value		                  */
	if (Round > 5)
	{
		Rate = Rate + 1;
	}
    /*%C Rate storage in compute base                                             */
   DB_ComputeWrite(MEASURE_R_U16,
	                (UWORD16)Rate);

    /******************* I/T MEASURE **************************/
    /*%C I/T measure : Measure I/T (%) = 100 * Ti /(Ti / Te)      */
   Measure_IT = ((UWORD32)Ti * 100) / ((UWORD32)Ti + (UWORD32)Te);
	Measure_IT = (UWORD32)saturation(Measure_IT,
								   01,
								   99);
    /*%C Rate storage in compute base                         */
   DB_ComputeWrite(MEASURE_IT_U16,
	                (UWORD16)Measure_IT);
}

