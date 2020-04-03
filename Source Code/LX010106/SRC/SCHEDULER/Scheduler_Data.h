/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : Scheduler_Data.h                                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                              */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


/******************************************************************************/
/*  Pour utiliser le module scheduler, il faut inclure ce fichier dans l'applicatif */
/*  et il faut aussi copier dans le projet les fichiers suivants:                   */
/*   - scheduler_config.c                                                           */
/*   - scheduler_config.h                                                           */
/*                                                                                  */
/*  ATTENTION: IL NE FAUT MODIFIER QUE LE FICHIER SCHEDULER_CONFIG.H                */
/*                                                                                  */
/*  Le fichier scheduler_config.c genere automatiquement les tables a la compilation*/        
/************************************************************************************/

#ifndef SCHEDULER_DATA_H
#define SCHEDULER_DATA_H


/************************************************************************/
/*                       STRUCTURE DECLARATION     	               	*/
/************************************************************************/



/************************************************************************/
/*                   EXTERNAL CONSTANT DECLARATION                     	*/
/************************************************************************/
#define EMPTY 0
#define NO_FUNCTION 1

/*-----------------------------------------------------*/
/* Type definissant l'etat d'une tache                 */
/* REM: remplissage automatique par scheduler_config.c */
//typedef enum
//
// TASK_INACTIVE,
//  TASK_ACTIVE
//} Task_State_T;

/*-----------------------------------------------------*/
/* Structure définissant la table de taches            */
/* REM: remplissage automatique par scheduler_config.c */
typedef struct
{
   void (*task_main_func_ptr)(void);
} tab_ptr_function;

/*--------------------------------------------------------------------*/
/* Definition des etiquettes de travail                               */
/*--------------------------------------------------------------------*/
#define EMPTY 0

/* Definition des TASK_ID */
#define TASK_1             1
#define TASK_2             2
#define TASK_3             4
#define TASK_4             8
#define TASK_5            16
#define TASK_6            32
#define TASK_7            64
#define TASK_8 	   	  	 128
#define TASK_9     	     256
#define TASK_10    	     512
#define TASK_11   	    1024
#define TASK_12   	    2048
#define TASK_13   	    4096
#define TASK_14   	    8192
#define TASK_15  	   16384
#define TASK_16  	   32768
#define TASK_17      1*65536
#define TASK_18      2*65536
#define TASK_19      4*65536
#define TASK_20      8*65536
#define TASK_21     16*65536
#define TASK_22     32*65536
#define TASK_23     64*65536
#define TASK_24    128*65536
#define TASK_25    256*65536
#define TASK_26    512*65536
#define TASK_27   1024*65536
#define TASK_28   2048*65536
#define TASK_29   4096*65536
#define TASK_30   8192*65536



#endif

