/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Psimv_Mode.h  	 	                 		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	datas declaration for                	*/
/*%C        DB_IHM_Setting_Adjust_Psimv_Mode:  					           			*/
/*                                                            				  		*/
/******************************************************************************/
/*%I Input Parameter :			 None                                    		  	*/
/*%IO Input/Output Parameter : None  	        			                  	   */
/*%O Output Parameter : 		 None       	                 				  		*/
/******************************************************************************/

#ifndef ADJUST_PSIMV_MODE_H
#define ADJUST_PSIMV_MODE_H

/******************************************************************************/
/*                            EXTERNAL FUNCTION DECLARATIONS                  */
/******************************************************************************/
extern UWORD16 DB_IHM_Setting_Adjust_Psimv_Mode_PControl(UWORD16 *Value,
                                                          UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Psimv_ModeTiControl(UWORD16 *Value,
                                                           UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Psimv_Mode_ControlR(UWORD16 *Value,
                                                          UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Psimv_Mode_PSupport(UWORD16 *Value,
                                                          UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Psimv_Mode_Peep(UWORD16 *Value,
                                                     UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Psimv_Mode_Apnea_Time(UWORD16 *Value,
                                                           UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Psimv_Mode_Insp_Sens(UWORD16 *Value,
                                                          UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Psimv_Mode_Exh_Sens(UWORD16 *Value,
                                                          UWORD16 Id);	  

extern UWORD16 DB_IHM_Setting_Adjust_Psimv_Mode_Low_Vti(UWORD16 *Value,
                                                        UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Psimv_Mode_High_Vti(UWORD16 *Value,
                                                         UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Psimv_Mode_Low_Vte(UWORD16 *Value,
                                                        UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Psimv_Mode_High_Vte(UWORD16 *Value,
                                                       UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Psimv_Mode_Low_Vm(UWORD16 *Value,
                                                       UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Psimv_Mode_High_Vm(UWORD16 *Value,
                                                        UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Psimv_Mode_High_R(UWORD16 *Value,
                                                       UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Psimv_Mode_Rise_Time(UWORD16 *Value,
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

extern UWORD16 DB_IHM_Setting_Adjust_Psimv_Mode_Exh_Sens_Neg(UWORD16 *Value,
																	UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Psimv_Mode_Exh_Sens(UWORD16 *Value,
																	UWORD16 Id);

 #endif

