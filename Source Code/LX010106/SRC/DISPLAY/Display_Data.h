/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : Display_data.h                                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Description fonctionnelle:		 	                        	      */
/*                                                                      	   */
/*%C Data declaration for ventilation cycles functions                        */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/
#define FIFO_DISPLAY_SIZE		 1000

#ifdef DECLARATION_DISPLAY_DATA

	#ifndef DISPLAY_DATA_H
	#define DISPLAY_DATA_H

UWORD16 DIS_FifoIdxRead ;
UWORD16 DIS_FifoIdxWrite;
UBYTE   DIS_FifoOverflow;
t_DisplayAccess DIS_FifoDisplay[FIFO_DISPLAY_SIZE];

	#endif
#else
	#ifndef DISPLAY_DATA_H
	#define DISPLAY_DATA_H

extern UWORD16 DIS_FifoIdxRead ;
extern UWORD16 DIS_FifoIdxWrite;
extern UBYTE   DIS_FifoOverflow;
extern t_DisplayAccess DIS_FifoDisplay[];

	#endif
#endif