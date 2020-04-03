/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelTwoValueTrig.hpp 		  			   	          	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_LabelTwoValueTrig.cpp  			  		      	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef LabelTwoValueTrigH
#define LabelTwoValueTrigH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_SymbolField.hpp"
#include "HMI_LabelTwoValueLock.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class LabelTwoValueTrig: public LabelTwoValueLock
{

private:
   
   /* Parametres */

   SymbolField FTrig;
   
	e_BOOL 	Trigger,
				Float;

   /* Methodes */

protected:

   /* Parametres */

   /* Methodes */

public:
   
   /* Parametres */

   /* Methodes */

	LabelTwoValueTrig();

	void SetFloat(e_BOOL _Float);
	e_BOOL GetFloat();

	void SetFloatValues(e_BOOL _FloatValues);

	void ShowTrigger();
   void HideTrigger();

   void SetTrigger(e_BOOL Flag);
	void SetColTrigger(UWORD16 Col);

	void SetInvertVideo(e_BOOL _Invert);

	e_BOOL IsTrigger();

	void RefreshValueColumn();

	virtual void StopMonitoringMode();
	virtual void Refresh();
	virtual void Show();
   virtual void Hide();
   virtual void HideAll();
};

#endif
