/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_CopyMngt.h 				   				                  		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	datas declaration for DB_CopyMngt.c		*/
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter : 			None		        			                  	*/
/*%IO Input/Output Parameter : 	None 	        			                  		*/
/*%O 	Output Parameter : 			None	                       				  		*/
/******************************************************************************/
#ifndef DB_COPYMNGT_H
#define DB_COPYMNGT_H

/******************************************************************************/
/*                 EXTERNAL FUNCTION DECLARATION	                          	*/
/******************************************************************************/

/* Access to the config read value */
extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);

/* Access to the config read value */
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);

/* Access to the config read value */
extern UWORD16 DB_CurrentRead(e_DB_CONTROL Id);

/* Access to the config write value */
extern void DB_ControlWrite(e_DB_CONTROL Id, UWORD16 Value);

/* Access to the config write value */
extern void DB_CurrentWrite(e_DB_ADJUST_CURRENT Id, UWORD16 Value);

/* Access to the rise time compute function */
extern void DB_RiseTimeCompute(UWORD16 Current_Mode);

extern UWORD16 DB_ConfigWrite(e_DB_CONFIG Id,
										UWORD16 Value);

extern void SEC_ResetAlarms(void);

extern void DB_ComputeWrite(e_DB_COMPUTE Id, 
							UWORD16 Value);

#endif