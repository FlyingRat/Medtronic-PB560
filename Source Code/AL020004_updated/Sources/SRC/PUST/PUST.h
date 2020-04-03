/*----------------------------------------------------------------------------*/
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

#ifndef PUST_h
#define PUST_h

typedef enum {
	MEM_ERR_OK = 0,
	MEM_ERR_CRC,
	MEM_ERR_FORCED_FAIL,
	MEM_ERR_MAX
} e_MEM_ERROR_CODE;

/* Address range struct */
typedef struct 
{
	e_BOOL ToBeCalc;
	UWORD32 MinAddress;
	UWORD32 MaxAddress;
} T_PUST_MEM_RANGE;

#define MEM_END_CODE_AND_CONST (0x0000FFFE)

#define MEM_CRC_ADDRESS (0x0000FFFF)

extern void PUST_Checks(UBYTE _ForceFail);

#endif // #ifndef PUST_h