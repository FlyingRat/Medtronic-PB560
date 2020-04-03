/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SCHED_Setup_Scheduler_Config.h                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                              										*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef SCHED_SETUP_SCHEDULER_CONFIG_H
#define SCHED_SETUP_SCHEDULER_CONFIG_H





/************************* DEFINITION DES TACHES **************************/
/*                                                                        */
/* On définit les taches et les fonctions a appeler par une étiquette qui */
/* contient un pointeur sur la tache ou la fonction en question.          */
/* Les noms des étiquettes sont repris par le fichier scheduler_config.c  */
/* et ne doivent donc pas etre modifies.                                  */
/*                                                                        */
/* Pour les étiquettes suivantes:                                         */
/*    TASK_1_MAIN_FUNC, TASK_2_MAIN_FUNC, TASK_3_MAIN_FUNC,...            */
/* Il n'est pas possible d'attribuer la pseudo-variable NO_FUNCTION       */
/*                                                                        */
/* Les pseudo_variables TASK_1, TASK_2, TASK_3,... contiennent le numéro  */
/* de priorité des taches correspondantes                                 */
/*                                                                        */
/* Les étiquettes TACHE1, TACHE2, TACHE3,... sont modifiables. Elles sont */
/* utilisées pour l'affectation des pas du scheduler                      */
/*                                                                        */
/* Le nombre de tache est défini  dans l'étiquette NUMBER_OF_TASKS. C'est */
/* cette etiquette qui fige la taille ROM de la table                     */
/*                                                                        */
/* REM: On peut définir plus de tache que le nombre inscrit dans          */
/*      NUMBER_OF_TASKS mais elles ne seront pas ajoutées dans la table   */
/*                                                                        */
/* REM: Le chien de garde est rafraîchi a chaque tour de séquenceur et a  */
/*      chaque réveil                                                     */
/*                                                                        */
/* REM: Une tache d'init est du type:  void MyFuncInit(void)              */
/*                                                                        */
/*      Une tache main est du type:    task_state_t MyFuncMain(void)      */
/*                                                                        */
/*        afin de renvoyer l'étiquette TASK_ACTIVE ou TASK_INACTIVE       */   
/*                                                                        */
/**************************************************************************/

