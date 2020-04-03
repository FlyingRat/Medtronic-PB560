/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelOneValueSignDefault.hpp 	                       	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_LabelOneValueSignDefault.cpp  		           	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef LabelOneValueSignDefaultH
#define LabelOneValueSignDefaultH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_LabelOneValueSign.hpp"
 
/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class LabelOneValueSignDefault: public LabelOneValueSign
{

private:
   
   /* Parametres */

   UWORD16 DefaultValue;
   
   UBYTE** NameDefaultValue;
   
   /* Methodes */

protected:
   
   /* Parametres */

   /* Methodes */

public:

   /* Parametres */

   /* Methodes */

   LabelOneValueSignDefault();

   void InitDefaultValue(UBYTE** NameDefaultValue, UWORD16 DefaultValue);
   
   void SetDefaultValue(UWORD16 DefaultValue);
   UWORD16 GetDefaultValue();

   void SetNameDefaultValue(UBYTE** NameDefaultValue);

   UBYTE** GetPtrNameDefaultValue();

   UBYTE* GetNameDefaultValue();

   virtual void SetValue1(UWORD16 Value1);
   virtual void RefreshLanguage();

};

#endif
