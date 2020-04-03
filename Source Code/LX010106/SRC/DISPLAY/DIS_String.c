/*****************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : DIS_String.c */
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
#include "DB_Config.h"
#include "DIS_String.h"
#include "enum.h"
			
UBYTE GetFontNameFromLang(UBYTE _Font, e_HMI_LANG _Lang);
/******************************************************************************/
/*                            FUNCTION BODY                                   */
/******************************************************************************/

void DIS_String( UBYTE *str
					, UBYTE font
					, SWORD16 line
					, UWORD16 column
					, UBYTE printon
					, UBYTE page )
{
UBYTE _FontName = font & ~INV;
UWORD16 _CurrentLang = DB_ConfigRead(ADJUST_LANGUAGE_U16);

// Déplacement de l'origine caractère en bas à gauche
switch(_FontName)
{
	case ARIAL9:
		if(_CurrentLang == HMI_LANG_CHINESE)
		{
			if(
            	(str[0]<= 0x24) ||
            	(str[0]== 0x26) ||
            	(str[0]== 0x27) ||
            	(str[0]== 0x2A) ||
            	(str[0]== 0x2C) ||
            	((str[0]>= 0x3B)&&(str[0]<= 0x3D)) ||
            	(str[0]== 0x40) ||
	            (str[0]== 0x44) ||
            	(str[0]== 0x47) ||
            	((str[0]>= 0x4A)&&(str[0]<= 0x4C)) ||
            	(str[0]== 0x4E) ||
            	(str[0]== 0x51) ||
            	((str[0]>= 0x58)&&(str[0]<= 0x60)) ||
				(str[0]== 0x71) ||
    	        (str[0]== 0x7B) ||
	            ((str[0]>= 0x7D)&&(str[0]<= 0xAF)) ||
        	    (str[0]>= 0xB2) ||
				((str[0] == '1') && (str[1] == '0')&& (str[2] == '0')&& (str[3] == '%')) ||
            	((str[0] == '2') && (str[1] == '4')&& (str[2] == 'V'))                     /* 24V Failure */
            	)
            {
				/* C'est un symbole chinois */ 
				line -= 11;
			}
			else
			{
				/* 	C'est un symbole alphanum, on passe en anglais
					pour pointer vers la police Gen2 Europ */
				_CurrentLang = HMI_LANG_ENGLISH;
				line -= 9;
			}
		}
		else
			line -= 9;
	break;
	case ARIALBLACK11:
		line -= 13;
	break;
	case ARIAL8:
		line -= 9;
	break;
	case ARIALBOLD29:
		line -= 34;
	break;
	default:
		line -= 13;
	break;
}

// Mise à jour du paramètre de fonte suivant la langue
font = GetFontNameFromLang(font, _CurrentLang);

// Interdit les lignes négatives
if (line < 1)
{
	line = 1;
}

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

DRV_DIS_grString ( (font & ~INV)
						, column-1
						, (UBYTE)line-1
						, (UBYTE *)str
						, ~printon ) ;
}
/*---------------------------------------------------------------*/
UBYTE GetFontNameFromLang(UBYTE _Font, e_HMI_LANG _Lang)
{   
	UBYTE _ReturnedFont = _Font & INV;
	UBYTE _FontName = _Font & ~INV;	 

   	switch(_FontName)
   	{
		default :
    	case ARIAL8 :		
		case ARIALBOLD29 :
		case ARIALBLACK11 :
			_ReturnedFont |= _FontName;
		break;

      	case ARIAL9 :      	
        	switch(_Lang)
        	{
           		default :
           			_ReturnedFont |= _FontName;
        		break;
            	case HMI_LANG_KOREAN :
            	case HMI_LANG_GREEK :
               		_ReturnedFont |= ARIAL9_KOREAN_GREEK;
            	break;
            	case HMI_LANG_JAPANESE :
         	      	_ReturnedFont |= ARIAL9_JAPANESE;
            	break;
            	case HMI_LANG_CHINESE :
            	   	_ReturnedFont |= ARIAL9_CHINESE;
            	break;
         	}
      		break;      	      	
   	}

   	return(_ReturnedFont);
}
