/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Write_Adjust_Pres_Mode_Insp_Sens.h                		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	datas declaration associated to   		*/
/*%C        DB_IHM_Write_Adjust_Pres_Mode_Insp_Sens                    		   */
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter :				None                                  		  	*/
/*%IO Input/Output Parameter : 	None  	        			                  	*/
/*%O 	Output Parameter : 			None       	                 				  		*/
/******************************************************************************/

#ifndef WRITE_ADJUST_PRES_MODE_INSP_SENS_H
#define WRITE_ADJUST_PRES_MODE_INSP_SENS_H

/******************************************************************************/
/*                 EXTERNAL FUNCTION DECLARATION	                          	*/
/******************************************************************************/

extern void DB_WriteDataInEepAndRam(UWORD16 xhuge *data_address,
												UWORD16 value);

extern void DB_CurrentWrite(e_DB_ADJUST_CURRENT Id,
                               UWORD16 Value);

extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);

extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);


#endif
