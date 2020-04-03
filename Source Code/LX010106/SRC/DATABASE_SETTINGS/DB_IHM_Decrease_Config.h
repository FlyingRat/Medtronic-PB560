/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_IHM_Decrease_Config.h   		 			                  		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 														*/
/*%C Data declaration for DB_IHM_Decrease_Config.c										*/
/*                                                            				  		*/
/******************************************************************************/
/*%I Input Parameter :				NONE                                  		  	*/
/*%IO Input/Output Parameter : 	NONE  	        			                  	*/
/*%O Output Parameter : 			NONE		 	                 				  		*/
/******************************************************************************/

			 
/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/
#ifndef DB_IHM_DECREASE_CONFIG_H
#define DB_IHM_DECREASE_CONFIG_H

/******************************************************************************/
/*                 EXTERNAL FUNCTION DECLARATION	 	                       	*/
/******************************************************************************/

/* Access to the control read value */
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);

extern UWORD16 DB_IHM_Setting_Config_Adjust_High_Spo2(UWORD16 *Value,
															 			UWORD16 Id);
extern UWORD16 DB_IHM_Setting_Config_Adjust_Low_Spo2(UWORD16 *Value,
															 			UWORD16 Id);
extern UWORD16 DB_IHM_Setting_Config_Adjust_High_Fio2(UWORD16 *Value,
															 			UWORD16 Id);
extern UWORD16 DB_IHM_Setting_Config_Adjust_Low_Fio2(UWORD16 *Value,
															 			UWORD16 Id);
extern UWORD16 DB_IHM_Setting_Config_Adjust_Fio2(UWORD16 *Value,
														UWORD16 Id);

#if defined(LEGENDAIR_S2)
	extern UWORD16 DB_IHM_Setting_Config_Adjust_Mode_S2(UWORD16 *Value,
																 UWORD16 Increase);
#else 
	extern UWORD16 DB_IHM_Setting_Config_Adjust_Mode(UWORD16 *Value,
																 UWORD16 Increase);
#endif


#endif
