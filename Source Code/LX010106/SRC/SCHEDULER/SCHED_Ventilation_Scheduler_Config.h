/*****************************************************************************/
/*                                                                            */
/* Project N�  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SCHED_Ventilation_Scheduler_Config.h                           */
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

#ifndef SCHED_VENTILATION_SCHEDULER_CONFIG_H
#define SCHED_VENTILATION_SCHEDULER_CONFIG_H

/************************* DEFINITION DES TACHES **************************/
/*                                                                        */
/* On d�finit les taches et les fonctions a appeler par une �tiquette qui */
/* contient un pointeur sur la tache ou la fonction en question.          */
/* Les noms des �tiquettes sont repris par le fichier scheduler_config.c  */
/* et ne doivent donc pas etre modifies.                                  */
/*                                                                        */
/* Pour les �tiquettes suivantes:                                         */
/*    TASK_1_MAIN_FUNC, TASK_2_MAIN_FUNC, TASK_3_MAIN_FUNC,...            */
/* Il n'est pas possible d'attribuer la pseudo-variable NO_FUNCTION       */
/*                                                                        */
/* Les pseudo_variables TASK_1, TASK_2, TASK_3,... contiennent le num�ro  */
/* de priorit� des taches correspondantes                                 */
/*                                                                        */
/* Les �tiquettes TACHE1, TACHE2, TACHE3,... sont modifiables. Elles sont */
/* utilis�es pour l'affectation des pas du scheduler                      */
/*                                                                        */
/* Le nombre de tache est d�fini  dans l'�tiquette NUMBER_OF_TASKS. C'est */
/* cette etiquette qui fige la taille ROM de la table                     */
/*                                                                        */
/* REM: On peut d�finir plus de tache que le nombre inscrit dans          */
/*      NUMBER_OF_TASKS mais elles ne seront pas ajout�es dans la table   */
/*                                                                        */
/* REM: Le chien de garde est rafra�chi a chaque tour de s�quenceur et a  */
/*      chaque r�veil                                                     */
/*                                                                        */
/* REM: Une tache d'init est du type:  void MyFuncInit(void)              */
/*                                                                        */
/*      Une tache main est du type:    task_state_t MyFuncMain(void)      */
/*                                                                        */
/*        afin de renvoyer l'�tiquette TASK_ACTIVE ou TASK_INACTIVE       */   
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
#define IT_WATCHDOG_TACHE1 TASK_1
#define TASK_1_MAIN_FUNC It_watchdog
/****************************** tache 2 ******************************/
#define SYS_LAUNCH_TACHE2 TASK_2
#define TASK_2_MAIN_FUNC SYS_VentilationLaunch
/****************************** tache 3 ******************************/
#define TIM_LAUNCH_TACHE3 TASK_3
#define TASK_3_MAIN_FUNC TIM_Launch
/****************************** tache 4 ******************************/
#define SYS_INTERPOLATION_TACHE4 TASK_4
#define TASK_4_MAIN_FUNC SYS_Interpolation
/****************************** tache 5 ******************************/
#define VEN_CYCLES_TACHE5 TASK_5
#define TASK_5_MAIN_FUNC VEN_Cycles
/****************************** tache 6 ******************************/
#define VEN_COMPUTE_TACHE6 TASK_6  
#define TASK_6_MAIN_FUNC VEN_Compute
/****************************** tache 7 ******************************/
#define VEN_ACTUATORS_TACHE7 TASK_7
#define TASK_7_MAIN_FUNC VEN_Actuators
/****************************** tache 8 ******************************/
#define VEN_SECURITY_TACHE8 TASK_8
#define TASK_8_MAIN_FUNC VEN_Security
/****************************** tache 9 ******************************/
#define DRV_EVENT_TACHE9 TASK_9   
#define TASK_9_MAIN_FUNC DRV_EVENT_Launch
/****************************** tache 10 ******************************/
#define DISPLAY_FIFO_READ_TACHE10 TASK_10 
#define TASK_10_MAIN_FUNC DIS_FifoRead
/****************************** tache 11 ******************************/
#define IHM_LAUNCH_TACHE11 TASK_11
#define TASK_11_MAIN_FUNC IHM_TimerEventLauch
/****************************** tache 12 ******************************/
#define KEY_EVENT_LAUNCH_TACHE12 TASK_12
#define TASK_12_MAIN_FUNC HMI_KeyboardEventLaunch 
/****************************** tache 13 ******************************/
#define MONIT_FLASH_TACHE_13 TASK_13
#define TASK_13_MAIN_FUNC DRV_MONIT_Launch
/****************************** tache 14 ******************************/
#define TREND_FLASH_TACHE_14 TASK_14
#define TASK_14_MAIN_FUNC DRV_TREND_Launch
/****************************** tache 15 ******************************/
#define DRV_USB_LAUNCH_TACHE15 TASK_15
#define TASK_15_MAIN_FUNC DRV_USB_Launch
/****************************** tache 16 ******************************/
#define COM_LAUNCH_TACHE_16 TASK_16
#define TASK_16_MAIN_FUNC DRV_COM_Launch
/****************************** tache 17 ******************************/
#define DRV_SPI_POWERSUPPLY_UPDATE_TACHE_17 TASK_17
#define TASK_17_MAIN_FUNC DRV_SPIPowerSupplyUpdate
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
/* Un pas de s�quenceur est d�fini par une �tiquette dont la construction */
/* est imposee: SCHED1_STEP[n]_ACTIVABLE_TASKS                            */
/*  [n] varie de 1 a 32 et repr�sente le num�ro du pas                    */
/* Ce sch�ma de construction est repris par le fichier scheduler_configu- */
/* -ration.c et ne doit donc pas �tre modifie                             */
/*                                                                        */
/* Le nombre de pas est d�finit dans l'�tiquette SCHED1_STEP_NUMBER. C'est*/
/* cette �tiquette qui fige la taille ROM de la table                     */
/*                                                                        */
/* REM: On peut d�finir plus de pas que le nombre inscrit dans            */
/*      SCHED1_STEP_NUMBER mais ils ne seront pas ajoutes dans la table   */
/*                                                                        */
/* REM: Un pas vide se d�finit avec la pseudo-variable EMPTY              */
/*                                                                        */
/**************************************************************************/

