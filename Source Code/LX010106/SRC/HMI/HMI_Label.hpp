/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_Label.hpp	 			  		                             	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_Label.cpp  	   		   	               	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef LabelH
#define LabelH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_DisplayObject.hpp"      
#include "HMI_Loupe.hpp"
#include "HMI_SymbolField.hpp"
#include "HMI_TextField.hpp"
 
/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class Label: public DisplayObject
{

private:

   /* Parametres */

   e_SYMBOL PreviousIcon;

   UBYTE **Name;

   Loupe *LoupeObject;

   SymbolField FIcon;

   TextField FLabel;

   e_BOOL Centered;

   /* Methodes */

protected:

   /* Parametres */

   /* Methodes */

public:

   /* Parametres */
   
   static UWORD16 Language;

   /* Methodes */

   Label();

   void Init(  e_SYMBOL Icon,
               UBYTE **Name,
               UWORD16 Line,
               UWORD16 Col);

   static void SetNbLanguage(UWORD16 NbLang);
   static UWORD16 GetNbLanguage();

   void SetPreviousIcon(e_SYMBOL PreviousIcon);
   e_SYMBOL GetPreviousIcon();

   void SetCentered(e_BOOL _Centered);
   e_BOOL GetCentered();

	void SetName(UBYTE** Name);
   virtual UBYTE* GetName();
   UWORD16 GetPixelSize();
   virtual UWORD16 GetEndCol();

   void SetIcon(e_SYMBOL Icon);
	SymbolField* GetFIcon();

   void SetColLabel(UWORD16 ColLabel);
   UWORD16 GetColLabel();   
	UBYTE** GetPtrName();

   void SetFontLabel(UWORD16 FontLabel);
   UWORD16 GetFontLabel();
   TextField* GetFLabel();
 
	virtual void SetLoupe(Loupe *LoupeObject);
	virtual Loupe* GetLoupe();
 
   virtual void SetInvertVideo(e_BOOL InvertVideo);
   virtual void Lock(e_BOOL Lock);
   virtual void Show();
   virtual void Hide();
   virtual void Blink(e_BOOL Actif);
   virtual void WinFocus();
   virtual void LoseFocus();
   virtual void StartModifMode();
   virtual void StopModifMode();
   virtual void CancelModifMode();
   virtual void RefreshLanguage();

};

#endif
