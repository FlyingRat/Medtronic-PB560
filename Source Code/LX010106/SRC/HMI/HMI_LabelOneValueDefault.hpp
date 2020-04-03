/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelOneValueDefault.hpp 	 	                          	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_LabelOneValueDefault.cpp  	               	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef LabelOneValueDefaultH
#define LabelOneValueDefaultH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_LabelOneValue.hpp"
 
/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class LabelOneValueDefault: public LabelOneValue
{

private:
   
   /* Parametres */

   UWORD16 DefaultValue;
   
   UBYTE** NameDefaultValue;
   
   /* Methodes */

protected:
   
   /* Parametres */

   /* Methodes*/

public:
   
   /* Parametres */

   /* Methodes */

   LabelOneValueDefault();
   
   void InitDefaultValue(UBYTE** NameDefaultValue, UWORD16 DefaultValue);

   void SetDefaultValue(UWORD16 DefaultValue);
   UWORD16 GetDefaultValue();

   void SetNameDefaultValue(UBYTE** NameDefaultValue);
   UBYTE* GetNameDefaultValue();

   UBYTE** GetPtrNameDefaultValue();
   virtual void SetValue1(UWORD16 Value1);

   virtual void RefreshLanguage();

};

#endif
