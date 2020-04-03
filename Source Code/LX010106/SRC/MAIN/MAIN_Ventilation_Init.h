/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : MAIN_Ventilation_Init.h                              		  		*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C          	Data declaration for ventilation init function                	*/
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


#ifndef MAIN_VENTILATION_INIT_H
#define MAIN_VENTILATION_INIT_H


/******************************************************************************/
/*             EXTERNAL FUNCTION DECLARATION                    	            */
/******************************************************************************/

extern UWORD16 DB_ConfigRead(e_DB_CONFIG Id);

extern void TIM_Temporize(UWORD32 useconde);

extern void ACT_BrakePower(UBYTE percentage);

extern void TIM_StartDecounter(e_TIM_TABLE_ID offset_table,
                               UWORD16 value);

extern void DB_ControlWrite(e_DB_CONTROL Id, UWORD16 Value);
extern UWORD16 DB_ConfigWrite(e_DB_CONFIG Id,UWORD16 Value);
#endif
