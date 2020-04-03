/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_ADC_ConvertInit.c                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                     */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/
#ifndef _TASKING
#include "LH_ST10F276.h"
#include <intrins.h>
#else
#include "regf276e.h"
#endif
#include "typedef.h"
	#define ADC_DRIVER_DATA_DECLARATION
#include "Driver_ADConverter_data.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DRV_ADC_ConvertInit(void)
{
	UWORD16 Read;

	// Registre de contrôle du convertisseur ad ADCON
		// sélection du canal 15 ADCH = 1111
		// conversion unique sur plusieurs canaux ADM = 10
		// pas de démarrage de la conversion ADST = 0
		// Status de la conversion, pas de conversion en cours ADBSY = 0
		// Pas de conversion sur lecture de ADDAT ADWR = 0
		// Pas d'autorisation d'injection ADCIN = 0
		// Flag de demande d'injection ADCRQ = 0
		// Temps d'échantillonnage = temps de conversion ADSTC = 11
		// Temps de convertion  TLSC * 24  ADCTC = 11
		// Attente pour mode lecture ADDAT ADWR = 1 
		// ==> ADCON =1111 10 0010 1111 = 0xF22F 
	ADCON = 0xF22F;
	ADCIC = 0; 		// Verrouillage des interruption pendant l'initialisation
	ADEIC = 0 ;		// Verrouillage des interruption pendant l'initialisation
	// Registre PECC0
		// Nbre de données à transférer 14 COUNT = 00001110 
		// Largeur de la donnée à transférer 16 bits BWT = 0
		// Incrémentation du pointeur de destination 	INC = 01
		// PECC0 = 0000 0000 0010 0001 0000 = 0x00210
	PECC0 = 0x0210;
	// Pointeur source pointe sur le registre du  resultat de chaque conversion 
	SRCP0 =(UWORD16) (&ADDAT); // adresse de ADDAT
	// Pointeur destination  pointe sur le tableau des résultats de conversion de toutes les voies
	DSTP0 = _sof_(conversion_numerique);  //Transformation d'un pointeur en adresse segment 0)
	
	/*%IR = 0 ,IE = 1; ILVL  = 14 ,GLVL = 0 ==> PEC canal 0		 */
	ADCIC = 0x78;
	
	//initialisation du registre de gestion d'erreur du convertisseur
	/*%IR = 0 ,IE = 1; ILVL  = 12 ,GLVL = 0 	 */
	ADEIC = 0x70;		
	
	//Vidage des registres du résultat de convertion
 	Read = ADDAT;
	Read = ADDAT2;
}
