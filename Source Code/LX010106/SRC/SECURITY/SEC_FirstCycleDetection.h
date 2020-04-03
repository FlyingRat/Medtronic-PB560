/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : SEC_FirstCycleDetection.h                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   This function detects the first and the second cycle of respiration    */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef SEC_FIRST_CYCLE_DETECTION_H
#define SEC_FIRST_CYCLE_DETECTION_H

/******************************************************************************/
/*                EXTERNAL FUNCTION DECLARATION                               */
/******************************************************************************/

/* Access to the Control base (Read)                                          */
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);

/* Access to the Control base (Write)                                         */
extern void DB_ControlWrite(e_DB_CONTROL Id, UWORD16 Value);

#endif
