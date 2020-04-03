/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CYC_TiLimitsCompute.c */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           It allows to compute the Timin and Ti max for the modes  		*/
/*%C				PSVTv VSIMV and PSIMV          											*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                            		*/
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : t_CYC_TiLimit TiLimit                                 */
/******************************************************************************/

/******************************************************************************/
/*                              INCLUDE FILES		                           */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "define.h"
#include "DB_Current.h"
#include "DB_Compute.h"
#include "Ventilation_Cycles_Datas.h"
#include "CYC_TiLimitsCompute.h"


/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

t_CYC_TiLimit CYC_TiLimitsCompute(void)	
{

/* Ti max auto select flag recovery from base                                 */
UWORD16 TiMaxAutoSelect = DB_CurrentRead(TI_MAX_AUTO_SELECT_U16);
/* Ti min auto select flag recovery from base                                 */
UWORD16 TiMinAutoSelect = DB_CurrentRead(TI_MIN_AUTO_SELECT_U16);
/* Ti max value recovery from base 				                                 */
UWORD16 AdjustTiMax = DB_CurrentRead(ADJUST_TI_MAX_U16);
/* Ti min value recovery from base                 				               */
UWORD16 AdjustTiMin = DB_CurrentRead(ADJUST_TI_MIN_U16);
/* Rise time recovery from base   					                              */
UWORD16 RiseTime = DB_CurrentRead(RISE_TIME_U16);
/* Measure rate recovery from base           				                     */
UWORD16 MeasureR = DB_ComputeRead(MEASURE_R_U16);

UWORD16 TiMaxAuto = 0;
UWORD16 TiMinAuto = 0 ;
t_CYC_TiLimit TiLimit;

/******************************************************************************/
/*%C                    Select the effective TiMin :               */
/******************************************************************************/

/*%C Compute of the Auto Ti Min depending on the adjusted Rise time + 300ms*/
	TiMinAuto = RiseTime + cVEN_300MS;
/*%C If TiMinAutoSelect is TRUE, then the Auto Ti MIN is theTiMinAuto value  */
/*%C else the adjusted Ti Min is selected. */
	if(TiMinAutoSelect == TRUE)
	{
		TiLimit.TiMin = TiMinAuto;
	}
	else
	{
		TiLimit.TiMin = AdjustTiMin;
	}

/* If the Ti Min is lower than the computed auto Ti Min, then	 */
	if(TiLimit.TiMin < TiMinAuto)
	{
/*%C  Ti Min value is set to the computed auto Ti Min value */
		TiLimit.TiMin = TiMinAuto;
	}

/*%C 	Ti Min writing in the Current base, if ti min auto is selected */
	if(TiMinAutoSelect == TRUE)
	{
		DB_CurrentWrite(ADJUST_TI_MIN_U16, TiLimit.TiMin); 
	}
/******************************************************************************/
/*%C                Select the effective TiMax :									*/
/******************************************************************************/

/*%C Compute of the Auto Ti Max depending on	the frequency measure "R" : */
/*%C 	TiMaxAuto(ms) = (30/R)*1000	 */
	if (MeasureR == 0)
	{
		MeasureR = cDEFAULT_MESURE_R;	
	}
	TiMaxAuto = (30000U / MeasureR);
/*%C It must be rounded at 0.1s , to be able to be displayed. */
	TiMaxAuto = TiMaxAuto - (TiMaxAuto%TI_MAX_STEP);                         
/*%C If TiMaxAutoSelect is TRUE, then the Auto Ti Max is the computed value */
/*%C else the adjusted Ti Max is selected. */
	if(TiMaxAutoSelect == TRUE)
	{
		TiLimit.TiMax = TiMaxAuto;
	}
	else
	{
		TiLimit.TiMax = AdjustTiMax;
	}
/*%C If the Ti Max is upper than the computed auto Ti Max, then	 */
	if(TiLimit.TiMax > TiMaxAuto)
	{
/*%C  Ti Max value is set to the computed auto Ti Max value */
		TiLimit.TiMax = TiMaxAuto;
	}
/*%C If the Ti Max is upper than 3s, then	 */
	if(TiLimit.TiMax > cVEN_3S)
	{
/*%C  Ti Max value is set to 3s */
		TiLimit.TiMax = cVEN_3S;
	}

/*%C If the Ti Max is upper than the  Ti Min, then	 */
	if(TiLimit.TiMax < TiLimit.TiMin)
	{
/*%C  Ti Max value is set to Ti Min value */
		TiLimit.TiMax = TiLimit.TiMin;
	}

/*%C 	Ti Min writing in the Current base, if ti min auto is selected */
	if(TiMaxAutoSelect == TRUE)
	{
		if(TiLimit.TiMax <= TI_MAX_MIN)
		{
			TiLimit.TiMax = TI_MAX_MIN;
		}
		if(TiLimit.TiMax >= TI_MAX_MAX)
		{
			TiLimit.TiMax = TI_MAX_MAX;
		}
		DB_CurrentWrite(ADJUST_TI_MAX_U16, TiLimit.TiMax); 
	}
/*%C Ti Max writing in the Compute base */


return(TiLimit);

}
