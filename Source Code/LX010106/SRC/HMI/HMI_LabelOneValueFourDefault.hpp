/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelOneValueFourDefault.hpp 	                   	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_LabelOneValueFourDefault.cpp  		        	   */
/*%C			                                                                  */
/******************************************************************************/

#ifndef LabelOneValueFourDefaultH
#define LabelOneValueFourDefaultH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_LabelOneValueDefault.hpp"
 
/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class LabelOneValueFourDefault: public LabelOneValueDefault
{

private:

   /* Parametres */

   UWORD16 DefaultValue;
   
   UBYTE** NameDefaultValue;
   
   UWORD16 DefaultValue1;
   
   UBYTE** NameDefaultValue1;
   
   UWORD16 DefaultValue2;

   UBYTE** NameDefaultValue2;

   UWORD16 DefaultValue3;

   UBYTE** NameDefaultValue3;

   UWORD16 DisplayValue;

   UWORD16 DisplayValue1;

   UWORD16 DisplayValue2;

   UWORD16 DisplayValue3;

   /* Methodes */

protected:

   /* Parametres */

   /* Methodes */

public:

   /* Parametres */

   /* Methodes */

   LabelOneValueFourDefault();
   void InitDefaultValue(  UBYTE** _NameDefaultValue,
                      UWORD16 _DefaultValue,
                      UBYTE** _NameDefaultValue1,
                      UWORD16 _DefaultValue1,
                      UBYTE** _NameDefaultValue2,
                      UWORD16 _DefaultValue2,
                      UBYTE** _NameDefaultValue3,
                      UWORD16 _DefaultValue3);

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

   void SetDefaultValue3(UWORD16 DefaultValue3);
   UWORD16 GetDefaultValue3();

   void SetNameDefaultValue3(UBYTE** NameDefaultValue3);
   UBYTE** GetPtrNameDefaultValue3();
   UBYTE* GetNameDefaultValue3();

   virtual void SetValue1(UWORD16 Value1);
   virtual void RefreshLanguage();

};
#endif
