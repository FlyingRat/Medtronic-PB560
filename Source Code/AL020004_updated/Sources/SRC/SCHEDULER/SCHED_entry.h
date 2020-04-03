/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SCHED_entry.h                                                  */
/*													 						  							*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                 														*/
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef SCHED_ENTRY_H
#define SCHED_ENTRY_H


/*************************** DEFINITION DES TACHES ****************************/
/*                                                                        		*/
/* On définit les taches et les fonctions a appeler par une étiquette qui 		*/
/* contient un pointeur sur la tache ou la fonction en question.          		*/
/* Les noms des étiquettes sont repris par le fichier scheduler_config.c  		*/
/* et ne doivent donc pas etre modifies.                                  		*/
/*                                                                        		*/
/* Pour les étiquettes suivantes:                                         		*/
/*    TASK_1_MAIN_FUNC, TASK_2_MAIN_FUNC, TASK_3_MAIN_FUNC,...            		*/
/* Il n'est pas possible d'attribuer la pseudo-variable NO_FUNCTION       		*/
/*                                                                        		*/
/* Les pseudo_variables TASK_1, TASK_2, TASK_3,... contiennent le numéro  		*/
/* de priorité des taches correspondantes                                 		*/
/*                                                                        		*/
/* Les étiquettes TACHE1, TACHE2, TACHE3,... sont modifiables. Elles sont 		*/
/* utilisées pour l'affectation des pas du scheduler                      		*/
/*                                                                        		*/
/* Le nombre de tache est défini  dans l'étiquette NUMBER_OF_TASKS. C'est 		*/
/* cette etiquette qui fige la taille ROM de la table                     		*/
/*                                                                        		*/
/* REM: On peut définir plus de tache que le nombre inscrit dans          		*/
/*      NUMBER_OF_TASKS mais elles ne seront pas ajoutées dans la table   		*/
/*                                                                        		*/
/* REM: Le chien de garde est rafraîchi a chaque tour de séquenceur et a  		*/
/*      chaque réveil                                                     		*/
/*                                                                        		*/
/* REM: Une tache d'init est du type:  void MyFuncInit(void)              		*/
/*                                                                        		*/
/*      Une tache main est du type:    task_state_t MyFuncMain(void)      		*/
/*                                                                        		*/
/*        afin de renvoyer l'étiquette TASK_ACTIVE ou TASK_INACTIVE       		*/   
/*                                                                       		*/
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/* nombre de tache a sequencer MINI:1  MAXI:30                        			*/
/*----------------------------------------------------------------------------*/

#define NUMBER_OF_TASKS 11

