/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_Rampe.cpp 		 	  								 						*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Affichage d'une Rampe	 													 			  	*/
/*		                                                                   	 	*/
/******************************************************************************/


/******************************************************************************/
/*                           HEADER INCLUDE FILE		                        */
/******************************************************************************/

#include "HMI_Rampe.hpp"
				 
/******************************************************************************/
/*                           OTHER INCLUDE FILE		                	   		*/
/******************************************************************************/

extern "C"
{
#include "enum.h"
#include "stdfile.h"
}
/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
Rampe::Rampe():LabelSymbol()
{

}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
UBYTE* Rampe::GetStringValue1()
{
#ifdef  _BORLAND
   switch(GetSymbol())
   {
      case RAMPE3    :
         sprintf(	DisplayObject::StringValue1,"%s", "SINUS");
         break;
      default        :
      case RAMPE2    :
         sprintf(	DisplayObject::StringValue1,"%s", "DECELERATED");
         break;
      case RAMPE1    :
         sprintf(	DisplayObject::StringValue1,"%s", "RECTANGLE");
         break;
   }

   return((UBYTE* ) DisplayObject::StringValue1);
#else
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
   	return((UBYTE* )"");
#endif
}
/******************************************************************************/
/*                           METHODES                					      		*/
/******************************************************************************/

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Convertion int / symbole  																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																            		*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
e_SYMBOL Rampe::IntToSymbol(UWORD16 _Val)
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
   	switch(_Val)
   	{
      	case RAMP_DECELERATED : return RAMPE2;

      	case RAMP_RECTANGLE   : return RAMPE1;

      	case RAMP_SINUS       : return RAMPE3;

      	default: return RAMPE2;
   	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C  Convertion symbole / int		  														*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																            		*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
UWORD16 Rampe::SymbolToInt()
{
   switch(GetSymbol())
   {
      case RAMPE3    : return RAMP_SINUS;
      case RAMPE2    : return RAMP_DECELERATED;
      case RAMPE1    : return RAMP_RECTANGLE;
      default        : return RAMP_DECELERATED;
   }
}

