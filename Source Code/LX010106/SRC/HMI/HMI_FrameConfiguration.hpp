/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_FrameConfiguration.hpp	  	                             	  	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_FrameConfiguration.cpp                       	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef FrameConfigurationH
#define FrameConfigurationH

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_VFrame.hpp"
#include "HMI_Label.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class FrameConfiguration : public VFrame

{

private:

   /* Parametres */

   Label LConfiguration;
   
   /* Methodes */

protected:

   /* Paramettres */

   /* Methodes */

public:
   /* Paramettres */

   /* Methodes */

	FrameConfiguration();
   
   void init();
   
   virtual void Show();
   virtual void Hide();
   virtual void RefreshLanguage();

   void SetLabel(UBYTE ** Name);

};

#endif
