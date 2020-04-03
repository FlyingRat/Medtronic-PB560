/******************************************************************************/
/*																										*/
/* Project Number	: 	RB0505     			     		                       	  		*/
/*																										*/
/*----------------------------------------------------------------------------*/
/*                                                                 			  	*/
/* Filename	: DRV_VarEeprom.c     		   				                  		*/
/*                                                           				  		*/
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C 			Functionnal description : 	declaration for var eeprom	            */
/*                                                            				  		*/
/******************************************************************************/
/*%I 	Input Parameter : 			None		      	                          	*/
/*%IO Input/Output Parameter : 	None 	        			                  		*/
/*%O 	Output Parameter : 			None                        				  		*/
/******************************************************************************/


#ifndef _BORLAND
    #ifndef _TASKING
    // Permet de ranger les adresses dans l'ordre de leur déclaration
      #pragma ORDER
    // Toutes les variables déclarés ici seront placé à l'adresse EEPROM
       #pragma RENAMECLASS(HDATA0=EEPROM)
	#else
/* le pragma ORDER (ordonner les variables dans la mémoire dans l'ordre des 
déclaration, est assuré sous TASKING par l'option de compilation sur ce fichier " -Ot" */
	   	   #pragma class HB=EEPROM
		  #endif
#endif


#define EEP_VAR_SOURCE

#include "typedef.h"
#include "DRV_VarEeprom.h"
//#include "database.h"

// Les variables locales sont automatiquement importées par le preprocesseur
// lors de la compilation.

// Cette déclaration permet de rendre visible toute la base pour l'émulateur
void TestReadBaseEmulator(void) { ; }

#undef EEP_VAR_SOURCE
