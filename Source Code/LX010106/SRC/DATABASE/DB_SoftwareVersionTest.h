/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_SoftwareVersionTest.h	   				                  		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	datas declaration for                	*/
/*%C 			DB_SoftwareVersionTest.c                                         	*/
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameters :  			None          			                  		*/
/*%IO Input/Output Parameters :  None          			                  		*/
/*%O 	Output Parameters :  		None         			                  		*/
/******************************************************************************/
#ifndef DB_SOFTWARE_VERSION_TEST_H
#define DB_SOFTWARE_VERSION_TEST_H

/************************************************************************/
/*                    CONSTANT DECLARATION                           	*/
/************************************************************************/

/************************************************************************/
/*                 EXTERNAL FUNCTION DECLARATION                     	*/
/************************************************************************/
extern void DRV_FLASH_Erase_Flash(void);

extern void EEP_FIFO_PushOneData(	UWORD16 xhuge *ptr_DataRam,
												e_EEP_ACCESS_STATE access_type);

extern void DRV_RTC_control (UBYTE data_control);

extern void DRV_EVENT_Erase_Flash(void);

#endif