/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelLanguage.hpp 	 		                             	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_LabelLanguage.cpp   	   	               	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef LabelModeH
#define LabelModeH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

//#include "DataBase.h"
#include "HMI_Label.hpp"
#include "HMI_TextField.hpp"
 
/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class LabelMode : public Label
{
private:

   /* Parametres */
 
   TextField   FNominalMode,
               FModifMode,
               FStateModifMode,
               FActifMode,
               FStateActifMode,
               FSep;

   UBYTE **NameMode,
         **NameMode2,
         **NameMode3,
         **ActifName,
         **NoActifName;

   e_MODE_TYPES   ActifMode,
                  ModifMode;

   e_BOOL   NominalMode,
            NameMode2Display,
            InModification;

   /* Methodes */

protected:
   
   /* Parametres */

   /* Methodes */

public:
   
   /* Parametres */

   /* Methodes */

   LabelMode();

   UBYTE* GetNameMode3(e_MODE_TYPES Mode);
   UBYTE* GetNameMode2(e_MODE_TYPES Mode);
   UBYTE* GetNameMode(e_MODE_TYPES Mode);
//   UBYTE* GetNameNominalMode(e_MODE_TYPES Mode);
  
   void SetNameMode( UBYTE** NameMode,
                     UBYTE** NameMode2,
                     UBYTE** NameMode3,
                     UBYTE** ActifName,
                     UBYTE** NoActifName);

   void SetActifMode(e_MODE_TYPES ActifMode);
   e_MODE_TYPES GetActifMode(void);
  
   void SetModifMode(e_MODE_TYPES ModifMode);
   e_MODE_TYPES GetModifMode(void);

 	void SetNominalMode(e_BOOL NominalMode);
	UBYTE* GetNameNominalMode(e_MODE_TYPES Mode);
  
   void SetNominalValue(UBYTE* ModeName);
  	e_BOOL IsNominalMode();
   
   void SetNameMode2Display(e_BOOL NameMode2Display);
   e_BOOL IsNameMode2Display();
   
   void SetInModification(e_BOOL InModification);
   e_BOOL IsInModification();

   void ShowNominalView();
   void ShowMultiModeView();
 
   virtual void Lock(e_BOOL Lock);
   virtual void Show();
   virtual void Hide();
   virtual void Blink(e_BOOL Actif);
   virtual void Refresh();
   virtual void IncreaseValue();
   virtual void DecreaseValue();
   virtual void StartModifMode();
   virtual void StopModifMode();
   virtual void CancelModifMode();
   virtual void RefreshLanguage();

 	virtual e_BOOL IncreaseValueOk(UWORD16* Val);
   virtual e_BOOL DecreaseValueOk(UWORD16* Val);

};

#endif
