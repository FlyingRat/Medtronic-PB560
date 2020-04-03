/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DB_Current.h					   				                  		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C Functionnal description : 	datas declaration for adjust base				*/
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter : 			None			      	                       	*/
/*%IO Input/Output Parameter : 	None 	        			                  		*/
/*%O 	Output Parameter : 			None				            				  		*/
/******************************************************************************/
#ifndef CURRENT_H
#define CURRENT_H

#include "typedef.h"

/******************************************************************************/
/*                     ENUM DECLARATION				                         	*/
/******************************************************************************/
// Base CURRENT
//
// These enumerations cannot be changed without affecting PB VTS. 
// DO NOT delete an enumerator, replace it with CURRENT_USED_XX_U16
// instead. This allows PB VST to maintain backwards compatibility with
// older vent software.
//
typedef enum {
	ADJUST_VOL_CONTROL_U16=0,
	ADJUST_P_CONTROL_U16,
	ADJUST_PEEP_U16,
	ADJUST_P_SUPPORT_U16,
	ADJUST_RAMP_U16,
	ADJUST_CONTROL_R_U16,
	ADJUST_BACKUP_R_U16,
	ADJUST_HIGH_R_U16,
	HIGH_R_NO_SELECT_U16,
	ADJUST_TI_CONTROL_U16,
	ADJUST_INSP_SENS_U16,
	INSP_SENS_NO_SELECT_U16,
	ADJUST_EXH_SENS_U16,
	AUTO_EXH_SENS_SELECT_U16,
	ADJUST_APNEA_U16,
	AUTO_APNEA_SELECT_U16,
	ADJUST_LOW_PIP_U16,
	ADJUST_HIGH_PIP_U16,
	ADJUST_LOW_VTE_U16,
	LOW_VTE_NO_SELECT_U16,
	ADJUST_HIGH_VTE_U16,
	HIGH_VTE_NO_SELECT_U16,
	ADJUST_RISE_TIME_U16,
	ADJUST_LOW_VM_U16,
	LOW_VM_NO_SELECT_U16,
	ADJUST_HIGH_VM_U16,
	HIGH_VM_NO_SELECT_U16,
	ADJUST_LOW_VTI_U16,
	LOW_VTI_NO_SELECT_U16,
	ADJUST_HIGH_VTI_U16,
	HIGH_VTI_NO_SELECT_U16,
	ADJUST_TI_MIN_U16,
	TI_MIN_AUTO_SELECT_U16,
	ADJUST_TI_MAX_U16,
	TI_MAX_AUTO_SELECT_U16,
	PI_SET_POINT_U16,
	BACKUP_R_NO_SELECT_U16,
	P_SUPPORT_NO_SELECT_U16,
	CONTROL_R_NO_SELECT_U16,
	PEEP_NO_SELECT_U16,
	RISE_TIME_U16,
	ADJUST_HIGH_LEAK_U16,
	HIGH_LEAK_SELECT_U16,
	CURRENT_USED_43_U16,
	CURRENT_USED_44_U16,
	CURRENT_USED_45_U16,
  	ADJUST_TARGET_VT_U16,
  	TARGET_VT_SELECT_U16,
  	ADJUST_MAX_PRESSURE_U16,
	ADJUST_EXH_SENS_NEGATIVE_U16,
	AUTO_EXH_SENS_NEG_SELECT_U16,
	ADJUST_SIGH_SELECT_U16,
	ADJUST_SIGH_CPT_U16,
	ADJUST_SIGH_VT_COEF_U16,
	ADJUST_DISCONNECTION_DELAY_U16,
	DISCONNECTION_DELAY_AUTO_U16,
	end_of_adjust_table
} e_DB_ADJUST_CURRENT;

#ifdef DECLARATION_CURRENT_BASE
/******************************************************************************/
/*                     CONSTANT DECLARATION			                         	*/
/******************************************************************************/
/* Base Current array */
UWORD16 DB_Current[end_of_adjust_table];
#else
/******************************************************************************/
/*                     CONSTANT DECLARATION			                         	*/
/******************************************************************************/
/* Base Current array */
extern UWORD16 DB_Current[end_of_adjust_table];
#endif

#endif
