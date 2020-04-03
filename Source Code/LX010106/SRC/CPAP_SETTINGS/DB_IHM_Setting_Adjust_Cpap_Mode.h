/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Cpap_Mode.h  	 	                 		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	datas declaration for                	*/
/*%C        DB_IHM_Setting_Adjust_Cpap_Mode:  					           			*/
/*                                                            				  		*/
/******************************************************************************/
/*%I Input Parameter :			 None                                    		  	*/
/*%IO Input/Output Parameter : None  	        			                  	   */
/*%O Output Parameter : 		 None       	                 				  		*/
/******************************************************************************/
#ifndef ADJUST_CPAP_MODE_H
#define ADJUST_CPAP_MODE_H

/******************************************************************************/
/*                            EXTERNAL FUNCTION DECLARATIONS                  */
/******************************************************************************/
extern UWORD16 DB_IHM_Setting_Adjust_Cpap_Mode_Peep(UWORD16 *Value,
                                                   UWORD16 Id);
extern UWORD16 DB_IHM_Setting_Adjust_Cpap_Mode_Apnea_Time(UWORD16 *Value,
                                                         UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Cpap_Mode_Low_Vti(UWORD16 *Value,
                                                      UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Cpap_Mode_High_Vti(UWORD16 *Value,
                                                       UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Cpap_Mode_High_R(UWORD16 *Value,
                                                     UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Cpap_Mode_High_Leak(UWORD16 *Value,
															   			UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Cpap_Mode_Disco_Delay(UWORD16 *Value,
															 		 UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Psv_Mode_Disco_Delay(UWORD16 *Value,
															 		 UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Pres_Mode_Disco_Delay(UWORD16 *Value,
															 		 UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Vol_Mode_Disco_Delay(UWORD16 *Value,
															 		 UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Vsimv_Mode_Disco_Delay(UWORD16 *Value,
															 		 UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Psimv_Mode_Disco_Delay(UWORD16 *Value,
															 		 UWORD16 Id);
#endif
