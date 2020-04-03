/******************************************************************************/
/*																			  */
/* Project Number	: 	RA0104     			     		                      */
/*																			  */
/*----------------------------------------------------------------------------*/
/*                                                                 			  */
/* Filename	: DB_Revision.h    				                  					  */
/*                                                           				  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/

/******************************************************************************/
/*%C 			Functionnal description : 	datas for revision identification */
/*                                                            				  */
/******************************************************************************/
/*%I	Input Parameters :  		None									  */
/*%IO	Input/Output Parameters :	None									  */
/*%O	Output Parameters :  		None									  */
/******************************************************************************/

/*%C This file is automatically filled with revision informations before every*/
/*%C compilation.															  */

#ifndef DB_REVISION_H
#define DB_REVISION_H

#define CFG_REVISION_REVISION_VALUE  "31372"
#define CFG_REVISION_BUILD_DATE_YEAR       "2020"
#define CFG_REVISION_BUILD_DATE_MONTH      "03"
#define CFG_REVISION_BUILD_DATE_DAY        "30"
#define CFG_REVISION_BUILD_DATE_HOUR       "00"
#define CFG_REVISION_BUILD_DATE_MINUTE     "18"
#define CFG_REVISION_BUILD_DATE_SECOND     "14"
#define CFG_REVISION_MODIFIED_VALUE  "1"
#define CFG_REVISION_MIXED_VALUE     "0"
#define CFG_REVISION_WORKING_COPY_URL     "http:\\"

/* Revision base */
typedef enum {
	REVISION_U16=0,
	BUILD_DATE_YEAR_U16,
	BUILD_DATE_MONTH_U16,
	BUILD_DATE_DAY_U16,
	BUILD_DATE_HOUR_U16,
	BUILD_DATE_MINUTE_U16,
	BUILD_DATE_SECOND_U16,
	MODIFIED_U16,
	MIXED_U16,
	end_of_db_revision_table
} e_DB_Revision;

#ifdef DECLARATION_REVISION_BASE

UBYTE* DB_Revision[end_of_db_revision_table] = {CFG_REVISION_REVISION_VALUE,
													CFG_REVISION_BUILD_DATE_YEAR,
													CFG_REVISION_BUILD_DATE_MONTH,
													CFG_REVISION_BUILD_DATE_DAY,
													CFG_REVISION_BUILD_DATE_HOUR,
													CFG_REVISION_BUILD_DATE_MINUTE,
													CFG_REVISION_BUILD_DATE_SECOND,
													CFG_REVISION_MODIFIED_VALUE,
													CFG_REVISION_MIXED_VALUE};

#else

extern UBYTE* DB_Revision[end_of_db_revision_table];

#endif													
													
#endif
