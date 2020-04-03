/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename		: DB_IHM_Write_Adjust_Pres_Mode.h 	   	                 		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	datas declaration associated to   		*/
/*%C        DB_IHM_Write_Adjust_Pres_Mode                              		   */
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter :				None                                  		  	*/
/*%IO Input/Output Parameter : 	None  	        			                  	*/
/*%O 	Output Parameter : 			None       	                 				  		*/
/******************************************************************************/

#ifndef WRITE_ADJUST_PRES_MODE_H
#define WRITE_ADJUST_PRES_MODE_H

/******************************************************************************/
/*                 EXTERNAL FUNCTION DECLARATION	                          	*/
/******************************************************************************/

extern UWORD16 DB_IHM_Write_Adjust_Pres_Mode_Control_R(UWORD16 *Value); 

extern UWORD16 DB_IHM_Write_Adjust_Pres_Mode_Insp_Sens(UWORD16 *Value);

extern UWORD16 DB_IHM_Write_Adjust_Pres_Mode_Low_Vm(UWORD16 *Value);

extern UWORD16 DB_IHM_Write_Adjust_Pres_Mode_High_Vm(UWORD16 *Value);

extern UWORD16 DB_IHM_Write_Adjust_Pres_Mode_Low_Vte(UWORD16 *Value);

extern UWORD16 DB_IHM_Write_Adjust_Pres_Mode_High_Vte(UWORD16 *Value);

extern UWORD16 DB_IHM_Write_Adjust_Pres_Mode_Low_Vti(UWORD16 *Value);

extern UWORD16 DB_IHM_Write_Adjust_Pres_Mode_High_Vti(UWORD16 *Value);

extern void DB_WriteDataInEepAndRam(UWORD16 xhuge *data_address,UWORD16 value);

extern UWORD16 DB_IHM_Write_Adjust_Cpap_Mode_Disco_Delay(UWORD16 *Value);

extern UWORD16 DB_IHM_Write_Adjust_Psv_Mode_Disco_Delay(UWORD16 *Value);

extern UWORD16 DB_IHM_Write_Adjust_Pres_Mode_Disco_Delay(UWORD16 *Value);

extern UWORD16 DB_IHM_Write_Adjust_Vol_Mode_Disco_Delay(UWORD16 *Value);

extern UWORD16 DB_IHM_Write_Adjust_Vsimv_Mode_Disco_Delay(UWORD16 *Value);

extern UWORD16 DB_IHM_Write_Adjust_Psimv_Mode_Disco_Delay(UWORD16 *Value);

extern UWORD16 DB_IHM_Write_Adjust_Pres_Mode_P_Control(UWORD16 *Value);

extern UWORD16 DB_IHM_Write_Adjust_Pres_Mode_Target_Vt(UWORD16 *Value);

extern UWORD16 DB_IHM_Write_Adjust_Pres_Mode_Max_Pressure(UWORD16 *Value);

extern UWORD16 DB_IHM_Write_Adjust_Pres_Mode_I_T(UWORD16 *Value);

extern UWORD16 DB_IHM_Write_Adjust_Pres_Mode_I_E_Numerator(UWORD16 *Value);

extern UWORD16 DB_IHM_Write_Adjust_Pres_Mode_Peep(UWORD16 *Value);


#endif
