/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505													  */
/*																			  */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_TREND_PageRead.h											  */
/* 																			  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  */
/******************************************************************************/
/*%I Input Parameter :  NONE												  */
/*%IO Input/Output :    NONE												  */
/*%O Output Parameter : NONE												  */
/******************************************************************************/

#ifndef DRV_TREND_PAGEREAD
#define DRV_TREND_PAGEREAD
/******************************************************************************/
/*                  EXTERNAL FUNCTION DECLARATION      						  */
/******************************************************************************/

extern void DRV_NAND_AddressInput(UWORD16 Block_Number,
							UBYTE	Page_Number,
							UWORD16 Column_Number );

extern void DRV_NAND_CommandInput(UBYTE Flash_Command);


extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);

extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);



#endif