/*----------------------------------------------------------------------------*/
/* definition des taches                                              			*/
/* pour chaque tache, on definit:                                     			*/
/* - un nom de tache                                                  			*/
/* - une fonction principale                                          			*/
/*                                                                    			*/
/* !!! LA FONCTION MAIN RENVOIE UN ARGUMENT DE TYPE task_state_t  !!! 			*/
/*                                                                    			*/
/* rem: la tache 1 est la plus prioritaire                           			*/
/*      la tache 30 est la moins prioritaire                          			*/
/*----------------------------------------------------------------------------*/
/****************************** tache 1 *******************************/
#define SAM_TACHE1 TASK_1
#define TASK_1_MAIN_FUNC SAM_Launch
/****************************** tache 2 ******************************/
#define RS_TACHE2 TASK_2  
#define TASK_2_MAIN_FUNC DRV_RS232_Launch
/****************************** tache 3 ******************************/
#define TIM_TACHE3 TASK_3
#define TASK_3_MAIN_FUNC TIM_Launch
/****************************** tache 4 ******************************/
#define SWITCH_TACHE4 TASK_4
#define TASK_4_MAIN_FUNC SWITCH_Launch
/****************************** tache 5 ******************************/
#define SYS_TACHE5 TASK_5
#define TASK_5_MAIN_FUNC SYS_Launch
/****************************** tache 6 ******************************/
#define CHARGER_TACHE6 TASK_6
#define TASK_6_MAIN_FUNC CHARGE_Launch
/****************************** tache 7 ******************************/
#define SEC_TACHE7 TASK_7
#define TASK_7_MAIN_FUNC SEC_Alarms
/****************************** tache 8 ******************************/
#define DRV_SPI_ST10_LAUNCH_TACHE8 TASK_8
#define TASK_8_MAIN_FUNC DRV_SPI_ST10_Launch
/****************************** tache 9 ******************************/
#define DRV_EEPROM_BAT_TACHE9 TASK_9
#define TASK_9_MAIN_FUNC DRV_EEPROM_BAT_Launch
/****************************** tache 10 *****************************/
#define FAN_DRIVING_LAUNCH_TACHE10 TASK_10
#define TASK_10_MAIN_FUNC FAN_Driving_Launch
/****************************** tache 11 *****************************/
#define WATCHDOG_TACHE11 TASK_11   
#define TASK_11_MAIN_FUNC Watchdog_Launch
/****************************** tache 12 *****************************/
#define TACHE12 TASK_12 
#define TASK_12_MAIN_FUNC NO_FUNCTION
/****************************** tache 13 *****************************/
#define TACHE13 TASK_13
#define TASK_13_MAIN_FUNC NO_FUNCTION
/****************************** tache 14 *****************************/
#define TACHE14 TASK_14
#define TASK_14_MAIN_FUNC NO_FUNCTION
/****************************** tache 15 *****************************/
#define TACHE15 TASK_15
#define TASK_15_MAIN_FUNC NO_FUNCTION
/****************************** tache 16 *****************************/
#define TACHE16 TASK_16
#define TASK_16_MAIN_FUNC NO_FUNCTION
/****************************** tache 17 *****************************/
#define TACHE17 TASK_17
#define TASK_17_MAIN_FUNC NO_FUNCTION
/****************************** tache 18 *****************************/
#define TACHE18 TASK_18
#define TASK_18_MAIN_FUNC NO_FUNCTION
/****************************** tache 19 *****************************/
#define TACHE19 TASK_19
#define TASK_19_MAIN_FUNC NO_FUNCTION
/****************************** tache 20 *****************************/
#define TACHE20 TASK_20
#define TASK_20_MAIN_FUNC NO_FUNCTION
/****************************** tache 21 *****************************/
#define TACHE21 TASK_21
#define TASK_21_MAIN_FUNC NO_FUNCTION
/****************************** tache 22 *****************************/
#define TACHE22 TASK_22
#define TASK_22_MAIN_FUNC NO_FUNCTION
/****************************** tache 23 *****************************/
#define TACHE23 TASK_23
#define TASK_23_MAIN_FUNC NO_FUNCTION
/****************************** tache 24 *****************************/
#define TACHE24 TASK_24
#define TASK_24_MAIN_FUNC NO_FUNCTION
/****************************** tache 25 *****************************/
#define TACHE25 TASK_25
#define TASK_25_MAIN_FUNC NO_FUNCTION
/****************************** tache 26 *****************************/
#define TACHE26 TASK_26
#define TASK_26_MAIN_FUNC NO_FUNCTION
/****************************** tache 27 *****************************/
#define TACHE27 TASK_27
#define TASK_27_MAIN_FUNC NO_FUNCTION
/****************************** tache 28 *****************************/
#define TACHE28 TASK_28
#define TASK_28_MAIN_FUNC NO_FUNCTION
/****************************** tache 29 *****************************/
#define TACHE29 TASK_29
#define TASK_29_MAIN_FUNC NO_FUNCTION
/****************************** tache 30 *****************************/
#define TACHE30 TASK_30
#define TASK_30_MAIN_FUNC NO_FUNCTION

/*********** DEFINITION DES PAS DU SEQUENCEUR PRINCIPAL ***********************/
/*                                                                        		*/
/* Un pas de séquenceur est défini par une étiquette dont la construction 		*/
/* est imposee: SCHED1_STEP[n]_ACTIVABLE_TASKS                            		*/
/*  [n] varie de 1 a 32 et représente le numéro du pas                    		*/
/* Ce schéma de construction est repris par le fichier scheduler_configu- 		*/
/* -ration.c et ne doit donc pas être modifie                             		*/
/*                                                                        		*/
/* Le nombre de pas est définit dans l'étiquette SCHED1_STEP_NUMBER. C'est		*/
/* cette étiquette qui fige la taille ROM de la table                     		*/
/*                                                                        		*/
/* REM: On peut définir plus de pas que le nombre inscrit dans            		*/
/*      SCHED1_STEP_NUMBER mais ils ne seront pas ajoutes dans la table  		*/
/*                                                                        		*/
/* REM: Un pas vide se définit avec la pseudo-variable EMPTY              		*/
/* rem: la tache 1 est la plus prioritaire                            			*/
/*      la tache 30 est la moins prioritaire                          			*/
/*                                                                        		*/
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/* nombre de pas du séquenceur principal  MINI:1  MAXI:32             			*/
/*----------------------------------------------------------------------------*/
#define SCHED1_STEP_NUMBER 8
   
