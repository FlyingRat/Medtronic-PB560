/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelOneValueThreeDefault.hpp 	                   	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_LabelOneValueThreeDefault.cpp  		        	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef LabelOneValueTwoDefaultH
#define LabelOneValueTwoDefaultH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_LabelOneValueDefault.hpp"
 
/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class LabelOneValueThreeDefault: public LabelOneValueDefault
{

private:

   /* Parametres */

   UWORD16 DefaultValue;
   
   UBYTE** NameDefaultValue;
   
   UWORD16 DefaultValue1;
   
   UBYTE** NameDefaultValue1;
   
   UWORD16 DefaultValue2;
   
   UBYTE** NameDefaultValue2;
   
   UWORD16 DisplayValue, DisplayValue1, DisplayValue2;
   
   /* Methodes */

protected:

   /* Parametres */

   /* Methodes */

public:

   /* Parametres */

   /* Methodes */

   LabelOneValueThreeDefault();
   void InitDefaultValue(	UBYTE** NameDefaultValue, 
   								UWORD16 DefaultValue,
                         	UBYTE** NameDefaultValue1, 
                         	UWORD16 DefaultValue1,
                         	UBYTE** NameDefaultValue2, 
                         	UWORD16 DefaultValue2);

   void SetDefaultValue(UWORD16 DefaultValue);
   UWORD16 GetDefaultValue();

   void SetNameDefaultValue(UBYTE** NameDefaultValue);
   UBYTE** GetPtrNameDefaultValue();
   UBYTE* GetNameDefaultValue();

   void SetDefaultValue1(UWORD16 DefaultValue1);
   UWORD16 GetDefaultValue1();

   void SetNameDefaultValue1(UBYTE** NameDefaultValue1);
   UBYTE** GetPtrNameDefaultValue1();
   UBYTE* GetNameDefaultValue1();

   void SetDefaultValue2(UWORD16 DefaultValue2);
   UWORD16 GetDefaultValue2();

   void SetNameDefaultValue2(UBYTE** NameDefaultValue2);
   UBYTE** GetPtrNameDefaultValue2();
   UBYTE* GetNameDefaultValue2();

   virtual void SetValue1(UWORD16 Value1);
   virtual void RefreshLanguage();

};

#endif
