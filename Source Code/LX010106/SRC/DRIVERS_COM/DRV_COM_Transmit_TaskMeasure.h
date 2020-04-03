/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_COM_Transmit_TaskMeasure.h  									  		*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                  																			*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                            		*/
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE       															*/
/******************************************************************************/


#ifndef DRV_COM_TRANSMIT_TASKMEASURE_H
#define DRV_COM_TRANSMIT_TASKMEASURE_H

/******************************************************************************/
/*                     EXTERNAL FUNCTION DECLARATION                          */
/******************************************************************************/


/*%C Transmit Task Measure */
	/* Keil  */
#ifndef _TASKING
UBYTE sdata Array_TaskMeasure	[	(MAXIMUM_VENTILATION_NUMBER_OF_TASKS * 3 * 2 )
 										+ 	End_Of_Table_Com_TX_Remote 
 										- 	1];
	/* Tasking  */
#else
UBYTE near Array_TaskMeasure	[	(MAXIMUM_VENTILATION_NUMBER_OF_TASKS * 3 * 2 )
 										+ 	End_Of_Table_Com_TX_Remote 
 										- 	1];
#endif


#endif
