/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_DisplayObject.hpp	   	                                	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_DisplayObject.cpp	    	                    	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef DisplayObjectH
#define DisplayObjectH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

extern "C"
{
#include "typedef.h"
#include "enum.h"
}
#include "HMI_MenuObject.hpp"

#define DISP_OBJ_MAX_CHAR 30

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class DisplayObject: public MenuObject
{
private:

   /* Parametres */
   
   DisplayObject *Parent;

	/*%C Line [ 0: ??? ] */
   UWORD16 Line;
   
   /*%C Col [ 0: ??? ] */
   UWORD16 Col;

	/*%C Page [ 0: ??? ] */
   UWORD16 Page;

   e_BOOL Visible;

   e_BOOL RefreshE;

   /* Methodes */

protected:

   /* Parametres */

   /* Methodes */

public:

   /* Parametres */

   static UWORD16 Language;
   static e_BOOL EndOfInit;
   static char StringValue1[DISP_OBJ_MAX_CHAR];
   static char StringValue2[DISP_OBJ_MAX_CHAR];   

   /* Methodes */

   DisplayObject();
   
   virtual void SetLine(UWORD16 Line);
	UWORD16 GetLine();   

   virtual void SetCol(UWORD16 Col);
	UWORD16 GetCol();

	void SetPage(UWORD16 Page);
	UWORD16 GetPage();

   virtual UWORD16 GetFullValue();

   void SetParent(DisplayObject *Parent);
   DisplayObject* GetParent();

  	void Init(UWORD16 Line, UWORD16 Col);
   virtual void SetVisible(e_BOOL V);
   virtual void SetForcedVisible(e_BOOL V);   
   void RefreshEnable(e_BOOL RefreshE);

   e_BOOL IsVisible();
   e_BOOL IsRefreshObject();
   e_BOOL HaveParent();

   virtual void Refresh();
   virtual void Show();
   virtual void Hide();
   virtual void Blink(e_BOOL Actif);
   virtual void RefreshLanguage();
   virtual void StopMonitoringMode();
   virtual void FreezeMonitoringMode();
   virtual void StartMonitoringMode();
   virtual void FreezeMonitoringModeImpactDisplay(e_BOOL _DisplayFlag);
   virtual void StartMonitoringModeImpactDisplay(e_BOOL _DisplayFlag);
   virtual void StopMonitoringModeImpactDisplay(e_BOOL _DisplayFlag);   
   virtual void SetLanguage(UWORD16 Lang);
   virtual UWORD16 GetLanguage();
  	virtual void SetEndOfInit(e_BOOL _EndOfInit);
	virtual e_BOOL GetEndOfInit();

   virtual UBYTE* GetName();
   virtual UBYTE* GetStringValue1();
   virtual UBYTE* GetStringValue2();      
   virtual UBYTE* GetUnit1();
   virtual UBYTE* GetUnit2();

};

#endif
