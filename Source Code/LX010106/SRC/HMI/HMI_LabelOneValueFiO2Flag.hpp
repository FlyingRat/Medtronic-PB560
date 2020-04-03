/******************************************************************************/
/*                                                                            */
/* Project N�  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelOneValueFiO2Flag.hpp		                        	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_LabelOneValueFiO2Flag.cpp                  	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef LabelOneValueFiO2Flag_H
#define LabelOneValueFiO2Flag_H

/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/
#include "HMI_LabelOneValueFlag.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class LabelOneValueFiO2Flag: public LabelOneValueFlag
{

private:

      /* Param�tres */
      e_BOOL   ModifyOn,
               ChangeModeOn;

      /* M�thodes */


protected:

      /* Param�tres */
      /* M�thodes */

public:

      /* Param�tres */

      /* M�thodes */

      LabelOneValueFiO2Flag();

	   void Set100FiO2();
      void SetChangeMode(e_BOOL _ChangeModeOn);
      virtual void Refresh();
      virtual void StartModifMode();
      virtual void ConfirmModifValue(e_BOOL _Confirm);
};

#endif

