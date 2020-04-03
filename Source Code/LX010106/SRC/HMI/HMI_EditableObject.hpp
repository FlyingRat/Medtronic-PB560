/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_EditableObject.hpp	  		                                	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_EditableObject.cpp	  	                     	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef EditableObjectH
#define EditableObjectH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_Label.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class EditableObject: public Label
{

private:

   /* Parametres */

	/*%C ValueTemp [ 0: ??? ] */
   UWORD16 ValueTemp;

	/*%C IdFlagTemp [ 0: ??? ] */
   UWORD16 IdFlagTemp;
   
	/*%C ValueFlagTemp [ 0: ??? ] */
   UWORD16 ValueFlagTemp;

   e_TYPE_OF_DB_TARGET DbIdFlagTemp;

   /* Methodes */

protected:

   /* Parametres */

   /* Methodes */

public:

   /* Parametres */

   /* Methodes */

   EditableObject();

   void SetValueTemp(UWORD16 ValueTemp);
   UWORD16 GetValueTemp();

   void SetValueFlagTemp(UWORD16 ValueFlagTemp);
   UWORD16 GetValueFlagTemp();

   void SetIdFlagTemp(UWORD16 IdFlagTemp);
   UWORD16 GetIdFlagTemp();

   void SetDbIdFlagTemp(e_TYPE_OF_DB_TARGET DbIdFlagTemp);
   e_TYPE_OF_DB_TARGET GetDbIdFlagTemp();

   virtual void ConfirmModifValue(e_BOOL Confirm);
   virtual void StopModifMode();
   virtual void CancelModifMode();
};

#endif
