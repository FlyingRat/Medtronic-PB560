/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Config_Adjust_High_Spo2.h    		   			*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	datas declaration for             		*/
/*%C        DB_IHM_Setting_Config_Adjust_High_Spo2		  								*/
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter :				 None                            		  	   */
/*%IO Input/Output Parameter :    None  	        			                  	*/
/*%O 	Output Parameter : 			 None 	                 				  		   */
/******************************************************************************/

#ifndef ADJUST_HIGH_SPO2_H
#define ADJUST_HIGH_SPO2_H


/******************************************************************************/
/*                      EXTERNAL FUNCTION DECLARATION	                      	*/
/******************************************************************************/

/* Access to the config write value */
extern void DB_ControlWrite(e_DB_CONTROL Id,
                            UWORD16 Value);

extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);

extern UWORD16 DB_ComputeRead(e_DB_COMPUTE Id);

#endif