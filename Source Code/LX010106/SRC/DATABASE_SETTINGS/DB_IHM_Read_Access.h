/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_IHM_Read_Access.h   		 			                  			*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	data declaration for				    		*/
/*%C        DB_IHM_Read_Access																*/
/*                                                            				  		*/
/******************************************************************************/
/*%I Input Parameter :				None                                  		  	*/
/*%IO Input/Output Parameter : 	None  	        			                  	*/
/*%O Output Parameter : 			None 	                 				  				*/
/******************************************************************************/
#ifndef DB_IHM_READ_ACCESS_H
#define DB_IHM_READ_ACCESS_H

/******************************************************************************/
/*                 EXTERNAL FUNCTION DECLARATION	                         	*/
/******************************************************************************/

UWORD16 DB_UsbRead(e_DB_USB Id);

extern UWORD16 DB_AlarmStatusRead(e_DB_ALARMS Id); 

extern UWORD16 DB_PowerSupplyRead(e_DB_POWERSUPPLY Id); 

extern UWORD16 DB_RTCRead(e_DB_RTC Id); 

extern UWORD16 DB_ControlRead(e_DB_CONTROL Id); 

extern UWORD16 DB_ComputeRead(e_DB_COMPUTE Id); 

extern UWORD16 DB_RevisionRead(e_DB_Revision Id);

#endif
