/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CYC_TiLimitsCompute.h */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C           It allows to compute the Timin and Ti max for the modes  */ 
/*%C				PSVTv VSIMV and PSIMV          */
/******************************************************************************/
/*%I Input Parameter :  NONE                                            */
/*%IO Input/Output :    NONE	                                              */
/*%O Output Parameter : Ti[TIMIN],Ti[TIMAX]                                   */
/******************************************************************************/

#ifndef CYC_TILIMITSCOMPUTE_H
#define CYC_TILIMITSCOMPUTE_H
/******************************************************************************/
/*                      CONSTANT DECLARATION  */
/******************************************************************************/
#define cVEN_3S 3000U
#define cVEN_300MS 300U
#define cDEFAULT_MESURE_R 13U
/******************************************************************************/
/*                       EXTERNAL FUNCTION DECLARATION  */
/******************************************************************************/

extern UWORD16 DB_CurrentRead(e_DB_ADJUST_CURRENT Id);
extern UWORD16 DB_ComputeRead(e_DB_COMPUTE Id);
extern void DB_CurrentWrite(e_DB_ADJUST_CURRENT Id,
                            UWORD16 Value);
#endif