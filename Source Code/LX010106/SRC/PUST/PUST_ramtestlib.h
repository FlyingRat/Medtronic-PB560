/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : PUST.c                                                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C          RAM Test routines                                               */
/******************************************************************************/
#include "typedef.h"
#include "PUST.h"

#ifndef _TASKING
#include "LH_ST10F276.h"
#include <intrins.h>
#else
#include "regf276e.h"
#endif	

#ifndef PUST_RAMTESTLIB_H
#define PUST_RAMTESTLIB_H

#define _16BITDATABUS

#ifdef _16BITDATABUS
typedef UWORD16 datum;
#else
typedef UBYTE datum;
#endif

/* Address range struct */
typedef struct 
{
	e_BOOL ToBeCalc;
	UWORD32 MinAddress;
	UWORD32 MaxAddress;
} T_RAM_MEM_RANGE;

typedef enum {
	RAM_MEM_RANGE_0 = 0,
	RAM_MEM_RANGE_1,
	RAM_MEM_RANGE_MAX 
} e_RAM_MEM_RANGE;

typedef enum {
	RAM_ERR_OK = 0,
	RAM_ERR_ADDRESS_BUS_KO,
	RAM_ERR_DATABUS_BUS_KO	
} e_RAM_ERROR_CODE;

extern e_RAM_ERROR_CODE RamTest(T_RAM_MEM_RANGE* PtMem);
extern UWORD16 _error_code;
 
#endif /* PUST_RAMTESTLIB_H */