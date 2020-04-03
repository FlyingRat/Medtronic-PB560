/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DRV_BuzInit.c                                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :   Buzzer driver function   */
/*%C                                                                          */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE                                                  */
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
#include "enum.h"
#include "Structure.h"
#include "DB_Config.h"
#include "DB_Control.h"
#include "io_declare.h"
#include "DRV_BuzInit.h"
#include "Driver_Datas.h"

/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void DRV_BuzInit(void)
{
	UWORD16 Version = DB_VersionRead(VERSION_NUMBER_0);
	static UWORD16 FirstBuzInit = TRUE;
    static UWORD16 Frequency_Buzzer;
	
	/*%C Si premiere initialisation au démarrage de l'appareil, on initialise 	 */
	/*%C tous les registres PWM et Timer */
	if (FirstBuzInit == TRUE)
	{
       e_Alarm_Tone Sound_Type_Select = DB_ConfigRead(SOUND_TYPE_SELECT_U16);
 
        if (Sound_Type_Select == ORIGINAL)
        {
            Frequency_Buzzer = CLASSIC_FREQUENCY_BUZZER;
        }
        else
        {
            Frequency_Buzzer = COMPLIANT_FREQUENCY_BUZZER;
        }

		/*%C Mise à jour du flag de 1ère initialisation */ 
 	    FirstBuzInit = FALSE; 

		//Programmation du pwm3 génération du niveau sonore du buzzer
		//Registre PWMCON1
		//PW3 programmé pa PM3 PS3 = 0
		//PS2 ne concerne pas le canal 3
		//PB01 ne concerne pas le canal 3
		//Canal 3 en mode standard PM3 = 0
		//Signal en sortie canal 3 PEN3 = 1
		//PWMCON3 =0xxx xxxx 0xxx 1xxx 
		PWMCON1 |= 0x0080;	   
		PWMCON1 &= 0x7F7F;  
		//Registre PWMCON0
		//Pas de demande d'interruption PIR3 = 0
		//Interruption non autorisée PIE3 = 0
		//Entrée d'horloge = FCPU PT3 = 0
		//Canal 3 en fonctionnement PTR3 = 1
		//PWMCON0 =0xxx 0xxx 0xxx 1xxx	
		PWMCON0 |= 0x0008;	   
		PWMCON0 &= 0x777F;	   
		PP3 = 10E8/(25*FREQUENCY_SOUND_LEVEL); //Programmation de la période du PWM3
		//Programmation du PWM par timer T8 génération de la fréquence buzzer
		//Programmation du registre de controle Timer T7
		//T7I = 000 Prescaler = FCPU/8 résolution 200ns à 40MHz
		//T7M = 0 Mode timer
		//Bit Réservé = 00
		//T7R = 0 Timer 7 à l'arrêt
		T78CON &= 0XFFF0;
		// Programmation du registre CCM2 pour CC28 capture compare mode
		//Capture compare mode register CCM0
		// ACC28 alloué au timer 7
		// CCMOD7 mode 3 compare reset de la sortie à overflow  de timer  
		// ACC31,ACC30,ACC29,CCMOM31,CCMOD30,CCMOD29 non programmés
		// ==> CCM7 = xxxx xxxx  xxxx 0111 = 0x XXX7
		CCM7 &= 0xFFF7;  //Reset ACC27
		CCM7 |= 0x0007;  //Set CMOD28
	
	
		//Préchargement des valeurs du BUZZER 
 	    //Calcul du rechargement du timer T7 pour fixer la période du PWM de réglage du niveau sonore 
	    //T7REL = 65535 - (1/Fréquence buzzer en ns) / Résolution du timer en ns(FCPU /8)200ns voir registre T78CON) 
        T7REL = 65535 - (10E9/Frequency_Buzzer)/(10E3/(FCPU/8)); 

		//Programmation du registre CC28 capture compare pour sortie P7.4
		//Rapport cyclique du PWM à 50%
		CC28 = (UWORD16)(T7REL + (65535 - T7REL)/2);
		
		//Arrêt du timer T7
		T7R = 0;
		// sortie Pwm3 désactivée
		PWMCON1 &= 0xFFF7;    	
		// Desactivation Buzzer Sécurité
		SEC_BUZ = 0;
	}
	else
	{
		
		//Préchargement des valeurs du BUZZER 
 	    //Calcul du rechargement du timer T7 pour fixer la période du PWM de réglage du niveau sonore 
 	    //T7REL = 65535 - (1/Fréquence buzzer en ns) / Résolution du timer en ns(FCPU /8)200ns voir registre T78CON) 
        T7REL = 65535 - (10E9/Frequency_Buzzer)/(10E3/(FCPU/8)); 
		//Programmation du registre CC28 capture compare pour sortie P7.4
		//Rapport cyclique du PWM à 50%
		CC28 = (UWORD16)(T7REL + (65535 - T7REL)/2);
		
	}
}
