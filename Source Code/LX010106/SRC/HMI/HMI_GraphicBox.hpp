/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_GraphicBox.hpp	     		                             	  	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_GraphicBox.cpp		      	               	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef GraphicBoxH
#define GraphicBoxH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_DisplayObject.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class GraphicBox: public DisplayObject
{

private:

	/* Parametres */

	/*%C Font [ 0: HeightBox ] */
	UWORD16 Height;

	/*%C Width [ 0: WidthBox ] */
	UWORD16 Width;

	e_BOOL FloodBlack;
	e_BOOL RoundHigh;
	e_BOOL RoundLow;

	/* Methodes */

protected:
     
   /* Parametres */

   /* Methodes */

public:
      
   /* Parametres */

   /* Methodes */

	GraphicBox();
   
   void Init(	UWORD16 Line, 
   				UWORD16 Col, 
   				UWORD16 Height, 
   				UWORD16 Width, 
   				e_BOOL FloodBlack, 
   				e_BOOL RoundHigh, 
   				e_BOOL RoundLow);

	void SetHeight(UWORD16 Height);
	UWORD16 GetHeight();
	 
	void SetWidth(UWORD16 Width);
	UWORD16 GetWidth();
	 
	void SetRoundHigh(e_BOOL RoundHigh);
	e_BOOL GetRoundHigh();

	void SetRoundLow(e_BOOL RoundLow);
	e_BOOL GetRoundLow();

	void SetFloodBlack(e_BOOL FloodBlack);
	e_BOOL IsFloodBlack();

	void RefreshBoxRound(UWORD16 _BackGround);

   
   virtual void Show();
   virtual void Hide();

};

#endif
