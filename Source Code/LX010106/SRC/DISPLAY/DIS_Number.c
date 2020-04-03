/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DIS_Number.c */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                  */
/******************************************************************************/
/*%I Input Parameter :  NONE                                            */
/*%IO Input/Output :    NONE	                                              */
/*%O Output Parameter : NONE       */
/******************************************************************************/

/******************************************************************************/
/*                                INCLUDE FILES		                          */
/******************************************************************************/

#include "typedef.h"
#include "Driver_Display_Data.h"
#include "DIS_Number.h"
			 
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DIS_Number( SWORD32 value
					, UBYTE nature
					, SWORD16 line
					, UWORD16 column
					, UBYTE font
					, UBYTE nbdigit
					, UBYTE zero
					, UBYTE printon
					, UBYTE page )
{
UBYTE string[12];

SWORD32 temp_value;
SBYTE i,j;

// Mémorisation de la valeur  
temp_value = value;
// Test si value négative travail sur une valeur positive uniquement
if (value < 0)
	{
	// Complément à 2
	temp_value--;
	temp_value = ~temp_value;
	}

// Déplacement de l'origine caractère en bas à gauche
if ((font & ~INV) == ARIAL9)
{
	line -= 9;
}
else if ((font & ~INV) == ARIALBLACK11) 
{
	line -= 13;
}
else if ((font & ~INV) == ARIAL8) 
{
	line -= 9;
}
else if ((font & ~INV) == ARIALBOLD29) 
{
	line -= 34;
}
// Interdit les lignes négatives
if (line < 1) line = 1;

DRV_DIS_grSetPage ( page-1 ) ;

if ( font & INV )
	{	
	DRV_DIS_grNegative(1) ;
	DRV_DIS_grSetColor ( ON ) ;
	}
else
	{
	DRV_DIS_grNegative(0) ;
	DRV_DIS_grSetColor ( OFF ) ;
	}

if (zero == OFF)
	{
	// affichage entier positif ou négatif
   if (nature == INTEGER)
		{          
		// positionne la fin de caractère
		string[10] = '\0';
		// Recherche des caractères valides
		for(i = 9; i >= 0  ;i--)
			{
			string[i] = (UBYTE)(temp_value%10 + 48);
			temp_value /= 10;
			if (temp_value == 0) break;
			}

		// Test si valeur négative - Rajout du "-" devant le chiffre
		if (value < 0) string[--i] = '-';

		// Réordonne le tablaeau de string
		for(j = i; j <= 10  ;j++)
			{
			string[j-i] = string[j];
			}
		}	
	// affichage décimal positif ou négatif
	else
		{
		// positionne la fin de caractère
		string[10] = '\0';

		// recherche de la décimale
		string[9] = (UBYTE)(temp_value%10 + 48);
		// Suppression de la décimale
		temp_value /= 10;
		// Affichage du séparateur
		string[8] = '.';
		
		// Recherche des caractères valides
		for(i = 7; i >= 0  ;i--)
			{
			string[i] = (UBYTE)(temp_value%10 + 48);
			temp_value /= 10;
			if (temp_value == 0) break;
			}

		// Test si valeur négative - Rajout du "-" devant le chiffre
		if (value < 0) string[--i] = '-';

		// Réordonne le tablaeau de string
		for(j = i; j <= 10  ;j++)
			{
			string[j-i] = string[j];
			}
		}
	}
// Zero = ON - Sans possibilité de valeur négative
else
	{
		// positionne la fin de caractère
		string[nbdigit] = '\0';
		// Recherche des caractères valides
		for(i = nbdigit-1; i >= 0  ;i--)
			{
			string[i] = (UBYTE)(temp_value%10 + 48);
			temp_value /= 10;
			}
	}

DRV_DIS_grString ( (font & ~INV), column-1, (UBYTE)line-1, string, ~printon ) ;

}
