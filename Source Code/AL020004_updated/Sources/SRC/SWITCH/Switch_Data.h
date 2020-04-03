/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : Switch_Data.h                                                	*/
/*													 						  							*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C       		Switch management Global Data declaration                     	*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifdef DECLARATION_SWITCH_DATA
	
	#ifndef SWITCH_DATA_H
	#define SWITCH_DATA_H
	
		UBYTE AC_Loss_Detected = TRUE;
		UBYTE DC_Loss_Detected = TRUE;	
		UBYTE BAT_Loss_Detected = TRUE;
	
	#endif

#else

	#ifndef SWITCH_DATA_H
	#define SWITCH_DATA_H

		extern UBYTE AC_Loss_Detected;
		extern UBYTE DC_Loss_Detected;
		extern UBYTE BAT_Loss_Detected;

	#endif
#endif
