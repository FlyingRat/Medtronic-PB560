/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_Loupe.hpp 		  							   	          	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_Loupe.cpp 		 					  		      	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef LoupeH
#define LoupeH


/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "typedef.h"
#include "HMI_Tools.hpp"
#include "HMI_DisplayObject.hpp"
#include "HMI_ValueField.hpp"
#include "HMI_TextField.hpp"
#include "HMI_GraphicBox.hpp"
#include "HMI_MessageDialog.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

typedef enum 
{
	eValue,
	eString,
	eValueSign
} DataType;

class Loupe: public DisplayObject
{
private:
   /* Parametres */
   TextField   FValueS;

   ValueField FValueI;

   e_BOOL   StringValue,
            HaveText;

   DataType Dtype;

   /* Methodes */
   UWORD16 GetFloat();

protected:
   
   /* Parametres */

   MessageDialog Message;

	GraphicBox MonitorBox;
   
   /* Methodes */

public:
   
   /* Parametres */

   /* Methodes */

   Loupe();
   
   UWORD16 GetValue();

   void SetColValue(UWORD16 ColValue);   
   void SetLineValue(UWORD16 LineValue);
   void SetValue(UWORD16 Value);
   void SetValue(UWORD16 Value, UWORD16 dec);
   void SetValue(UBYTE *ValueString);
   void SetValue(UBYTE *Sign, UWORD16 Value);
   void SetValue(UBYTE *Sign, UWORD16 Value, UWORD16 dec);
	
	/* Can used for SetFText Accessor */
   void SetMessage(UBYTE *Text);
   
   DataType GetDataType();
   void SetDataType(DataType Type);
   
   e_BOOL IsHaveMessage();
   void DisplayMessage(e_BOOL Val);

   TextField* GetFValueS();
   
   ValueField* GetFValueI();
   
   virtual void Show();
   virtual void Hide();
   virtual void Format(DataType Type);
   virtual void Blink(e_BOOL Actif);
};

#endif
