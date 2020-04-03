/******************************************************************************/
/*                                                                            */
/* Project N  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CMP_PiSetPointPsimvMode.h                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C   Data declaration for CMP_PiSetPointPsimvMode.c                         */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef CMP_PI_SET_POINT_PSIMV_MODE_H
#define CMP_PI_SET_POINT_PSIMV_MODE_H

/* Access to the current write value */
extern void DB_CurrentWrite(e_DB_ADJUST_CURRENT Id,
                               UWORD16 Value);
/* Access to the current read value */
extern UWORD16 DB_CurrentRead(e_DB_ADJUST_CURRENT Id);
/* Access to the control read value */
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);

extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);

extern void DB_ComputeWrite(e_DB_COMPUTE Id, UWORD16 Value);
#endif
