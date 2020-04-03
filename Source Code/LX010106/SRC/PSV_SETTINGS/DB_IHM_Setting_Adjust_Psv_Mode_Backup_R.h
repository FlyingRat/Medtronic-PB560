/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_IHM_Setting_Adjust_Psv_Mode_Backup_R.h 			          		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	data declaration for               		*/
/*%C        DB_IHM_Setting_Adjust_Psv_Mode_High_R.c									*/
/*                                                            				  		*/
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter :				None                                  		  	*/
/*%IO Input/Output Parameter : 	None  	        			                  	*/
/*%O 	Output Parameter : 			None       	                 				  		*/
/******************************************************************************/

#ifndef ADJUST_PSV_MODE_BACKUP_R_H
#define ADJUST_PSV_MODE_BACKUP_R_H

/******************************************************************************/
/*                      EXTERNAL FUNCTION DECLARATION	                      	*/
/******************************************************************************/

/* Access to the config write value */
extern void DB_ControlWrite(e_DB_CONTROL Id,
									 UWORD16 Value);

/* Access to the eeprom write function */
extern void DB_WriteDataInEepAndRam(UWORD16 xhuge *data_address,
												UWORD16 value);


#endif

