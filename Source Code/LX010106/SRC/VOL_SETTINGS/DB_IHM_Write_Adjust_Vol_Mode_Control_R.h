/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Write_Adjust_Vol_Mode_Control_R.h  		        		   */
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	declaration datas for            		*/
/*%C        DB_IHM_Write_Adjust_Vol_Mode_Control_R.c                  	  		*/
/*                                                            				  		*/
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter :				None                                 		  	*/
/*%IO Input/Output Parameter : 	None  	        			                  	*/
/*%O 	Output Parameter : 			None       	                 				  		*/
/******************************************************************************/


#ifndef WRITE_ADJUST_VOL_MODE_CONTROL_R_H
#define WRITE_ADJUST_VOL_MODE_CONTROL_R_H

/******************************************************************************/
/*                 EXTERNAL FUNCTION DECLARATION	                          	*/
/******************************************************************************/

extern void DB_ComputeWrite(e_DB_COMPUTE Id, UWORD16 Value);

extern SWORD32 saturation(SWORD32 Value,
                          SWORD32 Min,
                          SWORD32 Max); 

#endif
