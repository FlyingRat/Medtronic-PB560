/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_ParamNode.hpp 			  				 		          	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_ParamNode.cpp 	 					  		      	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef ParamNodeH
#define ParamNodeH
								
/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_Controller.hpp"
extern "C"
{
#include "typedef.h"
}

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

#define IHM_LE
																										  class ParamNode
{

private:

   /* Parametres */

	/*%C Id [ 0: ??? ] */
   UWORD16 Id;

   /* Methodes */

protected:
 
   /* Parametres */
 
   /* Methodes */

public:
   /* Parametres */

   Controller::PController OnButtonUp,
                           OnButtonDown,
                           OnTimeOut,
                           OnButtonValid,
                           OnButtonRefresh,
                           OnButtonLongValid;
   
   /* Methodes */

   ParamNode();

   ParamNode(  UWORD16 Id,
               Controller::PController OnButtonUp,
               Controller::PController OnButtonDown,
               Controller::PController OnTimeOut,
               Controller::PController OnButtonValid,
               Controller::PController OnButtonRefresh,
               Controller::PController OnButtonLongValid);

   UWORD16 GetId() const;
   void SetId(UWORD16 Id);

   void SetOnButtonUp(Controller::PController OnButtonUp);
   void SetOnButtonDown(Controller::PController OnButtonDown);
   void SetOnTimeOut(Controller::PController OnTimeOut);
   void SetOnButtonValid(Controller::PController OnButtonValid);
   void SetOnButtonRefresh(Controller::PController OnButtonRefresh);
   void SetOnButtonLongValid(Controller::PController OnButtonLongValid);

};

#endif
