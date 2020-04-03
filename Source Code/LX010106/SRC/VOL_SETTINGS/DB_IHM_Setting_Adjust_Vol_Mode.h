/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Setting_Adjust_Vol_Mode.h   	 	                 		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	Declarations for 								*/
/*%C                               		DB_IHM_Setting_Adjust_Vol_Mode	  		*/
/*                                                            				  		*/
/*                                                            				  		*/
/******************************************************************************/
/*%I  Input Parameters:          None            			                  	*/
/*%IO Input/output Parameters:   None	           			                  	*/
/*%O  Output Parameters:         None                        				  		*/
/******************************************************************************/
#ifndef ADJUST_VOL_MODE_H
#define ADJUST_VOL_MODE_H


/******************************************************************************/
/*                            EXTERNAL FUNCTION DECLARATIONS                  */
/******************************************************************************/
extern UWORD16 DB_IHM_Setting_Adjust_Vol_Mode_Control_R(UWORD16 *Value,
                                                        UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Vol_Mode_Vol_Control(UWORD16 *Value,
                                                        UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Vol_Mode_Ti_Control(UWORD16 *Value,
                                                         UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Vol_Mode_Ramp(UWORD16 *Value);

extern UWORD16 DB_IHM_Setting_Adjust_Vol_Mode_Peep(UWORD16 *Value,
                                                   UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Vol_Mode_Insp_Sens(UWORD16 *Value,
                                                        UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Vol_Mode_Low_Pip(UWORD16 *Value,
                                                      UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Vol_Mode_High_Pip(UWORD16 *Value,
                                                       UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Vol_Mode_Low_Vte(UWORD16 *Value,
                                                      UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Vol_Mode_High_Vte(UWORD16 *Value,
                                                       UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Vol_Mode_Low_Vm(UWORD16 *Value,
                                                     UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Vol_Mode_High_Vm(UWORD16 *Value,
                                                      UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Vol_Mode_High_R(UWORD16 *Value,
                                                     UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Vol_Mode_Sigh_Select(UWORD16 *Value,
                                                          UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Vol_Mode_Sigh_Vt_Coef(UWORD16 *Value,
															  					UWORD16 Id);

extern UWORD16 DB_IHM_Setting_Adjust_Vol_Mode_Sigh_Cpt(UWORD16 *Value,
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


