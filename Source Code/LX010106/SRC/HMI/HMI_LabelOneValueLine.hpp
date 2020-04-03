/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelOneValueSymbol.hpp  	     		                        	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/



/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_LabelOneValueSymbol.cpp     		               	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef LabelOneValueLineH
#define LabelOneValueLineH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_LabelOneValue.hpp"
#include "HMI_SymbolField.hpp"
 
/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class LabelOneValueLine: public LabelOneValue
{

private:

   /* Parametres */

   e_BOOL LineToBeDisplayed;
      

protected:
   
   /* Parametres */

   /* Methodes */

public:

   /* Parametres */

   /* Methodes */

   LabelOneValueLine();

   void Init(	e_SYMBOL Icon, 
   				UBYTE **Name,
   				UWORD16 Line,
   				UWORD16 Col,
   				UWORD16 Value, 
   				UBYTE **NameUnit);

    virtual void Show();
    virtual void Hide();

	void SetLineToBeDisplayed(e_BOOL _ToBeDisplayed);
	e_BOOL GetLineToBeDisplayed();	
 
};

#endif
