/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Vsimv_Mode_Ti_Control.h 		         		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	daclaration datas for              		*/
/*%C        DB_IHM_Setting_Adjust_Vsimv_Mode_Ti_Control.c	    					*/
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter :				None                                  		  	*/
/*%IO Input/Output Parameter : 	None  	        			                  	*/
/*%O 	Output Parameter : 			None       	                 				  		*/
/******************************************************************************/
#ifndef ADJUST_VSIMV_MODE_TI_CONTROL_H
#define ADJUST_VSIMV_MODE_TI_CONTROL_H

/******************************************************************************/
/*                      EXTERNAL FUNCTION DECLARATION	                      	*/
/******************************************************************************/

/* Access to the config write value */
extern void DB_ControlWrite(e_DB_CONTROL Id, UWORD16 Value);
extern void DB_ComputeBreathTimingRatios(void);
extern void DB_ComputeWrite(e_DB_COMPUTE Id, UWORD16 Value);

#endif