/*----------------------------------------------------------------------------*/
/* définition de l'ordre de séquencement des taches: pour chaque pas  			*/
/* du séquenceur, on déclare le nom des taches a lancer               			*/
/*L'ordre d'execution des tâches n'est pas définit par la définition  			*/
/*suivante mais par la définition des tâches :								 			*/
/* 		la tache 1 est la plus prioritaire                           			*/
/*      la tache 30 est la moins prioritaire                          			*/
/*----------------------------------------------------------------------------*/
  
/* step 1 */
#define SCHED1_STEP_1_ACTIVABLE_TASKS \
			WATCHDOG_TACHE11 + SAM_TACHE1 + RS_TACHE2 + TIM_TACHE3 + SYS_TACHE5 + SWITCH_TACHE4 + CHARGER_TACHE6 + DRV_SPI_ST10_LAUNCH_TACHE8 + FAN_DRIVING_LAUNCH_TACHE10
/* step 2 */
#define SCHED1_STEP_2_ACTIVABLE_TASKS \
			SAM_TACHE1 + RS_TACHE2 + TIM_TACHE3 + SWITCH_TACHE4 + CHARGER_TACHE6 + DRV_SPI_ST10_LAUNCH_TACHE8 + SEC_TACHE7 + DRV_EEPROM_BAT_TACHE9 
/* step 3 */
#define SCHED1_STEP_3_ACTIVABLE_TASKS \
			SAM_TACHE1 + RS_TACHE2 + TIM_TACHE3 + SWITCH_TACHE4+ CHARGER_TACHE6 + DRV_SPI_ST10_LAUNCH_TACHE8 + FAN_DRIVING_LAUNCH_TACHE10
/* step 4 */
#define SCHED1_STEP_4_ACTIVABLE_TASKS \
			SAM_TACHE1 + RS_TACHE2 + TIM_TACHE3 + SWITCH_TACHE4 + CHARGER_TACHE6 + DRV_SPI_ST10_LAUNCH_TACHE8 + SEC_TACHE7 + DRV_EEPROM_BAT_TACHE9
/* step 5 */
#define SCHED1_STEP_5_ACTIVABLE_TASKS \
			SAM_TACHE1 + RS_TACHE2 + TIM_TACHE3 + SWITCH_TACHE4 + CHARGER_TACHE6 + DRV_SPI_ST10_LAUNCH_TACHE8 + FAN_DRIVING_LAUNCH_TACHE10
/* step 6 */
#define SCHED1_STEP_6_ACTIVABLE_TASKS \
			SAM_TACHE1 + RS_TACHE2 + TIM_TACHE3 + SWITCH_TACHE4 + CHARGER_TACHE6 + DRV_SPI_ST10_LAUNCH_TACHE8 + SEC_TACHE7 + DRV_EEPROM_BAT_TACHE9
/* step 7 */
#define SCHED1_STEP_7_ACTIVABLE_TASKS \
			SAM_TACHE1 + RS_TACHE2 + TIM_TACHE3 + SWITCH_TACHE4 + CHARGER_TACHE6 + DRV_SPI_ST10_LAUNCH_TACHE8 + FAN_DRIVING_LAUNCH_TACHE10
/* step 8 */
#define SCHED1_STEP_8_ACTIVABLE_TASKS \
			SAM_TACHE1 + RS_TACHE2 + TIM_TACHE3 + SWITCH_TACHE4 + CHARGER_TACHE6 + DRV_SPI_ST10_LAUNCH_TACHE8 + SEC_TACHE7 + DRV_EEPROM_BAT_TACHE9

#endif
/************************************************************************/
