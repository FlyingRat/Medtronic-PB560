/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Psv_Mode.h  	 	                 		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	datas declaration for                	*/
/*%C        DB_IHM_Setting_Adjust_Psv_Mode: 						           			*/
/*                                                            				  		*/
/******************************************************************************/
/*%I Input Parameter :			 None                                    		  	*/
/*%IO Input/Output Parameter : None  	        			                  	   */
/*%O Output Parameter : 		 None       	                 				  		*/
/******************************************************************************/
#ifndef ADJUST_PSV_MODE_H
#define ADJUST_PSV_MODE_H

/******************************************************************************/
/*                            EXTERNAL FUNCTION DECLARATIONS                  */
/******************************************************************************/
extern UWORD16 DB_IHM_Setting_Adjust_Psv_Mode_P_Support(UWORD16 *Value,
                                                        UWORD16 Id,
														UWORD16 Pi_Max,
												 		UWORD16 Pi_Min,
														UWORD16 Delta_Peep_Pi);

extern UWORD16 DB_IHM_Setting_Adjust_Psv_Mode_Peep(UWORD16 *Value,
                                                   UWORD16 Id,
												   UWORD16 Pi_Max,
											 	   UWORD16 Peep_Min);

extern UWORD16 DB_IHM_Setting_Adjust_Psv_Mode_Rise_Time(UWORD16 *Value,
                                                        UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Psv_Mode_Backup_R(UWORD16 *Value,
                                                       UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Psv_Mode_Apnea_Time(UWORD16 *Value,
                                                         UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Psv_Mode_Insp_Sens(UWORD16 *Value,
                                                        UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Psv_Mode_Exh_Sens(UWORD16 *Value,
                                                       UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Psv_Mode_Ti_Min(UWORD16 *Value,
                                                     UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Psv_Mode_Ti_Max(UWORD16 *Value,
                                                     UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Psv_Mode_Low_Vti(UWORD16 *Value,
                                                      UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Psv_Mode_High_Vti(UWORD16 *Value,
                                                       UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Psv_Mode_Low_Vte(UWORD16 *Value,
                                                      UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Psv_Mode_High_Vte(UWORD16 *Value,
                                                       UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Psv_Mode_Low_Vm(UWORD16 *Value,
                                                     UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Psv_Mode_High_Vm(UWORD16 *Value,
                                                      UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Psv_Mode_High_R(UWORD16 *Value,
                                                     UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Psv_Mode_Target_Vt(UWORD16 *Value,
																		UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Psv_Mode_Max_Pressure(UWORD16 *Value,
																		UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Psv_Mode_Exh_Sens_Neg(UWORD16 *Value,
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

extern UWORD16 DB_IHM_Write_Adjust_Psv_Mode_P_Support_No_Select(UWORD16 *Value);

extern UWORD16 DB_IHM_Setting_Adjust_Psv_Mode_High_Leak(UWORD16 *Value,
															   			UWORD16 Id);

extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);

extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);
#endif
