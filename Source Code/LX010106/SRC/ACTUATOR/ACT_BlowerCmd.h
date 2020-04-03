/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : ACT_BlowerCmd.h																*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C            									                          				*/
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

#ifndef ACT_BLOWERCMD_H
#define ACT_BLOWERCMD_H


/************************************************************************/
/*                   EXTERNAL FUNCTION DECLARATION	                     */
/************************************************************************/
/* Access to the control read value */
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
extern UWORD16 DB_ComputeRead(e_DB_COMPUTE Id);
extern UWORD16 DB_AlarmStatusRead(e_DB_ALARMS Id);
extern void ACT_BrakePower(UBYTE percentage);
extern SWORD32 saturation(SWORD32 Value,
                          SWORD32 Min,
                          SWORD32 Max); 

extern void DB_ComputeWrite(e_DB_COMPUTE Id,
                            UWORD16 Value);
#endif