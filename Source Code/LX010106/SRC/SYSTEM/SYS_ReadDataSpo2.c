 /*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505 			               	                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_ReadDataSpo2.c															*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                  Lecture de la trame de reception SPO2                   */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
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
#include "System_Datas.h"

t_DataSpo2 SYS_ReadDataSpo2(void)
{
	t_DataSpo2 DataSpo2;

	DataSpo2.Status = DataFrameUART1[DATA_FRAME0];
  	DataSpo2.HeartRate = DataFrameUART1[DATA_FRAME1];
  	DataSpo2.Spo2 = DataFrameUART1[DATA_FRAME2];

	return  DataSpo2;
 
}


