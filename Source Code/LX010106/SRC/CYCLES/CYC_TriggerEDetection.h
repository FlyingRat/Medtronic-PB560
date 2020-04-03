/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CYC_TriggerEDetection.h                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                Detection of the exhalation trigger                			*/
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter :  NONE                                            		*/
/*%IO Input/Output :    NONE	                                              	*/
/*%O Output Parameter : UWORD16  TriggerEDetected      								*/
/******************************************************************************/

 

#ifndef CYC_TRIGGEREDETECTION_H
#define CYC_TRIGGEREDETECTION_H



/******************************************************************************/
/*                       EXTERNAL FUNCTION DECLARATION	                     */
/******************************************************************************/
extern UWORD16 DB_ComputeRead(e_DB_COMPUTE Id);
extern UWORD16 DB_CurrentRead(e_DB_ADJUST_CURRENT Id);
extern UWORD16 TIM_ReadCounterValue(e_TIM_TABLE_ID offset_table);
extern UWORD16 DB_ControlRead(e_DB_CONTROL Id);
#endif

