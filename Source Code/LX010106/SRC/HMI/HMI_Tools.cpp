/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_Tools.cpp											 						*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Classe utilitaire															 			  	*/
/*		                                                                   	 	*/
/******************************************************************************/


/******************************************************************************/
/*                           HEADER INCLUDE FILE		                        */
/******************************************************************************/

#include "HMI_Tools.hpp"

/******************************************************************************/
/*                           OTHER INCLUDE FILE		                	   		*/
/******************************************************************************/
#ifdef _BORLAND
#include <vcl.h>
#endif

#include "HMI_InterfaceCppC.hpp"
#include "HMI_DataBaseAccess.hpp"
#include "HMI_GlobalEventNode.hpp"
#include "HMI_Message.hpp"

extern "C"
{
#include "DB_Control.h"
}
/******************************************************************************/
/*                           CONSTANT DECLARATION		                	   	*/
/******************************************************************************/

/*%C Tailles des polices en largeur pour les */
/*%C caractères allant de 0x00 à 0xFF */
#define TOOLS_FONTS_MAX 5
#define TOOLS_CHARS_MAX 256

const UBYTE cGen2EuropFontPixelWidth[TOOLS_FONTS_MAX][TOOLS_CHARS_MAX] =
{

	{  /*%C Font ARIAL 9 */
    8, 8, 8, 8, 8, 8, 8, 8, 3, 8, 5, 9, 7, 5, 6, 3,
    9, 7, 8, 7, 8, 6, 9, 8, 7, 7, 5, 3, 6, 6, 6, 7,
    3, 3, 4, 7, 7,11, 8, 2, 4, 4, 5, 7, 3, 4, 3, 3,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 3, 8, 8, 7, 7, 7,
    8, 8, 8, 9, 9, 8, 7, 9, 9, 3, 6, 8, 7, 9, 9, 9,
    8, 9, 9, 8, 7, 9, 7,11, 7, 7, 7, 3, 3, 9, 5, 7,
    4, 7, 7, 6, 7, 7, 3, 7, 7, 3, 3, 6, 3,11, 7, 7,
    7, 7, 4, 7, 3, 7, 5, 9, 5, 5, 5, 4, 3, 4, 7, 8,      /*  => validé */
    8, 8, 7, 8, 8,11, 7, 9, 9, 7, 8,10, 9, 9, 9, 8,
    9, 7, 8, 9, 8, 9, 8,11,10, 8, 9,12, 9, 5, 8, 9,
    7, 3, 9, 7, 7, 6, 4, 7, 7, 9, 6, 7, 7, 6, 7, 9,
    5, 7, 7, 7, 6, 7, 5, 6, 6, 7, 4, 6, 9, 9, 8, 9,
    7, 6, 9, 7, 7, 8, 7, 9, 8, 7, 7, 7, 7, 3, 7, 7,
    7, 9, 7, 9, 7, 6, 9,11, 9, 7, 7, 9, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8
   },

   {  /*%C Font ARIAL 8 */
   7, 7, 7, 7, 7, 7, 7, 7, 2, 7, 7, 8, 6, 8, 6, 3,
   7, 6, 8, 7, 7, 6, 7, 6, 6, 7, 8, 3, 6, 6, 6, 6,
   3, 2, 4, 6, 6,10, 7, 2, 4, 4, 4, 6, 3, 4, 3, 3,
   6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 3, 3, 7, 6, 6, 6,
   11,8, 7, 7, 7, 6, 6, 8, 7, 2, 5, 7, 6, 8, 7, 8,
   6, 8, 7, 7, 6, 7, 8,11, 7, 8, 7, 3, 3, 3, 5, 6,
   4, 6, 6, 6, 6, 6, 4, 6, 6, 2, 2, 5, 2, 8, 6, 6,
   6, 6, 4, 6, 3, 6, 6,10, 6, 6, 6, 4, 2, 4, 6, 8,
   7, 7, 6, 8, 7,12, 6, 7, 7, 6, 7, 8, 7, 9, 7, 7,         /*  => validé */
   7, 7, 6, 8, 7, 7, 6,10, 9, 6, 7,10, 8, 5, 6, 8,
   5, 2, 8, 6, 6, 5, 4, 7, 6, 8, 5, 6, 6, 5, 6, 8,
   4, 6, 6, 6, 5, 6, 6, 6, 6, 6, 5, 6, 6, 8, 6, 8,
   6, 6, 8, 5, 5, 8, 6, 7, 7, 6, 6, 6, 6, 3, 6, 6,
   6, 7, 6, 8, 6, 6, 8,10, 8, 6, 6, 6, 8, 8, 8, 8,
   8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
   8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8
	},
   
   {  /*%C Font ARIAL FREE */
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
	3, 3, 4, 7, 7,11, 8, 2, 4, 4, 5, 7, 3, 4, 3, 3,
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 3, 3, 7, 7, 7, 7,
   12,7, 8, 9, 9, 8, 7, 9, 9, 3, 6, 8, 7, 9, 9, 9,
   8, 9, 9, 8, 7, 9, 7,11, 7, 7, 7, 3, 3, 3, 5, 7,
   4, 7, 7, 6, 7, 7, 3, 7, 7, 3, 3, 6, 3,11, 7, 7,
   7, 7, 4, 7, 3, 7, 5, 9, 5, 5, 5, 4, 3, 4, 7, 9,
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,        /*  => non utilisé */
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7
   },

   {   /*%C Font ARIAL BLACK 11 */
    8, 8,12,12, 8, 8,10, 9, 5,11, 8,12, 9, 8,10, 6,
   12,10,15, 6, 9, 8,11,10, 9,10, 8,12,12,11, 9,11,
    5, 5, 8,10,11,15,13,13, 6, 6, 8,10, 5, 5, 5, 4,
   10,10,10,10,10,10,10,10,10,10, 5,14,13,11,13,10,
   12,13,11,11,11,10, 9,12,12, 5,10,13, 9,13,12,12,
   10,12,12,10,11,12,13,17,13,13,10,13, 8,12, 6,12,
    8,10,10,10,10,10, 8,10,10, 5, 6,11, 5,15,10,10,
   10,10, 8, 9, 7,10, 9,14,10, 9, 8,10, 4,10,10,12,
   11,12, 9, 8,11,16, 9,12,12,13, 9,14,12,12,12,11,
   12,11,10,14,12,13,12,17,16,11,11,16, 7, 9,11,11,         /*  => validé */
   13,12,12,10,10,14, 9,14, 6,12,13,11,10,13,13,13,
   14,11,13,10,10,10,12,17,15,15, 6,12,12,12,11,12,
   13,13,12,14,12,12,12,11,10,11,11,12,14, 6,12,13,
   15,13,14,12,10,11,12, 9,12, 9,10,12,12, 6,15,10,
   13,12,16,15,15,15,15,13,12,15,15,15,15,16,12,14,
   14,15,15,16,15,15,15,15,15,16,11,15,15,15,15,15
   },

   {	 /*%C Font ARIAL BOLD 29 */
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,
   11,11,18,22,22,33,28, 9,13,13,15,23,11,13,11,11,
   22,22,22,22,22,22,22,22,22,22,13,13,23,23,23,24,
   38,27,28,28,28,26,24,30,28,11,22,28,24,33,28,30,
   26,30,28,26,23,28,26,35,26,25,24,13,11,13,23,22,
   13,22,24,22,24,22,13,24,24,11,11,22,11,35,24,24,
   24,24,15,22,13,24,21,31,22,21,20,15,11,15,23,29,
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27
   }
};

