/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : PUST_ref_voltages.h                                                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                     Voltage Check routine                                */
/******************************************************************************/

#include "typedef.h"
#ifndef _TASKING
#include "LH_ST10F276.h"
#include <intrins.h>
#else
#include "regf276e.h"
#endif	
#include "io_declare.h"

#ifndef PUST_RefVoltages_h
#define PUST_RefVoltages_h

typedef enum {
	REF_VOLTAGE_ERR_OK = 0,
	REF_VOLTAGE_ERR_KO	
} e_REF_VOLTAGE_CODE;

extern e_REF_VOLTAGE_CODE RefVoltagesCheck(void);


#endif /* PUST_RefVoltages_h */