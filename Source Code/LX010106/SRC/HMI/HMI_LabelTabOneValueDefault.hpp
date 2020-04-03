/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelTabOneValue.hpp 	     			   	          	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_LabelTabOneValue.cpp    	  				      	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef LabelTabOneValueDefaultH
#define LabelTabOneValueDefaultH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_LabelTabOneValue.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class LabelTabOneValueDefault: public LabelTabOneValue
{

private:
   
   /* Parametres */

   UWORD16 DefaultValue1;

   UBYTE** NameDefaultValue1;
   
   /* Methodes */

protected:
   //Paramettres
   //Methodes

public:

   /* Parametres */

   /* Methodes */

   LabelTabOneValueDefault();

   void InitDefaultValue(  UBYTE** NameDefaultValue1,
                           UWORD16 DefaultValue1);

   void SetNameDefaultValue1(UBYTE** NameDefaultValue1);
   UBYTE* GetNameDefaultValue1();

   virtual void SetValue1(UWORD16 Value1);
	UWORD16 GetDefaultValue1();

   void SetDefaultValue1(UWORD16 DefaultValue1);   
   UBYTE** GetPtrNameDefaultValue1();

   virtual void RefreshLanguage();

};

#endif
