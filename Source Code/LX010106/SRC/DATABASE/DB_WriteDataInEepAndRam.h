/******************************************************************************/
/*																										*/
/* N° du Projet	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Nom du Fichier	: DB_WriteDataInEepAndRam.h						          		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function writes datas in eeprom 	*/
/*%C        and Ram																				*/
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter : 			*data_address, value   */
/*%IO Input/Output Parameter : 	None 	        			                  		*/
/*%O 	Output Parameter : 			value			                 				  		*/
/******************************************************************************/
#ifndef DB_WRITEDATAINEEPANDRAM_H
#define DB_WRITEDATAINEEPANDRAM_H

extern void EEP_FIFO_PushOneData(	UWORD16 xhuge *ptr_DataRam,
												e_EEP_ACCESS_STATE access_type);

#endif
