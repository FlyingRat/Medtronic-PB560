/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : structure.h                                                    */
/*													 						  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                     structure definition                                 */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


#ifndef STRUCTURE_H
#define STRUCTURE_H

/******************  use for "counters" *************************************/
typedef struct
{
	UWORD16 value;
	UWORD16 type;
}t_TIM_TAB_DEF_ELEMENT_16;

// Structure pour les timers superieur à 60s (et < 50 jours!!!)
typedef struct
{
	UWORD32 value;
	UWORD16 type;
}t_TIM_TAB_DEF_ELEMENT_32;

/*-----------------------------------------------------*/
/* Structure définissant la table de taches            */
/* REM: remplissage automatique par scheduler_config.c */
typedef struct
{
  rom far void (*task_main_func_ptr)(void);
} tab_ptr_function;

#endif
