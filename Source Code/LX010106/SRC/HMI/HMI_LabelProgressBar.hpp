/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelProgressBar.hpp 	      			             	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_LabelProgressBar.cpp  		  			      	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef LabelProgressBarH
#define LabelProgressBarH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_Label.hpp"
#include "HMI_EditableObject.hpp"
#include "HMI_TextField.hpp"
 
/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class LabelProgressBar: public EditableObject
{

private:

	/* Parametres */

	TextField FSep;

	UBYTE **NameUnit;
   
   UWORD16 PixelValue;
	UWORD16 RealValue;
   UWORD16 ColValue;
   UWORD16 LowLimit;
   UWORD16 LimitDelta;
   
   e_BOOL BipRequest;
	
	/* Methodes */

protected:

	/* Parametres */

	/* Methodes */

public:

	/* Parametres */

	/* Methodes */

	LabelProgressBar();

	void Init(  e_SYMBOL Icon,
               UBYTE **Name,
               UWORD16 Line,
               UWORD16 Col,
               UWORD16 Value);

	void SetSep(UBYTE *Sep);
	UBYTE* GetSep();
	
	virtual void SetValue(UWORD16 Val);
	UWORD16 GetValue();
	
	void SetColSep(UWORD16 ColSep);
	UWORD16 GetColSep();
	
	void SetColValue(UWORD16 ColVal);
	UWORD16 GetColValue();

    e_BOOL GetBipRequest(); 
 	void SetBipRequest(e_BOOL Request);
	
	TextField* GetFSep();
   
   void SetLimits(UWORD16 LowLimit, UWORD16 HighLimit);

	virtual void ConfirmModifValue(e_BOOL Confirm);
	virtual void SetInvertVideo(e_BOOL InvertVideo);
	virtual void Refresh();
	virtual void Show();
	virtual void Hide();
	virtual void Blink(e_BOOL Actif);
	virtual void IncreaseValue();
	virtual void DecreaseValue();
	virtual void StartModifMode();
	virtual void RefreshLanguage();
};

#endif