/*--------------------------------------------------------------------*/
/* nombre de tache a sequencer MINI:1  MAXI:30                        */
/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/* definition des taches                                              */
/* pour chaque tache, on definit:                                     */
/* - un nom de tache                                                  */
/* - une fonction principale                                          */
/*                                                                    */
/* !!! LA FONCTION MAIN RENVOIE UN ARGUMENT DE TYPE task_state_t  !!! */
/*                                                                    */
/* rem: la tache 1 est la plus prioritaire                            */
/*      la tache 30 est la moins prioritaire                          */
/*--------------------------------------------------------------------*/
/****************************** tache 1 *******************************/
/****************************** tache 1 *******************************/
#define IT_WATCHDOG_TACHE1 TASK_1
#define TASK_1_MAIN_FUNC It_watchdog
/****************************** tache 2 ******************************/
#define SYS_SETUP_LAUNCH_TACHE2 TASK_2
#define TASK_2_MAIN_FUNC SYS_SetupLaunch 
/****************************** tache 3 ******************************/
#define TIM_LAUNCH_TACHE3 TASK_3
#define TASK_3_MAIN_FUNC TIM_Launch
/****************************** tache 4 ******************************/
#define SYS_INTERPOLATION_TACHE4 TASK_4
#define TASK_4_MAIN_FUNC SYS_Interpolation
/****************************** tache 5 ******************************/
#define SET_CALIBRATION_MANAGEMENT_TACHE5 TASK_5
#define TASK_5_MAIN_FUNC SET_CalibrationManagement
/****************************** tache 6 ******************************/
#define SET_ACTUATORS_TACHE6 TASK_6  
#define TASK_6_MAIN_FUNC SET_Actuator
/****************************** tache 7 ******************************/
#define SET_RTC_MNGT_TACHE7 TASK_7
#define TASK_7_MAIN_FUNC SET_RTC_Mngt
/****************************** tache 8 ******************************/
#define DRV_EVENT_LAUNCH_TACHE8 TASK_8
#define TASK_8_MAIN_FUNC DRV_EVENT_Launch
/****************************** tache 9 ******************************/
#define SET_TECHNICAL_ALARMS_TACHE9 TASK_9
#define TASK_9_MAIN_FUNC SET_TechnicalAlarms
/****************************** tache 10 ******************************/
#define KEY_EVENT_LAUNCH_TACHE10 TASK_10   
#define TASK_10_MAIN_FUNC HMI_KeyboardEventLaunch
/****************************** tache 11 ******************************/
#define IHM_LAUNCH_TACHE11 TASK_11
#define TASK_11_MAIN_FUNC IHM_TimerEventLauch
/****************************** tache 12 ******************************/
#define DISPLAY_FIFO_READ_TACHE12 TASK_12
#define TASK_12_MAIN_FUNC DIS_FifoRead
/****************************** tache 13 ******************************/
#define COM_LAUNCH_TACHE_13 TASK_13
#define TASK_13_MAIN_FUNC DRV_COM_Launch
/****************************** tache 14 ******************************/
#define DRV_SPI_POWERSUPPLY_UPDATE_TACHE_14 TASK_14
#define TASK_14_MAIN_FUNC DRV_SPIPowerSupplyUpdate
/****************************** tache 15 ******************************/
#define TACHE15 TASK_15
#define TASK_15_MAIN_FUNC NO_FUNCTION
/****************************** tache 16 ******************************/
#define TACHE16 TASK_16
#define TASK_16_MAIN_FUNC NO_FUNCTION
/****************************** tache 17 ******************************/
#define TACHE17 TASK_17
#define TASK_17_MAIN_FUNC NO_FUNCTION
/****************************** tache 18 ******************************/
#define TACHE18 TASK_18
#define TASK_18_MAIN_FUNC NO_FUNCTION
/****************************** tache 19 ******************************/
#define TACHE19 TASK_19
#define TASK_19_MAIN_FUNC NO_FUNCTION
/****************************** tache 20 ******************************/
#define TACHE20 TASK_20
#define TASK_20_MAIN_FUNC NO_FUNCTION
/****************************** tache 21 ******************************/
#define TACHE21 TASK_21
#define TASK_21_MAIN_FUNC NO_FUNCTION
/****************************** tache 22 ******************************/
#define TACHE22 TASK_22
#define TASK_22_MAIN_FUNC NO_FUNCTION
/****************************** tache 23 ******************************/
#define TACHE23 TASK_23
#define TASK_23_MAIN_FUNC NO_FUNCTION
/****************************** tache 24 ******************************/
#define TACHE24 TASK_24
#define TASK_24_MAIN_FUNC NO_FUNCTION
/****************************** tache 25 ******************************/
#define TACHE25 TASK_25
#define TASK_25_MAIN_FUNC NO_FUNCTION
/****************************** tache 26 ******************************/
#define TACHE26 TASK_26
#define TASK_26_MAIN_FUNC NO_FUNCTION
/****************************** tache 27 ******************************/
#define TACHE27 TASK_217
#define TASK_27_MAIN_FUNC NO_FUNCTION
/****************************** tache 28 ******************************/
#define TACHE28 TASK_28
#define TASK_28_MAIN_FUNC NO_FUNCTION
/****************************** tache 29 ******************************/
#define TACHE29 TASK_29
#define TASK_29_MAIN_FUNC NO_FUNCTION
/****************************** tache 30 ******************************/
#define TACHE30 TASK_30
#define TASK_30_MAIN_FUNC NO_FUNCTION

