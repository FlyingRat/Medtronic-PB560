/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelTabTwoValueDefault.hpp 			   	          	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_LabelTabTwoValueDefault.cpp  		  	      	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef LabelTabTwoValueDefaultH
#define LabelTabTwoValueDefaultH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_LabelTabTwoValue.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class LabelTabTwoValueDefault: public LabelTabTwoValue
{

private:
   
   /* Paramettres */

   UWORD16  DefaultValue1,
            DefaultValue2;
   
   UBYTE**  NameDefaultValue1,
            **NameDefaultValue2;
   
   /* Methodes */

protected:

   /* Paramettres */

   /* Methodes */

public:

   /* Paramettres */

   /* Methodes */

   LabelTabTwoValueDefault();
   void InitDefaultValue(  UBYTE** NameDefaultValue1,
                           UWORD16 DefaultValue1,
                           UBYTE** NameDefaultValue2,
                           UWORD16 DefaultValue2);

   void SetDefaultValue1(UWORD16 DefaultValue1);
   UWORD16 GetDefaultValue1();

   void SetDefaultValue2(UWORD16 DefaultValue2);
   UWORD16 GetDefaultValue2();

   void SetNameDefaultValue1(UBYTE** NameDefaultValue1);
   UBYTE* GetNameDefaultValue1();
	UBYTE** GetPtrNameDefaultValue1();

   void SetNameDefaultValue2(UBYTE** NameDefaultValue2);
   UBYTE* GetNameDefaultValue2();
	UBYTE** GetPtrNameDefaultValue2();

   virtual void SetValue1(UWORD16 Value1);
   virtual void SetValue2(UWORD16 Value2);
   virtual void RefreshLanguage();

};

#endif
