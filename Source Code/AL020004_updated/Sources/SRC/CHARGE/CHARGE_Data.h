/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CHARGE_Data.h         					              					*/
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

#ifndef CHARGE_DATA_DEFINE_H
#define CHARGE_DATA_DEFINE_H

/* Periode Init_Chargeur_Max (= 3s)															*/
#define CHARGE_INIT_PERIOD_TIME_OUT			3000
/* Periode Stop charge																			*/	
#define CHARGE_CUT_OFF_PERIOD					10000

#endif



#ifdef DECLARATION_CHARGE_DATA

	#ifndef CHARGE_DATA_H
	#define CHARGE_DATA_H

	UBYTE Previous_PWM_Charge ;
	UWORD16 Init_Chargeur_Autorisation = FALSE;
	UWORD32 CumulChargeCurrent = 0 ;

	#endif

#else

	#ifndef CHARGE_DATA_H
	#define CHARGE_DATA_H

	extern UBYTE Previous_PWM_Charge;
	extern UWORD16 Init_Chargeur_Autorisation;
	extern UWORD32 CumulChargeCurrent ;

	#endif

#endif
