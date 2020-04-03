/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_EVENT_RazPointerSector.h                                   */
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

#ifndef DRV_EVENT_RAZPOINTERSECTOR_H
#define DRV_EVENT_RAZPOINTERSECTOR_H

extern void DRV_EVENT_Erase_Flash(void);
extern UWORD16 DB_ConfigWrite(e_DB_CONFIG Id,
										UWORD16 Value);
/* Access to the config write value */
extern void DB_ControlWrite(e_DB_CONTROL Id, UWORD16 Value);

#endif