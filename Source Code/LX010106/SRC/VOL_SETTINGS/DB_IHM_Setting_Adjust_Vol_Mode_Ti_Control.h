/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Vol_Mode_Ti_Control.h   	       		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	declaration datas for 		            */
/*%C        DB_IHM_Setting_Adjust_Vol_Mode_Ti_Control.c	 						   */
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter :				None                                  		  	*/
/*%IO Input/Output Parameter : 	None  	        			                  	*/
/*%O 	Output Parameter : 			None       	                 				  		*/
/******************************************************************************/


#ifndef ADJUST_VOL_MODE_TI_CONTROL_H
#define ADJUST_VOL_MODE_TI_CONTROL_H

/******************************************************************************/
/*                      EXTERNAL FUNCTION DECLARATION	                      	*/
/******************************************************************************/

/* Access to the config write value */
extern void DB_ControlWrite(e_DB_CONTROL Id, UWORD16 Value);
extern void DB_ComputeWrite(e_DB_COMPUTE Id, UWORD16 Value);
extern void DB_ComputeBreathTimingRatios(void);

#endif
