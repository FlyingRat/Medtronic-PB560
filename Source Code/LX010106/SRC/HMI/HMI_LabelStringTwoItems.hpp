/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelStringTwoItems.hpp 	     			             	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_LabelStringTwoItems.cpp    	  			      	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef LabelStringTwoItemsH
#define LabelStringTwoItemsH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_LabelValueString.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class LabelStringTwoItems : public LabelValueString
{
private:

   /* Parametres */

   UBYTE **Item1Name,
         **Item2Name;
   
   /* Methodes */

protected:

   /* Parametres */

   /* Methodes */

public:

   /* Parametres */

   /* Methodes */

   LabelStringTwoItems();
   
   void SetItem1Name(UBYTE** Item1Name);
   
   UBYTE* GetItem1Name();
   virtual UBYTE* GetValue1Name();
    
   UBYTE* GetItem2Name();
   void SetItem2Name(UBYTE** Item2Name);
  	   
   virtual e_BOOL IncreaseValueOk(UWORD16* Val);
   virtual e_BOOL DecreaseValueOk(UWORD16* Val);
};

#endif
