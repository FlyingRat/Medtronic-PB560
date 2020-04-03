/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SYS_Interpolation.c                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C        Management of the interpolations after acuirements are done.      */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/



/******************************************************************************/
/*                               INCLUDE FILES                                */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "io_declare.h"
#include "DB_Control.h"
#include "SYS_Interpolation.h"
#include "Driver_Datas.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void SYS_Interpolation (void)
{

/*%C NOTA: "acquisition_disponible" is initialized with "TRUE" */
/*%C in "convertisseur_ad.c" */
/*%C if "acquisition_disponible" is true, then */
	if( DRV_Acquisition_Disponible == TRUE)
	{
/*%C  "Exhalation flow interpolation" function is launch, */
      INT_ExhFlow_Interpol();

/*%C  "Inspiration flow interpolation" function is launch,*/
      INT_InspFlow_Interpol();

/*%C  "Patient pressure interpolation" function is launch,*/
      INT_PatPress_Interpol();

/*%C  "Patient Proximal pressure interpolation" function is launch,*/
      INT_ProxiPress_Interpol();

/*%C  "Valve pressure interpolation" function is launch,*/
      INT_ValvePress_Interpol();

/*%C  "Voltages interpolation" function is launch.*/
      INT_Voltages_Interpol();

/*%C  Absolute pressure interpolation function is launch.*/
      INT_AbsPress_Interpol();

/*%C  Blower temperature interpolation function is launch.*/
      INT_BlowerTemperatureInterpol();

/*%C  Fio2 interpolation function launch.*/
		INT_Fio2_Interpol();

/*%C  O2 Flow interpolation function launch.*/
		INT_O2Flow_Interpol();

/*%C  O2 Pressure interpolation function launch.*/
		INT_O2Press_Interpol();
   }
/*%C In all cases, the functions of */
/*%C    channels acquirements "DRV_ADC_ChannelConvert",  */
	DRV_ADC_ChannelConvert();

/*%C    "speed blower interpolation", */
	INT_SpeedBlow_Interpol();

/*%C Flow Computing for waveform display */
	SYS_CurveFlowCalcul();

/*%C Supply Detect Function */
	SYS_SupplyDetect();

}