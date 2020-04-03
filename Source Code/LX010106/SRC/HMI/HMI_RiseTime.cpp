/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_RiseTime.cpp 										 						*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Affichage d'une pente	 													 			  	*/
/*		                                                                   	 	*/
/******************************************************************************/


/******************************************************************************/
/*                           HEADER INCLUDE FILE		                        */
/******************************************************************************/

#include "HMI_RiseTime.hpp"
				 
/******************************************************************************/
/*                           OTHER INCLUDE FILE		                	   		*/
/******************************************************************************/
extern "C"
{
#include "stdfile.h"
}

/******************************************************************************/
/*                           CONSTRUCTEUR/DESTRUCTEUR                			*/
/******************************************************************************/
RiseTime::RiseTime():LabelSymbol()
{

}

/******************************************************************************/
/*                           ACCESSEURS				                	   		*/
/******************************************************************************/
UBYTE* RiseTime::GetStringValue1()
{
#ifdef  _BORLAND
   switch(GetSymbol())
   {
      default        :
      case RISETIME1    :
         sprintf(	DisplayObject::StringValue1,"%s", "RISETIME1");
         break;
      case RISETIME2    :
         sprintf(	DisplayObject::StringValue1,"%s", "RISETIME2");
         break;
      case RISETIME3    :
         sprintf(	DisplayObject::StringValue1,"%s", "RISETIME3");
         break;
      case RISETIME4    :
         sprintf(	DisplayObject::StringValue1,"%s", "RISETIME4");
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
/*%C Convertion int / symbole	 																*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																            		*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
e_SYMBOL RiseTime::IntToSymbol(UWORD16 _Val)
{
	(void)this; /* to avoid w68 compilation warning (parameter "this" not used) */
   	switch(_Val)
   	{
      	case 1 : return RISETIME1;
      	case 2 : return RISETIME2;
      	case 3 : return RISETIME3;
      	case 4 : return RISETIME4;
      	default: return RISETIME1;
   	}
}

/******************************************************************************/
/*%C                       Functionnal description :                      		*/
/*%C                                                                          */
/*%C Convertion symbole / int	 															  	*/
/*%C                                                                         	*/
/*%I Input Parameter : 																			*/
/*%I		NONE																            		*/
/*%IO Input/Output : 																			*/
/*%IO		NONE																					  	*/
/*%O Output Parameter : 																	 	*/
/*%O 		NONE								  														*/
/******************************************************************************/
UWORD16 RiseTime::SymbolToInt()
{
   switch(GetSymbol())
   {
      case RISETIME1 : return 1;
      case RISETIME2 : return 2;
      case RISETIME3 : return 3;
      case RISETIME4 : return 4;
      default        : return 1;
   }
}
