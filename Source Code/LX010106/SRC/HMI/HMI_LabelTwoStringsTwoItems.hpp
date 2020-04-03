/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelTwoStringsTwoItems.hpp 	     			             	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_LabelTwoStringsTwoItems.cpp    	  			   */
/*%C			                                                                  */
/******************************************************************************/

#ifndef LabelTwoStringsTwoItemsH
#define LabelTwoStringsTwoItemsH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/
#include "HMI_LabelValueString.hpp"
#include "HMI_LabelStringTwoItems.hpp"
#include "HMI_LabelTwoStringsTwoItems.hpp"

typedef void (*T_CallBackPtr) (void);
/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class LabelTwoStringsTwoItems : public LabelStringTwoItems
{
private:

   /* Parametres */

   UBYTE **Value2Item1Name,
         **Value2Item2Name;

   TextField FValue2;

   TextField FSep2;

   UWORD16 IntValue2;

   UWORD16 ValueState;

   UWORD16 IdParam2;

   e_TYPE_OF_DB_TARGET DbTarget2;

   T_CallBackPtr CallBackPtr;

   /* Methodes */

protected:

   /* Parametres */

   /* Methodes */

public:

   /* Parametres */

   /* Methodes */
   LabelTwoStringsTwoItems();

   void SetColValue2(UWORD16 _Col);
   void SetColSep2(UWORD16 _Col);

   T_CallBackPtr GetCallBackPtr();
   void SetCallBackPtr(T_CallBackPtr _CallBackPtr);     

   void SetIdParam2(UWORD16 _IdParam2);
   UWORD16 GetIdParam2();

   void SetDbTarget2(e_TYPE_OF_DB_TARGET _DbTarget2);
   e_TYPE_OF_DB_TARGET GetDbTarget2();

   void SetIntValue2(UWORD16 _IntValue2);
   UWORD16 GetIntValue2();

   UWORD16 GetValueState();
   void SetValueState(UWORD16 _ValueState);

   void SetValue2Item1Name(UBYTE** _Value2Item1Name);
   UBYTE* GetValue2Item1Name();

   void SetValue2(UBYTE* _Value2);
   UBYTE* GetValue2();      

   void SetValue2Item2Name(UBYTE** _Value2Item2Name);
   UBYTE* GetValue2Item2Name();
   
   UBYTE* GetValue2Name();

   virtual UWORD16 GetFullValue();   

   void SetFontValue2(UWORD16 _FontValue2);
   UWORD16 GetFontValue2();

   void SetInvertVideo(e_BOOL _InvertVideo);

   void Init(  e_SYMBOL _Icon,
					UBYTE **_Name,
					UWORD16 _Line,
					UWORD16 _Col,
               UWORD16 _Value1,
               UWORD16 _Value2
               );

   void InitDbAccess(   UWORD16 _IdParam,
								e_TYPE_OF_DB_TARGET _DbTarget,
								UWORD16 _IdParam2,
								e_TYPE_OF_DB_TARGET _DbTarget2);


   void ModifNextValue();
   void ConfirmModifValue(e_BOOL _Confirm);
   void StartModifMode();

   void DecreaseValue();
   e_BOOL DecreaseValueOk(UWORD16* _Val);

   void IncreaseValue();
   e_BOOL IncreaseValueOk(UWORD16* _Val);

   void Blink(e_BOOL _Actif);
   void Hide();
   void Show();
   void Refresh();   


   void RefreshValue2();
   void RefreshValue1();
};

#endif
