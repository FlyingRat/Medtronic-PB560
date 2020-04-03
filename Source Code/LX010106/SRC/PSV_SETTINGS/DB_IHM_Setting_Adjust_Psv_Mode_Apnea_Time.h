/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_IHM_Setting_Adjust_Psv_Mode_Apnea_Time.h 		          		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	data declaration for               		*/
/*%C        DB_IHM_Setting_Adjust_Psv_Mode_Apnea_Time.c	  							*/
/*                                                            				  		*/
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter :				None                                  		  	*/
/*%IO Input/Output Parameter : 	None  	        			                  	*/
/*%O 	Output Parameter : 			None       	                 				  		*/
/******************************************************************************/

#ifndef ADJUST_PSV_MODE_APNEA_TIME_H
#define ADJUST_PSV_MODE_APNEA_TIME_H

/******************************************************************************/
/*                      EXTERNAL FUNCTION DECLARATION	                      	*/
/******************************************************************************/


/* Access to the config write value */
extern void DB_ControlWrite(e_DB_CONTROL Id,
									 UWORD16 Value);

#endif

