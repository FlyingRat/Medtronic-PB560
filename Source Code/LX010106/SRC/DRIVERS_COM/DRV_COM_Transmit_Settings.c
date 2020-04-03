/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_COM_Transmit_Settings.c                                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C          																						*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/

#ifndef _TASKING
#include "LH_ST10F276.h"
#include <intrins.h>
#else
#include "regf276e.h"
#endif
#include "typedef.h"
#include "enum.h"
#include "DB_Control.h"
#include "DB_Config.h"
#include "DB_Current.h"
#include "DRV_COM_Data.h"
#include "CRC16_Table.h"
#include "DRV_COM_Transmit_Settings.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void DRV_COM_Transmit_Settings(void)
{
 	UWORD16 Compute_CRC = 0;
	UWORD16 Value = 0;
	UWORD16 AdjustCyclingMode; 
	e_MODE_TYPES CurrentMode = 0;
	UWORD16 InspSensNoSelect = 0;
	UWORD16 BackupRNoSelect = 0;
	UWORD16 TargetVtSelect = 0;
	UWORD16 AutoExhSensSelect = 0;
  	UWORD16 AdjustFiO2Select = 0; 
	
  	/*%C Feed the frame with the 3 start bytes							*/
	Array_Settings [COM_TX_START_FRAME_1]
  							= START_FRAME_COM_VALUE_1;
	Array_Settings [COM_TX_START_FRAME_2]
  							= START_FRAME_COM_VALUE_2;
	Array_Settings [COM_TX_START_FRAME_3]
 							= START_FRAME_COM_VALUE_3;
 	  	
  	/*%C The settings frame ID */
  	Array_Settings [COM_TX_ID_FRAME] = ID_SETTINGS_DATA;

	CurrentMode = DB_ControlRead(CURRENT_MODE_U16);
	InspSensNoSelect = DB_CurrentRead(INSP_SENS_NO_SELECT_U16);
	BackupRNoSelect = DB_CurrentRead(BACKUP_R_NO_SELECT_U16);
	AdjustCyclingMode = DB_ConfigRead(ADJUST_CYCLING_MODE_U16);		
	TargetVtSelect = DB_CurrentRead(TARGET_VT_SELECT_U16);
	AutoExhSensSelect = DB_CurrentRead(AUTO_EXH_SENS_SELECT_U16);
	AdjustFiO2Select = DB_ConfigRead(ADJUST_FIO2_SELECT);

	/*%C Mode */ 
	switch (CurrentMode)
	{
		case VOL :
		{
			if (InspSensNoSelect == FALSE)
			{
				Array_Settings[COM_TX_DATA_FRAME + COM_TX_SETTINGS_MODE]	= COM_VOL_A;
			}
			else if (InspSensNoSelect == TRUE)
			{
				Array_Settings[COM_TX_DATA_FRAME + COM_TX_SETTINGS_MODE]	= COM_VOL_C; 
			}
			break;
		}
		case PRES :
		{
			if (InspSensNoSelect == FALSE)
			{
				Array_Settings[COM_TX_DATA_FRAME + COM_TX_SETTINGS_MODE] = COM_PRES_A;
			}
			else if (InspSensNoSelect == TRUE)
			{
				Array_Settings[COM_TX_DATA_FRAME	+ COM_TX_SETTINGS_MODE] = COM_PRES_C; 
			}
			break;
		}
		case PSVT :
		{
			if (BackupRNoSelect == FALSE)
			{
				Array_Settings[COM_TX_DATA_FRAME + COM_TX_SETTINGS_MODE] = COM_PSVT;
			}
			else if (BackupRNoSelect == TRUE)
			{
				Array_Settings[COM_TX_DATA_FRAME + COM_TX_SETTINGS_MODE] = COM_PSV; 
			}
			break;
 					}
		case VSIMV :
		{
			Array_Settings[COM_TX_DATA_FRAME + COM_TX_SETTINGS_MODE]	= COM_VSIMV;
			break;
		}
		case PSIMV :
		{
			Array_Settings[COM_TX_DATA_FRAME + COM_TX_SETTINGS_MODE]	= COM_PSIMV;
			break;
		}
		case CPAP :
		{
			Array_Settings[COM_TX_DATA_FRAME + COM_TX_SETTINGS_MODE]	= COM_CPAP;
			break;
		}
		default :
		{
			break;
		}
	} 


	/*%C  FiO2 */	
	Value = DB_ConfigRead(ADJUST_FIO2);
	if ((Value == 0xAAAA) || (AdjustFiO2Select == FALSE))
	{
		Value = 0;
	}

	Array_Settings[COM_TX_DATA_FRAME + COM_TX_SETTINGS_FIO2] = (UBYTE)Value;
	/****************************************************************************/
	
	/*%C VT_MSB */
	
	Value = DB_CurrentRead(ADJUST_VOL_CONTROL_U16);
	#ifdef LEGENDAIR_S2
		Value = 0;
	#else
		if ((Value == 0xAAAA)||(CurrentMode == (PRES || CPAP || PSVT)))
			{
				Value = 0;
			}
	#endif
	Array_Settings[COM_TX_DATA_FRAME + COM_TX_SETTINGS_VT_MSB]=(UBYTE)(Value >> 8);
	/*%C VT_LSB */
	Array_Settings[COM_TX_DATA_FRAME + COM_TX_SETTINGS_VT_LSB]=(UBYTE)Value;
	/****************************************************************************/

	
	/*%C Pi */
	
	if(CurrentMode == PRES)
	{
		Value = DB_CurrentRead(ADJUST_P_CONTROL_U16);
	}
	else			   
	{
		Value = DB_CurrentRead(ADJUST_P_SUPPORT_U16);
	}
	if (Value == 0xAAAA) 
	{
		Value = 0;
	}
	Array_Settings[COM_TX_DATA_FRAME + COM_TX_SETTINGS_PI]=(UBYTE)(Value / 10);
	/****************************************************************************/
	
	/*%C Pe */
	Value = DB_CurrentRead(ADJUST_PEEP_U16);
	if (Value == 0xAAAA)
	{
		Value = 0;
	}
	Array_Settings[COM_TX_DATA_FRAME + COM_TX_SETTINGS_PE]=(UBYTE)(Value / 10);
	/****************************************************************************/
	
	/*%C Pislope  */
	
	Value = DB_CurrentRead(ADJUST_RISE_TIME_U16);
	if ((Value == 0xAAAA) || (CurrentMode == VSIMV))
	{
		Value = 0;
	}
	Array_Settings [COM_TX_DATA_FRAME + COM_TX_SETTINGS_PISLOPE]=(UBYTE)Value;
	/****************************************************************************/
	
	/*%C Ramp */
	Value = DB_CurrentRead(ADJUST_RAMP_U16);
	if ((Value == 0xAAAA)|| (CurrentMode == VSIMV)) 
	{
		Value = 0;
	}
	else
	{
		Value = Value + 1;
	}
	Array_Settings[COM_TX_DATA_FRAME + COM_TX_SETTINGS_RAMP]=(UBYTE)Value;
	/****************************************************************************/
	
	/*%C IT */
	Array_Settings[COM_TX_DATA_FRAME + COM_TX_SETTINGS_IT]=0;
	/****************************************************************************/
	
	/*%C IE Numerator */
	Array_Settings[COM_TX_DATA_FRAME + COM_TX_SETTINGS_IE_NUM]=0;
	/****************************************************************************/
	
	/*%C IE Denominator*/
	Array_Settings[COM_TX_DATA_FRAME + COM_TX_SETTINGS_IE_DEN]=0;
	/****************************************************************************/
	
	/*%C Freq */
	if((CurrentMode == PRES) || (CurrentMode == VOL) || (CurrentMode == VSIMV))
	{
		Value = DB_CurrentRead(ADJUST_CONTROL_R_U16);
	}
	else
	{
		Value = DB_CurrentRead(ADJUST_BACKUP_R_U16);
	}
	if ((Value == 0xAAAA) || (BackupRNoSelect == TRUE))
	{
		Value = 0;
	}
	Array_Settings[COM_TX_DATA_FRAME	+ COM_TX_SETTINGS_FREQ]=(UBYTE)Value;
	/****************************************************************************/
	
	/*%C FVACI */
	Value = DB_CurrentRead(ADJUST_BACKUP_R_U16);
	if ((Value == 0xAAAA) || (BackupRNoSelect == TRUE)|| (CurrentMode == PSVT))
	{
		Value = 0;
	}
	Array_Settings[COM_TX_DATA_FRAME + COM_TX_SETTINGS_FVACI]=(UBYTE)Value;
	/****************************************************************************/
	
	/*%C Apnea */
	Value = DB_CurrentRead(ADJUST_APNEA_U16);
	if (Value == 0xAAAA) //|| ( CurrentMode == (PRES || VOL)))
	{
		Value = 0;
	}
	Array_Settings[COM_TX_DATA_FRAME + COM_TX_SETTINGS_APNEA]=(UBYTE)(Value / 1000);
	/****************************************************************************/
	
	/*%C ITrigger */
	Value = DB_CurrentRead(ADJUST_INSP_SENS_U16);
	if ((Value == 0xAAAA) || (InspSensNoSelect == TRUE))
	{
		Value = 0;
	}
	Array_Settings[COM_TX_DATA_FRAME + COM_TX_SETTINGS_ITRIGGER]=(UBYTE)Value;
	/****************************************************************************/
	
	/*%C ETrigger */
	Value = DB_CurrentRead(ADJUST_EXH_SENS_U16);
	if ((Value == 0xAAAA) || (AutoExhSensSelect == TRUE))
	{
		Value = 0;
	}
	Array_Settings[COM_TX_DATA_FRAME + COM_TX_SETTINGS_ETRIGGER]=(UBYTE)Value;
	/****************************************************************************/
	
	/*%C VTTarget_MSB */
	Value = DB_CurrentRead(ADJUST_TARGET_VT_U16);
	if ((Value == 0xAAAA) || (TargetVtSelect == FALSE)) 
	{
		Value = 0;
	}
	Array_Settings[COM_TX_DATA_FRAME + COM_TX_SETTINGS_VTTARGET_MSB]=(UBYTE)(Value >> 8);
	
	/*%C VTTarget_LSB */
	Array_Settings[COM_TX_DATA_FRAME + COM_TX_SETTINGS_VTTARGET_LSB]=(UBYTE)Value;
	/****************************************************************************/
	
	/*%C PiMaxi */
	Value = DB_CurrentRead(ADJUST_MAX_PRESSURE_U16);
	if ((Value == 0xAAAA)  || (TargetVtSelect == FALSE))
	{
		Value = 0;
	}
	Array_Settings[COM_TX_DATA_FRAME + COM_TX_SETTINGS_PIMAXI]=(UBYTE)(Value / 10);
	/****************************************************************************/

  	/*%C CRC16 Compute */
  	Compute_CRC = CRC16_TableCompute(	
					(UWORD16)(COM_TX_SETTINGS_MODE + COM_TX_DATA_FRAME), 
  	 				(UWORD16)(End_Of_Table_TX_Settings + COM_TX_DATA_FRAME),   
 					Array_Settings,
 					0 );


	/*%CFeed the frame with 2 CRC bytes */
	Array_Settings[COM_TX_MSB_CRC_FRAME + End_Of_Table_TX_Settings - 1] 
				   	 											= (UBYTE)(Compute_CRC >> 8);
	Array_Settings[COM_TX_LSB_CRC_FRAME + End_Of_Table_TX_Settings - 1] 
					 												= (UBYTE)(Compute_CRC &0x00FF );

	/*%C Feed the frame with the 3 stop frame bytes			    	*/
	Array_Settings[COM_TX_END_FRAME_1 + End_Of_Table_TX_Settings - 1]
																	= END_FRAME_COM_VALUE_1; 
	Array_Settings[COM_TX_END_FRAME_2 + End_Of_Table_TX_Settings - 1]
																	= END_FRAME_COM_VALUE_2; 
	Array_Settings[COM_TX_END_FRAME_3 + End_Of_Table_TX_Settings - 1]	
																	= END_FRAME_COM_VALUE_3;
	
  	S0TBIR = 0;
	/* Origin index increasing - sending a byte*/
	PECC2 = 0x0500; 
 	/* Size of array to transmit*/
 	PECC2 |= End_Of_Table_TX_Settings + End_Of_Table_Com_TX_Remote - 1 ; 
	/*%C Origin index on array*/
 	SRCP2 = _sof_(&Array_Settings); 	
 	/*%C Index transformation in adress  0 segment*/
	/*%C Destination index on  RS232 transmit register*/
 	   DSTP2 = (UWORD16) &S0TBUF; 
	/*%C Sending datas allowed*/
	S0TBIE = 1;
	S0TBIR = 1;
	/*%C End of transmition*/
 	Communication_State = COM_TRANSMIT_STOP;

}
