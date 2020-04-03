/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_IHM_Write_Access.h   					           		       		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	data declaration for							*/
/*%C         DB_IHM_Write_Access.c															*/
/*                                                            				  		*/
/******************************************************************************/
/*%I Input Parameter : None			              			                  	*/
/*                                                                    		  	*/
/*%O Output Parameter : None 	   		                      				  		*/
/******************************************************************************/

#ifndef WRITE_ACCESS_H
#define WRITE_ACCESS_H

/******************************************************************************/
/*                 EXTERNAL CONSTANT DECLARATION	                          	*/
/******************************************************************************/
extern UWORD16 DB_IHM_Write_Adjust_Vol_Mode(UWORD16 *Value,
														  UWORD16 Id);

extern UWORD16 DB_IHM_Write_Adjust_Pres_Mode(UWORD16 *Value,
														   UWORD16 Id);

extern UWORD16 DB_IHM_Write_Adjust_Psv_Mode(UWORD16 *Value,
														  UWORD16 Id);

extern UWORD16 DB_IHM_Write_Adjust_Cpap_Mode(UWORD16 *Value,
														  UWORD16 Id);

extern UWORD16 DB_IHM_Write_Adjust_Vsimv_Mode(UWORD16 *Value,
														    UWORD16 Id);

extern UWORD16 DB_IHM_Write_Adjust_Psimv_Mode(UWORD16 *Value,
															 UWORD16 Id);
                                              
extern void DB_ControlWrite(e_DB_CONTROL Id, UWORD16 Value);

extern UWORD16 DB_IHM_Write_Config_Adjust_Fio2(UWORD16 *Value);

extern UWORD16 DB_ConfigWrite(e_DB_CONFIG Id, UWORD16 Value);

extern void DB_AlarmStatusWrite(e_DB_ALARMS Id, e_DB_ALARMS_STATE Value);

#endif

