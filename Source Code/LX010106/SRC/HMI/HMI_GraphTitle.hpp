/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_GraphTitle.hpp	   		                             	  	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_GraphTitle.cpp  	      	               	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef GraphTitleH
#define GraphTitleH


/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_TextField.hpp"
 
/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class GraphTitle: public DisplayObject
{

private:
	
	/* Parametres */

	TextField TFMode;

   UBYTE **NameMode1;
   UBYTE **NameMode2;

   e_BOOL NameMode2Display;

   /* Méthodes */

   UBYTE* GetNameMode(e_MODE_TYPES _Mode);
   UBYTE* GetNameMode1(e_MODE_TYPES _Mode);
   UBYTE* GetNameMode2(e_MODE_TYPES _Mode);


protected:

	/* Parametres */

   /* Methodes */

public:

	/* Parametres */

   /* Methodes */

	GraphTitle();

	void Init(  UWORD16 Line,
					UWORD16 Col,
					UBYTE** NameMode1,
					UBYTE** NameMode2,
               UBYTE** TargetVT);

   virtual void Refresh();
	virtual void Show();
	virtual void Hide();
	virtual void RefreshLanguage();

   e_BOOL IsPressureMode();
	e_BOOL IsChangingMode();

   void SetNameMode2Display(e_BOOL _NameMode2Display);
   e_BOOL IsNameMode2Display();


};

#endif
