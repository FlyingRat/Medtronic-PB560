/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : CMP_LeakFactors.c     	 		                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C   This function computes leak factors values during inspiration          */
/*                                                                            */
/******************************************************************************/
/*%I Input Parameter : NONE                                                   */
/*%IO Input/Output : NONE                                                     */
/*%O Output Parameter : NONE                                                  */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                      */
/******************************************************************************/
#include "typedef.h"
#include "enum.h"
#include "DB_Current.h"
#include "DB_Compute.h"
#include "DB_Control.h"
#include "Ventilation_Datas.h"
#include "CMP_LeakFactors.h"
#include "DB_Measurement.h"
#include "Ventilation_Compute_data.h"
#include "math.h"
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void CMP_LeakFactors(void)
{
	UWORD16 j = 0;	// indice tableau
	UWORD16 i = 0;
	SWORD32 CriterePlateau = 0;
	UBYTE Increment = 0;
	SWORD16 Start = 0;
	SWORD32 Qee = 0;
	SWORD32 QinspTest1 = 0;
	SWORD32 QinspTest2 = 0;
	SWORD32 ComputedPeep = (SWORD32)DB_ComputeRead(COMPUTED_PEEP_U16);
	SWORD32	AdjustPeep = DB_CurrentRead(ADJUST_PEEP_U16);
	SWORD32 QLeak = 0;
	double QLeakTheoritical4mm = 0;
	UWORD16 PlateauLenght = 20;
	SWORD32 MoyenneCarreParCarreMoyenne = 3325;
	SWORD32 MoyenneDebitParTemps =0;
	SWORD32 PetitA = 0;
	SWORD32 PetitB = 0;
	SWORD32 Qee_glob = 0;
	UWORD16 Ventil_State = DB_ControlRead(VENTIL_STATE_U16);
	UWORD16 MeasureTe = 100 * DB_ComputeRead(MEASURE_TE_U16) / 2 - 100;
	static SWORD32 FiltreQee[5];
	SWORD32 Qee_Courant = 0;
	static UBYTE Filled = FALSE;
	static UBYTE Count = 0;
	SWORD32 QeeScale = 100;

//Décalage du pointeur acquisition à 100 ms avant le début inspi, si trigger, en gérant le buffer circulaire	
	//Offset of the acquisition of 100 ms pointer before the beginning of inspiration, if trigger, managing the circular buffer	
	if (Ventil_State == VEN_INSPIRATION_TRIGGERED)
	{	
		if (VEN_PtrMesureFlowPress >= 10)
  		{
   			VEN_PtrMesureFlowPress = VEN_PtrMesureFlowPress - 10;
   		}
   		else
   		{
   			VEN_PtrMesureFlowPress = cPLATEAU_TABLES_LENGHT - (10 - VEN_PtrMesureFlowPress);
   		}
    	Increment = 1;
	}
//Détermination de la durée d'échantillonage sur laquelle on réalise les calculs, selon le TE
	// Determine the sampling time on which calculations are performed, as the TE
	if (MeasureTe < 300 )
	{
		PlateauLenght = 20;
	}
	else if (MeasureTe < 400 )
	{
		PlateauLenght = 30;
	}
	else if (MeasureTe < 500 )
	{
		PlateauLenght = 40;
	}
	else if (MeasureTe < 600 )
	{
		PlateauLenght = 50;
	}
	else
	{
		PlateauLenght = 60;
	}	
		
// Calcul Qi moyen sur les 10 échantillons les plus récents. Utilisé pour critère stabilité
	// Calculate average Qi on the most recent 10 samples. Used to test stability
	QinspTest1 = CMP_MeanTable(VEN_PtrMesureFlowPress, 10,VEN_MesureFlowQinsp,cPLATEAU_TABLES_LENGHT);
//Boucle incrementant le plateau selon le critère de stabilité +/-5% QinspTest1 
//Saturé à la taille du plateau déduit du TE 
	// Loop incrementing the plate according to the criterion of stability + / -5% QinspTest1
	// Saturated size tray deducted from TE
	i = 0;
	while ((CriterePlateau < cSTABILITY_CONDITION_POS )&&(CriterePlateau > cSTABILITY_CONDITION_NEG )&& (PlateauLenght - ( 10 * i) >= 10 ))
	{
//Décalage de 10 échantillons en gérant le buffer circulaire
		// Offset of 10 samples in the circular buffer manager
		if (VEN_PtrMesureFlowPress >= 10 * ( i + 1 ))
   		{
   			j = VEN_PtrMesureFlowPress - 10 * ( i + 1 );
   		}
   		else
   		{
   			j = cPLATEAU_TABLES_LENGHT - ( 10 * ( i + 1 ) - VEN_PtrMesureFlowPress);
   		}
//Calcul sur la plage de 100ms courante de la moyenne Qi
		// Calculate the current range of 100ms average Qi
		QinspTest2 = CMP_MeanTable(j, 10,VEN_MesureFlowQinsp,cPLATEAU_TABLES_LENGHT);
//Calcul de l'écart entre QinspTest1entre le Qi moyen sur la plage courante
		// Calculate the difference between the average QinspTest1entre Qi on the current track
		CriterePlateau = (QinspTest1 - QinspTest2) * QeeScale / QinspTest1;

//Incrément de l'indice
		i = i + 1;
	}
	PlateauLenght = 10 * i;

//Pour la régression linéaire, on règle aussi le produit de la moyenne des temps, au carré, par
//la moyenne des carrés des temps.
//Exemple, pour PlateauLenght = 20, la durée des acquisitions est 200 ms.
// Le temps moyen est 105, au carré donne 11025. La moyenne des carrés des temps (partant de 10 à 200ms)
//donne 14350. La différence donne 3325. Voir méthode régression linéaire.
	//
	// Calculate the difference between the average QinspTest1entre Qi on the current track
	// For linear regression, also sets the product of the average time squared by
	// the average of the squares of the times .
	// Example for PlateauLenght = 20 , duration of acquisitions was 200 ms.
	// The average time is 105 square gives 11025 . The average square of time (up from 10 to 200ms )
	// gives 14350 . The difference gives 3325 . See linear regression method .
	//
	switch(PlateauLenght)
	{
	case 20:
			MoyenneCarreParCarreMoyenne = 3325;
			break;
	case 30: 
			MoyenneCarreParCarreMoyenne = 7491;
			break;
	case 40: 
			MoyenneCarreParCarreMoyenne = 13325;
			break;
	case 50: 
			MoyenneCarreParCarreMoyenne = 26275;
			break;
	case 60: 
			MoyenneCarreParCarreMoyenne = 29991;
			break;
	default: 
			MoyenneCarreParCarreMoyenne = 825;
			break;
	}
	
//Calcul de la moyenne des produits Qi * temps, sur une durée (PlateauLenght*10)ms, variable selon Te, 
//En démarrant (PlateauLenght*10)ms avant fin d'expi et allant jusqu'à la fin expi. (décalé de 100ms si trigg) 
	//
	// Calculate the average time * Qi products over a period ( PlateauLenght * 10) ms , varying Te,
	// When starting ( PlateauLenght * 10) ms before the end of expiration and up to the end expiration . (shifted 100ms if trigg )
	Start = VEN_PtrMesureFlowPress - PlateauLenght;
	Start = Start + 1;
	if (Start < 0)
	{
		Start = cPLATEAU_TABLES_LENGHT + Start;
	}
	// Calcule de la somme entre l'indice de début et l'indice de fin.
	// Calculate the sum from the start index and end index
	if (Start <= VEN_PtrMesureFlowPress)
	{
		i = 1;
		for (j = Start;j <= VEN_PtrMesureFlowPress;j++)
		{
			MoyenneDebitParTemps = MoyenneDebitParTemps + VEN_MesureFlowQinsp[j] * ( i * 10 );
			i = i + 1;
		}
	
	}
	else
	// Calcule de la somme entre l'indice de début et l'indice de fin.
	// Calculate the sum from the start index and end index
	{ 
		for (j = 0; j <= VEN_PtrMesureFlowPress;j++)
		{
			MoyenneDebitParTemps = MoyenneDebitParTemps + VEN_MesureFlowQinsp[j] * (PlateauLenght * 10 - ( VEN_PtrMesureFlowPress- j ) * 10);
		}
		for (j= (UWORD16)Start;j < cPLATEAU_TABLES_LENGHT;j++)
		{
			MoyenneDebitParTemps = MoyenneDebitParTemps + VEN_MesureFlowQinsp[j] * ((j - Start + 1 ) * 10);
		}
	}
//Calcul de la moyenne
	// Calculate the average
	MoyenneDebitParTemps= MoyenneDebitParTemps / PlateauLenght;

//Calcul Qee sur le plateau avant inspi 
	// Calculate Qee on the board before inspiration
	Qee_glob = CMP_MeanTable(VEN_PtrMesureFlowPress, PlateauLenght,VEN_MesureFlowQinsp,cPLATEAU_TABLES_LENGHT);

//Calcul de la pente PetitA de la courbe de débit selon regression linéaire	
// PetitA = (Moyenne[debit*temps] - moyenne[temps]*moyenne[débit]) / (Moyenne[temps carré]- carré[temps moyen])
// Pour ajouter de la précision, multiplié par 100
	// 
	// Calculate the slope of the curve PETITA flow according linear regression
	// PETITA = (Average [ flow * time ] - average [ time ] * mean [ speed ] ) / ( Average [ time square ] - square [ mean time ] )
	// To add precision, multiplied by 100 or QeeScale
	PetitA = (MoyenneDebitParTemps - ((SWORD32)PlateauLenght + 1)* 5 * Qee_glob)* QeeScale / MoyenneCarreParCarreMoyenne;

//Gestion de la pente négative, que l'on ignore et force à 0
	// Handle the negative slope, it is unknown and strength 0
	if (PetitA < 0) 
	{
		PetitA = 0;
	}
//Calcul du décalage à l'origine PetitB de la courbe de débit selon regression linéaire
//PetitB = Moyenne [débit] - PetitA * Moyenne[temps]
//On divise le produit de PetitA par 100, cf. ci-dessus.
	//
	// Calculation of offset originally PetitB of the flow curve by linear regression
	// PetitB = Average [ Speed ??] - PETITA * Average [ time ]
	// Product PETITA is divided by 100, cf. above.
	PetitB = Qee_glob  -  PetitA * (PlateauLenght +1 ) * 5 / QeeScale;
    if (PetitB < 0) 
	{
		PetitB = 0;
	}

	Qee = (PetitA * (PlateauLenght / 10 + Increment)) / QeeScale +  PetitB;
	if (Qee < 0)
	{
		Qee = 0;
	}
	//Filtre cinq valeurs de Qee
	// Filter five values Qee
	FiltreQee[Count]=Qee;
	Qee_Courant = Qee;
	Count = Count + 1;
	Count = (UBYTE)(Count % 5);
	if ((Filled == FALSE)&&(Count == 0)) 
	{
		Filled = TRUE; 
	}
	if (Filled == TRUE)
	{
		Qee = (FiltreQee[0] + FiltreQee[1] + FiltreQee[2] + FiltreQee[3] + FiltreQee[4]) / 5;
		if (((Qee - Qee_Courant) * 100 / Qee < -30 )|| ((Qee - Qee_Courant) * 100 / Qee > 30 ))
		{
			Qee = Qee_Courant;
			Count = 0;
			Filled = FALSE;
		}
	}

    VEN_LeakFlowFactorAverage = (Qee * Qee) * 100 / ComputedPeep;

	// Calcul de la fuite theoriquede 4 mm. (avec K=700)
	// Calculate the leak at theoritical 4 mm ID hole. (K = 700)
	QLeakTheoritical4mm = sqrt((double)ComputedPeep);
	QLeakTheoritical4mm = QLeakTheoritical4mm * c4MM_LEAK_COEFF ;

	// Calcul du débit de fuite parasite.
	// Calculate the flow of parasitic leakage 
	QLeak = (SWORD32)(Qee) - (SWORD32) QLeakTheoritical4mm; 
	
	if (QLeak < 0)
	{															  
		QLeak = 0;
	}
	DB_ComputeWrite (COMPUTED_LEAK_U16,(UWORD16)QLeak);
	DB_ComputeWrite (COMPUTED_LEAK_HMI_U16,(UWORD16)QLeak / 10);
	DB_ComputeWrite (COMPUTE_QEE_S16,(UWORD16)Qee);

	// keep these commented out incase these are of interest to someone in future
	//DB_ComputeWrite (COMPUTE_PLATEAULENGTH_U16 , (UWORD16)PlateauLenght);
	//DB_ComputeWrite (COMPUTE_QEE_GLOB_S16 , (UWORD16)Qee_glob);
}
