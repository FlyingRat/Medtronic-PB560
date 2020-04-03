/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Write_Adjust_Pres_Mode_Peep.h  	 	                 		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	datas declaration for                	*/
/*%C        DB_IHM_Write_Adjust_Pres_Mode_Peep: 						           			*/
/*                                                            				  		*/
/******************************************************************************/
/*%I Input Parameter :			 None                                    		  	*/
/*%IO Input/Output Parameter : None  	        			                  	   */
/*%O Output Parameter : 		 None       	                 				  		*/
/******************************************************************************/
#ifndef WRITE_ADJUST_PRES_MODE_PEEP_H
#define WRITE_ADJUST_PRES_MODE_PEEP_H

/******************************************************************************/
/*                            EXTERNAL FUNCTION DECLARATIONS                  */
/******************************************************************************/

extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);
extern void DB_CurrentWrite(e_DB_ADJUST_CURRENT Id, UWORD16 Value);

#endif
