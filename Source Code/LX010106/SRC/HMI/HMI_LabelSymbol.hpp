/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelOneValueTrig.hpp 	      			             	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_LabelOneValueTrig.cpp  		  			      	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef LabelSymbolH
#define LabelSymbolH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_Label.hpp"
#include "HMI_EditableObject.hpp"
#include "HMI_SymbolField.hpp"
 
/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class LabelSymbol: public EditableObject
{

private:

   /* Parametres */

   SymbolField FSymbol;

   TextField FTextUnderSymbol;

   e_BOOL UsedTextUnderSymbol;

   TextField FSep;

   /* Methodes */

   void SetUsedTextUnderSymbol(e_BOOL _UsedTextUnderSymbol);

   e_BOOL IsUsedTextUnderSymbol();
   
protected:

   /* Parametres */

   /* Methodes */

public:
 
   /* Parametres */

   /* Methodes */
 
   LabelSymbol();
 
   void Init(  e_SYMBOL Icon,
               UBYTE **Name,
               UWORD16 Line,
               UWORD16 Col,
               e_SYMBOL Symbol);

   void SetSep(UBYTE *Sep);
   UBYTE* GetSep();
 
   void SetSymbol(e_SYMBOL Symbol);
   e_SYMBOL GetSymbol();
 
   void SetColSymbol(UWORD16 ColSymbol);
   UWORD16 GetColSymbol();
 
   void SetColSep(UWORD16 ColSep);
   UWORD16 GetColSep();
 
   virtual e_SYMBOL IntToSymbol(UWORD16 Val);
 
   virtual UWORD16 SymbolToInt();

   virtual void ConfirmModifValue(e_BOOL Confirm);
   virtual void Refresh();
   virtual void Show();
   virtual void Hide();
   virtual void Blink(e_BOOL Actif);
   virtual void IncreaseValue();
   virtual void DecreaseValue();
   virtual void StartModifMode();

   virtual e_BOOL IncreaseValueOk(UWORD16* Val);
   virtual e_BOOL DecreaseValueOk(UWORD16* Val);
 
   TextField* GetFSep();

};

#endif
