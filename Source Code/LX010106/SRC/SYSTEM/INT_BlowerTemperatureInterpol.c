/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505				                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : INT_BlowerTemperatureInterpol.c                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C       Blower temperature sensor interpolation							         */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef _TASKING
#include "LH_ST10F276.h"
#else
#include "regf276e.h"
#endif	 
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "DB_Compute.h"
#include "Driver_Datas.h"
#include "INT_BlowerTemperatureInterpol.h"

void INT_BlowerTemperatureInterpol(void)
{

	SWORD32 TurbineTemperature = 0;
	UWORD16 IndexSegment = 0;
	UWORD16 CanValue = 0;
	static SWORD16 TurbineTempSample[10];
	static SWORD16 TurbineTempSampleNb = 0;
	static SWORD16 FilteredTurbineTemperature = 0;
 	SWORD16 TempCompute = 0;
	UWORD16 i = 0;

/*%C Interpolation segment declaration  													*/
/*%C 				Field 0 : CAN value  														*/
/*%C 				Field 1 : Temperature value (1/100 degree)							*/
	const SWORD32 TempConvTable[17][2]={{1024,-4600},{994,-3000},{975,-2000},
													{949,-1000}, {913,0},    {864,1000},
													{804,2000},	 {732,3000}, {653,4000},
													{570,5000},	 {489,6000}, {412,7000},
													{343,8000},	 {283,9000}, {232,10000},
													{191,11000}, {0,15600}};
/*%C Can Value refresh */
	CanValue = AD_Digit.MesBlowerTemp;
		
/*%C Segment detection function of CAN value */
	while (CanValue < TempConvTable[IndexSegment][0])
	{
		IndexSegment++;
	}
/* Prevent an out of bounds index in array TempConvTable[][]*/
    if (IndexSegment == 0)
        IndexSegment = 1;

/*%C Turbine temperature = 																	*/
/*%C (Can Value - TempConvTable[IndexSegment][0]) / 								 	*/
/*%C (TempConvTable[IndexSegment-1][0] - TempConvTable[IndexSegment][0]) *	 	*/
/*%C (TempConvTable[IndexSegment-1][1] - TempConvTable[IndexSegment][1]) +		*/
/*%C TempConvTable[IndexSegment][1]															*/
	TurbineTemperature = ((SWORD32)CanValue - TempConvTable[IndexSegment][0]) *
		  (TempConvTable[IndexSegment-1][1] - TempConvTable[IndexSegment][1]);

	TurbineTemperature = TurbineTemperature /	
		  (TempConvTable[IndexSegment-1][0] - TempConvTable[IndexSegment][0]);
	
	TurbineTemperature = TurbineTemperature + TempConvTable[IndexSegment][1];
	
/*%C Temperature convert (/10 to obtain tenth of a degree)										*/
	TurbineTemperature = TurbineTemperature / 10;
		   
	TurbineTempSample[TurbineTempSampleNb] = (SWORD16)TurbineTemperature; 

/*%C Temperature filtering on 10 values													*/
   for(i=0; i<10; i++)
	{
     	TempCompute = TempCompute + TurbineTempSample[i];
	}
	FilteredTurbineTemperature = TempCompute / 10;

/*%C Temperature array management															*/
   TurbineTempSampleNb++;
   TurbineTempSampleNb %= 10;
/*%C Temperature writing in compute base													*/
	DB_ComputeWrite(MEASURE_BLOWER_TEMPERATURE_S16,
						 FilteredTurbineTemperature);	
}
