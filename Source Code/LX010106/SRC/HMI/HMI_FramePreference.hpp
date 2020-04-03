/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_FramePreference.hpp	 		  		                       	  	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_FramePreference.cpp    			             	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef FramePreferenceH
#define FramePreferenceH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_VFrame.hpp"
#include "HMI_Label.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class FramePreference : public VFrame

{

private:

   /* Parametres */

   Label LPreferences;

   /* Methodes */

protected:

   /* Parametres */

   /* Methodes */

public:

   /* Parametres */

   /* Methodes */

	FramePreference();

   void init();

   virtual void Show();
   virtual void Hide();
   virtual void RefreshLanguage();

};

#endif
