/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_EVENT_Launch.c                                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                     */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef DRV_EVENT_LAUNCH_H
#define DRV_EVENT_LAUNCH_H


/******************************************************************************/
/*                  EXTERNAL FUNCTION DECLARATION										*/
/******************************************************************************/

extern UWORD16 DB_IhmAccessParaDataBase(UWORD16 *Value,
													  UWORD16 Id,
													  e_TYPE_OF_DB_TARGET DbType,
													  e_DATA_OPERATION DataOperation);
extern UWORD16 DRV_EVENT_Identification(void);
extern UBYTE DRV_EVENT_Erase_Sector(UBYTE secteur);
extern UBYTE DRV_EVENT_Program_Flash(UWORD16 data_prog,UWORD16 xhuge *adr_prog);
extern void DRV_EVENT_BlankCheck(void);

 

#endif
