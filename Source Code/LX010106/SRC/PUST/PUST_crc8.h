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
/*%C          CRC 8 calculation routines                                      */
/******************************************************************************/

#include "typedef.h"
#ifndef _TASKING
#include "LH_ST10F276.h"
#include <intrins.h>
#else
#include "regf276e.h"
#endif	
#include "io_declare.h"

#ifndef PUST_crc8_h
#define PUST_crc8_h

/* typedef's */
typedef enum {
	FLASH_MEM_RANGE_0 = 0,
	FLASH_MEM_RANGE_1,
	FLASH_MEM_RANGE_MAX 
} e_FLASH_MEM_RANGE;

/* Address range struct */
typedef struct 
{
	e_BOOL ToBeCalc;
	UWORD32 MinAddress;
	UWORD32 MaxAddress;
} T_FLASH_MEM_RANGE;

UBYTE PUST_CalcCrc8(T_FLASH_MEM_RANGE* PtMem);


#endif /* PUST_crc8_h */