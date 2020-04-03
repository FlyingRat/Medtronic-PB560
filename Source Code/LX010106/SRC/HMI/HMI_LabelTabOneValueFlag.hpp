/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelTabOneValueFlag.hpp 	   		   	          	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_LabelTabOneValueFlag.cpp    	  	  	      	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef LabelTabOneValueFlagH
#define LabelTabOneValueFlagH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_LabelTabOneValueDefault.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class LabelTabOneValueFlag: public LabelTabOneValueDefault
{

private:

	/* Parametres */

   UWORD16 IdFlag1;
   
   e_TYPE_OF_DB_TARGET DbIdFlag1;
   e_BOOL FlagForDefault1;
   
   /* Methodes */

protected:

	/* Parametres */

   /* Methodes */

public:

	/* Parametres */

   /* Methodes */

   LabelTabOneValueFlag();

   void InitDefaultFlag(UBYTE** NameDefaultValue1,
                        UWORD16 IdDefaultValue1,
                        e_TYPE_OF_DB_TARGET DbIdFlag1,
                        e_BOOL FlagForDefault1);

   void SetIdFlag1(UWORD16 IdFlag1);
   UWORD16 GetIdFlag1();

   void SetDbIdFlag1(e_TYPE_OF_DB_TARGET DbIdFlag1);
   e_TYPE_OF_DB_TARGET GetDbIdFlag1();

   void SetFlagForDefault1(e_BOOL FlagForDefault1);
   e_BOOL GetFlagForDefault1();

   virtual void SetValue1(UWORD16 Value1);
   virtual void IncreaseValue();
   virtual void DecreaseValue();
   virtual void ConfirmModifValue(e_BOOL Confirm);
   virtual void StartModifMode();

};

#endif
