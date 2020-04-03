/******************************************************************************/
/*																			  */
/* Project Number	: 	RB0505     			     		                      */
/*																			  */
/*----------------------------------------------------------------------------*/
/*                                                                 			  */
/* Filename		: DB_IHM_Setting_Adjust_Vol_Mode_Sigh_Select.h  		      */
/*                                                           				  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	datas declaration for             */
/*%C        DB_IHM_Setting_Adjust_Vol_Mode_Sigh_Select						  */
/*                                                            				  */
/******************************************************************************/
/*%I 	Input Parameter :				 None                            	  */
/*%IO Input/Output Parameter :    None  	        			              */
/*%O 	Output Parameter : 			 None 	                 				  */
/******************************************************************************/
#ifndef ADJUST_VOL_MODE_SIGH_SELECT_H
#define ADJUST_VOL_MODE_SIGH_SELECT_H
/******************************************************************************/
/*                      EXTERNAL FUNCTION DECLARATION	                      */
/******************************************************************************/

/* Access to the config write value */
extern void DB_ControlWrite(e_DB_CONTROL Id, UWORD16 Value);

#endif