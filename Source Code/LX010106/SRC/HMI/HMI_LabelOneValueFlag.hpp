/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelOneValueFlag.hpp 	 		                          	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_LabelOneValueFlag.cpp  	    		           	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef LabelOneValueFlagH
#define LabelOneValueFlagH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_LabelOneValueDefault.hpp"
 
/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/
 
 class LabelOneValueFlag: public LabelOneValueDefault
{

private:
   
   /* Parametres */

   UWORD16 IdFlag;

   e_TYPE_OF_DB_TARGET DbIdFlag;

   e_BOOL FlagForDefault;

   /* Methodes */

protected:
   
   /* Parametres */
   
   /* Methodes */

public:

   /* Parametres */
   
   /* Methodes */

   LabelOneValueFlag();

   void InitDefaultFlag(UBYTE** NameDefaultValue,
                        UWORD16 IdDefaultValue,
                        e_TYPE_OF_DB_TARGET DbIdFlag,
                        e_BOOL FlagForDefault);

   void SetIdFlag(UWORD16 IdFlag);
   UWORD16 GetIdFlag();

   void SetDbIdFlag(e_TYPE_OF_DB_TARGET DbIdFlag);
   e_TYPE_OF_DB_TARGET GetDbIdFlag();

   void SetFlagForDefault(e_BOOL FlagForDefault);
   e_BOOL GetFlagForDefault();

   virtual void ConfirmModifValue(e_BOOL Confirm);
   virtual void SetValue1(UWORD16 Value1);
   virtual void IncreaseValue();
   virtual void DecreaseValue();
   virtual void StartModifMode();
};

#endif
