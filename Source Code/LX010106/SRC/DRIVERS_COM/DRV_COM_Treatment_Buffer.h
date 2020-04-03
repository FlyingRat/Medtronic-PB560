/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_COM_TreatmentBuffer.h  									  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                  */
/******************************************************************************/
/*%I Input Parameter :  NONE                                            */
/*%IO Input/Output :    NONE	                                              */
/*%O Output Parameter : NONE       */
/******************************************************************************/


#ifndef DRV_COM_TREATMENT_BUFFER_H
#define DRV_COM_TREATMENT_BUFFER_H

/******************************************************************************/
/*                     EXTERNAL FUNCTION DECLARATION                          */
/******************************************************************************/


extern UWORD16 xhuge * DRV_EVENT_TransPtrMemory(void);
extern void TIM_StartDecounter(e_TIM_TABLE_ID offset_table,
                               UWORD16 Value);
extern void DB_ControlWrite(e_DB_CONTROL Id,	UWORD16 Value);

#endif
