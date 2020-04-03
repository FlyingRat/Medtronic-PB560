/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CAN_Channel_Acquisition.h         					         		*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C        			  										      		  					*/
/*%C          																  						*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

typedef enum
{
	Can_Acquisition_TempBat = 0,
	Can_Acquisition_IConso,
	Can_Acquisition_3V3,
	Can_Acquisition_NoMeasure,
	Can_Acquisition_VACDC,
	Can_Acquisition_IBat,
	Can_Acquisition_VCharge,
	Can_Acquisition_TempAmb,
	Can_Acquisition_VDC,
	Can_Acquisition_24VUtil,
	Can_Acquisition_5V,
	Can_Acquisition_VBat,
	EndCanAcquisition
} e_CanAcquisitionTab;

#ifdef DECLARATION_CAN_CHANNEL_ACQUISITION

	#ifndef CAN_ACQUISITION_H
	#define CAN_ACQUISITION_H

		UWORD16 CAN_Acquisition[EndCanAcquisition];
		UWORD16 CAN_Previous_Acquisition[EndCanAcquisition];

	#endif
#else

	#ifndef CAN_ACQUISITION_H
	#define CAN_ACQUISITION_H

		extern UWORD16 CAN_Acquisition[EndCanAcquisition];
		extern UWORD16 CAN_Previous_Acquisition[EndCanAcquisition];

	#endif

#endif
