/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Psv_Mode_Max_Pressure.h  	        		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	datas declaration for                	*/
/*%C        DB_IHM_Setting_Adjust_Psv_Mode_Max_Pressure.c	           			*/
/*                                                            				  		*/
/******************************************************************************/
/*%I  Input Parameter :			   None                               		  	   */
/*%IO Input/Output Parameter : 	None  	   			                  	   */
/*%O  Output Parameter : 		   None       	                 				      */
/******************************************************************************/


#ifndef ADJUST_PSV_MODE_MAX_PRESSURE_H
#define ADJUST_PSV_MODE_MAX_PRESSURE_H

/******************************************************************************/
/*                            EXTERNAL FUNCTION DECLARATIONS                  */
/******************************************************************************/

/* Access to the config write value */
extern void DB_ControlWrite(e_DB_CONTROL Id, UWORD16 Value);
extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);

#endif
