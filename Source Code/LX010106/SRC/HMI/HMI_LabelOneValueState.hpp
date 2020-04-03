/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelOneValueState.hpp 	  		                   	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_LabelOneValueState.cpp  		 		          	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef LabelOneValueStateH
#define LabelOneValueStateH
/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_LabelOneValue.hpp"
 
/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class LabelOneValueState: public LabelOneValue
{

private:

   /* Parametres */

   UWORD16 ValueState;

   /* Methodes */

protected:

   /* Parametres */

   /* Methodes */

public:

   /* Parametres */

   /* Methodes */

   LabelOneValueState();

   UWORD16 GetValueState();
   void SetValueState(UWORD16 ValueState);

   virtual void StartModifMode();
   virtual void StopModifMode();
   virtual void ModifNextValue();

};

#endif
