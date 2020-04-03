/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelRatioTrunk.hpp 						   	          	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_LabelRatio.cpp  				  		      	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef LabelRatioTrunkH
#define LabelRatioTrunkH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_LabelRatio.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class LabelRatioTrunk: public LabelRatio
{

private:
   
	/* Parametres */
   e_BOOL Threshold;

   /* Methodes */
   void SetAllVisible(e_BOOL _Visible);
   void ShowAll();

protected:

   /* Parametres */

   /* Methodes */

public:

   /* Parametres */

   /* Methodes */

   LabelRatioTrunk();

   void Init(  e_SYMBOL Icon,
               UBYTE **Name,
               UWORD16 Line,
               UWORD16 Col,
               UWORD16 Value1,
               UBYTE **NameUnit1,
               UWORD16 Value2,
               UBYTE **NameUnit2);

   void RefreshValueColumn();
   virtual void SetValueState(UWORD16 ValueState);
   virtual void IncreaseValue();
   virtual void DecreaseValue();
   virtual void StartModifMode();
   virtual void Refresh();      
   virtual void ConfirmModifValue(e_BOOL Confirm);
   virtual e_BOOL IncreaseValueOk(UWORD16* Val);
   virtual e_BOOL DecreaseValueOk(UWORD16* Val);
   virtual void HideAll();
   
};

#endif