const UBYTE cGen2KoreanGreekFontPixelWidth[TOOLS_FONTS_MAX][TOOLS_CHARS_MAX] =
{

	{  /*%C Font ARIAL 9 */
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 7, 9, 6, 5, 7, 5, 6, 8, 5, 8,10, 6, 6,10,
    3, 3, 4, 7, 7,11, 8, 2, 4, 4, 5, 7, 3, 4, 3, 3,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 3, 3, 7, 7, 7, 7,
   12, 7, 8, 9, 9, 8, 7, 9, 9, 3, 6, 8, 7, 9, 9, 9,
    8, 9, 9, 8, 7, 9, 7,11, 7, 7, 7, 3, 3, 3, 5, 7,
    4, 7, 7, 6, 7, 7, 3, 7, 7, 3, 3, 6, 3,11, 7, 7,
    7, 7, 4, 7, 3, 7, 5, 9, 5, 5, 5, 4, 3, 4, 7,11,
   12,12,11,11,11,12,10,12,12,11,10,10,12,11,10,10,        /*  => validé */
   11,11,11,12,10,11,10,10,10,11,10,11,10,12,11,11,
   11,11,12,12,12,12,11,12, 3,11,12,12, 7,11, 9,11,
    5, 7,11,11,11,11,11,11,11,11,13, 9, 8, 8, 8, 9,
   11, 8, 8,10, 9, 9, 9, 8,12, 8, 7, 8,10,10,13, 9,
    9, 9, 8, 9,10, 9, 9,12,12,12,12,11,11, 9,12,10,
   10,12,12, 8,12,12,11, 9,12,11, 9, 8,10, 9, 7, 6,
    6, 3, 7, 6, 6, 7, 6, 6, 7, 2, 6, 6, 6, 6, 6, 6,
   },

   {  /*%C Font ARIAL 8 */
   7, 7, 7, 7, 7, 7, 7, 7, 2, 7, 7, 8, 6, 8, 6, 3,
   7, 6, 8, 7, 7, 6, 7, 6, 6, 7, 8, 3, 6, 6, 6, 6,
   3, 2, 4, 6, 6,10, 7, 2, 4, 4, 4, 6, 3, 4, 3, 3,
   6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 3, 3, 7, 6, 6, 6,
   11,8, 7, 7, 7, 6, 6, 8, 7, 2, 5, 7, 6, 8, 7, 8,
   6, 8, 7, 7, 6, 7, 8,11, 7, 8, 7, 3, 3, 3, 5, 6,
   4, 6, 6, 6, 6, 6, 4, 6, 6, 2, 2, 5, 2, 8, 6, 6,
   6, 6, 4, 6, 3, 6, 6,10, 6, 6, 6, 4, 2, 4, 6, 8,
   7, 7, 6, 8, 7,12, 6, 7, 7, 6, 7, 8, 7, 9, 7, 7,         /*  => validé */
   7, 7, 6, 8, 7, 7, 6,10, 9, 6, 7,10, 8, 5, 6, 8,
   5, 2, 8, 6, 6, 5, 4, 7, 6, 8, 5, 6, 6, 5, 6, 8,
   4, 6, 6, 6, 5, 6, 6, 6, 6, 6, 5, 6, 6, 8, 6, 8,
   6, 6, 8, 5, 5, 8, 6, 7, 7, 6, 6, 6, 6, 3, 6, 6,
   6, 7, 6, 8, 6, 6, 8,10, 8, 6, 6, 6, 8, 8, 8, 8,
   8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
   8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8
	},
   
   {  /*%C Font ARIAL FREE */
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
	3, 3, 4, 7, 7,11, 8, 2, 4, 4, 5, 7, 3, 4, 3, 3,
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 3, 3, 7, 7, 7, 7,
   12,7, 8, 9, 9, 8, 7, 9, 9, 3, 6, 8, 7, 9, 9, 9,
   8, 9, 9, 8, 7, 9, 7,11, 7, 7, 7, 3, 3, 3, 5, 7,
   4, 7, 7, 6, 7, 7, 3, 7, 7, 3, 3, 6, 3,11, 7, 7,
   7, 7, 4, 7, 3, 7, 5, 9, 5, 5, 5, 4, 3, 4, 7, 9,         /*  => non utilisé */
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7
   },

   {   /*%C Font ARIAL BLACK 11 */
    8, 8,12,12, 8, 8,10, 9, 5,11, 8,12, 9, 8,10, 6,
   12,10,15, 6, 9, 8,11,10, 9,10, 8,12,12,11, 9,11,
    5, 5, 8,10,11,15,13,13, 6, 6, 8,10, 5, 5, 5, 4,
   10,10,10,10,10,10,10,10,10,10, 5,14,13,11,13,10,
   12,13,11,11,11,10, 9,12,12, 5,10,13, 9,13,12,12,
   10,12,12,10,11,12,13,17,13,13,10,13, 8,12, 6,12,
    8,10,10,10,10,10, 8,10,10, 5, 6,11, 5,15,10,10,
   10,10, 8, 9, 7,10, 9,14,10, 9, 8,10, 4,10,10,12,
   11,12, 9, 8,11,16, 9,12,12,13, 9,14,12,12,12,11,
   12,11,10,14,12,13,12,17,16,11,11,16, 7, 9,11,11,         /*  => validé */
   13,12,12,10,10,14, 9,14, 6,12,13,11,10,13,13,13,
   14,11,13,10,10,10,12,17,15,15, 6,12,12,12,11,12,
   13,13,12,14,12,12,12,11,10,11,11,12,14, 6,12,13,
   15,13,14,12,10,11,12, 9,12, 9,10,12,12, 6,15,10,
   13,12,16,15,15,15,15,13,12,15,15,15,15,16,12,14,
   14,15,15,16,15,15,15,15,15,16,11,15,15,15,15,15
   },

   {	 /*%C Font ARIAL BOLD 29 */
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,
   11,11,18,22,22,33,28, 9,13,13,15,23,11,13,11,11,
   22,22,22,22,22,22,22,22,22,22,13,13,23,23,23,24,
   38,27,28,28,28,26,24,30,28,11,22,28,24,33,28,30,
   26,30,28,26,23,28,26,35,26,25,24,13,11,13,23,22,
   13,22,24,22,24,22,13,24,24,11,11,22,11,35,24,24,
   24,24,15,22,13,24,21,31,22,21,20,15,11,15,23,29,
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27
   }
};