/*********** DEFINITION DES PAS DU SEQUENCEUR PRINCIPAL *******************/
/*                                                                        */
/* Un pas de séquenceur est défini par une étiquette dont la construction */
/* est imposee: SCHED1_STEP[n]_ACTIVABLE_TASKS                            */
/*  [n] varie de 1 a 32 et représente le numéro du pas                    */
/* Ce schéma de construction est repris par le fichier scheduler_configu- */
/* -ration.c et ne doit donc pas être modifie                             */
/*                                                                        */
/* Le nombre de pas est définit dans l'étiquette SCHED1_STEP_NUMBER. C'est*/
/* cette étiquette qui fige la taille ROM de la table                     */
/*                                                                        */
/* REM: On peut définir plus de pas que le nombre inscrit dans            */
/*      SCHED1_STEP_NUMBER mais ils ne seront pas ajoutes dans la table   */
/*                                                                        */
/* REM: Un pas vide se définit avec la pseudo-variable EMPTY              */
/*                                                                        */
/**************************************************************************/

/*--------------------------------------------------------------------*/
/* nombre de pas du séquenceur principal  MINI:1  MAXI:32             */
/*--------------------------------------------------------------------*/
#define cSETUP_SCHED1_STEP_NUMBER 4//4
   
/*--------------------------------------------------------------------*/
/* définition de l'ordre de séquencement des taches: pour chaque pas  */
/* du séquenceur, on déclare le nom des taches a lancer               */
/*--------------------------------------------------------------------*/
/* step 1 */
#define SCHED1_STEP_1_ACTIVABLE_TASKS  SYS_INTERPOLATION_TACHE4 + COM_LAUNCH_TACHE_13 + DRV_EVENT_LAUNCH_TACHE8 + DISPLAY_FIFO_READ_TACHE12 + TIM_LAUNCH_TACHE3 + SYS_SETUP_LAUNCH_TACHE2 + SET_CALIBRATION_MANAGEMENT_TACHE5 + SET_ACTUATORS_TACHE6 + SET_RTC_MNGT_TACHE7 + KEY_EVENT_LAUNCH_TACHE10 + DRV_SPI_POWERSUPPLY_UPDATE_TACHE_14

/* step 2 */
#define SCHED1_STEP_2_ACTIVABLE_TASKS  SYS_INTERPOLATION_TACHE4 + COM_LAUNCH_TACHE_13 +  DRV_EVENT_LAUNCH_TACHE8	+ DISPLAY_FIFO_READ_TACHE12 + SET_TECHNICAL_ALARMS_TACHE9 + DRV_SPI_POWERSUPPLY_UPDATE_TACHE_14

/* step 3 */
#define SCHED1_STEP_3_ACTIVABLE_TASKS  SYS_INTERPOLATION_TACHE4 + COM_LAUNCH_TACHE_13 + DRV_EVENT_LAUNCH_TACHE8 + DISPLAY_FIFO_READ_TACHE12 + TIM_LAUNCH_TACHE3 + SYS_SETUP_LAUNCH_TACHE2 + SET_CALIBRATION_MANAGEMENT_TACHE5 + SET_ACTUATORS_TACHE6 + SET_RTC_MNGT_TACHE7 + KEY_EVENT_LAUNCH_TACHE10	+ DRV_SPI_POWERSUPPLY_UPDATE_TACHE_14

/* step 4 */
#define SCHED1_STEP_4_ACTIVABLE_TASKS  SYS_INTERPOLATION_TACHE4 + COM_LAUNCH_TACHE_13 + DRV_EVENT_LAUNCH_TACHE8 + DISPLAY_FIFO_READ_TACHE12 + SET_TECHNICAL_ALARMS_TACHE9 + IT_WATCHDOG_TACHE1 + IHM_LAUNCH_TACHE11	+ DRV_SPI_POWERSUPPLY_UPDATE_TACHE_14

		  								  
#endif
/************************************************************************/
