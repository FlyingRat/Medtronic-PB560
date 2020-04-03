/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : INIT_Leds.c            					                     		*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C        			  										      					      */
/*%C          																					   */
/******************************************************************************/
/*%I Input Parameter :  NONE                                                  */
/*%IO Input/Output :    NONE	                                                */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                           */
/******************************************************************************/

#include "p18f6622.h"
#include "typedef.h"
#include "io_declare.h"
#include "enum.h"
#include "define.h"



/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/
void INIT_Leds(void)
{
	UWORD16 Loop = 0 ;
	UWORD16 SupplyAC = 0 ;
	UWORD16 SupplyDC = 0 ;

	/*%C Tempo to synchronise with CPU Card */
	for(Loop = 0 ; Loop < 85 ; Loop ++)
	{
		/*%C Run WatchDog */
		ClrWdt();
		
		/*%C Waiting for the end of MOS Switch _ 8 ms 										*/
		TMR3H = 0x05; 
		TMR3L = 0x0FF; 
		PIR2bits.TMR3IF = 0;
		while (PIR2bits.TMR3IF == 0);
	}

	/* Mesures VACDC et VDC */
	/* Moyenne sur 40 échantillons */
	for(Loop = 0 ; Loop < 40 ; Loop ++)
	{
		/* Lancement du WatchDog */
		ClrWdt();
		/* Prépare la mesure */
		ADCON0 = MEASURE_VACDC_CHANNEL ;
		/* Lance la mesure */
		ADCON0bits.GO = 1;
		/* Attendre la fin de l'acquisition */
		while(ADCON0bits.GO != 0);
		/* Faire la somme des acquisitions pour la moyenne*/
		
		SupplyAC = SupplyAC + ADRES;
		/* Lancement du WatchDog */
		ClrWdt();
		/* Prépare la mesure */		
		ADCON0 = MEASURE_VDC_CHANNEL ;
		/* Lance la mesure */
		ADCON0bits.GO = 1;
		/* Attendre la fin de l'acquisition */
		while(ADCON0bits.GO != 0);
		/* Faire la somme des acquisitions pour la moyenne*/
		SupplyDC = SupplyDC + ADRES;
	}
	
	/* Calcul de la moyenne de VAC */
	SupplyAC = SupplyAC / 40;
	/* Teste si VACDC est supérieur à 31V */
	if(SupplyAC > 880)
	{
		/* VAC présent*/
		SupplyAC = TRUE ;
	}
	else
	{
		/* VAC absent*/
		SupplyAC = FALSE;	
	}
	/* Calcul de la moyenne de VDC */
	SupplyDC = SupplyDC / 40;
	/* Teste si VACDC est supérieur à 9V */
	if(SupplyDC > 256)
	{
		/* VDC présent*/
		SupplyDC = TRUE ;
	}
	else
	{
		/* VDC absent*/
		SupplyDC = FALSE;	
	}
	/* Si on a du secteur et pas de DC */
	/* On pilote les led AC + DC + BAT */
	if ((SupplyAC == TRUE) && (SupplyDC == FALSE))
	{
		/* Pilotage des LED AC et BAT	pendant 200ms (aproximativement)*/
		PRESENCE_AC = TRUE;
		Nop()
		LED_ETAT_BAT = TRUE;
		
		/* Pilotage de la LED DC uniquemnt si il y a le secteur pendant 200ms (aproximativement)*/
		for(Loop = 0 ; Loop < 4000 ; Loop ++)
		{
			/* Lancement du WatchDog */
			ClrWdt();
			
			/* On hache le signal pour diminuer le courant qui remonte sur les autres alimentations.*/
			if (SupplyAC == TRUE)
			{
				SHUNT_DIODE_DC = TRUE;
			}
			/*%C Attendre 4 µs 										*/
			TMR3H = 0xFF; 
			TMR3L = 0xF3; 
			PIR2bits.TMR3IF = 0;
			while (PIR2bits.TMR3IF == 0);
				
			SHUNT_DIODE_DC = FALSE;
			/*%C Attendre 50 µs 										*/
			TMR3H = 0xFE; 
			TMR3L = 0x6F; 
			PIR2bits.TMR3IF = 0;
			while (PIR2bits.TMR3IF == 0);
		}
	
		/* Arret des led */
		PRESENCE_AC = FALSE;
		Nop()
		LED_ETAT_BAT = FALSE;
	}
	
	/* Si on a du secteur et du DC */
	/* On pilote les led AC + BAT */
	else if ((SupplyAC == TRUE) && (SupplyDC == TRUE))
	{
		/* Pilotage des LED AC et BAT	pendant 200ms (aproximativement)*/
		PRESENCE_AC = TRUE;
		Nop()
		LED_ETAT_BAT = TRUE;
		for(Loop = 0 ; Loop < 25 ; Loop ++)
		{
			/* Lancement du WatchDog */
			ClrWdt();
		
			/* Attendre 8 ms 										*/
			TMR3H = 0x05; 
			TMR3L = 0x0FF; 
			PIR2bits.TMR3IF = 0;
			while (PIR2bits.TMR3IF == 0);
		}
		/* Arret des led */
		PRESENCE_AC = FALSE;
		Nop()
		LED_ETAT_BAT = FALSE;
	}
	else
	{
		/*Pas de pilotage des led dans les autres cas*/
	}
}
