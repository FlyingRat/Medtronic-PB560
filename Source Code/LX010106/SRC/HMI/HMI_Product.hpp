/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_Product.hpp	 								 		 			  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Choix du produit à compiler          				 						     	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef HMIProductH
#define HMIProductH

#include "product.h"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/
#undef JUMPER_JP7
#undef JUMPER_JP8

#if defined(SUPPORTAIR_M2) /* ----- M2 ------- */

   /* configuration software */

   #define HMI_CONFIG_M2

   /* configuration hardware */

#ifdef _BORLAND
   #define JUMPER_JP7 1
   #define JUMPER_JP8 0
#endif

#elif defined(LEGENDAIR_XL2) /* ----- XL2 ------- */

   /* configuration software */

   #define HMI_CONFIG_XL2

   /* configuration hardware */

#ifdef _BORLAND
   #define JUMPER_JP7 1
   #define JUMPER_JP8 1
#endif


#elif defined(LEGENDAIR_S2) /* ----- S2 ------- */

   /* configuration software */

   #define HMI_CONFIG_S2

   /* configuration hardware */

#ifdef _BORLAND
   #define JUMPER_JP7 0
   #define JUMPER_JP8 1
#endif

#endif

#endif //#ifndef HMIProductH
