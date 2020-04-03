/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : MAIN_NAND_Flash_Bad_Block_Read.h                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*											                                  */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE                                                  */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef MAIN_NAND_FLASH_BADBLOCKREAD_H
#define MAIN_NAND_FLASH_BADBLOCKREAD_H


extern void DRV_NAND_CommandInput(UBYTE Flash_Command);
extern void DRV_NAND_AddressInput(UWORD16 Block_Number,
							UBYTE	Page_Number,
							UWORD16 Column_Number );


#endif
