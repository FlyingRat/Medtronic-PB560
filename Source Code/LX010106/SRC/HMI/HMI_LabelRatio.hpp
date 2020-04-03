/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelRatio.hpp 						   	          	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_LabelRatio.cpp  				  		      	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef LabelRatioH
#define LabelRatioH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_LabelTwoValue.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class LabelRatio: public LabelTwoValue
{

private:
   
	/* Parametres */

   UWORD16 Value2Temp;

   /* Methodes */

protected:

   /* Parametres */

   /* Methodes */

public:

   /* Parametres */

   /* Methodes */

   LabelRatio();

   void Init(  e_SYMBOL Icon,
               UBYTE **Name,
               UWORD16 Line,
               UWORD16 Col,
               UWORD16 Value1,
               UBYTE **NameUnit1,
               UWORD16 Value2,
               UBYTE **NameUnit2);

   void SetValue2Temp(UWORD16 _Value2Temp);  
   UWORD16 GetValue2Temp();

   virtual void StopMonitoringMode();
   virtual void StartMonitoringMode();

   virtual void Blink(e_BOOL Actif);
   virtual void IncreaseValue();
   virtual void DecreaseValue();
   virtual void StartModifMode();
   virtual void ConfirmModifValue(e_BOOL Confirm);
   virtual e_BOOL IncreaseValueOk(UWORD16* Val);
   virtual e_BOOL DecreaseValueOk(UWORD16* Val);
   
};

#endif
