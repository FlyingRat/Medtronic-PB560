/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_IHM_Setting_Adjust_Pres_Mode_High_R.h 			          		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	data declaration for               		*/
/*%C        DB_IHM_Setting_Adjust_Pres_Mode_High_R.c									*/
/*                                                            				  		*/
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter :				None                                  		  	*/
/*%IO Input/Output Parameter : 	None  	        			                  	*/
/*%O 	Output Parameter : 			None       	                 				  		*/
/******************************************************************************/

#ifndef ADJUST_PRES_MODE_HIGH_R_H
#define ADJUST_PRES_MODE_HIGH_R_H

/******************************************************************************/
/*                      EXTERNAL FUNCTION DECLARATION	                      	*/
/******************************************************************************/

/* Access to the config write value */
extern void DB_ControlWrite(e_DB_CONTROL Id, UWORD16 Value);

extern void DB_WriteDataInEepAndRam(UWORD16 xhuge *data_address,UWORD16 value);

#endif

