/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelLanguage.hpp 	 		                             	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_LabelLanguage.cpp   	   	               	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef LabelLanguageH
#define LabelLanguageH
/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_LabelValueString.hpp"
 
/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class LabelLanguage : public LabelValueString
{
private:
   
   /* Parametres */

   UBYTE **ValueName;
   
   /* Methodes */

protected:

   /* Parametres */

   /* Methodes */

public:

   /* Parametres */

   /* Methodes */

   LabelLanguage();

   void SetValue1Name(UBYTE** ValueName);
   virtual UBYTE* GetValue1Name();

};

#endif
