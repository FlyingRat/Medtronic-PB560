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
#include "PUST_crc8.h"

/* locate boot code to specific section */
#include "locate_boot_code.h"


/******************************************************************************/
/*%C                       Functionnal description :                          */
//*%C Checks the CRC of the flash (const + code)                              */
/*%C                                                                          */
/*%I  Input Parameter :                                                       */
/*%I		Pointer to memory description structure                           */
/*%IO Input/Output :                                                          */
/*%IO		NONE                                                              */
/*%O  Output Parameter :                                                      */
/*%O 		Calculated CRC                                                    */
/******************************************************************************/
UBYTE PUST_CalcCrc8(T_FLASH_MEM_RANGE* PtMem)
{
    UBYTE crc = 0;
	UBYTE byte;
	UWORD32 address = 0;
	UWORD16 cnt = 0;

	if(PtMem == NULL)
		return 1;

	while(PtMem->ToBeCalc)
	{
		address = PtMem->MinAddress;

		while(address <= PtMem->MaxAddress)
		{
			cnt++; 
			if(cnt == 0)
			{	/* software watchdog refresh */
		   		_srvwdt_();
			}

			byte = *(UBYTE xhuge *) address;

			crc += byte;			

			address++;
		}
		PtMem++;
	}
	/* Once addition has been done : two's complement it ! */
	crc ^= 0xFF;
	crc += 1;
	crc &= 0xFF;

    return (crc);
}