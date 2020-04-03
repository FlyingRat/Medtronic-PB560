/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Write_Adjust_Psv_Mode.h 	   	                 		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	datas declaration associated to   		*/
/*%C        DB_IHM_Write_Adjust_Psv_Mode                              		   */
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter :				None                                  		  	*/
/*%IO Input/Output Parameter : 	None  	        			                  	*/
/*%O 	Output Parameter : 			None       	                 				  		*/
/******************************************************************************/

#ifndef WRITE_ADJUST_PSV_MODE_H
#define WRITE_ADJUST_PSV_MODE_H

/******************************************************************************/
/*                 EXTERNAL FUNCTION DECLARATION	                          	*/
/******************************************************************************/

extern UWORD16 DB_IHM_Write_Adjust_Psv_Mode_Apnea_Time(UWORD16 *Value); 

extern UWORD16 DB_IHM_Write_Adjust_Psv_Mode_Backup_R(UWORD16 *Value);

extern UWORD16 DB_IHM_Write_Adjust_Psv_Mode_High_Vm(UWORD16 *Value);

extern UWORD16 DB_IHM_Write_Adjust_Psv_Mode_Low_Vm(UWORD16 *Value);

extern UWORD16 DB_IHM_Write_Adjust_Psv_Mode_High_Vte(UWORD16 *Value);

extern UWORD16 DB_IHM_Write_Adjust_Psv_Mode_Low_Vte(UWORD16 *Value);

extern UWORD16 DB_IHM_Write_Adjust_Psv_Mode_High_Vti(UWORD16 *Value);

extern UWORD16 DB_IHM_Write_Adjust_Psv_Mode_Low_Vti(UWORD16 *Value);

extern UWORD16 DB_IHM_Write_Adjust_Psv_Mode_Exh_Sens(UWORD16 *Value);

extern UWORD16 DB_IHM_Write_Adjust_Psv_Mode_Exh_Sens_Neg(UWORD16 *Value);

extern UWORD16 DB_IHM_Write_Adjust_Psv_Mode_Max_Pressure(UWORD16 *Value);

extern UWORD16 DB_IHM_Write_Adjust_Psv_Mode_Target_Vt(UWORD16 *Value);

extern void DB_WriteDataInEepAndRam(UWORD16 xhuge *data_address,
												UWORD16 value);

extern void DB_CurrentWrite(e_DB_ADJUST_CURRENT Id,
                               UWORD16 Value);

extern UWORD16 DB_IHM_Write_Adjust_Cpap_Mode_Disco_Delay(UWORD16 *Value);

extern UWORD16 DB_IHM_Write_Adjust_Psv_Mode_Disco_Delay(UWORD16 *Value);

extern UWORD16 DB_IHM_Write_Adjust_Pres_Mode_Disco_Delay(UWORD16 *Value);

extern UWORD16 DB_IHM_Write_Adjust_Vol_Mode_Disco_Delay(UWORD16 *Value);

extern UWORD16 DB_IHM_Write_Adjust_Vsimv_Mode_Disco_Delay(UWORD16 *Value);

extern UWORD16 DB_IHM_Write_Adjust_Psimv_Mode_Disco_Delay(UWORD16 *Value);

extern UWORD16 DB_IHM_Write_Adjust_Psv_Mode_P_Support_No_Select(UWORD16 *Value);

extern UWORD16 DB_IHM_Write_Adjust_Psv_Mode_P_Support(UWORD16 *Value);

extern UWORD16 DB_IHM_Write_Adjust_Psv_Mode_Ti_Min(UWORD16 *Value);

extern UWORD16 DB_IHM_Write_Adjust_Psv_Mode_Ti_Max(UWORD16 *Value);

extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);

extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);

extern UWORD16 DB_IHM_Write_Adjust_Psv_Mode_Peep(UWORD16 *Value);

#endif
