/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CMP_CalculAutoAdaptInsp.h                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   Data declaration for VEN_CalculAutoAdaptInsp.c                         */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/


#ifndef CMP_CALCUL_AUTO_ADAPT_INSP_H
#define CMP_CALCUL_AUTO_ADAPT_INSP_H

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

/*Pressure min value                                                          */
#define cPRESSURE_MIN 20

/* Inspiratory rise pressure percentage step                                  */
#define cVEN_PER_CENT_RISE_PRESS_STEP 5L

/* Inspiratory rise pressure percentage min                                   */
#define cVEN_PER_CENT_RISE_PRESS_MIN -60L

/* Inspiratory rise pressure percentage max                                   */
#define cVEN_PER_CENT_RISE_PRESS_MAX 100L

/* Inspiratory rise pressure percentage default                               */
#define cVEN_PER_CENT_RISE_PRESS_DEF -30L

/* Inspiratory rise pressure percentage step                                  */
#define cVEN_PER_CENT_RISE_FLOW_STEP 5L

/* Inspiratory rise pressure percentage min                                   */
#define cVEN_PER_CENT_RISE_FLOW_MIN -60L

/* Inspiratory rise pressure percentage max                                   */
#define cVEN_PER_CENT_RISE_FLOW_MAX 100L


/******************************************************************************/
/*             EXTERNAL FUNCTION DECLARATION                    	            */
/******************************************************************************/

extern SWORD32 saturation(SWORD32 Value,
                          SWORD32 Min,
                          SWORD32 Max); 

extern UWORD16 DB_ComputeRead(e_DB_COMPUTE Id);

extern UWORD16 DB_CurrentRead(e_DB_ADJUST_CURRENT Id);

extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);

#endif
 