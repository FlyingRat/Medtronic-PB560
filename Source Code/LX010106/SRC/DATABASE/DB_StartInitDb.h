/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_StartInitDb.h 			   				                  		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	datas declaration for DB_StartInitDb.c	*/
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameters :  			None          			                  		*/
/*%IO Input/Output Parameters :  None          			                  		*/
/*%O 	Output Parameters :  		None         			                  		*/
/******************************************************************************/
#ifndef DB_STARTINITDB_H
#define DB_STARTINITDB_H

/* Access to the config read value */
extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);
   
/*%C Version test function call                     									*/
extern void DB_SoftwareVersionTest(void);

/*%C Load and check Eeprom into Ram function call			    						*/
extern void DB_LoadAndCheckEepromIntoRam(void);

/*%C Tables initialization function call            									*/
extern void DB_InitializeTables(void);

/*%C Base copy management function call            									*/
extern void DB_CopyMngt(void);

/*%C Base event management function call            									*/
extern void DB_CopyMngt(void);

extern void EEP_FIFO_PushOneData(	UWORD16 xhuge *ptr_DataRam,
												e_EEP_ACCESS_STATE access_type);

extern void DB_EventMngt (UWORD16 Value);

extern void DB_WriteDataInEepAndRam(UWORD16 xhuge *data_address,
												UWORD16 value);

extern UWORD16 DB_TrendRead(e_DB_Trend Id);


#endif