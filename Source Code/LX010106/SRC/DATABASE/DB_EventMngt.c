/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_EventMngt.c 				   				                  		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function manages 						*/
/*%C 												the different events							*/
/*                                                                    		  	*/
/*%I 	Input Parameter : 			EventNb 	        			                  	*/
/*%IO Input/Output Parameter : 	None 	        			                  		*/
/*%O 	Output Parameter : 			None	                      				  		*/
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "Structure.h"
#include "DB_Rtc.h"
#include "DB_Control.h"
#include "DB_Config.h"
#include "DB_Compute.h"
#include "DB_Current.h"
#include "DB_PowerSupply.h"
#define DECLARATION_EVENT_MNGT_H
#include "DB_EventMngt.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void DB_EventMngt (UWORD16 EventNb)
{
#ifndef _BORLAND

    /* Current mode recovery					                                       */
    UWORD16 ActualMode = DB_ControlRead(CURRENT_MODE_U16);

    UBYTE   i = 0;
    UWORD16 DataToPush = 0;

    /* Array pointer for specific events					                           */
    const t_DB_EventMngtParam *ParamTable = DB_PsvEventMngtParam;

    /********************************/  
    /*%C Parameters memorization    */
    /********************************/  

    /*%C Event number writing */
    DRV_EVENT_PushEvent(EVENT_NB_ID,
                        EventNb);

    /*%C Common parameters flash writing (for all modes) */
    for (i = 0; i < EndCommonEventParam - BeginCommonEventParam + 1; i++)
    {
        /*%C  Writing parameter function base origin */
        switch (DB_CommonEventMngtParam[i].DataBaseType)
        {
        /*%C     Value reading in RTC base */
        case DB_RTC :                                                      
            {                                                                  
                DataToPush = DB_RTCRead(DB_CommonEventMngtParam[i].DataId);     
                break;                                                          
            }                                                                  
            /*%C     Value reading in current base */
        case DB_CURRENT :                                                  
            {                                                                  
                DataToPush = DB_CurrentRead(DB_CommonEventMngtParam[i].DataId); 

                /*%C  The Disconnection delay unit is Second in online 2  */
                if (DB_CommonEventMngtParam[i].DataId == ADJUST_DISCONNECTION_DELAY_U16)
                {
                    DataToPush = DataToPush / 1000;
                }

                break;                                                          
            }                                                                  
            /*%C     Value reading in config base */
        case DB_CONFIG :                                                   
            {                                                                  
                DataToPush = DB_ConfigRead(DB_CommonEventMngtParam[i].DataId);  

                if (DB_CommonEventMngtParam[i].DataId == ADJUST_CYCLING_MODE_U16)
                {
                    DataToPush = (EventDataSchemaVersion << 4) | (DataToPush & 0x0f);
                }
                /*%C     if the Spo2 function is not active, the 0 value is stored in Flash */
                /*%C     for the ADJUST_LOW_SPO2 and ADJUST_HIGH_SPO2 */
                if (DB_CommonEventMngtParam[i].DataId == ADJUST_LOW_SPO2)
                {
                    if (DB_ConfigRead(SPO2_LOW_SELECT) == FALSE)
                        DataToPush = 0;
                }
                else if (DB_CommonEventMngtParam[i].DataId == ADJUST_HIGH_SPO2)
                {
                    if (DB_ConfigRead(SPO2_HIGH_SELECT) == FALSE)
                        DataToPush = 0;
                }
                /*%C  If FiO2 is not activated, its value =0  */
                if (DB_CommonEventMngtParam[i].DataId == ADJUST_FIO2)
                {
                    if (DB_ConfigRead(ADJUST_FIO2_SELECT) == FALSE)
                    {
                        DataToPush = 0;
                    }
                }

                /*%C  If FiO2min is not activated, its value =0  */
                if (DB_CommonEventMngtParam[i].DataId == ADJUST_LOW_FIO2)
                {
                    if (DB_ConfigRead(FIO2_LOW_SELECT) == FALSE)
                    {
                        DataToPush = 0;
                    }
                }

                /*%C  If FiO2max is not activated, its value =0  */
                if (DB_CommonEventMngtParam[i].DataId == ADJUST_HIGH_FIO2)
                {
                    if (DB_ConfigRead(FIO2_HIGH_SELECT) == FALSE)
                    {
                        DataToPush = 0;
                    }
                }


                break;                                                          
            }                                                                  
            /*%C     Value reading in control base */
        case DB_CONTROL :                                                  
            {                                                                  
                DataToPush = DB_ControlRead(DB_CommonEventMngtParam[i].DataId); 
                // Stockage du Mode spécifique à la com		
                if (DB_CommonEventMngtParam[i].DataId == CURRENT_MODE_U16)
                {
                    switch (DataToPush)
                    {
                    case VOL :
                        {
                            if (DB_CurrentRead(INSP_SENS_NO_SELECT_U16) == FALSE)
                            {
                                DataToPush = COM_VOL_A;
                            }
                            else if (DB_CurrentRead(INSP_SENS_NO_SELECT_U16) == TRUE)
                            {
                                DataToPush = COM_VOL_C; 
                            }
                            break;
                        }

                    case PRES :
                        {
                            if (DB_CurrentRead(INSP_SENS_NO_SELECT_U16) == FALSE)
                            {
                                DataToPush = COM_PRES_A;
                            }
                            else if (DB_CurrentRead(INSP_SENS_NO_SELECT_U16) == TRUE)
                            {
                                DataToPush = COM_PRES_C; 
                            }
                            break;
                        }

                    case PSVT :
                        {
                            if (DB_CurrentRead(BACKUP_R_NO_SELECT_U16) == FALSE)
                            {
                                DataToPush = COM_PSVT;
                            }
                            else if (DB_CurrentRead(BACKUP_R_NO_SELECT_U16) == TRUE)
                            {
                                DataToPush = COM_PSV; 
                            }
                            break;
                        }

                    case VSIMV :
                        {
                            DataToPush = COM_VSIMV;
                            break;
                        }

                    case PSIMV :
                        {
                            DataToPush = COM_PSIMV;
                            break;
                        }


                    case CPAP :
                        {
                            DataToPush = COM_CPAP;
                            break;
                        }

                    default :
                        {
                            DataToPush = COM_VOL_A;
                            break;
                        }
                    }
                }
                break;                                                          
            }                                                                  
            /*%C     Value reading in compute base */
        case DB_COMPUTE :                                                  
            {                                                                  
                DataToPush = DB_ComputeRead(DB_CommonEventMngtParam[i].DataId); 
                // Stockage de la MEASURE_SPO2 		
                if (DB_CommonEventMngtParam[i].DataId == MEASURE_SPO2_U16)
                {
                    if (DB_ControlRead(ERROR_SPO2_SENSOR_DETECTED) == TRUE)
                        DataToPush = 0;
                }
                // Le stockage de la MEASURE_FIO2 sera divisé par 10 et arrondi		
                else if (DB_CommonEventMngtParam[i].DataId == MEASURE_FIO2)
                {
                    if (DB_ControlRead(DETECTED_FIO2_SENSOR) == TRUE)
                    {
                        if ((DataToPush % 10) < 5)
                            DataToPush /= 10;
                        else
                        {
                            DataToPush /= 10;
                            DataToPush++;
                        }
                    }
                    else
                        DataToPush = 0;             
                }
                else if (DB_CommonEventMngtParam[i].DataId == COMPUTED_LEAK_U16)
                {
                    DataToPush = DataToPush / 10;               
                }
                break;                                                          
            }                                                                  
            /*%C     Value reading in powersupply base */
        case DB_POWERSUPPLY :
            {
                DataToPush = DB_PowerSupplyRead(DB_CommonEventMngtParam[i].DataId); 
                break;                                                          
            }
        default :                                                          
            {                                                                  
                DataToPush = 0;                                                 
                break;                                                          
            }                                                                  
        }


        /*%C  Value size test (8 or 16 bits) (flash writing on 8 bits)                */
        /*%C  MSB value test  */
        if (DB_CommonEventMngtParam[i].StorageType == MSB)
        {
            /*%C     Flash writing  */
            DRV_EVENT_PushEvent(i+1, DataToPush >> 8);
        }
        /*%C  LSB value test  */
        else if (DB_CommonEventMngtParam[i].StorageType == LSB)
        {
            /*%C     Flash writing  */
            DRV_EVENT_PushEvent(i+1, DataToPush & 0x00FF);
        }
        /*%C  The value is already sized on 8 bits  */
        else
        {
            /*%C     Flash writing  */
            DRV_EVENT_PushEvent(i+1, (UBYTE)DataToPush);
        }
    }

    /*******************************************************/   
    /*%C Specific Parameters memorization for each mode    */
    /*******************************************************/   

    /*%C Array address memorization function of the ventilation mode              */
    switch (ActualMode)
    {
    /*%C  PSVT parameters array address memorization                         */
    case PSVT :
        ParamTable = DB_PsvEventMngtParam;
        break;

        /*%C  PRES parameters array address memorization                              */
    case PRES :
        ParamTable = DB_PresEventMngtParam;
        break;

        /*%C  VOL parameters array address memorization                               */
    case VOL :
        ParamTable = DB_VolEventMngtParam;
        break;

        /*%C  VSIMV parameters array address memorization                             */
    case VSIMV :
        ParamTable = DB_VsimvEventMngtParam;
        break;

        /*%C  PSIMV parameters array address memorization                             */
    case PSIMV :
        ParamTable = DB_PsimvEventMngtParam;
        break;

        /*%C  CPAP parameters array address memorization                         */
    case CPAP :
        ParamTable = DB_CpapEventMngtParam;
        break;


    default :
        break;
    }

    /*%C Specific events flash writing:                                           */
    /*%C - value recovery in current base                                         */
    /*%C - activated settings checking                                            */
    /*%C - flash writing                                                          */
    for (i = 0; i < EndSpecificEventParam - BeginSpecificEventParam + 1 ; i++)
    {
        /*%C  Compute base read                                       						*/
        if ((i == (EVENT_SPECPAR_29_ID - BeginSpecificEventParam)) || 
            (i == (EVENT_SPECPAR_30_ID - BeginSpecificEventParam)))
        {
            /*%C  Value recovery from Compute base                                        */
            DataToPush = DB_ComputeRead(ParamTable[i].DataId);
        }
        /*%C  Current base read                            						*/
        else
        {
            /*%C  Value recovery from Current base                                        */
            DataToPush = DB_CurrentRead(ParamTable[i].DataId);
            /******************************************************************************/
            /*%C  Activated settings checking, when unactivated, the value is equal to 0  */
            /******************************************************************************/

            /*%C  If apnea alarm is not activated in CPAP mode, its value = 0  */
            if (ParamTable[i].DataId == ADJUST_APNEA_U16)
            {
                if ( (DB_ControlRead(CURRENT_MODE_U16) == CPAP)
                     && (DB_ConfigRead(APNEA_ALARM_ACTIVATION) == FALSE) )
                {
                    DataToPush = 0;
                }
            }

            /*%C  If low vti is not activated, its value = 0  */
            if (ParamTable[i].DataId == ADJUST_LOW_VTI_U16)
            {
                if (DB_CurrentRead(LOW_VTI_NO_SELECT_U16) == TRUE)
                {
                    DataToPush = 0;
                }
            }

            /*%C  If high vti is not activated, its value = 0  */
            if (ParamTable[i].DataId == ADJUST_HIGH_VTI_U16)
            {
                if (DB_CurrentRead(HIGH_VTI_NO_SELECT_U16) == TRUE)
                {
                    DataToPush = 0;
                }
            }

            /*%C  If low vte is not activated, its value =0  */
            if (ParamTable[i].DataId == ADJUST_LOW_VTE_U16)
            {
                if (DB_CurrentRead(LOW_VTE_NO_SELECT_U16) == TRUE)
                {
                    DataToPush = 0;
                }
            }

            /*%C  If low vte is not activated, its value =0  */
            if (ParamTable[i].DataId == ADJUST_HIGH_VTE_U16)
            {
                if (DB_CurrentRead(HIGH_VTE_NO_SELECT_U16) == TRUE)
                {
                    DataToPush = 0;
                }
            }

            /*%C  If high rate is not activated, its value =0  */
            if (ParamTable[i].DataId == ADJUST_HIGH_R_U16)
            {
                if (DB_CurrentRead(HIGH_R_NO_SELECT_U16) == TRUE)
                {
                    DataToPush = 0;
                }
            }

            /*%C  If the backup rate is not activated, its value =0  */
            if (ParamTable[i].DataId == ADJUST_BACKUP_R_U16)
            {
                if (DB_CurrentRead(BACKUP_R_NO_SELECT_U16) == TRUE)
                {
                    DataToPush = 0;
                }
            }

            /*%C  The Adjust_Apnea unit is Second in online 2  */
            if (ParamTable[i].DataId == ADJUST_APNEA_U16)
            {
                DataToPush = DataToPush / 1000;
            }


            /*%C  If ti min is not activated, its value =0  */
            if (ParamTable[i].DataId == ADJUST_TI_MIN_U16)
            {
                DataToPush = DataToPush / 100;
            }

            /*%C  If ti max is not activated, its value =0  */
            if (ParamTable[i].DataId == ADJUST_TI_MAX_U16)
            {
                DataToPush = DataToPush / 100;
            }

            /*%C  Ti control value must be divided by 100  */
            if (ParamTable[i].DataId == ADJUST_TI_CONTROL_U16)
            {
                DataToPush = DataToPush / 100;
            }

            /*%C  P support value must be divided by 10  */
            if (ParamTable[i].DataId == ADJUST_P_SUPPORT_U16)
            {
                DataToPush = DataToPush / 10;
            }

            /*%C  P control value must be divided by 10  */
            if (ParamTable[i].DataId == ADJUST_P_CONTROL_U16)
            {
                DataToPush = DataToPush / 10;
            }

            /*%C  PEEP value must be divided by 10  */
            if (ParamTable[i].DataId == ADJUST_PEEP_U16)
            {
                DataToPush = DataToPush / 10;
            }

            /*%C  Max pressure value must be divided by 10  */
            if (ParamTable[i].DataId == ADJUST_MAX_PRESSURE_U16)
            {
                DataToPush = DataToPush / 10;
            }

            /*%C  Low PIP value must be divided by 10  */
            if (ParamTable[i].DataId == ADJUST_LOW_PIP_U16)
            {
                DataToPush = DataToPush / 10;
            }

            /*%C  High PIP value must be divided by 10  */
            if (ParamTable[i].DataId == ADJUST_HIGH_PIP_U16)
            {
                DataToPush = DataToPush / 10;
            }

            /*%C  If inspiratory sensitivity is not activated, its value =0  */
            if (ParamTable[i].DataId == ADJUST_INSP_SENS_U16)
            {
                if (DB_CurrentRead(INSP_SENS_NO_SELECT_U16) == TRUE)
                {
                    DataToPush = 0;
                }
            }

            /*%C  If target Vt is not activated, its value =0  */
            if (ParamTable[i].DataId == ADJUST_TARGET_VT_U16)
            {
                if (DB_CurrentRead(TARGET_VT_SELECT_U16) == FALSE)
                {
                    DataToPush = 0;
                }
            }

            /*%C  If sigh is not activated, sight rate value =0  */
            if (ParamTable[i].DataId == ADJUST_SIGH_CPT_U16)
            {
                if (DB_CurrentRead(ADJUST_SIGH_SELECT_U16) == FALSE)
                {
                    DataToPush = 0;
                }
            }

            /*%C  If sigh is not activated, sight vt coef value =0  */
            if (ParamTable[i].DataId == ADJUST_SIGH_VT_COEF_U16)
            {
                if (DB_CurrentRead(ADJUST_SIGH_SELECT_U16) == FALSE)
                {
                    DataToPush = 0;
                }
            }
        }               

        /*%C  Value size test (8 or 16 bits) (flash writing on 8 bits)                */
        /*%C  MSB value test  */
        if (ParamTable[i].StorageType == MSB)
        {
            /*%C     Flash writing  */
            DRV_EVENT_PushEvent(BeginSpecificEventParam + i, DataToPush >> 8);
        }
        /*%C  LSB value test  */
        else if (ParamTable[i].StorageType == LSB)
        {
            /*%C     Flash writing  */
            DRV_EVENT_PushEvent(BeginSpecificEventParam + i, DataToPush & 0x00FF);
        }
        /*%C  The value is constant (0 or 1)  */
        else if (ParamTable[i].StorageType == STORAGE_CONSTANT)
        {
            DRV_EVENT_PushEvent(BeginSpecificEventParam + i,ParamTable[i].DataId );
        }
        /*%C  The value is already sized on 8 bits  */
        else
        {
            DRV_EVENT_PushEvent(BeginSpecificEventParam + i, (UBYTE)DataToPush);
        }
    }
#endif
}