const UBYTE cGen2JapaneseFontPixelWidth[TOOLS_FONTS_MAX][TOOLS_CHARS_MAX] =
{

	{  /*%C Font ARIAL 9 */
   12,13,13,13,12,13,13,13,13,13, 5,13,13, 5,13,13,
   13,13,13, 7, 7, 6, 7, 6, 7, 6, 5,13,13, 5,11,10,
    3, 3, 4, 7, 7,11, 8, 2, 4, 4, 5, 7, 3, 4, 3, 3,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 3, 3, 7, 7, 7, 7,
   12,7, 8, 9, 9, 8, 7, 9, 9, 3, 6, 8, 7, 9, 9, 9,
    8, 9, 9, 8, 7, 9, 7,11, 7, 7, 7,13, 3,13,13,13,
    4, 7, 7, 6, 7, 7, 3, 7, 7, 3, 3, 6, 3,11, 7, 7,
    7, 7, 4, 7, 3, 7, 5, 9, 5, 5, 5, 4, 3, 4, 7,10,       /*  => validé */
   13, 9,10,11,13,13,12,12,12,12,11,13,12,11,13,11,
   11,13,11,10,12, 9,11,11, 9,11,10,12,13,12,13,10,
   11,13,12,12,12,12,12,10,13,10,12,13, 7, 8,13,13,
    5, 7,13,11,12,12,12,12,12,10,12,10,11, 9,11, 9,
   13,10,13,11,11,12,13,13,13,13,13,13,13,13,13,13,
   13,13,14,13,13,13,13,10,13,13,13,12,13,13,13,13,
   13,12,13,13,13,12,13,13,13,13,13,13,13,13,13,13,
   13,13,13,10,13,13,13,13,13,13,13,13,13,13,13,13
   },

   {  /*%C Font ARIAL 8 */
   7, 7, 7, 7, 7, 7, 7, 7, 2, 7, 7, 8, 6, 8, 6, 3,
   7, 6, 8, 7, 7, 6, 7, 6, 6, 7, 8, 3, 6, 6, 6, 6,
   3, 2, 4, 6, 6,10, 7, 2, 4, 4, 4, 6, 3, 4, 3, 3,
   6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 3, 3, 7, 6, 6, 6,
   11,8, 7, 7, 7, 6, 6, 8, 7, 2, 5, 7, 6, 8, 7, 8,
   6, 8, 7, 7, 6, 7, 8,11, 7, 8, 7, 3, 3, 3, 5, 6,
   4, 6, 6, 6, 6, 6, 4, 6, 6, 2, 2, 5, 2, 8, 6, 6,
   6, 6, 4, 6, 3, 6, 6,10, 6, 6, 6, 4, 2, 4, 6, 8,
   7, 7, 6, 8, 7,12, 6, 7, 7, 6, 7, 8, 7, 9, 7, 7,         /*  => validé */
   7, 7, 6, 8, 7, 7, 6,10, 9, 6, 7,10, 8, 5, 6, 8,
   5, 2, 8, 6, 6, 5, 4, 7, 6, 8, 5, 6, 6, 5, 6, 8,
   4, 6, 6, 6, 5, 6, 6, 6, 6, 6, 5, 6, 6, 8, 6, 8,
   6, 6, 8, 5, 5, 8, 6, 7, 7, 6, 6, 6, 6, 3, 6, 6,
   6, 7, 6, 8, 6, 6, 8,10, 8, 6, 6, 6, 8, 8, 8, 8,
   8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
   8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8
	},
   
   {  /*%C Font ARIAL FREE */
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
	3, 3, 4, 7, 7,11, 8, 2, 4, 4, 5, 7, 3, 4, 3, 3,
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 3, 3, 7, 7, 7, 7,
   12,7, 8, 9, 9, 8, 7, 9, 9, 3, 6, 8, 7, 9, 9, 9,
   8, 9, 9, 8, 7, 9, 7,11, 7, 7, 7, 3, 3, 3, 5, 7,
   4, 7, 7, 6, 7, 7, 3, 7, 7, 3, 3, 6, 3,11, 7, 7,
   7, 7, 4, 7, 3, 7, 5, 9, 5, 5, 5, 4, 3, 4, 7, 9,
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,         /*  => non utilisé */
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7
   },

   {   /*%C Font ARIAL BLACK 11 */
    8, 8,12,12, 8, 8,10, 9, 5,11, 8,12, 9, 8,10, 6,
   12,10,15, 6, 9, 8,11,10, 9,10, 8,12,12,11, 9,11,
    5, 5, 8,10,11,15,13,13, 6, 6, 8,10, 5, 5, 5, 4,
   10,10,10,10,10,10,10,10,10,10, 5,14,13,11,13,10,
   12,13,11,11,11,10, 9,12,12, 5,10,13, 9,13,12,12,
   10,12,12,10,11,12,13,17,13,13,10,13, 8,12, 6,12,
    8,10,10,10,10,10, 8,10,10, 5, 6,11, 5,15,10,10,
   10,10, 8, 9, 7,10, 9,14,10, 9, 8,10, 4,10,10,12,
   11,12, 9, 8,11,16, 9,12,12,13, 9,14,12,12,12,11,
   12,11,10,14,12,13,12,17,16,11,11,16, 7, 9,11,11,         /*  => validé */
   13,12,12,10,10,14, 9,14, 6,12,13,11,10,13,13,13,
   14,11,13,10,10,10,12,17,15,15, 6,12,12,12,11,12,
   13,13,12,14,12,12,12,11,10,11,11,12,14, 6,12,13,
   15,13,14,12,10,11,12, 9,12, 9,10,12,12, 6,15,10,
   13,12,16,15,15,15,15,13,12,15,15,15,15,16,12,14,
   14,15,15,16,15,15,15,15,15,16,11,15,15,15,15,15
   },

   {	 /*%C Font ARIAL BOLD 29 */
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,
   11,11,18,22,22,33,28, 9,13,13,15,23,11,13,11,11,
   22,22,22,22,22,22,22,22,22,22,13,13,23,23,23,24,
   38,27,28,28,28,26,24,30,28,11,22,28,24,33,28,30,
   26,30,28,26,23,28,26,35,26,25,24,13,11,13,23,22,
   13,22,24,22,24,22,13,24,24,11,11,22,11,35,24,24,
   24,24,15,22,13,24,21,31,22,21,20,15,11,15,23,29,
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27
   }
};