/*--------------------------------------------------------------------*/
/* nombre de pas du s�quenceur principal  MINI:1  MAXI:32             */
/*--------------------------------------------------------------------*/
#define cVENTILATION_SCHED1_STEP_NUMBER 4
   
/*--------------------------------------------------------------------*/
/* d�finition de l'ordre de s�quencement des taches: pour chaque pas  */
/* du s�quenceur, on d�clare le nom des taches a lancer               */
/*--------------------------------------------------------------------*/
/* step 1 */
#define SCHED1_STEP_1_ACTIVABLE_TASKS  SYS_INTERPOLATION_TACHE4 + DRV_EVENT_TACHE9 + DISPLAY_FIFO_READ_TACHE10 + TIM_LAUNCH_TACHE3 + SYS_LAUNCH_TACHE2 + VEN_CYCLES_TACHE5 + VEN_ACTUATORS_TACHE7 + VEN_SECURITY_TACHE8 + KEY_EVENT_LAUNCH_TACHE12 + COM_LAUNCH_TACHE_16 + DRV_SPI_POWERSUPPLY_UPDATE_TACHE_17 + DRV_USB_LAUNCH_TACHE15 + MONIT_FLASH_TACHE_13 + TREND_FLASH_TACHE_14

/* step 2 */
#define SCHED1_STEP_2_ACTIVABLE_TASKS SYS_INTERPOLATION_TACHE4 + DRV_EVENT_TACHE9 + DISPLAY_FIFO_READ_TACHE10 + VEN_COMPUTE_TACHE6 + COM_LAUNCH_TACHE_16 + DRV_SPI_POWERSUPPLY_UPDATE_TACHE_17 + DRV_USB_LAUNCH_TACHE15 + MONIT_FLASH_TACHE_13 + TREND_FLASH_TACHE_14


/* step 3 */
#define SCHED1_STEP_3_ACTIVABLE_TASKS  SYS_INTERPOLATION_TACHE4 + DRV_EVENT_TACHE9 + DISPLAY_FIFO_READ_TACHE10 + TIM_LAUNCH_TACHE3 + SYS_LAUNCH_TACHE2 + VEN_CYCLES_TACHE5 + VEN_ACTUATORS_TACHE7 + VEN_SECURITY_TACHE8 + KEY_EVENT_LAUNCH_TACHE12 + COM_LAUNCH_TACHE_16 + DRV_SPI_POWERSUPPLY_UPDATE_TACHE_17 + DRV_USB_LAUNCH_TACHE15 + MONIT_FLASH_TACHE_13 + TREND_FLASH_TACHE_14


/* step 4 */
#define SCHED1_STEP_4_ACTIVABLE_TASKS  SYS_INTERPOLATION_TACHE4 + DRV_EVENT_TACHE9 + DISPLAY_FIFO_READ_TACHE10 + VEN_COMPUTE_TACHE6 + IT_WATCHDOG_TACHE1 + IHM_LAUNCH_TACHE11 + COM_LAUNCH_TACHE_16 + DRV_SPI_POWERSUPPLY_UPDATE_TACHE_17 + DRV_USB_LAUNCH_TACHE15 + MONIT_FLASH_TACHE_13 + TREND_FLASH_TACHE_14




#endif
/************************************************************************/
