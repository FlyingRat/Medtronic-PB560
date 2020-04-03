#include "typedef.h"																	   /*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : PUST.h                                                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C          Power Up Self Test routines header file    					  */
/******************************************************************************/

#include "typedef.h"

#ifndef PUST_h
#define PUST_h

/* Error Codes */
typedef enum {
	PUST_ERR_OK = 0,
	PUST_ERR_DATA_BUS,
	PUST_ERR_ADDRESS_BUS,
	PUST_ERR_DEVICE,
	PUST_ERR_CRC,
	PUST_ERR_FORCED_FAIL,
	PUST_ERR_EEPROM,
	PUST_ERR_REF_VOLTAGE,
    PUST_ERR_SOFT_VERSION,
	PUST_ERR_UNKNOWN,
	PUST_ERR_MAX
} e_PUST_ERROR_CODE;

/* Check requests */
typedef enum {
	PUST_RAM_CHECK_REQ = 0,
	PUST_FLASH_CHECK_REQ,
	PUST_EEPROM_CHECK_REQ,
	PUST_REF_VOLTAGE_CHECK_REQ,
    PUST_SOFT_VERSION_CHECK_REQ,
	PUST_MAX_REQ
} e_PUST_REQUEST;

/* Address range struct */
typedef struct 
{
	e_BOOL ToBeCalc;
	UWORD32 MinAddress;
	UWORD32 MaxAddress;
} T_PUST_MEM_RANGE;

#define MEM_END_CODE_AND_CONST (0x000DFFFE)

#define MEM_CRC_ADDRESS (0x000DFFFF)

extern void PUST_Checks(UBYTE _ForceFail, e_PUST_REQUEST _CheckRequest);

/* called from assembly */
extern e_PUST_ERROR_CODE PUST_Check_Ram_First_Part(void);
extern e_PUST_ERROR_CODE PUST_Check_Ram_Second_Part(void);

#endif // #ifndef PUST_h