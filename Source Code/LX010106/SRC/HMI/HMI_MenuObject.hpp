/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_MenuObject.hpp 				  			 		          	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  							*/
/*%C Classe declaration for HMI_MenuObject.cpp 						  		      	*/
/*%C			                                                                  */
/******************************************************************************/

#ifndef MenuObjectH
#define MenuObjectH
								
/******************************************************************************/
/*                           	INCLUDE                    	      			  	*/
/******************************************************************************/

#include "HMI_IhmType.hpp"
extern "C"
{
#include "typedef.h"
#include "enum.h"
}

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class MenuObject
{
private:
   
   /* Parametres */

   e_TYPE_OF_DB_TARGET DbTarget;

   UWORD16 IdParam;
   
   /* Methodes */

protected:

   /* Parametres */

   /* Methodes */

public:

   /* Parametres */
   
   /* Methodes */

   MenuObject();

   void InitDbAccess(UWORD16 IdParam, e_TYPE_OF_DB_TARGET DbTarget);

   void SetIdParam(UWORD16 IdParam);
   UWORD16 GetIdParam();

   void SetDbTarget(e_TYPE_OF_DB_TARGET DbTarget);
   e_TYPE_OF_DB_TARGET GetDbTarget();

   virtual void Lock(e_BOOL Lock);
   virtual void WinFocus();
   virtual void LoseFocus();
   virtual void StartModifMode();
   virtual void StopModifMode();
   virtual void CancelModifMode();
   virtual void IncreaseValue();
   virtual void DecreaseValue();
   virtual void ModifNextValue();

};

#endif
