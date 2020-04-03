/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : Product.h	 								 		 		  */
/*                              	                                          */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  */
/*%C Choix du produit à compiler          				 					  */
/*%C			                                                              */
/******************************************************************************/

#ifndef PRODUCT_H
#define PRODUCT_H

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/
#if defined(SUPPORTAIR_M2)

	#define CONFIG_VOL_MODE
	
	#define CONFIG_SIMV_MODE

    #define CONFIG_VTE
	
   	#define CONFIG_REGUL_O2

   	#define CONFIG_ALARM_O2

	#define CONFIG_MEASURE_O2

	#define CONFIG_USB

#elif defined(LEGENDAIR_XL2)

	#define CONFIG_VOL_MODE

	#define CONFIG_SIMV_MODE

    #define CONFIG_VTE

	#define CONFIG_MEASURE_O2

	#define CONFIG_USB

#elif defined(LEGENDAIR_S2)

	#define CONFIG_USB
	
	#define CONFIG_SMALL_BATTERIES
	#define CONFIG_SMALL_BATTERIES_THRESHOLD (3000)

#else
      #error Il faut définir un produit valide (SUPPORTAIR_M2, LEGENDAIR_XL2 ou LEGENDAIR_S2) en directive de compilation !
#endif

#endif //#ifndef PRODUCT_H
