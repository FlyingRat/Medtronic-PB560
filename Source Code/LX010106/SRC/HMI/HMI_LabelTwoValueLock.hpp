/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_LabelTwoValueLock.hpp 		  			   	         	  	  	*/
/*                              	                                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/


/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C																		  						   */
/*%C Classe declaration for HMI_LabelTwoValueLock.cpp  			  		         */
/*%C			                                                                  */
/******************************************************************************/

#ifndef LabelTwoValueLockH
#define LabelTwoValueLockH

/******************************************************************************/
/*                           	INCLUDE                    	      			   */
/******************************************************************************/

#include "HMI_LabelTwoValue.hpp"

/******************************************************************************/
/*                           CONSTANT DECLARATION                    	      */
/******************************************************************************/

class LabelTwoValueLock: public LabelTwoValue
{

private:
  
	/* Parametres */

   /* Methodes */

protected:
  
	/* Parametres */

   /* Methodes */

public:

  
	/* Parametres */

   /* Methodes */
   
   LabelTwoValueLock();
   
   void InitDbAccess(UWORD16 IdParam1, 
   					 e_TYPE_OF_DB_TARGET DbTarget1,
   					 UWORD16 IdParam2, 
   					 e_TYPE_OF_DB_TARGET DbTarget2);

   virtual void Refresh();
   virtual void StartModifMode();
   virtual void ConfirmModifValue(e_BOOL Confirm);
   virtual void StartMonitoringMode();

};

#endif


