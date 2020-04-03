/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : FAN_Data.h                                                		*/
/*													 						  							*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                     																		*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


#ifndef FAN_DATA_DEFINE_H
#define FAN_DATA_DEFINE_H

	#define FAN_TR_MIN 						3000 // tr/min
	#define FAN_TR_MAX 						7500 // tr/min

	#define TEMP_AMB_MIN						2500 //100ième de °C
	#define TEMP_AMB_MAX						6000 //100ième de °C

	#define TEMP_BAT_MIN						2000 //100ième de °C
	#define TEMP_BAT_MAX						4000 //100ième de °C

	#define CMD_FAN_MAX						0x40
	#define SPEED_DIGIT_FAN_ARRAY_SIZE 	5

#endif



#ifdef DECLARATION_FAN_DATA

	#ifndef FAN_DATA_H
	#define FAN_DATA_H

		UWORD16 Speed_Fan = 0 ;
		UWORD16 Speed_Digit_Fan_Array[SPEED_DIGIT_FAN_ARRAY_SIZE];
		UWORD32 Speed_Fan_Tr_Min = 0 ;

	#endif

#else

	#ifndef FAN_DATA_H
	#define FAN_DATA_H

		extern UWORD16 Speed_Fan;
		extern UWORD16 Speed_Digit_Fan_Array[];
		extern UWORD32 Speed_Fan_Tr_Min;
	#endif

#endif
