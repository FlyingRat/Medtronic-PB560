/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_RiseTimeCompute.h 		   				                  		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function computes the rise time   */
/*%C value, fonction of rise level setting and respecting the condition :		*/
/*%C Ti < Rise time + 300 ms                                             		*/
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter : 			None		        			                  	*/
/*%IO Input/Output Parameter : 	None 	        			                  		*/
/*%O 	Output Parameter : 			None	                       				  		*/
/******************************************************************************/

#ifndef DB_RISE_TIME_COMPUTE_H
#define DB_RISE_TIME_COMPUTE_H


/******************************************************************************/
/*                  EXTERNAL FUNCTION DECLARATION                    	      */
/******************************************************************************/
extern UWORD16 DB_CurrentRead(e_DB_ADJUST_CURRENT Id);

extern void DB_CurrentWrite(e_DB_ADJUST_CURRENT Id,
                               UWORD16 Value);

extern void DB_WriteDataInEepAndRam(UWORD16 xhuge *data_address,UWORD16 value);

#endif
