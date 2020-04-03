/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_ValueField.hpp 	 						 		 			  	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_ValueField.cpp 			 						     	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef ValueFieldH
#define ValueFieldH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_FieldObject.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class ValueField: public FieldObject
{

private:

	/* Parametres */

	UWORD16 Value, NbDigit, Divider;

	e_BOOL DisplayZero, Float, SignValue;

	/* Methodes */

protected:

	/* Parametres */

	e_BOOL ChildBackgroundEqualParent;

	e_BOOL IEDisplay;

	/* Methodes */

public:

	/* Parametres */

	/* Methodes */

	ValueField();

	ValueField(DisplayObject *Parent);

	void Init(  UWORD16 Line,
               UWORD16 Col,
               UWORD16 Font,
               e_BOOL ReverseVideo,
               UWORD16 Value,
		      	UWORD16 NbNbDigit,
               e_BOOL DisplayZero,
               e_BOOL Float);
	
	virtual void SetValue(UWORD16 Value);
	virtual void ForceValue(UWORD16 Value);
	virtual void StoreValue(UWORD16 Value);
	
	UWORD16 GetValue();
	
	void SetNbDigit(UWORD16 NbDigit);
	UWORD16 GetNbDigit();
	
	void SetDisplayZero(e_BOOL DisplayZero);
	e_BOOL GetDisplayZero();
	
	void SetSignValue(e_BOOL SignValue);
	e_BOOL IsSignValue();

   void SetDivider(UWORD16 _Divider);
   UWORD16 GetDivider();
	
	void SetFloat(e_BOOL Float);
	e_BOOL GetFloat();
	
	void SetIEDisplay(e_BOOL Value);
	void SetChildBackgroundEqualParent(e_BOOL Value);

	virtual void Blink(e_BOOL Actif);
	virtual void Show();
	virtual void Hide();
	virtual void Clear();

};

#endif
