/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : MAIN_Security_Init.h                                		  		*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C          	Data declaration for ventilation init function                	*/
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


#ifndef MAIN_SECURITY_INIT_H
#define MAIN_SECURITY_INIT_H


/******************************************************************************/
/*             EXTERNAL FUNCTION DECLARATION                    	            */
/******************************************************************************/

extern void DB_AlarmStatusWrite(e_DB_ALARMS Id, 
										  e_DB_ALARMS_STATE Value);

extern void DB_EventMngt (UWORD16 Value);

extern void DB_AlarmInfoWrite(e_DB_ALARMS Id, UBYTE Value);

extern UWORD16 DB_TrendWrite(e_DB_Trend Id, UWORD16 Value);

#endif