const UBYTE cGen2ChineseFontPixelWidth[TOOLS_FONTS_MAX][TOOLS_CHARS_MAX] =
{

	{  /*%C Font ARIAL 9 */
   13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
   13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
    3,12, 5,13,13,13,13,13, 5, 5,13, 9,13, 4, 4, 4,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 3,13,13,14, 9, 8,
   13, 7, 7, 7,13, 8, 7,13,9, 3,13,13,13,11,13,  9,
    8,13, 9, 8, 7, 9, 7,11,14,11,13,11,12,13,13,13,
   12, 7, 7, 6, 7, 7, 3, 7, 7, 3, 3, 6, 3,11, 7, 7,
    7, 7, 4, 7, 3, 7, 5, 9, 5, 5, 5,13, 3,12,13,13,       /*  => validé */
   13,13,13,11,13,13,13,13,13,13,13,13,13,13,13,13,
   13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
   13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
   13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
   13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
   13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
   13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
   13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13
   },

   {  /*%C Font ARIAL 8 */
   7, 7, 7, 7, 7, 7, 7, 7, 2, 7, 7, 8, 6, 8, 6, 3,
   7, 6, 8, 7, 7, 6, 7, 6, 6, 7, 8, 3, 6, 6, 6, 6,
   3, 2, 4, 6, 6,10, 7, 2, 4, 4, 4, 6, 3, 4, 3, 3,
   6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 3, 3, 7, 6, 6, 6,
   11,8, 7, 7, 7, 6, 6, 8, 7, 2, 5, 7, 6, 8, 7, 8,
   6, 8, 7, 7, 6, 7, 8,11, 7, 8, 7, 3, 3, 3, 5, 6,
   4, 6, 6, 6, 6, 6, 4, 6, 6, 2, 2, 5, 2, 8, 6, 6,
   6, 6, 4, 6, 3, 6, 6,10, 6, 6, 6, 4, 2, 4, 6, 8,
   7, 7, 6, 8, 7,12, 6, 7, 7, 6, 7, 8, 7, 9, 7, 7,         /*  => validé */
   7, 7, 6, 8, 7, 7, 6,10, 9, 6, 7,10, 8, 5, 6, 8,
   5, 2, 8, 6, 6, 5, 4, 7, 6, 8, 5, 6, 6, 5, 6, 8,
   4, 6, 6, 6, 5, 6, 6, 6, 6, 6, 5, 6, 6, 8, 6, 8,
   6, 6, 8, 5, 5, 8, 6, 7, 7, 6, 6, 6, 6, 3, 6, 6,
   6, 7, 6, 8, 6, 6, 8,10, 8, 6, 6, 6, 8, 8, 8, 8,
   8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
   8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8
	},

   {  /*%C Font ARIAL FREE */
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
	3, 3, 4, 7, 7,11, 8, 2, 4, 4, 5, 7, 3, 4, 3, 3,
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 3, 3, 7, 7, 7, 7,
   12,7, 8, 9, 9, 8, 7, 9, 9, 3, 6, 8, 7, 9, 9, 9,
   8, 9, 9, 8, 7, 9, 7,11, 7, 7, 7, 3, 3, 3, 5, 7,
   4, 7, 7, 6, 7, 7, 3, 7, 7, 3, 3, 6, 3,11, 7, 7,
   7, 7, 4, 7, 3, 7, 5, 9, 5, 5, 5, 4, 3, 4, 7, 9,          /*  => non utilisé */
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
   7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7
   },

   {   /*%C Font ARIAL BLACK 11 */
    8, 8,12,12, 8, 8,10, 9, 5,11, 8,12, 9, 8,10, 6,
   12,10,15, 6, 9, 8,11,10, 9,10, 8,12,12,11, 9,11,
    5, 5, 8,10,11,15,13,13, 6, 6, 8,10, 5, 5, 5, 4,
   10,10,10,10,10,10,10,10,10,10, 5,14,13,11,13,10,
   12,13,11,11,11,10, 9,12,12, 5,10,13, 9,13,12,12,
   10,12,12,10,11,12,13,17,13,13,10,13, 8,12, 6,12,
    8,10,10,10,10,10, 8,10,10, 5, 6,11, 5,15,10,10,
   10,10, 8, 9, 7,10, 9,14,10, 9, 8,10, 4,10,10,12,
   11,12, 9, 8,11,16, 9,12,12,13, 9,14,12,12,12,11,
   12,11,10,14,12,13,12,17,16,11,11,16, 7, 9,11,11,         /*  => validé */
   13,12,12,10,10,14, 9,14, 6,12,13,11,10,13,13,13,
   14,11,13,10,10,10,12,17,15,15, 6,12,12,12,11,12,
   13,13,12,14,12,12,12,11,10,11,11,12,14, 6,12,13,
   15,13,14,12,10,11,12, 9,12, 9,10,12,12, 6,15,10,
   13,12,16,15,15,15,15,13,12,15,15,15,15,16,12,14,
   14,15,15,16,15,15,15,15,15,16,11,15,15,15,15,15
   },

   {	 /*%C Font ARIAL BOLD 29 */
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,
   11,11,18,22,22,33,28, 9,13,13,15,23,11,13,11,11,
   22,22,22,22,22,22,22,22,22,22,13,13,23,23,23,24,
   38,27,28,28,28,26,24,30,28,11,22,28,24,33,28,30,
   26,30,28,26,23,28,26,35,26,25,24,13,11,13,23,22,
   13,22,24,22,24,22,13,24,24,11,11,22,11,35,24,24,
   24,24,15,22,13,24,21,31,22,21,20,15,11,15,23,29,
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,
   27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27
   }
};

