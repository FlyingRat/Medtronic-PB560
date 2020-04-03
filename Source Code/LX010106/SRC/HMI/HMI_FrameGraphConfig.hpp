/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_FrameGraphConfig.hpp	     		                       	  	*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_FrameGraphConfig.cpp    			             	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef FrameGraphConfigH
#define FrameGraphConfigH


/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_VFrame.hpp"
#include "HMI_Label.hpp"
#include "HMI_LabelOneValueDefault.hpp"
#include "HMI_LabelStringTwoItems.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class FrameGraphConfig : public VFrame

{

private:

   /* Parametres */

   Label LGraphConfig;

   /* Methodes */

protected:

   /* Parametres */

   /* Methodes */

public:

   /* Parametres */

   /* Methodes */

	FrameGraphConfig();

   void init();

   virtual void Show();
   virtual void Hide();
   virtual void RefreshLanguage();

};

#endif
