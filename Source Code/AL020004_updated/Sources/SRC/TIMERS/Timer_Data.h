/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : Timer_Data.h                                                    */
/*													 						  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                     Timer Global Data declaration                        */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                              */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifdef DECLARATION_TIMER_DATA
	#ifndef TIMER_DATA_H
	#define TIMER_DATA_H

t_TIM_TAB_DEF_ELEMENT_16  
			TIM_TableOfCntAndDecnt16[end_of_table_cnt_decnt_16];
t_TIM_TAB_DEF_ELEMENT_32  
			TIM_TableOfCntAndDecnt32[end_of_table_cnt_decnt_32];	
	
	#endif
#else
	#ifndef TIMER_DATA_H
	#define TIMER_DATA_H

extern t_TIM_TAB_DEF_ELEMENT_16  
			TIM_TableOfCntAndDecnt16[end_of_table_cnt_decnt_16];
extern t_TIM_TAB_DEF_ELEMENT_32  
			TIM_TableOfCntAndDecnt32[end_of_table_cnt_decnt_32]; 	
	
	#endif
#endif

