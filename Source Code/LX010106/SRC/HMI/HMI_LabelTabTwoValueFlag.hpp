/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelTabTwoValueFlag.hpp 				   	          	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_LabelTabTwoValueFlag.cpp  		  		      	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef LabelTabTwoValueFlagH
#define LabelTabTwoValueFlagH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_LabelTabTwoValueDefault.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class LabelTabTwoValueFlag: public LabelTabTwoValueDefault
{

private:

   /* Parametres */

   UWORD16 IdFlag1;

   e_TYPE_OF_DB_TARGET DbIdFlag1;

   e_BOOL FlagForDefault1;

   UWORD16 IdFlag2;

   e_TYPE_OF_DB_TARGET DbIdFlag2;

   e_BOOL FlagForDefault2;

   /* Methodes */

protected:
  
   /* Parametres */
  
   /* Methodes */

public:
  
   /* Parametres */
  
   /* Methodes */
  
   LabelTabTwoValueFlag();
  
   void InitDefaultFlag(UBYTE** NameDefaultValue1,
                        UWORD16 IdDefaultValue1,
                        e_TYPE_OF_DB_TARGET DbIdFlag1,
                        e_BOOL FlagForDefault1,
                        UBYTE** NameDefaultValue2,
                        UWORD16 IdDefaultValue2,
                        e_TYPE_OF_DB_TARGET DbIdFlag2,
                        e_BOOL FlagForDefault2);

   void SetIdFlag1(UWORD16 IdFlag1);
   UWORD16 GetIdFlag1();

   void SetDbIdFlag1(e_TYPE_OF_DB_TARGET DbIdFlag1);
   e_TYPE_OF_DB_TARGET GetDbIdFlag1();

   void SetFlagForDefault1(e_BOOL FlagForDefault1);
   e_BOOL GetFlagForDefault1();

   void SetIdFlag2(UWORD16 IdFlag1);
   UWORD16 GetIdFlag2();

   void SetDbIdFlag2(e_TYPE_OF_DB_TARGET DbIdFlag2);
   e_TYPE_OF_DB_TARGET GetDbIdFlag2();

   void SetFlagForDefault2(e_BOOL FlagForDefault2);
   e_BOOL GetFlagForDefault2();

   virtual void SetValue2(UWORD16 Value1);
   virtual void SetValue1(UWORD16 Value1);

   virtual void IncreaseValue();
   virtual void DecreaseValue();
   virtual void ConfirmModifValue(e_BOOL Confirm);
   virtual void StartModifMode();
   virtual void ModifNextValue();
};
//---------------------------------------------------------------------------
#endif
