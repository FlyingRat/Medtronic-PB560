/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelStringNItems.hpp 	     	   		             	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_LabelStringNItems.cpp    	  			      	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef LabelStringNItemsH
#define LabelStringNItemsH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_LabelValueString.hpp"

#define MAX_ITEMS 10
/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class LabelStringNItems : public LabelValueString
{
private:

   /* Parametres */

   UBYTE **ItemNames[MAX_ITEMS];

   UWORD16 Size; /* doit être < MAX_ITEMS */

   UWORD16 CurrentRank;
   
   /* Methodes */

protected:

   /* Parametres */

   /* Methodes */

public:

   /* Parametres */

   /* Methodes */
   LabelStringNItems();
   LabelStringNItems(UWORD16 _Size);

   void SetSize(UWORD16 _Size);
   
   void SetItem(UWORD16 _Rank, UBYTE** _Item);

   UBYTE* GetItemName(UWORD16 _Rank);
   UBYTE** GetItem(UWORD16 _Rank);   
   virtual UBYTE* GetValue1Name();

   virtual e_BOOL IncreaseValueOk(UWORD16* Val);
   virtual e_BOOL DecreaseValueOk(UWORD16* Val);
};

#endif
