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

#ifndef LabelOneValueTrigH
#define LabelOneValueTrigH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_SymbolField.hpp"
#include "HMI_LabelOneValue.hpp"
 
/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class LabelOneValueTrig: public LabelOneValue
{

private:
   
   /* Parametres */

   SymbolField FTrig;

   e_BOOL Trigger;

   /* Methodes */

protected:

   /* Parametres */

   /* Methodes */

public:

   /* Parametres */

   /* Methodes */

   LabelOneValueTrig();

   virtual void Format(UWORD16 NewValue);

   void ShowTrigger();
   void HideTrigger();

   void SetTrigger(e_BOOL Flag);
	void SetColTrigger(UWORD16 Col);
      
   e_BOOL IsTrigger();

   virtual void SetInvertVideo(e_BOOL InvertVideo);

   virtual void Show();
   virtual void Hide();

};

#endif
