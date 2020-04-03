/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505 				                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_SPO2Interpol.c                               					*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C             		 Calibration des capteurs	                        		*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
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
#include "SYS_SPO2Interpol.h"

void SYS_SPO2Interpol(void)
{
	t_DataSpo2 Data;
	Data = SYS_ReadDataSpo2();

// Détection d'une erreur sur le capteur
// Possibilité de lire data.status mais à chaque fois que la mesure est impossible data.spo2 = 127
// Data.Spo2 = 0 -> Capteur non branché - rien sur la liaison série
//if((Data.Spo2 == 0) || (Data.Spo2 == 127))
//	DB_ControlWrite(ERROR_SPO2_SENSOR_DETECTED, TRUE);
//else
//  DB_ControlWrite(ERROR_SPO2_SENSOR_DETECTED, FALSE);
// Ecriture en base de donnée
//DB_ComputeWrite(MEASURE_SPO2_U16, Data.Spo2);
}
