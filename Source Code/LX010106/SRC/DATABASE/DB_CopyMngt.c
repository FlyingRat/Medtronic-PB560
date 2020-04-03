/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_CopyMngt.c 				   				                  		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	this function makes a copy from the		*/
/*%C         adjust to the current base       											*/
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter : 			None		        			                  	*/
/*%IO Input/Output Parameter : 	None 	        			                  		*/
/*%O 	Output Parameter : 			None	                       				  		*/
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          	*/
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "structure.h"
#include "define.h"
#include "DB_AlarmStatus.h"
#include "DB_Control.h"
#include "DB_Current.h"
#include "DB_Rtc.h"
#include "DB_Event.h"
#include "DB_IhmAccessParaDataBase.h"
#include "DRV_VarEeprom.h"
#include "Security_Datas.h"
#include "DB_Compute.h"
#include "DB_CopyMngt.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void DB_CopyMngt(void)
{

    /* Ventilation mode recovery */
    e_MODE_TYPES Adjust_Mode  = DB_ConfigRead(ADJUST_MODE_U16);

    /* Ventil request recovery*/
    UWORD16 Ventil_Req   = DB_ConfigRead(VENTIL_REQ_U16);

    /* Current mode recovery */
    e_MODE_TYPES Current_Mode = DB_ControlRead(CURRENT_MODE_U16);

    /* Ti_min and Ti_max auto flags recovery */
    UWORD16 TiMaxAutoSelect = DB_CurrentRead(TI_MAX_AUTO_SELECT_U16);
    UWORD16 TiMinAutoSelect = DB_CurrentRead(TI_MIN_AUTO_SELECT_U16);

    /* Ventil authorization recovery */
    UWORD16 Ventil_Authorization = DB_ControlRead(VENTIL_AUTHORIZATION_U16);

    /* Id declaration */
    UWORD16 Current_Base_Id = 0;

    /* Control R declaration */
    UWORD16 AdjustControlR = DB_CurrentRead(ADJUST_CONTROL_R_U16);

    /* Change mode declaration */
    UWORD16 Change_Mode = DB_ControlRead(CHANGE_MODE_U16);

    /* Adjustment in progress ????  */
    UWORD16 Adjustment_In_Progress = DB_ControlRead(ADJUSTMENT_IN_PROGRESS_U16);

    /* read of the pressure convention */
    UWORD16 Pressure_Support_Relative = DB_ConfigRead(PRESSURE_SUPPORT_RELATIVE_U16);

    static UWORD16 Previous_Mode = 0;
    static UWORD16 Flag_Previous_Mode = 0;
    static UWORD16 PreviousVsimvBackupR = 0;
    static UWORD16 PreviousPsimvBackupR = 0;

    if (Flag_Previous_Mode ==  0)
    {
        Previous_Mode = DB_ControlRead(CURRENT_MODE_U16);
        Flag_Previous_Mode = 1;
    }


    /* Voir fichier sous VSS:                                                     */
    /* "Etude Soft\Analyse Data Base\Gestion  des  réglages  des  paramètres.doc" */
    /* Vérifier qu'on ne recopie la base dans current que lorsqu'on a modifie     */
    /* un paramètre (sauf lors d'un changement de mode)                           */
    /*  => créer un flag modif_param (data globale)                               */

    /*%C At each change mode, an alarm reset is made         */
    /*%C The inhibited and reset flag are reseted too         */
    if (Current_Mode != Previous_Mode)
    {
        /*%C 	High pressure flags initilization         */
        DB_ControlWrite(HIGH_PRESSURE_DETECTED_U16,
                        FALSE);
        DB_ControlWrite(HIGH_PRESSURE_EXHALATION_DETECTED_U16,
                        FALSE);
        DB_ConfigWrite(PREVIOUS_MODE_U16,Current_Mode);
    }

    /*%C Parameter change for an active mode with ventilation change mode         */
    /*%C validation, ventilation off (stand by), during bases initialization      */

    if ( ( (Adjust_Mode == Current_Mode)
           || (Change_Mode == TRUE)  
           || ( (Ventil_Authorization == FALSE)
                && (Ventil_Req == FALSE) ) 
           || (DB_StartInitRequest == FALSE) )
         && (Adjustment_In_Progress == FALSE) )
    {
        /*%C  Current mode refresh */
        DB_ControlWrite(CURRENT_MODE_U16,
                        Adjust_Mode);



        /*%C  Copy from VOL to CURRENT base  */
        if (Adjust_Mode == VOL)
        {
            /*%C     Copy all the parameters */
            for (Current_Base_Id=0;Current_Base_Id<end_of_adjust_table;Current_Base_Id++)
            {
                DB_CurrentWrite(Current_Base_Id,
                                EEP_DB_VOL_Adjust[Current_Base_Id]);
            }
        }
        /*%C  Copy from PRES to CURRENT base  */
        else if (Adjust_Mode == PRES)
        {
            /*%C     Copy all the parameters */
            for (Current_Base_Id=0;Current_Base_Id<end_of_adjust_table;Current_Base_Id++)
            {
                /*%C        Inspiratory pressure set point compute  */
                if (Current_Base_Id == PI_SET_POINT_U16)
                {
                    if (Pressure_Support_Relative == TRUE)
                    {
                        DB_CurrentWrite(Current_Base_Id,
                                        EEP_DB_PRES_Adjust[ADJUST_P_CONTROL_U16] +
                                        EEP_DB_PRES_Adjust[ADJUST_PEEP_U16]);
                        EEP_DB_PRES_Adjust[Current_Base_Id]= EEP_DB_PRES_Adjust[ADJUST_P_CONTROL_U16] +
                                                             EEP_DB_PRES_Adjust[ADJUST_PEEP_U16];
                    }
                    else
                    {
                        DB_CurrentWrite(Current_Base_Id,
                                        EEP_DB_PRES_Adjust[ADJUST_P_CONTROL_U16]);
                        EEP_DB_PRES_Adjust[Current_Base_Id]= EEP_DB_PRES_Adjust[ADJUST_P_CONTROL_U16];
                    }
                }
                /*%C        Max pressure compute  */
                if (Current_Base_Id == ADJUST_MAX_PRESSURE_U16)
                {

                    DB_CurrentWrite(Current_Base_Id,
                                    EEP_DB_PRES_Adjust[ADJUST_MAX_PRESSURE_U16]);
                }
                /*%C        Rise time affectation  */
                else if (Current_Base_Id == RISE_TIME_U16)
                {
                    DB_RiseTimeCompute(PRES);
                }
                else
                {
                    DB_CurrentWrite(Current_Base_Id,
                                    EEP_DB_PRES_Adjust[Current_Base_Id]);
                }
            }
        }
        /*%C  Copy from PSV to CURRENT base  */
        else if (Adjust_Mode == PSVT)
        {
            /*%C     Copy all the parameters */
            for (Current_Base_Id=0;Current_Base_Id<end_of_adjust_table;Current_Base_Id++)
            {
                /*%C        Inspiratory pressure set point compute  */
                if (Current_Base_Id == PI_SET_POINT_U16)
                {
                    if (Pressure_Support_Relative == TRUE)
                    {
                        DB_CurrentWrite(Current_Base_Id,
                                        EEP_DB_PSV_Adjust[ADJUST_P_SUPPORT_U16] +
                                        EEP_DB_PSV_Adjust[ADJUST_PEEP_U16]);
                        EEP_DB_PSV_Adjust[Current_Base_Id]= EEP_DB_PSV_Adjust[ADJUST_P_SUPPORT_U16] +
                                                            EEP_DB_PSV_Adjust[ADJUST_PEEP_U16];
                    }
                    else
                    {
                        DB_CurrentWrite(Current_Base_Id,
                                        EEP_DB_PSV_Adjust[ADJUST_P_SUPPORT_U16]);
                        EEP_DB_PSV_Adjust[Current_Base_Id]= EEP_DB_PSV_Adjust[ADJUST_P_SUPPORT_U16];
                    }
                }
                /*%C        Inspiratory pressure set point compute  */
                if (Current_Base_Id == ADJUST_MAX_PRESSURE_U16)
                {
                    DB_CurrentWrite(Current_Base_Id,
                                    EEP_DB_PSV_Adjust[ADJUST_MAX_PRESSURE_U16]);
                }
                /*%C        Exh sens affectation  */
                else if ( (Current_Base_Id == ADJUST_EXH_SENS_U16)
                          && ( Current_Mode == CPAP) )
                {
                    DB_CurrentWrite(ADJUST_EXH_SENS_U16,
                                    0);
                }
                /*%C        Rise time affectation  */
                else if (Current_Base_Id == RISE_TIME_U16)
                {
                    DB_CurrentWrite(RISE_TIME_U16,
                                    RiseTime[EEP_DB_PSV_Adjust[ADJUST_RISE_TIME_U16] - 1]);
                }
                else if (Current_Base_Id == ADJUST_INSP_SENS_U16)
                {
                    if (Adjustment_In_Progress == FALSE)
                    {
                        DB_CurrentWrite(ADJUST_INSP_SENS_U16,
                                        EEP_DB_PSV_Adjust[ADJUST_INSP_SENS_U16]);
                    }
                    else
                    {
                    }   
                }
                else
                {
                    DB_CurrentWrite(Current_Base_Id,
                                    EEP_DB_PSV_Adjust[Current_Base_Id]);
                }
            }
        }
        /*%C  Copy from CPAP to CURRENT base  */
        else if (Adjust_Mode == CPAP)
        {
            /*%C     Copy all the parameters */
            for (Current_Base_Id=0;Current_Base_Id<end_of_adjust_table;Current_Base_Id++)
            {
                /*%C        Inspiratory pressure set point compute  */
                if (Current_Base_Id == PI_SET_POINT_U16)
                {
                    DB_CurrentWrite(Current_Base_Id,
                                    EEP_DB_CPAP_Adjust[ADJUST_PEEP_U16]);
                    EEP_DB_CPAP_Adjust[Current_Base_Id]= EEP_DB_CPAP_Adjust[ADJUST_PEEP_U16];
                    /*%C        		Compuited Pi set point initialization  */
                    DB_ComputeWrite(COMPUTED_PI_SET_POINT_U16,
                                    EEP_DB_CPAP_Adjust[ADJUST_PEEP_U16]);
                }
                /*%C        Rise time affectation  */
                else if (Current_Base_Id == RISE_TIME_U16)
                {
                    DB_CurrentWrite(RISE_TIME_U16,
                                    400);
                }
                else
                {
                    DB_CurrentWrite(Current_Base_Id,
                                    EEP_DB_CPAP_Adjust[Current_Base_Id]);
                }
            }
        }
        /*%C  Copy from VSIMV to CURRENT base  */
        else if (Adjust_Mode == VSIMV)
        {
            /*%C     Copy all the parameters */
            for (Current_Base_Id=0;Current_Base_Id<end_of_adjust_table;Current_Base_Id++)
            {
                /*%C        Inspiratory pressure set point compute  */
                if (Current_Base_Id == PI_SET_POINT_U16)
                {
                    if (Pressure_Support_Relative == TRUE)
                    {
                        DB_CurrentWrite(Current_Base_Id,
                                        EEP_DB_VSIMV_Adjust[ADJUST_P_SUPPORT_U16]+
                                        EEP_DB_VSIMV_Adjust[ADJUST_PEEP_U16]);
                        EEP_DB_VSIMV_Adjust[Current_Base_Id]= EEP_DB_VSIMV_Adjust[ADJUST_P_SUPPORT_U16] +
                                                              EEP_DB_VSIMV_Adjust[ADJUST_PEEP_U16];
                        /*%C        			Compuited Pi set point initialization  */
                        DB_ComputeWrite(COMPUTED_PI_SET_POINT_U16,
                                        EEP_DB_VSIMV_Adjust[ADJUST_P_SUPPORT_U16]+
                                        EEP_DB_VSIMV_Adjust[ADJUST_PEEP_U16]);
                    }
                    else
                    {
                        DB_CurrentWrite(Current_Base_Id,
                                        EEP_DB_VSIMV_Adjust[ADJUST_P_SUPPORT_U16]);
                        EEP_DB_VSIMV_Adjust[Current_Base_Id]= EEP_DB_VSIMV_Adjust[ADJUST_P_SUPPORT_U16];
                        /*%C        			Compuited Pi set point initialization  */
                        DB_ComputeWrite(COMPUTED_PI_SET_POINT_U16,
                                        EEP_DB_VSIMV_Adjust[ADJUST_P_SUPPORT_U16]);
                    }
                }
                /*%C        Simv Backup R = max(8,Control R)  */
                else if (Current_Base_Id == ADJUST_CONTROL_R_U16)
                {
                    DB_CurrentWrite(Current_Base_Id,
                                    EEP_DB_VSIMV_Adjust[Current_Base_Id]);

                    AdjustControlR = DB_CurrentRead(ADJUST_CONTROL_R_U16);

                    Simv_Backup_R = cSIMV_BACKUP_R_MIN;

                    if (Simv_Backup_R < AdjustControlR)
                    {
                        Simv_Backup_R = AdjustControlR;
                    }

                    DB_CurrentWrite(ADJUST_BACKUP_R_U16, Simv_Backup_R);
                    if (Simv_Backup_R != PreviousVsimvBackupR)
                    {
                        DB_WriteDataInEepAndRam(&EEP_DB_VSIMV_Adjust[ADJUST_BACKUP_R_U16],
                                                Simv_Backup_R);
                        PreviousVsimvBackupR = Simv_Backup_R;                           
                    }
                }
                /*%C        Rise time affectation  */
                else if (Current_Base_Id == RISE_TIME_U16)
                {
                    DB_RiseTimeCompute(VSIMV);
                }
                /*%C        Computed rate computing  */
                else if (Current_Base_Id == ADJUST_BACKUP_R_U16)
                {
                    /*%C        	Computed rate initialization  */
                    DB_ComputeWrite(COMPUTED_RATE_U16,
                                    EEP_DB_VSIMV_Adjust[ADJUST_BACKUP_R_U16]);
                    DB_CurrentWrite(Current_Base_Id,
                                    EEP_DB_VSIMV_Adjust[Current_Base_Id]);
                }
                else if (Current_Base_Id == ADJUST_INSP_SENS_U16)
                {
                    if (Adjustment_In_Progress == FALSE)
                    {
                        DB_CurrentWrite(ADJUST_INSP_SENS_U16,
                                        EEP_DB_VSIMV_Adjust[ADJUST_INSP_SENS_U16]);
                    }
                    else
                    {
                    }   
                }

                /*%C        else parameter writing in current base  */
                else
                {
                    DB_CurrentWrite(Current_Base_Id,
                                    EEP_DB_VSIMV_Adjust[Current_Base_Id]);
                }
            }
        }
        /*%C  Copy from PSIMV to CURRENT base  */
        else if (Adjust_Mode == PSIMV)
        {
            for (Current_Base_Id=0;Current_Base_Id<end_of_adjust_table;Current_Base_Id++)
            {
                /*%C        Inspiratory pressure set point compute  */
                if (Current_Base_Id == PI_SET_POINT_U16)
                {
                    if (Pressure_Support_Relative == TRUE)
                    {
                        DB_CurrentWrite(Current_Base_Id,
                                        EEP_DB_PSIMV_Adjust[ADJUST_P_SUPPORT_U16]+
                                        EEP_DB_PSIMV_Adjust[ADJUST_PEEP_U16]);
                        EEP_DB_PSIMV_Adjust[Current_Base_Id]= EEP_DB_PSIMV_Adjust[ADJUST_P_SUPPORT_U16] +
                                                              EEP_DB_PSIMV_Adjust[ADJUST_PEEP_U16];
                        /*%C        			Compuited Pi set point initialization  */
                        DB_ComputeWrite(COMPUTED_PI_SET_POINT_U16,
                                        EEP_DB_PSIMV_Adjust[ADJUST_P_SUPPORT_U16]+
                                        EEP_DB_PSIMV_Adjust[ADJUST_PEEP_U16]);

                        DB_CurrentWrite(Current_Base_Id,
                                        EEP_DB_PSIMV_Adjust[ADJUST_P_CONTROL_U16]+
                                        EEP_DB_PSIMV_Adjust[ADJUST_PEEP_U16]);
                        EEP_DB_PSIMV_Adjust[Current_Base_Id]= EEP_DB_PSIMV_Adjust[ADJUST_P_CONTROL_U16] +
                                                              EEP_DB_PSIMV_Adjust[ADJUST_PEEP_U16];
                        /*%C        			Compuited Pi set point initialization  */
                        DB_ComputeWrite(COMPUTED_PI_SET_POINT_U16,
                                        EEP_DB_PSIMV_Adjust[ADJUST_P_CONTROL_U16]+
                                        EEP_DB_PSIMV_Adjust[ADJUST_PEEP_U16]);
                    }
                    else
                    {
                        DB_CurrentWrite(Current_Base_Id,
                                        EEP_DB_PSIMV_Adjust[ADJUST_P_SUPPORT_U16]);
                        EEP_DB_PSIMV_Adjust[Current_Base_Id]= EEP_DB_PSIMV_Adjust[ADJUST_P_SUPPORT_U16];
                        /*%C        			Compuited Pi set point initialization  */
                        DB_ComputeWrite(COMPUTED_PI_SET_POINT_U16,
                                        EEP_DB_PSIMV_Adjust[ADJUST_P_SUPPORT_U16]);

                        DB_CurrentWrite(Current_Base_Id,
                                        EEP_DB_PSIMV_Adjust[ADJUST_P_CONTROL_U16]);
                        EEP_DB_PSIMV_Adjust[Current_Base_Id]= EEP_DB_PSIMV_Adjust[ADJUST_P_CONTROL_U16];
                        /*%C        			Compuited Pi set point initialization  */
                        DB_ComputeWrite(COMPUTED_PI_SET_POINT_U16,
                                        EEP_DB_PSIMV_Adjust[ADJUST_P_CONTROL_U16]);
                    }

                }
                /*%C        Simv Backup R = max(8,Control R)  */
                else if (Current_Base_Id == ADJUST_CONTROL_R_U16)
                {
                    DB_CurrentWrite(Current_Base_Id,
                                    EEP_DB_PSIMV_Adjust[Current_Base_Id]);

                    AdjustControlR = DB_CurrentRead(ADJUST_CONTROL_R_U16);

                    Simv_Backup_R = cSIMV_BACKUP_R_MIN;

                    if (Simv_Backup_R < AdjustControlR)
                    {
                        Simv_Backup_R = AdjustControlR;
                    }

                    DB_CurrentWrite(ADJUST_BACKUP_R_U16, Simv_Backup_R);
                    if (Simv_Backup_R != PreviousPsimvBackupR)
                    {
                        DB_WriteDataInEepAndRam(&EEP_DB_PSIMV_Adjust[ADJUST_BACKUP_R_U16],
                                                Simv_Backup_R);
                        PreviousPsimvBackupR = Simv_Backup_R;                           
                    }
                }
                /*%C        Rise time affectation  */
                else if (Current_Base_Id == RISE_TIME_U16)
                {
                    DB_RiseTimeCompute(PSIMV);
                }
                /*%C        Ti max skip if auto  */
                else if ( (Current_Base_Id == ADJUST_TI_MAX_U16)
                          && (TiMaxAutoSelect == TRUE) )
                {
                    /*%C        	No function  */
                }
                /*%C        Ti min skip if auto  */
                else if ( (Current_Base_Id == ADJUST_TI_MIN_U16)
                          && (TiMinAutoSelect == TRUE) )
                {
                    /*%C        	No function  */
                }
                /*%C        else parameter writing in current base  */
                else
                {
                    DB_CurrentWrite(Current_Base_Id,
                                    EEP_DB_PSIMV_Adjust[Current_Base_Id]);
                }
            }
        }
    }
    Previous_Mode = Current_Mode;
} 