extern UWORD16 cInfoNodeDisplayTable[NB_NODE];

UBYTE* FontWidthConfig = (UBYTE *) cGen2EuropFontPixelWidth;

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
												 
/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
void Tools::SetFontConfigForLang(UWORD16 _Lang)
{
   switch(_Lang)
   {
      default:
      case HMI_LANG_FRENCH :
      case HMI_LANG_ENGLISH :
      case HMI_LANG_SWEDISH :
      case HMI_LANG_NORWISH :
      case HMI_LANG_DANISH :
      case HMI_LANG_FINNISH :
      case HMI_LANG_ITALIAN :
      case HMI_LANG_SPANISH :
      case HMI_LANG_TURKISH :
      case HMI_LANG_POLISH :
      case HMI_LANG_DUTCH :
      case HMI_LANG_GERMAN :
      case HMI_LANG_RUSSIAN :
      case HMI_LANG_PORTUGUESE :
         FontWidthConfig =  (UBYTE*) cGen2EuropFontPixelWidth;
      break;
      case HMI_LANG_GREEK :
      case HMI_LANG_KOREAN :
         FontWidthConfig =  (UBYTE*) cGen2KoreanGreekFontPixelWidth;
      break;
      case HMI_LANG_JAPANESE :
         FontWidthConfig =  (UBYTE*) cGen2JapaneseFontPixelWidth;
      break;
      case HMI_LANG_CHINESE :
         FontWidthConfig =  (UBYTE*) cGen2ChineseFontPixelWidth;
      break;
   }
}
/*----------------------------------------------------------------------------*/
UBYTE* Tools::GetFontWidthConfig()
{
   if(FontWidthConfig == NULL)
      return((UBYTE*) cGen2EuropFontPixelWidth);
   else
      return(FontWidthConfig);
}
/******************************************************************************/
/*                           METHODES                									*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Contrôle la validité du contenu de la table de configuration des noeuds  */
/*%I Input Parameter : 																			*/
/*%I		_FirstNode : premier noeud de la table                               */
/*%I		_LastNode : dernier noeud de la table                                */
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		TRUE si le contenu est OK, FALSE sinon  										*/
/******************************************************************************/
e_BOOL Tools::CheckInfoNodeTable(UWORD16 _FirstNode, UWORD16 _LastNode)
{
   UWORD16 i,j,Order,LoopCount,countVisible ;
   UWORD16 Id, FirstIndex, LastIndex;

   /*%C récupération de l'index dans la table cInfoNode */
   FirstIndex = Tools::GetInfoNodeIndex(_FirstNode);
   LastIndex = Tools::GetInfoNodeIndex(_LastNode);
   if((FirstIndex == 10999) || (LastIndex == 10999))
      return FALSE;

   /*%C Pour chaque mode */
   for(i=0;i<cMAX_MODE;i++)
   {
      countVisible = 0;

      /*%C Pour chaque objet de la table cInfoNode */
      for(j=0;j<cINFO_NODE_NB;j++)
      {
         if((j >= FirstIndex) && (j <= LastIndex))
         {
            /*%C Un objet non visible doit avoir un Ordre égal à 0 */
            if((!cInfoNode[j].InfoByMode[i].Visible) &&
            (cInfoNode[j].InfoByMode[i].Order))
               return FALSE;
            if(cInfoNode[j].InfoByMode[i].Visible)
               countVisible++;
         }
      }

      /*%C Il y a forcément un objet d'ordre 0 */
      Order = 0;
      Id = GetIdFromOrder(Order,(e_MODE_TYPES) i, _FirstNode, _LastNode);
      if (Id == 10999)
            return (FALSE);

      /*%C Consécutivité des attributs "Order" pour chaque objet visible */
      LoopCount = 1;
      Order = 1;
      while (LoopCount != countVisible)
      {
         Id = GetIdFromOrder(Order,(e_MODE_TYPES) i, _FirstNode, _LastNode);
         if (Id == 10999)
            return (FALSE);
         LoopCount++;
         Order++;
      }
   }
   return (TRUE);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Determine a quelle fenetre appartient un noeudlink de l'Objet				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		IdNode : numero du noeud															*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		Numero de la fenetre			  														*/
/******************************************************************************/
UWORD16 Tools::GetNumFrame(UWORD16 _IdNode)
{
   return (cInfoNodeDisplayTable[_IdNode] & 0xFE);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Determine si le noeud peut etre locké												*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		IdNode : numero du noeud															*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		TRUE si le noeud peut etre locker												*/
/******************************************************************************/
e_BOOL Tools::IsLockWhithLock(UWORD16 _NodeId)
{
   UWORD16 i = 0;
   while(cInfoNode[i].NodeId != 10999)
	{
      if(cInfoNode[i].NodeId == _NodeId)
      {
			return (e_BOOL)cInfoNode[i].Lock;
      }
      i++;
   }
   return FALSE;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Determine si le noeud et present en fonction d'un mode							*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		IdNode : numero du noeud															*/
/*%I		Mode   : mode de ventilation														*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		TRUE si le noeud est present														*/
/******************************************************************************/
e_BOOL Tools::IsVisibleWhithMode(UWORD16 _NodeId, e_MODE_TYPES _Mode)
{
	UWORD16 i = 0;
	while(cInfoNode[i].NodeId != 10999)
   {
		if(cInfoNode[i].NodeId == _NodeId)
      {
			return (e_BOOL)cInfoNode[i].InfoByMode[_Mode].Visible;
		}

		i++;
    }
	return FALSE;
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Determine le rang d'affichage d'un noeud pour un mode donné  				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		_IdNode : numero du noeud															*/
/*%I		_Mode   : mode de ventilation														*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		TRUE si le noeud est present														*/
/******************************************************************************/
UWORD16 Tools::GetOrderWithMode( UWORD16 _NodeId, e_MODE_TYPES _Mode)
{
	UWORD16 i = 0;
	while(cInfoNode[i].NodeId != 10999)
   {
		if(cInfoNode[i].NodeId == _NodeId)
      {
			return (e_BOOL)cInfoNode[i].InfoByMode[_Mode].Order;
		}

		i++;
    }
	return (0);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Retourne l'index de la table cInfoNode à partir du numéro de noeud       */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		_NodeId : Noeud pour lequel on doit rencoyer l'index                 */
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		Numéro de noeud            														*/
/******************************************************************************/
UWORD16 Tools::GetInfoNodeIndex(UWORD16 _NodeId)
{
	UWORD16 i = 0;
	while(cInfoNode[i].NodeId != 10999)
   {
		if(cInfoNode[i].NodeId == _NodeId)
			return i;
		i++;
    }
	return (10999);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Determine l'id d'un noeud à partir de son rang d'affichage, le noeud     */
/*%C se situant entre FirstNode et LastNode                         				*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		_Order : Ordre d'affichage															*/
/*%I		_Mode   : mode de ventilation														*/
/*%I		_FirstNode   : premier noeud à partir duquel commencer la recherche  */
/*%I		_LastNode   : dernier noeud à partir duquel arrêter la recherche  	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		Numéro de noeud            														*/
/******************************************************************************/
UWORD16 Tools::GetIdFromOrder(UWORD16 _Order,
                              e_MODE_TYPES _Mode,
                              UWORD16 _FirstNode,
                              UWORD16 _LastNode)
{
	UWORD16 i = 0;
	while(cInfoNode[i].NodeId != 10999)
   {
		if((cInfoNode[i].InfoByMode[_Mode].Order == _Order) &&
        (cInfoNode[i].NodeId >= _FirstNode) &&
        (cInfoNode[i].NodeId <= _LastNode))
      {
			return (e_BOOL)cInfoNode[i].NodeId;
	   }
		i++;
    }
	return (10999);
}
/************************************************************************/
/*%C Description   : Permute les configurations d'affichage de deux     */
/*%C objets pour un mode donné                                          */
/*%C Parametres en entree : 		                                       */
/*    - _First, _Second : Objets dont les configurations doivent être   */
/*                       permutées                                      */
/*		- _Mode : mode pour lequel la configuration doit être permutée    */
/* Parametres en sortie : Néant                                         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Tools::SwitchDisplayConfigForOneMode(   UWORD16 _First,
                                             UWORD16 _Second,
                                             e_MODE_TYPES _Mode)
{

   tInfoNodeForMode InfoBackUp;
   UWORD16 i = 0;
   e_BOOL first_found = FALSE;
   e_BOOL second_found = FALSE;
   UWORD16 first_i = 0;
   UWORD16 second_i = 0;

	while(cInfoNode[i].NodeId != 10999)
   {
      /*%C premier noeud trouvé, sauvegarde */
		if(cInfoNode[i].NodeId == _First)
      {
         InfoBackUp.Visible = cInfoNode[i].InfoByMode[_Mode].Visible;
         InfoBackUp.Order = cInfoNode[i].InfoByMode[_Mode].Order;
         first_i = i;
         first_found = TRUE;
      }

      /*%C premier noeud trouvé */
		if(cInfoNode[i].NodeId == _Second)
      {
         second_i = i;
         second_found = TRUE;
      }

      /*%C Les deux noeuds ont été trouvés, on permute les configs*/
      if((first_found) && (second_found))
      {
         /*%C premier <- second  */
         cInfoNode[first_i].InfoByMode[_Mode].Visible = cInfoNode[second_i].InfoByMode[_Mode].Visible;
         cInfoNode[first_i].InfoByMode[_Mode].Order = cInfoNode[second_i].InfoByMode[_Mode].Order;

         /*%C second <- premier, via backup */
         cInfoNode[second_i].InfoByMode[_Mode].Visible = InfoBackUp.Visible;
         cInfoNode[second_i].InfoByMode[_Mode].Order = InfoBackUp.Order;

         break;
      }
		i++;
   }      
}
/************************************************************************/
/*%C Description   : Permute les configuration d'affichage de deux      */
/*%C objets pour tous les modes                                         */
/*%C Parametres en entree : 		                                       */
/*    - _First, _Second : Objets dont les configuration doivent être    */
/*                       permutées                                      */
/* Parametres en sortie : Néant                                         */
/* Contrainte                                                           */
/*        Pré-conditions  : Néant                                       */
/*        Post-condition  : Néant                                       */
/*        Exceptions      : Néant                                       */
/************************************************************************/
void Tools::SwitchDisplayConfigForAllModes(  UWORD16 _First,
                                             UWORD16 _Second)
{
   UWORD16 i;

   for(i=0; i<cMAX_MODE; i++)
   {
      SwitchDisplayConfigForOneMode(_First,_Second, (e_MODE_TYPES)i);
   }
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Routine appelée lorsqu'il y a un problème dans l'IHM                     */
/*%I Input Parameter : 																			*/
/*%I		_panic_module : module ayant provoqué le "panic"							*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O		NONE																					  	*/
/******************************************************************************/
void Tools::Panic(ePANIC_MODULE _panic_module)
{

   Controller* Cont = Controller::GetInstance();

   switch(_panic_module)
   {
      case PANIC_MODULE_VENTIL :
      #ifdef _BORLAND
         ShowMessage("PANIC (PANIC_MODULE_VENTIL)!!! : \nProblème dans la configuration des noeuds dans FrameVentilation.");
         exit(1);
      #endif
      break;

      case PANIC_MODULE_ALARM :
      #ifdef _BORLAND
         ShowMessage("PANIC (PANIC_MODULE_ALARM)!!! : \nProblème dans la configuration des noeuds dans FrameAlarm.cpp");
         exit(1);
      #endif
      break;

      case PANIC_MODULE_GRAPH:
      #ifdef _BORLAND
         ShowMessage("PANIC (PANIC_MODULE_GRAPH)!!! : \nProblème dans la configuration des noeuds dans FrameGraph.cpp");
         exit(1);
      #endif
      break;

      case PANIC_MODULE_EVENT_NODE_VENTIL:
      #ifdef _BORLAND
         ShowMessage("PANIC (PANIC_MODULE_EVENT_NODE_VENTIL)!!! : \nProblème dans la configuration des noeuds de ventilation dans GlobalEventNode.hpp");
         exit(1);
      #endif
      break;

      case PANIC_MODULE_EVENT_NODE_ALARM:
      #ifdef _BORLAND
         ShowMessage("PANIC (PANIC_MODULE_EVENT_NODE_ALARM)!!! : \nProblème dans la configuration des noeuds d'alarme dans GlobalEventNode.hpp");
         exit(1);
      #endif
      break;

      case PANIC_MODULE_EVENT_NODE_MAINT_CALIB:
      #ifdef _BORLAND
         ShowMessage("PANIC (PANIC_MODULE_EVENT_NODE_MAINT_CALIB)!!! : \nProblème dans la configuration des noeuds de calibration maintenance dans GlobalEventNode.hpp");
         exit(1);
      #endif
      break;


      case PANIC_MODULE_FRAME_GRAPH:
      #ifdef _BORLAND
         ShowMessage("PANIC (PANIC_MODULE_FRAME_GRAPH)!!! : \nProblème dans FrameGraph.cpp");
         exit(1);
      #endif
      break;

      default:
      case PANIC_MODULE_UNKNOWN:
      #ifdef _BORLAND
         ShowMessage("PANIC (PANIC_MODULE_UNKNOWN)!!! : \nModule ayant généré le panic inconnu.");
         exit(1);
      #endif
      break;
   }
   Cont->PlayBuzzerSec();
   Cont->PlayBuzzer();
   while(1);
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Determine le nombre de digit d'une valeur											*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		Number : valeur																		*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		nb de digit																				*/
/******************************************************************************/
UWORD16 Tools::FindNbDigit(UWORD16 _Number)
{
   if(_Number<10) return 1;
   if(_Number<100) return 2;
   if(_Number<1000) return 3;
   if(_Number<10000) return 4;
   if(_Number<100000) return 5;   
   return 1;
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Determine si on est sur un noeud de modification									*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		IdNode : Id du noeud																	*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 	  	TRUE si l'ID correspond a un noeud de modification					  		*/
/******************************************************************************/
e_BOOL Tools::IsModifyNode(UWORD16 _IdNode)
{
   return ((e_BOOL) (cInfoNodeDisplayTable[_IdNode] & 0x01));
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Determine la longueur d'une chaine													*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		Text : chaine																			*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 	  	longueur de la chaine														  		*/
/******************************************************************************/
UWORD16 Tools::StrLen(UBYTE* _Text)
{
   UWORD16 Cpt = 0;
   if( _Text)
   {
      while(_Text[Cpt] != 0)
      {
         Cpt++;
      }
   }      
   return Cpt;
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Copie la chaine Src dans Dest et renvoie un pointeur vers Dest           */
/*%C (réécriture de strcpy de la stdlib)                                      */
/*%I Input Parameter : 																			*/
/*%I		Text : chaine																			*/
/*%IO Input/Output : 																			*/
/*%IO		Dest																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 	  	longueur de la chaine														  		*/
/******************************************************************************/
UBYTE* Tools::StrCpy(UBYTE* Dest, UBYTE* Src)
{
   UWORD16 Cpt = 0;
   while(Src[Cpt] != 0)
   {
      Dest[Cpt] = Src[Cpt];
      Cpt++;
   }
   Dest[Cpt] = 0;
   return Dest;
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Determine la version logicielle														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 	  	Version logicielle															  		*/
/******************************************************************************/
UBYTE* Tools::GetVersionSoft()
{
   UWORD16 ValueS,Tmp;
   static UBYTE VersionSoft[9];

   DataBaseAccess::ReadValue(&ValueS, VERSION_NUMBER_0, VERSION);
   Tmp = ValueS & 0xFF00;
   Tmp >>= 8;
   VersionSoft[0] = Tmp;
   Tmp = ValueS & 0x00FF;
   VersionSoft[1] = Tmp;
   DataBaseAccess::ReadValue(&ValueS, VERSION_NUMBER_1, VERSION);
   Tmp = ValueS & 0xFF00;
   Tmp >>= 8;
   VersionSoft[2] = Tmp;
   Tmp = ValueS & 0x00FF;
   VersionSoft[3] = Tmp;
   DataBaseAccess::ReadValue(&ValueS, VERSION_NUMBER_2, VERSION);
   Tmp = ValueS & 0xFF00;
   Tmp >>= 8;
   VersionSoft[4] = Tmp;
   Tmp = ValueS & 0x00FF;
   VersionSoft[5] = Tmp;
   DataBaseAccess::ReadValue(&ValueS, VERSION_NUMBER_3, VERSION);
   Tmp = ValueS & 0xFF00;
   Tmp >>= 8;
   VersionSoft[6] = Tmp;
   Tmp = ValueS & 0x00FF;
   VersionSoft[7] = Tmp;

   VersionSoft[8] = 0;

   return VersionSoft;
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Determine la version logicielle de la carte alim 								*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 	  	Version logicielle															  		*/
/******************************************************************************/
UBYTE* Tools::GetVersionSoftSupply()
{
   UWORD16 ValueS,Tmp;
   static UBYTE VersionSoftSupply[9];

   VersionSoftSupply[0] = 'A';
   VersionSoftSupply[1] = 'L';
   DataBaseAccess::ReadValue(&ValueS, POWER_SUPPLY_VERSION_NUMBER_0, POWER_SUPPLY);
   Tmp = ValueS & 0x00F0;
   Tmp >>= 4;
   Tmp += (Tmp <= 9 )? 0x30:0x57;
   VersionSoftSupply[2] = Tmp;
   Tmp = ValueS & 0x000F;
   Tmp += (Tmp <= 9 )? 0x30:0x57;
   VersionSoftSupply[3] = Tmp;
   DataBaseAccess::ReadValue(&ValueS, POWER_SUPPLY_VERSION_NUMBER_1, POWER_SUPPLY);
   Tmp = ValueS & 0x00F0;
   Tmp >>= 4;
   Tmp += (Tmp <= 9 )? 0x30:0x57;
   VersionSoftSupply[4] = Tmp;
   Tmp = ValueS & 0x000F;
   Tmp += (Tmp <= 9 )? 0x30:0x57;
   VersionSoftSupply[5] = Tmp;
   DataBaseAccess::ReadValue(&ValueS, POWER_SUPPLY_VERSION_NUMBER_2, POWER_SUPPLY);
   Tmp = ValueS & 0x00F0;
   Tmp >>= 4;
   Tmp += (Tmp <= 9 )? 0x30:0x57;
   VersionSoftSupply[6] = Tmp;
   Tmp = ValueS & 0x000F;
   Tmp += (Tmp <= 9 )? 0x30:0x57;
   VersionSoftSupply[7] = Tmp;

   VersionSoftSupply[8] = 0;

   return VersionSoftSupply;
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Retourne le numéro de série du produit                                   */
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 	  	Numéro de série   															  		*/
/******************************************************************************/
UBYTE* Tools::GetProductSerialNumber()
{
   UWORD16 ValueS,Tmp;
   UWORD16 i, j;
   static UBYTE ProductSerialNumber[13];

   for(j=0; j<13; j++)
     ProductSerialNumber[j] = 0;
   j=0;
   for(i=SERIAL_NUMBER_1; i<=SERIAL_NUMBER_5; i++)
   {
      DataBaseAccess::ReadValue(&ValueS, (e_DB_VERSION)i, VERSION);
      Tmp = ValueS & 0xFF00;
      Tmp >>= 8;
      if(j < 13)
         ProductSerialNumber[j++] = Tmp;
      Tmp = ValueS & 0x00FF;
      if(j < 13)
         ProductSerialNumber[j++] = Tmp;
   }
   if(j < 13)
      ProductSerialNumber[j] = 0;

   return ProductSerialNumber;
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Determine la taille en pixel d'un string											*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 	  	NONE																				  		*/
/******************************************************************************/
UWORD16 Tools::GetStringPixelSize(UBYTE* _Text, UWORD16 _Font)
{
   UWORD16 i = 0, Size = 0;
   UBYTE* _Config = GetFontWidthConfig();

	while(_Text[i] > 0x00)
   {
		Size += _Config[(_Font-1)*TOOLS_CHARS_MAX + (_Text[i])];
      i++;
	}
    return Size;
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Determine la taille en pixel d'un nombre											*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 	  	NONE																				  		*/
/******************************************************************************/
UWORD16 Tools::GetNumberPixelSize(  UWORD16 _Number,
                                    UWORD16 _Font,
                                    e_BOOL _IsFloat)
{
   UBYTE* _Config = GetFontWidthConfig();

   /*%C Quelque soit la police, tous les chiffres ont exactement le même */
   /*%C nombre de pixels en largeur */
	UWORD16 Size = 0;

	Size = _Config[(_Font-1)*TOOLS_CHARS_MAX + ('1')] * Tools::FindNbDigit(_Number);
   if(_IsFloat)
	{
    	if(Tools::FindNbDigit(_Number) == 1)
		{
			Size = 2 * Size + _Config[(_Font-1)*TOOLS_CHARS_MAX + ('.')];
		}
      else
		{
   		Size += _Config[(_Font-1)*TOOLS_CHARS_MAX + ('.')];
		}
	}

   return Size;
}
/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Indique si le paramètre est de type Float											*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 	  	NONE																				  		*/
/******************************************************************************/
e_BOOL Tools::IsFloat(SWORD16 F)
{
	return (e_BOOL)((F%10) != 0);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Retourne la valeur absolue du paramètre												*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																						*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 	  	NONE																				  		*/
/******************************************************************************/
SWORD32 Tools::Abs(SWORD32 S)
{
   return (S>0?S:-S);
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Mise en forme des messages																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		Message Texte, Taille de la fenêtre												*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 	  	Texte mis en forme															  		*/
/******************************************************************************/
UBYTE* Tools::BuildMessage(UBYTE* Text , UWORD16 SizeBox , UWORD16 BoxFont)
{
  /*%C Déclarations variables locales*/
   static UBYTE TextTemp[cARRAY_SIZE];
   UWORD16 SizeString = 0;
   UWORD16 SizePreviousText = 0;
   UWORD16 i = 0 ,
           j = 0 ,
           k = 0 ,
			  x = 0;

 	/*%C String initialisation */
   for (j=0; j<cARRAY_SIZE; j++)
   {
      TextTemp[j] = 0;
   }
   if(!Text)
      return TextTemp;
  
  /*%C Receuil du nombre de caractère dans le message */
   SizeString = Tools::StrLen(Text) ;

   /*%C Mise en forme des messages */
   do
   {
   /*%C On calcule le première ligne */
      do
      {
		   /*%C Protection pour le dépasement */
		   x = i + k;
			x = x % cARRAY_SIZE;
         TextTemp[x] = Text[i];
         i = i + 1;
      }
   while(((	Tools::GetStringPixelSize(TextTemp, BoxFont) - 
   		 	SizePreviousText) < (SizeBox - 4)) &&
            (Text[i] != '\0') &&
            (Text[i] != '|')) ;

   /*%C On parcours la premiere ligne pour determiner le nombre */
   /*%C de caractere dans 1ere ligne */
      if((Text[i] != ' ') && (Text[i] != '\0') && (Text[i] != '|'))
      {
         /*%C Si le texte contient plusieurs mots */
         for(j = 0 ; j < i ; j++)
         {
            if (TextTemp[i-j] == ' ')
            {
				   /*%C Protection pour le dépasement */
				   x = i - j;
					x = x % cARRAY_SIZE;
               TextTemp[x] = '|';
				   /*%C Protection pour le dépasement */
				   x = i - j + 1;
					x = x % cARRAY_SIZE;
               TextTemp[x] = '\0';
               i = i - j + 1;
               break;
            }

            /*%C Sinon si on a parcouru tout le texte sans espace */
            else if(Text[i] != '|' && j == i-1)
            {
				   /*%C Protection pour le dépasement */
				   x = i - 1;
					x = x % cARRAY_SIZE;
               TextTemp[x] = '-';
				   /*%C Protection pour le dépasement */
				   x = i;
					x = x % cARRAY_SIZE;
               TextTemp[x] = '|';
				   /*%C Protection pour le dépasement */
				   x = i + 1;
					x = x % cARRAY_SIZE;
               TextTemp[x] = '\0';
               i = i - 1;
               k = 2;
               break;
            }
         }
      }
   /*%C Si le texte ce finis sur un espace */
   else if (Text[i] == ' ')
   {
	   /*%C Protection pour le dépasement */
	   x = i;
		x = x % cARRAY_SIZE;
      TextTemp[x] = '|';
	   /*%C Protection pour le dépasement */
	   x = i + 1;
		x = x % cARRAY_SIZE;
      TextTemp[x] = '\0';
      i = i + 1;
   }

   /*%C Mémo taille ligne précédente */
   SizePreviousText = Tools::GetStringPixelSize(TextTemp, BoxFont);
   }
while((i < SizeString));

/*%C Retourne le texte modifié */
return TextTemp ;
}
/********************************************************************************/
/*%C                       Functionnal description :                        	*/
/*%C                                                                          	*/
/*%C Short bip request															*/
/*%C                                                                         	*/
/*%I Input Parameter : 															*/
/*%I		NONE																*/
/*%IO Input/Output : 															*/
/*%IO		NONE																*/
/*%O Output Parameter : 														*/
/*%O 	  	NONE																*/
/********************************************************************************/
void Tools::ShortBipRequest(void)
{
	e_BOOL _bip_running = (e_BOOL) DB_ControlRead(BIP_RUNNING_U16); 

 	if (!_bip_running) 
        DB_ControlWrite(VALIDATION_BIP_U16, BIP_SHORT_VALID); 
}
